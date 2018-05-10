
#include "pedido-articulo.hpp"

inline bool OrdenaArticulos::operator() (Articulo* a1, Articulo* a2) const { return a1 > a2; }
inline bool OrdenaPedidos::operator() (Pedido* p1, Pedido* p2) const { return p1 > p2; }// return (p1->numero() > p2->numero()); }

void Pedido_Articulo::pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad) {
    this->pedir(a, p, precio, cantidad);
}

void Pedido_Articulo::pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad) {
    if(pedidos_articulos_.find(&p) != pedidos_articulos_.end()) {
        pedidos_articulos_.find(&p)->second.insert(std::make_pair(&a, LineaPedido(precio, cantidad)));
    } else {
        ItemsPedido items;
        items.insert(std::make_pair(&a, LineaPedido(precio, cantidad)));
        pedidos_articulos_.insert(std::make_pair(&p, items));
    }
    
    if(articulos_pedidos_.find(&a) != articulos_pedidos_.end()) {
        articulos_pedidos_.find(&a)->second.insert(std::make_pair(&p, LineaPedido(precio, cantidad)));
    } else {
        Pedidos items;
        items.insert(std::make_pair(&p, LineaPedido(precio, cantidad)));
        articulos_pedidos_.insert(std::make_pair(&a, items));
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

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Pedido_Articulo::Pedidos& p) {
    
    os << "[Pedidos: " << p.size() << "]" << std::endl;
    os << "============" << std::endl;
    os << "PVP CANTIDAD Fecha de Venta" << std::endl;
    os << "=====================" << std::endl;
    
    double total = 0;
    unsigned cantidad = 0;
    for (auto i : p) {
        total += i.first->total();
        cantidad += i.second.cantidad();
        os << i.first->total() << " € " << i.second.cantidad() << " " << i.first->fecha() << std::endl;
    }
    os << "=====================" << std::endl;
    
    char* total_str = new char[3];
    sprintf(total_str, "%.2f", total);
    
    os << "Total " << total_str << " € " << cantidad << std::endl;
    
    return os;
}

std::basic_ostream<char>& Pedido_Articulo::mostrarDetallePedidos(std::basic_ostream<char>& os) {
    double total = 0;
    for (auto i : pedidos_articulos_) {
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
