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
    printf("Typ von %s (1 Computer, 0 Spieler) : ", Spieler1.name);
    scanf(" %d", &Spieler1.type);
    printf("Spieler 1 eingeloggt: %s - %c - %d \n", Spieler1.name, Spieler1.zeichen, Spieler1.type);
    printf("------------------\n");
    printf("Spieler 2: ");
    scanf("%s", &Spieler2.name);
    printf("Zeichen von %s : ", Spieler2.name);
    scanf(" %c", &Spieler2.zeichen);
    printf("Typ von %s (1 Computer, 0 Spieler) : ", Spieler2.name);
    scanf(" %d", &Spieler2.type);
    printf("Spieler 1 eingeloggt: %s - %c - %d \n", Spieler2.name, Spieler2.zeichen, Spieler2.type);

    int gewinnerValue = 0;

    for(int i = 0; i < SPIELFELDGROESSE; i++) {
        for (int j = 0; j < SPIELFELDGROESSE; j++) {
            Playfield[i][j].value = ' ';
        }
    }
    int counter = 0;
    while(gewinnerValue == 0){


        drawTicTacToeField(Playfield);

        doTurn(SPIELER);
        KOORDINATE scanKoord;
        if(counter % 2 == 0){
            if (Spieler1.type == 0){
                printf(" %s ist am Zug, wo möchtest du etwas setzen ? (x , y)\n", Spieler1.name);
                scanf("%d %d", &scanKoord.x, &scanKoord.y);
            }
            else {
                //computereingabe
            }
            scanKoord.value = Spieler1.zeichen;
        }
        else {
            if (Spieler2.type ==0){
                printf(" %s ist am Zug, wo möchtest du etwas setzen ? (x , y)\n", Spieler2.name);
                scanf("%d %d", &scanKoord.x, &scanKoord.y);
            }
            else{
                //computereingabe
            }
            scanKoord.value = Spieler2.zeichen;
        }
        counter++;

        setMarkAtPosition(Playfield, scanKoord);

        gewinnerValue = testForWinner(Playfield);
    }
    drawTicTacToeField(Playfield);
    //ToDo: Ausgabe des Gewinners
}
