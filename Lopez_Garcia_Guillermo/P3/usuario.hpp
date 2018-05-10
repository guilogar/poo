#ifndef USUARIO_H
#define USUARIO_H

#include "fecha.hpp"
#include "cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

#include <map>
#include <unordered_map>
#include <unordered_set>
#include <string>

class Tarjeta;
class Numero;

class Clave {
    public:
        explicit Clave(const char* = "");
        Clave(const Clave& c);
        Cadena clave() const { return clave_; };
        bool verifica(const char*) const;
        
        friend std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Clave& c);
        enum Razon {CORTA, ERROR_CRYPT};
        class Incorrecta {
            public:
                Incorrecta(Razon z) : z_(z) { }
                Razon razon() const { return z_; }
            private:
                Razon z_;
        };
    private:
        Cadena clave_;
};

namespace std {
    template <> struct hash<Cadena> {
        size_t operator()(const Cadena& cad) const { // conversión const char* ->string
            return hash<string>{}(cad.c_str());
        }
    };
}

class Usuario {
    public:
        typedef std::map<Numero, Tarjeta*> Tarjetas;
        typedef std::unordered_map<Articulo*, unsigned int> Articulos;
        typedef std::unordered_set<Cadena> Usuarios;
        static Usuarios usuarios_;
        
        Usuario(Cadena ident, Cadena nom, Cadena ape, Cadena direc, Cadena con);
        Usuario(Cadena ident, Cadena nom, Cadena ape, Cadena direc, Clave con);
        //Usuario(const Usuario* u);
        void es_titular_de(Tarjeta& j);
        void no_es_titular_de(Tarjeta& j);
        
        Cadena id() const { return identificador_; }
        Cadena nombre() const { return nombre_; }
        Cadena apellidos() const { return apellidos_; }
        Cadena direccion() const { return direccion_; }
        
        void compra(Articulo& a, unsigned id = 1);
        
        const Tarjetas& tarjetas() const { return tarjetas_; }
        const Articulos& compra() const { return articulos_; }
        const Tarjetas& tarjetas() { return tarjetas_; }
        const Articulos& compra() { return articulos_; }
        
        size_t n_articulos() const;
        
        Usuario(const Usuario& u) = delete;
        Usuario(Usuario&& u) = default;
        Usuario& operator =(const Usuario& u) = delete;
        Usuario& operator =(Usuario&& u) = delete;
        
        friend std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Usuario& u);
        ~Usuario();
        class Id_duplicado {
            public:
                Id_duplicado(Cadena idd) : idd_(idd) { }
                Cadena idd() const { return idd_; }
            private:
                Cadena idd_;
        };
    private:
        Cadena identificador_;
        Cadena nombre_;
        Cadena apellidos_;
        Cadena direccion_;
        Cadena contrasena_;
        Tarjetas tarjetas_;
        Articulos articulos_;
};

void mostrar_carro(std::basic_ostream<char>&, const Usuario&);

#endif
