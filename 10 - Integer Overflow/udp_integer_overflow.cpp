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
    servaddr.sin_port = htons(8083);
    
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

// Function 1: Parse score data
std::string parseScoreData(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty score data received" << std::endl;
        return "0";
    }
    
    std::cout << "Parsing score data: " << data << std::endl;
    return data;
}

// Function 2: Validate score format
std::string validateScoreFormat(const std::string& scoreStr) {
    if (scoreStr.empty()) {
        std::cout << "Empty score format" << std::endl;
        return "0";
    }
    
    std::cout << "Validating score format: " << scoreStr << std::endl;
    return scoreStr;
}

// Function 3: Check score range
std::string checkScoreRange(const std::string& scoreStr) {
    int score = std::stoi(scoreStr);
    
    if (score < 0) {
        std::cout << "Negative score detected" << std::endl;
    }
    
    if (score > 1000) {
        std::cout << "High score detected" << std::endl;
    }
    
    std::cout << "Checking score range: " << score << std::endl;
    return scoreStr;
}

// Function 4: Apply score bonus
std::string applyScoreBonus(const std::string& scoreStr) {
    int score = std::stoi(scoreStr);
    
    if (score == 0) {
        std::cout << "Zero score, no bonus applied" << std::endl;
    }
    
    if (score < 100) {
        std::cout << "Low score, applying small bonus" << std::endl;
    } else {
        std::cout << "High score, applying large bonus" << std::endl;
    }
    
    std::cout << "Applying score bonus: " << score << std::endl;
    return scoreStr;
}

// Function 5: Process score calculation
std::string processScoreCalculation(const std::string& scoreStr) {
    int score = std::stoi(scoreStr);
    
    if (score % 10 == 0) {
        std::cout << "Score divisible by 10, applying special calculation" << std::endl;
    }
    
    if (score > 500) {
        std::cout << "High score, using advanced calculation method" << std::endl;
    }
    
    std::cout << "Processing score calculation: " << score << std::endl;
    return scoreStr;
}

// Function 6: Prepare total score calculation
std::string prepareTotalScoreCalculation(const std::string& scoreStr) {
    int score = std::stoi(scoreStr);
    
    if (score < 0) {
        std::cout << "Preparing calculation for negative score" << std::endl;
    }
    
    if (score > 10000) {
        std::cout << "Preparing calculation for very high score" << std::endl;
    }
    
    std::cout << "Preparing total score calculation: " << score << std::endl;
    return scoreStr;
}

int main() {
    // Receive data from network
    std::string networkData = receiveUdpData();
    
    // Process through intermediate functions
    std::string parsedScore = parseScoreData(networkData);
    std::string validatedScore = validateScoreFormat(parsedScore);
    std::string rangedScore = checkScoreRange(validatedScore);
    std::string bonusScore = applyScoreBonus(rangedScore);
    std::string calculatedScore = processScoreCalculation(bonusScore);
    std::string preparedScore = prepareTotalScoreCalculation(calculatedScore);
    
    // Convert to integer for calculation
    int score = std::stoi(preparedScore);
    
    std::cout << "Calculating total score for: " << score << std::endl;
    
    // Using signed int and no bounds checking
    int baseScore = 1000000;  // Base score to add
    // SINK CWE 190
    int totalScore = score + baseScore;  
    
    std::cout << "Base score: " << baseScore << std::endl;
    std::cout << "Player score: " << score << std::endl;
    std::cout << "Total score calculated: " << totalScore << std::endl;
    
    if (totalScore < 0) {
        std::cout << "WARNING: Integer overflow detected! Total score is negative: " << totalScore << std::endl;
    }
    
    if (totalScore < score) {
        std::cout << "WARNING: Integer wraparound detected! Total is less than input: " << totalScore << std::endl;
    }
    
    // Additional processing based on the total score
    if (totalScore > 2000000) {
        std::cout << "Exceptional score achieved!" << std::endl;
    }
    
    if (totalScore < 0) {
        std::cout << "Invalid negative score detected" << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Score calculation completed" << std::endl;
    
    return 0;
}