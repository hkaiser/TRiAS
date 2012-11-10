include( `dbhelp.m4' )

START(TRiASCoordSystems)

SeverityNames = (
	SEV(S,0x0,STATUS_SEVERITY_SUCCESS)
	SEV(I,0x1,STATUS_SEVERITY_INFORMATIONAL)
	SEV(W,0x2,STATUS_SEVERITY_WARNING)
	SEV(E,0x3,STATUS_SEVERITY_ERROR)
)
FacilityNames = (
	System=0x0FF
	FAC(TCS,0x0001,FACILITY_TCS)			; allgemeine Fehler
	FAC(CS,0x0002,FACILITY_CS)				; Fehler im Koordinatensystem
	FAC(GCS,0x0003,FACILITY_GCS)			; Fehler im geogr. Koordinatensystem
	FAC(PCS,0x0004,FACILITY_PCS)			; Fehler im projektiven Koordinatensystem
	FAC(CST,0x0005,FACILITY_CST)			; Fehler im Koordinatentransformator
	FAC(DTT,0x0006,FACILITY_DTT)			; Fehler im Datumstransformator
	FAC(STM,0x0007,FACILITY_STM)			; Fehler im StorageManager
	FAC(RCS,0x0008,FACILITY_RCS)			; Fehler im Raw-Transformator
)

;///////////////////////////////////////////////////////////////////////////////
;// allgemeine Fehler

MID(0x1000,E,TCS,COMMON)
GER(Allgemeiner Fehler.)
ENG(Common Error.)

MID(0x1001,E,TCS,INVALIDPARAMETERINDEX)
GER(Fehlerhafter Parameterindex.)
ENG(Invalid Parameterindex.)

MID(0x1002,E,TCS,INVALIDPARAMETERCOUNT)
GER(Fehlerhafte Parameteranzahl.)
ENG(Invalid Parametercount.)

MID(0x1003,E,TCS,INVALIDPARAMETER)
GER(Fehlerhafter Parameter.)
ENG(Invalid Parameter.)

MID(0x1004,E,TCS,CANNOTWRITEDATA)
GER(Daten können nicht geschrieben werden.)
ENG(Can't write Data.)

MID(0x1005,E,TCS,INVALIDDATAFORMAT)
GER(Fehlerhaftes Datenformat.)
ENG(Invalid Data.)

MID(0x1006,E,TCS,CANNOTREADDATA)
GER(Daten können nicht gelesen werden.)
ENG(Can't read Data.)

MID(0x1007,E,TCS,ACCESS_DENIED)
GER(Zugriff nicht möglich.)
ENG(Access denied.)

;///////////////////////////////////////////////////////////////////////////////
;// Fehler im Koordinatensystem

MID(0x2001,E,CS,INVALIDCOORDSYSTEMTYPE)
GER(Fehlerhafter Koordinatensystemtyp.)
ENG(Invalid Coordinatesystem Type)

MID(0x2002,E,CS,INVALIDCOORDSYSTEM)
GER(Fehler im Koordinatensystem.)
ENG(Invalid Coordinatesystem.)

MID(0x2003,E,CS,UNKNOWNCOORDSYSTEM)
GER(Unbekanntes Koordinatensystem.)
ENG(Unknown Coordinatesystem.)

MID(0x2004,E,CS,INVALIDGEOGRAPHICSYSTEM)
GER(Fehlerhaftes geographisches System.)
ENG(Invalid geographic system.)

MID(0x2005,E,CS,INVALIDPROJECTEDSYSTEM)
GER(Fehlerhaftes projektives System.)
ENG(Invalid projected system.)

MID(0x2006,E,CS,INVALIDDATUMTRANSFORMATION)
GER(Fehlerhafte Datumstransformation.)
ENG(Invalid datum transformation.)

MID(0x2010,E,CS,FILENOTFOUND)
GER(Die angegebene Datei kann nicht gefunden werden.)
ENG(File not found.)

MID(0x2011,E,CS,FILECORRUPTED)
GER(Die angegebene Datei ist keine gültige Koordinatensystemdatei.)
ENG(Invalid Coordinatesystemfile.)

MID(0x2012,W,CS,NEWEROBJECT)
GER(Format des zu ladenden Objektes zu neu.)
ENG(Object data to load has (unknown) newer format.)

;///////////////////////////////////////////////////////////////////////////////
;// Fehler im geodätischen Koordinatensystem

MID(0x3001,E,GCS,INVALIDGEODETICDATUM)
GER(Fehlerhaftes geodätisches Datum.)
ENG(Invalid geodetic datum.)

MID(0x3002,E,GCS,INVALIDPRIMEMERIDIAN)
GER(Fehlerhafte Zentralmeridian.)
ENG(Invalid prime meridian.)

MID(0x3003,E,GCS,INVALIDELLIPSOID)
GER(Fehlerhaftes Ellipsoid.)
ENG(Invalid ellipsoid.)

MID(0x3009,E,GCS,INVALIDUNITOFANGLE)
GER(Fehlerhafte Winkeleinheit.)
ENG(Invalid Unit of Angle.)

;///////////////////////////////////////////////////////////////////////////////
;// Fehler im projektiven Koordinatensystem

MID(0x4001,E,PCS,INAVLIDPROJECTIONALGORITHM)
GER(Ungültiger Projektionsalgorithmus.)
ENG(Invalid Projectionalgorithm.)

MID(0x4002,E,PCS,INAVLIDUNITOFLENGTH)
GER(Ungültige Längeneinheit.)
ENG(Invalid Unit of Length.)

MID(0x4003,E,PCS,INAVLIDTRANSFORMATION)
GER(Fehler im Projektionskern.)
ENG(Error in projection kernel.)

MID(0x4004,E,PCS,INAVLIDPARAMETER)
GER(Fehlerhafte(r) Parameter im projektiven System.)
ENG(Invalid parameter(s) in projected System.)

MID(0x4010,E,PCS,TRANSFORMATIONFAILED)
GER(Transformation fehlgeschlagen.)
ENG(Transformation failed.)

;///////////////////////////////////////////////////////////////////////////////
;// Fehler im Datumstransformator

MID(0x5001,E,DTT,INAVLIDDATUMTRANSFORMATION)
GER(Ungültiger Algorithmus für die Datumstransformation.)
ENG(Invalid Algorithm for Datumtransformation.)

MID(0x5002,E,DTT,INAVLIDGEODETICDATUM)
GER(Ungültiges geodätisches Datum.)
ENG(Invalid geodetic Datum.)

MID(0x5003,E,DTT,INCOMPATIBLEDATUMTRANSFORMATION )
GER(Das Datumstransformationsverfahren im Quell und Zielsystem ist nicht kompatibel.)
ENG(Incompatible datum Transformation in Source and Destinationsystem.)

MID(0x5004,E,DTT,INAVLIDPARAMETER)
GER(Fehlerhafte(r) Parameter im Datumstransformator.)
ENG(Invalid parameter(s) in datum transformation.)

MID(0x5010,E,DTT,TRANSFORMATIONFAILED)
GER(Transformation fehlgeschlagen.)
ENG(Transformation failed.)

;///////////////////////////////////////////////////////////////////////////////
;// Fehler im Koordinatentransformator

MID(0x6001,E,CST,INVALIDCOORDSYSTEM)
GER(Ungültiges Koordinatensystem.)
ENG(Invalid Coordinatesystem.)

MID(0x6002,E,CST,INVALIDSOURCECOORDSYSTEM)
GER(Ungültiges Eingangskoordinatensystem.)
ENG(Invalid Input Coordinatesystem.)

MID(0x6003,E,CST,INVALIDDESTINATIONCOORDSYSTEM)
GER(Ungültiges Ausgangskoordinatensystem.)
ENG(Invalid Output Coordinatesystem.)

MID(0x6004,E,CST,COORDSYSTEMNOTFOUND)
GER(Das angegebene Koordinatensystem kann nicht gefunden werden.)
ENG(Unknown Coordinatesystem.)

MID(0x6005,E,CST,COORDSYSTEMALREADYPRESENT)
GER(Ein Koordinatensystem ist unter diesen GUID bereits eingetragen.)
ENG(A Coordinatesystem with this GUID is already present.)

MID(0x6006,E,CST,INCOMPATIBLEDATUMTRANSFORMATION)
GER(Inkompatible Datumstransformation.)
ENG(Incompatible Datumtransformation.)

MID(0x6011,E,CST,INVALIDCOORDCOUNT)
GER(Koordinatenanzahl fehlerhaft (keine {X,Y,Z} Tripel).)
ENG(Invalid Coordinatecount (no {X,Y,Z} tripels).)

MID(0x6012,E,CST,INPUTTRANSFORMATIONFAILED)
GER(Transformation aus dem Quellsystem fehlgeschlagen.)
ENG(Transformation from Source system failed.)

MID(0x6013,E,CST,OUTPUTTRANSFORMATIONFAILED)
GER(Transformation in das Zielsystem fehlgeschlagen.)
ENG(Transformation to Destination system failed.)

;///////////////////////////////////////////////////////////////////////////////
;// Fehler im StorageManager

MID(0x6004,E,STM,COORDSYSTEMNOTFOUND)
GER(Das angegebene Koordinatensystem kann nicht gefunden werden.)
ENG(Unknown Coordinatesystem.)

;///////////////////////////////////////////////////////////////////////////////
;// Fehler im Raw-Transformator

MID(0x7001,E,RCS,COMMON)
GER(Allgemeiner Fehler in der Transformationbibliothek.)
ENG(Common error in transform library.)

MID(0x7002,E,RCS,HA_NULL)
GER(Große Halbachse ist null.)
ENG(Semi major axis is null.)

MID(0x7003,E,RCS,F_NULL)
GER(Abplattung ist null.)
ENG(Flattening is null.)

MID(0x7004,E,RCS,SCALE_NULL)
GER(Skalierungsfaktor ist null.)
ENG(Scale factor is null.)

MID(0x7011,E,RCS,MODELPARAMETERS)
GER(Fehlerhafte Modellparameter.)
ENG(Invalid model parameters.)

MID(0x7101,E,RCS,SINGULAR)
GER(Singuläre Matrix.)
ENG(Singular matrix.)

MID(0x7102,E,RCS,BADPARALLEL)
GER(Equal Latitiudes for Standard Parallels on opposite sides of equator.)
ENG(Equal Latitiudes for Standard Parallels on opposite sides of equator.)

MID(0x7103,E,RCS,NOCONVERGENCE)
GER(Konvergenzfehler.)
ENG(Convergence error.)

MID(0x7104,E,RCS,CANTPROJECTPOINT)
GER(Punkt kann nicht projeziert werden.)
ENG(Point can not be projected.)

;///////////////////////////////////////////////////////////////////////////////
;// Fehler im DistanceService
MID(0x8001,E,CS,INVALIDACCURACYTYPE)
GER(Fehlerhafte Genauigkeitsgrundlage für Berechnungen.)
ENG(Invalid calculation accuracy.)


END(TRiASCoordSystems)
