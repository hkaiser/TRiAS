include( `dbhelp.m4' )

START(ArcView)

SeverityNames = (
	SEV(S, 0x0, STATUS_SEVERITY_SUCCESS)
	SEV(I, 0x1, STATUS_SEVERITY_INFORMATIONAL)
	SEV(W, 0x2, STATUS_SEVERITY_WARNING)
	SEV(E, 0x3, STATUS_SEVERITY_ERROR)
)
FacilityNames = (
	System=0x0FF
	FAC(COM, 0x0011, FACILITY_COM)			; allgemeine Fehler
	FAC(ARCVIEW, 0x0012, FACILITY_EXP)		; Fehler in einem Exportmodul
)

MID(0x0001, E, COM, COMMON)
GER(Allgemeiner Fehler.)
ENG(Common Error.)

MID(0x0002, E, ARCVIEW, OPENFILE_FAILED)
GER(Datei kann nicht erzeugt werden.)
ENG(Could not create file.)

MID(0x0003, W, ARCVIEW, LAYERNAME_NOT_UNIQUE)
GER(Layername muß eindeutig sein.)
ENG(Layername should be unique.)

MID(0x0004, E, ARCVIEW, BADFILENAME)
GER(Ungültiger Datei- bzw. Verzeichnisname.)
ENG(Bad file or directory name.)

MID(0x0005, E, ARCVIEW, BADOBJECTTYPE)
GER(Ungültiger Objekttyp.)
ENG(Bad objecttype.)

END(ArcView)
