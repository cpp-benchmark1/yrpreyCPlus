#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define PORT 9004

void runQuery(const std::string& rawJsonInput) {
  mongocxx::instance inst{};
  mongocxx::client conn{mongocxx::uri{"mongodb://localhost:27017"}};
  auto db = conn["testdb"];
  auto collection = db["users"];

  bsoncxx::document::value query = bsoncxx::from_json(rawJsonInput);
  
  std::cout << "Query: " << rawJsonInput << std::endl;
  
  //SINK
  auto result = collection.find_one(query.view());
  if (result) {
      std::cout << "[!] Authenticated as: " << bsoncxx::to_json(*result) << std::endl;
  } else {
      std::cout << "[i] Authentication failed\n";
  }
}


int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char buffer[256] = {0};
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
            runQuery(std::string(buffer));
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

/*
To compile and run do:

g++ -std=c++17 -g nosqli.cpp -o nosqli $(pkg-config --cflags --libs libmongocxx)
./nosqli 

you also need to configure mongo on your machine. After this, do:
mongosh
use testdb
db.users.insertOne({ username: "admin", password: "secret" })

In another terminal:
echo '{ "username": "admin", "password": { "$ne": null } }' | nc localhost 9004

*/ 

