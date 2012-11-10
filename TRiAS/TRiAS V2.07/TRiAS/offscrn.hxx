// OffScreenBuffer, über welchen gezeichnet wird ------------------------------
// File: OFFSCRN.HXX

#if !defined(_OFFSCRN_HXX)
#define _OFFSCRN_HXX

///////////////////////////////////////////////////////////////////////////////
// Objekt, welches OffScreenBuffer verkörpert und einerseits DrawObject 
// (wird gezeichnet) und andererseite Fenster ist (wird drauf gezeichnet)
class COffScreenBuffer : public DrawObject {
private:
	HBITMAP m_hBmp;
	
// FensterObjekt, auf welches zuerst gezeichnet wird (HBITMAP)
	class COffScreenDC : public CDCWindow {
	protected:
		bool DCExpose (CDCExposeEvt);

	public:
			COffScreenDC (HDC hDC, Rectangle &rc);
			~COffScreenDC (void);
	};
	COffScreenDC *m_pDCWnd;

// nur dynamisch über CreateInstance zu erzeugen
		COffScreenBuffer (void);

protected:
	void DrawEx (DWORD dwData);				// Zeichnen der GeoDB
//		{ m_pDCWnd -> DrawEx ((DrawObject *)&m_rDBO, dwData); }
	bool DrawCallUp (DrawObject *pDO, bool fForce);

public:
// sonstige Verwaltungsfunktionen
		~COffScreenBuffer (void);

static COffScreenBuffer *CreateInstance (IrisWind *pW);

	bool FInit (IrisWind *pW);		// Initialisierung mit FensterGröße


};

#endif // _OFFSCRN_HXX
