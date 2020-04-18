#include "channel.h"

#include <cstring>
#include <string>
#include <stdexcept>
#include <unistd.h>

using std::string;
using std::runtime_error;

namespace tincan::server {

const int BUF_SIZE = 255;

Channel::Channel(int fd) : _fd(fd) {}

Channel::~Channel() {
    ::close(_fd);
}

string Channel::read() {
    char buf[BUF_SIZE];
    ::memset(&buf, 0, BUF_SIZE);

    int result = ::read(_fd, &buf, BUF_SIZE - 1);
    if(result < 0) {
        throw runtime_error("Failed to read from client");
    }

    return string(buf);
}

void Channel::write(string value) {
    int result = ::write(_fd, value.c_str(), value.length());
    if(result < 0) {
        throw runtime_error("Failed to write to client");
    }
}

}