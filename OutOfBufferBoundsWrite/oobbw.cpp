#include <iostream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdlib>

#define PORT 9002

void writeAtIndex(int index) {
    char buffer[10];
    memset(buffer, '-', sizeof(buffer));

    //SINK
    buffer[index] = 'X';  // Out-of-bounds write se index < 0 ou index >= 10

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
    if (server_fd == 0) {
        perror("socket failed");
        return 1;
    }

    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return 1;
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return 1;
    }

    std::cout << "Server listening on port " << PORT << "...\n";

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        return 1;
    }

    ssize_t bytesReceived = recv(new_socket, inputBuffer, sizeof(inputBuffer) - 1, 0);
    if (bytesReceived > 0) {
        inputBuffer[bytesReceived] = '\0';
        int index = std::atoi(inputBuffer); // user-controlled index
        writeAtIndex(index);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

/*
To compile and run do:

g++ -g oobbw.cpp -o oobbw   
./oobbw

In another terminal:
echo "12" | nc localhost 9002 

*/ 

