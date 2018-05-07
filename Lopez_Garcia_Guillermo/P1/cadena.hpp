#ifndef CADENA_HPP
#define CADENA_HPP

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iterator>

class Cadena {
    public:
        Cadena(const char* cad, int tamanio);
        Cadena(const char* cad, int init, int tam);
        Cadena(int tamanio, const char caracter);
        Cadena(const char* cad);
        Cadena(int tamanio = 0);
        Cadena(const Cadena& c);
        Cadena(Cadena&& c);
        
        unsigned length() const;
        
        Cadena substr(int init = 0, int tam = 0) const;
        
        char& at(int pos) const;
        char& operator[](int pos) const;
        
        const char* c_str() const { return cad_; }
        friend std::basic_ostream<char>& operator <<(std::basic_ostream<char>& os, const Cadena& c);
        friend std::basic_istream<char>& operator >>(std::basic_istream<char>& is, Cadena& c);
        
        Cadena& operator =(const Cadena& c);
        Cadena& operator =(Cadena&& c) noexcept;
        Cadena operator +(const Cadena& c);
        Cadena operator +(const Cadena& c) const;
        Cadena& operator +=(const Cadena& c);
        Cadena& operator +=(const char&);
        
        friend bool operator ==(const Cadena& p, const Cadena& c);
        friend bool operator !=(const Cadena& p, const Cadena& c);
        friend bool operator  >(const Cadena& p, const Cadena& c);
        friend bool operator  <(const Cadena& p, const Cadena& c);
        friend bool operator >=(const Cadena& p, const Cadena& c);
        friend bool operator <=(const Cadena& p, const Cadena& c);
        
        ~Cadena();
        
        class TamanioInvalido { };
        
        typedef char* iterator;
        typedef const char* const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        
        iterator begin() { return cad_; }
        iterator end() { return (cad_ + tamanio_); }
        
        iterator begin() const { return cad_; }
        iterator end() const { return (cad_ + tamanio_); }
        
        const_iterator cbegin() { return cad_; }
        const_iterator cend() { return (cad_ + tamanio_); }
        
        const_iterator cbegin() const { return cad_; }
        const_iterator cend() const { return (cad_ + tamanio_); }
        
        reverse_iterator rbegin() {
            return std::reverse_iterator<iterator> (cad_ + tamanio_);
        }
        reverse_iterator rend() {
            return std::reverse_iterator<iterator> (cad_);
        };
        
        reverse_iterator rbegin() const {
            return std::reverse_iterator<iterator> (cad_ + tamanio_);
        }
        
        reverse_iterator rend() const {
            return std::reverse_iterator<iterator> (cad_);
        };
        
        const_reverse_iterator crbegin() {
            return std::reverse_iterator<const_iterator> (cad_ + tamanio_);
        }
        const_reverse_iterator crend() {
            return std::reverse_iterator<const_iterator> (cad_);
        }
        
        const_reverse_iterator crbegin() const {
            return std::reverse_iterator<const_iterator> (cad_ + tamanio_);
        }
        const_reverse_iterator crend() const {
            return std::reverse_iterator<const_iterator> (cad_);
        }
    private:
        int tamanio_, tamanioMaximo_ = 32;
        char* cad_;
};
#endif
