#include "server/chatengine.h"
#include "server/clienthandler.h"

using tincan::server::ClientHandler;
using tincan::server::ChatEngine;

int main() {

    ClientHandler handler;
    ChatEngine engine;

    engine.start(3000, handler);

    return 0;
}