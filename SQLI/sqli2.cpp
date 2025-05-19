#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sqlite3.h>
#include <sstream>

#define PORT 9007

void runQuery(const std::string& username, const std::string& password) {
    sqlite3* db;
    sqlite3_stmt* stmt;

    if (sqlite3_open("users.db", &db) != SQLITE_OK) {
        std::cerr << "Failed to open database\n";
        return;
    }

    std::string query = "SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "';";

    //SINK
    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);

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
            std::string input(buffer);
            input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());

            // Espera um formato JSON simples: {"username": "...", "password": "..."}
            std::string user, pass;
            size_t u_start = input.find("\"username\":");
            size_t p_start = input.find("\"password\":");

            if (u_start != std::string::npos && p_start != std::string::npos) {
                size_t u_quote1 = input.find("\"", u_start + 10);
                size_t u_quote2 = input.find("\"", u_quote1 + 1);
                size_t p_quote1 = input.find("\"", p_start + 10);
                size_t p_quote2 = input.find("\"", p_quote1 + 1);

                user = input.substr(u_quote1 + 1, u_quote2 - u_quote1 - 1);
                pass = input.substr(p_quote1 + 1, p_quote2 - p_quote1 - 1);

                runQuery(user, pass);
            } else {
                std::cerr << "[!] Invalid input format\n";
            }
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

/*
To compile and run do:

g++ -std=c++17 -g sqli2.cpp -o sqli2 -lsqlite3 
./sqli

In another terminal:
echo '{"username": "admin", "password": "'\'' OR '\''1'\''='\''1"}' | nc localhost 9007
*/ 