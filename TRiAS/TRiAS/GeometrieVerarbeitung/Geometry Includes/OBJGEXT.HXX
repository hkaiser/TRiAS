// Interfacedeklaration für Schnittstelle der Klasse "ObjektGeometrie"
// File: OBJGEXT.HXX

#if !defined (_OBJGEXT_HXX)
#define _OBJGEXT_HXX



// Implementation der Interfaces
class ObjektGeometrie;

// --------------------------------------------------------------------------------------------
// Klasse: CObjGeometrieInit
class CObjGeometrieInit : public IInitObjektGeometrie
{
private:
	DWORD m_dwRefCnt;
	ObjektGeometrie* m_pOG;
	LPUNKNOWN m_pIUnk;

protected:
	CObjGeometrieInit (LPUNKNOWN pIUnk, ObjektGeometrie* pOG);

bool FInit (void);

public:
	// nur dynamisch über "CreateInstance" zu generieren
	static CObjGeometrieInit* CreateInstance (LPUNKNOWN pIUnk, ObjektGeometrie* pOG);

		~CObjGeometrieInit (void);

	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);

	// IInitObjektGeometrie-Methoden
	STDMETHOD_ (HRESULT, InitObjGeometry) (VOID);
	STDMETHOD_ (HRESULT, InitObjGeometry) (LONG lONr);
	STDMETHOD_ (HRESULT, InitObjGeometry) (LONG x, LONG y, short iOT);
	STDMETHOD_ (HRESULT, InitObjGeometry) (LONG* x, LONG* y, LONG lAnz, short iOT);
};



// ------------------------------------------------------------------------------------------------
// Klasse: CObjGeometrieFunkt
class CObjGeometrieFunkt : public IObjektGeometrie
{
private:
	DWORD m_dwRefCnt;
	ObjektGeometrie* m_pOG;
	LPUNKNOWN m_pIUnk;

protected:
	CObjGeometrieFunkt (LPUNKNOWN pIUnk, ObjektGeometrie* pOG);

bool FInit (void);

public:
	// nur dynamisch über "CreateInstance" zu generieren
	static CObjGeometrieFunkt* CreateInstance (LPUNKNOWN pIUnk, ObjektGeometrie* pOG);

		~CObjGeometrieFunkt (void);

	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);

	// Memberfunction
	ObjektGeometrie* GetOG (void) { return m_pOG; }

	// IObjektGeometrie-Methoden
	STDMETHOD_ (HRESULT, GetONr) (LONG* plONr);
	STDMETHOD_ (HRESULT, GetIdent) (ULONG* pulIdent);
	STDMETHOD_ (HRESULT, SetIdent) (ULONG ulIdent);
	STDMETHOD_ (HRESULT, GetObjTyp) (short* piObjTyp);
	STDMETHOD_ (HRESULT, SetObjTyp) (short iObjTyp);
	STDMETHOD_ (HRESULT, GetFlags) (short* piFlags);
	STDMETHOD_ (HRESULT, SetFlags) (short iFlags);
	STDMETHOD_ (HRESULT, GetCnt) (LONG* plCnt);
	STDMETHOD_ (HRESULT, SetCnt) (LONG lCnt);
	STDMETHOD_ (HRESULT, GetKCnt) (short* piKCnt);
	STDMETHOD_ (HRESULT, SetKCnt) (short iKCnt);
	STDMETHOD_ (HRESULT, GetX) (VOID** ppX);
	STDMETHOD_ (HRESULT, SetX) (VOID* pX);
	STDMETHOD_ (HRESULT, GetY) (VOID** ppY);
	STDMETHOD_ (HRESULT, SetY) (VOID* pY);
	STDMETHOD_ (HRESULT, GetLPCnt) (LONG** pplCnt);
	STDMETHOD_ (HRESULT, SetLPCnt) (LONG* plCnt, short iCnt);
	STDMETHOD_ (HRESULT, GetVertexIndex) (LONG lX, LONG lY, LONG* plInd);
	STDMETHOD_ (HRESULT, GetLineIndex) (LONG lX, LONG lY, LONG lEps, LONG* plInd);
	STDMETHOD_ (HRESULT, AddPunkt) (LONG x, LONG y, LONG lIndGes, short iKInd);
	STDMETHOD_ (HRESULT, AddPunkt) (LONG* plX, LONG* plY, LONG lAnzahl, LONG lIndGes,
									short iKInd);
	STDMETHOD_ (HRESULT, AddKante) (LONG* x, LONG* y, LONG lSize, short iKontInd);
	STDMETHOD_ (HRESULT, AddKantenTeil) (IObjektGeometrie* pIOG, LONG lAnfId, LONG lEndId,
										 MoveDir MD);
	STDMETHOD_ (HRESULT, SubPunkt) (LONG lIndGes, short* piKInd);
	STDMETHOD_ (HRESULT, SubPunkt) (LONG lIndGes, BOOL bEqVertDel, short* piKInd);
	STDMETHOD_ (HRESULT, SubPunkt) (LONG lAnz, LONG lIndGes, BOOL bEqVertDel, short* piKInd);
	STDMETHOD_ (HRESULT, SubKante) (short iAnzahl, short iKontInd);
	STDMETHOD_ (HRESULT, ModPunkt) (LONG x, LONG y, LONG lIndGes);
	STDMETHOD_ (HRESULT, IndexTest) (LONG lIndGes, short* piKInd, LONG* plInd, IndPos* pipIP);
	STDMETHOD_ (HRESULT, IndexVorNach) (LONG lIndGes, LONG* plIndv, LONG* plIndn);
	STDMETHOD_ (HRESULT, IndexVor) (LONG lIndGes, LONG* plIndv);
	STDMETHOD_ (HRESULT, GetCont) (LONG* plXmin, LONG* plXmax, LONG* plYmin, LONG* plYmax);
	STDMETHOD_ (HRESULT, OrientDreh) (short iKInd);
	STDMETHOD_ (HRESULT, IsClear) (VOID);
	STDMETHOD_ (HRESULT, RectangleToDraw) (RECT* pRec);
	STDMETHOD_ (HRESULT, RectangleToDraw2) (RECT* pRec, int iMarkGr);
	STDMETHOD_ (HRESULT, GeometrieAnTRiAS) (BOOL bUndo, RECT* pRec);
	STDMETHOD_ (HRESULT, GeometrieAnTRiASEx) (INT_PTR hPr, BOOL bUndo, RECT* pRec);
	STDMETHOD_ (HRESULT, CursorPositionAtObject) (LONG x, LONG y, LONG lEpsX, LONG lEpsY,
					   LONG lEpsStr, BOOL bInBorder, CursPos* pCP, LONG* pGrabX, LONG* pGrabY);
	STDMETHOD_ (HRESULT, CursorInMarker) (LONG x, LONG y, LONG lEpsX, LONG lEpsY,
										  BOOL* pbInMark, LONG* pGrabX, LONG* pGrabY);
	STDMETHOD_ (HRESULT, CursorInObject) (LONG xLM, LONG yLM, LONG lEpsX, LONG lEpsY,
										  LONG lEpsLine, BOOL bInBorder, CursPos* pCP);
	STDMETHOD_ (HRESULT, GetPointOnObject) (LONG* plXP, LONG* plYP, LONG* plInd, BOOL* pbSP);
	STDMETHOD_ (HRESULT, Position) (LONG lX, LONG lY, BOOL bIsland, Posit* pLage);
};

// globale Funktionen
// Erzeugung von IObjektGeometrie-Objekten
_GEOMETR_ENTRY HRESULT CreateInterfaceOG (IObjektGeometrie** ppIOG, LONG lONr);
_GEOMETR_ENTRY HRESULT CreateInterfaceOG (IObjektGeometrie** ppIOG, LONG x, LONG y, int iOT);
_GEOMETR_ENTRY HRESULT CreateInterfaceOG (IObjektGeometrie** ppIOG, LONG* plX, LONG* plY,
										  LONG lAnz, int iOT);

// Flächeninhalt bestimmen
_GEOMETR_ENTRY BOOL AreaSize (KoOrd* plXK, KoOrd* plYK, long lAInd, long lEInd,
							  CoordTransX* pCT, double* pdFlInh);
_GEOMETR_ENTRY BOOL GetInhalt (IObjektGeometrie* pIOG, CoordTransX* pCT, double* pdFlInh);

// Punkt auf Objekt ziehen
_GEOMETR_ENTRY EPunkt NearestPointToObject (EPunkt Pkt, IObjektGeometrie* pIOG, LONG lAInd,
										  LONG lEInd, BOOL bOuter, LONG* plPInd, LONG* plSInd);

// Hilfsroutine für NearestPointToObject()
bool IslLinesegmentPermissible (IObjektGeometrie* pIOG, long lSInd);

#endif // _OBJGEXT_HXX
