#ifndef USUARIO_CPP
#define USUARIO_CPP

#include "usuario.hpp"
#include <cstring>

extern "C" {
    #include <unistd.h>
}

#include <random>

Clave::Clave(const char* contrasena) {
    if(strlen(contrasena) < 5) throw Incorrecta(CORTA);
    
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
    if(char* pcc = crypt(contrasena, sal)) {
        clave_ = pcc;
    }
    else
        throw Incorrecta(ERROR_CRYPT);
}

Clave::Clave(const Clave& c) {
    clave_ = c.clave();
}

bool Clave::verifica(const char* posible_contrasena) const {
    if(const char* const pcc = crypt(posible_contrasena, clave_.c_str()))
        return clave_ == pcc;
    else
        throw Incorrecta(ERROR_CRYPT);
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Clave& c) {
    os << c.clave();
    return os;
}

Usuario::Usuarios Usuario::usuarios_;

Usuario::Usuario(Cadena ident, Cadena nom, Cadena ape, Cadena direc, Cadena con) {
    if(! this->usuarios_.insert(ident).second)
        throw Id_duplicado(ident);
    
    identificador_ = ident;
    nombre_ = nom;
    apellidos_ = ape;
    direccion_ = direc;
    contrasena_ = Clave(con.c_str()).clave();
}

Usuario::Usuario(Cadena ident, Cadena nom, Cadena ape, Cadena direc, Clave con) {
    if(! usuarios_.insert(ident).second)
        throw Id_duplicado(ident);
    
    identificador_ = ident;
    nombre_ = nom;
    apellidos_ = ape;
    direccion_ = direc;
    contrasena_ = con.clave();
}

Usuario::Usuario(const Usuario* u) {
    identificador_ = u->id();
    nombre_ = u->nombre();
    apellidos_ = u->apellidos();
    direccion_ = u->direccion();
    contrasena_ = u->contrasena_;
}

void Usuario::es_titular_de(Tarjeta& j) {
    if((j.titular() == nullptr || j.titular() == this)) {
        //Tarjetas::iterator it = tarjetas_.begin();
        //tarjetas_.insert(it, std::make_pair(j.numero(), &j));
        tarjetas_.insert(std::make_pair(j.numero(), &j));
    }
}

void Usuario::no_es_titular_de(Tarjeta& j) {
    for(auto i : tarjetas_)
        if (strcmp(i.first, j.numero()) == 0)
            tarjetas_.erase(i.first);
}

void Usuario::compra(Articulo& a, unsigned cant) {
    Articulos::iterator it = articulos_.find(&a);
    if(it == articulos_.end())
        articulos_.insert(std::make_pair(&a, cant));
    else {
        if(cant == 0) articulos_.erase(it);
        else it->second = cant;
    }
}

size_t Usuario::n_articulos() const {
    return articulos_.size();
}

Usuario::~Usuario() {
    for(auto i : tarjetas_)
        i.second->anular_titular();
    usuarios_.erase(usuarios_.find(identificador_));
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Usuario& u) {
    os << u.id() << " " << u.contrasena_ << " " << u.nombre() << " " << u.apellidos() << std::endl;
    os << u.direccion() << std::endl;
    os << "Tarjetas: " << std::endl;
    
    for (auto& i : u.tarjetas())
        os << i.first << " " << *i.second << std::endl;
    
    return os;
}

void mostrar_carro(std::basic_ostream<char>& os, const Usuario& u) {
    Usuario::Usuarios::iterator it = u.usuarios_.find(u.id());
    
    if(it != u.usuarios_.end()) {
        os << "Carrito de la compra de " << u.id() << " [Artículos: " << u.n_articulos() << "] " << "Cant. Articulo" << std::endl;
        os << "=======================================================================================================" << std::endl;
        
        for (auto i : u.compra())
            os << *i.first << std::endl;
    }
}

#endif
