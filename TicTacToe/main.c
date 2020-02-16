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
char Convstring[2] = {'0','\0'};
int Spielernummer = 0;
int x,y;

ClientTurn(int Spielernummer);
ServerTurn(int Spielernummer);
char tempstring[2];
int ZugEmpfangen = 0;



int main() {

    SPIELER Spieler1;
    SPIELER Spieler2;

    //sprintf(DatenPaket,"%d",tempInt[1]);

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
        Spieler1.type = 0; //Beides Spieler typen
        Spieler2.type = 0;

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

            //Datenpaket vom Clienten empfangen mit validem Spielernamen und Zeichen
            strcpy(Spieler2.name,string_1);
            Spieler2.zeichen = string_2[0];


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

            printf("Das Spiel beginnt...\n");
            Spielernummer = 1;



            //Spielername und Zeichen
            // überprüfen ob client name oder zeichen gleich ist ( wenn ja, nochmal
            // Random zwischen Spieler 1 und zwei auswählen RandZahl
            //RandZahl an Client schicken, -> Du bist spieler ...
            // "Du Bist Spieler .."
            // Spielfeldgröße? wird als Paket geschickt an Client
            // derjenige, der Spieler 1 ist, beginnt ein Paket rüberzuschicken mit 1 4 oder so und aktualisiert das gleichzeitig in seinem Spiel


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
            printf("Spieler 1: %s, mit %s\n",string_1,string_2);

            strcpy(Spieler1.name,string_1);
            Spieler1.zeichen = string_2[0];

            printf("------------------\n");
            printf("Spielereinstellungen\n");
            //Spieler 2
            printf("Spieler Server: [name] ");
            scanf("%s", &Spieler2.name);
            printf("Zeichen von %s : ", Spieler2.name);
            scanf(" %c", &Spieler2.zeichen);
            printf("Spieler 2 eingeloggt: %s - %c \n", Spieler2.name, Spieler2.zeichen);
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



            SPIELFELDGROESSE = atoi(string_1); //String umwandlung in Integer
            printf("Das Spielfeld ist %d groß. \n", SPIELFELDGROESSE);

            Spielernummer = 2;

        } else if (networkcheck == -1) {
            printf("Netzwerkfehler aufgetreten!\n");
        }

        KOORDINATE Playfield[SPIELFELDGROESSE][SPIELFELDGROESSE];
        int gewinnerValue = 0;

        for(int spalte = 0; spalte < SPIELFELDGROESSE; spalte++) {
            for (int reihe = 0; reihe < SPIELFELDGROESSE; reihe++) {
                Playfield[reihe][spalte].value = CELLPLACEHOLDER;
            }
        }
        system("clear");
        int counter = 0;
        while(gewinnerValue == 0){
            if(gewinnerValue == 0) {
                ServerTurn(Spielernummer); //Server ist dran mit Nummer 1
                if (ZugEmpfangen == 1) {
                    ZugEmpfangen = 0;
                    doTurn(Spieler1, Playfield, 1, atoi(string_1), atoi(string_2));
                } else { doTurn(Spieler1, Playfield, 1, x, y); }

                drawTicTacToeField(Playfield);
                gewinnerValue = testForWinner(Playfield);
            }
            if(gewinnerValue == 0) {
                ClientTurn(Spielernummer);
                if (ZugEmpfangen == 1) {
                    ZugEmpfangen = 0;
                    doTurn(Spieler2, Playfield, 1, atoi(string_1), atoi(string_2));
                } else { doTurn(Spieler2, Playfield, 1, x, y); }

                drawTicTacToeField(Playfield);
                gewinnerValue = testForWinner(Playfield);
            }
/*
            if(Spielernummer == 2) { //Server ist als erstes am Zug
                printf("Spieler: %s ist am Zug!",Spieler1.name );
                aktivListen = 1;
                while(checkMessage == 0) {Sleep(100);} // warten...
                checkMessage = 0;
                aktivListen = 0;
                //Bekomme paket und speicher es ein.

            }
            if(Spielernummer == 1) {

                printf("Spieler: %s ist am Zug!",Spieler2.name);

                strcpy(DatenPaket,)
                SendenBrauchbar(DatenPaket, (int) strlen(Spieler2.name) - 1, (int) strlen(Convstring));
            }*/

            counter++;
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
            doTurn(Spieler1,Playfield,0,0,0);
        }
        else {
            doTurn(Spieler2,Playfield,0,0,0);
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

ClientTurn(int Spielernummer) {

    if(Spielernummer == 2) {

        printf("Spieler: 2 ist am Zug!\n");
        printf("Eingabe als 1,1 2,2 usw \n");
        x = 0;
        y = 0;
        scanf(" %d,%d",&x,&y);
        int z = (1*y)+(10*x);
        sprintf(DatenPaket,"%d",z);
        printf("%s",DatenPaket);
        SendenBrauchbar(DatenPaket,1,1);

    } else if(Spielernummer == 1){

        printf("Spieler: 2 ist am Zug!\n");
        aktivListen = 1;
        printf("Bitte warten... \n");
        while(checkMessage == 0) {Sleep(100);} // warten...
        checkMessage = 0;
        aktivListen = 0;
        ZugEmpfangen = 1;




    }

}

ServerTurn(int Spielernummer) {

    if(Spielernummer == 1) {

        //scanf("%d,%d",tempInt[0],tempInt[1]);
      //  sprintf(DatenPaket,"%d",tempInt[0]);
       // sprintf(DatenPaket,"%d",tempInt[1]);
      //  sprintf(DatenPaket,"%d",tempInt[1]);
       // scanf(" %s", &tempstring);
       // strcpy(DatenPaket,tempstring);
        printf("Spieler: 1 ist am Zug");
        printf("Eingabe als 1,1 2,2 usw \n");
        x = 0;
        y = 0;
        scanf(" %d,%d",&x,&y);
        int z = (1*y)+(10*x);
        sprintf(DatenPaket,"%d",z);
        printf("%s",DatenPaket);
        SendenBrauchbar(DatenPaket,1,1);

    } else if(Spielernummer == 2){

        printf("Spieler: 1 ist am Zug\n");
        aktivListen = 1;
        printf("Bitte warten... \n");
        while(checkMessage == 0) {Sleep(100);} // warten...
        checkMessage = 0;
        aktivListen = 0;
        ZugEmpfangen = 1;




    }



}

