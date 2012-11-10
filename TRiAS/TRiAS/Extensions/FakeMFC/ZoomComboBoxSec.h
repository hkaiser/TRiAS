// ZoomComboBoxSec.h : Declaration of the CZoomComboBoxSec

#if !defined(_SEC_VER) || _SEC_VER < 0x0600
#include <secdll.h>
#endif // !defined(_SEC_VER) || _SEC_VER < 0x0600

#include <TbtnCmbo.h>

#include "FlatComboBox.h"
#include "MsgHook.h"

class CZoomComboBoxSec;

///////////////////////////////////////////////////////////////////////////////
// CInstZoomComboBox

class CInstZoomComboBox : 
	public ITRiASNotificationSink, 
	public CComObjectRoot
{
public:
		CInstZoomComboBox() { m_fProjectOpen = false; }
		~CInstZoomComboBox() { DisConnectFromServer(); }

	BEGIN_COM_MAP(CInstZoomComboBox)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CInstZoomComboBox)

	HRESULT FinalConstruct (void);

public:
// *** ITRiASNotificationSink specific functions ***
	STDMETHOD(ServerEvent) (THIS_ SERVEREVT se);
	STDMETHOD(ProjectEvent) (THIS_ long hPr, PROJECTEVT pe, VARIANT vData);
	STDMETHOD(GeoViewEvent) (THIS_ long hPr, GEOVIEWEVT ve, VARIANT vData);
	STDMETHOD(GeoClassEvent) (THIS_ long hPr, GEOCLASSEVT ce, long ulIdent);
	STDMETHOD(GeoObjectEvent) (THIS_ long hPr, GEOOBJECTEVT oe, long lONr);
	STDMETHOD(GeoFeatureEvent) (THIS_ long hPr, GEOFEATUREEVT fe, long ulMCode);
	STDMETHOD(GeoRelationEvent) (THIS_ long hPr, GEORELATIONEVT re, long ulRCode);
	STDMETHOD(ObjectWindowEvent) (THIS_ OBJWNDEVT oe, long hORWnd);

	HRESULT SetSitePointers (ITriasXtensionSite *pSite, CZoomComboBoxSec *pBack);
	HRESULT DisConnectFromServer (void);

private:
	WConnectionPointContainer m_Cont;
	DWORD m_dwCookie;
	CZoomComboBoxSec *m_pBack;

	bool m_fProjectOpen;	// Projekt geöffnet
};

/////////////////////////////////////////////////////////////////////////////
// CZoomEditSec window

class CZoomEditSec : 
	public CMsgHook
{
// Construction
public:
	CZoomEditSec() {}

// Implementation
public:
	virtual ~CZoomEditSec() {}
	virtual LRESULT WindowProc(UINT msg, WPARAM wp, LPARAM lp);

	virtual void OnChar (UINT nChar, UINT nRepCnt, UINT nFlags);
};


/////////////////////////////////////////////////////////////////////////////
// CZoomComboBoxSec window

class CZoomComboBoxSec : 
	public CFlatComboBox
{
// Construction
public:
	CZoomComboBoxSec();

// Attributes
public:

// Operations
public:
	bool GetModify (void);
	void SetModify (bool fModify);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomComboBoxSec)
	//}}AFX_VIRTUAL

	virtual void OnFontCreateAndSet();
	virtual BOOL CreateWnd (CWnd* pParentWnd, DWORD dwStyle, CRect& rect, int nID);
	virtual void PrePaint (void);
	virtual void PostPaint (void);

// SetMode informs the button when the button either enters/leaves a
// vertically docked state
	virtual void SetMode(BOOL bVertical);
// Modifies our window position
	virtual void SetPos(int x, int y);

// Implementation
public:
	virtual ~CZoomComboBoxSec();

	HRESULT FillWithZooms (void);
	HRESULT ActivateActualZoom (long lZoom);
	void AdjustZoom (void);

	bool GetActiveView() { return m_fActiveView ? true : false; }
	void SetActiveView (bool fFlag) { m_fActiveView = fFlag ? true : false; }

// Generated message map functions
protected:
	//{{AFX_MSG(CZoomComboBoxSec)
	afx_msg void OnDropdown();
	afx_msg void OnCloseup();
	afx_msg LONG OnGetSetModify (UINT wParam, LONG lParam);
	afx_msg void OnEnable(BOOL bEnable);
	afx_msg void OnWindowPosChanging(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_BUTTON(CZoomComboBoxSec)

private:
	CZoomEditSec m_Hook;
	CStatic m_ftZoom;

	bool m_fSubClassed;
	bool m_fChangedSel;
	bool m_fActiveView;		// Sicht ausgewählt

	int m_iCurrSel;
	CSize m_szText;			// Maße des VorTextes ('1:')

	CComObject<CInstZoomComboBox> *m_pCP;		// ConnectionSink
};

// Message sent when CWnd requires initialisation
extern const int WM_GETSETMODIFY;	// RegisterWindowMessage(_T("WM_GETSETMODIFY"));

/////////////////////////////////////////////////////////////////////////////

