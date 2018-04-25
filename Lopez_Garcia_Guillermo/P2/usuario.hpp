#ifndef USUARIO_H
#define USUARIO_H

#include "../P1/fecha.hpp"
#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

#include <map>
#include <unordered_map>

class Tarjeta;
class Numero;

class Clave {
    public:
        Clave(const char*);
        Cadena clave() const { return clave_; };
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

class Usuario {
    public:
        typedef std::map<Numero, Tarjeta*> Tarjetas;
        typedef std::unordered_map<Articulo*, unsigned int> Articulos;
        
        Usuario(Cadena ident, Cadena nom, Cadena ape, Cadena direc, Clave c);
        void es_titular_de(Tarjeta& j);
        void no_es_titular_de(Tarjeta& j);
        
        Cadena id() const { return identificador_; }
        Cadena nombre() const { return nombre_; }
        Cadena apellidos() const { return apellidos_; }
        Cadena direccion() const { return direccion_; }
        
        void compra(Articulos& a, unsigned id = 1);
        const Tarjetas& tarjetas() const { return tarjetas_; }
        const Articulos& compra() const { return articulos_; }
        size_t n_articulos() const;
        
        Usuario& operator =(const Usuario& u) = delete;
        Usuario& operator =(Usuario&& u) = delete;
        
        friend std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Usuario& u);
        
        ~Usuario();
        
        class Id_duplicado {
            public:
                Id_duplicado(Cadena idd) {
                    idd_ = idd;
                }
                const Cadena& idd() { return idd_; }
            private:
                Cadena idd_;
        };
    private:
        Cadena identificador_;
        Cadena nombre_;
        Cadena apellidos_;
        Cadena direccion_;
        Clave contrasena_;
        Tarjetas tarjetas_;
        Articulos articulos_;
};

#endif
