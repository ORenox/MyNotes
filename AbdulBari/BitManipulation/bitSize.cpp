#include <iostream>

int main() {
    // sizeof() nos da el tamaño en BYTES, así que lo multiplicamos por 8
    std::cout << "Bits en char: " << sizeof(char) * 8 << "\n";
    std::cout << "Bits en short: " << sizeof(short) * 8 << "\n";
    std::cout << "Bits en int: " << sizeof(int) * 8 << "\n";
    std::cout << "Bits en long long: " << sizeof(long long) * 8 << "\n";
    
    return 0;
}