// Zeichnen eines GeoDB-Ausschnittes in einen beliebigen hDC ------------------
// File: RENDERDB.HXX

#if !defined(_RENDERDB_HXX)
#define _RENDERDB_HXX

class CDirisDCWindow : public CDCWindow {
private:
	DatenBasisObjekt &m_rDBO;
	Window *m_pOldWnd;

	Point m_ptAspect;
	ObjContainer m_ocExtend;	// GeoDB-Auschnitt
	Rectangle m_rcActRect;		// Ausschnitt im Zielkontext
	Rectangle m_rcClipRect;		// aktuelles ClippingRechteck
		
protected:
	BOOL DCExpose (CDCExposeEvt);

public:
		CDirisDCWindow (RENDERGEODB *pRDB, 
				DatenBasisObjekt &rDBO, 
				Rectangle &rcC, Rectangle &rcClip);
		~CDirisDCWindow (void);
		
	void OldWnd (pWindow pW) { m_pOldWnd = pW; }
	pWindow OldWnd (void) { return m_pOldWnd; }
	
	Rectangle &ClipRect (void) { return m_rcClipRect; }
};

// sonstige FunktionsPrototypen -----------------------------------------------
Dimension GetDotsPerMM (HDC hDC);
Point GetAspectRatio (HDC hDC);
Rectangle EvalCanvasRect (RECTL *, Dimension);

#endif // _RENDERDB_HXX

