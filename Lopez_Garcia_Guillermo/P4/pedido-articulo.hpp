#ifndef Pedido_Articulo_H
#define Pedido_Articulo_H

#include "articulo.hpp"
#include "pedido.hpp"
#include <map>

class LineaPedido;
class Pedido;

struct OrdenaArticulos {
    bool operator() (Articulo *a1, Articulo *a2) const;
};

struct OrdenaPedidos {
    bool operator() (Pedido* p1, Pedido* p2) const;
};

class LineaPedido {
    public:
        explicit LineaPedido(double precio_venta, unsigned cantidad = 1);
        double precio_venta() const { return precio_venta_; }
        unsigned cantidad() const { return cantidad_; }
        
    private:
        double precio_venta_;
        unsigned cantidad_;
};

class Pedido_Articulo {
    public:
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef std::map<Pedido*, ItemsPedido, OrdenaPedidos> PedidosArticulos;
        
        typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
        typedef std::map<Articulo*, Pedidos, OrdenaArticulos> ArticulosPedidos;
        
        void pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad = 1);
        void pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad = 1);
        
        std::basic_ostream<char>& mostrarDetallePedidos(std::basic_ostream<char>& os);
        std::basic_ostream<char>& mostrarVentasArticulos(std::basic_ostream<char>& os);
        
        const ItemsPedido detalle(Pedido& p) const;
        const Pedidos ventas(Articulo& a) const;
    private:
        PedidosArticulos pedidos_articulos_;
        ArticulosPedidos articulos_pedidos_;
};

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const LineaPedido& p);
std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Pedido_Articulo::ItemsPedido& ip);
std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Pedido_Articulo::Pedidos& p);

#endif
