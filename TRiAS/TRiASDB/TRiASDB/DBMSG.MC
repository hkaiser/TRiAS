;///////////////////////////////////////////////////////////////////////////////
;// Messages for TRiASDB
;// SourceFile: DBMSG.MC
;
;#if !defined(_DBMSG_H)
;#define _DBMSG_H
;
;#if _MSC_VER >= 1000
;#pragma once
;#endif // _MSC_VER >= 1000
;

SeverityNames = (
	Success = 0x0:STATUS_SEVERITY_SUCCESS
	Informational = 0x1:STATUS_SEVERITY_INFORMATIONAL
	Warning = 0x2:STATUS_SEVERITY_WARNING
	Error = 0x3:STATUS_SEVERITY_ERROR
)

FacilityNames = (
	System = 0x0FF
	NativeDB = 0xF00:FACILITY_NATIVEDB	; Fehler des unterliegenden Datenbanksystems
	DBEngine = 0xF01:FACILITY_DBENGINE	; Fehler des TRiASDB-Layers
	Project = 0xF02:FACILITY_PROJECT	; Fehler im Project Objekt
	Database = 0xF03:FACILITY_DATABASE	; Fehler im Database Objekt
	Connection = 0xF04:FACILITY_CONNECTION	; Fehler im Connection Objekt
	Property = 0xF05:FACILITY_PROPERTY	; Fehler im Property Objekt
	View = 0xF06:FACILITY_VIEW			; Fehler im View Objekt
	Object = 0xF07:FACILITY_OBJECT		; Fehler im Object Objekt
	Objects = 0xF08:FACILITY_OBJECTS	; Fehler im Objects Objekt
	Feature = 0xF09:FACILITY_FEATURE	; Fehler im Feature Objekt
	Features = 0xF0A:FACILITY_FEATURES	; Fehler im Features Objekt
	GenPurpose = 0xF0F:FACILITY_GENPURPOSE	; Allgemeiner Fehler 
)

LanguageNames = (
	Deutsch=0x407:MSG00407
	English=0x409:MSG00409
)

MessageIdTypedef=HRESULT

;
MessageId=0x1001
Severity=Error
Facility=Database
SymbolicName=TRIASDB_E_DATABASE_NOT_OPENED
Language=Deutsch
Datenbank ist nicht geöffnet.
.

Language=English
Database was not opened.
.

;
MessageId=0x1001
Severity=Error
Facility=Project
SymbolicName=TRIASDB_E_PROJECT_NOT_OPENED
Language=Deutsch
Das Projekt ist nicht geöffnet.
.

Language=English
The project workspace was not opened.
.

;
MessageId=0x1002
Severity=Error
Facility=DBEngine
SymbolicName=TRIASDB_E_INVALID_PARAMETER
#if defined(_DEBUG)
Language=Deutsch
Ungültiger Parameter in Routine '%2'.
.

Language=English
Invalid parameter in routine '%2'.
.
#else
Language=Deutsch
Ungültiger Parameter.
.

Language=English
Invalid parameter.
.
#endif // _DEBUG

;
MessageId=0x1003
Severity=Error
Facility=NativeDB
SymbolicName=TRIASDB_E_ERROR_NATIVEDB
Language=Deutsch
Fehler im unterliegenden Datenbanksystem.
.

Language=English
Error in underlying database system.
.

;
MessageId=0x1004
Severity=Error
Facility=NativeDB
SymbolicName=TRIASDB_E_COULD_NOT_OPEN
Language=Deutsch
Datenbank konnte nicht geöffnet werden.
.

Language=English
Could not open database.
.

;
MessageId=0x1005
Severity=Informational
Facility=Database
SymbolicName=TRIASDB_W_ALREADY_OPENED
Language=Deutsch
Die Datenbank ist bereits geöffnet.
.

Language=English
The Database was already opened.
.

;
MessageId=0x1006
Severity=Error
Facility=DBengine
SymbolicName=TRIASDB_E_NOT_STARTED
Language=Deutsch
Das Datenbanksystem wurde nicht initialisiert.
.

Language=English
DBEngine is not initialized or started.
.

;
MessageId=0x1007
Severity=Error
Facility=DBengine
SymbolicName=TRIASDB_E_FILENOTEXISTS
Language=Deutsch
Die angegebene Datei existiert nicht.
.

Language=English
File not exists.
.

;
MessageId=0x1008
Severity=Informational
Facility=DBengine
SymbolicName=TRIASDB_S_MUSTOPENASCOPY
Language=Deutsch
Die angegebene Datei ist schreibgeschützt und muß als Kopie geöffnet werden.
.

Language=English
File is readonly and must be copied to open.
.

;
MessageId=0x1009
Severity=Error
Facility=Connection
SymbolicName=TRIASDB_E_MISSINGPARAMETER
Language=Deutsch
Die gewünschte Verbindung zu einer Datenquelle konnte auf Grund fehlender Parameter nicht hergestellt werden.
.

Language=English
The connection could not be established. Missing parameter.
.

;
MessageId=0x100a
Severity=Error
Facility=DBengine
SymbolicName=TRIASDB_E_NOTAPROJECT
Language=Deutsch
Die angegebene Datei ist kein TRiAS Projekt.
.

Language=English
File is not a TRiAS project.
.

;
MessageId=0x100b
Severity=Warning
Facility=DBengine
SymbolicName=TRIASDB_W_NEWERPROJECT
Language=Deutsch
Das angegebene TRiAS Projekt hat ein zu neues Format. Das Projekt kann daher nicht geöffnet werden.
.

Language=English
The specified TRiAS project has a newer file format. The project could not be opened.
.

;
MessageId=0x100c
Severity=Error
Facility=Connection
SymbolicName=TRIASDB_E_ALREADYCONNECTED
Language=Deutsch
Die gewünschte Operation ist nicht ausführbar, da bereits eine Datenbank angebunden ist.
.

Language=English
The required operation could not be finished successfull. The connection is already established.
.

;
MessageId=0x100d
Severity=Error
Facility=Connection
SymbolicName=TRIASDB_E_NOTCONNECTED
Language=Deutsch
Die gewünschte Operation ist nicht ausführbar, da keine Datenbank angebunden ist.
.

Language=English
The required operation could not be finished successfull. The connection is not established.
.

;
MessageId=0x100e
Severity=Error
Facility=Property
SymbolicName=TRIASDB_E_PROPERTY_NOT_INITIALIZED
Language=Deutsch
Dieses Propertyobjekt ist nicht initialisiert.
.

Language=English
The propertyobject is not initialized.
.

;
MessageId=0x100f
Severity=Error
Facility=Property
SymbolicName=TRIASDB_E_UNKNOWN_PROPERTY
Language=Deutsch
Diese Property (Eigenschaft) ist nicht verfügbar.
.

Language=English
The requested property is not available.
.

;
MessageId=0x100f
Severity=Error
Facility=DBEngine
SymbolicName=TRIASDB_E_CANNOTSAVE_AT_THIS_POINT
Language=Deutsch
Das Projekt kann zu diesem Zeitpunkt nicht gespeichert werden.
.

Language=English
The project cannot be saved at this moment.
.

;
MessageId=0x1010
Severity=Error
Facility=DBEngine
SymbolicName=TRIASDB_E_CSS_NOT_INSTALLED
Language=Deutsch
Es wurde kein installiertes Koordinatensystem gefunden. Überprüfen 
und wiederholen Sie gegebenenfalls die Installation von %1.
.

Language=English
There are no currently installed coordinate systems available. Verify your
installation and reinstall %1 if nessesary.
.

;
MessageId=0x1011
Severity=Informational
Facility=DBengine
SymbolicName=TRIASDB_S_MUSTOPENASCOPY_SHAREVIOLATION
Language=Deutsch
Auf die angegebene Datei kann auf Grund eines Zugriffskonfliktes nicht zugegriffen werden.
Sie muß als Kopie geöffnet werden.
.

Language=English
There was a shareviolation or accessviolation accessing the file. The File must be copied to open.
.

;
MessageId=0x1012
Severity=Error
Facility=DBEngine
SymbolicName=TRIASDB_E_UNKNOWN_DATASERVER
Language=Deutsch
Dieser TRiASDB-Datenserver ist nicht verfügbar.
.

Language=English
The requested TRiASDB-dataserver is not available.
.

;
MessageId=0x1013
Severity=Error
Facility=DBEngine
SymbolicName=TRIASDB_E_OBJECT_NOT_INITIALIZED
Language=Deutsch
Dieses COM-Objekt ist nicht initialisiert.
.

Language=English
The COM-object is not initialized.
.

;
MessageId=0x1014
Severity=Error
Facility=Project
SymbolicName=TRIASDB_E_NO_ACTIVE_PROJECT;
Language=Deutsch
Es existiert kein aktiviertes Projekt in dieser Projekt-Collection.
.

Language=English
There isn't any activated project in this collection.
.

;
MessageId=0x1015
Severity=Error
Facility=Connection
SymbolicName=TRIASDB_E_UNKNOWN_CONNECTION
Language=Deutsch
Eine TRiASDB-Datenquelle ist nicht verfügbar.
.

Language=English
The requested TRiASDB-datasource is not available.
.

;
MessageId=0x1016
Severity=Error
Facility=Project
SymbolicName=TRIASDB_E_UNKNOWN_PROJECT
Language=Deutsch
Ein TRiASDB-Projekt ist nicht verfügbar.
.

Language=English
The requested TRiASDB-project is not available.
.

;
MessageId=0x1017
Severity=Error
Facility=View
SymbolicName=TRIASDB_E_UNKNOWN_VIEWITEM
Language=Deutsch
Ein TRiASDB-Ansichtseintrag ist nicht verfügbar.
.

Language=English
The requested TRiASDB-viewitem is not available.
.

;
MessageId=0x1018
Severity=Error
Facility=View
SymbolicName=TRIASDB_E_UNKNOWN_VIEW
Language=Deutsch
Eine TRiASDB-Ansicht ist nicht verfügbar.
.

Language=English
The requested TRiASDB-view is not available.
.

;
MessageId=0x1019
Severity=Warning
Facility=Object
SymbolicName=TRIASDB_W_NEWEROBJECTSCOLLECTION
Language=Deutsch
Die einzulesende Objects-Collection hat ein zu neues Format. Die Collection kann daher nicht eingelesen werden.
.

Language=English
The Objects-collection to load has a newer file format. The collection could not be loaded.
.

;
MessageId=0x101a
Severity=Warning
Facility=Connection
SymbolicName=TRIASDB_W_NEWERCONNECTION
Language=Deutsch
Das einzulesende Datenquellen-Objekt hat ein zu neues Format. Die Connection kann daher nicht eingelesen werden.
.

Language=English
The connection-object to load has a newer file format. The connection could not be loaded.
.

;
MessageId=0x101b
Severity=Warning
Facility=View
SymbolicName=TRIASDB_W_NEWERVIEW
Language=Deutsch
Das einzulesende Ansichts-Objekt hat ein zu neues Format. Die Ansicht kann daher nicht eingelesen werden.
.

Language=English
The view-object to load has a newer file format. The view could not be loaded.
.

;
MessageId=0x101c
Severity=Warning
Facility=View
SymbolicName=TRIASDB_W_NEWERVIEWITEM
Language=Deutsch
Das einzulesende Legendeneintrags-Objekt hat ein zu neues Format. Der Legendeneintrag kann daher nicht eingelesen werden.
.

Language=English
The viewitem-object to load has a newer file format. The viewitem could not be loaded.
.

;
MessageId=0x101d
Severity=Error
Facility=Objects
SymbolicName=TRIASDB_E_UNKNOWN_OBJECTS
Language=Deutsch
Eine Objects-Objektsammlung ist nicht verfügbar.
.

Language=English
The requested objects-collection is not available.
.

;
MessageId=0x101e
Severity=Warning
Facility=View
SymbolicName=TRIASDB_W_NOVISINFO
Language=Deutsch
Für den Objekttyp ist in dem Legendeneintrag keine Visualisierungsinformation gegeben.
.

Language=English
There isn't any visualisation information for this objecttype.
.

;
MessageId=0x101f
Severity=Warning
Facility=View
SymbolicName=TRIASDB_W_NOOBJECTS
Language=Deutsch
In diesem Legendeneintrag ist der gewünschte Objekttyp nicht vertreten.
.

Language=English
The requested objecttype is not a part of this viewitem.
.

;
MessageId=0x1020
Severity=Warning
Facility=Object
SymbolicName=TRIASDB_W_NEWEROBJECT
Language=Deutsch
Das einzulesende Geometrieobjekt hat ein zu neues Format. Das Geometrieobjekt kann daher nicht eingelesen werden.
.

Language=English
The geometry-object to load has a newer file format. The geometry-object could not be loaded.
.

;
MessageId=0x1021
Severity=Error
Facility=Features
SymbolicName=TRIASDB_E_UNKNOWN_FEATURE
Language=Deutsch
Eine Objekteigenschafts-Objektsammlung ist nicht verfügbar.
.

Language=English
The requested objectproperties -collection is not available.
.

;
MessageId=0x1022
Severity=Warning
Facility=Feature
SymbolicName=TRIASDB_W_NEWERFEATURE
Language=Deutsch
Die einzulesende Objekteigenschaft hat ein zu neues Format. Die Objekteigenschaft kann daher nicht eingelesen werden.
.

Language=English
The objectproperty to load has a newer file format. The objectproperty could not be loaded.
.

;
MessageId=0x1023
Severity=Warning
Facility=Feature
SymbolicName=TRIASDB_W_ISREADONLY
Language=Deutsch
Die zu modifizierende Objekteigenschaft unterstützt keine Schreiboperationen.
.

Language=English
The objectproperty does not support write operations (is readonly).
.

;
MessageId=0x1024
Severity=Success
Facility=Feature
SymbolicName=TRIASDB_S_OBJECTDOESNOTFIT
Language=Deutsch
Die zu lesende Geometrie des Objektes liegt vollständig außerhalb des gegebenen Suchfensters.
.

Language=English
The geometry of the object is not contained in the searchwindow.
.

;
MessageId=0x1025
Severity=Error
Facility=Project
SymbolicName=TRIASDB_E_BADPROJECTHANDLE
Language=Deutsch
Die eindeutige Projektzugriffsnummer ist ungültig.
.

Language=English
Invalid project handle.
.

;
MessageId=0x1026
Severity=Error
Facility=Object
SymbolicName=TRIASDB_E_BADOBJECTHANDLE
Language=Deutsch
Die eindeutige Objektzugriffsnummer ist ungültig.
.

Language=English
Invalid object handle.
.

;
MessageId=0x1027
Severity=Success
Facility=Feature
SymbolicName=TRIASDB_S_SHOULDHANDLEOBJECTS
Language=Deutsch
Die Recherchefunktionalität ist nur lokal zur Objektmenge verfügbar.
.

Language=English
The required search function is available only for a separate objects collection.
.

;
MessageId=0x1028
Severity=Success
Facility=Feature
SymbolicName=TRIASDB_S_SEARCH_NOT_RECOMMENDED
Language=Deutsch
Die Recherchefunktionalität wird von dem Objekt zwar unterstützt, ist jedoch nicht zu empfehlen.
.

Language=English
The required search function is available for this feature, but it is not recomended to use it.
.

;
MessageId=0x1029
Severity=Error
Facility=Object
SymbolicName=TRIASDB_E_UNKNOWNOBJECTTYPE
Language=Deutsch
Die Geometrie des Objektes kann nicht dargestellt werden.
.

Language=English
The geomtry of the object is unknown.
.

;
MessageId=0x102a
Severity=Error
Facility=Object
SymbolicName=TRIASDB_E_UNKNOWNOBJECTCOORDSYSTEM
Language=Deutsch
Die Geometrie des Objektes kann nicht transformiert werden (unbekanntes Koordinatensystem).
.

Language=English
Unable to transform object geometry.
.

;
MessageId=0x102b
Severity=Error
Facility=Objects
SymbolicName=TRIASDB_E_UNKNOWNCOORDSYSTEM
Language=Deutsch
Die Geometrien der Objekte können nicht transformiert werden (unbekanntes Koordinatensystem).
.

Language=English
Unable to transform objects geometries.
.

;
MessageId=0x102c
Severity=Error
Facility=GenPurpose
SymbolicName=TRIASDB_E_BADOBJECTSIGNATURE
Language=Deutsch
Fehler beim einlesen eines Objektes (fehlerhafte Objektsignatur).
.

Language=English
Error reading object signature (object signature not recognized).
.

;
MessageId=0x102d
Severity=Error
Facility=Feature
SymbolicName=TRIASDB_E_FEATURENOTLOCKED
Language=Deutsch
Es wurde kein Bezugsobjekt für die Objekteigenschaft festgelegt.
.

Language=English
There isn't any target object for evaluating the property.
.

;
MessageId=0x102e
Severity=Error
Facility=Object
SymbolicName=TRIASDB_E_UNKNOWN_OBJECT
Language=Deutsch
Ein TRiASDB-Objekt ist nicht verfügbar.
.

Language=English
The requested TRiASDB-obejct is not available.
.

;
MessageId=0x102f
Severity=Success
Facility=GenPurpose
SymbolicName=TRIASDB_S_SEARCH_NOT_SUPPORTED
Language=Deutsch
Die gewünschte Recherche wird durch dieses Objekt nicht unterstützt.
.

Language=English
The requested search method isn't supported by this object.
.

;
MessageId=0x1030
Severity=Informational
Facility=Objects
SymbolicName=TRIASDB_I_OBJECTS_NOT_EXISTS
Language=Deutsch
Die gewünschte Objektklasse existiert in dieser Datenquelle nicht.
.

Language=English
The requested object class does not exist in this datasource.
.

;
MessageId=0x1031
Severity=Error
Facility=GenPurpose
SymbolicName=TRIASDB_E_REQUESTED_OBJECT_NOT_LOADED
Language=Deutsch
Das gesuchte Objekt ist in diesem Container nicht geladen.
.

Language=English
The requested object is not loaded in this container.
.

;
MessageId=0x1032
Severity=Error
Facility=Database
SymbolicName=TRIASDB_E_SINGLEDATABASE_NOT_FOUND
Language=Deutsch
Die Datenbank konnte nicht gefunden werden.
.

Language=English
The requested database was not found.
.

;
MessageId=0x1033
Severity=Error
Facility=Database
SymbolicName=TRIASDB_E_MULTIDATABASE_NOT_FOUND
Language=Deutsch
Eine oder mehrere der Dateien der Datenbank konnten nicht gefunden werden.
.

Language=English
One or more files of the database were not found.
.

;
MessageId=0x1034
Severity=Informational
Facility=Database
SymbolicName=TRIASDB_I_BROKEN_LINK
Language=Deutsch
Die Verbindung zu einer Datenquelle konnte nicht wiederhergestellt werden. Die Verbindung bleibt geschlossen.
.

Language=English
A database connection couldn't be reestablished. The connection remains closed.
.

;
MessageId=0x1035
Severity=Error
Facility=DBEngine
SymbolicName=TRIASDB_E_NOT_OPENING
Language=Deutsch
Derzeit wird kein Projekt geöffnet.
.

Language=English
There isn't any openening project at this moment.
.

;
MessageId=0x1036
Severity=Informational
Facility=Feature
SymbolicName=TRIASDB_I_NO_OBJECTS_FOUND;
Language=Deutsch
Es wurden keine Objekte entsprechend den gegebenen Recherchekriterien gefunden.
.

Language=English
Could not find any related objects.
.

;
MessageId=0x1037
Severity=Error
Facility=Database
SymbolicName=TRIASDB_E_DATABASENOTUPDATABLE;
Language=Deutsch
Die Datenquelle ist schreibgeschützt, der Zugriff wurde verweigert.
.

Language=English
The datasource is readonly, write access denied.
.

;
MessageId=0x1038
Severity=Error
Facility=Objects
SymbolicName=TRIASDB_E_OBJECTSNOTUPDATABLE;
Language=Deutsch
Die Objects-Collection ist schreibgeschützt, der Zugriff wurde verweigert.
.

Language=English
The objects collection is readonly, write access denied.
.

;
MessageId=0x1039
Severity=Error
Facility=Feature
SymbolicName=TRIASDB_E_FEATURENOTUPDATABLE;
Language=Deutsch
Die Objekteigenschaft ist schreibgeschützt, der Zugriff wurde verweigert.
.

Language=English
The objectproperty is readonly, write access denied.
.

;
MessageId=0x1040
Severity=Error
Facility=Feature
SymbolicName=TRIASDB_E_NOSUCHFEATURE;
Language=Deutsch
Die Objekteigenschaft existiert nicht für dieses Objekt.
.

Language=English
The objectproperty does not exist for this object.
.

;
MessageId=0x1041
Severity=Informational
Facility=Object
SymbolicName=TRIASDB_I_OBJECT_ALREADY_EXISTS
Language=Deutsch
Das gewünschte Objekt existiert bereits in dieser Objektklasse.
.

Language=English
The requested object already exists in this object class.
.

;
MessageId=0x1042
Severity=Informational
Facility=Feature
SymbolicName=TRIASDB_I_NO_OBJECT_FOUND;
Language=Deutsch
Es wurden keine abhängigen Objekte entsprechend den gegebenen Recherchekriterien gefunden.
.

Language=English
Could not find any related objects.
.

;#endif // _DBMSG_H
