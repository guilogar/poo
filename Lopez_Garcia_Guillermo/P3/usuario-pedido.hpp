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
        
        void asocia(const Usuario& u, const Pedido& p);
        void asocia(const Pedido& p, const Usuario& u);
        
        const Pedidos pedidos(const Usuario& u) const;
        Usuario& cliente(const Pedido& p) const;
    private:
        Pedidos pedidos_;
        Usuarios usuarios_;
};

#endif
