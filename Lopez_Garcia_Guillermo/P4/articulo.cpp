#ifndef ARTICULO_CPP
#define ARTICULO_CPP

#include "articulo.hpp"

Autor::Autor(Cadena nombre, Cadena apellidos, Cadena direccion) : nombre_(nombre), apellidos_(apellidos), direccion_(direccion) { }

Articulo::Articulo(const Autores a, Cadena cod, Cadena tit, Fecha f, double pr)
                  : cod_referencia_(cod), titulo_(tit), f_publi_(f), precio_(pr)
{
    if(a.empty()) throw Autores_vacios();
    a_ = a;
}

Articulo::~Articulo() {}

LibroDigital::LibroDigital(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, Fecha limite)
                          : Articulo(a, cod, tit, f, pr), f_expir_(limite) { }

ArticuloAlmacenable::ArticuloAlmacenable(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, unsigned num)
                                        : Articulo(a, cod, tit, f, pr), stock_(num) { }

ArticuloAlmacenable::~ArticuloAlmacenable() {}

Libro::Libro(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, size_t num_pags, unsigned num)
            : ArticuloAlmacenable(a, cod, tit, f, pr, num), n_pag_(num_pags) { }

Cederron::Cederron(Autores a, Cadena cod, Cadena tit, Fecha f, double pr, double tamanio, unsigned num)
                  : ArticuloAlmacenable(a, cod, tit, f, pr, num), tam_(tamanio) { }

void LibroDigital::impresion_especifica(std::basic_ostream<char>& os) const {
    os << "A la venta hasta el " << f_expir_ << ".";
}

void Libro::impresion_especifica(std::basic_ostream<char>& os) const {
    os << n_pag_ << " págs., " << stock_ << " unidades.";
}

void Cederron::impresion_especifica(std::basic_ostream<char>& os) const {
    os << setiosflags(ios::fixed) << setprecision(0) << tam_ << " MB, " << stock_ << " unidades.";
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Articulo& a) {
    
    os << "[" << a.referencia() << "] " << "\"" << a.titulo() << "\", de";
    
    Cadena c;
    for (auto i : a.autores()) c += Cadena(" ") + i->apellidos() + Cadena(","); // os << " " << i->apellidos() << ",";
    c = c.substr(0, c.length() - 1);
    os << c;
    
    os << ". " << a.f_publi().anno() << ". " << setiosflags(ios::fixed) <<
    setprecision(2) << a.precio() << " €" << "\n\t";
    
    a.impresion_especifica(os);
    
    return os;
}


#endif
