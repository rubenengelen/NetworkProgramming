#include <stdio.h>
#include <zmq.hpp>
#include "connect.h"

using namespace std;

void vijand(std::string hero, Verbinding::connect* x);
void gameOver(Verbinding::connect* y);
void battle(std::string held, std::string vijand, Verbinding::connect* z);
void battleplus(int aantal, string avengerArray[], string vijandArray[], int hpheld[], int attackheld[], int hpvijand[], int attackvijand[], int, Verbinding::connect* b);

int main()
{
    Verbinding::connect* s = new Verbinding::connect();
    while(1)
    {
        int hero = 0;
        string heronaam;
        string vijandnaam;
        int aantalAvengers;
        string avengerArray[3];
        string vijandArray[3];
        int hpheld[3];
        int attackheld[3];
        int hpvijand[3];
        int attackvijand[3];
        int genezen = 8;
        int aantal = 0;

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
            strcpy(s->buffer, "avengers>S>[Met hoeveel avengers wilt u spelen? (max 3) \n]");
            s->send();
            s->get();
            printf("net gekregen");
            if(!strcmp(s->buffer, "avengers>CL>3"))
            {
                printf("aantal  = 3");
                aantalAvengers = 3;
            }
            else if(!strcmp(s->buffer, "avengers>CL>2"))
            {
                printf("aantal  = 2");
                aantalAvengers = 2;
            }
            else
            {
                printf("aantal  = 1");
                aantalAvengers = 1;
            }
            aantal = aantalAvengers;
            //1 avenger
            if(aantalAvengers == 1)
            {
                strcpy(s->buffer, "avengers>S>[Spelen met 1 avenger \n]");
                s->send();
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
            else    //2 of 3
            {
                strcpy(s->buffer, "avengers>S>[Spelen met 2 of 3 avengers \n]");
                s->send();
                while(aantalAvengers != 0)
                {
                    strcpy(s->buffer, "avengers>S>[Geef een avenger op. Hulk, Iron Man, Thor of Spiderman:\n]");
                    s->send();
                    printf("\nVerzonden\n");
                    s->get();
                    if(!strcmp(s->buffer, "avengers>CL>Hulk") || !strcmp(s->buffer, "avengers>CL>hulk"))
                    {
                        s->reset();
                        strcpy(s->buffer, "avengers>S>[U heeft Hulk gekozen! ]");
                        heronaam = "Hulk";
                    }
                    else if(!strcmp(s->buffer, "avengers>CL>iron man") || !strcmp(s->buffer, "avengers>CL>Iron Man") || !strcmp(s->buffer, "avengers>CL>Iron man") || !strcmp(s->buffer, "avengers>CL>iron Man"))
                    {
                        s->reset();
                        strcpy(s->buffer,  "avengers>S>[U heeft Iron Man gekozen! ]");
                        heronaam = "Iron Man";
                    }
                    else if(!strcmp(s->buffer, "avengers>CL>Thor") || !strcmp(s->buffer, "avengers>CL>thor"))
                    {
                        s->reset();
                        strcpy(s->buffer,  "avengers>S>[U heeft Thor gekozen! ]");
                        heronaam = "Thor";
                    }
                    else if(!strcmp(s->buffer, "avengers>CL>spiderman") || !strcmp(s->buffer, "avengers>CL>Spiderman"))
                    {
                        s->reset();
                        strcpy(s->buffer,  "avengers>S>[U heeft Spiderman gekozen!\n]");
                        heronaam = "Spiderman";
                    }else
                    {
                        s->reset();
                        strcpy(s->buffer, "mislukt");
                    }
                    avengerArray[aantalAvengers] = hero;
                    strcpy(s->buffer, "avengers>S>[Volgende vraag \n]");
                    s->send();

                    strcpy(s->buffer, "avengers>S>[Geef een vijand op voor deze avenger. Thanos, Loki of Magneto:\n]");
                    s->send();
                    printf("\nVerzonden\n");
                    s->get();
                    if(!strcmp(s->buffer, "avengers>CL>Thanos") || !strcmp(s->buffer, "avengers>CL>thanos"))
                    {
                        s->reset();
                        strcpy(s->buffer, "avengers>S>[U heeft Thanos gekozen! ]");
                        s->send();
                        vijandnaam = "Thanos";
                    }
                    else if(!strcmp(s->buffer, "avengers>CL>Loki") || !strcmp(s->buffer, "avengers>CL>loki"))
                    {
                        s->reset();
                        strcpy(s->buffer,  "avengers>S>[U heeft Loki gekozen! ]");
                        s->send();
                        vijandnaam = "Loki";
                    }
                    else if(!strcmp(s->buffer, "avengers>CL>Magneto") || !strcmp(s->buffer, "avengers>CL>Magneto"))
                    {
                        s->reset();
                        strcpy(s->buffer,  "avengers>S>[U heeft Magneto gekozen! ]");
                        s->send();
                        vijandnaam = "Magneto";
                    }
                    vijandArray[aantalAvengers] = vijandnaam;
                    aantalAvengers--;
                    s->reset();
                }
                s->reset();
                strcpy(s->buffer,  "avengers>S>[Gevecht begint ]");
                s->send();

                //2 of 3 fight
                for(int i = 0; i <= aantal; i++)
                {
                    //stats avenger
                    if(!strcmp(avengerArray[i].c_str(), "Hulk"))
                    {
                        hpheld[i] = 300;
                        attackheld[i] = 17;
                    }
                    else if(!strcmp(avengerArray[i].c_str(), "Iron Man"))
                    {
                        hpheld[i] = 200;
                        attackheld[i] = 15;
                    }
                    else if(!strcmp(avengerArray[i].c_str(), "Thor"))
                    {
                        hpheld[i] = 250;
                        attackheld[i] = 19;
                    }
                    else if(!strcmp(avengerArray[i].c_str(), "Spiderman"))
                    {
                        hpheld[i] = 350;
                        attackheld[i] = 25;
                    }

                    //stats vijand
                    if(!strcmp(vijandArray[i].c_str(), "Thanos"))
                    {
                        hpvijand[i] = 250;
                        attackvijand[i] = 12;
                    }
                    else if(!strcmp(vijandArray[i].c_str(), "Loki"))
                    {
                        hpvijand[i] = 225;
                        attackvijand[i] = 15;
                    }
                    else if(!strcmp(vijandArray[i].c_str(), "Magneto"))
                    {
                        hpvijand[i] = 150;
                        attackvijand[i] = 10;
                    }
                    printf("Battleplus starten)");
                    battleplus(aantal, avengerArray, vijandArray, hpheld, attackheld, hpvijand, attackvijand, genezen, s);

                }
                gameOver(s);
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
    int hpHeld;
    int hpVijand = 500;
    int attackHeld;
    int attackVijand = 11;
    int genezen = 8;
    std::string outputstring;
    char kanaal[] = "avengers>S>[";
    int hpHulk = 300;
    int attackHulk = 17;
    int hpIronMan = 200;
    int attackIronMan = 15;
    int hpThor = 250;
    int attackThor = 19;
    int hpSpiderman = 350;
    int attackSpiderman = 25;
    int keuze = 0;

    if(!strcmp(held.c_str(), "Hulk"))
    {
        hpHeld = hpHulk;
        attackHeld = attackHulk;
        keuze = 1;
    }
    else if(!strcmp(held.c_str(), "Iron Man"))
    {
        hpHeld = hpIronMan;
        attackHeld = attackIronMan;
        keuze = 2;
    }
    else if(!strcmp(held.c_str(), "Thor"))
    {
        hpHeld = hpThor;
        attackHeld = attackThor;
        keuze = 3;
    }
    else if(!strcmp(held.c_str(), "Spiderman")) //warning maar een van de if structures is altijd juist door vorige structures
    {
        hpHeld = hpSpiderman;
        attackHeld = attackSpiderman;
        keuze = 4;
    }

    printf("\nGevecht tussen %s en %s!\n", held.c_str(), vijand.c_str());
    while(hpHeld > 0 && hpVijand > 0)
    {
        outputstring = "";
        strcpy(z->buffer, "avengers>S>[Wilt u aanvallen (a), genezen (g) of wisselen van held (Hulk, Iron Man, Thor, Spiderman)? ]");
        z->send();
        printf("Vraag verzonden\n");
        z->reset();
        z->get();
        if(!strcmp(z->buffer, "avengers>CL>Hulk") || !strcmp(z->buffer, "avengers>CL>hulk"))
        {
            hpHeld = hpHulk;
            attackHeld = attackHulk;
            held = "Hulk";
            keuze = 1;
        }
        else if(!strcmp(z->buffer, "avengers>CL>Iron Man") || !strcmp(z->buffer, "avengers>CL>Iron man") || !strcmp(z->buffer, "avengers>CL>iron man") || !strcmp(z->buffer, "avengers>CL>iron Man"))
        {
            hpHeld = hpIronMan;
            attackHeld = attackIronMan;
            held = "IronMan";
            keuze = 2;
        }

        else if(!strcmp(z->buffer, "avengers>CL>Thor") || !strcmp(z->buffer, "avengers>CL>thor"))
        {
            hpHeld = hpThor;
            attackHeld = attackThor;
            held = "Thor";
            keuze = 3;
        }
        else if(!strcmp(z->buffer, "avengers>CL>Spiderman") || !strcmp(z->buffer, "avengers>CL>spiderman"))
        {
            hpHeld = hpSpiderman;
            attackHeld = attackSpiderman;
            held = "Spiderman";
            keuze = 4;
        }
        else if(!strcmp(z->buffer, "avengers>CL>a"))
        {
            hpVijand = hpVijand - attackHeld;
            hpHeld = hpHeld - attackVijand;
        }
        else if(!strcmp(z->buffer, "avengers>CL>g"))
        {
            hpHeld = hpHeld + genezen;
        }

        //switch voor bijhouden hp van verschillende avengers
        switch (keuze)
        {
        case 1:
            hpHulk = hpHeld;
            printf("\n hulk in switch hp = %d\n", hpHeld);
            break;
        case 2:
            hpIronMan = hpHeld;
            printf("\n ironman in switch hp = %d\n", hpHeld);
            break;
        case 3:
            hpThor = hpHeld;
            printf("\n thor in switch hp = %d\n", hpHeld);
            break;
        case 4:
            hpSpiderman = hpHeld;
            printf("\n spiderman in switch hp = %d\n", hpHeld);
            break;
        default:
            break;
        }

        z->reset();
        outputstring.append("U bent ");
        outputstring.append(held.c_str());
        outputstring.append(" en u heeft nog ");
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
        printf("%s", z->buffer);
        z->send();
        printf("Result verzonden\n");
        z->reset();
    }
}

void battleplus(int aantal, string avengerArray[], string vijandArray[], int hpheld[], int attackheld[], int hpvijand[], int attackvijand[], int, Verbinding::connect* b)
{
    while(hpheld[0] != 0 && hpheld[1] != 0 && hpheld[2] != 0 && hpheld[3] != 0 && hpvijand[0] != 0 && hpvijand[1] != 0 && hpvijand[2] != 0 && hpvijand[3] != 0)
    {
        for(int i = 0; i <= aantal; i++)
        {
            std::string outputstring;
            char kanaal[] = "avengers>S>[";
            b->reset();
            outputstring.append("Aanval tussen ");
            outputstring.append(avengerArray[0]);
            outputstring.append(" en ");
            outputstring.append(vijandArray[0]);
            outputstring.append("]");
            for(int i=0;i<500;i++)
            {
                if(i<12)
                {
                    b->buffer[i]=kanaal[i];
                }else
                {
                    b->buffer[i]=outputstring[i-12];
                }
            }
            b->send();
        }
    }
}












