#include	"stdafx.h"

#include <vinfomfc.h>
#include "VismodImpl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////

#define	new	DEBUG_NEW

IMPLEMENT_DYNAMIC( CTriasVMD, COleControl )

BEGIN_MESSAGE_MAP(CTriasVMD,COleControl)
	//{{AFX_MSG_MAP(CTriasVMD)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static LPCTSTR g_szDEXMsg = TEXT( "TriasExtensionMessage" );
static LPCTSTR g_szDEXXMsg = TEXT( "TriasCPPExtensionMessage" );
static LPCTSTR g_szQNFYMsg = TEXT( "TriasRegisterNotification" );
static LPCTSTR g_szQNFYUNREGMsg = TEXT( "TriasUnRegisterNotification" );
static LPCTSTR g_szNOTIFYMsg = TEXT( "TriasNotification" );

extern "C" HWND __hWndM = NULL;
extern "C" UINT __DexReg = 0;
extern "C" UINT __DexUnReg = 0;
extern "C" UINT __DexCmd = 0;
extern "C" UINT __DexxCmd = 0;
extern "C" UINT __DexNotify = 0;

DEXEXTENSIONPROC g_pDexExtensionProc = NULL;
DEXEXTENSIONPROC2 g_pDexExtensionProc2 = NULL;
DEXEXTENSIONPROC g_pDexxExtensionProc = NULL;
DEXNOTIFICATIONPROC g_pDexNotificationProc = NULL;
DEXDISPATCHPROC g_pDexDispatchProc = NULL;

extern "C" bool g_bTRiASV2 = false;
extern "C" bool g_bTRiASV3 = false;

LRESULT PASCAL DexExtensionProc (WPARAM w, LPARAM l) {
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != g_pTE && NULL != g_pTE -> m_pIServiceProvider)
		return LRESULT(g_pTE -> m_pIServiceProvider -> DexExtensionProc (w, l));
#endif // _XTENSIONSITE_INTERFACE
	LRESULT	lResult;
	if (g_pDexExtensionProc) {
		lResult = (*g_pDexExtensionProc)(w, l);
	} else {
		_ASSERTE(::IsWindow(__hWndM));
		lResult = ::SendMessage (__hWndM, __DexCmd, w, l);
	}
	return lResult;
}

LRESULT PASCAL DexExtensionProc2 (HPROJECT hPr, WPARAM w, LPARAM l) {
#if defined(_XTENSIONSITE_INTERFACE)
	if (NULL != g_pTE && NULL != g_pTE -> m_pIServiceProvider)
		return LRESULT(g_pTE -> m_pIServiceProvider -> DexExtensionProc2 (hPr, w, l));
#endif // _XTENSIONSITE_INTERFACE

	LRESULT	lResult;
	_ASSERTE( NULL != g_pDexExtensionProc2 );
	if (g_pDexExtensionProc2) {
		lResult = (*g_pDexExtensionProc2)(hPr, w, l);
	} else {
		_ASSERTE(::IsWindow(__hWndM));
		lResult = ::SendMessage (__hWndM, __DexCmd, w, l);
	}
	return lResult;
}

BOOL CTRiASVMDModule::InitInstance() {
	BOOL bInit = COleControlModule::InitInstance();
	if( FALSE == bInit )
		return FALSE;
	EnableAutomation();
	AfxEnableControlContainer();

	__DexCmd = RegisterWindowMessage( g_szDEXMsg );
	__DexxCmd = RegisterWindowMessage( g_szDEXXMsg );
	__DexReg = RegisterWindowMessage( g_szQNFYMsg );
	__DexUnReg = RegisterWindowMessage( g_szQNFYUNREGMsg );
	__DexNotify = RegisterWindowMessage( g_szNOTIFYMsg );
	
	_ASSERTE( 0 != __DexCmd && 0 != __DexxCmd && 0 != __DexReg && 0 != __DexUnReg && 0 != __DexNotify );
	if( !__DexCmd || !__DexxCmd || !__DexReg || !__DexUnReg || !__DexNotify ) {
		return FALSE;
	} 
	HMODULE hTrias = GetModuleHandle (NULL);
	g_pDexExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, TEXT("DEXEXTENSIONPROC"));
	g_pDexExtensionProc2 = (DEXEXTENSIONPROC2)GetProcAddress (hTrias, TEXT("DEXEXTENSIONPROC2"));
	g_pDexxExtensionProc = (DEXEXTENSIONPROC)GetProcAddress (hTrias, TEXT("DEXXEXTENSIONPROC"));
	g_pDexNotificationProc = (DEXNOTIFICATIONPROC)GetProcAddress (hTrias, TEXT("DEXNOTIFICATIONPROCEX"));
	g_pDexDispatchProc = (DEXDISPATCHPROC)GetProcAddress (hTrias, TEXT("DEXDISPATCHPROC"));

	if( g_pDexExtensionProc && g_pDexxExtensionProc && g_pDexNotificationProc && g_pDexDispatchProc ) {
		g_bTRiASV2 = true;
	}
	if( g_pDexExtensionProc2 ) {
		g_bTRiASV3 = true;
	}

	GetWindowsDirectory( m_strTRiASIni.GetBufferSetLength( _MAX_PATH ), _MAX_PATH );
	m_strTRiASIni.ReleaseBuffer( -1 );

#ifdef WIN32
	m_strTRiASIni += TEXT( "\\trias20.ini" );
#else
	m_strTRiASIni += TEXT( "\\trias13.ini" );
#endif

	return TRUE;
}

int CTRiASVMDModule::ExitInstance() {
	return COleControlModule::ExitInstance();
}

CTriasVMD::CTriasVMD( )
	: m_bProjIsOpen(FALSE)
	, m_bViewIsOpen(FALSE)
	, m_bPalIsRealized(FALSE)
	, m_bAdminMode(FALSE)
	, m_bReadOnly(FALSE)
	, m_strCurrProj("")
	, m_nIdentBase(16)
	, m_nMCodeBase(10)
	, m_strCurrView("")
	, m_activeZoom(1.0)
	, m_activeScaling(1.0)
{
	// To keep the application running as long as an OLE automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();
	m_bProjIsOpen = FALSE;
	m_bViewIsOpen = FALSE;
	m_bPalIsRealized = FALSE;
//KK010105
	m_hPr = 0;

	DeleteContents();
}

CTriasVMD::~CTriasVMD( ) {
	// To terminate the application when all objects created with
	// 	with OLE automation, the destructor calls AfxOleUnlockApp.
	AfxOleUnlockApp();
	m_CWnd.Detach();
}

void	CTriasVMD::DeleteContents( ) {
	m_strCurrProj.Empty();
//	m_strCurrProjIni.Empty();
	m_strCurrView.Empty();
	m_nIdentBase = 10;
	m_nMCodeBase = 10;
//	m_lUniqueIdent = -1;

	m_bReadOnly = TRUE;
	m_bAdminMode = FALSE;
}

/////////////////////////////////////////////////////////////////////
// 

#define	LEAVEVOID	{ return; }
#define	LEAVE( status )	{ return (status); }

STDMETHODIMP_(void) CTriasVMD :: OnProjectChange ( HWND hWndM, PROJECTCHANGE rgPC, char * pszProjName ) {
	SetHandle( hWndM );
	COleVariant	v;
	GetRegistryValue( _T("ManageWindow"), v );

	if( PROJECTCHANGE_OPENED == rgPC ) {
		if( m_bProjIsOpen )
			LEAVEVOID;
		if( m_bViewIsOpen )
			OnViewChange( hWndM, VIEWCHANGE_DELETED, NULL );
		if( VT_I4 == v.vt && 0x01 == (DWORD) v.lVal )
			LoadWindowState( hWndM );
		m_bProjIsOpen = OnProjectOpen( pszProjName );
	} else if( PROJECTCHANGE_CLOSED == rgPC ) {
		if( m_bViewIsOpen )
			OnViewChange( hWndM, VIEWCHANGE_DELETED, NULL );
		if( VT_I4 == v.vt && 0x01 == (DWORD) v.lVal )
			SaveWindowState( hWndM );
		OnProjectClose( );
		m_bProjIsOpen = FALSE;
	}
	LEAVEVOID;
}

STDMETHODIMP_(void) CTriasVMD :: OnViewChange ( HWND hWndM, VIEWCHANGE rgVC, char * pszView ) {
	SetHandle( hWndM );
	if( VIEWCHANGE_SELECTED == rgVC ) {
		if( NULL == pszView )
			LEAVEVOID;

		if( !m_bProjIsOpen ) {
			CString	S;
// KK001116
			HPROJECT hPr = DEX_GetDataSourceHandle();
			DEX_GetDataSourceName( hPr, S.GetBufferSetLength( _MAX_PATH ) );

//			DEX_GetActiveProject( S.GetBufferSetLength( _MAX_PATH ) );
			S.ReleaseBuffer( -1 );
			OnProjectChange( hWndM, PROJECTCHANGE_OPENED, (char*) (LPCTSTR) S );
		}

		if( m_bViewIsOpen )
			OnViewChange( hWndM, VIEWCHANGE_DELETED, NULL );
		OnViewOpen( pszView );
		m_bViewIsOpen = TRUE;
	} else if( VIEWCHANGE_DELETED == rgVC ) {
		OnViewClose( );
		m_bViewIsOpen = FALSE;
	}
	LEAVEVOID;
}

STDMETHODIMP_(void) CTriasVMD :: OnPaletteChange ( HWND hWndM, HPALETTE hPal ) {
	if( !m_bProjIsOpen || !m_bViewIsOpen )
		LEAVEVOID;

	SetHandle( hWndM );
	CWnd *pWnd = CWnd::FromHandlePermanent( hWndM );
	CDC *pDC;
	if( NULL != pWnd && ( NULL != ( pDC = pWnd->GetWindowDC() ) ) ) {
		OnChangePalette( pDC, hPal );
		pWnd->ReleaseDC( pDC );
	}
	LEAVEVOID;
}

STDMETHODIMP CTriasVMD :: SymbolizeObject (
		HWND hWndM, long & rlONr, short & iOType,
		char * pszBuffer, short iLen )
{
	if( !m_bProjIsOpen )
		LEAVE( ResultFromScode(VISMODULE_E_GENERALERROR) );
	SetHandle( hWndM );
	LEAVE( ResultFromScode( E_NOTIMPL ) );
}

STDMETHODIMP CTriasVMD :: DrawObject (
		HWND hWndM, HDC hDC, HDC hTargetDC, 
		long lONr, short & fDrawFlags,			// DF_... xtension.h
		VisInfo * pVI, char * pszVisString )
{
	if( fDrawFlags & DF_Blinking )				// Trias blinken lassen
		LEAVE( ResultFromScode(VISMODULE_E_GENERALERROR) );

	if( !m_bProjIsOpen )
		LEAVE( ResultFromScode(VISMODULE_E_GENERALERROR) );

	MEM_STARTCHECK( GetRuntimeClass()->m_lpszClassName, "OnDrawObject" );

	if( FALSE == m_bViewIsOpen ) {
		CString	S;
		DEX_GetActiveSight( S.GetBufferSetLength( 256 ) );
		S.ReleaseBuffer( -1 );
		OnViewChange( hWndM, VIEWCHANGE_SELECTED, (char*) (LPCTSTR) S );
	}

	SetHandle( hWndM );
	// SetUp the Draw Context

	m_dcDraw.Attach( hDC ); 
	m_dcTarget.Attach( hTargetDC );

	m_dcDraw.m_bPrinting = ( DT_RASPRINTER == m_dcDraw.GetDeviceCaps( TECHNOLOGY ) ) ? TRUE : FALSE;
	m_dcTarget.m_bPrinting = ( DT_RASPRINTER == m_dcTarget.GetDeviceCaps( TECHNOLOGY ) ) ? TRUE : FALSE;

	DEX_GetActiveScaling( m_activeScaling );
	DEX_GetActiveZoom( m_activeZoom );

	HRESULT	hResult = ResultFromScode( VISMODULE_S_OBJECTISDRAWN );

	try {
		if( FALSE == OnDrawObject( &m_dcDraw, &m_dcTarget, lONr, pVI, pszVisString, fDrawFlags ) )
			if( !(fDrawFlags & DF_ShowHidden) )
				hResult = ResultFromScode(VISMODULE_E_GENERALERROR);
	} catch( ... ) {
		hResult = ResultFromScode(VISMODULE_E_GENERALERROR);
	}

	m_dcDraw.Detach( );
	m_dcTarget.Detach( );

	MEM_CHECKPOINT( GetRuntimeClass()->m_lpszClassName, "OnDrawObject" );

	LEAVE( hResult );
}

STDMETHODIMP CTriasVMD :: QueryParameters (
			HWND hWndM, long lONr,
			VisInfo * pVI, char * pszVisStr, 
			char * pBuffer, short iLen,
			short * piOTypes)  // xtension.h OGPunkt ...
{
	if( !m_bProjIsOpen )
		LEAVE( ResultFromScode(VISMODULE_E_GENERALERROR) );
	CWnd *pWnd = CWnd::FromHandle( hWndM );
	if( OnQueryParameters( pWnd, lONr, pVI, pszVisStr, pBuffer, iLen, piOTypes) )
		LEAVE( ResultFromScode(NOERROR) );
	LEAVE( ResultFromScode(VISMODULE_E_GENERALERROR) );
}

//////////////////////////////////////////////////////////////////////
// 

#include <io.h>		// _access

BOOL	CTriasVMD::OnProjectOpen( LPCTSTR pszNewProject ) {
	DeleteContents( );
	CString S = pszNewProject;

	if( S.GetLength() < 4 )
		return FALSE;		// es sollte schon mehr als nur die Extension da sein

	m_strCurrProj = pszNewProject;

//	::AfxExtractSubString( m_strCurrProjIni, pszNewProject, 0, '.' );
//	m_strCurrProjIni += ".ini";

	m_nIdentBase = (short) DEX_GetIdBase();
	m_nMCodeBase = (short) DEX_GetMkBase();
//	m_lUniqueIdent = DEX_GetUniqueIdentMCode();

	m_bReadOnly = DEX_GetROMode() || ( -1 == _access( pszNewProject, 2 ) );
	m_bAdminMode = DEX_QueryMode() & QMSysAdmin;

	return TRUE;
}

void	CTriasVMD::OnProjectClose( ) {
	DeleteContents( );
}

BOOL	CTriasVMD::OnViewOpen( LPCTSTR pszView ) {
	m_strCurrView = pszView;
	return TRUE;
}

void	CTriasVMD::OnViewClose( ) {
	m_strCurrView.Empty( );
}

ULONG CTriasVMD::GetUniqueIdent( void ) {
	return DEX_GetUniqueICode( );
}
ULONG CTriasVMD::GetUniqueMCode( void ) {
	return DEX_GetUniqueMCode( );
}

void CTriasVMD::SetHandle( HWND hWnd ) {
	__hWndM = hWnd;
	if( NULL == CWnd::FromHandlePermanent( hWnd ) && NULL == m_CWnd.GetSafeHwnd() )
		m_CWnd.Attach( hWnd );
/*
#ifdef _WIN32		// #ifdef _AFXDLL
		if( NULL == CWnd::FromHandlePermanent(hWnd) )
			m_CWnd.Attach( __hWndM = hWnd );
		ASSERT( &m_CWnd == CWnd::FromHandlePermanent(hWnd) );
#else
		m_CWnd.Detach( );
		m_CWnd.Attach( __hWndM = hWnd );
#endif
*/
}

//////////////////////////////////////////////////////////////////////
// Zugriff auf Merkmalscodes

#define	MAX_MCODELEN	2048

BOOL CTriasVMD::GetUniqueIdentMCode( ULONG& rlMCode ) {
	rlMCode = DEX_GetUniqueIdentMCode();
	return rlMCode ? TRUE : FALSE;
}

BOOL CTriasVMD::GetUniqueIdentValue( ULONG lObjNr, CString& rValue ) {
	TARGETMERKMAL	M;
	INITSTRUCT( M, M );
	HPROJECT	hPrj = DEX_GetObjectProject(lObjNr);
	ULONG		ulIdent;
	if( hPrj > 0 ) {
		ulIdent = DEX_GetUniqueIdentMCodeEx(hPrj);
	} else {
		ulIdent = DEX_GetUniqueIdentMCode();
	}
	return GetMCodeValue( lObjNr, ulIdent, rValue, TT_Objekt );
}

BOOL CTriasVMD::GetMCodeValue( ULONG lObjNr, ULONG lIdent, CString& rValue, short tType ) {
	ASSERT( TT_Objekt == tType || TT_Identifikator == tType );

	TARGETMERKMAL	M;
	INITSTRUCT( M, M );
	
	M.lTarget = lObjNr;
	M.lMCode = lIdent;
	M.imaxLen = MAX_MCODELEN + 1;
	M.pMText = rValue.GetBufferSetLength( MAX_MCODELEN );
	M.iTTyp = tType;
	DEX_GetTextMerkmal( M );
	rValue.ReleaseBuffer( -1 );
	return rValue.IsEmpty( ) ? FALSE : TRUE;
}                    

BOOL CTriasVMD::GetMCodeValue( LPCTSTR pszViewName, ULONG MCode, CString& rValue ) {
	TARGETMERKMAL	M;
	INITSTRUCT( M, M );
	
	M.lTarget = (LPARAM) pszViewName;
	M.lMCode = MCode;
	M.imaxLen = MAX_MCODELEN + 1;
	M.pMText = rValue.GetBufferSetLength( MAX_MCODELEN );
	M.iTTyp = TT_Sicht;
	DEX_GetTextMerkmal( M );
	rValue.ReleaseBuffer( -1 );
	return rValue.IsEmpty( ) ? FALSE : TRUE;
}

BOOL CTriasVMD::SetMCodeValue( ULONG lObjNr, ULONG lIdent, LPCTSTR pszValue, short len, short tType  ) {
	ASSERT( TT_Objekt == tType || TT_Identifikator == tType );

	TARGETMERKMAL	M;
	INITSTRUCT( M, M );
	
	M.lTarget       = lObjNr;
	M.lMCode        = lIdent;
	M.imaxLen       = -1 == len ? strlen( pszValue ) : len;
	M.pMText        = (char*) pszValue;
	M.iTTyp         = tType;
	return DEX_ModTextMerkmal( M ) == EC_OKAY ? TRUE : FALSE;
}

BOOL CTriasVMD::SetMCodeValue( LPCTSTR pszViewName, ULONG lIdent, LPCTSTR pszValue, short len ) {
	TARGETMERKMAL	M;
	INITSTRUCT( M, M );
	
	M.lTarget       = (LPARAM) pszViewName;
	M.lMCode        = lIdent;
	M.imaxLen       = -1 == len ? strlen( pszValue ) : len;
	M.pMText        = (char*) pszValue;
	M.iTTyp         = TT_Sicht;
	return DEX_ModTextMerkmal( M ) == EC_OKAY ? TRUE : FALSE;
}

BOOL CTriasVMD::SetMCodeDescription( ULONG MCode, LPCTSTR pszShort, LPCTSTR pszLong, int iMCodeType ) {
#ifdef	_DEBUG
	{
		int	typ = iMCodeType & ~( MPSystemFeatures | MPAllFeatures );
		ASSERT( MPObjectFeature == typ 
			|| MPViewFeature == typ
			|| MPIdentFeature == typ
			|| MPDoubleFeature == typ
			|| MPIntegerFeature == typ
			|| MPUnknownFeature == typ );
	}
#endif	// _DEBUG

	PBDMERKMAL	M;
	INITSTRUCT( M, M );

	M.pbdTyp        = 'm';
	M.pbdCode       = MCode;
	M.pbdReserved   = FALSE;
	M.pbdKText      = (char*) pszShort;
	M.pbdLText      = (char*) pszLong;
	M.pbdKTextLen   = strlen( pszShort );
	M.pbdLTextLen   = strlen( pszLong );
	M.ipbdMTyp      = iMCodeType;
	M.ipbdMLen      = 256;
	return DEX_ModPBDData( M );
}

BOOL CTriasVMD::SetMCodeDescription( ULONG MCode, UINT nID1, UINT nID2, int iMCodeType ) {
	CString	S1, S2;
	VERIFY( S1.LoadString( nID1 ) );
	VERIFY( S2.LoadString( nID2 ) );
	return SetMCodeDescription( MCode, S1, S2, iMCodeType );
}

BOOL CTriasVMD::GetMCodeDescription( ULONG MCode, CString& rShort, CString& rLong ) {
	PBDMERKMAL	M;
	INITSTRUCT( M, M );

	M.pbdTyp        = 'm';
	M.pbdCode       = MCode;
	M.pbdReserved   = FALSE;
	M.pbdKText      = rShort.GetBufferSetLength( MAX_MCODELEN );
	M.pbdLText      = rLong.GetBufferSetLength( MAX_MCODELEN );
	M.pbdKTextLen   = MAX_MCODELEN;
	M.pbdLTextLen   = MAX_MCODELEN;
	M.ipbdMTyp      = 'A';
	M.ipbdMLen      = 256;
	BOOL ret = DEX_GetPBDData( M ) == EC_OKAY ? TRUE : FALSE;
	rShort.ReleaseBuffer( -1 );
	rLong.ReleaseBuffer( -1 );
	return ret;
}

//////////////////////////////////////////////////////////////////////////////
// Zugriff auf GeoDB

#include	"hdrentrx.hxx"		// Definition von HDRKEYLENGTH

BOOL	CTriasVMD::GetGeoDBEntry( HPROJECT hPr,LPCTSTR pszKey, CString& rValue ) {
	GEODBHDRENTRY	H;
	INITSTRUCT( H, H );

	memset( H.hdrKey, ' ', HDRKEYLENGTH );
	memcpy( H.hdrKey, pszKey, __min( strlen( pszKey ), HDRKEYLENGTH ) );
	H.lphdrText = rValue.GetBufferSetLength( HDRENTRYTEXTLEN + 1 );	// Buffer bereitstellen
	H.hdrTextLen = HDRENTRYTEXTLEN;
	memset( H.lphdrText, '\0', HDRENTRYTEXTLEN + 1 );
	DEX_ReadGeoDBHdrEntryEx(hPr, H );
	rValue.ReleaseBuffer( -1 );					// Buffer anpassen
	return !rValue.IsEmpty( );					// wenn Eintrag da, dann TRUE
}

BOOL	CTriasVMD::GetGeoDBEntry( HPROJECT hPr,UINT iResrcID, CString& rValue ) {
	VERIFY( rValue.LoadString( iResrcID ) );
	return GetGeoDBEntry(hPr, rValue, rValue );
}

BOOL	CTriasVMD::SetGeoDBEntry(HPROJECT hPr, const char *Key, const char *Value ) {
	CString	HdrText( ' ', HDRENTRYTEXTLEN );

	strncpy( (char*) (LPCTSTR) HdrText, Value, HDRENTRYTEXTLEN );
	HdrText.ReleaseBuffer( -1 );

	GEODBHDRENTRY	H;
	INITSTRUCT( H, H );

	memset( H.hdrKey, ' ', HDRKEYLENGTH );
	memcpy( H.hdrKey, Key, __min( strlen( Key), HDRKEYLENGTH ) );
	H.lphdrText = (char*) (LPCTSTR) HdrText;
	H.hdrTextLen = HdrText.GetLength( );

	return DEX_WriteGeoDBHdrEntryEx( hPr,H ) == EC_OKAY ? TRUE : FALSE;
}

BOOL	CTriasVMD::SetGeoDBEntry( HPROJECT hPr,UINT nResrcID, LPCTSTR pszValue ) {
	CString	S;
	VERIFY( S.LoadString( nResrcID ) );
	return SetGeoDBEntry(hPr, S, pszValue );
}

///////////////////////////////////////////////////////////////////////////
// Zugriff auf projektspezifische INI-Datei

UINT CTriasVMD::GetProfileInt(HPROJECT hPr,LPCSTR lpszSection, LPCSTR lpszEntry, int nDefault ) {
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
	ASSERT(hPr != 0);

	CString	S;
// KK001116
//	HPROJECT hPr = DEX_GetDataSourceHandle();
	DEX_GetDataSourceName( hPr, S.GetBufferSetLength( _MAX_PATH ) );

//	DEX_GetActiveProject( S.GetBufferSetLength( _MAX_PATH ) );

	S.ReleaseBuffer( -1 );
	CPath	pathOfIni( S );
	pathOfIni.Suffix( ".ini" );

	return ::GetPrivateProfileInt(lpszSection, lpszEntry, nDefault, pathOfIni.Path() );
}

BOOL CTriasVMD::WriteProfileInt(HPROJECT hPr, LPCSTR lpszSection, LPCSTR lpszEntry, int nValue ) {
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);
	ASSERT(hPr != 0);

	CString	S;
// KK001116
//	HPROJECT hPr = DEX_GetDataSourceHandle();
	DEX_GetDataSourceName( hPr, S.GetBufferSetLength( _MAX_PATH ) );

//	DEX_GetActiveProject( S.GetBufferSetLength( _MAX_PATH ) );

	S.ReleaseBuffer( -1 );
	CPath	pathOfIni( S );
	pathOfIni.Suffix( ".ini" );

	S.Format( "%d", nValue);
	return ::WritePrivateProfileString(lpszSection, lpszEntry, S, pathOfIni.Path() );
}

static char	szDefault[] = "";

CString CTriasVMD::GetProfileString(HPROJECT hPr, LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszDefault /*= NULL */) {
	ASSERT(lpszSection != NULL);
	ASSERT(hPr != 0);

// KK010105
	m_hPr = hPr;

	CString	S;
// KK001116
//	HPROJECT hPr = DEX_GetDataSourceHandle();
	DEX_GetDataSourceName( hPr, S.GetBufferSetLength( _MAX_PATH ) );

//	DEX_GetActiveProject( S.GetBufferSetLength( _MAX_PATH ) );

	S.ReleaseBuffer( -1 );
	CPath	pathOfIni( S );
	pathOfIni.Suffix( ".ini" );
	if (lpszDefault == NULL)
		lpszDefault = szDefault;       // don't pass in NULL
	::GetPrivateProfileString(lpszSection, lpszEntry, lpszDefault, S.GetBufferSetLength( _MAX_PATH ), _MAX_PATH - 2, pathOfIni.Path() );
	S.ReleaseBuffer(-1);
	return S;
}

BOOL CTriasVMD::WriteProfileString(HPROJECT hPr, LPCSTR lpszSection, LPCSTR lpszEntry, LPCSTR lpszValue) {
	ASSERT(lpszSection != NULL);
	ASSERT(lpszEntry != NULL);

	CString	S;
// KK001116
//	HPROJECT hPr = DEX_GetDataSourceHandle();
	DEX_GetDataSourceName( hPr, S.GetBufferSetLength( _MAX_PATH ) );

//	DEX_GetActiveProject( S.GetBufferSetLength( _MAX_PATH ) );

	S.ReleaseBuffer( -1 );
	CPath	pathOfIni( S );
	pathOfIni.Suffix( ".ini" );
	return ::WritePrivateProfileString(lpszSection, lpszEntry, lpszValue, pathOfIni.Path() );
}

void CTriasVMD::ClearIniSection( HPROJECT hPr, LPCTSTR lpszSection ) {
	ASSERT(hPr != 0);
	CString	S;
// KK001116
//	HPROJECT hPr = DEX_GetDataSourceHandle();
	DEX_GetDataSourceName( hPr, S.GetBufferSetLength( _MAX_PATH ) );

//	DEX_GetActiveProject( S.GetBufferSetLength( _MAX_PATH ) );

	S.ReleaseBuffer( -1 );
	CPath	pathOfIni( S );
	pathOfIni.Suffix( ".ini" );
	::GetPrivateProfileString(lpszSection, NULL, szDefault, S.GetBufferSetLength( _MAX_PATH ), _MAX_PATH - 2, pathOfIni.Path() );
	S.ReleaseBuffer(-1);
	LPCTSTR pszS, pszE;
	pszS = pszE = S;
	if( !pszS || !*pszS )
		return;
	for(;;) {
		for(;*pszE;pszE++)
			;
		WriteProfileString( hPr,lpszSection, pszS, NULL );
		if( !*(++pszE) )
			break;
		pszS = pszE;
	}
}

static TCHAR *szSection = _T("Vismod");
static TCHAR *szKey = _T("WndState");

void CTriasVMD::SaveWindowState( HWND hWnd ) {
	ASSERT(m_hPr != 0);
    WINDOWPLACEMENT wp;
    CString szValue ;
    wp.length = sizeof( WINDOWPLACEMENT );
    ::GetWindowPlacement( hWnd, &wp );
    szValue.Format( _T("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d"),
        wp.showCmd, wp.flags,
		wp.ptMinPosition.x, wp.ptMinPosition.y,
        wp.ptMaxPosition.x, wp.ptMaxPosition.y,
        wp.rcNormalPosition.left, wp.rcNormalPosition.top,
        wp.rcNormalPosition.right, wp.rcNormalPosition.bottom
		);
    WriteProfileString( m_hPr,szSection, szKey, szValue );
}

void CTriasVMD::LoadWindowState( HWND hWnd ) {
	ASSERT(m_hPr != 0);
	CString	strValue;

//	strValue = GetProfileString(szSection, szKey, _T("") ) ;
// KK010105
	strValue = GetProfileString(m_hPr,szSection, szKey, _T("") ) ;
	if( strValue.IsEmpty() )
		return;

	long	l;
    WINDOWPLACEMENT wp;
    wp.length = sizeof( WINDOWPLACEMENT );

	LAfxExtractSubLong( l = 0, strValue, 0, ',' );
	wp.showCmd = (int) l;
	LAfxExtractSubLong( l = 0, strValue, 1, ',' );
	wp.flags = (int) l;
	LAfxExtractSubLong( l = 0, strValue, 2, ',' );
	wp.ptMinPosition.x = (int) l;
	LAfxExtractSubLong( l = 0, strValue, 3, ',' );
	wp.ptMinPosition.y = (int) l;
	LAfxExtractSubLong( l = 0, strValue, 4, ',' );
	wp.ptMaxPosition.x = 0;	// (int) l;
	LAfxExtractSubLong( l = 0, strValue, 5, ',' );
	wp.ptMaxPosition.y = 0;	// (int) l;
	LAfxExtractSubLong( l = 0, strValue, 6, ',' );
	wp.rcNormalPosition.left = (int) l;
	LAfxExtractSubLong( l = 0, strValue, 7, ',' );
	wp.rcNormalPosition.top = (int) l;
	LAfxExtractSubLong( l = 0, strValue, 8, ',' );
	wp.rcNormalPosition.right = (int) l;
	LAfxExtractSubLong( l = 0, strValue, 9, ',' );
	wp.rcNormalPosition.bottom = (int) l;

	if(wp.showCmd == SW_SHOWMINIMIZED)
		wp.showCmd = SW_SHOWNORMAL ;
	::SetWindowPlacement( hWnd, &wp );
}
