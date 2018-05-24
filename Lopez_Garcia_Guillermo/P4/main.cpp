#include <iostream>
#include <string>
#include "../P1/cadena.cpp"

int main(int argc, const char *argv[])
{
    Cadena ident("pepe");
    std::cout << ident << std::endl;
    
    size_t s = std::hash<std::string>{} ( ident.c_str() );
    std::cout << s << std::endl;
    return 0;
}
