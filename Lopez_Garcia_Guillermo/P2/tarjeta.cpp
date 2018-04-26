#ifndef TARJETA_CPP
#define TARJETA_CPP

#include "tarjeta.hpp"
#include "../luhn.cpp"
#include <locale>

Numero::Numero(Cadena num) {
    int i;
    for (i = 0; i < num.length(); i++)
        if(!std::isdigit(num[i]))
            break;
    
    if(i < num.length())
        throw Incorrecto(DIGITOS);
    if(num.length() < 13 || num.length() > 19)
        throw Incorrecto(LONGITUD);
    if(!luhn(num))
        throw Incorrecto(NO_VALIDO);
    
    num_troq_ = num;
}

Tarjeta::Tarjeta(Tipo t, Numero n, Usuario *u, Fecha f) : tipo_(t), numero_(n), usuario_(u) {
    if(f < Fecha())
        throw Caducada(f);
}

bool Tarjeta::operator <(const Tarjeta& t) {
    return (numero_ < t.numero());
}

Tarjeta::~Tarjeta() {
    if(usuario_ != nullptr) usuario_->no_es_titular_de(*this);
    usuario_->~Usuario();
    numero_.~Numero();
    caducidad_.~Fecha();
    titular_facial_.~Cadena();
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
    os << "Caduca: " << t.caducidad_.mes() << "/" << t.caducidad_.anno() << std::endl;
    return os;
}

#endif
