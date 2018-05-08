
#include "pedido-articulo.hpp"


void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad = 1) {
    
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad = 1) {
    //pedidos_.insert(std::make_pair(&p, ));
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, Pedido_Articulo::ItemPedidos, Pedido_Articulo::Pedidos) {
    
    return os;
}
