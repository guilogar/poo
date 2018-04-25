#ifndef ARTICULO_CPP
#define ARTICULO_CPP

#include "articulo.hpp"

Articulo::Articulo(Cadena cod, Cadena tit, Fecha f, double pr, int num) {
    cod_referencia_ = cod;
    titulo_ = tit;
    f_publi_ = f;
    precio_ = pr;
    numero_ejem_ = num;
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Articulo& a) {
    os << "[" << a.cod_referencia_ << "] " << "\"" << a.titulo_ << "\", " << a.f_publi_.anno() << ". " << a.precio_ << " €" << std::endl;
    return os;
}


#endif
