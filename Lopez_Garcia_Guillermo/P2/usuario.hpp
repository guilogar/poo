#ifndef USUARIO_H
#define USUARIO_H

#include "fecha.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

class Tarjeta;

class Usuario {
    public:
        void es_titular_de(Tarjeta& j);
        void no_es_titular_de(Tarjeta& j);
        Cadena id() const;
        Cadena nombre() const;
        Cadena apellidos() const;
        Cadena direccion() const;
        const Tarjeta& tarjetas() const;
        void compra(Articulo& a, unsigned id);
        const Articulo& compra() const;
        size_t n_articulos() const;
    private:
        
};

class Clave {
    public:
        Clave(const char*);
        Cadena clave() const;
        bool verifica(const char*);
        
        enum Razon {CORTA, ERROR_CRYPT};
        class Incorrecta {
            public:
                Incorrecta(Razon z) : z_(z) { }
            private:
                Razon z_;
        };
    private:
        Cadena clave_;
};
#endif
