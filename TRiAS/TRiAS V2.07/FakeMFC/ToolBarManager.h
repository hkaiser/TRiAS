// Unser ToolBarManager
// File: ToolBarManager.h

#if !defined(_TOOLBARMANAGER_H)
#define _TOOLBARMANAGER_H

#include <itoolbar.h>
#include <toolguid.h>

#include <tbarmgr.h>	// SECToolBarManager

///////////////////////////////////////////////////////////////////////////////
// Liste aller geladenen BitmapResourcen

class CResource 
{
private:
	HINSTANCE m_hInst;
	UINT m_uiRsc;
	int m_iCnt;

public:
		CResource (void)
			: m_hInst(NULL), m_uiRsc(0), m_iCnt(0) {}
		CResource (HINSTANCE hInst, UINT uiRsc, int iCnt)
			: m_hInst(hInst), m_uiRsc(uiRsc), m_iCnt(iCnt) {}

	HINSTANCE GetInstanceHandle() const { return m_hInst; }
	UINT GetResourceId() const { return m_uiRsc; }
	int GetCount() const { return m_iCnt; }

	bool operator< (const CResource&) const { return true; }		// Reihenfolge is wurscht
};

typedef list<CResource> CResources;

///////////////////////////////////////////////////////////////////////////////
// Manager aller Toolbars im Hauptfenster

typedef map<UINT, WTRiASUIOwner,less<UINT> > CBttnOwners;

// Helperklasse, die verhindert, daß Attach'te Bitmap freigegeben wird
class CAttachedBitmap :
	public CBitmap
{
private:
	bool m_fAttached;

public:
	CAttachedBitmap ()
		{ m_fAttached = false; }
	~CAttachedBitmap()
		{ if (m_fAttached) Detach(); }

	BOOL Attach(HGDIOBJ hObject)
		{ BOOL fResult = CBitmap::Attach (hObject); m_fAttached = true; return fResult; }
	HGDIOBJ Detach()
		{ HGDIOBJ hObject = CBitmap::Detach(); m_fAttached = false; return hObject; }
	BOOL IsAttached() { return m_fAttached; }
};

class CTRiASToolBarManager :
	public SECToolBarManager
{
	DECLARE_DYNAMIC(CTRiASToolBarManager)

public:
	CTRiASToolBarManager();
	CTRiASToolBarManager(CFrameWnd* pFrameWnd);
	
	virtual ~CTRiASToolBarManager();

	HRESULT CreateToolBar (UINT uiID, LPCTSTR lpszTitle, ITRiASToolBar **ppITools);
	DWORD GetDefaultBarStyleEx();

// Bitmap zu ButtonPool hinzufügen etc.
	HRESULT AddBitmap (HINSTANCE hInst, UINT uiRsc, int iBttnCnt, int *piOffset);
	HRESULT AddButtons (CTRiASToolBar *pBar, int iBttnCnt, const TBBUTTON *pBttns, ITRiASUIOwner *pUIOwner);
	HRESULT InsertButton (CTRiASToolBar *pBar, int iIndex, const TBBUTTON *pBttn, ITRiASUIOwner *pUIOwner);
	HRESULT DeleteButton (CTRiASToolBar *pBar, int iIndex);
	HRESULT GetButton (const CTRiASToolBar *pBar, int iIndex, TBBUTTON *pBttn);
	HRESULT GetUIOwner (CTRiASToolBar *pBar, int iIndex, ITRiASUIOwner **ppIOwner);
	HRESULT ResetToolBar (CTRiASToolBar *pBar);

// Handles system color changes
	void SysColorChange();		// #HK970806: added virtual
	void SetButtonMap (const SECBtnMapEntry *pMap);
	HRESULT GetButtonIds (const TBBUTTON *pBttns, int iBttnCnt, UINT **ppIds);
	BOOL HasBmpIndex (UINT nID);

	void DefineDefaultToolBar (
		UINT nID, LPCTSTR lpszTitle, const TBBUTTON *pBttns, UINT nBtnCount, 
		DWORD dwAlignment = CBRS_ALIGN_ANY, UINT nDockBarID = AFX_IDW_DOCKBAR_TOP, 
		UINT nDockNextToID = 0,	BOOL bDocked = TRUE, BOOL bVisible = TRUE);

protected:
	// Generated message map functions
    //{{AFX_MSG(CTRiASToolBarManager)
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
	BOOL AppendToExisting (CAttachedBitmap &rBmp, int *piOffset);
	BOOL AddToOwnerList (int iIndex, ITRiASUIOwner *pUIOwner);
	BOOL RemoveFromOwnerList (int iIndex);

	enum ADDBUTTON {
		ADDBUTTON_FAILED = 1,
		ADDBUTTON_ADDED = 2,
		ADDBUTTON_REPLACED = 3,
	};
	ADDBUTTON AddToButtonMap (const SECBtnMapEntry *pBttn, int iCnt = 1);
	ADDBUTTON AddToButtonMap (const TBBUTTON *pBttn);
	BOOL RemoveFromButtonMap (const TBBUTTON *pBttn);

	BOOL AddToDefaultButtonList (CTRiASToolBar *pBar, const TBBUTTON *pBttns, int iCnt, int iIndex = -1);
	BOOL RemoveFromDefaultButtonList (CTRiASToolBar *pBar, int iIndex, const TBBUTTON *pBttns);

private:
	CResources m_Rscs;		// alle geladenen BitmapResourcen
	CBttnOwners m_Owner;	// UIOwner aller Buttons
};

#endif // _TOOLBARMANAGER_H
