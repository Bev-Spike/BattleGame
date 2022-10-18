#include "MsgHandler.h"

#include "CilentState.h"
#include "NetManager.h"
#include "PlayerManager.h"
#include "Player.h"
#include "Proto.h"
#include "Logger.h"
#include <cstdio>
#include <memory>
#include <string>


void MsgHandler::handleMoveMsg(CilentState* state, MsgBase* msgBase) {
    MsgMove* msgMove = dynamic_cast<MsgMove*>(msgBase);
    LOG_DEBUG << "[协议]get MoveMsg ";
    std::shared_ptr<Player> player = state->_player;
    player->x = msgMove->x;
    player->y = msgMove->y;
    player->z = msgMove->z;
    //广播
    player->broadcast(*msgMove);
}

//进入协议。当有新玩家加入游戏时，获取他的各种信息
void MsgHandler::handleEnterMsg(CilentState* state, MsgBase* msgBase) {
    MsgEnter* enter = dynamic_cast<MsgEnter*>(msgBase);
    LOG_DEBUG << "[协议] get EnterMsg : x = " << enter->x << ",y = " << enter->y
              << ",z = " << enter->z << ",id = " << enter->id;

    if (!state->_isPlayer) {
        //在服务端新建一个玩家
        std::shared_ptr<Player> player(new Player(state));
        state->_player = player;
        player->_id = enter->id;
        player->x = enter->x;
        player->y = enter->y;
        player->z = enter->z;
        player->eulY = enter->rotate;
        player->hp = 100;
        //添加到玩家管理器中
        PLAYER_MANAGER.addPlayer(player->_id, player);
        state->_isPlayer = true;
        // player->broadcast(*enter);//向其他玩家广播自己进入游戏的消息
    }
    //广播玩家进入的消息
    PLAYER_MANAGER.broadcastMsg(enter->id, *enter);
}

void MsgHandler::handleListMsg(CilentState* state, MsgBase* msgBase) {
    MsgList* list = dynamic_cast<MsgList*>(msgBase);
    LOG_DEBUG << "[协议]get listMsg";
    //将所有玩家的信息组装成listMsg
    for (auto& playerInfo : PLAYER_MANAGER._players) {
        std::shared_ptr<Player> player = playerInfo.second;
        if (player != nullptr) {
            list->lists.push_back({player->x,
                                   player->y,
                                   player->z,
                                   player->eulY,
                                   player->hp,
                                   player->_id});
            
        }
    }
    NET_MANAGER.send(state, list);
}

void MsgHandler::handleLeaveMsg(CilentState* state, MsgBase* msgBase) {
    MsgLeave* leave = dynamic_cast<MsgLeave*>(msgBase);
    LOG_DEBUG << "[协议] get LeaveMsg : id = " << leave->id;
    PLAYER_MANAGER.broadcastMsg(leave->id, *leave);
}

void MsgHandler::handleAttack(CilentState* state, MsgBase* msgBase) {
    MsgAttack* attack = dynamic_cast<MsgAttack*>(msgBase);
    LOG_DEBUG << "[协议] get AttackMsg: id = " << attack->id;
    PLAYER_MANAGER.broadcastMsg(attack->id, *attack);
}

//将受到攻击的角色扣血，如果血量小于0，广播死亡协议
//如果血量大于0，广播hit协议，届时被攻击者在客户端会被击退
void MsgHandler::handleHit(CilentState* state, MsgBase* msgHit) {
    MsgHit* hit = dynamic_cast<MsgHit*>(msgHit);
    std::string attId = hit->attacker;
    std::string hitId = hit->hiter;

    //找出被攻击的角色
    std::weak_ptr<Player> hitPlayerPTR = PLAYER_MANAGER.getPlayer(hitId);
    std::shared_ptr<Player> hitPlayer = hitPlayerPTR.lock();
    if (!hitPlayer){
        LOG_ERROR << "[协议] 不存在的被攻击者: " << hitId;
        return;
    }
    hitPlayer->hp -= 25;
    if (hitPlayer->hp <= 0) {
        MsgDie die;
        die.id = hitId;
        PLAYER_MANAGER.broadcastMsg(die);
    }
    else {
        PLAYER_MANAGER.broadcastMsg(*msgHit);
    }
    

}