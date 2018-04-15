#include <cstring>
#include <ctime>
#include <iostream>
#include <regex>

class Fecha {
    public:
        static const char * diasSemana[];
        static const char * meses[];
        
        explicit Fecha(int dia = 0, int mes = 0, int anno = 0);
        Fecha(const char* s);
        
        int dia() const;
        int mes() const;
        int anno() const;
        
        //friend inline std::ostream& operator <<(std::ostream& os, const Fecha& f);
        friend std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Fecha& f);
        friend std::basic_istream<char>& operator >>(std::basic_istream<char>& is, Fecha& f);
        
        //operator const char*() const;
        const char* cadena() const;
        
        static const int AnnoMinimo = 1902;
        static const int AnnoMaximo = 2037;
        
        Fecha operator =(const Fecha& f);
        
        Fecha& operator ++();
        Fecha operator ++(int f);
        Fecha& operator --();
        Fecha operator --(int f);
        
        Fecha operator +(int f) const;
        Fecha operator -(int f) const;
        
        Fecha& operator +=(int f);
        Fecha& operator -=(int f);
        
        bool operator ==(const Fecha& f) const;
        bool operator !=(const Fecha& f) const;
        bool operator  >(const Fecha& f) const;
        bool operator  <(const Fecha& f) const;
        bool operator >=(const Fecha& f) const;
        bool operator <=(const Fecha& f) const;
        
        class Invalida {
            public:
                Invalida(const char * motivo = "") : motivo_(motivo) {}
                const char* por_que() const {
                    return motivo_;
                }
            private:
                const char* motivo_;
        };
    private:
        int dia_, mes_, anno_;
        int numSegundosIncremento = 86400;
        
        tm obtenerStructTime() const;
        int diaSemana() const;
};

