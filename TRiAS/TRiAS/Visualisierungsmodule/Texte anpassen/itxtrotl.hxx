// Implementation des CustomVisualisationInterfaces ---------------------------
// File: ITXTROTL.HXX


#if !defined(_ITXTROTL_HXX)
#define _ITXTROTL_HXX

extern "C" {
// Type for an object-destroyed callback --------------------------------------
	typedef void (FAR PASCAL *LPFNDESTROYED)(void);
}


class CVisModule : public IUnknown {
friend class CTextRotIVisModule;
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


// Implementation des VisualisierungsInterfaces -------------------------------
class CTextRotIVisModule : public IVisModule {
private:
	ULONG		m_cRef;         // Interface reference count.
	LPVOID		m_pObj;         // Back pointer to the object.
	LPUNKNOWN	m_punkOuter;    // Controlling unknown for delegation

	class ResourceFile 	*m_pRF;		// diese Datei
	double m_dAspect;
		
public:
	        CTextRotIVisModule (LPVOID, LPUNKNOWN);
        	~CTextRotIVisModule (void);
        	
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
};
typedef CTextRotIVisModule * LPTEXTROTIVISMODULE;

// sonstige FunktionsPrototypen -----------------------------------------------
OBJGEOMETRIE *GetObjectGeometrie (HWND __hWndM, long lONr);
void dtOBJGEOMETRIE (OBJGEOMETRIE *& pOG);
long EvalArc (long lTX1, long lTX2, long lTY, long lCnt, double dAspect, long *pdblX, long *pdblY);

#endif // _ITXTROTL_HXX

