#ifndef TARJETA_CPP
#define TARJETA_CPP

#include "tarjeta.hpp"

Numero::Numero(Cadena num) {
    unsigned i;
    Cadena number;
    
    for (i = 0; i < num.length(); i++)
        if(num[i] != ' ' && std::isdigit(num[i]))
            number += num[i];
    for (i = 0; i < number.length(); i++)
        if(!std::isdigit(number[i]))
            break;
    
    if(!luhn(number))
        throw Incorrecto(NO_VALIDO);
    if(i < number.length())
        throw Incorrecto(DIGITOS);
    if(number.length() < 13 || number.length() > 18)
        throw Incorrecto(LONGITUD);
    
    num_troq_ = number;
}

Tarjeta::Tarjeta(Tipo t, Numero n, Usuario& u, Fecha f) : tipo_(t), numero_(n) {
    if(f < Fecha())
        throw Caducada(f);
    usuario_ = &u;
    caducidad_ = f;
    titular_facial_ = u.nombre() + " " + u.apellidos();
}

void Tarjeta::anular_titular() {
    usuario_ = nullptr;
}

bool Tarjeta::operator <(const Tarjeta& t) const {
    return (numero_ < t.numero());
}

Tarjeta::~Tarjeta() {
    if(usuario_ != nullptr) usuario_->no_es_titular_de(*this);
    usuario_ = nullptr;
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Tarjeta::Tipo& t) {
    switch (t) {
        case Tarjeta::Tipo::VISA: os << "VISA"; break;
        case Tarjeta::Tipo::Mastercard: os << "MasterCard"; break;
        case Tarjeta::Tipo::Maestro: os << "Maestro"; break;
        case Tarjeta::Tipo::JCB: os << "JCB"; break;
        case Tarjeta::Tipo::AmericanExpress: os << "AmericanExpress"; break;
        default:
            os << "Error";
    }
    return os;
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Tarjeta& t) {
    os << t.tipo_ << std::endl;
    os << t.numero_ << std::endl;
    os << t.titular_facial_ << std::endl;
    os << "Caduca: ";
    
    if(t.caducidad_.mes() < 10) os << "0";
    os << t.caducidad_.mes() << "/" << (t.caducidad_.anno() % 100);
    
    return os;
}

#endif
