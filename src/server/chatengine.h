#ifndef TINCAN_SERVER_CHAT_ENGINE_H_
#define TINCAN_SERVER_CHAT_ENGINE_H_

#include <netinet/in.h>
#include <sys/types.h>

#include "connectionhandler.h"

namespace tincan::server {

class ChatEngine {
 public:
  ChatEngine();
  ~ChatEngine();
  void start(short port, ConnectionHandler &handler);
  void close();

 private:
  int _fd;
  struct sockaddr_in _address;

  void _start();
};

}  // namespace tincan::server

#endif