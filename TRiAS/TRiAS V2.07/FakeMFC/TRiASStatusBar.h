// TRiASStatusBar.h : header file
//

#include <toolguid.h>
#include <itoolbar.h>

/////////////////////////////////////////////////////////////////////////////
// CTRiASStatusBar window

class CTRiASStatusBar : public CStatusBar
{
// Construction
public:
	typedef map<int, WTRiASUIOwner, less<int> > UIOwners;

	CTRiASStatusBar(ITRiASStatusBar *pIBar);

// Attributes
public:
	HRESULT GetBarStyleEx (LPSTR pName, ULONG ulLen, ULONG *pulWritten, DWORD *pdwStyle, DWORD *pdwStyleEx);
	HRESULT CommandToIndex (UINT uiID, int *piIndex);
	HRESULT GetBarID (UINT *puiID);
	HRESULT GetBarHandle (HWND *phWnd);
	HRESULT GetItemRect (int iIndex, LPRECT pRc);

// Operations
public:
	HRESULT SetBarStyleEx (LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, bool fDelay);
	HRESULT DeleteItem (int iIndex);
	HRESULT OnCmdMessage (UINT uiID, int nCode, void *pExtra1, AFX_CMDHANDLERINFO *pHandlerInfo);

	HRESULT InitNew (void);
	HRESULT RemoveBar (void);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTRiASStatusBar)
	virtual void OnUpdateCmdUI (CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTRiASStatusBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTRiASStatusBar)
	afx_msg void OnNcDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:

private:
	CMainFrame *m_pMainFrm;		// zuständiges Hauptfenster 
	UIOwners m_Owners;			// Map mit TRiASUIOwner der Buttons
	ITRiASStatusBar *m_pIBar;	// zugehöriges ITRiASStatusBar-Objekt
	DWORD m_dwFlags;			// sonstige Flags
};

/////////////////////////////////////////////////////////////////////////////
