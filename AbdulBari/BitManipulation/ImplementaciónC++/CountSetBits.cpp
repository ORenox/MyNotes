#include <iostream>
#include <bitset> // Cabecera obligatoria

int main(){
    long n = 554481233;
    int cnt=0;

    // Mostrar el número en formato de 8 bits
    std::cout << "En bits:  " << std::bitset<64>(n) << "\n";
    std::cout << "bits:  " << __builtin_popcount(n) << "\n";

    while( n > 0){
        cnt += n & 1;
        n = n >> 1;
    }

    std::cout << "bits Manual:  " << cnt << "\n";
}