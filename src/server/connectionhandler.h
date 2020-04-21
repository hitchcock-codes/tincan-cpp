#ifndef TINCAN_SERVER_CONNECTION_HANDLER_H_
#define TINCAN_SERVER_CONNECTION_HANDLER_H_

#include "clientchannel.h"

namespace tincan::server {

class ConnectionHandler {
 public:
  virtual void operator()(ClientChannel chan) = 0;
};

}  // namespace tincan::server

#endif