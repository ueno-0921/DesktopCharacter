#include "sound.hpp"

PlayWav::PlayWav(STRING filePath)
{
    HANDLE fh;
    DWORD dwFileSize, dwReadSize;

    fh = CreateFile(filePath.c_str(), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    dwFileSize = GetFileSize(fh, NULL);
    lpSnd = (LPCSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwFileSize);
    ReadFile(fh, (LPVOID)lpSnd, dwFileSize, &dwReadSize, NULL);
    CloseHandle(fh);
}

PlayWav::~PlayWav()
{
    PlaySound(NULL, NULL, 0);
    HeapFree(GetProcessHeap(), 0, (LPVOID)lpSnd);
}

bool PlayWav::PlayWavSnd(bool interrupt)
{
    if (interrupt)
        PlaySound(NULL, NULL, 0);
    return PlaySound(lpSnd, NULL, SND_ASYNC | SND_NODEFAULT | SND_NOSTOP | SND_MEMORY);
}