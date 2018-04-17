
class Tarjeta {
    public:
        Tipo tipo() const;
        Numero numero() const;
        Fecha caducidad() const;
        Cadena titular_facial() const;
        const Usuario* titular() const;
    private:
        
}
