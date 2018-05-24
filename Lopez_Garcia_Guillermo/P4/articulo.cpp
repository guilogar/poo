#ifndef ARTICULO_CPP
#define ARTICULO_CPP

#include "articulo.hpp"

Autor::Autor(Cadena nombre, Cadena apellidos, Cadena direccion) : nombre_(nombre), apellidos_(apellidos), direccion_(direccion) { }

Articulo::Articulo(const Autores a, Cadena cod, Cadena tit, Fecha f, double pr) {
    
    if(a.empty()) throw Autores_vacios();
    
    a_ = a;
    cod_referencia_ = cod;
    titulo_ = tit;
    f_publi_ = f;
    precio_ = pr;
}

Articulo::~Articulo() {}

LibroDigital::LibroDigital(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, Fecha limite)
                          : Articulo(a, cod, tit, f, pr), limite_(limite) { }

ArticuloAlmacenable::ArticuloAlmacenable(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, unsigned num)
                                        : Articulo(a, cod, tit, f, pr), num_ejem_(num) { }

ArticuloAlmacenable::~ArticuloAlmacenable() {}

Libro::Libro(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, unsigned num, size_t num_pags)
            : ArticuloAlmacenable(a, cod, tit, f, pr, num), num_pags_(num_pags) { }

Cederron::Cederron(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, unsigned num, double tamanio)
                  : ArticuloAlmacenable(a, cod, tit, f, pr, num), tamanio_(tamanio) { }

void LibroDigital::impresion_especifica(std::basic_ostream<char>& os) const {
    os << "A la venta hasta el " << limite_ << "." << std::endl;
}

void Libro::impresion_especifica(std::basic_ostream<char>& os) const {
    os << num_pags_ << " págs., " << stock() << " unidades." << std::endl;
}

void Cederron::impresion_especifica(std::basic_ostream<char>& os) const {
    os << tamanio_ << " MB," << stock() << " unidades." << std::endl;
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Articulo& a) {

    os << "[" << a.referencia() << "] " << "\"" << a.titulo() << "\", de";
    
    for (auto i : a.autores()) os << " " << i->apellidos() << ",";
    
    os << ". " << a.f_publi().anno() << ". " << setiosflags(ios::fixed) <<
    setprecision(2) << a.precio() << " €" << std::endl;
    
    a.impresion_especifica(os);
    os << std::endl;

    return os;
}


#endif
