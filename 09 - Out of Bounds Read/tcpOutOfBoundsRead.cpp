#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

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
    address.sin_port = htons(8080);
    
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

// Configuration item structure
struct ConfigItem {
    std::string name;
    std::string value;
    bool enabled;
};

// Global configuration array (simulating a configuration system)
ConfigItem configItems[] = {
    {"debug_mode", "false", false},
    {"max_connections", "100", true},
    {"timeout", "30", true},
    {"log_level", "info", true},
    {"backup_enabled", "true", false}
};

// Function 1: Parse network data
std::string parseNetworkData(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty data received" << std::endl;
        return "0";
    }
    
    std::cout << "Parsing network data: " << data << std::endl;
    return data;
}

// Function 2: Validate configuration index
std::string validateConfigIndex(const std::string& indexStr) {
    if (indexStr.empty()) {
        std::cout << "Empty index string" << std::endl;
        return "0";
    }
    
    std::cout << "Validating config index: " << indexStr << std::endl;
    return indexStr;
}

// Function 3: Check configuration bounds
std::string checkConfigBounds(const std::string& indexStr) {
    int index = std::stoi(indexStr);
    
    if (index < 0) {
        std::cout << "Negative index not allowed" << std::endl;
        return "0";
    }
    
    std::cout << "Checking bounds for index: " << index << std::endl;
    return indexStr;
}

// Function 4: Apply configuration filter
std::string applyConfigFilter(const std::string& indexStr) {
    int index = std::stoi(indexStr);
    
    if (index % 2 == 0) {
        std::cout << "Even index" << std::endl;
    } else {
        std::cout << "Odd index" << std::endl;
    }
    
    if (index > 50) {
        std::cout << "High index value detected" << std::endl;
    }
    
    std::cout << "Applying filter for index: " << index << std::endl;
    return indexStr;
}

// Function 5: Process configuration request
std::string processConfigRequest(const std::string& indexStr) {
    int index = std::stoi(indexStr);
    
    if (index == 0) {
        std::cout << "Default configuration requested" << std::endl;
    }
    
    if (index < 10) {
        std::cout << "Low priority configuration" << std::endl;
    } else {
        std::cout << "High priority configuration" << std::endl;
    }
    
    std::cout << "Processing config request for index: " << index << std::endl;
    return indexStr;
}

// Function 6: Get configuration item (SINK - Out-of-bounds read vulnerability)
std::string getConfigItem(const std::string& indexStr) {
    int index = std::stoi(indexStr);
    
    std::cout << "Accessing config item at index: " << index << std::endl;
    
    // SINK CWE 125
    ConfigItem item = configItems[index]; 
    
    std::cout << "Config item name: " << item.name << std::endl;
    std::cout << "Config item value: " << item.value << std::endl;
    std::cout << "Config item enabled: " << (item.enabled ? "true" : "false") << std::endl;
    
    return item.name;
}

// Function 7: Log configuration access
void logConfigAccess(const std::string& configName) {
    if (configName.empty()) {
        std::cout << "Empty config name, skipping log" << std::endl;
        return;
    }
    
    std::cout << "Logging access to configuration: " << configName << std::endl;
    
    if (configName.length() > 20) {
        std::cout << "Long config name detected" << std::endl;
    }
}

int main() {
    // Receive data from network
    std::string networkData = receiveTcpData();
    
    // Process through intermediate functions
    std::string parsedData = parseNetworkData(networkData);
    std::string validatedIndex = validateConfigIndex(parsedData);
    std::string boundedIndex = checkConfigBounds(validatedIndex);
    std::string filteredIndex = applyConfigFilter(boundedIndex);
    std::string processedIndex = processConfigRequest(filteredIndex);
    
    // Access configuration (vulnerability occurs here)
    std::string configName = getConfigItem(processedIndex);
    
    // Log the access
    logConfigAccess(configName);
    
    std::cout << std::endl;
    std::cout << "Configuration access completed" << std::endl;
    
    return 0;
}