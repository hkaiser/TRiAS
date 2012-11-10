// ChangeNr.cpp : implementation file
//

#include "stdafx.h"		// vorübers. Header
#include "gak.h"		// CGakApp und Ressourcen
#include "searchse.h"	// CSearchSet
#include "numedit.h"	// CErzNrEdit
#include "ChangeNr.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	Konstanten
// const long MaxLBItems = 32767;	

/////////////////////////////////////////////////////////////////////////////
// CChangeNummerDlg dialog

CChangeNummerDlg::CChangeNummerDlg (CDaoDatabase *pDB, const char *pSel, 
									CWnd* pParent /*=NULL*/, BOOL bSelect /*=FALSE*/)
				 : CDialog(CChangeNummerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChangeNummerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pDatabase = NULL;

	ASSERT (pDB != NULL && pDB -> IsOpen ());
	m_pDatabase = pDB;

	m_bSelect = bSelect;

	if (pSel && *pSel)
		m_strNummer = pSel;
}


void CChangeNummerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChangeNummerDlg)
	DDX_Control(pDX, IDS_INFOTEXT, m_stInfo);
	DDX_Control(pDX, IDE_NUMMER, m_edNummer);
	DDX_Control(pDX, IDL_NUMMERN_ERZ, m_lbNummern);
	DDX_Control(pDX, IDOK, m_btOk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChangeNummerDlg, CDialog)
	//{{AFX_MSG_MAP(CChangeNummerDlg)
	ON_EN_CHANGE(IDE_NUMMER, OnChangeNummer)
	ON_LBN_DBLCLK(IDL_NUMMERN_ERZ, OnDblclkNummern)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChangeNummerDlg message handlers
void CChangeNummerDlg::OutputNummern (void)
{
	// TODO: Add your specialized code here and/or call the base class
	// ListBox füllen: kein TRY/CATCH
	ASSERT (m_pDatabase != NULL);

	CWaitCursor wc;
	CSearchSet Set (m_pDatabase);
	Set.Open (dbOpenSnapshot, NULL, dbForwardOnly);

	while (!Set.IsEOF ())
	{
		if (m_lbNummern.AddString (Set.m_strNummer) < 0)
			AfxThrowMemoryException ();
		Set.MoveNext ();
	}

	Set.Close ();
}

BOOL CChangeNummerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	TODO: Add extra initialization here
	OutputNummern ();			// ListBox füllen

	CString strCaption;
#ifdef _BRANDENBURG
	m_edNummer.LimitText (ErzNummerLaenge);
#else
	m_edNummer.LimitText (NummerLaenge);
#endif
	if (!m_strNummer.IsEmpty ())
	{
		m_edNummer.SetWindowText (m_strNummer);
		m_lbNummern.SelectString (-1, m_strNummer);
	}
#ifdef _BRANDENBURG
	else
	{
		CString strInfo;
		VERIFY (strInfo.LoadString (IDS_ERZNR_BRBRG));
		m_edNummer.SetWindowText (strInfo);		
	}
#endif

	if (m_bSelect)
		VERIFY (strCaption.LoadString (IDS_SELECT_NR));
	else 
	{			
		if (m_strNummer.IsEmpty ())
			VERIFY (strCaption.LoadString (IDS_ENTER_NR));
		else
			VERIFY (strCaption.LoadString (IDS_CHANGE_NR));
	}

//	Überschrift ausgeben
	SetWindowText (strCaption);

//	Anzahl Einträge ausgeben
	CString strFormat, strInfo;
	m_stInfo.GetWindowText (strFormat);
	char *pInfo = strInfo.GetBuffer	(strFormat.GetLength () + 10);
	wsprintf (pInfo, strFormat, m_lbNummern.GetCount ());
	m_stInfo.SetWindowText (pInfo);

	m_btOk.EnableWindow (FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CChangeNummerDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	m_strNummer.Empty ();
	
	CDialog::OnCancel();
}

void CChangeNummerDlg::OnChangeNummer() 
{
	// TODO: Add your control notification handler code here
	if (m_edNummer.LineLength () == ErzNummerLaenge)
	{
		m_btOk.EnableWindow (TRUE);
		CString strSel;
		m_edNummer.GetWindowText (strSel);	
		m_lbNummern.SelectString (-1, strSel);
	}		

	else
	{
#ifdef _BRANDENBURG
		if (m_edNummer.LineLength () == 1)
		{
			CString strInfo, strNr;
			VERIFY (strInfo.LoadString (IDS_ERZNR_BRBRG));
			m_edNummer.GetWindowText (strNr);
			if (strNr != strInfo)
			{                                                
				AfxFormatString1 (strNr, IDS_ERZNR_BRBRG_FORMAT, strInfo);
				((CGakApp *) AfxGetApp ()) -> OutputMessage (strNr);	
				m_edNummer.SetWindowText (strInfo);
				m_edNummer.SetSel (1, 1);
			}
		}
#endif
		m_btOk.EnableWindow (FALSE);			
		m_lbNummern.SetCurSel (-1);
	}
}

void CChangeNummerDlg::OnDblclkNummern() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_lbNummern.GetCurSel ();
	if (iSel >= 0)
	{		
		CString strSel;
		m_lbNummern.GetText (iSel, strSel);		
		m_edNummer.SetWindowText (strSel);
	}

	OnOK ();
}

void CChangeNummerDlg::OnOK() 
{
//	TODO: Add extra validation here
	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (pApp != NULL);
	ASSERT_VALID (pApp);

	m_edNummer.GetWindowText (m_strNummer);
	int iSel = m_lbNummern.FindStringExact (-1, m_strNummer);
	m_lbNummern.SetCurSel (iSel);
	if (!m_bSelect && iSel >= 0)
	{
	//	Info an Nutzer ausgeben
		pApp -> OutputMessage (IDS_NUMMER_EXIST);
		return;
	}
	else
	{
		if (m_bSelect && iSel < 0)
		{
			pApp -> OutputMessage (IDS_NUMMER_NOT_EXIST);
			return;
		}
	}
	
	CDialog::OnOK();
}

BOOL CChangeNummerDlg::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	
	ASSERT (pHelpInfo != NULL);

	if (pHelpInfo -> dwContextId)
		WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	// return CDialog::OnHelpInfo(pHelpInfo);
	return TRUE;
}
