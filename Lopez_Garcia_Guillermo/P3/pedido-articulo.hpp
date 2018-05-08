#ifndef Pedido_Articulo_H
#define Pedido_Articulo_H

class Pedido_Articulo {
    public:
        typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemPedidos;
        typedef std::set<Pedido*> Pedidos;
        
        void pedir(Pedido& p, Articulo& a, double precio, unsigned cantidad = 1);
        void pedir(Articulo& a, Pedido& p, double precio, unsigned cantidad = 1);
        
        const ItemPedidos detalle(Pedido& p) const;
        const Pedidos ventas(Articulo& a) const;
        //const ItemPedidos detalle(Pedido& p);
        //const Pedidos ventas(Articulo& a);
    private:
        std::map<Pedido*, ItemPedidos, OrdenaPedidos> pedidos_;
};

#endif
