include( `dbhelp.m4' )

START(TRiASMetaDataServices)

SeverityNames = (
	SEV(S,0x0,STATUS_SEVERITY_SUCCESS)
	SEV(I,0x1,STATUS_SEVERITY_INFORMATIONAL)
	SEV(W,0x2,STATUS_SEVERITY_WARNING)
	SEV(E,0x3,STATUS_SEVERITY_ERROR)
)
FacilityNames = (
	System=0x0FF
	FAC(MDS,0x0001,FACILITY_MDS)			; allgemeine Fehler
	FAC(MAP,0x0002,FACILITY_MAP)			; Fehler in Metadatenmap
	FAC(KEY,0x0003,FACILITY_KEY)			; Fehler in OKS-Parser
)

;///////////////////////////////////////////////////////////////////////////////
;// allgemeine Fehler

MID(0x1000,E,MDS,COMMON)
GER(Allgemeiner Fehler.)
ENG(Common Error.)

MID(0x1001,E,MDS,COERCE)
GER(Fehler bei der Datentypumwandlung.)
ENG(Error on coercing data.)

MID(0x2000,E,MAP,INVALIDSEARCHITEM)
GER(Ungültiges Suchelement.)
ENG(Invalid search item.)

MID(0x2001,E,MAP,INVALIDSEARCHMODE)
GER(Ungültiger Suchmodus.)
ENG(Invalid search mode.)

MID(0x2002,E,MAP,ELEMENTNOTFOUND)
GER(Element nicht gefunden.)
ENG(Element not found.)

MID(0x2000,E,KEY,NOOBJECTKEY)
GER(Die übergebene Zeichenkette ist kein gültiger Objektklassenschlüssel.)
ENG(The string is not a valid classkey.)

MID(0x2001,E,KEY,NOHEXDIGITS)
GER(Der angegebene Objektklassenschlüssel enthält Zeichen die nicht als Hexadezimalzeichen interpretiert werden können.)
ENG(The Objektkey contains non-hexadecimal characters.)

END(TRiASMetaDataServices)
