#pragma once

#include <windows.h>
#include <mmsystem.h>
#include <strsafe.h>
#include "STRING.hpp"
#pragma comment(lib, "winmm")

class PlayWav
{
public:
    PlayWav(STRING filePath);
    ~PlayWav();
    bool PlayWavSnd(bool interrupt);

private:
    LPCSTR lpSnd;
};
