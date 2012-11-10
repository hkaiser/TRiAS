include( `dbhelp.m4' )

START(TDBGEO)

SeverityNames = (
	SEV(S,0x0,STATUS_SEVERITY_SUCCESS)
	SEV(I,0x1,STATUS_SEVERITY_INFORMATIONAL)
	SEV(W,0x2,STATUS_SEVERITY_WARNING)
	SEV(E,0x3,STATUS_SEVERITY_ERROR)
)
FacilityNames = (
	System=0x0FF
	FAC(STREAM,0xe01,FACILITY_STREAM)				; Fehler in IPersistXXX
	FAC(TGEO, 0xF20,FACILITY_TDBCOMMON)				; allgemeine Fehler
	FAC(POINT,0xF21,FACILITY_TDBPOINT)				; Fehler im Punktobjekt
	FAC(POINTS,0xF22,FACILITY_TDBPOINTS)			; Fehler im Punktcollection
	FAC(LINE,0xF23,FACILITY_TDBLINE)				; Fehler im Linienobjekt
	FAC(GCOLL,0xF2e,FACILITY_GEOMETRYCOLLECTION)	; Fehler in der Geometrycollection
)

MID(0x1000,E,STREAM,OBJECTALREADYINITIALIZED)
GER(Das Objekt ist bereits initialisiert.)
ENG(Object already initialized.)

MID(0x1001,E,STREAM,OBJECTNOTINITIALIZED)
GER(Das Objekt ist nicht initialisiert.)
ENG(Object not initialized.)

MID(0x1002,E,STREAM,INVALIDSIZE)
GER(Zu ladende Byteanzahl stimmt nicht mit der Objektgröße überein.)
ENG(Bytecount doesn't match Objectsize.)

MID(0x1003,E,STREAM,CORRUPTED)
GER(Beim Lesen aus einem Stream ist ein Fehler aufgetreten.)
ENG(Error during reading stream.)

MID(0x1010,E,STREAM,CANNOTLOADITEM)
GER(Fehler beim Laden des Objektes.)
ENG(Error while loading Object.)

MID(0x1011,E,STREAM,CANNOTSAVEITEM)
GER(Fehler beim Speichern des Objektes.)
ENG(Error while saving Object.)

;///////////////////////////////////////////////////
;// allgemeine Fehler

MID(0x1000,E,TGEO,INTERNAL)
GER(Interner Fehler.)
ENG(internal error.)

MID(0x1001,E,TGEO,SERVICE_NOTAVAILABLE)
GER(Service nicht verfügbar.)
ENG(Service not available.)

MID(0x1002,E,TGEO,INVALID_PARAMETER)
GER(Fehlerhafter Parameter.)
ENG(Invalid Parameter.)

MID(0x1003,E,TGEO,COERCE)
GER(Fehler bei Datentypumwndlung.)
ENG(Error on coercing data.)

MID(0x1004,E,TGEO,INDEXISZERO)
GER(Index muß größer als 0 sein.)
ENG(Index must be greater then zero.)

MID(0x1005,E,TGEO,ACCESSELEMENT)
GER(Fehler beim Zugriff auf das geforderte Element.)
ENG(Error accessing requested Element.)

MID(0x100a,E,TGEO,INVALID_OBJECTSTATE)
GER(Fehlerhafte Objektzustand.)
ENG(Invalid object state.)

MID(0x100b,E,TGEO,UNKNOWN_OBJECTTYPE)
GER(Unbekannter Objekttyp)
ENG(Unknown object type)

;///////////////////////////////////////////////////
;// Fehler im Punktobjekt

MID(0x1010,E,POINT,CANNOTRETRIEVECOORDINATE)
GER(Fehler beim Ermitteln einer Koordinate.)
ENG(Cannot retrieve coordinate.)

MID(0x1011,E,POINT,CANNOTSETCOORDINATE)
GER(Fehler beim Setzen einer Koordinate.)
ENG(Cannot set coordinate.)

MID(0x1020,E,POINT,CANNOTTRANSFORMGEOMETRY)
GER(Geometrie kann nicht transformiert werden.)
ENG(Cannot transform Geometry.)

;///////////////////////////////////////////////////
;// Fehler in der Punktcollection

MID(0x100a,E,POINTS,INDEXTOLARGE_A)
GER(Index muß eins größer sein als Elementanzahl.)
ENG(Index must be one greater then elementcount.)

MID(0x100b,E,POINTS,INDEXTOLARGE_R)
GER(Index darf nicht größer sein als Elementanzahl.)
ENG(Index cannt be greater then elementcount.)

;///////////////////////////////////////////////////
;// Fehler in der GeometryCollection

MID(0x1020,E,GCOLL,CANNOTTRANSFORMGEOMETRY)
GER(Geometrie kann nicht transformiert werden.)
ENG(Cannot transform Geometry.)

;///////////////////////////////////////////////////
;// Fehler im Linienobjekt

MID(0x1030,E,LINE,CANNOTTRANSFORMGEOMETRY)
GER(Geometrie kann nicht transformiert werden.)
ENG(Cannot transform Geometry.)

END(TDBGEO)
