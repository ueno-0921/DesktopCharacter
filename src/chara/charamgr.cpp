#include "charamgr.hpp"
#include "options.hpp"

CharacterManager::CharacterManager()
{
    rnd.seed();

    std::unordered_map<STRING, STRING> optionList = {
        {O_IMG, DEFAULT},
        {O_IMG_I, DEFAULT},
        {O_DEF_IMG_I, DEFAULT},
        {O_SND, DEFAULT},
        {O_SND_I, DEFAULT},
        {O_INT_SND_I, DEFAULT},
        {O_VOL, TEXT("100")},
        {O_CLICK_I, DEFAULT},
        {O_IS_TRUE_RAND, TEXT("false")},
        {O_POS, DEFAULT},
        {O_IS_BASED_H, TEXT("true")},
        {O_MAX, TEXT("850")},
        {O_MIN, TEXT("200")},
        {O_INIT_SIZE, TEXT("850")},
        {O_SENSI, TEXT("40")},
        {O_POS_PAD, TEXT("10")}};
    std::unordered_map<STRING, std::vector<STRING>> args = argParse(optionList);

    if (args.at(O_IMG)[0] == DEFAULT)
        throw "Error : Nothing image.\n";
    std::vector<STRING> imgs = std::move(args.at(O_IMG));
    imgsIdx = std::vector<int>();
    int defImgIdx;
    if (args.at(O_IMG_I)[0] == DEFAULT)
        for (int i = 0; i < imgs.size(); ++i)
            imgsIdx.push_back(i);
    else
        imgsIdx = std::move(castInt(args.at(O_IMG_I)));
    if (args.at(O_DEF_IMG_I)[0] == DEFAULT)
        defImgIdx = imgsIdx[0];
    else
        defImgIdx = castInt(args.at(O_DEF_IMG_I))[0];

    std::vector<STRING> snds;
    if (args.at(O_SND)[0] != DEFAULT)
        snds = std::move(args.at(O_SND));
    sndsIdx = std::vector<int>();
    intSndsIdx = std::unordered_map<int, bool>();
    short vol = std::stoi(args.at(O_VOL)[0]);
    if (args.at(O_SND_I)[0] == DEFAULT)
        for (int i = 0; i < snds.size(); ++i)
            sndsIdx.push_back(i);
    else
        sndsIdx = std::move(castInt(args.at(O_SND_I)));
    if (args.at(O_INT_SND_I)[0] == DEFAULT)
        for (int i = 0; i < snds.size(); ++i)
            intSndsIdx[i] = false;
    else
        for (int i = 0; i < snds.size(); ++i)
            intSndsIdx[i] =
                args.at(O_INT_SND_I)[i] == TEXT("true") ? true : false;

    if (args.at(O_CLICK_I)[0] == DEFAULT)
    {
        clickIdx = std::vector<int>();
        std::vector<int> v1, v2;
        std::copy(imgsIdx.begin(), imgsIdx.end(), std::back_inserter(v1));
        std::copy(sndsIdx.begin(), sndsIdx.end(), std::back_inserter(v2));
        std::sort(v1.begin(), v1.end());
        std::sort(v2.begin(), v2.end());
        std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(clickIdx));
    }
    else
        clickIdx = std::move(castInt(args.at(O_CLICK_I)));
    isTrueRand = (args.at(O_IS_TRUE_RAND)[0] == TEXT("true"));

    if (args.at(O_POS)[0] != DEFAULT)
    {
        initPos = false;
        std::vector<int> pos = std::move(castInt(args.at(O_POS)));
        x = pos[0];
        y = pos[1];
    }
    bool isBase = (args.at(O_IS_BASED_H)[0] != TEXT("false"));
    int max = std::stoi(args.at(O_MAX)[0]);
    int min = std::stoi(args.at(O_MIN)[0]);
    int size = std::stoi(args.at(O_INIT_SIZE)[0]);
    short sensi = std::stoi(args.at(O_SENSI)[0]);
    PAD_SIZE = std::stoi(args.at(O_POS_PAD)[0]);

    charaImg = std::make_unique<CharacterImage>(imgs, imgsIdx, defImgIdx, isBase, max, min, size, sensi);
    charaSnd = std::make_unique<CharacterSound>(snds, sndsIdx, vol);
}

void CharacterManager::addImg(int idx, STRING &path)
{
    charaImg->addImg(idx, path);
    imgsIdx.push_back(idx);
}

void CharacterManager::addSnd(int idx, STRING &path, bool isInt)
{
    charaSnd->addSnd(idx, path);
    sndsIdx.push_back(idx);
    intSndsIdx[idx] = isInt;
}

void CharacterManager::addClick(int idx)
{
    clickIdx.push_back(idx);
}

void CharacterManager::setLimit(HWND hWnd, int max, int min)
{
    charaImg->setLimit(hWnd, max, min);
}

CharacterManager::~CharacterManager() {}

void CharacterManager::scaling(HWND hWnd, WPARAM wParam)
{
    short zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
    charaImg->scaling(zDelta);
    SendMessage(hWnd, WM_PAINT, 0, 0);
}

void CharacterManager::setCorner(HWND hWnd, bool isRight)
{
    RECT desktopRect;
    RECT wndRect;
    int pos_x, pos_y;

    SystemParametersInfo(SPI_GETWORKAREA, 0, &desktopRect, 0);
    GetWindowRect(hWnd, &wndRect);

    if (isRight)
    {
        pos_x = (desktopRect.right - desktopRect.left) - (wndRect.right - wndRect.left) + desktopRect.left;
        pos_y = (desktopRect.bottom - desktopRect.top) - (wndRect.bottom - wndRect.top) + desktopRect.top;
        pos_x -= PAD_SIZE;
        pos_y -= PAD_SIZE;
    }
    else
    {
        pos_x = desktopRect.left + PAD_SIZE;
        pos_y = (desktopRect.bottom - desktopRect.top) - (wndRect.bottom - wndRect.top) + desktopRect.top;
        pos_y -= PAD_SIZE;
    }
    setPos(hWnd, pos_x, pos_y);
}

void CharacterManager::setPos(HWND hWnd, int pos_x, int pos_y)
{
    SetWindowPos(hWnd, HWND_TOPMOST, pos_x, pos_y, 0, 0, SWP_NOSIZE);
    x = pos_x;
    y = pos_y;
}

void CharacterManager::move(HWND hWnd, int move_x, int move_y)
{
    setPos(hWnd, x + move_x, y + move_y);
}

void CharacterManager::setSize(HWND hWnd, int size)
{
    charaImg->setSize(hWnd, size);
}

void CharacterManager::setVol(short volume) { charaSnd->setVol(volume); }

short CharacterManager::getW() { return charaImg->w; }

short CharacterManager::getH() { return charaImg->h; }
