#include "fecha.hpp"

const char * Fecha::diasSemana[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
const char * Fecha::meses[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

Fecha::Fecha(int dia, int mes, int anno) {
    time_t calendario = time(0);
    tm* tiempoDescompuesto = localtime(&calendario);
    
    (dia == 0) ? dia_ = tiempoDescompuesto->tm_mday : dia_ = dia;
    (mes == 0) ? mes_ = ++tiempoDescompuesto->tm_mon : mes_ = mes;
    (anno == 0) ? anno_ = tiempoDescompuesto->tm_year + 1900 : anno_ = anno;
    
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

int Fecha::dia() const {
    return dia_;
}
int Fecha::mes() const {
    return mes_;
}
int Fecha::anno() const {
    return anno_;
}

const char* Fecha::cadena() const {
    char* fecha = new char[250];
    char* dia_str = new char[2];
    char* anno_str = new char[4];
    
    strcpy(fecha, "");
    
    strcat(fecha, Fecha::diasSemana[this->diaSemana()]);
    strcat(fecha, ", ");
    
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
    
    f = Fecha(fecha_str);
    return is;
}

// Empieza la sobrecarga de operadores.
// Sobrecarga operador igual (=).
Fecha Fecha::operator =(const Fecha& f) {
    dia_ = f.dia();
    mes_ = f.mes();
    anno_ = f.anno();
    return *this;
}

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

bool Fecha::operator ==(const Fecha& f) const {
    return (this->dia() == f.dia() && this->mes() == f.mes() && this->anno() == f.anno());
}

bool Fecha::operator !=(const Fecha& f) const {
    return !(*this == f);
}

bool Fecha::operator >(const Fecha& f) const {
    if(this->anno() == f.anno()) {
        if(this->mes() == f.mes())
            return (this->dia() > f.dia());
        return (this->mes() > f.mes());
    }
    return (this->anno() > f.anno());
}

bool Fecha::operator >=(const Fecha& f) const {
    return (*this > f || *this == f);
}

bool Fecha::operator <(const Fecha& f) const {
    return !(*this >= f);
}

bool Fecha::operator <=(const Fecha& f) const {
    return !(*this > f);
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
