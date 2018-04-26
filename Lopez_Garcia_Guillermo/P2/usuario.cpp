#ifndef USUARIO_CPP
#define USUARIO_CPP

#include "usuario.hpp"
#include <cstring>

extern "C" {
    #include <unistd.h>
}

#include <random>

Clave::Clave(const char* contrasena) {
    if(std::strlen(contrasena) < 5) throw Incorrecta(CORTA);
    
    static const char *const cvs = "abcdfghijklmnoprstuvwxyz"
                                   "ABCDEFGHIJKLMNOPQRS"
                                   "TUVWXYZ0123456789/.";
    std::size_t longtd = sizeof(cvs) - 1;
    std::random_device r;
    std::uniform_int_distribution<std::size_t> distribucion(0, longtd - 1);
    char sal[] = {
                    cvs[distribucion.operator()(r)],
                    cvs[distribucion(r)]
                 };
    if(char* pcc = crypt(contrasena, sal))
        clave_ = pcc;
    else
        throw Incorrecta(ERROR_CRYPT);
}

Clave::Clave(const Clave& c) {
    clave_ = c.clave();
}

bool Clave::verifica(const char* posible_contrasena) {
    if(const char* const pcc = crypt(posible_contrasena, clave_.c_str()))
        return clave_ == pcc;
    else
        throw Incorrecta(ERROR_CRYPT);
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Clave& c) {
    os << c.clave();
    return os;
}

Usuario::Usuario(Cadena ident, Cadena nom, Cadena ape, Cadena direc, Clave c) {
    std::hash<std::string>{}(ident.c_str());
    
    //if(! usuarios_.insert(ident, hash(ident)).second)
        //throw Id_duplicado(ident);
    
    identificador_ = ident;
    nombre_ = nom;
    apellidos_ = ape;
    direccion_ = direc;
    contrasena_ = c;
}

void Usuario::es_titular_de(Tarjeta& j) {
    tarjetas_.insert(std::make_pair(j.numero(), &j));
    
}

void Usuario::no_es_titular_de(Tarjeta& j) {
    for(auto i : tarjetas_) {
        if(i.second == &j) {
            tarjetas_.erase(i.first); j.anular_titular();
            break;
        }
    }
}

void Usuario::compra(Articulo& a, unsigned can) {
    articulos_.insert(std::make_pair(&a, can));
}

size_t Usuario::n_articulos() const {
    return articulos_.size();
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Usuario& u) {
    os << u.identificador_ << " " << u.contrasena_ << " " << u.nombre_ << " " << u.apellidos_ << std::endl;
    os << u.direccion_ << std::endl;
    os << "Tarjetas: " << std::endl;
    for (auto& i : u.tarjetas_)
        os << i.first << " " << i.second << std::endl;
    return os;
}

#endif
