;///////////////////////////////////////////////////////////////////////////////
;// Messages for FastDB
;// SourceFile: DBMSG.MC
;
;#if !defined(_FASTDB_H)
;#define _FASTDB_H
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
MessageId=0x2001
Severity=Error
Facility=Database
SymbolicName=FASTDB_E_DATABASE_COULDNOTSAVE
Language=Deutsch
Datenbank konnte nicht gespeichert werden.
.

Language=English
Database could not be saved.
.

;
MessageId=0x2002
Severity=Error
Facility=Database
SymbolicName=FASTDB_E_DATABASE_INVALIDSCHEMA
Language=Deutsch
Datenbankstruktur ist fehlerhaft.
.

Language=English
Invalid database schema.
.

;
MessageId=0x2003
Severity=Error
Facility=Objects
SymbolicName=FASTDB_E_OBJECTS_BADREFERENCE
Language=Deutsch
Fehlerhafter Verweis auf eine nichtexistierende Objektklasse.
.

Language=English
Bad Objects reference.
.

;
MessageId=0x2004
Severity=Error
Facility=Object
SymbolicName=FASTDB_E_OBJECT_BADREFERENCE
Language=Deutsch
Fehlerhafter Verweis auf ein nichtexistierendes Objekt.
.

Language=English
Bad Object reference.
.

;
MessageId=0x2005
Severity=Error
Facility=Feature
SymbolicName=FASTDB_E_FEATURE_BADREFERENCE
Language=Deutsch
Fehlerhafter Verweis auf eine nichtexistierende Objekteigenschaft.
.

Language=English
Bad Feature reference.
.

;
MessageId=0x2006
Severity=Warning
Facility=Database
SymbolicName=FASTDB_E_UNKNOWN_DATABASE_VERSION
Language=Deutsch
Die angegebene Datenbank hat ein unbekanntes Format. Die Datenbank kann daher nicht geöffnet werden.
.

Language=English
The specified database has a unknown file format. The database could not be opened.
.

;#endif // _DBMSG_H
