#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

// Default configuration file path
const std::string defaultPath = "/tmp/config.txt";

// Network function to receive data via TCP
std::string receiveNetworkData() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        return "";
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        return "";
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);
    
    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return "";
    }
    
    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return "";
    }
    
    std::cout << "TCP Server listening on port 8080..." << std::endl;
    
    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        return "";
    }
    
    // Read data from client
    int valread = read(new_socket, buffer, 1024);
    std::string receivedData(buffer, valread);
    
    close(new_socket);
    close(server_fd);
    
    return receivedData;
}

// Function 1: Validate and sanitize input
std::string validateInput(const std::string& input) {
    std::cout << "Validating input: " << input << std::endl;
    
    // Simulate some validation logic
    if (input.empty()) {
        std::cout << "Warning: Empty input received" << std::endl;
        return "";
    }
    
    // Log the validation attempt
    std::cout << "Input validation completed" << std::endl;
    return input;
}

// Function 2: Check system requirements
std::string checkSystemRequirements(const std::string& path) {
    std::cout << "Checking system requirements for path: " << path << std::endl;
    
    // Simulate system requirement checks
    if (path.length() > 256) {
        std::cout << "Warning: Path too long" << std::endl;
        return "";
    }
    
    std::cout << "System requirements check passed" << std::endl;
    return path;
}

// Function 3: Apply security policies
std::string applySecurityPolicies(const std::string& path) {
    std::cout << "Applying security policies to: " << path << std::endl;
    
    // Simulate security policy application
    if (path.find("..") != std::string::npos) {
        std::cout << "Security warning: Path traversal detected" << std::endl;
    }
    
    std::cout << "Security policies applied" << std::endl;
    return path;
}

// Function 4: Prepare file operation
std::string prepareFileOperation(const std::string& path) {
    std::cout << "Preparing file operation for: " << path << std::endl;
    
    // Simulate file operation preparation
    std::cout << "File operation prepared successfully" << std::endl;
    return path;
}

// Function 5: Execute file operation (SINK - vulnerable function)
void executeFileOperation(const std::string& customPath) {
    std::cout << "Executing file operation with custom path: " << customPath << std::endl;
    
    struct stat fileStat;
    if (stat(defaultPath.c_str(), &fileStat) == 0) {
        std::cout << "Default config file exists and is accessible" << std::endl;
        
        // Remove existing file/directory before creating symlink
        remove(defaultPath.c_str());
        
        // Create symlink from default path to custom path
        if (symlink(customPath.c_str(), defaultPath.c_str()) == 0) {
            std::cout << "Symlink created successfully" << std::endl;
        } else {
            std::cout << "Failed to create symlink" << std::endl;
        }
        
        // Use the default path (now pointing to custom path)
        // SINK CWE 367
        int fd = open(defaultPath.c_str(), O_RDONLY);
        if (fd != -1) {
            char buffer[1024];
            ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
            if (bytesRead > 0) {
                buffer[bytesRead] = '\0';
                std::cout << "File content: " << buffer << std::endl;
            }
            close(fd);
        } else {
            std::cout << "Failed to open file" << std::endl;
        }
    } else {
        std::cout << "Default config file does not exist or is not accessible" << std::endl;
    }
}

// Function 6: Log operation result
void logOperationResult(const std::string& path, bool success) {
    std::cout << "Logging operation result for: " << path << std::endl;
    std::cout << "Operation " << (success ? "succeeded" : "failed") << std::endl;
}

int main() {
    // Receive data from network (source)
    std::string customPath = receiveNetworkData();
    if (customPath.empty()) {
        std::cout << "No data received from network" << std::endl;
        return 1;
    }
    
    std::cout << "Received custom path from network: " << customPath << std::endl;
    
    // Flow through intermediate functions
    std::string validatedPath = validateInput(customPath);
    if (validatedPath.empty()) {
        std::cout << "Input validation failed" << std::endl;
        return 1;
    }
    
    std::string checkedPath = checkSystemRequirements(validatedPath);
    if (checkedPath.empty()) {
        std::cout << "System requirements check failed" << std::endl;
        return 1;
    }
    
    std::string securedPath = applySecurityPolicies(checkedPath);
    if (securedPath.empty()) {
        std::cout << "Security policy application failed" << std::endl;
        return 1;
    }
    
    std::string preparedPath = prepareFileOperation(securedPath);
    if (preparedPath.empty()) {
        std::cout << "File operation preparation failed" << std::endl;
        return 1;
    }
    
    // Execute file operation
    executeFileOperation(preparedPath);
    
    // Log the result
    logOperationResult(preparedPath, true);
    
    return 0;
}