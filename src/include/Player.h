#pragma once

#include "MsgBase.h"
#include <string>
class CilentState;
class Player {
  public:
    std::string _id;
    CilentState* _state;
    int hp;
    float x;
    float y;
    float z;
    float eulY;
  public:
    Player(CilentState*);
    ~Player() = default;
    void Send(MsgBase&);
    void broadcast(MsgBase&);
};