// Implementation des CustomVisualisationInterfaces ---------------------------
// File: IMPCUSTM.HXX


#if !defined(_IMPCUSTM_HXX)
#define _IMPCUSTM_HXX

extern "C" {
// Type for an object-destroyed callback --------------------------------------
	typedef void (FAR PASCAL *LPFNDESTROYED)(void);
}


class CVisModule : public IUnknown {
friend class CTortenVisModule;
protected:
	ULONG           m_cRef;         // Object reference count.
	LPUNKNOWN       m_punkOuter;    // Controlling Unknown for aggregation

	LPFNDESTROYED   m_pfnDestroy;   // Function to call on closure.
	LPVISMODULE     m_pIVisModule;  // Contained interface implemetation

public:
		CVisModule (LPUNKNOWN, LPFNDESTROYED);
		~CVisModule (void);

	BOOL FInit(void);

public:
// Non-delegating object IUnknown
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG,AddRef) (THIS);
	STDMETHOD_(ULONG,Release) (THIS);
};
typedef CVisModule * LPCVisModule;


// Balkentypen ----------------------------------------------------------------
typedef enum tagBALKENMODE {
	BMNormal = 0,		// linear
	BMLog = 1,		// logarithmisch
	BMExp = 2,		// exponentiell
} BALKENMODE;

// Implementation des VisualisierungsInterfaces -------------------------------
class CTortenVisModule : public IVisModule {
private:
	ULONG		m_cRef;         // Interface reference count.
	LPVOID		m_pObj;         // Back pointer to the object.
	LPUNKNOWN	m_punkOuter;    // Controlling unknown for delegation

	class ResourceFile 	*m_pRF;		// diese Datei
	
	class CVisPaletteTree	*m_pPalT;	// Baum aller Paletten dieses Projektes
	char 		*m_pActProject;	
	
	HPALETTE 	m_hPal;		// Palette des Hauptfensters

public:
	        CTortenVisModule (LPVOID, LPUNKNOWN);
        	~CTortenVisModule (void);
        	
        BOOL FInit (void);

// InterfaceFunktionen --------------------------------------------------------
// *** IUnknown methods ***
	STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* ppvObj);
	STDMETHOD_(ULONG,AddRef) (THIS);
	STDMETHOD_(ULONG,Release) (THIS);

// *** Own Methods ***
	STDMETHOD(QueryParameters) (THIS_ HWND hWnd, long lONr, 
				    class VisInfo *pVI, char *pVisStr,
				    char *pBuffer, short iLen, short *piOTypes);
	STDMETHOD(SymbolizeObject) (THIS_ HWND hWnd, long &rlONr, short &iOType,
				    char *pBuffer, short iLen);
	STDMETHOD(DrawObject) (THIS_ HWND hWnd, HDC hDC, HDC hTargetDC, 
			       long lONr, short &fDrawFlags, 
			       class VisInfo *pVI, char *pVisString);
	STDMETHOD_(void,OnProjectChange)(THIS_ HWND hWndM, PROJECTCHANGE rgPC, char *pPrName);
	STDMETHOD_(void,OnViewChange)(THIS_ HWND hWndM, VIEWCHANGE rgVC, char *pView);
	STDMETHOD_(void,OnPaletteChange)(THIS_ HWND hWndM, HPALETTE hPal);

// sonstige Member ------------------------------------------------------------
protected:
	HRESULT ParseVisString (HWND __hWnd, char *pVisString, long lONr, 
				short *pCnt, char ***pppMWerte, char &cDel);
	short GetSectors (char **ppMWerte, short iCnt, 
			  long &lRadius, long *pSectors, char cDel);
	HRESULT GetPoint (HWND hWnd, long lONr, POINT *pszPoint);
	BOOL EvalSize (HWND hWnd, HDC hTargetDC, 
		       long lRadius, SIZE *pSize);
	BOOL ReadTextMerkmal (HWND hWnd, short iTTyp, long lTarget, 
			      long lMCode, char *pText);
	OBJGEOMETRIE *GetObjectGeometrie (HWND hWnd, long lONr);

// Zeichenfunktionen
	BOOL DrawTorte (class VisInfo *pVI, HDC hDC, HDC hTargetDC, POINT szPoint, 
			SIZE szSize, int iSectors, 
			long *pSectors, char **ppMWerte);
	BOOL DrawBalkenHochPos (VisInfo *pVI, HDC hDC, HDC hTargetDC, POINT szPoint, 
				SIZE szSize, short iSectors, 
				long *pSectors, char **ppMWerte, BALKENMODE);
// PalettenHandling
	BOOL SavePalettes (HWND hWndM);
	HRESULT OpenProjectPaletteStorage (HWND hWndM, char *pPrName, 
					   LPSTORAGE *ppIStorage);
	class CVisPalette *DefinitelyGetPalette (VisInfo *pVI, BOOL &fTempPal);

public:
	BOOL DrawGraphic (VisInfo *pVI, HDC hDC, HDC hTargetDC, 
			  POINT szPoint, SIZE szSize,
			  short iSectors, long *pSectors, char **ppMWerte);
};
typedef CTortenVisModule * LPIMPIVISMODULE;


// sonstige Funktionen --------------------------------------------------------
BOOL EvalSchwerPunkt (OBJGEOMETRIE *pOG, POINTL *pszPt);
void dtOBJGEOMETRIE (OBJGEOMETRIE *& pOG);
void CalcTextPosition (int i, RECT *pRc, CoOrd &xT, CoOrd &yT, double dArc, SIZE szText);

extern "C" LPSTR FAR PASCAL DtoA (LPSTR String, LPSTR Format, double Wert);

// Typen, die durch diesen VisModule unterstützt werden -----------------------
#define TORTEN_FULLCIRCLE	0	// volle KreisTorte
#define TORTEN_UPPERHALF	1	// untere HalbkreisTorte
#define TORTEN_LOWERHALF	2	// obere HalbkreisTorte

#define TORTEN_BALKENHOCHPOS	10	// Balken hochkant nach oben
#define TORTEN_BALKENHOCHPOSLOG	11	// Balken hoch, logarithmisch
#define TORTEN_BALKENROT	12	// Balken drehbar 
#define TORTEN_BALKENROTLOG	13	// Balken drehbar, logarithmisch

#define TORTEN_BALKENHOCHPOSEXP	14	// Säule hoch, exponentiell

#define TORTEN_BALKENHOCHNEG	15	// Balken hochkant nach unten
#define TORTEN_BALKENQUERPOS	16	// Balken quer nach rechts
#define TORTEN_BALKENQUERNEG	17	// Balken quer nach links

#define TORTEN_SAEULEHOCH	20	// Säule hoch
#define TORTEN_SAEULEQUER	21	// Säule quer

#define TORTEN_TYPEMASK		0xff	// Maske für Darstellungstypen

#define TORTEN_OFFSET		0x100	// Diagramm mit Offset versehen
#define TORTEN_TEXTSABS		0x200	// Werte als Texte mit anzeigen
#define TORTEN_TEXTSREL		0x400	// Werte als Prozente anzeigen
#define TORTEN_BIGFONT		0x800	// großer Font für Beschriftung

#define VALUE_SCALING		1000.0	// Wert um den intern skaliert wird

// Farbtabelle für Grafiken ---------------------------------------------------
extern COLORREF FAR crefPieColors[];
#define MAXPIECOLORS    16		// Anzahl der StandardFarben
#define PI		3.14159265359

#endif // _IMPCUSTM_HXX

