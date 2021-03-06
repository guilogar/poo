#ifndef FECHA_CPP
#define FECHA_CPP

#include "fecha.hpp"

const char * Fecha::diasSemana[7] = {"domingo", "lunes", "martes", "miércoles", "jueves", "viernes", "sábado"};
const char * Fecha::meses[12] = {"enero", "febrero", "marzo", "abril", "mayo", "junio", "julio", "agosto", "septiembre", "octubre", "noviembre", "diciembre"};

Fecha::Fecha(int dia, int mes, int anno) {
    time_t calendario = time(0);
    tm* tiempoDescompuesto = localtime(&calendario);
    
    (dia == 0) ? dia_ = tiempoDescompuesto->tm_mday : dia_ = dia;
    (mes == 0) ? mes_ = ++tiempoDescompuesto->tm_mon : mes_ = mes;
    (anno == 0) ? anno_ = tiempoDescompuesto->tm_year + 1900 : anno_ = anno;
    
    if(mes_ == 2 || mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11) {
        if(dia_ >= 31)
            throw Invalida ("Día incorrecto.");
    }
    
    if(anno_ < 0 || mes_ < 0 || dia_ < 0)
        throw Invalida ("Día o mes o año totalmente incorrectos.");
    
    if(dia_ > 31 || mes_ > 12)
        throw Invalida ("Día o mes totalmente incorrectos.");
    
    if(mes_ == 2 && dia_ > 29)
        throw Invalida ("Día imposible para el mes actual.");
    
    if(mes_ == 2 && dia_ > 28 && !(anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0))) {
        throw Invalida ("Día imposible para el mes actual.");
    }
    
    if(anno_ < AnnoMinimo || anno_ > AnnoMaximo) {
        throw Invalida ("El año no puede ser menor de 1902 ni mayor de 2037.");
    }
}

Fecha::Fecha(const char* s) {
    int dia, mes, anno;
    bool correct_format = (sscanf(s, "%d/%d/%d", &dia, &mes, &anno) == 3);
    (correct_format) ? *this = Fecha(dia, mes, anno) : throw Invalida("Formato Incorrecto.");
}

inline int Fecha::dia() const noexcept { return dia_; }
inline int Fecha::mes() const noexcept { return mes_; }
inline int Fecha::anno() const noexcept { return anno_; }

const char* Fecha::cadena() const {
    static char* fecha = new char[250];
    char* dia_str = new char[3];
    char* anno_str = new char[5];
    
    strcpy(fecha, "");
    
    strcat(fecha, Fecha::diasSemana[this->diaSemana()]);
    strcat(fecha, " ");
    
    sprintf(dia_str, "%02d", this->dia());
    strcat(fecha, dia_str);
    
    strcat(fecha, " de ");
    strcat(fecha, Fecha::meses[this->mes() - 1]);
    strcat(fecha, " de ");
    
    sprintf(anno_str, "%04d", this->anno());
    strcat(fecha, anno_str);
    
    return fecha;
}

std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Fecha& f) {
    os << f.cadena();
    return os;
}

std::basic_istream<char>& operator >>(std::basic_istream<char>& is, Fecha& f) {
    char* fecha_str = new char[1000];
    
    is.getline(fecha_str, 11);
    
    try {
        f = Fecha(fecha_str);
    } catch(Fecha::Invalida &f) {
        is.setstate(std::ios_base::failbit);
        throw f;
    }
    
    return is;
}

// Empieza la sobrecarga de operadores.
// Sobrecarga operador pre-incremento (++Fecha).
Fecha& Fecha::operator ++() {
    *this += 1;
    return *this;
}

// Sobrecarga operador post-incremento (Fecha++).
Fecha Fecha::operator ++(int f) {
    Fecha self(*this);
    ++(*this);
    return self;
}

// Sobrecarga operador pre-decremento (--Fecha).
Fecha& Fecha::operator --() {
    *this -= 1;
    return *this;
}

// Sobrecarga operador post-decremento (Fecha--).
Fecha Fecha::operator --(int f) {
    Fecha self(*this);
    --(*this);
    return self;
}

// Sobrecarga operador suma (Fecha + int).
Fecha Fecha::operator +(int f) const {
    Fecha suma(*this);
    suma += f;
    return suma;
}

// Sobrecarga operador resta (Fecha - int).
Fecha Fecha::operator -(int f) const {
    Fecha resta(*this);
    resta -= f;
    return resta;
}

// Sobrecarga operador += .
Fecha& Fecha::operator +=(int f) {
    struct tm fecha = obtenerStructTime();
    
    time_t manana = mktime(&fecha) + (numSegundosIncremento * f);
    tm* tiempoDescompuesto = localtime(&manana);
    
    int dia = tiempoDescompuesto->tm_mday;
    int mes = tiempoDescompuesto->tm_mon + 1;
    int anno = tiempoDescompuesto->tm_year + 1900;
    
    *this = Fecha(dia, mes, anno);
    
    return *this;
}

// Sobrecarga operador -= .
Fecha& Fecha::operator -=(int f) {
    (*this) += (f*-1);
    return *this;
}

bool operator ==(const Fecha& p, const Fecha& f) {
    return (p.dia() == f.dia() && p.mes() == f.mes() && p.anno() == f.anno());
}

bool operator !=(const Fecha& p, const Fecha& f) {
    return !(p == f);
}

bool operator >(const Fecha& p, const Fecha& f) {
    if(p.anno() == f.anno()) {
        if(p.mes() == f.mes())
            return (p.dia() > f.dia());
        return (p.mes() > f.mes());
    }
    return (p.anno() > f.anno());
}

bool operator >=(const Fecha& p, const Fecha& f) {
    return (p > f || p == f);
}

bool operator <(const Fecha& p, const Fecha& f) {
    return !(p >= f);
}

bool operator <=(const Fecha& p, const Fecha& f) {
    return !(p > f);
}

// Metodo privado.
tm Fecha::obtenerStructTime() const {
    struct tm hoy = { 0 };
    hoy.tm_mday = dia_;
    hoy.tm_mon = mes_ - 1;
    hoy.tm_year = anno_ - 1900;
    hoy.tm_isdst = -1;

    return hoy;
}
int Fecha::diaSemana() const {
    tm fecha = obtenerStructTime();
    time_t time = mktime(&fecha);
    tm* tiempoDescompuesto = localtime(&time);
    
    return tiempoDescompuesto->tm_wday;
}
#endif
