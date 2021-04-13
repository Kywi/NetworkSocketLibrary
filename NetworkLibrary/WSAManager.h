#pragma once

namespace EugeneProduction
{
    class WSAManager
    {
    public:
        WSAManager(const WSAManager&) = delete;
        WSAManager& operator =(const WSAManager&) = delete;
        ~WSAManager();

        static WSAManager& getInstance();
        void WSAStart();
        void WSAEnd();

    private:
        WSAManager() = default;

        WSADATA m_winSockData;
        bool m_wasCleanedUp = false;
    };
}