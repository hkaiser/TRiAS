// CoordStaticsSec.h : Declaration of the CZoomComboBox

#include <dblpair.hxx>

#include "SecDll.h"
#include "TbtnWnd.h"

#include "ConnectedCtf.h"

class CCompoundStaticSec;

///////////////////////////////////////////////////////////////////////////////
// CInstCoordStatics

class CInstCoordStatics : 
	public ITRiASNotificationSink,
	public ITRiASSysNotificationSink,
	public CComObjectRoot
{
public:
		CInstCoordStatics();
		~CInstCoordStatics() { DisConnectFromServer(); }

	BEGIN_COM_MAP(CInstCoordStatics)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
		COM_INTERFACE_ENTRY(ITRiASSysNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CInstCoordStatics)

public:
// *** ITRiASNotificationSink specific functions ***
	STDMETHOD(ServerEvent) (THIS_ SERVEREVT se);
	STDMETHOD(ProjectEvent) (THIS_ long hPr, PROJECTEVT pe, VARIANT vProj);
	STDMETHOD(GeoViewEvent) (THIS_ long hPr, GEOVIEWEVT ve, VARIANT vData);
	STDMETHOD(GeoClassEvent) (THIS_ long hPr, GEOCLASSEVT ce, long ulIdent);
	STDMETHOD(GeoObjectEvent) (THIS_ long hPr, GEOOBJECTEVT oe, long lONr);
	STDMETHOD(GeoFeatureEvent) (THIS_ long hPr, GEOFEATUREEVT fe, long ulMCode);
	STDMETHOD(GeoRelationEvent) (THIS_ long hPr, GEORELATIONEVT re, long ulRCode);
	STDMETHOD(ObjectWindowEvent)(THIS_ OBJWNDEVT oe, long hORWnd);

// *** ITRiASSysNotificationSink specific functions ***
	STDMETHOD(WindowsMessage) (THIS_ long hWnd, long uiMsg, long wParam, long lParam);

	HRESULT SetSitePointers (ITriasXtensionSite *pSite, CCompoundStaticSec *pBack);
	HRESULT DisConnectFromServer (void);

protected:
	HRESULT RouteMouseEvents (HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam);

private:
	CCompoundStaticSec *m_pBack;
	CPoint m_ptLast;

	bool m_fDrag;					// derzeit Dragging/Abstandsmessung aktiv
	CString m_strIdle;

	WConnectionPointContainer m_Cont;
	DWORD m_dwCookie;
	DWORD m_dwCookieSys;
};

///////////////////////////////////////////////////////////////////////////////
// Map CommandID's to ToolNumbers 
// ... from tool.hxx
#define NUMARROW 	0
#define NUMZOOM		1
#define NUMLUPE 	2
#define NUMSCHERE 	3
#define NUMLINEAL	4
#define NUMSCHRIFT	5

/////////////////////////////////////////////////////////////////////////////
// CToolTipStatic window

class CToolTipStaticSec : 
	public CStatic
{
// Construction
public:
	CToolTipStaticSec();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolTipStaticSec)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CToolTipStaticSec();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolTipStaticSec)
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CCompoundStaticSec window

class CCompoundStaticSec : 
	public CStatic,
	public SECWndBtn
{
// Construction
public:
	CCompoundStaticSec();

// Attributes
public:

// Operations
	virtual void OnFontCreateAndSet();
	virtual BOOL CreateWnd (CWnd* pParentWnd, DWORD dwStyle, CRect& rect, int nID);
	virtual CWnd *GetWnd();
	virtual void AdjustSize(void);

public:
	bool ResetTexts (void);
	HRESULT SetCoords (CPoint &rPt, bool fDrag = false);

	bool ShowToolTips (void) { return m_fShowToolTips; }
	void ShowToolTips (bool fFlag) { m_fShowToolTips = fFlag ? true : false; }

	bool LoadCTF (void) { ASSERT(NULL != m_pCTF); return m_pCTF -> LoadCTF(); }
	void ReleaseCTF (void) { ASSERT(NULL != m_pCTF); m_pCTF -> ReleaseCTF(); }
	bool CTFCanConfig (void) { ASSERT(NULL != m_pCTF); return m_pCTF -> CanConfig(); }

	void ResetDrag (void) { m_fDrag = false; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCompoundStaticSec)
	virtual int OnToolHitTest( CPoint point, TOOLINFO* pTI ) const;
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCompoundStaticSec();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCompoundStaticSec)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg UINT OnNcHitTest(CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
	DECLARE_BUTTON(CCompoundStaticSec)

private:
	CToolTipStaticSec m_ftCoordX;
	CToolTipStaticSec m_ftCoordY;
	CStatic m_ftDel;
	CFont m_font;

	bool m_fShowToolTips;
	bool m_fDrag;

	DoublePair m_dblBegin;		// AnfangsKoordinate für Abstandsanzeige
	CString m_strDistance;

	CComObject<CConnectedCtf> *m_pCTF;			// aktuelle KoordinatenTransformation
	CComObject<CInstCoordStatics> *m_pCP;		// ConnectionSink

	int m_iHeight;				// FontHöhe
};

/////////////////////////////////////////////////////////////////////////////
