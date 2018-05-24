#ifndef ARTICULO_H
#define ARTICULO_H

#include <iostream>
#include <iomanip>
#include <set>
#include "fecha.hpp"
#include "cadena.hpp"

using namespace std;

class Autor {
    public:
        Autor(Cadena nombre, Cadena apellidos, Cadena direccion);
        Cadena nombre() const { return nombre_; }
        Cadena apellidos() const { return apellidos_; }
        Cadena direccion() const { return direccion_; }
    private:
        Cadena nombre_;
        Cadena apellidos_;
        Cadena direccion_;
};

class Articulo {
    public:
        typedef std::set<Autor*> Autores;
        Articulo(Autores a, Cadena cod, Cadena tit, Fecha f, double pr);
        
        Cadena referencia() const { return cod_referencia_; }
        Cadena titulo() const     { return titulo_; }
        Fecha f_publi() const     { return f_publi_; }
        double precio() const     { return precio_; }
        double& precio()          { return precio_; }
        Autores autores() const   { return a_; }
        
        virtual unsigned stock() const = 0;
        virtual unsigned& stock() = 0;
        virtual void impresion_especifica(std::basic_ostream<char>& os) const = 0;
        
        class Autores_vacios { };
        
        virtual ~Articulo();
    private:
        Autores a_;
        Cadena cod_referencia_;
        Cadena titulo_;
        Fecha f_publi_;
        double precio_;
};

class LibroDigital : public Articulo {
    public:
        LibroDigital(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, Fecha limite);
        Fecha f_expir() const { return limite_; }
        unsigned stock() const { return 0; }
        unsigned& stock() { return p; }
        void impresion_especifica(std::basic_ostream<char>& os) const;
    private:
        unsigned p;
        Fecha limite_;
};

class ArticuloAlmacenable : public Articulo {
    public:
        ArticuloAlmacenable(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, unsigned num = 0);
        unsigned stock() const { return num_ejem_; }
        unsigned& stock() { return num_ejem_; }
        virtual ~ArticuloAlmacenable();
    private:
        unsigned num_ejem_;
};

class Libro : public ArticuloAlmacenable {
    public:
        Libro(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, unsigned num, size_t num_pags = 0);
        size_t n_pag() const { return num_pags_; }
        void impresion_especifica(std::basic_ostream<char>& os) const;
    private:
        size_t num_pags_;
};

class Cederron : public ArticuloAlmacenable {
    public:
        Cederron(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, unsigned num, double tamanio);
        double tam() const { return tamanio_; }
        void impresion_especifica(std::basic_ostream<char>& os) const;
    private:
        double tamanio_;
};

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Articulo& a);

#endif
