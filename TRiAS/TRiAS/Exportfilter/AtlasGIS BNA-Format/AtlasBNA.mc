include( `dbhelp.m4' )

START(AtlasBNA)

SeverityNames = (
	SEV(S,0x0,STATUS_SEVERITY_SUCCESS)
	SEV(I,0x1,STATUS_SEVERITY_INFORMATIONAL)
	SEV(W,0x2,STATUS_SEVERITY_WARNING)
	SEV(E,0x3,STATUS_SEVERITY_ERROR)
)
FacilityNames = (
	System=0x0FF
	FAC(COM,0x0001,FACILITY_COM)			; allgemeine Fehler
	FAC(EXP,0x0002,FACILITY_EXP)			; Fehler in einem Exportmodul
)

MID(0x0001,E,COM,COMMON)
GER(Allgemeiner Fehler.)
ENG(Common Error.)

END(AtlasBNA)
