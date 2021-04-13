#pragma once
#include "ConnectionInfo.h"
#include "ISocket.h"

namespace EugeneProduction
{
    class Socket : public ISocket
    {
    public:
        explicit Socket(ConnectionInfo info);
        ~Socket();

        bool IsConnected() override;
        void SendData(std::string data) override;
        std::string ReceiveData() override;
        SOCKADDR_IN GetSockAddr() override;
        void CloseConnection() override;

    private:
        ConnectionInfo m_info;
    };
}

