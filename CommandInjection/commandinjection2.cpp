#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>

#define PORT 9009

void runCommandWithOutput(const std::string& userCommand) {
    std::cout << "Running: " << userCommand << std::endl;

    //SINK
    FILE* pipe = popen(userCommand.c_str(), "r");
    if (!pipe) {
        std::cerr << "[!] Failed to execute command\n";
        return;
    }

    char buffer[128];
    std::cout << "[i] Output:\n";
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        std::cout << buffer;
    }

    pclose(pipe);
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
            std::string command(buffer);

            command.erase(std::remove(command.begin(), command.end(), '\n'), command.end());

            runCommandWithOutput(command);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

/*
To compile and run do:

g++ -std=c++17 -g commandinjection2.cpp -o commandinjection2

./commandinjection2

In another terminal:
echo "ls / && echo hacked" | nc localhost 9009

*/ 