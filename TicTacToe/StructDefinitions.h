//
// Created by Felix on 22.01.20.
//

#ifndef TICTACTOE_STRUCTDEFINITIONS_H
#define TICTACTOE_STRUCTDEFINITIONS_H

#define SPIELFELDGROESSE 3

typedef struct {
    int x;
    int y;
    char value;
}KOORDINATE;

typedef struct {
    char zeichen;
    char name[10];
    int type;
}SPIELER;

#define FELD_SIZE 3;

#endif //TICTACTOE_STRUCTDEFINITIONS_H
