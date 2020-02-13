#include <stdio.h>
#include <stdlib.h>
#include "StructDefinitions.h"
#include "Feldausgabe.h"
#include "Logik.h"
#include <string.h>

int SPIELFELDGROESSE;

int main() {

    SPIELER Spieler1;
    SPIELER Spieler2;

    printf("\033[31mSpieleinstellungen\033[0m\n");
    printf("Wie groß soll das Spielfeld sein : \033[33m(3 - 10)\033[0m\n");
    scanf("%d", &SPIELFELDGROESSE);

    if(SPIELFELDGROESSE < 3){
        SPIELFELDGROESSE = 3;
    }
    if(SPIELFELDGROESSE > 10){
        SPIELFELDGROESSE = 10;
    }

    KOORDINATE Playfield[SPIELFELDGROESSE][SPIELFELDGROESSE];

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
    printf("Spieler 1 eingeloggt: \033[32m%s - %c - %d\033[0m \n", Spieler2.name, Spieler2.zeichen, Spieler2.type);

    int gewinnerValue = 0;

    for(int spalte = 0; spalte < SPIELFELDGROESSE; spalte++) {
        for (int reihe = 0; reihe < SPIELFELDGROESSE; reihe++) {
            Playfield[reihe][spalte].value = CELLPLACEHOLDER;
        }
    }
    system("clear");
    int counter = 0;
    while(gewinnerValue == 0){

        printf("\033[31mAktueller Zug : %d\033[0m\n", counter);

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

    if(gewinnerValue == 5){
        printf("Das Feld ist voll, Unentschieden\n");
        return 1;
    }

    drawTicTacToeField(Playfield);

    if(counter % 2 == 0){
        printf("\033[33m%s ist Sieger\033[0m\n",Spieler2.name);
    } else {
        printf("\033[33m%s ist Sieger\033[0m\n",Spieler1.name);
    }
    return 1;
}

