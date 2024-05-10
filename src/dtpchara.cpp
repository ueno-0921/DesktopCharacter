#define IDT_CLICK_TIMER 1
#define TIMER_INTERVAL 90000

#include "charamgr.hpp"
#include "recvmsg.hpp"
#include <memory>
#include <windows.h>

using namespace std;
static const auto szTitle = TEXT(APPLICATION_NAME_DC);
static const auto szWindowClass = TEXT(APPLICATION_NAME_DC);
unique_ptr<CharacterManager> charaMgr;
unique_ptr<ReceiveMessage> recvMsg;
ProcedMsg msg;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpszCmdLine, int nCmdShow) {
    charaMgr = make_unique<CharacterManager>();
    recvMsg = make_unique<ReceiveMessage>();

    MSG msg;
    HWND hWnd;
    WNDCLASSEX windowClass;
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.cbClsExtra = 0;
    windowClass.cbWndExtra = 0;
    windowClass.hInstance = hInstance;
    windowClass.hIcon = NULL;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
    windowClass.lpszMenuName = NULL;
    windowClass.lpszClassName = szWindowClass;
    windowClass.hIconSm = NULL;
    RegisterClassEx(&windowClass);
    hWnd = CreateWindowEx(WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
                          szWindowClass, szTitle, 0,
                          charaMgr->initPos ? 0 : charaMgr->x,
                          charaMgr->initPos ? 0 : charaMgr->y, charaMgr->getW(),
                          charaMgr->getH(), 0, 0, hInstance, 0);
    ShowWindow(hWnd, nCmdShow);
    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)(msg.wParam);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
#ifdef IDT_CLICK_TIMER
        SetTimer(hWnd, IDT_CLICK_TIMER, TIMER_INTERVAL, (TIMERPROC)NULL);
#endif
        if (charaMgr->initPos)
            charaMgr->setCorner(hWnd, true);
        charaMgr->draw(hWnd);
        break;
    case WM_PAINT:
        charaMgr->draw(hWnd);
        break;
    case WM_LBUTTONDOWN:
        ReleaseCapture();
        SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
        break;
    case WM_NCLBUTTONUP:
        charaMgr->draw(hWnd);
        break;
    case WM_RBUTTONUP:
        charaMgr->click(hWnd);
        break;
    case WM_MBUTTONDOWN:
        DestroyWindow(hWnd);
        break;
    case WM_MOUSEWHEEL:
        charaMgr->scaling(hWnd, wParam);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_COPYDATA: {
        msg = recvMsg->msgProc(lParam);
        switch (msg.id) {
        case CHARA_OPERATE:
            if (msg.first >= 0)
                charaMgr->draw(hWnd, msg.first);
            if (msg.second >= 0)
                charaMgr->play(msg.second);
            break;
        case CHARA_EDIT:
            if (msg.first >= 0) {
                STRING tmp = msg.s1;
                charaMgr->addImg(msg.first, tmp);
            }
            if (msg.second >= 0) {
                STRING tmp = msg.s2;
                charaMgr->addSnd(msg.second, tmp, false);
            }
            if (msg.third >= 0)
                charaMgr->addClick(msg.third);
            break;
        case SET_VOLUME:
            if (msg.first >= 0)
                charaMgr->setVol(msg.first);
            break;
        case SET_POSITION:
            charaMgr->setPos(hWnd, msg.first, msg.second);
            break;
        case MOVE_POSITION:
            charaMgr->move(hWnd, msg.first, msg.second);
            break;
        case SET_SIZE:
            charaMgr->setSize(hWnd, msg.first);
            break;
        case SET_LIMIT:
            charaMgr->setLimit(hWnd, msg.first, msg.second);
            break;
#ifdef IDT_CLICK_TIMER
        case SET_TIMER:
            SetTimer(hWnd, IDT_CLICK_TIMER, msg.first, (TIMERPROC)NULL);
            break;
#endif
        case DESTROY:
            DestroyWindow(hWnd);
            break;
        default:
            break;
        }
        break;
    }
#ifdef IDT_CLICK_TIMER
    case WM_TIMER:
        switch (wParam) {
        case IDT_CLICK_TIMER:
            charaMgr->click(hWnd);
            break;
        default:
            break;
        }
        break;
#endif
    default:
        return (DefWindowProc(hWnd, uMsg, wParam, lParam));
    }
    return 0;
}