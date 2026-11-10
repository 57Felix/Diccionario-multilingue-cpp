#ifndef ARBOL_H
#define ARBOL_H
#include "Nodo.h"
#include <string>

using namespace std;

// Declaración de funciones
Nodo* eliminarNodo(Nodo* raiz, string palabra);
Nodo* insertar(Nodo* raiz, string espNormalizado, string espOriginal, string ita, string fra, string ale, string ing);
Nodo* buscar(Nodo* raiz, string palabra);
string normalizar(const string& str);
void enOrden(Nodo* raiz);
void eliminarArbol(Nodo* raiz);

#endif