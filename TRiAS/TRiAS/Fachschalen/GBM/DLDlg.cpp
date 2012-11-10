// DLDlg.cpp : implementation file
//

#include "bool.h"
#include "stdafx.h"
#include "GbmTRiAS.h"

#include "ResiWnd.h"
#include "DLDlg.h"

#include "ErfassPrivDlg.h"

#include "EdPage1.h"
#include "EdPage2.h"
#include "EdPage3.h"
#include "EdPage4.h"
#include "EdPage5.h"
#include "EdPage6.h"
#include "EditPage7.h"

#include "MyPropS.h"
#include "SuchPage0.h"
#include "SuchPage1.h"
#include "SuchPage2.h"
#include "SuchPage3.h"
#include "SuchPage4.h"

#include "SuchResDlg.h"
#include "GSTeilenDlg.h"
#include "SetOI.h"

#include "PrintAnlage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern UINT g_iGSTeilenMsg;

CPtrArray	*g_pArrONr = NULL;
CStringArray	*g_pArrIDE = NULL;
CDatenListeDlg	*g_pDatenListeDlg = NULL;

extern CTriDBSet* g_pSetTriDB;
extern CDatabase* g_pDatabase;
extern COPAngeschlGS* g_pOPAngeschlGS;
extern COPBeitragsartGS* g_pOPBeitragsartGS;
extern COPEigentumGS* g_pOPEigentumGS;
extern COPGedrucktGS* g_pOPGedrucktGS;
extern COPGedrucktGS* g_pOPGedruck2GS;

extern CSetNF_PG1* g_pNF_PG1;
extern CSetNF_PG2H* g_pNF_PG2H;
extern CSetNF_PG2D* g_pNF_PG2D;
extern CSetNF_PG1GB* g_pNF_PG1GB;
extern CSetNF_PG4* g_pNF_PG4;
extern int g_iMessageStatus;

/////////////////////////////////////////////////////////////////////////////
// CDatenListeDlg dialog

/*
CDatenListeDlg::CDatenListeDlg(CWnd* pParent )
	: CDialog(CDatenListeDlg::IDD, pParent)
{
}
*/
CDatenListeDlg::CDatenListeDlg( CWnd* pParent, short oisy, CSetNF_PG1* pNF )
{
	m_bBusy = FALSE;
	m_hWndRemove = NULL;
	m_iOISY = oisy;
	m_bGSTeilenAtWork = FALSE;

	m_pSetOrte = NULL;
	m_pSetStrasse = NULL;
//	m_pNF_PG1 = pNF;
//	m_pNF_PG1GB = NULL;
//	m_pNF_PG2D = NULL;
//	m_pNF_PG2H = NULL;
	m_pNF_PG3 = NULL;

	m_uiSelObjTimerID = 0;
	m_bSuspendSelObj = FALSE;
	m_uiSyncTimerID = 0;
	m_lAddedObjsSinceSync = 0L;
	m_lAddedObjsSinceTimer = 0L;

	m_lGSClassID = 0L;
	m_lGebClassID = 0L;
	m_lDTClassID = 0L;
	m_lHofClassID = 0L;

//	SECDialogBar::Create( pParent, CDatenListeDlg::IDD,
//		WS_CHILD | CBRS_ORIENT_ANY, CBRS_EX_STRETCH_ON_SIZE|CBRS_EX_ALLOW_MDI_FLOAT, 8888 );

//		WS_CHILD | CBRS_ORIENT_ANY, CBRS_EX_STRETCH_ON_SIZE, 101 );

//		WS_CHILD | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_ALIGN_RIGHT | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT,
//		CBRS_EX_STRETCH_ON_SIZE );

//	EnableDocking( CBRS_ALIGN_RIGHT|CBRS_ALIGN_LEFT );

//	if ( SECDialogBar::Create( pParent, CDatenListeDlg::IDD,
//		CBRS_RIGHT | WS_VISIBLE | CBRS_SIZE_DYNAMIC | CBRS_TOOLTIPS,
//		CBRS_EX_STDCONTEXTMENU | CBRS_EX_ALLOW_MDI_FLOAT |
//		CBRS_EX_STRETCH_ON_SIZE | CBRS_EX_COOL, 8887 ))
	if ( SECDialogBar::Create( pParent, CDatenListeDlg::IDD,
		CBRS_RIGHT | CBRS_SIZE_DYNAMIC,
		CBRS_EX_ALLOW_MDI_FLOAT | CBRS_EX_STRETCH_ON_SIZE, 8887 ))
	{
		EnableDocking(CBRS_ALIGN_ANY);
	} 
//	DockControlBarEx( this, AFX_IDW_DOCKBAR_BOTTOM, 1, 0, (float)0.40, 130);

	OnInitDialog();
	//{{AFX_DATA_INIT(CDatenListeDlg)
	m_strEigent = _T("");
	m_strFlur = _T("");
	m_strFlurstk = _T("");
	m_strIDE = _T("");
	m_strOrt = _T("");
	m_strStr = _T("");
	m_strGSFlaeche = _T("");
	m_strBFlaeche = _T("");
	m_strBeitrag = _T("");
	m_bDetailsDummy = FALSE;
	m_bSuchenDummy = FALSE;
	m_bLoeschen = FALSE;
	m_bBBGedr = FALSE;
	m_bGBGedr = FALSE;
	//}}AFX_DATA_INIT

	g_pArrONr = &m_arrAlleONr;
	g_pArrIDE = &m_arrAlleID;

	m_bDetailsDummy = FALSE;	// immer auf FALSE halten
	m_bSuchenDummy = FALSE;		// für Buttondarstellung

	m_cx = m_cy = -1;

	ShowSingleData( FALSE );

	g_pDatenListeDlg = this;
}

CDatenListeDlg::~CDatenListeDlg()
{
	g_pDatenListeDlg = NULL;

//	m_txtGBM.SetFont( m_pOldFontGBM );
//	m_FontGBM.DeleteObject();
//	if ( m_pNF_PG1 )	delete m_pNF_PG1;	// nur geliehen!!
//	m_pNF_PG1 = NULL;

	if ( 0 != m_uiSyncTimerID )
		KillTimer( m_uiSyncTimerID );

//	CPrintAnlage1	*pPA;
//	pPA = new CPrintAnlage1( "XX" );
//	pPA -> DeleteStaticMembers();
	ResetInvalidDockBars( this );
}

void CDatenListeDlg::DoDataExchange(CDataExchange* pDX)
{
//	CDialog::DoDataExchange(pDX);
	SECDialogBar::DoDataExchange(pDX);
//	DDX_Control(pDX, IDC_LOGO, m_staticLogo);
	//{{AFX_DATA_MAP(CDatenListeDlg)
	DDX_Control(pDX, IDC_MINSIZETEXT, m_txtError);
	DDX_Control(pDX, IDC_BTEXT6, m_txtBText6);
	DDX_Control(pDX, IDC_BTEXT7, m_txtBText7);
	DDX_Control(pDX, IDC_LOESCHEN, m_btnLoeschen);
	DDX_Control(pDX, IDC_BGEDR, m_btnGedr);
	DDX_Control(pDX, IDC_BGEDR2, m_btnGedr2);
	DDX_Control(pDX, IDC_DETAILS, m_btnDetails);
	DDX_Control(pDX, IDC_TEXT12, m_txtText12);
	DDX_Control(pDX, IDC_TEXT11, m_txtText11);
	DDX_Control(pDX, IDC_TEXT10, m_txtText10);
	DDX_Control(pDX, IDC_TEXT0, m_txtText0);
	DDX_Control(pDX, IDC_SUMME3, m_txtSumme3);
	DDX_Control(pDX, IDC_SUMME2, m_txtSumme2);
	DDX_Control(pDX, IDC_SUMME1, m_txtSumme1);
	DDX_Control(pDX, IDC_SUCHEN, m_btnSuchen);
	DDX_Control(pDX, IDC_EIGENT, m_txtEigent);
	DDX_Control(pDX, IDC_FLURSTK, m_txtFlurStk);
	DDX_Control(pDX, IDC_FLUR, m_txtFlur);
	DDX_Control(pDX, IDC_STR, m_txtStr);
	DDX_Control(pDX, IDC_ORT, m_txtOrt);
	DDX_Control(pDX, IDC_IDE, m_txtIDE);
	DDX_Control(pDX, IDC_BTEXT5, m_txtBText5);
	DDX_Control(pDX, IDC_BTEXT4, m_txtBText4);
	DDX_Control(pDX, IDC_BTEXT3, m_txtBText3);
	DDX_Control(pDX, IDC_BTEXT2, m_txtBText2);
	DDX_Control(pDX, IDC_BTEXT1, m_txtBText1);
	DDX_Control(pDX, IDC_BTEXT0, m_txtBText0);
	DDX_Control(pDX, IDC_LIST1, m_lbListe);
	DDX_Text(pDX, IDC_EIGENT, m_strEigent);
	DDX_Text(pDX, IDC_FLUR, m_strFlur);
	DDX_Text(pDX, IDC_FLURSTK, m_strFlurstk);
	DDX_Text(pDX, IDC_IDE, m_strIDE);
	DDX_Text(pDX, IDC_ORT, m_strOrt);
	DDX_Text(pDX, IDC_STR, m_strStr);
	DDX_Text(pDX, IDC_SUMME1, m_strGSFlaeche);
	DDX_Text(pDX, IDC_SUMME2, m_strBFlaeche);
	DDX_Text(pDX, IDC_SUMME3, m_strBeitrag);
	DDX_Check(pDX, IDC_DETAILS, m_bDetailsDummy);
	DDX_Check(pDX, IDC_SUCHEN, m_bSuchenDummy);
	DDX_Check(pDX, IDC_LOESCHEN, m_bLoeschen);
	DDX_Check(pDX, IDC_BGEDR, m_bBBGedr);
	DDX_Check(pDX, IDC_BGEDR2, m_bGBGedr);
	//}}AFX_DATA_MAP
}

#include "sectlf.h"

BOOL CDatenListeDlg::OnInitDialog() 
{
//	CDialog::OnInitDialog();
//	SECDialogBar::OnInitDialog();	gibt es nicht!!
	UpdateData( FALSE );		// Anstelle des CDialog::OnInitDialog

	CRect	rect;

	GetWindowRect( &rect );
	m_lMinHeight  = rect.Height();
	m_lStartWidth = rect.Width();

	BeginWaitCursor();

	m_arrResizeItem.SetParent( this );
	m_arrResizeItem.m_bSpezialItem = TRUE;
	m_arrResizeItem.AddItem( &m_txtError, MitteOben );
//	m_arrResizeItem.AddItem( &m_staticLogo, LinksOben );
	m_arrResizeItem.AddItem( &m_txtText0,   LinksOben );
	m_arrResizeItem.AddItem( &m_lbListe,    Mitte );
	m_arrResizeItem.AddItem( &m_txtText10,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtText11,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtText12,  LinksUnten );
	m_arrResizeItem.AddItem( &m_btnDetails, LinksUnten );
	m_arrResizeItem.AddItem( &m_btnSuchen,  LinksUnten );
	m_arrResizeItem.AddItem( &m_btnLoeschen,LinksUnten );
	m_arrResizeItem.AddItem( &m_txtBText0,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtBText1,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtBText2,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtBText3,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtBText4,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtBText5,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtBText6,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtBText7,  LinksUnten );
	m_arrResizeItem.AddItem( &m_btnGedr,    LinksUnten );
	m_arrResizeItem.AddItem( &m_btnGedr2,   LinksUnten );
	m_arrResizeItem.AddItem( &m_txtEigent,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtFlur,    LinksUnten );
	m_arrResizeItem.AddItem( &m_txtFlurStk, LinksUnten );
	m_arrResizeItem.AddItem( &m_txtIDE,     LinksUnten );
	m_arrResizeItem.AddItem( &m_txtOrt,     LinksUnten );
	m_arrResizeItem.AddItem( &m_txtStr,     LinksUnten );
	m_arrResizeItem.AddItem( &m_txtSumme1,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtSumme2,  LinksUnten );
	m_arrResizeItem.AddItem( &m_txtSumme3,  LinksUnten );
	m_arrResizeItem.Init();


	CString		strID;

//	if ( m_pNF_PG1 == NULL )
//		m_pNF_PG1 = new CSetNF_PG1;
	ASSERT( g_pNF_PG1 );

	OISY2String( m_iOISY, strID );
	g_pNF_PG1 -> InitListen( strID );
	if ( g_pNF_PG1 -> GetSize() == 0 )
	{
		g_pNF_PG1 -> Reset();
		OISY2String2( m_iOISY, strID );
		g_pNF_PG1 -> InitListen( strID );
	}

	RefreshGebDB();
	RefreshDTDB();
	RefreshVFDB();

	if ( m_pNF_PG3 == NULL )
		m_pNF_PG3 = new CSetNF_PG3( g_pDatabase );
	ASSERT( m_pNF_PG3 );
	m_pNF_PG3 -> InitListen( strID );

	if ( m_pSetOrte == NULL )
		m_pSetOrte = new COrteSet( g_pDatabase );

	if ( m_pSetOrte != NULL )
	{
		m_pSetOrte -> InitListen();
		m_pSetOrte -> MoveFirst();
		while ( !m_pSetOrte -> IsEOF())
		{
			m_arrOrte.SetAtGrow((int)m_pSetOrte -> m_ORT_ISY, m_pSetOrte -> m_ORT_NAM );
			m_pSetOrte -> MoveNext();
		}
	}

	EndWaitCursor();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//BEGIN_MESSAGE_MAP(CDatenListeDlg, CDialog)
BEGIN_MESSAGE_MAP(CDatenListeDlg, SECDialogBar)
	//{{AFX_MSG_MAP(CDatenListeDlg)
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeListe)
	ON_BN_CLICKED(ID_DETAILS, OnDetails)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(ID_SUCHEN, OnSuchen)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_BN_CLICKED(IDC_BGEDR, OnBGedr)
	ON_BN_CLICKED(IDC_LOESCHEN, OnLoeschen)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_DETAILS, OnDetails)
	ON_BN_CLICKED(IDC_SUCHEN, OnSuchen)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BGEDR2, OnGGedr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatenListeDlg message handlers

void CDatenListeDlg::ResetListe()
{
	m_arrID.RemoveAll();
	m_arrONr.RemoveAll();
	m_arrSelectedONr.RemoveAll();
	m_arrSelectedIDE.RemoveAll();
	m_strGSFlaeche.Empty();
	m_strBFlaeche.Empty();
	m_strBeitrag.Empty();
	UpdateData( FALSE );
	m_hWndRemove = NULL;
}

void CDatenListeDlg::RefreshListe()
{
	CString		name;
	long		onr;
	short		i, j;
	int			index;
	BOOL		selected;

	m_strGSFlaeche.Empty();
	m_strBFlaeche.Empty();
	m_strBeitrag.Empty();
	UpdateData( FALSE );

	BeginWaitCursor();
	m_lbListe.ResetContent();
	for ( i = 0; i < m_arrID.GetSize(); i++ )
	{
		name = m_arrID[i];
		onr = (long)m_arrONr[i];
		index = LB_ERR;
		if ( !name.IsEmpty())	index = m_lbListe.AddString( name );

		selected = FALSE;
		if ( index != LB_ERR )
			for ( j = 0; j < m_arrSelectedONr.GetSize(); j++ )
				if ((long)m_arrSelectedONr[j] == onr )
				{
					selected = TRUE;
					break;
				}
		if ( selected )
			m_lbListe.SetSel( index, TRUE );
	}

	for ( i = 0; i < m_lbListe.GetCount(); i++ )
	{
		if ( m_lbListe.GetSel( i ) > 0 )
		{
			m_lbListe.SetTopIndex( i );
			i = m_lbListe.GetCount();
		}
	}

	EndWaitCursor();
	ShowSingleData( m_arrSelectedONr.GetSize() == 1 );
}

void CDatenListeDlg::InitClassIDs()
{
	if ( 0L != m_lGSClassID )	return;

	CString		text;

	text.LoadString( IDS_GS_CLASSNAME );
	m_lGSClassID = DEX_GetIdentFromClassName( (const char*)text );
	text.LoadString( IDS_GEB_CLASSNAME );
	m_lGebClassID = DEX_GetIdentFromClassName( (const char*)text );
	text.LoadString( IDS_DACH_CLASSNAME );
	m_lDTClassID = DEX_GetIdentFromClassName( (const char*)text );
	text.LoadString( IDS_HOF_CLASSNAME );
	m_lHofClassID = DEX_GetIdentFromClassName( (const char*)text );
}

BOOL CDatenListeDlg::IstClassMember( long onr, long classid )
{
	BOOL	result = FALSE;

	ASSERT( 0L != classid );
	ASSERT( 0L < onr );

	result = ( DEX_GetObjIdent( onr ) == classid );
	return result;
}

BOOL CDatenListeDlg::IstGrundstueck( long onr )
{
	InitClassIDs();
	return IstClassMember( onr, m_lGSClassID );
}

BOOL CDatenListeDlg::IstGebaeude( long onr )
{
	InitClassIDs();
	return IstClassMember( onr, m_lGebClassID );
}

BOOL CDatenListeDlg::IstDachteilflaeche( long onr )
{
	InitClassIDs();
	return IstClassMember( onr, m_lDTClassID );
}

BOOL CDatenListeDlg::IstHofflaeche( long onr )
{
	InitClassIDs();
	return IstClassMember( onr, m_lHofClassID );
}

CString CDatenListeDlg::GetIdentNummer( long onr )
{
	CString	result;
	TARGETMERKMAL	tm;
int	ot;

//	if ( DEX_GetObjectType( onr ) != OTFlaeche )
	if (( ot = DEX_GetObjectType( onr )) != OGFlaeche )
		return result;

	tm.dwSize  = sizeof( TARGETMERKMAL );
	tm.lTarget = onr;
	tm.lMCode  = DEX_GetMCodeFromFeatureName( "Identifikationsnummer" );
	tm.imaxLen = 1020;
	tm.pMText  = result.GetBuffer( 1024 );
	tm.iTTyp   = TT_Objekt;

	DEX_GetTextMerkmal( tm );
	result.ReleaseBuffer();

	return result;
}

CString CDatenListeDlg::GetObjektName( long onr )
{
	CString	result;
	TARGETMERKMAL	tm;

	tm.dwSize  = sizeof( TARGETMERKMAL );
	tm.lTarget = onr;
	tm.lMCode  = DEX_GetMCodeFromFeatureName( "Objektname" );
	tm.imaxLen = 1020;
	tm.pMText  = result.GetBuffer( 1024 );
	tm.iTTyp   = TT_Objekt;

	DEX_GetTextMerkmal( tm );
	result.ReleaseBuffer();

	return result;
}

CString CDatenListeDlg::GetUniqueIdent( long onr )
{
	CString	result;
	TARGETMERKMAL	tm;

	tm.dwSize  = sizeof( TARGETMERKMAL );
	tm.lTarget = onr;
	tm.lMCode  = DEX_GetUniqueIdentMCode();
	tm.imaxLen = 1020;
	tm.pMText  = result.GetBuffer( 1024 );
	tm.iTTyp   = TT_Objekt;

	DEX_GetTextMerkmal( tm );
	result.ReleaseBuffer();

	return result;
}

void CDatenListeDlg::SetIdentNummer( long onr, const char* id )
{
	CString	result;
	TARGETMERKMAL	tm;

	ASSERT( AfxIsValidString( id ));
	result = id;
	tm.dwSize  = sizeof( TARGETMERKMAL );
	tm.lTarget = onr;
	tm.lMCode  = DEX_GetMCodeFromFeatureName( "Identifikationsnummer" );
	tm.imaxLen = result.GetLength();
	tm.pMText  = result.GetBuffer( 1024 );
	tm.iTTyp   = TT_Objekt;

	DEX_ModTextMerkmal( tm );
	result.ReleaseBuffer();

	CxString	strONr;
	int			i;

	for ( i = 0; i < m_arrONr.GetSize(); i++ )
		if ( m_arrONr[i] == (void*)onr )
	{
		m_arrID[i] = id;
		break;
	}
	for ( i = 0; i < m_arrAlleONr.GetSize(); i++ )
		if ( m_arrAlleONr[i] == (void*)onr )
	{
		m_arrAlleID[i] = id;
		break;
	}

	strONr.Empty();
	strONr.AppendF( onr, -1 );
	m_mapAlleONr.SetAt( strONr, id );
	m_mapAlleID.SetAt( id, (void*)onr );

	SyncListen( FALSE );
}

void CDatenListeDlg::SetObjektName( long onr, const char* name )
{
	CString	result;
	TARGETMERKMAL	tm;

	ASSERT( AfxIsValidString( name ));
	result = name;
	tm.dwSize  = sizeof( TARGETMERKMAL );
	tm.lTarget = onr;
	tm.lMCode  = DEX_GetMCodeFromFeatureName( "Objektname" );
	tm.imaxLen = result.GetLength();
	tm.pMText  = result.GetBuffer( 1024 );
	tm.iTTyp   = TT_Objekt;

	DEX_ModTextMerkmal( tm );
	result.ReleaseBuffer();

	SetupTextObjekt( onr, name );
}

void CDatenListeDlg::OnSelchangeListe() 
{
	CString		id;
	long		onr;
	short		i, j;

	m_arrSelectedONr.RemoveAll();
	m_arrSelectedIDE.RemoveAll();
	for ( i = 0; i < m_lbListe.GetCount(); i++ )
	{
		if ( m_lbListe.GetSel( i ) > 0 )
		{
			m_lbListe.GetText( i, id );
			onr = 0L;
			if ( !id.IsEmpty())
			{
				for ( j = 0; j < m_arrID.GetSize(); j++ )
				{
					if ( id == m_arrID[j])
					{
						onr = (long)m_arrONr[j];
						break;
					}
				}
			}
			if ( onr > 0L )
			{
				m_arrSelectedONr.Add((void*)onr );
				m_arrSelectedIDE.Add( id );
			}
		}
	}

	m_strGSFlaeche.Empty();
	m_strBFlaeche.Empty();
	m_strBeitrag.Empty();
	UpdateData( FALSE );

//	SyncListen( TRUE );
	UpdateTriasSelection();
	ShowSingleData( m_arrSelectedONr.GetSize() == 1 );
}

extern BOOL PASCAL FAR RechIDProc( long ONr, BOOL iNotLast, void *pData );

void CDatenListeDlg::UpdateTriasSelection()
{
	if ( m_bBusy )	return;
	m_bBusy = TRUE;

	long			i, j;
	long			w[2048], h[256];
	long			len, onr, cnt;
	ENUMNOKEYLONG	enkl;
	ENUMLONGKEY		elk;
//	BOOL			bSelected;
	CxString		messagetext;
	CPtrArray		arrSelected;

	m_bSuspendSelObj = TRUE;

	BeginWaitCursor();
	h[0] = 2L;
	h[1] = 253L;
	enkl.eFcn = (ENUMNOKEYLONGPROC)RechIDProc;
	enkl.ePtr  = (void*)h;

	if ( g_iMessageStatus >= 2 )
	{
		messagetext = "Recherchieren der Grundstücke";
		DEX_SetMessageString((const char*)messagetext );
	}

	//	alle OR-Fenster beschaffen
	DEX_EnumORWindows( enkl );
	len = h[0] - 2;
	if ( len > 253L )	len = 253L;

	//	Für alle OR-Fenster
	j = 2;
	while ( j <= len+1 )
	{
		if ( g_iMessageStatus >= 2 )
		{
			messagetext = "Markieren der selektierten Grundstücke";
			DEX_SetMessageString((const char*)messagetext );
		}

		elk.eKey = h[j];
		elk.eFcn = (ENUMLONGKEYPROC)RechIDProc;
		elk.ePtr  = (void*)w;

		w[0] = 2L;
		w[1] = 2046L;

		DEX_EnumSelectedObjects( elk );

		cnt = w[0] - 2;
		if ( cnt > 2046L )	cnt = 2046L;

		for ( i = 2; i <= cnt + 1; i++ )
			arrSelected.Add((void*)w[i]);

		// Alle selektierten GS in OR-Fenster markieren
		for ( i = 0; i < m_arrSelectedONr.GetSize(); i++ )
		{
			onr = (long)m_arrSelectedONr[i];
			if ( !(ObjektSelected((HWND)h[j], onr ) & 1 ))	// Nur bislang nicht selektierte!
				if ( ObjektEnthalten((HWND)h[j], onr ))		// aber im OR-Fenster enthaltene GS
			{
//				DEXOR_ActivateObject((HWND)h[j], onr );
				DEXOR_SelectObject((HWND)h[j], onr );
			}
		}

		if ( g_iMessageStatus >= 2 )
		{
			messagetext = "Löschen der Markierung für alle nicht selektierten Grundstücke";
			DEX_SetMessageString((const char*)messagetext );
		}

		// Alle nicht selektierten GS, die im OR-Fenster evtl. noch
		// markiert sind, zurücksetzen
		for ( i = 0; i < arrSelected.GetSize(); i++ )
		{
			onr = (long)arrSelected[i];
			if ( !ObjektInArray( onr, m_arrSelectedONr ))		// Nur nicht selektierte GS
				DEXOR_UnselectObject((HWND)h[j], onr );
		}
		j++;
	}

	if ( g_iMessageStatus >= 2 )
	{
		messagetext = "Markieren des aktuell gewählten Grundstückes";
		DEX_SetMessageString((const char*)messagetext );
	}

	CString		name;
	j = m_lbListe.GetCaretIndex();		// welcher Satz ist markiert?
	if ( j != LB_ERR )
	{
		m_lbListe.GetText( j, name );
		onr = FindONr( name );
		if ( onr > 0 )
		{
			j = 2;
			while ( j <= len+1 )
			{
				if ((HWND)h[j] != m_hWndRemove )
					if ( ObjektEnthalten((HWND)h[j], onr ))
				{
					DEXOR_ActivateObject((HWND)h[j], onr );		// Nur Caret setzen!!
				}
				j++;
			}
		}
	}

	messagetext.LoadString( IDS_BEREIT );
	DEX_SetMessageString((const char*)messagetext );

	m_bBusy = FALSE;
	m_bSuspendSelObj = FALSE;
	EndWaitCursor();
}

void CDatenListeDlg::SelectObject( long lSelONr )
{
	if ( m_bSuspendSelObj )		return;

	if ( m_uiSelObjTimerID == 0 )
		m_uiSelObjTimerID = SetTimer( 2, 100, NULL );
}

void CDatenListeDlg::SelectObjectProc()
{
	if ( m_bBusy )	return;
	m_bBusy = TRUE;

	long			i, j, cnt;
	long			w[2048], h[256];
//	long			onr;
	long			len;
	ENUMNOKEYLONG	enkl;
	ENUMLONGKEY		elk;
//	BOOL			bSelected;
	CxString		ide, messagetext;

	BeginWaitCursor();
	h[0] = 2L;
	h[1] = 253L;
	enkl.eFcn = (ENUMNOKEYLONGPROC)RechIDProc;
	enkl.ePtr  = (void*)h;

	//	alle OR-Fenster beschaffen
	DEX_EnumORWindows( enkl );
	len = h[0] - 2;
	if ( len > 253L )	len = 253L;

	if ( g_iMessageStatus >= 1 )
	{
		messagetext = "Recherchieren der Grundstücke";
		DEX_SetMessageString((const char*)messagetext );
	}

	m_arrSelectedONr.RemoveAll();
	m_arrSelectedIDE.RemoveAll();

	for ( j = 2; j <= len+1; j++ )
	{
		elk.eKey = h[j];
		elk.eFcn = (ENUMLONGKEYPROC)RechIDProc;
		elk.ePtr  = (void*)w;

		w[0] = 2L;
		w[1] = 2046L;

		DEX_EnumSelectedObjects( elk );

		cnt = w[0] - 2;
		if ( cnt > 2046L )	cnt = 2046L;

		for ( i = 2; i <= cnt + 1; i++ )
		{
			ide = FindID( w[i]);
			if ( !ide.IsEmpty())
			{
				m_arrSelectedONr.Add((void*)w[i]);
				m_arrSelectedIDE.Add( ide );
			}
		}
	}

	// Für alle recherchierten GS
/*
	for ( i = 0; i < m_arrONr.GetSize(); i++ )
	{
		onr = (long)m_arrONr[i];
		bSelected = FALSE;
		// In allen OR-Fenster nachsehen
		for ( j = 2; j <= len+1; j++ )
			if ( ObjektSelected((HWND)h[j], onr ) & 1 )
				bSelected = TRUE;

		if ( bSelected )
		{
			m_arrSelectedONr.Add((void*)onr );
			m_arrSelectedIDE.Add( m_arrID[i]);
		}
	}
*/
	if ( g_iMessageStatus >= 1 )
	{
		messagetext = "Füllen der Datenliste";
		DEX_SetMessageString((const char*)messagetext );
	}

	FillListe();

	messagetext = "Bereit";
	DEX_SetMessageString((const char*)messagetext );

	m_bBusy = FALSE;
	EndWaitCursor();
}

void CDatenListeDlg::SyncListen( BOOL updateTRiAS )
{
	if ( m_bBusy )	return;
	m_bBusy = TRUE;

	// Der Timer dient nur dem Aufruf von SyncListen, wenn andere Mechanismen
	// nicht greifen. Speziell wenn GS zu vorhandenen OR-Fenstern hinzugefügt werden.
	// Wird SyncListen also zum Beispiel durch Erzeugung eines OR-Fensters ange-
	// stoßen, können wir den Timer getrost vergessen!
	if	( 0 != m_uiSyncTimerID )
	{
		KillTimer( m_uiSyncTimerID );
		m_uiSyncTimerID = 0;
	}

	CStringArray	arrTRiAS_Liste;
	CMapStringToPtr	mapTRiAS_Liste;
	CPtrArray		arrTRiAS_ONr;
	CPtrArray		arrTRiAS_Select;
	CPtrArray		arrUnSelect;
	CxString		name, messagetext;
	BOOL			found;
	long			lTRiAS_BLinkONr;
	void			*ptr;

	long			w[2048], h[256];
	long			len, cnt, onr;
	ENUMNOKEYLONG	enkl;
	ENUMLONGKEY		elk;
	short			i, j, res;

	m_lMultiONr1 = m_lMultiONr2 = m_lMultiONr3 = -1L;
	m_strMultiName.Empty();
	lTRiAS_BLinkONr = -1L;
	BeginWaitCursor();
	h[0] = 2L;
	h[1] = 253L;
	enkl.eFcn = (ENUMNOKEYLONGPROC)RechIDProc;
	enkl.ePtr  = (void*)h;

	//	alle OR-Fenster beschaffen
	DEX_EnumORWindows( enkl );

	//	Alle recherchierten Grundstücke in TRiAS beschaffen
	j = 2;
	len = h[0] - 2;
	if ( len > 253L )	len = 253L;

	if ( g_iMessageStatus >= 1 )
	{
		messagetext = "Recherchieren der Grundstücke";
		DEX_SetMessageString((const char*)messagetext );
	}

	while ( j <= len+1 )
	{
		if ( (HWND)h[j] != m_hWndRemove )
		{
			elk.eKey = h[j];
			elk.eFcn = (ENUMLONGKEYPROC)RechIDProc;
			elk.ePtr  = (void*)w;

			w[0] = 2L;
			w[1] = 2046L;

//			DEX_EnumSelectedObjects( elk );
			DEX_EnumAllORObjects( elk );

			cnt = w[0] - 2;
			if ( cnt > 2046L )	cnt = 2046L;

			for ( i = 2; i <= cnt + 1; i++ )
			{
				if ( g_iMessageStatus >= 3 )
				{
					messagetext = "Recherchieren der Grundstücke (";
					messagetext.AppendF( i, -1 );
					messagetext += "/";
					messagetext.AppendF( cnt, -1 );
					messagetext += ")";
					DEX_SetMessageString((const char*)messagetext );
				}

				// Zuerst sehen, ob es ein bereits registriertes GS ist
				name = FindID( w[i]);
				if ( !name.IsEmpty())
				{
					if ( !mapTRiAS_Liste.Lookup( name, ptr ))
					{
						mapTRiAS_Liste.SetAt( name, (void*)w[i]);
						arrTRiAS_ONr.Add( (void*)w[i]);
						arrTRiAS_Liste.Add( name );
						if ( res = ObjektSelected((HWND)h[j], w[i]))
							arrTRiAS_Select.Add( (void*)w[i]);
						if ( res > 1 )
							lTRiAS_BLinkONr = w[i];
					}
				}
				else
				{
					// Ist es überhaupt ein GS?
					if (( w[i] > 0L ) &&
						( DEX_GetObjectType( w[i]) == OGFlaeche ) &&
						( IstGrundstueck( w[i])))
					{
						// Neues GS!
						name = GetIdentNummer( w[i]);
						// Mit Identifikationsnummer?
						if ( !name.IsEmpty())
						{
							// Neues GS mit neuer IDE?
//							if ( !mapTRiAS_Liste.Lookup( name, ptr ))
							if ( !m_mapAlleID.Lookup( name, ptr ))
							{
								mapTRiAS_Liste.SetAt( name, (void*)w[i]);
								arrTRiAS_ONr.Add( (void*)w[i]);
								arrTRiAS_Liste.Add( name );
								if ( res = ObjektSelected((HWND)h[j], w[i]))
									arrTRiAS_Select.Add( (void*)w[i]);
								if ( res > 1 )
									lTRiAS_BLinkONr = w[i];

								CxString	strONr;

								strONr.Empty();
								strONr.AppendF( w[i], -1 );
								m_mapAlleONr.SetAt( strONr, name );
								m_mapAlleID.SetAt( name, (void*)w[i]);
								//m_mapAlleID.SetAt( name, (void*)w[i]);
								//m_arrAlleONr.SetAt();
							}
							else
							{
								if (( name == m_strMultiName ) && ( m_lMultiONr2 > 0L ))
								{
									if ( m_lMultiONr3 < 0 )		m_lMultiONr3 = w[i];
									else
									{
										m_lMultiONr2 = -1L;
										m_lMultiONr3 = -1L;
										m_strMultiName.Empty();
									}
								}
								if ( m_lMultiONr2 < 0 )
								{
									m_strMultiName = name;
									m_lMultiONr2 = w[i];
								}
							}
						}
					}
				}
			}
		}
		j++;
	}

	if ( g_iMessageStatus >= 2 )
	{
		messagetext = "Recherchieren der Grundstücke in der GBM-Datenbank";
		DEX_SetMessageString((const char*)messagetext );
	}

	//	eventuelle Differenzmenge zu den in der Liste enthaltenen bilden
	if ( updateTRiAS )
	{
		//	in der Liste nicht enthaltene GS aus TRiAS-OR-Fenstern entfernen
		for ( i = 0; i < arrTRiAS_ONr.GetSize(); i++ )
		{
			onr = (long)arrTRiAS_ONr[i];
			found = FALSE;
			for ( j = 0; j < m_arrONr.GetSize(); j++ )
			{
				if ( onr == (long)m_arrONr[j])
				{
					found = TRUE;
					break;
				}
			}
			if ( !found )	RemoveFromORWnd( onr, h );
		}

		//	in der Liste mehr enthaltene GS zu TRiAS-OR-Fenstern hinzufügen
		if (( h[0] < 3 ) && ( m_arrONr.GetSize() > 0 ))
		{
			CreateORWnd( &m_arrONr, "Grundstücke" );

			h[0] = 2L;
			h[1] = 253L;
			enkl.eFcn = (ENUMNOKEYLONGPROC)RechIDProc;
			enkl.ePtr  = (void*)h;

			//	alle OR-Fenster beschaffen
			DEX_EnumORWindows( enkl );
		}
		else
		{
			for ( i = 0; i < m_arrONr.GetSize(); i++ )
			{
				onr = (long)m_arrONr[i];
				found = FALSE;
				for ( j = 0; j < arrTRiAS_ONr.GetSize(); j++ )
				{
					if ( onr == (long)arrTRiAS_ONr[j])
					{
						found = TRUE;
						break;
					}
				}
				if ( !found )	AddToORWnd( onr, h );
			}
		}
	}
	else
	{
		m_arrID.RemoveAll();
		m_arrONr.RemoveAll();

		for ( i = 0; i < arrTRiAS_ONr.GetSize(); i++ )
		{
			// TRiAS-Liste einfach übernehmen
			onr = (long)arrTRiAS_ONr[i];
			name = arrTRiAS_Liste[i];
			AddToListe( onr, name );
		}
	}

	if ( g_iMessageStatus >= 2 )
	{
		messagetext = "Erstellen der Auswahllisten / Markieren der GS";
		DEX_SetMessageString((const char*)messagetext );
	}

	if ( updateTRiAS )
	{
		//	zunächst die nicht selektierten Objekte ermitteln
		for ( i = 0; i < arrTRiAS_ONr.GetSize(); i++ )
		{
			onr = (long)arrTRiAS_ONr[i];
			if ( !ObjektInArray( onr, m_arrSelectedONr ))
				arrUnSelect.Add((void*)onr );
		}
		//	die in der Liste selektierten GS in den OR-Fenstern selektieren
		j = 2;
		while ( j <= len+1 )
		{
			if ((HWND)h[j] != m_hWndRemove )
			{
				for ( i = 0; i < m_arrSelectedONr.GetSize(); i++ )
				{
					onr = (long)m_arrSelectedONr[i];
					if ( !ObjektInArray( onr, arrTRiAS_Select ))		// Nur bislang nicht selektierte!
						if ( ObjektEnthalten((HWND)h[j], onr ))
					{
//						DEXOR_ActivateObject((HWND)h[j], onr );
						DEXOR_SelectObject((HWND)h[j], onr );
					}
				}

				for ( i = 0; i < arrUnSelect.GetSize(); i++ )
				{
					onr = (long)arrUnSelect[i];
					if ( ObjektInArray( onr, arrTRiAS_Select ))		// Nur bislang selektierte!
						if ( ObjektEnthalten((HWND)h[j], onr ))
							DEXOR_UnselectObject((HWND)h[j], onr );
				}
			}
			j++;
		}

		j = m_lbListe.GetCaretIndex();		// welcher Satz ist markiert?
		if ( j != LB_ERR )
		{
			m_lbListe.GetText( j, name );
			onr = -1;
			for ( i = 0; i < m_arrID.GetSize(); i++ )
				if ( name == m_arrID[i])
			{
				onr = (long)m_arrONr[i];	// zugehörige Objektnummer
				break;
			}
			if ( onr > 0 )
			{
				j = 2;
				while ( j <= len+1 )
				{
					if ((HWND)h[j] != m_hWndRemove )
						if ( ObjektEnthalten((HWND)h[j], onr ))
					{
						DEXOR_ActivateObject((HWND)h[j], onr );		// Nur Caret setzen!!
					}
					j++;
				}
			}
		}
	}
	else
	{
		//	Selektionsliste von TRiAS übernehmen
		m_arrSelectedONr.RemoveAll();
		m_arrSelectedIDE.RemoveAll();

		for ( i = 0; i < arrTRiAS_Select.GetSize(); i++ )
		{
			onr = (long)arrTRiAS_Select[i];
			m_arrSelectedONr.Add((void*)onr );
			for ( j = 0; j < m_arrONr.GetSize(); j++ )
			{
				if ( onr == (long)m_arrONr[j])
				{
					m_arrSelectedIDE.Add( m_arrID[j]);
					break;
				}
			}
		}

		FillListe();
		// Hier ansetzen um lTRiAS_BlinkONr zu berücksichtigen
		// und SetCaretIndes auszuführen!
	}

	if ( !m_strMultiName.IsEmpty() && ( m_lMultiONr3 > 0L ))
	{
		for ( i = 0; i < m_arrONr.GetSize(); i++ )
		{
			if ( m_arrID[i] == m_strMultiName )
			{
				m_lMultiONr1 = (long)m_arrONr[i];
				AfxGetMainWnd() -> PostMessage( g_iGSTeilenMsg, (WPARAM)0, (LPARAM)0L );
				break;
			}
		}
	}

	messagetext.LoadString( IDS_BEREIT );
	DEX_SetMessageString((const char*)messagetext );

	m_hWndRemove = (HWND)NULL;
	m_bBusy = FALSE;
	EndWaitCursor();
}

BOOL CDatenListeDlg::RemoveFromORWnd( long onr, long* hwnd )
{
	BOOL	result = FALSE;
	short	j, len;

	if ( onr <= 0L )	return result;
	j = 2;
	len = hwnd[0] - 1;
	while ( j <= len + 1 )
		if ( DEXOR_RemoveFromListObject((HWND)hwnd[j++], onr ))
			result = TRUE;

	return result;
}

void CDatenListeDlg::AddToORWnd( long onr, long* hwnd )
{
	if ( onr <= 0L )	return;
	if ( hwnd[0] < 1 )		return;

	DEXOR_AddObjectToList((HWND)hwnd[2], onr );
}

BOOL CDatenListeDlg::RemoveFromListe( long onr )
{
	BOOL	result = FALSE;
	short	i;

	for ( i = 0; i < m_arrONr.GetSize(); i++ )
	{
		if ((long)m_arrONr[i] == onr )
		{
			result = TRUE;
			m_arrONr.RemoveAt( i );
			m_arrID.RemoveAt( i );
			break;
		}
	}
	return result;
}

short CDatenListeDlg::AddToListe( long onr, const char* name )
{
	short	i, result;
	BOOL	found = FALSE;

	ASSERT( onr > 0L );
	ASSERT( AfxIsValidString( name ));
	ASSERT( m_arrONr.GetSize() == m_arrID.GetSize());

	for ( i = 0; i < m_arrONr.GetSize(); i++ )
	{
		if ((long)m_arrONr[i] == onr )
		{
			found = TRUE;
			break;
		}
	}
	if ( !found )
	{
		m_arrONr.Add( (void*)onr );
		m_arrID.Add( name );
	}

	result = m_arrONr.GetSize();
	return result;
}

void CDatenListeDlg::FillListe()
{	RefreshListe();
}

short CDatenListeDlg::ObjektSelected( HWND hWnd, long onr )
{
	short			result = 0;
	RECHOBJECT		ro;

	ro.dwSize   = sizeof( RECHOBJECT );
	ro.lONr     = onr;		// ObjektNummer
	ro.lIdent   = 0L;		// Identifikator
	ro.lpText   = NULL;		// anzuzeigender Text
	ro.iTextLen = 0;		// Größe des TextBuffers
	ro.iOTyp    = 0;		// ObjektTyp
	ro.iFlags   = 0;		// anzuzeigende Informationen

	DEXOR_QueryRechercheStatus( hWnd, ro );
//	result = ( ro.iFlags & RSSelected );
	if ( ro.iFlags & RSSelected )	result += 1;
	if ( ro.iFlags & RSActivated )	result += 2;
	return result;
}

BOOL CDatenListeDlg::ObjektEnthalten( HWND hWnd, long onr )
{
	BOOL			result = FALSE;
	RECHOBJECT		ro;

	ro.dwSize   = sizeof( RECHOBJECT );
	ro.lONr     = onr;		// ObjektNummer
	ro.lIdent   = 0L;		// Identifikator
	ro.lpText   = NULL;		// anzuzeigender Text
	ro.iTextLen = 0;		// Größe des TextBuffers
	ro.iOTyp    = 0;		// ObjektTyp
	ro.iFlags   = 0;		// anzuzeigende Informationen

	DEXOR_QueryRechercheStatus( hWnd, ro );
	result = ( ro.iFlags & RSListed );
	return result;
}

void CDatenListeDlg::ShowSingleData( BOOL show )
{
	m_txtBText0.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtBText1.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtBText2.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtBText3.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtBText4.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtBText5.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtBText6.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtBText7.ShowWindow( show ? SW_SHOW : SW_HIDE );
//	m_frmBFrame0.ShowWindow( show ? SW_SHOW : SW_HIDE );
//	m_frmBFrame1.ShowWindow( show ? SW_SHOW : SW_HIDE );
//	m_frmBFrame2.ShowWindow( show ? SW_SHOW : SW_HIDE );
//	m_frmBFrame3.ShowWindow( show ? SW_SHOW : SW_HIDE );
//	m_frmBFrame4.ShowWindow( show ? SW_SHOW : SW_HIDE );
//	m_frmBFrame5.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtIDE.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtOrt.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtStr.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtFlur.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtFlurStk.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_txtEigent.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_btnGedr.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_btnGedr2.ShowWindow( show ? SW_SHOW : SW_HIDE );
	m_btnDetails.EnableWindow( show );

	if ( show && ( m_arrSelectedIDE.GetSize() == 1 ))
	{
		CBasisSatz		*pS = NULL;
		CString			ide, ort;
		CxString		text;

		ide = m_arrSelectedIDE[0];
		m_strIDE = ide;
		pS = g_pNF_PG1 -> FindIDE( ide );
		if ( pS != NULL )
		{
			ort = pS -> Ort();
			ort += "   ";
			ort += pS -> PLZ();
			m_strOrt = ort;
			m_strStr = pS -> Strasse();
			m_strFlur = pS -> Flur();
			m_strFlurstk = pS -> Flurstk();
			m_strEigent = pS -> Besitzer();

			text.Empty();
//			text.printf( "%.2f m²", pS -> GSFlaeche());
			text.printf( "%.2lf m²", pS -> GEF());
			text.FormatZahl( 2 );
			m_strGSFlaeche = text;

			text.Empty();
			text.printf( "%.2lf m²", pS -> BFlaeche());
			text.FormatZahl( 2 );
			m_strBFlaeche  = text;

			text.Empty();
			text.printf( "%.2lf DM", pS -> Beitrag());
			text.FormatZahl( 2 );
			m_strBeitrag   = text;

			m_bBBGedr = pS -> m_bBBGedr;
			m_bGBGedr = pS -> m_bGBGedr;
		}
		else
		{
			m_txtBText0.ShowWindow( SW_HIDE );
			m_txtBText1.ShowWindow( SW_HIDE );
			m_txtBText2.ShowWindow( SW_HIDE );
			m_txtBText3.ShowWindow( SW_HIDE );
			m_txtBText4.ShowWindow( SW_HIDE );
			m_txtBText5.ShowWindow( SW_HIDE );
			m_txtBText6.ShowWindow( SW_HIDE );
			m_txtBText7.ShowWindow( SW_HIDE );
			m_btnGedr.ShowWindow( SW_HIDE );
			m_btnGedr2.ShowWindow( SW_HIDE );
			m_txtIDE.ShowWindow( SW_HIDE );
			m_txtOrt.ShowWindow( SW_HIDE );
			m_txtStr.ShowWindow( SW_HIDE );
			m_txtFlur.ShowWindow( SW_HIDE );
			m_txtFlurStk.ShowWindow( SW_HIDE );
			m_txtEigent.ShowWindow( SW_HIDE );

			m_strOrt.Empty();
			m_strStr.Empty();
			m_strFlur.Empty();
			m_strFlurstk.Empty();
			m_strEigent.Empty();
			m_strGSFlaeche.Empty();
			m_strBFlaeche.Empty();
			m_strBeitrag.Empty();
		}
		UpdateData( FALSE );
	}
	else
		if ( m_arrSelectedIDE.GetSize() > 1 )
			OnButton1();
}

void CDatenListeDlg::OnDetails() 
{
	Bearbeiten( NULL );
}

void CDatenListeDlg::Bearbeiten( const char* pIDE )
{
	CBasisSatz			*pS = NULL;
	CDetailSatz			*pDS = NULL;
	CPG2DArray			arrPG2D, arrPG2H;
	CPG1GBArray			arrPG1GB;
	CEigentuemerArray	arrEigent;
	CString				ide, caption;
	CxString			text;

	UpdateData( TRUE );
	m_bDetailsDummy = FALSE;	// immer auf FALSE halten
	m_bSuchenDummy = FALSE;		// für Buttondarstellung
	UpdateData( FALSE );

	if ( pIDE == NULL )
	{
		ASSERT( m_arrSelectedIDE.GetSize() == 1 );
		if ( m_arrSelectedIDE.GetSize() != 1 )	return;
		ide = m_arrSelectedIDE[0];
	}
	else
	{
		ASSERT( AfxIsValidString( pIDE ));
		if ( !AfxIsValidString( pIDE ))		return;
		ide = pIDE;

		CVerzSet	*pVerzSet = new CVerzSet( g_pDatabase );
		CString		name;
		int			verz;

		GetActiveProject( name );
		verz = pVerzSet -> IstProjektIntegriert( name );
		if ( NULL == g_pSetTriDB )
		{
			if ( NULL == g_pDatabase )
			{
				g_pSetTriDB = new CTriDBSet;
				g_pDatabase = g_pSetTriDB -> m_pDatabase;
			}
			else
				g_pSetTriDB = new CTriDBSet( g_pDatabase );

			g_pSetTriDB -> Open();
		}
		if ( verz > -1 )	g_pSetTriDB -> AddIDE( ide, verz );
	}

	caption = "Grundstück ";
	caption += ide;
	caption += " bearbeiten";

	CErfassPrivDlg	sheet( caption, AfxGetMainWnd());
	CEditPage1		page1;
	CEditPage2		page2;
	CEditPage3		page3;
	CEditPage4		page4;
	CEditPage5		page5;
//	CEditPage6		page6;
	CEditPage7		page7;


	sheet.m_strNFP1_IDE   = ide;
	sheet.m_strNFP1_ORT   = OrtFromIDE( ide );
	text.Empty();	text.AppendFormated( TB( ide ), -1, 2, 2 );
	page1.m_strTB         = text;

	pS = g_pNF_PG1 -> FindIDE( ide );
	if ( pS != NULL )
	{
		// Seite 1
		sheet.m_strNFP1_ENA   = pS -> Besitzer();
		sheet.m_strNFP1_EAN   = pS -> Strasse();
		sheet.m_strNFP1_EPL   = pS -> PLZ();
		sheet.m_strNFP1_EOR   = pS -> Ort();
		sheet.m_strNFP1_FLU   = pS -> Flur();
		sheet.m_strNFP1_FST   = pS -> Flurstk();
		sheet.m_rNFP1_BAR     = pS -> BAR();
		sheet.m_rNFP1_GFZ     = pS -> GFZ();
		sheet.m_rNFP1_BMZ     = pS -> BMZ();
		sheet.m_rNFP1_VGZ     = pS -> VGZ();
		sheet.m_rNFP1_GUZ     = pS -> GUZ();
		sheet.m_rNFP1_KAT     = pS -> KAT();
		sheet.m_tNFP1_ANDAT   = pS -> ANDAT();
		sheet.m_bMiteigent    = ( pS -> NEIG() == "M" );

		page1.m_bNFP1_TIEF    = pS -> TIEF();
		page1.m_strNA_B_PLAN  = pS -> NA_B_PLAN();
		text.Empty();	text.AppendFormated( pS -> GEFS(), -1, 2, 2 );
		page1.m_strNFP1_GEFS  = text;
		text.Empty();	text.AppendFormated( pS -> AGGS(), -1, 2, 2 );
		page1.m_strNFP1_AGGS  = text;
		text.Empty();	text.AppendFormated( pS -> AGG(), -1, 2, 2 );
		page1.m_strNFP1_AGG   = text;
		text.Empty();	text.AppendF( pS -> TIEB(), -1, 2 );
		page1.m_strNFP1_TIEB  = text;
		page1.m_rNFP1_VOLU    = pS -> VOLU();
		page1.m_strNFP1_NEIG  = pS -> NEIG();

		sheet.m_strANNWL = pS -> AnNWL();
		sheet.m_bEditIDE      = FALSE;
	}
	else
		sheet.m_bEditIDE      = TRUE;

	// Seite 2
	g_pNF_PG2D -> InitArray( ide, &arrPG2D );
	sheet.m_arrPG2D = arrPG2D;

	// Seite 3
	g_pNF_PG2H -> InitArray( ide, &arrPG2H );
	sheet.m_arrPG2H = arrPG2H;

	pDS = m_pNF_PG3 -> FindIDE( ide );
	if ( !pDS -> IDE().IsEmpty())
	{
		// Seite 4
		sheet.m_rAWE     = pDS -> AWE();
		sheet.m_rAEW     = pDS -> AEW();
		sheet.m_rEGW     = pDS -> GW();
		sheet.m_bZE      = pDS -> MOB();
		sheet.m_bSGR     = pDS -> SAM();
		sheet.m_rFS      = pDS -> SAG();
		sheet.m_bSGT     = pDS -> SAT();
		sheet.m_bKK      = pDS -> KK();
		sheet.m_rFKK     = pDS -> KKG();
		sheet.m_bKKT     = pDS -> KKT();
		sheet.m_bVF      = pDS -> KKV();
		sheet.m_bK       = pDS -> KKK();
		sheet.m_bFZ      = pDS -> FZ();
		sheet.m_bFE      = pDS -> FE();
		sheet.m_bFZE     = pDS -> FZE();
		sheet.m_strBem   = pDS -> Bem();

		// Seite 6

		delete pDS;
		pDS = NULL;
	}
	else
	{
		delete pDS;
		pDS = NULL;
	}

	// Seite 5
	g_pNF_PG1GB -> InitArray( ide, &arrPG1GB );
	sheet.m_arrPG1GB = arrPG1GB;

	// Seite 7
	g_pNF_PG4 -> InitArray( ide, &arrEigent );
	sheet.m_arrEigent = arrEigent;

	sheet.m_strCaption = "  ";
	sheet.m_strCaption += ide;

	sheet.AddPage( &page1 );
	sheet.AddPage( &page2 );
	sheet.AddPage( &page3 );
	sheet.AddPage( &page4 );
	sheet.AddPage( &page5 );
//	sheet.AddPage( &page6 );
	sheet.AddPage( &page7 );

	sheet.page1 = &page1;
	sheet.page2 = &page2;
	sheet.page3 = &page3;
	sheet.page4 = &page4;
	sheet.page5 = &page5;
//	sheet.page6 = &page6;
	sheet.page7 = &page7;

	sheet.InitPages();

	BOOL	bPromptDlg = TRUE;
//	DEX_BeginModalDialog();
	while ( bPromptDlg )
	{
		if ( sheet.DoModal() == IDOK )
		{
			if ( page7.m_bDivError )
			{
				MessageBox( "Fehlerhafte Anteilsverhältnisse: Division durch 0!",
					"Daten nicht gespeichert" );
			}
			else if ( page7.m_bSummError )
			{
				MessageBox( "Fehlerhafte Anteilsverhältnisse: Summe der Anteil ist ungleich 1!",
					"Daten nicht gespeichert" );
			}
			else
			{
				bPromptDlg = FALSE;
				if ( pS == NULL )				// wenn neu angelegt, nicht freigeben!!
					pS = new CBasisSatz( ide );	// wird in CSetNF_PG1 aufgehoben!!

				// Seite 1
				pS -> Besitzer() = sheet.m_strNFP1_ENA;
				pS -> Strasse()  = sheet.m_strNFP1_EAN;
				pS -> PLZ()      = sheet.m_strNFP1_EPL;
				pS -> Ort()      = sheet.m_strNFP1_EOR;
				pS -> Flur()     = sheet.m_strNFP1_FLU;
				pS -> Flurstk()  = sheet.m_strNFP1_FST;
				pS -> BAR()      = sheet.m_rNFP1_BAR;
				pS -> GFZ()      = sheet.m_rNFP1_GFZ;
				pS -> BMZ()      = sheet.m_rNFP1_BMZ;
				pS -> VGZ()      = sheet.m_rNFP1_VGZ;
				pS -> GUZ()      = sheet.m_rNFP1_GUZ;
				pS -> KAT()      = sheet.m_rNFP1_KAT;
				pS -> ANDAT()    = sheet.m_tNFP1_ANDAT;

				pS -> TIEF()      = page1.m_bNFP1_TIEF;
				pS -> NA_B_PLAN() = page1.m_strNA_B_PLAN;
				pS -> VOLU()      = page1.m_rNFP1_VOLU;

				pS -> AnNWL() = sheet.m_strANNWL;

				arrEigent = sheet.m_arrEigent;
				if ( arrEigent.GetSize() == 1 )		pS -> NEIG() = "E";
				else if ( sheet.m_bMiteigent )		pS -> NEIG() = "M";
				else								pS -> NEIG() = "W";

				g_pNF_PG1 -> RewriteIDE( pS );

				// Seite 2
				arrPG2D = sheet.m_arrPG2D;
				g_pNF_PG2D -> RewriteArray( &arrPG2D );

				// Seite 3
				arrPG2H = sheet.m_arrPG2H;
				g_pNF_PG2H -> RewriteArray( &arrPG2H );

				pDS = new CDetailSatz;
				pDS -> IDE() = ide;

				// Seite 4
				pDS -> AWE()   = sheet.m_rAWE;
				pDS -> AEW()   = sheet.m_rAEW;
				pDS -> GW()    = sheet.m_rEGW;
				pDS -> MOB()   = sheet.m_bZE;
				pDS -> SAM()   = sheet.m_bSGR;
				pDS -> SAG()   = sheet.m_rFS;
				pDS -> SAT()   = sheet.m_bSGT;
				pDS -> KK()    = sheet.m_bKK;
				pDS -> KKG()   = sheet.m_rFKK;
				pDS -> KKT()   = sheet.m_bKKT;
				pDS -> KKV()   = sheet.m_bVF;
				pDS -> KKK()   = sheet.m_bK;
				pDS -> FZ()    = sheet.m_bFZ;
				pDS -> FE()    = sheet.m_bFE;
				pDS -> FZE()   = sheet.m_bFZE;
				pDS -> Bem()   = sheet.m_strBem;

				m_pNF_PG3 -> RewriteIDE( ide, pDS );
				long	onr = FindONr( ide );
				g_pOPAngeschlGS -> SetONr( onr, pDS -> MOB());
				g_pOPBeitragsartGS -> SetONr( onr, (WORD)int( pS -> BAR()));
				g_pOPEigentumGS -> SetONr( onr, 1 );
				g_pOPGedrucktGS -> SetONr( onr, pS -> m_bBBGedr );
				g_pOPGedruck2GS -> SetONr( onr, pS -> m_bGBGedr );

				delete pDS;
				pDS = NULL;

				// Seite 5
				arrPG1GB = sheet.m_arrPG1GB;
				g_pNF_PG1GB -> RewriteArray( ide, &arrPG1GB );

				// Seite 7
//				arrEigent = sheet.m_arrEigent;	// schon oben!!
//				g_pNF_PG4 -> RewriteArray( ide, &arrEigent );
				// RewriteEig in Sheet macht schon alles!
			}
		}
		else
			bPromptDlg = FALSE;
	}
//	DEX_EndModalDialog();
}

//	Summen bilden
void CDatenListeDlg::OnButton1() 
{
	short		i;
	CString		ide;
	double		flaeche1, flaeche2, beitrag;
	CxString	text;
	CBasisSatz	*pS;

	flaeche1 = flaeche2 = beitrag = 0;
	for ( i = 0; i < m_arrSelectedIDE.GetSize(); i++ )
	{
		ide = m_arrSelectedIDE[i];
		pS = g_pNF_PG1 -> FindIDE( ide );
		if ( pS != NULL )
		{
//			flaeche1 += pS -> GSFlaeche();
			flaeche1 += pS -> GEF();
			flaeche2 += pS -> BFlaeche();
			beitrag  += pS -> Beitrag();
		}
	}

	text.Empty();
	text.printf( "%.2lf m²", flaeche1 );
	text.FormatZahl( 2 );
	m_strGSFlaeche = text;

	text.Empty();
	text.printf( "%.2lf m²", flaeche2 );
	text.FormatZahl( 2 );
	m_strBFlaeche  = text;

	text.Empty();
	text.printf( "%.2lf DM", beitrag );
	text.FormatZahl( 2 );
	m_strBeitrag   = text;

	UpdateData( FALSE );
}

void CDatenListeDlg::OnSuchen() 
{
	CMySuchSheet	sheet( "Grundstücke suchen", AfxGetMainWnd());
	CSuchPage0		page0;
	CSuchPage1		page1;
	CSuchPage2		page2;
	CSuchPage3		page3;
	CSuchPage4		page4;
	CString			ide, ide1;

	UpdateData( TRUE );
	m_bDetailsDummy = FALSE;	// immer auf FALSE halten
	m_bSuchenDummy = FALSE;		// für Buttondarstellung
	UpdateData( FALSE );

	sheet.AddPage( &page0 );
	sheet.AddPage( &page1 );
	sheet.AddPage( &page2 );
	sheet.AddPage( &page3 );
	sheet.AddPage( &page4 );
	sheet.SetWizardMode();

	page1.m_strIdent = m_strMinIDE;

	page2.m_iOISY = m_iOISY;
	if ( m_strMinIDE.GetLength() >= 2 )
	{
		page2.m_strIdent = m_strMinIDE.Left( 2 );
		page2.m_strIDE = m_strMinIDE.Left( 2 );
	}
	page2.m_pSetStrasse = m_pSetStrasse;

	if ( sheet.DoModal() == ID_WIZFINISH )
	{
		switch ( sheet.m_iNextPage )
		{
		case 1:
			ide = page1.m_strIdent;
			if ( ide.GetLength() <= 4 )
			{
				MessageBox( "Identifikator zu kurz für effektive Suche!\n(Es sind zu viele Treffer zu erwarten!)",
							"Fehler in Suchkriterium" );
				return;
			}
			break;
		case 3:
			ide = page3.m_strFlur;
			ide1 = page3.m_strFlurStck;
			if (( ide.GetLength() <= 0 ) && ( ide1.GetLength() <= 1 ))
			{
				MessageBox( "Flur/Flurstücksbezeichnung zu kurz für effektive Suche!\n(Es sind zu viele Treffer zu erwarten!)",
							"Fehler in Suchkriterium" );
				return;
			}
			break;
		case 4:
			ide = page4.m_strName;
			if ( ide.GetLength() <= 1 )
			{
				MessageBox( "Name zu kurz für effektive Suche!\n(Es sind zu viele Treffer zu erwarten!)",
							"Fehler in Suchkriterium" );
				return;
			}
			break;
		}
		m_lbListe.ShowWindow( SW_HIDE );
		switch ( sheet.m_iNextPage )
		{
		case 1:
			ide = page1.m_strIdent;
			if ( ide.GetLength() > 4 )
				AddGS( ide );
			break;
		case 2:
			ide = page2.m_strIdent;
			AddGS( ide );
			break;
		case 3:
			ide = page3.m_strFlur;
			ide1 = page3.m_strFlurStck;
			if (( ide.GetLength() > 0 ) || ( ide1.GetLength() > 1 ))
				AddFlurGS( ide, ide1 );
			break;
		case 4:
			ide = page4.m_strName;
			if ( ide.GetLength() > 1 )
				AddEignerGS( ide );
			break;
		}
		m_lbListe.ShowWindow( SW_SHOW );
	}
}

void CDatenListeDlg::AddGS( const char* ide1, const char* ide2 )
{
	CString			strID;
	CxString		text;
	CStringArray	arrID;
	CPtrArray		arrONr;
	long			onr;
	int				i, n;

	ASSERT( g_pNF_PG1 );
	ASSERT( AfxIsValidString( ide1 ));

	strID = ide1;
	if ( strID.GetLength() > 2 )
		strID = strID.Left( 2 );

	BeginWaitCursor();
	g_pNF_PG1 -> InitListen( strID );

//	ResetListe();

	n = 0;
	strID = ide1;
	if ( strID.GetLength() > 4 )
	{
		g_pNF_PG1 -> Add2Array( strID, &arrID );
		if ( ide2 != NULL )
		{
			strID = ide2;
			if ( strID.GetLength() > 4 )
				g_pNF_PG1 -> Add2Array( strID, &arrID );
		}
		for ( i = 0; i < arrID.GetSize(); i++ )
		{
			onr = FindONr( arrID[i]);
			if ( onr > 0L )
				arrONr.Add((void*)onr );
			else
				n++;
		}

		EndWaitCursor();
		if (( n > 0 ) || ( arrID.GetSize() == 0 ))
		{
			CSuchResDlg	dlg( AfxGetMainWnd());

			dlg.m_iGesamt = arrID.GetSize();
			dlg.m_iFehl   = n;
			if ( dlg.DoModal() == IDOK )
				if ( n < arrID.GetSize())
					CreateORWnd( &arrONr, "Gefundene Grundstücke" );
			return;
		}

		if ( n < arrID.GetSize())
			CreateORWnd( &arrONr, "Gefundene Grundstücke" );

//		FillListe();
	}
	else
		EndWaitCursor();

}	// AddGS

void CDatenListeDlg::AddEignerGS( const char* name )
{
	CxString		text;
	CStringArray	arrID;
	CPtrArray		arrONr;
	long			onr;
	int				i, n;

	ASSERT( g_pNF_PG1 );
	ASSERT( AfxIsValidString( name ));

	BeginWaitCursor();
	n = 0;
	g_pNF_PG1 -> Add2ArrayByEigner( name, &arrID );
	for ( i = 0; i < arrID.GetSize(); i++ )
	{
		onr = FindONr( arrID[i]);
		if ( onr > 0L )
			arrONr.Add((void*)onr );
		else
			n++;
	}

	EndWaitCursor();
	if (( n > 0 ) || ( arrID.GetSize() == 0 ))
	{
		CSuchResDlg	dlg( AfxGetMainWnd());

		dlg.m_iGesamt = arrID.GetSize();
		dlg.m_iFehl   = n;
		if ( dlg.DoModal() == IDOK )
		{
			text = "Eigentümer: '";
			text += name;
			text += "'";
			if ( n < arrID.GetSize())
				CreateORWnd( &arrONr, text );
		}
		return;
	}

	text = "Eigentümer: '";
	text += name;
	text += "'";
	if ( n < arrID.GetSize())
		CreateORWnd( &arrONr, text );

}	// AddEignerGS

void CDatenListeDlg::AddFlurGS( const char* flur, const char* stck )
{
	CxString		text;
	CStringArray	arrID;
	CPtrArray		arrONr;
	long			onr;
	int				i, n;

	ASSERT( g_pNF_PG1 );
	ASSERT( AfxIsValidString( flur ));
	ASSERT( AfxIsValidString( stck ));

	BeginWaitCursor();
	n = 0;
	g_pNF_PG1 -> Add2ArrayByFlur( flur, stck, &arrID );
	for ( i = 0; i < arrID.GetSize(); i++ )
	{
		onr = FindONr( arrID[i]);
		if ( onr > 0L )
			arrONr.Add((void*)onr );
		else
			n++;
	}

	EndWaitCursor();
	if (( n > 0 ) || ( arrID.GetSize() == 0 ))
	{
		CSuchResDlg	dlg( AfxGetMainWnd());

		dlg.m_iGesamt = arrID.GetSize();
		dlg.m_iFehl   = n;
		if ( dlg.DoModal() == IDOK )
		{
			text = "Grundstücke in Flur '";
			text += flur;
			text += " / ";
			text += stck;
			text += "'";
			if ( n < arrID.GetSize())		CreateORWnd( &arrONr, text );
		}
		return;
	}

	text = "Grundstücke in Flur '";
	text += flur;
	text += " / ";
	text += stck;
	text += "'";
	if ( n < arrID.GetSize())		CreateORWnd( &arrONr, text );
}

void CDatenListeDlg::RegisterProjekt()
{
	CString			text, name;
	ENUMLONGKEY		elk;
	CBasisSatz		*pS;
//	CDetailSatz		*pD;
	long			*w;
	long			key;
	int				i, cnt;

	m_arrAlleONr.RemoveAll();
	m_arrSonstONr.RemoveAll();
	m_arrAlleID.RemoveAll();
	m_mapAlleONr.RemoveAll();
	m_mapAlleID.RemoveAll();
	ResetListe();

	text.LoadString( IDS_GS_CLASSNAME );
	key = DEX_GetIdentFromClassName( (const char*)text );
	if ( key != 0L )
	{
		w = new long[2048];
		ASSERT( w );
		if ( w == NULL )	return;

		elk.eKey = key;
		elk.eFcn = (ENUMLONGKEYPROC)RechIDProc;
		elk.ePtr  = (void*)w;

		w[0] = 2L;
		w[1] = 2046L;

		DEX_EnumIdentObjects( elk );
//		DEX_EnumIdentObjectsEx( elk );

		cnt = w[0] - 2;
		if ( cnt > 2046L )
		{
			delete [] w;

			w = new long[cnt + 4];
			ASSERT( w );
			if ( w == NULL )	return;

			elk.ePtr  = (void*)w;
			w[0] = 2L;
			w[1] = cnt+2;

			DEX_EnumIdentObjects( elk );
		}

		CxString	strONr;
		for ( i = 2; i <= cnt + 1; i++ )
		{
			name = GetIdentNummer( w[i]);
			if ( !name.IsEmpty())
			{
				m_arrAlleONr.Add((void*)w[i]);
				m_arrAlleID.Add( name );
				strONr.Empty();
				strONr.AppendF( w[i], -1 );
				m_mapAlleONr.SetAt( strONr, name );
				m_mapAlleID.SetAt( name, (void*)w[i]);
			}
			else
//				if ( DEX_GetObjectType( w[i]) == OTFlaeche )
				if ( DEX_GetObjectType( w[i]) == OGFlaeche )
					m_arrSonstONr.Add((void*)w[i]);
		}

		delete [] w;
	}

	m_strMinIDE.Empty();
	if ( m_arrAlleID.GetSize() > 1 )
	{
		m_strMinIDE = m_arrAlleID[0];
		cnt = m_strMinIDE.GetLength();
		for ( i = 1; i < m_arrAlleID.GetSize(); i++ )
		{
			name = m_arrAlleID[i];

			if ( g_iMessageStatus >= 2 )
			{
				text = "Initialisiere Grundstück: ";
				text += name;
				if ( g_iMessageStatus >= 3 )
					text += "  >";
				DEX_SetMessageString((const char*)text );
			}

			pS = g_pNF_PG1 -> FindIDE( name );
			if ( g_iMessageStatus >= 3 )
			{
				text += ">";
				DEX_SetMessageString((const char*)text );
			}

//			pD = m_pNF_PG3 -> FindIDE( name );
//			if ( pD != NULL )
//				if ( pD -> MOB())

			if ( m_pNF_PG3 -> IstMOB( name ))
					g_pOPAngeschlGS -> AddONr((long)m_arrAlleONr[i]);

			if ( g_iMessageStatus >= 3 )
			{
				text += ">";
				DEX_SetMessageString((const char*)text );
			}

			if ( pS != NULL )
				g_pOPBeitragsartGS -> SetONr((long)m_arrAlleONr[i], (WORD)int( pS -> BAR()));

			if ( g_iMessageStatus >= 3 )
			{
				text += ">";
				DEX_SetMessageString((const char*)text );
			}

			g_pOPEigentumGS -> SetONr((long)m_arrAlleONr[i], 1 );

			if ( g_iMessageStatus >= 3 )
			{
				text += ">";
				DEX_SetMessageString((const char*)text );
			}

			if ( pS != NULL )
			{
				g_pOPGedrucktGS -> SetONr((long)m_arrAlleONr[i], pS -> m_bBBGedr );
				g_pOPGedruck2GS -> SetONr((long)m_arrAlleONr[i], pS -> m_bGBGedr );
			}

			if ( g_iMessageStatus >= 3 )
			{
				text += ">";
				DEX_SetMessageString((const char*)text );
			}

			if ( name.GetLength() > cnt )
				name = name.Left( cnt );
			if ( !(name == m_strMinIDE ))
			{
				if ( name.GetLength() < cnt )
				{
					cnt = name.GetLength();
					m_strMinIDE = m_strMinIDE.Left( cnt );
				}
				while (( cnt > 2 ) && !( name == m_strMinIDE ))
				{
					cnt--;
					name = name.Left( cnt );
					m_strMinIDE = m_strMinIDE.Left( cnt );
				}
			}

			if ( g_iMessageStatus >= 3 )
			{
				text += ">";
				DEX_SetMessageString((const char*)text );
			}
		}
	}
}

long CDatenListeDlg::FindONr( const char* id )
{
	CString	ident;
	long	result = 0L;

	ASSERT( AfxIsValidString( id ));
	void	*ptr = NULL;
	if ( m_mapAlleID.Lookup( id, ptr ))
		result = (long)ptr;

	return result;
}	// FindONr

void CDatenListeDlg::CreateORWnd( CPtrArray* arr, const char* text )
{
	CREATEOBJEKTINFO	coi;
	CString				caption;
	POINT				pt;
	long				*onr;
	short				i;

	if ( arr -> GetSize() < 1 )	return;

	ASSERT( AfxIsValidString( text ));

	caption = text;
	onr = new long[arr -> GetSize()];
	ASSERT( onr );
	if ( onr == NULL )	return;

	for ( i = 0; i < arr -> GetSize(); i++ )
		onr[i] = (long)( arr -> GetAt( i ));

	pt.x = 0L;
	pt.y = 0L;

	coi.dwSize = sizeof( CREATEOBJEKTINFO );
	coi.lpCaption = caption.GetBuffer( 0 );	// FensterCaption
	coi.plObjs    = onr;					// ObjektNummern, die angezeigt werden sollen
	coi.iNumObjs  = arr -> GetSize();		// Anzahl der ObjektNummern
	coi.cMColor   = RGB( 255, 0, 0 );		// Markierungsfarbe
	coi.pntPos    = pt;						// AnfangsPosition im Hauptfenster

	DEX_CreateObjektInfo( coi );

	delete [] onr;
}	// CreateORWnd

void CDatenListeDlg::OnTimer(UINT nIDEvent) 
{
	if (( 1 == nIDEvent ) && ( 0 != m_uiSyncTimerID ))
	{
		if ( m_lAddedObjsSinceSync == m_lAddedObjsSinceTimer )
		{
			SyncListen( FALSE );
			KillTimer( m_uiSyncTimerID );
			m_uiSyncTimerID = 0;
			m_lAddedObjsSinceSync = m_lAddedObjsSinceTimer = 0L;
		}
		else
			m_lAddedObjsSinceTimer = m_lAddedObjsSinceSync;

		return;
	}

	if (( 2 == nIDEvent ) && ( 0 != m_uiSelObjTimerID ))
	{
		SelectObjectProc();
		KillTimer( m_uiSelObjTimerID );
		m_uiSelObjTimerID = 0;

		return;
	}

	SECDialogBar::OnTimer(nIDEvent);
}

void CDatenListeDlg::AddGS( long onr )
{
	if ( m_bBusy )	return;
	m_bBusy = TRUE;

	CString		name;

	ASSERT( onr > 0L );

	name = FindID( onr );
	if ( !name.IsEmpty())
	{
		m_arrID.Add( name );
		m_arrONr.Add((void*)onr );

//		FillListe();
		if ( m_uiSyncTimerID == 0 )
			m_uiSyncTimerID = SetTimer( 1, 500, NULL );

		m_lAddedObjsSinceSync++;
	}
	m_hWndRemove = (HWND)NULL;
	m_bBusy = FALSE;
}	// AddGS

CString CDatenListeDlg::FindID( long onr )
{
	CString		result;
	CxString	strONr;

	ASSERT( onr > 0L );
	strONr.AppendF( onr, -1 );
	m_mapAlleONr.Lookup( strONr, result );

	return result;
}	// FindID

void CDatenListeDlg::HandleGSTeilen()
{
	if ( m_bGSTeilenAtWork )	return;
	m_bGSTeilenAtWork = TRUE;

	CGSTeilenDlg	dlg( AfxGetMainWnd());
	CString			id2, id3, bez1, bez2, bez3;
	CxString		nr;
	short			i, n;
	long			onr;

	bez1 = GetUniqueIdent( m_lMultiONr1 );
	bez2 = GetUniqueIdent( m_lMultiONr2 );
	bez3 = GetUniqueIdent( m_lMultiONr3 );
	if ( bez2.GetLength() < bez1.GetLength())
	{
		onr = m_lMultiONr1;
		m_lMultiONr1 = m_lMultiONr2;
		m_lMultiONr2 = onr;
	}
	if ( bez3.GetLength() < bez1.GetLength())
	{
		onr = m_lMultiONr1;
		m_lMultiONr1 = m_lMultiONr3;
		m_lMultiONr3 = onr;
	}

	id2 = m_strMultiName;
	id3 = m_strMultiName;
	i = 5;
	n = id2.GetLength();
	while (( id2.GetAt( i ) != '0' ) && ( i < 8 ))	i++;
	if ( i < n )
	{
		id2 = m_strMultiName.Left( i );
		id2 += m_strMultiName.Right( n - i - 1 );
		id3 = id2;
		id2 += "a";
		id3 += "b";
	}
	bez1 = GetObjektName( m_lMultiONr1 );
	bez2 = bez1;
	bez3 = bez2;
	bez2 += "A";
	bez3 += "B";

	dlg.m_strBez1 = bez1;
	dlg.m_strBez2 = bez2;
	dlg.m_strBez3 = bez3;
	dlg.m_strIdent1 = m_strMultiName;
	dlg.m_strIdent2 = id2;
	dlg.m_strIdent3 = id3;
	nr.Empty();
	nr.AppendF( m_lMultiONr1, -1 );
	dlg.m_strONr1 = nr;
	nr.Empty();
	nr.AppendF( m_lMultiONr2, -1 );
	dlg.m_strONr2 = nr;
	nr.Empty();
	nr.AppendF( m_lMultiONr3, -1 );
	dlg.m_strONr3 = nr;

	CxString	strONr;
	if ( dlg.DoModal() == IDOK )
	{
		id2 = dlg.m_strIdent2;
		id3 = dlg.m_strIdent3;
		bez2 = dlg.m_strBez2;
		bez3 = dlg.m_strBez3;
		if ( id2.GetLength() == n )
		{
			SetIdentNummer( m_lMultiONr2, id2 );
			g_pNF_PG1 -> CopyGS( m_strMultiName, id2 );
			m_arrAlleONr.Add( (void*)m_lMultiONr2 );
			m_arrAlleID.Add( id2 );
			strONr.Empty();
			strONr.AppendF( m_lMultiONr2, -1 );
			m_mapAlleONr.SetAt( strONr, id2 );
			m_mapAlleID.SetAt( id2, (void*)m_lMultiONr2 );
		}
		if ( id3.GetLength() == n )
		{
			SetIdentNummer( m_lMultiONr3, id3 );
			g_pNF_PG1 -> CopyGS( m_strMultiName, id3 );
			m_arrAlleONr.Add( (void*)m_lMultiONr3 );
			m_arrAlleID.Add( id3 );
			strONr.Empty();
			strONr.AppendF( m_lMultiONr3, -1 );
			m_mapAlleONr.SetAt( strONr, id3 );
			m_mapAlleID.SetAt( id3, (void*)m_lMultiONr3 );
		}
		if ( bez2.GetLength())
			SetObjektName( m_lMultiONr2, bez2 );
		if ( bez3.GetLength())
			SetObjektName( m_lMultiONr3, bez3 );

		DEX_RebuildSight();
		DEX_RePaintWait();
		SyncListen( FALSE );
	}
	m_bGSTeilenAtWork = FALSE;
}

void CDatenListeDlg::SetupTextObjekt( long onrF, const char* text )
{
	ASSERT( AfxIsValidString( text ));

	long	onrT = TriasFindBObject( onrF );
	CString	textID;
	double	dHoch, dRechts;
	double	*hoch, *rechts;
	double	dHMin, dHMax, dRMin, dRMax;
	short	i;

	textID.LoadString( IDS_GS_CLASSNAME );

	if ( onrT <= 0L )	onrT = -1L;

	{
		TEXTGEOMETRIE	tg;
		OBJSTATISTIK	ost;
		OBJGEOMETRIE    og;
		MODRELATION		mr;
		CString			texttext;
		char			*txt;
		long			lcnt = 1L;
		long			*lCnt;
		long			gs_id = DEX_GetIdentFromClassName( (const char*)textID );

		ost.dwSize  = sizeof( OBJSTATISTIK );		// Größe dieser Struktur
		ost.lONr    = onrF;							// ObjektNummer
		ost.lIdent  = gs_id;						// Identifikator
		ost.iObjTyp = OGFlaeche;					// ObjektTyp
		ost.iFlags  = 0;							// Modi von QueryObjStatistik (unused)
		ost.lCnt    = 0L;							// Anzahl der Stützpunkte
		ost.iKCnt   = 0;							// Flächen: Anzahl der Konturen

		DEX_GetObjStatistik( ost );

		if ( ost.lCnt > 0L )
		{
			hoch = new double[ost.lCnt+1];
			rechts = new double[ost.lCnt+1];
		}
		else
		{
			hoch = new double[10];
			rechts = new double[10];
		}
		if ( ost.iKCnt > 0 )
			lCnt = new long[ost.iKCnt+1];
		else
			lCnt = new long[2];

		if ( !hoch )	return;
		if ( !rechts )	return;
		if ( !lCnt )	return;

		og.dwSize  = sizeof( OBJGEOMETRIE );
		og.lONr    = onrF;
		og.lIdent  = gs_id;
		og.iObjTyp = OGFlaeche;
		og.iFlags = OGModObject;
		og.iFlags  = og.iFlags | OGConverted
							   | OGNoMemoryObject
							   | OGForceGeometry;
		og.lCnt    = ost.lCnt;
		og.iKCnt   = ost.iKCnt;
		og.pdblX   = hoch;
		og.pdblY   = rechts;
		og.plCnt   = lCnt;

		DEX_GetObjGeometrie( og );

		dHMax = dHMin = hoch[0];
		dRMax = dRMin = rechts[0];
		for ( i = 1; i < short( lCnt[0]); i++ )
		{
			if ( dHMin > hoch[i])	dHMin = hoch[i];
			if ( dHMax < hoch[i])	dHMax = hoch[i];
			if ( dRMin > rechts[i])	dRMin = rechts[i];
			if ( dRMax < rechts[i])	dRMax = rechts[i];
		}
		dHoch = ( dHMin + dHMax ) / 2;
		dRechts = ( dRMin + dRMax ) / 2;

		tg.dwSize  = sizeof( TEXTGEOMETRIE );
		tg.lONr    = onrT;
		tg.lIdent  = gs_id;
		tg.iObjTyp = OGText;
		if ( onrT > 0 )	tg.iFlags = OGModObject;
		else			tg.iFlags = OGNewObject;

		tg.iFlags  = tg.iFlags | OGConverted
//							   | OGNoMemoryObject
							   | OGForceGeometry;
		tg.pdblX   = &dHoch;
		tg.pdblY   = &dRechts;
		texttext   = text;

		tg.lCnt    = 1L;
		tg.iKCnt   = 1;
		txt = texttext.GetBuffer( 0 );
		tg.pText   = txt;

		DEX_ModObjGeometrie( tg );
		texttext.ReleaseBuffer();
		onrT = tg.lONr;

		if (( onrT > 0L ) && ( onrF > 0L ))
		{
			mr.dwSize = sizeof( MODRELATION );
			mr.lPONr  = onrF;
			mr.lSONr  = onrT;
			mr.lRCode = -1;
			mr.iRTyp  = RTBegleitO;

			DEX_ModifyRelation( mr );
			DEX_RePaintObject(onrT );
		}
		if ( hoch )		delete [] hoch;
		if ( rechts )	delete [] rechts;
		if ( lCnt )		delete [] lCnt;
	}
}	// SetupTextObjekt

//	Sucht das Begleitobjekt zu einem gegebenen Objekt
BOOL PASCAL FAR RechBOProc( long ONr, long lRCode, short iRTyp, void *pData )
{
	*(long*)pData = ONr;
	return TRUE;
}

LRESULT CDatenListeDlg::TriasFindBObject( long onr )
{
	ENUMRELATIONOBJS        ero;
	LRESULT                         result = 0L;

	ASSERT( onr > 0L );

	ero.dwSize = sizeof( ENUMRELATIONOBJS );
	ero.lONr   = onr;
	ero.lRCode = -1L;
	ero.iRTyp  = RTBegleitO|RTBegleitU;
	ero.eFcn   = (ENUMRELOBJPROC)RechBOProc;
	ero.pData  = (void*)&result;

	DEX_EnumRelationObjects( ero );
	return result;
}	// TriasFindBObject

CString CDatenListeDlg::OrtFromIDE( const char* ide )
{
	ASSERT( AfxIsValidString( ide ));

	CString		strIDE = ide;
	CString		result, helper;
	short		i;

	if ( strIDE.GetLength() >= 2 )
	{
		helper = m_strIDE.Left( 2 );
		i = String2OISY(helper );
		result.Empty();
		if (( i >= 0 ) && ( i < m_arrOrte.GetSize()))
			result = m_arrOrte[i];
	}

	return result;
}	// OrtFromIDE

int CDatenListeDlg::AnzahlSelectedGS()
{	return m_arrID.GetSize();
}

int CDatenListeDlg::AnzahlMarkedGS()
{	return m_arrSelectedIDE.GetSize();
}

CString CDatenListeDlg::AktIDE()
{
	CString		result;
	int			i;

	if ( AnzahlMarkedGS() == 0 )	return result;

	result = m_arrSelectedIDE[0];

	i = m_lbListe.GetCaretIndex();
	if ( i != LB_ERR )
		if ( m_lbListe.GetSel( i ) > 0 )
			m_lbListe.GetText( i, result );

	return result;
}

void CDatenListeDlg::CopyArrayID( CStringArray& array )
{
	ASSERT_VALID( &array );

	array.RemoveAll();
	for ( int i = 0; i < m_arrID.GetSize(); i++ )
		array.Add( m_arrID[i]);
}

void CDatenListeDlg::CopyArraySelID( CStringArray& array )
{
	ASSERT_VALID( &array );

	array.RemoveAll();
	for ( int i = 0; i < m_arrSelectedIDE.GetSize(); i++ )
		array.Add( m_arrSelectedIDE[i]);
}

void CDatenListeDlg::OnSize(UINT nType, int cx, int cy) 
{
	CWnd *pWnd = AfxGetMainWnd();
	CRect	rectInside;

	GetInsideRect( rectInside );

//	CDialog::OnSize(nType, cx, cy);
	SECDialogBar::OnSize(nType, cx, cy);
/*	{
	if (nType != SIZE_MINIMIZED && cx > 0 && cy > 0) {
		int xAdjustedPos=0;
		int yAdjustedPos=0;
		int x, y;
		if(m_dwExStyle & CBRS_EX_GRIPPER) {
			if(m_dwStyle & CBRS_ORIENT_HORZ) {
			   x=m_GripperInfo.GetWidth();
			   y=m_GripperInfo.m_nGripperOffSidePadding;
			   cx=max(cx-(m_GripperInfo.GetWidth()+m_GripperInfo.m_nGripperOffSidePadding),0);
			   cy=max(cy-(2*m_GripperInfo.m_nGripperOffSidePadding),0);
			   }
			 else {
			   y=m_GripperInfo.GetHeight();
			   x=m_GripperInfo.m_nGripperOffSidePadding;
			   cx=max(cx-(2*m_GripperInfo.m_nGripperOffSidePadding),0);
			   cy=max(cy-(m_GripperInfo.GetHeight()+m_GripperInfo.m_nGripperOffSidePadding),0);
			   }
			xAdjustedPos=x;
			yAdjustedPos=y;
		}
		else if (m_dwExStyle & CBRS_EX_BORDERSPACE) {
			x = m_rcBorderSpace.left;
			y = m_rcBorderSpace.top;
			cx = max(cx - (m_rcBorderSpace.left + m_rcBorderSpace.right), 0);
			cy = max(cy - (m_rcBorderSpace.top + m_rcBorderSpace.bottom), 0);
		}
		else
		{
			x = 0;
			y = 0;
		}

		if (m_dwExStyle & CBRS_EX_STRETCH_ON_SIZE && m_pArrLayoutInfo != NULL) {
			HDWP hDWP = ::BeginDeferWindowPos(m_pArrLayoutInfo->GetSize());
			CSize sizeOrig = ((LayoutInfo*)m_pArrLayoutInfo->GetAt(0))->m_rect.Size();

			// Iterate through all child windows, readjusting size as needed
			for (int i = 1; i < m_pArrLayoutInfo->GetSize(); i++) {
				LayoutInfo* pLI = (LayoutInfo*)m_pArrLayoutInfo->GetAt(i);
				CRect newRect = pLI->m_rect;
				newRect.left = xAdjustedPos+(newRect.left * cx / sizeOrig.cx);
				newRect.top = yAdjustedPos+(newRect.top * cy / sizeOrig.cy);
				newRect.right = xAdjustedPos+(newRect.right * cx / sizeOrig.cx);
				newRect.bottom = yAdjustedPos+(newRect.bottom * cy / sizeOrig.cy);
				if (m_dwExStyle & CBRS_EX_BORDERSPACE)
					newRect.OffsetRect(m_rcBorderSpace.left, m_rcBorderSpace.top);
				if ( (hDWP = ::DeferWindowPos(hDWP, pLI->m_hWnd, NULL,
					newRect.left, newRect.top, newRect.Width(),
					newRect.Height(), SWP_NOACTIVATE | SWP_NOZORDER
					| ((m_bOptimizedRedrawEnabled) ? SWP_NOREDRAW : 0))) == NULL)
					TRACE(_T("Warning: DeferWindowPos failed - low system resources.  Code=0x%x\n"), GetLastError());
			}
			if (hDWP == NULL || !::EndDeferWindowPos(hDWP))
				TRACE(_T("Warning: DeferWindowPos failed - low system resources.  Code=0x%x\n"), GetLastError());

			// if this is a floating control bar, must force an invalidate
			// (no automatic cleanup)
			if(IsFloating()) this->Invalidate();
		}

		else if (m_dwExStyle & CBRS_EX_SIZE_TO_FIT) {
			HWND hWndChild;

#ifdef _DEBUG
			// Make sure we have only one child of this control bar.  Otherwise,
			// it becomes ambiguous which child to size to fit?
			int nChildWindows = 0;
			for (hWndChild = ::GetTopWindow(m_hWnd); hWndChild != NULL;
				hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
					nChildWindows++;
			if (nChildWindows > 1)
				TRACE(_T("More than one toplevel child of this control bar. Which one should be sized to fit?\n"));
#endif

			hWndChild = ::GetTopWindow(m_hWnd);
			if (hWndChild != NULL &&
				!::SetWindowPos(hWndChild, NULL, x, y, cx, cy,
					SWP_NOACTIVATE | SWP_NOZORDER
					| ((m_bOptimizedRedrawEnabled) ? SWP_NOREDRAW : 0)))
				TRACE(_T("Warning: SetWindowPos failed - low system resources.  Code=0x%x\n"), GetLastError());
		}
	}
	
	CControlBar::OnSize(nType, cx, cy);
	}
*/
	m_cx = cx;
	m_cy = cy;

	m_arrResizeItem.Resize( rectInside.Width(), rectInside.Height());

	RedrawWindow();
}

void CDatenListeDlg::OnGetMinMaxInfo( MINMAXINFO FAR* lpMMI )
{
//	CDialog::OnGetMinMaxInfo( lpMMI );
	SECDialogBar::OnGetMinMaxInfo( lpMMI );

	if ( m_arrResizeItem.Initialisiert())
	{
		CRect	rect;

		GetParent() -> GetClientRect( &rect );
//	POINT ptReserved;
//	POINT ptMaxSize;
//	POINT ptMaxPosition;
//	POINT ptMinTrackSize;
//	POINT ptMaxTrackSize;
	lpMMI -> ptMinTrackSize.x = m_lStartWidth;
//	lpMMI -> ptMinTrackSize.y = m_lMinHeight;
	lpMMI -> ptMinTrackSize.y = rect.Height();
	lpMMI -> ptMaxTrackSize.x = m_lStartWidth;
//	lpMMI -> ptMaxTrackSize.y = m_lMinHeight;		// bleibt unverändert
	lpMMI -> ptMaxTrackSize.y = rect.Height();
	}
}	// OnGetMinMaxInfo

void CDatenListeDlg::RefreshNFPG1()
{
	CString		strID;

	ASSERT( g_pNF_PG1 );

	TRY {
		OISY2String( m_iOISY, strID );

		g_pNF_PG1 -> Refresh();

		g_pNF_PG1 -> InitListen( strID );
		if ( g_pNF_PG1 -> GetSize() == 0 )
		{
			g_pNF_PG1 -> Reset();
			OISY2String2( m_iOISY, strID );
			g_pNF_PG1 -> InitListen( strID );
		}
	}
	CATCH (CDBException, d)
	{
		AfxMessageBox( "DB - Fehler!" );
		AfxMessageBox( d -> m_strError );
	}
	END_CATCH
}

void CDatenListeDlg::RefreshGebDB()
{
	CString		strID;

	OISY2String( m_iOISY, strID );

	if ( g_pNF_PG1GB != NULL )
	{
		g_pNF_PG1GB -> Close();
		delete g_pNF_PG1GB;
		g_pNF_PG1GB = NULL;
	}

	if ( g_pNF_PG1GB == NULL )
		g_pNF_PG1GB = new CSetNF_PG1GB( g_pDatabase );
	ASSERT( g_pNF_PG1GB );
	g_pNF_PG1GB -> InitListen( strID );
}

void CDatenListeDlg::RefreshDTDB()
{
	CString		strID;

	OISY2String( m_iOISY, strID );

	if ( g_pNF_PG2D != NULL )
	{
		g_pNF_PG2D -> Close();
		delete g_pNF_PG2D;
		g_pNF_PG2D = NULL;
	}

	g_pNF_PG2D = new CSetNF_PG2D( g_pDatabase );
	ASSERT( g_pNF_PG2D );
	g_pNF_PG2D -> InitListen( strID );
}

void CDatenListeDlg::RefreshVFDB()
{
	CString		strID;

	OISY2String( m_iOISY, strID );

	if ( g_pNF_PG2H != NULL )
	{
		g_pNF_PG2H -> Close();
		delete g_pNF_PG2H;
		g_pNF_PG2H = NULL;
	}

	if ( g_pNF_PG2H == NULL )
		g_pNF_PG2H = new CSetNF_PG2H( g_pDatabase );
	ASSERT( g_pNF_PG2H );
	g_pNF_PG2H -> InitListen( strID );
}

BOOL CDatenListeDlg::PreTranslateMessage(MSG* pMsg) 
{
	short	i;
	if ( pMsg -> message == WM_GETMINMAXINFO )
	{
		i = 0;
	}
	return SECDialogBar::PreTranslateMessage(pMsg);
}

double CDatenListeDlg::TB( const char* id )
{
	double	result;
	short	nr;

//	nr = OrtNr( id );
	if ( *id == 'J' )	nr = 4;
	else				nr = atoi( id );

	if ( nr )	result = m_pSetOrte -> TB( nr );
	else		result = 50;

	return result;
}

void CDatenListeDlg::SaveTRiDBNr( int verznr )
{
	BOOL		opened = FALSE;
	CxString	strNR;

	if ( NULL == g_pSetTriDB )
		g_pSetTriDB = new CTriDBSet( g_pDatabase );

	ASSERT( g_pSetTriDB );
	if ( !g_pSetTriDB -> IsOpen())
	{
		g_pSetTriDB -> Open();
		opened = TRUE;
	}

	strNR.Empty();
	strNR.AppendF( verznr, -1 );
	for ( int i = 0; i < m_arrAlleID.GetSize(); i++ )
	{
		g_pSetTriDB -> AddNew();
		g_pSetTriDB -> m_NFPG1_IDE = m_arrAlleID[i];
		g_pSetTriDB -> m_TRIDB_NR  = strNR;
		g_pSetTriDB -> Update();
	}

	if ( opened )	g_pSetTriDB -> Close();
	else			g_pSetTriDB -> Requery();
}

long CDatenListeDlg::GSohneIDE()
{
	long			result = 0L;
	long			w[2048], h[256];
	ENUMNOKEYLONG	enkl;
	ENUMLONGKEY		elk;
	short			i;

	if ( AnzahlMarkedGS() > 0 )		return result;

	h[0] = 2L;
	h[1] = 253L;
	enkl.eFcn = (ENUMNOKEYLONGPROC)RechIDProc;
	enkl.ePtr  = (void*)h;

	//	alle OR-Fenster beschaffen
	DEX_EnumORWindows( enkl );

	//	nur ein einzelnes OR-Window mit einem einzelnen
	//	kann eindeutig ein GS ohne IDE zur Bearbeitung bereitstellen
	if ( h[0] != 3L )		return result;

	elk.eKey = h[2];
	elk.eFcn = (ENUMLONGKEYPROC)RechIDProc;
	elk.ePtr  = (void*)w;
//	enkl.eFcn = (ENUMNOKEYLONGPROC)RechIDProc;
//	enkl.ePtr  = (void*)w;

	w[0] = 2L;
	w[1] = 2046L;

//	DEX_EnumAllORObjects( elk );
	DEX_EnumSelectedObjects( elk );
//	DEX_EnumSelectedObjects( enkl );

	if ( w[0] != 3L )		return result;

	for ( i = 0; i < m_arrSonstONr.GetSize(); i++ )
		if ( w[2] == (long)m_arrSonstONr[i])
	{
		result = w[2];
		break;
	}

	return result;
}

void CDatenListeDlg::OnBGedr() 
{
	UpdateData( TRUE );
	if ( m_arrSelectedIDE.GetSize() != 1 )	return;

	CxString	ide, text, caption;
	ide = m_arrSelectedIDE[0];

	if ( m_bBBGedr )
		AfxFormatString1( text, IDS_FRAGEMARKDRUCK1, ide );
	else
		AfxFormatString1( text, IDS_FRAGEMARKDRUCK2, ide );

	caption.LoadString( IDS_CAPTMARKDRUCK );
	if ( MessageBox( text, caption, MB_ICONQUESTION|MB_YESNO ) != IDYES )
	{
		m_bBBGedr = !m_bBBGedr;
		UpdateData( FALSE );
		return;
	}

	CBasisSatz		*pS = NULL;

	pS = g_pNF_PG1 -> FindIDE( ide );
	if ( pS != NULL )
	{
		pS -> m_bBBGedr = m_bBBGedr;
		g_pNF_PG1 -> RewriteIDE( pS );
	}
}

void CDatenListeDlg::OnGGedr() 
{
	UpdateData( TRUE );
	if ( m_arrSelectedIDE.GetSize() != 1 )	return;

	CxString	ide, text, caption;
	ide = m_arrSelectedIDE[0];

	if ( m_bGBGedr )
		AfxFormatString1( text, IDS_FRAGEMARKDRUCK3, ide );
	else
		AfxFormatString1( text, IDS_FRAGEMARKDRUCK4, ide );

	caption.LoadString( IDS_CAPTMARKDRUCK );
	if ( MessageBox( text, caption, MB_ICONQUESTION|MB_YESNO ) != IDYES )
	{
		m_bGBGedr = !m_bGBGedr;
		UpdateData( FALSE );
		return;
	}

	CBasisSatz		*pS = NULL;

	pS = g_pNF_PG1 -> FindIDE( ide );
	if ( pS != NULL )
	{
		pS -> m_bGBGedr = m_bGBGedr;
		g_pNF_PG1 -> RewriteIDE( pS );
	}
}

void CDatenListeDlg::OnLoeschen() 
{
	CxString	ide;
	CxString	text, caption, ort;

	UpdateData( TRUE );
	m_bLoeschen = FALSE;	// immer auf FALSE halten
	UpdateData( FALSE );

	ASSERT( m_arrSelectedIDE.GetSize() == 1 );
	if ( m_arrSelectedIDE.GetSize() != 1 )	return;
	ide = m_arrSelectedIDE[0];

	AfxFormatString1( text, IDS_FRAGELOESCHEN, ide );
	caption.LoadString( IDS_CAPTLOESCHEN );
	if ( MessageBox( text, caption, MB_ICONQUESTION|MB_YESNO ) != IDYES )	return;

	g_pNF_PG1 -> ResetIDE( ide );	// Setzt Summen auf 0

	CBasisSatz		*pS = NULL;

	pS = g_pNF_PG1 -> FindIDE( ide );
	if ( pS != NULL )
	{
		ort = pS -> Ort();
		ort += "   ";
		ort += pS -> PLZ();
		m_strOrt = ort;
		m_strStr = pS -> Strasse();
		m_strFlur = pS -> Flur();
		m_strFlurstk = pS -> Flurstk();
		m_strEigent = pS -> Besitzer();

		text.Empty();
		text.printf( "%.2lf m²", pS -> GEF());
		text.FormatZahl( 2 );
		m_strGSFlaeche = text;

		text.Empty();
		text.printf( "%.2lf m²", pS -> BFlaeche());
		text.FormatZahl( 2 );
		m_strBFlaeche  = text;

		text.Empty();
		text.printf( "%.2lf DM", pS -> Beitrag());
		text.FormatZahl( 2 );
		m_strBeitrag   = text;

		m_bBBGedr = pS -> m_bBBGedr;
		m_bGBGedr = pS -> m_bGBGedr;
	}
	g_pNF_PG1GB -> DeleteIDE( ide );
	g_pNF_PG2D -> DeleteIDE( ide );
	g_pNF_PG2H -> DeleteIDE( ide );

	UpdateData( FALSE );
}

BOOL CDatenListeDlg::ObjektInArray( long onr, CPtrArray& array )
{
	BOOL	result = FALSE;
	long	l;

	for ( l = 0; l < array.GetSize(); l++ )
		if ( result = ((long)array[l] == onr ))		break;

	return result;
}

void CDatenListeDlg::ResetInvalidDockBars( CControlBar* pTargetBar )
{
	HWND	hWnd = AfxGetMainWnd() -> m_hWnd;

	for (HWND hWndChild = ::GetTopWindow(hWnd); hWndChild != NULL;
		hWndChild = ::GetNextWindow(hWndChild, GW_HWNDNEXT))
	{
	SECDockBar* pBar = (SECDockBar*)CWnd::FromHandlePermanent(hWndChild);
		
		if (pBar && pBar->IsKindOf(RUNTIME_CLASS(SECDockBar))) {
			if (NULL == pTargetBar)
				pBar->m_arrInvalidBars.RemoveAll();
			else {
			// finden der Einen und rauslöschen
				for (int i = 0; i < pBar->m_arrInvalidBars.GetSize(); i++) 
				{
					if (pTargetBar == (CControlBar *)pBar->m_arrInvalidBars[i]) 
					{
						pBar->m_arrInvalidBars.RemoveAt(i);
						break;
					}	/*if*/
				}		/*for*/
			}
		}
	}
}

void CDatenListeDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	SECDialogBar::OnShowWindow(bShow, nStatus);
}
