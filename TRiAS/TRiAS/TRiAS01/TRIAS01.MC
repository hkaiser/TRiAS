;///////////////////////////////////////////////////////////////////////////////
;// Messages for TRiASDB
;// SourceFile: TRiAS01.MC
;
;#if !defined(_TRiAS01_HMC)
;#define _TRiAS01_HMC
;
;#if _MSC_VER >= 1000
;#pragma once
;#endif // _MSC_VER >= 1000
;

;#define MAX_MSG_LENGTH				1024

;#define SEVERITY_MASK				0xC0000000
;#define APPLICATION_MASK			0x20000000
;#define SEVERITY_SUCCESS_MASK		0x00000000
;#define SEVERITY_INFORMATIONAL_MASK 0x40000000
;#define SEVERITY_WARNING_MASK		0xB0000000
;#define SEVERITY_ERROR_MASK			0xC0000000

;#define FACILITY_MASK				0x0FFF0000
;#define FACILITY_TRIAS01_MASK		0x0F110000

;#define MSG_ID_MASK					0x0000FFFF

SeverityNames = (
	Success = 0x0:STATUS_SEVERITY_SUCCESS
	Informational = 0x1:STATUS_SEVERITY_INFORMATIONAL
	Warning = 0x2:STATUS_SEVERITY_WARNING
	Error = 0x3:STATUS_SEVERITY_ERROR
)

FacilityNames = (
	System = 0x0FF
	TRiAS01 = 0xF11:FACILITY_TRIAS01	; Fehler des Datenbanksystems
)

LanguageNames = (Deutsch = 0x407:MSG00407)

MessageIdTypedef = HRESULT

;
MessageId=1805
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENODBF
Language=Deutsch
dBASE-Dateien nicht angegeben
.

MessageId=1804
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENODBC
Language=Deutsch
Keine Anbindung von dBASE-S‰tzen definiert
.

MessageId=1802
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EBADFO
Language=Deutsch
Falsche Objektauswahl
.

MessageId=1801
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EBADIN
Language=Deutsch
Falsche Anichts-Spezifikation
.

MessageId=1800
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EBADWI
Language=Deutsch
Falsche Gebiets-Spezifikation
.

MessageId=1720
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EEXTIN
Language=Deutsch
Kann Erweiterung nicht laden
.

MessageId=1719
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EREGDX
Language=Deutsch
Kann Windowsmessages f¸r Erweiterung nicht registrieren
.

MessageId=1716
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENODLL
Language=Deutsch
DLL-Funktion nicht gefunden
.

MessageId=1715
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EEXPRS
Language=Deutsch
Der dBASE-Ausdruckspuffer ist zu klein
.

MessageId=1714
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENMKML
Language=Deutsch
Referenz auf nichtexistierendes Objektmerkmal
.

MessageId=1713
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EBPARM
Language=Deutsch
Ung¸ltiger Parameter in dBASE-Ausdruck
.

MessageId=1712
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOSCR
Language=Deutsch
Keine Scriptdatei f¸r Recherche gegeben
.

MessageId=1711
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EDLLAC
Language=Deutsch
Import Semaphore ist gesetzt, bitte noch einmal versuchen
.

MessageId=1710
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENHELP
Language=Deutsch
Hilfetext  Datei nicht auffindbar
.

MessageId=1709
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EBPERS
Language=Deutsch
Personalisierungs-Information wurde ver‰ndert
.

MessageId=1708
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EBMFLT
Language=Deutsch
Device Dependent Bitmap kann nicht generiert werden
.

MessageId=1707
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EPALET
Language=Deutsch
Palette kann nicht generiert werden
.

MessageId=1706
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENODIB
Language=Deutsch
Bild ist keine DIB (falsches Format)
.

MessageId=1705
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOTIM
Language=Deutsch
Kein weiterer System-Timer mehr verf¸gbar
.

MessageId=1704
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EBDCPU
Language=Deutsch
Anwendung benˆtigt mindestens einen Prozessor vom Typ 80286
.

MessageId=1703
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EBDMDE
Language=Deutsch
Anwendung kann nicht im Windows-Realmode gestartet werden
.

MessageId=1702
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EPBDNO
Language=Deutsch
Im DatenbasisHeader ist kein PBDName gegeben
.

MessageId=1701
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EILPAR
Language=Deutsch
Illegaler Parameter
.

MessageId=1700
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENODBN
Language=Deutsch
DBName ist nicht definiert
.

MessageId=1620
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BDIRIS
Language=Deutsch
Sie benutzen eine zu alte TRiAS-Version
.

MessageId=1607
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BADPRI
Language=Deutsch
Ung¸ltiges Prim‰rObjekt
.

MessageId=1606
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BADTYP
Language=Deutsch
Falscher SatzTyp
.

MessageId=1605
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BRECPB
Language=Deutsch
PBDSatz ist nicht vorhanden
.

MessageId=1604
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BRECMW
Language=Deutsch
MerkmalsWert ist nicht vorhanden
.

MessageId=1603
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BRECRL
Language=Deutsch
RelationsSatz ist nicht vorhanden
.

MessageId=1602
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BRECMK
Language=Deutsch
MerkmalsSatz ist nicht vorhanden
.

MessageId=1601
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BRECID
Language=Deutsch
IdentifikatorSatz ist nicht vorhanden
.

MessageId=1501
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BADPOL
Language=Deutsch
Ung¸ltiger Verweis aus POL in VGO
.

MessageId=1446
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_FATAL
Language=Deutsch
Fataler Fehler beim Arbeiten mit dBASE
.

MessageId=1445
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_RESULT
Language=Deutsch
Unerwartetes Ergebnis einer Funktion beim Arbeiten mit dBASE
.

MessageId=1444
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_PARM
Language=Deutsch
Unerwarteter R¸ckkehrwert einer dBASEFunktion
.

MessageId=1443
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NEW
Language=Deutsch
Fehler bei HauptspeicherAnforderung in dBASE
.

MessageId=1442
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_MEMORY
Language=Deutsch
Hauptspeicher ist nicht ausreichend f¸r dBASE
.

MessageId=1441
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_INFO
Language=Deutsch
Interner Fehler in dBASEBibliothek
.

MessageId=1440
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UNTSTR
Language=Deutsch
Nichtbeendete Zeichenkette in einem dBASEAusdruck
.

MessageId=1439
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UNRVAL
Language=Deutsch
Unbekannter Wert in einem dBASEAusdruck
.

MessageId=1438
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UNROPR
Language=Deutsch
Unbekannter Operator in einem dBASEAusdruck
.

MessageId=1437
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UNRFCT
Language=Deutsch
Unbekannte Funktion in einem dBASEAusdruck
.

MessageId=1436
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_TYPE
Language=Deutsch
Unbekannter Operand in einem dBASEAusdruck
.

MessageId=1435
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_RIGHTM
Language=Deutsch
In einem dBASEAusdruck fehlt die rechte Klammer
.

MessageId=1434
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_OVERFL
Language=Deutsch
dBASEAusdruck ist zu lang oder zu kompliziert
.

MessageId=1433
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NUMPAR
Language=Deutsch
Falsche Anzahl Parameter in einem dBASEAusdruck
.

MessageId=1432
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_DATANM
Language=Deutsch
In einem dBASEEpression benˆtigte dBASEDatei konnte nicht geˆffnet werden
.

MessageId=1431
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_COMPLT
Language=Deutsch
dBASEAusdruck ist unvollst‰ndig
.

MessageId=1430
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_COMMAE
Language=Deutsch
In einem dBASEExpresion fehlen Komma oder rechte Klammer
.

MessageId=1429
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UNIQUE
Language=Deutsch
Schl¸ssel nicht einzigartig
.

MessageId=1428
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_TAGNAM
Language=Deutsch
TagName wurde nicht gefunden
.

MessageId=1427
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_INDEX
Language=Deutsch
Fehler beim ÷ffnen einer IndexDatei
.

MessageId=1426
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENTRY
Language=Deutsch
TagEintrag wurde nicht gefunden
.

MessageId=1425
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_RECDLN
Language=Deutsch
Satzl‰nge ist zu groﬂ (max. 65535)
.

MessageId=1424
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_FIELDT
Language=Deutsch
Unbekannter Feldtyp
.

MessageId=1423
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_FIELDN
Language=Deutsch
Unbekannter Feldname
.

MessageId=1422
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_DATA
Language=Deutsch
Fehler beim ÷ffnen einer dBASEDatendatei
.

MessageId=1421
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_WRITE
Language=Deutsch
Fehler beim Schreiben einer dBASEDatei
.

MessageId=1420
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UNLOCK
Language=Deutsch
Fehler beim Entriegeln einer dBASEDatei
.

MessageId=1419
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_SEEK
Language=Deutsch
Fehler beim Positionieren einer dBASEDatei
.

MessageId=1418
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_RENAME
Language=Deutsch
Fehler beim Umbenennen einer dBASEDatei
.

MessageId=1417
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_REMOVE
Language=Deutsch
Fehler beim Lˆschen einer dBASEDatei
.

MessageId=1416
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_READ
Language=Deutsch
Fehler beim Lesen einer dBASEDatei
.

MessageId=1415
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_OPEN
Language=Deutsch
Fehler beim ÷ffnen einer dBASEDatei
.

MessageId=1414
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_LOCK
Language=Deutsch
Fehler beim Verriegeln einer dBASEDatei
.

MessageId=1413
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_LENSET
Language=Deutsch
Fehler beim Setzen der L‰nge einer dBASEDatei
.

MessageId=1412
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_LENGTH
Language=Deutsch
Fehler beim Bestimmen der L‰nge einer dBASEDatei
.

MessageId=1411
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_CREATE
Language=Deutsch
Fehler beim Erzeugen einer dBASEDatei
.

MessageId=1410
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_CLOSE
Language=Deutsch
Fehler beim Schlieﬂen einer dBASEDatei
.

MessageId=1300
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BADGEO
Language=Deutsch
Fehlerhafte Geometrie
.

MessageId=1252
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOWRIT
Language=Deutsch
Fehler beim Schreiben in Datei
.

MessageId=1251
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOSCAL
Language=Deutsch
Skalierung ist nicht berechenbar
.

MessageId=1250
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOTMPF
Language=Deutsch
Kann tempor‰re Datei nicht ˆffnen
.

MessageId=1223
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NORELA
Language=Deutsch
Keine Relation
.

MessageId=1222
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NODBFF
Language=Deutsch
Keine dBaseDatei
.

MessageId=1221
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NUMEFO
Language=Deutsch
Daten nicht im numerischen Format
.

MessageId=1220
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_GROUPS
Language=Deutsch
Unvollst‰ndige Gruppenspezifikation
.

MessageId=1219
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UNCOMP
Language=Deutsch
Unvollst‰ndige Anfrage
.

MessageId=1218
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UOUTST
Language=Deutsch
Ung¸ltige Ausgabeanweisung    
.

MessageId=1217
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_OUTFOR
Language=Deutsch
Unbekanntes Ausgabeform
.

MessageId=1216
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_OUTDEV
Language=Deutsch
Unbekanntes Ausgabeger‰t
.

MessageId=1215
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_KEYSPE
Language=Deutsch
Ung¸ltige Schl¸sselAnbindung
.

MessageId=1214
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_DBASEE
Language=Deutsch
Ung¸ltiger dBASEAusdruck
.

MessageId=1213
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_FILESP
Language=Deutsch
Ung¸ltige dBASEDatei
.

MessageId=1212
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_IDENTS
Language=Deutsch
Ung¸ltiger Identifikator
.

MessageId=1211
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NODATA
Language=Deutsch
Ung¸ltige Daten    
.

MessageId=1210
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOTEXT
Language=Deutsch
Daten nicht im Textformat    
.

MessageId=1209
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_RAKTIV
Language=Deutsch
Recherche ist bereits aktiv    
.

MessageId=1208
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_SYNTAX
Language=Deutsch
SyntaxFehler    
.

MessageId=1207
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NIIDDE
Language=Deutsch
Es gibt keine g¸ltigen IdentifikatorBeschreibungen
.

MessageId=1206
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UOBJTY
Language=Deutsch
Ung¸ltiger Objekttyp oder keine Visualisierungsinformation
.

MessageId=1205
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_USBREK
Language=Deutsch
Abbruch durch den Nutzer
.

MessageId=1204
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NORESO
Language=Deutsch
Resource nicht gefunden
.

MessageId=1203
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOSYMB
Language=Deutsch
Symbol nicht gefunden
.

MessageId=1202
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EVISIN
Language=Deutsch
Kann VisualisierungsTemplate nicht erzeugen
.

MessageId=1201
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ELINET
Language=Deutsch
Kann Linientabelle nicht erzeugen
.

MessageId=1200
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ELAYER
Language=Deutsch
EbenenNamen nicht gefunden
.

MessageId=1154
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NODSNA
Language=Deutsch
DataSourceName nicht gefunden
.

MessageId=1153
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NTABLN
Language=Deutsch
Name der Tabelle nicht gefunden
.

MessageId=1152
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOQUER
Language=Deutsch
F¸r diesen Feldtyp ist keine Anfrage mˆglich
.

MessageId=1151
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UNKNFN
Language=Deutsch
Unbekannter Feldname
.

MessageId=1150
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_UNKNFT
Language=Deutsch
Unbekannter Feldtyp 
.

MessageId=1130
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NODSCN
Language=Deutsch
Verbindung zum ODBCTreiber nicht mˆglich
.

MessageId=1129
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ONLFOR
Language=Deutsch
Nur Vorw‰rtsScrollen mˆglich
.

MessageId=1128
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EMPTCO
Language=Deutsch
Leere FeldnamensListe
.

MessageId=1127
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_FIELDM
Language=Deutsch
F¸r einen Feldtyp ist keine Anbindung definiert
.

MessageId=1126
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ILLNOD
Language=Deutsch
ODBCTreiber im illegalen Modus geˆffnet
.

MessageId=1125
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_MULROW
Language=Deutsch
Kann nicht mehrere S‰tze ‰ndern/lˆschen        
.

MessageId=1124
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOCURR
Language=Deutsch
Es existiert kein aktueller Satz
.

MessageId=1123
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ACTRNF
Language=Deutsch
Aktuellen Satz nicht mehr gefunden
.

MessageId=1122
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_READON
Language=Deutsch
Nur LeseOperationen mˆglich   
.

MessageId=1121
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOTOTA
Language=Deutsch
Maximale Grˆﬂe eines CLongBinaryFeldes nicht bestimmbar
.

MessageId=1120
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NODBCL
Language=Deutsch
ODBC kann nicht geladen werden          
.

MessageId=1119
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NODYNA
Language=Deutsch
Dynamisches Nachf¸hren wird durch ODBCTreiber nicht unterst¸tzt
.

MessageId=1118
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOSNAP
Language=Deutsch
ODBC ist nicht vollst‰ndig installiert
.

MessageId=1117
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOAPIC
Language=Deutsch
Der ODBCTreiber unterstÅtzt nicht ODBCAPILevel 1
.

MessageId=1116
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOSQLC
Language=Deutsch
Der ODBCTreiber unterst¸tzt nicht ODBCSQLLevel "MINIMUM"
.

MessageId=1115
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NODATF
Language=Deutsch
Keine Daten gefunden
.

MessageId=1114
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOROWU
Language=Deutsch
Zeilenénderung wird nicht unterst¸tzt
.

MessageId=1113
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ODBCV2
Language=Deutsch
ODBCVersion 2.0 nicht installiert
.

MessageId=1112
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOPOSU
Language=Deutsch
énderung der Daten nicht mˆglich    
.

MessageId=1111
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_NOLOKM
Language=Deutsch
VerriegelungsModus wird nicht unterst¸tzt  
.

MessageId=1110
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_DATTRU
Language=Deutsch
Daten zu groﬂ (wurden entsprechend gek¸rzt)
.

MessageId=1104
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_LOERRO
Language=Deutsch
Fehler beim Verriegeln eines Objektes    
.

MessageId=1101
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOSCHWERPUNKT
Language=Deutsch
Fl‰chenschwerpunkt nicht bestimmbar
.

MessageId=1100
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOSCHNITTPUNKT
Language=Deutsch
Geraden haben keinen Schnittpunkt
.

MessageId=1020
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFTYP
Language=Deutsch
Falsche Typangabe ( zul‰ssig sind nur M,F,L,P )
.

MessageId=1019
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ETYPF
Language=Deutsch
Informationstyp nicht vorhanden
.

MessageId=1018
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ETYPM
Language=Deutsch
Informationstyp nur f¸r E/A Merkmalswerttext
.

MessageId=1014
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EMKLNO
Language=Deutsch
Merkmal in der PBD nicht vorhanden
.

MessageId=1013
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ERELNO
Language=Deutsch
Relation in der PBD nicht vorhanden
.

MessageId=1012
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EIDLNO
Language=Deutsch
Identifikator in PBD nicht vorhanden
.

MessageId=940
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENWFAK
Language=Deutsch
Wiederholungsfaktor bei MI ist inkompatibel
.

MessageId=939
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENIDMK
Language=Deutsch
Zuordnung IdentifikatorMerkmalskode falsch
.

MessageId=938
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EDEFWT
Language=Deutsch
Quantitativer Merkmalswert undefiniert
.

MessageId=937
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EINKON
Language=Deutsch
Inkonsistenz bei letztem Objekt
.

MessageId=936
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EHEAD
Language=Deutsch
Fehler bei Zugriff auf Header
.

MessageId=935
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EAHEAD
Language=Deutsch
Fehler bei Anlegen des Headers
.

MessageId=934
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ECOND
Language=Deutsch
Parameterfehler bei 'cond'
.

MessageId=933
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ERIK
Language=Deutsch
Fehler im RIKFeld
.

MessageId=932
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EPUTKO
Language=Deutsch
Fehler bei Einrichten des KO
.

MessageId=931
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ETYPKO
Language=Deutsch
Keine Typ¸bereinstimmung bei KO
.

MessageId=930
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EANSCH
Language=Deutsch
Kein Anschluﬂ bei linienhaften Objekten
.

MessageId=929
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ERA
Language=Deutsch
Falsche Relationsart
.

MessageId=928
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EDEL
Language=Deutsch
Fehler bei Lˆschen eines Objektes
.

MessageId=927
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EONF
Language=Deutsch
Formaler Fehler im onfFeld
.

MessageId=926
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EZDB
Language=Deutsch
Fehler aus DatenbasisVerwaltung
.

MessageId=925
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENTQWT
Language=Deutsch
Qualitativer Merkmalswert undefiniert
.

MessageId=924
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ETOUCH
Language=Deutsch
Neuer Zustand der DB nicht sicherbar
.

MessageId=923
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EREST
Language=Deutsch
Restore der DB nicht mˆglich
.

MessageId=922
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EGETO
Language=Deutsch
Objekt nicht wiederauffindbar
.

MessageId=921
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EADFGI
Language=Deutsch
GIAusgabedatenformat falsch
.

MessageId=920
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENLMI
Language=Deutsch
L‰ngenfehler im MIFeld
.

MessageId=919
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENP
Language=Deutsch
Parameter 'np' ist falsch
.

MessageId=918
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EOBNR
Language=Deutsch
Objektnummer ist kleiner 1
.

MessageId=917
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EOFF
Language=Deutsch
Geometriefehler bei fl‰chenhaften EO
.

MessageId=916
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EINZ
Language=Deutsch
Selbstinzidenz einer Linie
.

MessageId=915
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EEPS
Language=Deutsch
Epsilon ist negativ
.

MessageId=914
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EEDFGI
Language=Deutsch
GIEingabedatenformat falsch
.

MessageId=913
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENLGI
Language=Deutsch
L‰ngenfehler bei Geometriefeld
.

MessageId=912
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENTSK
Language=Deutsch
falscher Strukturkode
.

MessageId=911
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENTMK
Language=Deutsch
Merkmalskode nicht in PBD
.

MessageId=910
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EMI
Language=Deutsch
Fehler in MIStruktur
.

MessageId=909
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENTTYP
Language=Deutsch
Geometrietyp des EO falsch
.

MessageId=908
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENTID
Language=Deutsch
Identifikator nicht in PBD
.

MessageId=907
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENTACT
Language=Deutsch
DB/PBD nicht aktivierbar
.

MessageId=906
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EPUTEO
Language=Deutsch
EO nicht in DB eintragbar
.

MessageId=905
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EDELET
Language=Deutsch
DB/PBD nicht lˆschbar
.

MessageId=904
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ECLSE
Language=Deutsch
DB/PBD nicht schlieﬂbar
.

MessageId=903
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EOPEN
Language=Deutsch
DB/PBD nicht erˆffenbar
.

MessageId=902
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EMXDB
Language=Deutsch
Maximale Anzahl erˆffenbarer DB/PBD erreicht
.

MessageId=901
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EDBNOT
Language=Deutsch
DB/PBD ist nicht initialisierbar
.

MessageId=900
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EDBACT
Language=Deutsch
DB ist schon erˆffnet
.

MessageId=793
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOFLX
Language=Deutsch
Kein dynamisches Feld mehr verf¸gbar
.

MessageId=792
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFLINI
Language=Deutsch
Dynamisches Feld enth‰lt keine Daten (ist initialisiert)
.

MessageId=791
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EINDEX
Language=Deutsch
Fragw¸rdiger Index bei Flexaddressierung
.

MessageId=790
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFLEX
Language=Deutsch
Fragw¸rdige Flexnummer
.

MessageId=753
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_RECDEL
Language=Deutsch
Satz ist nur in R¸ckverkettung enthalten
.

MessageId=752
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_DELREC
Language=Deutsch
Satz ist nicht in R¸ckverkettung enthalten
.

MessageId=751
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_INVCHA
Language=Deutsch
Ung¸ltiger R¸ckverkettungszeiger
.

MessageId=750
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_BADFNO
Language=Deutsch
Ung¸ltige Dateinummer
.

MessageId=730
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENPBDN
Language=Deutsch
Ung¸ltiger Name der BeschreibungsDatenbasis
.

MessageId=728
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EISDEL
Language=Deutsch
Zu lˆschender Satz ist bereits gelˆscht
.

MessageId=727
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EBADHD
Language=Deutsch
DBHeader  Textfeld zu klein
.

MessageId=726
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENEVEC
Language=Deutsch
Kann Fehlervektor nicht anlegen
.

MessageId=725
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EOVERF
Language=Deutsch
öberlauf des Fehlervektors
.

MessageId=724
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EMAXDB
Language=Deutsch
Bereits MAXDB Datenbasen erˆffnet
.

MessageId=723
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EOVRFL
Language=Deutsch
öberlauf der Hashtabelle
.

MessageId=722
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EBCKUP
Language=Deutsch
Fehler im Prozeﬂ des Backup
.

MessageId=721
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ESPAWN
Language=Deutsch
Kann Subprozeﬂ nicht starten
.

MessageId=720
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EACCES
Language=Deutsch
öberschreitung der Zugriffsrechte
.

MessageId=719
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EREAD
Language=Deutsch
Lesefehler
.

MessageId=718
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EUNLNK
Language=Deutsch
Kann Page nicht von File lˆsen
.

MessageId=717
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ELINK
Language=Deutsch
Kann Page nicht an File binden
.

MessageId=716
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENFILE
Language=Deutsch
Datei nicht gefunden
.

MessageId=715
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOMEM
Language=Deutsch
Hauptspeicher nicht ausreichend
.

MessageId=714
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENWORK
Language=Deutsch
Kein 'working_file' gegeben
.

MessageId=713
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFAULT
Language=Deutsch
Pagefehler
.

MessageId=712
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ESYSTM
Language=Deutsch
Systemfehler
.

MessageId=711
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EDFULL
Language=Deutsch
Datei kann nicht vergrˆﬂert werden
.

MessageId=710
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ECLOSE
Language=Deutsch
Kann DB nicht abschlieﬂen
.

MessageId=709
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EACTIV
Language=Deutsch
Fehler beim Aktivieren einer DB
.

MessageId=708
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EKEYNO
Language=Deutsch
Fragw¸rdige Schl¸sselnummer
.

MessageId=707
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ECTREE
Language=Deutsch
CubicTree zu tief verschachtelt
.

MessageId=706
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EQTREE
Language=Deutsch
Quadtree zu tief verschachtelt
.

MessageId=705
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EHTREE
Language=Deutsch
Hextree zu tief verschachtelt
.

MessageId=704
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOKEY
Language=Deutsch
Kein g¸ltiger Schl¸ssel
.

MessageId=703
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EVERSN
Language=Deutsch
Falsche Versionsnummer
.

MessageId=702
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENDBA
Language=Deutsch
Ung¸ltige Datenbankadresse
.

MessageId=701
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOPEN
Language=Deutsch
Datenbasis nicht erˆffnet
.

MessageId=700
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENAME
Language=Deutsch
Ung¸ltige(r) Datenbasis(name)
.

MessageId=618
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EUELKE
Language=Deutsch
Zu viele Konturen, öberlauf Feld KE
.

MessageId=617
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EMIX
Language=Deutsch
Geschlossene und nicht geschlossene Polygonz¸ge
.

MessageId=616
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EIKINC
Language=Deutsch
Innenkonturen liegen ineinander
.

MessageId=615
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EIKEX
Language=Deutsch
Innenkontur liegt nicht in Auﬂenkontur
.

MessageId=614
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EKSCHN
Language=Deutsch
Konturen schneiden einander (nicht in St¸tzpunkt)
.

MessageId=613
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EKBER
Language=Deutsch
Ber¸hrung oder Schnitt von Konturen (in St¸tzpkt)
.

MessageId=612
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EPSCHN
Language=Deutsch
Selbst¸berschneidung Polygonzug (nicht in St¸tzpkt)
.

MessageId=611
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EPBER
Language=Deutsch
Doppel/Ber¸hrungspkt/Selbst¸berschneidung Polygonzug
.

MessageId=583
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EGIVLT
Language=Deutsch
Tempor‰res GIFeld f¸r Aufbereitung der GI fuer FEO zu klein
.

MessageId=582
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFUNCL
Language=Deutsch
Fl‰chenumrandung nicht geschlossen
.

MessageId=581
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFLOF
Language=Deutsch
Fehlerhafte Linienobjektfolge
.

MessageId=575
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EABEND
Language=Deutsch
Abbruch der Verarbeitung
.

MessageId=570
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOPBD
Language=Deutsch
Widerspruch PBDName zwischen DBHeader und IKE
.

MessageId=565
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EOBKTR
Language=Deutsch
Objekt besitzt keine thematischen Relationen
.

MessageId=564
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EVOREL
Language=Deutsch
Verweis Objekt zu Relation falsch
.

MessageId=563
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFOREL
Language=Deutsch
Falsche Objektnummer in Relation
.

MessageId=562
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFVRAO
Language=Deutsch
Verweis RelationsartObjektfolge ist falsch
.

MessageId=561
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOVRE
Language=Deutsch
Verweis RelationsartRelation ist fehlerhaft
.

MessageId=560
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ERANRA
Language=Deutsch
Relationsart aus DB nicht in KeyTabelle
.

MessageId=555
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENODB
Language=Deutsch
Kein Objekt in der Datenbasis
.

MessageId=549
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EMKDUP
Language=Deutsch
Objekt besitzt in MIKette doppelten Merkmalscode
.

MessageId=548
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOVMO
Language=Deutsch
Objekt nicht in Verbindung MerkmalObjektfolge
.

MessageId=547
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFVMOB
Language=Deutsch
Verweis MerkmalskodeObjektfolge fehlerhaft
.

MessageId=546
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EMKNMK
Language=Deutsch
Merkmalskode aus DB nicht in KeyTabelle
.

MessageId=545
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOVIO
Language=Deutsch
Objekt nicht in Verbindung IdentifikatorObjektfolge
.

MessageId=544
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFVIOB
Language=Deutsch
Verweis IdentifikatorObjektfolge fehlerhaft
.

MessageId=543
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EIKNID
Language=Deutsch
Identifikator aus DB nicht in KeyTabelle
.

MessageId=542
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFRDEF
Language=Deutsch
Verweis ObjektRelationsart fehlerhaft
.

MessageId=541
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFMDEF
Language=Deutsch
Verweis ObjektMerkmalscode fehlerhaft
.

MessageId=540
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFIDEF
Language=Deutsch
Verweis ObjektIdentifikator fehlerhaft
.

MessageId=536
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOGIB
Language=Deutsch
GI nicht im GeometrieBaum
.

MessageId=535
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOREC
Language=Deutsch
Satz in der Datei ist gelˆscht
.

MessageId=530
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EWIKAN
Language=Deutsch
Winkel in Kante falsch
.

MessageId=529
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOKKF
Language=Deutsch
Kante in Kantenfolge nicht gefunden
.

MessageId=528
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EKPKFK
Language=Deutsch
Verweis vom Knoten zur Kantenfolge falsch
.

MessageId=527
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EASPK
Language=Deutsch
Anzahl der St¸tzpunkte einer Kante falsch
.

MessageId=526
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOKAF
Language=Deutsch
Kantenfolge fehlerhaft
.

MessageId=525
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EVEKSP
Language=Deutsch
Verweis kante zur St¸tzpunktfolge falsch
.

MessageId=524
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOVEK
Language=Deutsch
Verweis aus St¸tzpunktfolge in Kante falsch
.

MessageId=523
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFKVOL
Language=Deutsch
Verweis von Objekt zur Kante falsch
.

MessageId=522
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOVGO
Language=Deutsch
Verweis von der Geometrie zum Objekt falsch
.

MessageId=521
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFKFK
Language=Deutsch
Kantenfolgeliste fehlerhaft
.

MessageId=520
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENODEF
Language=Deutsch
Keine Objektdefinition
.

MessageId=512
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ESONFD
Language=Deutsch
Sekund‰robjekt nicht vorhanden
.

MessageId=511
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EPONFD
Language=Deutsch
Prim‰robjekt nicht vorhanden
.

MessageId=501
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EONDUP
Language=Deutsch
Objektnummer in Parameterfeld doppelt
.

MessageId=217
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOPAD
Language=Deutsch
Falsche Verzweigung angegeben
.

MessageId=216
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOKOM
Language=Deutsch
Kein Komplexobjekt
.

MessageId=213
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EANZON
Language=Deutsch
Anzahl der Maschenobjekte um Knotenpunkt falsch
.

MessageId=210
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EKANT
Language=Deutsch
Drei Kanten mit gleicher Objektnummer schneiden sich
.

MessageId=209
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EKAMA
Language=Deutsch
Falsche Liste, NKAL bzw. NMAL nicht gefunden
.

MessageId=207
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EZSPL
Language=Deutsch
Fehler in Zeiger SPL
.

MessageId=206
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EZAEL
Language=Deutsch
Fehler im Vergleich Z‰hler  LAEMAX(GIFelder)
.

MessageId=205
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EZKAL
Language=Deutsch
Zeiger KL darf nicht 0 sein
.

MessageId=204
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFFLA
Language=Deutsch
Fehler beim FF  Laden
.

MessageId=202
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOGD
Language=Deutsch
Fehler beim Erˆffnen der Grafik
.

MessageId=201
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EMAXL
Language=Deutsch
X,Y  Felder grˆﬂer als MAXL angegeben
.

MessageId=199
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ESTAND
Language=Deutsch
Fehlermeldung Standard
.

MessageId=198
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ESPEZ
Language=Deutsch
Fehlermeldung unterdr¸cken
.

MessageId=126
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRVZO
Language=Deutsch
E/A Fehler Verbindung Masche  inneres Objekt
.

MessageId=125
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRPOL
Language=Deutsch
E/A Fehler Punktliste
.

MessageId=124
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EMTEXT
Language=Deutsch
Modifikation von Text mit Funktionskennz. (D,M,B) nicht erlaubt
.

MessageId=123
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENPMI
Language=Deutsch
Kein Zeiger auf Merkmale
.

MessageId=122
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENPID
Language=Deutsch
Kein Zeiger auf Identifikator
.

MessageId=121
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EYPREL
Language=Deutsch
Relationen eingetragen
.

MessageId=120
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENPGI
Language=Deutsch
Kein Zeiger auf Geometrie
.

MessageId=118
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRVBD
Language=Deutsch
E/A Fehler Verbindungslisten allgemein
.

MessageId=117
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRKFM
Language=Deutsch
E/A Fehler Kantenfolge Maschen
.

MessageId=116
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRDBT
Language=Deutsch
E/A Fehler Textdatei
.

MessageId=115
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRVIO
Language=Deutsch
E/A Fehler Verbindungsdatei IdentifikatorObjekt
.

MessageId=114
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRIDL
Language=Deutsch
E/A Fehler Identifikatorliste
.

MessageId=111
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRMI
Language=Deutsch
E/A Fehler Merkmalsinformation
.

MessageId=110
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRMKL
Language=Deutsch
E/A Fehler Merkmalscodeliste
.

MessageId=109
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRVOM
Language=Deutsch
E/A Fehler Verbindungsdatei ObjektMerkmal
.

MessageId=108
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRVOL
Language=Deutsch
E/A Fehler Verbindungsliste ObjektLinie
.

MessageId=106
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRVGO
Language=Deutsch
E/A Fehler Verbindungsliste GeometrieObjekt
.

MessageId=105
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRKFL
Language=Deutsch
E/A Fehler Kantenfolge Knoten
.

MessageId=104
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRMAL
Language=Deutsch
E/A Fehler Maschenliste
.

MessageId=103
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRKPL
Language=Deutsch
E/A Fehler Knotenpunktliste
.

MessageId=102
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRSPL
Language=Deutsch
E/A Fehler St¸tzpunktliste
.

MessageId=101
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENRKAL
Language=Deutsch
E/A Fehler Kantenliste
.

MessageId=83
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ETYP
Language=Deutsch
Formattyp Merkmal in MI stimmt nicht mit Typ in DB ¸berein
.

MessageId=82
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EVDAT
Language=Deutsch
Generierungfehler in Verbindungsdatei
.

MessageId=80
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ESPO
Language=Deutsch
Zu teilendes Objekt ist keine Linie oder Fl‰che
.

MessageId=79
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ETP
Language=Deutsch
Teilungpunkt liegt nicht auf dem zu teilenden Objekt
.

MessageId=78
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EOSTA
Language=Deutsch
F¸r das neue Objekt wurde ein falscher Status vereinbart
.

MessageId=77
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFON
Language=Deutsch
Zu ¸berlagerndes Objekt hat falschen Status
.

MessageId=76
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EOBJF
Language=Deutsch
Angegebene Objektfolge falsch bzw. Objekt nicht in DB
.

MessageId=75
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EAPEP
Language=Deutsch
Anfangsbzw. Endpunkt nicht auf erstem bzw. letztem Objekt
.

MessageId=74
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EWIN
Language=Deutsch
Bei der Errechnung des Winkels einer Kante ist Divisor 0
.

MessageId=73
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EKLSPL
Language=Deutsch
Zugriffsfehler in SPL
.

MessageId=72
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EGEOV
Language=Deutsch
Feld f¸r Geometrieinf¸gung (X, YVektor, Zeigervektor) nicht ausreichend
.

MessageId=71
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EKTAB
Language=Deutsch
Feld (ktab) f¸r die Schnittinformationen nicht ausreichend
.

MessageId=70
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EFFO
Language=Deutsch
Ein als Fl‰che angegebenes Objekt ist kein geschlossener Polygonzug
.

MessageId=10
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOON
Language=Deutsch
Kein Objekt mit dieser Nummer gefunden
.

MessageId=9
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ESTAT
Language=Deutsch
Statusfehler des Objekts
.

MessageId=8
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENL
Language=Deutsch
Nachladeparameter falsch
.

MessageId=7
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOID
Language=Deutsch
Identifikator in DB nicht vorhanden
.

MessageId=6
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOMK
Language=Deutsch
Merkmalskode in DB nicht vorhanden
.

MessageId=5
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENOREL
Language=Deutsch
Relation in der DB nicht vorhanden
.

MessageId=3
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_ENODIM
Language=Deutsch
Dimension im Feld falsch ¸bergeben
.

MessageId=2
Severity=Error
Facility=TRiAS01
SymbolicName=TRIAS01_E_EPAFEH
Language=Deutsch
Parameter beim Funktionsaufruf falsch
.

MessageId=1
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WDHLG 
Language=Deutsch
Wiederholung des Aufrufs
.

MessageId=5
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNORELDB
Language=Deutsch
Relation in der DB nicht vorhanden
.

MessageId=6
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOMK
Language=Deutsch
Merkmalskode in DB nicht vorhanden
.

MessageId=7
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOID
Language=Deutsch
Identifikator in DB nicht vorhanden
.

MessageId=116
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WJTDBT
Language=Deutsch
Text bereits vorhanden
.

MessageId=120
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNPGI
Language=Deutsch
Kein Zeiger auf Geometrie
.

MessageId=123
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNPMI
Language=Deutsch
Kein Zeiger auf Merkmale
.

MessageId=203
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOEOK
Language=Deutsch
Objekt ist kein Elementarobjekt
.

MessageId=208
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOON
Language=Deutsch
Keine Objekte gefunden
.

MessageId=211
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WFORT
Language=Deutsch
Fortsetzung notwendig
.

MessageId=212
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNORIG
Language=Deutsch
Keine topologischen Relationen vorhanden
.

MessageId=214
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WFORTR
Language=Deutsch
Es folgt letzter Knotenpunkt, weiterer Fl‰chenrand folgt
.

MessageId=215
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WFORTI
Language=Deutsch
Folgende Objekte vˆllig in Fl‰che, bzw. voll ¸berdeckend
.

MessageId=500
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WRELEX
Language=Deutsch
Zu speichernde Relation schon vorhanden
.

MessageId=511
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WPONFD
Language=Deutsch
Prim‰robjekt nicht vorhanden
.

MessageId=512
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WSONFD
Language=Deutsch
Sekund‰robjekt nicht vorhanden
.

MessageId=513
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WPONOD
Language=Deutsch
Prim‰robjekt ist nicht definiert
.

MessageId=514
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WSONOD
Language=Deutsch
Sekund‰robjekt ist nicht definiert
.

MessageId=565
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WOBKTR
Language=Deutsch
Objekt besitzt keine thematischen Relationen
.

MessageId=600
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WLINE
Language=Deutsch
Polygonzug nicht geschlossen (Linie)
.

MessageId=601
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WAREA
Language=Deutsch
Fl‰che, aber nicht umorientiert
.

MessageId=611
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WUMOR
Language=Deutsch
Fl‰che, mindestens eine Konturorientierung wurde korrigiert
.

MessageId=700
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WDUMMY
Language=Deutsch
Kein Fehler, aber Ret-Value !=  S_OKAY
.

MessageId=701
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNTFND
Language=Deutsch
Keine Datens‰tze vorhanden
.

MessageId=702
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WDUPL
Language=Deutsch
Bereits vorhandener Schl¸ssel soll in einzigartiges Feld gespeichert werden
.

MessageId=703
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOFIL
Language=Deutsch
Datenbasis enth‰lt keine Dateien
.

MessageId=704
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_VERSIO
Language=Deutsch
Falsche Versionsnummer
.

MessageId=730
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WBADMK
Language=Deutsch
Falscher Merkmalstyp
.

MessageId=731
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_TEXTTO
Language=Deutsch
Merkmalstext zu lang
.

MessageId=732
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_MKODEE
Language=Deutsch
Merkmals-Kode existiert bereits f¸r dieses Objekt
.

MessageId=733
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_BADREL
Language=Deutsch
Falscher Relations-Typ
.

MessageId=734
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_DUPLBR
Language=Deutsch
Doppeltes Begleitobjekt
.

MessageId=735
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_DUPLRE
Language=Deutsch
Doppelte Relation
.

MessageId=750
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_BADCOO
Language=Deutsch
Koordinaten auﬂerhalb des g¸ltigen Bereiches
.

MessageId=1005
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WSBNO
Language=Deutsch
Symbol in der PBD nicht vorhanden
.

MessageId=1010
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNRECI
Language=Deutsch
Satznummer f¸r die Identifikatordatei (PBD) nicht vorhanden
.

MessageId=1011
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNRECR
Language=Deutsch
Satznummer f¸r die Relationsartendatei (PBD) nicht vorhanden
.

MessageId=1012
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WIDLNO
Language=Deutsch
Identifikator in PBD nicht vorhanden
.

MessageId=1013
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WRELNO
Language=Deutsch
Relation in der PBD nicht vorhanden
.

MessageId=1014
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WMKLNO
Language=Deutsch
Merkmal in der PBD nicht vorhanden
.

MessageId=1015
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNRECM
Language=Deutsch
Satznummer f¸r die Merkmalsdatei der PBD nicht vorhanden
.

MessageId=1016
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNRECS
Language=Deutsch
Recordnummer f¸r Symboldatei (PBD) nicht vorhanden
.

MessageId=1017
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WTYPR
Language=Deutsch
Einspeicherung des Merkmalswertes nicht mˆglich, MW-Typ ist REAL
.

MessageId=1018
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNRECW
Language=Deutsch
Satznummer f¸r die Merkmalswertedatei in der PBD nicht vorhanden
.

MessageId=1200
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOTAP
Language=Deutsch
Dateianh‰ngen wird bei Export nicht unterst¸tzt
.

MessageId=1600
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNORELOBJ
Language=Deutsch
Relation ist am Objekt nicht vorhanden
.

MessageId=1699
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOVAL
Language=Deutsch
Wert existiert nicht
.

MessageId=1700
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOTXT
Language=Deutsch
Kein Objekt mit Merkmal entsprechend Suchtext gefunden
.

MessageId=1701
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WCNLIB
Language=Deutsch
Druckertreiber nicht auffindbar
.

MessageId=1702
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WEXIST
Language=Deutsch
Datei existiert bereits
.

MessageId=1703
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WMMATC
Language=Deutsch
Nichtentsprechung bei dBASE-relevaten Merkmalskodes
.

MessageId=1704
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WRNOTF
Language=Deutsch
Kein Objekt entsprechend Recherchekriterien gefunden
.

MessageId=1705
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WBADCM
Language=Deutsch
Unbekannte Kommandozeilenoption
.

MessageId=1706
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOTEX
Language=Deutsch
Objekt ist kein Text-Objekt
.

MessageId=1707
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WTEXTO
Language=Deutsch
Objekt ist ein Text-Objekt
.

MessageId=1708
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WMULTR
Language=Deutsch
Komplexobjekt besitzt mehrere Komplexrelationen
.

MessageId=1709
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOKOR
Language=Deutsch
Komplexobjekt besitzt keine Komplexrelation
.

MessageId=1710
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOTMK
Language=Deutsch
Bezugsobjekt hat keinen Text f¸r Textobjekt
.

MessageId=1711
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WBADRC
Language=Deutsch
Komplexobjekt soll unterschiedliche Relationscodes enthalten
.

MessageId=1712
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOKO
Language=Deutsch
Komplexobjekt kann nicht gebildet werden
.

MessageId=1713
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOASS
Language=Deutsch
Abh‰ngiger Textobjekt hat kein Bezugsobjekt
.

MessageId=1717
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOVIT
Language=Deutsch
Textobjekt hat keine Visualisierungsinformation
.

MessageId=1718
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOVIF
Language=Deutsch
Fl‰chenobjekt hat keine Visualisierungsinformation
.

MessageId=1719
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOVIL
Language=Deutsch
Linieobjekt hat keine Visualisierungsinformation
.

MessageId=1720
Severity=Informational
Facility=TRiAS01
SymbolicName=TRIAS01_S_WNOVIP
Language=Deutsch
Punktobjekt hat keine Visualisierungsinformation
.

MessageId=2000
Severity=Warning
Facility=TRiAS01
SymbolicName=WC_DATASOURCE_ISRO
Language=Deutsch
Datenquelle ist schreibgesch¸tzt.
.

MessageId=2001
Severity=Warning
Facility=TRiAS01
SymbolicName=WC_METADATA_ISRO
Language=Deutsch
Beschreibungsdaten sind schreibgesch¸tzt (Datenbankschema kann nicht modifiziert werden).
.

MessageId=2002
Severity=Warning
Facility=TRiAS01
SymbolicName=WC_CLASS_ISRO
Language=Deutsch
Die Objektklasse (Tabelle) ist schreibgesch¸tzt.
.

MessageId=2003
Severity=Warning
Facility=TRiAS01
SymbolicName=WC_FEATURE_ISRO
Language=Deutsch
Objekteigenschaft ist schreibgesch¸tzt.
.

;#endif // _TRiAS01_HMC
