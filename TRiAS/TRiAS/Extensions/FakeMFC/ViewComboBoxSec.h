// ViewComboBoxSec.h : Declaration of the CViewComboBoxSec

#include "SecDll.h"
#include "TbtnCmbo.h"
#include "FlatComboBox.h"

class CViewComboBoxSec;

/////////////////////////////////////////////////////////////////////////////
// ConnectionSink for TRiAS Notifications

class CInstViewComboBox : 
	public ITRiASNotificationSink,
	public CComObjectRoot
{
public:
		CInstViewComboBox() {}
		~CInstViewComboBox() { DisConnectFromServer(); }

	BEGIN_COM_MAP(CInstViewComboBox)
		COM_INTERFACE_ENTRY(ITRiASNotificationSink)
	END_COM_MAP()

	DECLARE_NOT_AGGREGATABLE(CInstViewComboBox)

	HRESULT FinalConstruct (void);

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

	HRESULT SetSitePointers (ITriasXtensionSite *pSite, CViewComboBoxSec *pBack);
	HRESULT DisConnectFromServer (void);

private:
	WConnectionPointContainer m_Cont;
	DWORD m_dwCookie;
	CViewComboBoxSec *m_pBack;
};

/////////////////////////////////////////////////////////////////////////////
// CViewComboBoxSec window

class CViewComboBoxSec : public CFlatComboBox
{
// Construction
public:
	CViewComboBoxSec();

// Attributes
public:

// Operations
public:
	HRESULT FillWithViews (void);
	HRESULT ActivateActualView (LPCSTR pcView = NULL);
	bool DeleteEntry (UINT uiStr);

	int FindViewName (int iStartIndex, LPCSTR pcViewName) const;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewComboBoxSec)
//	virtual int OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	//}}AFX_VIRTUAL

	virtual void OnFontCreateAndSet();
	virtual BOOL CreateWnd (CWnd* pParentWnd, DWORD dwStyle, CRect& rect, int nID);

// Implementation
public:
	virtual ~CViewComboBoxSec();

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewComboBoxSec)
	//}}AFX_MSG
//	afx_msg bool OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()
	DECLARE_BUTTON(CViewComboBoxSec)

private:
	bool m_fNoActView;
	CComObject<CInstViewComboBox> *m_pCP;		// ConnectionSink
};

///////////////////////////////////////////////////////////////////////////////


