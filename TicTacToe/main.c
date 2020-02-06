#include <stdio.h>
#include "StructDefinitions.h"
#include "Feldausgabe.h"
#include "Logik.h"




int main() {

    KOORDINATE Playfield[SPIELFELDGROESSE][SPIELFELDGROESSE];
    SPIELER Spieler1;
    SPIELER Spieler2;

    printf("Spieler 1: ");
    scanf("%s", &Spieler1.name);
    printf("Zeichen von %s : ", Spieler1.name);
    scanf(" %c", &Spieler1.zeichen);
    printf("Spieler 1 eingeloggt: %s - %c \n", Spieler1.name, Spieler1.zeichen);
    printf("------------------\n");
    printf("Spieler 2: ");
    scanf("%s", &Spieler2.name);
    printf("Zeichen von %s : ", Spieler2.name);
    scanf(" %c", &Spieler2.zeichen);
    printf("Spieler 1 eingeloggt: %s - %c \n", Spieler2.name, Spieler2.zeichen);

    int gewinnerValue = 0;

    for(int i = 0; i < SPIELFELDGROESSE; i++) {
        for (int j = 0; j < SPIELFELDGROESSE; j++) {
            Playfield[i][j].value = ' ';
        }
    }
    int counter = 0;
    while(gewinnerValue == 0){


        drawTicTacToeField(Playfield);

        KOORDINATE scanKoord;
        if(counter % 2 == 0){
            printf("%s ist am Zug, wo möchtest du etwas setzen ? (x , y)\n", Spieler1.name);
            scanKoord.value = Spieler1.zeichen;
        }
        else {
            printf("%s ist am Zug, wo möchtest du etwas setzen ? (x , y)\n", Spieler2.name);
            scanKoord.value = Spieler2.zeichen;
        }
        counter++;
        scanf("%d %d", &scanKoord.x, &scanKoord.y);

        setMarkAtPosition(Playfield, scanKoord);

        gewinnerValue = testForWinner(Playfield);
    }
    drawTicTacToeField(Playfield);

    if(gewinnerValue == 2){
        printf("Das Feld ist voll, Unentschieden");
        return 1;
    }

    if(counter % 2 == 0){
        printf("%s ist Sieger",Spieler1.name);
    } else {
        printf("%s ist Sieger",Spieler2.name);
    }
    return 1;
}
