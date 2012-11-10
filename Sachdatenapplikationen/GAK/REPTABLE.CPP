// RepTable.cpp : implementation file
//

#include "stdafx.h"			//	prec. Header
#include "recset.h"			//	CRecordsetExt
#include "erzliste.h"		//	CErzListeSet
#include "res.h"			//	Ressourcen
#include "Gak.h"			//  zum Drucken

#include "RepTable.h"		//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	Konstanten
static const int iFieldCnt = 17;		//	Anzahl der Spalten
static const char *szFieldNames [iFieldCnt] = {
	"lfd. Nr.",
	"Erzeuger-Nr.",
	"Anfallstelle",
	"Ort der Anfallstelle",
	"Ansprechpartner",
	"Telefon",
	"Telefax",
	"Branchen-Nr.",
	"Abfallschl¸ssel-Nr.",
	"Sonderabfall",
	"EN/SN-Nr.",
	"Menge [t]",
	"Befˆrderer-Nr.",
	"Entsorger-Nr.",
	"R/D-Verfahren",
	"Priorit‰t",
	"Bilanzdaten",
	// "Bearbeitet",
};

//	Konstanten zum kopieren
static const int CopyBufferSize = 512 * 1024;	// max. 512 KB-Puffer f¸r Copy ins Clipboard
static const short MaxFeldLen = 128;			// max. 128 Zeichen f¸r Feld ausgeben
static const char Tab [] = "\t";
static const char NL [] = "\n";

/////////////////////////////////////////////////////////////////////////////
// CReportTable dialog
CReportTable::CReportTable(CWnd* pParent, CErzListeSet *pSet, const CString &strTable)
	: CDialog(CReportTable::IDD, pParent)
{
	//{{AFX_DATA_INIT(CReportTable)
	//}}AFX_DATA_INIT
	ASSERT (NULL != pSet && pSet -> IsOpen ());
	ASSERT (!strTable.IsEmpty ());
	m_pSet = pSet;
	m_strTable = strTable;
	init = false;
}


void CReportTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReportTable)
	DDX_Control(pDX, IDC_ERZLISTDRUCKVOR, m_btErzListDruckVor);
	DDX_Control(pDX, IDOK, m_btOK);
	DDX_Control(pDX, IDC_ERZLISTDRUCK, m_btErzListDruck);
	DDX_Control(pDX, IDC_LIST, m_lcListe);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReportTable, CDialog)
	//{{AFX_MSG_MAP(CReportTable)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_ERZLISTDRUCK, OnErzlistdruck)
	ON_BN_CLICKED(IDC_ERZLISTDRUCKVOR, OnErzlistdruckvor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReportTable message handlers

BOOL CReportTable::OnInitDialog() 
{
	CDialog::OnInitDialog();

//	pr¸fe Parameter
	ASSERT (m_pSet && m_pSet -> IsOpen ());

	CWaitCursor wc;

//	Spaltennamen ausgeben
	for (int iItem = 0; iItem < iFieldCnt; iItem++)
	{
		ASSERT (NULL != szFieldNames [iItem]);
		ASSERT (*szFieldNames [iItem]);
		if (m_lcListe.InsertColumn (iItem, szFieldNames [iItem]) != iItem)
			AfxThrowMemoryException ();
	}
	
//	Caption akt.
	CString strFormat, strCaption;
	GetWindowText (strFormat);
	strCaption.Format (strFormat, m_strTable);
	SetWindowText (strCaption);
	
//	Dateninhalte ausgeben
	CString strJa, strNein, strTemp;
	VERIFY (strJa.LoadString (IDS_JA)); 
	VERIFY (strNein.LoadString (IDS_NEIN)); 
	for (iItem = 0; !m_pSet -> IsEOF (); m_pSet -> MoveNext (), iItem++)
	{
	//	zuerst SatzNummer ausgeben
		strTemp.Format ("%d", iItem + 1);
		if (m_lcListe.InsertItem (iItem, strTemp) != iItem)
			AfxThrowMemoryException ();

	//	restlichen Felder ausgeben
		if (!m_lcListe.SetItemText (iItem, 1, m_pSet->m_strNummer))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 2, m_pSet->m_strAnfallstelle))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 3, m_pSet->m_strOrtsname))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 4, m_pSet->m_strAnsprechpartner))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 5, m_pSet->m_strPartnertelefon))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 6, m_pSet->m_strPartnertelefax))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 7, m_pSet->m_strBranchennummer))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 8, m_pSet->m_strAbfallnummer))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 9, m_pSet->m_bSonderabfall ? strJa : strNein))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 10, m_pSet->m_strNachweisnummer))
			AfxThrowMemoryException ();
		strTemp.Format (szMengenFormat, m_pSet->m_dMenge);
		if (!m_lcListe.SetItemText (iItem, 11, strTemp))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 12, m_pSet->m_strTransporteurnummer))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 13, m_pSet->m_strEntsorgernummer))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 14, m_pSet->m_strVerfahren))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 15, m_pSet->m_strPrioritaet))
			AfxThrowMemoryException ();
		if (!m_lcListe.SetItemText (iItem, 16, m_pSet->m_bBilanzdaten ? strJa : strNein))
			AfxThrowMemoryException ();
		/*
		if (!m_lcListe.SetItemText (iItem, 17, m_pSet->m_bBearbeitet ? strJa : strNein))
			AfxThrowMemoryException ();
		*/
	}

//	Breite aller Felder setzen
	// int iItemCnt = m_lcListe.GetItemCount ();
	for (int i = 0; i < iFieldCnt; i++)
		// m_lcListe.SetColumnWidth (i, iItemCnt > 0 ? LVSCW_AUTOSIZE : LVSCW_AUTOSIZE_USEHEADER);
		m_lcListe.SetColumnWidth (i, LVSCW_AUTOSIZE_USEHEADER);			

//	ggf. Men¸item kopieren anh‰ngen
	if (m_lcListe.GetItemCount () > 0)
	{
		CMenu *pMenu = GetSystemMenu (FALSE);
		ASSERT (NULL != pMenu);
		CString strMenu;
		VERIFY (strMenu.LoadString (IDS_MENU_COPY));
		VERIFY (pMenu->AppendMenu (MF_STRING, IDM_COPY, strMenu));
	}

	init = true;
	CRect recFenster;
	GetClientRect(recFenster);
	OnSize(0, recFenster.right, recFenster.left);
	init = false;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CReportTable::OnSize(UINT nType, int cx, int cy) 
{
	static bool b2Init = true;
	static int randx, randy, buttondx;  // die Abst‰nde der beiden Buttons zum Rand und untereinander
										// sie liegen beide auf gleicher Hˆhe
	if (b2Init && m_lcListe.m_hWnd)
	{
		CRect newRect;
		GetClientRect(newRect);
			
		CRect okRect;
		m_btOK.GetClientRect(okRect);
		
		CRect drRect;
		m_btErzListDruck.GetClientRect(drRect);

		randy = okRect.Height() / 2;
		randx = okRect.Width() / 2;
		buttondx = randx;
		
		b2Init = false;
	}
	
	if (!init)
		CDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (m_lcListe.m_hWnd)
	{
		
		// das neue Rechteck des Fensters
		CRect newRect;
		GetClientRect(newRect);
			
		CRect okRect;
		m_btOK.GetClientRect(okRect);
		
		CRect listRect = newRect;
		listRect -= listRect.TopLeft();	// Ursprung wiederherstellen

		listRect.bottom -= okRect.Height() + 2 * randy;	// unten Platz machen
		m_lcListe.MoveWindow(listRect);

		okRect.OffsetRect((newRect.BottomRight() - CSize(randx, randy)) - okRect.BottomRight());
		m_btOK.MoveWindow(okRect);

		okRect.OffsetRect(CSize(-okRect.Width()-buttondx, 0));
		m_btErzListDruck.MoveWindow(okRect);

		okRect.OffsetRect(CSize(-okRect.Width()-buttondx, 0));
		m_btErzListDruckVor.MoveWindow(okRect);
// old Code
//		m_lcListe.MoveWindow (0,0,cx,cy);
		
	}
}

void CReportTable::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int iItem = m_lcListe.GetNextItem (-1, LVIS_SELECTED);
	if (iItem >= 0)
		VERIFY (m_lcListe.SetItemState (iItem, 0, LVIS_SELECTED));
	
	*pResult = 0;
}

void CReportTable::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// TODO: Add your message handler code here and/or call default
	if (IDM_COPY == nID)
	{
		try
		{
			CWaitCursor wc;
			
			if (!OpenClipboard () || !EmptyClipboard ())
				AfxThrowUserException ();

			int iItem = 0;							// akt. Item

		//	max. Zeilenzahl
			int iItemCnt = m_lcListe.GetItemCount ();
			CString strRes (' ', __min(iItemCnt * 1024, CopyBufferSize));	// ErgebnisText;

		//	Feldnamen ausgeben
			for (iItem = 0; iItem < iFieldCnt; iItem++)
			{
				ASSERT (NULL != szFieldNames [iItem]);
				strRes += szFieldNames [iItem];
				if (iItem < iFieldCnt-1)
					strRes += Tab;
			}
			strRes += NL;		// neue Zeile
			
		//	f¸r alle Items
			for (iItem = 0; iItem < iItemCnt; iItem++)
			{
			//	f¸r alle Spalten
				for (int iCol = 0; iCol < iFieldCnt; iCol++)
				{
					strRes += m_lcListe.GetItemText (iItem, iCol);
					if (iCol < iFieldCnt-1)
						strRes += Tab;
				}
				strRes += NL;			
			}

		//	String ins Clipboard ausgeben
			HGLOBAL hText = :: GlobalAlloc (GMEM_MOVEABLE | GMEM_DDESHARE,
											strRes.GetLength () + 1);
			if (!hText)
				AfxThrowMemoryException ();
			char *pText = (char *) :: GlobalLock (hText);
			if (!pText)
				AfxThrowMemoryException ();
			strcpy (pText, strRes);	
			if (GlobalUnlock (hText) == TRUE)
				AfxThrowMemoryException ();
			if (!SetClipboardData (CF_TEXT, hText))
				AfxThrowUserException ();
		}
		catch (CUserException *e)	// Clipboard-Fehler
		{
			CString strError;
			VERIFY (strError.LoadString (IDS_CLIPB_ERROR));
			MessageBox (strError, AfxGetAppName (), MB_OK | MB_ICONSTOP);		
			e -> Delete ();
		}
		catch (CException *e)
		{
			e -> ReportError ();
			e -> Delete ();
		}

		 CloseClipboard ();	// auf jeden Fall schlieﬂen
	}
	else		
		CDialog::OnSysCommand(nID, lParam);
}


void CReportTable::OnErzlistdruck() 
{
	Druck(false);
}

void CReportTable::OnErzlistdruckvor() 
{
	Druck(true);
}

void CReportTable::Druck(bool bToWindow)
{
	CGakApp* pApp = static_cast<CGakApp*> (AfxGetApp());
	if (NULL == pApp)
		return;

	pApp->Print("erzlist", "Erzeugerliste", m_strTable, bToWindow, this);
}

