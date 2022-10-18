#include "Buffer.h"
#include "Connection.h"
#include "Epoll.h"
#include "Server.h"
#include "Socket.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "Channel.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>
#include <cstring>
#include "configor/configor.hpp"
#include "BattleServer.h"
#include "Proto.h"
// #include "SqlConnectionPool.h"
#include "MsgBase.h"
using namespace std;

int main() {
    unique_ptr<EventLoop> loop(new EventLoop());
    unique_ptr<BattleServer> server(new BattleServer(loop.get()));
    loop->loop();
    //ConnectionPool::GetInstance().init("82.156.16.46", "root", "594137", "game", 3306, 2);

    
    return 0;
}

