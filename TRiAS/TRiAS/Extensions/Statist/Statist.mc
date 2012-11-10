include(`dbhelp.m4')

START(STATIST)

SeverityNames = (
	SEV(S,0x0,STATUS_SEVERITY_SUCCESS)
	SEV(I,0x1,STATUS_SEVERITY_INFORMATIONAL)
	SEV(W,0x2,STATUS_SEVERITY_WARNING)
	SEV(E,0x3,STATUS_SEVERITY_ERROR)
)
FacilityNames = (
	System=0x0FF
	FAC(STATIST,0xe10,FACILITY_STATIST)				; Fehler im SimpleStatist-Objekt
)

MID(0x1000,E,STATIST,BADCOUNTERVALUE)
GER(Fehlerhafter Wertezähler.)
ENG(Bad value counter.)

MID(0x1001,E,STATIST,BADSUMVALUE)
GER(Fehlerhafte Wertesumme.)
ENG(Bad summation value.)

MID(0x1002,E,STATIST,BADMINBOUNDSARRAY)
GER(Fehlerhaftes Feld für untere Bereichsgrenzen.)
ENG(Bad array for lower bounds.)

MID(0x1003,E,STATIST,BADMAXBOUNDSARRAY)
GER(Fehlerhaftes Feld für obere Bereichsgrenzen.)
ENG(Bad array for upper bounds.)

MID(0x1004,E,STATIST,BADCOUNTSARRAY)
GER(Fehlerhaftes Feld für Zähler der Wertebereiche.)
ENG(Bad array for range counter.)

MID(0x1005,E,STATIST,BADOBJECTS)
GER(Fehlerhaftes TRiASObjects Objekt.)
ENG(Bad TRiASObjects object.)

MID(0x1006,E,STATIST,BADFEATURE)
GER(Fehlerhaftes TRiASFeature Objekt.)
ENG(Bad TRiASFeature object.)

MID(0x1007,E,STATIST,BADDATAVALUE)
GER(Fehlerhafter Datenwert.)
ENG(Bad data value.)

MID(0x1008,E,STATIST,VALUENOTFOUND)
GER(Der gegebene Datenwert wurde nicht gefunden.)
ENG(Data value not found.)


END(STATIST)
