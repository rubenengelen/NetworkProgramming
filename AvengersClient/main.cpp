#include <stdio.h>
#include <zmq.hpp>
#include "connect.h"

int main()
{
    char kanaal[] = "avengers>CL>";
    Verbinding::connect* s = new Verbinding::connect();
    s->maken();
    s->reset();

    strcpy(s->buffer, "avengers>CL>[begin]");
    s->send();
    printf("\nVerzonden\n");
    s->reset();
    //held en vijand
    for(int i = 0; i < 2; i++)
    {
        s->get();   //vraag
        char input[50];
        gets(input);
        for(int i=0;i<50;i++)
        {
            if(i<12)
            {
                s->buffer[i]=kanaal[i];
            }else
            {
                s->buffer[i]=input[i-12];
            }
        }
        s->send();
        s->reset();
        s->get();   //antwoord
    }

    //gevecht
    while(strcmp(s->buffer, "avengers>S>[stop]"))
    {
        char input[15];
        gets(input);
        for(int i=0;i<50;i++)
        {
            if(i<12)
            {
                s->buffer[i]=kanaal[i];
            }else
            {
                s->buffer[i]=input[i-12];
            }
        }
        s->send();
        s->reset();
        s->get();   //antwoord
        s->get();   //vraag
    }
    s->reset();
    s->verbreken();
    return 0;
}
//strcmp(s->buffer, "avengers>S>[stop]")
