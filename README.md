# TicTacToe_Network
# Projekt nur über Windows Spielbar

- [Entwicklerdokumentation](#entwicklerdokumentation)
  * [Vorraussetzungen fuer Multiplayer](#vorraussetzungen-fuer-multiplayer)
  * [Spielablauf](#spielablauf)
  * [Gewinntester](#gewinntester)
  * [Computerspieler](#computerspieler)
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

# Anwenderdokumentation

## TicTacToe starten:
Um das Spiel zu starten, muss lediglich die Programmdatei ausgeführt werden.     Man befindet sich danach direkt bei der Eingabe der Einstellungen.

## Eingabe der Einstellungen:
Zuerst muss der Anwender sich für Multiplayer („m“) oder Singleplayer („s) entscheiden. 

## Multiplayer 
Netzwerk und zweiter Anwender notwendig
Der Host muss sich als Host („H“) angeben und der zweite Anwender muss sich als Client („C“) angeben.
Die Verbindung wird dann über Eingabe der IP-Adresse des Hosts im angegebenen Format hergestellt und danach müssen die Spieleinstellungen konfiguriert werden.

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
Felix Grohme, Dennis Mayer, Daniel De Marco
