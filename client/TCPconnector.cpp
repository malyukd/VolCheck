#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <errno.h>
#include "TCPconnector.h"

void TCPConnector::connect(const char* server, int port)
{
    struct sockaddr_in address;

    memset (&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    if (resolveHostName(server, &(address.sin_addr)) != 0 ) {
        inet_pton(PF_INET, server, &(address.sin_addr));        
    } 

    // Create and connect the socket, bail if we fail in either case
    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("socket() failed");
        this->stream = NULL;
    }
    if (::connect(sd, (struct sockaddr*)&address, sizeof(address)) != 0) {
        perror("connect() failed");
        close(sd);
        this->stream = NULL;
    }
    this->stream = new TCPStream(sd, &address);
}

TCPConnector::~TCPConnector()
{
    delete this->stream;
}

int TCPConnector::resolveHostName(const char* hostname, struct in_addr* addr) 
{ //чтобы можно было подключаться по доменному имени
    struct addrinfo *res;
  
    int result = getaddrinfo (hostname, NULL, NULL, &res);
    if (result == 0) {
        memcpy(addr, &((struct sockaddr_in *) res->ai_addr)->sin_addr, sizeof(struct in_addr));
        freeaddrinfo(res);
    }
    return result;
}