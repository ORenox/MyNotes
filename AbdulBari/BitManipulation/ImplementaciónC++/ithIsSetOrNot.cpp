#include <iostream>
#include <bitset> // Cabecera obligatoria

int main(){

    int n = 13;

    int i = 2;

    // Mostrar el número en formato de 8 bits
    std::cout << "En 8 bits:  " << std::bitset<8>(n) << "\n";

    // Mostrar el número en formato de 16 bits
    std::cout << "En 16 bits: " << std::bitset<16>(n) << "\n";


    //lo que hace este es hacer que el 1 recorra tantos espacios diga i
    //    1101
    //   & 100  <- el uno es al que le afecta el shift
    //   -----
    //    0100  <- puedo ser 0 o cualquier número, por eso compruebo el 0
    if( ( n & ( 1 << i)) != 0){
        std::cout<<"not set"<<"\n";
    }else{
        std::cout<<"set"<<"\n";
    }

    //Tambien se puede hacer shift a la derecha
    //lo que hace esto es que en numero se acorte tantos espacios diga i

    //    0011 <- el número es al que le afecta el shift
    //   &   1  
    //   -----
    //    0001 <- siempre va a ser o 0 o 1

    if( ( ( n >> i) & 1) == 0){
        std::cout<<"not set"<<"\n";
    }else{
        std::cout<<"set"<<"\n";
    }


    
    return 0;
}