#include "network/TcpServer.h"

#ifdef sn_unix_base
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

namespace snet {

#ifdef sn_unix_base
    TcpServer::TcpServer()
    {
    }

    TcpServer::~TcpServer()
    {
        if(serverSocket != -1)
        { stop(); close(); }
    }

    bool TcpServer::open() {

        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == -1)
        {
            throw std::runtime_error("Failed to create server socket");
        }

        int optval = 1;
        if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
        {
            ::close(serverSocket);
            throw std::runtime_error("Failed to set socket options");
        }

        return true;
    }


    bool TcpServer::listen(const char *address, u32 port) {

        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);

        if (bind(serverSocket, reinterpret_cast<sockaddr *>(&serverAddress), sizeof(serverAddress)) == -1)
        {
            ::close(serverSocket);
            throw std::runtime_error("Failed to bind server socket");
        }

        if (::listen(serverSocket, SOMAXCONN) == -1)
        {
            ::close(serverSocket);
            throw std::runtime_error("Failed to listen on server socket");
        }

        isListening = true;
        return true;
    }

    ref<INetServerConnection> TcpServer::accept_client()
    {
        if (!isListening)
        {
            throw std::runtime_error("Server is not listening for connections");
        }

        sockaddr_in clientAddress{};
        socklen_t clientAddressLength = sizeof(clientAddress);

        int clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress), &clientAddressLength);
        if (clientSocket == -1)
        {
            throw std::runtime_error("Failed to accept client connection");
        }

        // 调用 INetServerConnection 的 accept() 方法，处理客户端连接
        auto cn = create_ref<TcpServerConnection>();
        socket_ptr ptr { clientSocket };

        if (!cn->accept(ptr))
        {
            ::close(clientSocket);
            throw std::runtime_error("Failed to handle client connection");
        }

        std::cout << "Accepted client connection" << std::endl;
        return cn;
    }


    bool TcpServer::stop() {

        isListening = false;
        return true;
    }


    bool TcpServer::close() {

        ::close(serverSocket);
        return true;
    }

    bool TcpServerConnection::accept(socket_ptr ptr)
    {
        client.setSocket(ptr);
        return true;
    }

#else

    TcpServer::TcpServer()
    {
    }

    TcpServer::~TcpServer()
    {
        if (serverSocket != INVALID_SOCKET)
        {
            stop();
            close();
        }
    }

    bool TcpServer::open()
    {
        serverSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (serverSocket == INVALID_SOCKET)
        {
            throw std::runtime_error("Failed to create server socket");
        }

        BOOL optval = TRUE;
        if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char *>(&optval), sizeof(optval)) == SOCKET_ERROR)
        {
            closesocket(serverSocket);
            throw std::runtime_error("Failed to set socket options");
        }

        return true;
    }

    bool TcpServer::listen(const char *address, u32 port)
    {
        sockaddr_in serverAddress{};
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(port);

        if (bind(serverSocket, reinterpret_cast<sockaddr *>(&serverAddress), sizeof(serverAddress)) == SOCKET_ERROR)
        {
            closesocket(serverSocket);
            throw std::runtime_error("Failed to bind server socket");
        }

        if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR)
        {
            closesocket(serverSocket);
            throw std::runtime_error("Failed to listen on server socket");
        }

        isListening = true;
        return true;
    }

    ref<INetServerConnection> TcpServer::accept_client()
    {
        if (!isListening)
        {
            throw std::runtime_error("Server is not listening for connections");
        }

        sockaddr_in clientAddress{};
        int clientAddressLength = sizeof(clientAddress);

        SOCKET clientSocket = accept(serverSocket, reinterpret_cast<sockaddr *>(&clientAddress), &clientAddressLength);
        if (clientSocket == INVALID_SOCKET)
        {
            throw std::runtime_error("Failed to accept client connection");
        }

        // Call the accept() method of INetServerConnection to handle the client connection
        auto cn = create_ref<TcpServerConnection>();
        socket_ptr ptr{clientSocket};

        if (!cn->accept(ptr))
        {
            closesocket(clientSocket);
            throw std::runtime_error("Failed to handle client connection");
        }

        std::cout << "Accepted client connection" << std::endl;
        return cn;
    }

    bool TcpServer::stop()
    {
        isListening = false;
        return true;
    }

    bool TcpServer::close()
    {
        closesocket(serverSocket);
        return true;
    }

#endif
}