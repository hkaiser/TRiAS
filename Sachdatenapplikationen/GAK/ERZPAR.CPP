// ErzPar.cpp : implementation file
//
#include "stdafx.h"		//	prec. Header
#include "gak.h"		//	CGakApp
#include "ChangeNr.h"	//	CChangeNummerDlg
#include "FirmaSet.h"	//	CFirmaSet	

#include "ErzPar.h"		//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErzeugerParam property page

IMPLEMENT_DYNCREATE(CErzeugerParam, CPropertyPage)

CErzeugerParam::CErzeugerParam() : CPropertyPage(CErzeugerParam::IDD)
{
	//{{AFX_DATA_INIT(CErzeugerParam)
	//}}AFX_DATA_INIT
	m_pSet = NULL;
	m_pQueryDef = NULL;
}

CErzeugerParam::~CErzeugerParam()
{
	m_pQueryDef = NULL;
	DELETE_OBJ (m_pSet);
}

void CErzeugerParam::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErzeugerParam)
	DDX_Control(pDX, IDE_FIRMA, m_edName);
	DDX_Control(pDX, IDE_ERZ_NR, m_edNummer);
	DDX_Control(pDX, IDB_ERZEUGER, m_btSelect);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CErzeugerParam, CPropertyPage)
	//{{AFX_MSG_MAP(CErzeugerParam)
	ON_BN_CLICKED(IDB_ERZEUGER, OnErzeuger)
	ON_COMMAND(ID_HELP, OnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErzeugerParam message handlers

BOOL CErzeugerParam::OnSetActive() 
{
// TODO: Add your specialized code here and/or call the base class
//	Prüfe Parameter
	ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());
	
//	Wert lesen und setzen	
	if (!m_QueryInfo.m_strName.IsEmpty ())
	{
		CString strVal;
		GetQueryParamValue (m_QueryInfo, strVal);
		m_edNummer.SetWindowText (strVal);
		OutputName (strVal);
	}

	SetWButtons ();

	return CPropertyPage::OnSetActive();
}

BOOL CErzeugerParam::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
//	Prüfe Parameter
	ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());
	
//	Wert speichern
	if (!m_QueryInfo.m_strName.IsEmpty ())
	{
		CString strVal;
		m_edNummer.GetWindowText (strVal);
		VERIFY (WriteQueryParamValue (m_QueryInfo, strVal));
		m_pQueryDef->SetParamValue (m_QueryInfo.m_strName, m_QueryInfo.m_varValue);
	}

	return CPropertyPage::OnKillActive();
}

//	Nutzer will Erzeuger-Nummer auswählen
void CErzeugerParam::OnErzeuger() 
{
	// TODO: Add your control notification handler code here
	m_btSelect.EnableWindow (FALSE);

	try
	{
		CWaitCursor wc;
		CString strNummer;
		m_edNummer.GetWindowText (strNummer);

#ifdef _BRANDENBURG
		CString strText;
		VERIFY (strText.LoadString (IDS_ERZNR_BRBRG));
		if (0 != (strNummer == strText))
			strNummer.Empty ();
#endif	_BRANDENBURG
		CChangeNummerDlg Dlg (m_pQueryDef -> m_pDatabase, strNummer, this, TRUE);
		if (IDOK == Dlg.DoModal ())
		{
			m_edNummer.SetWindowText (Dlg.m_strNummer);
			OutputName (Dlg.m_strNummer);
		}

		SetWButtons ();
	}
	catch (CDaoException *db)
	{
		::DisplayDaoException (db);
		db -> Delete ();
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}

	m_btSelect.EnableWindow (TRUE);
}

//	lese ParameterInfo aus Abfrage
BOOL CErzeugerParam::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
//	TODO: Add extra initialization here
//	Prüfe Parameter
	try
	{
		ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());
		ASSERT (NULL != m_pQueryDef -> m_pDatabase);
		ASSERT (m_pQueryDef -> m_pDatabase -> IsOpen ());

		int iCnt = m_pQueryDef -> GetParameterCount();
		ASSERT (iCnt > 0);

	//	Set anlegen
		if (NULL == m_pSet)
		{
			m_pSet = new CFirmaSet (m_pQueryDef -> m_pDatabase);
			m_pSet -> Open ();
		}			

	//	lese Vergleichsname
		CString strParam;
		VERIFY (strParam.LoadString (IDS_ERZEUGER_PARAM));
		m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfo, AFX_DAO_SECONDARY_INFO);

	//	Parameter gefunden ?
		if (m_QueryInfo.m_nType != dbText)
			m_QueryInfo.m_strName.Empty ();		

	//	Button setzen
		m_btSelect.EnableWindow (!m_QueryInfo.m_strName.IsEmpty ());
	}
	catch (CDaoException *db)
	{
		::DisplayDaoException (db);
		db -> Delete ();
	}
	catch (CMemoryException *me)
	{
		me -> ReportError ();
		me -> Delete ();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//	Wizzard-Button setzen
void CErzeugerParam::SetWButtons ()
{
	CPropertySheet *pSheet = (CPropertySheet *) GetParent ();			
	ASSERT (NULL != pSheet);
	ASSERT_VALID (pSheet);

//	zuerst vorige Seite bestimmen
	DWORD dwFlags =  pSheet -> GetActiveIndex () > 0 ? PSWIZB_BACK : 0;
	
//	wenn Parameter gültig, dann auch nächste Seite zulassen
	if (m_edNummer.LineLength () > 0)
		dwFlags |= PSWIZB_NEXT;
		
//	Buttons setzen
	pSheet -> SetWizardButtons (dwFlags);
}

void CErzeugerParam :: OnHelp ()
{
	AfxGetApp () -> WinHelp (IDD+HelpDialogOffset);
}

void CErzeugerParam :: OutputName (const CString &strNummer)
{
	ASSERT (NULL != m_pSet && m_pSet -> IsOpen ());
	if (strNummer.IsEmpty ())
		m_edName.SetWindowText ("");
	else
	{
		if (!(strNummer == m_pSet -> m_Nummer))
		{
			CString strFilter;
			AfxFormatString1 (strFilter, IDS_FIND_NUMMER, strNummer);
			CWaitCursor wc;
			m_pSet -> FindFirst (strFilter);
		}
		
		m_edName.SetWindowText (m_pSet -> m_Firmenname);
	}
}
