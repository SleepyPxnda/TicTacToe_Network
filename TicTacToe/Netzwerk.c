
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
#include <pthread.h>
#include <unistd.h>



//für TCP hinzugefügt - was macht das??
//#include&lt;stdio.h&gt;
//#include&lt;winsock2.h&gt;

//#pragma comment(lib,"WS2_32")//Winsock Library, die für Funktionen der winsock2.h notwending ist.

char hosttyp = ' ';
int ippart1,ippart2,ippart3,ippart4;
// Network Test
//char *Pmessage = 'a';
int listenfd = 0;
//struct sockadrr_in serv_addr;
char buffer[1024];
char buffer_reply[2000];
char targetIP[256];
char OwnIP[256];
int numvr=0;

// IPv4 AF_INET sockets:

int SendMessageToClient(int socketfd, char *message){

    // Send Data to test client in Byte?
    int n = 0; // Debug
    n = send(socketfd,message,(strlen(message)+1),0); //Wieso übergebe ich hier ein CHAR
    if(n<0) {
        printf("Error sending to Server");
    } else if ( n == 0 ) {printf("Server closed the Connection.\n");}

    //printf("message: %c \n", message);
    return n;


}

int ReadMessage(int socket, char * buffer) {
    int i, recv_size;

    // recv wartet bis andere Client daten zurücksendet
    printf("t");
    if ((recv_size = recv(socket , buffer , 2000 , 0)) == SOCKET_ERROR) {
        puts("recv failed");
    } else {puts("recv success");}
    puts(buffer);

}



int GetHosttype() {

    /* TODO
     * 1. Abfrage ob Host oder Client
     * 2. Winsock initialisierung (Nur auf WINDOWS GERÄTEN)
     */


    WSADATA wsa; // enthält Information für Socket implementation
    SOCKET sock;
    struct sockaddr_in server, client;
    char Ceingabe = 'n';
    WSACleanup();

    printf("Sind Sie Host oder Client? [H] [C]. \n");
    scanf(" %c", &hosttyp);
    printf("Willkommen %c \n",hosttyp);
    /* nun ersetzt durch INADDR_ANY
    do {
        printf("Bitte geben sie Ihre IP Adresse an. \n");
        printf("Format ist: XXX.XXX.XXX.XXX \n");
        scanf(" %s", &OwnIP);
        printf("Ist %s richtig? ###[y] [n]### \n", OwnIP);
        scanf(" %c", &Ceingabe);
    }while(Ceingabe == 'n');
    */
    do {
        printf("Mit wem wollen sie sich verbinden?\n");
        printf("Bitte geben sie die IP Adresse des Partners an. \n");
        printf("Format ist: XXX.XXX.XXX.XXX \n");
        scanf(" %s", &targetIP);
        printf("Ist %s richtig? ###[y] [n]### \n", targetIP);
        scanf(" %c", &Ceingabe);
        } while(Ceingabe =='n');


    // zum Testen, zwei Sockel anlegen und entweder als H oder C

    if(hosttyp == 'H') {

        //Felix IP ist 192.168.137.23
        /*
         * socket bind
         * listen
         * accept
         * recv / read
         * write / send
         * recv / read
         * close
         */

        int len,connfd; // Client nummer?


        printf("\nInitialising Winsock...");
        // Socket wird aufgebaut...
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


        server.sin_addr.s_addr = htonl(INADDR_ANY); //74.125.235.20 Google server
        server.sin_family = AF_INET;
        server.sin_port = htons(8080);
        printf("Given IP: %s \n",&OwnIP[0]);


        if((bind(sock,(struct sockaddr*)&server, sizeof(server))) != 0) {
            printf("Socket konnte nicht gebunden werden \n");
        } else printf("Socket wurde an Server gebunden\n");

        printf("Server listening und verification wird initialisiert...\n");

        if((listen(sock,50)) != 0) {
            printf("Listening fehlgeschlagen\n");
        } else {
            printf("Server hoert dich und ist bereit!\n");
            len = sizeof(client);
        }





        SOCKET ClientSocket;
        ClientSocket = INVALID_SOCKET;

        while(ClientSocket == INVALID_SOCKET) {
            ClientSocket = INVALID_SOCKET;
            printf("test");
            ClientSocket = accept(sock, NULL, NULL);
            if (ClientSocket == INVALID_SOCKET) {
                printf("accept failed with error %d\n", WSAGetLastError());
                //closesocket(sock);
                //WSACleanup;

            }
        }




        printf("Akzeptiere einkommende Anfragen von Partner...\n");


         //connfd = accept(sock, (struct sockaddr*)&cli, &len);
                if(connfd < 0 ){
                    printf("Server akzeptiert Client nicht\n");
                } else {
                    printf ("Server akzeptiert Client\n");
                }

                printf("Server ist fertig");



    } else {
        /*
         * socket server bind
         * connect
         * write / send
         * recv / read
         * close
         */

        printf("\nInitialising Winsock...");
        // Socket wird aufgebaut...
        if ( WSAStartup(MAKEWORD(2,2),&wsa) != 0)
        {
            printf("Failed. Error Code : %d",WSAGetLastError());
            return 1;
        } else {
            printf("socket retrieve success\n");
        }

        if((sock = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
        {
            printf("Konnte Socket nicht erstellen: : %d \n" , WSAGetLastError());
            return -1;
        } else { printf("Socket erstellt.\n"); }

        //weise IP & Port zu
        //Dennis Server IP: 141.31.83.34
        server.sin_addr.s_addr = inet_addr(&targetIP[0]); //127.0.0.1 wäre local
        server.sin_family = AF_INET;
        server.sin_port = htons(8080);
        printf("Given IP: %s \n",&targetIP[0]);

        printf("Trying to connect...");

        // connect the client socket to server socket
        if (connect(sock, (struct sockaddr*)&server, sizeof(server)) != 0) {
            printf("connection with the server failed...\n");
            exit(0);
        }
        else
            printf("connected to the server..\n");

        //ConnectToServer();
    }

    //closesocket(sock);

    /*
   * Creating TCP socket
   */

    //Beispiel auf google server connecten
    //server addr. ist der client/Host
    //IpAdresseFormatieren();
    //server.sin_addr.s_addr = inet_addr(targetIP); //QUOT stand für "", da man die "" nicht hinzufügen kann.

/*
    printf("\nInitialising Winsock...");
    // Socket wird aufgebaut...
    if ( WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    } else {
        printf("socket retrieve success\n");
    }

    if((sock = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d \n" , WSAGetLastError());
        return -1;
    } else { printf("Socket created.\n"); }

    server.sin_addr.s_addr = inet_addr(&targetIP[0]); //74.125.235.20 Google server
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    printf("Given IP: %s \n",&targetIP[0]);

    */




/*
//listenfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET IPv4, SOCK_STREAM(TCP), 0 - Protocol
    long rc;
    // Connect to a remote server
    if(rc = connect(sock, (struct sockadrr*)&server, sizeof(server)), 0)
    {
        puts("connect error");
        return 1;
    }
    printf("rc: %d \n",rc);
    if(rc==SOCKET_ERROR) // SOCKET_ERROR = -1; SUCCEED = 0;
    {
        printf("Fehler: connect gescheitert, fehler code: %d\n",WSAGetLastError());
        if(WSAGetLastError() == 10060) {
            printf("Connection Timeout\n");
        }
        if(WSAGetLastError() == 10061) {
            printf("Connection refused - Firewall?\n");
        }
        printf("%s",WSAGetLastError());
        return 1;
    }

    char server_reply[2000], server_send[1000];
    int recv_size;

    server_send[0] = "wrwarwrw";
    rc = send(sock , server_send, (int)strlen(server_send),0);
    printf("rc: %d",rc);
    printf ("WSAError: %s",WSAGetLastError());

    if((recv_size = recv(sock , server_reply , 2000 , 0)) == SOCKET_ERROR)
    {
        puts("recv failed \n");
    }

    puts("Server reply: %s",server_reply);




    //Receive a reply from the server



    //rc = send(sock,)

    printf("Verbunden mit IP: %s \n",targetIP[0]);
    /*
    closesocket(sock);
    WSACleanup();
    */
    /*
    printf("Bitte was zum Uebertragen eingeben: ");
    scanf(" %s",&buffer); // Message die übersendet wird.
    printf("Message ist: %s \n", buffer);
    int debugSend = SendMessageToClient(sock, buffer);
    printf("N: %d \n", debugSend);

   // int debugRead = ReadMessage(sock, buffer_reply);

     */







}

void CreateTCPSocket() {








}







