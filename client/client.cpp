#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <iostream>
#include "TCPconnector.h"

using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("usage: %s <port> <ip>\n", argv[0]);
        exit(1);
    }

    int len;
    string message;
    char line[256];
    TCPConnector *connector = new TCPConnector();
    connector->connect(argv[2], atoi(argv[1]));

    while (message != "exit")
    {
        getline(cin, message);
        connector->stream->send((message + "\n").c_str(), message.size() + 1);
        printf("sent - %s\n", message.c_str());
        size_t pos = 0;
        while (pos < sizeof(line) - 1) {
            ssize_t n = connector->stream->receive(&line[pos], 1); 
            if(n<=0){
                cout << "сервер не отвечает\n";
                delete connector;
                exit(0);
            }
            if (n <= 0) break;
            if (line[pos] == '\n') {
                line[pos + 1] = '\0';
                break;
            }
            pos++;
        }
        line[sizeof(line)-1] = '\0';

        printf("received - %s", line);
        printf("received - %d\n", len);
        memset(line, 0, sizeof(line));
    }
    delete connector;
    exit(0);
}