# TicTacToe_Network
## Projekt nur über Windows Spielbar

- [Entwicklerdokumentation](#entwicklerdokumentation)
  * [Vorraussetzungen fuer Multiplayer](#vorraussetzungen-fuer-multiplayer)
  * [Spielablauf](#spielablauf)
  * [Gewinntester](#gewinntester)
  * [Computerspieler](#computerspieler)
  * [Netzwerk](#Netzwerk)
  * [Spielablauf Netzwerk](#Spielablauf-Netzwerk)
  * [Paketvermittlung](#Paketvermittlung)
- [Anwenderdokumentation](#anwenderdokumentation)
  * [TicTacToe starten](#tictactoe-starten)
  * [Eingabe der Einstellungen](#eingabe-der-einstellungen)
  * [Multiplayer](#multiplayer)
  * [Singleplayer](#singleplayer)
  * [Spieleinstellungen](#spieleinstellungen)
  * [Spielablauf](#spielablauf-1)


# Entwicklerdokumentation

## Vorraussetzungen fuer Multiplayer
- Serverseite darf keine Firewall anhaben
oder
- Entsprechende TCP Packete müssen Serverseitig erlaubt werden

## Spielablauf
Das Spiel beginnt mit diversen Einstellungsdialogen, wir fragen hier die Spielfeldgröße ab. Basierend auf dieser Eingabe wird darauf das Spielfeld generiert. Das Spielfeld repräsentieren wir in unserem Fall mit einem 2D-Array, welches aus Koordinaten structs besteht. Diese Koordinatenstructs enthalten einen x-Wert, einen y-Wert und das Zeichen, welches bei einem Zug darin gespeichert wird, um das Zeichen zu erleichtern. Danach fragen wir die Daten der beiden Spieler ab. Diese speichern wir in einem struct namens Spieler, welches aus den Namen und das Zeichen, des Spielers enthält, sowie die Information ob dieser Spieler ein Computer oder ein realer Spieler ist. Wurden diese Informationen nun eingegeben, leert sich die Konsole der Übersichtlichkeit wegen, und das leere Spielfeld wird gezeichnet. Dies haben wir durch eine einfache Funktion „drawTicTacToeField“ realisiert, welche durch unser Array itariert und jedes Koordinatenzeichen aufmalt. Nun beginnt der Spielablauf. Die Spieler werden nacheinander durch Konsolenaufforderungen dazu bewegt Koordinaten im Format „(reihe , spalte)“ einzugeben. Dies geschieht solange bis einer der Spieler ein, nach den Regeln von TicTacToe, Gewinn erzielt hat. Da wir mit einer unbestimmt Spielfeldgröße arbeiten, haben wir den Spielablauf in eine While-Schleife gebaut. Somit kann das Spiel beliebig groß sein, und wir beenden das Spiel nie vorzeitig. Hat ein Spieler nun gewonnen, wird dies über eine Nachricht im Terminal ausgegeben. Zudem wird das Spielfeld basierend auf dem letzten Zug angezeigt.

## Gewinntester
In unserer Gewinntester Methode wird nach jedem Zug das Spielfeld nach einem Sieger durchsucht. Dies haben wir mit verschieden geschachtelten for-schleifen zusammengebaut. Wir definierten am Anfang jeder for-schleife immer einer Variablen welche den aktuellen Stand des Feldes im Hinblick auf die Annäherung an den Gewinn repräsentiert, sobald also 2 Felder hintereinander gleich sind wird dieser variable hochgezählt. Am Ende vergleichen wir diese Variable dann nur mit der passenden Größe des Spielfeldes, womit wir dann einen Spielgrößenunabhängigen Gewinntester erhalten.
Zudem ist in dieser Funktion eine Schleife welche den Fall des Unentschiedens abdeckt.
Auch wird jeder „Art“ des Gewinns mit verschiedenen Returns bezeichnet, sodass eine Unterscheidung möglich ist, und wir somit auch die „Art“ des Gewinnes am Ende anzeigen können.

## Computerspieler
Unser Computerspieler hat mehr oder weniger nur eine Funktionalität, er sucht sich aus allen freien Feldern eins zufällig raus und setzt an diese Stelle sein Zeichen, welches in der Spielerauswahl festgelegt wurde

## Netzwerk
Man wird gefragt, ob man entweder Client oder Host ist. Wenn Client, dann die IP Adresse im Format XXX.XXX.XXX.XXX eingeben und bestätigen. Nach der Bestätigung, wird Winsock initialisiert, welcher Notwendig ist für Netzwerkkonfigurationen. Mit WSAStartup wird dies umgesetzt und WSA (bei keinen Fehlern) gestartet. ein Socket (der für die Verbindung benötigt wird) wird erstellt, mit eigener AF_INET (IPv4 Adresse), SOCK_STREAM (TCP) und Protokoll: 0. In ein gegebener vordefinierter Strukt von winsock2.h werden die Daten von dem zu erreichenden Server eingepflegt. Standart Port hier für die Verbindung ist 8080. Anschließend wird versucht mit connect(ClientSocket, strukt des Servers, sizeof(server)) != 0) sich zu verbinden, bei Fehlermeldung ist es ein Error und das Programm schließt sich oder man verbindet sich. 

Der Host initialisiert Winsock genauso, erstellt seinen socket und speichert in den Server strukt als Adresse htonl(INADDR_ANY), was für alle eigenen IP Adressen "gebündelt" steht. Der Socket wird anschließen per Funktion bind(EigenerSocket, strukt des Servers, sizeof(server))) != 0 gebunden, falls keine Probleme auftreten. Anschließend wird der Socket auf "listening" gestellt und ist damit erreichbar für Clienten, die sich verbinden wollen. In einer While schleife wird dann so lange gewartet, bis ein valider ClientSocket eintritt und durch accept(eigenerSocket,Adresse: NULL,addlren: NULL) akzeptiert. 

## Spielablauf Netzwerk
ein Listener Thread wird gestartet, der sich für die ReadMessages(...) kümmert.
Der Server/Host als Spieler 1, gibt seinen Spieler1.namen und Spieler.zeichen in das definierte Spieler strukt ein. Darauffolgend wird das Zeichen in ein String umgewandelt (Convstring), per strcpy (string-copy) und strcat(Concatenate strings) durch strcpy(DatenPaket,strcat(Spieler1.name,Convstring)) die Daten in das zu übermittelnde Datenpaket übergeben und zur Abrundung das Datenpaket an der Stelle strlen von namen und convstring+1 mit '\0' versehen. 
---Paketvermittlung---
aktivListen = 1 (ReadMessages Funktion wird alle 0,5s abgerufen) und auf die Eingabe vom Clienten für namen und zeichen wird gewartet. Wenn der C name == H name ist, (oder zeichen), dann muss der Client das neu eingeben. Das Paket wird auch so verpackt und übermittelt und Host stellt die Spielfeldgröße (zwischen 3 und 10) ein und beginnt das Spiel. 
Host (Spielernummer = 1), Client (Spielernummer == 2).
Spiel wird gestartet: if(Spielernummer == 1)
Spieler 1 ist am Zug, eingabe von x,y und getestet ob das belegt ist. Wenn nicht, setze dein Zeichen und sende ein Paket an Spieler 2 und wenn doch, erfordere erneute eingabe.)
if(Spielernummer == 2) 
Spieler 1 ist am Zug, Bitte warten und eine while Schleife zwingt den Anwender zu warten, bis ein Paket reinkommt. Wenn angekommen, setze die Koordinaten vom Paket in dein eigenes Feld mit seinem Zeichen. 
TestForWinner testet, ob ein Spieler gewonnen hat. Wenn ja, breche while Schleife vom Spiel ab. 
Das ganze wird dann nochmal gedreht, also mit (Spielernummer == 2) und dann (Spielernummer == 1) um ein symmetrischen Aufbau zu haben und am Ende wird noch ein counter hochgezählt, anhand diesem man den Sieger ermittelt. 

## Paketvermittlung
Idee: Speichere alles in ein langen String(als Paket) und übergeben der Funktion die Längen der eingefügten Strings, um diese wieder auseinanderbauen zu können.
Das Paket wird dann an den Clienten per SendenBrauchbar(DatenPaket,int strlen(name),int strlen(convstring)) übergeben. In SendenBrauchbar(char (pointer)Datenpaket, int string1length, int string2length) wird in string1 das Datenpaket reinkopiert und string_1 an stelle der übergebenen string1length mit '\0' abgeschlossen. Dasselbe passiert bei string_2, jedoch geht man da von string_2[0] aus und speichert dort hinnein string_2[string1length], anschließen auch abgeschlossen an string2length mit '\0'. jetzt werden die int string1length und 2 in ein char array gespeichert und an die Funktion SendMessageToClient(GetOtherSocket(),Datenpaket,stringlength) übergeben.
Diese Funktion Sendet einmal die message(das DatenPaket) und die Längen der Strings um sie wieder auseinanderbauen zu können. 
ReadMessage(int socket, char * DataToMe) wird durch ein Thread (falls aktivListen = 1 ist) alle 0,5s abgefragt und bei empfang eines Pakets durch recv(socket, DataToMe /* Buffer */*/, 65 (Datenpaket länge),0) zum einen der String entgegengenommen messageStatus == 0 und dann darauffolgend die String längen, um das Paket auseinander zu bauen (messageStatus == 0). Am Ende wird das DataToMe array geleert mit DataToMe[0] = '\0' und memset(DataToMe,0,strlen(DataToMe)).   

# Anwenderdokumentation

## TicTacToe starten:
Um das Spiel zu starten, muss lediglich die Programmdatei ausgeführt werden.     Man befindet sich danach direkt bei der Eingabe der Einstellungen.

## Eingabe der Einstellungen:
Zuerst muss der Anwender sich für Multiplayer („m“) oder Singleplayer („s) entscheiden. 

## Multiplayer 
Netzwerk und zweiter Anwender notwendig
Der Host muss sich als Host („H“) angeben und der zweite Anwender muss sich als Client („C“) angeben.
Die Verbindung wird dann über Eingabe der IP-Adresse des Hosts im angegebenen Format hergestellt und danach müssen die Spieleinstellungen konfiguriert werden. Erst der Host und dann der Client. Anschließend bekommt der Host die eingestellte Spieleinstellung übermittelt und das Spiel beginnt.

## Singleplayer
Direkter Übergang zu den Spieleinstellungen.

## Spieleinstellungen
Zuerst muss die Spielfeldgröße bestimmt werden.
Werte von 3 bis 10 sind gültig, allerdings wird die Spielfeldgröße 3 empfohlen.
Nun muss man zuerst für Spieler 1 Name, Zeichen mit dem er seine Felder setzt und den Spielertyp („1“ für Computer und „0“ für Spieler) angeben. Anschließend muss man die gleichen Parameter für Spieler 2 angeben.
Der Spielertyp „Computer“ wird seine Felder selbst setzen.                                                                      Für Spielertyp „Spieler“ muss eine eigene Angabe des Feldes stattfinden. 

## Spielablauf
Spieler 1 und Spieler 2 setzen immer abwechselnd ihr Zeichen auf das Spielfeld, bis ein Spieler gewonnen hat oder es kein freies Feld mehr gibt.
Ein Spieler hat gewonnen, wenn er es schafft eine ganze Reihe, Spalte oder Diagonale mit seinem Zeichen zu belegen.
Wenn ein Spieler gewonnen hat, wird der Sieger ermittelt und ausgegeben.                                      Ist das Spielfeld voll und es gibt keinen Sieger wird unentschieden ausgegeben.
In beiden Fällen ist der Programmablauf beendet.

# Gruppe
Felix Grohme, Dennis Maier, Daniel De Marco
