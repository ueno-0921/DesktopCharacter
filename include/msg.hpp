#pragma once
#include <windows.h>

#define APPLICATION_NAME_DC "DesktopCharacter"

typedef struct CharacterMESSAGE
{
    int first;
    int second;
    int third;
    char s1[MAX_PATH];
    char s2[MAX_PATH];
} CHARAMSG;

#define CHARA_OPERATE 1
#define CHARA_EDIT 2
#define SET_VOLUME 3
#define SET_POSITION 4
#define MOVE_POSITION 5
#define SET_SIZE 6
#define SET_LIMIT 7
#define DESTROY 8
#define SET_TIMER 9