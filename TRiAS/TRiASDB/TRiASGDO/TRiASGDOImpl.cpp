#include "stdafx.h"
#include "TRiASGDOImpl.h"

#if defined(_DEBUG)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// Helfer für Umwandlung eines Rechtecks in ein Polygon

HRESULT MakePolyFromRect( _DGMPolygonGeometry* poly, _DGMRectangleGeometry* rect ) {
	RETURN_EXPR_TRUE( NULL == poly || NULL == rect, E_POINTER );

	CSCOORD		C0, C;
	double	w, h;
	W_DGMPoint	pt;
	RETURN_FAILED_HRESULT( rect->get_Origin( pt.ppi() ) );
	RETURN_FAILED_HRESULT( pt->GetPoint( &C0.X ) );
	RETURN_FAILED_HRESULT( rect->get_Width( &w ) );
	RETURN_FAILED_HRESULT( rect->get_Height( &h ) );

	W_DGMPoints				ptsT;
	pt = W_DGMPoint(CLSID_TRiASCSPoint);
	RETURN_FAILED_HRESULT( poly->get_Points( ptsT.ppi() ) );
	C = C0;		// links unten
	RETURN_FAILED_HRESULT( pt->SetPoint( &C.X ) );
	RETURN_FAILED_HRESULT( ptsT->Add( pt ) );
	C.X += w;	// rechts unten
	RETURN_FAILED_HRESULT( pt->SetPoint( &C.X ) );
	RETURN_FAILED_HRESULT( ptsT->Add( pt ) );
	C.Y += h;	// rechts oben
	RETURN_FAILED_HRESULT( pt->SetPoint( &C.X ) );
	RETURN_FAILED_HRESULT( ptsT->Add( pt ) );
	C.X -= w;	// links oben
	RETURN_FAILED_HRESULT( pt->SetPoint( &C.X ) );
	RETURN_FAILED_HRESULT( ptsT->Add( pt ) );
	C.Y -= h;	// wieder links unten, Polygon schließen
	RETURN_FAILED_HRESULT( pt->SetPoint( &C.X ) );
	RETURN_FAILED_HRESULT( ptsT->Add( pt ) );
	return S_OK;
}

HRESULT CopyPolygon( _DGMPolygonGeometry* polyDst, _DGMPolygonGeometry* polySrc ) {
	RETURN_EXPR_TRUE( NULL == polySrc || NULL == polyDst, E_POINTER );

	W_DGMPoints		pDGMPointsSrc, pDGMPointsDst;
	W_DGMPoint		pDGMPoint(CLSID_GMPoint);
	RETURN_FAILED_HRESULT( polySrc->get_Points( pDGMPointsSrc.ppi() ) );
	RETURN_FAILED_HRESULT( polyDst->get_Points( pDGMPointsDst.ppi() ) );
	long		nPoints;
	CSCOORD		C;
	RETURN_FAILED_HRESULT( pDGMPointsSrc->get_Count( &nPoints ) );
	for( long i = 0; i < nPoints; ++i ) {
		RETURN_FAILED_HRESULT( pDGMPointsSrc->GetPoint( i + 1, &C.X ) );
		C.Z = 0;
//		ATLTRACE( "p.X = %lf : p.Y = %lf : pts.Add(p)\n", C.X, C.Y );
		RETURN_FAILED_HRESULT( pDGMPoint->SetPoint( &C.X ) );
		RETURN_FAILED_HRESULT( pDGMPointsDst->Add( pDGMPoint ) );
	}
	return S_OK;
}

HRESULT SearchMDSMap (WTRiASMDSMap& rMap, const CComBSTR& strKey, CComBSTR& strResult, long lMode) 
{
	strResult = _T("");
	if (strKey.Length() < 1)
		return S_FALSE;

WTRiASMDSStringColl mdsSrchRes;
HRESULT	hr;

	RETURN_FAILED_HRESULT(hr = rMap -> Search (strKey, lMode, mdsSrchRes.ppi()));
	if (S_FALSE == hr)
		return S_FALSE;

WEnumVARIANT strings;
CComVariant v;

	mdsSrchRes -> _NewEnum (strings.ppu());

#pragma TODO( "Was ist bei Mehrdeutigkeiten zu tun??" )
	for (strings -> Reset(); S_OK == strings -> Next (1, CLEARED(v), NULL); /**/) {
		_ASSERTE(V_ISBSTR(&v));
		strResult = V_BSTR(&v);
		break;		// erstmal den ersten gefundenen nehmen
	}
	if (0 == strResult.Length())
		return S_FALSE;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Namen auf gültigen Datenbankbezeichner testen

HRESULT	ParseName( LPCOLESTR lpszName ) {
	CComBSTR	S(lpszName);
	return S.Length() > 64 ? E_FAIL : S_OK;
/*
	USES_CONVERSION;
	LPCTSTR	p = OLE2A(lpszName);
	for( ; *p; ++p ) {
		if( isalnum(*p) 
			|| *p == _T('_') 
			|| *p == _T('ä')
			|| *p == _T('ö')
			|| *p == _T('ü')
			|| *p == _T('Ä')
			|| *p == _T('Ö')
			|| *p == _T('Ü')
			)
			continue;
		return E_FAIL;
	}
	return S_OK;
*/
}

///////////////////////////////////////////////////////////////////////////////
// Namen in gültigen Datenbankbezeichner umwandeln

HRESULT NormalizeName (LPCOLESTR lpszName, CComBSTR& strNewName) 
{
	USES_CONVERSION;

TCHAR buf[64];
LPCTSTR	p = OLE2A(lpszName);
int idx = 0;

//	memset(buf, 0, sizeof(buf));

	for (/**/; *p && idx < 64; ++p, ++idx) 
		buf[idx] = __iscsym(*p) ? *p : _T('_');
	buf[idx] = _T('\0');

	strNewName = buf;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// wandelt einfache Hochkommata in 2-mal ein Hochkomma (==>SQL-Abfragen in
// Textfeldern)

inline CComBSTR QuoteStatement (const CComBSTR &strOldStmt) 
{
LPCOLESTR lpszOldStmt = strOldStmt;
OLECHAR	_buf[_MAX_PATH];
CComBSTR strNewStmt;
int	nChar = 0;

//	memset(_buf, 0x00, sizeof(_buf));
	_buf[nChar++] = L'\'';
	for (/**/ ; *lpszOldStmt; /**/) {
		if (L'\'' == *lpszOldStmt)
			_buf[nChar++] = L'\'';
		_buf[nChar++] = *lpszOldStmt++;

		if (nChar > _MAX_PATH - 5) {
			_buf[nChar] = L'\0';
			strNewStmt.Append(_buf);
			nChar = 0;
		}
	}
	_buf[nChar] = L'\0';
	strNewStmt.Append(_buf);
	strNewStmt.Append(L"\'");
	return strNewStmt;
}

/////////////////////////////////////////////////////////////////////////////
// liefert einen WHERE-Filterausdruck wie z.B. "[Attribute1] = 'hallo'"
// (insbes. für OriginatingPipe)

HRESULT GetFilter (IGDOObject* pGDOObject, CComBSTR& strFilter) 
{
	COM_TRY {
	WTRiASObject pTRiASObject (pGDOObject);
	CComBSTR strCrit;
	WDispatch pDisp;
		
		THROW_FAILED_HRESULT(pTRiASObject -> get_Name (CLEARED(strCrit)));
		THROW_FAILED_HRESULT(pTRiASObject -> get_Parent (pDisp.ppi()));

	WTRiASObjects pTRiASObjects (pDisp);
	WTRiASFeatures pTRiASFeatures;
	WTRiASFeature pTRiASPKeyFeature;
	CComBSTR strPKeyname;

		THROW_FAILED_HRESULT(pTRiASObjects -> get_PrimaryKey (CLEARED(strPKeyname)));
		THROW_FAILED_HRESULT(pTRiASObjects -> get_Features (pTRiASFeatures.ppi()));
		THROW_FAILED_HRESULT(pTRiASFeatures -> Item (CComVariant(strPKeyname), pTRiASPKeyFeature.ppi()));

	short gmType;
		
		THROW_FAILED_HRESULT(WGField(pTRiASPKeyFeature) -> get_Type (&gmType));
		if (gdbText == gmType) 
			strCrit = QuoteStatement(strCrit);

		strFilter = strPKeyname;
		strFilter.Append (L"=");
		strFilter.Append (strCrit);
	} COM_CATCH;
	return S_OK;
}

#if 0 // obsolete
/////////////////////////////////////////////////////////////////////////////
// Sucht einen bestimmten Record für ein bestimmtes GDO (TRiAS) -Objekt

//inline HRESULT GetFilter( IGDOFeature* pGDOFeature, const CComBSTR strValue, CComBSTR& strFilter ) {
//	short		gmType;
//	CComBSTR	strFieldname;
//	CComBSTR	strCrit = strValue;
//	RETURN_FAILED_HRESULT( pGDOFeature->get_Fieldname( CLEARED(strFieldname )) );
//	RETURN_FAILED_HRESULT( WGField(pGDOFeature)->get_Type( &gmType ) );
//	if( gdbText == gmType ) {
//		strCrit = QuoteStatement(strCrit);
//	}
//	strFilter = strFieldname;
//	strFilter.Append( L"=" );
//	strFilter.Append( strCrit );
//	return S_OK;
//}
//
//HRESULT LocateRecord( IGDODatabase* pGDODatabase, IGDOObjects* pGDOObjects, IGDOFeature* pGDOFeature, const CComBSTR& strValue, AC_GRecordset& rs ) {
//	WGTableDef			pGTableDef;
//	CComBSTR			strTablename;
//	WOriginatingPipe	pOriginatingPipe;
//	CComBSTR			strFilter;
//
//	RETURN_FAILED_HRESULT( pGDOObjects->get_Tablename( CLEARED(strTablename )) );
//	RETURN_FAILED_HRESULT( pGDODatabase->GetPipes( pOriginatingPipe.ppu(), NULL, NULL ) );
//	GetFilter( pGDOFeature, strValue, strFilter );
//	EXT_RETURN_FAILED_HRESULT( pOriginatingPipe->put_Table( EnBraceStatement(strTablename) ) );
//	EXT_RETURN_FAILED_HRESULT( pOriginatingPipe->put_Filter( strFilter ) );
//	COM_TRY {
//		EXT_RETURN_FAILED_HRESULT( pOriginatingPipe->get_OutputRecordset( rs.ppi() ) );
//	} COM_CATCH_RETURN( E_UNEXPECTED );
//	EXT_RETURN_FAILED_HRESULT( rs->MoveFirst() );
//	EXT_RETURN_FAILED_HRESULT( rs->MoveLast() );
//	long	lCount = 0;
//	EXT_RETURN_FAILED_HRESULT( rs->get_RecordCount( &lCount ) );
//	RETURN_EXPR_FALSE( 1 == lCount, E_FAIL );
//	return S_OK;
//}
//HRESULT LocateRecord( IGDOObject* pGDOObject, IGDOFeature* pGDOFeature, AC_GRecordset& rs ) {
//	WGDODatabase	pGDODatabase;
//	WGDOObjects		pGDOObjects;
//	RETURN_FAILED_HRESULT( FindSpecificParent( pGDOObject, pGDOObjects.GetIID(), pGDOObjects.ppv() ) );
//	RETURN_FAILED_HRESULT( FindSpecificParent( pGDOObject, pGDODatabase.GetIID(), pGDODatabase.ppv() ) );
//
//	CComBSTR			strTablename;
//	RETURN_FAILED_HRESULT( pGDOObjects->get_Tablename( CLEARED(strTablename )) );
//
//	WOriginatingPipe		pOriginatingPipe;
//	CComBSTR				strFilter;
//	RETURN_FAILED_HRESULT( pGDODatabase->GetPipes( pOriginatingPipe.ppu(), NULL, NULL ) );
//	GetFilter( pGDOObject, pGDOFeature, strFilter );
//	EXT_RETURN_FAILED_HRESULT( pOriginatingPipe->put_Table( EnBraceStatement(strTablename) ) );
//	EXT_RETURN_FAILED_HRESULT( pOriginatingPipe->put_Filter( strFilter ) );
//	COM_TRY {
//		EXT_RETURN_FAILED_HRESULT( pOriginatingPipe->get_OutputRecordset( rs.ppi() ) );
//	} COM_CATCH_RETURN( E_UNEXPECTED );
//	EXT_RETURN_FAILED_HRESULT( rs->MoveFirst() );
//	EXT_RETURN_FAILED_HRESULT( rs->MoveLast() );
//	long	lCount = 0;
//	EXT_RETURN_FAILED_HRESULT( rs->get_RecordCount( &lCount ) );
//	RETURN_EXPR_FALSE( 1 == lCount, E_FAIL );
//	return S_OK;
//}
#endif // 0 - obsolete

///////////////////////////////////////////////////////////////////////////////
// Routine, die RegistryKey liefert, unter dem alle GDO Server registriert sind

HKEY OpenDataServerKey (void) 
{
CRegKey key;

	if (ERROR_SUCCESS != key.Open (HKEY_CLASSES_ROOT, g_cbMyProgID) ||
		ERROR_SUCCESS != key.Open (key, TEXT("TRiASDB")))
	{
		return NULL;		// keine GDO-Server registriert
	}
	return key.Detach();
}

///////////////////////////////////////////////////////////////////////////////
// alle registrierten Einträge durchgehen und zählen

int CountRegisteredDataServers (HKEY hKey) 
{
	_ASSERTE(NULL != hKey);

DWORD dwCnt = 0;
TCHAR cbEnumKey[_MAX_PATH];

	while (ERROR_SUCCESS == ::RegEnumKey (hKey, dwCnt, cbEnumKey, _MAX_PATH)) 
		dwCnt++;		// nur zählen

	return int(dwCnt);
}
