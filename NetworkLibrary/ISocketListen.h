#pragma once

#include "ConnectionInfo.h"
#include "ISocket.h"

namespace EugeneProduction
{
    class ISocketListen : public ISocket
    {
    public:
        virtual ConnectionInfo AcceptConnection() = 0;
    };
}
