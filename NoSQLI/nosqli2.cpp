#include <bsoncxx/json.hpp>
#include <bsoncxx/document/value.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define PORT 9005

void runRoleAccessCheck(const std::string& jsonInput) {
    mongocxx::instance inst{};
    mongocxx::client conn{mongocxx::uri{"mongodb://localhost:27017"}};
    auto db = conn["testdb"];
    auto collection = db["users"];

    bsoncxx::document::value filter = bsoncxx::from_json(jsonInput);
    
    std::cout << "Query: " << jsonInput << std::endl;
    
    //SINK
    auto result = collection.find_one(filter.view());
    if (result) {
        std::cout << "[!] Access granted for: " << bsoncxx::to_json(*result) << std::endl;
    } else {
        std::cout << "[i] Access denied\n";
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[512] = {0};
    int opt = 1;
    int addrlen = sizeof(address);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Listening on port " << PORT << "...\n";

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) >= 0) {
        ssize_t bytesReceived = recv(new_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            runRoleAccessCheck(std::string(buffer));
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

/*
To compile and run do:

g++ -std=c++17 -g nosqli2.cpp -o nosqli2 $(pkg-config --cflags --libs libmongocxx)
./nosqli2

you also need to configure mongo on your machine. After this, do:
mongosh
use testdb
db.users.insertMany([
  { username: "admin", role: "admin", status: "active" },
  { username: "guest", role: "user", status: "active" }
])

In another terminal:
echo '{ "role": { "$ne": "user" }, "status": "active" }' | nc localhost 9005

*/ 