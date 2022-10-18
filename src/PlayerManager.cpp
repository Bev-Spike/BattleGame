#include "PlayerManager.h"

#include "CilentState.h"
#include "Logger.h"
#include "NetManager.h"
#include "Player.h"

#include <memory>
#include <mutex>

bool PlayerManager::isOnline(std::string id) {
    std::unique_lock<std::mutex> lock(_mtx);
    return _players.count(id);
}

std::weak_ptr<Player> PlayerManager::getPlayer(std::string id) {
    std::unique_lock<std::mutex> lock(_mtx);
    if (_players.count(id))
        return _players[id];
    return {};
}

void PlayerManager::addPlayer(std::string id, std::shared_ptr<Player> player) {
    std::unique_lock<std::mutex> lock(_mtx);
    _players[id] = std::shared_ptr<Player>(player);
}

void PlayerManager::removePlayer(std::string id) {
    std::unique_lock<std::mutex> lock(_mtx);
    if (_players.count(id)) {
        _players.erase(id);
        LOG_TRACE << "移除玩家" << id;
        LOG_TRACE << "remain player count =" << _players.size();
    }
}

//对除了
void PlayerManager::broadcastMsg(std::string id, MsgBase& msg) {
    //有严重的线程安全问题。。我现在想不到有什么办法可以快速解决
    //涉及到Connection对象生命周期的问题，如果在运行这个函数的时候，有connection对象析构了怎么办？
    for (auto& p : _players) {
        if (p.first != id) {
            std::unique_lock<std::mutex> lock(_mtx);
            if (p.second != nullptr)
                p.second.get()->Send(msg);
        }
    }
}

void PlayerManager::broadcastMsg(MsgBase& msg) {
    for (auto& p : _players) {
        std::unique_lock<std::mutex> lock(_mtx);
        if (p.second != nullptr)
            p.second.get()->Send(msg);
    }
}