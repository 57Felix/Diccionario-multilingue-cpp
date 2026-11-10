#ifndef NODO_H
#define NODO_H

#include <string>
using namespace std;

struct Nodo {
    string esp; 
    string espOriginal; 
    string ita;  
    string fra;  
    string ale;  
    string ing;  

    Nodo* izquierda;
    Nodo* derecha;

    int altura; // campo para AVL
    
    Nodo(string espNormalizado, string espOriginal, string italiano, string frances, string aleman, string ingles)
        : esp(espNormalizado), espOriginal(espOriginal), ita(italiano), fra(frances), ale(aleman), ing(ingles),
        izquierda(nullptr), derecha(nullptr), altura(1)
    
    {
    }


    void mostrarNodo() const;

};

#endif

