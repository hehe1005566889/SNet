#include "network/INet.h"
#include "network/TcpClient.h"
#include "network/TcpServer.h"

namespace snet {

    ref<INetServer> INetServer::create(ConnectionType type)
    {
        switch (type)
        {
        case ConnectionType::TCP:
            return create_ref<TcpServer>();
            break;
        default:
            throw std::runtime_error("unknown api");
            break;
        }
        
        throw std::runtime_error("unknown api");
        return nullptr;
    }

    ref<INetClient> INetClient::create(ConnectionType type)
    {
        switch (type)
        {
        case ConnectionType::TCP:
            return create_ref<TcpClient>();
            break;
        default:
            throw std::runtime_error("unknown api");
            break;
        }

        throw std::runtime_error("unknown api");
        return nullptr;
    }
}