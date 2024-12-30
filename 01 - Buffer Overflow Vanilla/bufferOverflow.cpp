#include <iostream>
#include <cstring>
#include <windows.h>

int main() {

    char buffer[5];  // Set a buffer size 5
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Sets the text color to red
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);    
    
    std::cout << "Enter a maximum of 5 characters: ";
    std::cin >> buffer;  // Possible overflow here if input is longer than 5 characters
    std::cout << "Typed characters: " << buffer;

    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);    
    
    return 0;
    
}
