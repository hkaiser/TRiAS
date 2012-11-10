// DbFrmVw2.cpp : implementation file
//

#include "bscriptp.hxx"
#include "bscript.h"

#include <iobjman.h>
#include <registrx.hxx>

#include "macrguid.h"

#include "iscrprop.h"

#include "projscr.h"
#include "strinfo.h"
#include "dummypar.h"
#include "conststr.h"
#include "fndrpld.h"
#include "toolbarx.h"
#include "runscorg.h"
#include "relscrpt.h"
#include "runerr.h"
#include "runebobs.h"
#include "DebCtrl.h"
#include "projscr.h"
#include "spltree.h"
#include "splitter.h"
#include "split.h"
#include "editctrl.h"
#include "DbFrmVw2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDebFormView2

IMPLEMENT_DYNCREATE(CDebFormView2, CFormView)

CDebFormView2::CDebFormView2()
	: CFormView(CDebFormView2::IDD)
{
	//{{AFX_DATA_INIT(CDebFormView2)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iInitialStaticHeight = 0;
}

CDebFormView2::~CDebFormView2()
{
}

void CDebFormView2::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDebFormView2)
	DDX_Control(pDX, IDC_DEBUGGERCAPTION, m_stDebuggerCaption);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDebFormView2, CFormView)
	//{{AFX_MSG_MAP(CDebFormView2)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDebFormView2 diagnostics

#ifdef _DEBUG
void CDebFormView2::AssertValid() const
{
	CFormView::AssertValid();
}

void CDebFormView2::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDebFormView2 message handlers

int CDebFormView2::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CRect rect;
	memset(&rect, 0, sizeof(CRect));
	if (!m_DebuggerCtrl.Create(
				NULL, 
				NULL, 
				lpCreateStruct->style, 
				rect,
				this, 
				0, 
				NULL
				))
		return -1;

	return 0;
}

void CDebFormView2::OnSize(UINT nType, int cx, int cy) 
{
	if (::IsWindow(m_stDebuggerCaption.m_hWnd) && ::IsWindow(m_DebuggerCtrl.m_hWnd)) 
	{
		CRect rect;
		m_stDebuggerCaption.GetClientRect(&rect);
		m_stDebuggerCaption.MoveWindow(
									0, 
									3*SIZE_YBORDER, 
									cx + 4*SIZE_XBORDER,
									m_iInitialStaticHeight + 3*SIZE_YBORDER
									);
		m_DebuggerCtrl.MoveWindow(
									-2*SIZE_XBORDER, 
									m_iInitialStaticHeight + 6*SIZE_YBORDER, 
									cx + 4*SIZE_XBORDER, 
									cy - m_iInitialStaticHeight - 4*SIZE_YBORDER
									);
		SetScrollSizes(m_nMapMode, CSize(cx, cy));
	}
	CFormView::OnSize(nType, cx, cy);	
}



void CDebFormView2::OnInitialUpdate() 
{
	CFormView::OnInitialUpdate();
	
	if (::IsWindow(m_stDebuggerCaption.m_hWnd) && ::IsWindow(m_DebuggerCtrl.m_hWnd)) 
	{
		CRect rect;
		m_stDebuggerCaption.GetClientRect(&rect);
		m_iInitialStaticHeight = rect.bottom;
	}	
}
