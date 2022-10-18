#pragma once

#include <memory>
#include "MsgBase.h"
#include "Player.h"
#include <map>
#include <mutex>

//维护一个玩家列表
class PlayerManager {
  private:
    PlayerManager() = default;
    std::mutex _mtx;

  public:
    static PlayerManager& getInstance() {
        static PlayerManager manager;
        return manager;
    }
    std::map<std::string, std::shared_ptr<Player>> _players;
    bool isOnline(std::string);
    std::weak_ptr<Player>  getPlayer(std::string);
    void addPlayer(std::string, std::shared_ptr<Player> player);
    void removePlayer(std::string);
    //广播协议
    //id参数为广播的发起者
    void broadcastMsg(std::string id, MsgBase&);
    void broadcastMsg(MsgBase&);
};

#define PLAYER_MANAGER PlayerManager::getInstance()