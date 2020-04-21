#ifndef TINCAN_SERVER_CLIENT_HANDLER_H_
#define TINCAN_SERVER_CLIENT_HANDLER_H_

#include "clientchannel.h"
#include "connectionhandler.h"

namespace tincan::server {

class ClientHandler : public ConnectionHandler {
   public:
    void operator()(ClientChannel chan) override;
};

}  // namespace tincan::server

#endif