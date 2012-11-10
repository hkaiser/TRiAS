#include "stdafx.h"
#include "KartenImpl.h"
#include <ospace/stlex/boolops.h>

#include "TKarten.h"
//#include "TKPpg.h"
#include "dialogs.h"
#include "DlgPgBW.h"
#include "ImagePropertySheet.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// Prototypen für Umwandlung Ident <--> ObjektKlassenSchlüssel
const int MAX_OKS_LENX = 32;		// max. Zeichenkettenlänge für ObjektKlassenSchlüssel
#include <xtension.h>
#include <xtensnx.h>

HRESULT ClassFromIdentX (ULONG ulIdent, char *pBuffer, int iBuffLen);
HRESULT IdentFromClassX (LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew);
HRESULT ClassFromIdentX (HPROJECT hPr, ULONG ulIdent, char *pBuffer, int iBuffLen);
HRESULT IdentFromClassX (HPROJECT hPr, LPCSTR pcClass, ULONG *pulIdent, BOOL fCreateNew);


/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNCREATE(CKartenCtrl, CTriasVMD)
IMPLEMENT_OLETYPELIB(CKartenCtrl, _tlid, _wVerMajor, _wVerMinor)

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CKartenCtrl, CTriasVMD)
	//{{AFX_MSG_MAP(CKartenCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
//	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CKartenCtrl, CTriasVMD)
	//{{AFX_DISPATCH_MAP(CKartenCtrl)
	// NOTE - ClassWizard will add and remove dispatch map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CKartenCtrl, CTriasVMD)
	//{{AFX_EVENT_MAP(CKartenCtrl)
	// NOTE - ClassWizard will add and remove event map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_EVENT_MAP
END_EVENT_MAP()

/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CKartenCtrl, 1)
//	PROPPAGEID(CKartenPropPage::guid)
END_PROPPAGEIDS(CKartenCtrl)

/////////////////////////////////////////////////////////////////////////////
// Interface Maps

BEGIN_INTERFACE_MAP(CKartenCtrl, CTriasVMD)
	INTERFACE_MAP_VISMODULE(CKartenCtrl)
END_INTERFACE_MAP()

IMPLEMENT_VISMOD_INTERFACE(CKartenCtrl)

/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid
// 07963893-3123-101C-BB62-00AA0018497C	- topographische Karten

#ifdef _WIN32
IMPLEMENT_OLECREATE_EX(CKartenCtrl, _T( "TRiAS.VMTopKarten.1" ),
	0x07963893L, 0x3123, 0x101C, 0xBB, 0x62, 0x00, 0xAA, 0x00, 0x18, 0x49, 0x7C)
#else
IMPLEMENT_OLECREATE_EX(CKartenCtrl, _T( "karten" ),
	0x321C58E0L, 0x0C60, 0x101B, 0xAA, 0xE1, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7)
#endif

	//  Event dispatch interface for CKartenCtrl

//	[ uuid(0603C948-B16A-11CF-86AA-00A024145748),
const IID BASED_CODE IID_DKarten =
		{ 0x0603c948, 0xb16a, 0x11cf, { 0x86, 0xaa, 0x0, 0xa0, 0x24, 0x14, 0x57, 0x48 } };

//	[ uuid(0603C949-B16A-11CF-86AA-00A024145748),
const IID BASED_CODE IID_DKartenEvents =
		{ 0x0603c949, 0xb16a, 0x11cf, { 0x86, 0xaa, 0x0, 0xa0, 0x24, 0x14, 0x57, 0x48 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwKartenOleMisc =
	OLEMISC_INVISIBLEATRUNTIME |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CKartenCtrl, IDS_KARTEN, _dwKartenOleMisc)

/////////////////////////////////////////////////////////////////////////////
// CKartenCtrl::CKartenCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CKartenCtrl

//static LPCTSTR g_szTKLongName = TEXT( "Hintergrundrasterbilder\nkarten" );

LPCTSTR CKartenCtrl::GetProgIdent()		// liefert ProgIdent "TRiAS.VM...."
	{ return _T( "TRiAS.VMTopKarten.1" ); }

BOOL CKartenCtrl::CKartenCtrlFactory::UpdateRegistry(BOOL bRegister) {
	if( bRegister ) {
		CString	S;
		VERIFY( S.LoadString( IDS_REGENTRY ) );
		return VMDRegister( AfxGetInstanceHandle(), m_clsid, m_lpszProgID, S, OTFlaeche );
	} else {
		return VMDUnRegister( m_clsid, m_lpszProgID );
	}
}

/////////////////////////////////////////////////////////////////////////////
// CKartenCtrl::CKartenCtrl - Constructor

//static TCHAR szPalTypes[] = _T("Standardfarben,Grau (normal),Grau (hell)");

CKartenCtrl::CKartenCtrl() : CTriasVMD() {
	InitializeIIDs(&IID_DKarten,&IID_DKartenEvents);
	// TODO: Initialize your control's instance data here.
//	m_bMapsVisible = TRUE;
	m_nTranspChannel = 0;
	m_lMapMCode = -1;
	m_pMemBlock = new CMemBlock( Size2MB );
//	m_pPicture	= new CBmpPicture( m_pMemBlock );
	m_pPicture	= NULL; // new CTifPicture( m_pMemBlock );
	CString	strPalTypes;
	CString	strPalType;
	VERIFY(strPalTypes.LoadString(IDS_PALETTES));
	for( int i = 0; ; i++ ) {
		::AfxExtractSubString( strPalType, strPalTypes, i, ',' );
		if( strPalType.IsEmpty() )
			break;
		m_listOfPalTypes.SetAt( strPalType, (void*) i );
	}
    m_pVI = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CKartenCtrl::~CKartenCtrl - Destructor

CKartenCtrl::~CKartenCtrl() {
	// TODO: Cleanup your control's instance data here.
	DeleteContents( );
	POSITION	pos;
	CObject*	pValue;
	CString		sKey;
	for( pos = m_listOfPalettes.GetStartPosition( ); pos != NULL; ) {
		m_listOfPalettes.GetNextAssoc( pos, sKey, pValue );
		delete pValue;
		m_listOfPalettes.RemoveKey( sKey );
	}
	m_listOfPalTypes.RemoveAll();
	CRuntimeClass	*pRT;
	for( pos = m_pictTypes.GetStartPosition(); NULL != pos; ) {
		m_pictTypes.GetNextAssoc( pos, (void*&) pRT, (void*&) pValue );
		ASSERT_KINDOF( CPicture, pValue );
		delete pValue;
	}
	m_pictTypes.RemoveAll();
	delete m_pMemBlock;
}

/////////////////////////////////////////////////////////////////////////////
// CKartenCtrl::DoPropExchange - Persistence support

void CKartenCtrl::DoPropExchange(CPropExchange* pPX) {
//	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
//	CTriasVMD::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.
}

/////////////////////////////////////////////////////////////////////////////
// CKartenCtrl::OnResetState - Reset control to default state

void CKartenCtrl::OnResetState() {
//	CTriasVMD::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}

/////////////////////////////////////////////////////////////////////////////
// muß hier darhinnen sein, damit '_szProgID_CKartenCtrl' erreichbar ist

static TCHAR szShowEver[] = "<beliebig>";
static LPCTSTR g_szEmpty = TEXT( ":-(" );

BOOL CKartenCtrl::OnQueryParameters(
						CWnd *pParentWnd,
						const DWORD lONr, 
						class VisInfo * pVI, 
						LPCTSTR pszVisStr, 
						LPSTR pBuffer, 
						short iLen,
						short * piOTypes)
{
// KK010108
	m_lMapONr = lONr;
//	long lIdent = DEX_GetObjIdent(lONr);
//	m_hPr = DEX_GetObjectsProject(lIdent);	// aktuelle Datenquelle

	m_hPr = DEX_GetObjectProject(lONr);	// aktuelle Datenquelle

	ULONG lCount = DEX_GetOpenConnectionCount(QDCAllOpen);
	if ( lCount != m_strDQ.Count()) {
// strDQ + strKVZ aktualisieren !!
		SetDQ();
		ModKVZ();
		SetKVZCodes();
	}

	CString	S;

	CDlgPgColor			pgColor;
	CDlgPgBW			pgBWPict;
	CDlgPgVisparam		pgVisparam;
	CDlgPgDirectories	pgDirs;

	CImagePropertySheet	dlg( IDS_DIALOG_TITLE, pParentWnd );

	dlg.AddPage( &pgColor );
	dlg.AddPage( &pgBWPict );
//	dlg.AddPage( &pgVisparam );
	dlg.AddPage( &pgDirs );

	::AfxExtractSubString( S, pVI->VisName(), 0, ';' );
	pgColor.m_strMapPalette = S;

	::AfxExtractSubString( S, pVI->VisName(), 1, ';' );
	pgVisparam.m_strFromScale = "0" == S || S.IsEmpty() ? szShowEver : S;
	::AfxExtractSubString( S, pVI->VisName(), 2, ';' );
	pgVisparam.m_strToScale = "0" == S || S.IsEmpty() ? szShowEver : S;

	pgColor.m_strViewPalette = m_strViewPalette;
	pgColor.m_chkSingleMap = m_strViewPalette.IsEmpty() ? 0 : 1;
    pgColor.m_bTransparent = m_nTranspChannel ? TRUE : FALSE;

//	pgVisparam.m_bMapsVisible = m_bMapsVisible;

	////////////
	// Listboxen werden in 'OnInitDialog' gefüllt

	DWORD	w;
	for( POSITION pos = m_listOfPalTypes.GetStartPosition(); pos; ) {
		m_listOfPalTypes.GetNextAssoc( pos, S, (void*&) w );
		ASSERT( w < N_PALETTETYPES );
		pgColor.m_strPalettes.SetAtGrow( w, S );
	}

	for( int i = 0; i < m_strMapDirs.GetSize(); i++ )
		pgDirs.m_strMapDirs.Add( m_strMapDirs[i] );

	pgBWPict.m_bTransparent = m_nTranspChannel ? TRUE : FALSE;
	pgBWPict.m_nChannel = m_nTranspChannel ? m_nTranspChannel - 1 : 0;


	if( IDOK == dlg.DoModal( ) ) {
        m_nTranspChannel = 0;

        if (1 == dlg.m_iLastActivePage && pgBWPict.m_bTransparent)
		    m_nTranspChannel = pgBWPict.m_nChannel + 1;
        else if (0 == dlg.m_iLastActivePage && pgColor.m_bTransparent)
            m_nTranspChannel = 1;

//		m_strViewPalette = ( 0 == pgColor.m_chkSingleMap ) ? TEXT( "" ) : pgColor.m_strViewPalette;
//		S = m_strViewPalette.IsEmpty() ? g_szEmpty : m_strViewPalette;
		m_strViewPalette = pgColor.m_strViewPalette;
		CString	strView;
		if( DEX_GetActiveSight(strView.GetBufferSetLength(_MAX_PATH))) {
			strView.ReleaseBuffer(-1);
			S.Format( "%s@%d;%ld", m_strViewPalette, m_nTranspChannel, 0L );	// #fje19991101 0L eingefügt
//			SetMCodeValue( strView, m_lPalMCode, S, S.GetLength() );
			SetMCodeValue( strView, PalMCode(m_hPr), S, S.GetLength() );
		}

//		m_bMapsVisible = pgVisparam.m_bMapsVisible;

		S.Format( _T("t=10,\"%s;0;0;\"; z=\"karten\":%%%ld;")
			, (LPCTSTR) pgColor.m_strMapPalette
//			, m_lMapMCode
			, MapMCode(m_hPr)
			);
		if( iLen > S.GetLength() + 1 ) {
			strcpy( pBuffer, S );
		}
		*piOTypes = (OTFlaeche);


		m_strMapDirs.RemoveAll();


// KK010108
// Aktualisieren Kartenverzeichnis
		CPrjMap strKVZ;

		CPrjMapOutputIter outer(&strKVZ);

		long *pRef = new long [100];
		for( int i = 0; i < pgDirs.m_strMapDirs.GetSize(); i++ ) {

			S = pgDirs.m_strMapDirs[i];

			if( '\\' != S.Right( 1 ) && '/' != S.Right( 1 ) )
				S += '\\';

			m_strMapDirs.Add( S );

			if ( pgDirs.ChangeKVZList()) {		// Dir geändert

				if ( FindMapList( pRef, (LPCTSTR) S)) {

					for ( long k = 0; k < *pRef; k++ ) {
						HPROJECT hPr = (HPROJECT) *(pRef+k+1);
						strKVZ.InsertKVObject(hPr,(LPCTSTR)S);
					}

				} else {
					strKVZ.InsertKVObject(m_hPr,(LPCTSTR)S);
				}
			}
			

		}

		DELETE_OBJ(pRef);

		m_strKVZ.Clear();

		m_strKVZ = strKVZ;

		return TRUE;
	}

	return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CKartenCtrl message handlers

void CKartenCtrl::DeleteContents( ) {
	POSITION	pos;
	CObject*	pValue;
	CString		sKey;

// KK010108
// Loeschen eines Kartenverzeichnisses

	m_lMapIdent = 0L;
	m_lMapMCode = 0L;
	m_lPalMCode = 0L;
	m_bMatchMapName = FALSE;
	m_bMatchMapData = FALSE;
	m_bPalRealized = FALSE;

	m_strMapDirs.RemoveAll();

//	for( pos = m_listOfSights.GetStartPosition( ); pos != NULL; ) {
//		m_listOfSights.GetNextAssoc( pos, sKey, (void*&) pValue );
//		m_listOfSights.RemoveKey( sKey );
//	}


// KK010108
// m_strKVZ - Erase
	m_strDQ.Clear();
	m_strKVZ.Clear();

	for( pos = m_listOfMaps.GetStartPosition(); pos != NULL; ) {
		m_listOfMaps.GetNextAssoc( pos, sKey, pValue );
		delete pValue;
		m_listOfMaps.RemoveKey( sKey );
	}
	CTriasVMD::DeleteContents( );
	ASSERT( m_listOfSights.IsEmpty( ) );
}

////////////////////////////////////////////////////////////////////////////////////

BOOL CKartenCtrl::OnProjectOpen( LPCTSTR pszNewProject ) {
	ASSERT(m_listOfSights.IsEmpty());
	ASSERT(m_listOfMaps.IsEmpty());

	m_hPr = 0;

// KK001220
// Projekt ( *.riw) enthält kein Kartenverzeichnis 
// - in Datenquellen suchen und Liste kumulieren

	CTriasVMD::OnProjectOpen( pszNewProject );

	m_strDQ.clear();	// Verzeichnis der Datenquellen (HPROJECT,DATEI)

	SetDQ();

	m_strKVZ.clear();

	SetKVZ();	// For Each der Datenquellen !!

	m_strKVZCodes.clear();

	SetKVZCodes();	// For Each der Datenquellen-HeaderEinträge !!

	m_hPr = DEX_GetDataSourceHandle();

//----------------------------------------------------------------------------
// KK010105
/*--------------------
// Durchsuchen der INI-DatenquellenDateien

	CString	myIniSection, myIniEntry;

	VERIFY( myIniSection.LoadString( IDS_MYINISECTION ) );
	VERIFY( myIniEntry.LoadString( IDS_MAPDIRENTRY ) );

	CString	strMapDir;
	char	ch;
	for( int i = 1;; i++ ) {
		strMapDir.Format( "%s%d", (LPCTSTR) myIniEntry, i );
		strMapDir = GetProfileString( myIniSection, strMapDir ); // myIniEntry + (char) ( '1' + i ) );
		if( strMapDir.IsEmpty() )
			break;
		if( '\\' != ( ch = strMapDir[ strMapDir.GetLength() - 1 ] ) && '/' != ch )
			strMapDir += '\\';
		strMapDir.MakeLower();
		m_strMapDirs.Add( strMapDir );
	}

// KK010105
--------------------------------------------------------------------------------*/

// Nur, falls in allen Datenquellen kein Verzeichnis vorhanden ist, Standard setzen

	if( 0 == m_strMapDirs.GetSize() ) {

// KK001116
		CString	myIniSection, myIniEntry;
		CString	strMapDir;

		VERIFY( myIniSection.LoadString( IDS_MYINISECTION ) );
		VERIFY( myIniEntry.LoadString( IDS_MAPDIRENTRY ) );

		CString	S;
		DEX_GetDataSourceName( m_hPr, S.GetBufferSetLength( _MAX_PATH ) );
		CPath	pathOfProj( S );

		VERIFY( myIniEntry.LoadString( IDS_DEFMAPDIR ) );
		strMapDir = pathOfProj.Drive() + pathOfProj.Dir() + myIniEntry;
		m_strMapDirs.Add( strMapDir );
	}


//--------------------------------------------------------------------------------
	
/*-----------------------------KK010111---------------------------------------------

	CString	strHdrValue;

	if( GetGeoDBEntry( m_hPr,szOldPdbEntry, strHdrValue ) ) {
		::LAfxExtractSubBase( m_lMapMCode, m_nMCodeBase, strHdrValue, 1, ';' );
		::LAfxExtractSubBase( m_lPalMCode, m_nMCodeBase, strHdrValue, 2, ';' );
	}

	if( GetGeoDBEntry(m_hPr, szTKPdbEntry, strHdrValue ) )
		::LAfxExtractSubBase( m_lMapMCode, m_nMCodeBase, strHdrValue, 0, ';' );

	if( GetGeoDBEntry(m_hPr, szViewPdbEntry, strHdrValue ) )
		::LAfxExtractSubBase( m_lPalMCode, m_nMCodeBase, strHdrValue, 0, ';' );

*/
	CString	strHdrValue;
	GetGeoDBEntry(HACTPROJECT, szMatchPdbEntry, strHdrValue);

/*
	CString	strHdrData;
	GetGeoDBEntry( m_hPr,szDataPdbEntry, strHdrData );
*/
// KK010109
// Parameter @TopKartMatch in DB-Header : falls true - Bildname über uniqueIdent ( TK@...)
//	m_bMatchMapName = strHdrValue.IsEmpty() ? TRUE : (BOOL) atol( strHdrValue );
	m_bMatchMapName = strHdrValue.IsEmpty() ? FALSE : (BOOL) atol( strHdrValue );

/*
	if( 0L == m_lMapMCode )
		m_lMapMCode = 99999301;

	if( 0L == m_lPalMCode )
		m_lPalMCode = 99999302;


-----------------------------KK010111---------------------------------------------*/

	m_bProjDrawn = FALSE;

	m_minSize = 5.0;
	COleVariant	v;
	GetRegistryValue( _T("MinimumSize"), v );
	if( VT_I4 == v.vt ) {
		m_minSize = (double) v.lVal;
	} else if( VT_BSTR == v.vt ) {
		strHdrValue = v.bstrVal;
		m_minSize = atof(strHdrValue);
	}
	return TRUE;
}
//------------------------------------------------------------------------------
// KK010111
//-----------------------------------------------------------------------------
BOOL  CKartenCtrl:: SetKVZCodes(void)
{

	m_strKVZCodes.clear();

	CPrjMapInputIter iter (&m_strDQ); 
 
	while ( !iter.EndMarker()) {
			LoadHeader (iter.HProject());
		++iter;
	}

	// bricht ab, wenn ein Fehler auftritt (im Gegensatz zu for_each()
	//bool fResult = boolop_and(CPrjMapInputIter(&m_strDQ), CPrjMapInputIter(), operator ());

	return true;
}
//--------------------------------------------------------------------
BOOL  CKartenCtrl:: LoadHeader(HPROJECT hPr)
{

	m_lMapIdent = 0L;
	m_lMapMCode = 0L;
	m_lPalMCode = 0L;

	CString	strHdrValue;

	if( GetGeoDBEntry( hPr,szOldPdbEntry, strHdrValue ) ) {
		::LAfxExtractSubBase( m_lMapIdent, m_nMCodeBase, strHdrValue, 0, ';' );
		::LAfxExtractSubBase( m_lMapMCode, m_nMCodeBase, strHdrValue, 1, ';' );
		::LAfxExtractSubBase( m_lPalMCode, m_nMCodeBase, strHdrValue, 2, ';' );
	}

	if( GetGeoDBEntry(hPr, szTKPdbEntry, strHdrValue ) )
		::LAfxExtractSubBase( m_lMapMCode, m_nMCodeBase, strHdrValue, 0, ';' );

	if( GetGeoDBEntry(hPr, szViewPdbEntry, strHdrValue ) )
		::LAfxExtractSubBase( m_lPalMCode, m_nMCodeBase, strHdrValue, 0, ';' );

//	GetGeoDBEntry( hPr,szMatchPdbEntry, strHdrValue );
////	m_bMatchMapName = FALSE;
//	m_bMatchMapName = strHdrValue.IsEmpty() ? FALSE : (BOOL) atol( strHdrValue );

	CString	strHdrData;
	GetGeoDBEntry( hPr,szDataPdbEntry, strHdrData );

	m_bMatchMapData = strHdrData.IsEmpty() ? FALSE : (BOOL) atol( strHdrData );


// KK010109
// Parameter @TopKartMatch in DB-Header : falls true - Bildname über uniqueIdent ( TK@...)

	if( 0L == m_lMapMCode )
		m_lMapMCode = 99999301;

	if( 0L == m_lPalMCode )
		m_lPalMCode = 99999302;


	m_strKVZCodes.InsertObject (hPr,m_lMapMCode);
	m_strKVZCodes.InsertObject (hPr,m_lPalMCode);

// Objektklassenschlüssel
	if( 0L == m_lMapIdent )
		m_lMapMCode = 99999300;

/*
	if( 0L != m_lMapIdent ) {
		char Ident[MAX_OKS_LENX + 1];
		wsprintf ( Ident,"%ld",m_lMapIdent);
		ULONG uIdent;
		HRESULT hr = IdentFromClassX (hPr,Ident,&uIdent,true);
		m_lMapIdent = uIdent;
	}
*/

	return TRUE;
}
//------------------------------------------------------------------------------

//-------------------------------------------------------------------------------
BOOL  CKartenCtrl:: LoadSection(HPROJECT hPr, CPrjMap * pKVZ)
{
// KK010105
// durchsuchen der INI-DatenquellenDateien

	CString	myIniSection, myIniEntry;

	VERIFY( myIniSection.LoadString( IDS_MYINISECTION ) );
	VERIFY( myIniEntry.LoadString( IDS_MAPDIRENTRY ) );

	CString	strMapDir;
	char	ch;
	for( int i = 1;; i++ ) {
		strMapDir.Format( "%s%d", (LPCTSTR) myIniEntry, i );
		strMapDir = GetProfileString( hPr,myIniSection, strMapDir ); // myIniEntry + (char) ( '1' + i ) );
		if( strMapDir.IsEmpty() )
			break;
		if( '\\' != ( ch = strMapDir[ strMapDir.GetLength() - 1 ] ) && '/' != ch )
			strMapDir += '\\';
		strMapDir.MakeLower();

		if (m_bMatchMapData) {
			m_strMapDirs.Add( strMapDir );	// alle Verzeichnisse
		} else {
			if ( MapUnique( m_strMapDirs.GetSize(), (LPCTSTR)strMapDir)) {
				m_strMapDirs.Add( strMapDir );
			}
		}

		pKVZ->InsertKVObject(hPr,(LPCTSTR)strMapDir);

	}


	return true;
}
// KK010105
//--------------------------------------------------------------------------------
long CKartenCtrl :: MapMCode(HPROJECT hPr) {

	CPrjVec::iterator it = m_strKVZCodes.find(hPr);
	CCodesFromProject::iterator m_itl;

	long lMCode = 0;

	if (it != m_strKVZCodes.end()) {
		m_itl = (*it).second.begin();
		if (m_itl != (*it).second.end()) {
			lMCode = *m_itl;
		}
	}
	return 0 != lMCode ? lMCode : m_lMapMCode;

}
//-----------------------------------------------------------------------------
long CKartenCtrl :: PalMCode(HPROJECT hPr) {

	CPrjVec::iterator it = m_strKVZCodes.find(hPr);
	CCodesFromProject::iterator m_itl;

	long lMCode = 0;

	if (it != m_strKVZCodes.end()) {
		m_itl = (*it).second.begin();
		if (m_itl != (*it).second.end()) {
			++m_itl;
			lMCode = *m_itl;
		}
	}
	return 0 != lMCode ? lMCode : m_lPalMCode;
}
//-----------------------------------------------------------------------------
BOOL  CKartenCtrl:: ModKVZ(void)
{
CPrjMapInputIter iter (&m_strDQ); 
CPrjMapInputIter oter (&m_strKVZ); 

CPrjMap::iterator it = m_strKVZ.begin();
CPrjMap::iterator itd = m_strDQ.begin();

// alte DQ herausnehmen
	while (!oter.EndMarker()) {
		itd = m_strDQ.find(oter.HProject());
//		it = m_strKVZ.find(oter.HProject());
		if (itd == m_strDQ.end())		// nicht mehr als DQ vorhanden
			oter.erase_act();
		else	
			++oter;
	}

// Neue DQ hinzufügen
	while (!iter.EndMarker()) {
		ModMapList (*iter);
		++iter;
	}
	return true;
}


//-----------------------------------------------------------------------------
BOOL  CKartenCtrl:: SetKVZ(void)
{

	CPrjMapInputIter iter (&m_strDQ); 
 
	while ( !iter.EndMarker()) {
			MapList (*iter);
		++iter;
	}

	// bricht ab, wenn ein Fehler auftritt (im Gegensatz zu for_each()
	//bool fResult = boolop_and(CPrjMapInputIter(&m_strDQ), CPrjMapInputIter(), operator ());

	return true;
}
//-----------------------------------------------------------------------------
bool CKartenCtrl :: MapList (const char *value) {


	CPrjMapOutputIter outer(&m_strKVZ);

	HPROJECT hPr = DEX_GetDataSourceHandleEx(value);
	LoadSection ( hPr , &m_strKVZ);


	return true;
}

//-----------------------------------------------------------------------------
bool CKartenCtrl :: ModMapList (const char *value) {


	CPrjMapOutputIter outer(&m_strKVZ);

	HPROJECT hPr = DEX_GetDataSourceHandleEx(value);

	CPrjMap::iterator it = m_strKVZ.end();

	it = m_strKVZ.find(hPr);

	if (it == m_strKVZ.end()) 
		LoadSection ( hPr , &m_strKVZ);

	return true;

}

//-----------------------------------------------------------------------------
BOOL  CKartenCtrl:: SetDQ(void)

{

	m_strDQ.clear();	// Verzeichnis der Datenquellen (HPROJECT,DATEI)

	CPrjMapOutputIter iter(&m_strDQ);

	ENUMNOKEY EN;
//	Bestimmen der Anzahl der Datenquellen

	EN.eFcn = ( ENUMNOKEYPROC) SucheDatenQuellen;
	EN.ePtr = (void *)&m_strDQ;
	DEX_EnumDataSources(EN);

	return true;
}

//---------------------------------------------------------------------
extern "C" 
BOOL PASCAL _XTENSN_EXPORT SucheDatenQuellen (char *pName, bool , void *pData)
{


	CPrjMap* m_pDQ = (CPrjMap *)pData;


	m_pDQ->InsertObject((const char *)pName);

	return TRUE;

}
//////////KK010105//////////////////////////////////////////////////////////////////
bool CPrjMap::InsertKVObject (HPROJECT hPr,const char *pName)
{

	iterator it =  end();

	it = find(hPr);

	if (it != end()) {
	// nicht erstes Objekt dieser DQ
	
	} else {
	// erstes Objekt dieser DQ
	pair<iterator, bool> p = insert (value_type(hPr, CCardsFromProject(hPr)));

		it = p.first;
		// p.second ==> success
	}

	size_t lCnt = (*it).second.size();
	
	(*it).second.push_back(pName);
	return lCnt+1 == (*it).second.size();
}
//////////KK010111//////////////////////////////////////////////////////////////////
bool CPrjVec::InsertObject (HPROJECT hPr,long lMCode)
{

	iterator it =  end();

	it = find(hPr);

	if (it != end()) {
	// nicht erstes Objekt dieser DQ
	
	} else {

	// erstes Objekt dieser DQ
		pair<iterator, bool> p = insert (value_type(hPr, CCodesFromProject()));

		it = p.first;
		// p.second ==> success

	}

	size_t lCnt = (*it).second.size();
	
	(*it).second.push_back(lMCode);
	return lCnt+1 == (*it).second.size();
}

BOOL CPrjMap::GetMatchMapName(DWORD lONr)
{
iterator it = find (DEX_GetObjectProject(lONr));

	if (it == end())
		return FALSE;

	return (*it).second.GetMatchMapName();
}

////////// KK001221 /////////////////////////////////////////////////////////////////
bool CPrjMap::InsertObject (const char *pName)
{

	HPROJECT hPr = DEX_GetDataSourceHandleEx(pName);

	iterator it =  end();

	it = find(hPr);

	if (it != end()) {
	// nicht erstes Objekt dieser DQ
	
	} else {
	// erstes Objekt dieser DQ
	pair<iterator, bool> p = insert (value_type(hPr, CCardsFromProject(hPr)));

		it = p.first;
		// p.second ==> success
	}

	size_t lCnt = (*it).second.size();
	
	(*it).second.push_back(pName);
	return lCnt+1 == (*it).second.size();
}
//------------------------------------------------------------------------------
// KK010105
bool CKartenCtrl::MapUnique(int i, const char * pName ) {


	CString S;

	for( int j = 0; j < i; j++ ) {

		S = m_strMapDirs[j];

		if( '\\' != S.Right( 1 ) && '/' != S.Right( 1 ) )
			S += '\\';

		if ( strcmp(pName,(LPCTSTR)S) == 0)
			return false;
	}

	return true;
}

//------------------------------------------------------------------------------
// KK010105
void CKartenCtrl::OnDQClose( ) {

	CString	myIniSection, myIniEntry, iniKey;
	VERIFY( myIniSection.LoadString( IDS_MYINISECTION ) );
	VERIFY( myIniEntry.LoadString( IDS_MAPDIRENTRY ) );

	CPrjMapInputIter iter (&m_strKVZ); 
	HPROJECT hRef = 0; 
	int i = 0;
	int Count = m_strKVZ.Count();

	while ( !iter.EndMarker()) {
		m_hPr = iter.HProject();
		if ( hRef != m_hPr) {
			hRef = m_hPr;
			i = 0;
			ClearIniSection(m_hPr, myIniSection );
		}

		iniKey.Format( "%s%d", myIniEntry, i + 1 );
		WriteProfileString( m_hPr,myIniSection, iniKey, *iter );
		i++;
		++iter;
	}


}

//-----------------------------------------------------------------------------

bool CKartenCtrl::FindMapList( long *phRef, const char *pName) {

	CPrjMapInputIter iter (&m_strKVZ); 
	int Count = m_strKVZ.Count();
	long i = 0;
	bool iFlag = false;
	while ( !iter.EndMarker()) {
		HPROJECT hPr = iter.HProject();
		if ( strcmp(*iter,pName) == 0 ) {
			*(phRef+i+1) = (long)hPr;
			i++;
			iFlag = true;
		}
		++iter;
	}
	if (iFlag)
		*phRef = i;

	return iFlag;

}

//-----------------------------------------------------------------------------

void CKartenCtrl::OnProjectClose( ) {

// KK010105
/*---------------
	CString	myIniSection, myIniEntry, iniKey;
	VERIFY( myIniSection.LoadString( IDS_MYINISECTION ) );
	VERIFY( myIniEntry.LoadString( IDS_MAPDIRENTRY ) );

	ClearIniSection( myIniSection );
	for( int i = 0; i < m_strMapDirs.GetSize(); i++ ) {
		iniKey.Format( "%s%d", myIniEntry, i + 1 );
		WriteProfileString( myIniSection, iniKey, m_strMapDirs[i] );
	}
//	if( 0.0 != m_mysticFactor && 0.0 != m_scaleX ) {
//		myIniEntry.Format("%lf",m_mysticFactor / m_scaleX);
//		WriteProfileString( myIniSection, _T("MysticFactor"), myIniEntry );
//	}
--------------------------------------*/
	CPolyGISPicture::ReleaseCache();		// alle Bilder freigeben
	OnDQClose();
	CTriasVMD::OnProjectClose();
}

BOOL CKartenCtrl::OnViewOpen(LPCTSTR lpszView) 
{
	CTriasVMD::OnViewOpen(lpszView);

// KK010111
ULONG lCount = DEX_GetOpenConnectionCount(QDCAllOpen);

	if (lCount != m_strDQ.Count()) {
	// strDQ + strKVZ aktualisieren !!
		SetDQ();
		ModKVZ();
		SetKVZCodes();
	}
	m_hPr = DEX_GetDataSourceHandle();

CString	S, S1;
long	l;

	GetMCodeValue( m_strCurrView, PalMCode(m_hPr), S );
//	GetMCodeValue( m_strCurrView, m_lPalMCode, S );
	::AfxExtractSubString( m_strViewPalette, S, 0, '@' );
	if( m_strViewPalette.IsEmpty() || m_strViewPalette == g_szEmpty )
		m_strViewPalette.LoadString(IDS_DEFAULTPALETTE);
	::AfxExtractSubString( S1, S, 1, '@' );
	if( S1.IsEmpty() > 0 ) {
		m_nTranspChannel = 0;
	} else {
		::LAfxExtractSubLong( l, S1, 0, ';' ); m_nTranspChannel = l;
	}

	m_bPalRealized = FALSE;
	return TRUE;
}

void CKartenCtrl::OnViewClose() 
{
//	m_listOfSights.SetAt( m_strCurrView, m_bMapsVisible ? (void*) &m_bMapsVisible : NULL );

//	if( m_bViewDrawn )
//	{
//		CString	strOldViewPalette;
//		GetMCodeValue( m_strCurrView, m_lPalMCode, strOldViewPalette );
//		if( strOldViewPalette != m_strViewPalette || m_strViewPalette.IsEmpty() )
//		{
//			if( m_strViewPalette.IsEmpty() )
//				m_strViewPalette = g_szEmpty;
//			SetMCodeValue( m_strCurrView, m_lPalMCode, m_strViewPalette, m_strViewPalette.GetLength() );
//		SetMCodeDescription( m_lPalMCode, IDS_VIEWMCODESHORT, IDS_VIEWMCODELONG, MPViewFeature | MPSystemFeatures );
//		}
//	}

	CPolyGISPicture::ReleaseCache();		// alle Bilder freigeben
	m_strViewPalette.Empty();
	CTriasVMD::OnViewClose( );
}

/////////////////////////////////////////////////////////////////////////////
// Palettenverwaltung

BOOL CKartenCtrl::OnChangePalette(CDC *pDC, HPALETTE hPal) 
{
	return TRUE;		// Palettenbehandlung machen wir selbst :-)
}
