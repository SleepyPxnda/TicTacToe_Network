#include <stdio.h>
#include <stdlib.h>
#include "StructDefinitions.h"
#include "Feldausgabe.h"
#include "Logik.h"
#include "Netzwerk.h"
#include <string.h>

int SPIELFELDGROESSE;
char abfrage = 'n';
char DatenPaket[64];

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


            char Convstring[2]= {Spieler2.zeichen, '\0'};
            strcpy(DatenPaket,strcat(Spieler2.name,Convstring));

            printf("DATENPAKET: %s \n",DatenPaket);
            DatenPaket[strlen(Spieler2.name)+strlen(Convstring)+1]='\0';

            SendenBrauchbar(DatenPaket,(int) strlen(Spieler2.name)-1,(int)strlen(Convstring));

          //  SendenBrauchbar(DatenPaket,strlen(Spieler2.name),strlen(Spieler2.zeichen));

            //SendenBrauchbar(DatenPaket,int 1. string, int 2. String, int 3...)

            //Spielername und Zeichen an Server schicken
            // warte auf Zuweisung
            //



        } else if (networkcheck == -1) {
            printf("Netzwerkfehler aufgetreten!");
        }

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

