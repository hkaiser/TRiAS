// ObjProp2.cpp

#include "StdAfx.h"
#include "ObjProp.h"

#include "GbmTRiAS.h"
#include "XtsnGUID.h"
#include "Resource.h"
#include "SetOP1.h"
#include "SetOP2.h"
#include "SetOP3.h"
#include "SetOP4.h"

extern CSetNF_PG2H* g_pNF_PG2H;
extern CSetNF_PG2D* g_pNF_PG2D;
extern CSetNF_PG1GB* g_pNF_PG1GB;
extern CSetNF_PG1* g_pNF_PG1;

CSetOP1* g_pSetOP1 = NULL;
CSetOP2* g_pSetOP2 = NULL;
CSetOP3* g_pSetOP3 = NULL;
CSetOP4* g_pSetOP4 = NULL;

COPDouble::COPDouble()
{
	m_ulCount    = 0L;
	m_ulCumu     = 0L;
	m_ulRefCnt   = 0L;
}

COPDouble::~COPDouble()
{
}

// *** IUnknown methods ***
STDMETHODIMP COPDouble::QueryInterface( REFIID riid, void** ppv )
{
	*ppv = NULL;

	if ( IID_IUnknown == riid )
		*ppv = this;

	if ( IID_IObjectProperty == riid )
		*ppv = this;

	if ( IID_IObjectProperty2 == riid )
		*ppv = this;

    if ( NULL == *ppv )
        return ResultFromScode( E_NOINTERFACE );

    ((LPUNKNOWN)*ppv) -> AddRef();

	return NOERROR;
}

ULONG COPDouble::AddRef( void )
{
	return ++m_ulRefCnt;
}

ULONG COPDouble::Release( void )
{
	if ( 0 != --m_ulRefCnt )
		return m_ulRefCnt;

	delete this;
	return 0;
}

// *** IObjectProperty specific functions ***
STDMETHODIMP COPDouble::GetPropInfo( LPSTR pBuffer, WORD wLen,
										DWORD *pdwFlags/*=NULL*/ )
{
	CString		info;

	info = m_strPropInfo;
	if ( info.GetLength() >= wLen )
		info = info.Left( wLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );
	if ( NULL != pdwFlags )
		*pdwFlags = PROPCAPS_OBJPROPTYPE_DOUBLE|PROPCAPS_NOTREADONLY;

	return NOERROR;
}

STDMETHODIMP COPDouble::Reset( void )
{
	m_ulCount  = 0L;
	m_ulCumu   = 0.0;
	return NOERROR;
}

ULONG COPDouble::Count( void )
{
	return m_ulCount;
}

STDMETHODIMP COPDouble::HelpInfo( LPSTR pBuffer, ULONG ulLen, 
				LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/)
{
	CString		info;

	info = m_strHelpInfo;
	if ( info.GetLength() >= ulLen )
		info = info.Left( ulLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

STDMETHODIMP COPDouble::Cumulation( LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/)
{
	CxString	info;

//	info.AppendFormated( m_ulCumu, -1, 2, 2 );
	info.AppendF( m_ulCumu, -1, 2 );
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

// *** IObjectProperty2 specific functions ***
STDMETHODIMP COPDouble::Set( LONG lONr, LPCSTR pcBuffer )
{
	if ( !AfxIsValidString( pcBuffer ))
		return E_POINTER;

	CxString	text( pcBuffer );
	CxString	strONr;
	CxString	strWert;

//	strWert.AppendFormated( text.FormatedDouble(), -1, 4, 4 );
	strWert.AppendF( text.Double(), -1, 4 );
//	SetONr( lONr, text.FormatedDouble());
	SetONr( lONr, text.Double());

	strONr.AppendF( lONr, -1 );
	//	WriteBack-Cache schreiben, sollte gelegentlich in die Datenbank
	//	zurückgeschrieben werden! (Spätestens beim Schließen)
	if ( lONr == -1L )	return NOERROR;
	if ( lONr == 0L )	return NOERROR;
	m_mapModi.SetAt( strONr, strWert );

	return NOERROR;
}

// Implementation der Funktionalität
BOOL COPDouble::SetONr( long onr, double wert )
{
	CxString	strWert, strONr;

	if ( onr == -1L )	return FALSE;
	if ( onr == 0L )	return FALSE;
//	strWert.AppendFormated( wert, -1, 4, 4 );
	strWert.AppendF( wert, -1, 4 );
	strONr.AppendF( onr, -1 );
	m_mapONr.SetAt( strONr, strWert );
	return TRUE;
}

double COPDouble::Wert( long onr )
{
	CxString	strWert, strONr;
	double		wert = 0.0;

	if ( onr == -1L )	return FALSE;
	if ( onr == 0L )	return FALSE;
	strONr.AppendF( onr, -1 );
	if ( m_mapONr.Lookup( strONr, strWert ))
		wert = atof( strWert );
	else
	{
		wert = RequeryWert( onr );
		SetONr( onr, wert );
	}

	return wert;
}


COPLong::COPLong()
{
	m_ulCount    = 0L;
	m_ulCumu     = 0L;
	m_ulRefCnt   = 0L;
}

COPLong::~COPLong()
{
}

// *** IUnknown methods ***
STDMETHODIMP COPLong::QueryInterface( REFIID riid, void** ppv )
{
	*ppv = NULL;

	if ( IID_IUnknown == riid )
		*ppv = this;

	if ( IID_IObjectProperty == riid )
		*ppv = this;

	if ( IID_IObjectProperty2 == riid )
		*ppv = this;

    if ( NULL == *ppv )
        return ResultFromScode( E_NOINTERFACE );

    ((LPUNKNOWN)*ppv) -> AddRef();

	return NOERROR;
}

ULONG COPLong::AddRef( void )
{
	return ++m_ulRefCnt;
}

ULONG COPLong::Release( void )
{
	if ( 0 != --m_ulRefCnt )
		return m_ulRefCnt;

	delete this;
	return 0;
}

// *** IObjectProperty specific functions ***
STDMETHODIMP COPLong::GetPropInfo( LPSTR pBuffer, WORD wLen,
										DWORD *pdwFlags/*=NULL*/ )
{
	CString		info;

	info = m_strPropInfo;
	if ( info.GetLength() >= wLen )
		info = info.Left( wLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );
	if ( NULL != pdwFlags )
		*pdwFlags = PROPCAPS_OBJPROPTYPE_INTEGER|PROPCAPS_NOTREADONLY;

	return NOERROR;
}

STDMETHODIMP COPLong::Reset( void )
{
	m_ulCount  = 0L;
	m_ulCumu   = 0L;
	return NOERROR;
}

ULONG COPLong::Count( void )
{
	return m_ulCount;
}

STDMETHODIMP COPLong::HelpInfo( LPSTR pBuffer, ULONG ulLen, 
				LPSTR pHelpFile/*=NULL*/, ULONG *pulHelpCtx/*=NULL*/)
{
	CString		info;

	info = m_strHelpInfo;
	if ( info.GetLength() >= ulLen )
		info = info.Left( ulLen - 1 );

	lstrcpyn( pBuffer, info, info.GetLength() + 1 );

	return NOERROR;
}

STDMETHODIMP COPLong::Cumulation( LPSTR pBuffer, ULONG ulLen, 
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

// *** IObjectProperty2 specific functions ***
STDMETHODIMP COPLong::Set( LONG lONr, LPCSTR pcBuffer )
{
	if ( !AfxIsValidString( pcBuffer ))
		return E_POINTER;

	CxString	text( pcBuffer );
	CxString	strONr;

//	SetONr( lONr, text.FormatedLong());
	SetONr( lONr, text.Long());

	strONr.AppendF( lONr, -1 );
	//	WriteBack-Cache schreiben, sollte gelegentlich in die Datenbank
	//	zurückgeschrieben werden! (Spätestens beim Schließen)
	if ( lONr == -1L )	return NOERROR;
	if ( lONr == 0L )	return NOERROR;
//	m_mapModi.SetAt((void*)lONr, (void*)text.FormatedLong());
	m_mapModi.SetAt((void*)lONr, (void*)text.Long());

	return NOERROR;
}

// Implementation der Funktionalität
BOOL COPLong::SetONr( long onr, long wert )
{
	if ( onr == -1L )	return FALSE;
	if ( onr == 0L )	return FALSE;
	m_mapONr.SetAt((void*)onr, (void*)wert );
	return TRUE;
}

long COPLong::Wert( long onr )
{
	long		wert = 0L;
	void		*ptr;

	if ( onr == -1L )	return FALSE;
	if ( onr == 0L )	return FALSE;
	if ( m_mapONr.Lookup((void*)onr, ptr ))
		wert = (long)ptr;
	else
	{
		wert = RequeryWert( onr );
		SetONr( onr, wert );
	}

	return wert;
}

//////////////////////////////////////////////////////////////////////
COP_AGGS::COP_AGGS()
{
	m_strPropInfo.LoadString( IDS_OPNAME06 );
	m_strHelpInfo.LoadString( IDS_OPINFO06 );
}

COP_AGGS::~COP_AGGS()
{
	RewriteModi();
}

STDMETHODIMP COP_AGGS::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten )
{
	CxString	info;
	double		wert = 0.0;

	if ( IstGrundstueck( lONr ))
	{
		++m_ulCount;
		wert = Wert( lONr );
//		info.AppendFormated( wert, -1, 2, 2 );
		info.AppendF( wert, -1, 2 );
		m_ulCumu += wert;
	}
	else
		info = "0.00";

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

double COP_AGGS::RequeryWert( long onr )
{
	double	result = 0.0;

	if ( !IstGrundstueck( onr ))	return result;

	if ( NULL == g_pSetOP1 )	g_pSetOP1 = new CSetOP1;
	if ( g_pSetOP1 -> SelectONr( onr ))
		result = g_pSetOP1 -> m_AGGS;

	return result;
}

void COP_AGGS::RewriteModi()
{
	POSITION	pos;
	CxString	strKey, strWert;
	BOOL		bCallUpdate = FALSE;

	pos = m_mapModi.GetStartPosition();
	while ( NULL != pos )
	{
		m_mapModi.GetNextAssoc( pos, strKey, strWert );
		if ( bCallUpdate = g_pSetOP1 -> SelectONr( atol( strKey )))
			g_pSetOP1 -> Edit();
		else
		{
			CString		ide;

			if ( IDEfromONr( atol( strKey ), ide ))
			{
				g_pSetOP1 -> AddNew();
				g_pSetOP1 -> m_IDE = ide;
				bCallUpdate = TRUE;
			}
		}

		if ( bCallUpdate )
		{
			g_pSetOP1 -> m_AGGS = strWert.Double();
			g_pSetOP1 -> Update();
		}
	}
	m_mapModi.RemoveAll();
}

COP_FLG::COP_FLG()
{
	m_strPropInfo.LoadString( IDS_OPNAME05 );
	m_strHelpInfo.LoadString( IDS_OPINFO05 );
}

COP_FLG::~COP_FLG()
{
	RewriteModi();
}


ULONG COP_FLG::AddRef( void )
{
	ULONG result = COPDouble::AddRef();
	return result;
}

ULONG COP_FLG::Release( void )
{
	ULONG result = COPDouble::Release();
	return result;
}

STDMETHODIMP COP_FLG::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten )
{
	CxString	info;
	double		wert = 0.0;

	if ( IstGebaeude( lONr ) ||
		 IstDachteilflaeche( lONr ) ||
		 IstHofflaeche( lONr ))
	{
		++m_ulCount;
		wert = Wert( lONr );
//		info.AppendFormated( wert, -1, 2, 2 );
		info.AppendF( wert, -1, 2 );
		m_ulCumu += wert;
	}
	else
		info = "0.00";

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

double COP_FLG::RequeryWert( long onr )
{
	double	result = 0.0;

	if ( IstGebaeude( onr ))
	{
		if ( NULL == g_pSetOP2 )	g_pSetOP2 = new CSetOP2;
		if ( g_pSetOP2 -> SelectONr( onr ))
			result = g_pSetOP2 -> m_GFL;
	}
	else if ( IstDachteilflaeche( onr ))
	{
		if ( NULL == g_pSetOP3 )	g_pSetOP3 = new CSetOP3;
		if ( g_pSetOP3 -> SelectONr( onr ))
			result = g_pSetOP3 -> m_FLG;
	}
	else if ( IstHofflaeche( onr ))
	{
		if ( NULL == g_pSetOP4 )	g_pSetOP4 = new CSetOP4;
		if ( g_pSetOP4 -> SelectONr( onr ))
			result = g_pSetOP4 -> m_FLG;
	}

	return result;
}

void COP_FLG::RewriteModi()
{
	POSITION	pos;
	CxString	strKey, strWert;
	long		onr;
	BOOL		bCallUpdate = FALSE;

	pos = m_mapModi.GetStartPosition();
	while ( NULL != pos )
	{
		m_mapModi.GetNextAssoc( pos, strKey, strWert );
		onr = strKey.Long();
		if ( IstGebaeude( onr ))
		{
			if ( NULL == g_pSetOP2 )	g_pSetOP2 = new CSetOP2;
			if ( bCallUpdate = g_pSetOP2 -> SelectONr( onr ))
				g_pSetOP2 -> Edit();
			else
			{
				CString		ide;

				if ( IDEfromONr( onr, ide ))
				{
					g_pSetOP2 -> AddNew();
					g_pSetOP2 -> m_IDE = ide;
					bCallUpdate = TRUE;
				}
			}

			if ( bCallUpdate )
			{
				g_pSetOP2 -> m_GFL = strWert.Double();
				g_pSetOP2 -> Update();
			}
		}
		else if ( IstDachteilflaeche( onr ))
		{
			if ( NULL == g_pSetOP3 )	g_pSetOP3 = new CSetOP3;
			if ( bCallUpdate = g_pSetOP3 -> SelectONr( onr ))
				g_pSetOP3 -> Edit();
			else
			{
				CString		ide;

				if ( IDEfromONr( onr, ide ))
				{
					g_pSetOP3 -> AddNew();
					g_pSetOP3 -> m_IDE = ide;
					bCallUpdate = TRUE;
				}
			}

			if ( bCallUpdate )
			{
				g_pSetOP3 -> m_FLG = strWert.Double();
				g_pSetOP3 -> Update();
			}
		}
		else if ( IstHofflaeche( onr ))
		{
			if ( NULL == g_pSetOP4 )	g_pSetOP4 = new CSetOP4;
			if ( bCallUpdate = g_pSetOP4 -> SelectONr( onr ))
				g_pSetOP4 -> Edit();
			else
			{
				CString		ide;

				if ( IDEfromONr( onr, ide ))
				{
					g_pSetOP4 -> AddNew();
					g_pSetOP4 -> m_IDE = ide;
					bCallUpdate = TRUE;
				}
			}

			if ( bCallUpdate )
			{
				g_pSetOP4 -> m_FLG = strWert.Double();
				g_pSetOP4 -> Update();
			}
		}
	}
	m_mapModi.RemoveAll();
}


COP_GEFS::COP_GEFS()
{
	m_strPropInfo.LoadString( IDS_OPNAME07 );
	m_strHelpInfo.LoadString( IDS_OPINFO07 );
}

COP_GEFS::~COP_GEFS()
{
	RewriteModi();
}

STDMETHODIMP COP_GEFS::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten )
{
	CxString	info;
	double		wert = 0.0;

	if ( IstGrundstueck( lONr ))
	{
		++m_ulCount;
		wert = Wert( lONr );
//		info.AppendFormated( wert, -1, 2, 2 );
		info.AppendF( wert, -1, 2 );
		m_ulCumu += wert;
	}
	else
		info = "0.00";

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

double COP_GEFS::RequeryWert( long onr )
{
	double	result = 0.0;

	if ( !IstGrundstueck( onr ))	return result;

	if ( NULL == g_pSetOP1 )	g_pSetOP1 = new CSetOP1;
	if ( g_pSetOP1 -> SelectONr( onr ))
		result = g_pSetOP1 -> m_GEFS;

	return result;
}

void COP_GEFS::RewriteModi()
{
	POSITION	pos;
	CxString	strKey, strWert;
	BOOL		bCallUpdate = FALSE;

	pos = m_mapModi.GetStartPosition();
	while ( NULL != pos )
	{
		m_mapModi.GetNextAssoc( pos, strKey, strWert );
		if ( bCallUpdate = g_pSetOP1 -> SelectONr( atol( strKey )))
			g_pSetOP1 -> Edit();
		else
		{
			CString		ide;

			if ( IDEfromONr( atol( strKey ), ide ))
			{
				g_pSetOP1 -> AddNew();
				g_pSetOP1 -> m_IDE = ide;
				bCallUpdate = TRUE;
			}
		}

		if ( bCallUpdate )
		{
			g_pSetOP1 -> m_GEFS = strWert.Double();
			g_pSetOP1 -> Update();
		}
	}
	m_mapModi.RemoveAll();
}


COP_TIEB::COP_TIEB()
{
	m_strPropInfo.LoadString( IDS_OPNAME08 );
	m_strHelpInfo.LoadString( IDS_OPINFO08 );
}

COP_TIEB::~COP_TIEB()
{
	RewriteModi();
}

STDMETHODIMP COP_TIEB::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten )
{
	CxString	info;
	double		wert = 0.0;

	if ( IstGrundstueck( lONr ))
	{
		++m_ulCount;
		wert = Wert( lONr );
//		info.AppendFormated( wert, -1, 2, 2 );
		info.AppendF( wert, -1, 2 );
		m_ulCumu += wert;
	}
	else
		info = "0.00";

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

double COP_TIEB::RequeryWert( long onr )
{
	double	result = 0.0;

	if ( !IstGrundstueck( onr ))	return result;

	if ( NULL == g_pSetOP1 )	g_pSetOP1 = new CSetOP1;
	if ( g_pSetOP1 -> SelectONr( onr ))
		result = g_pSetOP1 -> m_TIEB;

	return result;
}

void COP_TIEB::RewriteModi()
{
	POSITION	pos;
	CxString	strKey, strWert;
	BOOL		bCallUpdate = FALSE;

	pos = m_mapModi.GetStartPosition();
	while ( NULL != pos )
	{
		m_mapModi.GetNextAssoc( pos, strKey, strWert );
		if ( bCallUpdate = g_pSetOP1 -> SelectONr( atol( strKey )))
			g_pSetOP1 -> Edit();
		else
		{
			CString		ide;

			if ( IDEfromONr( atol( strKey ), ide ))
			{
				g_pSetOP1 -> AddNew();
				g_pSetOP1 -> m_IDE = ide;
				bCallUpdate = TRUE;
			}
		}

		if ( bCallUpdate )
		{
			g_pSetOP1 -> m_TIEB = strWert.Double();
			g_pSetOP1 -> Update();
		}
	}
	m_mapModi.RemoveAll();
}


COP_KAT::COP_KAT()
{
	m_strPropInfo.LoadString( IDS_OPNAME09 );
	m_strHelpInfo.LoadString( IDS_OPINFO09 );
}

COP_KAT::~COP_KAT()
{
	RewriteModi();
}

STDMETHODIMP COP_KAT::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten )
{
	CxString	info;
	double		wert = 0.0;

	if ( IstGrundstueck( lONr ))
	{
		++m_ulCount;
		wert = Wert( lONr );
//		info.AppendFormated( wert, -1, 2, 2 );
		info.AppendF( wert, -1, 2 );
		m_ulCumu += wert;
	}
	else
		info = "0.00";

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

double COP_KAT::RequeryWert( long onr )
{
	double	result = 0.0;

	if ( !IstGrundstueck( onr ))	return result;

	if ( NULL == g_pSetOP1 )	g_pSetOP1 = new CSetOP1;
	if ( g_pSetOP1 -> SelectONr( onr ))
		result = g_pSetOP1 -> m_KAT;

	return result;
}

void COP_KAT::RewriteModi()
{
	POSITION	pos;
	CxString	strKey, strWert;
	BOOL		bCallUpdate = FALSE;

	pos = m_mapModi.GetStartPosition();
	while ( NULL != pos )
	{
		m_mapModi.GetNextAssoc( pos, strKey, strWert );
		if ( bCallUpdate = g_pSetOP1 -> SelectONr( atol( strKey )))
			g_pSetOP1 -> Edit();
		else
		{
			CString		ide;

			if ( IDEfromONr( atol( strKey ), ide ))
			{
				g_pSetOP1 -> AddNew();
				g_pSetOP1 -> m_IDE = ide;
				bCallUpdate = TRUE;
			}
		}

		if ( bCallUpdate )
		{
			g_pSetOP1 -> m_KAT = strWert.Double();
			g_pSetOP1 -> Update();
		}
	}
	m_mapModi.RemoveAll();
}


COP_FLN::COP_FLN()
{
	m_strPropInfo.LoadString( IDS_OPNAME10 );
	m_strHelpInfo.LoadString( IDS_OPINFO10 );
}

COP_FLN::~COP_FLN()
{
	RewriteModi();
}

STDMETHODIMP COP_FLN::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten )
{
	CxString	info;
	long		wert = 0L;

	if ( IstGebaeude( lONr ) ||
		 IstDachteilflaeche( lONr ) ||
		 IstHofflaeche( lONr ))
	{
		++m_ulCount;
		wert = Wert( lONr );
//		info.AppendFormated( wert, -1 );
		info.AppendF( wert, -1 );
		m_ulCumu += wert;
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

long COP_FLN::RequeryWert( long onr )
{
	long	result = 0.0;

	if ( IstGebaeude( onr ))
	{
		if ( NULL == g_pSetOP2 )	g_pSetOP2 = new CSetOP2;
		if ( g_pSetOP2 -> SelectONr( onr ))
			result = g_pSetOP2 -> m_lFLN;
	}
	else if ( IstDachteilflaeche( onr ))
	{
		if ( NULL == g_pSetOP3 )	g_pSetOP3 = new CSetOP3;
		if ( g_pSetOP3 -> SelectONr( onr ))
			result = g_pSetOP3 -> m_lFLN;
	}
	else if ( IstHofflaeche( onr ))
	{
		if ( NULL == g_pSetOP4 )	g_pSetOP4 = new CSetOP4;
		if ( g_pSetOP4 -> SelectONr( onr ))
			result = g_pSetOP4 -> m_lFLN;
	}

	return result;
}

void COP_FLN::RewriteModi()
{
	POSITION	pos;
	void		*ptrKey, *ptrWert;
	long		onr;
	BOOL		bCallUpdate = FALSE;

	pos = m_mapModi.GetStartPosition();
	while ( NULL != pos )
	{
		m_mapModi.GetNextAssoc( pos, ptrKey, ptrWert );
		onr = (long)ptrKey;
		if ( IstGebaeude( onr ))
		{
			if ( NULL == g_pSetOP2 )	g_pSetOP2 = new CSetOP2;
			if ( bCallUpdate = g_pSetOP2 -> SelectONr( onr ))
				g_pSetOP2 -> Edit();
			else
			{
				CString		ide;

				if ( IDEfromONr( onr, ide ))
				{
					g_pSetOP2 -> AddNew();
					g_pSetOP2 -> m_IDE = ide;
					bCallUpdate = TRUE;
				}
			}

			if ( bCallUpdate )
			{
				g_pSetOP2 -> m_lFLN = (long)ptrWert;
				g_pSetOP2 -> Update();
			}
		}
		else if ( IstDachteilflaeche( onr ))
		{
			if ( NULL == g_pSetOP3 )	g_pSetOP3 = new CSetOP3;
			if ( bCallUpdate = g_pSetOP3 -> SelectONr( onr ))
				g_pSetOP3 -> Edit();
			else
			{
				CString		ide;

				if ( IDEfromONr( onr, ide ))
				{
					g_pSetOP3 -> AddNew();
					g_pSetOP3 -> m_IDE = ide;
					bCallUpdate = TRUE;
				}
			}

			if ( bCallUpdate )
			{
				g_pSetOP3 -> m_lFLN = (long)ptrWert;
				g_pSetOP3 -> Update();
			}
		}
		else if ( IstHofflaeche( onr ))
		{
			if ( NULL == g_pSetOP4 )	g_pSetOP4 = new CSetOP4;
			if ( bCallUpdate = g_pSetOP4 -> SelectONr( onr ))
				g_pSetOP4 -> Edit();
			else
			{
				CString		ide;

				if ( IDEfromONr( onr, ide ))
				{
					g_pSetOP4 -> AddNew();
					g_pSetOP4 -> m_IDE = ide;
					bCallUpdate = TRUE;
				}
			}

			if ( bCallUpdate )
			{
				g_pSetOP4 -> m_lFLN = (long)ptrWert;
				g_pSetOP4 -> Update();
			}
		}
	}
	m_mapModi.RemoveAll();
}


COP_TIEF::COP_TIEF()
{
	m_strPropInfo.LoadString( IDS_OPNAME11 );
	m_strHelpInfo.LoadString( IDS_OPINFO11 );
}

COP_TIEF::~COP_TIEF()
{
	RewriteModi();
}

STDMETHODIMP COP_TIEF::Eval( LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				ULONG *pulWritten/*=NULL*/)
{
	CxString	info;
	long		wert = 0L;

	if ( IstGrundstueck( lONr ))
	{
		++m_ulCount;
		wert = Wert( lONr );
//		info.AppendFormated( wert, -1 );
		info.AppendF( wert, -1 );
		m_ulCumu += wert;
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

long COP_TIEF::RequeryWert( long onr )
{
	long	result = 0L;

	if ( !IstGrundstueck( onr ))	return result;

	if ( NULL == g_pSetOP1 )	g_pSetOP1 = new CSetOP1;
	if ( g_pSetOP1 -> SelectONr( onr ))
		if ( TestYES( g_pSetOP1 -> m_TIEF ))
			result = 1L;

	return result;
}

void COP_TIEF::RewriteModi()
{
	POSITION	pos;
	void		*ptrKey, *ptrWert;
	BOOL		bCallUpdate = FALSE;

	pos = m_mapModi.GetStartPosition();
	while ( NULL != pos )
	{
		m_mapModi.GetNextAssoc( pos, ptrKey, ptrWert );
		if ( bCallUpdate = g_pSetOP1 -> SelectONr((long)ptrKey ))
			g_pSetOP1 -> Edit();
		else
		{
			CString		ide;

			if ( IDEfromONr((long)ptrKey, ide ))
			{
				g_pSetOP1 -> AddNew();
				g_pSetOP1 -> m_IDE = ide;
				bCallUpdate = TRUE;
			}
		}

		if ( bCallUpdate )
		{
			g_pSetOP1 -> m_TIEF = ( NULL != ptrWert ? "j" : "n" );
			g_pSetOP1 -> Update();
		}
	}
	m_mapModi.RemoveAll();
}
