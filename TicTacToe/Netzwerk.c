
//
// Created by A002485 on 04.02.2020.
//

//Initialisiere Winsock ( Socket programming bei windows )
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <string.h>
#include <windows.h>
#include <tchar.h>
//#include <strsafe.h>

#define MAX_THREADS 3
#define BUF_SIZE 255


//für TCP hinzugefügt - was macht das??
//#include&lt;stdio.h&gt;
//#include&lt;winsock2.h&gt;

//#pragma comment(lib,"WS2_32")//Winsock Library, die für Funktionen der winsock2.h notwending ist.

char hosttyp = ' ';
char DataToMe[64] = "Moin";
char DataToHim[64] = "-";
char targetIP[256];
char OwnIP[256];
int Verbindung = 1;
char string_1[20];
char string_2[20];
SOCKET ClientSocket = INVALID_SOCKET;
int ReadMessage(int socket, char * DataToMe, int modus);
int SendMessageToClient(int socket, char *message, char *intarray);
int aktivListen = 0;
int messageStatus = 0;
int modus = 0;
int checkMessage = 0;
char *GetMessages(int a);





// IPv4 AF_INET sockets:

int GetOtherSocket() {
    return ClientSocket;
}

ChangeModus(int a) {

    modus = a;

}

DWORD WINAPI ThreadFunc(void* data) {
    // Do stuff.  This will be the first function called on the new thread.
    // When this function returns, the thread goes away.  See MSDN for more details.
    printf("thread meldet sich! \n");
    while(aktivListen == 1) {
        Sleep(500);
        ReadMessage(ClientSocket,DataToMe,modus);
        //printf("ich lese...\n");
    }


    // return 0; return löscht thread
}


int GetHosttype() {

    WSADATA wsa; // enthält Information für Socket implementation
    SOCKET sock;
    struct sockaddr_in server, client;
    char Ceingabe = 'n';
    WSACleanup();

    printf("Sind Sie Host oder Client? [H] [C]. \n");
    scanf(" %c", &hosttyp);
    printf("Willkommen %c \n",hosttyp);

    if(hosttyp == 'C') {

        do {
            printf("Mit wem wollen sie sich verbinden?\n");
            printf("Bitte geben sie die IP Adresse des Partners an. \n");
            printf("Format ist: XXX.XXX.XXX.XXX \n");
            scanf(" %s", &targetIP);
            printf("Ist %s richtig? ###[y] [n]### \n", targetIP);
            scanf(" %c", &Ceingabe);
        } while (Ceingabe == 'n');
    }

    if(hosttyp == 'H') {

        printf("\nInitialising Winsock...");  // Socket wird aufgebaut...

        if ( WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            printf("Failed. Error Code : %d", WSAGetLastError());
            return 1;
        } else {
            printf("socket retrieve success\n");
        }

        if((sock = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            printf("Konnte Socket nicht erstellen: : %d \n" , WSAGetLastError());
            return -1;
        } else {
            printf("Socket erstellt.\n");
            sock = socket(AF_INET, SOCK_STREAM, 0); // Unsicher, ob überhaupt benötigt
        }

        server.sin_addr.s_addr = htonl(INADDR_ANY); // INADDR_ANY Server-side
        server.sin_family = AF_INET;
        server.sin_port = htons(8080);

        if((bind(sock,(struct sockaddr*)&server, sizeof(server))) != 0) {
            printf("Socket konnte nicht gebunden werden \n");
        } else printf("Socket wurde an Server gebunden\n");

        printf("Server listening und verification wird initialisiert...\n");

        if((listen(sock,5)) != 0) {
            printf("Listening fehlgeschlagen\n");
        } else {
            printf("Server hoert dich und ist bereit!\n");
        }



        printf("Akzeptiere einkommende Anfragen von Partner...\n");

        while(ClientSocket == INVALID_SOCKET) {
            ClientSocket = INVALID_SOCKET;
            printf("Warte auf Client Anfrage... \n");
            ClientSocket = accept(sock, NULL, NULL);
            if (ClientSocket == INVALID_SOCKET) {
                printf("accept failed with error %d\n", WSAGetLastError());

            }
        }

        if(ClientSocket < 0 ){
            printf("Server akzeptiert Client nicht\n");
        } else {
            printf ("Server akzeptiert Client\n");
        }

        return 0;

    } else { // Client


        printf("\nInitialising Winsock..."); // Socket wird aufgebaut...

        if ( WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            printf("Failed. Error Code : %d",WSAGetLastError());
            return 1;
        } else {
            printf("socket retrieve success\n");
        }

        if((ClientSocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            printf("Konnte Socket nicht erstellen: : %d \n" , WSAGetLastError());
            return -1;
        } else { printf("Socket erstellt.\n"); }

        server.sin_addr.s_addr = inet_addr(&targetIP[0]); //127.0.0.1 wäre local
        server.sin_family = AF_INET;
        server.sin_port = htons(8080);
        printf("Given IP: %s \n",&targetIP[0]);

        printf("Trying to connect...");

        // connect the client socket to server socket
        if (connect(ClientSocket, (struct sockaddr*)&server, sizeof(server)) != 0) {
            printf("connection with the server failed...\n");
            exit(0);
        }
        else
            printf("VERBUNDEN\n");

        return 1;
    }



}

int ThreadErstellen(int erkennung) {

    HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
    if (thread) {
        // Optionally do stuff, such as wait on the thread.
        printf("Thread wird gestartet...\n");
        Sleep(500);
        printf("Thread ist erfolgreich gestartet.\n");
        CloseHandle(thread);
    }
    return 1;

}

int SendenBrauchbar(char *Datenpaket, int string1length, int string2length) {

    // Empfange array, nehme das außeinander mit den jeweiligen größen, habe arrays hier initialisiert, die einfach nach dem 6. char \n setzen und beim anderen
    /*
     * Empfange array, size 1. block, size 2. block
     * nehme array von stelle 0 bis size 1 und kopiere das in ein anderes array, das setzt bei size1+1 ein \0
     *
     */
   // printf(" %s",Datenpaket);
    strcpy(string_1,Datenpaket); // ich nehme mein string_1 array und kopiere den inhalt da rein
    string_1[string1length] = '\0'; // nach dem string1 Länge des 1. Strings +1 und \0 zum abschließen
    strcpy(string_2,Datenpaket);
    string_2[0] = string_2[string1length];
    string_2[string2length] = '\0';                 // ist jetzt statisch festgelegt - hab kein kopf dafür

    printf("String1: %s \n",string_1);
    printf("String2: %s \n",string_2);

    // Schicke erst das array mit den Integern,
    // Schicke dann die Strings

   /* char string_1[6] = Datenpaket[0];
    printf("%s \n",string_1);
    char string_2[1] = Datenpaket[string1];
    printf("%s \n",string_2); */
    //scanf(" %s",&DataToHim);

    char stringlength[] = { string1length, string2length};



    SendMessageToClient(GetOtherSocket(),Datenpaket,stringlength); // Sendet zum Clienten oder Server

    Sleep(500);
}

int SendenChat() {

    DataToHim[0] = '\0';
    scanf(" %s",&DataToHim);

    //SendMessageToClient(GetOtherSocket(),DataToHim); // Sendet zum Clienten oder Server

    Sleep(500);

}

int SendMessageToClient(int socket, char *message, char *intarray){

    int n = 0; // Debug
    n = send(socket,message,65,0); //Wieso übergebe ich hier ein CHAR
    Sleep(1000);
    n = send(socket,intarray,2,0); //Wieso übergebe ich hier ein CHAR
    if(n==SOCKET_ERROR) {
        printf("Send failed %d\n", WSAGetLastError());
    }
    if(n<0) {
        printf("Error sending to Server");
    } else if ( n == 0 ) {printf("Server closed the Connection.\n");}

    printf("message: %s \n", message);
    //return n;


}

int ReadMessage(int socket, char * DataToMe, int modus) {
    int a,b, recv_size;
    char tempstring[60];

    recv_size = recv(socket, DataToMe,65,0); // 1. Auswertung sind immer die beiden Integer
    if(recv_size > 0 ) {
        if(DataToMe == "bbb") {
            //erneute Eingabe von Name,Zeichen
        }
        if(DataToMe == "ccc") {
            // Geb Random Zahl vom Server
        }
        if(DataToMe == "ddd") {
            //Spielfeldgröße als paket zu geschickt bekommen
        }
        if(DataToMe == "eee") {
            // Dein Gegner hat feld xy belegt (aktualisiert auch auf deiner Seite)
        }
        if(messageStatus == 0) {
            printf("habe empfangen - ");
            //DataToMe[0] = '/0';
            printf("message: %s \n", DataToMe);
            strcpy(tempstring,DataToMe);
            messageStatus = 1;
            printf("Warte jetzt auf den String...\n");
        }else if(messageStatus == 1) {
            printf("String bekommen!\n");

            a = (int) DataToMe[0];
            b = (int) DataToMe[1];

            printf("a: %d, b: %d \n",a,b);

            strcpy(string_1,tempstring); // ich nehme mein string_1 array und kopiere den inhalt da rein
            string_1[a] = '\0'; // nach dem string1 Länge des 1. Strings +1 und \0 zum abschließen
            strcpy(string_2,tempstring);
            string_2[0] = string_2[a];
            string_2[b] = '\0';                 // ist jetzt statisch festgelegt - hab kein kopf dafür

            printf("HABE BEKOMMEN : String1: %s \n",string_1);
            printf("HABE BEKOMMEN : String2: %s \n",string_2);
            DataToMe[0] = '/0';
            messageStatus = 0;

            checkMessage = 1;

        }
    }

    if(modus == 1) {



    }

    DataToMe[0] = '/0';
    memset(DataToMe,0,strlen(DataToMe));



}

char *GetMessages(int a) {



    if(a == 1) {

        char* arr = malloc(100);
        strcpy(arr,string_1);
        return arr;

    }

    if(a == 2) {

        char* arr = malloc(100);
        strcpy(arr,string_2);
        return arr;

    }
}






