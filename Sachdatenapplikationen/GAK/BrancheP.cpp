// BrancheP.cpp : implementation file
//

#include "stdafx.h"		//	prec. Header
#include "gak.h"		//	CGakApp
#include "selset.h"		//	CSelectSet
#include "selnum.h"		//	CSelNumberDlg
#include "numedit.h"	//	CRealedit	

#include "BrancheP.h"	//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBrancheParam property page

IMPLEMENT_DYNCREATE(CBrancheParam, CPropertyPage)

CBrancheParam::CBrancheParam() : CPropertyPage(CBrancheParam::IDD)
{
	//{{AFX_DATA_INIT(CBrancheParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pQueryDef = NULL;
	m_pSet = NULL;
}

CBrancheParam::~CBrancheParam()
{
	DELETE_OBJ (m_pSet);
}

void CBrancheParam::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBrancheParam)
	DDX_Control(pDX, IDB_ALLE, m_btAlle);
	DDX_Control(pDX, IDB_CHANGE, m_btChange);
	DDX_Control(pDX, IDE_NAME, m_edName);
	DDX_Control(pDX, IDE_NUMMER, m_edNummer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBrancheParam, CPropertyPage)
	//{{AFX_MSG_MAP(CBrancheParam)
	ON_BN_CLICKED(IDB_CHANGE, OnChange)
	ON_EN_CHANGE(IDE_NAME, OnChangeName)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_EN_CHANGE(IDE_NUMMER, OnChangeNummer)
	ON_BN_CLICKED(IDB_ALLE, OnAlle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBrancheParam message handlers

BOOL CBrancheParam::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());
	
//	Wert lesen und setzen	
	CString strValue;
	if (!m_QueryInfo.m_strName.IsEmpty ())
	{
		
		GetQueryParamValue (m_QueryInfo, strValue);
		m_edNummer.SetWindowText (strValue);

		OutputName (strValue);
	}

//	Alle Abfälle
	if (!m_QueryInfoAlle.m_strName.IsEmpty ())
	{
		GetQueryParamValue (m_QueryInfoAlle, strValue);
		if (!strValue.IsEmpty ())
			m_btAlle.SetCheck (strValue == "0" ? 0 : 1);
	}

	SetWButtons ();

	return CPropertyPage::OnSetActive();
}

BOOL CBrancheParam::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	//	Prüfe Parameter
	ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());
	
//	Wert speichern
	CString strVal;
	if (!m_QueryInfo.m_strName.IsEmpty ())
	{
		
		m_edNummer.GetWindowText (strVal);
		VERIFY (WriteQueryParamValue (m_QueryInfo, strVal));
		m_pQueryDef->SetParamValue (m_QueryInfo.m_strName, m_QueryInfo.m_varValue);
	}

//	Alle
	if (!m_QueryInfoAlle.m_strName.IsEmpty ())
	{
		strVal = (1 == m_btAlle.GetCheck () ? "1" : "0");
		VERIFY (WriteQueryParamValue (m_QueryInfoAlle, strVal));
		m_pQueryDef->SetParamValue (m_QueryInfoAlle.m_strName, m_QueryInfoAlle.m_varValue);
	}

	return CPropertyPage::OnKillActive();
}

BOOL CBrancheParam::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	//	Prüfe Parameter
	try
	{
		ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());

		int iCnt = m_pQueryDef -> GetParameterCount();
		ASSERT (iCnt > 0);

	//	Set öffnen
		CWaitCursor wc;
		if (NULL == m_pSet)
		{
			m_pSet = new CSelectSet (m_pQueryDef -> m_pDatabase, ((CGakApp *)AfxGetApp ())->BranchenDefaultSQL());
			m_pSet -> Open (dbOpenSnapshot);
		}
		
	//	suche Parameterinfo in Query
		CString strParam;
		VERIFY (strParam.LoadString (IDS_BRANCHE_PARAM));
		try
		{
			m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfo, AFX_DAO_SECONDARY_INFO);
			if (m_QueryInfo.m_nType != dbText)
				m_QueryInfo.m_strName.Empty ();	
		}
		catch (CDaoException *db)
		{
		//	nur auffangen
			db -> Delete ();
		}

	//	jetzt Parameter alle Branchen suchen
		VERIFY (strParam.LoadString (IDS_ALLE_BRANCHEN_PARAM));
		try
		{
			m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfoAlle, AFX_DAO_SECONDARY_INFO);
			if (m_QueryInfoAlle.m_nType != dbBoolean)
				m_QueryInfoAlle.m_strName.Empty ();		
		} 
		catch (CDaoException *db)
		{
		//	nur auffangen
			db -> Delete ();
		}

	//	Button setzen
		m_btChange.EnableWindow (!m_QueryInfo.m_strName.IsEmpty ());
		m_edNummer.EnableWindow (!m_QueryInfo.m_strName.IsEmpty ());
		m_btAlle.EnableWindow (!m_QueryInfoAlle.m_strName.IsEmpty ());
		m_edNummer.LimitText (BranchenNummerLaenge); 
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

void CBrancheParam::OutputName (const CString &strNumber)
{
//	prüfe Parameter
	ASSERT (NULL!= m_pSet && m_pSet -> IsOpen ());
	
	if (strNumber.IsEmpty ())
		m_edName.SetWindowText ("");
	else
	{
		if (!(strNumber == m_pSet -> m_Nummer))
		{
			CWaitCursor wc;	
			CString strFilter;
			AfxFormatString1 (strFilter, IDS_FIND_NUMMER, strNumber);
			m_pSet -> FindFirst (strFilter);
		}
		
		m_edName.SetWindowText (m_pSet -> m_Name);
	}
}


//	neue Nummer über Select-Button eingegeben
void CBrancheParam::OnChange() 
{
	// TODO: Add your control notification handler code here
	m_btChange.EnableWindow (FALSE);

	try
	{
		CWaitCursor wc;
		CString strNummer;
		m_edNummer.GetWindowText (strNummer);

		ASSERT (m_pSet -> IsOpen ());

	//	neue Branchennummer vom Nutzer eingeben
		m_pSet -> MoveFirst ();
		CSelNumberDlg BrDlg (this, m_pSet, ((CGakApp *)AfxGetApp ())->BranchenDefaultSQL(), 
							 IDS_BRANCHE_CAPTION, FALSE, strNummer);
		if (BrDlg.DoModal () == IDOK && !BrDlg.m_strNumber.IsEmpty ())
		{
			m_edNummer.SetWindowText (BrDlg.m_strNumber);

		//	zugeh. Name ausgeben
			OutputName (BrDlg.m_strNumber);
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

	m_btChange.EnableWindow (TRUE);
}

void CBrancheParam::OnChangeName() 
{
	// TODO: Add your control notification handler code here
	SetWButtons ();
}

//	Wizzard-Button setzen
void CBrancheParam::SetWButtons ()
{
	CPropertySheet *pSheet = (CPropertySheet *) GetParent ();			
	ASSERT (NULL != pSheet);
	ASSERT_VALID (pSheet);

//	zuerst vorige Seite bestimmen
	DWORD dwFlags =  pSheet -> GetActiveIndex () > 0 ? PSWIZB_BACK : 0;
	
//	wenn Parameter gültig, dann auch nächste Seite zulassen
	if ((1 == m_btAlle.GetCheck ()) || (m_edNummer.LineLength () > 0))
		dwFlags |= PSWIZB_NEXT;
		
//	Buttons setzen
	pSheet -> SetWizardButtons (dwFlags);

//  JG981009
// bei aktiviertem alle Button die Auswahl einer Branche deaktivieren
	bool bAlle = (m_btAlle.GetCheck() == 1);
	
	m_btChange.EnableWindow (!m_QueryInfo.m_strName.IsEmpty () && !bAlle);
	m_edNummer.EnableWindow (!m_QueryInfo.m_strName.IsEmpty () && !bAlle);
}

void CBrancheParam :: OnHelp ()
{
	AfxGetApp () -> WinHelp (IDD+HelpDialogOffset);
}

void CBrancheParam::OnChangeNummer() 
{
	// TODO: Add your control notification handler code here
	SetWButtons ();
}

void CBrancheParam::OnAlle() 
{
	// TODO: Add your control notification handler code here
	SetWButtons ();
}
