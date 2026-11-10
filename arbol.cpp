#include "arbol.h"
#include <iostream>
#include <unordered_map>
#include <cctype>
//#include <sstream>
using namespace std;

// ================= NORMALIZAR ====================
string normalizar(const string& str) {
    string resultado;
    unordered_map<string, char> reemplazos = {
        
        {"á", 'a'}, {"é", 'e'}, {"í", 'i'}, {"ó", 'o'}, {"o", 'ó'}, {"ú", 'u'},
        {"Á", 'a'}, {"É", 'e'}, {"Í", 'i'}, {"Ó", 'o'}, {"Ú", 'u'},
        {"ñ", 'n'}, {"Ñ", 'n'}
    };

    for (size_t i = 0; i < str.length(); ) {
        unsigned char c = str[i];

        
        if ((c & 0xE0) == 0xC3 && i + 1 < str.length()) {
            string utf8Char = str.substr(i, 2);
            if (reemplazos.count(utf8Char)) {
                resultado += reemplazos[utf8Char];
            }
            else {
                resultado += '?'; // caracter desconocido
            }
            i += 2;
        }
        else {
            resultado += tolower(c);
            i++;
        }
    }

    return resultado;
}
//===============AUXILIARES PARA AVL=================
int altura(Nodo* nodo) { return nodo ? nodo->altura : 0; }
int balance(Nodo* nodo) { return nodo ? altura(nodo->izquierda) - altura(nodo->derecha) : 0; }

void actualizarAltura(Nodo* nodo) { nodo->altura = 1 + max(altura(nodo->izquierda), altura(nodo->derecha)); }

Nodo* rotarIzquierda(Nodo* x) { Nodo* y = x->derecha; x->derecha = y->izquierda; y->izquierda = x;
actualizarAltura(x);
actualizarAltura(y);
return y;
}

Nodo* rotarDerecha(Nodo* y) {
    Nodo* x = y->izquierda;
    y->izquierda = x->derecha;
    x->derecha = y;
    actualizarAltura(y);
    actualizarAltura(x);
    return x;
}


// ================= INSERTAR ====================
Nodo* insertar(Nodo* nodo, string espNormalizado, string espOriginal, string ita, string fra, string ale, string ing) {
    if (!nodo)
        return new Nodo(espNormalizado, espOriginal, ita, fra, ale, ing);

    if (espNormalizado < nodo->esp)
        nodo->izquierda = insertar(nodo->izquierda, espNormalizado, espOriginal, ita, fra, ale, ing);
    else if (espNormalizado > nodo->esp)
        nodo->derecha = insertar(nodo->derecha, espNormalizado, espOriginal, ita, fra, ale, ing);
    else {
        cout << "Palabra duplicada: " << espNormalizado << endl;
        return nodo;
    }

    actualizarAltura(nodo);
    int b = balance(nodo);

    if (b > 1 && espNormalizado < nodo->izquierda->esp)
        return rotarDerecha(nodo);
    if (b < -1 && espNormalizado > nodo->derecha->esp)
        return rotarIzquierda(nodo);
    if (b > 1 && espNormalizado > nodo->izquierda->esp) {
        nodo->izquierda = rotarIzquierda(nodo->izquierda);
        return rotarDerecha(nodo);
    }
    if (b < -1 && espNormalizado < nodo->derecha->esp) {
        nodo->derecha = rotarDerecha(nodo->derecha);
        return rotarIzquierda(nodo);
    }

    return nodo;
}



// ================= BUSCAR ====================
Nodo* buscar(Nodo* raiz, string palabra) {
    if (raiz == nullptr) return nullptr;

    string clave = normalizar(raiz->esp);
    palabra = normalizar(palabra);

    if (palabra == clave)
        return raiz;
    else if (palabra < clave)
        return buscar(raiz->izquierda, palabra);
    else
        return buscar(raiz->derecha, palabra);
}

// ================= EN ORDEN ====================
void enOrden(Nodo* raiz) {
    if (raiz != nullptr) {
        enOrden(raiz->izquierda);
        raiz->mostrarNodo();
        enOrden(raiz->derecha);
    }
}

// ================= ELIMINAR ÁRBOL ====================
void eliminarArbol(Nodo* raiz) {
    if (raiz != nullptr) {
        eliminarArbol(raiz->izquierda);
        eliminarArbol(raiz->derecha);
        delete raiz;
    }
}

// ================= ELIMINAR NODO ESPECÍFICO ====================
Nodo* eliminarNodo(Nodo* raiz, string palabra) {
    if (raiz == nullptr) return nullptr;

    string clave = normalizar(raiz->esp);
    palabra = normalizar(palabra);

    if (palabra < clave) {
        raiz->izquierda = eliminarNodo(raiz->izquierda, palabra);
    }
    else if (palabra > clave) {
        raiz->derecha = eliminarNodo(raiz->derecha, palabra);
    }
    else {
        // Nodo encontrado
        if (!raiz->izquierda || !raiz->derecha) {
            Nodo* temp = raiz->izquierda ? raiz->izquierda : raiz->derecha;
            delete raiz;
            return temp;
        }

        // Buscar sucesor (mínimo en el subárbol derecho)
        Nodo* sucesor = raiz->derecha;
        while (sucesor->izquierda)
            sucesor = sucesor->izquierda;

        // Copiar los datos del sucesor
        raiz->esp = sucesor->esp;
        raiz->espOriginal = sucesor->espOriginal;
        raiz->ita = sucesor->ita;
        raiz->fra = sucesor->fra;
        raiz->ale = sucesor->ale;
        raiz->ing = sucesor->ing;

        // Eliminar el sucesor
        raiz->derecha = eliminarNodo(raiz->derecha, sucesor->esp);
    }

    // 🧠 Recalcular altura y balancear
    actualizarAltura(raiz);
    int b = balance(raiz);

    // Casos de rotación
    if (b > 1 && balance(raiz->izquierda) >= 0)
        return rotarDerecha(raiz);

    if (b > 1 && balance(raiz->izquierda) < 0) {
        raiz->izquierda = rotarIzquierda(raiz->izquierda);
        return rotarDerecha(raiz);
    }

    if (b < -1 && balance(raiz->derecha) <= 0)
        return rotarIzquierda(raiz);

    if (b < -1 && balance(raiz->derecha) > 0) {
        raiz->derecha = rotarDerecha(raiz->derecha);
        return rotarIzquierda(raiz);
    }

    return raiz;
    }




