// AbfPage.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp
#include "gaksete.h"		// CDaoRecordsetExt
#include "abfset.h"			// CAbfSet
#include "selset.h"			// CSelectSet
#include "abfArset.h"		// CAbfArtSet
#include "selnum.h"			// CSeletcNumberDlg
#include "numedit.h"		// CErzNrEdit	
#include "AbfPage.h"		// zugeh. Header
#include "BranPage.h"		// CBranchPage
#include "TransPge.h"		// CTranspPage
#include "EntPage.h"		// CEntsorgerPage
#include "betrpage.h"		// CBetreiberPage	

#include "abfsheet.h"		// CAbfSheet

#include "gakSet.h"			// CGakSet
extern CGakSet * g_pErzSet;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	enums
enum MengenTyp { MengenInit = 0, MengenTonnen = 1, MengenMeter = 2 };

//	Konstanten
const char FloatFormat [] = "%.3lf";	//	Dichten- und Mengen-Format
const char Vorbehandlung [] = "x";		//	Flag für Vorbehandlung		
const char NotVorbehandlung [] = " ";

// erterne Variablen
extern CAbfSet *g_pAbfSet;

//	globale Funktionen (ohne TRY/CATCH)
void CALLBACK SetAbfallArt (LPARAM lParam)
{
	ASSERT (NULL != g_pAbfSet);
	g_pAbfSet -> m_Abfallnummer = (const char *) lParam;
}

/////////////////////////////////////////////////////////////////////////////
// CAbfPage property page
IMPLEMENT_DYNCREATE(CAbfPage, CPropertyPage)

CAbfPage::CAbfPage() : CPropertyPage(CAbfPage::IDD)
{
	//{{AFX_DATA_INIT(CAbfPage)
	//}}AFX_DATA_INIT
	m_bOutputArten = TRUE;		// Abfallarten Ausgeben
	m_bAction = TRUE;			// Abfallart neu/ändern
	m_pSet = NULL;
	m_pDlg = NULL;
	m_dDichte = 0.0;			// Dichte


}

CAbfPage::~CAbfPage()
{
	DELETE_OBJ (m_pSet);
	DELETE_OBJ (m_pDlg);
}

void CAbfPage::DoDataExchange(CDataExchange* pDX)
{
		// allg. tests
		ASSERT (g_pAbfSet != NULL);
//	KK990714
		if (!g_pAbfSet)
			return;

		// wenn der Datensatz gültig ist
		if (g_pAbfSet->IsValid())
		{
			DDX_FieldText (pDX, IDE_COMMENT, g_pAbfSet -> m_Bemerkungen, g_pAbfSet);
			DDX_FieldText (pDX, IDE_MENGET, g_pAbfSet -> m_Menge_t, g_pAbfSet);
			DDX_FieldText (pDX, IDE_INTERNE_BEZ, g_pAbfSet -> m_Abfallbezeichnung, g_pAbfSet);
			DDX_FieldText (pDX, IDE_VERBRINGUNG, g_pAbfSet -> m_Verbringungscode, g_pAbfSet);
			DDX_FieldText (pDX, IDE_EAK_NR, g_pAbfSet -> m_EAKNummer, g_pAbfSet);
			DDX_FieldText (pDX, IDE_NACHWEIS_NR, g_pAbfSet -> m_Nachweisnummer, g_pAbfSet);
			DDX_FieldText (pDX, IDE_VERFAHREN, g_pAbfSet -> m_Entsorgungsverfahren, g_pAbfSet);
		}
		else
		{
			// alle Felder leeren
			CString strDummy;
			DDX_Text (pDX, IDE_COMMENT, strDummy);
			DDX_Text (pDX, IDE_MENGET, strDummy);
			DDX_Text (pDX, IDE_INTERNE_BEZ, strDummy);
			DDX_Text (pDX, IDE_VERBRINGUNG, strDummy);
			DDX_Text (pDX, IDE_EAK_NR, strDummy);
			DDX_Text (pDX, IDE_NACHWEIS_NR, strDummy);
			DDX_Text (pDX, IDE_VERFAHREN, strDummy);
//	KK990713
			DDX_Text (pDX, IDS_ARTEN_INFO, strDummy);
			DDX_Text (pDX, IDE_ABFART, strDummy);
			DDX_Text (pDX, IDE_DICHTE, strDummy);

		}

		CPropertyPage::DoDataExchange(pDX);
		//{{AFX_DATA_MAP(CAbfPage)
		DDX_Control(pDX, IDE_VERFAHREN, m_edVerfahren);
		DDX_Control(pDX, IDE_EAK_NR, m_edEAKNummer);
		DDX_Control(pDX, IDE_VERBRINGUNG, m_edVerbringung);
		DDX_Control(pDX, IDB_CHANGE, m_btChange);
		DDX_Control(pDX, IDB_VORBEHANDLUNG, m_btVorbehandlung);
		DDX_Control(pDX, IDS_ARTEN_INFO, m_stArtenInfo);
		DDX_Control(pDX, IDE_MENGET, m_edMengeT);
		DDX_Control(pDX, IDS_SONDER_ABFALL, m_stSonderAbfall);
		DDX_Control(pDX, IDE_DICHTE, m_edDichte);
		DDX_Control(pDX, IDE_ABFART, m_edAbfArt);
		DDX_Control(pDX, IDE_MENGEM, m_edMengeM);
		DDX_Control(pDX, IDL_ABFALLART, m_lbAbfallArt);
		//}}AFX_DATA_MAP

		if (g_pAbfSet->IsValid())
		{
			if (pDX -> m_bSaveAndValidate)	// Daten schreiben
					g_pAbfSet -> m_Vorbehandlung = 1 == m_btVorbehandlung.GetCheck () ? Vorbehandlung : NotVorbehandlung;
			else							// Daten lesen
			{
				if (/*!g_pAbfSet->IsValid() &&*/ g_pAbfSet -> m_Vorbehandlung.IsEmpty () || g_pAbfSet -> m_Vorbehandlung == NotVorbehandlung)
					m_btVorbehandlung.SetCheck (FALSE);
				else
					m_btVorbehandlung.SetCheck (TRUE);
				OutputAbfarten ();
				if (m_pSet)
				{
					OutputArtenParameter ();						
					OutputMengen (MengenInit);
				}
				SetControlState ();
			}
		
		}
		else
		// keine Daten da und es soll gelesen werden
		{
			if (!pDX -> m_bSaveAndValidate)
			{
				m_lbAbfallArt.ResetContent ();		// Listboxinhalt lö.
				SetControlState(true);
			}
		}
}

BEGIN_MESSAGE_MAP(CAbfPage, CPropertyPage)
	//{{AFX_MSG_MAP(CAbfPage)
	ON_COMMAND (IDB_ARTDEL, OnArtDel)
	ON_EN_KILLFOCUS(IDE_MENGEM, OnKillfocusMengem)
	ON_EN_KILLFOCUS(IDE_MENGET, OnKillfocusMenget)
	ON_LBN_SELCHANGE(IDL_ABFALLART, OnSelchangeAbfallart)
	ON_WM_CREATE()
	ON_MESSAGE (IDM_SEND_TEXT, OnChangeName)
	ON_MESSAGE (IDM_SEND_NUMBER, OnChangeNummer)
	ON_MESSAGE (IDM_SEND_DELETEOBJ, OnDeleteDlg)
	ON_COMMAND (IDB_ARTNEU, OnArtneu)
	ON_COMMAND (IDB_ARTCHA, OnArtChange)
	ON_BN_CLICKED(IDB_CHANGE, OnChangeVerbringung)
	ON_BN_CLICKED(IDB_CHANGE_VERF, OnChangeVerfahren)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CAbfPage::SetControlState (bool disableall)
{
	ASSERT (NULL != g_pAbfSet);
	//				was soll'n ma    nicht synchron			 kein Schreibrecht		 
	bool bGlobState	= !disableall && g_pAbfSet->IsValid() && g_pAbfSet->CanUpdate(); // der Bearb.-Status der Recordsets

//	Kommentarfeld
	CWnd *pCWnd = GetDlgItem (IDE_COMMENT);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (bGlobState); 

//	Button neu
	pCWnd = GetDlgItem (IDB_ARTNEU);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (/*!disableall && */g_pAbfSet->CanUpdate());	// immer an wenn updatebar

//	Button löschen
	pCWnd = GetDlgItem (IDB_ARTDEL);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (bGlobState && 
						  (m_lbAbfallArt.GetCount () > 0));

//	Button ändern
	pCWnd = GetDlgItem (IDB_ARTCHA);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (bGlobState &&  
						  (m_lbAbfallArt.GetCount () > 0));

//	Bezeichnungsfeld
	pCWnd = GetDlgItem (IDE_ABFART);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (bGlobState);

//	interne Bezeichnung
	pCWnd = GetDlgItem (IDE_INTERNE_BEZ);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (bGlobState); 

//	Verbringungscode
	pCWnd = GetDlgItem (IDE_VERBRINGUNG);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (bGlobState); 

//	Nachweisnummer
	pCWnd = GetDlgItem (IDE_NACHWEIS_NR);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (bGlobState); 

//	Verfahren
	pCWnd = GetDlgItem (IDB_CHANGE_VERF);
	ASSERT (pCWnd != NULL);
	pCWnd -> EnableWindow (bGlobState); 

//	restl. Controls setzen
	m_edEAKNummer.EnableWindow (bGlobState);
	m_btVorbehandlung.EnableWindow (bGlobState);
	m_edMengeM.EnableWindow (bGlobState);
	m_edMengeT.EnableWindow (bGlobState);
	m_edDichte.EnableWindow (bGlobState);
	m_lbAbfallArt.EnableWindow (bGlobState && (m_lbAbfallArt.GetCount () > 0));
	m_btChange.EnableWindow (bGlobState);
	m_edVerfahren.EnableWindow (bGlobState);
}

/////////////////////////////////////////////////////////////////////////////
// CAbfPage message handlers
void CAbfPage::OnSelchangeAbfallart()	// ok
{
//	TODO: Add your control notification handler code here
	int iSel = m_lbAbfallArt.GetCurSel ();
	if (iSel < 0)
		return;

	COleVariant varOld, varAct;
	try
	{
		CWaitCursor wc;
		CMutex mt;
		ASSERT (NULL != g_pAbfSet);
		if (!g_pAbfSet -> IsOpen ())
			return;
//-----------------------------
	//	alte Buchmarke speichern			
		varOld = g_pAbfSet -> GetLastModifiedBookmark ();
		
		if (!g_pAbfSet -> CDaoRecordsetExt::LockReckord (Store, this))	// Satz speichern	
			return;
		
	//	lese zugeh. RecordInfo
		CRecordInfo *pInfo = (CRecordInfo *) m_lbAbfallArt.GetItemData (iSel);
		ASSERT (NULL != pInfo);
#ifdef _DEBUG
		CString strAbfArt;
		m_lbAbfallArt.GetText (iSel, strAbfArt);
		ASSERT (strAbfArt == pInfo -> m_strAbfArt);
#endif
		g_pAbfSet -> m_bOutputLockError = FALSE;	// keine Lock-Meldung an Nutzer
		g_pAbfSet -> SetBookmark (varAct = pInfo -> m_varBookMark);
		g_pAbfSet -> m_bOutputLockError = TRUE;

		m_bOutputArten = FALSE;
		UpdateData (FALSE);							// Ergebnisse im Dialog anzeigen
		m_bOutputArten = TRUE;


	}
	catch (CException *e)
	{
		if (e -> IsKindOf (RUNTIME_CLASS (CDaoException)))
			:: DisplayDaoException ((CDaoException *)e);
		else
			e -> ReportError ();
		e -> Delete ();
		m_lbAbfallArt.DeleteString (iSel);			// diesen Satz löschen
		if (varAct.vt != VT_EMPTY)
			VERIFY (g_pAbfSet -> m_RecordInfoList.DeleteRecord (varAct));	// auch Satz aus Liste löschen
		if (varOld.vt != VT_EMPTY)
			g_pAbfSet -> SetBookmark (varOld);		// alte Buchmarke einstellen	

	//	Meldung an Nutzer ausgeben: Satz nicht gefunden
		CGakApp *pApp = (CGakApp *) AfxGetApp ();
		ASSERT (pApp != NULL);
		pApp -> OutputMessage (IDS_NO_DRECORD_FOUND);								
	}

	m_bOutputArten = TRUE;
	SetCaption ();
}

//	Abfallarten ausgeben
void CAbfPage::OutputAbfarten ()	// ok
{
	if (!m_bOutputArten)
		return;

	ASSERT (NULL != g_pAbfSet);

	try
	{
		m_lbAbfallArt.ResetContent ();		// Listboxinhalt lö.
		CRecordInfoList &List = g_pAbfSet -> m_RecordInfoList;
		if (List.IsEmpty ())
			return;

		POSITION pos = List.GetHeadPosition ();	// 1. Pos.
		if (List.IsEmpty ())
			return;
		int iIndex = -1;					// akt. Index
		CRecordInfo *pInfo = NULL;			// akt. Recordinfo
		while (NULL != pos)
		{
			CRecordInfo *pInfo = List.GetNext (pos);
			ASSERT (NULL != pInfo);
			iIndex = m_lbAbfallArt.AddString (pInfo -> m_strAbfArt);
			if (iIndex < 0)
				AfxThrowMemoryException ();
			if (m_lbAbfallArt.SetItemData (iIndex, (DWORD) pInfo) < 0)
				AfxThrowMemoryException ();
		}

	//	jetzt erst Selektion setzen
		ASSERT (m_lbAbfallArt.GetCount () == List.GetCount ());
		int iMax = List.GetCount ();
		for (iIndex = 0; iIndex < iMax; iIndex++)
		{
			pInfo = (CRecordInfo *) m_lbAbfallArt.GetItemData (iIndex);
			ASSERT (NULL != pInfo);					

			if (pInfo -> m_bFirst)
			{
			//	vorher Test, ob richtiger Satz gewählt
#ifdef _DEBUG
				ASSERT ((pInfo->m_varBookMark == g_pAbfSet->GetBookmark ()) ||
						(pInfo->m_varBookMark == g_pAbfSet->GetLastModifiedBookmark ()));				
				CString strAbfArt;
				m_lbAbfallArt.GetText (iIndex, strAbfArt);
				ASSERT (strAbfArt == pInfo -> m_strAbfArt);
#endif
				VERIFY (m_lbAbfallArt.SetCurSel (iIndex) >= 0);
				break;			// nur ein Satz kann der aktuelle sein
			}
		}

	//	Anzahl Einträge in Listbox ausgeben
		CString strInfo;
		strInfo.Format (IDS_ARTEN_INFO, m_lbAbfallArt.GetCount ());
		m_stArtenInfo.SetWindowText (strInfo);
	}
	catch (CException *e)
	{
		if (e -> IsKindOf (RUNTIME_CLASS (CDaoException)))
			:: DisplayDaoException ((CDaoException *)e);
		else
			e -> ReportError ();
		e -> Delete ();
		m_lbAbfallArt.ResetContent ();
	}
}

BOOL CAbfPage::OnKillActive()	// ok
{
//	TODO: Add your specialized code here and/or call the base class
	try
	{
		if (!CPropertyPage::OnKillActive())
			return FALSE;

		if (m_pDlg && m_pDlg -> IsWindowVisible ())
			m_pDlg -> ShowWindow (SW_HIDE);		

		ASSERT (NULL != g_pAbfSet);
	
		int iSel = m_lbAbfallArt.GetCurSel ();
		// JG Datensatz muß gültig sein
		if ((iSel >= 0) && (g_pAbfSet->IsValid()))
		{
			CRecordInfo *pInfo = (CRecordInfo *) m_lbAbfallArt.GetItemData (iSel);			
			ASSERT (NULL != pInfo);
			VERIFY (g_pAbfSet -> m_RecordInfoList.SetFirstRecord (pInfo -> m_varBookMark));	
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

	return TRUE;
}

int CAbfPage::OnCreate(LPCREATESTRUCT lpCreateStruct) // ok

{
	if (CPropertyPage::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	return OpenSet ();
}

//	zugeh. Abfartennamen ausgeben, Dichte lesen, Mengen ausgeben
void CAbfPage::OutputArtenParameter ()	// ok
{
//	prüfe Parameter
	ASSERT (m_pSet != NULL && m_pSet -> IsOpen ());
	
	CString strSel;
	int iSel = m_lbAbfallArt.GetCurSel ();
	if (iSel >= 0)
		m_lbAbfallArt.GetText (iSel, strSel); 

	if (strSel.IsEmpty ())
	{
		m_dDichte = 0.0;
		m_edDichte.SetWindowText ("0.0");
		m_edAbfArt.SetWindowText ("");
		CString strInfo;
		VERIFY (strInfo.LoadString (IDS_NEIN));
		m_stSonderAbfall.SetWindowText (strInfo);
		return;
	}

//	Zeichenkette suchen
	try
	{
		CString strFind;
		AfxFormatString1 (strFind, IDS_FIND_NUMMER, (const char *)strSel);
		if (m_pSet -> FindFirst (strFind))
		{
			m_edAbfArt.SetWindowText (m_pSet -> m_Name); 
			m_dDichte = m_pSet -> m_Dichte;
			CString strInfo;
			VERIFY (strInfo.LoadString (m_pSet -> m_Sonderabfall ? IDS_JA : IDS_NEIN));
			m_stSonderAbfall.SetWindowText (strInfo);
			char Buffer [30] = "";
			m_edDichte.SetWindowText (DtoA (m_dDichte, Buffer, FloatFormat));
			return;
		}
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
	}
	catch (CException* e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	m_edAbfArt.SetWindowText ("");			
	m_dDichte = 0.0;
	m_edDichte.SetWindowText ("0.0");

	CString strInfo;
	VERIFY (strInfo.LoadString (IDS_NEIN));
	m_stSonderAbfall.SetWindowText (strInfo);
}

//	Fenster löscht sich selbst
LONG CAbfPage::OnDeleteDlg (UINT, LONG)	// ok
{
	m_pDlg = NULL;	
	return TRUE;
}

//	Set Öffnen
int CAbfPage::OpenSet ()		// ok
{
	if (m_pSet)
		return 0;

	try
	{
		ASSERT (NULL != g_pAbfSet);
		m_pSet = new CAbfArtSet (g_pAbfSet -> m_pDatabase,
							   ((CGakApp *)AfxGetApp ())->AbfallArtenDefaultSQL());
		m_pSet -> Open ();
		return 0;
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

	return -1;
}

BOOL CAbfPage::OnInitDialog()		// ok
{
	CPropertyPage::OnInitDialog();
	
//	TODO: Add extra initialization here
	VERIFY (m_btArtNeu.AutoLoad (IDB_ARTNEU, this));
	VERIFY (m_btArtDel.AutoLoad (IDB_ARTDEL, this));
	VERIFY (m_btArtChange.AutoLoad (IDB_ARTCHA, this));

//	Textlängen begrenzen
//	interne Bezeichnungsfeld
	CEdit *pWnd = (CEdit *)GetDlgItem (IDE_INTERNE_BEZ);
	ASSERT (pWnd != NULL);
	pWnd -> LimitText (NamenLaenge); 

//	EAK-Nummer
	m_edEAKNummer.LimitText (NummerLaenge);

//	Nachweisnummer
	pWnd = (CEdit *) GetDlgItem (IDE_NACHWEIS_NR);
	ASSERT (pWnd != NULL);
	pWnd -> LimitText (NummerLaenge*2);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAbfPage::OnKillfocusMengem()	// ok
{
	// TODO: Add your control notification handler code here
	CString strSel;
	m_edMengeM.GetWindowText (strSel);
	OutputMengen (MengenMeter, atof (strSel));	
}

void CAbfPage::OnKillfocusMenget() // ok
{
	// TODO: Add your control notification handler code here
	CString strSel;
	m_edMengeT.GetWindowText (strSel);
	OutputMengen (MengenTonnen, atof (strSel));	
}

void CAbfPage::OutputMengen (int iType, double dInputMenge)	// ok
{
	if (m_dDichte <= 0.0)		// nichts zu machen
		return;

	char Buffer [30] = "";

	switch (iType)
	{
		case MengenInit:		// Init.
		{
			CString strTonnen; //, strMeter;
			m_edMengeT.GetWindowText (strTonnen);
			// m_edMengeM.GetWindowText (strMeter);
			double dTonnen = atof (strTonnen);
			// double dMeter = atof (strMeter);
			if (dTonnen > 0.0)
			{
				m_edMengeT.SetWindowText (DtoA (dTonnen, Buffer, FloatFormat));
				OutputMengen (MengenTonnen, dTonnen);
			}
			else
				m_edMengeM.SetWindowText ("");				
			/*
			else
			{
				if (dMeter > 0.0)
				{
					m_edMengeM.SetWindowText (DtoA (dMeter, Buffer, FloatFormat));
					OutputMengen (MengenMeter, dMeter);
				}
			}
			*/
		}
		break;
		case MengenTonnen:		// Volumen berechnen und ausgeben
		{
			double dVol = dInputMenge / m_dDichte;				
			m_edMengeM.SetWindowText (DtoA (dVol, Buffer, FloatFormat));
		}
		break;
		case MengenMeter:		// Masse berechnen
		{
			double dTonnen = dInputMenge * m_dDichte;
			m_edMengeT.SetWindowText (DtoA (dTonnen, Buffer, FloatFormat));
		}
		break;
		default:
			ASSERT (FALSE);
	}
}		

BOOL CAbfPage::OpenDialog (void)	// ok
{
	try
	{	
		if (!m_pDlg)
		{
			ASSERT (NULL != m_pSet);
			ASSERT (m_pSet -> IsOpen ());
			m_pSet -> MoveFirst ();
			m_pDlg = new CSelNumberDlg (this, m_pSet, IDS_ABFART_CAPTION,
									  ((CGakApp *)AfxGetApp ())->AbfallArtenDefaultSQL());
			if (!m_pDlg -> Create (IDD_SEL_NUMMER))
				AfxThrowMemoryException ();
		}			

	//	Fenster aktivieren
		m_pDlg -> ShowWindow (SW_SHOWNORMAL);	

	//	aktuelle Selektion setzen
		int iSel = m_lbAbfallArt.GetCurSel ();
		if (iSel >= 0)
		{
			CString strOldName;
			m_lbAbfallArt.GetText (iSel, strOldName);
			m_pDlg -> StoreSelection (strOldName);
		}

	//	Fenster aktivieren
		m_pDlg -> SetFocus ();
		return TRUE;
	}
	catch (CDaoException *e)
	{
		:: DisplayDaoException (e);
		e -> Delete ();
		DELETE_OBJ (m_pDlg);
	}
	catch (CException* e)
	{
		e -> ReportError ();
		e -> Delete ();
		DELETE_OBJ (m_pDlg);
	}

	return FALSE;
}

//	neuer Abfallname gesendet
LONG CAbfPage:: OnChangeName(UINT, LONG) // ok
{
	//if (IsWindowVisible ()) --> hier nichts machen
	//	m_edAbfArt.SetWindowText ((const char *) lText);
	return TRUE;
}

//	Abfallart ändern
void CAbfPage::OnArtChange()	// ok
{
	m_bAction = FALSE;			// Nummer ändern
	OpenDialog ();				// Auswahl-Dialog aufrufen
}

//	neue Abfallart
void CAbfPage::OnArtneu()		// ok
{
	m_bAction = TRUE;			// Neue Nummer
	OpenDialog ();				// Auswahl-Dialog aufrufen
}

void CAbfPage::SetCaption()
{
	((CAbfSheet *) GetParent ()) -> SetCaption ();
}

//	neue Abfallnummer gesendet	// ok
LONG CAbfPage:: OnChangeNummer(UINT, LONG lText)	
{
	ASSERT (NULL != g_pAbfSet);
	try
	{
		CWaitCursor wc;
		CMutex mt;
		switch (m_bAction)
		{
			case FALSE:			// Nummer ändern
			{
				//g_pAbfSet -> m_Menge_t = 0.0;
				// g_pAbfSet -> m_Menge_cbm = 0.0;
				g_pAbfSet -> m_Abfallnummer = (char *) lText;	
				
			//	alten Satz speichern					
				if (!g_pAbfSet -> CDaoRecordsetExt::LockReckord (Store, this))
					break;
				VERIFY (g_pAbfSet -> m_RecordInfoList.SetFirstRecord (g_pAbfSet -> GetLastModifiedBookmark (),
																	  g_pAbfSet -> m_Abfallnummer));					
			}
			break;
			case TRUE:			// neue Abfallart
			{
				bool bWasValid = g_pAbfSet->IsValid();
				
			//	alten Satz speichern					
				if (!g_pAbfSet -> CDaoRecordsetExt::LockReckord (Store, this))
					break;

			//	Datensatz für 'AddNew' vorbereiten und locken
			// JG hier Synchronisation eingefügt
				if (!g_pAbfSet -> PrepareAddNew (g_pErzSet -> m_Nummer, SetAbfallArt, (LPARAM) lText))
					break;

				//	Satz in Liste aufnehmen
				COleVariant varBM = g_pAbfSet -> GetLastModifiedBookmark ();
				
				
				VERIFY (g_pAbfSet -> m_RecordInfoList.AddRecord (varBM, (const char *) lText, TRUE));
				g_pAbfSet -> SetBookmark (varBM);

			//	jetzt haben wir ja jemanden
			//	g_pAbfSet->SearchNummer(/*(const char *) lText*/);
			// mit anderen Parametern zeigt diese Funktion eine gewünschte Abfallart an 
				
			// wenn der Datensatz vorher ungültig war, dann jetzt alle gültigen DS lesen, ohne Rücksicht auf die Position
				if (!bWasValid)
					g_pAbfSet->SearchNummer();
			}
			break;
			default:
				ASSERT (FALSE);
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

	UpdateData (FALSE);		// Ergebnisse im Dialog anzeigen
	SetCaption ();
	return TRUE;
}

//	Abfallart löschen
void CAbfPage::OnArtDel() 
{
	ASSERT (g_pAbfSet && g_pAbfSet -> IsOpen ());

//	Transaktion bewirkt leeren des internen Puffers
	CDaoWorkspace *pWSpace = g_pAbfSet -> m_pDatabase -> m_pWorkspace;
	ASSERT (pWSpace != NULL);

	try
	{

	//	Operation durchführbar ?
		int iOldSel = m_lbAbfallArt.GetCurSel ();
#ifdef _DEBUG
		if (m_lbAbfallArt.GetCount () <= 0 || iOldSel < 0)
		{
			ASSERT (FALSE);
			return;
		}	
#endif		

	// JG 981006 
	// Änderungen an der Behandlung des letzten Datensatzes
	//	Spezialfall soll Parent behandeln
		if (1 == m_lbAbfallArt.GetCount ())
		{
			((CAbfSheet *) GetParent ()) -> DeleteAbfallGruppe ();
			return;
		}

	//	Nutzer nachfragen
		CString strDelText;
		AfxFormatString1 (strDelText, IDS_DELETE_ABFALL, g_pAbfSet -> m_Abfallnummer);
		if (IDYES != MessageBox (strDelText, AfxGetAppName(), MB_ICONQUESTION | MB_YESNO))
			return;

		CWaitCursor wc;						// Sanduhr einschalten
		CMutex mt;

	//	neue Selektion ermitteln
		int iNewSel = 0 == iOldSel ? 1 : iOldSel - 1;
	
	//	Transaktion beginnen
		pWSpace -> BeginTrans ();
		g_pAbfSet -> m_bDeleteAll = FALSE;	// nur akt. Satz löschen
		g_pAbfSet -> Delete ();			// wenn Satz nicht gelöscht werden konnte 
										// folgt Exception !

		// JG 981006 
		// Änderungen an der Behandlung des letzten Datensatzes

		// außer wenn der letzte Datensatz gelöscht wurde
/*		if (1 != m_lbAbfallArt.GetCount ())*/
		{
			//	neuen Satz setzen
			CRecordInfo *pInfo = (CRecordInfo *) m_lbAbfallArt.GetItemData (iNewSel);
			ASSERT (NULL != pInfo);
			g_pAbfSet -> SetBookmark (pInfo -> m_varBookMark);

		//	dieser Satz wird selektierter
			VERIFY (g_pAbfSet -> m_RecordInfoList.SetFirstRecord (pInfo -> m_varBookMark));	
		}

	//	alten Satz aus Liste löschen
		CRecordInfo *pInfo = (CRecordInfo *) m_lbAbfallArt.GetItemData (iOldSel);
		ASSERT (NULL != pInfo);
		VERIFY (g_pAbfSet -> m_RecordInfoList.DeleteRecord (pInfo -> m_varBookMark));

		pWSpace -> CommitTrans ();			// Ende der Transaktion
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
		pWSpace -> Rollback ();
	}

	// die anderen Seiten auch mal informieren
//	dynamic_cast<CAbfSheet*> (GetParent()) -> UpdatePages())
	UpdateData (FALSE);
	SetCaption ();
}

/*
//	auf akt. Satz pos.
BOOL CAbfPage::FindActRecord()	// ok
{
	try
	{
		if (-1 == OpenSet ())
			return FALSE;

		ASSERT (NULL != g_pAbfSet);
		ASSERT (NULL != m_pSet && m_pSet -> IsOpen ());
		CString strFind;
		AfxFormatString1 (strFind, IDS_FIND_NUMMER, g_pAbfSet -> m_Abfallnummer);
		return m_pSet -> FindFirst (strFind);
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

	return FALSE;
}

//	lese Abfallart
CString CAbfPage::GetName ()		// ok
{
	return FindActRecord () ? m_pSet -> m_Name : "";
}		

CString CAbfPage::GetSonderAbfall (void)
{
	CString strRes;
	try
	{
		BOOL bFind = FindActRecord ();
		if (bFind && m_pSet -> m_Sonderabfall)
			VERIFY (strRes.LoadString (IDS_JA));
		else
			VERIFY (strRes.LoadString (IDS_NEIN));
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

	return strRes;
}

CString CAbfPage::GetMengeT (void)		// ok
{
	CString strRes;
	try 
	{
		ASSERT (NULL != g_pAbfSet);
		char Buffer [30] = "";
		strRes = DtoA (g_pAbfSet -> m_Menge_t, Buffer, FloatFormat);
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
	}

	return strRes;
}

CString CAbfPage::GetVorbehandlung (void)	// ok
{
	ASSERT (NULL != g_pAbfSet);

	try 
	{
		int iFind = m_cbVorbehandlung.FindString (-1, g_pAbfSet -> m_Vorbehandlung);
		if (iFind >= 0)
		{
			CString strRes;
			m_cbVorbehandlung.GetLBText (iFind, strRes);				
			if (!strRes.IsEmpty ())
				return strRes;
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

	return g_pAbfSet -> m_Vorbehandlung;	
}
*/

void CAbfPage::OnChangeVerbringung() 
{
	// TODO: Add your control notification handler code here
	ASSERT (NULL != m_pSet);
	ASSERT (m_pSet -> IsOpen ());
	ASSERT (NULL != m_pSet -> m_pDatabase);

	try
	{
	//	Set öffnen
		CSelectSet Set (m_pSet -> m_pDatabase, ((CGakApp *)AfxGetApp ())->VerbringungsDefaultSQL());
		Set.Open (dbOpenSnapshot, NULL, dbForwardOnly);

	//	neuen Verbringungskode vom Nutzer auswählen
		CString strNummer;
		m_edVerbringung.GetWindowText (strNummer);
		CSelNumberDlg VerDlg (this, &Set, ((CGakApp *)AfxGetApp ())->VerbringungsDefaultSQL(), 
							  IDS_VERBRC_CAPTION, FALSE, strNummer);
		if ((VerDlg.DoModal () == IDOK) && !VerDlg.m_strNumber.IsEmpty ())
			m_edVerbringung.SetWindowText (VerDlg.m_strNumber);
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

void CAbfPage::OnChangeVerfahren() 
{
	// TODO: Add your control notification handler code here
	ASSERT (NULL != m_pSet);
	ASSERT (m_pSet -> IsOpen ());

	try
	{
	//	Set öffnen
		CSelectSet Set(m_pSet -> m_pDatabase, ((CGakApp *)AfxGetApp ())-> VerfahrenDefaultSQL());
		Set.Open (dbOpenSnapshot, NULL, dbForwardOnly);

	//	neues Verfahren vom Nutzer eingeben
		CString strSel;
		m_edVerfahren.GetWindowText (strSel);
		CSelNumberDlg Dlg (this, &Set, ((CGakApp *)AfxGetApp ())-> VerfahrenDefaultSQL(), IDS_VERFAHREN_CAPTION,
						   FALSE, strSel);
		if ((IDOK == Dlg.DoModal ()) && (!Dlg.m_strNumber.IsEmpty ()))
			m_edVerfahren.SetWindowText (Dlg.m_strNumber);
		
	//	Set schließen
		if (Set.IsOpen ())
			Set.Close ();		
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
