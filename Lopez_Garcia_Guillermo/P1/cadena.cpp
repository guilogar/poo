#ifndef CADENA_CPP
#define CADENA_CPP

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
    for (int i = 0; i < tamanio_; i++) { cad_[i] = caracter; }
    cad_[tamanio_] = '\0';
}

Cadena::Cadena(const char* cad) {
    tamanio_ = strlen(cad);
    cad_ = new char[tamanio_ + 1];
    strcpy(cad_, cad);
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

Cadena::Cadena(Cadena&& c) {
    tamanio_ = c.length();
    cad_ = new char[tamanio_ + 1];
    strcpy(cad_, c.cad_);
    
    c.cad_ = new char[0];
    c.tamanio_ = 0;
}

// Metodo observador.
unsigned Cadena::length() const {
    return tamanio_;
}

Cadena Cadena::substr(int init, int tam) const {
    if (init + tam > tamanio_) throw std::out_of_range ("Tamaño maximo excedido.");
    if (init < 0) throw std::out_of_range ("Tamaño maximo excedido.");
    if (tam < 0) throw std::out_of_range ("Tamaño maximo excedido.");
    
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
    palabra[0] = '\0';
    
    is.width(c.tamanioMaximo_ + 1);
    
    is >> palabra;
    c.tamanio_ = strlen(palabra);
    c.cad_ = new char[c.tamanio_];
    
    strcpy(c.cad_, palabra);
    
    return is;

    /*
     *
     *c.tamanio_ = 0;
     *int white_spaces = 0;
     *
     *char* p = new char[2];
     *p[1] = '\0';
     *p[0] = is.get();
     *
     *if(p[0] != EOF) {
     *    while(p[0] == ' ') { // Caso de entrada con espacios al principio.
     *        p[0] = is.get();
     *        white_spaces++;
     *    }
     *    
     *    // Caso general de palabras
     *    Cadena n;
     *    while(p[0] != '\n' && p[0] != ' ' && is.gcount() > 0 &&
     *          strcmp(p, " ") > 0 && c.tamanio_ < c.tamanioMaximo_) {
     *        n += p;
     *        p[0] = is.get();
     *        c = n;
     *    }
     *    if(p[0] == ' ') is.putback(' ');
     *    else if(c.tamanio_ == c.tamanioMaximo_) c += p;
     *    
     *    // Caso de caso con solo espacios.
     *    if(c.tamanio_ == 0 && white_spaces > 0) {
     *        c.tamanio_ = 0;
     *        c.cad_ = new char[c.tamanio_];
     *    }
     *} else { // Caso de entrada vacia.
     *    c.cad_ = new char[0];
     *}
     *return is;
     */
}

char& Cadena::operator [](int pos) const {
    return *(cad_ + pos);
}

Cadena& Cadena::operator =(const Cadena& c) {
    if(*this != c) {
        tamanio_ = c.length();
        cad_ = new char[tamanio_ + 1];
        strcpy(cad_, c.cad_);
    }
    return *this;
}

Cadena& Cadena::operator =(Cadena&& c) noexcept {
    if(this != &c) {
        tamanio_ = c.length();
        cad_ = new char[tamanio_ + 1];
        strcpy(cad_, c.cad_);
        
        c.cad_ = new char[0];
        c.tamanio_ = 0;
    }
    return *this;
}

Cadena& Cadena::operator +=(const Cadena& c) {
    char* cc = new char[tamanio_ + 1];
    strcpy(cc, cad_);
    
    tamanio_ += c.length();
    delete[] cad_;
    cad_ = new char[tamanio_ + 1];
    
    strcpy(cad_, cc);
    strcat(cad_, c.c_str());
    
    return *this;
}

Cadena& Cadena::operator +=(const char& c) {
    char* cc = new char[tamanio_ + 1];
    strcpy(cc, cad_);
    
    tamanio_ += 1;
    delete[] cad_;
    cad_ = new char[tamanio_ + 1];
    
    strcpy(cad_, cc);
    char* cad = new char[2]; cad[0] = c; cad[1] = '\0';
    strcat(cad_, cad);
    
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

bool operator >(const Cadena& p, const Cadena& c) {
    return strcmp(p.c_str(), c.c_str()) > 0;
}

bool operator ==(const Cadena& p, const Cadena& c) {
    return strcmp(p.c_str(), c.c_str()) == 0;
}

bool operator !=(const Cadena& p, const Cadena& c) {
    return !(p == c);
}

bool operator >=(const Cadena& p, const Cadena& c) {
    return (p > c || p == c);
}

bool operator <(const Cadena& p, const Cadena& c) {
    return !(p >= c);
}

bool operator <=(const Cadena& p, const Cadena& c) {
    return !(p > c);
}

// Destructor.
Cadena::~Cadena() {
    if(tamanio_ > 0) {
        delete[] cad_;
        tamanio_ = 0;
        cad_ = nullptr;
    }
}
#endif
