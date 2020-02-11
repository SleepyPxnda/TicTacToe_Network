//
// Created by Felix on 06.02.20.
//

#include <stdlib.h>
#include <time.h>
#include "ComputerLogic.h"
#include "StructDefinitions.h"

extern int SPIELFELDGROESSE;

KOORDINATE getCoordinateForComputer(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE]) {

    KOORDINATE computerKoord;
    computerKoord= getRandomPlace(Feld);

    computerKoord.x += 1;
    computerKoord.y += 1;

    return computerKoord;
}
/*
KOORDINATE getFirstFreePlace(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE]){
    KOORDINATE returnCoord;
    for(int spalte = 0; spalte < SPIELFELDGROESSE; spalte++){
        for(int reihe = 0; reihe < SPIELFELDGROESSE; reihe++){
            if(Feld[reihe][spalte].value == CELLPLACEHOLDER){
                returnCoord.x = reihe;
                returnCoord.y = spalte;
                return returnCoord;
            }
        }
    }
}
 */
KOORDINATE getRandomPlace(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE]){
    srand(time(0));
    KOORDINATE returnCoord;
    int randx,randy;
    do {
        randx = rand() % SPIELFELDGROESSE;
        randy = rand() % SPIELFELDGROESSE;
    }while(Feld[randx][randy].value != CELLPLACEHOLDER);

    returnCoord.x = randx;
    returnCoord.y = randy;

    return returnCoord;


}