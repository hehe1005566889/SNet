#include "network/TcpClient.h"

#ifdef sn_unix_base
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

namespace snet {

#ifdef sn_unix_base
    TcpClient::TcpClient() : _socket_fd(-1) {}

    TcpClient::~TcpClient()
    {
        close();
    }

    bool TcpClient::open()
    {
        {
        _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket_fd == -1)
        {
            throw std::runtime_error("open socket error");
            return false;
        }
        return true;
        }
    }

    bool TcpClient::connect(const char *address, u32 port)
    {
        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        if (inet_pton(AF_INET, address, &(serverAddr.sin_addr)) <= 0)
        {
            throw std::runtime_error("address error");
            return false;
        }

        if (::connect(_socket_fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
        {
            throw std::runtime_error("connect error");
            return false;
        }

        return true;
    }

    bool TcpClient::send(const u8 *data, u32 size)
    {
        return send(data, size);
    }

    bool TcpClient::send(const void *data, u32 size)
    {
        ssize_t sentBytes = ::send(_socket_fd, data, size, 0);
        if (sentBytes < 0)
        {
            throw std::runtime_error("send data error");
            return false;
        }
        return true;
    }

    int TcpClient::read(void *data)
    {
        ssize_t bytesRead = ::recv(_socket_fd, data, 1024, 0);
        if (bytesRead < 0)
        {
            throw std::runtime_error("read data error");
            return -1;
        }
        return static_cast<int>(bytesRead);
    }
    int TcpClient::read(u8 *data)
    {
        return read(data);
    }

    bool TcpClient::close()
    {
        if (_socket_fd != -1)
        {
            ::close(_socket_fd);
            _socket_fd = -1;
        }
        return true;
    }

    bool TcpClient::stop()
    {
        return close();
    }

    bool TcpClient::setSocket(socket_ptr ptr)
    { _socket_fd = ptr.socket; }

#else

    TcpClient::TcpClient() : _socket_fd(INVALID_SOCKET)
    {}

    TcpClient::~TcpClient()
    {
        close();
    }

    bool TcpClient::open()
    {
        _socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (_socket_fd == INVALID_SOCKET)
        {
            throw std::runtime_error("open socket error");
            return false;
        }
        return true;
    }

    bool TcpClient::connect(const char *address, u32 port)
    {
        struct sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(port);
        if (inet_pton(AF_INET, address, &(serverAddr.sin_addr)) <= 0)
        {
            throw std::runtime_error("address error");
            return false;
        }

        if (::connect(_socket_fd, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR)
        {
            throw std::runtime_error("connect error");
            return false;
        }

        return true;
    }

    bool TcpClient::send(const u8 *data, u32 size)
    {
        return send(reinterpret_cast<const void *>(data), size);
    }

    bool TcpClient::send(const void *data, u32 size)
    {
        int sentBytes = ::send(_socket_fd, reinterpret_cast<const char *>(data), size, 0);
        if (sentBytes == SOCKET_ERROR)
        {
            throw std::runtime_error("send data error");
            return false;
        }
        return true;
    }

    int TcpClient::read(void *data)
    {
        char buffer[1024];
        int bytesRead = ::recv(_socket_fd, buffer, sizeof(buffer), 0);
        if (bytesRead == SOCKET_ERROR)
        {
            throw std::runtime_error("read data error");
            return -1;
        }
        memcpy(data, buffer, bytesRead);
        return bytesRead;
    }

    int TcpClient::read(u8 *data)
    {
        return read(reinterpret_cast<void *>(data));
    }

    bool TcpClient::close()
    {
        if (_socket_fd != INVALID_SOCKET)
        {
            ::closesocket(_socket_fd);
            _socket_fd = INVALID_SOCKET;
        }
        return true;
    }

    bool TcpClient::stop()
    {
        return close();
    }

    bool TcpClient::setSocket(socket_ptr ptr)
    {
        _socket_fd = ptr.socket;
    }

#endif
}