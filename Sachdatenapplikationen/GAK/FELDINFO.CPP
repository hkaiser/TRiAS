// FeldInfo.cpp : implementation file
//

#include "stdafx.h"		// prec. Header
#include "gak.h"		// CGakApp un Ressourcen
#include "selset.h"		// CSelectSet
#include "winnls.h"		// WideCharToMultiByte
#include "FeldInfo.h"	// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	globale Funktionen	
//	Konvertierung UNICODE --> ANSI ---------------------------------------------
inline char *__ConvertStrWtoA (LPCWSTR strIn, char *buf, UINT size)
{
	int badConversion = 0;
	WideCharToMultiByte (CP_ACP, NULL, strIn, -1, buf, size, NULL, &badConversion);
	return buf;
}

char *AnsiStringNew (LPCWSTR strIn)
{
	static char buf[_MAX_PATH];
	return (__ConvertStrWtoA (strIn, buf, _MAX_PATH));
}

/////////////////////////////////////////////////////////////////////////////
// CFeldInfos dialog
CFeldInfos :: CFeldInfos(CWnd* pParent, CSelectSet *pSet, 
						 const char *pCaption, const char *pTableName,
						 const char *pName /*=NULL*/)
			: CDialog(CFeldInfos::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFeldInfos)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_pSet = NULL;

	ASSERT (NULL != pSet);
	ASSERT_VALID (pSet);
	ASSERT (NULL != pCaption && AfxIsValidString (pCaption));
	ASSERT (NULL != pTableName && AfxIsValidString (pTableName));

	m_pSet = pSet;
	m_strCaption = pCaption;
	m_strTableName = pTableName;

//	ggf. Name übernehmen
	if (pName && *pName)
		m_strName = pName;
}


void CFeldInfos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFeldInfos)
	DDX_Control(pDX, IDC_FELDINFO, m_lcFeldInfos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFeldInfos, CDialog)
	//{{AFX_MSG_MAP(CFeldInfos)
	ON_WM_SIZE()
	ON_NOTIFY(NM_CLICK, IDC_FELDINFO, OnClickFeldinfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CFeldInfos::OnSize(UINT nType, int cx, int cy) // ok
{
	CDialog::OnSize(nType, cx, cy);
	
 // TODO: Add your message handler code here
	if (m_lcFeldInfos.m_hWnd && m_lcFeldInfos.IsWindowVisible ())
		m_lcFeldInfos.MoveWindow (0, 0, cx, cy);			
}

void CFeldInfos::OnClickFeldinfo(NMHDR* pNMHDR, LRESULT* pResult) // ok
{
//	TODO: Add your control notification handler code here
	int iIndex = m_lcFeldInfos.GetNextItem (-1, LVNI_SELECTED);
	if (iIndex >= 0)
		m_lcFeldInfos.SetItemState (iIndex, 0, LVIS_SELECTED);	// Selektion rücksetzen

	*pResult = 0;
}

BOOL CFeldInfos::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	TODO: Add extra initialization here
	ASSERT (NULL != m_pSet);
	ASSERT_VALID (m_pSet);

	CWaitCursor wc;
	SetWindowText (m_strCaption);		// Überschrift ausgeben

//	Spalten-Überschrift für ListControl
	CString strName, strNummer;
	if (! strName.LoadString (IDS_FELDNAME) ||
		! strNummer.LoadString (IDS_FELDINHALT) ||
		 (m_lcFeldInfos.InsertColumn (0, strName) != 0) ||
		 (m_lcFeldInfos.InsertColumn (1, strNummer) != 1))
		AfxThrowResourceException ();

//	Ja/Nein-Feld
	CString strJa, strNein;
	VERIFY (strJa.LoadString (IDS_JA));
	VERIFY (strNein.LoadString (IDS_NEIN));

//	Set öffnen und positionieren
	CString strSel;	// select * from '%1' where Nummer = '%2'
	AfxFormatString2 (strSel, IDS_SELECT_FELDINFO, m_strTableName, m_strCaption); 

//	ggf. vollständige Suche über Name: AND Name = '%1'
	if (!m_strName.IsEmpty ())
	{
		CString strAnd;
		AfxFormatString1 (strAnd, IDS_AND_KLAUSEL, m_strName);
		strSel += " " + strAnd;
	}

	CDaoRecordset Set (m_pSet -> m_pDatabase);
	Set.Open (dbOpenSnapshot, strSel, dbForwardOnly);	// set öffnen
	short sCnt = Set.GetFieldCount ();					// Anzahl Felder
	CDaoFieldInfo Info;									// ak. FeldInfo
	int iActIndex = 0;									// akt. Index
	const char *pVal = NULL;		// Zeiger auf akt. Wert
	COleVariant vars, vard;			// Feldwert
	char Empty [] = "";				// leere ZK
	while (! Set.IsEOF ())
	{
	//	ListBox füllen
		for (short sIndex = 0; sIndex < sCnt; sIndex++, iActIndex++)
		{
			vars.Clear ();

		//	Feldinformation lesen
			Set.GetFieldInfo (sIndex, Info);		
			vars = Set.GetFieldValue (Info.m_strName);
			if ((VT_EMPTY == vars.vt) || (VT_NULL == vars.vt) || (VT_UNKNOWN == vars.vt))
				pVal = Empty;
			else
			{
				if (VT_BSTR == vars.vt)
					pVal = (char *) vars.pbVal;
				else
				{
					if (VT_BOOL == vars.vt)
						pVal = 0 == vars.pbVal ? strNein : strJa;
					else
					{
						vard.ChangeType (VT_BSTR, vars);		// in Zeichenkette umwandeln
						pVal = AnsiStringNew ((LPCWSTR) vard.pbVal);
					}
				}
			}

		//	jetzt Infos in ListBox ausgeben
			if ((m_lcFeldInfos.InsertItem (iActIndex, Info.m_strName) != iActIndex)	||
				  !(m_lcFeldInfos.SetItemText (iActIndex, 1, pVal)))
				  AfxThrowMemoryException ();
		}

		Set.MoveNext ();		// zum nächsten Satz
	}
	if (Set.IsOpen ())
		Set.Close ();

//	Größe der Listbox an Dialog anpassen
	CRect rc;
	GetClientRect (rc);
	m_lcFeldInfos.MoveWindow (0, 0, rc.Width (), rc.Height ());		

//	Listbox größe einstellen
	m_lcFeldInfos.SetColumnWidth (0, rc.Width () / 3);
	m_lcFeldInfos.SetColumnWidth (1, rc.Width () * 2 / 3);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

