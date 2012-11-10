include( `dbhelp.m4' )

START(TRiASErrorTrekking)

SeverityNames = (
	SEV(S,0x0,STATUS_SEVERITY_SUCCESS)
	SEV(I,0x1,STATUS_SEVERITY_INFORMATIONAL)
	SEV(W,0x2,STATUS_SEVERITY_WARNING)
	SEV(E,0x3,STATUS_SEVERITY_ERROR)
)
FacilityNames = (
	System=0x0FF
	FAC(GEN,0x0001,FACILITY_GEN)			; allgemeine Fehler
)

MID(0x1000,E,GEN,COMMON)
GER(Allgemeiner Fehler.)
ENG(Common Error.)

END(TRiASErrorTrekking)
