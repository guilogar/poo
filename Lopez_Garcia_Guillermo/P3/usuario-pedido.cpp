#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(Pedido& p, Usuario& u) {
    pedidos_.insert(&p);
    
    if(usuarios_.find(&u) != usuarios_.end()) {
        usuarios_.find(&u)->second.insert(&p);
    } else {
        Pedidos pe;
        pe.insert(&p);
        usuarios_.insert(std::make_pair(&u, pe));
    }
}

void Usuario_Pedido::asocia(Usuario& u, Pedido& p) {
    this->asocia(p, u);
}

const Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario& u) const {
    return usuarios_.find(&u)->second;
}

const Usuario Usuario_Pedido::cliente(Pedido& p) const {
    if(pedidos_.find(&p) != pedidos_.end())
        return p.tarjeta()->titular();
    else {
        throw Pedido::Vacio();
    }
}
