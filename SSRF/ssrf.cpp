#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <curl/curl.h>

#define PORT 9010

void performRequest(const std::string& targetUrl) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "[!] Failed to initialize curl\n";
        return;
    }

    curl_easy_setopt(curl, CURLOPT_URL, targetUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    //SINK
    CURLcode res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "[!] Request failed: " << curl_easy_strerror(res) << std::endl;
    } else {
        std::cout << "[i] Request to " << targetUrl << " completed successfully\n";
    }

    curl_easy_cleanup(curl);
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
            std::string url(buffer);
            url.erase(std::remove(url.begin(), url.end(), '\n'), url.end());

            performRequest(url);
        }
    }

    close(new_socket);
    close(server_fd);
    return 0;
}


/*
To compile and run do:

g++ -std=c++17 -g ssrf.cpp -o ssrf -lcurl

./ssrf

In another terminal:
echo "http://example.com" | nc localhost 9010
*/ 