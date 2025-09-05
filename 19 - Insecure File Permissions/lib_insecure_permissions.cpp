#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    // Hardcoded sensitive data
    const char* sensitiveData ="DATABASE_PASSWORD=MozApHERC4\n"
                               "API_SECRET=rjHBt3B2Igzb4sS7v4FHX6MhXQQrIabo\n"
                               "ENCRYPTION_KEY=i4Nhuq9bTV2S8Ca8B7lsACBxV5NG7dEQ\n";
    
    
    const char* libFilePath = "/lib/system_secrets.conf";
    
    std::cout << "Creating file at: " << libFilePath << std::endl;
    
    // SINK CWE 732
    int fd = open(libFilePath, O_CREAT | O_WRONLY | O_TRUNC, 0664);
    if (fd == -1) {
        std::cout << "Failed to create library file" << std::endl;
        return 1;
    }
    
    // Write sensitive data to file
    ssize_t bytesWritten = write(fd, sensitiveData, strlen(sensitiveData));
    if (bytesWritten == -1) {
        std::cout << "Failed to write data to library file" << std::endl;
        close(fd);
        return 1;
    }
    
    std::cout << "Successfully wrote " << bytesWritten << " bytes to library file" << std::endl;
    
    // Close file
    close(fd);
    
    return 0;
}