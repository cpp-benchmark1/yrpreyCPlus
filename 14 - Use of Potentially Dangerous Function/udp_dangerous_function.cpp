#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <ctime>

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
    servaddr.sin_port = htons(8091);
    
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

// Function 1: Parse schedule time data
std::string parseScheduleTimeData(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty schedule time data received" << std::endl;
        return "0";
    }
    
    std::cout << "Parsing schedule time data: " << data << std::endl;
    return data;
}

// Function 2: Validate schedule format
std::string validateScheduleFormat(const std::string& scheduleStr) {
    if (scheduleStr.empty()) {
        std::cout << "Empty schedule format" << std::endl;
        return "0";
    }
    
    std::cout << "Validating schedule format: " << scheduleStr << std::endl;
    return scheduleStr;
}

// Function 3: Check schedule range
std::string checkScheduleRange(const std::string& scheduleStr) {
    int scheduleTime = std::stoi(scheduleStr);
    
    if (scheduleTime < 0) {
        std::cout << "Negative schedule time detected" << std::endl;
    }
    
    if (scheduleTime > 3000000000) {
        std::cout << "High schedule time detected" << std::endl;
    }
    
    std::cout << "Checking schedule range: " << scheduleTime << std::endl;
    return scheduleStr;
}

// Function 4: Apply schedule adjustment
std::string applyScheduleAdjustment(const std::string& scheduleStr) {
    int scheduleTime = std::stoi(scheduleStr);
    
    if (scheduleTime == 0) {
        std::cout << "Zero schedule time, using default adjustment" << std::endl;
    }
    
    if (scheduleTime < 1000000) {
        std::cout << "Low schedule time, applying small adjustment" << std::endl;
    } else {
        std::cout << "High schedule time, applying large adjustment" << std::endl;
    }
    
    std::cout << "Applying schedule adjustment: " << scheduleTime << std::endl;
    return scheduleStr;
}

// Function 5: Process schedule calculation
std::string processScheduleCalculation(const std::string& scheduleStr) {
    int scheduleTime = std::stoi(scheduleStr);
    
    if (scheduleTime % 5 == 0) {
        std::cout << "Schedule time divisible by 5, processing normally" << std::endl;
    } else {
        std::cout << "Schedule time not divisible by 5, applying special processing" << std::endl;
    }
    
    if (scheduleTime > 2000000000) {
        std::cout << "Large schedule time, using advanced calculation" << std::endl;
    }
    
    std::cout << "Processing schedule calculation: " << scheduleTime << std::endl;
    return scheduleStr;
}

// Function 6: Prepare schedule processing
std::string prepareScheduleProcessing(const std::string& scheduleStr) {
    int scheduleTime = std::stoi(scheduleStr);
    
    if (scheduleTime < 0) {
        std::cout << "Preparing processing for negative schedule time" << std::endl;
    }
    
    if (scheduleTime > 4000000000) {
        std::cout << "Preparing processing for very large schedule time" << std::endl;
    }
    
    std::cout << "Preparing schedule processing: " << scheduleTime << std::endl;
    return scheduleStr;
}

int main() {
    // Receive data from network
    std::string networkData = receiveUdpData();
    
    // Process through intermediate functions with conditional flow
    std::string parsedSchedule = parseScheduleTimeData(networkData);
    std::string validatedSchedule = validateScheduleFormat(parsedSchedule);
    
    int scheduleValue = std::stoi(validatedSchedule);
    
    // Conditional flow based on schedule value
    std::string rangedSchedule;
    if (scheduleValue % 3 == 0) {
        rangedSchedule = checkScheduleRange(validatedSchedule);
    } else {
        std::cout << "Skipping range check for non-divisible schedule" << std::endl;
        rangedSchedule = validatedSchedule;
    }
    
    std::string adjustedSchedule;
    if (scheduleValue > 500000000) {
        adjustedSchedule = applyScheduleAdjustment(rangedSchedule);
    } else {
        std::cout << "Skipping adjustment for small schedule" << std::endl;
        adjustedSchedule = rangedSchedule;
    }
    
    std::string calculatedSchedule;
    if (scheduleValue % 7 == 0) {
        calculatedSchedule = processScheduleCalculation(adjustedSchedule);
    } else {
        std::cout << "Skipping calculation for non-divisible schedule" << std::endl;
        calculatedSchedule = adjustedSchedule;
    }
    
    std::string preparedSchedule;
    if (scheduleValue != 0) {
        preparedSchedule = prepareScheduleProcessing(calculatedSchedule);
    } else {
        std::cout << "Skipping preparation for zero schedule" << std::endl;
        preparedSchedule = calculatedSchedule;
    }
    
    // Convert to integer for processing
    int scheduleTime = std::stoi(preparedSchedule);
    
    std::cout << "Processing schedule time: " << scheduleTime << std::endl;
    
    if (scheduleTime > 0) {
        time_t t = scheduleTime;  // Convert to time_t
        // SINK CWE 676
        struct tm* timeinfo = localtime(&t); 
        
        std::cout << "Schedule time processed successfully" << std::endl;
        std::cout << "Scheduled Year: " << (timeinfo->tm_year + 1900) << std::endl;
        std::cout << "Scheduled Month: " << (timeinfo->tm_mon + 1) << std::endl;
        std::cout << "Scheduled Day: " << timeinfo->tm_mday << std::endl;
        std::cout << "Scheduled Hour: " << timeinfo->tm_hour << std::endl;
        std::cout << "Scheduled Minute: " << timeinfo->tm_min << std::endl;
        std::cout << "Scheduled Second: " << timeinfo->tm_sec << std::endl;
    } else {
        std::cout << "Skipping schedule processing for zero or negative time" << std::endl;
    }
    
    std::cout << std::endl;
    std::cout << "Schedule processing completed" << std::endl;
    
    return 0;
}