// Deklaration der Klasse ObjektGeometrie
// File: OBJGEOM.HXX
// H. Kaiser, W. Mörtl


#ifndef _OBJGEOM_HXX
#define _OBJGEOM_HXX


// die Klasse ObjektGeometrie als ganzes kann nicht exportiert werden, weil dann die
// Basisklassen ebenfalls mit exportiert werden müßten
class ObjektGeometrie : public tagOBJGEOMETRIE, public IUnknown
{
private:
	DWORD m_dwRefCnt;				// Referenz-Zähler
	CObjGeometrieInit* m_pOGInit;
	CObjGeometrieFunkt* m_pOGFunc;
	DESTROYNOTIFYPROC* m_pFEnd;

protected:
		ObjektGeometrie (long lONrPar, DESTROYNOTIFYPROC* pFcn = 0);

public:
	bool FInit (LPUNKNOWN pIUnk = 0);
	bool FInit (long lONr);
	bool FInit (KoOrd x, KoOrd y, int iOT);
	bool FInit (KoOrd* x, KoOrd* y, long lAnz, int iOT);

		~ObjektGeometrie (void);

	// IUnknown-Methoden
	STDMETHOD (QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_ (ULONG, AddRef) (THIS);
	STDMETHOD_ (ULONG, Release) (THIS);

_GEOMETR_ENTRY static ObjektGeometrie* CreateInstance (LPUNKNOWN pIUnk,
													   DESTROYNOTIFYPROC* pFcn);
_GEOMETR_ENTRY static ObjektGeometrie* CreateInstance (long lONr);
_GEOMETR_ENTRY static ObjektGeometrie* CreateInstance (KoOrd x, KoOrd y, int iOT);

_GEOMETR_ENTRY bool AddPunkt (EPunkt& Pkt, long lIndGes = -1, int iKontInd = -1);
_GEOMETR_ENTRY bool AddPunkt (KoOrd* x, KoOrd* y, long lAnzahl, long lIndGes = -1,
							  int iKontInd = -1);
_GEOMETR_ENTRY bool AddKante (KoOrd* x, KoOrd* y, long lSize, int iKontInd);
_GEOMETR_ENTRY bool AddKantenTeil (IObjektGeometrie* pOG, long lAnfId, long lEndId,
								   MoveDir MD = MOVEDIR_UP);
_GEOMETR_ENTRY bool SubPunkt (long lIndGes, short& iKontInd);
_GEOMETR_ENTRY bool SubPunkt (long lIndGes, bool bEqVertDel, short& iKontInd);
_GEOMETR_ENTRY bool SubPunkt (long lAnz, bool bEqVertDel, long lIndGes, short& iKontInd);
_GEOMETR_ENTRY bool SubKante (int iAnzahl, int iKontInd);
_GEOMETR_ENTRY bool ModPunkt (EPunkt& Pkt, long lIndGes);
_GEOMETR_ENTRY bool GetVertexIndex (KoOrd lX, KoOrd lY, long& lInd);
_GEOMETR_ENTRY bool GetLineIndex (KoOrd lX, KoOrd lY, long lEps, long& lInd);
_GEOMETR_ENTRY IndPos IndexTest (long lIndGes, short& iKontInd, long& lInd);
_GEOMETR_ENTRY bool IndexVorNach (long lIndGes, long& lIndv, long& lIndn);
_GEOMETR_ENTRY bool IndexVor (long lIndGes, long& lIndv);
_GEOMETR_ENTRY ObjRechteck GetCont (void);
_GEOMETR_ENTRY bool OrientDreh (int iKInd = -1);
_GEOMETR_ENTRY HRESULT IsClear (void);
_GEOMETR_ENTRY CursPos CursorPositionAtObject (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY,
								   long lEpsStr, bool bInBorder, KoOrd& lGrabX, KoOrd& lGrabY);
CursPos CursorPositionAtPoint (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY, KoOrd& lGrabX,
							   KoOrd& lGrabY);
CursPos CursorPositionAtLine (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY, long lEpsStr,
							  KoOrd& lGrabX, KoOrd& lGrabY);
CursPos CursorPositionAtArea (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY, long lEpsStr,
							  bool bInBorder, KoOrd& lGrabX, KoOrd& lGrabY);
bool PunktInMarker (KoOrd xLM, KoOrd yLM, KoOrd XK, KoOrd YK, long lEpsX, long lEpsY);
bool PunktAnStrecke (KoOrd xLM, KoOrd yLM, KoOrd x1, KoOrd y1, KoOrd x2, KoOrd y2,
					 KoOrd& lAbst);
_GEOMETR_ENTRY bool CursorInMarker (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY, KoOrd& GrabX,
									KoOrd& lGrabY);
_GEOMETR_ENTRY CursPos CursorInObject (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY,
									   long lEpsLine, bool bInBorder);
CursPos CursorInPoint (KoOrd xLM, KoOrd yLM, long lEpsX, long lEpsY);
CursPos CursorInLine (KoOrd xLM, KoOrd yLM, long lEpsLine);
CursPos CursorInArea (KoOrd xLM, KoOrd yLM, bool bInBorder);
CursPos CursorInText (KoOrd xLM, KoOrd yLM);

};

#endif // _OBJGEOM_HXX
