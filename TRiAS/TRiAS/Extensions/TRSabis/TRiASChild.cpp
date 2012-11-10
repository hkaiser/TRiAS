// TRiASChild.cpp : implementation file
//

#include "stdafx.h"
#include "TRSABIS.h"
#include "TRiASChild.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTRiASChild dialog


CTRiASChild::CTRiASChild(CWnd* pParent /*=NULL*/, UINT uiResID)
	: CDialog(CTRiASChild::IDD, pParent), m_hIcon(NULL)
{
	CDialog::Create(uiResID, pParent);
	//{{AFX_DATA_INIT(CTRiASChild)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_BackColor = GetSysColor(COLOR_WINDOW);
}

void CTRiASChild::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTRiASChild)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTRiASChild, CDialog)
	//{{AFX_MSG_MAP(CTRiASChild)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTRiASChild message handlers

void CTRiASChild::SetBackgroundColor(COLORREF cBackColor)
{
	m_BackColor = cBackColor;
	Invalidate();
}

COLORREF CTRiASChild::GetBackgroundColor()
{
	return m_BackColor;
}

BOOL CTRiASChild::OnEraseBkgnd(CDC* pDC) 
{
	// Input abtesten
	if (NULL == pDC)
		return false;

	CRect InvRect;
	GetClientRect(&InvRect); 

//	GetUpdateRect(InvRect);

	pDC->FillSolidRect( InvRect, m_BackColor);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Anzuzeigendes Bildchen
bool CTRiASChild::EnsureIcon()
{
	if (NULL == m_hIcon) {
		m_hIcon = ::LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_SABiS));
		_ASSERTE(NULL != m_hIcon);
	}
	return (NULL != m_hIcon) ? true : false;
}

