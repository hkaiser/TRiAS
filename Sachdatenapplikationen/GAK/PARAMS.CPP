// params.cpp : implementation file
//

#include "stdafx.h"			//	prec. Header
#include "res.h"			//	Resourcen
#include <tableset.hpp>		//	CTables     
#include "editext.h"		//	CEditExt
#include "numedit.h"		//	CRealEdit
#include "columnst.h"		// 	CColumns
#include "getodbci.hpp"		//	ODBC-Infos
#include "SelTable.h"		//	CSelTable
#include "params.h"			//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//	Strukturen der Tabellen
FieldInfo BgsTable [] = {
	{ "Erzeugernummer",				SQL_VARCHAR, 	sMinErzNrLen },
	{ "Nachweisnummer",				SQL_VARCHAR, 	-1 },
	{ "Abfallschluesselnummer",		SQL_VARCHAR, 	-1 },
	{ "Befoerderernummer",			SQL_VARCHAR, 	-1 },
	{ "Entsorgernummer",			SQL_VARCHAR, 	-1 },
	{ "Menge",						SQL_DOUBLE, 	-1 },	
	{ "Menge_en",					SQL_DOUBLE, 	-1 },	
	{ "Entsorgungsverfahren",		SQL_VARCHAR, 	-1 },	
	{ NULL,			0, 				-1 },
};    
pFieldInfo pBgsTable = BgsTable;

FieldInfo ErzeugerTable [] = {                     
	{ "Nummer",			SQL_VARCHAR, 	sMinErzNrLen },
	{ "Anfallstelle",	SQL_VARCHAR,	-1 },
	{ "Branchennummer",	SQL_VARCHAR,	-1 },
	{ "Ortsname",		SQL_VARCHAR,	-1 },
	{ "Ansprechpartner",SQL_VARCHAR,	-1 },
	{ "Partnertelefon",	SQL_VARCHAR,	-1 },
	{ "Partnertelefax",	SQL_VARCHAR,	-1 },
	{ NULL,				0, 				-1 },
};
pFieldInfo pErzeugerTable = ErzeugerTable;

FieldInfo BilanzTable [] = {                      
	{ "Nummer",				SQL_VARCHAR, 	sMinErzNrLen },
	{ "Abfallnummer",		SQL_VARCHAR,	-1 },
	{ "Menge_t",			SQL_DOUBLE, 	-1 },		
	{ "Transporteurnummer",	SQL_VARCHAR,	-1 },
	{ "Entsorgernummer",	SQL_VARCHAR,	-1 },
	{ "Entsorgungsverfahren", SQL_VARCHAR,	-1 },
	{ "Nachweisnummer",		SQL_VARCHAR,	-1 },	
	{ NULL,			0, 					-1 },
};
pFieldInfo pBilanzTable = BilanzTable;

FieldInfo ErzListeTable [] = {
	{ "Nummer",				SQL_VARCHAR, 	sMinErzNrLen },
	{ "Anfallstelle",		SQL_VARCHAR,	-1 },
	{ "Ortsname",			SQL_VARCHAR,	-1 },
	{ "Ansprechpartner",	SQL_VARCHAR,	-1 },
	{ "Partnertelefon",		SQL_VARCHAR,	-1 },
	{ "Partnertelefax",		SQL_VARCHAR,	-1 },
	{ "Abfallnummer",		SQL_VARCHAR,	-1 },
	{ "Menge",				SQL_DOUBLE,		-1 },
	{ "Transporteurnummer",	SQL_VARCHAR,	-1 },
	{ "Entsorgernummer",	SQL_VARCHAR,	-1 },
	{ "Sonderabfall",		SQL_BIT, 		-1 },	
	{ "Bilanzdaten",		SQL_BIT, 		-1 },
	{ "Bearbeitet",			SQL_BIT, 		-1 },	
	{ "Nachweisnummer",		SQL_VARCHAR,	-1 },
	{ "Branchennummer",		SQL_VARCHAR,	-1 },
	{ "Prioritaet",			SQL_VARCHAR,	-1 },
	{ "Verfahren",			SQL_VARCHAR,	-1 },
	{ NULL,			0, 					-1 },
};                                    
pFieldInfo pErzListeTable = ErzListeTable;

FieldInfo AbfArtenTable [] = {            
	{ "Nummer",			SQL_VARCHAR, 	-1 },
	{ "Sonderabfall",	SQL_BIT, 		-1 },		
	{ "Dichte",			SQL_REAL, 		-1 },	
	{ NULL,				0, 				-1 },	
};	        
pFieldInfo pAbfArtenTable = AbfArtenTable;

//	globale Funktion
//	prüfe diese Tabelle                               
BOOL TableOK (CDatabase *pDatabase, const CString &strTable, FieldInfo *pInfo, UINT uiErrorString, 
			  BOOL bOutputError)
{   
//	Parameter prüfen	
	ASSERT (NULL != pDatabase);
	ASSERT (pDatabase -> IsOpen ());
	ASSERT (!strTable.IsEmpty ());
	ASSERT (uiErrorString > 0);
	ASSERT (NULL != pInfo);
	BOOL bRet = FALSE;

	TRY
	{        
		CWaitCursor wc;
		CString strError, strActField;

	//	zähle Anzahl Felder
		short sCnt = 0;
		for (FieldInfo *pInf = pInfo; pInf && pInf -> pFieldName && *pInf -> pFieldName; pInf++)
			sCnt++;
		ASSERT (sCnt > 0);
		
	//	Set öffnen
		CColumns Set (pDatabase);                   
		Set.m_strTableNameParam = strTable;		
		Set.Open ();
		
	//	für alle Felder
		short sFound = 0;
		while (! Set.IsEOF ())
		{   
            for (FieldInfo *pI = pInfo; pI && pI -> pFieldName && *pI -> pFieldName; pI++) 
			{
			//	suche akt. Feld in FeldInfo
				if ((0 == strcmpi (pI -> pFieldName, Set.m_strColumnName)) && (pI -> sType == Set.m_nDataType))
				{
				//	ggf. auch Länge vergleichen
					if (pI -> sLen > 0)   
					{
						if (Set.m_lLength >= pI -> sLen)
						{
							sFound++;
							break;
						}
					}						
					else
					{
						sFound++;
						break;
					}
				}
			}					
			Set.MoveNext ();				// zum nächsten Feld
		}	

	//	Result bilden
		bRet = sCnt == sFound;

	//	ggf. Fehler ausgeben
		if (!bRet && bOutputError)
		{
			AfxFormatString1 (strError, uiErrorString, strTable);
			OutputError (strError);
		}					
	}
	CATCH (CMemoryException, me)
	{               
		OutputMemoryError ();
	}                        
	AND_CATCH (CFileException, fe)
	{
		OutputFileError (fe -> m_cause);
	}                      
	AND_CATCH (CDBException, de)
	{
		OutputError (de -> m_strError);		
	}
	END_CATCH	
	
	return bRet;
}

/////////////////////////////////////////////////////////////////////////////
// CParameters dialog
CParameters::CParameters(CWnd* pParent /*=NULL*/)
	: CDialog(CParameters::IDD, pParent)
{
	//{{AFX_DATA_INIT(CParameters)
	m_strLastErzeuger = "";
	m_iPrioritaet = 0;
	m_iModus = 0;
	//}}AFX_DATA_INIT
	m_strLastAsn = "";
	m_dMenge = 0.0;				//lBilanzMenge;
	m_dMengeRec = 0.0;
	m_bOnlySonderAbfall = FALSE;
	m_pFoxProDB = NULL;
	m_pMdbDB = NULL;
	m_bAbfallAppend = FALSE;
	m_bErzListeAppend = FALSE;
	m_bOnlyThisErzeuger = FALSE;
	m_bLockErzeugerSelection = FALSE;
	m_bLockAbfaelleSelection = FALSE;
}

void CParameters::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CParameters)
	DDX_Control(pDX, IDE_ASN, m_edLastAsn);
	DDX_Control(pDX, IDB_OUTPUT_DB, m_btOutputTable);
	DDX_Control(pDX, IDB_ERZ_NR, m_btErzeuger);
	DDX_Control(pDX, IDC_VJABFALL_TABLE, m_cbAbfallTableVJ);
	DDX_Control(pDX, IDC_ERZEUGER_TABLE, m_cbErzeugerTable);
	DDX_Control(pDX, IDC_BGS_TABLE, m_cbBgsTable);
	DDX_Control(pDX, IDC_ABFALL_TABLE, m_cbAbfallTable);
	DDX_Control(pDX, IDE_MENGE_REC, m_edMengeRec);
	DDX_Control(pDX, IDE_MENGE2, m_edMenge);
	DDX_Control(pDX, IDE_ERZ_NUMMER, m_edLastErzeuger);
	DDX_Control(pDX, IDB_CREATE_ERZLISTE, m_btErzeugerListe);
	DDX_Control(pDX, IDT_ERZLISTE, m_stErzListe);
	DDX_Control(pDX, IDB_SONDERABFALL, m_btSonderAbfall);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDE_OUTPUT_DB, m_edOutputDB);
	DDX_Radio(pDX, IDB_RD1, m_iPrioritaet);
	DDX_Radio(pDX, IDB_ABGLEICH, m_iModus);
	//}}AFX_DATA_MAP
	//DDX_Text(pDX, IDE_ERZ_NUMMER, m_strLastErzeuger);
}

BEGIN_MESSAGE_MAP(CParameters, CDialog)
	//{{AFX_MSG_MAP(CParameters)
	ON_BN_CLICKED(IDB_OUTPUT_DB, OnOutputDb)
	ON_EN_CHANGE(IDE_MENGE2, OnChangeMenge)
	ON_CBN_SELCHANGE(IDC_ABFALL_TABLE, OnSelchangeAbfallTable)
	ON_CBN_SELCHANGE(IDC_BGS_TABLE, OnSelchangeBgsTable)
	ON_CBN_SELCHANGE(IDC_ERZEUGER_TABLE, OnSelchangeErzeugerTable)
	ON_BN_CLICKED(IDB_SONDERABFALL, OnSonderabfall)
	ON_BN_CLICKED(IDB_CREATE_ERZLISTE, OnCreateErzliste)
	ON_COMMAND(IDM_CUT, OnCut)
	ON_COMMAND(IDM_COPY, OnCopy)
	ON_COMMAND(IDM_INSERT, OnInsert)
	ON_COMMAND(IDM_DELETE, OnDelete)
	ON_COMMAND(IDM_SELECT, OnSelect)	
	ON_COMMAND(IDM_BACK, OnBack)
	ON_BN_CLICKED(ID_HELP, OnHelp)  
	ON_EN_CHANGE(IDE_MENGE_REC, OnChangeMengeRec)
	ON_CBN_SELCHANGE(IDC_VJABFALL_TABLE, OnSelchangeVjabfallTable)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDB_ABGLEICH, OnAbgleich)
	ON_BN_CLICKED(IDB_KONTROLLE, OnKontrolle)
	ON_BN_CLICKED(IDB_ERZ_NR, OnLastErzNrText)
	ON_EN_CHANGE(IDE_ERZ_NUMMER, OnChangeErzNummer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CParameters::OnInitDialog()
{
	CDialog::OnInitDialog();
	
//	prüfe Parameter
	ASSERT (NULL != m_pFoxProDB);
	ASSERT (NULL != m_pMdbDB);
	ASSERT (m_pFoxProDB -> IsOpen ());
	ASSERT (m_pMdbDB -> IsOpen ());
	
//	ComboBoxen füllen           
	CWaitCursor wc;
	CTables Tables (m_pFoxProDB);
	Tables.Open ();
	m_cbErzeugerTable.ResetContent ();
	m_cbAbfallTableVJ.ResetContent ();
	m_cbAbfallTable.ResetContent ();
	while (!Tables.IsEOF ())            
	{
		if ((m_cbErzeugerTable.AddString (Tables.m_strName) < 0) || 
			(m_cbAbfallTableVJ.AddString (Tables.m_strName) < 0) ||
			(m_cbAbfallTable.AddString (Tables.m_strName) < 0))
			AfxThrowMemoryException ();
		Tables.MoveNext ();			
	}                     
	if (Tables.IsOpen ())
		Tables.Close ();
	m_cbErzeugerTable.EnableWindow (m_cbErzeugerTable.GetCount () > 0);
	m_cbAbfallTable.EnableWindow (m_cbAbfallTable.GetCount () > 0);
	m_cbAbfallTableVJ.EnableWindow (m_cbAbfallTableVJ.GetCount () > 0);

	CTables MTables (m_pMdbDB);         
	MTables.Open ();
	m_cbBgsTable.ResetContent ();
	while (!MTables.IsEOF ())
	{
		if (m_cbBgsTable.AddString (MTables.m_strName) < 0)
			AfxThrowMemoryException ();
		MTables.MoveNext ();			
	}                     
	if (MTables.IsOpen ())
		MTables.Close ();		
	m_cbBgsTable.EnableWindow (m_cbBgsTable.GetCount () > 0);
		
//	prüfe evtl. übergebene Erzeugertabelle
	int iSel = -1;
	if (!m_strErzeugerTable.IsEmpty () && 
		TableOK (m_pFoxProDB, m_strErzeugerTable, ErzeugerTable, IDS_ERZ_TABLE_ERROR, FALSE) &&
	    ((iSel = m_cbErzeugerTable.FindStringExact (-1, m_strErzeugerTable)) >= 0))
		m_cbErzeugerTable.SetCurSel (iSel);	
	else
		m_strErzeugerTable.Empty ();		
		
//	prüfe evtl. übergebene Bilanztabelle
	if (!m_strAbfallTable.IsEmpty () && 
		TableOK (m_pFoxProDB, m_strAbfallTable, BilanzTable, IDS_BILANZ_TABLE_ERROR, FALSE) &&
	    ((iSel = m_cbAbfallTable.FindStringExact (-1, m_strAbfallTable)) >= 0))
		m_cbAbfallTable.SetCurSel (iSel);	
	else                            
		m_strAbfallTable.Empty ();					

//	prüfe evtl. übergebene Bilanztabelle (Vorjahr)
	if (!m_strAbfallTableVJ.IsEmpty () && 
		TableOK (m_pFoxProDB, m_strAbfallTableVJ, BilanzTable, IDS_BILANZ_TABLE_ERROR, FALSE) &&
	    ((iSel = m_cbAbfallTableVJ.FindStringExact (-1, m_strAbfallTableVJ)) >= 0))
		m_cbAbfallTableVJ.SetCurSel (iSel);	
	else                            
		m_strAbfallTableVJ.Empty ();
	
//	prüfe evtl. übergebene BGS-Tabelle
	if (!m_strBGSTable.IsEmpty () && 
		TableOK (m_pMdbDB, m_strBGSTable, BgsTable, IDS_BGS_TABLE_ERROR, FALSE) &&
	    ((iSel = m_cbBgsTable.FindStringExact (-1, m_strBGSTable)) >= 0))
		m_cbBgsTable.SetCurSel (iSel);	
	else                            
		m_strBGSTable.Empty ();							
		
//	prüfe evtl. übergebene Ausgabe-Tabelle
	if (!m_strOutputTable.IsEmpty () && 
		 TableOK (m_pFoxProDB, m_strOutputTable, BilanzTable, IDS_BILANZ_TABLE_ERROR, FALSE))
		m_edOutputDB.SetWindowText (m_strOutputTable);		
	else
	{                            
		m_strOutputTable.Empty ();							
		m_bAbfallAppend = FALSE;		
	}		                        
	
//	prüfe evtl. übergebene Erzeugerliste
	if (!m_strErzListe.IsEmpty () && 
		TableOK (m_pFoxProDB, m_strErzListe, ErzListeTable, IDS_ERZLISTE_TABLE_ERROR, FALSE))
	{		
		m_stErzListe.SetWindowText (m_strErzListe);	
		m_btErzeugerListe.SetCheck (1);		
	}		
	else
	{
		m_strErzListe.Empty ();
		m_bErzListeAppend = FALSE;	
	}

//	Mengen ausgeben
	CString strMenge;
	strMenge.Format (szMengenFormat, (double) max (m_dMengeRec, 0.0));
	m_edMengeRec.SetWindowText (strMenge);
	strMenge.Format (szMengenFormat, (double) max (m_dMenge, 0.0));
	m_edMenge.SetWindowText (strMenge);

//	Sonderabfall
	m_btSonderAbfall.SetCheck (m_bOnlySonderAbfall); 

//	letzten Erzeuger ausgeben
	if (!m_strLastErzeuger.IsEmpty ())	
	{
		m_strLastErzeuger = m_strLastErzeuger.Left (min(m_strLastErzeuger.GetLength(),sMaxErzNrLen));
		m_edLastErzeuger.SetWindowText (m_strLastErzeuger);
	}

//	letzte ASN ausgeben
	if (!m_strLastAsn.IsEmpty ())
	{
		m_strLastAsn = m_strLastAsn.Left (min(m_strLastAsn.GetLength(),sMaxAsnNrLen));
		m_edLastAsn.SetWindowText (m_strLastAsn);
	}

//	Felder begrenzen: ErzNr, ASN
	m_edLastAsn.LimitText (sMaxAsnNrLen);
	m_edLastErzeuger.LimitText (sMaxErzNrLen);

//	Button setzen und zugeh. Text für letzte Gruppe ausgeben
	m_btErzeuger.SetCheck (m_bOnlyThisErzeuger && !m_strLastErzeuger.IsEmpty ());
	m_btErzeuger.EnableWindow (!m_strLastErzeuger.IsEmpty ());

	OnLastErzNrText ();
	
//	Modi ausgeben
	if (m_iModus < 0 || m_iModus > 1)
		m_iModus = 0;

//	Priorität ausgeben
	if (m_iPrioritaet < 0 || m_iPrioritaet > 2)
		m_iPrioritaet = 0;

//	Werte der Variablen übernehmen
	UpdateData (FALSE);

//  JG Extrawünsche bei der Auswahl der Tabellen
	if (m_bLockErzeugerSelection)
		m_cbErzeugerTable.EnableWindow(false);
	if (m_bLockAbfaelleSelection)
		m_cbAbfallTable.EnableWindow(false);


//	Controlstate setzen
	SetControlState ();

//	Ok-Button setzen
	SetOkButton ();	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}                  

void CParameters::SetControlState (void)
{
//	Controls aktivieren in Abhängigkeit vom Modus
	BOOL bEnable = 0 == m_iModus;		//	Abgleich
	m_cbAbfallTableVJ.EnableWindow (bEnable);
	m_edMengeRec.EnableWindow (bEnable);
	m_edMenge.EnableWindow (bEnable);
	m_btSonderAbfall.EnableWindow (bEnable);
	m_btErzeugerListe.EnableWindow (bEnable);
	GetDlgItem (IDB_RD1) -> EnableWindow (bEnable);
	GetDlgItem (IDB_RD2) -> EnableWindow (bEnable);
	GetDlgItem (IDB_RD3) -> EnableWindow (bEnable);
}

void CParameters::SetOkButton (void)
{
//	lese Modus
	UpdateData (TRUE);		
	BOOL bAbgleich = (0 == m_iModus);

//	diese Tabellen werden immer benötigt
	BOOL bEnable = !m_strAbfallTable.IsEmpty () && !m_strErzeugerTable.IsEmpty () &&
				   !m_strBGSTable.IsEmpty () && !m_strOutputTable.IsEmpty ();	

//	beim Abgleich kommt noch Vorjahres-Tabelle hinzu
	if (bEnable && bAbgleich)
		bEnable = !m_strAbfallTableVJ.IsEmpty ();

//	alle Tabellen-Namen müssen verschieden sein
	if (bEnable)
//	prüfe zuerst die notwendigen Tabellen: BGS-Tabelle ist in einer anderen Datenquelle
	{
		bEnable = (m_strAbfallTable != m_strErzeugerTable) &&
				  (m_strAbfallTable != m_strOutputTable) &&
				  (m_strErzeugerTable != m_strOutputTable);
				  
	//	beim Abgleich müssen noch die Vorjahres-Tabelle und ggf. die Erzeugerliste geprüft werden
		if (bAbgleich)
		{
			if (bEnable)
			{
				bEnable = (m_strAbfallTableVJ != m_strErzeugerTable) &&
						  (m_strAbfallTableVJ != m_strOutputTable) &&
						  (m_strAbfallTableVJ != m_strAbfallTable);
				
			//	prüfe jetzt ggf. die Erzeugerliste
				if (bEnable && !m_strErzListe.IsEmpty ())
				{
					bEnable = (m_strErzListe != m_strErzeugerTable) &&
							  (m_strErzListe != m_strOutputTable) &&
							  (m_strErzListe != m_strAbfallTableVJ) &&
							  (m_strErzListe != m_strAbfallTable);
				}
			}
		}
	}

//	Button setzen
	m_btOK.EnableWindow (bEnable);			
}

/////////////////////////////////////////////////////////////////////////////
// CParameters message handlers
void CParameters::OnChangeMenge()
{
	// TODO: Add your control notification handler code here
	CString strText;
	m_edMenge.GetWindowText (strText);
	m_dMenge = atof (strText);		
	
	if ((m_dMenge >= 0) && (m_dMenge >= m_dMengeRec))
		SetOkButton ();
	else
		m_btOK.EnableWindow (FALSE);
}

void CParameters::OnChangeMengeRec() 
{
	// TODO: Add your control notification handler code here
	CString strText;
	m_edMengeRec.GetWindowText (strText);
	m_dMengeRec = atof (strText);				

	if ((m_dMengeRec >= 0) && (m_dMengeRec <= m_dMenge))
		SetOkButton ();
	else
		m_btOK.EnableWindow (FALSE);
}

//	Ausgabetabelle festlegen                                                            
void CParameters::OnOutputDb()
{
	// TODO: Add your control notification handler code here
	CString strCaption;
	VERIFY (strCaption.LoadString (IDS_SELECT_OUTPUT_TABLE));
	OpenDBFTable (m_strOutputTable, m_bAbfallAppend, strCaption);

//	prüfe Tabelle	
	if (m_bAbfallAppend && !TableOK (m_pFoxProDB, m_strOutputTable, BilanzTable, IDS_BILANZ_TABLE_ERROR))
		m_strOutputTable.Empty ();						
	
	m_edOutputDB.SetWindowText (m_strOutputTable); 				
	SetOkButton ();	
}

void CParameters::OnSelchangeAbfallTable()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbAbfallTable.GetCurSel ();
	if (iSel >= 0)                                          
	{
		m_cbAbfallTable.GetLBText (iSel, m_strAbfallTable);	
	
	//	prüfe die Art der Tabelle
		if (! TableOK (m_pFoxProDB, m_strAbfallTable, BilanzTable, IDS_BILANZ_TABLE_ERROR))
		{
			m_strAbfallTable.Empty ();					
			m_cbAbfallTable.SetCurSel (-1);
		}			
	}		
	else
		m_strAbfallTable.Empty ();
	SetOkButton ();	
}

void CParameters::OnSelchangeVjabfallTable() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbAbfallTableVJ.GetCurSel ();
	if (iSel >= 0)                                          
	{
		m_cbAbfallTableVJ.GetLBText (iSel, m_strAbfallTableVJ);	
	
	//	prüfe die Art der Tabelle
		if (! TableOK (m_pFoxProDB, m_strAbfallTableVJ, BilanzTable, IDS_BILANZ_TABLE_ERROR))
		{
			m_strAbfallTableVJ.Empty ();					
			m_cbAbfallTableVJ.SetCurSel (-1);
		}			
	}		
	else
		m_strAbfallTableVJ.Empty ();
	SetOkButton ();	
}

void CParameters::OnSelchangeBgsTable()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbBgsTable.GetCurSel ();
	if (iSel >= 0)                                      
	{	
		m_cbBgsTable.GetLBText (iSel, m_strBGSTable);	
		
	//	prüfe die Art der Tabelle
		if (! TableOK (m_pMdbDB, m_strBGSTable, BgsTable, IDS_BGS_TABLE_ERROR))
		{
			m_strBGSTable.Empty ();		
			m_cbBgsTable.SetCurSel (-1);
		}	
	}		
	else
		m_strBGSTable.Empty ();
	SetOkButton ();	
}

void CParameters::OnSelchangeErzeugerTable()
{
	// TODO: Add your control notification handler code here
	int iSel = m_cbErzeugerTable.GetCurSel ();
	if (iSel >= 0)                                              
	{
		m_cbErzeugerTable.GetLBText (iSel, m_strErzeugerTable);	
		
	//	prüfe die Art der Tabelle
		if (! TableOK (m_pFoxProDB, m_strErzeugerTable, ErzeugerTable, IDS_ERZ_TABLE_ERROR))
		{
			m_strErzeugerTable.Empty ();		
			m_cbErzeugerTable.SetCurSel (-1);
		}			
	}		
	else
		m_strErzeugerTable.Empty ();
	SetOkButton ();		
}

void CParameters::OnSonderabfall()
{
	// TODO: Add your control notification handler code here
	m_bOnlySonderAbfall	= m_btSonderAbfall.GetCheck (); 
}

void CParameters::OnCreateErzliste()
{
	// TODO: Add your control notification handler code here
	if (0 == m_btErzeugerListe.GetCheck ())
	{
		m_strErzListe.Empty ();	
		m_bErzListeAppend = FALSE;
	}		
	else
	{
		CString strCaption;
		VERIFY (strCaption.LoadString (IDS_ERZLISTE_SEL));
		OpenDBFTable (m_strErzListe, m_bErzListeAppend, strCaption);
		if (m_bErzListeAppend && !TableOK (m_pFoxProDB, m_strErzListe, ErzListeTable, IDS_ERZLISTE_TABLE_ERROR))
			m_strErzListe.Empty ();							
	}		
	               
	m_stErzListe.SetWindowText (m_strErzListe);               
	m_btErzeugerListe.SetCheck (m_strErzListe.IsEmpty () ? FALSE : TRUE);
	SetOkButton ();	 
}
                  
//	FoxPro-Tabelle öffnen                  
void CParameters::OpenDBFTable (CString &strTableName, BOOL &bAppend, CString strCaption)
{
/*
	CString strExt, strFilter, strDataPath, strDateiFilter;
	VERIFY (strExt.LoadString (IDS_DBF_EXTENSION));
	VERIFY (strFilter.LoadString (IDS_FOXPRO_FILTER));	
	VERIFY (GetDataPath (strDataPath));
	VERIFY (strDateiFilter.LoadString (IDS_DBF_FILTER));
	CFileDialog Dlg (FALSE, strExt, strDateiFilter, OFN_HIDEREADONLY,
					 strFilter, this);              
	Dlg.m_ofn.lpstrInitialDir = strDataPath;
	if (IDOK == Dlg.DoModal ())
	{       
	//	lese Tabellennamen
		CString strTable = Dlg.GetFileName ();	
		char FileName [_MAX_FNAME] = "";
		_splitpath (strTable, NULL, NULL, FileName, NULL);
		strTableName = FileName;
	
	//	wenn Tabelle existiert		                
		CString strFullFileName (Dlg.GetPathName ());
		OFSTRUCT of;
		bAppend = FALSE;										
		if (OpenFile (strFullFileName, &of, OF_EXIST) > 0)
		{      
		//	Tabelle löschen ?                                 
			CString strTemp;
			AfxFormatString1 (strTemp, IDS_TABLE_EXIST, strTableName);
			if (IDYES == MessageBox (strTemp, AfxGetAppName (), MB_ICONQUESTION | MB_YESNO))
			{
			//	Tabelle durch ODBC löschen
				AfxFormatString1 (strTemp, IDS_DELETE_TABLE, strTableName);
				ExecuteSQL (strTemp);
			}   
			else
				bAppend = TRUE;
		}                   
	}	
*/
	try
	{
	//	prüfe Parameter
		ASSERT (NULL != m_pFoxProDB);
		ASSERT (m_pFoxProDB -> IsOpen ());
		ASSERT (!strCaption.IsEmpty ());

	//	Auswahl-Dialog öffnen
		CSelTable SelDlg (this);
		SelDlg.m_strCaption = strCaption;
		SelDlg.m_bEnterNew = TRUE;
		SelDlg.m_pDataBase = m_pFoxProDB;
		if (IDOK == SelDlg.DoModal ())
		{
			strTableName = SelDlg.m_strTableName; 

		//	Append-Flag setzen
			bAppend = FALSE;										

		//	wenn Tabelle existiert 
			if (SelDlg.m_bTableExists)
			{
			//	Tabelle löschen ?                                 
				CString strTemp;
				AfxFormatString1 (strTemp, IDS_TABLE_EXIST, strTableName);
				if (IDYES == MessageBox (strTemp, AfxGetAppName (), MB_ICONQUESTION | MB_YESNO))
				{
				//	Tabelle durch ODBC löschen
					AfxFormatString1 (strTemp, IDS_DELETE_TABLE, strTableName);
					m_pFoxProDB -> ExecuteSQL (strTemp);
				}
				else
					bAppend = TRUE;
			}
		}			
	}
	catch (CException *e)
	{               
		e -> ReportError ();
		e -> Delete ();
	}	
}		

//	SQL-Anweisung ausführen
/*
BOOL CParameters::ExecuteSQL (const char *pSQL)
{                          
	ASSERT (NULL != pSQL && AfxIsValidString (pSQL));
	ASSERT (NULL != m_pFoxProDB && m_pFoxProDB -> IsOpen ());
	
	HSTMT hstmt = NULL;
	RETCODE nRetCode;                                   
	
	TRY
	{  
		AFX_SQL_ASYNC (m_pFoxProDB, :: SQLAllocStmt (m_pFoxProDB -> m_hdbc, &hstmt));
		if (nRetCode != SQL_SUCCESS)
			AfxThrowMemoryException ();
			
		AFX_SQL_ASYNC (m_pFoxProDB, :: SQLExecDirect (hstmt, (UCHAR FAR*)pSQL, SQL_NTS));
		if (SQL_ERROR == nRetCode)
			AfxThrowDBException (nRetCode, m_pFoxProDB, hstmt); 														 	    			
	}
	CATCH_ALL(e)
	{               
	//	SQL-Statement freigeben		                                       
		if (NULL != hstmt);
		{
			AFX_SQL_ASYNC (m_pFoxProDB, :: SQLFreeStmt (hstmt, SQL_DROP));			                                               
			hstmt = NULL;			
		}			
		THROW_LAST ();		
	}
	END_CATCH_ALL
                   
//	SQL-Statement freigeben		                                       
	if (NULL != hstmt);
		AFX_SQL_ASYNC (m_pFoxProDB, :: SQLFreeStmt (hstmt, SQL_DROP));			                                               
	
	return TRUE;
}
*/

void CParameters::OnCut()
{
	// TODO: Add your command handler code here
	HasFocus () -> Cut ();	
}
                               
void CParameters::OnBack()
{
	// TODO: Add your command handler code here
	if (HasFocus () -> CanUndo ())
		HasFocus () -> Undo ();
}

void CParameters::OnCopy()
{
	// TODO: Add your command handler code here
	HasFocus () -> Copy ();			
}

void CParameters::OnDelete()
{
	// TODO: Add your command handler code here
	HasFocus () -> Clear ();		
}

void CParameters::OnInsert()
{
	// TODO: Add your command handler code here
	HasFocus () -> Paste ();	
}

void CParameters::OnSelect()
{
	// TODO: Add your command handler code here
	HasFocus () -> SetSel (0, -1);
}
     
void CParameters::OnHelp()
{
	// TODO: Add your control notification handler code here
	AfxGetApp () -> WinHelp (IDD);		//	Hilfe zum Dialog		
}

/*
BOOL CParameters::OnHelpInfo(HELPINFO* pHelpInfo) 
{
	// TODO: Add your message handler code here and/or call default
	ASSERT (pHelpInfo != NULL);
	if (pHelpInfo -> dwContextId)
		AfxGetApp () -> WinHelp (pHelpInfo -> dwContextId, HELP_CONTEXTPOPUP);

	return TRUE;
}
*/

void CParameters::OnOK()
{
	UpdateData (TRUE);	//	Daten speichern

//	lese restlichen Parameter
	m_edLastErzeuger.GetWindowText (m_strLastErzeuger);
	m_edLastAsn.GetWindowText (m_strLastAsn);
	m_bOnlyThisErzeuger = m_btErzeuger.GetCheck ();

//	in Abhängigkeit vom Modus Variablen verändern
	if (0 == m_iModus)
	{
		CString strTemp;
		m_edMenge.GetWindowText (strTemp);
		m_dMenge = atof (strTemp);
		m_edMengeRec.GetWindowText (strTemp);
		m_dMengeRec = atof (strTemp);
		m_bOnlySonderAbfall = m_btSonderAbfall.GetCheck ();
	}
	else
	{
		m_dMenge = m_dMengeRec = 0.0;
		m_bOnlySonderAbfall = FALSE;
		m_strErzListe.Empty ();
		m_iPrioritaet = 0;
		m_strAbfallTableVJ.Empty ();
	}			

	CDialog::OnOK();
}

void CParameters::OnAbgleich() 
{
	// TODO: Add your control notification handler code here
	UpdateData (TRUE);
	SetControlState ();
	SetOkButton ();
}

void CParameters::OnKontrolle() 
{
	// TODO: Add your control notification handler code here
	UpdateData (TRUE);
	SetControlState ();
	SetOkButton ();
}

void CParameters::OnLastErzNrText() 
{
	// TODO: Add your control notification handler code here
	CString strTemp;
	m_bOnlyThisErzeuger = m_btErzeuger.GetCheck (); 
	VERIFY (strTemp.LoadString (m_bOnlyThisErzeuger ? IDS_START_TEXT2 : IDS_START_TEXT1));
	m_btErzeuger.SetWindowText (strTemp); 	
}

void CParameters::OnChangeErzNummer() 
{
	// TODO: Add your control notification handler code here
	m_btErzeuger.EnableWindow (m_edLastErzeuger.LineLength () > 0);
}
