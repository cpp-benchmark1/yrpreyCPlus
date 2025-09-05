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
    servaddr.sin_port = htons(8085);
    
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

// Function 1: Parse credit reduction data
std::string parseCreditReductionData(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty credit reduction data received" << std::endl;
        return "0";
    }
    
    std::cout << "Parsing credit reduction data: " << data << std::endl;
    return data;
}

// Function 2: Validate credit format
std::string validateCreditFormat(const std::string& creditStr) {
    if (creditStr.empty()) {
        std::cout << "Empty credit format" << std::endl;
        return "0";
    }
    
    std::cout << "Validating credit format: " << creditStr << std::endl;
    return creditStr;
}

// Function 3: Check credit range
std::string checkCreditRange(const std::string& creditStr) {
    int credit = std::stoi(creditStr);
    
    if (credit < 0) {
        std::cout << "Negative credit detected" << std::endl;
    }
    
    if (credit > 10000) {
        std::cout << "High credit detected" << std::endl;
    }
    
    std::cout << "Checking credit range: " << credit << std::endl;
    return creditStr;
}

// Function 4: Apply credit adjustment
std::string applyCreditAdjustment(const std::string& creditStr) {
    int credit = std::stoi(creditStr);
    
    if (credit == 0) {
        std::cout << "Zero credit, no adjustment needed" << std::endl;
    }
    
    if (credit < 100) {
        std::cout << "Low credit, applying small adjustment" << std::endl;
    } else {
        std::cout << "High credit, applying large adjustment" << std::endl;
    }
    
    std::cout << "Applying credit adjustment: " << credit << std::endl;
    return creditStr;
}

// Function 5: Process credit calculation
std::string processCreditCalculation(const std::string& creditStr) {
    int credit = std::stoi(creditStr);
    
    if (credit % 2 == 0) {
        std::cout << "Even credit value, processing normally" << std::endl;
    } else {
        std::cout << "Odd credit value, applying special processing" << std::endl;
    }
    
    if (credit > 5000) {
        std::cout << "Large credit, using advanced calculation" << std::endl;
    }
    
    std::cout << "Processing credit calculation: " << credit << std::endl;
    return creditStr;
}

// Function 6: Prepare credit deduction
std::string prepareCreditDeduction(const std::string& creditStr) {
    int credit = std::stoi(creditStr);
    
    if (credit < 0) {
        std::cout << "Preparing deduction for negative credit" << std::endl;
    }
    
    if (credit > 50000) {
        std::cout << "Preparing deduction for very high credit" << std::endl;
    }
    
    std::cout << "Preparing credit deduction: " << credit << std::endl;
    return creditStr;
}

int main() {
    int remainingCredits = 1000;
    // Receive data from network
    std::string networkData = receiveUdpData();
    
    // Process through intermediate functions
    std::string parsedCredit = parseCreditReductionData(networkData);
    std::string validatedCredit = validateCreditFormat(parsedCredit);
    std::string rangedCredit = checkCreditRange(validatedCredit);
    std::string adjustedCredit = applyCreditAdjustment(rangedCredit);
    std::string calculatedCredit = processCreditCalculation(adjustedCredit);
    std::string preparedCredit = prepareCreditDeduction(calculatedCredit);
    
    // Convert to integer for calculation
    int creditReduction = std::stoi(preparedCredit);
    
    std::cout << "Calculating remaining credits after reduction: " << creditReduction << std::endl;
    
    // SINK CWE 191
    remainingCredits -= creditReduction;
    
    std::cout << "Current credits: " << remainingCredits << std::endl;
    std::cout << "Credit reduction: " << creditReduction << std::endl;
    std::cout << "Remaining credits calculated: " << remainingCredits << std::endl;
    std::cout << std::endl;
    std::cout << "Credit calculation completed" << std::endl;
    
    return 0;
}