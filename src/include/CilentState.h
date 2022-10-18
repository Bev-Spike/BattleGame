//保存连接客户的数据
#pragma once

#include <memory>
#include "Buffer.h"
#include "Connection.h"
#include "Player.h"
class Connection;
class BattleServer;
class Buffer;
class CilentState {
  public:
    Connection* _conn;
    BattleServer* _server;
    std::shared_ptr<Player> _player;
    //该客户数据是否已经对应一个User
    bool _isPlayer;
    long _lastPingTime;

  public:
    CilentState(Connection* conn, BattleServer* server);
    ~CilentState();
};