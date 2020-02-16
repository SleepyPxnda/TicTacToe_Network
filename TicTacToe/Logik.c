//
// Created by Felix on 22.01.20.
//

#include "StructDefinitions.h"
#include "ComputerLogic.h"
#include "Logik.h"

#
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

extern int SPIELFELDGROESSE;

int setMarkAtPosition(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE], KOORDINATE platz){
    int x = platz.x - 1; // - 1 um eingabe an Array anzupassen, sonst würde Eingabe 1,2 Feld 0,1 belegen -> Benutzerfreundlicher
    int y = platz.y - 1;

    if((x >= 0 && x < SPIELFELDGROESSE) && (y >= 0 && y < SPIELFELDGROESSE)) {

        if (Feld[x][y].value == CELLPLACEHOLDER) {
            Feld[x][y].value = platz.value;
        }else
        {
            return 0;
        }
    } else {
        printf("Die Zahl ist zu groß/klein");
    }
    return 1;
}


int testForWinner(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE]) {


    //Horizontal Check for Win
    for(int reihe = 0; reihe < SPIELFELDGROESSE; reihe++){
        int rowCellEquals = 0;
        for(int spalte = 0; spalte < SPIELFELDGROESSE - 1; spalte++){ //Keine Ahnung wieso, aber sonst klappt der Hori Wincheck nicht
            if(Feld[reihe][spalte].value != CELLPLACEHOLDER) {
                if (Feld[reihe][spalte].value == Feld[reihe][spalte + 1].value) {
                    rowCellEquals += 1;
                }
            }
        }
        if(rowCellEquals == SPIELFELDGROESSE - 1){

            return 1;
        }
    }

    //Vertical Check for Win
    for(int spalte = 0; spalte < SPIELFELDGROESSE; spalte++){
        int rowCellEquals = 0;
        for(int reihe = 0; reihe < SPIELFELDGROESSE ; reihe++){
                if(Feld[reihe][spalte].value != CELLPLACEHOLDER) {
                    if (Feld[reihe][spalte].value == Feld[reihe + 1][spalte].value) {
                        rowCellEquals += 1;
                    }
                }
        }
        if(rowCellEquals == SPIELFELDGROESSE - 1){
            return 2;
        }
    }

    //Diagonal Check for Win
    int rowCellsEqualsUp = 0;
    for(int diagonal = 0; diagonal < SPIELFELDGROESSE; diagonal++){
        if(Feld[diagonal][diagonal].value != CELLPLACEHOLDER){
            if(Feld[diagonal][diagonal].value == Feld[diagonal + 1][diagonal + 1].value){
                rowCellsEqualsUp +=1;
            }
        }
    }
    if(rowCellsEqualsUp == SPIELFELDGROESSE - 1){
        return 3;
    }

    //Anti Diagonal Check for Win
    int rowCellsEqualsDown = 0;
    int diagonalreihe = (SPIELFELDGROESSE - 1);
    int diagonalspalte = 0;

    for(int diagonal = 0; diagonal < SPIELFELDGROESSE; diagonal++){
        if(Feld[diagonalreihe][diagonalspalte].value != CELLPLACEHOLDER){
            if(Feld[diagonalreihe][diagonalspalte].value == Feld[diagonalreihe - 1][diagonalspalte + 1].value){
                rowCellsEqualsDown += 1;
            }
        }
        diagonalreihe--;
        diagonalspalte++;
    }
    if(rowCellsEqualsDown == SPIELFELDGROESSE - 1){   // Abfrage für Spieler
        return 4;
    }
    if(rowCellsEqualsDown == SPIELFELDGROESSE){       // Abfrage für Computer, weil andere Koordinateneinheit FIX?
        return 4;
    }

    int maxCells = 0;
    for(int spalte = 0; spalte < SPIELFELDGROESSE; spalte++){
        for(int reihe = 0; reihe < SPIELFELDGROESSE; reihe++){
            if(Feld[spalte][reihe].value != CELLPLACEHOLDER){
                maxCells += 1;
            }
        }
    }
    if(maxCells == SPIELFELDGROESSE * SPIELFELDGROESSE){
        return 5;
    }

    return 0;
}


int doTurn(SPIELER player, KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE],int mode,int x,int y){
    KOORDINATE scanKoord;

    if (player.type == 0 && mode == 0){
        printf(" %s ist am Zug, wo möchtest du etwas setzen ? (x,y)\n", player.name);
        scanf(" %d,%d", &scanKoord.x, &scanKoord.y);


    } else if(player.type == 1){
            sleep(1);
        scanKoord = getCoordinateForComputer(Feld);
        printf("Der Computer %s hat ein Zeichen an %d , %d gesetzt\n",player.name, scanKoord.x, scanKoord.y);
    } else if (player.type == 0 && mode == 1){

        scanKoord.x = x;
        scanKoord.y = y;

        scanKoord.value = player.zeichen;

        if(setMarkAtPosition(Feld,scanKoord) == 0) {
            printf("Dieses Feld ist bereits belegt, bitte gebe 2 neue Koordinaten ein\n");
            return -1;
        } else {return 0;}
    }

    scanKoord.value = player.zeichen;

    while(setMarkAtPosition(Feld,scanKoord) == 0 && mode == 0){
        printf("Dieses Feld ist bereits belegt, bitte gebe 2 neue Koordinaten ein\n");
        scanf(" %d,%d", &scanKoord.x, &scanKoord.y);

    }

}




