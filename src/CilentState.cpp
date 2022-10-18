#include "CilentState.h"
#include "BattleServer.h"
#include "PlayerManager.h"
CilentState::CilentState(Connection* conn, BattleServer* server)
    : _conn(conn),
      _server(server),
      _isPlayer(false),
      _lastPingTime(0) {}
//在玩家列表中移除玩家
CilentState::~CilentState() {
    if (_isPlayer) {
        _isPlayer = false;
        PLAYER_MANAGER.removePlayer(_player->_id);
    }
}