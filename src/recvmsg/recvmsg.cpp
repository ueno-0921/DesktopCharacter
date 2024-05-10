#include "recvmsg.hpp"

ReceiveMessage::ReceiveMessage() {}
ReceiveMessage::~ReceiveMessage() {}
ProcedMsg ReceiveMessage::msgProc(LPARAM lParam)
{
    pMyCDS = (PCOPYDATASTRUCT)lParam;
    procedMsg.id = (int)pMyCDS->dwData;
    procedMsg.first = (int)((CHARAMSG *)(pMyCDS->lpData))->first;
    procedMsg.second = (int)((CHARAMSG *)(pMyCDS->lpData))->second;
    procedMsg.third = (int)((CHARAMSG *)(pMyCDS->lpData))->third;
    strcpy_s(procedMsg.s1, sizeof(procedMsg.s1), (LPSTR)((CHARAMSG *)(pMyCDS->lpData))->s1);
    strcpy_s(procedMsg.s2, sizeof(procedMsg.s2), (LPSTR)((CHARAMSG *)(pMyCDS->lpData))->s2);
    return procedMsg;
}