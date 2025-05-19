#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdlib>

#define PORT 9008

void runCommand(const std::string& userCommand) {
    std::cout << "Executing command: " << userCommand << std::endl;

    //SINK
    int result = system(userCommand.c_str());

    if (result == -1) {
        std::cerr << "[!] Failed to execute command\n";
    } else {
        std::cout << "[i] Command executed with return code: " << result << std::endl;
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
            std::string command(buffer);

            // remove newline
            command.erase(std::remove(command.begin(), command.end(), '\n'), command.end());

            runCommand(command);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

/*
To compile and run do:

g++ -std=c++17 -g commandinjection.cpp -o commandinjection

./commandinjection

In another terminal:
echo "whoami" | nc localhost 9008
*/ 