//
// Created by Felix on 24.01.20.
//
#include "StructDefinitions.h"
#include <stdio.h>

void drawTicTacToeField(KOORDINATE Feld[][SPIELFELDGROESSE]){
    for(int i = 0; i < SPIELFELDGROESSE; i++){
        printf("| ");
        for(int j = 0; j < SPIELFELDGROESSE; j++){
            printf("%c",Feld[j][i].value);
            printf(" | ");
        }
        printf("\n- - - - - - -\n");
    }
}