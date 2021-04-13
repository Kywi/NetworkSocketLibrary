#include "pch.h"
#include "ConnectionInfo.h"
#include "ISocketListen.h"

namespace EugeneProduction
{
    class ISocketFactory
    {
    public:
        virtual std::shared_ptr<ISocketListen> CreateListenSocket(const SOCKADDR_IN& conInfo) = 0;
        virtual std::shared_ptr<ISocket> CreateConnectionSocket(const SOCKADDR_IN& conInfo) = 0;
        virtual std::shared_ptr<ISocket> CreateAcceptedConnectionSocket(ConnectionInfo info) = 0;
    };
}
