
//
// Created by A002485 on 04.02.2020.
//

#include <stdio.h>

char hosttyp = ' ';
int ippart1,ippart2,ippart3,ippart4;

void GetHosttype() {

    printf("Sind Sie Host oder Client? [H] [C] \n .");
    scanf(" %c", &hosttyp);
    printf(" Willkommen %c, Bitte geben sie Ihre IP Adresse an. \n",hosttyp);
    printf("Format ist: XXX.XXX.XXX.XXX \n");
    scanf(" %d.%d.%d.%d", &ippart1, &ippart2, &ippart3, &ippart4);
    printf("Ist %d.%d.%d.%d richtig? \n",ippart1,ippart2,ippart3,ippart4);

}




