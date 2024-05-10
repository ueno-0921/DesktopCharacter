#pragma once

#include <vector>
#include <unordered_map>
#include <memory>
#include "STRING.hpp"
#include "sound.hpp"

class CharacterSound
{
public:
    CharacterSound(std::vector<STRING> &snds, std::vector<int> &idx, short vol);
    ~CharacterSound();
    void setVol(short vol);
    bool play(int idx, bool isInt);
    void addSnd(int idx, STRING &path);

private:
    std::unordered_map<int, std::unique_ptr<PlayWav>> charaSnd;
};

inline bool CharacterSound::play(int idx, bool isInt)
{
    return charaSnd.at(idx)->PlayWavSnd(isInt);
}