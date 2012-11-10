// TRiASToolBar.h : header file
//

#include <toolguid.h>
#include <itoolbar.h>

#if defined(_USE_SEC_CLASSES)
#include <afxtempl.h>
#define __AFXCONV_H__
#include <afxpriv.h>		// CDockState et.al.
#include <sdocksta.h>
#include <tbarcust.h>
#else
#define SECCustomToolBar CToolBar
#endif // _USE_SEC_CLASSES

/////////////////////////////////////////////////////////////////////////////
// CTRiASToolBar window

class CMainFrame;

class CTRiASToolBar : 
	public SECCustomToolBar
{
	DECLARE_DYNAMIC(CTRiASToolBar);

// Construction
public:
	typedef map<int, WTRiASUIOwner, less<int> > UIOwners;

	CTRiASToolBar(ITRiASToolBar *pIBar);

// Attributes
public:
	HRESULT GetBarStyleEx (LPSTR pName, ULONG ulLen, ULONG *pulWritten, DWORD *pdwStyle, DWORD *pdwStyleEx);
	HRESULT CommandToIndex (UINT uiID, int *piIndex);
	HRESULT GetBarID (UINT *puiID);
	HRESULT GetBarHandle (HWND *phWnd);
	HRESULT GetStatusText (UINT uiID, CString &rStr);
	BOOL SetStatusText (int nHit);
	HRESULT GetItemRect (int iIndex, LPRECT pRc);
	HRESULT SetBarID (int iCtrlID, BOOL fAdjustWnd = TRUE);

// Operations
public:
	HRESULT DockBar (UINT uiWhere, LPCRECT pcRc);
	HRESULT FloatBar (const POINT &pt, DWORD dwStyle);
	HRESULT SetBarStyleEx (LPCSTR pcName, DWORD dwStyle, DWORD dwStyleEx, bool fDelay);
	HRESULT DeleteItem (int iIndex);
	HRESULT InsertButton (int iIndex, const TBBUTTON *pBttn, ITRiASUIOwner *pIOwner);
	HRESULT AddButtons (const TBBUTTON *pBttns, int iCnt, ITRiASUIOwner *pIOwner);
	HRESULT AddBitmap (HINSTANCE hInst, UINT uiRsc, int nNumButtons, int *piOffset);
	HRESULT GetButtonStyle (int iIndex, UINT *puiStyle, UINT *puiID = NULL);
	HRESULT SetButtonStyle (int iIndex, UINT uiStyle);
	HRESULT OnCmdMessage (UINT uiID, int nCode, void *pExtra1, AFX_CMDHANDLERINFO *pHandlerInfo);
	HRESULT GetButtonEx (int iIndex, TBBUTTON *pBttn, ITRiASUIOwner **ppIOwner);

	HRESULT InitNew (void);
	HRESULT RemoveBar (void);

	HRESULT Reset (void);

/* ----------------------------------------------------------------------------
	CSize CalcDynamicLayout(int nLength, DWORD dwMode);
---------------------------------------------------------------------------- */
	void OnBarStyleChange (DWORD dwOldStyle, DWORD dwNewStyle);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTRiASToolBar)
	virtual BOOL PreTranslateMessage (MSG* pMsg);
	virtual void OnUpdateCmdUI (CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTRiASToolBar();

	ITRiASToolBar *GetToolBarObj (BOOL fAddRef = FALSE)
		{
			ASSERT(NULL != m_pIBar);
			if (fAddRef) m_pIBar -> AddRef();
			return m_pIBar;
		}

	// Generated message map functions
protected:
	//{{AFX_MSG(CTRiASToolBar)
	afx_msg void OnContextMenu(CWnd*, CPoint point);
	afx_msg void OnNcDestroy();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg bool OnToolTipText(UINT uiID, NMHDR* pNMHDR, LRESULT* pResult);

	DECLARE_MESSAGE_MAP()

	HRESULT FindOwner (UINT uiID, ITRiASUIOwner **ppUIOwner);
	bool FreeInstalledControls (void);
#if defined(_USE_SEC_CLASSES)
	BOOL IDToBmpIndex (UINT nID, int *piIndex);

public:
	void PropagateMode (void);
	inline BOOL IsDefaultBar (void)
		{ 	return (m_dwFlags & TRIASTOOLBAR_PREDEFINED) ? TRUE : FALSE; }
#endif // _USE_SEC_CLASSES

private:
	void _GetButtonEx (int nIndex, TBBUTTON* pButton) const;
	void _SetButtonEx (int nIndex, TBBUTTON* pButton);

private:
	CMainFrame *m_pMainFrm;		// zuständiges Hauptfenster 
	UIOwners m_Owners;			// Map mit TRiASUIOwner der Buttons
	UINT m_uiID;				// ID dieser Bar
	ITRiASToolBar *m_pIBar;		// zugehöriges ITRiASToolBar-Objekt
	bool m_fHasDummySep;		// Anfangs enthält ToolBar einen Separator
	DWORD m_dwFlags;			// sonstige Flags
};

/////////////////////////////////////////////////////////////////////////////
