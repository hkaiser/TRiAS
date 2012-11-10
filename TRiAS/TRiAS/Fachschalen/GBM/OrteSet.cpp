// OrteSet.cpp : implementation file
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
// COrteSet

IMPLEMENT_DYNAMIC(COrteSet, CRecordset)

COrteSet::COrteSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(COrteSet)
	m_ORT_NAM = _T("");
	m_ORT_ISY = 0.0;
	m_ORT_TB = 0.0;
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_bInitialisiert = FALSE;
}


CString COrteSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString COrteSet::GetDefaultSQL()
{
	return _T("[ORT]");
}

void COrteSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(COrteSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ORT_NAM]"), m_ORT_NAM);
	RFX_Double(pFX, _T("[ORT_ISY]"), m_ORT_ISY);
	RFX_Double(pFX, _T("[ORT_TB]"), m_ORT_TB);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// COrteSet diagnostics

#ifdef _DEBUG
void COrteSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void COrteSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void COrteSet::InitListen( BOOL overwrite )
{
	if ( m_bInitialisiert && !overwrite )	return;

	if ( !IsOpen())	Open();

	m_mapListe.RemoveAll();
	MoveFirst();
	while ( !IsEOF())
	{
		RegisterOrt( m_ORT_ISY, m_ORT_NAM );
		MoveNext();
	}
}

void COrteSet::RegisterOrt( double isy, const char* name )
{
	ASSERT( AfxIsValidString( name ));
	CString		strName = name;
	CString		strISY;
	CString		text;

	OISY2String( isy, strISY );
	if ( strName.IsEmpty())		return;
	if ( strISY.IsEmpty())		return;

	if ( m_mapListe.Lookup( strISY, text ))
	{
#ifdef _DEBUG
		AfxMessageBox( "Fehler in Tabelle Orte! Mehrfachnennung!" );
#endif //_DEBUG
		return;
	}

	m_mapListe.SetAt( strISY, strName );

	strISY.Empty();
	OISY2String2( isy, strISY );
	if ( strISY.IsEmpty())		return;

	if ( m_mapListe.Lookup( strISY, text ))
	{
#ifdef _DEBUG
		AfxMessageBox( "Fehler in Tabelle Orte! Mehrfachnennung!" );
#endif //_DEBUG
		return;
	}

	m_mapListe.SetAt( strISY, strName );
}

double COrteSet::TB( short isy )
{
	double		result = -1;

	if ( !IsOpen())	Open();

	MoveFirst();
	while ( !IsEOF() && ( result < 0 ))
	{
		if ( isy == (int)m_ORT_ISY )	result = m_ORT_TB;
		MoveNext();
	}
	if ( result < 0 )	result = 50;
	return result;
}

CString COrteSet::Ort( const char* ide )
{
	ASSERT( AfxIsValidString( ide ));
	CString		oisy, result;

	oisy = ide;
	ASSERT( oisy.GetLength() >= 2 );
	oisy = oisy.Left( 2 );
	m_mapListe.Lookup( oisy, result );
	return result;
}
