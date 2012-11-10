Grundstücke über Stadtbezirk bilden :

	Beschreibungsdaten importieren (TXI,TXM)
	Makro ALB starten
	Recherche nach Flurstücken mit Grundstücksnummer, ASC-EXPORT
	GRUNDST.AWK über ASC-File laufen lassen ( 1123 wird zu 1124)
	Import des neuen ASC-Files (=Grundstücke)
	GesamtGrundstückeBilden - Makro starten (Blinkeln)

Nun die Stanze :

Voraussetzung - Statistik ist geladen, ALK-Karten [961016] sind in der Sicht definiert!
Ausgehend von einem Kartenblatt wird eine Stanze [961016a] konstruiert. Die Stanze wie 
die Grundstücke in der Stanze erhalten die Kartennummer (Kode 71100000) der Ursprungskarte.
Grundstücke ohne Kartennummer müssen überprüft werden 
( meist Grundstücke mit Geometriefehler).
Innerhalb von Stanzen liegende kleinere Stanzen der Nachbarkarte (auch Inseln/Löcher)
werden gelöscht und die darin liegenden Grundstücke der größeren Stanze zugeordnet.

Test der Überlappung von Stanzen durch Makro GeometrieTest.

Sind anzahlmäßig mehr Stanzen entstanden als Kartenblätter bzw. räumlich relativ 
kleine Stanzen, so sollte überprüft werden, ob kleinere Stanzen größeren zugeordnet 
werden können ( Kartennummer beachten!).


