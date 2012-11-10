// GebietP.cpp : implementation file
//

#include "stdafx.h"		//	prec. Header
#include "gak.h"		//	CGakApp
#include "selset.h"		//	CSelectSet
#include "selnum.h"		//	CSelNumberDlg
#include "GebietP.h"	//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGebietParam property page

IMPLEMENT_DYNCREATE(CGebietParam, CPropertyPage)

CGebietParam::CGebietParam() : CPropertyPage(CGebietParam::IDD)
{
	//{{AFX_DATA_INIT(CGebietParam)
	//}}AFX_DATA_INIT
	m_pQueryDef = NULL;
	m_pSet = NULL;
	m_pSetKreis = NULL;
}

CGebietParam::~CGebietParam()
{
	DELETE_OBJ (m_pSet);
	DELETE_OBJ (m_pSetKreis);
}

void CGebietParam::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGebietParam)
	DDX_Control(pDX, IDB_GEMEINDE_SEL, m_btSelectGemeinde);
	DDX_Control(pDX, IDE_GKZ, m_edGKZ);
	DDX_Control(pDX, IDT_GEMEINDE, m_stGemeinde);
	DDX_Control(pDX, IDB_KREIS_SEL, m_btSelectKreis);
	DDX_Control(pDX, IDB_ALLE_GEMEINDEN, m_btAlleGemeinden);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CGebietParam, CPropertyPage)
	//{{AFX_MSG_MAP(CGebietParam)
	ON_COMMAND(ID_HELP, OnHelp)
	ON_BN_CLICKED(IDB_ALLE_GEMEINDEN, OnAlleGemeinden)
	ON_BN_CLICKED(IDB_GEMEINDE_SEL, OnGemeindeSelect)
	ON_BN_CLICKED(IDB_KREIS_SEL, OnKreisSelect)
	ON_EN_CHANGE(IDE_GKZ, OnChangeGkz)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGebietParam message handlers

void CGebietParam::OnAlleGemeinden() 
{
	// TODO: Add your control notification handler code here
	SetWButtons ();
}

void CGebietParam::OnGemeindeSelect() 
{
	// TODO: Add your control notification handler code here
	m_btSelectGemeinde.EnableWindow (FALSE);

	try
	{
		CWaitCursor wc;
		CString strNummer;
		m_edGKZ.GetWindowText (strNummer);

		ASSERT (m_pSet -> IsOpen ());

	//	neue GKZ vom Nutzer eingeben
		m_pSet -> MoveFirst ();
		CSelNumberDlg Dlg (this, m_pSet, ((CGakApp *)AfxGetApp ())->GemeindenDefaultSQL(), 
						   IDS_GEMEINDE_CAPTION, FALSE, strNummer);
		if (Dlg.DoModal () == IDOK && !Dlg.m_strNumber.IsEmpty ())
		{
			m_edGKZ.SetWindowText (Dlg.m_strNumber);

		//	zugeh. Name ausgeben
			OutputName (Dlg.m_strNumber, m_pSet);
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

	m_btSelectGemeinde.EnableWindow (TRUE);
}

void CGebietParam::OnKreisSelect() 
{
	// TODO: Add your control notification handler code here
	m_btSelectKreis.EnableWindow (FALSE);

	try
	{
		CWaitCursor wc;
		CString strNummer;
		m_edGKZ.GetWindowText (strNummer);

		ASSERT (m_pSetKreis -> IsOpen ());

	//	neuen Kreis vom Nutzer eingeben
		m_pSetKreis -> MoveFirst ();
		CSelNumberDlg Dlg (this, m_pSetKreis, ((CGakApp *)AfxGetApp ())->KreisDefaultSQL(), 
						   IDS_KREIS_CAPTION, FALSE, strNummer);
		if (Dlg.DoModal () == IDOK && !Dlg.m_strNumber.IsEmpty ())
		{
			m_edGKZ.SetWindowText (Dlg.m_strNumber);

		//	zugeh. Name ausgeben
			OutputName (Dlg.m_strNumber, m_pSetKreis);
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

	m_btSelectKreis.EnableWindow (TRUE);
}

BOOL CGebietParam::OnSetActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());

//	Werte lesen
	CString strVal;
	if (!m_QueryInfoAlleGemeinden.m_strName.IsEmpty ())
	{
		GetQueryParamValue (m_QueryInfoAlleGemeinden, strVal);
		if (!strVal.IsEmpty ())
			m_btAlleGemeinden.SetCheck (strVal == "0" ? 0 : 1);
	}
	else
	{	
		if (!m_QueryInfoAlleKreise.m_strName.IsEmpty ())
		{
			GetQueryParamValue (m_QueryInfoAlleKreise, strVal);
			if (!strVal.IsEmpty ())
				m_btAlleGemeinden.SetCheck (strVal == "0" ? 0 : 1);
		}
	}
		
//	Wert lesen und setzen	
	if (!m_QueryInfoGemeinde.m_strName.IsEmpty ())
	{
		GetQueryParamValue (m_QueryInfoGemeinde, strVal);
		m_edGKZ.SetWindowText (strVal);
		OutputName (strVal, m_pSet);
	}
	else
	{
		if (!m_QueryInfoKreis.m_strName.IsEmpty ())
		{
			GetQueryParamValue (m_QueryInfoKreis, strVal);
			m_edGKZ.SetWindowText (strVal);
			OutputName (strVal, m_pSetKreis);
		}
	}

	SetWButtons ();

	return CPropertyPage::OnSetActive();
}

BOOL CGebietParam::OnKillActive() 
{
	// TODO: Add your specialized code here and/or call the base class
	ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());

//	Werte speichern
	CString strVal (1 == m_btAlleGemeinden.GetCheck () ? "1" : "0");
	if (!m_QueryInfoAlleGemeinden.m_strName.IsEmpty ())
	{
		VERIFY (WriteQueryParamValue (m_QueryInfoAlleGemeinden, strVal));
		m_pQueryDef->SetParamValue (m_QueryInfoAlleGemeinden.m_strName, m_QueryInfoAlleGemeinden.m_varValue);
	}
	else
	{
		if (!m_QueryInfoAlleKreise.m_strName.IsEmpty ())
		{
			VERIFY (WriteQueryParamValue (m_QueryInfoAlleKreise, strVal));
			m_pQueryDef->SetParamValue (m_QueryInfoAlleKreise.m_strName, m_QueryInfoAlleKreise.m_varValue);
		}
	}

//	Gemeindekennzahl
	m_edGKZ.GetWindowText (strVal);
	if (!m_QueryInfoGemeinde.m_strName.IsEmpty ())
	{
		VERIFY (WriteQueryParamValue (m_QueryInfoGemeinde, strVal));
		m_pQueryDef->SetParamValue (m_QueryInfoGemeinde.m_strName, m_QueryInfoGemeinde.m_varValue);
	}
	else
	{
		if (!m_QueryInfoKreis.m_strName.IsEmpty ())
		{
			VERIFY (WriteQueryParamValue (m_QueryInfoKreis, strVal));
			m_pQueryDef->SetParamValue (m_QueryInfoKreis.m_strName, m_QueryInfoKreis.m_varValue);
		}
	}

	return CPropertyPage::OnKillActive();
}

BOOL CGebietParam::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	// TODO: Add extra initialization here

	try
	{
		ASSERT (NULL != m_pQueryDef && m_pQueryDef -> IsOpen ());

		int iCnt = m_pQueryDef -> GetParameterCount();
		ASSERT (iCnt > 0);

	//	Sets öffnen
		CWaitCursor wc;
		if (NULL == m_pSet)
		{
			m_pSet = new CSelectSet (m_pQueryDef -> m_pDatabase, ((CGakApp *)AfxGetApp ())->GemeindenDefaultSQL());
			m_pSet -> Open (dbOpenSnapshot);
		}
		if (NULL == m_pSetKreis)
		{
			m_pSetKreis = new CSelectSet (m_pQueryDef -> m_pDatabase, ((CGakApp *)AfxGetApp ())->KreisDefaultSQL());
			m_pSetKreis -> Open (dbOpenSnapshot);
		}
		
	//	suche Parameterinfo in Query: prmGemeindekennzahl
		CString strParam;
		m_edGKZ.LimitText (GemeindekennzahlLaenge);
		VERIFY (strParam.LoadString (IDS_GEMEINDE_PARAM));
		try
		{
			m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfoGemeinde, AFX_DAO_SECONDARY_INFO);
			if (m_QueryInfoGemeinde.m_nType != dbText)
				m_QueryInfoGemeinde.m_strName.Empty ();		
		} 
		catch (CDaoException *db)
		{
		//	nur auffangen
			db -> Delete ();
		}

	//	wenn Parameter Gemeinde nicht gefunden, dann mit dem Parameter Kreis neuer Versuch
		if (m_QueryInfoGemeinde.m_strName.IsEmpty ())
		{
			VERIFY (strParam.LoadString (IDS_KREIS_PARAM));
			try
			{
				m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfoKreis, AFX_DAO_SECONDARY_INFO);
				if (m_QueryInfoKreis.m_nType != dbText)
				{
					m_QueryInfoKreis.m_strName.Empty ();		
					m_edGKZ.LimitText (KreiskennzahlLaenge);
				}
			} 
			catch (CDaoException *db)
			{
			//	nur auffangen
				db -> Delete ();
			}
		}

	//	jetzt Parameter alle Gemeinden suchen
		VERIFY (strParam.LoadString (IDS_ALLE_GEMEINDEN_PARAM));
		try
		{
			m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfoAlleGemeinden, AFX_DAO_SECONDARY_INFO);
			if (m_QueryInfoAlleGemeinden.m_nType != dbBoolean)
				m_QueryInfoAlleGemeinden.m_strName.Empty ();		
		} 
		catch (CDaoException *db)
		{
		//	nur auffangen
			db -> Delete ();
		}

	//	wenn Parameter AlleGemeinden nicht gefunden, dann mit dem Parameter AlleKreise neuer Versuch
		if (m_QueryInfoAlleGemeinden.m_strName.IsEmpty ())
		{
			VERIFY (strParam.LoadString (IDS_ALLE_KREISE_PARAM));
			try
			{
				m_pQueryDef -> GetParameterInfo (strParam, m_QueryInfoAlleKreise, AFX_DAO_SECONDARY_INFO);
				if (m_QueryInfoAlleKreise.m_nType != dbBoolean)
					m_QueryInfoAlleKreise.m_strName.Empty ();		
			} 
			catch (CDaoException *db)
			{
			//	nur auffangen
				db -> Delete ();
			}
		}

	//	jetzt Controls aktivieren, deak.
		m_bSelectAll = !m_QueryInfoAlleGemeinden.m_strName.IsEmpty () ||
						  !m_QueryInfoAlleKreise.m_strName.IsEmpty ();
		m_btAlleGemeinden.EnableWindow (m_bSelectAll);

		m_bSelect = !m_QueryInfoGemeinde.m_strName.IsEmpty () || !m_QueryInfoKreis.m_strName.IsEmpty ();
		m_edGKZ.EnableWindow (m_bSelect);	
		m_btSelectGemeinde.EnableWindow (m_bSelect && m_QueryInfoKreis.m_strName.IsEmpty ());	
		m_btSelectKreis.EnableWindow (m_bSelect);	
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

void CGebietParam :: OnHelp ()
{
	AfxGetApp () -> WinHelp (IDD+HelpDialogOffset);
}

//	Wizzard-Button setzen und Ctrl's schalten 
void CGebietParam :: SetWButtons ()
{
	CPropertySheet *pSheet = (CPropertySheet *) GetParent ();
	ASSERT (NULL != pSheet);
	ASSERT_VALID (pSheet);

//	zuerst vorige Seite bestimmen
	DWORD dwFlags =  pSheet -> GetActiveIndex () > 0 ? PSWIZB_BACK : 0;
	
//	wenn Parameter gültig, dann auch nächste Seite zulassen
	BOOL bCheck = (!m_QueryInfoGemeinde.m_strName.IsEmpty () || !m_QueryInfoKreis.m_strName.IsEmpty ()) 
				   && (0 == m_btAlleGemeinden.GetCheck ());

	if (bCheck)
	{
		if (m_edGKZ.LineLength () > 0)
			dwFlags |= PSWIZB_NEXT;
	}
	else
		dwFlags |= PSWIZB_NEXT;
		
//	Buttons setzen
	pSheet -> SetWizardButtons (dwFlags);

//	In Abgängigkeit vom alle Button die anderen Ctrl's jeweils passivieren / aktivieren
	if (0 == m_btAlleGemeinden.GetCheck () && m_bSelect)
	{
		m_edGKZ.EnableWindow (m_bSelect);
		m_btSelectGemeinde.EnableWindow (m_bSelect && m_QueryInfoKreis.m_strName.IsEmpty ());
		m_btSelectKreis.EnableWindow (m_bSelect);
	}
	else
	{
		m_edGKZ.EnableWindow (false);
		m_btSelectGemeinde.EnableWindow (false);
		m_btSelectKreis.EnableWindow (false);
	}
}

void CGebietParam::OnChangeGkz() 
{
	// TODO: Add your control notification handler code here
	SetWButtons ();
}

//	Beschreibung ausgeben
void CGebietParam::OutputName (const CString &strNumber, CSelectSet *pSet)
{
//	prüfe Parameter
	ASSERT (pSet -> IsOpen ());
	
	if (strNumber.IsEmpty ())
		m_stGemeinde.SetWindowText ("");
	else
	{
		if (!(strNumber == pSet -> m_Nummer))
		{
			CWaitCursor wc;
			CString strFilter;
			AfxFormatString1 (strFilter, IDS_FIND_NUMMER, strNumber);
			pSet -> FindFirst (strFilter);
		}
	
		m_stGemeinde.SetWindowText (pSet -> m_Name);
	}
}
