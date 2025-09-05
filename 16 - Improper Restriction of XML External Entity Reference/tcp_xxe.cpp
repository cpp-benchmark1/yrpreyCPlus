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
        return "";
    }
    
    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        std::cerr << "Setsockopt failed" << std::endl;
        return "";
    }
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8094);
    
    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        return "";
    }
    
    // Listen for connections
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        return "";
    }
    
    // Accept connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        std::cerr << "Accept failed" << std::endl;
        return "";
    }
    
    // Read data
    int valread = read(new_socket, buffer, 1024);
    if (valread <= 0) {
        std::cerr << "Read failed" << std::endl;
        return "";
    }
    
    close(new_socket);
    close(server_fd);
    
    return std::string(buffer);
}

// Function 1: Parse configuration filename
std::string parseConfigFilename(const std::string& data) {
    if (data.empty()) {
        std::cout << "Empty configuration filename received" << std::endl;
        return "default.xml";
    }
    
    std::cout << "Parsing configuration filename: " << data << std::endl;
    return data;
}

// Function 2: Validate filename format
std::string validateFilenameFormat(const std::string& filename) {
    if (filename.empty()) {
        std::cout << "Empty filename format" << std::endl;
        return "default.xml";
    }
    
    std::cout << "Validating filename format: " << filename << std::endl;
    return filename;
}

// Function 3: Check filename extension
std::string checkFilenameExtension(const std::string& filename) {
    if (filename.length() < 4) {
        std::cout << "Short filename detected" << std::endl;
    }
    
    if (filename.find(".xml") != std::string::npos) {
        std::cout << "XML extension found in filename" << std::endl;
    } else {
        std::cout << "No XML extension found, adding .xml" << std::endl;
        return filename + ".xml";
    }
    
    std::cout << "Checking filename extension: " << filename << std::endl;
    return filename;
}

// Function 4: Process configuration file (SINK - XXE vulnerability)
xmlDocPtr processConfigFile(const std::string& filename) {
    std::cout << "Processing configuration file: " << filename << std::endl;
    
    // Create XML context
    xmlParserCtxtPtr ctxt = xmlNewParserCtxt();
    if (ctxt == NULL) {
        std::cout << "Failed to create XML parser context" << std::endl;
        return NULL;
    }
    
    // SINK CWE 611
    xmlDocPtr doc = xmlCtxtReadFile(ctxt, filename.c_str(), NULL, XML_PARSE_NOENT | XML_PARSE_DTDLOAD);
    
    if (doc == NULL) {
        std::cout << "Failed to parse XML file: " << filename << std::endl;
    } else {
        std::cout << "Successfully parsed XML configuration file" << std::endl;
    }
    
    xmlFreeParserCtxt(ctxt);
    return doc;
}

void logConfigProcessing(const std::string& filename) {
    std::cout << "Logging configuration processing for file: " << filename << std::endl;
    
    if (filename.length() > 20) {
        std::cout << "Long filename detected" << std::endl;
    }
}

int main() {
    // Initialize libxml2
    xmlInitParser();
    
    // Receive data from network
    std::string networkData = receiveTcpData();
    
    // Process through intermediate functions with conditional flow
    std::string parsedFilename = parseConfigFilename(networkData);
    
    // Conditional flow based on filename
    std::string validatedFilename;
    if (parsedFilename.length() > 3) {
        validatedFilename = validateFilenameFormat(parsedFilename);
    } else {
        std::cout << "Skipping validation for short filename" << std::endl;
        validatedFilename = parsedFilename;
    }
    
    std::string finalFilename;
    if (validatedFilename.find(".") != std::string::npos) {
        finalFilename = checkFilenameExtension(validatedFilename);
    } else {
        std::cout << "Skipping extension check for filename without dots" << std::endl;
        finalFilename = validatedFilename;
    }
    
    // Process configuration file 
    xmlDocPtr configDoc = processConfigFile(finalFilename);
    
    // Log the processing
    logConfigProcessing(finalFilename);
    
    // Clean up
    if (configDoc != NULL) {
        xmlFreeDoc(configDoc);
    }
    
    // Cleanup libxml2
    xmlCleanupParser();
    
    std::cout << std::endl;
    std::cout << "Configuration processing completed" << std::endl;
    
    return 0;
}