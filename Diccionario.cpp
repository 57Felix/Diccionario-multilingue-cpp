#include <iostream>
#include <string>
#include <limits>
#include <fstream>  // Para verificar si el archivo existe
#include "Nodo.h"
#include "arbol.h"
#include "funciones.h"
#include "Audio.h"
#include <vector>
#include <map>
#include <algorithm>
#include "historial.h"
#include "usuario.h"
#include <windows.h>

using namespace std;

extern string normalizar(const string& str);
extern string encriptar(const string& palabra);
vector<string> historialOriginal;
map<string, int> contadorBusquedas;


int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

   Nodo* raiz = nullptr;
    string archivo = "palabras.txt";

   
    string usuario;
    int opcionInicio;
    cout << "**************************";
    cout << "\n ===== ¡BIENVENIDO! =====\n";
    cout << "**************************";
    cout << "\n\n Elige una opcion\n";
    cout << "1. Crear usuario\n";
    cout << "2. Iniciar sesión\n";
    cout << "\n Opción: ";
    cin >> opcionInicio;
    cin.ignore();
    system("cls");

    if (opcionInicio == 1) {
        if (crearUsuario()) {
           // cout << "\n Usuario creado exitosamente.\n";
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // LIMPIAR BUFFER
        }
        else {
            cout << "\n Error al crear el usuario.\n";
            return 0;
        }
    }

    bool loginExitoso = false;
    while (!loginExitoso) {
        loginExitoso = loginUsuario(usuario);

        if (!loginExitoso) {
            cout << "\n === ¡Usuario o contraseña incorrectos!===\n";
            cout << "\n¿Deseas volver a intentar? (s/n): ";
            char retry;
            cin >> retry;
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); 
            if (tolower(retry) != 's') {
                cout << "Saliendo del sistema.\n";
                return 0;
            }
        }
    }
    system("cls");

    cout << "\n    === ¡BIENVENID@! " << usuario << " ===" << "\n";
    
      
    cargar(archivo, raiz);

    
    if (raiz == nullptr) {
        cout << "El arbol está vacio. No se cargaron palabras.\n";
    }

    int opcion = 0;
    while (opcion != 5) {
        cout << "\n\n*********************************";
        cout << "\n     ==== TRADUCTOR ====\n";
        cout << "*********************************";
        cout << " \n\n     1. Buscar palabra\n";
        cout << "     2. Agregar palabra\n";
        cout << "     3. Eliminar palabra\n";
        cout << "     4. Actualizar archivo\n";
        cout << "     5. Mostrar top de palabras más buscadas\n";
                cout << "     6. Cerrar sesión\n";
        cout << "\n       Opcion: ";
        cin >> opcion;

        
        cin.ignore(); 

        system("cls");
        switch (opcion) {
        case 2: {
            string esp, ita, fra, ale, ing;

            cout << "Palabra en español: ";
            getline(cin, esp);
            cout << "Traducción en italiano: ";
            getline(cin, ita);
            cout << "Traducción en francés: ";
            getline(cin, fra);
            cout << "Traducción en alemán: ";
            getline(cin, ale);
            cout << "Traducción en inglés: ";
            getline(cin, ing);

            if (esp.empty() || ita.empty() || fra.empty() || ale.empty() || ing.empty()) {
                cout << "\n Error: Todos los campos son obligatorios.\n";
                break;
            }

            string palabraBuscada = normalizar(esp);
            if (buscar(raiz, palabraBuscada) != nullptr) {
                cout << "\n La palabra '" << esp << "' ya existe en el diccionario.\n";
                break;
            }


            raiz = insertar(
                raiz,
                normalizar(esp),  
                esp,              
                ita,            
                fra,          
                ale,              
                ing);             

            // Buscar el nodo recién insertado
            Nodo* nuevoNodo = buscar(raiz, normalizar(esp));

           
            if (nuevoNodo) {
                agregar(archivo, nuevoNodo);
                cout << "\nPalabra agregada y guardada correctamente.\n";
            }
            else {
                cout << "\n Error al guardar la palabra en el archivo.\n";
            }

            break;
        }

        system("cls");
        case 3: {
         
            string esp;
            cout << "Ingrese la palabra en español a eliminar: ";
            getline(cin, esp);
            raiz = eliminarNodo(raiz, esp);
            break;
        }
        system("cls");
        case 1: {
          
            string esp;
            cout << "\nIngrese la palabra en español a buscar: ";
            getline(cin, esp);

            esp = normalizar(esp);
            Nodo* result = buscar(raiz, esp);

            historialOriginal.push_back(esp);
            contadorBusquedas[esp]++;

            if (result) {
                result->mostrarNodo();

                int opcionIdioma;
                cout << "\n Seleccione el idioma para reproducir el audio:\n";
                cout << "\n1. Español\n2. Italiano\n3. Francés\n4. Alemán\n5. Inglés\n  \n  Opción: ";
                cin >> opcionIdioma;
                cin.ignore(); 

                string palabraAudio;
                switch (opcionIdioma) {
                case 1: palabraAudio = result->esp + "_es"; break;
                case 2: palabraAudio = result->ita + "_it"; break;
                case 3: palabraAudio = result->fra + "_fr"; break;
                case 4: palabraAudio = result->ale + "_al"; break;
                case 5: palabraAudio = result->ing + "_in"; break;
                default:
                    cout << "Opción inválida. No se reproducirá audio.\n";
                    break;
                }

                if (!palabraAudio.empty()) {
                    string ruta = "audios/" + palabraAudio + ".wav";
                    std::ifstream archivo(ruta);
                    if (archivo.good()) {
                        reproducirAudio(ruta);
                    }
                    else {
                        cout << "Archivo de audio no encontrado: " << ruta << endl;
                    }
                    archivo.close();
                }
            }
            else {
                cout << "La palabra no se encontró en el diccionario.\n";
            }

            break;
        }

        system("cls");
        case 4: {
            
            guardar(archivo, raiz);
            cout << "Actualizar archivo " << archivo << "\n";
            break;
        }
        system("cls");
        case 5: {
            guardarHistorial();         
            mostrarTopBusquedas();     
            break;
        }
       
        system("cls");
        case 6: {
            
            cout << "\n\n  Cerrando sesion...\n\n\n";
            break;
        }
        default:
            cout << "Opcion invalida.\n";
        }
    }

    return 0;
}
