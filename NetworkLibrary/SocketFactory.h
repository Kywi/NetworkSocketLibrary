#pragma once

#include <memory>

#include "ISocket.h"
#include "ISocketFactory.h"
#include "ISocketListen.h"

namespace EugeneProduction
{
    class SocketFactory : public ISocketFactory
    {
    public:
        std::shared_ptr<ISocketListen> CreateListenSocket(const SOCKADDR_IN& conInfo) override;
        std::shared_ptr<ISocket> CreateConnectionSocket(const SOCKADDR_IN& conInfo) override;
        std::shared_ptr<ISocket> CreateAcceptedConnectionSocket(ConnectionInfo info) override;
    };
}