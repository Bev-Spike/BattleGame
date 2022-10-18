#include "Proto.h"

#include "MsgFactory.h"
#include "configor/json.hpp"

configor::json MsgMove::getJson() { return *this; }
REGISTER(MsgMove);

configor::json MsgEnter::getJson() { return *this; }
REGISTER(MsgEnter);

configor::json MsgList::getJson() { return *this; }
REGISTER(MsgList);

configor::json MsgLeave::getJson() { return *this; }
REGISTER(MsgLeave);

configor::json MsgAttack::getJson() { return *this; }
REGISTER(MsgAttack);

configor::json MsgHit::getJson() { return *this; }
REGISTER(MsgHit);

configor::json MsgDie::getJson() { return *this; }
REGISTER(MsgDie);