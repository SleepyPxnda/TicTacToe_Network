//
// Created by Felix on 24.01.20.
//

#ifndef TICTACTOE_LOGIK_H
#define TICTACTOE_LOGIK_H

#include "StructDefinitions.h"
extern int SPIELFELDGROESSE;

int testForWinner(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE]);
void setMarkAtPosition(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE], KOORDINATE platz);
int doTurn(SPIELER player,KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE],int mode);
KOORDINATE getCoordinateForComputer(KOORDINATE Feld[SPIELFELDGROESSE][SPIELFELDGROESSE]);
int SendenBrauchbar(char *Datenpaket, int string1, int string2);
int GetTempstring(char x);

#endif //TICTACTOE_LOGIK_H
