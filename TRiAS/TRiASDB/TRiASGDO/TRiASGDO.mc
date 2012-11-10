include( `dbhelp.m4' )

START(TRiASGDO)

SeverityNames = (
	SEV(S,0x0,STATUS_SEVERITY_SUCCESS)
	SEV(I,0x1,STATUS_SEVERITY_INFORMATIONAL)
	SEV(W,0x2,STATUS_SEVERITY_WARNING)
	SEV(E,0x3,STATUS_SEVERITY_ERROR)
)
FacilityNames = (
	System=0x0FF
	FAC(GDO,0x001,FACILITY_GDOCOMMON)		; allgemeine Fehler
	FAC(NDB,0x002,FACILITY_GDONATIVEDB)		; Fehler des unterliegenden Datenbanksystems
	FAC(DBE,0x003,FACILITY_GDODBENGINE)		; Fehler des TRiASGDO-Layers
	FAC(GDB,0x004,FACILITY_GDODATABASE)		; Fehler im Database Objekt
	FAC(OBJ,0x005,FACILITY_GDOOBJECT)		; Fehler in einem GDO-Objekt
	FAC(OBS,0x006,FACILITY_GDOOBJECTS)		; Fehler in einem GDO-Objekts - Objekt
	FAC(OBC,0x007,FACILITY_GDOOBJCOLL)		; Fehler in GDO-Objectscollection
)

;///////////////////////////////////////////////////
;// allgemeine Fehler

MID(0x1000,E,GDO,COMMON)
GER(Allgemeiner Fehler.)
ENG(Common Error.)

MID(0x1001,E,GDO,SERVICE_NOTAVAILABLE)
GER(Service nicht verfügbar.)
ENG(Service not available.)

MID(0x1002,E,GDO,COERCE)
GER(Datentypumwandlung gescheitert.)
ENG(Failed to coerce data.)

MID(0x1003,E,GDO,INVALIDNAME)
GER(Unzulässiger Bezeichner.)
ENG(Name inakzeptable.)

MID(0x1004,E,GDO,OBJECTNOTINITIALIZED)
GER(Objekt ist nicht initialisert.)
ENG(Object not initialized.)

MID(0x1005,E,GDO,NOAPPLICATION)
GER(Application kann nicht ermittelt werden.)
ENG(Cannot retrieve Application.)

MID(0x1006,E,GDO,NOPARENT)
GER(Parent kann nicht ermittelt werden.)
ENG(Cannot retrieve parent.)

MID(0x1011,E,GDO,OBJECTS)
GER(Allgemeiner Fehler GDO-Objects.)
ENG(Common Error in GDO-Objects.)

MID(0x1012,E,GDO,OBJECT)
GER(Allgemeiner Fehler in einem GDO-Objekt.)
ENG(Common Error in GDO-Object.)

MID(0x1013,E,GDO,FEATURES)
GER(Allgemeiner Fehler in GDO-Features.)
ENG(Common Error in GDO-Features.)

MID(0x1014,E,GDO,FEATURE)
GER(Allgemeiner Fehler in GDO-Feature.)
ENG(Common Error in GDO-Feature.)

MID(0x1015,E,GDO,METADATA)
GER(Allgemeiner Fehler im Metadatenservice.)
ENG(Common Error in Metadataservice.)

MID(0x1016,E,GDO,READONLY)
GER(Kein Schreibzugriff auf Objekt / Eigenschaft möglich.)
ENG(Write access denied.)

MID(0x1017,E,GDO,INVALIDHANDLE)
GER(Fehlerhaftes Handle.)
ENG(Invalid Handle.)

;///////////////////////////////////////////////////
;// DBEngine

MID(0x1001,E,DBE,SERVICE_NOTAVAILABLE)
GER(GDO-Datenbankservice nicht verfügbar.)
ENG(GDO-Databaseservice not available.)

MID(0x1002,E,DBE,DATABASE_NOT_OPENED)
GER(Datenbank ist nicht geöffnet.)
ENG(Database was not opened.)

MID(0x1003,E,DBE,INVALID_PARAMETER)
GER(Ungültiger Parameter.)
ENG(Invalid parameter.)

MID(0x1004,W,DBE,ALREADY_OPENED)
GER(Datenbank ist bereits geöffnet.)
ENG(Database was already opened.)

MID(0x1005,W,DBE,NOTSTARTED)
GER(Das Datenbanksystem wurde nicht initialisiert.)
ENG(DBE is not initialized or started.)

MID(0x1006,E,DBE,COULD_NOT_OPEN)
GER(Datenbank konnte nicht geöffnet werden.)
ENG(Could not open database.)

MID(0x1007,E,DBE,UNDEFINED_COORDSYS)
GER(Ungültige oder fehlende Koordinatensystemdefinition.)
ENG(Invalid or missing Coordinate system definition.)

MID(0x1008,E,DBE,FAILED_TOACCESSDATABASE)
GER(Auf Datenbank kann nicht zugegriffen werden.)
ENG(Couldn't access database.)

MID(0x1009,E,DBE,INVALID_COORDDEF)
GER(Ungültige Koordinatensystemdatei.)
ENG(Invalid Coordinatesystemfile.)

MID(0x100a,E,DBE,FAILED_TOCREATEDATABASE)
GER(Datenbank kann nicht erzeugt werden.)
ENG(Couldn't create database.)

MID(0x100b,E,DBE,FAILED_TOACCESSDATASERVER)
GER(GDO Datenserver nicht verfügbar.)
ENG(GDO Dataserver not available.)

;///////////////////////////////////////////////////
;// GDODatabase

MID(0x1001,E,GDB,CANTOPENDATABASE)
GER(Kann Datenbank nicht öffnen.)
ENG(Can't open database.)

MID(0x1002,E,GDB,CANTCLOSEDATABASE)
GER(Kann Datenbank nicht schließen.)
ENG(Can't close database.)

MID(0x1003,E,GDB,INVALIDCOORDSYSTEM)
GER(Ungültiges Koordinatensystem.)
ENG(Invalid coordinatesystem.)

MID(0x1004,E,GDB,UNKNOWNCLASS)
GER(Unbekannte Objektklasse.)
ENG(Unknown object class.)

MID(0x1005,E,GDB,CLASSEXISTS)
GER(Objektklasse existiert bereits.)
ENG(Object class already exists.)

MID(0x1006,E,GDB,CANNOTCREATECLASS)
GER(Objektklasse kann nicht erzeugt werden.)
ENG(Cannot create object class.)

MID(0x1007,E,GDB,INVALIDDATABASE)
GER(Fehlerhafte GDO-Datenbankbeschreibung.)
ENG(Invalid Databasedescription.)

MID(0x1008,E,GDB,INVALID_PARAMETER)
GER(Fehlerhafter Parameter.)
ENG(Invalid Paramater.)

MID(0x1011,E,GDB,CANTOPENRECORDSET)
GER(Kann Recordset nicht öffnen.)
ENG(Can't open recordset.)

MID(0x1012,E,GDB,PROPERTYSET_SETNOTAVAILABLE)
GER(Properties nicht verfügbar.)
ENG(Properties not available)

MID(0x1013,E,GDB,PROPERTY_NOTAVAILABLE)
GER(Propertie nicht verfügbar.)
ENG(Propertie not available)

MID(0x1014,E,GDB,PROPERTYVAL_NOTAVAILABLE)
GER(Wert der Propertie nicht verfügbar.)
ENG(Propertievalue not available)

MID(0x1015,E,GDB,CANNOTCOUNTOBJECTS)
GER(Objektanzahl kann nicht ermittelt werden.)
ENG(Cannot count Objects.)

MID(0x1020,E,GDB,CANNOTLOADOBJECTS)
GER(Objekte können nicht geladen werden.)
ENG(Cannot load Objects.)

MID(0x1021,E,GDB,CANNOTLOADGEOMETRIES)
GER(Objektgeometrien können nicht geladen werden.)
ENG(Cannot load Objectgeometries.)

MID(0x1022,E,GDB,CANNOTLOADGEOMETRY)
GER(Objektgeometrie kann nicht geladen werden.)
ENG(Cannot load Objectgeometry.)

MID(0x1023,E,GDB,CANNOTBUILDOBJECT)
GER(Objektgeometrie kann nicht erzeugt werden.)
ENG(Cannot build Objectgeometry.)

MID(0x1024,E,GDB,CANNOTINITRECORDDATA)
GER(Daten können nicht initialisiert werden.)
ENG(Cannot initialize record data.)

MID(0x1030,E,GDB,FEATURESNOTAVAILABLE)
GER(Keine Features verfügbar.)
ENG(Features not available.)

MID(0x1031,E,GDB,CANNOTLOADFEATURES)
GER(Features können nicht geladen werden.)
ENG(Cannot load Objects.)

MID(0x1032,E,GDB,UNKNOWNOBJECTTYPE)
GER(Features können nicht geladen werden.)
ENG(Cannot load Objects.)

MID(0x1033,E,GDB,FEATUREDOESNOTEXIST)
GER(Feature existiert nicht.)
ENG(Feature does not exist.)

;///////////////////////////////////////////////////
;// NativeDB

MID(0x1001,E,NDB,NATIVEDB)
GER(Allgemeiner Fehler im unterliegenden Datenbanksystem.)
ENG(Common error in underlying database system.)

MID(0x1002,E,NDB,CANTOPENRECORDSET)
GER(Kann Recordset nicht öffnen.)
ENG(Can't open recordset.)

;///////////////////////////////////////////////////
;// Fehler in einem GDO-Objekt

;///////////////////////////////////////////////////
;// Fehler in einem GDO-Objekts Objekt

MID(0x1001,E,OBS,LOADINGFEATURES)
GER(Eigenschaften der Objektklasse können nicht geladen werden.)
ENG(Can't load features of cobjectlass.)

MID(0x1002,E,OBS,INITFEATURES)
GER(Eigenschaften der Objektklasse können nicht geladen werden.)
ENG(Can't load features of cobjectlass.)

MID(0x1003,E,OBS,PKEYNOTDELETABLE)
GER(Primäreigenschaft kann nicht gelöscht werden.)
ENG(Can't delete primary feature.)

;///////////////////////////////////////////////////
;// Fehler in GDO-Objectscollection

MID(0x1001,E,OBC,CLASSEXISTS)
GER(Objeklasse existiert bereits.)
ENG(Class already exists.)

END(TRiASGDO)
