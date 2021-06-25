#include "connect.h"

Verbinding::connect::connect()
{

}

void Verbinding::connect::maken()
{
    this->context = zmq_ctx_new();

    this->sub = zmq_socket (context, ZMQ_SUB);
    this->pusher = zmq_socket( context, ZMQ_PUSH );
    zmq_connect( pusher, "tcp://benternet.pxl-ea-ict.be:24041" );
    zmq_connect( sub, "tcp://benternet.pxl-ea-ict.be:24042" );

    this->reset();
}

void Verbinding::connect::send()
{
    zmq_send( pusher, buffer,500 , 0 );
}

void Verbinding::connect::get()
{
    int i = 0;
    int t = 0;
    char letter = 0;
    zmq_setsockopt(this->sub, ZMQ_SUBSCRIBE,"avengers>CL>", 12);
    printf("\nwaiting\n");
    zmq_recv (sub, buffer, 500, 0);

    printf("\nbuffer: %s\n",buffer);

    while(buffer[i] !=  '[')
    {
        i++;
    }
    i++;
    while(buffer[i] != ']')
    {
        deelbuffer[t] = letter;
        t++;
        i++;
    }
}

void Verbinding::connect::reset()
{
    for(int i=0; i<500;i++)
    {
        buffer[i]=' ';
        deelbuffer[i] = ' ';
    }
}

void Verbinding::connect::verbreken()
{
    zmq_close( sub);
    zmq_close( pusher );
    zmq_ctx_shutdown( context ); //optional for cleaning lady order (get ready you l*zy f*ck)
    zmq_ctx_term( context ); //cleaning lady goes to work
}
