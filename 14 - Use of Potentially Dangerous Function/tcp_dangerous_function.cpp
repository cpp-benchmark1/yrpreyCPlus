#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <ctime>

// TCP network function to receive data
std::string receiveTcpData() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return "0";
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "Setsockopt failed" << std::endl;
        return "0";
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8090);
    
    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return "0";
    }
    
    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        return "0";
    }
    
    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        std::cerr << "Accept failed" << std::endl;
        return "0";
    }
    
    // Read data
    int valread = read(new_socket, buffer, 1024);
    if (valread <= 0) {
        std::cerr << "Read failed" << std::endl;
        return "0";
    }
    
    close(new_socket);
    close(server_fd);
    
    return std::string(buffer);
}

// Function 1: Parse timestamp data
std::string parseTimestampData(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty timestamp data received" << std::endl;
        return "0";
    }
    
    std::cout << "Parsing timestamp data: " << data << std::endl;
    return data;
}

// Function 2: Validate timestamp format
std::string validateTimestampFormat(const std::string& timestampStr) {
    if (timestampStr.empty()) {
        std::cout << "Empty timestamp format" << std::endl;
        return "0";
    }
    
    std::cout << "Validating timestamp format: " << timestampStr << std::endl;
    return timestampStr;
}

// Function 3: Check timestamp range
std::string checkTimestampRange(const std::string& timestampStr) {
    int timestamp = std::stoi(timestampStr);
    
    if (timestamp < 0) {
        std::cout << "Negative timestamp detected" << std::endl;
    }
    
    if (timestamp > 2000000000) {
        std::cout << "High timestamp detected" << std::endl;
    }
    
    std::cout << "Checking timestamp range: " << timestamp << std::endl;
    return timestampStr;
}

// Function 4: Apply timestamp adjustment
std::string applyTimestampAdjustment(const std::string& timestampStr) {
    int timestamp = std::stoi(timestampStr);
    
    if (timestamp == 0) {
        std::cout << "Zero timestamp, using default adjustment" << std::endl;
    }
    
    if (timestamp < 1000000) {
        std::cout << "Low timestamp, applying small adjustment" << std::endl;
    } else {
        std::cout << "High timestamp, applying large adjustment" << std::endl;
    }
    
    std::cout << "Applying timestamp adjustment: " << timestamp << std::endl;
    return timestampStr;
}

// Function 5: Process timestamp calculation
std::string processTimestampCalculation(const std::string& timestampStr) {
    int timestamp = std::stoi(timestampStr);
    
    if (timestamp % 2 == 0) {
        std::cout << "Even timestamp, processing normally" << std::endl;
    } else {
        std::cout << "Odd timestamp, applying special processing" << std::endl;
    }
    
    if (timestamp > 1000000000) {
        std::cout << "Large timestamp, using advanced calculation" << std::endl;
    }
    
    std::cout << "Processing timestamp calculation: " << timestamp << std::endl;
    return timestampStr;
}

// Function 6: Calculate log timestamp (SINK - Dangerous function vulnerability)
void calculateLogTimestamp(const std::string& timestampStr) {
    int timestamp = std::stoi(timestampStr);
    
    std::cout << "Calculating log timestamp for value: " << timestamp << std::endl;
    
    time_t t = timestamp;  // Convert to time_t
    // SINK CWE 676
    struct tm* timeinfo = localtime(&t);
    
    std::cout << "Log timestamp calculated successfully" << std::endl;
    std::cout << "Year: " << (timeinfo->tm_year + 1900) << std::endl;
    std::cout << "Month: " << (timeinfo->tm_mon + 1) << std::endl;
    std::cout << "Day: " << timeinfo->tm_mday << std::endl;
    std::cout << "Hour: " << timeinfo->tm_hour << std::endl;
    std::cout << "Minute: " << timeinfo->tm_min << std::endl;
    std::cout << "Second: " << timeinfo->tm_sec << std::endl;
}

void logTimestampCalculation() {
    std::cout << "Logging timestamp calculation completion" << std::endl;
}

int main() {
    // Receive data from network
    std::string networkData = receiveTcpData();
    
    // Process through intermediate functions with conditional flow
    std::string parsedTimestamp = parseTimestampData(networkData);
    std::string validatedTimestamp = validateTimestampFormat(parsedTimestamp);
    
    int timestampValue = std::stoi(validatedTimestamp);
    
    // Conditional flow based on timestamp value
    std::string rangedTimestamp;
    if (timestampValue % 2 == 0) {
        rangedTimestamp = checkTimestampRange(validatedTimestamp);
    } else {
        std::cout << "Skipping range check for odd timestamp" << std::endl;
        rangedTimestamp = validatedTimestamp;
    }
    
    std::string adjustedTimestamp;
    if (timestampValue > 1000000) {
        adjustedTimestamp = applyTimestampAdjustment(rangedTimestamp);
    } else {
        std::cout << "Skipping adjustment for small timestamp" << std::endl;
        adjustedTimestamp = rangedTimestamp;
    }
    
    std::string calculatedTimestamp;
    if (timestampValue % 3 == 0) {
        calculatedTimestamp = processTimestampCalculation(adjustedTimestamp);
    } else {
        std::cout << "Skipping calculation for non-divisible timestamp" << std::endl;
        calculatedTimestamp = adjustedTimestamp;
    }
    
    // Calculate log timestamp
    if (timestampValue != 0) {
        calculateLogTimestamp(calculatedTimestamp);
    } else {
        std::cout << "Skipping timestamp calculation for zero value" << std::endl;
    }
    
    // Log the calculation
    logTimestampCalculation();
    
    std::cout << std::endl;
    std::cout << "Log timestamp calculation completed" << std::endl;
    
    return 0;
}