#include <iostream>
#include <cstdlib>

int main() {
    std::string directoryName;

    // Prompt the user to enter the name of the directory
    std::cout << "Enter the name of the directory you want to create: ";
    std::getline(std::cin, directoryName);  // Code vulnerable to Command Injection
    // You can execute name_directory | ipconfig

    // Command to create the directory using the system function
    std::string command = "mkdir " + directoryName;

    // Execute the command
    int result = system(command.c_str());

    // Check if the command was executed successfully
    if (result == 0) {
        std::cout << "Directory '" << directoryName << "' created successfully!" << std::endl;
    } else {
        std::cerr << "Error creating directory '" << directoryName << "'." << std::endl;
    }

    return 0;
}
