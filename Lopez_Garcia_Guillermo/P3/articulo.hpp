#ifndef ARTICULO_H
#define ARTICULO_H

#include <iostream>
#include <iomanip>
#include "fecha.hpp"
#include "cadena.hpp"

using namespace std;

class Articulo {
    public:
        Articulo(Cadena cod, Cadena tit, Fecha f, double pr, int num);
        Cadena referencia() const { return cod_referencia_; }
        Cadena titulo() const { return titulo_; }
        Fecha f_publi() const { return f_publi_; }
        double precio() const {return precio_; }
        double& precio() { return precio_; }
        unsigned stock() const { return numero_ejem_; }
        unsigned& stock() { return numero_ejem_; }

    private:
        Cadena cod_referencia_;
        Cadena titulo_;
        Fecha f_publi_;
        double precio_;
        unsigned numero_ejem_;
};

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Articulo& a);

#endif
