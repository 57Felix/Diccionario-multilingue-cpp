#include <fstream>
#include "funciones.h"
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include <iostream>
#include <windows.h>

using namespace std;

extern string encriptar(const string& palabra);

extern vector<string> historialOriginal;
extern map<string, int> contadorBusquedas;

void guardarHistorial() {
    SetConsoleOutputCP(CP_UTF8);
    
    ofstream clave("llave.txt");
    clave << "Umg";
    clave.close();

    ofstream original("historial_original.txt");
    for (const string& palabra : historialOriginal)
        original << palabra << endl;
    original.close();

    ofstream encriptado("historial_encriptado.txt");
    for (const string& palabra : historialOriginal)
        encriptado << encriptar(palabra) << endl;
    encriptado.close();
}

void mostrarTopBusquedas() {
    vector<pair<string, int>> top(contadorBusquedas.begin(), contadorBusquedas.end());
    sort(top.begin(), top.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });
    cout << "\n\n  ****************************************";
    cout << "\n     ===Top de palabras más buscadas===\n";
    cout << "  ****************************************\n";
    int limite = min(5, (int)top.size());
    for (int i = 0; i < limite; ++i)
        cout << "\n" << i + 1 << ". " << top[i].first << " (" << top[i].second << " veces)\n";
}
