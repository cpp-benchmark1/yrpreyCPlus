 
#include <iostream>
#include <cstdio>
#include <cstring>

int main() {
    char buf[16];

    // Prompt the user to enter input
    std::cout << "Enter some text: ";

    // Using gets which is unsafe and can lead to buffer overflow
    gets(buf);

    // Print the user input using printf, which is vulnerable to format string attacks
    printf(buf);

    return 0;
}
