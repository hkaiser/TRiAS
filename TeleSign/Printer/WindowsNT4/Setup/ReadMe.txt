Installation des TeleSafe Druckers unter Windows NT 4.0
Stand 08.06.1999

Die vorliegende Version des TeleSafe Druckers arbeitet mit einem eigenen Port-Monitor.
Dieser wird durch die Datei tsdmon.dll realisiert.

Die Installation erfolgt in zwei Schritten:
1. Kopieren der Datei tsdmon.dll in das Verzeichnis c:\winnt\system32
   und ausführen der Datei TSInstall.reg Danach wird das System neu gebootet
2. Installation des Druckers am Anschluß TSDV:

Um den Drucker zu entfernen wird er einfach im Druckerordner gelöscht.
Um den Port-Monitor zu entfernen, muß der Schlüssel [HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Print\Monitors\TeleSign Port] gelöscht  und der Rechner neu gebootet werden.
Das gleiche gilt, wenn man eine neuere Version der Datei tsdmon.dll installieren möchte.

Die aktuelle Version des Port-Monitors startet nicht mehr eine fest eingestellte Anwendung,
sondern verwendet Einträge der Registrierungsdatenbank.
Diese sind:

[HKEY_LOCAL_MACHINE\SOFTWARE\FEZ Potsdam GmbH\TeleSafe\Printer]
"ShellExecute"="D:\\Programme\\TeleSafe\\TeleSafe.exe"
; Name des auszuführenden Programmes
"ShellDirectory"="D:\\Programme\\TeleSafe"
; Standardverzeichnis während der Ausführung
"DataFileName"="C:\\TSDBMP.DAT"
; Dateiname, unter dem der Port die vom Drucker erzeugten Daten ablegt.
; Soll TeleSafe diese Datei verarbeiten, muß sie die Erweiterung .DAT haben.
"ShellExecuteMode"=dword:00000001
; Steuerparameter für Port und TeleSafe. Ist das niedrigste Bit gesetzt,
; wird ShellExecute mit den obigen Parametern ausgeführt.
; Alle übrigen Bits sind für die spätere Verwendung im aufgerufenen Programm reserviert.
"ShellExecuteDefaultMode"=dword:00000001
; TeleSafe wird bei jedem Aufruf den Registry-Eintrag ShellExecuteMode auf diesen Wert setzen, um eine Standardausführung zu gewährleisten.

Um diese Einträge zu erzeugen, muß die Datei Printer.reg ausgeführt werden.