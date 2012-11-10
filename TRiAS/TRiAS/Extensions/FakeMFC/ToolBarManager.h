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

typedef map<UINT, __Interface<ITRiASUIOwner>, less<UINT> > CBttnOwners;

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
#if _SEC_VER < 0x0600
	// Generated message map functions
    //{{AFX_MSG(CTRiASToolBarManager)
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()
#endif // _SEC_VER < 0x0600

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

public:
	CPtrArray *GetDefaultToolBarArray() { return &m_defaultBars; }
	typedef SECToolBarManager::SECDefaultToolBar SECDefaultToolBar;

private:
	CResources m_Rscs;		// alle geladenen BitmapResourcen
	CBttnOwners m_Owner;	// UIOwner aller Buttons

#if _SEC_VER >= 0x0600
// JG needed for our toolbars
private:
	CBitmap m_bmp;						// The bitmap used by all the toolbars
	UINT m_nBmpItems;					// No. of buttons in bmp
	UINT m_nBmpIndex;					// Index unserer privaten Bitmap im BitmapMgr
	BOOL m_bBmpInMgr;					// ist unsere Bmp bereits im BmpManager (eigentlich unsinnig)

protected:
	HRESULT BmpMgrAddBmp();				// schreibt unsere Bitmap in den BmpManager
	HRESULT BmpMgrAddButton(const TBBUTTON *pBttn);			// schreibt den Button in den bmpMgr
	HRESULT BmpMgrRemoveButton(const TBBUTTON *pBttn);		// löscht den Button aus dem bmpMgr

public:
	HRESULT FindCommandID4Index(int nIndex, UINT& uiCmd);	// suchen des CmdID's zu dem angegebneen Index
	HRESULT FindIndex4CommandID(UINT uiCmd, int& nIndex);	// und andersrum	(liefert nur Werte für unsere Bitmap)
#endif // _SEC_VER >= 0x0600
};

#endif // _TOOLBARMANAGER_H
