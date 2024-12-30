#include <iostream>

int main(int argc, char* argv[]) {
    char a, b;

    a = -128;

    std::cout << static_cast<int>(a) << std::endl;

    b = a - 1; // Underflow occurs here

    std::cout << static_cast<int>(b) << std::endl;

    return 0;
}
