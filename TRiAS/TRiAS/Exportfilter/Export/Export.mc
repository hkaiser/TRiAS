include( `dbhelp.m4' )

START(Export)

SeverityNames = (
	SEV(S,0x0,STATUS_SEVERITY_SUCCESS)
	SEV(I,0x1,STATUS_SEVERITY_INFORMATIONAL)
	SEV(W,0x2,STATUS_SEVERITY_WARNING)
	SEV(E,0x3,STATUS_SEVERITY_ERROR)
)
FacilityNames = (
	System=0x0FF
	FAC(COM,0x0001,FACILITY_COM)			; allgemeine Fehler
	FAC(EPA,0x0002,FACILITY_EPA)			; Fehler in C(E)xport(P)roperty(A)ction
	FAC(EXP,0x0100,FACILITY_EXP)			; Fehler in einem Exportmodul
)

;///////////////////////////////////////////////////////////////////////////////
;// allgemeine Fehler

MID(0x0001,E,COM,COMMON)
GER(Allgemeiner Fehler.)
ENG(Common Error.)

;///////////////////////////////////////////////////////////////////////////////
;// Fehler in C(E)xport(P)roperty(A)ction

MID(0x0001,E,EPA,NOENGINESLOADED)
GER(Keine ExportEngines gefunden.)
ENG(No ExportEngines found.)

MID(0x0002,E,EPA,KEYNOTEXIST)
GER(Ungültiger Registrierungsschlüssel.)
ENG(Invalid Registrationkey.)

MID(0x0003,E,EPA,INVALIDXML)
GER(Fehlerhaftes Exporttemplate.)
ENG(Invalid Exporttemplate.)

MID(0x0004,E,EPA,INVALIDEXPORTENGINE)
GER(Fehlerhafte Exportengine.)
ENG(Invalid Exportengine.)

END(Export)
