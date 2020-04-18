#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::runtime_error;

const int MAX_CONNECTIONS_IN_QUEUE = 5;

int main() {
  cout << "Opening a TCP Socket" << endl;

  // Create a new socket file descriptor
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_fd < 0) {
    throw runtime_error("Failed to create socket");
  }

  try {
    // Enable immediate socket reuse after process exits
    int so_reuseaddr_value = 1;
    setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &so_reuseaddr_value, sizeof(so_reuseaddr_value));

    // Initialize the struct that contains information about ther address for
    // the server
    struct sockaddr_in server_address;
    socklen_t server_address_size = sizeof(server_address);
    memset(&server_address, 0, server_address_size);

    server_address.sin_family = AF_INET;          // Match the socket type
    server_address.sin_addr.s_addr = INADDR_ANY;  // Use the host's IP address
    server_address.sin_port = htons(3000);        // Set the port

    // Bind the socket file descriptor to the address specified in the above
    // struct
    int result = bind(socket_fd, (struct sockaddr *)&server_address, server_address_size);
    if (result < 0) {
      int err = errno;
      if (err == EADDRINUSE) {
        throw runtime_error("Failed to bind socket: address already in use");
      } else {
        throw runtime_error("Failed to bind on socket");
      }
    }

    // Begin listening for connections on the socket file descriptor
    result = listen(socket_fd, MAX_CONNECTIONS_IN_QUEUE);
    if (result < 0) {
      int err = errno;
      if (err == EADDRINUSE) {
        throw runtime_error("Failed to listen on socket: address already in use");
      } else {
        throw runtime_error("Failed to listen on socket");
      }
    }

    // Initialize the client address struct
    struct sockaddr_in client_address;
    memset(&client_address, 0, server_address_size);
    socklen_t client_address_size;

    int client_fd = accept(socket_fd, (struct sockaddr *)&client_address, &client_address_size);
    if (client_fd < 0) {
      throw runtime_error("Failed to accept client connection");
    }

    send(client_fd, "Hello, world!\n", 14, 0);

    close(client_fd);
    close(socket_fd);

    return 0;
  } catch (std::exception &e) {
    cerr << "Error in tincan: " << e.what() << endl;
    close(socket_fd);
  }
}