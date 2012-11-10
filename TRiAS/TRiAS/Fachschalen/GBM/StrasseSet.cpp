// StrasseSet.cpp : implementation file
//

#include <bool.h>
#include "stdafx.h"
#include "GbmTRiAS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStrasseSet

IMPLEMENT_DYNAMIC(CStrasseSet, CRecordset)

CStrasseSet::CStrasseSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CStrasseSet)
	m_STR_NAM = _T("");
	m_STR_ISY = 0.0;
	m_STR_OISY = 0.0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_bInitialisiert = FALSE;
}

CStrasseSet::~CStrasseSet()
{
	CleanupListen();
}


CString CStrasseSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CStrasseSet::GetDefaultSQL()
{
	return _T("[STR]");
}

void CStrasseSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CStrasseSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[STR_NAM]"), m_STR_NAM);
	RFX_Double(pFX, _T("[STR_ISY]"), m_STR_ISY);
	RFX_Double(pFX, _T("[STR_OISY]"), m_STR_OISY);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CStrasseSet diagnostics

#ifdef _DEBUG
void CStrasseSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStrasseSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CStrasseSet::InitListen( BOOL overwrite )
{
	if ( m_bInitialisiert && !overwrite )	return;

	if ( !IsOpen())	return;

	CleanupListen();
	MoveFirst();
	while ( !IsEOF())
	{
		RegisterStrasse( m_STR_OISY, m_STR_ISY, m_STR_NAM );
		MoveNext();
	}
	m_bInitialisiert = TRUE;
}

void CStrasseSet::CleanupListen()
{
	POSITION			pos;
	CString				key;
	void				*pv;
	CMapStringToString	*pa;

	m_mapListe.RemoveAll();

	for( pos = m_mapOrtListen.GetStartPosition(); pos != NULL; )
	{
		m_mapOrtListen.GetNextAssoc( pos, key, pv );
		pa = (CMapStringToString*)pv;
		if ( pa )
		{
			pa -> RemoveAll();
			delete pa;
			pa = NULL;
		}
	}
	m_mapOrtListen.RemoveAll();
}

void CStrasseSet::RegisterStrasse( double oisy, double isy, const char* name )
{
	CString				strOISY, strISY, strName;
	CString				key;
	void				*pv;
	CMapStringToString	*mapOrt = NULL;

	OISY2String( oisy, strOISY );
	ISY2String( oisy, isy, strISY );
	strName = name;

	if ( strOISY.IsEmpty())		return;
	if ( strISY.IsEmpty())		return;
	if ( strName.IsEmpty())		return;

	key = strOISY;
	if ( m_mapOrtListen.Lookup( key, (void*)pv ))
	{
		mapOrt = (CMapStringToString*)pv;
		if ( mapOrt != NULL )
			mapOrt -> SetAt( strISY, strName );
	}
	else
	{
		mapOrt = new CMapStringToString;
		if ( mapOrt != NULL )
			mapOrt -> SetAt( strISY, strName );
		m_mapOrtListen.SetAt( key, mapOrt );
	}
	key = strOISY;
	key += strISY;
	m_mapListe.SetAt( key, strName );

	OISY2String2( oisy, strOISY );

	if ( strOISY.IsEmpty())		return;

	key = strOISY;
	if ( m_mapOrtListen.Lookup( key, (void*)pv ))
	{
		mapOrt = (CMapStringToString*)pv;
		if ( mapOrt != NULL )
			mapOrt -> SetAt( strISY, strName );
	}
	else
	{
		mapOrt = new CMapStringToString;
		if ( mapOrt != NULL )
			mapOrt -> SetAt( strISY, strName );
		m_mapOrtListen.SetAt( key, mapOrt );
	}
	key = strOISY;
	key += strISY;
	m_mapListe.SetAt( key, strName );
}

short CStrasseSet::GetZahlStrassen( short oisy )
{
	short	result = 0;
	CString				strOISY;
	CString				key;
	void				*pv;
	CMapStringToString	*mapOrt = NULL;

	OISY2String( oisy, strOISY );

	if ( strOISY.IsEmpty())		return result;

	key = strOISY;
	if ( m_mapOrtListen.Lookup( key, (void*)pv ))
	{
		mapOrt = (CMapStringToString*)pv;
		if ( mapOrt != NULL )
			result = mapOrt -> GetCount();
	}
	return result;
}	// GetZahlStrassen

CMapStringToString* CStrasseSet::GetStrassen( short oisy )
{
	CString				strOISY;
	CString				key;
	void				*pv;
	CMapStringToString	*result = NULL;

	OISY2String( oisy, strOISY );

	if ( strOISY.IsEmpty())		return result;

	key = strOISY;
	if ( m_mapOrtListen.Lookup( key, (void*)pv ))
		result = (CMapStringToString*)pv;

	return result;
}	// GetStrassen

CString CStrasseSet::Strasse( const char* ide )
{
	CString				result;
	CString				ort, str;
	void				*pv;
	CMapStringToString	*pMap = NULL;

	ASSERT( AfxIsValidString( ide ));
	ort = ide;
	ASSERT( ort.GetLength() >= 5 );
	str = ort.Mid( 2, 3 );
	ort = ort.Left( 2 );

	if ( m_mapOrtListen.Lookup( ort, pv ))
	{
		pMap = (CMapStringToString*)pv;
		ASSERT_VALID( pMap );
		pMap -> Lookup( str, result );
	}

	return result;
}
