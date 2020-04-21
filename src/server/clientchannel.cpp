#include "clientchannel.h"

#include <unistd.h>

#include <cstring>
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;

namespace tincan::server {

ClientChannel::ClientChannel(int fd) : _fd(fd) {
    _max_read_buffer_size = 255;
}

ClientChannel::~ClientChannel() {
    ::close(_fd);
}

string ClientChannel::read() {
    char buf[_max_read_buffer_size + 1];
    ::memset(&buf, 0, _max_read_buffer_size + 1);

    int result = ::read(_fd, &buf, _max_read_buffer_size);
    if (result < 0) {
        throw runtime_error("Failed to read from client");
    }

    return string(buf);
}

void ClientChannel::write(string value) {
    int result = ::write(_fd, value.c_str(), value.length());
    if (result < 0) {
        throw runtime_error("Failed to write to client");
    }
}

void ClientChannel::set_max_read_buffer_size(int size) {
    _max_read_buffer_size = size;
}

}  // namespace tincan::server