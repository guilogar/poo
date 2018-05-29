#ifndef PEDIDO_H
#define PEDIDO_H

#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"

#include <map>
#include <typeinfo>

class Usuario_Pedido;
class Pedido_Articulo;

class Pedido {
    public:
        static int N_pedidos;
        
        Pedido(Usuario_Pedido& usuario_pedido, Pedido_Articulo& pedido_articulo,
               Usuario& u, const Tarjeta& t, const Fecha& fp = Fecha());
        
        const Tarjeta* tarjeta() { return tarjeta_; }
        
        int numero() const { return num_; }
        const Tarjeta* tarjeta() const { return tarjeta_; }
        Fecha fecha() const { return fecha_; }
        double total() const { return total_; }
        static int n_total_pedidos() { return N_pedidos; }
        
        class Vacio {
            public:
                Vacio(Usuario& u) : u_(u) {}
                Usuario& usuario() const { return u_; }
                Usuario& usuario() { return u_; }
            private:
                Usuario& u_;
        };
        class Impostor {
            public:
                Impostor(Usuario& u) : u_(u) {}
                Usuario& usuario() const { return u_; }
                Usuario& usuario() { return u_; }
            private:
                Usuario& u_;
        };
        class SinStock {
            public:
                SinStock(Articulo& a) : a_(a) {}
                Articulo& articulo() const { return a_; }
                Articulo& articulo() { return a_; }
            private:
                Articulo& a_;
        };
    private:
        int num_;
        const Tarjeta* tarjeta_;
        Fecha fecha_;
        double total_;
};

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Pedido& p);

#endif
