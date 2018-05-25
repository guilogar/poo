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
        Cadena nombre() const noexcept { return nombre_; }
        Cadena apellidos() const noexcept { return apellidos_; }
        Cadena direccion() const noexcept { return direccion_; }
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
        Fecha f_expir() const { return f_expir_; }
        void impresion_especifica(std::basic_ostream<char>& os) const;
    private:
        Fecha f_expir_;
};

class ArticuloAlmacenable : public Articulo {
    public:
        ArticuloAlmacenable(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, unsigned num = 0);
        unsigned stock() const { return stock_; }
        unsigned& stock() { return stock_; }
        virtual void impresion_especifica(std::basic_ostream<char>& os) const = 0;
        virtual ~ArticuloAlmacenable();
    protected:
        unsigned stock_;
};

class Libro : public ArticuloAlmacenable {
    public:
        Libro(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, size_t num_pags = 0, unsigned num = 0);
        size_t n_pag() const { return n_pag_; }
        void impresion_especifica(std::basic_ostream<char>& os) const;
    private:
        size_t n_pag_;
};

class Cederron : public ArticuloAlmacenable {
    public:
        Cederron(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, double tamanio, unsigned num = 0);
        double tam() const { return tam_; }
        void impresion_especifica(std::basic_ostream<char>& os) const;
    private:
        double tam_;
};

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Articulo& a);

#endif
