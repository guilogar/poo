
class Usuario {
    public:
        void es_titular_de(Tarjeta& j);
        void no_es_titular_de(Tarjeta& j);
        Cadena id() const;
        Cadena nombre() const;
        Cadena apellidos() const;
        Cadena direccion() const;
        const Tarjetas& tarjetas() const;
        void compra(Articulo& a, unsigned id);
        const Articulos& compra() const;
        size_t n_articulos() const;
    private:
        
}

class Clave {
    public:
        Cadena clave() const;
        bool verifica(const char*);
    private:
        
}
