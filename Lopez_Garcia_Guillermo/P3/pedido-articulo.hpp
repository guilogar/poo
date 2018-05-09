#ifndef Pedido_Articulo_H
#define Pedido_Articulo_H

#include "articulo.hpp"
#include "pedido.hpp"

struct OrdenaArticulos {
    bool operator() (Articulo *a1, Articulo *a2) { return a1 > a2; }
};

struct OrdenaPedidos {
    bool operator() (int n1, int n2) { return n1 < n2; }
};

class Pedido_Articulo {
    public:
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemPedidos;
        typedef std::map<Pedido*, ItemPedidos, OrdenaPedidos> Pedidos;
        
        void pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad = 1);
        void pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad = 1);
        const ItemsPedidos detalle(Pedido& p) const;
        const Pedidos ventas(Articulo& a, double precio, unsigned cantidad);
        
        const ItemPedidos detalle(Pedido& p) const;
        const Pedidos ventas(Articulo& a) const;
        //const ItemPedidos detalle(Pedido& p);
        //const Pedidos ventas(Articulo& a);
        
        std::basic_ostream<char>& mostrarDetallesPedidos(std::basic_ostream<char>& os);
        std::basic_ostream<char>& mostrarVentasArticulos(std::basic_ostream<char>& os);
    private:
        Pedidos pedidos_;
};

#endif
