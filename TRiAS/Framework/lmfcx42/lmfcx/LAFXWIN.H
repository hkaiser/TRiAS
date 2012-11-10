#ifndef	__LAFXWIN_H__
#define	__LAFXWIN_H__

#ifndef __LAFX_H__
	#include "lmfcx/lafx.h"
#endif

#ifndef __LAFXRES_H__
	#include "lmfcx42Res.h"
#endif

#ifndef __AFXEXT_H__
	#include <afxext.h>
#endif


#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA AFXAPI_DATA
#endif

/////////////////////////////////////////////////////////////////////
// classes

// class	CObject
//		class CListBox
			class CUpDownList;
//		class CFileDialog
			class CDirSelectDialog;

#ifndef _AFXEXT
	#if _MFC_VER < 0x0400
		extern "C" void WINAPI InitLafxDLL();
	#else
		#pragma comment( lib, IMPORT_THIS_DLL )
	#endif // _MFC_VER
#endif // _AFXDLL

/////////////////////////////////////////////////////////////////////
// analog zu ::AfxExtractSubString( ...  )       (siehe afxwin.h)
// Zahlenbasis 10, 16 und beliebig

BOOL AFX_EXT_API	LAfxExtractSubDouble( double& rResult, LPCTSTR pszFullString, int iSubString, TCHAR chSep = '\n');
BOOL AFX_EXT_API	LAfxExtractSubLong( long& rResult, LPCTSTR pszFullString, int iSubString, TCHAR chSep = '\n');
BOOL AFX_EXT_API	LAfxExtractSubHex( long& rResult, LPCTSTR pszFullString, int iSubString, TCHAR chSep = '\n');
BOOL AFX_EXT_API	LAfxExtractSubBase( long& rResult,  int iBase, LPCTSTR pszFullString, int iSubString, TCHAR chSep = '\n');

/////////////////////////////////////////////////////////////////////
// Devicecontext - Erweiterungen

UINT AFX_EXT_API	LAfxMergePalette( CPalette* pPalette, COLORREF *pColor, int nColors = 1 );

#include	<afxdlgs.h>

/////////////////////////////////////////////////////////////////////////////
// CDirSelectDialog dialog

class AFX_EXT_CLASS CDirSelectDialog : public CFileDialog
{
	DECLARE_DYNAMIC(CDirSelectDialog)
	CString	m_strTitle;
// Construction
public:
	CDirSelectDialog(CWnd* pParent = NULL);

// Dialog Data
	//{{AFX_DATA(CDirSelectDialog)
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	CString	m_strDirectory;

// Overrides
public:
	virtual BOOL	DoModal();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDirSelectDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef	_WIN32		// hier gibt es CSpinButtonControl

class AFX_EXT_CLASS CSpinControl : public CWnd
{
	DECLARE_DYNAMIC(CSpinControl)

// Constructors
public:
	CSpinControl();
	BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);

// Attributes
	CWnd* GetAssociate();
	void SetAssociate(CWnd* pNew);
	void GetRange(UINT& iMin, UINT& iMax);
	void SetRange(UINT iMin, UINT iMax);
	UINT GetCurrentPos();
	void SetCurrentPos(UINT iPos);
	// there are more APIs in 'muscroll.h' not wrapped here

// Implementation
protected:
	virtual WNDPROC* GetSuperWndProcAddr();
};

#endif		// !_WIN32

/////////////////////////////////////////////////////////////////////////////
// CUpDownList control

void AFX_EXT_API DDX_Control( CDataExchange* pDX, int nIDC, CBitmapButton& rControl );
void AFX_EXT_API DDX_Control( CDataExchange* pDX, int nIDC, CUpDownList& rControl );

class AFX_EXT_CLASS CUpDownList : public CListBox
{
	DECLARE_DYNAMIC( CUpDownList )
protected:
	CObArray	m_lstCtrls;
//	COwnedBitmapButton	m_btnUp;		// LAFX_BUTTON_UP
//	COwnedBitmapButton	m_btnDown;		// LAFX_BUTTON_DOWN
//	COwnedBitmapButton	m_btnAdd;		// LAFX_BUTTON_ADD
//	COwnedBitmapButton	m_btnDel;		// LAFX_BUTTON_DEL
//	CStatic				m_txtHead;		// HeaderText

// Construction
public:
	CUpDownList();

// Attributes
protected:
	BOOL	m_bUseBitmapButtons;
	BOOL	m_bUp, m_bDn, m_bAdd, m_bDel;
public:
	int		m_nBorderSize;
	int		m_nButtonDistance;

// Operations
public:
	virtual BOOL CreateCommon( CWnd* pDialogWnd );
	void MoveWindow( int x, int y, int nWidth, int nHeight, BOOL bRepaint = TRUE );
	void MoveWindow( LPCRECT lpRect, BOOL bRepaint = TRUE );
	void SetWindowText( LPCTSTR lpszText );

protected:
	void RecalcLayout( CRect& rc, BOOL bRepaint = TRUE );
	void UpdateButtons();
	void SwitchItems( int itm1, int itm2 );

// Implementation
public:
	virtual ~CUpDownList();

	void	UseBitmapButtons();
	void	UseTextButtons();
	void	EnableButtons( BOOL bEnable = TRUE, BOOL bBtnUp = TRUE, BOOL bBtnDn = TRUE, BOOL bBtnAdd = TRUE, BOOL bBtnDel = TRUE );
	void	ShowButtons( BOOL bShow = TRUE, BOOL bBtnUp = TRUE, BOOL bBtnDn = TRUE, BOOL bBtnAdd = TRUE, BOOL bBtnDel = TRUE );

// Overrides
public:
	int	AddString( LPCSTR lpszItem );
	int	SetCurSel( int select );
	void ResetContent();
	
protected:
	virtual BOOL OnChildNotify(UINT msg, WPARAM wp, LPARAM lp, LRESULT* pLRes);
	// Generated message map functions
	//{{AFX_MSG(CUpDownList)
	afx_msg void OnButtonUp();
	afx_msg void OnButtonDown();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	afx_msg void OnDoubleclickedButtonDown();
	afx_msg void OnDoubleclickedButtonUp();
	afx_msg void OnDoubleclickedButtonAdd();
	afx_msg void OnDoubleclickedButtonDel();
	//}}AFX_MSG
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM lParam);
	afx_msg void OnUpdateBtnUp( CCmdUI *pCmdUI );
	afx_msg void OnUpdateBtnDown( CCmdUI *pCmdUI );
	afx_msg void OnUpdateBtnAdd( CCmdUI *pCmdUI );
	afx_msg void OnUpdateBtnDel( CCmdUI *pCmdUI );
	DECLARE_MESSAGE_MAP()
};

//////////////////////////////////////////////////////////////////////
// for use in MFC-Message-Maps

#define	LBN_MOVEUP		(WM_USER+100)
#define	LBN_MOVEDOWN	(WM_USER+101)
#define	LBN_ADDITEM		(WM_USER+102)
#define	LBN_DELITEM		(WM_USER+103)

#define ON_LBN_MOVEUP( id, memberFxn ) \
	ON_CONTROL( LBN_MOVEUP, id, memberFxn )
#define	ON_LBN_MOVEDOWN(id, memberFxn ) \
	ON_CONTROL( LBN_MOVEDOWN, id, memberFxn )
#define	ON_LBN_ADDITEM(id, memberFxn ) \
	ON_CONTROL( LBN_ADDITEM, id, memberFxn )
#define	ON_LBN_DELITEM(id, memberFxn ) \
	ON_CONTROL( LBN_DELITEM, id, memberFxn )

//////////////////////////////////////////////////////////////////////
// verschiedene Hilfsfunktionen zum Koordinatendebugging
// (sehr einfach, aber nützlich)
//////////////////////////////////////////////////////////////////////

#define	RGB_RED		RGB( 255, 0, 0 )
#define	RGB_GREEN	RGB( 0, 255, 0 )
#define	RGB_BLUE	RGB( 0, 0, 255 )
#define RGB_WHITE	RGB( 255, 255, 255 )
#define	RGB_BLACK	RGB( 0, 0, 0 )

void	AFX_EXT_API	MarkPoint( CDC* pDC, const POINT& pPt, COLORREF color = RGB_RED, short width = 3 );
void	AFX_EXT_API	MarkPoint( CDC* pDC, const POINTL& pPt, COLORREF color = RGB_RED, short width = 3 );
void	AFX_EXT_API	MarkPoint( CDC* pDC, const DPOINT& pPt, COLORREF color = RGB_RED, short width = 3 );
void	AFX_EXT_API	MarkStraith( CDC* pDC, const CStraith& pS, COLORREF color = RGB_GREEN, short width = 3 );
void	AFX_EXT_API	MarkLine( CDC* pDC, const CLine& pL, COLORREF color = RGB_BLUE, short width = 3 );
void	AFX_EXT_API	MarkRect( CDC* pDC, const CRect& pR, COLORREF color = RGB_BLACK, short width = 3 );

#ifdef	_AFX_ENABLE_INLINES
#if !defined(_AFXWIN_INLINE)
#define	_AFXWIN_INLINE inline
#endif
#include	"lmfcx/lafxwin.inl"
#endif

#ifdef _AFXDLL
#undef AFXAPP_DATA
#define AFXAPP_DATA NEAR
#endif

#endif		// __LAFXWIN_H__
