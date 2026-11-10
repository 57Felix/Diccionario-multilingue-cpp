#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <string>
#include "Nodo.h"

using namespace std;

// Carga las palabras desde un archivo y las inserta en el árbol
void cargar(const string& archivo, Nodo*& raiz);

// Guarda el árbol en un archivo
void guardar(const string& archivo, Nodo* raiz);

//agrgar palabra en el archivo
void agregar(const string& archivo, Nodo* raiz);

#endif

