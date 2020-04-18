#ifndef TINCAN_SERVER_CHANNEL_H_
#define TINCAN_SERVER_CHANNEL_H_

#include <string>

using std::string;

namespace tincan::server {

class Channel {
   public:
   Channel(int fd);
   ~Channel();
   string read();
   void write(string value);

   private:
   int _fd; 
};

}  // namespace tincan::server

#endif