#ifndef Pedido_Articulo_H
#define Pedido_Articulo_H

#include "articulo.hpp"
#include "pedido.hpp"

class LineaPedido;
class Pedido;

struct OrdenaArticulos {
    bool operator() (Articulo *a1, Articulo *a2) const;
};

struct OrdenaPedidos {
    bool operator() (Pedido* p1, Pedido* p2) const;
};
/*
 *struct OrdenaArticulos {
 *    bool operator() (Articulo *a1, Articulo *a2) const { return a1 > a2; }
 *};
 *
 *struct OrdenaPedidos {
 *    bool operator() (Pedido* p1, Pedido* p2) const { return p1->numero() < p2->numero(); }
 *};
 */


class Pedido_Articulo {
    public:
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedidos;
        typedef std::map<Pedido*, ItemsPedidos, OrdenaPedidos> Pedidos;
        
        void pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad = 1);
        void pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad = 1);
        const ItemsPedidos detalle(Pedido& p) const;
        const Pedidos ventas(Articulo& a, double precio, unsigned cantidad);
        
        //const Pedidos ventas(Articulo& a) const;
        //const ItemPedidos detalle(Pedido& p);
        //const Pedidos ventas(Articulo& a);
        
        friend std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, ItemsPedidos ip);
        friend std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, Pedidos p);
        
        std::basic_ostream<char>& mostrarDetallePedidos(std::basic_ostream<char>& os);
        std::basic_ostream<char>& mostrarVentasArticulos(std::basic_ostream<char>& os);
    private:
        Pedidos pedidos_;
};

#endif
