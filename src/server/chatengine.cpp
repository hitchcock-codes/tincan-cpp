#include "chatengine.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include "channel.h"
#include "connectionhandler.h"

using std::cerr;
using std::cout;
using std::endl;
using std::runtime_error;

const int MAX_CONNECTIONS_IN_QUEUE = 5;

namespace tincan::server {

ChatEngine::ChatEngine() {
    _fd = 0;
    ::memset(&_address, 0, sizeof(_address));
}

ChatEngine::~ChatEngine() {
    if(_fd != 0) {
        ::close(_fd);
    }
}

void ChatEngine::start(short port, ConnectionHandler &handler) {
  cout << "Starting chat engine" << endl;

  // Create a new socket file descriptor
  _fd = ::socket(AF_INET, SOCK_STREAM, 0);
  if (_fd < 0) {
    throw runtime_error("Failed to create socket");
  }

  try {
    // Enable immediate socket reuse after process exits
    int so_reuseaddr_value = 1;
    ::setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &so_reuseaddr_value, sizeof(so_reuseaddr_value));

    // Initialize the struct that contains information about ther address for
    // the server
    socklen_t address_size = sizeof(_address);

    _address.sin_family = AF_INET;          // Match the socket type
    _address.sin_addr.s_addr = INADDR_ANY;  // Use the host's IP address
    _address.sin_port = ::htons(3000);        // Set the port

    // Bind the socket file descriptor to the address specified in the above
    // struct
    int result = ::bind(_fd, (struct sockaddr *)&_address, address_size);
    if (result < 0) {
      int err = errno;
      if (err == EADDRINUSE) {
        throw runtime_error("Failed to bind socket: address already in use");
      } else {
        throw runtime_error("Failed to bind on socket");
      }
    }

    // Begin listening for connections on the socket file descriptor
    result = ::listen(_fd, MAX_CONNECTIONS_IN_QUEUE);
    if (result < 0) {
      int err = errno;
      if (err == EADDRINUSE) {
        throw runtime_error("Failed to listen on socket: address already in use");
      } else {
        throw runtime_error("Failed to listen on socket");
      }
    }

    // The server socket is initialized

    // Initialize the client address struct
    struct sockaddr_in client_address;
    ::memset(&client_address, 0, address_size);
    socklen_t client_address_size;

    int client_fd = ::accept(_fd, (struct sockaddr *)&client_address, &client_address_size);
    if (client_fd < 0) {
      throw runtime_error("Failed to accept client connection");
    }

    // Got a client connection. Create a channel and pass it to the handler.
    Channel chan(client_fd);

    handler(client_fd);
  } catch (std::exception &e) {
    cerr << "Error in tincan: " << e.what() << endl;
    ::close(_fd);
  }
}

}  // namespace tincan::server