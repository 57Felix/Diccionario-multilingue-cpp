#ifndef AUDIO_H
#define AUDIO_H

#include <windows.h>
#include <mmsystem.h>
#include <string>

using namespace std;

#pragma comment(lib, "winmm.lib")  // Enlaza la librería de sonido

void reproducirAudio(const string& archivo);

#endif
