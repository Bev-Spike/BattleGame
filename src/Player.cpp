#include "Player.h"
#include "NetManager.h"
#include "PlayerManager.h"
Player::Player(CilentState* state) : _state(state){};
void Player::Send(MsgBase& msg) { NET_MANAGER.send(_state, &msg); }

void Player::broadcast(MsgBase& msg) {
    PLAYER_MANAGER.broadcastMsg(_id, msg);
}