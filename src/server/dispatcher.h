#ifndef TINCAN_SERVER_DISPATCHER_H_
#define TINCAN_SERVER_DISPATCHER_H_

#include <memory>

#include "clientchannel.h"

using std::weak_ptr;

namespace tincan::server {

class Dispatcher {
 public:
  virtual void register_channel() = 0;
  virtual void unregister_channel() = 0;

 private:
}

}  // namespace tincan::server

#endif