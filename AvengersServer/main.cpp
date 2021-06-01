#include <stdio.h>
#include <zmq.hpp>
#include "connect.h"

using namespace std;

void vijand(std::string hero, Verbinding::connect* x);
void gameOver(Verbinding::connect* y);
void battle(std::string held, std::string vijand, Verbinding::connect* z);

int main()
{
    Verbinding::connect* s = new Verbinding::connect();
    while(1)
    {
        int hero = 0;
        s->maken();
        s->reset();

        while(s->deelbuffer[0]!=0 && s->deelbuffer[1]!=0 && s->deelbuffer[2]!=0 && s->deelbuffer[3]!=0)
        {
            s->get();

        }

        if(strcmp(s->buffer, "begin") || strcmp(s->buffer, "Begin"))
        {
            s->reset();
            printf("\nBeginnen\n");
            strcpy(s->buffer, "avengers>S>[Met welke hero wilt u spelen? Hulk, Iron Man, Thor of Spiderman:\n]");
            s->send();
            printf("\nVerzonden\n");
            s->get();
            //keuze hero
            if(!strcmp(s->buffer, "avengers>CL>Hulk") || !strcmp(s->buffer, "avengers>CL>hulk"))
            {
                s->reset();
                strcpy(s->buffer, "avengers>S>[U heeft Hulk gekozen! ]");
                hero = 1;
            }
            else if(!strcmp(s->buffer, "avengers>CL>iron man") || !strcmp(s->buffer, "avengers>CL>Iron Man") || !strcmp(s->buffer, "avengers>CL>Iron man") || !strcmp(s->buffer, "avengers>CL>iron Man"))
            {
                s->reset();
                strcpy(s->buffer,  "avengers>S>[U heeft Iron Man gekozen! ]");
                hero = 2;
            }
            else if(!strcmp(s->buffer, "avengers>CL>Thor") || !strcmp(s->buffer, "avengers>CL>thor"))
            {
                s->reset();
                strcpy(s->buffer,  "avengers>S>[U heeft Thor gekozen! ]");
                hero = 3;
            }
            else if(!strcmp(s->buffer, "avengers>CL>spiderman") || !strcmp(s->buffer, "avengers>CL>Spiderman"))
            {
                s->reset();
                strcpy(s->buffer,  "avengers>S>[U heeft Spiderman gekozen!\n]");
                hero = 4;
            }else
            {
                s->reset();
                strcpy(s->buffer, "mislukt");
            }
            s->send();

            //battle
            switch(hero)
            {
            case 1:
            {
                //hulk
                vijand("Hulk", s);
                break;
            }
            case 2:
            {
                //iron man
                vijand("Iron Man", s);
                break;
            }
            case 3:
            {
                //thor
                vijand("Thor", s);
                break;
            }
            case 4:
            {
                //spiderman
                vijand("Spiderman", s);
                break;
            }
            }
        }
    }
    s->reset();
    s->verbreken();
    return 0;
}

void vijand(std::string held, Verbinding::connect* x)
{
    std::string naamVijand;

    x->reset();
    strcpy(x->buffer, "avengers>S>[Tegen wie wilt u spelen? Thanos, Loki of Magneto:\n]");
    x->send();
    x->get();
    naamVijand = x->buffer;
    naamVijand.erase(0,12);

    battle(held, naamVijand, x);

    //verbreken
    gameOver(x);
}

void gameOver(Verbinding::connect* y)
{
    strcpy(y->buffer, "avengers>S>[stop]");
    y->send();
    printf("\n\nstop gestuurd\n\n");
}

void battle(std::string held, std::string vijand, Verbinding::connect* z)
{
    int hpHeld = 250;
    int hpVijand = 300;
    int attackHeld = 15;
    int attackVijand = 11;
    int genezen = 8;
    std::string outputstring;
    char kanaal[] = "avengers>S>[";

    printf("\nGevecht tussen %s en %s!\n", held.c_str(), vijand.c_str());
    while(hpHeld > 0 && hpVijand > 0)
    {
        outputstring = "";
        strcpy(z->buffer, "avengers>S>[Wilt u aanvallen (a) of genezen (g)? ]");
        z->send();
        printf("Vraag verzonden\n");
        z->reset();
        z->get();
        if(!strcmp(z->buffer, "avengers>CL>a"))
        {
            hpVijand = hpVijand - attackHeld;
            hpHeld = hpHeld - attackVijand;
        }
        else if(!strcmp(z->buffer, "avengers>CL>g"))
        {
            hpHeld = hpHeld + genezen;
        }
        z->reset();
        outputstring.append("U heeft nog ");
        outputstring.append(to_string(hpHeld));
        outputstring.append(" hp, ");
        outputstring.append(vijand);
        outputstring.append(" heeft nog ");
        outputstring.append(to_string(hpVijand));
        outputstring.append(" hp.");
        outputstring.append("]");
        for(int i=0;i<500;i++)
        {
            if(i<12)
            {
                z->buffer[i]=kanaal[i];
            }else
            {
                z->buffer[i]=outputstring[i-12];
            }
        }
        z->send();
        printf("Result verzonden\n");
        z->reset();
    }
}
