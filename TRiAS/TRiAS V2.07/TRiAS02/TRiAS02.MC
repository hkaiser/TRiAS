;///////////////////////////////////////////////////////////////////////////////
;// Messages for TRiASDB
;// SourceFile: TRiAS02.MC
;
;#if !defined(_TRiAS02_HMC)
;#define _TRiAS02_HMC
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
	TRiAS02 = 0xF10:FACILITY_TRIAS02	; Fehler des unterliegenden Datenbanksystems
)

LanguageNames = (
	Deutsch=0x407:MSG00407
)

MessageIdTypedef=HRESULT

;
MessageId=0x1001
Severity=Error
Facility=TRiAS02
SymbolicName=TRIAS02_E_CSSNOTINITIALIZED
Language=Deutsch
Der Koordinatensystem-Service ist nicht korrekt initialisiert (Funktion '%2').
.

;#endif // _TRiAS02_HMC
