#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

// UDP network function to receive data
std::string receiveUdpData() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    char buffer[1024];
    socklen_t len;
    int n;
    
    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return "0";
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    // Configure server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8093);
    
    // Bind socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return "0";
    }
    
    len = sizeof(cliaddr);
    
    // Receive data
    n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, 
                 (struct sockaddr *)&cliaddr, &len);
    if (n <= 0) {
        std::cerr << "Receive failed" << std::endl;
        return "0";
    }
    
    buffer[n] = '\0';
    close(sockfd);
    
    return std::string(buffer);
}

// Function 1: Parse processing index data
int* parseProcessingIndexData(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty processing index data received" << std::endl;
        return new int(0);
    }
    
    int* processingIndex = new int(std::stoi(data));
    std::cout << "Parsing processing index data: " << data << std::endl;
    return processingIndex;
}

// Function 2: Check processing range
int* checkProcessingRange(int* processingIndex) {
    if (*processingIndex < 0) {
        std::cout << "Negative processing index detected" << std::endl;
    }
    
    if (*processingIndex > 1000) {
        std::cout << "High processing index detected" << std::endl;
    }
    
    std::cout << "Checking processing range: " << *processingIndex << std::endl;
    return processingIndex;
}

// Function 3: Process processing calculation
int* processProcessingCalculation(int* processingIndex) {
    if (*processingIndex % 3 == 0) {
        std::cout << "Processing index divisible by 3, processing normally" << std::endl;
    } else {
        std::cout << "Processing index not divisible by 3, applying special processing" << std::endl;
    }
    
    if (*processingIndex > 100) {
        std::cout << "Large processing index, using advanced calculation" << std::endl;
    }
    
    std::cout << "Processing processing calculation: " << *processingIndex << std::endl;
    return processingIndex;
}

// Function 4: Prepare processing index
int* prepareProcessingIndex(int* processingIndex) {
    if (*processingIndex < 0) {
        std::cout << "Preparing processing for negative index" << std::endl;
    }
    
    if (*processingIndex > 5000) {
        std::cout << "Preparing processing for very large index" << std::endl;
    }
    
    std::cout << "Preparing processing index: " << *processingIndex << std::endl;
    
    // Set pointer to NULL if processing index is 0
    if (*processingIndex == 0) {
        processingIndex = nullptr;
        std::cout << "Processing index is 0, setting pointer to NULL" << std::endl;
    }
    
    return processingIndex;
}

int main() {
    // Receive data from network
    std::string networkData = receiveUdpData();
    
    // Process through intermediate functions with conditional flow
    int* parsedProcessingIndex = parseProcessingIndexData(networkData);
    
    // Conditional flow based on processing index
    int* rangedProcessingIndex;
    if (*parsedProcessingIndex % 2 == 0) {
        rangedProcessingIndex = checkProcessingRange(parsedProcessingIndex);
    } else {
        std::cout << "Skipping range check for odd processing index" << std::endl;
        rangedProcessingIndex = parsedProcessingIndex;
    }
    
    int* calculatedProcessingIndex;
    if (*rangedProcessingIndex % 5 == 0) {
        calculatedProcessingIndex = processProcessingCalculation(rangedProcessingIndex);
    } else {
        std::cout << "Skipping calculation for non-divisible processing index" << std::endl;
        calculatedProcessingIndex = rangedProcessingIndex;
    }
    
    int* preparedProcessingIndex = prepareProcessingIndex(calculatedProcessingIndex);
    
    std::cout << "Processing index for execution: " << *preparedProcessingIndex << std::endl;
    
    // SINK CWE 476
    int processingValue = *preparedProcessingIndex;
    
    std::cout << "Processing value accessed: " << processingValue << std::endl;
    
    // Additional processing based on the value
    if (processingValue > 50) {
        std::cout << "High processing value detected" << std::endl;
    }
    
    if (processingValue < 0) {
        std::cout << "Negative processing value detected" << std::endl;
    }
    
    // Clean up memory
    delete parsedProcessingIndex;
    
    std::cout << std::endl;
    std::cout << "Processing index execution completed" << std::endl;
    
    return 0;
}