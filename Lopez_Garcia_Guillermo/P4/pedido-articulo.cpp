
#include "pedido-articulo.hpp"

LineaPedido::LineaPedido(double precio_venta, unsigned cantidad)
            : precio_venta_(precio_venta), cantidad_(cantidad) {}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const LineaPedido& p) {
    char* precio_str = new char[3];
    sprintf(precio_str, "%.2f", p.precio_venta());
    
    os << precio_str << " €\t" << p.cantidad();
    
    return os;
}

inline bool OrdenaArticulos::operator() (Articulo* a1, Articulo* a2) const { return a1 > a2; }
inline bool OrdenaPedidos::operator() (Pedido* p1, Pedido* p2) const { return p1->numero() < p2->numero(); }// return (p1->numero() > p2->numero()); }

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad) {
    this->pedir(a, p, precio, cantidad);
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad) {
    if(pedidos_articulos_.find(&p) != pedidos_articulos_.end()) { // Comprueba si el pedido ya esta
        pedidos_articulos_.find(&p)->second.insert(std::make_pair(&a, LineaPedido(precio, cantidad))); // Añade un articulo a ese a ese pedido con su linea de pedido
    } else {
        ItemsPedido items;
        items.insert(std::make_pair(&a, LineaPedido(precio, cantidad))); // Crea un articulo con su linea de pedido
        pedidos_articulos_.insert(std::make_pair(&p, items)); // Crea un pedido con la primera linea de pedido
    }
    
    if(articulos_pedidos_.find(&a) != articulos_pedidos_.end()) { // Comprueba si ya esta el articulo
        articulos_pedidos_.find(&a)->second.insert(std::make_pair(&p, LineaPedido(precio, cantidad))); // Añade un pedido a ese articulo, con su linea de pedido
    } else {
        Pedidos items;
        items.insert(std::make_pair(&p, LineaPedido(precio, cantidad))); // Crea un nuevo articulo con su primer pedido y la linea de pedido
        articulos_pedidos_.insert(std::make_pair(&a, items)); // Inserta el articulo con el pedido y su linea de pedido
    }
}

const Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle(Pedido& p) const {
    if(pedidos_articulos_.find(&p) != pedidos_articulos_.end())
        return pedidos_articulos_.find(&p)->second;
    else
        return ItemsPedido();
}

const Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a) const {
    if(articulos_pedidos_.find(&a) != articulos_pedidos_.end())
        return articulos_pedidos_.find(&a)->second;
    else
        return Pedidos();
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Pedido_Articulo::ItemsPedido& ip) {
    
    os << "PVP CANTIDAD Artículo" << std::endl;
    os << "=====================" << std::endl;
    
    os << setiosflags(ios::fixed) << setprecision(2);
    
    double total = 0;
    for (auto i : ip) {
        total += i.second.precio_venta() * i.second.cantidad();
        os << i.second.precio_venta() << " € " << i.second.cantidad() << " " << *i.first << std::endl;
    }
    os << "Total " << total << " €" << std::endl;
    
    return os;
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Pedido_Articulo::Pedidos& p) {
    
    os << "[Pedidos: " << p.size() << "]" << std::endl;
    os << "===========================" << std::endl;
    os << "PVP CANTIDAD Fecha de Venta" << std::endl;
    os << "===========================" << std::endl;
    os << setiosflags(ios::fixed) << setprecision(2);
    
    double total = 0;
    unsigned cantidad = 0;
    for (auto i : p) {
        total += i.second.precio_venta() * i.second.cantidad();
        cantidad += i.second.cantidad();
        os << i.second.precio_venta() << " € " << i.second.cantidad() << " " << i.first->fecha() << std::endl;
    }
    os << "=====================" << std::endl;
    os << "Total " << total << " € " << cantidad << std::endl;
    
    return os;
}

std::basic_ostream<char>& Pedido_Articulo::mostrarDetallePedidos(std::basic_ostream<char>& os) {
    double total = 0;
    os << setiosflags(ios::fixed) << setprecision(2);
    
    for (auto i : pedidos_articulos_) {
        os << "Pedido núm. " << i.first->numero() << std::endl;
        os << "Cliente " << i.first->tarjeta()->titular()->id() << " Fecha: " << i.first->fecha() << std::endl;
        os << i.second << std::endl;
        total += i.first->total();
    }
    
    os << "TOTAL VENTAS " << total << " €"<< std::endl;
    
    return os;
}

std::basic_ostream<char>& Pedido_Articulo::mostrarVentasArticulos(std::basic_ostream<char>& os) {
    for (auto i : articulos_pedidos_) {
        os << "Ventas de " << *i.first;
        os << i.second << std::endl;
    }
    
    return os;
}
