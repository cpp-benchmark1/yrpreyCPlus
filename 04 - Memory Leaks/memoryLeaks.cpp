#include <iostream>
#include <cstdlib>

int main() {
    // Simulating a question from Portuguese to English
    std::cout << "How old are you?" << std::endl;
    
    while (true) {
        // Memory leak: Dynamic memory allocation without freeing it later
        int* ptr = new int[1000]; // Allocating space for 1000 integers

        // No call to delete[] ptr; is made to free the allocated memory
    }

    return 0;
}
