#include "pedido.hpp"

int Pedido::N_pedidos = 0;  // contador de pedidos

Pedido::Pedido(Usuario_Pedido& usuario_pedido, Pedido_Articulo& pedido_articulo,
               Usuario& u, const Tarjeta& t, const Fecha& fp)
               : num_(N_pedidos + 1), tarjeta_(&t), fecha_(fp), total_(0)
{
    if(u.n_articulos() == 0) throw Vacio(u);    // ¿Carrito vacío?
    if(t.titular() != &u)    throw Impostor(u); // ¿Tarjetita mangada?
    if(t.caducidad() < fp)   throw Tarjeta::Caducada(t.caducidad());
    
    for (auto c : u.compra()) {                                                      // c es pair<Articulo*, unsigned> (cantidad)
        if(ArticuloAlmacenable *aa = dynamic_cast<ArticuloAlmacenable*>(c.first)) {  // Se comprueba el puntero a ArticuloAlmacen
            if(aa->stock() < c.second) {                                             // No hay bastante en el almacén
                const_cast<Usuario::Articulos&>(u.compra()).clear();
                throw SinStock(*(c.first));
            }
        }
    }
    
    unsigned nle = 0; // numero de libros expirados
    unsigned na = 0;  // numero de articulos con stock
    Usuario::Articulos carro = u.compra();
    for(auto c : carro) {
        Articulo* pa = c.first;
        unsigned int cantidad = c.second;
        double precio = pa->precio();
        
        if(ArticuloAlmacenable *pa = dynamic_cast<ArticuloAlmacenable*>(c.first)) {  // Se comprueba el puntero a ArticuloAlmacen
            pa->stock() -= cantidad;
            pedido_articulo.pedir(*this, *pa, precio, cantidad);
            u.compra(*pa, 0);
            na++;
        } else if(LibroDigital *lg = dynamic_cast<LibroDigital*>(c.first)) {  // Se comprueba el puntero a LibroDigital
            u.compra(*lg, 0);
            if(lg->f_expir() < fp) { nle++; continue; }
            pedido_articulo.pedir(*this, *lg, precio, cantidad);
        }
        total_ += precio * cantidad;
    }
    if(na == 0 && nle > 0) throw Vacio(u);
    
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

