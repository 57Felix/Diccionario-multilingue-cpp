# Diccionario Multi-idioma con Árbol AVL y Encriptación

**Universidad Mariano Gálvez de Guatemala**  
**Facultad de Ingeniería en Sistemas**  
**Curso:** Programación 3  
**Catedrático:** Ing. Axel Aguilar  

---

## 📌 Descripción del Proyecto

Este proyecto consiste en un sistema de **Diccionario y Traductor Multi-idioma (Español, Inglés, Francés, Alemán e Italiano)** desarrollado en C++. El sistema permite la gestión dinámica de palabras mediante estructuras de datos avanzadas (**Árboles AVL**), persistencia de datos en archivos, reproducción de audio para las pronunciaciones, un sistema de autenticación de usuarios y encriptación personalizada de historial de búsquedas.

---

## 🚀 Funcionalidades Principales

### 🔹 Fase 1: Captura, Definición de Datos y Árboles
- **Carga de Datos:** Lectura automática del diccionario desde el archivo `palabras.txt`.
- **Estructura del Árbol:** Almacenamiento y organización de palabras en español con sus traducciones a 4 idiomas.
- **Inserción y Eliminación:** Permite agregar nuevos términos y eliminar palabras manteniendo el balance del árbol.
- **Audio:** Reproducción de sonidos WAV de pronunciación utilizando la librería SFML.

### 🔹 Fase 2: Diseño Lógico, Árbol AVL y Encriptación
- **Balanceo AVL:** Mantenimiento automático de la altura del árbol (rotaciones simples y dobles) para optimizar las búsquedas.
- **Encriptación $Umg$:** Algoritmo de sustitución personalizado de vocales y consonantes para resguardar la privacidad del historial.
- **Historial y Top de Búsquedas:** Registro de las palabras más consultadas por el usuario.

### 🔹 Fase 3: Seguridad y Perfiles de Usuario
- **Autenticación:** Registro e inicio de sesión de usuarios con contraseñas y credenciales cifradas.
- **Persistencia Binaria:** Salvaguarda de perfiles en archivos propietarios (`usuarios.dat`) para evitar modificaciones no autorizadas.

---

## 📂 Estructura del Proyecto

```text
├── main.cpp / diccionario.cpp # Punto de entrada del programa y menú principal
├── arbol.h / arbol.cpp         # Lógica del Árbol AVL (Inserción, Búsqueda, Balanceo)
├── Nodo.h / Nodo.cpp           # Estructura del Nodo de datos del diccionario
├── Audio.h / Audio.cpp         # Reproductor de sonido 
├── funciones.h / funciones.cpp # Utilidades de cadenas, normalización y persistencia
├── historial.h / historial.cpp # Gestión del historial encriptado y Top de búsquedas
├── usuario.h / usuario.cpp     # Gestión de registro e inicio de sesión
├── palabras.txt                # Base de datos de traducciones
├── usuarios.dat                # Archivo binario de usuarios registrados
├── audios/                     # Carpeta con archivos de voz (.wav)
└── Diccionario.sln             # Archivo de solución para Microsoft Visual Studio