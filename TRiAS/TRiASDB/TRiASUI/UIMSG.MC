;///////////////////////////////////////////////////////////////////////////////
;// Messages for TRiASUI
;// SourceFile: UIMSG.MC
;
;#if !defined(_UIMSG_HMC)
;#define _UIMSG_HMC
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
	TRIASUI = 0xF20:FACILITY_TRIASUI	; Fehler in einer NutzerinterfaceKomponente
)

LanguageNames = (
	Deutsch=0x407:MSG00407
	English=0x409:MSG00409
)

MessageIdTypedef=HRESULT

;
MessageId=0x1001
Severity=Error
Facility=TRiASUI
SymbolicName=TRIASUI_E_BADOBJECTSIGNATURE
Language=Deutsch
Fehler beim Einlesen eines Objektes (fehlerhafte Objektsignatur).
.

Language=English
Error reading object signature (object signature not recognized).
.

;
MessageId=0x1002
Severity=Error
Facility=TRiASUI
SymbolicName=TRIASUI_W_NEWERTRIASOPTIONDLG
Language=Deutsch
Das angegebene TRiAS Nutzerinterfaceobjekt hat ein zu neues Format. Das Nutzerinterface-Element kann daher nicht initialisiert werden.
.

Language=English
The specified TRiAS user interface object has a newer file format. The corresponding user interface element could not be initialzed.
.

;#endif // _UIMSG_HMC
