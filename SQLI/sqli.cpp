#include <iostream>
#include <string>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sqlite3.h>
#include <algorithm> 

#define PORT 9006

void runQuery(const std::string& username) {
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to open database\n";
        return;
    }

    std::string query = "SELECT * FROM users WHERE username = '" + username + "';";

    //SINK
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

    std::cout << "Query: " << query << std::endl;

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        std::cout << "[!] Authenticated as: " << sqlite3_column_text(stmt, 0) << std::endl;
    } else {
        std::cout << "[i] Authentication failed\n";
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
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
            if (bytesReceived > 0) {
              buffer[bytesReceived] = '\0';
              std::string cleanInput(buffer);
          
              // remove newline (\n) and carriage return (\r)
              cleanInput.erase(std::remove(cleanInput.begin(), cleanInput.end(), '\n'), cleanInput.end());
              cleanInput.erase(std::remove(cleanInput.begin(), cleanInput.end(), '\r'), cleanInput.end());
          
              runQuery(cleanInput);
          }
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}


/*
To compile and run do:

g++ -std=c++17 -g sqli.cpp -o sqli -lsqlite3 
./sqli

In another terminal:
echo "' OR '1'='1" | nc localhost 9006 

*/ 