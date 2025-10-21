#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include "TCPacceptor.h"
#include "StringHandler.h"

int main(int argc, char **argv)
{

    TCPAcceptor *acceptor = NULL;
    if (argc == 3)
    {
        acceptor = new TCPAcceptor(atoi(argv[1]), argv[2]);
    }
    else if (argc == 2)
    {
        acceptor = new TCPAcceptor(atoi(argv[1]));
    }
    else
    {
        printf("usage: server <port> [<ip>]\n");
        delete acceptor;
        exit(1);
    }
    bool program = true;
    if (acceptor->start() != 0)
    {
        delete acceptor;
        exit(1);
    }
    ssize_t len;
    char line[256];
    while (true)
    {
        acceptor->accept();
        if (acceptor->stream == NULL)
            continue;


        while ((len = acceptor->stream->receive(line, sizeof(line))) > 0)
        {
            line[len] = 0;
            printf("received - %s\n", line);
            if (!strcmp(line, "exit"))
            {
                delete acceptor;
                exit(1);
            }
            else
            {
                StringHandler str(line);
                if (str.isValid())
                {
                    acceptor->stream->send("Success", len);
                    printf("Success");
                }
                else
                {
                    acceptor->stream->send(str.error, sizeof(str.error));
                    printf("sent - %s\n", str.error);
                }
            }
        }
    }
    delete acceptor;

    exit(0);
}