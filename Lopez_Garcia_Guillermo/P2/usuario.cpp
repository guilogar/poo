#include "usuario.hpp"
#include <cstring>

extern "C" {
    #include <unistd.h>
}

#include <random>

Clave::Clave(const char* contrasena) {
    if(std::strlen(contrasena) < 5) throw Incorrecta(CORTA);
    
    static const char *const cvs = "abcdfghijklmnoprstuvwxyz"
                                   "ABCDEFGHIJKLMNOPQRS"
                                   "TUVWXYZ0123456789/.";
    std::size_t longtd = sizeof(cvs) - 1;
    std::random_device r;
    std::uniform_int_distribution<std::size_t> distribucion(0, longtd - 1);
    char sal[] = {
                    cvs[distribucion.operator()(r)],
                    cvs[distribucion(r)]
                 };
    if(char* pcc = crypt(contrasena, sal))
        clave_ = pcc;
    else
        throw Incorrecta(ERROR_CRYPT);
}

bool Clave::verifica(const char* posible_contrasena) {
    if(const char* const pcc = crypt(posible_contrasena, clave_.c_str()))
        return clave_ == pcc;
    else
        throw Incorrecta(ERROR_CRYPT);
}

/*
 *#include <cstdlib>
 *#include <ctime>
 *
 *class SNA {
 *    SNA() {
 *        std::srand(std::time(nullptr));
 *    }
 *} sna;
 *
 *Clave::Clave(const char* contrasena) {
 *    if(std::strlen(contrasena) < 5) throw Incorrecta(CORTA);
 *    
 *    static const char *const cvs = "abcdfghijklmnoprstuvwxyz"
 *                                   "ABCDEFGHIJKLMNOPQRS"
 *                                   "TUVWXYZ0123456789/.";
 *    std::size_t longtd = sizeof(cvs) - 1;
 *    char sal[] = {
 *                    cvs[std::rand() % (longtd - 1)],
 *                    cvs[std::rand() % (longtd - 1)]
 *                 };
 *    if(char* pcc = crypt(contrasena, sal))
 *        clave_ = pcc;
 *    else
 *        throw Incorrecta(ERROR_CRYPT);
 *}
 */
