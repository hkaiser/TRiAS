include( `dbhelp.m4' )

START(LPICT)

SeverityNames = (
	SEV(S,0x0,STATUS_SEVERITY_SUCCESS)
	SEV(I,0x1,STATUS_SEVERITY_INFORMATIONAL)
	SEV(W,0x2,STATUS_SEVERITY_WARNING)
	SEV(E,0x3,STATUS_SEVERITY_ERROR)
)
FacilityNames = (
	System=0x0FF
	FAC(CMN,0x001,FACILITY_LPICTCOMMON)		; allgemeine Fehler
)

;///////////////////////////////////////////////////
;// allgemeine Fehler

MID(0x1000,E,CMN,COMMON)
GER(Allgemeiner Fehler.)
ENG(Common Error.)

END(LPICT)
