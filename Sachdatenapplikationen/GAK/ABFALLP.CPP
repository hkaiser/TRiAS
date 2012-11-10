// AbfallP.cpp : implementation file
//

#include "stdafx.h"		//	prec. Header
#include "gak.h"		//	CGakApp
#include "selset.h"		//	CSelectSet
#include "selnum.h"		//	CSelNumberDlg
#include "numedit.h"	//	CRealEdit

#include "AbfallP.h"	//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	Konstanten
const char szMinMenge [] = "2";			// Mengenschwelle

/////////////////////////////////////////////////////////////////////////////
// CAbfallParam property page

IMPLEMENT_DYNCREATE(CAbfallParam, CPropertyPage)

CAbfallParam::CAbfallParam() : CPropertyPage(CAbfallParam::IDD)
{
	//{{AFX_DATA_INIT(CAbfallParam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pQueryDef = NULL;
	m_pSet = NULL;
}

CAbfallParam::~CAbfallParam()
{
	DELETE_OBJ (m_pSet);
}

void CAbfallParam::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAbfallParam)
	DDX_Control(pDX, IDE_ABF_BEZ, m_edName);
	DDX_Control(pDX, IDE_ABFART, m_edAbfall);
	DDX_Control(pDX, IDE_MENGE, m_edMenge);
	DDX_Control(pDX, IDB_SELECT, m_btSelect);
	DDX_Control(pDX, IDB_ONLY_SONDER_ABF, m_btOnlySonder);
	DDX_Control(pDX, IDB_ALL_ABF, m_btAlle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAbfallParam, CPropertyPage)
	//{{AFX_MSG_MAP(CAbfallParam)
	ON_BN_CLICKED(IDB_SELECT, OnSelectAbfallart)
	ON_EN_CHANGE(IDE_ABFART, OnChangeAbfart)
	ON_EN_CHANGE(IDE_MENGE, OnChangeMenge)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDB_ALL_ABF, OnAlleAbfallarten)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAbfallParam message handlers

BOOL CAbfallParam::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();

//	TODO: Add extra initialization here
	try
	{
		ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());

		int iCnt = m_pQueryDef -> GetParameterCount();
		ASSERT (iCnt > 0);

	//	Set öffnen
		CWaitCursor wc;
		if (NULL == m_pSet)
		{
			m_pSet = new CSelectSet (m_pQueryDef -> m_pDatabase, 
									((CGakApp *)AfxGetApp ())->AbfallArtenDefaultSQL());
			m_pSet -> Open (dbOpenSnapshot);
		}
		
	//	suche Parameterinfo in Query: prmAbfallart
		m_edAbfall.LimitText (AbfallArtNummerLaenge);
		CString strParam;
		VERIFY (strParam.LoadString (IDS_ABF_ART_PARAM));
		try
		{
			m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfoAbfArt, AFX_DAO_SECONDARY_INFO);
			if (m_QueryInfoAbfArt.m_nType != dbText)
				m_QueryInfoAbfArt.m_strName.Empty ();		
		} 
		catch (CDaoException *db)
		{
		//	nur auffangen
			db -> Delete ();
		}

	//	Parameter Menge
		VERIFY (strParam.LoadString (IDS_MENGE_PARAM));
		try
		{
			m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfoAbfMenge, AFX_DAO_SECONDARY_INFO);
			if (m_QueryInfoAbfMenge.m_nType != dbSingle)
				m_QueryInfoAbfMenge.m_strName.Empty ();		
		} 
		catch (CDaoException *db)
		{
		//	nur auffangen
			db -> Delete ();
		}

	//	jetzt Parameter alle Abfallarten suchen
		VERIFY (strParam.LoadString (IDS_ALLE_ABF_ART_PARAM));
		try
		{
			m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfoAlleAbf, AFX_DAO_SECONDARY_INFO);
			if (m_QueryInfoAlleAbf.m_nType != dbBoolean)
				m_QueryInfoAlleAbf.m_strName.Empty ();		
		} 
		catch (CDaoException *db)
		{
		//	nur auffangen
			db -> Delete ();
		}

	//	wenn Parameter Nur Sonderabfälle
		VERIFY (strParam.LoadString (IDS_ONLY_SONDER_ABF_PARAM));
		try
		{
			m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfoNurSonderAbf, AFX_DAO_SECONDARY_INFO);
			if (m_QueryInfoNurSonderAbf.m_nType != dbBoolean)
				m_QueryInfoNurSonderAbf.m_strName.Empty ();		
		} 
		catch (CDaoException *db)
		{
		//	nur auffangen
			db -> Delete ();
		}
		
	//	jetzt Controls aktivieren, deak.
		m_edAbfall.EnableWindow (!m_QueryInfoAbfArt.m_strName.IsEmpty ());
		m_btSelect.EnableWindow (!m_QueryInfoAbfArt.m_strName.IsEmpty ());
		m_edMenge.EnableWindow (!m_QueryInfoAbfMenge.m_strName.IsEmpty ());
		m_btOnlySonder.EnableWindow (!m_QueryInfoNurSonderAbf.m_strName.IsEmpty ());
		m_btAlle.EnableWindow (!m_QueryInfoAlleAbf.m_strName.IsEmpty ());
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

BOOL CAbfallParam::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());
	
//	Werte lesen und setzen	
	CString strVal;
	if (!m_QueryInfoAbfArt.m_strName.IsEmpty ())
	{
		GetQueryParamValue (m_QueryInfoAbfArt, strVal);
		m_edAbfall.SetWindowText (strVal);
		OutputName (strVal);
	}

//	Mengenschwelle
	if (!m_QueryInfoAbfMenge.m_strName.IsEmpty ())
	{
		GetQueryParamValue (m_QueryInfoAbfMenge, strVal);
		if (strVal.IsEmpty ())
			strVal = szMinMenge;
		m_edMenge.SetWindowText (strVal);
	}

//	Nur Sonderabfälle
	if (!m_QueryInfoNurSonderAbf.m_strName.IsEmpty ())
	{
		GetQueryParamValue (m_QueryInfoNurSonderAbf, strVal);
		if (!strVal.IsEmpty ())
			m_btOnlySonder.SetCheck (strVal == "0" ? 0 : 1);
	}

//	Alle Abfälle
	if (!m_QueryInfoAlleAbf.m_strName.IsEmpty ())
	{
		GetQueryParamValue (m_QueryInfoAlleAbf, strVal);
		if (!strVal.IsEmpty ())
			m_btAlle.SetCheck (strVal == "0" ? 0 : 1);
	}

	SetWButtons ();

	return CPropertyPage::OnSetActive();
}

BOOL CAbfallParam::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());

//	Werte speichern: zuerst NurSonderabfall
	CString strVal; 
	if (!m_QueryInfoNurSonderAbf.m_strName.IsEmpty ())
	{
		strVal = (1 == m_btOnlySonder.GetCheck () ? "1" : "0");
		VERIFY (WriteQueryParamValue (m_QueryInfoNurSonderAbf, strVal));
		m_pQueryDef->SetParamValue (m_QueryInfoNurSonderAbf.m_strName, m_QueryInfoNurSonderAbf.m_varValue);
	}

//	Alle Abfallarten
	if (!m_QueryInfoAlleAbf.m_strName.IsEmpty ())
	{
		strVal = (1 == m_btAlle.GetCheck () ? "1" : "0");
		VERIFY (WriteQueryParamValue (m_QueryInfoAlleAbf, strVal));
		m_pQueryDef->SetParamValue (m_QueryInfoAlleAbf.m_strName, m_QueryInfoAlleAbf.m_varValue);
	}

//	Menge
	if (!m_QueryInfoAbfMenge.m_strName.IsEmpty ())
	{
		m_edMenge.GetWindowText (strVal);
		if (strVal.IsEmpty ())
			strVal = "0";
		VERIFY (WriteQueryParamValue (m_QueryInfoAbfMenge, strVal));
		m_pQueryDef->SetParamValue (m_QueryInfoAbfMenge.m_strName, m_QueryInfoAbfMenge.m_varValue);
	}

//	Abfallart
	if (!m_QueryInfoAbfArt.m_strName.IsEmpty ())
	{
		m_edAbfall.GetWindowText (strVal);
		VERIFY (WriteQueryParamValue (m_QueryInfoAbfArt, strVal));
		m_pQueryDef->SetParamValue (m_QueryInfoAbfArt.m_strName, m_QueryInfoAbfArt.m_varValue);
	}

	return CPropertyPage::OnKillActive();
}

void CAbfallParam::OnSelectAbfallart() 
{
	// TODO: Add your control notification handler code here
	m_btSelect.EnableWindow (FALSE);

	try
	{
		CWaitCursor wc;
		CString strNummer;
		m_edAbfall.GetWindowText (strNummer);

		ASSERT (m_pSet -> IsOpen ());

	//	neue Branchennummer vom Nutzer eingeben
		m_pSet -> MoveFirst ();
		CSelNumberDlg Dlg (this, m_pSet, ((CGakApp *)AfxGetApp ())->AbfallArtenDefaultSQL(), 
						   IDS_ABFART_CAPTION, FALSE, strNummer);
		if (Dlg.DoModal () == IDOK && !Dlg.m_strNumber.IsEmpty ())
		{
			m_edAbfall.SetWindowText (Dlg.m_strNumber);

		//	zugeh. Name ausgeben
			OutputName (Dlg.m_strNumber);
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

void CAbfallParam::OnChangeAbfart() 
{
	// TODO: Add your control notification handler code here
	SetWButtons ();
}

void CAbfallParam::OnChangeMenge() 
{
	// TODO: Add your control notification handler code here
	SetWButtons ();
}

//	Wizzard-Button setzen
void CAbfallParam::SetWButtons ()
{
	CPropertySheet *pSheet = (CPropertySheet *) GetParent ();			
	ASSERT (NULL != pSheet);
	ASSERT_VALID (pSheet);

//	zuerst vorige Seite bestimmen
	DWORD dwFlags =  pSheet -> GetActiveIndex () > 0 ? PSWIZB_BACK : 0;

	if (1 == m_btAlle.GetCheck ())
	{
		if (!m_QueryInfoAbfMenge.m_strName.IsEmpty ())
		{
			if (m_edMenge.LineLength () > 0)
				dwFlags |= PSWIZB_NEXT;
		}
		else
			dwFlags |= PSWIZB_NEXT;			
	}
	else
	{		
	//	nicht alle gesetzt
		if (!m_QueryInfoAbfArt.m_strName.IsEmpty () && !m_QueryInfoAbfMenge.m_strName.IsEmpty ())
		{
			if ((m_edMenge.LineLength () > 0) && (m_edAbfall.LineLength () > 0))
				dwFlags |= PSWIZB_NEXT;
		}
		else
		{
			if (!m_QueryInfoAbfArt.m_strName.IsEmpty ())
			{
				if (m_edAbfall.LineLength () > 0)
					dwFlags |= PSWIZB_NEXT;
			}
			else
			{
				if (!m_QueryInfoAbfMenge.m_strName.IsEmpty ())
				{
					if (m_edMenge.LineLength () > 0)
						dwFlags |= PSWIZB_NEXT;
				}
				else
					dwFlags |= PSWIZB_NEXT;
			}
		}	
	}

// JG 981007
// die verschiedenen Wahlmöglichkeiten schalten

	// wenn alle Abfallarten aktiviert ist, dann die auswahl einer Abfallart deaktivieren
	//	jetzt Controls aktivieren, deak.
	bool bAlle = (m_btAlle.GetCheck() == 1);
	m_edAbfall.EnableWindow (!m_QueryInfoAbfArt.m_strName.IsEmpty () && !bAlle);
	m_btSelect.EnableWindow (!m_QueryInfoAbfArt.m_strName.IsEmpty () && !bAlle);
//	m_edMenge.EnableWindow (!m_QueryInfoAbfMenge.m_strName.IsEmpty () && !bAlle);


//	Buttons setzen
	pSheet -> SetWizardButtons (dwFlags);
}

void CAbfallParam :: OnHelp ()
{
	AfxGetApp () -> WinHelp (IDD+HelpDialogOffset);
}

void CAbfallParam::OutputName (const CString &strNumber)
{
//	prüfe Parameter
	ASSERT (NULL != m_pSet && m_pSet -> IsOpen ());
	
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

void CAbfallParam::OnAlleAbfallarten() 
{
	// TODO: Add your control notification handler code here
	SetWButtons ();
}
