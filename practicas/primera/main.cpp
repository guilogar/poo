#include <iostream>
#include "fecha.cpp"
#include "cadena.cpp"

using namespace std;
int main(int argc, const char *argv[])
{
      Cadena c;
      cout << "Escribe un par de palabras, por favor: ";
      cin >> c;
      cout << "Palabra 1: " << c << endl;
      cout << "Carácter actual: '" << static_cast<char>(cin.peek())
           << "'" << endl;
      cin >> c;
      cout << "Palabra 2: " << c << endl;
      
      /*
       * Pruebas de iteradores
       *c = "No te digo trigo por no llamarte Rodrigo";
       *for (auto i : c)
       *  cout << i;
       *cout << endl;
       *for (Cadena::const_reverse_iterator r = c.rbegin(); r != c.rend(); ++r)
       *  cout << *r;
       *cout << endl;
       */
    return 0;
}
