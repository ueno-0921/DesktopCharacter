#include "image.hpp"

Gdiplus::Bitmap *makeBitmapImage(LPCTSTR filePath)
{
#ifndef UNICODE
    WCHAR wc[MAX_PATH];
    size_t ret;
    mbstowcs_s(&ret, wc, MAX_PATH, filePath, _TRUNCATE);
    const WCHAR *path = wc;
#else
    const WCHAR *path = filePath;
#endif
    return Gdiplus::Bitmap::FromFile(path);
}