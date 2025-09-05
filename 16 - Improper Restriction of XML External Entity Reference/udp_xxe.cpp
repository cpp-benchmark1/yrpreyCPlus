#include <iostream>
#include <string>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <fcntl.h>

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
        return "";
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    // Configure server address
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8095);
    
    // Bind socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return "";
    }
    
    len = sizeof(cliaddr);
    
    // Receive data
    n = recvfrom(sockfd, (char *)buffer, 1024, MSG_WAITALL, 
                 (struct sockaddr *)&cliaddr, &len);
    if (n <= 0) {
        std::cerr << "Receive failed" << std::endl;
        return "";
    }
    
    buffer[n] = '\0';
    close(sockfd);
    
    return std::string(buffer);
}

// Function 1: Parse data filename
std::string parseDataFilename(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty data filename received" << std::endl;
        return "data.xml";
    }
    
    std::cout << "Parsing data filename: " << data << std::endl;
    return data;
}

// Function 2: Sanitize filename
std::string sanitizeFilename(const std::string& filename) {
    if (filename.empty()) {
        std::cout << "Empty filename for sanitization" << std::endl;
        return "data.xml";
    }
    
    std::cout << "Sanitizing filename: " << filename << std::endl;
    return filename;
}

// Function 3: Check file permissions
std::string checkFilePermissions(const std::string& filename) {
    if (filename.length() < 5) {
        std::cout << "Short filename detected" << std::endl;
    }
    
    if (filename.find("/") != std::string::npos) {
        std::cout << "Path separator found in filename" << std::endl;
    }
    
    std::cout << "Checking file permissions for: " << filename << std::endl;
    return filename;
}

// Function 4: Prepare file processing
std::string prepareFileProcessing(const std::string& filename) {
    if (filename.find("..") != std::string::npos) {
        std::cout << "Parent directory reference found" << std::endl;
    }
    
    if (filename.length() > 50) {
        std::cout << "Very long filename detected" << std::endl;
    }
    
    std::cout << "Preparing file processing for: " << filename << std::endl;
    return filename;
}

int main() {
    // Initialize libxml2
    xmlInitParser();
    
    // Receive data from network
    std::string networkData = receiveUdpData();
    
    // Process through intermediate functions with conditional flow
    std::string parsedFilename = parseDataFilename(networkData);
    
    // Conditional flow based on filename
    std::string sanitizedFilename;
    if (parsedFilename.length() > 1) {
        sanitizedFilename = sanitizeFilename(parsedFilename);
    } else {
        std::cout << "Skipping sanitization for single character filename" << std::endl;
        sanitizedFilename = parsedFilename;
    }
    
    std::string checkedFilename;
    if (sanitizedFilename.find(".") != std::string::npos) {
        checkedFilename = checkFilePermissions(sanitizedFilename);
    } else {
        std::cout << "Skipping permission check for filename without extension" << std::endl;
        checkedFilename = sanitizedFilename;
    }
    
    std::string finalFilename = prepareFileProcessing(checkedFilename);
    
    std::cout << "Processing XML data file: " << finalFilename << std::endl;
    
    // Open file descriptor
    int fd = open(finalFilename.c_str(), O_RDONLY);
    if (fd < 0) {
        std::cout << "Failed to open file: " << finalFilename << std::endl;
        xmlCleanupParser();
        return 1;
    }
    
    // SINK CWE 611
    xmlDocPtr doc = xmlReadFd(fd, finalFilename.c_str(), NULL, XML_PARSE_NOENT | XML_PARSE_DTDLOAD);
    
    close(fd);
    
    if (doc == NULL) {
        std::cout << "Failed to parse XML file: " << finalFilename << std::endl;
    } else {
        std::cout << "Successfully parsed XML data file" << std::endl;
        
        // Additional processing based on the parsed document
        xmlNodePtr root = xmlDocGetRootElement(doc);
        if (root != NULL) {
            std::cout << "Root element: " << root->name << std::endl;
        }
    }
    
    // Clean up
    if (doc != NULL) {
        xmlFreeDoc(doc);
    }
    
    // Cleanup libxml2
    xmlCleanupParser();
    
    std::cout << std::endl;
    std::cout << "XML data processing completed" << std::endl;
    
    return 0;
}