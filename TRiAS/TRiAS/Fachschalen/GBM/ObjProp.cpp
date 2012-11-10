// GBM-Objekteigenschaften
// ObjProp.cpp

#include "StdAfx.h"
#include "ObjProp.h"

#include "XtsnGUID.h"
#include "Resource.h"

extern CSetNF_PG2H* g_pNF_PG2H;
extern CSetNF_PG2D* g_pNF_PG2D;
extern CSetNF_PG1GB* g_pNF_PG1GB;

COPAngeschlGS::COPAngeschlGS()
{
	m_ulCount    = 0L;
	m_ulCumu     = 0L;
	m_ulRefCnt   = 0L;

	m_lDachIdent = 0L;
	m_lHofIdent  = 0L;
	m_lGebIdent  = 0L;
	m_lGS_Ident  = 0L;
}

COPAngeschlGS::~COPAngeschlGS()
{
}

// *** IUnknown methods ***
STDMETHODIMP COPAngeschlGS::QueryInterface( REFIID riid, void** ppv )
{
	*ppv = NULL;

	if ( IID_IUnknown == riid )
		*ppv = this;

	if ( IID_IObjectProperty2 == riid )
		*ppv = this;

    if ( NULL == *ppv )
        return ResultFromScode( E_NOINTERFACE );

    ((LPUNKNOWN)*ppv) -> AddRef();

	return NOERROR;
}

ULONG COPAngeschlGS::AddRef( void )
{
	return ++m_ulRefCnt;
}

ULONG COPAngeschlGS::Release( void )
{
	if ( 0 != --m_ulRefCnt )
		return m_ulRefCnt;

	delete this;
	return 0;
}

// *** IObjectProperty specific functions ***
STDMETHODIMP COPAngeschlGS::GetPropInfo( LPSTR pBuffer, WORD wLen,
										DWORD *pdwFlags/*=NULL*/ )
{
	CString		info;

	info.LoadString( IDS_OPNAME01 );
//	info = "Fläche angeschlossen";
	if ( info.GetLength() >= wLen )
		info = info.Left( wLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );
	if ( NULL != pdwFlags )
		*pdwFlags = PROPCAPS_OBJPROPTYPE_BOOL;	// Objekteigenschaft liefert Bool

	return NOERROR;
}

STDMETHODIMP COPAngeschlGS::Reset( void )
{
	m_ulCount  = 0L;
	m_ulCumu   = 0L;
	return NOERROR;
}

ULONG COPAngeschlGS::Count( void )
{
	return m_ulCount;
}

STDMETHODIMP COPAngeschlGS::HelpInfo( LPSTR pBuffer, ULONG ulLen, 
				LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/)
{
	CString		info;

	info.LoadString( IDS_OPINFO01 );
//	info = "Liefert 1, wenn ein GBM-Objekt (Grundstück, angeschlossen ist. ";
//	info += "Sonst (auch für andere Objekte) stets FALSE (0).";
	if ( info.GetLength() >= ulLen )
		info = info.Left( ulLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

STDMETHODIMP COPAngeschlGS::Cumulation( LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/)
{
	CxString	info;

	info.AppendF( m_ulCumu, -1 );
	if ( info.GetLength() >= ulLen )
	{
		info = "***";
		if ( info.GetLength() >= ulLen )
			info = info.Left( ulLen - 1 );
	}

	if ( NULL != pulWritten )
		*pulWritten = info.GetLength();

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

STDMETHODIMP COPAngeschlGS::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/)
{
	CxString	info;

	++m_ulCount;

	if ( IstAngeschlossen( lONr ))
	{
		info = "1";
		++m_ulCumu;
	}
	else
		info = "0";

	if ( info.GetLength() > ulLen )
	{
		info = "***";
		if ( info.GetLength() > ulLen )
			info = info.Left( ulLen );
	}

	if ( NULL != pulWritten )
		*pulWritten = info.GetLength();

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

// *** IObjectProperty2 specific functions ***
STDMETHODIMP COPAngeschlGS::Set( LONG lONr, LPCSTR pcBuffer )
{
	if ( !AfxIsValidString( pcBuffer ))
		return E_POINTER;

	CString		text( pcBuffer );

	if (( text != "0" ) && ( text != "1" ))
		return E_UNEXPECTED;

	SetONr( lONr, ( text == "1" ));

	//	WriteBack-Cache schreiben, sollte gelegentlich in die Datenbank
	//	zurückgeschrieben werden! (Spätestens beim Schließen)
	if ( lONr == -1L )	return NOERROR;
	if ( lONr == 0L )	return NOERROR;
	m_mapModi.SetAt((void*)lONr, (WORD)( text == "1" ));

	return NOERROR;
}

// Implementation der Funktionalität
BOOL COPAngeschlGS::AddONr( long onr )
{
	return SetONr( onr, TRUE );
}

BOOL COPAngeschlGS::RemoveONr( long onr )
{
	return SetONr( onr, FALSE );
}

BOOL COPAngeschlGS::SetONr( long onr, BOOL flag )
{
	if ( onr == -1L )	return FALSE;
	if ( onr == 0L )	return FALSE;
	m_mapONr.SetAt((void*)onr, (WORD)flag );
	return TRUE;
}

BOOL COPAngeschlGS::IstAngeschlossen( long onr )
{
	void	*ptr;
	WORD	result = 0;

	if ( onr == -1L )	return FALSE;
	if ( onr == 0L )	return FALSE;

	// Ist es schon registriert (in der laufenden Sitzung schon einmal nachgefragt
	// oder aktuell editiert worden).
	if ( m_mapONr.Lookup((void*)onr, result ))
		return ( result == 1 );

	if ( DEX_GetObjectType( onr ) != OGFlaeche )	return FALSE;

	CString		ide = GetIdentNummer( onr );
	if ( ide.IsEmpty())		return FALSE;

	CxString	nummer, name = GetObjectName( onr );
	if ( name.IsEmpty())	return FALSE;

	long	cls_id = DEX_GetObjIdent( onr );

	if (( name.GetLength() > 1 ) && (( name.Left( 1 ) == "D" ) ||
		( name.Left( 1 ) == "V" )))
		name = name.Mid( 1 );

	nummer.Empty();
	nummer.AppendF( name.Long(), -1 );

	if ( cls_id == m_lDachIdent )
	{
		name = ide;		name += "D";	name += nummer;
		if ( m_mapName.Lookup( name, ptr ))
			result = LOWORD( ptr );
		else
			result = ( g_pNF_PG2D -> IstAngeschlossen( ide, nummer ) ? 1 : 0 );
		m_mapNameToONr.SetAt( name, (void*)onr );
	}
	else if ( cls_id == m_lHofIdent )
	{
		name = ide;		name += "V";	name += nummer;
		if ( m_mapName.Lookup( name, ptr ))
			result = LOWORD( ptr );
		else
			result = ( g_pNF_PG2H -> IstAngeschlossen( ide, nummer ) ? 1 : 0 );
		m_mapNameToONr.SetAt( name, (void*)onr );
	}
	else if ( cls_id == m_lGebIdent )
	{
		name = ide;		name += "G";	name += nummer;
		if ( m_mapName.Lookup( name, ptr ))
			result = LOWORD( ptr );
		else
			result = ( g_pNF_PG1GB -> IstAngeschlossen( ide, nummer ) ? 1 : 0 );
		m_mapNameToONr.SetAt( name, (void*)onr );
	}

	SetONr( onr, ( result == 1 ));
	return ( result == 1 );
}


BOOL COPAngeschlGS::IsObjectOf( UINT ids, long onr )
{
	BOOL	result = FALSE;
	CString	text;

	text.LoadString( ids );
	LONG	gs_id;

	if ( text.IsEmpty())	return result;

	gs_id = DEX_GetIdentFromClassName( (const char*)text );

	result = ( DEX_GetObjIdent( onr ) == gs_id );
	return result;
}

CString COPAngeschlGS::GetIdentNummer( long onr )
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

CString COPAngeschlGS::GetObjectName( long onr )
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

void COPAngeschlGS::InitData()
{
	CString	text;

	m_lDachIdent = 0L;
	m_lHofIdent  = 0L;
	m_lGebIdent  = 0L;
	m_lGS_Ident  = 0L;

	m_mapName.RemoveAll();
	m_mapONr.RemoveAll();
	m_mapNameToONr.RemoveAll();

	text.LoadString( IDS_DACH_CLASSNAME );
	if ( !text.IsEmpty())
		m_lDachIdent = DEX_GetIdentFromClassName((const char*)text );
	text.LoadString( IDS_HOF_CLASSNAME );
	if ( !text.IsEmpty())
		m_lHofIdent = DEX_GetIdentFromClassName((const char*)text );
	text.LoadString( IDS_GEB_CLASSNAME );
	if ( !text.IsEmpty())
		m_lGebIdent = DEX_GetIdentFromClassName((const char*)text );
	text.LoadString( IDS_GS_CLASSNAME );
	if ( !text.IsEmpty())
		m_lGS_Ident = DEX_GetIdentFromClassName((const char*)text );
}

BOOL COPAngeschlGS::AddName( const char* ide, const char* nr, char suff )
{	return SetName( ide, nr, suff, TRUE );
}

BOOL COPAngeschlGS::RemoveName( const char* ide, const char* nr, char suff )
{	return SetName( ide, nr, suff, FALSE );
}

BOOL COPAngeschlGS::SetName( const char* ide, const char* nr, char suff, BOOL flag )
{
	CxString	name;
	void		*wert;
	void		*onr = NULL;

	if ( !AfxIsValidString( ide ))	return FALSE;
	if ( !AfxIsValidString( nr ))	return FALSE;
	if (( suff != 'D' ) && ( suff != 'V' ))
		suff = 'G';

	name = ide;
	if ( nr[0] != suff )	name += suff;
	name += nr;

	wert = ( flag ? (void*)1 : (void*)0 );

	if ( m_mapNameToONr.Lookup( name, onr ))
		m_mapONr.SetAt( onr, ( flag ? 1 : 0 ));
	else
		m_mapName.SetAt( name, wert );
	return TRUE;
}


////
//	COPGedrucktGS

COPGedrucktGS::COPGedrucktGS()
{
	m_ulCount    = 0L;
	m_ulCumu     = 0L;
	m_ulRefCnt   = 0L;
}

COPGedrucktGS::~COPGedrucktGS()
{
}

// *** IUnknown methods ***
STDMETHODIMP COPGedrucktGS::QueryInterface( REFIID riid, void** ppv )
{
	*ppv = NULL;

	if ( IID_IUnknown == riid )
		*ppv = this;

	if ( IID_IObjectProperty == riid )
		*ppv = this;

    if ( NULL == *ppv )
        return ResultFromScode( E_NOINTERFACE );

    ((LPUNKNOWN)*ppv) -> AddRef();

	return NOERROR;
}

ULONG COPGedrucktGS::AddRef( void )
{
	return ++m_ulRefCnt;
}

ULONG COPGedrucktGS::Release( void )
{
	if ( 0 != --m_ulRefCnt )
		return m_ulRefCnt;

	delete this;
	return 0;
}

// *** IObjectProperty specific functions ***
STDMETHODIMP COPGedrucktGS::GetPropInfo( LPSTR pBuffer, WORD wLen,
										DWORD *pdwFlags/*=NULL*/ )
{
	CString		info;

//	info.LoadString( IDS_OPNAME02 );
	info.LoadString( m_uiInfo );
	if ( info.GetLength() >= wLen )
		info = info.Left( wLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );
	if ( NULL != pdwFlags )
		*pdwFlags = PROPCAPS_OBJPROPTYPE_BOOL;	// Objekteigenschaft liefert Bool

	return NOERROR;
}

STDMETHODIMP COPGedrucktGS::Reset( void )
{
	m_ulCount  = 0L;
	m_ulCumu   = 0L;
	return NOERROR;
}

ULONG COPGedrucktGS::Count( void )
{
	return m_ulCount;
}

STDMETHODIMP COPGedrucktGS::HelpInfo( LPSTR pBuffer, ULONG ulLen, 
				LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/)
{
	CString		info;

//	info.LoadString( IDS_OPINFO02 );
	info.LoadString( m_uiHelp );
	if ( info.GetLength() >= ulLen )
		info = info.Left( ulLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

STDMETHODIMP COPGedrucktGS::Cumulation( LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/)
{
	CxString	info;

	info.AppendF( m_ulCumu, -1 );
	if ( info.GetLength() >= ulLen )
	{
		info = "***";
		if ( info.GetLength() >= ulLen )
			info = info.Left( ulLen - 1 );
	}

	if ( NULL != pulWritten )
		*pulWritten = info.GetLength();

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

STDMETHODIMP COPGedrucktGS::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/)
{
	CxString	info;

	++m_ulCount;

	if ( IstGedruckt( lONr ))
	{
		info = "1";
		++m_ulCumu;
	}
	else
		info = "0";

	if ( info.GetLength() > ulLen )
	{
		info = "***";
		if ( info.GetLength() > ulLen )
			info = info.Left( ulLen );
	}

	if ( NULL != pulWritten )
		*pulWritten = info.GetLength();

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

// *** IObjectProperty2 specific functions ***
STDMETHODIMP COPGedrucktGS::Set( LONG lONr, LPCSTR pcBuffer )
{
	if ( !AfxIsValidString( pcBuffer ))
		return E_POINTER;

	CString		text( pcBuffer );

	if (( text != "0" ) && ( text != "1" ))
		return E_UNEXPECTED;

	SetONr( lONr, ( text == "1" ));

	//	WriteBack-Cache schreiben, sollte gelegentlich in die Datenbank
	//	zurückgeschrieben werden! (Spätestens beim Schließen)
	if ( lONr == -1L )	return NOERROR;
	if ( lONr == 0L )	return NOERROR;
	m_mapModi.SetAt((void*)lONr, (WORD)( text == "1" ));

	return NOERROR;
}

// Implementation der Funktionalität
BOOL COPGedrucktGS::SetONr( long onr, BOOL flag )
{
	if ( onr == -1L )	return FALSE;
	if ( onr == 0L )	return FALSE;
	m_mapONr.SetAt((void*)onr, (WORD)flag );
	return TRUE;
}

BOOL COPGedrucktGS::IstGedruckt( long onr )
{
	WORD	result = 0;

	if ( onr == -1L )	return FALSE;
	if ( onr == 0L )	return FALSE;

	m_mapONr.Lookup((void*)onr, result );

	return ( result == 1 );
}


////
//	COPBeitragsartGS

COPBeitragsartGS::COPBeitragsartGS()
{
	m_ulCount    = 0L;
	m_ulCumu     = 0L;
	m_ulRefCnt   = 0L;

	CString		text;

	text.LoadString( IDS_BEITRAGSART01 );
	m_arrText.Add( text );
	text.LoadString( IDS_BEITRAGSART02 );
	m_arrText.Add( text );
	text.LoadString( IDS_BEITRAGSART03 );
	m_arrText.Add( text );
	text.LoadString( IDS_BEITRAGSART04 );
	m_arrText.Add( text );
	text.LoadString( IDS_BEITRAGSART05 );
	m_arrText.Add( text );
	text.LoadString( IDS_BEITRAGSART06 );
	m_arrText.Add( text );
}

COPBeitragsartGS::~COPBeitragsartGS()
{
}

// *** IUnknown methods ***
STDMETHODIMP COPBeitragsartGS::QueryInterface( REFIID riid, void** ppv )
{
	*ppv = NULL;

	if ( IID_IUnknown == riid )
		*ppv = this;

	if ( IID_IObjectProperty == riid )
		*ppv = this;

    if ( NULL == *ppv )
        return ResultFromScode( E_NOINTERFACE );

    ((LPUNKNOWN)*ppv) -> AddRef();

	return NOERROR;
}

ULONG COPBeitragsartGS::AddRef( void )
{
	return ++m_ulRefCnt;
}

ULONG COPBeitragsartGS::Release( void )
{
	if ( 0 != --m_ulRefCnt )
		return m_ulRefCnt;

	delete this;
	return 0;
}

// *** IObjectProperty specific functions ***
STDMETHODIMP COPBeitragsartGS::GetPropInfo( LPSTR pBuffer, WORD wLen,
										DWORD *pdwFlags/*=NULL*/ )
{
	CString		info;

	info.LoadString( IDS_OPNAME03 );
	if ( info.GetLength() >= wLen )
		info = info.Left( wLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );
	if ( NULL != pdwFlags )
		*pdwFlags = PROPCAPS_OBJPROPTYPE_BOOL;	// Objekteigenschaft liefert Bool

	return NOERROR;
}

STDMETHODIMP COPBeitragsartGS::Reset( void )
{
	m_ulCount  = 0L;
	m_ulCumu   = 0L;
	return NOERROR;
}

ULONG COPBeitragsartGS::Count( void )
{
	return m_ulCount;
}

STDMETHODIMP COPBeitragsartGS::HelpInfo( LPSTR pBuffer, ULONG ulLen, 
				LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/)
{
	CString		info;

	info.LoadString( IDS_OPINFO03 );
	if ( info.GetLength() >= ulLen )
		info = info.Left( ulLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

STDMETHODIMP COPBeitragsartGS::Cumulation( LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/)
{
	CxString	info;

	info.AppendF( m_ulCumu, -1 );
	if ( info.GetLength() >= ulLen )
	{
		info = "***";
		if ( info.GetLength() >= ulLen )
			info = info.Left( ulLen - 1 );
	}

	if ( NULL != pulWritten )
		*pulWritten = info.GetLength();

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

STDMETHODIMP COPBeitragsartGS::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/)
{
	CxString	info;
	WORD		wert;

	++m_ulCount;

	if ( m_mapONr.Lookup((void*)lONr, wert ))
	{
		if ( wert >= 0 )
		{
			if ( wert > 6 )		wert = 6;
			if ( wert == 0 )	wert = 6;
			wert--;
			if ( wert < m_arrText.GetSize())
				info = m_arrText[wert];
		}
		++m_ulCumu;
	}

	if ( info.GetLength() > ulLen )
	{
		info = "***";
		if ( info.GetLength() > ulLen )
			info = info.Left( ulLen );
	}

	if ( NULL != pulWritten )
		*pulWritten = info.GetLength();

	if ( info.GetLength() > 0 )
		lstrcpyn( pBuffer, info, info.GetLength() + 1 );
	else
		*pBuffer = '\0';

	return NOERROR;
}

// Implementation der Funktionalität
BOOL COPBeitragsartGS::SetONr( long onr, WORD flag )
{
	if ( onr == -1L )	return FALSE;
	if ( onr == 0L )	return FALSE;
	m_mapONr.SetAt((void*)onr, flag );
	return TRUE;
}


////
//	COPEigentumGS

COPEigentumGS::COPEigentumGS()
{
	m_ulCount    = 0L;
	m_ulCumu     = 0L;
	m_ulRefCnt   = 0L;

	CString		text;

	text.LoadString( IDS_EIGENTUM01 );
	m_arrText.Add( text );
	text.LoadString( IDS_EIGENTUM02 );
	m_arrText.Add( text );
}

COPEigentumGS::~COPEigentumGS()
{
}

// *** IUnknown methods ***
STDMETHODIMP COPEigentumGS::QueryInterface( REFIID riid, void** ppv )
{
	*ppv = NULL;

	if ( IID_IUnknown == riid )
		*ppv = this;

	if ( IID_IObjectProperty == riid )
		*ppv = this;

    if ( NULL == *ppv )
        return ResultFromScode( E_NOINTERFACE );

    ((LPUNKNOWN)*ppv) -> AddRef();

	return NOERROR;
}

ULONG COPEigentumGS::AddRef( void )
{
	return ++m_ulRefCnt;
}

ULONG COPEigentumGS::Release( void )
{
	if ( 0 != --m_ulRefCnt )
		return m_ulRefCnt;

	delete this;
	return 0;
}

// *** IObjectProperty specific functions ***
STDMETHODIMP COPEigentumGS::GetPropInfo( LPSTR pBuffer, WORD wLen,
										DWORD *pdwFlags/*=NULL*/ )
{
	CString		info;

	info.LoadString( IDS_OPNAME04 );
	if ( info.GetLength() >= wLen )
		info = info.Left( wLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );
	if ( NULL != pdwFlags )
		*pdwFlags = PROPCAPS_OBJPROPTYPE_BOOL;	// Objekteigenschaft liefert Bool

	return NOERROR;
}

STDMETHODIMP COPEigentumGS::Reset( void )
{
	m_ulCount  = 0L;
	m_ulCumu   = 0L;
	return NOERROR;
}

ULONG COPEigentumGS::Count( void )
{
	return m_ulCount;
}

STDMETHODIMP COPEigentumGS::HelpInfo( LPSTR pBuffer, ULONG ulLen, 
				LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/)
{
	CString		info;

	info.LoadString( IDS_OPINFO04 );
	if ( info.GetLength() >= ulLen )
		info = info.Left( ulLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

STDMETHODIMP COPEigentumGS::Cumulation( LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/)
{
	CxString	info;

	info.AppendF( m_ulCumu, -1 );
	if ( info.GetLength() >= ulLen )
	{
		info = "***";
		if ( info.GetLength() >= ulLen )
			info = info.Left( ulLen - 1 );
	}

	if ( NULL != pulWritten )
		*pulWritten = info.GetLength();

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

STDMETHODIMP COPEigentumGS::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/)
{
	CxString	info;
	WORD		wert;

	++m_ulCount;

	if ( m_mapONr.Lookup((void*)lONr, wert ))
	{
		if ( wert == 1 )
			info = m_arrText[0];
		else
			info = m_arrText[1];

		++m_ulCumu;
	}

	if ( info.GetLength() > ulLen )
	{
		info = "***";
		if ( info.GetLength() > ulLen )
			info = info.Left( ulLen );
	}

	if ( NULL != pulWritten )
		*pulWritten = info.GetLength();

	if ( info.GetLength() > 0 )
		lstrcpyn( pBuffer, info, info.GetLength() + 1 );
	else
		*pBuffer = '\0';

	return NOERROR;
}

// Implementation der Funktionalität
BOOL COPEigentumGS::SetONr( long onr, WORD flag )
{
	if ( onr == -1L )	return FALSE;
	if ( onr == 0L )	return FALSE;
	m_mapONr.SetAt((void*)onr, flag );
	return TRUE;
}
