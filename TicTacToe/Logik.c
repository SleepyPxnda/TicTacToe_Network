//
// Created by Felix on 22.01.20.
//

#include "StructDefinitions.h"
#include "ErrorMessages.h"
#include <stdio.h>

void setMarkAtPosition(KOORDINATE Feld[][SPIELFELDGROESSE], KOORDINATE platz){
    int x = platz.x - 1; // - 1 um eingabe an Array anzupassen, sont würde Eingabe 1,2 Feld 0,1 belegen -> Benutzerfreundlicher
    int y = platz.y - 1;

    if((x >= 0 && x < SPIELFELDGROESSE) && (y >= 0 && y < SPIELFELDGROESSE)) {
        if (Feld[x][y].value == ' ') {
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
            if(Feld[reihe][spalte].value != ' ') {
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
                if(Feld[reihe][spalte].value != ' ') {
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
        if(Feld[diagonal][diagonal].value != ' '){
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
            if(Feld[reihe][spalte].value != ' '){
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
            if(Feld[spalte][reihe].value != ' '){
                maxCells += 1;
            }
        }
    }
    if(maxCells == SPIELFELDGROESSE * SPIELFELDGROESSE){
        return 2;
    }


    return 0;
}