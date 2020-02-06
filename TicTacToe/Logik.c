//
// Created by Felix on 22.01.20.
//

#include "StructDefinitions.h"
#include "ErrorMessages.h"
#include "ComputerLogic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void setMarkAtPosition(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE], KOORDINATE platz){
    int x = platz.x - 1; // - 1 um eingabe an Array anzupassen, sont würde Eingabe 1,2 Feld 0,1 belegen -> Benutzerfreundlicher
    int y = platz.y - 1;

    if((x >= 0 && x < SPIELFELDGROESSE) && (y >= 0 && y < SPIELFELDGROESSE)) {
        if (Feld[x][y].value == CELLPLACEHOLDER) {
            Feld[x][y].value = platz.value;
        }
    } else {
        printf(NUMBEROUTOFBOUNDS);
    }
}

int testForWinner(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE]) {

    //Horizontal Check for Win
    for(int reihe = 0; reihe < SPIELFELDGROESSE; reihe++){
        int rowCellEquals = 0;
        for(int spalte = 0; spalte < SPIELFELDGROESSE; spalte++){
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
            return 1;
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
        return 1;
    }

    int rowCellsEquals = 0;
    for(int spalte = SPIELFELDGROESSE - 1; spalte >= 0; spalte--){
        for(int reihe = 0; reihe < SPIELFELDGROESSE; reihe++){
            if(Feld[reihe][spalte].value != CELLPLACEHOLDER){
                if(Feld[reihe][spalte].value == Feld[reihe + 1][spalte - 1].value){
                    rowCellsEquals += 1;
                }
            }
        }
    }
    if(rowCellsEquals == SPIELFELDGROESSE - 1){
        return 1;
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
        return 2;
    }


    return 0;
}


void doTurn(SPIELER player, KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE]){
    KOORDINATE scanKoord;

    if (player.type == 0){
        printf(" %s ist am Zug, wo möchtest du etwas setzen ? (x , y)\n", player.name);
        scanf("%d %d", &scanKoord.x, &scanKoord.y);
    } else
        if(player.type == 1){
        scanKoord = getCoordinateForComputer(Feld);

        printf("Der Computer %s hat ein Zeichen an %d , %d gesetzt\n",player.name, scanKoord.x, scanKoord.y);
    }

    scanKoord.value = player.zeichen;

    setMarkAtPosition(Feld,scanKoord);
}



