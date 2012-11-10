// ErfassPrivDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "ErfassPrivDlg.h"

#include "EdPage1.h"
#include "EdPage2.h"
#include "EdPage3.h"
#include "EdPage4.h"
#include "EdPage5.h"
//#include "EdPage6.h"
#include "EditPage7.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CTriDBSet* g_pSetTriDB;
extern CDatabase* g_pDatabase;
extern CSetNF_PG4* g_pNF_PG4;

/////////////////////////////////////////////////////////////////////////////
// CErfassPrivDlg

IMPLEMENT_DYNAMIC(CErfassPrivDlg, CPropertySheet)

CErfassPrivDlg::CErfassPrivDlg(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_bEditIDE = FALSE;
	m_bGeaendert = FALSE;
	m_bGBmodified = FALSE;
	m_bDmodified = FALSE;
	m_bHmodified = FALSE;
	m_bEmodified = FALSE;

	m_rAWE = 0;
	m_rAEW = 0;
	m_rEGW = 0;
	m_bZE = FALSE;
	m_bSGR = FALSE;
	m_rFS = 0;
	m_bSGT = FALSE;
	m_bKK = FALSE;
	m_rFKK = 0;
	m_bKKT = FALSE;
	m_bVF = FALSE;
	m_bK = FALSE;
	m_bFZ = FALSE;
	m_bFE = FALSE;
	m_bFZE = FALSE;

	m_rNFP1_BAR = 0;
	m_rNFP1_GFZ = 0;
	m_rNFP1_BMZ = 0;
	m_rNFP1_VGZ = 0;
	m_rNFP1_GUZ = 0;
	m_rNFP1_KAT = 0;

	m_tNFP1_ANDAT = time_t( 0 );
}

CErfassPrivDlg::CErfassPrivDlg(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_bEditIDE = FALSE;
	m_bGeaendert = FALSE;
	m_bGBmodified = FALSE;
	m_bDmodified = FALSE;
	m_bHmodified = FALSE;
	m_bEmodified = FALSE;

	m_rAWE = 0;
	m_rAEW = 0;
	m_rEGW = 0;
	m_bZE = FALSE;
	m_bSGR = FALSE;
	m_rFS = 0;
	m_bSGT = FALSE;
	m_bKK = FALSE;
	m_rFKK = 0;
	m_bKKT = FALSE;
	m_bVF = FALSE;
	m_bK = FALSE;
	m_bFZ = FALSE;
	m_bFE = FALSE;
	m_bFZE = FALSE;

	m_rNFP1_BAR = 0;
	m_rNFP1_GFZ = 0;
	m_rNFP1_BMZ = 0;
	m_rNFP1_VGZ = 0;
	m_rNFP1_GUZ = 0;
	m_rNFP1_KAT = 0;

	m_tNFP1_ANDAT = time_t( 0 );
}

CErfassPrivDlg::~CErfassPrivDlg()
{
}


BEGIN_MESSAGE_MAP(CErfassPrivDlg, CPropertySheet)
	//{{AFX_MSG_MAP(CErfassPrivDlg)
	ON_BN_CLICKED(IDOK, OnOK )
	ON_BN_CLICKED(IDCANCEL, OnCancel )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErfassPrivDlg message handlers

int CErfassPrivDlg::DoModal() 
{
	m_psh.dwFlags |= PSH_NOAPPLYNOW;
	return CPropertySheet::DoModal();
}


void CErfassPrivDlg::OnOK()
{
	int		result = IDOK;

	if ( !Geaendert())
		result = IDCANCEL;
	else
	{
		RestorePages();
		if ( GBGeaendert())		RewriteGeb();
		if ( DGeaendert())		RewriteDT();
		if ( HGeaendert())		RewriteVF();
		if ( EGeaendert())		RewriteEig();
	}

	CPropertySheet::EndDialog( result );
}	// OnOK

void CErfassPrivDlg::OnCancel()
{
	CPropertySheet::EndDialog( IDCANCEL );
}	// OnCancel

void CErfassPrivDlg :: InitPages()
{
	CxString	text, ort, str;

	// Seite 1
	page1 -> m_strNFP1_IDE = m_strNFP1_IDE;
	page1 -> m_strNFP1_ENA = m_strNFP1_ENA;
	page1 -> m_strNFP1_EAN = m_strNFP1_EAN;
	page1 -> m_strNFP1_EPL = m_strNFP1_EPL;
	page1 -> m_strNFP1_EOR = m_strNFP1_EOR;
//	page1 -> m_strNFP1_ORT = m_strNFP1_ORT;
	g_pSetTriDB -> Ortslage( m_strNFP1_IDE, ort, str );
	text = ort;
	text += ", ";
	text += str;
	page1 -> m_strNFP1_ORT = text;
	page1 -> m_strNFP1_FLU = m_strNFP1_FLU;
	page1 -> m_iNFP1_BAR = int( m_rNFP1_BAR ) - 1;	// DB: 1...; ComboBox: 0...
	page1 -> m_rNFP1_GFZ = m_rNFP1_GFZ;
	page1 -> m_rNFP1_BMZ = m_rNFP1_BMZ;
	page1 -> m_rNFP1_VGZ = m_rNFP1_VGZ;
	page1 -> m_rNFP1_GUZ = m_rNFP1_GUZ;
	page1 -> m_strNFP1_FST = m_strNFP1_FST;
	page1 -> m_rNFP1_KAT = m_rNFP1_KAT;
//	page1 -> m_tNFP1_ANDAT = m_tNFP1_ANDAT.GetTime();
	if ( m_tNFP1_ANDAT == time_t( 0 ))
		page1 -> m_strNFP1_ANDAT = "";
	else
	{
		text.Empty();
		text.AppendF( m_tNFP1_ANDAT, 10 );
		page1 -> m_strNFP1_ANDAT = text;
	}

	page1 -> m_bEditIDE = m_bEditIDE;

	// Seite 2
	page2 -> m_parrPG2D = &m_arrPG2D;
	page2 -> m_strIDE   = m_strNFP1_IDE;

	// Seite 3
	page3 -> m_parrPG2H = &m_arrPG2H;
	page3 -> m_strIDE   = m_strNFP1_IDE;

	// Seite 4
	page4 -> m_rAWE = m_rAWE;
	page4 -> m_rAEW = m_rAEW;
	page4 -> m_rEGW = m_rEGW;
	page4 -> m_bZE = m_bZE;
	page4 -> m_bSGR = m_bSGR;
	page4 -> m_rFS = m_rFS;
	page4 -> m_bSGT = m_bSGT;
	page4 -> m_bKK = m_bKK;
	page4 -> m_rFKK = m_rFKK;
	page4 -> m_bKKT = m_bKKT;
	page4 -> m_bVF = m_bVF;
	page4 -> m_bK = m_bK;
	page4 -> m_bFZ = m_bFZ;
	page4 -> m_bFE = m_bFE;
	page4 -> m_bFZE = m_bFZE;
	page4 -> m_strSonst = m_strBem;
	page4 -> m_bANNWL =	TestYES( m_strANNWL );

	// Seite 5
	page5 -> m_parrPG1GB = &m_arrPG1GB;
	page5 -> m_strIDE   = m_strNFP1_IDE;

	// Seite 6
//	page6 -> m_strBem = m_strBem;

	// Seite 7 (Eigentümer)
	page7 -> m_parrEigent = &m_arrEigent;
	page7 -> m_bMiteigentum = m_bMiteigent;
}

void CErfassPrivDlg :: RestorePages()
{
	CEigentuemer	*pSatz;
	CTime			tempTime;
	CxString		text;

//	if ( page1 -> m_tNFP1_ANDAT.GetStatus() == COleDateTime::valid )
//		tempTime = CTime( page1 -> m_tNFP1_ANDAT.GetYear(),
//						  page1 -> m_tNFP1_ANDAT.GetMonth(),
//						  page1 -> m_tNFP1_ANDAT.GetDay(),
//						  page1 -> m_tNFP1_ANDAT.GetHour(),
//						  page1 -> m_tNFP1_ANDAT.GetMinute(),
//						  page1 -> m_tNFP1_ANDAT.GetSecond());

	page1 -> UpdateData( TRUE );
	if ( ::IsWindow( page2 -> m_hWnd ))		// Falls Seite 2 nicht aufgeklappt wurde!
		page2 -> UpdateData( TRUE );
	if ( ::IsWindow( page3 -> m_hWnd ))		page3 -> UpdateData( TRUE );
	if ( ::IsWindow( page4 -> m_hWnd ))		page4 -> UpdateData( TRUE );
	if ( ::IsWindow( page5 -> m_hWnd ))		page5 -> UpdateData( TRUE );
	if ( ::IsWindow( page7 -> m_hWnd ))		page7 -> UpdateData( TRUE );

	if ( page1 -> m_strNFP1_ANDAT.IsEmpty())
		tempTime = time_t( 0 );
	else
	{
		text = page1 -> m_strNFP1_ANDAT;
		tempTime = text.GetDate();
	}

	// Seite 1
	if ( m_bEditIDE )
		m_strNFP1_IDE = page1 -> m_strNFP1_IDE;

	if ( 1 <= m_arrEigent.GetSize())
	{
		pSatz = (CEigentuemer*)m_arrEigent.GetAt(0);
		m_strNFP1_ENA   = pSatz -> m_NFP4_ENA;
		m_strNFP1_EAN   = pSatz -> m_NFP4_EAN;
		m_strNFP1_EPL   = pSatz -> m_NFP4_EPL;
		m_strNFP1_EOR   = pSatz -> m_NFP4_EOR;
	}
	else
	{
		m_strNFP1_ENA   = "";
		m_strNFP1_EAN   = "";
		m_strNFP1_EPL   = "";
		m_strNFP1_EOR   = "";
	}

//	m_strNFP1_ORT   = page1 -> m_strNFP1_ORT;
	m_strNFP1_FLU   = page1 -> m_strNFP1_FLU;
	m_rNFP1_BAR     = page1 -> m_iNFP1_BAR + 1;
	m_rNFP1_GFZ     = page1 -> m_rNFP1_GFZ;
	m_rNFP1_BMZ     = page1 -> m_rNFP1_BMZ;
	m_rNFP1_VGZ     = page1 -> m_rNFP1_VGZ;
	m_rNFP1_GUZ     = page1 -> m_rNFP1_GUZ;
	m_strNFP1_FST   = page1 -> m_strNFP1_FST;
	m_rNFP1_KAT     = page1 -> m_rNFP1_KAT;
	m_tNFP1_ANDAT   = tempTime;

	// Seite 4
	m_rAWE = page4 -> m_rAWE;
	m_rAEW = page4 -> m_rAEW;
	m_rEGW = page4 -> m_rEGW;
	m_bZE = page4 -> m_bZE;
	m_bSGR = page4 -> m_bSGR;
	m_rFS = page4 -> m_rFS;
	m_bSGT = page4 -> m_bSGT;
	m_bKK = page4 -> m_bKK;
	m_rFKK = page4 -> m_rFKK;
	m_bKKT = page4 -> m_bKKT;
	m_bVF = page4 -> m_bVF;
	m_bK = page4 -> m_bK;
	m_bFZ = page4 -> m_bFZ;
	m_bFE = page4 -> m_bFE;
	m_bFZE = page4 -> m_bFZE;
	m_strBem = page4 -> m_strSonst;
	if ( page4 -> m_bANNWL )	m_strANNWL = "Y";
	else						m_strANNWL = "N";

	// Seite 5
	page5 -> m_parrPG1GB = &m_arrPG1GB;

	// Seite 6
//	m_strBem = page6 -> m_strBem;

	// Seite 7 (Eigentümer)
	page7 -> m_parrEigent = &m_arrEigent;
	m_bMiteigent = page7 -> m_bMiteigentum;
}

void CErfassPrivDlg::RewriteGeb()
{
	CSetNF_PG1GB	pg1gb;
	CPG1GBSatz		*pSatz;
	short			i;

	pg1gb.Open();
	if ( !pg1gb.CanUpdate() || !pg1gb.CanAppend())
	{
		AfxMessageBox( "Änderungen an der Gebäude-Datenbank nicht möglich!" );
		pg1gb.Close();
		return;
	}

	// Zuerst alle alten Einträge löschen!
	if ( !pg1gb.IsEOF() || !pg1gb.IsEOF())
	{
		pg1gb.MoveFirst();
		while ( !pg1gb.IsEOF())
		{
			if ( pg1gb.m_NFP1_IDE == m_strNFP1_IDE )
				pg1gb.Delete();
			pg1gb.MoveNext();
		}
	}

	// Dann komplett anfügen
	if ( m_arrPG1GB.GetSize() > 0 )
	{
		for ( i = 0; i < m_arrPG1GB.GetSize(); i++ )
		{
			pSatz = (CPG1GBSatz*)m_arrPG1GB.GetAt( i );

			pg1gb.AddNew();
			pg1gb.m_NFP1_IDE = pSatz -> m_NFP1_IDE;
			pg1gb.m_NFP1_ANL = pSatz -> m_NFP1_ANL;
			pg1gb.m_NFP1_GFL = pSatz -> m_NFP1_GFL;
			pg1gb.m_NFP1_GNR = pSatz -> m_NFP1_GNR;
			pg1gb.m_NFP1_HOH = pSatz -> m_NFP1_HOH;
			pg1gb.m_NFP1_VOL = pSatz -> m_NFP1_VOL;
			pg1gb.Update();
		}
	}
}

void CErfassPrivDlg::RewriteDT()
{
	CSetNF_PG2D		pg2d;
	CPG2DSatz		*pSatz;
	CString			text;
	short			i;

	pg2d.Open();
	if ( !pg2d.CanUpdate() || !pg2d.CanAppend())
	{
		AfxMessageBox( "Änderungen an der Dachflächen-Datenbank nicht möglich!" );
		pg2d.Close();
		return;
	}

	// Zuerst alle alten Einträge löschen!
	if ( !pg2d.IsEOF() || !pg2d.IsEOF())
	{
		pg2d.MoveFirst();
		while ( !pg2d.IsEOF())
		{
			if ( pg2d.m_NFP2_IDE == m_strNFP1_IDE )
				pg2d.Delete();
			pg2d.MoveNext();
		}
	}

	// Dann komplett anfügen
	if ( m_arrPG2D.GetSize() > 0 )
	{
		for ( i = 0; i < m_arrPG2D.GetSize(); i++ )
		{
			pSatz = (CPG2DSatz*)m_arrPG2D.GetAt( i );

			pg2d.AddNew();
			pg2d.m_NFP2_IDE = pSatz -> m_NFP2_IDE;
			pg2d.m_NFP2_ABF = pSatz -> m_NFP2_ABF;
//			pg2d.m_NFP2_ANS = pSatz -> m_NFP2_ANS;
			if ( TestYES( pSatz -> m_NFP2_ANS ))	text = "Y";
			else									text = "N";
			pg2d.m_NFP2_ANS = text;
			pg2d.m_NFP2_FLG = pSatz -> m_NFP2_FLG;
			pg2d.m_NFP2_FLN = pSatz -> m_NFP2_FLN;
			pg2d.Update();
		}
	}
}

void CErfassPrivDlg::RewriteVF()
{
	CSetNF_PG2H		pg2h;
	CPG2DSatz		*pSatz;
	CString			text;
	short			i;

	pg2h.Open();
	if ( !pg2h.CanUpdate() || !pg2h.CanAppend())
	{
		AfxMessageBox( "Änderungen an der Hofflächen-Datenbank nicht möglich!" );
		pg2h.Close();
		return;
	}

	// Zuerst alle alten Einträge löschen!
	if ( !pg2h.IsEOF() || !pg2h.IsEOF())
	{
		pg2h.MoveFirst();
		while ( !pg2h.IsEOF())
		{
			if ( pg2h.m_NFP2_IDE == m_strNFP1_IDE )
				pg2h.Delete();
			pg2h.MoveNext();
		}
	}

	// Dann komplett anfügen
	if ( m_arrPG2H.GetSize() > 0 )
	{
		for ( i = 0; i < m_arrPG2H.GetSize(); i++ )
		{
			pSatz = (CPG2DSatz*)m_arrPG2H.GetAt( i );

			pg2h.AddNew();
			pg2h.m_NFP2_IDE = pSatz -> m_NFP2_IDE;
			pg2h.m_NFP2_ABF = pSatz -> m_NFP2_ABF;
//			pg2h.m_NFP2_ANS = pSatz -> m_NFP2_ANS;
			if ( TestYES( pSatz -> m_NFP2_ANS ))	text = "Y";
			else									text = "N";
			pg2h.m_NFP2_ANS = text;
			pg2h.m_NFP2_FLG = pSatz -> m_NFP2_FLG;
			pg2h.m_NFP2_FLN = pSatz -> m_NFP2_FLN;
			pg2h.Update();
		}
	}
}

void CErfassPrivDlg::RewriteEig()
{
//	CSetNF_PG4		pg4;
	CEigentuemer	*pSatz;
	CString			filter;
	CString			sql;
	short			i;

	filter = "(NFP4_IDE = '";
	filter += m_strNFP1_IDE;
	filter += "')";

	if ( g_pNF_PG4 == NULL )	g_pNF_PG4 = new CSetNF_PG4( g_pDatabase );
	ASSERT( g_pNF_PG4 );

	sql = "DELETE FROM NF_PG4 WHERE NF_PG4.NFP4_IDE = '";
	sql += m_strNFP1_IDE;
	sql += "';";
	g_pDatabase -> ExecuteSQL( sql );

	g_pNF_PG4 -> m_strFilter = filter;
	if ( g_pNF_PG4 -> IsOpen())
		g_pNF_PG4 -> Requery();
	else
		g_pNF_PG4 -> Open();

	if ( !g_pNF_PG4 -> CanUpdate() || !g_pNF_PG4 -> CanAppend())
	{
		AfxMessageBox( "Änderungen an der Eigentümer-Datenbank nicht möglich!" );
		g_pNF_PG4 -> Close();
		return;
	}

	// Zuerst alle alten Einträge löschen!
//	if ( !g_pNF_PG4 -> IsEOF() || !g_pNF_PG4 -> IsBOF())
//	{
//		g_pNF_PG4 -> MoveFirst();
//		while ( !g_pNF_PG4 -> IsEOF())
//		{
//			if ( g_pNF_PG4 -> m_NFP4_IDE == m_strNFP1_IDE )
//			g_pNF_PG4 -> Delete();
//			g_pNF_PG4 -> MoveNext();
//		}
//	}

	// Dann komplett anfügen
	if ( m_arrEigent.GetSize() > 0 )
	{
		for ( i = 0; i < m_arrEigent.GetSize(); i++ )
		{
			pSatz = (CEigentuemer*)m_arrEigent.GetAt( i );

			g_pNF_PG4 -> AddNew();
			g_pNF_PG4 -> m_NFP4_IDE = m_strNFP1_IDE;
			g_pNF_PG4 -> m_NFP4_KASS = pSatz -> m_NFP4_KASS;
			g_pNF_PG4 -> m_NFP4_BDM  = pSatz -> m_NFP4_BDM;
			g_pNF_PG4 -> m_NFP4_EAN  = pSatz -> m_NFP4_EAN;
			g_pNF_PG4 -> m_NFP4_ENA  = pSatz -> m_NFP4_ENA;
			g_pNF_PG4 -> m_NFP4_EOR  = pSatz -> m_NFP4_EOR;
			g_pNF_PG4 -> m_NFP4_EPL  = pSatz -> m_NFP4_EPL;
			g_pNF_PG4 -> m_NFP4_HER  = pSatz -> m_NFP4_HER;
			g_pNF_PG4 -> m_NFP4_TFL  = pSatz -> m_NFP4_TFL;
			g_pNF_PG4 -> m_NFP4_PN   = pSatz -> m_NFP4_PN;
			g_pNF_PG4 -> m_NFP4_PZ   = pSatz -> m_NFP4_PZ;
			g_pNF_PG4 -> m_NFP4_NR   = pSatz -> m_NFP4_NR;
			g_pNF_PG4 -> Update();
		}
	}
	g_pNF_PG4 -> Requery();
}
