#include "cadena.hpp"

// Constructores
Cadena::Cadena(const char* cad, int tamanio) {
    (tamanio < 0) ? throw TamanioInvalido () : tamanio_ = tamanio;
    
    cad_ = new char[tamanio_ + 1];
    for (int i = 0; i < tamanio_ && cad[i] != '\0'; i++) { cad_[i] = cad[i]; }
    cad_[tamanio_] = '\0';
}

Cadena::Cadena(const char* cad, int init, int tam) {
    (tam < 0) ? throw TamanioInvalido () : tamanio_ = tam;
    
    cad_ = new char[tam + 1];
    for (int i = init, j = 0; i < init+tam && cad[i] != '\0'; i++, j++) { cad_[j] = cad[i]; }
    cad_[tam] = '\0';
}

Cadena::Cadena(int tamanio, const char caracter) {
    (tamanio < 0) ? throw TamanioInvalido () : tamanio_ = tamanio;
    
    cad_ = new char[tamanio_ + 1];
    for (int i = 0; i < tamanio_ - 1; i++) { cad_[i] = caracter; }
    cad_[tamanio_] = '\0';
}

Cadena::Cadena(const char* cad) {
    int tamanio = 0;
    cad_ = new char[strlen(cad)];
    
    while (cad[tamanio] != '\0') {
        cad_[tamanio] = cad[tamanio];
        tamanio++;
    }
    tamanio_ = tamanio;
    cad_[tamanio_] = '\0';
}

Cadena::Cadena(int tamanio) {
    (tamanio < 0) ? throw TamanioInvalido () : tamanio_ = tamanio;
    
    cad_ = new char[tamanio_ + 1];
    for (int i = 0; i < tamanio_; i++) { cad_[i] = ' '; }
    cad_[tamanio_] = '\0';
}

Cadena::Cadena(const Cadena& c) {
    tamanio_ = c.length();
    cad_ = new char[tamanio_ + 1];
    strcpy(cad_, c.cad_);
}

Cadena::Cadena(const Cadena&& c) {
    tamanio_ = c.length();
    cad_ = new char[tamanio_ + 1];
    strcpy(cad_, c.cad_);
}

// Metodo observador.
unsigned Cadena::length() const {
    return tamanio_;
}

Cadena Cadena::substr(int init, int tam) const {
    if (init + tam >= tamanio_) throw std::out_of_range ("Tamaño maximo excedido.");
    
    char* cc = new char[tam];
    for (int i = init, j = 0; i < init+tam; i++, j++) { cc[j] = cad_[i]; }
    return Cadena(cc);
}

char& Cadena::at(int pos) const {
    if(pos >= tamanio_) throw std::out_of_range ("Tamaño maximo excedido.");
    return (*this)[pos];
}

// Sobrecarga de operadores.
std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Cadena& c) {
    os << c.c_str();
    return os;
}

std::basic_istream<char>& operator >>(std::basic_istream<char>& is, Cadena& c) {
    char* palabra = new char[c.tamanioMaximo_];
    
    is >> palabra;
    delete[] c.cad_;
    c.cad_ = new char[is.gcount()];
    
    strcpy(c.cad_, palabra);
    
    return is;
}

char& Cadena::operator [](int pos) const {
    return *(cad_ + pos);
}

Cadena& Cadena::operator =(const char* c) {
    tamanio_ = strlen(c);
    cad_ = new char[tamanio_];
    strcpy(cad_, c);
    return *this;
}

Cadena& Cadena::operator =(const Cadena& c) {
    if(*this != c) {
        tamanio_ = c.length();
        cad_ = new char[tamanio_ + 1];
        strcpy(cad_, c.cad_);
    }
    return *this;
}

Cadena& Cadena::operator =(const Cadena&& c) {
    if(this != &c) {
        tamanio_ = c.length();
        cad_ = new char[tamanio_ + 1];
        strcpy(cad_, c.cad_);
    }
    return *this;
}

Cadena& Cadena::operator +=(const Cadena& c) {
    char* cc = new char[tamanio_];
    strcpy(cc, cad_);
    
    tamanio_ += c.length();
    delete[] cad_;
    cad_ = new char[tamanio_];
    
    strcpy(cad_, cc);
    strcat(cad_, c.c_str());
    
    return *this;
}

Cadena Cadena::operator +(const Cadena& c) {
    Cadena q(*this);
    q += c;
    return q;
}

Cadena Cadena::operator +(const Cadena& c) const {
    Cadena q(*this);
    q += c;
    return q;
}

bool Cadena::operator >(const Cadena& c) const {
    return strcmp(cad_, c.c_str()) > 0;
}

bool Cadena::operator ==(const Cadena& c) const {
    return strcmp(cad_, c.c_str()) == 0;
}

bool Cadena::operator !=(const Cadena& c) const {
    return !(Cadena(cad_) == Cadena(c));
}

bool Cadena::operator >=(const Cadena& c) const {
    return (Cadena(cad_) > Cadena(c) || Cadena(cad_) == Cadena(c));
}

bool Cadena::operator <(const Cadena& c) const {
    return !(Cadena(cad_) >= Cadena(c));
}

bool Cadena::operator <=(const Cadena& c) const {
    return !(Cadena(cad_) > Cadena(c));
}

// Destructor.
Cadena::~Cadena() {
    if(tamanio_ > 0) {
        delete[] cad_;
        tamanio_ = 0;
        cad_ = nullptr;
    }
}
