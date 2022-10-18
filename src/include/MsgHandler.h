//所有协议的处理方式都放在这里面
#pragma once
#include "Proto.h"
#include "MsgFactory.h"
class CilentState;
class MsgBase;
class MsgHandler {
  public:
    static void handleMoveMsg(CilentState* state, MsgBase* msgBase);
    static void handleEnterMsg(CilentState* state, MsgBase* msgBase);
    static void handleListMsg(CilentState* state, MsgBase* msgBase);
    static void handleLeaveMsg(CilentState* state, MsgBase* msgBase);
    static void handleAttack(CilentState* state, MsgBase* msgBase);
    static void handleHit(CilentState* state, MsgBase* msgHit);
};