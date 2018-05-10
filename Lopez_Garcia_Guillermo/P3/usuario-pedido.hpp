#ifndef Usuario_Pedido_H
#define Usuario_Pedido_H

#include "pedido.hpp"
#include "usuario.hpp"
#include <set>
#include <map>

class Pedido;

class Usuario_Pedido {
    public:
        typedef std::set<Pedido*> Pedidos;
        typedef std::map<Usuario*, Pedidos> Usuarios;
        
        void asocia(Usuario& u, Pedido& p);
        void asocia(Pedido& p, Usuario& u);
        
        const Pedidos pedidos(Usuario& u) const;
        const Usuario cliente(Pedido& p) const;
    private:
        Pedidos pedidos_;
        Usuarios usuarios_;
};

#endif
