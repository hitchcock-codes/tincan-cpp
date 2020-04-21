#include "clienthandler.h"

#include <string>

#include "clientchannel.h"

using std::string;

namespace tincan::server {

void ClientHandler::operator()(ClientChannel chan) {
    chan.write("Tell me something\n");
    string response = chan.read();
    chan.write("You told me: " + response + "\n");
}

}  // namespace tincan::server