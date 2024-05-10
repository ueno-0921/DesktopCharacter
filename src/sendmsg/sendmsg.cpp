#include "msg.hpp"
#include "argparse.hpp"
#include <unordered_map>
#include <STRING.hpp>
#include <vector>
#include <windows.h>

static const auto className = TEXT("DesktopCharacterInterface");

static const std::unordered_map<STRING, int> optionDict = {
    {"--chara_operate", CHARA_OPERATE},
    {"--chara_edit", CHARA_EDIT},
    {"--set_volume", SET_VOLUME},
    {"--set_position", SET_POSITION},
    {"--move_position", MOVE_POSITION},
    {"--set_size", SET_SIZE},
    {"--set_limit", SET_LIMIT},
    {"--set_timer", SET_TIMER},
    {"--destroy", DESTROY}};
COPYDATASTRUCT MyCDS;
CHARAMSG charaMsg;
HWND hwDispatch = FindWindow(APPLICATION_NAME_DC, APPLICATION_NAME_DC);
void sendData();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    sendData();
    return 0;
}

void sendData()
{
    std::vector<STRING> args = getArgs();
    int argC = (int)args.size();
    int msgId = optionDict.at(args[1]);
    charaMsg.first = (argC > 2) ? std::stoi(args[2]) : -1;
    charaMsg.second = (argC > 3) ? std::stoi(args[3]) : -1;
    charaMsg.third = (argC > 4) ? std::stoi(args[4]) : -1;
    strcpy_s(charaMsg.s1, sizeof(charaMsg.s1), (argC > 5) ? args[5].c_str() : "");
    strcpy_s(charaMsg.s2, sizeof(charaMsg.s2), (argC > 6) ? args[6].c_str() : "");

    MyCDS.dwData = msgId;
    MyCDS.cbData = sizeof(charaMsg);
    MyCDS.lpData = &charaMsg;

    SendMessageTimeout(hwDispatch, WM_COPYDATA, (WPARAM)0, (LPARAM)&MyCDS, SMTO_ABORTIFHUNG, 50, 0);
}