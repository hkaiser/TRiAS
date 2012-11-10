// dummypar.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"
#include "dummypar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDummyParent dialog


CDummyParent::CDummyParent(CWnd* pParent /*=NULL*/)
	: CDialog()
{
	Create (CDummyParent::IDD, pParent);	// modeless
		
	//{{AFX_DATA_INIT(CDummyParent)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	CenterMe();	// im TRiAS-Fenster zentrieren
}

void CDummyParent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDummyParent)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDummyParent, CDialog)
	//{{AFX_MSG_MAP(CDummyParent)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDummyParent::CenterMe(CWnd* pAlternateOwner /*= NULL*/)
{
	CRect rcScreen(0, 0, ::GetSystemMetrics(SM_CXSCREEN),
		::GetSystemMetrics(SM_CYSCREEN));

	// hWndOwner is the window we should center ourself in
	HWND hWndOwner = (pAlternateOwner != NULL) ?
			pAlternateOwner->m_hWnd : ::GetWindow(m_hWnd, GW_OWNER);

	// rcParent is the rectange we should center ourself in
	CRect rcParent;
	if (hWndOwner == NULL)
		rcParent = rcScreen;
	else
		::GetWindowRect(hWndOwner, &rcParent);

	// find ideal center point
	int xMid = (rcParent.left + rcParent.right) / 2;
	int yMid = (rcParent.top + rcParent.bottom) / 2;

	// find dialog's upper left based on that
	CRect rcDlg;
	GetWindowRect(&rcDlg);
	int xLeft = xMid - rcDlg.Width() / 2;
	int yTop = yMid - rcDlg.Height() / 2;

	// if the dialog is outside the screen, move it inside
	if (xLeft < 0)
		xLeft = 0;
	else if (xLeft + rcDlg.Width() > rcScreen.right)
		xLeft = rcScreen.right - rcDlg.Width();

	if (yTop < 0)
		yTop = 0;
	else if (yTop + rcDlg.Height() > rcScreen.bottom)
		yTop = rcScreen.bottom - rcDlg.Height();

	SetWindowPos (NULL, xLeft, yTop, -1, -1, 
		      SWP_NOSIZE | SWP_NOZORDER | SWP_HIDEWINDOW);
}

/////////////////////////////////////////////////////////////////////////////
// CDummyParent message handlers
