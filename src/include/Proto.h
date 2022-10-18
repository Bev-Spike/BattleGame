#ifndef __PROTO__
#define __PROTO__
//将所有协议都写在这个文件中

#include "MsgBase.h"
#include "configor/json.hpp"

#include <string>
class MsgMove : public MsgBase {
  public:
    float x;
    float y;
    float z;
    std::string id;
    MsgMove() { protoName = "MsgMove"; }

    JSON_BIND(MsgMove, protoName, x, y, z, id);
    configor::json getJson();
};

//进入游戏协议
class MsgEnter : public MsgBase {
  public:
    MsgEnter() { protoName = "MsgEnter"; }
    float x;
    float y;
    float z;
    float rotate;
    std::string id;
    JSON_BIND(MsgEnter, protoName, x, y, z, id)
    configor::json getJson();
};

//同步所有玩家的信息
class MsgList : public MsgBase {
  public:
    MsgList() { protoName = "MsgList"; }
    struct PlayerInfo {
        float x;
        float y;
        float z;
        float rotate;
        int hp;
        std::string id;
        JSON_BIND(PlayerInfo, x, y, z, rotate, hp, id);
    };
    std::vector<PlayerInfo> lists;
    json getJson();
    JSON_BIND(MsgList, protoName, lists);
};

class MsgLeave : public MsgBase {
  public:
    MsgLeave() { protoName = "MsgLeave"; }
    std::string id;
    JSON_BIND(MsgLeave, protoName, id);
    json getJson();
};

class MsgAttack : public MsgBase {
  public:
    MsgAttack() { protoName = "MsgAttack"; }
    std::string id;
    float eulY;
    JSON_BIND(MsgAttack, protoName, id, eulY);
    json getJson();
};

//击中协议
class MsgHit : public MsgBase {
  public:
    MsgHit() { protoName = "MsgHit"; }

    std::string attacker; //攻击者的ID
    std::string hiter;    //被打的人的ID
    float eulY; //攻击者的朝向,被攻击的人要向后平移一段距离
    JSON_BIND(MsgHit, protoName, attacker, hiter, eulY);
    json getJson();
};

class MsgDie : public MsgBase {
  public:
    MsgDie() { protoName = "MsgDie"; }
    std::string id; //死亡者的ID
    JSON_BIND(MsgDie, protoName, id);
    json getJson();
};
#endif