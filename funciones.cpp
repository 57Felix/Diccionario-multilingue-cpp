#include "funciones.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "arbol.h"

using namespace std;

extern string normalizar(const string& str); 


void cargar(const string& archivo, Nodo*& root) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo: " << archivo << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string esp, ita, fra, ale, ing;

        if (getline(ss, esp, ';') &&
            getline(ss, ita, ';') &&
            getline(ss, fra, ';') &&
            getline(ss, ale, ';') &&
            getline(ss, ing, ';'))
        {
           root = insertar(root,
                normalizar (esp),
                (esp),
                (ita),
                (fra),
                (ale),
                (ing));

            string palabraNormalizada = normalizar(esp);
           //cout << "[DEBUG] Insertado: " << normalizar(esp) << " original: " << esp << ")\n";

        }
    }

    file.close();
}

static void escribirenorden(ofstream& file, Nodo* raiz) {
    if (!raiz) return;

    escribirenorden(file, raiz->izquierda);

    // Guardar en orden: esp;ita;fra;ale;ing
    file << raiz->espOriginal << ';'
        << raiz->ita << ';'
        << raiz->fra << ';'
        << raiz->ale << ';'
        << raiz->ing << '\n';

    escribirenorden(file, raiz->derecha);
}

void guardar(const string& archivo, Nodo* raiz) {
    ofstream file(archivo);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para escribir: " << archivo << endl;
        return;
    }

    escribirenorden(file, raiz);
    file.close();
}

void agregar(const string& archivo, Nodo* nodo) {
    ofstream file(archivo, ios::app);
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo para agregar: " << archivo << endl;
        return;
    }

    file << nodo->espOriginal << ';'
        << nodo->ita << ';'
        << nodo->fra << ';'
        << nodo->ale << ';'
        << nodo->ing << '\n';

    file.close();
}

//====================ENCRIPTACION=================================
string encriptar(const string& palabra) {
    string resultado;
    for (char c : palabra) {
        switch (c) {
            // Vocales
        case 'a': resultado += "U1"; break;
        case 'e': resultado += "U2"; break;
        case 'i': resultado += "U3"; break;
        case 'o': resultado += "U4"; break;
        case 'u': resultado += "U5"; break;
            // Minúsculas
        case 'b': resultado += "m1"; break;
        case 'c': resultado += "m2"; break;
        case 'd': resultado += "m3"; break;
        case 'f': resultado += "m4"; break;
        case 'g': resultado += "m5"; break;
        case 'h': resultado += "m6"; break;
        case 'j': resultado += "m7"; break;
        case 'k': resultado += "m8"; break;
        case 'l': resultado += "m9"; break;
        case 'm': resultado += "m10"; break;
        case 'n': resultado += "m11"; break;
        case 'ñ': resultado += "m12"; break;
        case 'p': resultado += "m13"; break;
        case 'q': resultado += "m14"; break;
        case 'r': resultado += "m15"; break;
        case 's': resultado += "m16"; break;
        case 't': resultado += "m17"; break;
        case 'v': resultado += "m18"; break;
        case 'w': resultado += "m19"; break;
        case 'x': resultado += "m20"; break;
        case 'y': resultado += "m21"; break;
        case 'z': resultado += "m22"; break;
            // Mayúsculas
        case 'B': resultado += "g1"; break;
        case 'C': resultado += "g2"; break;
        case 'D': resultado += "g3"; break;
        case 'F': resultado += "g4"; break;
        case 'G': resultado += "g5"; break;
        case 'H': resultado += "g6"; break;
        case 'J': resultado += "g7"; break;
        case 'K': resultado += "g8"; break;
        case 'L': resultado += "g9"; break;
        case 'M': resultado += "g10"; break;
        case 'N': resultado += "g11"; break;
        case 'Ñ': resultado += "g12"; break;
        case 'P': resultado += "g13"; break;
        case 'Q': resultado += "g14"; break;
        case 'R': resultado += "g15"; break;
        case 'S': resultado += "g16"; break;
        case 'T': resultado += "g17"; break;
        case 'V': resultado += "g18"; break;
        case 'W': resultado += "g19"; break;
        case 'X': resultado += "g20"; break;
        case 'Y': resultado += "g21"; break;
        case 'Z': resultado += "g22"; break;
        default: resultado += c; break;
        }
    }

    return resultado;
}