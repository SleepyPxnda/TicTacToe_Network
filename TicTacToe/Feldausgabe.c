//
// Created by Felix on 24.01.20.
//
#include "StructDefinitions.h"
#include <stdio.h>

extern int SPIELFELDGROESSE;

void drawTicTacToeField(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE]){
    for(int spalte = 0;spalte  < SPIELFELDGROESSE; spalte++){
        printf("| ");
        for(int reihe = 0; reihe < SPIELFELDGROESSE; reihe++){
            printf("%c",Feld[spalte][reihe].value);
            printf(" | ");
        }

        printf("\n");
        for(int i = 0; i <= (SPIELFELDGROESSE * 2); i++){
            printf("- ");

        }
        printf("\n");
    }
}