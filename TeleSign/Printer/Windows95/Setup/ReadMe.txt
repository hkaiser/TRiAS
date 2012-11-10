Installation des TeleSafe Druckers unter Windows 95
Stand 11.06.1999

Die Installation erfolgt in zwei Schritten:
1. Kopieren der Datei TeleSign.ini in das Verzeichnis C:\Windows\
2. Installation des Druckers

Um den Drucker zu entfernen wird er einfach im Druckerordner gelöscht.

Die aktuelle Version des Druckers startet nicht mehr eine fest eingestellte Anwendung,
sondern verwendet Einträge aus der Datei TeleSign.ini.
Diese sind:

[Printer]
ShellExecute=C:\Programme\TeleSign\\TeleSafe.exe"
; Name des auszuführenden Programmes
ShellDirectory=C:\Programme\TeleSign
; Standardverzeichnis während der Ausführung
DataFileName=C:\TSDBMP.
; Dateiname, unter dem der Drucker die erzeugten Bitmaps ablegt.
; Unter Windows 95 wird eine Datei pro Seite erzeugt. Der Dateiname muß mit einem Punkt
; enden, und wird um  die dreistellige Seitennummer ergänzt.
ShellExecuteMode=1
; Steuerparameter für Drucker und TeleSafe. Ist das niedrigste Bit gesetzt,
; wird ShellExecute mit den obigen Parametern ausgeführt.
; Alle übrigen Bits sind für die spätere Verwendung im aufgerufenen Programm reserviert.
ShellExecuteDefaultMode=1
; TeleSafe wird bei jedem Aufruf den Eintrag ShellExecuteMode auf diesen Wert setzen, um eine Standardausführung zu gewährleisten.

