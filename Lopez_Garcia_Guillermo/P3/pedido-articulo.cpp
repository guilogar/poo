
#include "pedido-articulo.hpp"

inline bool OrdenaArticulos::operator() (Articulo* a1, Articulo* a2) const { return a1 > a2; }
inline bool OrdenaPedidos::operator() (Pedido* p1, Pedido* p2) const { return p1 > p2; }// return (p1->numero() > p2->numero()); }

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad) {
    pedir(a, p, precio, cantidad);
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad) {
    if(pedidos_.find(&p) != pedidos_.end()) {
        pedidos_.find(&p)->second.insert(std::make_pair(&a, LineaPedido(precio, cantidad)));
    } else {
        ItemsPedidos items;
        items.insert(std::make_pair(&a, LineaPedido(precio, cantidad)));
        pedidos_.insert(std::make_pair(&p, items));
    }
}
const Pedido_Articulo::ItemsPedidos Pedido_Articulo::detalle(Pedido& p) const {
    //if(pedidos_.find(&p) != pedidos_.end())
    return pedidos_.find(&p)->second;
    //return null;
}
const Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& a, double precio, unsigned cantidad) {
    Pedidos p;
    for (auto i: pedidos_) { // i es un pedido
        ItemsPedidos::iterator it = i.second.find(&a); // it es un ItemsPedidos<Articulo*, LineaPedido>
        if(it != i.second.end() && it->second.precio_venta() == precio && it->second.cantidad() == cantidad) // it.second es un LineaPedido
            p.insert(i);
    }
    return p;
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, Pedido_Articulo::ItemsPedidos ip) {
    
    os << "PVP CANTIDAD Artículo" << std::endl;
    os << "=====================" << std::endl;
    
    double total = 0;
    for (auto i : ip) {
        total += i.second.precio_venta();
        os << i.second.precio_venta() << " € " << i.second.cantidad() << " " << *i.first << std::endl;
    }
    os << "=====================" << std::endl;
    
    char* total_str = new char[3];
    sprintf(total_str, "%.2f", total);
    
    os << "Total " << total_str << " €" << std::endl;
    
    return os;
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, Pedido_Articulo::Pedidos p) {
    
    os << "[Pedidos: " << p.size() << "]" << std::endl;
    os << "============" << std::endl;
    os << "PVP CANTIDAD Fecha de Venta" << std::endl;
    os << "=====================" << std::endl;
    
    double total = 0;
    unsigned cantidad = 0;
    for (auto i : p) {
        total += i.first->total();
        cantidad += i.second.size();
        os << i.first->total() << " € " << i.second.size() << " " << i.first->fecha() << std::endl;
    }
    os << "=====================" << std::endl;
    
    char* total_str = new char[3];
    sprintf(total_str, "%.2f", total);
    
    os << "Total " << total_str << " € " << cantidad << std::endl;
    
    return os;
}

std::basic_ostream<char>& Pedido_Articulo::mostrarDetallePedidos(std::basic_ostream<char>& os) {
    double total = 0;
    for (auto i : pedidos_) {
        os << "Pedido núm. " << i.first->numero() << std::endl;
        os << "Cliente " << i.first->tarjeta()->titular()->id() << "Fecha: " << i.first->fecha() << std::endl;
        os << i.second << i.first << std::endl;
        total += i.first->total();
    }
    
    char* total_str = new char[3];
    sprintf(total_str, "%.2f", total);
    
    os << "TOTAL VENTAS " << total_str << " €"<< std::endl;
    
    return os;
}

std::basic_ostream<char>& Pedido_Articulo::mostrarVentasArticulos(std::basic_ostream<char>& os) {
    
    return os;
}
