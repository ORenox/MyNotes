#include <iostream>

int main() {

    int a = 5;
    int b = 29;

    std::cout<< "Antes"<<"\n";
    std::cout << "a =  " << a << "\n";
    std::cout << "b =  " << b << "\n";

    //a = a ^ b;
    //b = a ^ b;
    //a = a ^ b;
    // simplificando las expreciones tenemos que 
    a = (a ^ b) ^ b;
    b =  (a ^ b) ^ a ;
    std::cout<< "Después"<<"\n";
    std::cout << "a =  " << a << "\n";
    std::cout << "b =  " << b << "\n";
    
    return 0;
}