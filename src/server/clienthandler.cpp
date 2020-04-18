#include "clienthandler.h"
#include "channel.h"

#include <string>

using std::string;

namespace tincan::server {

void ClientHandler::operator()(Channel chan) {
    chan.write("Tell me something\n");
    string response = chan.read();
    chan.write("You told me: " + response + "\n");
}

}