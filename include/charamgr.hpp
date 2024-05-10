#pragma once

#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <memory>
#include <math.h>
#include "Random.hpp"
#include "STRING.hpp"
#include "argparse.hpp"
#include "charasnd.hpp"
#include "charaimg.hpp"

class CharacterManager
{
public:
    CharacterManager();
    ~CharacterManager();
    void draw(HWND hWnd);
    void draw(HWND hWnd, int idx);
    void addImg(int idx, STRING &path);
    void scaling(HWND hWnd, WPARAM wParam);
    void setSize(HWND hWnd, int size);
    void setLimit(HWND hWnd, int max, int min);
    void setPos(HWND hWnd, int pos_x, int pos_y);
    void move(HWND hWnd, int move_x, int move_y);
    void setCorner(HWND hWnd, bool isRight);

    void click(HWND hWnd);
    void addClick(int idx);

    bool play(int idx);
    void setVol(short volume);
    void addSnd(int idx, STRING &path, bool isInt);
    short getW();
    short getH();

    bool initPos = true;
    int x, y;

private:
    short PAD_SIZE;
    std::unique_ptr<CharacterImage> charaImg;
    std::vector<int> imgsIdx;
    std::unique_ptr<CharacterSound> charaSnd;
    std::vector<int> sndsIdx;
    std::vector<int> clickIdx;
    std::unordered_map<int, bool> intSndsIdx;
    bool isTrueRand = false;
};

inline void CharacterManager::draw(HWND hWnd)
{
    charaImg->draw(hWnd);
}

inline void CharacterManager::draw(HWND hWnd, int idx)
{
    charaImg->draw(hWnd, idx);
}

inline bool CharacterManager::play(int idx)
{
    if (sndsIdx.size() > 0)
        return charaSnd->play(idx, intSndsIdx.at(idx));
    return false;
}

inline void CharacterManager::click(HWND hWnd)
{
    if (clickIdx.size() <= 0)
        return;
    auto randIdx = isTrueRand ? rnd.trueRand() % (int)clickIdx.size() : rnd((int)clickIdx.size());
    int idx = clickIdx[randIdx];
    if (play(idx))
        draw(hWnd, idx);
}