;///////////////////////////////////////////////////////////////////////////////
;// Messages for TRiASIMP
;// SourceFile: IMPMSG.MC
;
;#if !defined(_IMPMSG_H)
;#define _IMPMSG_H
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
	DBEngine = 0xF00:FACILITY_DBENGINE	; Fehler des TRiASDB-Layers
	NativeDB = 0xF01:FACILITY_NATIVEDB	; Fehler des unterliegenden Datenbanksystems
)

LanguageNames = (
	Deutsch=0x407:MSG00407
	English=0x409:MSG00409
)

MessageIdTypedef=HRESULT

;
MessageId=0x1001
Severity=Error
Facility=DBEngine
SymbolicName=TRIASIMP_E_DATABASE_NOT_OPENED
Language=Deutsch
Datenbank ist nicht geöffnet.
.

Language=English
Database was not opened.
.

;
MessageId=0x1002
Severity=Error
Facility=DBEngine
SymbolicName=TRIASIMP_E_INVALID_PARAMETER
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
SymbolicName=TRIASIMP_E_ERROR_NATIVEDB
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
SymbolicName=TRIASIMP_E_COULD_NOT_OPEN
Language=Deutsch
Datenbank konnte nicht geöffnet werden.
.

Language=English
Could not open database.
.

;
MessageId=0x1005
Severity=Warning
Facility=DBengine
SymbolicName=TRIASIMP_E_ALREADY_OPENED
Language=Deutsch
Datenbank ist bereits geöffnet.
.

Language=English
Database was already opened.
.

;
MessageId=0x1006
Severity=Error
Facility=DBengine
SymbolicName=TRIASIMP_E_NOT_STARTED
Language=Deutsch
Das Datenbanksystem wurde nicht initialisiert.
.

Language=English
DBEngine is not initialized or started.
.

;#endif // _IMPMSG_H
