#pragma once

#include "Buffer.h"
#include "Connection.h"
#include "CilentState.h"
#include "Server.h"
#include <memory>
#include <mutex>
#include <unordered_map>
class EventLoop;

class BattleServer {
  private:
    std::unique_ptr<Server> _server;
    std::unordered_map<int, std::unique_ptr<CilentState>> _cilents;
    int _playerCnt;
    std::mutex _mtx;
    void addListenner();


  public:
    BattleServer(EventLoop* loop);
    ~BattleServer() = default;

    //在建立和关闭连接时调用
    void OnConnection(Connection* conn);
    void OnReadData(Connection* conn, Buffer* buffer);

};
