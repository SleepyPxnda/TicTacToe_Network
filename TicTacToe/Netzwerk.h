//
// Created by Link on 12.02.2020.
//

#ifndef TICTACTOE_NETZWERK_H
#define TICTACTOE_NETZWERK_H


int GetHosttype();
int ThreadErstellen();
int SendenBrauchbar(char *Datenpaket, int string1, int string2);




int checkMessage;
char string_1[20];
char string_2[20];
int aktivListen;

#endif //TICTACTOE_NETZWERK_H
