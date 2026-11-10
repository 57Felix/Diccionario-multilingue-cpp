#include "Audio.h"
#include <windows.h>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "user32.lib")

using namespace std;

void reproducirAudio(const string& archivo) {
    // Convertir std::string (UTF-8 o ANSI) a std::wstring (Unicode)
    int bufferTam = MultiByteToWideChar(CP_UTF8, 0, archivo.c_str(), -1, NULL, 0);
    if (bufferTam == 0) {
        MessageBox(NULL, L"Error al convertir la ruta del archivo", L"Error", MB_OK | MB_ICONERROR);
        return;
    }

    wstring archivoW(bufferTam, 0);
    MultiByteToWideChar(CP_UTF8, 0, archivo.c_str(), -1, &archivoW[0], bufferTam);

    PlaySound(archivoW.c_str(), NULL, SND_FILENAME | SND_ASYNC);
}
