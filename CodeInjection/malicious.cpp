#include <iostream>

extern "C" void injected() {
    std::cout << "[!!!] Injected code executed!\n";
}
