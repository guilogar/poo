#ifndef TARJETA_H
#define TARJETA_H

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "usuario.hpp"

class Usuario;

class Numero {
    public:
        Numero(Cadena num);
        operator const char*() const {
            return num_troq_.c_str();
        }
        
        bool operator <(const Numero& n);
        
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
        //Tipo tipo() const;
        Numero numero() const;
        Fecha caducidad() const;
        Cadena titular_facial() const;
        const Usuario* titular() const;
    private:
        
};

#endif
