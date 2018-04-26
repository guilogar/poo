#ifndef TARJETA_CPP
#define TARJETA_CPP

#include "tarjeta.hpp"

Tarjeta::Tarjeta(Tipo t, Numero n, Usuario *u, Fecha f) : tipo_(t), numero_(n), usuario_(u) {
    if(f < Fecha())
        throw Caducada(f);
}

Tarjeta::~Tarjeta() {
    
    if(usuario_ != nullptr)
        usuario_->no_es_titular_de(*this);
}

#endif
