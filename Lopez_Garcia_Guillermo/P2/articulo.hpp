#include "fecha.hpp"
#include "cadena.hpp"

class Articulo {
    public:
        Cadena referencia() const;
        Cadena titulo() const;
        Fecha f_publi() const;
        double precio() const;
        double& precio();
        unsigned stock() const;
        unsigned& stock();
    private:
        
};
