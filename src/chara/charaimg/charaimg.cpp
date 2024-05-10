#include "charaimg.hpp"

CharacterImage::CharacterImage(std::vector<STRING> &imgs, std::vector<int> &idx, int defIdx, bool base, int max, int min, int size, int sensi)
{
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    for (int i = 0; i < (int)idx.size(); ++i)
        addImg(idx.at(i), imgs.at(i));
    nowImgIdx = defIdx;
    w = charaImg.begin()->second->GetWidth();
    h = charaImg.begin()->second->GetHeight();

    SCALE_SENSI = sensi;
    MAX_SIZE = max;
    MIN_SIZE = min;
    IS_BASE_H = base;
    ASPECT = IS_BASE_H ? (double)w / (double)h : (double)h / (double)w;

    if (IS_BASE_H)
        h = size;
    else
        w = size;
    limitSize();
}

void CharacterImage::addImg(int idx, STRING &path)
{
    std::pair<int, Gdiplus::Bitmap *> keyVal;
    keyVal = std::pair<int, Gdiplus::Bitmap *>(idx, makeBitmapImage((LPCTSTR)path.c_str()));
    charaImg.insert(std::move(keyVal));
}

CharacterImage::~CharacterImage()
{
    for (auto i : charaImg)
    {
        delete i.second;
    }
    Gdiplus::GdiplusShutdown(gdiplusToken);
}

void CharacterImage::draw(HWND hWnd)
{
    draw(hWnd, nowImgIdx);
}

void CharacterImage::draw(HWND hWnd, int idx)
{
    nowImgIdx = idx;

    hdc = BeginPaint(hWnd, &ps);
    HDC charaDC = CreateCompatibleDC(hdc);
    HBITMAP newBitmap = CreateCompatibleBitmap(hdc, w, h);
    HBITMAP oldBitmap = (HBITMAP)SelectObject(charaDC, newBitmap);

    graphics = new Gdiplus::Graphics(charaDC);
    graphics->DrawImage(charaImg.at(idx), 0, 0, w, h);

    BLENDFUNCTION blend = {0};
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = 255;
    blend.AlphaFormat = AC_SRC_ALPHA;

    RECT wndRect;
    RECT dtpRect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &dtpRect, 0);
    GetWindowRect(hWnd, &wndRect);
    // Scaling based on the LOWER RIGHT corner of the window (image)
    int wndPosY = wndRect.bottom - h;
    int wndPosX = wndRect.right - w;
    // When "scaling down", if the window extends beyond the BOTTOM edge of the main display.
    // Scale down based on the TOP edge of the window.
    wndPosY = (dtpRect.bottom <= wndRect.bottom && (wndRect.bottom - wndRect.top) > h) ? wndRect.top : wndPosY;
    // When "scaling up", if the window extends beyond the LEFT edge of the main display.
    // Scale up based on the LEFT edge of the window.
    wndPosX = (dtpRect.left >= wndRect.left && (wndRect.right - wndRect.left) < w) ? wndRect.left : wndPosX;
    // Windows should not extend beyond the TOP and RIGHT edges of the main display
    wndPosY = wndPosY < 0 ? 0 : wndPosY;
    wndPosX = wndPosX + w > dtpRect.right ? dtpRect.right - w : wndPosX;

    GetWindowRect(hWnd, &wndRect);
    POINT wndPos = {wndPosX, wndPosY};
    SIZE wndSize = {w, h};
    POINT imgPos = {0, 0};

    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, w, h, SWP_NOMOVE);
    UpdateLayeredWindow(hWnd, hdc, &wndPos, &wndSize, charaDC, &imgPos, 0, &blend, ULW_ALPHA);
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    delete graphics;
    SelectObject(charaDC, oldBitmap);
    DeleteObject(newBitmap);
    DeleteDC(charaDC);
    ReleaseDC(NULL, hdc);
    EndPaint(hWnd, &ps);
}

void CharacterImage::setLimit(HWND hWnd, int max, int min)
{
    if (max < min)
        return;
    MAX_SIZE = max > 0 ? max : MAX_SIZE;
    MIN_SIZE = min > 0 ? min : MIN_SIZE;
    limitSize();
    draw(hWnd, nowImgIdx);
}

void CharacterImage::limitSize()
{
    auto size = IS_BASE_H ? h : w;
    if (size > MAX_SIZE)
    {
        size = MAX_SIZE;
    }
    else if (size < MIN_SIZE)
    {
        size = MIN_SIZE;
    }
    if (IS_BASE_H)
    {
        h = size;
        w = (int)ceil((double)ASPECT * (double)h);
    }
    else
    {
        w = size;
        h = (int)ceil((double)ASPECT * (double)w);
    }
}

void CharacterImage::setSize(HWND hWnd, int newSize)
{
    if (IS_BASE_H)
        h = newSize;
    else
        w = newSize;
    limitSize();
    draw(hWnd, nowImgIdx);
}

void CharacterImage::scaling(short delta)
{
    short scalingValue = (int)(delta / WHEEL_DELTA) * SCALE_SENSI;

    if (IS_BASE_H)
    {
        h += scalingValue;
    }
    else
    {
        w += scalingValue;
    }
    limitSize();
}