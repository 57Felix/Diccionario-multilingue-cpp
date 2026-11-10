#include "Usuario.h"
#include "funciones.h"
#include <fstream>
#include <iostream>
#include <map>
#include <windows.h>


bool crearUsuario() {
    SetConsoleOutputCP(CP_UTF8);

    Usuario u;
    cout << "****************************";
    cout << "\n   === CREAR USUARIO ===\n";
    cout << "****************************";
    cout << "\n\nNombre de usuario: ";
    getline(cin, u.nombre);
    cout << "Contraseña: ";
    getline(cin, u.contrasena);

    u.contrasena = encriptar(u.contrasena);

    ofstream out("usuarios.dat", ios::app);
    if (!out.is_open()) {
        cout << "No se pudo abrir el archivo de usuarios.\n";
        return false;
    }

    out << u.nombre << "|" << u.contrasena << "\n";
    out.close();

    cout << "\nUsuario creado EXITOSAMENTE.\n";
    return true;
}

bool loginUsuario(string& nombreLogueado) {
    SetConsoleOutputCP(CP_UTF8);

    string nombre, pass;
    cout << "********************************";
    cout << "\n ====== INICIO DE SESION ======\n";
    cout << "********************************";
    cout << "\n\n Usuario: ";
    getline(cin, nombre);
    cout << "Contraseña: ";
    getline(cin, pass);

    string passEncriptada = encriptar(pass);

    ifstream in("usuarios.dat");
    if (!in.is_open()) {
        cout << "No se pudo abrir el archivo de usuarios.\n";
        return false;
    }

    string linea;
    while (getline(in, linea)) {
        size_t sep = linea.find('|');
        if (sep != string::npos) {
            string usuario = linea.substr(0, sep);
            string clave = linea.substr(sep + 1);
            if (usuario == nombre && clave == passEncriptada) {
                nombreLogueado = nombre;
                return true;
            }
        }
    }

    return false;
}
