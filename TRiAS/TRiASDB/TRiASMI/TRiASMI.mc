;///////////////////////////////////////////////////////////////////////////////
;// Messages for TRiASMI
;// SourceFile: TRiASMI.MC
;
;#if !defined(_TRiASMI_HMC)
;#define _TRiASMI_HMC
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
MessageId=0x3101
Severity=Error
Facility=Database
SymbolicName=TRIASMI_E_BADFILENAME
Language=Deutsch
Der angegebene Dateiname bezieht sich weder auf eine Datei noch auf ein Verzeichnis.
.

Language=English
The given name relates neither to a file nor to a directory, Shape access failed.
.

;
MessageId=0x3102
Severity=Error
Facility=Database
SymbolicName=TRIASMI_E_OPENFILE_FAILED
Language=Deutsch
Die Shapedatei konnte nicht geöffnet werden. Sie könnte beschädigt sein.
.

Language=English
Failed to open shapefile. It may be corrupt.
.

;
MessageId=0x3102
Severity=Warning
Facility=Database
SymbolicName=TRIASMI_W_NOFILESFOUND
Language=Deutsch
Es wurden keine Shapedateien gefunden im gegebenen Verzeichnis gefunden.
.

Language=English
No Shapefiles found in directory.
.

;
MessageId=0x3103
Severity=Error
Facility=Database
SymbolicName=TRIASMI_E_BADGEOMETRYTYPE
Language=Deutsch
Unbekannter Geometrietyp.
.

Language=English
Unknown geometry type.
.

;
MessageId=0x3104
Severity=Warning
Facility=Database
SymbolicName=TRIASMI_W_LAYERNAME_NOT_UNIQUE
Language=Deutsch
Layername muß innerhalb einer Datenquelle eindeutig sein.
.

Language=English
The layername should be unique.
.

;
MessageId=0x3105
Severity=Error
Facility=Database
SymbolicName=TRIASMI_E_NO_COORDSYSTEM_GIVEN
Language=Deutsch
Es ist keine Koordinatensystem-Transformation initialisiert.
.

Language=English
No coordsystem transform objct initialized.
.

;
MessageId=0x3106
Severity=Error
Facility=NativeDB
SymbolicName=TRIASMI_E_NO_VALID_ENVELOPE
Language=Deutsch
Es ist kein gültiges umschließendes Rechteck des Layers verfügbar.
.

Language=English
No valid bounds available for a layer.
.

;#endif // _TRiASMI_HMC
