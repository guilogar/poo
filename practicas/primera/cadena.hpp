#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class Cadena {
    public:
        Cadena(const char* cad, int tamanio);
        Cadena(const char* cad, int init, int tam);
        Cadena(int tamanio, const char caracter);
        Cadena(const char* cad);
        Cadena(int tamanio = 0);
        Cadena(const Cadena& c);
        
        unsigned length() const;
        
        Cadena substr(int init = 0, int tam = 0) const;
        
        char& at(int pos) const;
        char& operator[](int pos) const;
        
        operator const char* () const { return cad_; }
        
        Cadena& operator =(const Cadena& c);
        Cadena& operator =(const char* c);
        Cadena operator +(const char* c);
        Cadena operator +(const char* c) const;
        Cadena& operator +=(const char* c);
        //Cadena& operator +=(const Cadena& c);
        
        bool operator ==(const char* c) const;
        bool operator !=(const char* c) const;
        bool operator  >(const char* c) const;
        bool operator  <(const char* c) const;
        bool operator >=(const char* c) const;
        bool operator <=(const char* c) const;
        
        ~Cadena();
        
        class TamanioInvalido { };
    private:
        int tamanio_;
        char* cad_;
};
