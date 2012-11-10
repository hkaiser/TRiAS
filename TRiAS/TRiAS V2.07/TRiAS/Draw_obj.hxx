// Datenbankobjekte (GeoPunkt, GeoKante, GeoFlaeche, GeoKO)
// File: DRAW_OBJ.HXX

// IRISWIN: %W% %E%

#ifndef _DRAW_OBJ_HXX
#define _DRAW_OBJ_HXX

#include <attribs.hxx>
#include <objliste.hxx>

#if !defined(NOEXTSHAPEOBJECT)

#if !defined(NOPUNKTOBJEKT)
// PunktObjekt ----------------------------------------------------------------
class PunktObjekt : 
	public ExtShapeObject 
{
private:
	GeoPunkt *_pGP;         	// Geometrie
	unsigned int _Marker;           // Markertyp
	Color _C;                       // Farbe
	short m_iRotation;		// Drehung
	Color m_SecC;			// zweite Farbe

protected:
	void DrawEx (DWORD);		// Punkt Zeichnen

public:
// Konstruktor
		PunktObjekt (GeoPunkt &, unsigned int MTyp = 1, Color *pC = NULL);

// Memberfunktionen
	Rectangle BoundingBox (void);	// Container (HiHi) WindowKoord
	void SetMarker (unsigned int MTyp) { _Marker = MTyp; }
	ObjTyp isTyp (void);
	Color ChangeColor (Color *newColor) 
		{ Color oldColor = _C; _C = *newColor; return oldColor;	}
	Color Change2ndColor (Color newColor) 
		{ Color oldColor = m_SecC; m_SecC = newColor; return oldColor;	}
	void SetRotation (short iRot) { m_iRotation = iRot; }
	short GetRotation (void) { return m_iRotation; }
	GeoPunkt &GP(void) const { return *_pGP; }

// Zeichenattribute setzen
	VisInfo *SetAttributes (CIdentifikator *pId, Dimension, CTable &, VisType = VT_Default, short = DF_Normal);
	void ResetAttributes (void);
	void TypeDependendDraw (CIdentifikator *, CTable &, Dimension);

// ObjektNummer und Identifikator liefern
	long &ObjNr (void);
	long &Id (void);

// Typkonvertierungen
	GeoObjekt *operator -> (void);
	operator GeoObjekt * (void);

// neue Geometrie 
	GeoObjekt *NewGI (GeoObjekt *pGO);

// Destruktor
		~PunktObjekt (void);
};
#endif // NOPUNKTOBJEKT

#if !defined(NOKANTENOBJEKT)
// KantenObjekt ---------------------------------------------------------------
class KantenObjekt : 
	public ExtShapeObject 
{
private:
	GeoKante *_pGK;         // Geometrie
	
protected:
	void DrawEx (DWORD);           // KanteZeichnen

public:
// Konstruktor
		KantenObjekt (GeoKante &, pPen = NULL);

// Memberfunktionen
	Rectangle BoundingBox ();       // KantenContainer in WindowKoord
	ObjTyp isTyp (void);
	GeoKante &GK (void) const { return *_pGK; }

// Zeichenattribute setzen
	VisInfo *SetAttributes (CIdentifikator *pId, Dimension, CTable &, VisType = VT_Default, short = DF_Normal);
	void ResetAttributes (void);

// ObjektNummer und Identifikator liefern
	long &ObjNr (void);
	long &Id (void);

// TypKonvertierungen
	GeoObjekt *operator -> (void);
	operator GeoObjekt * (void);

// neue Geometrie 
	GeoObjekt *NewGI (GeoObjekt *pGO);

// Destruktor
		~KantenObjekt (void);
};
#endif // NOKANTENOBJEKT

#if !defined(NOMASCHENOBJEKT)
// MaschenObjekt --------------------------------------------------------------
class MaschenObjekt : 
	public ExtShapeObject 
{
private:
	GeoFlaeche *_pGF;			// Geometrie
	short _iMode;
	Color m_BkCol;				// HintergrundFarbe für Opaque
	Bitmap *m_pBmp;

protected:
	void DrawEx (DWORD);		// Masche zeichen

public:
// Konstruktor
		MaschenObjekt (GeoFlaeche &, pPen = NULL, pBrush = NULL);

// Memberfunktionen
	Rectangle BoundingBox (void);	// MaschenContainer in WindowKoord
	ObjTyp isTyp (void);
	GeoFlaeche &GF (void) const { return *_pGF; }

// Zeichenattribute setzen
	VisInfo *SetAttributes (CIdentifikator *pId, Dimension, CTable &, VisType = VT_Default, short = DF_Normal);
	void ResetAttributes (void);
	void TypeDependendDraw (CIdentifikator *, CTable &, Dimension);

// ObjektNummer und Identifikator liefern
	long &ObjNr (void);
	long &Id (void);

// TypKonvertierungen
	GeoObjekt *operator -> (void);
	operator GeoObjekt * (void);

// neue Geometrie 
	GeoObjekt *NewGI (GeoObjekt *pGO);

	short isOpaque (void) { return _iMode & BMOpaque; }
	bool isBkConture (void) { return _iMode & BMBkConture; }
	void SetBkMode (short isOpaque);
	void SetBkConture (bool isBkConture);
	void SetBkColor (Color C) { m_BkCol = C; }
	Color GetBkColor (void) { return m_BkCol; }	
	void ChangeBitmap (Bitmap *pBmp) { m_pBmp = pBmp; }

	bool DrawNormal (HDC hDC, bool fForceHollow = false);	// normales Zeichnen
	bool FrameObject (HDC hDC);	// dieses Objekt ist ClipregionObj --> mit Frame versehen
	bool DrawTransparentWithPattern (HDC hDC);	// transparente patterns

// Destruktor
		~MaschenObjekt (void);
};
#endif // NOMASCHENOBJEKT

#if !defined(NODATENBASISOBJEKT)
typedef struct tagOBJSTATISTIK OBJSTATISTIK;
typedef struct tagOBJGEOMETRIE OBJGEOMETRIE;
typedef struct tagENUMRECHTEXTMERKMAL ENUMRECHTEXTMERKMAL;
typedef struct tagENUMRECHGEOMETRIE ENUMRECHGEOMETRIE;
typedef struct tagVISINFO VISINFO;

class ExtShapeObject;
class ExtShapeObjectDCreator;
class CIdentifikator;
class CIdRefLock;
class VisInfo;
class CViewsTree;

#if defined(WIN32)
#include <ospace/std/list>
typedef list<ObjContainer> CLoadedRects;
#endif // WIN32

// Klasse um DB zu zeichnen ---------------------------------------------------
class DatenBasisObjekt : 
	public ExtShapeObject 
{
private:
	PaintFlag _toPaint;             // darf gezeichnet werden
	unsigned int _MarkerTyp;        // Markertyp für PunktObjekt
	ObjContainer _DBOCont;          // Container des zu zeichnenden Objekts
					// (aktueller Bildausschnitt)
	PBD_DB m_pbdDB;					// zugehörige PBD
	
// BitmapStreifen, die die aktuellen Punktsymbole enthalten
	class CBitmapBar *m_pBmp15sw;	// Punktsymbole
	class CBitmapBar *m_pBmp23sw;
	class CBitmapBar *m_pBmp32sw;
	bool m_fNewPnts;
	short m_iBmpCnt;				// Anzahl der Punktsymbole
	LONG m_lObjCnt;					// Objektanzahl in GeoDB
	LONG m_lActScale;
	int m_iActLayer;				// derzeit gezeichneter Layer eines Identifikators

	class CMapPunktID *m_pPunktIDs;			// PunktID <--> iIndex
	class CMapIdentToClass *m_pClsIdents;	// Idents <--> ObjektklassenSchlüssel
					
public:
	CBitmapBar *GetBmp (unsigned int uiPntID, Dimension &dim) const;
	void LoadBitmapBars (void);

inline	bool FNewPnts (void) { return m_fNewPnts; }
inline	short FCntPnts (void) { return m_iBmpCnt; }
inline	CoOrd FHeight (unsigned int uiIndex) { return m_pBmp32sw -> FHeight (uiIndex); }
inline	CoOrd FWidth (unsigned int uiIndex) { return m_pBmp32sw -> FWidth (uiIndex); }
inline	int FGetIndex (WORD wPunktID) { return m_pPunktIDs -> FGetIndex (wPunktID); }
inline	WORD FGetPunktID (int iIndex) { return m_pPunktIDs -> FGetPunktID (iIndex); }
inline	CIndexMap &GetMap (void) const { return m_pPunktIDs -> GetMap(); }

inline int GetActLayer() { return m_iActLayer; }
inline void SetActLayer (int iActLayer) { m_iActLayer = iActLayer; }

protected:
	void DrawEx (DWORD);	// ganze DB Zeichnen
	ErrCode NextDraw (DWORD);	// weitere Male zeichnen

	ObjektListe *_Shapes;	// Liste aller Objekte
	CIdTree *_Idents;		// Liste aller zu zeichnenden Objekte
	GeoDB *_pGeoDB;			// DatenBasis
	Dimension _DotsPerMM;	// DotsPerMM des aktuellen Gerätes

	CoordTrans *_pCT;		// KoordinatenTransformation

// Menu, welches Ansichten enthält
	pMenu _SightMenu;		// Menu der Ansichten
	CViewsTree *m_pViews;	// Baum mit allen Sichten

	short _iDrawSem;		// diese DB wird derzeit gezeichnet
	
	short m_IdentBase;		// Zahlensystem des Idents
	short m_MCodeBase;		// Zahlensystem der MCodes

	Color m_cBkColor;		// HintergrundFarbe für dieses Projekt
	bool m_fToClose;		// Projekt wird derzeit geschlossen
	bool m_fPosTextAtBaseLine;		// Texte an Basislinie orientieren
	bool m_fIsFile;			// repräsentiert Datei
	bool m_fIsOpening;		// wird derzeit geöffnet
	bool m_fCompatibility16;	// OKS ist identisch mit Ident

	long m_lScaleMCode[VT_Text+1];		// MCodes für IdentScale
	long m_lObjGuidMCode;		// MCode für ObjektGuid (bis VERSION0500000B)

	IrisWind *m_pViewWnd;		// Zugehöriges ViewFenster

public:
// öffentliche Memberwerte
	ObjContainer ExposedArea;       // ungültiger Bildschirmbereich

// Konstruktor
		DatenBasisObjekt (void);
		DatenBasisObjekt (const GeoDB &, unsigned int MTyp, 
				  pPen pP = NULL, pBrush pB = NULL);

// Scalierung des Fensters
	bool Scale (Window *pW, ObjContainer &, Point &, Rectangle * = NULL);
#if defined(WIN32)
	bool SetActiveScaling (long lZoom, Rectangle &rRc, Rectangle &rCRc, ObjContainer &rOC);

private:
	CLoadedRects *m_pLoadedOC;
	bool m_fLoadMode;		// beim Zeichnen Objekte laden

public:
	bool IsLoadedRect (ObjContainer &rOC);		// Verwaltung der geladenen GeoDB-Bereiche
	bool AddLoadedRect (ObjContainer &rOC);
	void ResetLoadedRects (void);

	void SetLoadMode (bool fLoadMode) { m_fLoadMode = fLoadMode ? true : false; }
	bool GetLoadMode (void) { return m_fLoadMode; }
#endif // WIN32

// Memberfunktionen
	Rectangle BoundingBox (void);
	ErrCode GetGI (long ObjNr, ExtShapeObjectDCreator &, ExtShapeObject **, ObjContainer * = NULL);
	ErrCode GetGIAll (CIdRefLock &, bool fTest, DWORD);
	ErrCode KOGetGI (KomplexObjekt &, ExtShapeObjectDCreator &);
	PaintFlag toPaint (void) { return _toPaint; }

	void SetMarker (unsigned int MTyp) { _MarkerTyp = MTyp; }
	void SetExtend (Window *pW, ObjContainer &R, Point &);
	ObjContainer & GetExtend (void) const { return (ObjContainer &)_DBOCont; }
	PaintFlag SetPaintFlag (PaintFlag);

	void EveryDelete (void);

	ObjTyp isTyp (void);
	short GetActIdentObjTypes (LONG lIdent);

// liefert Objektliste
	ObjektListe &Shapes (void) const { return *_Shapes; }	// liefert ObjektListe
	CIdTree &Idents (void) const { return *_Idents; }	// liefert Id's
	ErrCode FillIdents (void);                      	// Idents füllen
	GeoDB &DB (void) { return *_pGeoDB; }			// liefert DB

#if defined(NOPRIORITY)
// Testen, ob dieses Objekt entspr. seinem Id gezeichnet werden soll
	bool toPaint (long Ident);
#endif

// Liefert GeoObjekt zu vorgegbener ON
	GeoObjekt *GetGeoObj (long ON);
	long PutGeoObj (GeoObjekt *, short iFlags);
	bool GetObjContainer (long, ObjContainer &);

// Funktionen zu Verwaltung der Ansichten
	pMenu SightMenu (void) { return _SightMenu; }

	bool InitSightMenu (pMenu pM, bool iStandard = true);
	bool AddItemToSightMenu (pMenu pM, LPCSTR pcView);
	bool AddItemToSightMenu (pMenu pM, LPCSTR pcView, UINT &ruiID);
	
	bool DeleteView (pMenu pM, char *pView);
	bool DeleteSightMenuItem (pMenu pM, LPCSTR Item);
	bool DeleteAllSightItems (pMenu pM);

	bool SetActiveSightName (LPCSTR pcView);
	bool GetActiveSightName (LPSTR cbBuffer, int iLen = -1);

	bool SetDefaultSightName (LPCSTR pcView);
	bool GetDefaultSightName (LPSTR cbBuffer, int iLen = -1);

	bool CheckItemAsActive (LPCSTR pcView);
	bool UnCheckItemAsActive (void);

	ErrCode WriteSightIDs (char *Sight, long *IDs, short numIDs, 
			       short *pTypInfo, Sicht * = NULL, 
			       short = 0, long = -1L);

	bool EnumSights (bool (*pFcn)(char *, bool, void *), void *);
	
	bool ProcessMenuEvent (UINT uiMenuID);
	bool ProcessMenuEvent (LPCSTR pcView, bool fForce);

	ErrCode SetActSichtCont (ObjContainer &);
	ErrCode GetActSichtCont (ObjContainer * = NULL, char *pView = NULL);
	ErrCode DelActSichtCont (void);
	bool hasSichtCont (void);

	bool _SightFlag;

	short OptTreeDelta;

	HDC Handle (Service s) { return DrawObject :: Handle (s); }
	Dimension &DotsPerMM (void) { return _DotsPerMM; }
	HRGN CreatePaintRegion (HDC hDC, Rectangle &, long);

// neue Geometrie 
	GeoObjekt *NewGI (GeoObjekt *) { return NULL; }
	bool ModIdent (long ONr, long newId, long oldId = -1L, short iTemp = 0);

// Zeichenattribute eines Objektes setzen/rücksetzen
	VisInfo *PresetAttributes (Window *pCanvas, long ONr);
	void ResetAttributes (void) {}
	bool ResetAttributes (long ONr, VisInfo *);

	CoordTrans * &pCT (void) { return _pCT; }

	bool QueryObjStatistik (OBJSTATISTIK *);
	bool QueryObjGeometrie (OBJGEOMETRIE *);
	bool ModObjGeometrie (OBJGEOMETRIE *);
	bool DeleteObjekt (long ONr, bool fUndo = false);

	GeoObjekt *MakeGI (OBJGEOMETRIE *, long *, long *);

	ObjTyp RetrieveObjTyp (long ONr);
	
	void EvalMasstab (Window *pW, double * = NULL);

	bool DeleteTempIdents (void);
	bool DeleteAllObjs (long Ident, short fToDelete, CTable &, CTable &);

	bool ActivateSight (char *pSight);                      

	bool EnumRechTextMerkmal (ENUMRECHTEXTMERKMAL *);
	bool EnumRechGeometrie (ENUMRECHGEOMETRIE *);

	short isDrawing (void) { return _iDrawSem; }
	short GetIdBase (void) { return m_IdentBase; }
	short GetMkBase (void) { return m_MCodeBase; }

	void SetIdBase (short newBase) { m_IdentBase = newBase; }
	void SetMkBase (short newBase) { m_MCodeBase = newBase; }

	bool RemoveTempIdents (void);
	ErrCode ReloadAllObjects (long lIdent);

	ErrCode ChangeVisInfo (long lIdent, short iVTyp, VISINFO &rVI, 
			       char *pView = NULL, short fBits = 0, bool fForce = false);
	ErrCode ChangeVisInfo (CIdentifikator &rId, VisType iVTyp, 
			       VisInfo *pVI, char *pView = NULL, short fBits = 0);
	ErrCode SaveVI (VisInfo *pVI, char *pView, long lIdent, 
					VisType iVTyp, short fBits, bool fTemp = false);

// Verwaltung der IdentMaßstabsBereiche
	bool RetrieveIdentScaleData (LPCSTR pcView, long lIdent, 
					VisType rgVTyp, long *plUpper, long *plLower);
	bool SetIdentScaleData (LPCSTR pcView, long lIdent, 
					VisType rgVTyp, long lUpper, long lLower);
	void ResetIdentScaleMCodes (bool fForce = false);

	ULONG QueryUnknownIdent (void);
	long FindObjFromName (char *);
		
// InitialisierungsFunktionen
	bool ReScale (Window *pW);
	bool ReReadIdents (void);

	bool QueryExposedOC (ObjContainer *pOC);
	bool QueryExposedArea (Rectangle *pRc);
	char *SetViewDesc (struct tagVIEWDESC *);
	char *QueryViewDesc (struct tagVIEWDESC *);
	
	void InitPbd (char *pDir, bool = false);
	ErrCode CloseDB (bool fCommit = true);
#if defined(WIN32)
	bool SaveAsGeoDB (LPCSTR pcName);
	bool ExportAsGeoDB (LPCSTR pcName);

// Zugehöriges ViewWindow behandeln
	IrisWind *AttachViewWindow (IrisWind *pViewWnd);

inline IrisWind *DetachViewWindow (void) { return AttachViewWindow (NULL); }
inline IrisWind *GetViewWindow (void) { return m_pViewWnd; }
#endif // WIN32

	bool EnumIdentViewsEx (ENUMLONGKEYEX *pENK);

// Export vornehmen
	ErrCode doExport (pWindow pW, ObjContainer *pOC = NULL, 
			  class ObjFeld *pObjs = NULL, pWindow pWaitParent = NULL);

	bool isComFile (void);

#if defined(WIN32)
	bool DeleteFeatures (LONG lONr);
	bool DeleteRelations (LONG lONr);

	bool ConvertRCToOC (double dX, double dY, long &rlX, long &rlY);
	bool ConvertOCToRC (long lX, long lY, double &rdX, double &rdY);
#endif

	long RetrieveIdent (LONG lONr);
	Color GetObjectColor (long lONr);
		
	Color GetBkColor (void) { return m_cBkColor; }
	void SetBkColor (Color cBkColor) { m_cBkColor = cBkColor; }

	bool isClosing (void) { return m_fToClose; }
	bool isOpeningOrClosing (void) { return m_fToClose || m_fIsOpening; }
	void toClose (bool fFlag = true) { m_fToClose = fFlag; }
	void isOpening (bool fFlag) { m_fIsOpening = fFlag; }

	long GetClipRegionONr (LPCSTR pcView);
	bool SetClipRegionONr (CLIPOBJECTSET *pCOS);

// Objektanzahl dieser GeoDB
	LONG CountObjects (void);
	LONG IncrementObjectCount (void);
	LONG DecrementObjectCount (void);
	LONG GetIdentObjectCount (IDENTOBJECTCOUNT *);

// Mapping Ident/Objektklassenschlüssel
	bool InitClsIdentMap (void);
	void DeleteClsIdentMap (void);
	HRESULT IdentFromClass(IDENTFROMCLASS *);
	HRESULT ClassFromIdent (CLASSFROMIDENT *);
	HRESULT ModObjClassCode (MODOBJCLASSCODE *);

// Priorität ändern/abfragen
	HRESULT GetIdentPriority (IDENTPRIORITY *pData);
	HRESULT SetIdentPriority (IDENTPRIORITY *pData);

// Objekt hervorheben/wieder normal zeichnen
	bool ActivateObj (Window *pWnd, long lONr, COLORREF crAct, bool fAssoc = true);
	bool DeActivateObj (Window *pWnd, long lONr, bool fAssoc = true);

// ObjektGuid verwalten
	HRESULT GetObjectGuid (OBJECTGUID *pGuid);
	HRESULT FindObjectFromGuid (OBJECTGUID *pGuid);
	HRESULT SetObjectGuid (OBJECTGUID *pGuid);

// aktuellen Maßstab
inline long GetActScale (void) { return m_lActScale; }
inline void SetActScale (long lActScale) { m_lActScale = lActScale; }

// diverse Infos am Ende wegschreiben
	bool SaveHeader (void);

// zugriff auf Member
inline	PBD_DB &PbdDB (void) { return m_pbdDB; }
inline	void PosTextAtBaseLine (bool fPos) { m_fPosTextAtBaseLine = fPos; }
inline	bool PosTextAtBaseLine (void) { return m_fPosTextAtBaseLine; }
inline	void Compatibility (bool fFlag) { m_fCompatibility16 = fFlag; }
inline	bool Compatibility (void) { return m_fCompatibility16; }

// Destruktor
		~DatenBasisObjekt (void);
};

const short GCFNormal 		= 0x00;
const short GCFAbort 		= 0x01;
const short GCFRepaint		= 0x02;
const short GCFAppClosed	= 0x04;

const UINT MAXSHOWNVIEWS = 20;		// max. Anzahl der Sichten im Menu

#endif // NODATENBASISOBJEKT
#endif // NOEXTSHAPEOBJEKT

const short WSActVis 	= 0x01;		// Konstanten für WriteSightIDs
const short WSDelView 	= 0x02;

#if !defined(LONGCOMP)
#define LONGCOMP
// Funktionen für ObjektListe : Tree (Zugriffs- und Vergleichsfunktionen) -----
inline int LongCmp (void *Key1, void *Key2) {
long Par1 = *(long *)Key1, Par2 = *(long *)Key2;
	if (Par1 > Par2)        return 1;
	else if (Par1 < Par2)   return -1;
	else                    return 0;
}
#endif // LONGCOMP

#endif // _DRAW_OBJ_HXX

