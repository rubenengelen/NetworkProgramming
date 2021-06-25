#ifndef CONNECT_H
#define CONNECT_H

#include <stdio.h>
#include <zmq.hpp>

namespace Verbinding
{
class connect
{
public:
    connect();
    void * context; //Global context, because you only need one !
    void *sub;
    void *pusher;
    char buffer [500];
    char deelbuffer [500];
    void maken();
    void verbreken();
    void send();
    void get();
    void reset();
};
}
#endif // CONNECT_H
