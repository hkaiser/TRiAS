// Interfacedeklaration für Schnittstellen der Geometrie-Erweiterungen
// File: IGEOMETR.HXX

#ifndef _IGEOMETR_HXX
#define _IGEOMETR_HXX

#if _MSC_VER < 1100 && !defined(DECLSPEC_UUID)
#define DECLSPEC_UUID(x)
#endif // _MSC_VER < 1100 && !defined(DECLSPEC_UUID)


// --------------------------------------------------------------------------------------------
// Interfacedeklaration für Schnittstellen der Klasse "ObjektGeometrie"

#undef INTERFACE
#define INTERFACE IID_IInitObjektGeometrie

// 07963834-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IInitObjektGeometrie, 0x07963834L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA,
//			   0x00, 0x18, 0x49, 0x7C);

interface DECLSPEC_UUID("07963834-3123-101C-BB62-00AA0018497C")
IInitObjektGeometrie : IUnknown
{
	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvOBJ) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

	// IInitObjektGeometrie-Methoden
	STDMETHOD_ (HRESULT, InitObjGeometry) (VOID) PURE;
	STDMETHOD_ (HRESULT, InitObjGeometry) (LONG lONr) PURE;
	STDMETHOD_ (HRESULT, InitObjGeometry) (LONG x, LONG y, short iOT) PURE;
	STDMETHOD_ (HRESULT, InitObjGeometry) (LONG* plX, LONG* plY, LONG lAnz, short iOT) PURE;
};




#undef INTERFACE
#define INTERFACE IID_IObjektGeometrie

// 07963833-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IObjektGeometrie, 0x07963833L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00,
//			   0x18, 0x49, 0x7C);

// Position eines Indexes innerhalb des pOG->pdblX- bzw. pOG->pdblY-Vektors einer Fläche
enum IndPos
{
	ERSTER,		// erster Index
	MITTE,		// Index innerhalb einer Kontur
	LETZTER,	// letzter Index
	NICHTS		// pOG keine Fläche
};

#if !defined(_CURSPOS_DEFINED)	// auch in IGeoEdit.idl definiert
#define _CURSPOS_DEFINED
// CursorPosition bez. eines pOG-Objektes
enum CursPos
{
	CURSPOS_VERTEX,				// Cursor im Marker eines beliebigen Stützpunktes
	CURSPOS_FIRST_VERTEX,		// Cursor im Marker des ersten Stützpunktes
	CURSPOS_LAST_VERTEX,		// Cursor im Marker des letzten Stützpunktes
	CURSPOS_OUTBORDER_VERTEX,	// Cursor im Marker eines belieb. Stützpunktes der Außenkontur
	CURSPOS_INBORDER_VERTEX,	// Cursor im Marker eines belieb. Stützpunktes der Innenkontur
	CURSPOS_LINE,				// Cursor "in der Nähe" einer beliebigen Strecke
	CURSPOS_OUTBORDER,			// Cursor "in der Nähe" der Strecke der Außenkontur
	CURSPOS_INBORDER,			// Cursor "in der Nähe" der Strecke der Innenkontur
	CURSPOS_OBJECT,				// Cursor innerhalb eines Objektes
	CURSPOS_OUTSIDE,			// Cursor ohne Bezug zu einem Objekt
	CURSPOS_UNKNOWN				// unbekannte Cursorposition
};
#endif // _CURSPOS_DEFINED

// Durchlaufrichtung bei Übernahme einer Teilkante
enum MoveDir
{
	MOVEDIR_UP,		// mit aufsteigenden Stützpunkt-Indizes
	MOVEDIR_DOWN	// mit absteigenden Stützpunkt-Indizes
};

// Position eines Objektes zu einem Bezugsobjekt
enum Posit
{
	INNERH,		// vollständig innerhalb des Bezugsobjektes
	INNERHB,	// innerhalb des Bezugsobjektes ( = Fläche), aber mit Berührung des
				// Flächenrandes
	KONTUR,		// vollständig auf dem Rand des Bezugsobjektes
	AUSSERH,	// vollständig außerhalb des Bezugsobjektes
	AUSSERHB,	// außerhalb des Bezugsobjektes, aber mit Berührung des Bezugsobjektes
	INNAUSS,	// teilweise innerhalb, teilweise außerhalb des Bezugsobjektes
	UMSCHL,		// außerhalb des Bezugsobjektes, aber umschließt das Bezugsobjekt vollständig
				// (nur für geschlossenes Bezugsobjekt möglich)
	UMSCHLB,	// außerhalb des Bezugsobjektes, aber mit Berührung des Bezugsobjektes und
				// umschließt das Bezugsobjekt vollständig (nur für geschlossenes Bezugsobjekt
				// möglich)
	OFFEN,		// Rand des Bezugsobjektes ( = Fläche) nicht geschlossen
	UNKLAR,		// vorzeitiges Ende bei falschen Parametern, unzureichendem dynamischen
				// Speicher oder Abbruch durch den Anwender
	GLEICH		// beide Objekte sind identisch
};

interface DECLSPEC_UUID("07963833-3123-101C-BB62-00AA0018497C")
IObjektGeometrie : IUnknown
{
	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvOBJ) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

	// IObjektGeometrie-Methoden
	STDMETHOD_ (HRESULT, GetONr) (LONG* plONr) PURE;
	STDMETHOD_ (HRESULT, GetIdent) (ULONG* pulIdent) PURE;
	STDMETHOD_ (HRESULT, SetIdent) (ULONG ulIdent) PURE;
	STDMETHOD_ (HRESULT, GetObjTyp) (short* piObjTyp) PURE;
	STDMETHOD_ (HRESULT, SetObjTyp) (short iObjTyp) PURE;
	STDMETHOD_ (HRESULT, GetFlags) (short* piFlags) PURE;
	STDMETHOD_ (HRESULT, SetFlags) (short iFlags) PURE;
	STDMETHOD_ (HRESULT, GetCnt) (LONG* plCnt) PURE;
	STDMETHOD_ (HRESULT, GetKCnt) (short* piKCnt) PURE;
	STDMETHOD_ (HRESULT, SetKCnt) (short iKCnt) PURE;
	STDMETHOD_ (HRESULT, GetX) (VOID** ppX) PURE;
	STDMETHOD_ (HRESULT, GetY) (VOID** ppY) PURE;
	STDMETHOD_ (HRESULT, GetLPCnt) (LONG** pplCnt) PURE;
	STDMETHOD_ (HRESULT, AddPunkt) (LONG x, LONG y, LONG lIndGes, short iKInd) PURE;
	STDMETHOD_ (HRESULT, AddPunkt) (LONG* plX, LONG* plY, LONG lAnzahl, LONG lIndGes,
									short iKInd) PURE;
	STDMETHOD_ (HRESULT, AddKantenTeil) (IObjektGeometrie* pIOG, LONG lAnfId, LONG lEndId,
										 MoveDir MD) PURE;
	STDMETHOD_ (HRESULT, SubPunkt) (LONG lIndGes, short* piKInd) PURE;
	STDMETHOD_ (HRESULT, ModPunkt) (LONG x, LONG y, LONG lIndGes) PURE;
	STDMETHOD_ (HRESULT, IndexTest) (LONG lIndGes, short* piKInd, LONG* plInd, IndPos* pipIP)
									 PURE;
	STDMETHOD_ (HRESULT, IndexVorNach) (LONG lIndGes, LONG* plIndv, LONG* plIndn) PURE;
	STDMETHOD_ (HRESULT, IndexVor) (LONG lIndGes, LONG* plIndv) PURE;
	STDMETHOD_ (HRESULT, GetCont) (LONG* plXmin, LONG* plXmax, LONG* plYmin, LONG* plYmax)
								   PURE;
	STDMETHOD_ (HRESULT, OrientDreh) (short iKInd) PURE;
	STDMETHOD_ (HRESULT, GeometrieAnTRiAS) (BOOL bUndo, RECT* pRec) PURE;
	STDMETHOD_ (HRESULT, SetLPCnt) (LONG* plCnt, short iCnt) PURE;
	STDMETHOD_ (HRESULT, AddKante) (LONG* x, LONG* y, LONG lSize, short iKontInd) PURE;
	STDMETHOD_ (HRESULT, SubKante) (short iAnzahl, short iKontInd) PURE;
	STDMETHOD_ (HRESULT, IsClear) (VOID) PURE;
	STDMETHOD_ (HRESULT, SubPunkt) (LONG lAnz, LONG lIndGes, BOOL bEqVertDel, short* piKInd)
									PURE;
	STDMETHOD_ (HRESULT, RectangleToDraw) (RECT* pRec) PURE;
	STDMETHOD_ (HRESULT, SubPunkt) (LONG lIndGes, BOOL bEqVertDel, short* piKInd) PURE;
	STDMETHOD_ (HRESULT, CursorPositionAtObject) (LONG x, LONG y, LONG lEpsX, LONG lEpsY,
				LONG lEpsStr, BOOL bInBorder, CursPos* pCP, LONG* pGrabX, LONG* pGrabY) PURE;
	STDMETHOD_ (HRESULT, CursorInObject) (LONG xLM, LONG yLM, LONG lEpsX, LONG lEpsY,
										  LONG lEpsLine, BOOL bInBorder, CursPos* pCP) PURE;
	STDMETHOD_ (HRESULT, GetVertexIndex) (LONG lX, LONG lY, LONG* plInd) PURE;
	STDMETHOD_ (HRESULT, GetPointOnObject) (LONG* plXP, LONG* plYP, LONG* plInd, BOOL* pbSP)
											PURE;
	STDMETHOD_ (HRESULT, SetCnt) (LONG lCnt) PURE;
	STDMETHOD_ (HRESULT, SetX) (VOID* pX) PURE;
	STDMETHOD_ (HRESULT, SetY) (VOID* pY) PURE;
	STDMETHOD_ (HRESULT, GetLineIndex) (LONG lX, LONG lY, LONG lEps, LONG* plInd) PURE;
	STDMETHOD_ (HRESULT, Position) (LONG lX, LONG lY, BOOL bIsland, Posit* pLage) PURE;
	STDMETHOD_ (HRESULT, CursorInMarker) (LONG x, LONG y, LONG lEpsX, LONG lEpsY,
										  BOOL* pbInMark, LONG* pGrabX, LONG* pGrabY) PURE;
	STDMETHOD_ (HRESULT, RectangleToDraw2) (RECT* pRec, int iMarkGr) PURE;
	STDMETHOD_ (HRESULT, GeometrieAnTRiASEx) (INT_PTR hPr, BOOL bUndo, RECT* pRec) PURE;
};



// --------------------------------------------------------------------------------------------
// Interfacedeklaration für Schnittstelle zur Erweiterung "Abstandsmessung"

#undef INTERFACE
#define INTERFACE IExtendAbstand2

// 0796383C-3123-101C-BB62-00AA0018497C
// DEFINE_GUID(IID_IExtendAbstand2, 0x0796383CL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00,
//			   0x18, 0x49, 0x7C);

// verschiedene Formen der Abstandsbestimmung
enum DistTyp
{
	DISTTYP_AUTO,	// automatische Entscheidung über die Form der Abstandsbestimmung
	DISTTYP_MIDDLE,	// Abstand zwischen den Containermittelpunken der beiden Objekte
	DISTTYP_VERTEX,	// kürzeste Entfernung zwischen je einem Stützpunkt
	DISTTYP_EXACT	// kürzeste Entfernung bei Berücksichtigung der Punkte zwischen den
					// Stützpunkten
};

// Extrema bei der Abstandsbestimmung
enum ExtrAbst
{
	ABST_MIN,		// kleinster Abstand
	ABST_MAX,		// größter Abstand
	ABST_MAXMIN,	// größter der kleinsten Abstände
	ABST_MINMAX,	// kleinster der größten Abstände
};

// Seite für Verschiebung einer Teilkante
enum Side
{
	ABST_LEFT,		// linke Seite
	ABST_RIGHT,		// rechte Seite
};


interface DECLSPEC_UUID("0796383C-3123-101C-BB62-00AA0018497C")
IExtendAbstand2 : IUnknown
{
	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvOBJ) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

	// IExtendAbstand2-Methoden
	STDMETHOD_ (HRESULT, DistanceObjObj_ONr) (LONG lONr1, LONG lONr2, double* pdAbst,
											  DistTyp dtTyp, ExtrAbst exAbst) PURE;
	STDMETHOD_ (HRESULT, DistanceObjObj_Geom) (IObjektGeometrie* pIOG1,
				 IObjektGeometrie* pIOG2, double* pdAbst, DistTyp dtTyp, ExtrAbst exAbst) PURE;

	// kleinster bzw. größter Abstand der Objekte einer ulIdent-Objektklasse
	STDMETHOD_ (HRESULT, DistanceObjOClass_ONr) (LONG lONr, ULONG ulIdent, double* pdAbst,
											 DistTyp dtTyp, ExtrAbst exAbst, LONG* plONr) PURE;
	STDMETHOD_ (HRESULT, DistanceObjOClass_Geom) (IObjektGeometrie* pIOG, ULONG ulIdent,
							 double* pdAbst, DistTyp dtTyp, ExtrAbst exAbst, LONG* plONr) PURE;
	STDMETHOD_ (HRESULT, LinePart) (IObjektGeometrie* pIOGIn, LONG lXA, LONG lYA, LONG lXE,
									LONG lYE, double dDist, IObjektGeometrie** ppIOGOut) PURE;
	STDMETHOD_ (HRESULT, DistanceFromOrigin_Geom) (IObjektGeometrie* pIOG, LONG* plX,
												   LONG* plY, double* pdAbst) PURE;
	STDMETHOD_ (HRESULT, ShiftedLinePart) (IObjektGeometrie* pIOGIn, LONG lXA, LONG lYA,
										   double dLaenge, Side Seite, double* pdAbst,
										   ULONG ulIdent, IObjektGeometrie** ppIOGOut) PURE;
};

typedef IExtendAbstand2* LPEXTENDABSTAND;



// --------------------------------------------------------------------------------------------
// Interfacedeklaration für Schnittstelle zur Erweiterung "Puffer um GeoObjekte"

#undef INTERFACE
#define INTERFACE IExtendBuffer

// 0796383E-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IExtendBuffer, 0x0796383EL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00,
//			   0x18, 0x49, 0x7C);

// Ausformung der konvexen Ecken
enum ConvexMode
{
	BUFF_ARC,		// quasi-kreisförmig (n-Eck)
	BUFF_KITE,		// Drachenviereck
	BUFF_TIP,		// spitz
	BUFF_PLAIN		// abgeflacht
};

// Anzeige der Ergebnisse beim Objekt-Verschnitt
enum BuffSide
{
	BUFF_LEFT,		// linksseitiger Puffer
	BUFF_RIGHT,		// rechtsseitiger Puffer
	BUFF_BOTH		// beidseitiger Puffer
};

// Pufferaufbau
enum PuffBau
{
	PBAU_RING,	// Fläche mit Aussparung ("ringförmige" Form)
	PBAU_VOLL	// vollständige Fläche
};

// Form der Abspeicherung
enum SpForm
{
	SFORM_PERM,	// permanente Abspeicherung
	SFORM_TEMP	// temporäre Abspeicherung
};

// Puffer um ein GeoObjekt
interface DECLSPEC_UUID("0796383E-3123-101C-BB62-00AA0018497C")
IExtendBuffer : IUnknown
{
	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvOBJ) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

	// IExtendBuffer-Methoden
	// Pufferung des lONr-Objektes mit den Eingabeparametern
	// dWidth	 Pufferbreite (in Metern mit Kommastellen)
	// iCount    Pufferanzahl
	// bPBau     ringförmiger Puffer / volle Fläche
	// sfSForm   permanente / temporäre Abspeicherung
	// ulBIdent  Basis-Identifikator, aus dem die Identifikatoren der Pufferobjekte abgeleitet
	//           werden
	// In ppEnumOut werden die Objektnummern der erzeugten Puffer zurückgegeben.

	// echter Puffer um lONr-Objektes
	STDMETHOD_ (HRESULT, RealBuffering_ONr) (LONG lONr, double dWidth, short iCount,
					PuffBau bPBau, SpForm sfSForm, ULONG ulBIdent, IEnumLONG** ppEnumOut) PURE;

	// echter Puffer um lpIOG-Objektes
	STDMETHOD_ (HRESULT, RealBuffering_Geom) (IObjektGeometrie* pIOG, double dWidth,
					 short iCount, SpForm sfSForm, ULONG ulBIdent, IEnumLONG** ppEnumOut) PURE;

	// kreisförmiger Puffer um Mittelpunkt des Objektcontainers
	STDMETHOD_ (HRESULT, CircularBuffering_ONr) (LONG lONr, double dWidth, short iCount,
					PuffBau bPBau, SpForm sfSForm, ULONG ulBIdent, IEnumLONG** ppEnumOut) PURE;

	STDMETHOD_ (HRESULT, CircularBuffering_Geom) (IObjektGeometrie* pIOG, double dWidth,
					 short iCount, SpForm sfSForm, ULONG ulBIdent, IEnumLONG** ppEnumOut) PURE;

	// einzelner echter Puffer um lONr-Objekt
	STDMETHOD_ (HRESULT, WorkingBuffer_ONr) (LONG lONr, double dWidth, PuffBau bPBau,
						   BuffSide bsSide, ConvexMode cmMode, double dPrec, LONG* plONr) PURE;

	// einzelner echter Puffer um pInObj-Objekt, der NICHT in die DB gespeichert wird
	STDMETHOD_ (HRESULT, WorkingBuffer_Geom) (IObjektGeometrie* pInObj, double dWidth,
											 PuffBau bPBau, BuffSide bsSide, ConvexMode cmMode,
											 double dPrec, IObjektGeometrie** ppOutObj) PURE;
};

typedef IExtendBuffer* LPExtendBuffer;



// --------------------------------------------------------------------------------------------
// Interfacedeklaration für Schnittstelle zur Erweiterung "Editierung von GeoObjekten"

#undef INTERFACE
#define INTERFACE IExtendGeoEdit

// 07963831-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IExtendGeoEdit, 0x07963831L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00,
//             0x18, 0x49, 0x7C);

// Auswahl der Bezugsstrecke (mit fallender Priorität)
enum RefLine
{
	EDIT_RECTANGULAR,	// gemeinsame Strecke zu Objekten, die schon rechtwinklig gemacht
						// wurden
	EDIT_COMMON,		// gemeinsame Strecke zu Objekten vorgebbarer Objektklassen
	EDIT_LONGEST,		// die längste Strecke
	EDIT_SOUTHERN		// die südlichste Strecke
};

// Editierung von GeoObjekten
interface DECLSPEC_UUID("07963831-3123-101C-BB62-00AA0018497C")
IExtendGeoEdit : IUnknown
{
	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvOBJ) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

	// IExtendGeoEdit-Methoden
	STDMETHOD_ (HRESULT, MakeRectangular_ONr) (LONG lONr, RefLine rfLine, double dEps90,
			   double dEps180, double dEpsCom, IEnumLONG* pEnumIn, IEnumLONG** ppEnumOut) PURE;
};

typedef IExtendGeoEdit* LPExtendGeoEdit;
								


// --------------------------------------------------------------------------------------------
// Interfacedeklaration für Schnittstelle zur Erweiterung "Objektoperationen"

#undef INTERFACE
#define INTERFACE IExtendObjOper

// 0796381E-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IExtendObjOper, 0x0796381EL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00,
//             0x18, 0x49, 0x7C);

// auswählbare Lage für Lagebestimmung der Schnittergebnisse
#define LINN	0x01			// Objekt liegt innerhalb,
#define LAUSS	0x02			//  außerhalb,
#define LINAU	LINN | LAUSS	//	sowohl innerhalb als auch außerhalb,
#define LKONT	0x04			//  auf der Kontur des schneidenden Objektes

enum MoveDir;	// Definition siehe bei INTERFACE IID_IObjektGeometrie

interface DECLSPEC_UUID("0796381E-3123-101C-BB62-00AA0018497C")
IExtendObjOper : IUnknown
{
	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvOBJ) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

	// IExtendObjOper-Methoden
	// lONr-Objekt schneidet die Objekte, deren Objektnummern in pEnumIn übergeben werden;
	// das Bitmuster für Auswahl bei Schnittoperationen kann in dwLageAusw, die Speicherform in
	// sfSForm vorgegeben werden;
	// die Objektnummern der Ergebnis-Objekte werden in ppEnumOut zurückgegeben
	STDMETHOD_ (HRESULT, SectionObjObjs_ONr) (LONG lONr, IEnumLONG* pEnumIn, DWORD dwLageAusw,
											  SpForm sfSForm, IEnumLONG** ppEnumOut) PURE;

	// pIOG-Objekt schneidet die Objekte, deren Objektnummern in pEnumIn übergeben werden
	STDMETHOD_ (HRESULT, SectionObjObjs_Geom) (IObjektGeometrie* pIOG, IEnumLONG* pEnumIn,
								 DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut) PURE;

	// lONr-Objekt schneidet alle Objekte der ulIdent-Objektklasse
	STDMETHOD_ (HRESULT, SectionObjOClass_ONr) (LONG lONr, ULONG ulIdent, DWORD dwLageAusw,
												SpForm sfSForm, IEnumLONG** ppEnumOut) PURE;

	// pIOG-Objekt schneidet alle Objekte der ulIdent-Objektklasse
	STDMETHOD_ (HRESULT, SectionObjOClass_Geom) (IObjektGeometrie* pIOG, ULONG ulIdent,
								 DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut) PURE;

	// pIOG-Kante schneidet lONr-Objekt
	STDMETHOD_ (HRESULT, SectionLineObj_Geom) (IObjektGeometrie* pIOG, LONG lONr,
											   IEnumLONG** ppEnumOut) PURE;

	// pIOG-Kante schneidet alle Objekte der ulIdent-Objektklasse
	STDMETHOD_ (HRESULT, SectionLineObjs_Geom) (IObjektGeometrie* pIOG, ULONG ulIdent,
												IEnumLONG** ppEnumOut) PURE;

	// Durchschnitt der Flächen, deren Objektnummern in pEnumIn übergeben werden
	STDMETHOD_ (HRESULT, AndArea) (IEnumLONG* pEnumIn, ULONG ulIdent, SpForm sfSForm,
								   IEnumLONG** ppEnumOut) PURE;

	// Vereinigung der Flächen, deren Objektnummern in pEnumIn übergeben werden
	STDMETHOD_ (HRESULT, OrArea) (IEnumLONG* pEnumIn, ULONG ulIdent, SpForm sfSForm,
								  IEnumLONG** ppEnumOut) PURE;

	// Exklusiv-Oder der lONr-Fläche mit allen Flächen, deren Objektnummern in pEnumIn
	// übergeben werden
	STDMETHOD_ (HRESULT, XorArea_ONr) (LONG lONr, IEnumLONG* pEnumIn, SpForm sfSForm,
									   IEnumLONG** ppEnumOut) PURE;

	// Exklusiv-Oder der pIOG-Fläche mit allen Flächen, deren Objektnummern in pEnumIn
	// übergeben werden
	STDMETHOD_ (HRESULT, XorArea_Geom) (IObjektGeometrie* pIOG, IEnumLONG* pEnumIn,
										SpForm sfSForm, IEnumLONG** ppEnumOut) PURE;

	// gemeinsame Konturabschnitte (Kanten) der lONr-Fläche mit allen pEnumIn-Flächen
	STDMETHOD_ (HRESULT, CommonContour_ONr) (LONG lONr, ULONG ulIdent, IEnumLONG* pEnumIn,
								 DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut) PURE;

	// gemeinsame Konturabschnitte (Kanten) der pIOG-Fläche mit allen pEnumIn-Flächen
	STDMETHOD_ (HRESULT, CommonContour_Geom) (IObjektGeometrie* pIOG, ULONG ulIdent,
			 IEnumLONG* pEnumIn, DWORD dwLageAusw, SpForm sfSForm, IEnumLONG** ppEnumOut) PURE;

	// Linienobjekte werden zu möglichst gemeinsamen Linienobjekten vereinigt
	STDMETHOD_ (HRESULT, LinesUnion) (IEnumLONG* pEnumIn, ULONG ulIdent, ULONG ulFill,
									 BOOL bAsArea, SpForm sfSForm, IEnumLONG** ppEnumOut) PURE;

	// 2 Linienobjekte werden (möglichst) zu einem gemeinsamen Linienobjekt vereinigt
	STDMETHOD_ (HRESULT, LinesUnion_Geom) (IObjektGeometrie* pIOGIn1,
										 IObjektGeometrie* pIOGIn2, ULONG ulFill, BOOL bAsArea,
										 ULONG ulIdent, IObjektGeometrie** ppIOGOut) PURE;

	// Splitten aller Objekte, deren Objektnummern in pEnumIn übergeben werden
	STDMETHOD_ (HRESULT, Splitting) (IEnumLONG* pEnumIn, ULONG ulFuzzyX, ULONG ulFuzzyY,
					  ULONG ulDangle, IEnumLONG** ppEnumOutNew, IEnumLONG** ppEnumOutMod) PURE;

	// Verschieben des lONr-Objektes
	STDMETHOD_ (HRESULT, LineShifting_ONr) (LONG lONr, LONG lXB, LONG lYB, LONG lXA, LONG lYA,
						   LONG lXE, LONG lYE, MoveDir MD, BOOL bVerlA, BOOL bVerlE, LONG lEps,
						   LONG lXMin, LONG lYMin, LONG lXMax, LONG lYMax, LONG* plONr) PURE;

	// Verschieben des pIOG-Objektes
	STDMETHOD_ (HRESULT, LineShifting_Geom) (IObjektGeometrie* pIOG, LONG lXB, LONG lYB,
				  LONG lXA, LONG lYA, LONG lXE, LONG lYE, MoveDir MD, BOOL bVerlA, BOOL bVerlE,
				  LONG lEps, LONG lXMin, LONG lYMin, LONG lXMax, LONG lYMax, LONG* plONr) PURE;

	// Die pEnumRegard-Objekte schneiden die pEnumTarget-Objekte; die wirklich geschnittenen
	// Originalobjekte werden in ppEnumUsed zurückgegeben, die neu erzeugten Objekte in
	// ppEnumNew
	STDMETHOD_ (HRESULT, ObjectSection) (HPROJECT hPr, IEnumLONG* pEnumRegard,
							   IEnumLONG* pEnumTarget, DWORD dwLage, BOOL bFeat, BOOL bFortAnz,
							   IEnumLONG** ppEnumUsed, IEnumLONG** ppEnumNew) PURE;
};

typedef IExtendObjOper* LPExtendObjOPer;



// --------------------------------------------------------------------------------------------
// Interfacedeklaration für Schnittstelle zur Erweiterung "Topologische Relationen"

#undef INTERFACE
#define INTERFACE IExtendTopRel2

// 0796383D-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IExtendTopRel2, 0x0796383DL, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00,
//			   0x18, 0x49, 0x7C);

// TRiAS-Relation eines Objektes zu einem Bezugsobjekt
enum Relat
{
// TRiAS-Relationen (im niederwertigen Byte)
	REL_INN,	// vollständig innerhalb des Bezugsobjektes (alle Punkte des Objektes sind auch
				// Punkte des Bezugsobjektes)
	REL_AUSS,	// vollständig außerhalb des Bezugsobjektes (kein einziger Punkte des Objektes
				// ist auch Punkt des Bezugsobjektes)
	REL_INAUS,	// Objekt liegt sowohl innerhalb als auch außerhalb des Bezugsobjektes (es gibt
				// sowohl Punkte des Objektes, die zum Bezugsobjekt gehören, als auch Punkte,
				// die nicht zum Bezugsobjekt gehören)
	REL_UNKLAR,	// Relation nicht bestimmbar, z. B. durch unzureichenden dynamischen Speicher

// OGC-Relationen (im höherwertigen Byte)
	REL_WITHIN = 0x0100,	// vollständig innerhalb des Bezugsobjektes
	REL_CONTAIN = 0x0200,	// überdeckt das Bezugsobjekt vollständig
	REL_OVERLAP = 0x0400,	// teilweise innerhalb, teilweise außerhalb des Bezugsobjektes
							// (nur für die Kombinationen Linie/Linie und Fläche/Fläche; der
							// Durchschnitt beider Objekte muß die gleiche Dimension wie die
							// Vergleichsobjekte haben)
	REL_ENTER = 0x0800,		// teilweise innerhalb, teilweise außerhalb des Bezugsobjektes (nur
							// für die Kombinationen Linie/Linie, Linie/Fläche und
							// Fläche/Linie; der Durchschnitt beider Objekte muß eine geringere
							// Dimension wie die größere der beiden Dimensionen der
							// Vergleichsobjekte haben)
	REL_TOUCH = 0x1000,		// berührt das Bezugsobjekt von außen
	REL_EQUAL = 0x2000,		// vollständig identisch mit dem Bezugsobjekt
	REL_DISJOINT = 0x4000,	// keinerlei Gemeinsamkeiten mit dem Bezugsobjekt
	REL_INTERSECT = REL_WITHIN | REL_CONTAIN | REL_OVERLAP | REL_ENTER | REL_TOUCH | REL_EQUAL,
							// mindestens ein Punkt mit dem Bezugsobjekt gemeinsam
							// (NOT DISJOINT)
	REL_UNCLEAR = 0x8000	// Relation nicht bestimmbar, z. B. durch vorzeitiges Ende bei
							// falschen Parametern, unzureichendem dynamischen Speicher oder
							// Abbruch durch den Anwender
};


interface DECLSPEC_UUID("0796383D-3123-101C-BB62-00AA0018497C")
IExtendTopRel2 : IUnknown
{
	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvOBJ) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

	// IExtendTopRel2-Methoden
	STDMETHOD_ (HRESULT, TopoRelationObjObj_ONr) (LONG lONr1, LONG lONr2, Relat* prTR) PURE;
	STDMETHOD_ (HRESULT, TopoRelationObjObj_Geom) (IObjektGeometrie* pIOG1,
												   IObjektGeometrie* pIOG2, Relat* prTR) PURE;
	STDMETHOD_ (HRESULT, GetObjectsObj_ONr) (LONG lONr, Relat rTR, IEnumLONG** ppEnumOut) PURE;
	STDMETHOD_ (HRESULT, GetObjectsObj_Geom) (IObjektGeometrie* pIOG, Relat rTR,
											  IEnumLONG** ppEnumOut) PURE;

	STDMETHOD_ (HRESULT, TopoRelationObjObj2_ONr) (LONG lONr1, LONG lONr2, UINT* puiTR) PURE;
	STDMETHOD_ (HRESULT, TopoRelationObjObj2_Geom) (IObjektGeometrie* pIOG1,
													IObjektGeometrie* pIOG2, UINT* puiTR) PURE;
	STDMETHOD_ (HRESULT, GetPointInsideArea_ONr) (LONG lONr, double* pdInX, double* pdInY)
												  PURE;
	STDMETHOD_ (HRESULT, GetPointInsideArea_Geom) (IObjektGeometrie* pIOG, double* pdInX,
												  double* pdInY) PURE;
};

typedef IExtendTopRel2* LPExtendTopRel;



// --------------------------------------------------------------------------------------------
// Interfacedeklarationen für Schnittstelle zur Erweiterung "Geometriebereinigung"

#undef INTERFACE
#define INTERFACE IExtendGeoRein

// 07963840-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IExtendGeoRein, 0x07963840L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00,
//			   0x18, 0x49, 0x7C);

#if !defined(_TESTRICHT_DEFINED)	// auch in IGeoEdit.idl definiert
#define _TESTRICHT_DEFINED
// Wahlmöglichkeiten bei verkürztem Test auf Geometriefehler
enum TestRicht
{
	VORW,		// Test nur mit der Strecke, die mit dem Bezugsindex und dessen Nachfolger
				// gebildet wird
	RUECKW,		// Test nur mit der Strecke, die mit dem Bezugsindex und dessen Vorgänger
				// gebildet wird
	VORRUECK,	// Test nur mit den zwei Strecken, die mit dem Bezugsindex und sowohl dessen
				// Vorgänger als auch dessen Nachfolger gebildet werden
	OHNE		// kein Test auf Geometriefehler
};
#endif // _TESTRICHT_DEFINED


// Anzeige der Ergebnisse beim Objekt-Verschnitt
enum ErrorTextMode
{
	REIN_NOTHING,	// Fehlertext an keines der beiden Objekte wegschreiben
	REIN_FIRST,		// Fehlertext an das erste Objekt wegschreiben
	REIN_SECOND,	// Fehlertext an das zweite Objekt wegschreiben
	REIN_BOTH		// Fehlertext an beide Objekte wegschreiben
};


interface DECLSPEC_UUID("07963840-3123-101C-BB62-00AA0018497C")
IExtendGeoRein : IUnknown
{
	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvOBJ) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

	// IExtendGeoRein-Methoden
	STDMETHOD_ (HRESULT, WholeAnalysis_ONr) (LONG lONr, BOOL* pbSucc) PURE;
	STDMETHOD_ (HRESULT, WholeAnalysis_Geom) (IObjektGeometrie* pIOG, BOOL* pbSucc) PURE;
	STDMETHOD_ (HRESULT, ShortAnalysis) (IObjektGeometrie* pIOG, TestRicht trRicht,
										 LONG* plSInd) PURE;
	STDMETHOD_ (HRESULT, InterObjectsAnalysis_ONr) (LONG lONr1, LONG lONr2,
													ErrorTextMode etText, BOOL* pbSucc) PURE;
	STDMETHOD_ (HRESULT, InterObjectsAnalysis_Geom) (IObjektGeometrie* pIOG1,
							 IObjektGeometrie* pIOG2, ErrorTextMode etText, BOOL* pbSucc) PURE;
	STDMETHOD_ (HRESULT, ReducedGeometryCleaning) (IObjektGeometrie* pIOG) PURE;
};

typedef IExtendGeoRein* LPEXTENDGEOREIN;




#undef INTERFACE
#define INTERFACE IAdjustValues

// 07963841-3123-101C-BB62-00AA0018497C	
// DEFINE_GUID(IID_IAdjustValues, 0x07963841L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00,
//             0x18, 0x49, 0x7C);


// Abfrage bzw. Modifizierung von einstellbaren Parametern
enum AdjValue
{
	REIN_DEFAULT,		// für alle Parameter die default-Werte einstellen
	REIN_AUTOCLEAR,		// automatische bzw. keine Bereinigung von Geometriefehlern
	REIN_DOUBLE,		// Grenzwert für Test auf "doppelte Punkte"
	REIN_ACUTEANGLE,	// Grenzwert für Test auf "Spitze"
	REIN_VERTREDUCE		// Wert für die Reduzierung der Stützpunktanzahl
};


interface DECLSPEC_UUID("07963841-3123-101C-BB62-00AA0018497C")
IAdjustValues : IUnknown
{
	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvOBJ) PURE;
	STDMETHOD_ (ULONG, AddRef) (THIS) PURE;
	STDMETHOD_ (ULONG, Release) (THIS) PURE;

	// IAdjustValues-Methoden
	STDMETHOD_ (HRESULT, GetAdjustValue) (AdjValue avKey, LONG* plValue) PURE;
	STDMETHOD_ (HRESULT, SetAdjustValue) (AdjValue avKey, LONG lValue) PURE;
};

typedef IAdjustValues* LPAdjustValues;


#endif // _IGEOMETR_HXX
