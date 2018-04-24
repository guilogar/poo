#include "fecha.hpp"
#include "cadena.hpp"
#include "usuario.hpp"

class Usuario;

class Numero {
    public:
        operator const char*() const {
            
        }
    private:
        
};

class Tarjeta {
    public:
        //Tipo tipo() const;
        Numero numero() const;
        Fecha caducidad() const;
        Cadena titular_facial() const;
        const Usuario* titular() const;
    private:
        
};
