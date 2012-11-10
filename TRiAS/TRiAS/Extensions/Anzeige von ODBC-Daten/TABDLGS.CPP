// TabDlgs.cpp : implementation file
//

#include "pheader.h"		// vorübersetzter Header
#include "odbcext.hr"		// Resource-Konstanten
#include <protos.h>			// DELETE_VEC
#include <TabDlgs.hpp>		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabbedDialogs

CTabbedDialogs::CTabbedDialogs(int iDialogCnt)
{
//	prüfe Parameter
	ASSERT (iDialogCnt > 0);

	m_iMaxCnt = iDialogCnt;
	m_iActSel = -1;
	m_iActInd = -1;

	m_ppDialog = NULL;

	try
	{
		m_ppDialog = new CDialog *[m_iMaxCnt];

	//	init.
		memset (m_ppDialog, 0, m_iMaxCnt * sizeof (CDialog *));
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}
}

CTabbedDialogs::~CTabbedDialogs()
{
/*
	if (m_ppDialog)
	{
		for (int i = 0; i <= m_iActInd; i++)
		{
			DELETE_OBJ (m_ppDialog [i]);
		}
		DELETE_VEC (m_ppDialog);
	}
*/
	DELETE_VEC (m_ppDialog);
}

int CTabbedDialogs::AddDialog (CDialog *pDlg, UINT uiResID, const char *pTitle)
{
	try
	{
		ASSERT (m_iActInd+1 < m_iMaxCnt);	// nicht max. Anzahl überschreiten
		ASSERT (NULL != m_ppDialog);
		ASSERT (NULL != pTitle && AfxIsValidString (pTitle));
		ASSERT (NULL != pDlg);
		ASSERT (uiResID > 0);

		TC_ITEM tie;
		tie.mask = TCIF_TEXT | TCIF_IMAGE;
		tie.iImage = -1;
		tie.pszText = (char *) pTitle;
		m_iActInd++;
		VERIFY (m_iActInd == InsertItem (m_iActInd, &tie));
	
	//	Dialog speichern
		m_ppDialog [m_iActInd] = pDlg; 
		VERIFY (pDlg -> Create (uiResID, this));
		
	//	Dialog verschieben
		CRect rc, rcc;
		GetItemRect (0, &rc);
		int iY = rc.Height ();
		pDlg -> GetWindowRect (&rc);
		GetClientRect (&rcc);
		pDlg -> MoveWindow ((rcc.Width()-rc.Width())/2, 
							(((rcc.Height()-rc.Height()-iY)/2)+iY), 
							 rc.Width (), rc.Height ());
		
	//	Dialog nicht darstellen
		pDlg -> ShowWindow (SW_HIDE);
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
		return -1;
	}

	return m_iActInd;
}

BEGIN_MESSAGE_MAP(CTabbedDialogs, CTabCtrl)
	//{{AFX_MSG_MAP(CTabbedDialogs)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabbedDialogs message handlers

void CTabbedDialogs::OnSelchange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	SetActiveDialog (GetCurSel ());
	
	*pResult = 0;
}

void CTabbedDialogs::SetActiveDialog (int iSel)
{
//	prüfe Parameter
	ASSERT (iSel >= 0 && iSel <= m_iActInd);
	ASSERT (NULL != m_ppDialog);

	if (iSel == m_iActSel)
		return;

	for (int i = 0; i <= m_iActInd; i++)
	{
		if (i == iSel)
			m_ppDialog [i] -> ShowWindow (SW_NORMAL);
		else
			m_ppDialog [i] -> ShowWindow (SW_HIDE);
	}
	
	m_iActSel = iSel;
	if (GetCurSel () != m_iActSel)
		SetCurSel (m_iActSel);
}

BOOL CTabbedDialogs::SetActiveDialog (CDialog *pDlg)
{
	ASSERT (NULL != pDlg);
	ASSERT (NULL != m_ppDialog);

	BOOL bFound = FALSE;
	for (int i = 0; i <= m_iActInd; i++)
	{
		if (m_ppDialog [i] == pDlg)
		{
			m_ppDialog [i] -> ShowWindow (SW_NORMAL);
			bFound = TRUE;
			m_iActSel = i;
			if (GetCurSel () != m_iActSel)
				SetCurSel (m_iActSel);
		}
		else
			m_ppDialog [i] -> ShowWindow (SW_HIDE);
	}

	return bFound;
}

CDialog *CTabbedDialogs::GetDialog (int iSel)	
{
	ASSERT (iSel >= 0 && iSel <= m_iActInd);
	ASSERT (NULL != m_ppDialog);

	return m_ppDialog [iSel];
}

CDialog *CTabbedDialogs::GetActiveDialog (void)
{
	ASSERT (NULL != m_ppDialog);

	if (m_iActSel >= 0)
		return m_ppDialog [m_iActSel];
	else
		return NULL;
}

BOOL CTabbedDialogs::OnCommand (WPARAM wParam, LPARAM lParam)
{
	return (BOOL) ::SendMessage (GetParent () -> m_hWnd, WM_COMMAND, wParam, lParam);
}

