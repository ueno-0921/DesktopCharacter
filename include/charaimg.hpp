#pragma once

#include <ole2.h>
#include <gdiplus.h>
#include <vector>
#include <unordered_map>
#include <windows.h>
#include "STRING.hpp"
#include "image.hpp"

#pragma comment(lib, "Gdiplus.lib")

class CharacterImage
{
public:
    CharacterImage(std::vector<STRING> &imgs, std::vector<int> &idx, int defIdx, bool base, int max, int min, int size, int sensi);
    ~CharacterImage();
    void draw(HWND hWnd);
    void draw(HWND hWnd, int idx);
    void setSize(HWND hWnd, int newSize);
    void scaling(short delta);
    void setLimit(HWND hWnd, int max, int min);
    void addImg(int idx, STRING &path);

    int w, h;

private:
    void limitSize();

    int MAX_SIZE, MIN_SIZE;
    bool IS_BASE_H;
    double ASPECT;
    int SCALE_SENSI;
    std::unordered_map<int, Gdiplus::Bitmap *> charaImg;
    int nowImgIdx;

    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    HDC hdc;
    PAINTSTRUCT ps;
    Gdiplus::Graphics *graphics;
};