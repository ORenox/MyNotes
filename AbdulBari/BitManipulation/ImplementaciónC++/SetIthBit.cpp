#include <iostream>
#include <bitset> // Cabecera obligatoria

int main(){
    int n = 9;
    int i = 7;

    // Mostrar el número en formato de 8 bits
    std::cout << "En 8 bits:  " << std::bitset<8>(n) << "\n";

    n = n | 1 << i;

    std::cout << "En 8 bits:  " << std::bitset<8>(n) << "\n";

}