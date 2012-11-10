// addfdlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"

#include "iobjmex.h"
#include <iObjMan.h>

#include "enumex.h"
#include "ObjMn.h"
#include "timedlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHideTimerDialog dialog


CHideTimerDialog::CHideTimerDialog(CObjectManagement *pIOM, CWnd* pParent /*=NULL*/)
	: CDialog(CHideTimerDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHideTimerDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// Backpointer nicht AddRef(),
	// Dialog wird erst in ~CObjectManagement()
	// freigegeben (Rekursion)
	m_pObjectManagement = pIOM;
}
CHideTimerDialog::~CHideTimerDialog()
{
	// Backpointer nicht Release(),
	// Dialog wird erst in ~CObjectManagement()
	// freigegeben (Rekursion)
	m_pObjectManagement = NULL;
}


void CHideTimerDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHideTimerDialog)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHideTimerDialog, CDialog)
	//{{AFX_MSG_MAP(CHideTimerDialog)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHideTimerDialog message handlers

BOOL CHideTimerDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetTimer (0, 100, NULL);
	return false;  // return FALSE if you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CHideTimerDialog::OnDestroy() 
{	
	KillTimer (0);
	CDialog::OnDestroy();	
}

void CHideTimerDialog::OnTimer(UINT nIDEvent)
{
	ASSERT(m_pObjectManagement);
	if (NULL == m_pObjectManagement) return;
	m_pObjectManagement -> DelayedDelete();
}
