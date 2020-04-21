#ifndef TINCAN_SERVER_CHANNEL_H_
#define TINCAN_SERVER_CHANNEL_H_

#include <string>

using std::string;

namespace tincan::server {

class ClientChannel {
   public:
    ClientChannel(int fd);
    ~ClientChannel();
    string read();
    void write(string value);
    void set_max_read_buffer_size(int size);

   private:
    int _fd;
    int _max_read_buffer_size;
};

}  // namespace tincan::server

#endif