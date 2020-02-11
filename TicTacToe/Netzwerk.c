
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
#include <strsafe.h>

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
SOCKET ClientSocket = INVALID_SOCKET;


// IPv4 AF_INET sockets:

int GetOtherSocket() {
    return ClientSocket;
}

int SendMessageToClient(int socket, char *message){

    int n = 0; // Debug
    n = send(socket,message,65,0); //Wieso übergebe ich hier ein CHAR
    if(n==SOCKET_ERROR) {
        printf("Send failed %d\n", WSAGetLastError());
    }
    if(n<0) {
        printf("Error sending to Server");
    } else if ( n == 0 ) {printf("Server closed the Connection.\n");}

    printf("message: %s \n", message);
    //return n;


}

int ReadMessage(int socket, char * DataToMe) {
    int i, recv_size;

    recv_size = recv(socket, DataToMe,65,0);
    if(recv_size > 0 ) {
        printf("habe empfangen - ");
        printf("message: %s \n", DataToMe);
    }
}

DWORD WINAPI ThreadFunc(void* data) {
    // Do stuff.  This will be the first function called on the new thread.
    // When this function returns, the thread goes away.  See MSDN for more details.
    printf("thread meldet sich! \n");
    while(Verbindung == 1) {
        Sleep(500);
        ReadMessage(ClientSocket,DataToMe);
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

    do {
        printf("Mit wem wollen sie sich verbinden?\n");
        printf("Bitte geben sie die IP Adresse des Partners an. \n");
        printf("Format ist: XXX.XXX.XXX.XXX \n");
        scanf(" %s", &targetIP);
        printf("Ist %s richtig? ###[y] [n]### \n", targetIP);
        scanf(" %c", &Ceingabe);
        } while(Ceingabe =='n');

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


       // SendMessageToClient(ClientSocket,DataToHim);




    } else{


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
    }

    HANDLE thread = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
    if (thread) {
        // Optionally do stuff, such as wait on the thread.
        printf("Thread wird gestartet...\n");
        Sleep(2000);
        printf("Thread ist erfolgreich gestartet.\n");
        CloseHandle(thread);
    }

    while(1) {
        DataToHim[0] = '\0';
        scanf(" %s",&DataToHim);

        SendMessageToClient(GetOtherSocket(),DataToHim);

        Sleep(500);
    }

}







