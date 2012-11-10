// FillArea.h : header file
//

#include <icustom.hxx>

/////////////////////////////////////////////////////////////////////////////
// CFillArea command target

class CFillArea : public CCmdTarget
{
	DECLARE_DYNCREATE(CFillArea)
	DECLARE_OLECREATE_EX(CFillArea)

	CFillArea();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFillArea)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
private:
	HRESULT HatchVertical (CDC &rDC, CFillParams &rfp);
	HRESULT HatchHorizontal (CDC &rDC, CFillParams &rfp);

protected:
	HRESULT CreateObjectRegion (CGObject &rGO, CRgn &rRgn);
	HRESULT FillObjectRgn (HDC hDC, CRgn &rRgn, FVisInfo *pFVI, CFillParams &rfp);
	void ResetPoints (void);
	bool InitPoints (int iCnt);

protected:	// InterfaceHandler
	HRESULT SymbolizeObject (HWND hWndM, long &rlONr, short &riOType, char *pBuffer, short iLen);
	HRESULT DrawObject (HWND hWndM, HDC hDC, HDC hTargetDC, long lONr, short &rfDrawFlags, VisInfo *pVI, char *pVisString);
	HRESULT QueryParameters (HWND hWnd, long lONr, VisInfo *pVI, char *pVisStr, char *pBuffer, short iLen, short *piOTypes);
	void OnProjectChange (HWND hWndM, PROJECTCHANGE rgPC, char *pPrName);
	void OnViewChange (HWND hWndM, VIEWCHANGE rgVC, char *pView);
	void OnPaletteChange (HWND hWndM, HPALETTE hPal);
	
protected:	
	virtual ~CFillArea();

// Generated message map functions
	//{{AFX_MSG(CFillArea)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CFillArea)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

// Interfaces dieser Klasse
	DECLARE_INTERFACE_MAP()

// IVisModule
	BEGIN_INTERFACE_PART(VisModule, IVisModule)
		STDMETHOD(QueryParameters) (THIS_ HWND hWnd, long lONr, 
						class VisInfo *pVI, char *pVisStr,
						char *pBuffer, short iLen, short *piOTypes);
		STDMETHOD(SymbolizeObject) (THIS_ HWND hWnd, long &rlONr, short &iOType,
						char *pBuffer, short iLen);
		STDMETHOD(DrawObject) (THIS_ HWND hWnd, HDC hDC, HDC hTargetDC, 
					   long lONr, short &fDrawFlags, 
					   class VisInfo *pVI, char *pVisString);
		STDMETHOD_(void,OnProjectChange)(THIS_ HWND hWndM, PROJECTCHANGE rgPC, 
						 char *pPrName);
		STDMETHOD_(void,OnViewChange)(THIS_ HWND hWndM, VIEWCHANGE rgVC, 
						  char *pView);
		STDMETHOD_(void,OnPaletteChange)(THIS_ HWND hWndM, HPALETTE hPal);
    END_INTERFACE_PART(VisModule)

private:
	HPALETTE m_hPal;
	int m_iCnt;			// Größe des Feldes m_pPts
	CPoint *m_pPts;		// Feld der Objektgeometrie
	CRect m_rcBound;	// Umschließendes Rechteck
};

/////////////////////////////////////////////////////////////////////////////
