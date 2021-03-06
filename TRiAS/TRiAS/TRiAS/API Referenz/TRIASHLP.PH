(Kurztext)
(Message
(Objektnummer,
(Schl�ssel)
(Text-)Merkmal
(_MAX_PATH
(bzw.
(indem
(void)
(z.B.
) an die zu rufende Funktion
) die Gr��e des Textpuffers sowie nach dem Aufruf die L�nge des gelesenen Textes. Beim Schreiben (Message
) enth�lt dieses Feld die L�nge der zu schreibenden Zeichenkette.
) mu�
) wird hier d
) �bergebene 2. Parameter
, DEX_ENUM
, DEX_ENUMVIEWIDENTS
, DWORD
, anderenfalls und im Fehlerfall
, bool
, der
, die die notwendigen Informationen enth�lt.
, im Fehlerfall
, void *
, welche
, wenn die Diagnose-Notifikationen bereits erlaubt waren, und
, wenn nicht).
- Wert,
- Wert, also im Normalfall
- Wert, wenn das gegebene Objekt zur Sicht geh�rt
-Schl�ssel
-Wert, also im Normalfall
-Wert, der Auskunft dar�ber gibt, ob
-Wert, der angibt, ob der aktuelle Nutzer �ber erweiterte Zugriffsrechte verf�gt
. Das Feld
. Wird die Enumeration durch die Enumerationsfunktion abgebrochen (indem diese Funktion
.Wenn die gegebene Ansicht bereits im aktuellen Projekt existiert, dann
Abbruch
Abfragen de
Abh�ngigkeit
Abschlu�
Aktion
Aktionen
Aktivierung
An TRiAS� durchzureichende Daten.
An die R�ckruffunktion als 3. Parameter durchzureichende Daten.
An die gerufene Funktion durchgereichte Daten.
An dieser Stelle
Ansicht
Ansichtmerkmal.
Ansichtnamen
Ansonsten
Anzahl
Aufruf
Auskunft
Bearbeitung
Bedeutung
Bei dieser Enumeration wird der Objekttyp
Beim
Beim Lesen (Message
Bemerkungen
Ber�cksichtigung
Beschreibung
Beschreibungs-Datenbasis
Bezugssicht
Bitmap
COPYGEOMETRIE
CObjectpropertyExtension
CTriasExtension
CTriasExtension::InitExtension
CTriasExtension::MenuInit
CTriasExtension::RegisterNotification
CTriasExtension::UnRegisterNotification
DEX_AddIdentFromView
DEX_AddIdentToView
DEX_CreateView
DEX_CreateViewOpt
DEX_DELETEIDENT
DEX_DELETEIDENTFROMVIEW
DEX_DIAGNOSTICSENABLE
DEX_DRAWIDENT
DEX_DRAWOBJECT
DEX_DeleteAllIdentObjects
DEX_DisableDiagnostics
DEX_ENUMALLIDENTS
DEX_ENUMALLSIGHTS
DEX_ENUMEXTENSIONPROP
DEX_ENUMIDENTOBJS
DEX_ENUMMERKMALE
DEX_ENUMMERKMALEEX
DEX_ENUMMERKMALEIDENT
DEX_ENUMMERKMALESICHT
DEX_ENUMTEXTMERKMALRECH
DEX_ENUMVIEWIDENTS
DEX_EnableDiagnostics
DEX_EnumIdentMerkmale
DEX_EnumIdentObjects
DEX_EnumIdents
DEX_EnumObjektMerkmale
DEX_EnumRechTextMerkmal
DEX_EnumSichtMerkmale
DEX_FINDIDENTFROMNAME
DEX_FINDOBJFROMNAME
DEX_GetActiveProject
DEX_GetActiveSight
DEX_GetActiveUser
DEX_GetDBVersion
DEX_GetIdentFromClassName
DEX_GetMainIniName
DEX_GetONrFromObjName
DEX_GetObjNameMCode
DEX_GetObjectName
DEX_GetROMode
DEX_GetTextMerkmal
DEX_GetUniqueIdentMCode
DEX_GetUnknownIdent
DEX_HASPROJECTVIEW
DEX_HASVIEWIDENT
DEX_HASVIEWOBJECT
DEX_HEADERREREAD
DEX_IDENTADDTOVIEW
DEX_INITEXTENSION
DEX_INVOKEOBJPROPFUNC
DEX_InstallMenuItem
DEX_InstallTool
DEX_LOADEXTENSION
DEX_MENUINIT
DEX_MENUITEMINSTALL
DEX_MENUITEMREMOVE
DEX_MODIFYMERKMAL
DEX_MODIFYOBJGEOMETRIE
DEX_ModObjectName
DEX_ModTextMerkmal
DEX_OpenProject
DEX_PROJECTOPEN
DEX_ProjectHasView
DEX_QUERYACTIVEPROJECT
DEX_QUERYACTIVESIGHT
DEX_QUERYACTIVEUSER
DEX_QUERYADMINMODE
DEX_QUERYGEODBVERSION
DEX_QUERYMAINININAME
DEX_QUERYOBJECTNAME
DEX_QUERYOBJNAMEMCODE
DEX_QUERYROMODE
DEX_QUERYTEXTMERKMAL
DEX_QUERYUNIQUEIDENTMCODE
DEX_QUERYUNKNOWNIDENT
DEX_QueryMode
DEX_QueryUnknownIdent
DEX_ReReadHeader
DEX_RemoveIdentFromView
DEX_RemoveMenuItem
DEX_RemoveTool
DEX_RenameView
DEX_SELNEWSIGHT
DEX_SETADMINMODE
DEX_SETOBJECTNAME
DEX_SetMode
DEX_TOOLINSTALL
DEX_TOOLREMOVE
DEX_UNLOADEXTENSION
DEX_VIEWCREATE
DEX_VIEWRENAME
DEX_ViewHasIdent
DEX_ViewHasObject
DO_
DRAWOBJECT
DT_HasNewVI
DT_Normal
DT_WillDrawComplete
DWORD
DWORD dwSize;
DWORD eData;
DWORD m_dwSize;
Darstellung
Darstellungs
Darstellungsattribute
Das
Das Feld
Dateiname
Daten
Daten.
Datenbasis
Datenstruktur
Definition
Der
Der Name de
Der Name der neu zu erzeugenden Sicht.
Der Objektname
Der Objektname eines Objektes ist ein Merkmalswert, welcher f�r ein Objekt unter einem speziellen Merkmalscode abgelegt ist. Dieser Merkmalscode wird z.Zt. spezifisch f�r den Identifikator eines Objektes �ber die Initialisierungsdatei des aktuellen Proje
Der R�ckgabewert enth�lt
Der R�ckgabewert enth�lt d
Der R�ckgabewert enth�lt den gesuchten Merkmalscode bzw. Null im Fehlerfall.
Der aktuelle Wert der zu enumerierenden Eigenschaft (Objektnummer, Merkmalscode o.�.).
Der an die zu rufende Funktion (
Diagnose-
Diagnose-Notifikationen
Die
Die Erweiterung
Die Erweiterung soll lediglich initialisiert werden. Es darf kein Nutzerinterface installiert werden (z.B. zus�tzliche Menupunkte).
Die Erweiterung soll nicht geladen werden
Die Erweiterung soll vollst�ndig initialisiert werden. Das Nutzerinterface darf installiert werden.
Die Gr��e dieser Struktur.
Die Implementation der Standard-Basisklasse
Die Notifikation erfolgt im Zu
Die Objektnummer
Die Programmierschnittstelle von TRiAS(R)
Die an dieser Stelle �bergebenen Daten sind spezifisch f�r jede konkrete Message und jeweils dort beschrieben.
Die im Feld
Diese
Diese Datenstruktur unterscheidet sich von der Struktur
Diese Datenstruktur wird verwendet, um eine Enumeration
Diese Datenstruktur wird verwendet, um eine Erweiterung aufzufordern,
Diese Message
Diese Message ben�tigt keine Parameter.
Diese Message liefert den Wert von lParam, wenn kein Fehler aufgetreten ist. Wenn kein aktives Projekt existiert
Diese Message liefert einen
Diese Message wird
Diese Message wird durch die Funktion
Diese Notifikation
Diese S
Diese Struktur wird
Diese Struktur wird im Zusammenhang mit de
Dieser
Dieser Merkmalscode ist als Identifikatormerkmalscode registriert.
Dieser Merkmalscode ist als Objektmerkmalscode registriert.
Dieser Merkmalscode ist als Sichtmerkmalscode registriert.
Dieser Merkmalscode ist als Systemmerkmal registriert.
Dieser Wert
Dieser Wert gibt an, ob der aktuelle Aufruf der Funktion nicht der letzte in dieser Enumeration ist.
Dieses
Dieses Feld mu� die Objektnummer, den Identifikator oder einen Zeiger auf den Ansichtnamen enthalten, f�r den/die das Merkmal behandelt werden soll. Dieses Feld wird in Abh�ngigkeit vom Feld
Dokument
Durch die Enumeration zu rufende Funktion
Durch diese Message werden lediglich die Merkmale enumeriert, die in der Beschreibungs-Datenbasis als Objektmerkmale registriert sind und keine Systemmerkmale sind. Werden alle Merkmale ben�tigt, so mu� die Message
Durchzureichende Daten.
EC_OKAY
ENUMLONGKEY
ENUMLONGKEYCALLBACK
ENUMLONGKEYEX
ENUMLONGKEYPROC eFcn;
ENUMNOKEY
ENUMNOKEYCALLBACK
ENUMNOKEYLONG
ENUMNOKEYLONGCALLBACK
ENUMOBJPROPCALLBACK
ENUMOBJPROPDATA
ENUMRECHTEXTMERKMAL
ENUMTEXTKEY
ENUMTEXTKEYCALLBACK
ENUMTEXTKEYEX
ENUMTEXTKEYEXCALLBACK
Eigenschaft
Ein Zeiger auf eine Struktur vom Typ
Ein mit DEX_
Eine Erweiterung sollte
Einsatz
Eintr�ge
Elemente de
Enable-Flags
Enfern
Enth�lt
Enth�lt beim Lesen einen Zeiger auf den Pufferbereich, in dem das gelesene Merkmal abgelegt werden soll, beim Schreiben den neuen Merkmalstext.
Enth�lt beim Lesen eines Merkmales (Message
Enth�lt d
Enth�lt den Merkmalscode des zu behandelnden Merkmales.
Enth�lt die Information, ob es sich um ein Merkmal eines Objektes, eines Identifikators oder einer Ansicht handelt. Es kann folgende Werte enthalten
Enumeration
Enumerationsfunktion
Enumerieren aller Identifikator
Enumerieren aller Merkmale eine
Enumerieren aller Objekt
Enumertaion
Ergebnispuffer
ErrCode
Erweiterung
Er�ffnen
Es 
Es handelt sich um ein Ansichtmerkmal.
Es handelt sich um ein Objektmerkmal.
Es handelt sich um ein identifikatormerkmal.
Es sollen zus�tzliche alle Merkmale enumeriert werden, die in der Beschreibungs-Datenbasis als Systemmerkmale gekennzeichnet sind.
Es sollten nur
Es werden alle Objekte geliefert, d
Es wird ein
Exist
Fall
Farbwert
Fehler
Fehlerfall
Feld
Felder
Fernerkundungszentrum
Flag
Fl�chenobjekte
Funktion
Funktionen
Funktionsaufruf
Generierung
GmbH
Gr��e
Gr��e dieser Struktur
HDEX hDex;
HMENU
Handle
Hauptfenster
Headereintr
Hilfe
INSTALLDATA
INSTALLMENUITEM
INSTALLTOOL
INVOKEOBJPROPDATA
Ident
Identifikation
Identifikator
Identifikator, f�r dessen Objekte der Merkmalscode gesucht wird.
Identifikator/Objekttyp-
Identifikatoren
Identifikatormerkmal
Identifikators
Im Unterschied zur Message
Implementation
Information
Informationen
Inhalt
Initialisierung
Initialisierungsdatei
Interface-Beschreibungen
Klassen
Klassenmember
Kombination
LEFullLoad
LEInitOnly
LENoLoad
LPARAM lTarget;
Legt eine neue Ansicht unter dem gegebenen Sichtnamen an. Wenn diese Ansicht bereits existiert,
Lesen
Liefert
Liefert bei erfolgreichem Abschlu� der Aktion
Liefert d
Liefert den vorhergehenden Zustand des Enable-Flags (
Liefert einen
Liefert f�r das aktuelle Projekt
Liefert im Normalfall
Linie
L�nge
L�schen
MPAllFeatures
MPIdentFeature
MPObjectFeature
MPSystemFeatures
MPViewFeature
Makro's
Member
Menu
Menupunkt
Merkmal
Merkmale
Merkmals-
Merkmalscode
Merkmalstext
Merkmalswert
Message
Messages
Mit dieser Message an TRiAS�
Mit dieser Message an TRiAS� ist es m�glich
Mit dieser Message an TRiAS� ist es m�glich Merkmale eines Objektes, eines Identifikators oder einer Ansicht zu
Mod
Mode
Module
NULL
NULL,
NULL.
Nach
Name
Namen
Normalfall
Normalmodus,
Notifikation
Notifikationen
Null
Nummer des PopupMenus,
Nutzer
Nutzerinterface
Nutzername
Nutzeroberfl�che
Nutzers
OBJCREATE
OBJECTFEATURE
OBJGEOMETRIE
OM_
OTFlaeche
OTLinie
OTPunkt
OTText
ObjProp::InvokeFunc
Objekt
Objekt- und Interface-Beschreibungen
Objekte
Objekteigenschaft
Objektes
Objektes,
Objektes.
Objektgeometrien
Objektklasse
Objektmerkmal
Objektmethoden
Objektname
Objektnummer
Objektrecherche
Objektrecherche-Fenster
Objekttyp
Offset
Parameter
Pfadnamen
Pointer
PopupMenus,
Popupmenu
Pots
Programm
Programmierschnittstelle
Projekt
Projektes
Puffer
Pufferbereich,
Pufferbereich, in dem der Name zur�ckgeliefert werden soll.
Punkt
RECHTEXTMERKMALCALLBACK
REMOVEMENUITEM
RENAMEVIEW
Recherche
Referenz auf Struktur vom Typ
Referenz einer Struktur vom Typ
R�ck
R�ckgabewert
R�ckruf-Funktion, die durch eine Erweiterung installiert werden mu�, wenn eine Enumeration �ber einen
R�ckruffunktion
Schl�ssel
Schreib
Schreiben
Schreibzugriff
Sicht
Sicht.
Sichtmerkmale
Sichtmerkmalscode
Sichtname
Sie
Siehe auch
Speicher
Standard
Standard-Basisklasse
Standardansicht,
Stelle
Stellt fest, ob
Struktur
Struktur.
Strukturen
Strukturmember
Such
Suchschl�ssel, �ber den zu enumerieren ist.
System
Systemmerkmal
TARGETMERKMAL
TEXTGEOMETRIE
TRIASLOADEX
TRIAS_OPEN
TRiAS(R)
TRiAS�
TRiAS� liefert
TRiAS� liefert das Handle des Popupmenus, in dem der Menupunkt installiert wurde, wenn kein Fehler aufgetreten ist. Ansonsten ist der R�ckgabewert NULL.
TT_Identifikator
TT_Objekt
TT_Sicht
Text
Text-Schl�ssel
Textes.
Textmerkmal
Textobjekte
Textpuffers
Typ
ULONG
Unique
Unterschied
VIEWCREATED
VIEWIDENTOBJECT
Verhalten
Versionsnummer
Ver�nderung
Wenn
Werden
Werkzeug
Wert
Wert,
Werte
Windows
Wird
XTENSION.H
XTENSND.H
XTENSNN.H
XTENSNX
Zeichen
Zeichenkette
Zeichenkette, die den Namen der neu zu erzeugenden Ansicht enth�lt.
Zeichenkettenpuffer
Zeiger
Zu registrierende R�ckruffunktion.
Zugriffsrechte
Zusammenhang
Zustand
Zus�tzliche Parameter f�r die Enumeration. Die Bedeutung dieser Parameter ist abh�ngig von der konkreten Enumeration und jeweils dort beschrieben.
abge
abgebrochen
abgefragt
abgelegt
abh�ngig
abzufragen
aktiv
aktuelle
aktuellen
aktuelles
alle
aller
allgemeinen
als
also
an TRiAS� liefert, so ist der R�ckgabewert der Message ebenfalls
an,
anderen
anderenfalls
angefordert
angegeben
angelegt
angezeigt
angibt,
annehmen:
ansonsten
antworten:
anzeigen.
anzuzeigen
auch
auf
aufgetreten
aufzufordern,
aus
ausgef�hrt
ausgel�st und ist nur unter WindowsNT und Windows 95 verf�gbar.
ausgel�st.
ausgenullt
ausgew�hlt
beantwortet)
bearbeitende
bearbeitet
bearbeitet diese Message vollst�ndig.
beeinflu
behandeln
behandelnden
behandelt
behandelt diese Message.
bei
beim
belegt
ben�tigt
bequemen
ber
berechne
bereits
beschreib
beschrieben.
beschr�nkt
besitzen
besitzt.
besondere
bestimmte
betreffen
bevor
bool
bzw.
bzw. im Fehlerfall NULL.
char
char *
char * p
char m_sz
const char * m_p
d.h.
dann
darf
dargestellt
dar�ber
das
davon,
dazu
definiert
dem
den
den zu untersuchenden Identifikator und das Feld
den/die
der
der Struktur
deren
derzeit
des
dessen
die
diese
diesem
dieser
dieses
diverse
dort
durch
durchgef�hrt
durchgereichte
durchzuf�hren
durchzureichende
dwData
dwSize
dwSize;
eData
eFcn
eFcn;
eKey
ePtr
ePtr;
ebenfalls
eigentliche
ein
eine
eine Kombination der zu behandelnden Objekttypen. Das Feld
eineindeutig
einem
einen
einer
eines
einge
eingeh�ngt
eingelesen
eingesetzt werden.
einheitlichen
einmal
einzeln
einzu
entfernen
entfernt
enthalten
enth�lt
enth�lt die zu bearbeitende Ansicht (bzw. NULL, f�r die aktuelle Ansicht), das Feld
enth�lt,
enth�lt.
entladen
entsprechen
enumerieren
enumerierenden
enumeriert
erfolgreich
erfolgreichem
erfolgt
erfragen
erhalten
erlaubt
erste
erweiterte
erzeugen
erzeugenden
erzeugt
er�ffne
etc.)
evtl.
exist
existiert
existiert,
fNotLast
false
fest,
festgelegt.
finden.
folgende
fortgesetzt
frei
freigegeben
f�r
gefundene
gegeben
gegebene
gegebenen
gegebenes
geh�ren
geh�rt
gekennzeichnet
geladen
gelesene
geliefert
gel�scht
generiert
genu
gen�gt
gerufen
gesamte
geschickt,
gesucht
gesuchten
gew�nschten
gezeichnet
ge�ffnet
gibt
gibt,
gleich NULL
gro�
hDex
haben.
halten
handelt
heraus
hier
iBuffLen
iFlag
iFuncID
iMenuID
iMenuNum
iMenuPos
iMode
iNotLast
iObjTyp
iTTyp
iToolID
identi
identifikatormerkmal.
ignoriert.
ihre
ihrerseits
imaxLen
implemented
initialisier
installieren
installiert
interne
interpretiert
ist
ist es m�glich alle Merkmale zu enumerieren, die der vorgegebene Identifikator besitzt.
ist,
ist.
jede
jedoch
jeweils
kann
kann folgende Werte oder eine Kombination dieser annehmen:
kann f�r diese Message einen der folgenden Werte oder deren Kombination annehmen:
kein
keine
klassifizierte
konkrete
ktes festgelegt.
k�nnen
lIdent
lMCode
lONr
lObjNr
lParam
lParam enth�lt einen Pointer auf eine Struktur vom Typ
lParam enth�lt einen Zeichenkettenpuffer, der gro� genug sein mu�, um einen
lParam zeigt auf eine Struktur vom Typ
lParam,
lTarget
lValue
laufenden
lediglich
lediglich durch den Typ der vorzugebenden R�ckruffunktion.
leitet diese Message an die
lesen
letzte
liefern, wenn die Enumertaion fortgesetzt werden soll. Im Fehlerfall oder wenn die Enumeration abgebrochen werden soll, mu� diese Funktion
liefern, wenn diese Message bearbeitet w
liefern.
liefert
liefert,
long
long eKey;
long lIdent;
long lMCode;
long lO
long m_lONr;
lpPassWord
lpProject
lpUser
l�schen
m_dwSize
m_fFlags
m_fcDef
m_hMenu
m_hORMenu
m_iLen
m_iMode
m_iOTyp
m_lIdent
m_lONr
m_pMText
m_pNewName
m_pOldName
m_pTarget
m_pView
m_szMenuName[DEX_MENUNAMELEN]
m_szORMenuName[DEX_MENUNAMELEN]
m_wMenuDelta
mach
mehrere
mit
modifizier
modifiziert
mu�
mu� vor dem Aufruf der Message mit dem Namen der zu behandelnden Ansicht belegt werden.
mu� vor dem Aufruf der Message mit dem zu untersuchenden Identifikator belegt werden.
mu� vor dem Aufruf der Message mit der Objektnummer des zu behandelnden Objektes belegt werden.
mu�,
m�glich
m�ssen
nach
neu
neue
neuen
nicht
nicht.
normal
notwendigen
nur
o.�.).
oder
ohne
pBuff
pClassName
pData
pEnum
pEnumLongKey
pFName
pFunc
pIniName
pInstall
pMText
pMWert
pMenuText
pNewVI
pObjFeature
pObjName
pProjectName
pPtr
pTargetFeature
pUserName
pValue
pView
pViewIdentObject
pViewName
rEnumLongKey
rEnumNoKey
rEnumTextKey
rInstallItem
rInstallTool
rObjFeature
rRechTextMerkmal
rRemoveItem
rRenameView
rTargetFeature
rViewIdentOTyp
registrier
registriert.
riewIdentOTyp
rufende
schlie�en.
schreiben
sein
selbst
setzen
short
short i
short iFlag
short iMenu
short imaxLen;
short m_
sich
sind
sind.
soll
soll,
soll.
sollen
sollte
soory).
sowie
spezielle
spezifisch
struct
tag
true
typedef struct tag
umbenannt
umzubenennen
unabh�ngig
und
und Fehlerfall
und im Fehlerfall oder bei Abbruch der Enumeration
ungleich
unter
unterscheidet
unterst
untersuchenden
verf�gbar.
verf�gt
vers
verschickt
verwandten
verwendet
verwendet,
verwendet, um ein Merkmal eines Objektes, eines Identifikators oder einer Ansicht zu lesen, zu schreiben oder zu l�schen.
ver�nder
void
void * ePtr;
void * p
volle
vollst�ndig
vom
von
vor
vorg
vorgeben
vorgegeben
vorgegebenen
vorgegebenen Daten werden ohne Ver�nderung als 3. Parameter (
vorgegebenes
vorher
vorherge
vormerken
vorzugebenden
wParam
waren,
weiter
welche
welches
wenn
werden
werden,
werden.
wesentlichen
wieder
wieder entfernt werden, bevor diese entladen wird.
wird
wird ignoriert.
wird,
wird.
worden
wurde
wurde mit
w�hlen
w�hrend
zeigt
zugeh�rigen
zur
zur�ckgeliefert
zus�tzlich
zus�tzliche
�ber dieses Dokument
�bersichten
�bertragung
�ber
�bergeben
�bergeben und k�nnen durch die Erweiterung frei belegt werden.
�bergebene
