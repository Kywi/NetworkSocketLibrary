#include "pch.h"
#include "WSAManager.h"

#include <exception>

using namespace EugeneProduction;

WSAManager::~WSAManager()
{
    if (m_wasCleanedUp)
        return;

    m_wasCleanedUp = true;
    WSACleanup();
}

WSAManager& WSAManager::getInstance()
{
    static WSAManager instance;
    return instance;
}

void WSAManager::WSAStart()
{
    const long successful = WSAStartup(MAKEWORD(2, 1), &m_winSockData);
    if (successful != 0) throw std::exception("WSAStartup failed with error!\n");
}

void WSAManager::WSAEnd()
{
    m_wasCleanedUp = true;
    WSACleanup();
}
