
// SelNum.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp
#include "selset.h"		// CSelectSet	
#include "feldinfo.h"	// CFeldInfos
#include "SelNum.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelNumberDlg dialog
CSelNumberDlg::CSelNumberDlg(CWnd* pParent, CSelectSet *pSet, UINT uiCaptionID,
							 const char *pTableName, const char *pSel /*=NULL*/, 
							 UINT uiThirdFieldId /*=0*/,
							 BOOL bReadName /*=FALSE*/)
			  :CDialog()
{
	//{{AFX_DATA_INIT(CSelNumberDlg)
	//}}AFX_DATA_INIT
	m_bIngnoreChange = FALSE;
	m_pSet = NULL;
	m_pParent = NULL;
	m_bIsModal = FALSE;
	m_bReadName = bReadName;

	ASSERT (pSet != NULL);
	ASSERT (pParent != NULL);
	ASSERT (uiCaptionID > 0);
	ASSERT (NULL != pTableName && AfxIsValidString (pTableName));

	m_pSet = pSet;
	m_pParent = pParent;
	m_uiThirdFieldId = uiThirdFieldId;
	m_strTableName = pTableName;

	m_uiCaptionID = uiCaptionID;
	StoreSelection (pSel);
}

CSelNumberDlg::CSelNumberDlg(CWnd* pParent, CSelectSet *pSet, 
							 const char *pTableName, UINT uiCaptionID,
							 BOOL bReadName /*=FALSE*/, const char *pSelection /*NULL*/)
			  :CDialog (CSelNumberDlg::IDD, pParent)
{
	m_bIngnoreChange = FALSE;
	m_pSet = NULL;
	m_pParent = NULL;
	m_uiThirdFieldId = 0;
	m_bIsModal = TRUE;
	m_bReadName = bReadName;

	ASSERT (pSet != NULL);
	ASSERT (pParent != NULL);
	ASSERT (uiCaptionID > 0);
	ASSERT (NULL != pTableName && AfxIsValidString (pTableName));

	m_pSet = pSet;
	m_pParent = pParent;
	m_strTableName = pTableName;

	m_uiCaptionID = uiCaptionID;

	if (pSelection && *pSelection)
		m_strNumber = pSelection;
}

void CSelNumberDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelNumberDlg)
	DDX_Control(pDX, IDC_CNT, m_stCnt);
	DDX_Control(pDX, IDE_SEARCH, m_edSearch);
	DDX_Control(pDX, IDE_SEARCH_NUMBER, m_edNummer);
	DDX_Control(pDX, IDB_STORE_DATA, m_btStore);
	DDX_Control(pDX, IDOK, m_btOk);
	DDX_Control(pDX, IDC_SELECT, m_lcListe);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSelNumberDlg, CDialog)
	//{{AFX_MSG_MAP(CSelNumberDlg)
	ON_NOTIFY(NM_CLICK, IDC_SELECT, OnClickSelect)
	ON_NOTIFY(NM_DBLCLK, IDC_SELECT, OnDblclkSelect)
	ON_WM_HELPINFO()
	ON_EN_CHANGE(IDE_SEARCH, OnChangeSearch)
	ON_EN_CHANGE(IDE_SEARCH_NUMBER, OnChangeNummer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelNumberDlg message handlers

BOOL CSelNumberDlg::OnInitDialog() // kein TRY/CATCH // ok
{
	CDialog::OnInitDialog();

//	TODO: Add extra initialization here
//	Sanduhr einschalten
	CWaitCursor wc;

//	Column-Namen lesen
	CString strName, strNummer;
	if (! strName.LoadString (IDS_NAME) ||
		! strNummer.LoadString (IDS_NUMMER) ||
		(m_lcListe.InsertColumn (0, strName) != 0) ||
		(m_lcListe.InsertColumn (1, strNummer) != 1))
		AfxThrowResourceException ();

	if (m_uiThirdFieldId > 0)
	{
		CString strThirdField;
		VERIFY (strThirdField.LoadString (m_uiThirdFieldId));
		if (m_lcListe.InsertColumn (2, strThirdField) != 2)
			AfxThrowResourceException ();
	}

//	ListBox füllen
	ASSERT (m_pSet != NULL && m_pSet -> IsOpen ());	
		
	int iIndex = 0;					// akt. Item
	if (!m_bIsModal)
		m_pSet -> MoveFirst ();			// zur Sicherheit
	while (! m_pSet -> IsEOF ())	// alle Infos ausgeben	
	{	
		if ((m_lcListe.InsertItem (iIndex, m_pSet -> m_Name) == iIndex) &&
			m_lcListe.SetItemText (iIndex, 1, m_pSet -> m_Nummer))
			iIndex++;		// nächster Item
		else
			AfxThrowMemoryException ();

		m_pSet -> MoveNext ();
	}

//	Caption setzen
	CString strCaption;
	VERIFY (strCaption.LoadString (m_uiCaptionID));
	SetWindowText (strCaption);

//	Anzahl Einträge setzen
	m_stCnt.GetWindowText (strCaption);
	char Buffer [80] = "";
	wsprintf (Buffer, strCaption, iIndex);
	m_stCnt.SetWindowText (Buffer);

	CRect rc;
	GetClientRect (&rc);
	if (0 == m_uiThirdFieldId)
	{
		m_lcListe.SetColumnWidth (0, rc.Width () * 2 / 3);
		m_lcListe.SetColumnWidth (1, rc.Width () / 3);
	}
	else
	{
		m_lcListe.SetColumnWidth (0, rc.Width () * 6 / 10);
		m_lcListe.SetColumnWidth (1, rc.Width () * 2 / 10);
		m_lcListe.SetColumnWidth (2, rc.Width () * 1 / 10);
	}

//	Selektion "beibehalten" setzen
	long lAttr = :: GetWindowLong (m_lcListe.m_hWnd, GWL_STYLE);
	:: SetWindowLong (m_lcListe.m_hWnd, GWL_STYLE, lAttr | LVS_SHOWSELALWAYS);

	if (m_bIsModal)
	{
		m_btStore.ShowWindow (SW_HIDE);

		if (!m_strNumber.IsEmpty ())
			StoreSelection (m_strNumber);
	}
	else
		m_btStore.SetCheck (1);		// Daten immer im Hintergrund speichern

	UpdateWindow ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSelNumberDlg::OnCancel()			// ok
{
	// TODO: Add extra cleanup here
	CDialog::OnCancel ();

	if (!m_bIsModal)
	{
		if (m_btStore.GetCheck () != 1)		// Fenster nicht speichern ?
			DestroyWindow ();
	}
//	KK990709
	CWnd * pWnd = this->GetSafeOwner(m_pParent);
	pWnd->BringWindowToTop();
	pWnd->SetFocus();
}

//	Selektion in ListBox anzeigen
void CSelNumberDlg::ChangeName (const CString &strSelection)		
{
	if (!strSelection.IsEmpty ())
	{
	//	Suchstruktur init.
		LV_FINDINFO fi;						
		memset (&fi, 0, sizeof (fi));
		fi.flags = LVFI_PARTIAL;
		fi.psz = strSelection;

	//	suche Item in ListControl		
		int	iItem = m_lcListe.FindItem (&fi, -1);
		if (iItem >= 0)
		{
			m_lcListe.EnsureVisible (iItem, FALSE);
			m_lcListe.SetItemState (iItem, LVIS_SELECTED, LVIS_SELECTED);						
		}
	}
}

void CSelNumberDlg::StoreSelection (const char *pNummer, const char *pName)
{
	try
	{
		CMutex mt;
		CWaitCursor wc;
		if (pNummer && *pNummer)
		{
			CString strSel;
			m_strSelection = pNummer;
			int iIndex = m_lcListe.GetNextItem (-1, LVNI_SELECTED);
			if (iIndex >= 0)						
			{
				strSel = m_lcListe.GetItemText (iIndex, 1);
				if (strSel == m_strSelection)	// wenn Nummer stimmt
				{
					m_bIngnoreChange = TRUE;
					m_edNummer.SetWindowText (m_strSelection); // Nummer setzen
					m_bIngnoreChange = FALSE;

				//	ggf. noch Name prüfen
					if (pName && *pName)
					{
						m_strName = pName;
						strSel = m_lcListe.GetItemText (iIndex, 0);	// Name
						if (m_strName == strSel)
							return;	// Name gefunden
					}
					return;			// kein Name gegeben
				}
			}

		//	wenn Name gegeben und noch keine Selektion: spezielles Suchverfahren
			if (pName && *pName)
			{
				m_strName = pName;			// Name speichern
				LV_FINDINFO fi;						
				memset (&fi, 0, sizeof (fi));
				fi.flags = LVFI_STRING;		// exakt match
				fi.psz = m_strName;

			//	suche Item in ListControl		
				iIndex = -1;		// Suche am beginnt am Anfang
				while ((iIndex = m_lcListe.FindItem (&fi, iIndex)) >= 0)
				{
					strSel = m_lcListe.GetItemText (iIndex, 1);	 				
					if (m_strSelection == strSel)	// stimmt Nummer ?
						break;
				}
				m_lcListe.EnsureVisible (iIndex, FALSE);
				m_lcListe.SetItemState (iIndex, LVIS_SELECTED, LVIS_SELECTED);							
			}
			else
			{
			//	Nummer selektieren: keine Selektion vorhanden 				
				if (ChangeNummer (m_strSelection))
				{
					m_bIngnoreChange = TRUE;
					m_edNummer.SetWindowText (m_strSelection);
					m_bIngnoreChange = FALSE;
				}
			}
		}
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}
}

void CSelNumberDlg::PostNcDestroy()			// ok
{
	// TODO: Add your specialized code here and/or call the base class

//	Parent benachrichtigen
	if (m_bIsModal)
		CDialog::PostNcDestroy();
	else
	{
		ASSERT (m_pParent != NULL);
		m_pParent -> SendMessage (IDM_SEND_DELETEOBJ, 0, 0L);

		CDialog::PostNcDestroy();
		delete this;
	}
}

void CSelNumberDlg::OnOK()					// ok
{
//	TODO: Add extra validation here
//	Werte an Parent senden
	SendValues ();

	CDialog::OnOK();


	if (!m_bIsModal)
	{
		if (m_btStore.GetCheck () != 1)		// Fenster nicht speichern ?
			DestroyWindow ();
	}
//	KK990709
	CWnd * pWnd = this->GetSafeOwner(m_pParent);
	pWnd->BringWindowToTop();
	pWnd->SetFocus();
	
}

void CSelNumberDlg::OnClickSelect(NMHDR* pNMHDR, LRESULT* pResult) // ok
{
	// TODO: Add your control notification handler code here
	m_btOk.EnableWindow (TRUE);

	*pResult = 0;
}

void CSelNumberDlg::OnDblclkSelect(NMHDR* pNMHDR, LRESULT* pResult) // ok
{
//	TODO: Add your control notification handler code here
//	Werte an Parent senden
	// SendValues ();
	// EndDialog (IDOK); 

	try
	{
		int iIndex = m_lcListe.GetNextItem (-1, LVNI_SELECTED);	
		if (iIndex >= 0)	// Index gültig
		{
			CString strSel (m_lcListe.GetItemText (iIndex, 1)); // Nummer lesen

			CString strName;
		//	ggf. auch Name lesen
			if (m_bReadName)
				strName = (m_lcListe.GetItemText (iIndex, 0)); // Name lesen

			ASSERT (NULL != m_pSet);
			ASSERT_VALID (m_pSet);
			CFeldInfos Infos (this, m_pSet, strSel, m_strTableName, strName); 
			Infos.DoModal ();	// Detail-Dialog rufen
		}
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	m_btOk.EnableWindow (TRUE);
	*pResult = 0;
}

//	Werte an Parent senden
void CSelNumberDlg::SendValues (void)
{
	int iIndex = m_lcListe.GetNextItem (-1, LVNI_SELECTED);
	try
	{
		if (iIndex >= 0)
		{
			m_strNumber = m_lcListe.GetItemText (iIndex, 1);

		//	Werte an Parent senden
			if (!m_bIsModal)
			{
				ASSERT (m_pParent != NULL);
				CString strName;
				strName = m_lcListe.GetItemText (iIndex, 0);
				m_pParent -> SendMessage (IDM_SEND_NUMBER, 0, (LPARAM)(const char *) m_strNumber);
				m_pParent -> SendMessage (IDM_SEND_TEXT, 0, (LPARAM) (const char *) strName);
			}				
		}
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();			// Fehler ausgeben
		me -> Delete ();
	}
}

BOOL CSelNumberDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;	
	// return CDialog::OnHelpInfo(pHelpInfo);
}

void CSelNumberDlg::OnChangeSearch() 
{
//	TODO: Add your control notification handler code here
	CString strSelection;
	m_edSearch.GetWindowText (strSelection);
	ChangeName (strSelection);
}

//	Nummer im Suchfeld hat sich geändert
void CSelNumberDlg::OnChangeNummer()
{
	CString strEnter;
	m_edNummer.GetWindowText (strEnter);		// eingegebene Nummer
	ChangeNummer (strEnter);
}
	
BOOL CSelNumberDlg::ChangeNummer (const CString &strSearch)
{
	if (m_bIngnoreChange)
		return TRUE;
	try
	{
		CWaitCursor wc;
		CMutex mt;
		if (!strSearch.IsEmpty ())
		{
			register int iIndex = -1;
			CString strSel;
			register int iCnt = m_lcListe.GetItemCount ();
			char *pFound = NULL;
			for (iIndex = 0; iIndex < iCnt; iIndex++)
			{
				strSel = m_lcListe.GetItemText (iIndex, 1); // Nummer lesen			
				pFound = strstr (strSel, strSearch);
				if (pFound && pFound == (char *)(const char *)strSel)
				{
					m_lcListe.EnsureVisible (iIndex, FALSE);
					m_lcListe.SetItemState (iIndex, LVIS_SELECTED, LVIS_SELECTED);							
					return TRUE;
				}
			}
		}
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	return FALSE;
}

