
#include "usuario-pedido.hpp"

void Usuario_Pedido::asocia(const Usuario& u, const Pedido& p) {
    asocia(p, u);
}

void Usuario_Pedido::asocia(const Pedido& p, const Usuario& u) {
    pedidos_.insert(&p);
    
    if(usuarios_.find(&u) != usuarios_.end()) {
        usuarios_.find(&u).insert(&p);
    } else {
        Pedidos pe;
        pe.insert(&p);
        usuarios_.insert(std::make_pair(&u, pe))
    }
}


const Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(const Usuario& u) const {
    return usuarios_.find(&u);
}
Usuario& Usuario_Pedido::cliente(const Pedido& p) const {
    return pedidos_.find(&p)->*(usuario);
}
