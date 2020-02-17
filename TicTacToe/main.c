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

char tempstring[2];
int ZugEmpfangen = 0;

void sendWinMessage(int , SPIELER);



int main() {

    SPIELER Spieler1;
    SPIELER Spieler2;

    // 1. Server / Client festlegen
    // Server: Spielername, Zeichen
    // Server: Spielername, Zeichen an Client senden, wenn Server == Client name oder zeichen -> client neu eingeben

    printf("Willkommen\n");
    do {
        printf("Single- oder Multiplayer? [s] [m] \n");
        scanf(" %c", &abfrage);
    } while (abfrage != 's' && abfrage != 'm');

    if (abfrage == 'm') {

        int networkcheck = GetHosttype();
        ThreadErstellen(networkcheck);
        Spieler1.type = 0; //Beides Spieler typen
        Spieler2.type = 0;

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
            printf("Übermittle Daten...\n");

            //Schickt Datenpaket mit Name und Zeichen
            Convstring[0] = Spieler1.zeichen;
            strcpy(DatenPaket, strcat(Spieler1.name, Convstring));

            printf("DATENPAKET: %s \n", DatenPaket);
            DatenPaket[strlen(Spieler1.name) + strlen(Convstring) + 1] = '\0';

            SendenBrauchbar(DatenPaket, (int) strlen(Spieler1.name) - 1, (int) strlen(Convstring));

            aktivListen = 1; // Listen Thread für Kommunikation wird aktiviert

            printf("Warte auf Spieler 2 einstellung...");

            while (checkMessage == 0) {
                Sleep(100);
            } // warten...
            checkMessage = 0;

            //Datenpaket vom Clienten empfangen mit validem Spielernamen und Zeichen
            strcpy(Spieler2.name, string_1);
            Spieler2.zeichen = string_2[0];
            
            printf("Spieleinstellungen\n");

            printf("Wie groß soll das Spielfeld sein : (3 - 10)\n");

            scanf("%d", &SPIELFELDGROESSE);

            if (SPIELFELDGROESSE < 3) {
                SPIELFELDGROESSE = 3;
            }
            if (SPIELFELDGROESSE > 10) {
                SPIELFELDGROESSE = 10;
            }

            printf("Übermittle Spieleinstellung...");

            sprintf(DatenPaket, "%d", SPIELFELDGROESSE);
            printf("Spielfeld ist: %s groß \n", DatenPaket);
            if (SPIELFELDGROESSE < 10) {
                SendenBrauchbar(DatenPaket, 1, 1);
            } else { SendenBrauchbar(DatenPaket, 2, 1); }

            printf("Das Spiel beginnt...\n");
            Spielernummer = 1;


        } else if (networkcheck == 1) {

            //Client

            printf("Hallo Spieler 2! \n");
            printf("Warte auf Spielereingabe von Spieler 1...\n");

            //wenn Spieler 1 fertig ist, wird ein Paket mit verschickt, mit Name und Zeichen
            //Wenn bekommen, also CheckMessage == 1, dann eigene Eingabe machen und prüfen ob die sich überlappen.
            // wenn nicht, schicke das Paket zum Server rüber und er übernimmt es auch auf seiner Seite.

            aktivListen = 1;

            while (checkMessage == 0) { Sleep(100); } // warten...

            checkMessage = 0;
            aktivListen = 0;

            do {
                printf("------------------\n");
                printf("Spieler 1: %s, mit %s\n", string_1, string_2);

                strcpy(Spieler1.name, string_1);
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

                Convstring[0] = Spieler2.zeichen; // Spieler 2. in String umgewandelt für Abfrage

            } while (string_1 == Spieler1.name || string_2[0] == Convstring[0]);

            //Schickt Datenpaket mit Name und Zeichen
            char Convstring[2] = {Spieler2.zeichen, '\0'};
            strcpy(DatenPaket, strcat(Spieler2.name, Convstring));

            printf("DATENPAKET: %s \n", DatenPaket);
            DatenPaket[strlen(Spieler2.name) + strlen(Convstring) + 1] = '\0';

            SendenBrauchbar(DatenPaket, (int) strlen(Spieler2.name) - 1, (int) strlen(Convstring));

            printf("warte auf Spieler 1 Spielfeldeinstellungen \n");

            aktivListen = 1;

            while (checkMessage == 0) { Sleep(100); } // warten...

            checkMessage = 0;
            aktivListen = 0;


            SPIELFELDGROESSE = atoi(string_1); //String umwandlung in Integer
            printf("Das Spielfeld ist %d groß. \n", SPIELFELDGROESSE);

            Spielernummer = 2;

        } else if (networkcheck == -1) {
            printf("Netzwerkfehler aufgetreten!\n");
        }

        // INITIALISIERUNG FÜR SPIEL

        int gewinnerValue = 0;
        KOORDINATE Playfield[SPIELFELDGROESSE][SPIELFELDGROESSE];


        for (int spalte = 0; spalte < SPIELFELDGROESSE; spalte++) {
            for (int reihe = 0; reihe < SPIELFELDGROESSE; reihe++) {
                Playfield[reihe][spalte].value = CELLPLACEHOLDER;

            }
        }

        system("clear");
        int counter = 0;
        while (gewinnerValue == 0) {
            //ServerTurn

            if (Spielernummer == 1) {

                printf("Spieler: 1 ist am Zug\n");
                printf("Eingabe als 1,1 2,2 usw \n");
                x = 0;
                y = 0;
                int a = 0;
                do {
                    scanf(" %d,%d", &x, &y);
                    int z = (1 * y) + (10 * x);
                    sprintf(DatenPaket, "%d", z);
                    // printf("%s", DatenPaket);
                    a = doTurn(Spieler1, Playfield, 1, x, y);
                } while (a == -1);

                SendenBrauchbar(DatenPaket, 1, 1);

            } else if (Spielernummer == 2) {

                printf("Spieler: 1 ist am Zug\n");
                aktivListen = 1;
                printf("Bitte warten... \n");
                while (checkMessage == 0) {
                    Sleep(100);
                } // warten...
                checkMessage = 0;
                aktivListen = 0;
                ZugEmpfangen = 1;
            }

            if (ZugEmpfangen == 1) {
                ZugEmpfangen = 0;
                doTurn(Spieler1, Playfield, 1, atoi(string_1), atoi(string_2));
            }

            drawTicTacToeField(Playfield);
            gewinnerValue = testForWinner(Playfield);

            if (gewinnerValue == 2) {
                printf("Das Feld ist voll, Unentschieden\n");
                return 1;
            }

            //Client

            if (Spielernummer == 2) {

                printf("Spieler: 2 ist am Zug!\n");
                printf("Eingabe als 1,1 2,2 usw \n");
                x = 0;
                y = 0;
                int a = 0;
                do {
                    scanf(" %d,%d", &x, &y);
                    int z = (1 * y) + (10 * x);
                    sprintf(DatenPaket, "%d", z);
                    // printf("%s", DatenPaket);
                    a = doTurn(Spieler2, Playfield, 1, x, y);
                } while (a == -1);

                SendenBrauchbar(DatenPaket, 1, 1);

            } else if (Spielernummer == 1) {

                printf("Spieler: 2 ist am Zug!\n");
                aktivListen = 1;
                printf("Bitte warten... \n");
                while (checkMessage == 0) { Sleep(100); } // warten...
                checkMessage = 0;
                aktivListen = 0;
                ZugEmpfangen = 1;
            }

            if (ZugEmpfangen == 1) {
                ZugEmpfangen = 0;
                doTurn(Spieler2, Playfield, 1, atoi(string_1), atoi(string_2));
            }

            drawTicTacToeField(Playfield);
            gewinnerValue = testForWinner(Playfield);

            system("clear");
        }

        if (gewinnerValue == 2) {
            printf("Das Feld ist voll, Unentschieden\n");
            return 1;
        }

        //Anhand des Counters(Runden) wird Gewinner ermittelt
        SPIELER gewinner;
        if (counter % 2 == 0) {
            gewinner = Spieler2;
        } else {
            gewinner = Spieler1;
        }
        sendWinMessage(gewinnerValue, gewinner);
        return 1;
    } else if (abfrage == 's') {


        //Singleplayer

        printf("Spieleinstellungen\n");
        printf("Wie groß soll das Spielfeld sein : (3 - 10)\n");
        scanf("%d", &SPIELFELDGROESSE);

        if (SPIELFELDGROESSE < 3) {
            SPIELFELDGROESSE = 3;
        }
        if (SPIELFELDGROESSE > 10) {
            SPIELFELDGROESSE = 10;
        }

        printf("------------------\n");
        printf("\033[31mSpielereinstellungen\033[0m\n");
        //Spieler 1
        printf("Spieler 1: ");
        scanf("%s", &Spieler1.name);
        printf("Zeichen von %s : ", Spieler1.name);
        scanf(" %c", &Spieler1.zeichen);
        printf("Typ von %s (1 Computer, 0 Spieler) : ", Spieler1.name);
        scanf(" %d", &Spieler1.type);
        printf("Spieler 1 eingeloggt: \033[32m%s - %c - %d \033[0m\n", Spieler1.name, Spieler1.zeichen, Spieler1.type);
        printf("------------------\n");
        //Spieler 2
        printf("Spieler 2: ");
        scanf("%s", &Spieler2.name);
        while (strcmp(Spieler2.name, Spieler1.name) == 0) {
            printf("Bitte anderen Namen eingeben\n");
            scanf(" %s", &Spieler2.name);
        };
        printf("Zeichen von %s : ", Spieler2.name);
        scanf(" %c", &Spieler2.zeichen);
        while (Spieler2.zeichen == Spieler1.zeichen) {
            printf("Bitte anderes Zeichen eingeben\n");
            scanf(" %c", &Spieler2.zeichen);
        }
        printf("Typ von %s (1 Computer, 0 Spieler) : ", Spieler2.name);
        scanf(" %d", &Spieler2.type);
        printf("Spieler 1 eingeloggt: \033[32m%s - %c - %d\033[0m \n", Spieler2.name, Spieler2.zeichen, Spieler2.type);

        int gewinnerValue = 0;
        KOORDINATE Playfield[SPIELFELDGROESSE][SPIELFELDGROESSE];

        for (int spalte = 0; spalte < SPIELFELDGROESSE; spalte++) {
            for (int reihe = 0; reihe < SPIELFELDGROESSE; reihe++) {
                Playfield[reihe][spalte].value = CELLPLACEHOLDER;
            }
        }
        system("clear");
        int counter = 0;

        //Offline Turn-Loop
        while (gewinnerValue == 0) {

            printf("\033[31mAktueller Zug : %d\033[0m\n", counter++);

            drawTicTacToeField(Playfield);

            if (counter % 2 == 0) {
                doTurn(Spieler1, Playfield, 0, 0, 0);
            } else {
                doTurn(Spieler2, Playfield, 0, 0, 0);
            }

            gewinnerValue = testForWinner(Playfield);

            system("clear");
        }

        if (gewinnerValue == 5) {
            printf("Das Feld ist voll, Unentschieden\n");
            return 1;
        }

        SPIELER gewinner;

        if (counter % 2 == 0) {
            gewinner = Spieler2;
        } else {
            gewinner = Spieler1;
        }

        sendWinMessage(gewinnerValue, gewinner);

        return 1;
    }
}

void sendWinMessage(int winType, SPIELER gewinner){

    printf("\033[33m%s hat ",gewinner.name);

    switch(winType) {
        case 1: //Horizontal
            printf("Horizontal gewonnen ");
            break;
        case 2: //Vertikal
            printf("Vertikal gewonnen ");
            break;
        case 3: //Diagonal
            printf("Diagonal gewonnen ");
            break;
        case 4: //Antidiagonal
            printf("Antidiagonal gewonnen ");
            break;
        default:
            printf("Error  bei der Gewinnvaluation, bitte kontaktieren sie den Administrator");
    }
    printf("\033[0m");
}




