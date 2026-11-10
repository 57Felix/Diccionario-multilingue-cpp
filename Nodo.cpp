#include "Nodo.h"
#include <iostream>

using namespace std;


void Nodo::mostrarNodo() const {
    
    cout << "\n === Palabra encontrada==\n\n";
    cout << " Espanol:   " << espOriginal << '\n';
    cout << " Italiano:  " << ita << '\n';
    cout << " Frances:   " << fra << '\n';
    cout << " Aleman:    " << ale << '\n';
    cout << " Ingles:    " << ing << '\n';
}