#include <string>
#include <netinet/in.h>
#include "TCPstream.h"

using namespace std;

class TCPAcceptor
{
  int m_lsd;
  int m_port;
  string m_address;
  bool m_listening;

public:
  TCPStream *stream;
  TCPAcceptor(int port, const char *address = "");
  ~TCPAcceptor();

  int start();
  void accept();

private:
  TCPAcceptor() {}
};
