#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdlib>

#define PORT 9012

int extractIndexFromList(const std::string& input) {
    std::vector<int> numbers;
    std::stringstream ss(input);
    std::string token;

    for (char& c : ss.str()) {
        if (isdigit(c) || c == ',') {
            token += c;
        } else if (!token.empty()) {
            numbers.push_back(std::stoi(token));
            token.clear();
        }
    }

    if (!token.empty()) {
        numbers.push_back(std::stoi(token));
    }

    if (numbers.size() >= 3) {
        return numbers[2];  
    }

    return 0;
}

void writeAtIndex(int index) {
    char buffer[10];
    memset(buffer, '-', sizeof(buffer));

    //SINK
    buffer[index] = 'X';

    std::cout << "Buffer content: ";
    for (int i = 0; i < 10; ++i) {
        std::cout << buffer[i];
    }
    std::cout << std::endl;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char inputBuffer[128] = {0};
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
        ssize_t bytesReceived = recv(new_socket, inputBuffer, sizeof(inputBuffer) - 1, 0);
        if (bytesReceived > 0) {
            inputBuffer[bytesReceived] = '\0';
            std::string input(inputBuffer);
            int index = extractIndexFromList(input);  
            writeAtIndex(index);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

/*
To compile and run do:

g++ -std=c++17 -g oobbw2.cpp -o oobbw2
./oobbw2

In another terminal:
echo "[0, 1, 12, 4]" | nc localhost 9012 

*/ 