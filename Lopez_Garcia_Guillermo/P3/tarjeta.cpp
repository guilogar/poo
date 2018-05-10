#ifndef TARJETA_CPP
#define TARJETA_CPP

#include "tarjeta.hpp"
#include <algorithm>

Numero::Numero(Cadena num) {
    
    if(num.length() == 0) throw Incorrecto(LONGITUD);
    
    auto res = std::remove_if(num.begin(), num.end(), [](unsigned char x) { return std::isspace(x); });
    num = num.substr(0, num.length() - strlen(res));
    res = std::find_if(num.begin(), num.end(), [](char x) { return !std::isdigit(x); });
    
    if(num.length() < 13 || num.length() > 19) throw Incorrecto(LONGITUD);
    if(res != num.end()) throw Incorrecto(DIGITOS);
    if(!luhn(num)) throw Incorrecto(NO_VALIDO);
    
    num_troq_ = num;
}

Tarjeta::Tarjeta(Tipo t, Numero n, Usuario& u, Fecha f) : tipo_(t), numero_(n) {
    if(f < Fecha()) throw Caducada(f);
    
    caducidad_ = f;
    titular_facial_ = u.nombre() + " " + u.apellidos();
    
    usuario_ = &u;
    usuario_->es_titular_de(*this);
}

void Tarjeta::anular_titular() {
    usuario_ = nullptr;
}

bool Tarjeta::operator <(const Tarjeta& t) const {
    return (numero_ < t.numero());
}

Tarjeta::~Tarjeta() {
    if(usuario_ != nullptr)
        usuario_->no_es_titular_de(*this);
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Tarjeta::Tipo& t) {
    switch (t) {
        case Tarjeta::Tipo::VISA: os << "VISA"; break;
        case Tarjeta::Tipo::Mastercard: os << "Mastercard"; break;
        case Tarjeta::Tipo::Maestro: os << "Maestro"; break;
        case Tarjeta::Tipo::JCB: os << "JCB"; break;
        case Tarjeta::Tipo::AmericanExpress: os << "AmericanExpress"; break;
        
        default: os << "Error";
    }
    
    return os;
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Tarjeta& t) {
    os << t.tipo() << std::endl;
    os << t.numero() << std::endl;
    os << t.titular_facial() << std::endl;
    os << "Caduca: ";
    
    if(t.caducidad().mes() < 10) os << "0";
    os << t.caducidad().mes() << "/" << (t.caducidad().anno() % 100);
    
    return os;
}

#endif
