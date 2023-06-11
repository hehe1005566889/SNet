#include "network/UdpServer.h"

#ifdef sn_unix_base
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

namespace snet {

    UdpServer::~UdpServer() {
        if (serverSocket != -1)
        { stop(); close(); }
    }

    bool UdpServer::open() {
        serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
        if (serverSocket == -1)
        {
            throw std::runtime_error("Failed to create server socket");
            return false;
        }

        return true;
    }

    bool UdpServer::listen(const char *address, u32 port)
    {
        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);

        if (bind(serverSocket, reinterpret_cast<sockaddr *>(&serverAddress), sizeof(serverAddress)) == -1)
        {
            close();
            throw std::runtime_error("Failed to bind server socket");
            return false;
        }

        return true;
    }

    ref<INetServerConnection> UdpServer::accept_client()
    {
    }

    bool UdpServer::stop()
    {
    }

    bool UdpServer::close()
    {
    }
}