//	Print Anlage

#include "StdAfx.h"
#include "PrintAnlage.h"
#include "GbmTrias.h"

#include "SetVorlagen.h"

#include <AfxPriv.h>

extern CPtrArray			*g_pArrONr;
extern CStringArray			*g_pArrIDE;
extern CGbmTRiASExtension	*g_pExt;
static BOOL g_bRenderingInProgres;

extern CStrasseSet* g_pSetStrasse;
extern COrteSet* g_pSetOrte;
extern CTriDBSet* g_pSetTriDB;
extern CSetNF_PG1* g_pNF_PG1;
extern CSetNF_PG4* g_pNF_PG4;
extern CDatabase* g_pDatabase;

extern CSetVorlagen	*g_pSetVorlagen;

///////////////////////////////////////////////////////////////////////
CPrintAnlage1::CPrintAnlage1( const char* ide, long enr )
{
	ASSERT( AfxIsValidString( ide ));
	m_strIDE = ide;
	m_bInitialisiert = FALSE;
	m_cKennung = '1';
	m_lENR = enr;

	m_iBAR  = 0;
	m_rGFZ  = 0;
	m_rBMZ  = 0;
	m_rVGZ  = 0;
	m_rGUZ  = 0;
	m_rGEF  = 0;
	m_rGEFS = 0;
	m_rKAT  = 0;
	m_rAGG  = 0;
	m_rAGGS = 0;
	m_rTB   = 0;

	m_lrTRiAS.left   = -1L;
	m_lrTRiAS.top    = -1L;
	m_lrTRiAS.right  = -1L;
	m_lrTRiAS.bottom = -1L;

	m_hMetaFile = NULL;
	m_sizeTopLeftOffset.cx = 0;
	m_sizeTopLeftOffset.cy = 0;
	m_bNeuerOffset = TRUE;

	m_strViewName = "Druckblatt 1";
}

CPrintAnlage1::~CPrintAnlage1()
{
	GEBAEUDE*	pG;

	for ( int i = 0; i < m_arrGebaeude.GetSize(); i++ )
	{
		pG = (GEBAEUDE*)m_arrGebaeude[i];
		delete pG;
	}
	m_arrGebaeude.RemoveAll();

	if ( m_hMetaFile )	DeleteEnhMetaFile( m_hMetaFile );
	m_hMetaFile = NULL;
}

BOOL CPrintAnlage1::Init()
{
	if ( m_bInitialisiert )		return TRUE;
	m_bInitialisiert = TRUE;

	CBasisSatz*		pS;
	CEigentuemer*	pE;

try {
	pS = m_pNF_PG1 -> FindIDE( m_strIDE );

	m_strPRO = m_pNF_PG1 -> Projekt();
	if ( pS )
	{
		m_strStrasse = m_pStrassen -> Strasse( m_strIDE );
//		m_strENA = pS -> Besitzer();
//		m_strEAN = pS -> Strasse();
//		m_strEPL = pS -> PLZ();
//		m_strEOR = pS -> Ort();
		m_strORT = m_pOrte -> Ort( m_strIDE );
		m_strFLU = pS -> Flur();
		m_strFST = pS -> Flurstk();
		m_strTIEF = ( pS -> TIEF() ? "N" : "Y" );
		m_iBAR   = (int)pS -> BAR();
		m_rGFZ   = pS -> GFZ();
		m_rBMZ   = pS -> BMZ();
		m_rGUZ   = pS -> GUZ();
		m_rGEF   = pS -> GEF();
		m_rGEFS  = pS -> GEFS();
		m_rKAT   = pS -> KAT();
		m_rAGG   = pS -> AGG();
		m_rAGGS  = pS -> AGGS();
		m_rVGZ   = pS -> VGZ();
		m_strANDAT = pS -> AnDatum();
		m_strANNWL = pS -> AnNWL();
	}

	pE = g_pNF_PG4 -> FindEigentuemer( m_strIDE, m_lENR );
	if ( pE )
	{
		m_strENA = pE -> m_NFP4_ENA;
		m_strEAN = pE -> m_NFP4_EAN;
		m_strEPL = pE -> m_NFP4_EPL;
		m_strEOR = pE -> m_NFP4_EOR;
	}
	m_rTB = TB( m_strIDE );
} catch(...) {
	AfxMessageBox( "Zu wenig Speicher! (Pos.01.1)" );
}

	CPG1GBArray	arrPG1GB;
	CPG1GBSatz	*pGBS;
	GEBAEUDE	*pG;
	CString		text;
	short		i;

try {
	m_pNF_PG1GB -> InitArray( m_strIDE, &arrPG1GB );

	for ( i = 0; i < arrPG1GB.GetSize(); i++ )
	{
		pGBS = (CPG1GBSatz*)arrPG1GB[i];
		pG = new GEBAEUDE;
		ASSERT( pG );
		pG -> m_rNr = pGBS -> m_NFP1_GNR;
		pG -> m_bVa = TestYES( pGBS -> m_NFP1_ANL );
		pG -> m_rFl = pGBS -> m_NFP1_GFL;
		pG -> m_rGh = pGBS -> m_NFP1_HOH;
		pG -> m_rVz = pGBS -> m_NFP1_VOL;
		m_arrGebaeude.SetAtGrow( i, (void*)pG );
	}
	arrPG1GB.Clear();

	double	max = 0;
	GEBAEUDE		*gbsatz;

	for ( i = 0; i < m_arrGebaeude.GetSize(); i++ )
	{
		gbsatz = (GEBAEUDE*)m_arrGebaeude.GetAt( i );
		if ( gbsatz -> m_bVa )
		{
			if (( gbsatz -> m_rVz != 0 ) && ( gbsatz -> m_rVz > max ))
				max = gbsatz -> m_rVz;
			if (( gbsatz -> m_rGh != 0 ) && ( gbsatz -> m_rGh > max ))
				max = gbsatz -> m_rGh;
		}
	}
} catch(...) {
	AfxMessageBox( "Zu wenig Speicher! (Pos.02.1)" );
}

//	if ( max != 0 )		m_rVGZ = max;
	text = GetAnsichtName( "1" );
	if ( !text.IsEmpty())
		m_strViewName = text;

	return TRUE;
}	// Init

void CPrintAnlage1::Print( CDC* pDC )
{
	CxString	text;
	Init();

	CRect rcDest;

	// get size of printer page (in pixels)
	int cxPage = pDC->GetDeviceCaps(HORZRES);
	int cyPage = pDC->GetDeviceCaps(VERTRES);
	// get printer pixels per inch
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

// Hauptrahmen
	rcDest.top = cyInch / 2;				// oben 1/2 Zoll
	rcDest.bottom = cyPage - cyInch / 2;	// unten ebenso
	rcDest.left = cxInch * 3 / 4;			// links 3/4 Zoll
	rcDest.right = cxPage - cxInch / 2;		// rechts 1/2 Zoll
	pDC -> Rectangle( rcDest );

// Rahmen für die Karte
	rcDest.top = cyInch * 2;				// oben 2 Zoll
	rcDest.left = cxInch * 5 / 4;
	rcDest.right = cxPage - cxInch;
	rcDest.bottom = (int)(cyPage / 2);

	int xDiff, yDiff;

	xDiff = cxInch / 20;
	yDiff = cyInch / 20;

	CRect   rect = rcDest;
	rect.top -= yDiff - xDiff;
	rect.bottom += yDiff + xDiff;
	rect.left -= xDiff - xDiff;
	rect.right += xDiff + xDiff;
	for ( short i = 0; i < xDiff; i +=2 )
	{
		pDC -> Rectangle( rect );
		rect.top -= 2;
		rect.bottom -= 2;
		rect.left -= 2;
		rect.right -= 2;
	}
	rect.top    += xDiff;
	rect.bottom += xDiff;
	rect.left   += xDiff;
	rect.right  += xDiff;
//	pDC -> Rectangle( rect );
//	pDC -> Rectangle( rcDest );

	rcDest.top    += 2;
	rcDest.bottom -= 2;
	rcDest.left   += 2;
	rcDest.right  -= 2;

	CSize   size;
	CFont   *pOldFont = NULL;

	pOldFont = pDC -> SelectObject( m_pFntNormal );

	text = "E";
	size = pDC -> GetTextExtent( text, text.GetLength());
	int dy = size.cy * 12 / 10;

	int spalte0  = cxInch * 5 / 4;
	int spalte1  = spalte0 + cxInch/2;
	int spalte2  = spalte0 + cxInch;
	int spalte3  = spalte1 + cxInch;
	int spalte4  = spalte2 + cxInch;
	int spalte5  = spalte3 + cxInch;
	int spalte6  = spalte4 + cxInch;
	int spalte7  = spalte5 + cxInch;
	int spalte8  = spalte6 + cxInch;
	int spalte9  = spalte7 + cxInch;
	int spalte10 = spalte8 + cxInch;
	int spalte11 = spalte9 + cxInch;
	int spalte12 = spalte10 + cxInch;
	int spalte13 = spalte11 + cxInch;
	
	int zeile0 = cyInch/2 + dy;

// Kopftexte

	text = "Erfassungsblatt \"Private Grundstücke\"";
	PrintText( pDC, m_pFntUeberschrift, spalte0, zeile0, text );

	text = "Blatt 1";
//      size = pDC -> GetTextExtent( text, text.GetLength());
//      pDC -> SelectObject( m_pFntFett );
//      pDC -> TextOut( cxPage - cxInch/2 - size.cx, cyInch / 2 + dy, text );
	PrintText( pDC, m_pFntFett, spalte11, zeile0, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 2*dy, "Projekt:" );
//	text = "AV \"";
	text = m_strPRO;
//	text += '"';
	PrintText( pDC, NULL, spalte1, zeile0 + 2*dy, text );

	CTime   date = CTime::GetCurrentTime();
	text.Empty();
	text.printf( "%d.%d.%d", date.GetDay(), date.GetMonth(), date.GetYear());
	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 2*dy, "Datum:" );
	PrintText( pDC, NULL, spalte7, zeile0 + 2*dy, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 4*dy, "Identifikationsnummer:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 4*dy, m_strIDE );

//      PrintText( pDC, m_pFntFett, spalte5, zeile0 + 6*dy, "Stra_e:" );
//      PrintText( pDC, NULL, spalte6, zeile0 + 6*dy, Str( m_strIDE ));

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 6*dy, "Straße:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 6*dy, m_strStrasse );


// zeile0 korrigieren!!
	zeile0 = (int)( cyPage / 2 ) - 32*dy;

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 33*dy, "Eigentümer(Anschrift):" );
	PrintText( pDC, NULL, spalte3, zeile0 + 33*dy, "Name:" );
	PrintText( pDC, NULL, spalte6, zeile0 + 33*dy, m_strENA );

	PrintText( pDC, NULL, spalte3, zeile0 + 34*dy, "Straße/Hausnummer:" );
	PrintText( pDC, NULL, spalte6, zeile0 + 34*dy, m_strEAN );

	PrintText( pDC, NULL, spalte3, zeile0 + 35*dy, "PLZ/Ort:" );
	PrintText( pDC, NULL, spalte6, zeile0 + 35*dy, m_strEPL );
	PrintText( pDC, NULL, spalte7, zeile0 + 35*dy, m_strEOR );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 36*dy, "Gemeinde und Ortslage:" );
	PrintText( pDC, NULL, spalte6, zeile0 + 36*dy, m_strORT );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 37*dy, "Flur:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 37*dy, m_strFLU );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 38*dy, "Flurstücke:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 38*dy, m_strFST );

	PrintText( pDC, NULL, spalte0, zeile0 + 40*dy, "Gebäude-" );
	PrintText( pDC, NULL, spalte0, zeile0 + 41*dy, "nummer" );

	PrintText( pDC, NULL, spalte2, zeile0 + 40*dy, "Grund-" );
	PrintText( pDC, NULL, spalte2, zeile0 + 41*dy, "flächen" );

	PrintText( pDC, NULL, spalte4, zeile0 + 40*dy, "Vollgeschoß-" );
	PrintText( pDC, NULL, spalte4, zeile0 + 41*dy, "zahl/Wohnbeb." );

	PrintText( pDC, NULL, spalte6, zeile0 + 40*dy, "Gebäudehöhe" );
	PrintText( pDC, NULL, spalte6, zeile0 + 41*dy, "Gewerbe" );

	PrintText( pDC, NULL, spalte8, zeile0 + 40*dy, "veranlagbar" );

	short	in, n = m_arrGebaeude.GetSize();
	if ( n > 10 )
	{
		n = 9;
		PrintText( pDC, NULL, spalte0, zeile0 + 51*dy, "..." );
	}
	GEBAEUDE	*gbsatz;
	for ( in = 0; in < n; in++ )
	{
		gbsatz = (GEBAEUDE*)m_arrGebaeude[in];
		PrintTextF0( pDC, NULL, spalte1, zeile0 + (42+in)*dy, gbsatz -> m_rNr );
		PrintTextF2( pDC, NULL, spalte3, zeile0 + (42+in)*dy, gbsatz -> m_rFl );
		PrintTextF2( pDC, NULL, spalte5, zeile0 + (42+in)*dy, gbsatz -> m_rVz );
		PrintTextF2( pDC, NULL, spalte7, zeile0 + (42+in)*dy, gbsatz -> m_rGh );
		PrintCheckBox( pDC, spalte9, zeile0 + (42+in)*dy, dy/2, gbsatz -> m_bVa );
	}

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 52*dy, "Herstellungsbeitrag:" );
//  if m_strBAR = 1
	PrintCheckBox( pDC, spalte4, zeile0+52*dy, dy/2, (m_iBAR == 1 ));

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 53*dy, "Erneuerungsbeitrag:" );
//  if m_strBAR = 2
	PrintCheckBox( pDC, spalte4, zeile0+53*dy, dy/2, (m_iBAR == 2 ));

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 54*dy, "Verbesserungsbeitrag:" );
//  if m_strBAR = 3
	PrintCheckBox( pDC, spalte4, zeile0+54*dy, dy/2, (m_iBAR == 3 ));

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 55*dy, "Erweiterungsbeitrag:" );
//  if m_strBAR = 4
	PrintCheckBox( pDC, spalte4, zeile0+55*dy, dy/2, (m_iBAR == 4 ));

	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 52*dy, "Unbebautes Grundstück:" );

	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 53*dy, "Geschoßflächenzahl:" );
	PrintTextF2( pDC, NULL, spalte11, zeile0 + 53*dy, m_rGFZ );

	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 54*dy, "Baumassenzahl:" );
	PrintTextF2( pDC, NULL, spalte11, zeile0 + 54*dy, m_rBMZ );

	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 55*dy, "Vollgeschoßzahl:" );
	PrintTextF2( pDC, NULL, spalte11, zeile0 + 55*dy, m_rVGZ );

	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 56*dy, "Grundflächenzahl:" );
	PrintTextF2( pDC, NULL, spalte11, zeile0 + 56*dy, m_rGUZ );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 58*dy, "Luftbildvermessene Fläche des Grundstücks (m²):" );
	PrintTextF2( pDC, NULL, spalte11, zeile0 + 58*dy, m_rGEFS );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 59*dy, "Gesamtfläche des Grundstücks laut Grundbuchamt (m²):" );
	PrintTextF2( pDC, NULL, spalte11, zeile0 + 59*dy, m_rKAT );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 60*dy, "Grundstücksfläche nach Tiefenbegrenzung (m²):" );
	PrintTextF2( pDC, NULL, spalte11, zeile0 + 60*dy, m_rAGGS );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 61*dy, "Tiefenbegrenzung bei (m):" );
	m_strTIEF.MakeUpper();
	if ( m_strTIEF != "N" )
	{
		PrintTextF2( pDC, NULL, spalte11, zeile0 + 61*dy, m_rTB );
	}

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 62*dy, "Anschlußdatum:" );
	PrintTextR( pDC, NULL, spalte11, zeile0 + 62*dy, m_strANDAT );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 63*dy, "Anschluß Niederschlagsentwässerung möglich:" );
	if ( !m_strANNWL.IsEmpty())
	{
		if ( TestYES( m_strANNWL ))
			PrintTextR( pDC, NULL, spalte11, zeile0 + 63*dy, "Ja" );
		else
			PrintTextR( pDC, NULL, spalte11, zeile0 + 63*dy, "Nein" );
	}

// nach dem letzten Text: Font zurücksetzen
	if ( pOldFont )		pDC -> SelectObject( pOldFont );

// Karte eindrucken (wenn vorhanden)
	if ( m_lONr < 0L )	m_lONr = GetObjNr( m_strIDE );

	BOOL	bNeedsPrepare = ( m_hMetaFile == NULL );

	if ( m_lONr > 0L )
	{
		if ( bNeedsPrepare )
		{
			SelectTRiASProject( GetProjectName( m_strIDE ));
			SelectTRiASView( m_strViewName );
			PrepareObjColor( m_lONr, TRUE );
		}
		RenderTRiASAusschnitt( pDC, "", m_lONr, m_lrTRiAS, &rcDest );
		if ( bNeedsPrepare )
			ResetObjColor( m_lONr, TRUE );
	}
	else
	{
		SelectTRiASProject( GetProjectName( m_strIDE ));
		m_lONr = GetObjNr( m_strIDE );
		if ( m_lONr > 0L )
		{
			SelectTRiASView( m_strViewName );
			PrepareObjColor( m_lONr, TRUE );
			RenderTRiASAusschnitt( pDC, "", m_lONr, m_lrTRiAS, &rcDest );
			ResetObjColor( m_lONr, TRUE );
		}
	}

}	// Print Anlage 1

///////////////////////////////////////////////////////////////////////
CPrintAnlage2::CPrintAnlage2( const char* ide, long enr )
{
	ASSERT( AfxIsValidString( ide ));
	m_strIDE = ide;
	m_bInitialisiert = FALSE;
	m_cKennung = '2';
	m_lENR = enr;

	m_lrTRiAS.left   = -1L;
	m_lrTRiAS.top    = -1L;
	m_lrTRiAS.right  = -1L;
	m_lrTRiAS.bottom = -1L;

	m_strViewName = "Druckblatt 2";
}

CPrintAnlage2::~CPrintAnlage2()
{
	FLAECHE*	pF;
	int			i;

	for ( i = 0; i < m_arrDFlaeche.GetSize(); i++ )
	{
		pF = (FLAECHE*)m_arrDFlaeche[i];
		delete pF;
	}
	m_arrDFlaeche.RemoveAll();

	for ( i = 0; i < m_arrHFlaeche.GetSize(); i++ )
	{
		pF = (FLAECHE*)m_arrHFlaeche[i];
		delete pF;
	}
	m_arrDFlaeche.RemoveAll();
}

BOOL CPrintAnlage2::Init()
{
	if ( m_bInitialisiert )		return TRUE;
	m_bInitialisiert = TRUE;

	CPG2DArray	arrPG2D;
	CPG2DSatz	*pDS;
	FLAECHE		*pF;
	CString		text;
	short		i;

try {
	m_strPRO = m_pNF_PG1 -> Projekt();
	m_pNF_PG2D -> InitArray( m_strIDE, &arrPG2D );
} catch(...) {
	AfxMessageBox( "Zu wenig Speicher! (Pos.01.2)" );
}

//	CBasisSatz*	pS;
	CEigentuemer*	pE;

try {
//	pS = m_pNF_PG1 -> FindIDE( m_strIDE );
	pE = g_pNF_PG4 -> FindEigentuemer( m_strIDE, m_lENR );
/*
	if ( pS != NULL )
	{
		m_strENA = pS -> Besitzer();
		m_strEAN = pS -> Strasse();
		m_strEPL = pS -> PLZ();
		m_strEOR = pS -> Ort();
	}
*/
	if ( pE != NULL )
	{
		m_strENA = pE -> m_NFP4_ENA;
		m_strEAN = pE -> m_NFP4_EAN;
		m_strEPL = pE -> m_NFP4_EPL;
		m_strEOR = pE -> m_NFP4_EOR;
	}
	for ( i = 0; i < arrPG2D.GetSize(); i++ )
	{
		pDS = (CPG2DSatz*)arrPG2D[i];
		pF = new FLAECHE;
		ASSERT( pF );
		pF -> m_strNr = pDS -> m_NFP2_FLN;
		pF -> m_bAns = TestYES( pDS -> m_NFP2_ANS );
		pF -> m_rFl  = pDS -> m_NFP2_FLG;
		pF -> m_rAbf = pDS -> m_NFP2_ABF;
		m_arrDFlaeche.SetAtGrow( i, (void*)pF );
	}
	arrPG2D.Clear();

	m_pNF_PG2H -> InitArray( m_strIDE, &arrPG2D );

	for ( i = 0; i < arrPG2D.GetSize(); i++ )
	{
		pDS = (CPG2DSatz*)arrPG2D[i];
		pF = new FLAECHE;
		ASSERT( pF );
		pF -> m_strNr = pDS -> m_NFP2_FLN;
		pF -> m_bAns = ( TestYES( pDS -> m_NFP2_ANS ));
		pF -> m_rFl  = pDS -> m_NFP2_FLG;
		pF -> m_rAbf = pDS -> m_NFP2_ABF;
		m_arrHFlaeche.SetAtGrow( i, (void*)pF );
	}
	arrPG2D.Clear();

	m_strStrasse = m_pStrassen -> Strasse( m_strIDE );
	m_strOrt = m_pOrte -> Ort( m_strIDE );
} catch(...) {
	AfxMessageBox( "Zu wenig Speicher! (Pos.02.2)" );
}

	text = GetAnsichtName( "2" );
	if ( !text.IsEmpty())
		m_strViewName = text;

	return TRUE;
}	// Init

void CPrintAnlage2::Print( CDC* pDC )
{
	CxString	text;
	Init();

	CRect	rcDest;

	// get size of printer page (in pixels)
	int cxPage = pDC->GetDeviceCaps(HORZRES);
	int cyPage = pDC->GetDeviceCaps(VERTRES);
	// get printer pixels per inch
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

// Hauptrahmen
	rcDest.top = cyInch / 2;				// oben 1/2 Zoll
	rcDest.bottom = cyPage - cyInch / 2;	// unten ebenso
	rcDest.left = cxInch * 3 / 4;			// links 3/4 Zoll
	rcDest.right = cxPage - cxInch / 2;		// rechts 1/2 Zoll
	pDC -> Rectangle( rcDest );

// Rahmen für die Karte
	rcDest.top = cyInch * 2;				// oben 2 Zoll
	rcDest.left = cxInch * 5 / 4;
	rcDest.right = cxPage - cxInch;
	rcDest.bottom = (int)(cyPage / 2);

	int xDiff, yDiff;

	xDiff = cxInch / 20;
	yDiff = cyInch / 20;

	CRect   rect = rcDest;
	rect.top -= yDiff - xDiff;
	rect.bottom += yDiff + xDiff;
	rect.left -= xDiff - xDiff;
	rect.right += xDiff + xDiff;
	for ( short i = 0; i < xDiff; i +=2 )
	{
		pDC -> Rectangle( rect );
		rect.top -= 2;
		rect.bottom -= 2;
		rect.left -= 2;
		rect.right -= 2;
	}

	CSize	size;
	CFont	*pOldFont;

	pOldFont = pDC -> SelectObject( m_pFntNormal );

	text = "E";
	size = pDC -> GetTextExtent( text, text.GetLength());
	int dy = size.cy * 12 / 10;

	int spalte0  = cxInch * 5 / 4;
	int spalte1  = spalte0 + cxInch/2;
	int spalte2  = spalte0 + cxInch;
	int spalte3  = spalte1 + cxInch;
	int spalte4  = spalte2 + cxInch;
	int spalte5  = spalte3 + cxInch;
	int spalte6  = spalte4 + cxInch;
	int spalte7  = spalte5 + cxInch;
	int spalte8  = spalte6 + cxInch;
	int spalte9  = spalte7 + cxInch;
	int spalte10 = spalte8 + cxInch;
	int spalte11 = spalte9 + cxInch;
	int spalte12 = spalte10 + cxInch;
	int spalte13 = spalte11 + cxInch;

	int zeile0 = cyInch/2 + dy;

// Kopftexte

	text = "Erfassungsblatt \"Private Grundstücke\"";
	PrintText( pDC, m_pFntUeberschrift, spalte0, zeile0, text );

	text = "Blatt 2";
	PrintText( pDC, m_pFntFett, spalte11, zeile0, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 2*dy, "Projekt:" );
	text = m_strPRO;
	PrintText( pDC, NULL, spalte1, zeile0 + 2*dy, text );

	CTime   date = CTime::GetCurrentTime();
	text.Empty();
	text.printf( "%d.%d.%d", date.GetDay(), date.GetMonth(), date.GetYear());
	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 2*dy, "Datum:" );
	PrintText( pDC, NULL, spalte7, zeile0 + 2*dy, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 4*dy, "Identifikationsnummer:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 4*dy, m_strIDE );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 6*dy, "Ort:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 6*dy, m_strOrt );
	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 7*dy, "Straße:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 7*dy, m_strStrasse );

//	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 33*dy, "Eigentümer(Anschrift):" );
//	PrintText( pDC, NULL, spalte3, zeile0 + 33*dy, "Name:" );
	PrintText( pDC, NULL, spalte7, zeile0 + 5*dy, m_strENA );

//	PrintText( pDC, NULL, spalte3, zeile0 + 34*dy, "Straße/Hausnummer:" );
	PrintText( pDC, NULL, spalte7, zeile0 + 6*dy, m_strEAN );

//	PrintText( pDC, NULL, spalte3, zeile0 + 35*dy, "PLZ/Ort:" );
	PrintText( pDC, NULL, spalte7, zeile0 + 7*dy, m_strEPL );
	PrintText( pDC, NULL, spalte8, zeile0 + 7*dy, m_strEOR );

// zeile0 korrigieren!!
	zeile0 = (int)( cyPage / 2 ) - 32*dy;

	PrintText( pDC, NULL, spalte0, zeile0 + 33*dy, "Flächen-" );
	PrintText( pDC, NULL, spalte0, zeile0 + 34*dy, "nummer" );

	PrintText( pDC, NULL, spalte1+dy, zeile0 + 33*dy, "Fläche" );

	PrintText( pDC, NULL, spalte3, zeile0 + 33*dy, "Abfluß-" );
	PrintText( pDC, NULL, spalte3, zeile0 + 34*dy, "beiwert" );

	PrintText( pDC, NULL, spalte4, zeile0 + 33*dy, "ange-" );
	PrintText( pDC, NULL, spalte4, zeile0 + 34*dy, "schlossen" );

	PrintText( pDC, NULL, spalte6, zeile0 + 33*dy, "Flächen-" );
	PrintText( pDC, NULL, spalte6, zeile0 + 34*dy, "nummer" );

	PrintText( pDC, NULL, spalte7+dy, zeile0 + 33*dy, "Fläche" );

	PrintText( pDC, NULL, spalte9, zeile0 + 33*dy, "Abfluß-" );
	PrintText( pDC, NULL, spalte9, zeile0 + 34*dy, "beiwert" );

	PrintText( pDC, NULL, spalte10, zeile0 + 33*dy, "ange-" );
	PrintText( pDC, NULL, spalte10, zeile0 + 34*dy, "schlossen" );

	PrintText( pDC, NULL, spalte0, zeile0 + 47*dy, "Flächen-" );
	PrintText( pDC, NULL, spalte0, zeile0 + 48*dy, "nummer" );

	PrintText( pDC, NULL, spalte1+dy, zeile0 + 47*dy, "Fläche" );

	PrintText( pDC, NULL, spalte3, zeile0 + 47*dy, "Abfluß-" );
	PrintText( pDC, NULL, spalte3, zeile0 + 48*dy, "beiwert" );

	PrintText( pDC, NULL, spalte4, zeile0 + 47*dy, "ange-" );
	PrintText( pDC, NULL, spalte4, zeile0 + 48*dy, "schlossen" );

	PrintText( pDC, NULL, spalte6, zeile0 + 47*dy, "Flächen-" );
	PrintText( pDC, NULL, spalte6, zeile0 + 48*dy, "nummer" );

	PrintText( pDC, NULL, spalte7+dy, zeile0 + 47*dy, "Fläche" );

	PrintText( pDC, NULL, spalte9, zeile0 + 47*dy, "Abfluß-" );
	PrintText( pDC, NULL, spalte9, zeile0 + 48*dy, "beiwert" );

	PrintText( pDC, NULL, spalte10, zeile0 + 47*dy, "ange-" );
	PrintText( pDC, NULL, spalte10, zeile0 + 48*dy, "schlossen" );

	short	in, n1, n = m_arrDFlaeche.GetSize();
	if ( n > 20 )
	{
		n = 19;
		PrintText( pDC, NULL, spalte6, zeile0 + 44*dy, "..." );
	}
	if ( n > 10 )	n1 = 10;
	else			n1 = n;

	FLAECHE		*d2satz;
	for ( in = 0; in < n1; in++ )
	{
		d2satz = (FLAECHE*)m_arrDFlaeche[in];
		PrintText( pDC, NULL, spalte0, zeile0 + (35+in)*dy, d2satz -> m_strNr );
		PrintTextF2( pDC, NULL, spalte2, zeile0 + (35+in)*dy, d2satz -> m_rFl );
		PrintTextF2( pDC, NULL, spalte4 - dy, zeile0 + (35+in)*dy, d2satz -> m_rAbf );
		PrintCheckBox( pDC, spalte4 + dy, zeile0 + (35+in)*dy, dy/2, d2satz -> m_bAns );
	}

	for ( in = 10; in < n; in++ )
	{
		d2satz = (FLAECHE*)m_arrDFlaeche[in];
		PrintText( pDC, NULL, spalte6, zeile0 + (25+in)*dy, d2satz -> m_strNr );
		PrintTextF2( pDC, NULL, spalte8, zeile0 + (25+in)*dy, d2satz -> m_rFl );
		PrintTextF2( pDC, NULL, spalte10 - dy, zeile0 + (25+in)*dy, d2satz -> m_rAbf );
		PrintCheckBox( pDC, spalte10 + dy, zeile0 + (25+in)*dy, dy/2, d2satz -> m_bAns );
	}

	n = m_arrHFlaeche.GetSize();
	if ( n > 20 )
	{
		n = 19;
		PrintText( pDC, NULL, spalte6, zeile0 + 58*dy, "..." );
	}
	if ( n > 10 )	n1 = 10;
	else			n1 = n;

	for ( in = 0; in < n1; in++ )
	{
		d2satz = (FLAECHE*)m_arrHFlaeche[in];
		PrintText( pDC, NULL, spalte0, zeile0 + (49+in)*dy, d2satz -> m_strNr );
		PrintTextF2( pDC, NULL, spalte2, zeile0 + (49+in)*dy, d2satz -> m_rFl );
		PrintTextF2( pDC, NULL, spalte4 - dy, zeile0 + (49+in)*dy, d2satz -> m_rAbf );
		PrintCheckBox( pDC, spalte4 + dy, zeile0 + (49+in)*dy, dy/2, d2satz -> m_bAns );
	}

	for ( in = 10; in < n; in++ )
	{
		d2satz = (FLAECHE*)m_arrHFlaeche[in];
		PrintText( pDC, NULL, spalte6, zeile0 + (39+in)*dy, d2satz -> m_strNr );
		PrintTextF2( pDC, NULL, spalte8, zeile0 + (39+in)*dy, d2satz -> m_rFl );
		PrintTextF2( pDC, NULL, spalte10 - dy, zeile0 + (39+in)*dy, d2satz -> m_rAbf );
		PrintCheckBox( pDC, spalte10 + dy, zeile0 + (39+in)*dy, dy/2, d2satz -> m_bAns );
	}

// nach dem letzten Text: Font zurücksetzen
	if ( pOldFont )		pDC -> SelectObject( pOldFont );

// Karte eindrucken (wenn vorhanden)
	if ( m_lONr < 0L )	m_lONr = GetObjNr( m_strIDE );
	if ( m_lONr > 0L )
	{
		SelectTRiASProject( GetProjectName( m_strIDE ));
		SelectTRiASView( m_strViewName );
		PrepareObjColor( m_lONr, TRUE );
		RenderTRiASAusschnitt( pDC, "", m_lONr, m_lrTRiAS, &rcDest );
		ResetObjColor( m_lONr, TRUE );
	}
	else
	{
		SelectTRiASProject( GetProjectName( m_strIDE ));
		m_lONr = GetObjNr( m_strIDE );
		if ( m_lONr > 0L )
		{
			SelectTRiASView( m_strViewName );
			PrepareObjColor( m_lONr, TRUE );
			RenderTRiASAusschnitt( pDC, "", m_lONr, m_lrTRiAS, &rcDest );
			ResetObjColor( m_lONr, TRUE );
		}
	}

}	// Print Anlage 2

///////////////////////////////////////////////////////////////////////
CPrintAnlage3::CPrintAnlage3( const char* ide, long enr )
{
	ASSERT( AfxIsValidString( ide ));
	m_strIDE = ide;
	m_bInitialisiert = FALSE;
	m_cKennung = '3';
	m_lENR = enr;

	m_rAWE = 0;
	m_rAEW = 0;
	m_rEW  = 0;
	m_bMOB = FALSE;
	m_bSAM = FALSE;
	m_rSAG = 0;
	m_bSAT = FALSE;
	m_bKK  = FALSE;
	m_rKKG = 0;
	m_bKKT = FALSE;
	m_bKKV = FALSE;
	m_bKKK = FALSE;
	m_bFZ  = FALSE;
	m_bFE  = FALSE;
	m_bFZE = FALSE;
}

CPrintAnlage3::~CPrintAnlage3()
{
}

BOOL CPrintAnlage3::Init()
{
	if ( m_bInitialisiert )		return TRUE;
	m_bInitialisiert = TRUE;

	CString		text;

	if ( m_pNF_PG3 -> Find( m_strIDE ))
	{
		m_bFE    = ( m_pNF_PG3 -> m_NFP3_FV == 1 );
		m_bFZ    = ( m_pNF_PG3 -> m_NFP3_FV == 2 );
		m_bFZE   = ( m_pNF_PG3 -> m_NFP3_FV == 3 );
		m_bKK    = TestYES( m_pNF_PG3 -> m_NFP3_KK );
		m_bKKK   = TestYES( m_pNF_PG3 -> m_NFP3_KKK );
		m_bKKT   = TestYES( m_pNF_PG3 -> m_NFP3_KKT );
		m_bKKV   = TestYES( m_pNF_PG3 -> m_NFP3_KKV );
		m_bMOB   = TestYES( m_pNF_PG3 -> m_NFP3_MOB );
		m_bSAM   = TestYES( m_pNF_PG3 -> m_NFP3_SAM );
		m_bSAT   = TestYES( m_pNF_PG3 -> m_NFP3_SAT );
		m_rAEW   = m_pNF_PG3 -> m_NFP3_AEW;
		m_rAWE   = m_pNF_PG3 -> m_NFP3_AWE;
		m_rEW    = m_pNF_PG3 -> m_NFP3_GW;
		m_rKKG   = m_pNF_PG3 -> m_NFP3_KKG;
		m_rSAG   = m_pNF_PG3 -> m_NFP3_SAG;
		m_strBem = m_pNF_PG3 -> m_NFP3_BEM;

	
	}
	m_strPRO = m_pNF_PG1 -> Projekt();

	text = GetAnsichtName( "3" );
	if ( !text.IsEmpty())
		m_strViewName = text;

	return TRUE;
}	// Init

void CPrintAnlage3::Print( CDC* pDC )
{
	CxString	text;
	Init();

	CRect rcDest;

	// get size of printer page (in pixels)
	int cxPage = pDC->GetDeviceCaps(HORZRES);
	int cyPage = pDC->GetDeviceCaps(VERTRES);
	// get printer pixels per inch
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

// Hauptrahmen
	rcDest.top = cyInch / 2;				// oben 1/2 Zoll
	rcDest.bottom = cyPage - cyInch / 2;	// unten ebenso
	rcDest.left = cxInch * 3 / 4;			// links 3/4 Zoll
	rcDest.right = cxPage - cxInch / 2;		// rechts 1/2 Zoll
	pDC -> Rectangle( rcDest );

	CSize		size;
	CFont		*pOldFont;

	pOldFont = pDC -> SelectObject( m_pFntNormal );

	text = "E";
	size = pDC -> GetTextExtent( text, text.GetLength());
	int dy = size.cy * 12 / 10;

	int spalte0  = cxInch * 5 / 4;
	int spalte1  = spalte0 + cxInch/2;
	int spalte2  = spalte0 + cxInch;
	int spalte3  = spalte1 + cxInch;
	int spalte4  = spalte2 + cxInch;
	int spalte5  = spalte3 + cxInch;
	int spalte6  = spalte4 + cxInch;
	int spalte7  = spalte5 + cxInch;
	int spalte8  = spalte6 + cxInch;
	int spalte9  = spalte7 + cxInch;
	int spalte10 = spalte8 + cxInch;
	int spalte11 = spalte9 + cxInch;
	int spalte12 = spalte10 + cxInch;
	int spalte13 = spalte11 + cxInch;

	int zeile0 = cyInch/2 + dy;

// Kopftexte

	text = "Erfassungsblatt \"Private Grundstücke\"";
	PrintText( pDC, m_pFntUeberschrift, spalte0, zeile0, text );

	text = "Blatt 3";
	PrintText( pDC, m_pFntFett, spalte11, zeile0, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 2*dy, "Projekt:" );
	text = m_strPRO;
	PrintText( pDC, NULL, spalte1, zeile0 + 2*dy, text );

	CTime   date = CTime::GetCurrentTime();
	text.Empty();
	text.printf( "%d.%d.%d", date.GetDay(), date.GetMonth(), date.GetYear());
	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 2*dy, "Datum:" );
	PrintText( pDC, NULL, spalte7, zeile0 + 2*dy, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 4*dy, "Identifikationsnummer:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 4*dy, m_strIDE );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 6*dy, "Anzahl Wohneinheiten auf dem Grundstück" );
	PrintTextF0( pDC, NULL, spalte8, zeile0 + 6*dy, m_rAWE );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 7*dy, "Anzahl Einwohner" );
	PrintTextF0( pDC, NULL, spalte8, zeile0 + 7*dy, m_rAEW );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 8*dy, "Anzahl Einwohnergleichwerte aus Gewerbe" );
	PrintTextF0( pDC, NULL, spalte8, zeile0 + 8*dy, m_rEW );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 10*dy, "Zentrale Entsorgung" );
	PrintCheckBox( pDC, spalte6, zeile0+10*dy, dy/2, m_bMOB );

	PrintText( pDC, m_pFntFett, spalte8, zeile0 + 12*dy, "Fassungs-" );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 13*dy, "Dezentrale Entsorgung" );

	PrintText( pDC, m_pFntFett, spalte8, zeile0 + 13*dy, "vermögen m²" );

	PrintText( pDC, NULL, spalte10, zeile0 + 13*dy, "n.d.a.a.R.d.T*" );

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 15*dy, "Sammelgrube" );
	PrintCheckBox( pDC, spalte6, zeile0+15*dy, dy/2, m_bSAM );
	PrintTextF2( pDC, NULL, spalte9, zeile0 + 15*dy, m_rSAG );
	PrintCheckBox( pDC, spalte10, zeile0+15*dy, dy/2, m_bSAT );

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 16*dy, "Kleinkläranlage" );
	PrintCheckBox( pDC, spalte6, zeile0+16*dy, dy/2, m_bKK );
	PrintTextF2( pDC, NULL, spalte9, zeile0 + 16*dy, m_rKKG );
	PrintCheckBox( pDC, spalte10, zeile0+16*dy, dy/2, m_bKKT );

	PrintText( pDC, m_pFntFett, spalte2, zeile0 + 17*dy, "Überlauf in Vorflut/Versickerung" );
	PrintCheckBox( pDC, spalte6, zeile0+17*dy, dy/2, m_bKKV );

	PrintText( pDC, m_pFntFett, spalte2, zeile0 + 18*dy, "Überlauf in Kanalnetz" );
	PrintCheckBox( pDC, spalte6, zeile0+18*dy, dy/2, m_bKKK );

	PrintText( pDC, NULL, spalte5, zeile0 + 20*dy, "*nach den allgemein anerkannten Regeln der Technik" );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 22*dy, "Frischwasserversorgung" );

	PrintText( pDC, m_pFntFett, spalte8, zeile0 + 22*dy, "Sonstige Angaben" );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 25*dy, "Zentral" );
	PrintCheckBox( pDC, spalte4, zeile0+25*dy, dy/2, m_bFZ );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 26*dy, "Eigenversorgung" );
	PrintCheckBox( pDC, spalte4, zeile0+26*dy, dy/2, m_bFE );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 27*dy, "Zentral und Eigenvers." );
	PrintCheckBox( pDC, spalte4, zeile0+27*dy, dy/2, m_bFZE );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 30*dy, "Bemerkungen" );
	PrintExtText( pDC, NULL, spalte1, zeile0 + 31*dy,
									spalte9, zeile0 +41*dy,
									m_strBem );

// nach dem letzten Text: Font zurücksetzen
	if ( pOldFont )		pDC -> SelectObject( pOldFont );

}	// Print Anlage 3

///////////////////////////////////////////////////////////////////////
CPrintAnlage4::CPrintAnlage4( const char* ide, long enr )
{
	ASSERT( AfxIsValidString( ide ));
	m_strIDE = ide;
	m_bInitialisiert = FALSE;
	m_cKennung = '4';
	m_lENR = enr;

	m_rBFL = 0;
	m_rKAT = 0;
	m_rAGG = 0;
	m_rTB  = 0;
	m_rVGZ = 0;
	m_iBAR = 0;

	m_lrTRiAS.left   = -1L;
	m_lrTRiAS.top    = -1L;
	m_lrTRiAS.right  = -1L;
	m_lrTRiAS.bottom = -1L;
}

CPrintAnlage4::~CPrintAnlage4()
{
}

BOOL CPrintAnlage4::Init()
{
	if ( m_bInitialisiert )		return TRUE;
	m_bInitialisiert = TRUE;

	CBasisSatz*		pS;
	CEigentuemer*	pE;

	pS = m_pNF_PG1 -> FindIDE( m_strIDE );

	m_strPRO = m_pNF_PG1 -> Projekt();
	if ( pS )
	{
		m_strStrasse = m_pStrassen -> Strasse( m_strIDE );
//		m_strENA = pS -> Besitzer();
//		m_strEAN = pS -> Strasse();
//		m_strEPL = pS -> PLZ();
//		m_strEOR = pS -> Ort();
		m_strOrt = m_pOrte -> Ort( m_strIDE );
		m_strFLU = pS -> Flur();
		m_strFST = pS -> Flurstk();
		m_iBAR   = (int)pS -> BAR();
		m_rBFL   = pS -> BFL();
//		m_rGFZ   = pS -> GFZ();
//		m_rBMZ   = pS -> BMZ();
//		m_rGUZ   = pS -> GUZ();
//		m_rGEF   = pS -> GEF();
		m_rKAT   = pS -> KAT();
		m_rAGG   = pS -> AGG();
		m_rGEF   = pS -> GEF();
//		m_rVGZ   = pS -> VGZ();
		m_rVGZ   = pS -> VOLLIE2() / 100.0;
		m_rTB    = pS -> TIEB();
//		m_strANDAT = pS -> AnDatum();
		if ( pS -> TIEF())	m_strTIEF = "N";
		else				m_strTIEF = "Y";
	}
//	m_rTB = TB( m_strIDE );
	pE = g_pNF_PG4 -> FindEigentuemer( m_strIDE, m_lENR );
	if ( pE )
	{
		m_strENA = pE -> m_NFP4_ENA;
		m_strEAN = pE -> m_NFP4_EAN;
		m_strEPL = pE -> m_NFP4_EPL;
		m_strEOR = pE -> m_NFP4_EOR;
	}

	CString		text = GetAnsichtName( "4" );
	if ( !text.IsEmpty())
		m_strViewName = text;

	return TRUE;
}	// Init

void CPrintAnlage4::Print( CDC* pDC )
{
	CxString	text;
	Init();

	CRect rcDest;

	// get size of printer page (in pixels)
	int cxPage = pDC->GetDeviceCaps(HORZRES);
	int cyPage = pDC->GetDeviceCaps(VERTRES);
	// get printer pixels per inch
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

// Hauptrahmen
	rcDest.top = cyInch / 2;				// oben 1/2 Zoll
	rcDest.bottom = cyPage - cyInch / 2;	// unten ebenso
	rcDest.left = cxInch * 3 / 4;			// links 3/4 Zoll
	rcDest.right = cxPage - cxInch / 2;		// rechts 1/2 Zoll
	pDC -> Rectangle( rcDest );

// Rahmen für die Karte
	rcDest.top = cyInch * 2;				// oben 2 Zoll
	rcDest.left = cxInch * 5 / 4;
	rcDest.right = cxPage - cxInch;
	rcDest.bottom = (int)(cyPage / 2);

	int xDiff, yDiff;

	xDiff = cxInch / 20;
	yDiff = cyInch / 20;

	CRect   rect = rcDest;
	rect.top -= yDiff - xDiff;
	rect.bottom += yDiff + xDiff;
	rect.left -= xDiff - xDiff;
	rect.right += xDiff + xDiff;
	for ( short i = 0; i < xDiff; i +=2 )
	{
		pDC -> Rectangle( rect );
		rect.top -= 2;
		rect.bottom -= 2;
		rect.left -= 2;
		rect.right -= 2;
	}

	CSize   size;
	CFont   *pOldFont;

	pOldFont = pDC -> SelectObject( m_pFntNormal );

	text = "E";
	size = pDC -> GetTextExtent( text, text.GetLength());
	int dy = size.cy * 12 / 10;

	int spalte0  = cxInch * 5 / 4;
	int spalte1  = spalte0 + cxInch/2;
	int spalte2  = spalte0 + cxInch;
	int spalte3  = spalte1 + cxInch;
	int spalte4  = spalte2 + cxInch;
	int spalte5  = spalte3 + cxInch;
	int spalte6  = spalte4 + cxInch;
	int spalte7  = spalte5 + cxInch;
	int spalte8  = spalte6 + cxInch;
	int spalte9  = spalte7 + cxInch;
	int spalte10 = spalte8 + cxInch;
	int spalte11 = spalte9 + cxInch;
	int spalte12 = spalte10 + cxInch;
	int spalte13 = spalte11 + cxInch;

	int zeile0 = cyInch/2 + dy;

// Kopftexte

	text = "Anlage zum Beitragsbescheid";
	PrintText( pDC, m_pFntUeberschrift, spalte0, zeile0, text );

	CTime   date = CTime::GetCurrentTime();
	text.Empty();
	text.printf( "%d.%d.%d", date.GetDay(), date.GetMonth(), date.GetYear());
	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 2*dy, "Datum:" );
	PrintText( pDC, NULL, spalte7, zeile0 + 2*dy, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 4*dy, "Identifikationsnummer:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 4*dy, m_strIDE );

// zeile0 korrigieren!!
	zeile0 = (int)( cyPage / 2 ) - 32*dy;

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 35*dy, "Eigentümer(Anschrift):" );
	PrintText( pDC, NULL, spalte3, zeile0 + 35*dy, "Name:" );
	PrintText( pDC, NULL, spalte6, zeile0 + 35*dy, m_strENA );

	PrintText( pDC, NULL, spalte3, zeile0 + 36*dy, "Straße/Hausnummer:" );
	PrintText( pDC, NULL, spalte6, zeile0 + 36*dy, m_strEAN );

	PrintText( pDC, NULL, spalte3, zeile0 + 37*dy, "PLZ/Ort:" );

	PrintText( pDC, NULL, spalte6, zeile0 + 37*dy, m_strEPL );
	PrintText( pDC, NULL, spalte7, zeile0 + 37*dy, m_strEOR );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 39*dy, "Gemeinde und Ortslage:" );
	text = m_strOrt;
//	if ( text.IsEmpty())    text = Ort( m_strIDE, FALSE );
	if ( text.IsEmpty())    text = m_strOrt;
	PrintText( pDC, NULL, spalte6, zeile0 + 39*dy, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 40*dy, "Straße/Hausnummer:" );
	text = m_strStrasse;
//	text += "  ";
//	text += Nr( m_strIDE );
	PrintText( pDC, NULL, spalte6, zeile0 + 40*dy, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 42*dy, "Flur:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 42*dy, m_strFLU );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 43*dy, "Flurstücke:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 43*dy, m_strFST );

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 45*dy, "Gesamtfläche des Grundstückes:" );
//	if (( m_rKAT < m_rGEF ) && ( m_rKAT > 0 ))
//		PrintTextF2( pDC, NULL, spalte10, zeile0 + 45*dy, m_rKAT );
//	else
		PrintTextF2( pDC, NULL, spalte10, zeile0 + 45*dy, m_rGEF );
	PrintText( pDC, NULL, spalte10, zeile0 + 45*dy, "  m²" );

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 46*dy, "Anrechenbare Grundstücksgröße:" );
//	if (( m_rKAT < m_rAGG ) && ( m_rKAT > 0 ))
//		PrintTextF2( pDC, NULL, spalte10, zeile0 + 46*dy, m_rKAT );
//	else
		PrintTextF2( pDC, NULL, spalte10, zeile0 + 46*dy, m_rAGG );
	PrintText( pDC, NULL, spalte10, zeile0 + 46*dy, "  m²" );

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 47*dy, "Tiefenbegrenzung:" );
	m_strTIEF.MakeUpper();
	if ( m_strTIEF != "N" )
	{
		PrintTextF2( pDC, NULL, spalte10, zeile0 + 47*dy, m_rTB );
		PrintText( pDC, NULL, spalte10, zeile0 + 47*dy, "  m" );
	}

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 48*dy, "Vollgeschoßzahl:" );
	PrintTextF2( pDC, NULL, spalte10, zeile0 + 48*dy, m_rVGZ );

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 50*dy, "Beitragsfläche:" );
	PrintTextF2( pDC, NULL, spalte10, zeile0 + 50*dy, m_rBFL );
	PrintText( pDC, NULL, spalte10, zeile0 + 50*dy, "  m²" );

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 52*dy, "Beitragsart:" );
	switch ( int( m_iBAR ))
	{
	case 1:
		PrintText( pDC, NULL, spalte6, zeile0 + 52*dy, "Herstellungsbeitrag" );
		break;
	case 2:
		PrintText( pDC, NULL, spalte6, zeile0 + 52*dy, "Erneuerungsbeitrag" );
		break;
	case 3:
	case 4:
		PrintText( pDC, NULL, spalte6, zeile0 + 52*dy, "Verbesserungsbeitrag" );
		break;
	case 5:
		PrintText( pDC, NULL, spalte6, zeile0 + 52*dy, "Erweiterungsbeitrag" );
		break;
	default:
		PrintText( pDC, NULL, spalte6, zeile0 + 52*dy, "?" );
		break;
	}


// nach dem letzten Text: Font zurncksetzen
	if ( pOldFont )		pDC -> SelectObject( pOldFont );

// Karte eindrucken (wenn vorhanden)
	if ( m_lONr < 0L )	m_lONr = GetObjNr( m_strIDE );
	if ( m_lONr > 0L )
	{
		SelectTRiASProject( GetProjectName( m_strIDE ));
		SelectTRiASView( m_strViewName );
		PrepareObjColor( m_lONr, TRUE );
		RenderTRiASAusschnitt( pDC, "", m_lONr, m_lrTRiAS, &rcDest );
		ResetObjColor( m_lONr, TRUE );
	}
	else
	{
		SelectTRiASProject( GetProjectName( m_strIDE ));
		m_lONr = GetObjNr( m_strIDE );
		if ( m_lONr > 0L )
		{
			SelectTRiASView( m_strViewName );
			PrepareObjColor( m_lONr, TRUE );
			RenderTRiASAusschnitt( pDC, "", m_lONr, m_lrTRiAS, &rcDest );
			ResetObjColor( m_lONr, TRUE );
		}
	}

}	// Print Anlage 4

///////////////////////////////////////////////////////////////////////
CPrintAnlage5::CPrintAnlage5( const char* ide, long enr )
{
	ASSERT( AfxIsValidString( ide ));
	m_strIDE = ide;
	m_bInitialisiert = FALSE;
	m_cKennung = '5';
	m_lENR = enr;

	m_lrTRiAS.left   = -1L;
	m_lrTRiAS.top    = -1L;
	m_lrTRiAS.right  = -1L;
	m_lrTRiAS.bottom = -1L;
}

CPrintAnlage5::~CPrintAnlage5()
{
	FLAECHE*	pF;
	int			i;

	for ( i = 0; i < m_arrDFlaeche.GetSize(); i++ )
	{
		pF = (FLAECHE*)m_arrDFlaeche[i];
		delete pF;
	}
	m_arrDFlaeche.RemoveAll();

	for ( i = 0; i < m_arrHFlaeche.GetSize(); i++ )
	{
		pF = (FLAECHE*)m_arrHFlaeche[i];
		delete pF;
	}
	m_arrDFlaeche.RemoveAll();
}

BOOL CPrintAnlage5::Init()
{
	if ( m_bInitialisiert )		return TRUE;
	m_bInitialisiert = TRUE;

//	CBasisSatz*	pS;
	CEigentuemer*	pE;

//	pS = m_pNF_PG1 -> FindIDE( m_strIDE );
	pE = g_pNF_PG4 -> FindEigentuemer( m_strIDE, m_lENR );

	m_strPRO = m_pNF_PG1 -> Projekt();
/*
	if ( pS )
	{
		m_strENA = pS -> Besitzer();
		m_strEAN = pS -> Strasse();
		m_strEPL = pS -> PLZ();
		m_strEOR = pS -> Ort();
	}
*/
	if ( pE )
	{
		m_strENA = pE -> m_NFP4_ENA;
		m_strEAN = pE -> m_NFP4_EAN;
		m_strEPL = pE -> m_NFP4_EPL;
		m_strEOR = pE -> m_NFP4_EOR;
	}

	CPG2DArray	arrPG2D;
	CPG2DSatz	*pDS;
	FLAECHE		*pF;
	CString		text;
	short		i;

	m_pNF_PG2D -> InitArray( m_strIDE, &arrPG2D );

	for ( i = 0; i < arrPG2D.GetSize(); i++ )
	{
		pDS = (CPG2DSatz*)arrPG2D[i];
		pF = new FLAECHE;
		ASSERT( pF );
		pF -> m_strNr = pDS -> m_NFP2_FLN;
		pF -> m_bAns = TestYES( pDS -> m_NFP2_ANS );
		pF -> m_rFl  = pDS -> m_NFP2_FLG;
		pF -> m_rAbf = pDS -> m_NFP2_ABF;
		m_arrDFlaeche.SetAtGrow( i, (void*)pF );
	}
	arrPG2D.Clear();

	m_pNF_PG2H -> InitArray( m_strIDE, &arrPG2D );

	for ( i = 0; i < arrPG2D.GetSize(); i++ )
	{
		pDS = (CPG2DSatz*)arrPG2D[i];
		pF = new FLAECHE;
		ASSERT( pF );
		pF -> m_strNr = pDS -> m_NFP2_FLN;
		pF -> m_bAns = TestYES( pDS -> m_NFP2_ANS );
		pF -> m_rFl  = pDS -> m_NFP2_FLG;
		pF -> m_rAbf = pDS -> m_NFP2_ABF;
		m_arrHFlaeche.SetAtGrow( i, (void*)pF );
	}
	arrPG2D.Clear();

	m_rDFlGes = 0;
	for ( i = 0; i < m_arrDFlaeche.GetSize(); i++ )
	{
		pF = (FLAECHE*)m_arrDFlaeche.GetAt( i );
		if ( pF -> m_bAns )
			m_rDFlGes += pF -> m_rFl;
	}

	m_rVFlGes = 0;
	for ( i = 0; i < m_arrHFlaeche.GetSize(); i++ )
	{
		pF = (FLAECHE*)m_arrHFlaeche.GetAt( i );
		if ( pF -> m_bAns )
			m_rVFlGes += pF -> m_rFl;
	}

	text = GetAnsichtName( "5" );
	if ( !text.IsEmpty())
		m_strViewName = text;

	return TRUE;
}	// Init

void CPrintAnlage5::Print( CDC* pDC )
{
	CxString	text;
	Init();

	CRect rcDest;

	// get size of printer page (in pixels)
	int cxPage = pDC->GetDeviceCaps(HORZRES);
	int cyPage = pDC->GetDeviceCaps(VERTRES);
	// get printer pixels per inch
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

// Hauptrahmen
	rcDest.top = cyInch / 2;				// oben 1/2 Zoll
	rcDest.bottom = cyPage - cyInch / 2;	// unten ebenso
	rcDest.left = cxInch * 3 / 4;			// links 3/4 Zoll
	rcDest.right = cxPage - cxInch / 2;		// rechts 1/2 Zoll
	pDC -> Rectangle( rcDest );

// Rahmen für die Karte
	rcDest.top = cyInch * 2;				// oben 2 Zoll
	rcDest.left = cxInch * 5 / 4;
	rcDest.right = cxPage - cxInch;
	rcDest.bottom = (int)(cyPage / 2);

	int xDiff, yDiff;

	xDiff = cxInch / 20;
	yDiff = cyInch / 20;

	CRect   rect = rcDest;
	rect.top -= yDiff - xDiff;
	rect.bottom += yDiff + xDiff;
	rect.left -= xDiff - xDiff;
	rect.right += xDiff + xDiff;
	for ( short i = 0; i < xDiff; i +=2 )
	{
		pDC -> Rectangle( rect );
		rect.top -= 2;
		rect.bottom -= 2;
		rect.left -= 2;
		rect.right -= 2;
	}

	CSize   size;
	CFont   *pOldFont;

	pOldFont = pDC -> SelectObject( m_pFntNormal );

	text = "E";
	size = pDC -> GetTextExtent( text, text.GetLength());
	int dy = size.cy * 12 / 10;

	int spalte0  = cxInch * 5 / 4;
	int spalte1  = spalte0 + cxInch/2;
	int spalte2  = spalte0 + cxInch;
	int spalte3  = spalte1 + cxInch;
	int spalte4  = spalte2 + cxInch;
	int spalte5  = spalte3 + cxInch;
	int spalte6  = spalte4 + cxInch;
	int spalte7  = spalte5 + cxInch;
	int spalte8  = spalte6 + cxInch;
	int spalte9  = spalte7 + cxInch;
	int spalte10 = spalte8 + cxInch;
	int spalte11 = spalte9 + cxInch;
	int spalte12 = spalte10 + cxInch;
	int spalte13 = spalte11 + cxInch;

	int zeile0 = cyInch/2 + dy;

// Kopftexte

	text = "Anlage zum Niederschlagswassergebührenbescheid";
	PrintText( pDC, m_pFntUeberschrift, spalte0, zeile0, text );

	CTime   date = CTime::GetCurrentTime();
	text.Empty();
	text.printf( "%d.%d.%d", date.GetDay(), date.GetMonth(), date.GetYear());
	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 2*dy, "Datum:" );
	PrintText( pDC, NULL, spalte7, zeile0 + 2*dy, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 4*dy, "Identifikationsnummer:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 4*dy, m_strIDE );

// zeile0 korrigieren!!
	zeile0 = (int)( cyPage / 2 ) - 32*dy;

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 35*dy, "Über das öffentliche Netz entwässerte Dachflächen" );

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 37*dy, "Über das öffentliche Netz entwässerte Hofflächen" );

	PrintText( pDC, NULL, spalte1, zeile0 + 40*dy, "Name:" );
	PrintText( pDC, NULL, spalte4, zeile0 + 40*dy, m_strENA );

	PrintText( pDC, NULL, spalte1, zeile0 + 41*dy, "Straße/Hausnummer:" );
	PrintText( pDC, NULL, spalte4, zeile0 + 41*dy, m_strEAN );

	PrintText( pDC, NULL, spalte1, zeile0 + 42*dy, "PLZ/Ort:" );
	PrintText( pDC, NULL, spalte4, zeile0 + 42*dy, m_strEPL );
	PrintText( pDC, NULL, spalte5, zeile0 + 42*dy, m_strEOR );

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 45*dy, "Entwässerte Dachfläche:" );
	PrintTextF2( pDC, NULL, spalte7, zeile0 + 45*dy, m_rDFlGes );
	PrintText( pDC, NULL, spalte7, zeile0 + 45*dy, "  m²" );

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 47*dy, "Entwässerte Hoffläche:" );
	PrintTextF2( pDC, NULL, spalte7, zeile0 + 47*dy, m_rVFlGes );
	PrintText( pDC, NULL, spalte7, zeile0 + 47*dy, "  m²" );

// nach dem letzten Text: Font zurücksetzen
	if ( pOldFont )		pDC -> SelectObject( pOldFont );

// Karte eindrucken (wenn vorhanden)
	if ( m_lONr < 0L )	m_lONr = GetObjNr( m_strIDE );
	if ( m_lONr > 0L )
	{
		SelectTRiASProject( GetProjectName( m_strIDE ));
		SelectTRiASView( m_strViewName );
		PrepareObjColor( m_lONr, FALSE );
		RenderTRiASAusschnitt( pDC, "", m_lONr, m_lrTRiAS, &rcDest );
		ResetObjColor( m_lONr, FALSE );
	}
	else
	{
		SelectTRiASProject( GetProjectName( m_strIDE ));
		m_lONr = GetObjNr( m_strIDE );
		if ( m_lONr > 0L )
		{
			SelectTRiASView( m_strViewName );
			PrepareObjColor( m_lONr, FALSE );
			RenderTRiASAusschnitt( pDC, "", m_lONr, m_lrTRiAS, &rcDest );
			ResetObjColor( m_lONr, FALSE );
		}
	}

	// Legende!
	CBrush          brush1, brush2;
	CBrush          *oldBrush = NULL;
	CPen            pen1, pen2;
	CPen            *oldPen = NULL;
	short           hatch;
	COLORREF        color;

	text = "2";
	text += m_strIDE;

	color = GetLegendColor( 1, text );
	if (( hatch = GetLegendHatch( 1, text )) < 0 )
		brush1.CreateSolidBrush( color );
	else
		brush1.CreateHatchBrush( hatch, color );
//	pen1.CreatePen( PS_SOLID, 0, color );
	oldBrush = pDC -> SelectObject( &brush1 );
//	oldPen = pDC -> SelectObject( &pen1 );
	rcDest.top = zeile0 + 35*dy;
	rcDest.left = spalte7;
	rcDest.right = spalte8;
	rcDest.bottom = zeile0 + 36*dy;
	pDC -> Rectangle( rcDest );

	color = GetLegendColor( 2, text );
	if (( hatch = GetLegendHatch( 2, text )) < 0 )
		brush2.CreateSolidBrush( color );
	else
		brush2.CreateHatchBrush( hatch, color );
//	pen2.CreatePen( PS_SOLID, 0, color );
	pDC -> SelectObject( &brush2 );
//	pDC -> SelectObject( &pen2 );
	rcDest.top = zeile0 + 37*dy;
	rcDest.bottom = zeile0 + 38*dy;
	pDC -> Rectangle( rcDest );

	if ( oldBrush )
		pDC -> SelectObject( oldBrush );
	if ( oldPen )
		pDC -> SelectObject( oldPen );

}	// Print Anlage 5

///////////////////////////////////////////////////////////////////////
CPrintAnlage6::CPrintAnlage6( const char* ide, long enr )
{
	ASSERT( AfxIsValidString( ide ));
	m_strIDE = ide;
	m_bInitialisiert = FALSE;
	m_cKennung = '6';
	m_lENR = enr;

	m_iART = 0;
	m_iBLT = 0;
	m_rFLG = 0;
	m_rVFL = 0;
	m_rPFA = 0;
	m_rPFU = 0;
	m_rPGR = 0;
}

CPrintAnlage6::~CPrintAnlage6()
{
}

BOOL CPrintAnlage6::Init()
{
	if ( m_bInitialisiert )		return TRUE;
	m_bInitialisiert = TRUE;

	m_strPRO = m_pNF_PG1 -> Projekt();
	if ( m_pNF_OG1 -> FindIDE( m_strIDE ))
	{
		m_iART   = (int)m_pNF_OG1 -> m_NFO1_ART;
		m_iBLT   = (int)m_pNF_OG1 -> m_NFO1_BLT;
		m_rFLG   = m_pNF_OG1 -> m_NFO1_FLG;
		m_rVFL   = m_pNF_OG1 -> m_NFO1_VFL;
		m_rPFA   = m_pNF_OG1 -> m_NFO1_PFA;
		m_rPFU   = m_pNF_OG1 -> m_NFO1_PFU;
		m_rPGR   = m_pNF_OG1 -> m_NFO1_PGR;
		m_strAFA = m_pNF_OG1 -> m_NFO1_AFA;
		m_strAFU = m_pNF_OG1 -> m_NFO1_AFU;
		m_strBEM = m_pNF_OG1 -> m_NFO1_BEM;
		m_strORT = m_pNF_OG1 -> m_NFO1_ORT;
		m_strFLU = m_pNF_OG1 -> m_NFO1_FLU;
		m_strFST = m_pNF_OG1 -> m_NFO1_FST;
	}

	CString		text = GetAnsichtName( "6" );
	if ( !text.IsEmpty())
		m_strViewName = text;

	return TRUE;
}	// Init

void CPrintAnlage6::Print( CDC* pDC )
{
	Init();

	CRect rcDest;

	// get size of printer page (in pixels)
	int cxPage = pDC->GetDeviceCaps(HORZRES);
	int cyPage = pDC->GetDeviceCaps(VERTRES);
	// get printer pixels per inch
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

// Hauptrahmen
	rcDest.top = cyInch / 2;				// oben 1/2 Zoll
	rcDest.bottom = cyPage - cyInch / 2;	// unten ebenso
	rcDest.left = cxInch * 3 / 4;			// links 3/4 Zoll
	rcDest.right = cxPage - cxInch / 2;		// rechts 1/2 Zoll
	pDC -> Rectangle( rcDest );

	CSize		size;
	CxString	text;
	CFont		*pOldFont;

	pOldFont = pDC -> SelectObject( m_pFntNormal );

	text = "E";
	size = pDC -> GetTextExtent( text, text.GetLength());
	int dy = size.cy * 12 / 10;

	int spalte0  = cxInch * 5 / 4;
	int spalte1  = spalte0 + cxInch/2;
	int spalte2  = spalte0 + cxInch;
	int spalte3  = spalte1 + cxInch;
	int spalte4  = spalte2 + cxInch;
	int spalte5  = spalte3 + cxInch;
	int spalte6  = spalte4 + cxInch;
	int spalte7  = spalte5 + cxInch;
	int spalte8  = spalte6 + cxInch;
	int spalte9  = spalte7 + cxInch;
	int spalte10 = spalte8 + cxInch;
	int spalte11 = spalte9 + cxInch;
	int spalte12 = spalte10 + cxInch;
	int spalte13 = spalte11 + cxInch;

	int zeile0 = cyInch/2 + dy;

// Kopftexte

	text = "Erfassungsblatt \"öffentliche Flächen\"";
	PrintText( pDC, m_pFntUeberschrift, spalte0, zeile0, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 2*dy, "Projekt:" );
	text = m_strPRO;
	PrintText( pDC, NULL, spalte1, zeile0 + 2*dy, text );

	CTime   date = CTime::GetCurrentTime();
	text.Empty();
	text.printf( "%d.%d.%d", date.GetDay(), date.GetMonth(), date.GetYear());
	PrintText( pDC, m_pFntFett, spalte6, zeile0 + 2*dy, "Datum:" );
	PrintText( pDC, NULL, spalte7, zeile0 + 2*dy, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 4*dy, "Identifikationsnummer:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 4*dy, m_strIDE );
	text = "(";
	text += m_strStrasse;
	if ( text.GetLength() > 6 )     text = text.Left( text.GetLength() - 6 );
	text += ")";
	PrintText( pDC, NULL, spalte4, zeile0 + 4*dy, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 6*dy, "Gemeinde und Ortslage:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 6*dy, m_strORT );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 7*dy, "Flur:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 7*dy, m_strFLU );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 8*dy, "Flurstücke:" );
	PrintText( pDC, NULL, spalte3, zeile0 + 8*dy, m_strFST );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 10*dy, "Baulastträger Fahrbahn" );

	PrintText( pDC, m_pFntFett, spalte7, zeile0 + 10*dy, "Straße/Platz" );
	PrintCheckBox( pDC, spalte9, zeile0 + 10*dy, dy/2, ( m_iART == 1 ));

	PrintText( pDC, m_pFntFett, spalte7, zeile0 + 11*dy, "Parkplatz" );
	PrintCheckBox( pDC, spalte9, zeile0 + 11*dy, dy/2, ( m_iART == 2 ));

	PrintText( pDC, m_pFntFett, spalte7, zeile0 + 12*dy, "sonstige" );
	PrintCheckBox( pDC, spalte9, zeile0 + 12*dy, dy/2, ( m_iART == 3 ));

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 11*dy, "Bund" );
	PrintCheckBox( pDC, spalte3, zeile0 + 11*dy, dy/2, ( m_iBLT == 1 ));

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 12*dy, "Land" );
	PrintCheckBox( pDC, spalte3, zeile0 + 12*dy, dy/2, ( m_iBLT == 2 ));

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 13*dy, "Landkreis" );
	PrintCheckBox( pDC, spalte3, zeile0 + 13*dy, dy/2, ( m_iBLT == 3 ));

	PrintText( pDC, m_pFntFett, spalte1, zeile0 + 14*dy, "Gemeinde" );
	PrintCheckBox( pDC, spalte3, zeile0 + 14*dy, dy/2, ( m_iBLT == 4 ));

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 16*dy, "Fläche - lt. Luftbild:" );
	PrintTextF2( pDC, NULL, spalte5, zeile0 + 16*dy, m_rFLG );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 17*dy, "Fläche - lt. Grundbuch:" );
	PrintTextF2( pDC, NULL, spalte5, zeile0 + 17*dy, m_rVFL );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 19*dy, "Prozentuale Aufteilung" );
	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 20*dy, "der öffentlichen Fläche" );

	PrintText( pDC, m_pFntFett, spalte5, zeile0 + 19*dy, "Anschluß" );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 22*dy, "Fahrbahn" );
	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 23*dy, "Fußgängerbereich" );
	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 24*dy, "Grünanlagen" );
	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 25*dy, "Summe" );

	PrintTextF2( pDC, NULL, spalte4, zeile0 + 22*dy, m_rPFA );
	PrintTextF2( pDC, NULL, spalte4, zeile0 + 23*dy, m_rPFU );
	PrintTextF2( pDC, NULL, spalte4, zeile0 + 24*dy, m_rPGR );
	PrintTextF2( pDC, NULL, spalte4, zeile0 + 25*dy, 100.0 );

	PrintText( pDC, NULL, spalte4, zeile0 + 22*dy, " %" );
	PrintText( pDC, NULL, spalte4, zeile0 + 23*dy, " %" );
	PrintText( pDC, NULL, spalte4, zeile0 + 24*dy, " %" );
	PrintText( pDC, NULL, spalte4, zeile0 + 25*dy, " %" );

	PrintCheckBox( pDC, spalte5 + cxInch/4, zeile0 + 22*dy, dy/2, ( m_strAFA == "Y" ));
	PrintCheckBox( pDC, spalte5 + cxInch/4, zeile0 + 23*dy, dy/2, ( m_strAFU == "Y" ));

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 28*dy, "Bemerkungen" );
	PrintExtText( pDC, NULL, spalte1, zeile0 + 29*dy,
							spalte9, zeile0 +41*dy, m_strBEM );

// nach dem letzten Text: Font zurücksetzen
	if ( pOldFont )			pDC -> SelectObject( pOldFont );

}	// Print Anlage 6

///////////////////////////////////////////////////////////////////////
//	CPrintAnlageArray
CPrintAnlageArray::~CPrintAnlageArray()
{
	CPrintAnlage	*pPA;

	for ( int i = 0; i < GetSize(); i++ )
	{
		pPA = (CPrintAnlage*)GetAt( i );
		if ( pPA )	delete pPA;
	}
}


void CPrintAnlage::CreateStaticMembers( CDC* pDC, const char* ide )
{
	m_pFntNormal       = new CFont;
	m_pFntUeberschrift = new CFont;
	m_pFntFett         = new CFont;
	m_pFntAnschrift    = new CFont;
	m_pFntAnschrFett   = new CFont;
	m_pFntBeitrag      = new CFont;
	m_pFntBeitragFett  = new CFont;

	ASSERT( m_pFntNormal );
	ASSERT( m_pFntUeberschrift );
	ASSERT( m_pFntFett );
	ASSERT( m_pFntAnschrift );
	ASSERT( m_pFntBeitrag );
	ASSERT( m_pFntBeitragFett );

	int		FontHeight = MulDiv( 10, pDC -> GetDeviceCaps( LOGPIXELSY ), 72 );
//	static char BASED_CODE szFontName [] = "MS Sans Serif";
	static char BASED_CODE szFontName [] = "Arial";

	if ( !m_pFntUeberschrift -> CreateFont( -FontHeight, 0, 0, 0, FW_BOLD, FALSE, TRUE,
			FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, szFontName ))
	{
		AfxMessageBox( "Fehler beim Initialisieren der Schriftart!" );
	}

	if ( !m_pFntBeitrag -> CreateFont( -FontHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE,
			FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, szFontName ))
	{
		AfxMessageBox( "Fehler beim Initialisieren der Schriftart!" );
	}

	if ( !m_pFntBeitragFett -> CreateFont( -FontHeight, 0, 0, 0, FW_BOLD, FALSE, FALSE,
			FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, szFontName ))
	{
		AfxMessageBox( "Fehler beim Initialisieren der Schriftart!" );
	}

	FontHeight = MulDiv( 10, pDC -> GetDeviceCaps( LOGPIXELSY ), 72 );

	if ( !m_pFntAnschrift -> CreateFont( -FontHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE,
			FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, szFontName ))
	{
		AfxMessageBox( "Fehler beim Initialisieren der Schriftart!" );
	}

	if ( !m_pFntAnschrFett -> CreateFont( -FontHeight, 0, 0, 0, FW_BOLD, FALSE, FALSE,
			FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, szFontName ))
	{
		AfxMessageBox( "Fehler beim Initialisieren der Schriftart!" );
	}

	FontHeight = MulDiv( 8, pDC -> GetDeviceCaps( LOGPIXELSY ), 72 );

	if ( !m_pFntNormal -> CreateFont( -FontHeight, 0, 0, 0, FW_NORMAL, FALSE, FALSE,
			FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, szFontName ))
	{
		AfxMessageBox( "Fehler beim Initialisieren der Schriftart!" );
	}

	if ( !m_pFntFett -> CreateFont( -FontHeight, 0, 0, 0, FW_BOLD, FALSE, FALSE,
			FALSE, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
			DEFAULT_QUALITY, VARIABLE_PITCH | FF_SWISS, szFontName ))
	{
		AfxMessageBox( "Fehler beim Initialisieren der Schriftart!" );
	}

	if ( NULL != m_pNF_PG1 )		return;

	m_pNF_PG1       = g_pNF_PG1;
	m_pNF_PG1GB     = new CSetNF_PG1GB( g_pDatabase );
	m_pNF_PG2D      = new CSetNF_PG2D( g_pDatabase );
	m_pNF_PG2H      = new CSetNF_PG2H( g_pDatabase );
	m_pNF_OG1       = new CSetNF_OG1( g_pDatabase );
	m_pNF_PG3       = new CSetNF_PG3( g_pDatabase );
	m_pOrte         = new COrteSet( g_pDatabase );
	m_pStrassen     = new CStrasseSet( g_pDatabase );
	m_pVerz         = new CVerzSet( g_pDatabase );
//	m_pTRiDB        = new CTriDBSet;
	m_pTRiDB        = g_pSetTriDB;
	if ( NULL == m_pTRiDB )
	{
//		m_pTRiDB    = new CTriDBSet( g_pDatabase );
		AfxMessageBox( "Unerwarteter Datenbankfehler beim Initialisieren von PrintAnlage!" );
	}

	ASSERT( m_pNF_PG1 );
	ASSERT( m_pNF_PG1GB );
	ASSERT( m_pNF_PG2D );
	ASSERT( m_pNF_PG2H );
	ASSERT( m_pNF_OG1 );
	ASSERT( m_pNF_PG3 );
	ASSERT( m_pOrte );
	ASSERT( m_pStrassen );

//	m_pNF_PG1 -> Open();
	if ( !m_pNF_PG1 -> IsOpen())
	{
		m_pNF_PG1 -> Open();
		m_pNF_PG1 -> InitListen( ide );
	}
	m_pNF_PG1GB -> Open();
	m_pNF_PG2D -> Open();
	m_pNF_PG2H -> Open();
	m_pNF_OG1 -> Open();
	m_pNF_PG3 -> Open();
	m_pOrte -> Open();
	m_pStrassen -> Open();
	m_pVerz -> Open();
//	m_pTRiDB -> Open();
	if ( !m_pTRiDB -> IsOpen())
	{
		m_pTRiDB -> Open();
		m_pTRiDB -> InitListen();
	}

//	m_pNF_PG1 -> InitListen( ide );
	m_pNF_PG1GB -> InitListen( ide );
	m_pNF_PG2D -> InitListen( ide );
	m_pNF_PG2H -> InitListen( ide );
	m_pNF_PG3 -> InitListen( ide );
	m_pOrte -> InitListen();
	m_pStrassen -> InitListen();
	m_pVerz -> InitListen();
//	m_pTRiDB -> InitListen();
}

void CPrintAnlage::DeleteStaticMembers()
{
	DELE( m_pFntNormal );
	DELE( m_pFntUeberschrift );
	DELE( m_pFntFett );
	DELE( m_pFntAnschrift );
	DELE( m_pFntAnschrFett );
	DELE( m_pFntBeitrag );
	DELE( m_pFntBeitragFett );
//	CLOSE_DELETE( m_pNF_PG1 );
	CLOSE_DELETE( m_pNF_PG1GB );
	CLOSE_DELETE( m_pNF_PG2D );
	CLOSE_DELETE( m_pNF_PG2H );
	CLOSE_DELETE( m_pNF_OG1 );
	CLOSE_DELETE( m_pNF_PG3 );
	CLOSE_DELETE( m_pOrte );
	CLOSE_DELETE( m_pStrassen );
	CLOSE_DELETE( m_pVerz );
//	CLOSE_DELETE( m_pTRiDB );
}

CFont* CPrintAnlage::m_pFntNormal = NULL;
CFont* CPrintAnlage::m_pFntUeberschrift = NULL;
CFont* CPrintAnlage::m_pFntFett = NULL;
CFont* CPrintAnlage::m_pFntAnschrift = NULL;
CFont* CPrintAnlage::m_pFntAnschrFett = NULL;
CFont* CPrintAnlage::m_pFntBeitrag = NULL;
CFont* CPrintAnlage::m_pFntBeitragFett = NULL;
CSetNF_PG1* CPrintAnlage::m_pNF_PG1 = NULL;
CSetNF_PG1GB* CPrintAnlage::m_pNF_PG1GB = NULL;
CSetNF_PG2D* CPrintAnlage::m_pNF_PG2D = NULL;
CSetNF_PG2H* CPrintAnlage::m_pNF_PG2H = NULL;
CSetNF_OG1* CPrintAnlage::m_pNF_OG1 = NULL;
CSetNF_PG3* CPrintAnlage::m_pNF_PG3 = NULL;
COrteSet* CPrintAnlage::m_pOrte = NULL;
CStrasseSet* CPrintAnlage::m_pStrassen = NULL;
CVerzSet* CPrintAnlage::m_pVerz = NULL;
CTriDBSet* CPrintAnlage::m_pTRiDB = NULL;

void CPrintAnlage::PrintText( CDC *pDC, CFont *fnt, int x, int y, const char *txt )
{
	CFont	*pOldFont = NULL;
	BOOL	res = FALSE;

	if ( fnt )	pOldFont = pDC -> SelectObject( fnt );
	res = pDC -> TextOut( x, y, txt );
	if ( pOldFont )	pDC -> SelectObject( pOldFont );
}

void CPrintAnlage::PrintExtText( CDC *pDC, CFont *fnt, int x, int y, int x1, int y1, const char* txt )
{
	CFont   *pOldFont = NULL;
	CRect   rect = CRect( x, y, x1, y1 );
	CString text = txt;

	if ( fnt )              pOldFont = pDC -> SelectObject( fnt );
	pDC -> DrawText( txt, text.GetLength(), &rect, DT_WORDBREAK|DT_LEFT );
	pDC -> ExtTextOut( x, y, ETO_CLIPPED,   // Options
						&rect,
						txt,
						text.GetLength(),
						NULL );
}

void CPrintAnlage::PrintTextR( CDC *pDC, CFont *fnt, int x, int y, const char *txt )
{
	CFont   *pOldFont = NULL;

	if ( fnt )      pOldFont = pDC -> SelectObject( fnt );
	pDC -> SetTextAlign(TA_RIGHT); //fnr Zahlen mit Komma als rechtsbnndig
	pDC -> TextOut( x, y, txt );
	pDC -> SetTextAlign(TA_LEFT);
	if ( pOldFont )         pDC -> SelectObject( pOldFont );
}

void CPrintAnlage::PrintTextF0( CDC *pDC, CFont *fnt, int x, int y, double r )
{
	CFont           *pOldFont = NULL;
	CxString        txt;

	txt.printf( "%7.0f", r );
	if ( fnt )              pOldFont = pDC -> SelectObject( fnt );
	pDC -> SetTextAlign(TA_RIGHT);
	pDC -> TextOut( x, y, txt );
	pDC -> SetTextAlign(TA_LEFT);
	if ( pOldFont )         pDC -> SelectObject( pOldFont );
}

void CPrintAnlage::PrintTextF2( CDC *pDC, CFont *fnt, int x, int y, double r )
{
	CFont           *pOldFont = NULL;
	CxString        txt;

	txt.printf( "%8.2f", r );
	if ( fnt )              pOldFont = pDC -> SelectObject( fnt );
	pDC -> SetTextAlign(TA_RIGHT);
	pDC -> TextOut( x, y, txt );
	pDC -> SetTextAlign(TA_LEFT);
	if ( pOldFont )         pDC -> SelectObject( pOldFont );
}

void CPrintAnlage::PrintTextF3( CDC *pDC, CFont *fnt, int x, int y, double r )
{
	CFont           *pOldFont = NULL;
	CxString        txt;

	txt.printf( "%10.3f", r );
	if ( fnt )              pOldFont = pDC -> SelectObject( fnt );
	pDC -> SetTextAlign(TA_RIGHT);
	pDC -> TextOut( x, y, txt );
	pDC -> SetTextAlign(TA_LEFT);
	if ( pOldFont )         pDC -> SelectObject( pOldFont );
}

void CPrintAnlage::PrintCheckBox( CDC *pDC, int x, int y, int dx, BOOL flag )
{
	pDC -> MoveTo( x, y );
	pDC -> LineTo( x+dx, y );
	pDC -> LineTo( x+dx, y+dx );
	pDC -> LineTo( x, y+dx );
	pDC -> LineTo( x, y );

	if ( flag )
	{
		pDC -> MoveTo( x, y );
		pDC -> LineTo( x+dx, y+dx );
		pDC -> MoveTo( x+dx, y );
		pDC -> LineTo( x, y+dx );
	}
}

double CPrintAnlage::TB( const char* id )
{
	double	result;
	short	nr;

	nr = OrtNr( id );

	if ( nr )	result = m_pOrte -> TB( nr );
	else		result = 50;

	return result;
}	// TB

short CPrintAnlage::OrtNr( const char* id )
{
	CString         txt = id;
	short           nr;

	ASSERT( txt.GetLength() > 5 );
	txt = txt.Left( 2 );
	nr = atoi( txt );
	if ( nr == 0 )
	{
		switch ( txt[0] )
		{
			case 'A':	nr = 12;	break;
			case 'B':	nr = 3;		break;
			case 'C':	nr = 11;	break;
			case 'D':	nr = 13;	break;
			case 'E':	nr = 2;		break;
			case 'F':	nr = 14;	break;
			case 'G':	nr = 6;		break;
			case 'H':	nr = 10;	break;
			case 'I':	nr = 1;		break;
			case 'J':	nr = 4;		break;
			case 'K':	nr = 15;	break;
			case 'L':	nr = 8;		break;
			case 'M':	nr = 7;		break;
			case 'N':	nr = 9;		break;
			case 'O':	nr = 16;	break;
			case 'P':	nr = 5;		break;
		}
	}

	return nr;
}

//	liefert den ObjektContainer des angegebenen Objektes
BOOL CPrintAnlage::GetTriasObjContainer( long onr, long* cont )
{
	ASSERT( onr > 0L );
	ASSERT( AfxIsValidAddress( cont, sizeof( long )*4 ));
	long	buffer[4];
	LRESULT	result;

	result = DEX_GetObjContainer( onr, buffer );
	cont[0] = buffer[0];
	cont[1] = buffer[1];
	cont[2] = buffer[2];
	cont[3] = buffer[3];
	return ( result != 0L );
}

//	liefert die RGB-Farbanteile für das angegebene Objekt in der
//	aktuellen Sicht
long CPrintAnlage::GetTriasObjColor( long onr )
{
	ASSERT( onr > 0L );
	return (long)DEX_GetObjColor( onr );
}


long CPrintAnlage::GetObjNr( const char* ide )
{
	ASSERT( AfxIsValidString( ide ));
	CString		id = ide;
	long		result = 0L;
	short		i;

	ASSERT( id.GetLength() > 4 );
	ASSERT( g_pArrIDE );
	ASSERT( g_pArrONr );

	for ( i = 0; i < g_pArrIDE -> GetSize(); i++ )
		if ( id == g_pArrIDE -> GetAt( i ))
	{
		result = (long)g_pArrONr -> GetAt( i );
		break;
	}

	return result;
}

void CPrintAnlage::RenderTRiASAusschnitt( CDC* pDC, const char* view, long onr, RECTL& cont, CRect* rcDest )
{
	BOOL	abbruch = FALSE;
	CSize	size;
	RECT	rcPict;
	RECTL	rclClipBox, rclFrame;
	long	c[4];

	size.cx = rcDest -> left;
	size.cy = rcDest -> top;
	pDC -> LPtoHIMETRIC( &size );
	rcDest -> left = size.cx;
	rcDest -> top  = size.cy;
	size.cx = rcDest -> right;
	size.cy = rcDest -> bottom;
	pDC -> LPtoHIMETRIC( &size );
	rcDest -> right  = size.cx;
	rcDest -> bottom = size.cy;

	rclFrame.left   = rcDest -> left;
	rclFrame.right  = rcDest -> right;
	rclFrame.top    = - rcDest -> top;
	rclFrame.bottom = - rcDest -> bottom;

	rclClipBox.left   = rclFrame.left + 100;
	rclClipBox.right  = rclFrame.right - 100;
	rclClipBox.top    = rclFrame.top - 100;
	rclClipBox.bottom = rclFrame.bottom + 100;

	if ( m_hMetaFile == NULL )
	{
		if ( !GetTriasObjContainer( onr, (long*)c ))
			abbruch = TRUE;

		if ( !abbruch )
		{
			cont.left   = c[0];
			cont.top    = c[3];
			cont.right  = c[1];
			cont.bottom = c[2];

			long	dx, dy;
			dx = long(( cont.right - cont.left ) * 0.2 );
			dy = long(( cont.bottom - cont.top ) * 0.2 );
			cont.left   -= dx;
			cont.right  += dx;
			cont.top    -= dy;
			cont.bottom += dy;
		}
	}

	if ( !abbruch )
	{
		if ( m_hMetaFile == NULL )
		{
//			DEX_RePaintWait();
			DEX_RePaintWait();

			RENDERGEODB		sRend;
			RECTL			rectl;
			HDC				hdcMetaFile;
			int				oldMapMode;

			::SaveDC( pDC -> m_hAttribDC );

			oldMapMode = ::SetMapMode( pDC -> m_hAttribDC, MM_HIMETRIC );

			rectl.bottom = labs( rclFrame.bottom - rclFrame.top );
			rectl.top    = 0L;
			rectl.right  = labs( rclFrame.right - rclFrame.left );
			rectl.left   = 0L;
			rcPict.top    = rectl.top;
			rcPict.bottom = rectl.bottom;
			rcPict.left   = rectl.left;
			rcPict.right  = rectl.right;

			hdcMetaFile = CreateEnhMetaFile( pDC -> m_hAttribDC, NULL, &rcPict, NULL );

			sRend.dwSize              = sizeof( RENDERGEODB );
			sRend.m_hDC               = hdcMetaFile;
			sRend.m_hTargetDC         = pDC -> m_hAttribDC;

			sRend.m_rclFrame.left     = 0L;
			sRend.m_rclFrame.top      = rectl.bottom;
			sRend.m_rclFrame.right    = rectl.right;
			sRend.m_rclFrame.bottom   = 0L;
			sRend.m_rclClipBox        = sRend.m_rclFrame;

			sRend.m_rclGeoDB.left     = cont.left;
			sRend.m_rclGeoDB.top      = cont.top;
			sRend.m_rclGeoDB.right    = cont.right;
			sRend.m_rclGeoDB.bottom   = cont.bottom;

			::SetMapMode( hdcMetaFile, MM_HIMETRIC );
			::SetWindowOrgEx( hdcMetaFile, 0, (int)( sRend.m_rclFrame.top - sRend.m_rclFrame.bottom ), NULL );

			if ( hdcMetaFile )
			{
				DexExtensionProc((WPARAM)DEX_RENDERGEODB, (LPARAM)&sRend );
				m_hMetaFile = CloseEnhMetaFile( hdcMetaFile );
			}

			::SetMapMode( pDC -> m_hAttribDC, oldMapMode );
			::RestoreDC( pDC -> m_hAttribDC, -1 );
		}

		if ( m_hMetaFile )
		{
			CRect	DestRect;
			POINT	pt1, pt2;

			DestRect.bottom = rclFrame.bottom;
			DestRect.top    = rclFrame.top;
			DestRect.left   = rclFrame.left;
			DestRect.right  = rclFrame.right;

			if (( pDC -> IsKindOf( RUNTIME_CLASS( CPreviewDC ))) &&
				( m_bNeuerOffset ))
			{
				m_bNeuerOffset = FALSE;
			}

			int saveDC = pDC -> SaveDC();
			pDC -> SetMapMode( MM_HIMETRIC );
			if ( pDC -> IsKindOf( RUNTIME_CLASS( CPreviewDC )))
			{
				pt1.x = rclClipBox.left;
				pt1.y = rclClipBox.top;
				pt2.x = rclClipBox.right;
				pt2.y = rclClipBox.bottom;
				::LPtoDP( pDC -> m_hAttribDC, &pt1, 1 );
				::LPtoDP( pDC -> m_hAttribDC, &pt2, 1 );
				((CPreviewDC*)pDC ) -> PrinterDPtoScreenDP( &pt1 );
				((CPreviewDC*)pDC ) -> PrinterDPtoScreenDP( &pt2 );
				pt1.x += m_sizeTopLeftOffset.cx;
				pt1.y += m_sizeTopLeftOffset.cy;
				pt2.x += m_sizeTopLeftOffset.cx;
				pt2.y += m_sizeTopLeftOffset.cy;
				::DPtoLP( pDC -> m_hDC, &pt1, 1 );
				::DPtoLP( pDC -> m_hDC, &pt2, 1 );
			}
			else
			{
				pt1.x = rclClipBox.left;
				pt1.y = rclClipBox.top;
				pt2.x = rclClipBox.right;
				pt2.y = rclClipBox.bottom;
			}

			if ( pDC -> m_hDC != NULL )
			{
				::IntersectClipRect( pDC -> m_hDC, pt1.x, pt1.y, pt2.x, pt2.y );
				pDC -> PlayMetaFile( m_hMetaFile, &DestRect );
			}
			else
				::MessageBeep( -1 );
			pDC -> RestoreDC( saveDC );
		}
	}

	g_bRenderingInProgres = FALSE;
}	// RenderTRiASAusschnitt

void CPrintAnlage::SetTopLeftOffset( CSize* sizeTopLeft )
{
	ASSERT( sizeTopLeft );
	ASSERT( AfxIsValidAddress( sizeTopLeft, sizeof( CSize )));

	m_sizeTopLeftOffset = *sizeTopLeft;
	m_bNeuerOffset = TRUE;
}	// SetTopLeftOffset

void CPrintAnlage::PrepareObjColor( long onr, BOOL alles )
{
	CxString	ObjNr;

	ObjNr.AppendF( onr, -1 );
	if ( g_pExt != NULL )
	{
		if ( alles )	// "2" ==> Alle Flächen einfärben
			g_pExt -> ExecBasicScriptParam( IDR_MACRO3, ObjNr, "2" );
		else			// "1" ==> Nur GS einfärben
			g_pExt -> ExecBasicScriptParam( IDR_MACRO3, ObjNr, "1" );
	}
}

void CPrintAnlage::ResetObjColor( long onr, BOOL alles )
{
	CxString	ObjNr;

	ObjNr.AppendF( onr, -1 );
	if ( g_pExt != NULL )
	{
		if ( alles )	// "0" ==> Alle Flächen rücksetzen
			g_pExt -> ExecBasicScriptParam( IDR_MACRO3, ObjNr, "0" );
		else			// "-1" ==> Nur GS rücksetzen
			g_pExt -> ExecBasicScriptParam( IDR_MACRO3, ObjNr, "-1" );
	}
}

void CPrintAnlage::SelectTRiASView( const char* name )
{
	CString	strName, strBuffer;
	char    buffer[MAX_PATH];

	strName = name;
	if ( strName.IsEmpty())		return;

	ASSERT( AfxIsValidString( name ));
	buffer[0] = '\0';
	DEX_GetActiveSight( buffer );

	strBuffer = buffer;
	if ( !( strName == strBuffer ))
		if ( DEX_ProjectHasView((LPARAM)(const char*)strName ))
			DEX_SelectNewSight((LPARAM)(const char*)strName );
}

//	öffnet das angegebene Projekt in TRiAS
LRESULT  PASCAL TriasOpenProject( const char *b )
{
	TRIAS_OPEN	tos;
	char		buffer[256];
	char		*pProjekt, *pUser, *pPassWord;

	strcpy( buffer, b );
	pProjekt = buffer;
	pUser = pProjekt;

	while ( *pUser && ( *pUser != ',' )) pUser++;
	if ( !*pUser ) return 0L;

	pPassWord = pUser;
	*pUser++ = '\0';

	tos.dwSize     = sizeof( TRIAS_OPEN );
	tos.lpProject  = pProjekt;
	tos.lpUser     = pUser;
	tos.lpPassWord = pPassWord;
	tos.iMode      = 0;     // Standardsicht zeigen!

	return DexExtensionProc((WPARAM)DEX_PROJECTOPEN,(LPARAM)&(tos));
}	// TriasOpenProject

void CPrintAnlage::SelectTRiASProject( const char* project )
{
	char		*txt;

	if ( m_hMetaFile != NULL )	return;

	CxString	text, curproject;
	CxString	temp;
	BOOL		isOpen = FALSE;

	ASSERT( AfxIsValidString( project ));
	if ( *project == '\0' )		return;

	temp = project;
	if ( !temp.FileExist())		return;

	txt = curproject.GetBuffer( 1024 );
	*txt = '\0';
	DEX_GetActiveProject( txt );
	curproject.ReleaseBuffer();
	curproject.MakeUpper();

	if ( curproject == project )	isOpen = TRUE;

	if ( !isOpen )
	{
		if ( DEX_IsGeoDBDirty())		DEX_FlushModifications();

/*				long	geduld = 0L;
				MSG		msg;

				while ( m_bIsPainting && ( geduld < 10000L ))
				{
					geduld++;
					while (::GetMessage(&msg, (HWND) NULL, 0, 0))
					{
						::TranslateMessage(&msg);
						::DispatchMessage(&msg);
					}
				}
*/
		temp = project;
		temp += ",";
		TriasOpenProject( temp );
/*
				geduld = 0L;
				while (::GetMessage(&msg, (HWND) NULL, 0, 0) && ( geduld < 5L ))
				{
					geduld++;
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
				}

				short	geduld2 = 0;
				geduld = 0L;
				while ( m_bIsPainting && ( geduld < 50L ))
				{
					geduld++;
					geduld2 = 0;
					while (::GetMessage(&msg, (HWND) NULL, 0, 0) && ( geduld2 < 5L ))
					{
						geduld2++;
						::TranslateMessage(&msg);
						::DispatchMessage(&msg);
					}
				}
*/
	}
}

CString CPrintAnlage::GetProjectName( const char* ide )
{
	CString	key;
	CString	result;
	int		id = -1;
	void	*ptr;

	ASSERT( AfxIsValidString( ide ));
	key = ide;
	if ( m_mapObj2Project.Lookup( key, ptr ))	id = int( ptr );
	if ( id < 0 )
	{
		id = m_pTRiDB -> GetProjectNr( ide );
		m_mapObj2Project.SetAt( ide, (void*)id );
	}
	if ( id > 0 )
		result = m_pVerz -> GetProjectName( id );

	return result;
}


///////////////////////////////////////////////////////////////////////
CPrintAnlage7::CPrintAnlage7( const char* ide, long enr )
{
	ASSERT( AfxIsValidString( ide ));
	m_strIDE = ide;
	m_bInitialisiert = FALSE;
	m_cKennung = '7';
	m_bDatum = FALSE;
	m_lENR = enr;
}

CPrintAnlage7::~CPrintAnlage7()
{
}

BOOL CPrintAnlage7::Init()
{
	if ( m_bInitialisiert )		return TRUE;
	m_bInitialisiert = TRUE;

	CBasisSatz*		pS;
	CEigentuemer*	pE;
	CxString		text, item, rest;
	CString			filename;
//	char*			txt;
	BOOL			if_aktiv, bed, lesen;

	pS = m_pNF_PG1 -> FindIDE( m_strIDE );

	if ( pS )
	{
//		m_strNFP1_ENA  = pS -> Besitzer();
//		m_strNFP1_EAN  = pS -> Strasse();
//		m_strNFP1_EPL  = pS -> PLZ();
//		m_strNFP1_EOR  = pS -> Ort();
//		m_strNFP1_KASS = pS -> KASS();

		m_strSTR_DECO  = m_pStrassen -> Strasse( m_strIDE );
		m_strNFP1_ORT  = m_pOrte -> Ort( m_strIDE );
		m_strNFP1_FLU  = pS -> Flur();
		m_strNFP1_FST  = pS -> Flurstk();
		
		text.Empty();	text.AppendF( pS -> GFZ(), -1, 0 );
		m_strNFP1_GFZ  = text;

		text.Empty();	text.AppendFormated( pS -> AGG(), -1, 2, 2 );
		m_strNFP1_AGG  = text;
//		m_rAGGS  = pS -> AGGS();

		text.Empty();	text.AppendFormated( pS -> VGZ(), -1, 2, 2 );
		m_strNFP1_VGZ  = text;

		text.Empty();	text.AppendF( pS -> VOLLIE2(), -1, 0 );
		m_strVOLLIE2   = text;

		text.Empty();	text.AppendF( pS -> VOLLIE2() / 100.0, -1, 2 );
		m_strVOLLGESCH = text;

		text.Empty();	text.AppendF( pS -> VOLLIE3(), -1, 0 );
		m_strVOLLIE3   = text;

		text.Empty();	text.AppendFormated( pS -> BDM(), -1, 2, 2 );
		m_strNFP1_BDM  = text;

		text.Empty();	text.AppendFormated( pS -> RW_FL_GE(), -1, 2, 2 );
		m_strRW_FL_GE  = text;

		text.Empty();	text.AppendFormated( pS -> RW_FL_RU(), -1, 2, 2 );
		m_strRW_FL_RU  = text;

		text.Empty();	text.AppendFormated( pS -> RW_DM_JA(), -1, 2, 2 );
		m_strRW_DM_JA  = text;

		text.Empty();	text.AppendFormated( pS -> RW_DM_QA(), -1, 2, 2 );
		m_strRW_DM_QA  = text;
	}

	pE = g_pNF_PG4 -> FindEigentuemer( m_strIDE, m_lENR );

	if ( pE )
	{
		m_strNFP1_ENA  = pE -> m_NFP4_ENA;
		m_strNFP1_EAN  = pE -> m_NFP4_ENA;
		m_strNFP1_EPL  = pE -> m_NFP4_ENA;
		m_strNFP1_EOR  = pE -> m_NFP4_ENA;
		m_strNFP1_KASS = pE -> m_NFP4_KASS;
	}

	// Datei lesen!
/*
	m_arrText.Add( "Beitragsbescheid für die öffentliche Abwasseranlage (Herstellungsbeitrag)" );
	m_arrInfo.Add( "Fett" );
	m_arrText.Add( "I. Beitragspflichtiges Grundstück" );
	m_arrInfo.Add( "Fett;L=1" );
	m_arrText.Add( "Gemeinde / Stadt:  <<NFP1_ORT>>" );
	m_arrInfo.Add( "L=1" );
	m_arrText.Add( "Straße:  <<STR_DECO>>" );
	m_arrInfo.Add( "L=1" );
	m_arrText.Add( "Flur:  <<NFP1_FLU>>" );
	m_arrInfo.Add( "L=1" );
	m_arrText.Add( "Flurstück:  <<NFP1_FST>>" );
	m_arrInfo.Add( "O=0;X=5" );
	m_arrText.Add( "Anzahl Wohneinheiten:  <<NFP1_GFZ>>" );
	m_arrInfo.Add( "L=1" );
	m_arrText.Add( "II. Herstellungsbeitrag gem. § 4, § 5 der Herstellungsbeitragssatzung" );
	m_arrInfo.Add( "Fett;L=2;" );
	m_arrText.Add( "heranzuziehende" );
	m_arrInfo.Add( "L=1" );
	m_arrText.Add( "Grundstücksfläche" );
	m_arrInfo.Add( "" );
	m_arrText.Add( "Schmutzwasser-" );
	m_arrInfo.Add( "X=9;O=0" );
	m_arrText.Add( "lt. Anlage" );
	m_arrInfo.Add( "" );
	m_arrText.Add( "Beitragssatz" );
	m_arrInfo.Add( "X=6;O=0" );
	m_arrText.Add( "beitrag" );
	m_arrInfo.Add( "X=9;O=0" );
	m_arrText.Add( "<<NFP1_AGG>> m²  x   <<VOLLIE2>>%   x" );
	m_arrInfo.Add( "L=1" );
	m_arrText.Add( "7,13 DM/m²   =" );
	m_arrInfo.Add( "X=6;O=0" );
	m_arrText.Add( "<<NFP1_BDM>> DM" );
	m_arrInfo.Add( "X=9;O=0" );
	m_arrText.Add( "Für das beitragspflichtige Grundstück besteht kein Bebauungsplan. Als tatsächlich" );
	m_arrInfo.Add( "L=1" );
	m_arrText.Add( "vorhandene Vollgeschosse wurde <<NFP1_VGZ>> festgestellt." );
	m_arrInfo.Add( "" );
	m_arrText.Add( "(Für das erste Vollgeschoß sind 100%, für jedes weitere zusätzlich 60% der heranzuziehenden Grundstücksfläche anzusetzen.)" );
	m_arrInfo.Add( "Klein;L=2" );
*/
//	text.Empty();
//	txt = text.GetBuffer( 256 );
	item.Empty();
	item += m_cKennung;
//	GetPrivateProfileString( "Texte", item, "", txt, 256, "GBM.INI" );
//	text.ReleaseBuffer();
	text = GetVorlageFileName( m_cKennung );
	if ( text.IsEmpty())		return FALSE;
	if ( !FileExist( text ))	return FALSE;

	m_bDatum = FALSE;
	m_strLogoFileName.Empty();
	m_strLogoPosition.Empty();
	TRY
	{
		CStdioFile file( text, CFile::modeRead|CFile::typeText );
		filename = text;

		if_aktiv = bed = FALSE;
		lesen = TRUE;
		while ( file.ReadString( text ))
		{
			item.Empty();
			if ( text[0] != ';' )		// Kommentar überlesen
			{
				if ( text[0] == '#' )
				{
					text = text.Mid( 1 );
					text.Teilen( item, text, '=' );
					item.MakeUpper();
					if ( item == "ADR1" )			m_strAddr1 = text;
					if ( item == "ADR2" )			m_strAddr2 = text;
					if ( item == "ADR3" )			m_strAddr3 = text;
					if ( item == "ADR4" )			m_strAddr4 = text;
					if ( item == "ADR5" )			m_strAddr5 = text;
					if ( item == "DATUM" )			m_bDatum = TRUE;
					if ( item == "LEGENDCOLOR" )	m_strColor = text;
					if ( item == "LOGOFILENAME" )	m_strLogoFileName = text;
					if ( item == "LOGOPOSITION" )	m_strLogoPosition = text;
				}
				else if ( text[0] == '[' )	// 'IF'-Klauseln
				{
					text = text.Mid( 1 );
					text.MakeUpper();
					text.Teilen( item, text, ' ' );
					if ( text.IsEmpty())	item.Teilen( item, text, ']' );
					else					text.Teilen( text, rest, ']' );
					if ( item == "IF" )
					{
						if ( if_aktiv )		Fehler( IDS_MULTIIFKLAUSEL, filename );
						if_aktiv = TRUE;
						bed = TRUE;
						if ( text == "B_PLAN" )
						{
//							if ( !pS -> NA_B_PLAN().IsEmpty())	bed = TRUE;
							if ( !pS -> TIEF())	bed = TRUE;
							else				bed = FALSE;
						}
						lesen = bed;
					}
					else if ( item == "ELSE" )
					{
						if ( !if_aktiv )	Fehler( IDS_BADELSEKLAUSEL, filename );
						if_aktiv = TRUE;
						lesen = !bed;
					}
					else if ( item == "ENDIF" )
					{
						if ( !if_aktiv )	Fehler( IDS_BADENDIFKLAUSEL, filename );
						if_aktiv = FALSE;
						bed = FALSE;
						lesen = TRUE;
					}
					else
					{
						Fehler( IDS_BADIFKLAUSEL, filename );
						lesen = TRUE;
					}
				}
				else
				{
					if ( lesen )
					{
						if ( text[0] == '{' )	// Steuerkodes extrahieren
						{
							text = text.Mid( 1 );
							text.Teilen( item, text, '}' );
						}
						m_arrText.Add( text );
						m_arrInfo.Add( item );
					}
				}
			}
		}

		file.Close();
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
		afxDump << "Datei '" << text << "' kann nicht geöffnet werden! " << e->m_cause << "\n";
		#endif
	}
	END_CATCH
  

	for ( short i = 0; i < m_arrText.GetSize(); i++ )
		SetupDataString( m_arrText[i]);

	return TRUE;
}	// Init

void CPrintAnlage7::Print( CDC* pDC )
{
	CxString	text;
	Init();

	CRect rcDest;

	// get size of printer page (in pixels)
	int cxPage = pDC->GetDeviceCaps(HORZRES);
	int cyPage = pDC->GetDeviceCaps(VERTRES);
	// get printer pixels per inch
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

// Hauptrahmen
	rcDest.top = cyInch / 2;				// oben 1/2 Zoll
	rcDest.bottom = cyPage - cyInch / 2;	// unten ebenso
	rcDest.left = cxInch * 3 / 4;			// links 3/4 Zoll
	rcDest.right = cxPage - cxInch / 2;		// rechts 1/2 Zoll
//	pDC -> Rectangle( rcDest );
	int	yLogo  = rcDest.top + 4;
	int	xLogo1 = rcDest.left + 4;
	int	xLogo2 = rcDest.right + 4;

// Rahmen für die Kundennummer
	rcDest.top = cyInch * 4;				// oben 4 Zoll
	rcDest.left = cxInch * 3 / 4;
	rcDest.right = cxPage - cxInch / 2;
	rcDest.bottom = cyInch * 4.5;

	int xDiff, yDiff;

	xDiff = cxInch / 30;
	yDiff = cyInch / 30;

	CRect   rect = rcDest;
	rect.top -= yDiff - xDiff;
	rect.bottom += yDiff + xDiff;
	rect.left -= xDiff - xDiff;
	rect.right += xDiff + xDiff;
	for ( short i = 0; i < xDiff; i +=2 )
	{
		pDC -> Rectangle( rect );
		rect.top -= 2;
		rect.bottom -= 2;
		rect.left -= 2;
		rect.right -= 2;
	}

	CSize		size;
	CFont		*pOldFont;

	if ( !m_strLogoFileName.IsEmpty())
	{
		text = m_strLogoFileName;
		if ( text.FileExist())
			yLogo = PrintLogo( pDC, xLogo1, xLogo2, yLogo, text, m_strLogoPosition );
		else
			yLogo = 0;
	}
	else
		yLogo = 0;

	pOldFont = pDC -> SelectObject( m_pFntNormal );

	text = "E";
	size = pDC -> GetTextExtent( text, text.GetLength());
	int dx = size.cx;
	int dy = size.cy * 12 / 10;

	int spalte0  = cxInch * 3 / 4;
	int spalte1  = spalte0 + cxInch/2;
	int spalte2  = spalte0 + cxInch;
	int spalte3  = spalte1 + cxInch;
	int spalte4  = spalte2 + cxInch;
	int spalte5  = spalte3 + cxInch;
	int spalte6  = spalte4 + cxInch;
	int spalte7  = spalte5 + cxInch;
	int spalte8  = spalte6 + cxInch;
	int spalte9  = spalte7 + cxInch;
	int spalte10 = spalte8 + cxInch;
	int spalte11 = spalte9 + cxInch;
	int spalte12 = spalte10 + cxInch;
	int spalte13 = spalte11 + cxInch;

	int zeile0 = cyInch/2 + dy;

	// Absender
	if ( !m_strAddr1.IsEmpty())
		PrintText( pDC, m_pFntAnschrFett, spalte0, zeile0 + 1*dy, m_strAddr1 );
	if ( !m_strAddr2.IsEmpty())
		PrintText( pDC, m_pFntAnschrFett, spalte0, zeile0 + 2*dy, m_strAddr2 );
	if ( !m_strAddr3.IsEmpty())
		PrintText( pDC, m_pFntAnschrFett, spalte0, zeile0 + 3*dy, m_strAddr3 );
	if ( !m_strAddr4.IsEmpty())
		PrintText( pDC, m_pFntAnschrFett, spalte0, zeile0 + 4*dy, m_strAddr4 );
	if ( !m_strAddr5.IsEmpty())
		PrintText( pDC, m_pFntAnschrFett, spalte0, zeile0 + 5*dy, m_strAddr5 );

	// Anschrift
	PrintText( pDC, m_pFntAnschrift, spalte0, zeile0 + 12*dy, m_strNFP1_ENA );
	PrintText( pDC, m_pFntAnschrift, spalte0, zeile0 + 13*dy, m_strNFP1_EAN );
	text = m_strNFP1_EPL;
	text += "    ";
	text += m_strNFP1_EOR;
	PrintText( pDC, m_pFntAnschrift, spalte0, zeile0 + 16*dy, text );

	// Neue Zeile0 ist die Kundennummer im Rahmen!
	zeile0 = rcDest.top + dy;

	// Datum
	CTime   date = CTime::GetCurrentTime();
	if ( m_bDatum )
	{
		text.Empty();
		text.printf( "%d.%d.%d", date.GetDay(), date.GetMonth(), date.GetYear());
		PrintText( pDC, m_pFntFett, spalte11, zeile0 - 4*dy, "Datum:" );
		PrintText( pDC, NULL, spalte12, zeile0 - 4*dy, text );
	}

	// Kundennummer / IDE
	if ( m_strNFP1_KASS.IsEmpty())
	{
		text = "Grundstücksidentifikationsnummer:  ";
		text += m_strIDE;
	}
	else
	{
		text = "Grundstücksidentifikationsnummer:  ";
		text += m_strIDE;
		PrintText( pDC, m_pFntFett, spalte7, zeile0 + 0.5*dy, text );

		text = "Kundennummer:  ";
		text += m_strNFP1_KASS;
	}
	PrintText( pDC, m_pFntAnschrift, spalte0 + dx, zeile0, text );
	PrintText( pDC, NULL, spalte0 + dx, zeile0 + 1.5*dy, "(bei Überweisung bitte angeben)" );

	CxString	option, temp;
	CFont		*pFont;
	short		j;
	int			xPos, yOffset, zeile;

	zeile = zeile0 + 4*dy;
	for ( i = 0; i < m_arrText.GetSize(); i++ )
	{
		text = m_arrText[i];
		option = m_arrInfo[i];
		option.MakeUpper();

		pFont = m_pFntBeitrag;
		if ( option.Find( "FETT" ) >= 0 )	pFont = m_pFntBeitragFett;
		if ( option.Find( "KLEIN" ) >= 0 )
		{
			pFont = NULL;
			if ( option.Find( "FETT" ) >= 0 )	pFont = m_pFntFett;
		}

		xPos = spalte0;
		if (( j = option.Find( "X=" )) >= 0 )
		{
			temp = option.Mid( j + 2 );
			j = atoi( temp );
			switch ( j )
			{
			case 1:		xPos = spalte1;		break;
			case 2:		xPos = spalte2;		break;
			case 3:		xPos = spalte3;		break;
			case 4:		xPos = spalte4;		break;
			case 5:		xPos = spalte5;		break;
			case 6:		xPos = spalte6;		break;
			case 7:		xPos = spalte7;		break;
			case 8:		xPos = spalte8;		break;
			case 9:		xPos = spalte9;		break;
			case 10:	xPos = spalte10;	break;
			case 11:	xPos = spalte11;	break;
			case 12:	xPos = spalte12;	break;
			}
		}

		yOffset = 0;
		if (( j = option.Find( "O=" )) >= 0 )
		{
			temp = option.Mid( j + 2 );
			j = atoi( temp );
			yOffset = dy*j;
		}
		else
		{
			if (( j = option.Find( "L=" )) >= 0 )
			{
				temp = option.Mid( j + 2 );
				j = atoi( temp ) + 1;
				zeile += dy*j;
			}
			else
				zeile += dy;
		}

		PrintText( pDC, pFont, xPos, zeile - yOffset, text );
	}
// nach dem letzten Text: Font zurücksetzen
	if ( pOldFont )		pDC -> SelectObject( pOldFont );

}	// Print Anlage 7

void CPrintAnlage7::SetupDataString( CString& text )
{
	CxString	teil1, teil2, rest, item;
	short		i;

	rest = text;
	while ( rest.Find( "<<" ) >= 0 )
	{
		i = rest.Find( "<<" );
		if ( i > 0 )
			teil1 += rest.Left( i );
		rest = rest.Mid( i + 2 );
		item.Empty();
		i = rest.Find( ">>" );
		if ( i >= 0 )
		{
			if ( i > 0 )	item = rest.Left( i );
			rest = rest.Mid( i + 2 );
			if ( item == "NFP1_IDE" )
				teil1 += m_strIDE;
			else if ( item == "NFP1_AGG" )
				teil1 += m_strNFP1_AGG;
			else if ( item == "NFP1_BDM" )
				teil1 += m_strNFP1_BDM;
			else if ( item == "NFP1_EAN" )
				teil1 += m_strNFP1_EAN;
			else if ( item == "NFP1_ENA" )
				teil1 += m_strNFP1_ENA;
			else if ( item == "NFP1_EOR" )
				teil1 += m_strNFP1_EOR;
			else if ( item == "NFP1_EPL" )
				teil1 += m_strNFP1_EPL;
			else if ( item == "NFP1_FLU" )
				teil1 += m_strNFP1_FLU;
			else if ( item == "NFP1_FST" )
				teil1 += m_strNFP1_FST;
			else if ( item == "NFP1_GFZ" )
				teil1 += m_strNFP1_GFZ;
			else if ( item == "NFP1_KASS" )
				teil1 += m_strNFP1_KASS;
			else if ( item == "NFP1_ORT" )
				teil1 += m_strNFP1_ORT;
			else if ( item == "NFP1_VGZ" )
				teil1 += m_strNFP1_VGZ;
			else if ( item == "STR_DECO" )
				teil1 += m_strSTR_DECO;
			else if ( item == "VOLLIE2" )
				teil1 += m_strVOLLIE2;
			else if ( item == "VOLLIE3" )
				teil1 += m_strVOLLIE3;
			else if ( item == "VOLLGESCH" )
				teil1 += m_strVOLLGESCH;
			else if ( item == "RW_FL_GE" )
				teil1 += m_strRW_FL_GE;
			else if ( item == "RW_FL_RU" )
				teil1 += m_strRW_FL_RU;
			else if ( item == "RW_DM_JA" )
				teil1 += m_strRW_DM_JA;
			else if ( item == "RW_DM_QA" )
				teil1 += m_strRW_DM_QA;
		}
	}

	text  = teil1;
	text += rest;
}


///////////////////////////////////////////////////////////////////////
CPrintAnlage8::CPrintAnlage8( const char* ide, long enr )
{
	ASSERT( AfxIsValidString( ide ));
	m_strIDE = ide;
	m_bInitialisiert = FALSE;
	m_cKennung = '8';

	m_lrTRiAS.left   = -1L;
	m_lrTRiAS.top    = -1L;
	m_lrTRiAS.right  = -1L;
	m_lrTRiAS.bottom = -1L;

	m_hMetaFile = NULL;
	m_sizeTopLeftOffset.cx = 0;
	m_sizeTopLeftOffset.cy = 0;
	m_bNeuerOffset = TRUE;

	m_strViewName = "Druckblatt 1";
}

CPrintAnlage8::~CPrintAnlage8()
{
	if ( m_hMetaFile )	DeleteEnhMetaFile( m_hMetaFile );
	m_hMetaFile = NULL;
}

BOOL CPrintAnlage8::Init()
{
	if ( m_bInitialisiert )		return TRUE;
	m_bInitialisiert = TRUE;

	CString			text;

	text = GetAnsichtName( "8" );
	if ( !text.IsEmpty())
		m_strViewName = text;

	return TRUE;
}	// Init

void CPrintAnlage8::Print( CDC* pDC )
{
	CxString	text, param;
	Init();

	CRect rcDest;

	// get size of printer page (in pixels)
	int cxPage = pDC->GetDeviceCaps(HORZRES);
	int cyPage = pDC->GetDeviceCaps(VERTRES);
	// get printer pixels per inch
	int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
	int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

// Hauptrahmen
	rcDest.top = cyInch / 2;				// oben 1/2 Zoll
	rcDest.bottom = cyPage - cyInch / 2;	// unten ebenso
	rcDest.left = cxInch * 3 / 4;			// links 3/4 Zoll
	rcDest.right = cxPage - cxInch / 2;		// rechts 1/2 Zoll
	pDC -> Rectangle( rcDest );

// Rahmen für die Karte
	rcDest.top = cyInch * 2;					// oben 2 Zoll
	rcDest.left = cxInch;
	rcDest.right = cxPage - cxInch * 3 / 4;
	rcDest.bottom = cyInch * 2 + rcDest.right - rcDest.left;

	int xDiff, yDiff;

	xDiff = cxInch / 20;
	yDiff = cyInch / 20;

	CRect   rect = rcDest;
	rect.top -= yDiff - xDiff;
	rect.bottom += yDiff + xDiff;
	rect.left -= xDiff - xDiff;
	rect.right += xDiff + xDiff;
	for ( short i = 0; i < xDiff; i +=2 )
	{
		pDC -> Rectangle( rect );
		rect.top -= 2;
		rect.bottom -= 2;
		rect.left -= 2;
		rect.right -= 2;
	}
	rect.top    += xDiff;
	rect.bottom += xDiff;
	rect.left   += xDiff;
	rect.right  += xDiff;

	rcDest.top    += 2;
	rcDest.bottom -= 2;
	rcDest.left   += 2;
	rcDest.right  -= 2;

	CSize   size;
	CFont   *pOldFont = NULL;

	pOldFont = pDC -> SelectObject( m_pFntNormal );

	text = "E";
	size = pDC -> GetTextExtent( text, text.GetLength());
	int dy = size.cy * 12 / 10;

	int spalte0  = cxInch * 5 / 4;
	int spalte1  = spalte0 + cxInch/2;
	
	int zeile0 = cyInch/2 + dy;

// Kopftexte

	text = "Massstabsgerechte Lageskizze";
	PrintText( pDC, m_pFntUeberschrift, spalte0, zeile0, text );

	PrintText( pDC, m_pFntFett, spalte0, zeile0 + 2*dy, "Identifikationsnummer:" );
	PrintText( pDC, NULL, spalte0 + cxInch, zeile0 + 2*dy, m_strIDE );

// zeile0 korrigieren!!
	zeile0 = rcDest.bottom + 3*dy;

// Karte eindrucken (wenn vorhanden)
	if ( m_lONr < 0L )	m_lONr = GetObjNr( m_strIDE );

	if ( m_lONr <= 0L )
	{
		SelectTRiASProject( GetProjectName( m_strIDE ));
		m_lONr = GetObjNr( m_strIDE );
	}

	BerechneMasstab( pDC, m_lONr, m_lrTRiAS, &rcDest );

	text = "Massstab:  ca. 1 : ";
	param.Empty();
	param.AppendFormated( m_lMasstab, -1 );
	text += param;
	PrintText( pDC, NULL, spalte0, zeile0 + 2*dy, text );

// nach dem letzten Text: Font zurücksetzen
	if ( pOldFont )		pDC -> SelectObject( pOldFont );

	BOOL	bNeedsPrepare = ( m_hMetaFile == NULL );

	if ( bNeedsPrepare )
	{
		SelectTRiASView( m_strViewName );
		PrepareObjColor( m_lONr, TRUE );
	}
	RenderTRiASAusschnittDirekt( pDC, "", m_lONr, m_lrTRiAS, &rcDest );
//	RenderTRiASAusschnitt( pDC, "", m_lONr, m_lrTRiAS, &rcDest );
	if ( bNeedsPrepare )
		ResetObjColor( m_lONr, TRUE );

}	// Print Anlage 8

void CPrintAnlage8::BerechneMasstab( CDC* pDC, long onr, RECTL& cont, CRect* rcDest )
{
	BOOL	abbruch = FALSE;
	CSize	size;
	CRect	rcTemp;
	long	c[4];

	size.cx = rcDest -> left;
	size.cy = rcDest -> top;
	pDC -> LPtoHIMETRIC( &size );
	rcTemp.left = size.cx;
	rcTemp.top  = size.cy;
	size.cx = rcDest -> right;
	size.cy = rcDest -> bottom;
	pDC -> LPtoHIMETRIC( &size );
	rcTemp.right  = size.cx;
	rcTemp.bottom = size.cy;

	if ( m_hMetaFile == NULL )
	{
		if ( !GetTriasObjContainer( onr, (long*)c ))
			abbruch = TRUE;

		if ( !abbruch )
		{
			cont.left   = c[0];
			cont.top    = c[3];
			cont.right  = c[1];
			cont.bottom = c[2];

			long	dx, dy;
			dx = long(( cont.right - cont.left ) * 0.2 );
			dy = long(( cont.bottom - cont.top ) * 0.2 );
			cont.left   -= dx;
			cont.right  += dx;
			cont.top    -= dy;
			cont.bottom += dy;
		}
	}
	
	int		iPaperSizeX = rcTemp.Width();				// Breite und Höhe des
	int		iPaperSizeY = rcTemp.Height();				// Ausschnittes in Pixeln
	long	lKarteSizeX = labs( cont.left - cont.right );	// Breite und Höhe des
	long	lKarteSizeY = labs( cont.top - cont.bottom );	// Ausschnittes in m (?)
//	int		cxInch = pDC -> GetDeviceCaps( LOGPIXELSX );
//	int		cyInch = pDC -> GetDeviceCaps( LOGPIXELSY );
//	iPaperSizeX = iPaperSizeX / ( cxInch * 10 / 567 );
//	iPaperSizeY = iPaperSizeY / ( cyInch * 10 / 567 );

	long	lX, lY;
//	lX = (long)((double)iPaperSizeX / lKarteSizeX * 100000.0 );
//	lY = (long)((double)iPaperSizeY / lKarteSizeY * 100000.0 );
	lX = (long)((double)lKarteSizeX / iPaperSizeX * 100 );
	lY = (long)((double)lKarteSizeY / iPaperSizeY * 100 );
	if ( lX > lY )	m_lMasstab = lX;
	else			m_lMasstab = lY;

	if ( m_lMasstab < 100 )			m_lMasstab = 100;
	else if ( m_lMasstab < 200 )	m_lMasstab = 200;
	else if ( m_lMasstab < 250 )	m_lMasstab = 250;
	else if ( m_lMasstab < 300 )	m_lMasstab = 300;
	else if ( m_lMasstab < 500 )	m_lMasstab = 500;
	else if ( m_lMasstab < 750 )	m_lMasstab = 750;
	else if ( m_lMasstab < 1000 )	m_lMasstab = 1000;
	else if ( m_lMasstab < 1500 )	m_lMasstab = 1500;
	else if ( m_lMasstab < 2000 )	m_lMasstab = 2000;
	else if ( m_lMasstab < 2500 )	m_lMasstab = 2500;
	else if ( m_lMasstab < 3000 )	m_lMasstab = 3000;
	else if ( m_lMasstab < 4000 )	m_lMasstab = 4000;
	else if ( m_lMasstab < 5000 )	m_lMasstab = 5000;
	else if ( m_lMasstab < 6000 )	m_lMasstab = 6000;
	else if ( m_lMasstab < 7500 )	m_lMasstab = 7500;
	else if ( m_lMasstab < 8000 )	m_lMasstab = 8000;
	else if ( m_lMasstab < 9000 )	m_lMasstab = 9000;
	else if ( m_lMasstab < 10000 )	m_lMasstab = 10000;

	long	lDelta;
	if ( lX > lY )
	{
		lDelta = ( lKarteSizeX * m_lMasstab / lX - lKarteSizeX ) / 2;
		cont.left -= lDelta;
		cont.right += lDelta;
	}
	else
	{
		lDelta = ( lKarteSizeY * m_lMasstab / lY - lKarteSizeY ) / 2;
		cont.top -= lDelta;
		cont.bottom += lDelta;
	}
}

///////////////////////////////////////////////////////////////////////
CString CPrintAnlage::GetAnsichtName( const char* anla_id )
{
	CxString	text, item;
	CString		result;
//	char		*txt;

//	text.Empty();
//	txt = text.GetBuffer( 256 );
	item.Empty();
	item += m_cKennung;
//	GetPrivateProfileString( "Texte", item, "", txt, 256, "GBM.INI" );
//	text.ReleaseBuffer();
	text = GetVorlageFileName( m_cKennung );
	if ( text.IsEmpty())		return result;
	if ( !FileExist( text ))	return result;

	TRY
	{
		CStdioFile file( text, CFile::modeRead|CFile::typeText );
		while ( file.ReadString( text ))
		{
			item.Empty();
			if ( text[0] != ';' )		// Kommentar überlesen
			{
				if ( text[0] == '#' )
				{
					text = text.Mid( 1 );
					text.Teilen( item, text, '=' );
					item.MakeUpper();
					if ( item == "ANSICHT" )	result = text;
					if ( item == "LEGENDCOLOR" )	m_strColor = text;
				}
			}
		}

		file.Close();
	}
	CATCH( CFileException, e )
	{
		#ifdef _DEBUG
		afxDump << "Datei '" << text << "' kann nicht geöffnet werden! " << e->m_cause << "\n";
		#endif
	}
	END_CATCH

	return result;
}

short CPrintAnlage5::GetLegendHatch( short n, const char* id )
{
// HS_HORIZONTAL       0
// HS_VERTICAL         1
// HS_FDIAGONAL        2
// HS_BDIAGONAL        3
// HS_CROSS            4
// HS_DIAGCROSS        5
	short	result = -1;
	CString	color, c;
//	short	i;

//	for ( i = 0; i < 10; i++ )
//		if ( m_strID[i] == id )
//			color = m_strColor[i];

	color = m_strColor;
	if ( color.GetLength() < 20 )
		color = "x255255000x255180000";

	if ( n == 1 )
	{
		if ( color.GetLength() > 1 )
		{
			switch (color[0])
			{	case 'H':	result = HS_HORIZONTAL;
							break;
				case 'V':	result = HS_VERTICAL;
							break;
				case 'F':	result = HS_FDIAGONAL;
							break;
				case 'B':	result = HS_BDIAGONAL;
							break;
				case 'C':	result = HS_CROSS;
							break;
				case 'D':	result = HS_DIAGCROSS;
							break;
	}	}	}
	else if ( n == 2 )
	{
		if ( color.GetLength() > 11 )
		{
			c = color.Left(11);
			c = c.Right(1);
			switch (c[0])
			{	case 'H':	result = HS_HORIZONTAL;
							break;
				case 'V':	result = HS_VERTICAL;
							break;
				case 'F':	result = HS_FDIAGONAL;
							break;
				case 'B':	result = HS_BDIAGONAL;
							break;
				case 'C':	result = HS_CROSS;
							break;
				case 'D':	result = HS_DIAGCROSS;
							break;
	}	}	}

	return result;
}

COLORREF CPrintAnlage5::GetLegendColor( short n, const char* id )
{
	COLORREF	result = RGB( 255, 0, 0 );
	CString	color, r,g,b;
//	short	i;

//	for ( i = 0; i < 10; i++ )
//		if ( m_strID[i] == id )
//			color = m_strColor[i];

	color = m_strColor;
	if ( color.GetLength() < 20 )
		color = "x255255000x255180000";

	if ( n == 1 )
	{
		if ( color.GetLength() > 10 )
		{
			r = color.Left( 4 );
			r = r.Right( 3 );
			g = color.Left( 7 );
			g = g.Right( 3 );
			b = color.Left( 10 );
			b = b.Right( 3 );

			result = RGB( atoi( r ), atoi( g ), atoi( b ));
	}	}
	else if ( n == 2 )
	{
		if ( color.GetLength() >= 20 )
		{
			r = color.Left( 14 );
			r = r.Right( 3 );
			g = color.Left( 17 );
			g = g.Right( 3 );
			b = color.Left( 20 );
			b = b.Right( 3 );

			result = RGB( atoi( r ), atoi( g ), atoi( b ));
	}	}

	return result;
}

int CPrintAnlage::PrintLogo( CDC *pDC, int x1, int x2, int y, const char* filename, const char* position )
{
	CFileBitmap		fb( filename );
	CString			pos;
	int				size, result = 0;

	if ( NULL != fb.GetHDIB())
	{
		HDIB	hDIB = fb.GetHDIB();

		if ( AfxIsValidString( position ))	pos = position;
		else								pos = "L4";

		size = atoi( pos.Right( 1 ));
		pos = pos.Left( 1 );
		if ( size < 1 )		size = 1;
		if ( size > 5 )		size = 5;

		if ( NULL != hDIB )
		{
			LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) hDIB);
			int cxDIB = (int) ::DIBWidth(lpDIB);         // Size of DIB - x
			int cyDIB = (int) ::DIBHeight(lpDIB);        // Size of DIB - y
			::GlobalUnlock((HGLOBAL) hDIB);
			CRect rcDIB;
			rcDIB.top = rcDIB.left = 0;
			rcDIB.right = cxDIB;
			rcDIB.bottom = cyDIB;
			CRect rcDest;
//			if (pDC->IsPrinting())   // printer DC
			{
				// get size of printer page (in pixels)
				int cxPage = pDC->GetDeviceCaps(HORZRES);
				int cyPage = pDC->GetDeviceCaps(VERTRES);
				// get printer pixels per inch
				int cxInch = pDC->GetDeviceCaps(LOGPIXELSX);
				int cyInch = pDC->GetDeviceCaps(LOGPIXELSY);

				//
				// Best Fit case -- create a rectangle which preserves
				// the DIB's aspect ratio, and fills the page horizontally.
				//
				// The formula in the "->bottom" field below calculates the Y
				// position of the printed bitmap, based on the size of the
				// bitmap, the width of the page, and the relative size of
				// a printed pixel (cyInch / cxInch).
				//
				rcDest.top = rcDest.left = 0;
				rcDest.bottom = (int)(((double)cyDIB * cxPage * cyInch )
						/ ((double)cxDIB * cxInch * size ));
				rcDest.right = (int)((double)cxPage / size );
			}
//			else   // not printer DC
//			{
//				rcDest = rcDIB;
//			}

			rcDest.top    += y;
			rcDest.bottom += y;

			if ( pos == "R" )
			{
				int		dx = x2 - rcDest.right;
				rcDest.left   += dx;
				rcDest.right  += dx;
			}
			else
			{
				rcDest.left   += x1;
				rcDest.right  += x1;
			}

			result = rcDest.bottom;

			::PaintDIB( pDC->m_hDC, &rcDest, fb.GetHDIB(), &rcDIB, fb.GetDocPalette());
		}
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////
// CFileBitmap
CFileBitmap::CFileBitmap( const char* filename )
{
	CxString	strName;

	ASSERT( AfxIsValidString( filename ));
	strName = filename;
	ASSERT( strName.FileExist());

	m_strFileName = strName;

	m_hDIB = NULL;
	m_palDIB = NULL;
	m_sizeDoc = CSize(1,1);

	CFile			file;
	CFileException	fe;

	if ( !file.Open( m_strFileName, CFile::modeRead|CFile::shareDenyWrite, &fe ))
	{
//		ReportSaveLoadException(lpszPathName, &fe, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		return;
	}

//	DeleteContents();
//	BeginWaitCursor();

	TRY
	{
		m_hDIB = ::ReadDIBFile(file);
	}
	CATCH (CFileException, eLoad)
	{
		file.Abort(); // will not throw an exception
//		EndWaitCursor();
//		ReportSaveLoadException(lpszPathName, eLoad, FALSE, AFX_IDP_FAILED_TO_OPEN_DOC);
		m_hDIB = NULL;
		return;
	}
	END_CATCH

	InitDIBData();
//	EndWaitCursor();

	if (m_hDIB == NULL)
	{
		// may not be DIB format
//		CString strMsg;
//		strMsg.LoadString(IDS_CANNOT_LOAD_DIB);
//		MessageBox(NULL, strMsg, NULL, MB_ICONINFORMATION | MB_OK);
		return;
	}
}

CFileBitmap::~CFileBitmap()
{
	if (m_hDIB != NULL)
	{
		::GlobalFree((HGLOBAL) m_hDIB);
	}
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
	}
}

HDIB CFileBitmap::GetHDIB()
{
	return m_hDIB;
}

void CFileBitmap::InitDIBData()
{
	if (m_palDIB != NULL)
	{
		delete m_palDIB;
		m_palDIB = NULL;
	}
	if (m_hDIB == NULL)
	{
		return;
	}
	// Set up document size
	LPSTR lpDIB = (LPSTR) ::GlobalLock((HGLOBAL) m_hDIB);
	if (::DIBWidth(lpDIB) > INT_MAX ||::DIBHeight(lpDIB) > INT_MAX)
	{
		::GlobalUnlock((HGLOBAL) m_hDIB);
		::GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB = NULL;
//		CString strMsg;
//		strMsg.LoadString(IDS_DIB_TOO_BIG);
//		MessageBox(NULL, strMsg, NULL, MB_ICONINFORMATION | MB_OK);
		return;
	}
	m_sizeDoc = CSize((int) ::DIBWidth(lpDIB), (int) ::DIBHeight(lpDIB));
	::GlobalUnlock((HGLOBAL) m_hDIB);
	// Create copy of palette
	m_palDIB = new CPalette;
	if (m_palDIB == NULL)
	{
		// we must be really low on memory
		::GlobalFree((HGLOBAL) m_hDIB);
		m_hDIB = NULL;
		return;
	}
	if (::CreateDIBPalette(m_hDIB, m_palDIB) == NULL)
	{
		// DIB may not have a palette
		delete m_palDIB;
		m_palDIB = NULL;
		return;
	}
}

void CPrintAnlage8::RenderTRiASAusschnittDirekt( CDC* pDC, const char* view, long onr, RECTL& cont, CRect* rcDest )
{
	BOOL	abbruch = FALSE;
	CSize	size;
	RECT	rcPict;
	RECTL	rclClipBox, rclFrame;
	long	c[4];
	size.cx = rcDest -> left;
	size.cy = rcDest -> top;
	pDC -> LPtoHIMETRIC( &size );
	rcDest -> left = size.cx;
	rcDest -> top  = size.cy;
	size.cx = rcDest -> right;
	size.cy = rcDest -> bottom;
	pDC -> LPtoHIMETRIC( &size );
	rcDest -> right  = size.cx;
	rcDest -> bottom = size.cy;

	rclFrame.left   = rcDest -> left;
	rclFrame.right  = rcDest -> right;
	rclFrame.top    = - rcDest -> top;
	rclFrame.bottom = - rcDest -> bottom;

	rclClipBox.left   = rclFrame.left + 100;
	rclClipBox.right  = rclFrame.right - 100;
	rclClipBox.top    = rclFrame.top - 100;
	rclClipBox.bottom = rclFrame.bottom + 100;
/*
	if ( m_hMetaFile == NULL )
	{
		if ( !GetTriasObjContainer( onr, (long*)c ))
			abbruch = TRUE;

		if ( !abbruch )
		{
			cont.left   = c[0];
			cont.top    = c[3];
			cont.right  = c[1];
			cont.bottom = c[2];

			long	dx, dy;
			dx = long(( cont.right - cont.left ) * 0.2 );
			dy = long(( cont.bottom - cont.top ) * 0.2 );
			cont.left   -= dx;
			cont.right  += dx;
			cont.top    -= dy;
			cont.bottom += dy;
		}
	}
*/
	if ( !abbruch )
	{
		if ( m_hMetaFile == NULL )
		{
//			DEX_RePaintWait();
			DEX_RePaintWait();

			RENDERGEODB		sRend;
			RECTL			rectl;
			HDC				hdcMetaFile;
			int				oldMapMode;

			::SaveDC( pDC -> m_hAttribDC );

			oldMapMode = ::SetMapMode( pDC -> m_hAttribDC, MM_HIMETRIC );

			rectl.bottom = labs( rclFrame.bottom - rclFrame.top );
			rectl.top    = 0L;
			rectl.right  = labs( rclFrame.right - rclFrame.left );
			rectl.left   = 0L;
			rcPict.top    = rectl.top;
			rcPict.bottom = rectl.bottom;
			rcPict.left   = rectl.left;
			rcPict.right  = rectl.right;

			hdcMetaFile = CreateEnhMetaFile( pDC -> m_hAttribDC, NULL, &rcPict, NULL );

			sRend.dwSize              = sizeof( RENDERGEODB );
			sRend.m_hDC               = hdcMetaFile;
			sRend.m_hTargetDC         = pDC -> m_hAttribDC;

			sRend.m_rclFrame.left     = 0L;
			sRend.m_rclFrame.top      = rectl.bottom;
			sRend.m_rclFrame.right    = rectl.right;
			sRend.m_rclFrame.bottom   = 0L;
			sRend.m_rclClipBox        = sRend.m_rclFrame;

			sRend.m_rclGeoDB.left     = cont.left;
			sRend.m_rclGeoDB.top      = cont.top;
			sRend.m_rclGeoDB.right    = cont.right;
			sRend.m_rclGeoDB.bottom   = cont.bottom;

			::SetMapMode( hdcMetaFile, MM_HIMETRIC );
			::SetWindowOrgEx( hdcMetaFile, 0, (int)( sRend.m_rclFrame.top - sRend.m_rclFrame.bottom ), NULL );

			if ( hdcMetaFile )
			{
				DexExtensionProc((WPARAM)DEX_RENDERGEODB, (LPARAM)&sRend );
				m_hMetaFile = CloseEnhMetaFile( hdcMetaFile );
			}

			::SetMapMode( pDC -> m_hAttribDC, oldMapMode );
			::RestoreDC( pDC -> m_hAttribDC, -1 );
		}

		if ( m_hMetaFile )
		{
			CRect	DestRect;
			POINT	pt1, pt2;

			DestRect.bottom = rclFrame.bottom;
			DestRect.top    = rclFrame.top;
			DestRect.left   = rclFrame.left;
			DestRect.right  = rclFrame.right;

			if (( pDC -> IsKindOf( RUNTIME_CLASS( CPreviewDC ))) &&
				( m_bNeuerOffset ))
			{
				m_bNeuerOffset = FALSE;
			}

			int saveDC = pDC -> SaveDC();
			pDC -> SetMapMode( MM_HIMETRIC );
			if ( pDC -> IsKindOf( RUNTIME_CLASS( CPreviewDC )))
			{
				pt1.x = rclClipBox.left;
				pt1.y = rclClipBox.top;
				pt2.x = rclClipBox.right;
				pt2.y = rclClipBox.bottom;
				::LPtoDP( pDC -> m_hAttribDC, &pt1, 1 );
				::LPtoDP( pDC -> m_hAttribDC, &pt2, 1 );
				((CPreviewDC*)pDC ) -> PrinterDPtoScreenDP( &pt1 );
				((CPreviewDC*)pDC ) -> PrinterDPtoScreenDP( &pt2 );
				pt1.x += m_sizeTopLeftOffset.cx;
				pt1.y += m_sizeTopLeftOffset.cy;
				pt2.x += m_sizeTopLeftOffset.cx;
				pt2.y += m_sizeTopLeftOffset.cy;
				::DPtoLP( pDC -> m_hDC, &pt1, 1 );
				::DPtoLP( pDC -> m_hDC, &pt2, 1 );
			}
			else
			{
				pt1.x = rclClipBox.left;
				pt1.y = rclClipBox.top;
				pt2.x = rclClipBox.right;
				pt2.y = rclClipBox.bottom;
			}

			if ( pDC -> m_hDC != NULL )
			{
				::IntersectClipRect( pDC -> m_hDC, pt1.x, pt1.y, pt2.x, pt2.y );
				pDC -> PlayMetaFile( m_hMetaFile, &DestRect );
			}
			else
				::MessageBeep( -1 );
			pDC -> RestoreDC( saveDC );
		}
	}

	g_bRenderingInProgres = FALSE;
}	// RenderTRiASAusschnittDirekt
