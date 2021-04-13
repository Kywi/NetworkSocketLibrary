#pragma once

#include <mutex>
#include <vector>

#include "SocketFactory.h"

namespace EugeneProduction
{
    class SocketManager
    {
    public:
        SocketManager(std::shared_ptr<ISocketFactory> socketFactory);
        ~SocketManager();

        bool IfListens() const;

        std::shared_ptr<ISocket> Connect(const SOCKADDR_IN& address);
        std::shared_ptr<ISocket> Accept();

        void CreateListenSock(const SOCKADDR_IN& address);
        void CloseConnectedSock(std::shared_ptr<ISocket>& sock);
        void CloseAllConnections();

    private:
        void CloseListenSock() const;

        std::shared_ptr<ISocketFactory> m_socketFactory;

        mutable std::mutex m_mutex;
        std::shared_ptr<ISocketListen> m_listenerSocket;
        std::vector<std::shared_ptr<ISocket>> m_sockets;
    };
}