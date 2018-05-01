#ifndef TARJETA_H
#define TARJETA_H

#include "fecha.hpp"
#include "cadena.hpp"
#include "usuario.hpp"
//#include "../luhn.cpp"

#include <locale>
#include <cstring>

class Usuario;

class Numero {
    public:
        Numero(Cadena num);
        operator const char*() const { return num_troq_.c_str(); }
        
        bool operator <(const Numero& n) const {
            return std::stod(num_troq_.c_str()) < std::stod((const char*)n);
        }
        
        enum Razon { LONGITUD, DIGITOS, NO_VALIDO };
        class Incorrecto {
            public:
                Incorrecto(Razon z) : z_(z) {}
                Razon razon() const { return z_; }
            private:
                Razon z_;
        };
    private:
        Cadena num_troq_;
};

class Tarjeta {
    public:
        enum Tipo { VISA, Mastercard, Maestro, JCB, AmericanExpress };
        
        Tarjeta(Tipo t, Numero n, Usuario& u, Fecha f);
        Tarjeta(const Tarjeta&) = delete;
        Tarjeta& operator =(const Tarjeta&) = delete;
        
        Tipo tipo() const { return tipo_; }
        Numero numero() const { return numero_; }
        Fecha caducidad() const { return caducidad_; }
        Cadena titular_facial() const { return titular_facial_; }
        Usuario* titular() const { return usuario_; }
        
        bool operator <(const Tarjeta& t) const;
        
        friend std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Tarjeta& t);
        void anular_titular();
        
        class Caducada {
            public:
                Caducada(Fecha f) : f_(f) { }
                Fecha cuando() const { return f_; }
            private:
                Fecha f_;
        };
        ~Tarjeta();
    private:
        Tipo tipo_;
        Numero numero_;
        Usuario* usuario_;
        Fecha caducidad_;
        Cadena titular_facial_;
};

#endif
