#include <stdio.h>
#include <stdlib.h>
#include "StructDefinitions.h"
#include "Feldausgabe.h"
#include "Logik.h"
#include "Netzwerk.h"
#include <string.h>
#include <w32api/synchapi.h>

int SPIELFELDGROESSE;
char abfrage = 'n';
char DatenPaket[64];
int sperre = 0;
char Convstring[2] = {'0','\0'};


int main() {

    SPIELER Spieler1;
    SPIELER Spieler2;

        /*
    char temp[10] = "Stefan1";
    strncpy(DatenPaket,temp,7);
    DatenPaket[7]='\0';
    SendenBrauchbar(DatenPaket,6,1); */ // test fürs senden - funktioniert!


    // 1. Server / Client festlegen
    // Server: Spielername, Zeichen
    // Client: Spielername, Zeichen an Server senden, wenn Server == Client name oder zeichen -> client neu anfragen

    printf("Guten Tag Spieler! \n");
    do {
        //abfrage = '0';
        //printf("%s",abfrage);
        printf("Was darf es sein? - Single- oder Multiplayer? [s] [m] \n");
        scanf(" %c", &abfrage);
    } while (abfrage != 's' && abfrage != 'm');



    if(abfrage == 'm') {

        int networkcheck = GetHosttype();
        int threadDebug = ThreadErstellen(networkcheck);

        if (networkcheck == 0) {
            //Server
/*
            printf("------------------\n");
            printf("Spielereinstellungen\n");
            //Spieler 1
            printf("Spieler Server: [name] ");
            scanf("%s", &Spieler1.name);
            printf("Zeichen von %s : ", Spieler1.name);
            scanf(" %c", &Spieler1.zeichen);
            printf("Spieler 1 eingeloggt: %s - %c - %d \n", Spieler1.name, Spieler1.zeichen, Spieler1.type);
            printf("------------------\n");
            printf("Frage Daten vom Clienten ab...");
*/

            printf("------------------\n");
            printf("Spielereinstellungen\n");
            //Spieler 1
            printf("Spieler Server: [name] ");
            scanf("%s", &Spieler1.name);
            printf("Zeichen von %s : ", Spieler1.name);
            scanf(" %c", &Spieler1.zeichen);
            printf("Spieler 1 eingeloggt: %s - %c - %d \n", Spieler1.name, Spieler1.zeichen, Spieler1.type);
            printf("------------------\n");
            printf("Übermittle Daten...\n");

            //Schickt Datenpaket mit Name und Zeichen
             Convstring[0] = Spieler1.zeichen;
            strcpy(DatenPaket,strcat(Spieler1.name,Convstring));

            printf("DATENPAKET: %s \n",DatenPaket);
            DatenPaket[strlen(Spieler1.name)+strlen(Convstring)+1]='\0';

            SendenBrauchbar(DatenPaket,(int) strlen(Spieler1.name)-1,(int)strlen(Convstring));

            printf("ich höre");

            aktivListen = 1; // Listen Thread für Kommunikation wird aktiviert

            while(checkMessage == 0) {Sleep(100);} // warten...

            checkMessage = 0;

            printf("Spieleinstellungen\n");
            printf("Wie groß soll das Spielfeld sein : (3 - 10)\n");

            scanf("%d", &SPIELFELDGROESSE);

            if(SPIELFELDGROESSE < 3){
                SPIELFELDGROESSE = 3;
            }
            if(SPIELFELDGROESSE > 10){
                SPIELFELDGROESSE = 10;
            }

            printf("Übermittle Spieleinstellung...");

            sprintf(DatenPaket,"%d",SPIELFELDGROESSE);
            printf("Spielfeld ist: %s groß \n", DatenPaket);

           // Convstring[0]= (char) SPIELFELDGROESSE;
            //strcpy(DatenPaket, Convstring);
            //DatenPaket[1] = '\0';

            //DatenPaket[0] = (char) &SPIELFELDGROESSE;
           // printf("Spielfeld ist: %d groß", DatenPaket[0]);

            SendenBrauchbar(DatenPaket,1,1);

            printf("Das Spiel beginnt...");



            //Spielername und Zeichen
            // überprüfen ob client name oder zeichen gleich ist ( wenn ja, nochmal
            // Random zwischen Spieler 1 und zwei auswählen RandZahl
            //RandZahl an Client schicken, -> Du bist spieler ...
            // "Du Bist Spieler .."
            // Spielfeldgröße? wird als Paket geschickt an Client
            // derjenige, der Spieler 1 ist, beginnt ein Paket rüberzuschicken mit 1 4 oder so und aktualisiert das gleichzeitig in seinem Spiel
    printf("test");


        } else if (networkcheck == 1) {
            //Client

            printf("Hallo Spieler 2! \n");
            printf("Warte auf Spielereingabe von Spieler 1...\n");

            //wenn Spieler 1 fertig ist, wird ein Paket mit verschickt, mit Name und Zeichen
            //Wenn bekommen, also CheckMessage == 1, dann eigene Eingabe machen und prüfen ob die sich überlappen.
            // wenn nicht, schicke das Paket zum Server rüber und er übernimmt es auch auf seiner Seite.

            aktivListen = 1;

            while(checkMessage == 0) {Sleep(100);} // warten...

            checkMessage = 0;
            aktivListen = 0;

            do {
            printf("------------------\n");
            printf("Spieler 1: %s, mit %c",string_1,string_2);
            printf("------------------\n");
            printf("Spielereinstellungen\n");
            //Spieler 2
            printf("Spieler Server: [name] ");
            scanf("%s", &Spieler2.name);
            printf("Zeichen von %s : ", Spieler2.name);
            scanf(" %c", &Spieler2.zeichen);
            printf("Spieler 1 eingeloggt: %s - %c - %d \n", Spieler2.name, Spieler2.zeichen, Spieler2.type);
            printf("------------------\n");
            printf("Übermittle Daten...\n");

                Convstring[0]= Spieler2.zeichen; // Spieler 2. in String umgewandelt für Abfrage

            } while (string_1 == Spieler1.name ||  string_2[0] == Convstring[0]);

            //Schickt Datenpaket mit Name und Zeichen
            char Convstring[2] = {Spieler2.zeichen, '\0'};
            strcpy(DatenPaket, strcat(Spieler2.name, Convstring));

            printf("DATENPAKET: %s \n", DatenPaket);
            DatenPaket[strlen(Spieler2.name) + strlen(Convstring) + 1] = '\0';

            SendenBrauchbar(DatenPaket, (int) strlen(Spieler2.name) - 1, (int) strlen(Convstring));

            printf("warte auf Spieler 1 Spielfeldeinstellungen \n");

            aktivListen = 1;

            while(checkMessage == 0) {Sleep(100);} // warten...

            checkMessage = 0;
            aktivListen = 0;

            SPIELFELDGROESSE = string_1[0];
            printf("Das Spielfeld ist %d groß. \n", string_1[0]);

                //ChangeModus(1); // 1 - ist warte auf Server paket für Name und Spieler



                //char string1[32] = GetMessages(1);
               // char string2[32] = GetMessages(2);
            /*
                while (checkMessage == 1) {

                    printf("bin in sperre");

                    char Convstring[2] = {Spieler1.zeichen, '\0'}; // Spieler 1. in String umgewandelt

                    if (string_1 == Spieler1.name ||  string_2[0] == Convstring[0]) {

                        char temp[10] = "not";
                        strcpy(DatenPaket, temp);
                        printf("DATENPAKET abgelehnt: %s \n", DatenPaket);
                        SendenBrauchbar(DatenPaket, strlen(temp),0);




                    } else {

                        sperre = 1;
                        char temp[10] = "ok";
                        strcpy(DatenPaket, temp);
                        printf("DATENPAKET erlaubt: %s \n", DatenPaket);
                        SendenBrauchbar(DatenPaket, strlen(temp),0);




                    }


                }
            */
            /*
            do {

                printf("------------------\n");
                printf("Spielereinstellungen\n");
                //Spieler 2
                printf("Spieler Server: [name] ");
                scanf("%s", &Spieler2.name);
                printf("Zeichen von %s : ", Spieler2.name);
                scanf(" %c", &Spieler2.zeichen);
                printf("Spieler 1 eingeloggt: %s - %c - %d \n", Spieler2.name, Spieler2.zeichen, Spieler2.type);
                printf("------------------\n");
                printf("Übermittle Daten...\n");

                //Schickt Datenpaket mit Name und Zeichen
                char Convstring[2] = {Spieler2.zeichen, '\0'};
                strcpy(DatenPaket, strcat(Spieler2.name, Convstring));

                printf("DATENPAKET: %s \n", DatenPaket);
                DatenPaket[strlen(Spieler2.name) + strlen(Convstring) + 1] = '\0';

                SendenBrauchbar(DatenPaket, (int) strlen(Spieler2.name) - 1, (int) strlen(Convstring));

            } while (GetMessages(1) != "ok");

            printf("Spieler2 geschafft!");

          //  SendenBrauchbar(DatenPaket,strlen(Spieler2.name),strlen(Spieler2.zeichen));

            //SendenBrauchbar(DatenPaket,int 1. string, int 2. String, int 3...)

            //Spielername und Zeichen an Server schicken
            // warte auf Zuweisung
            //


        */
        } else if (networkcheck == -1) {
            printf("Netzwerkfehler aufgetreten!");
        }

        KOORDINATE Playfield[SPIELFELDGROESSE][SPIELFELDGROESSE];

    }


    printf("Spieleinstellungen\n");
    printf("Wie groß soll das Spielfeld sein : (3 - 10)\n");
    scanf("%d", &SPIELFELDGROESSE);

    if(SPIELFELDGROESSE < 3){
        SPIELFELDGROESSE = 3;
    }
    if(SPIELFELDGROESSE > 10){
        SPIELFELDGROESSE = 10;
    }
    KOORDINATE Playfield[SPIELFELDGROESSE][SPIELFELDGROESSE];
/*
    printf("------------------\n");
    printf("Spielereinstellungen\n");
    //Spieler 1
    printf("Spieler 1: ");
    scanf("%s", &Spieler1.name);
    printf("Zeichen von %s : ", Spieler1.name);
    scanf(" %c", &Spieler1.zeichen);
    printf("Typ von %s (1 Computer, 0 Spieler) : ", Spieler1.name);
    scanf(" %d", &Spieler1.type);
    printf("Spieler 1 eingeloggt: %s - %c - %d \n", Spieler1.name, Spieler1.zeichen, Spieler1.type);
    printf("------------------\n"); */
    //Spieler 2
    printf("Spieler 2: ");
    scanf("%s", &Spieler2.name);
   while (strcmp(Spieler2.name, Spieler1.name) == 0){
        printf("Bitte anderen Namen eingeben\n");
        scanf(" %s", &Spieler2.name);
    };
    printf("Zeichen von %s : ", Spieler2.name);
    scanf(" %c", &Spieler2.zeichen);
    while (Spieler2.zeichen == Spieler1.zeichen){
        printf("Bitte anderes Zeichen eingeben\n");
        scanf(" %c", &Spieler2.zeichen);
    }
    printf("Typ von %s (1 Computer, 0 Spieler) : ", Spieler2.name);
    scanf(" %d", &Spieler2.type);
    printf("Spieler 1 eingeloggt: %s - %c - %d \n", Spieler2.name, Spieler2.zeichen, Spieler2.type);

    int gewinnerValue = 0;

    for(int spalte = 0; spalte < SPIELFELDGROESSE; spalte++) {
        for (int reihe = 0; reihe < SPIELFELDGROESSE; reihe++) {
            Playfield[reihe][spalte].value = CELLPLACEHOLDER;
        }
    }
    system("clear");
    int counter = 0;
    while(gewinnerValue == 0){

        printf("Zug : %d\n", counter);

        drawTicTacToeField(Playfield);

        if(counter % 2 == 0){
            doTurn(Spieler1,Playfield);
        }
        else {
            doTurn(Spieler2,Playfield);
        }
        counter++;

        gewinnerValue = testForWinner(Playfield);

        system("clear");
    }

    if(gewinnerValue == 2){
        printf("Das Feld ist voll, Unentschieden\n");
        return 1;
    }

    drawTicTacToeField(Playfield);

    if(counter % 2 == 0){
        printf("%s ist Sieger\n",Spieler2.name);
    } else {
        printf("%s ist Sieger\n",Spieler1.name);
    }
    return 1;
}

