#include <iostream>
#include <string>

int main() {
    std::string user_input;

    std::cout << "Enter a string without a null terminator: ";
    std::getline(std::cin, user_input);

    // Exibindo o último caractere da string
    if (!user_input.empty()) {
        std::cout << "Last character of the string: " << user_input[user_input.length() - 1] << std::endl;
    } else {
        std::cout << "Empty string entered." << std::endl;
    }

    return 0;
}
