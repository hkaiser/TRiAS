//////////////////////////////////////////////////////////////////////////////                                                                                                                                                                                                                                                                                                                                                                   
//            Hinweise zu Markroprogrammierung                              //
//                                                                          //
//            Version 3.05.025 vom 2&. 6. 97                                //
//////////////////////////////////////////////////////////////////////////////                                                                                                                                                                                                                                                                                                                                                                   

1.	Aenderungen in der BasicScript-Erweiterung gegenueber der zur Zeit
        genutzten:

Dem Makroeditor wurde ein Fenster (Baumstruktur vorhandener Makros) hinzugefuegt,
in dem alle internen Makros eines TRiAS-Projektes zu sehen sind. Dabei sind zu
den allgemeinen Makros sogenannte "Filtermakros" und "Objekteigenschaftsmakros"
hinzugekommen.
	
Die Bearbeitung von Dateien im Makroeditor ist natuerlich auch weiterhin moeglich.
	 
Filtermakros ermoeglichen es, einzelne Objekte, die zu ausgewaehlten Objektklassen 
gehoeren, zu bearbeiten. Diese sind nur editierbar angelegt und muessen mittels eines 
anderen Makros, einer "Propertysequence", oder anderweitig (siehe auch Menuepunkt 
"Makro/Filtermakros") gestartet werden. Filtermakros koennen innerhalb einer 
Propertysequence debuggt werden. Eine "Propertysequence" ist natuerlich ueber den 
Makroeditor startbar.

"Objekteigenschaftsmakros" werden an Objekte als "dynamisch" erzeugte 
Objekteigenschaften angehaengt. Diese sind im Makroeditor auch nur editierbar angelegt, 
koennen unter dem Menuepunkt "Extras" installiert/deinstalliert und bei eventueller 
Objektrecherche abgearbeitet werden. 

Es ist moeglich, "Untermakros" zu erzeugen und innerhalb eines "Obermakros" zu 
starten. Der Name des Obermakros ist gleichzeituíg der Name des "BasicScript-Projektes". 
Startmakro ist dann immer das Obermakro ("Main()"). Die Schaffung solcher BasicScript-Projekte 
war notwendig, um Makros, die groesser als 64K werden, splitten zu koennen (Makroeditor kann 
nur Makros bis zu einer Groesse von 64K laden). Es koennen alle TRiAS-Projekt-internen 
Makros mit solchen Untermakros versehen werden.  Der Linkvorgang erfolgt allerdings erst 
waehrend der Makroabarbeitung. Der BasicScript-Compiler erkennt noch nicht, ob die in einem 	
anderen Makro nur eventuell vorhandenen Funktionen auch wirklich verfuegbar sind.  

Ein Dateimakro kann allerdings nicht mit Untermakros versehen werden. 
Es gibt jedoch die Moeglichkeit, Dateien als Datei-Links in das TRiAS-Projekt zu importieren. 
Diese werden, obwohl diese noch ausserhalb als Datei weiter verfuegbar sind, genauso behandelt 
wie andere TRiAS-Projekt-internen Makros und koennen ebenfalls Untermakros besitzen bzw. selbst 
Untermakros sein.Dateien, die nicht als Link importiert worden sind, sind von Aenderungen im 
jeweils importierten Makro nicht betroffen.Jede Aenderung in einer als Link importierten Datei 
zieht jedoch eine Aenderung dieser sich ausserhalb befindlichen Datei nach sich und umgekehrt.

Allgemeine Makros koennen ausserhalb des Makroeditors ueber den Menuepunkt "Makro/Makros" und 
den daraufhin erscheinenenden Dialog ("Ausfuehren") ausgefuehrt werden.
Darueberhinaus ist es nun moeglich, auch Makrodateien im gleichen Dialog ("Datei ausfuehren") 
zu starten. Ausfuehrbare allgemeine Makros muessen die Funktion "Main()" besitzen.

Der Makroeditor kann bei Projekt/Schliessen bzw. Projekt/Oeffnen sowohl im laufenden als auch 
im ruhenden Zustand offen gehalten werden. So koennen z.B. mehrere Projekte hintereinander 
ueber das selbe Makro bearbeitet werden. 

Im Makroeditor koennen Sub's bzw. Function's automatisch generiert und in den Makrotext 
(TRiAS-Projekt-interne Makros) eingefuegt werden. 
Einzelne Funktionen (Sub's) sind in der Baumstruktur des Makroeditorfensters unterhalb jeden 
Makros aufgelistet. Es kann zu diesen Funktionen in den Makrotext gesprungen werden.

Speicheroperationen werden über die "objman.dll" abgewickelt. Diese DLL kann auch autark für 
andere Objekte als die der BasicScript-Erwiterung verwandt werden. Diese Objekte müssen entweder 
eine Implementation des IPersistStream- oder IPersistFile-Interfaces besitzen.

Makrodateien können als "TRiAS-Erweiterungen" entweder projektbezogen oder global geladen werden. 
Dazu muß im Menue "Extras/Anpassen" eine Makrodatei im "Browse-Dialog" ausgewaehlt und als 
Erweiterung installiert werden. Das Entladen dieser Erweiterung erfolgt je nach Art 
(projektbezogen oder global) bei Projekt- oder Programmende. Über den gleichen Menuepunkt 
"Extras/Anpassen" koennen diese Erweiterungen wieder deinstalliert werden. Jedes als Erweiterung 
genutzte Makro muss als Startfunktion die Funktion "Main()" besitzen.

2. Probleme:

Sollten TRiAS-Projekt-interne Makros mit der alten BasicScript-Erweiterung erzeugt worden sein, 
koennen diese mit der neuen Erweiterung geladen werden. Es kann unter Umstaenden zu Schwierigkeiten 
bei Bearbeitung, Speicherung u.a. dieser Makros kommen, da die neuen Makros eine andere 
Speicherstruktur besitzen.

Die objman.dll, muss vorhanden sein, um mit der neuen Erweiterung arbeiten zu koennen 
(wird mit der TRiAS-Installation mitgeliefert).

Es kann vorkommen, dass wegen Versionskonflikten kompilierter Code der alten Erweiterung nicht zu 
starten ist. Es erscheint die Fehlermeldung "Cannot find extension.". In diesem Falle muss der 
Makrotext (nach einer Aenderung im Makrotext) noch einmal im Makroeditor kompiliert werden 
("Syntax testen").

Einige Funktionsdeklarationen bzw. -definitionen innerhalb von TRiAS haben sich geaendert. 
Es werden dadurch diese Funktionen im Makro bei weiterlaufende Makros ("SetBreakScript(false)") 
nicht mehr gerufen,da die Einsprungfunktionen im Makro nicht mehr gefunden werden. Diese 
Funktionen sind dementsprechend fuer ordnungsgemaesse Abarbeitung zu aendern. Dies betrifft vor 
allem Funktionen, die auf Ereignisse in TRiAS, wie beispielsweise das Schliessen des jeweiligen 
Projektes oder Schliessen von TRiAS, reagieren sollen.

Wird eine Datei ausserhalb des Makroeditors über Menuepunkt "Makro/Makros.../Datei ausfuehren" 
gestartet und es tritt ein Laufzeitfehler auf, kann diese Datei im erzeugten Makroeditor, der 
den Fehler anzeigt, nicht abgespeichert werden. Der Makroeditor ist an dieser Stelle zu schliessen.
Zur Fehlerbeseitigung sollte die fehlerhafte Makroscriptdatei im Makroeditor nochmals geoeffnet 
und geaendert werden.
