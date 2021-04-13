#pragma once
#include <WinSock2.h>

namespace EugeneProduction
{
    struct ConnectionInfo
    {
        SOCKET socketConnection;
        SOCKADDR_IN m_address;
    };
}
