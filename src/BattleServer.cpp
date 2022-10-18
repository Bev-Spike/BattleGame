#include "BattleServer.h"
#include "EventLoop.h"
#include "MsgHandler.h"
#include "PlayerManager.h"
#include "Proto.h"
#include "Server.h"
#include "Logger.h"
#include "NetManager.h"
#include <functional>
#include <memory>
#include <mutex>

BattleServer::BattleServer(EventLoop* loop) : _playerCnt(0) {
    _server = std::make_unique<Server>(loop);
    _server->setConnectionCallBack(
        std::bind(&BattleServer::OnConnection, this, std::placeholders::_1));
    _server->setMessageCallback(std::bind(&BattleServer::OnReadData,
                                          this,
                                          std::placeholders::_1,
                                          std::placeholders::_2));
    addListenner();
}

void BattleServer::OnConnection(Connection* conn) {
    int socketfd = conn->getSocket()->getFd();
    LOG_INFO << "Connection " << socketfd << " "
             << (conn->getState() == Connection::Connected ? "up" : "down");

    std::unique_lock<std::mutex> lock(_mtx);

    //新用户连接
    if (conn->getState() == Connection::Connected) {
        _cilents[socketfd] = std::make_unique<CilentState>(conn, this);
        _playerCnt++;
    }
    //关闭用户连接
    else {
        //广播下线协议
        std::string id = _cilents[socketfd]->_player->_id;
        MsgLeave leave;
        leave.id = id;
        PLAYER_MANAGER.broadcastMsg(id, leave);
        
        //移除玩家
        _cilents.erase(socketfd);
        _playerCnt --;
    }
}

void BattleServer::OnReadData(Connection* conn, Buffer* buffer) {
    int socketfd = conn->getSocket()->getFd();
    CilentState* state = _cilents[socketfd].get();
    NET_MANAGER.onReceiveData(state, buffer);
}

void BattleServer::addListenner() {
    NET_MANAGER.addMsgListener("MsgEnter", &MsgHandler::handleEnterMsg);
    NET_MANAGER.addMsgListener("MsgList", &MsgHandler::handleListMsg);
    NET_MANAGER.addMsgListener("MsgMove", &MsgHandler::handleMoveMsg);
    // NET_MANAGER.addMsgListener("MsgLeave", &MsgHandler::handleLeaveMsg);
    NET_MANAGER.addMsgListener("MsgAttack", &MsgHandler::handleAttack);
}