#include "pedido.hpp"

int Pedido::N_pedidos = 0;  // contador de pedidos

Pedido::Pedido(Usuario_Pedido& usuario_pedido, Pedido_Articulo& pedido_articulo,
               Usuario& u, const Tarjeta& t, const Fecha& fp)
               : num_(N_pedidos + 1), tarjeta_(&t), fecha_(fp), total_(0)
{
    if(u.n_articulos() == 0) throw Vacio(u);    // ¿Carrito vacío?
    if(t.titular() != &u)    throw Impostor(u); // ¿Tarjetita mangada?
    if(t.caducidad() < fp)   throw Tarjeta::Caducada(t.caducidad());
    
    for (auto c : u.compra())                   // c es pair<Articulo*, unsigned> (cantidad)
        if(c.first->stock() < c.second) {       // No hay bastante en el almacén
            const_cast<Usuario::Articulos&>(u.compra()) .clear();
            throw SinStock(*(c.first));
        }
    
    Usuario::Articulos carro = u.compra();
    for(auto c : carro) {
        Articulo* pa = c.first;
        unsigned int cantidad = c.second;
        double precio = pa->precio();
        
        pa->stock() -= cantidad;
        pedido_articulo.pedir(*this, *pa, precio, cantidad);
        total_ += precio * cantidad;
        u.compra(*pa, 0);
    }
    usuario_pedido.asocia(u, *this);
    ++N_pedidos;
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Pedido& p) {
    os << "Núm. pedido: " << p.numero() << std::endl;
    os << "Fecha: " << p.fecha() << std::endl;
    os << "Pagado con: ";
    
    os << p.tarjeta()->tipo() << " n.º: " << p.tarjeta()->numero() << std::endl;
    os << "Importe: " << p.total() << " €"<< std::endl;
    
    return os;
}

LineaPedido::LineaPedido(double precio_venta, unsigned cantidad)
            : precio_venta_(precio_venta), cantidad_(cantidad) {}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const LineaPedido& p) {
    char* precio_str = new char[3];
    sprintf(precio_str, "%.2f", p.precio_venta());
    
    os << precio_str << " €\t" << p.cantidad();
    
    return os;
}
