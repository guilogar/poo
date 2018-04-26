#ifndef TARJETA_H
#define TARJETA_H

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "usuario.hpp"

#include <cstring>

class Usuario;

class Numero {
    public:
        Numero(Cadena num);
        operator const char*() const {
            return num_troq_.c_str();
        }
        
        bool operator <(const Numero& n) {
            return std::stod(num_troq_.c_str()) < std::stod((const char*)n);
        }
        
        enum Razon { LONGITUD, DIGITOS, NO_VALIDO };
        class Incorrecto {
            public:
                Incorrecto(Razon z) : z_(z) {}
                Razon razon() { return z_; }
            private:
                Razon z_;
        };
    private:
        Cadena num_troq_;
};

class Tarjeta {
    public:
        enum Tipo { VISA, Mastercard, Maestro, JCB, AmericanExpress };
        
        Tarjeta(Tipo t, Numero n, Usuario *u, Fecha f);
        Tipo tipo() const { return tipo_; }
        Numero numero() const { return numero_; }
        Fecha caducidad() const { return caducidad_; }
        Cadena titular_facial() const { return titular_facial_; }
        const Usuario* titular() const { return usuario_; }
        
        Tarjeta(const Tarjeta& t) = delete;
        Tarjeta& operator =(const Tarjeta& t) = delete;
        
        void anular_titular() { usuario_ = nullptr; }
        
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
