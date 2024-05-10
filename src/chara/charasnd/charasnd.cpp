#include "charasnd.hpp"

CharacterSound::CharacterSound(std::vector<STRING> &snds, std::vector<int> &idx, short vol)
{
    for (int i = 0; i < (int)idx.size(); ++i)
        addSnd(idx.at(i), snds.at(i));
    setVol(vol);
}

CharacterSound::~CharacterSound()
{
    setVol(100);
}

void CharacterSound::addSnd(int idx, STRING &path)
{
    charaSnd.insert(std::move(std::pair<int, std::unique_ptr<PlayWav>>(idx, std::make_unique<PlayWav>(path))));
}

void CharacterSound::setVol(short vol)
{
    short volumeScale = (vol > 100) ? 100
                        : (vol < 0) ? 0
                                    : vol;
    DWORD baseVolume = (DWORD)(((0xFFFF) * volumeScale) / 100);
    DWORD stereoVolume = ((baseVolume << 16) & 0xFFFF0000) + (baseVolume & 0xFFFF);
    waveOutSetVolume(0, stereoVolume);
}