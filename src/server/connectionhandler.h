#ifndef TINCAN_SERVER_CONNECTION_HANDLER_H_
#define TINCAN_SERVER_CONNECTION_HANDLER_H_

#include "channel.h"

namespace tincan::server {

class ConnectionHandler {
 public:
  virtual void operator()(Channel chan) = 0;
};

}  // namespace tincan::server

#endif