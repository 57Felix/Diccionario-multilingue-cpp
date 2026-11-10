#ifndef USUARIO_H
#define USUARIO_H

#include <string>
using namespace std;

struct Usuario {
    string nombre;
    string contrasena;
    string llave;
};

// Funciones públicas
bool crearUsuario();
bool loginUsuario(string& nombreLogueado);
string encriptar(const string& texto);

#endif

