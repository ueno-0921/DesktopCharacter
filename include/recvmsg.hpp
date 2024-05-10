#pragma once

#include <windows.h>
#include "msg.hpp"

typedef struct ProcessedMessage : CHARAMSG
{
    int id;
} ProcedMsg;

class ReceiveMessage
{
public:
    ReceiveMessage();
    ~ReceiveMessage();
    ProcedMsg msgProc(LPARAM lParam);

private:
    PCOPYDATASTRUCT pMyCDS;
    ProcedMsg procedMsg;
};
