#include <netinet/in.h>
#include "TCPstream.h"

class TCPConnector
{
  
  public:
    TCPStream* stream;
    void connect(const char* server, int port);
    ~TCPConnector();
  private:
    int resolveHostName(const char* host, struct in_addr* addr);
};