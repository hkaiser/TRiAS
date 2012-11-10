TRiAS GmbH Potsdam, Potsdam, den 6. Juni 2000, InterTRiAS V3.12

Im folgenden wird eine Übergangslösung für das Problem des nicht 
funtionierenden gleichzeitigen Zugriffs auf InterTRiAS-Datenquellen 
und -projekte unter Novell-Netzwerken beschrieben.

Der Auftretende Fehler äußert sich in verschiedenen Fehlermeldungen 
und teilweisen Abstürzen von InterTRiAS, wenn gleichzeitig mehrere 
Nutzer auf ein und die selben InterTRiAS-Datenquellen bzw. -projekte
zugreifen.

Der kann zur Zeit lediglich durch folgende Maánahmen umgangen werden:

Die Datei 'UseNovellTestCode.reg' muß auf jedem Client-Rechner (für jeden
InterTRiAS-Nutzer) nach der erfolgreichen Installation von InterTRiAS in die
Systemregistrierung übernommen werden. Dazu klicken Sie bitte im Explorer mit 
der rechten Maustaste auf diese Datei und wählen den Menupunkt 'Zusammenführen'.

Die Datei 'InterTRiAS.Dir' muß in jedes Verzeichnis kopiert werden, in welchem
sich InterTRiAS-Datenquellen bzw. -projekte existieren, auf die über ein
Novell-Netzwerk zugegriffen werden soll.

