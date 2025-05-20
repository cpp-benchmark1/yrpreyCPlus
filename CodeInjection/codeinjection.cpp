#include <iostream>
#include <string>
#include <dlfcn.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <algorithm>

#define PORT 9008

void runDynamicCode(const std::string& libPath) {
    std::cout << "Loading dynamic library: " << libPath << std::endl;

    void* handle = dlopen(libPath.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "[!] Failed to load library\n";
        return;
    }
    
    typedef void (*func_t)();
    // SINK
    func_t injectedFunction = (func_t)dlsym(handle, "injected");

    if (injectedFunction) {
        injectedFunction();  // Execução de código injetado
    } else {
        std::cerr << "[!] Symbol 'injected' not found\n";
    }

    dlclose(handle);
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
            std::string libPath(buffer);
            libPath.erase(std::remove(libPath.begin(), libPath.end(), '\n'), libPath.end());

            runDynamicCode(libPath);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}

/*
To compile and run do:

g++ -std=c++17 -g codeinjection.cpp -o codeinjection -ldl

./codeinjection

In another terminal:
echo "./libmalicious.so" | nc localhost 9008
*/ 