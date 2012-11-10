// SetVorlagen.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetVorlagen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetVorlagen

IMPLEMENT_DYNAMIC(CSetVorlagen, CRecordset)

CSetVorlagen::CSetVorlagen(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetVorlagen)
	m_ID = 0;
	m_Kode = _T("");
	m_Name = _T("");
	m_Pfad = _T("");
	m_Typ = 0;
	m_NurLesen = FALSE;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetVorlagen::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetVorlagen::GetDefaultSQL()
{
	return _T("[Vorlagen]");
}

void CSetVorlagen::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetVorlagen)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[Kode]"), m_Kode);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Pfad]"), m_Pfad);
	RFX_Int(pFX, _T("[Typ]"), m_Typ);
	RFX_Bool(pFX, _T("[NurLesen]"), m_NurLesen);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetVorlagen diagnostics

#ifdef _DEBUG
void CSetVorlagen::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetVorlagen::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CSetVorlagen::SelectVorlage( const char id )
{
	BOOL		result = FALSE;
	CString		key, name;

	InitListen();

	m_Kode = id;
	m_Name = "";
	m_Pfad = "";
	m_Typ = 0;
	key = id;
	if ( m_mapNamen.Lookup( key, name ))
	{
		m_Name = name;
		m_mapPfade.Lookup( key, m_Pfad );
		m_mapType.Lookup( key, name );
		m_Typ = atoi( name );
		m_NurLesen = ( "O" == name.Right( 1 ));
		result = TRUE;
	}
	return result;
}

void CSetVorlagen::InitListen()
{
	if ( m_mapNamen.GetCount())	return;

	CxString	key, item;

	try {
		Open();
		while ( !IsEOF())
		{
			key = m_Kode;
			m_mapNamen.SetAt( key, m_Name );
			if ( !m_Pfad.IsEmpty())
				m_mapPfade.SetAt( key, m_Pfad );
			item.Empty();
			item.AppendF( m_Typ, -1 );
			if ( m_NurLesen )	item += "O";
			else				item += "R";
			m_mapType.SetAt( key, item );

			MoveNext();
		}
		Close();

	} catch ( CDBException *e ) {

		AfxMessageBox( e -> m_strError );

	} catch ( CMemoryException *e) {

		AfxMessageBox( g_cbMemoryException );
		e -> Delete();

	} catch (...) {

		AfxMessageBox( g_cbUnhandeledException );
	}
}

BOOL CSetVorlagen::UpdateVorlage()
{
	BOOL		result = FALSE;
	BOOL		found = FALSE;
	CString		key, name, pfad;
	long		typ;

	key  = m_Kode;
	name = m_Name;
	pfad = m_Pfad;
	typ  = m_Typ;
	try {
		Open();
		while ( !IsEOF())
		{
			if ( found = ( key == m_Kode ))
				break;

			MoveNext();
		}
		if ( found )	Edit();
		else			AddNew();

		m_Kode = key;
		m_Name = name;
		m_Pfad = pfad;
		m_Typ  = typ;

		Update();
		Close();

		result = TRUE;

	} catch ( CDBException *e ) {

		AfxMessageBox( e -> m_strError );

	} catch ( CMemoryException *e) {

		AfxMessageBox( g_cbMemoryException );
		e -> Delete();

	} catch (...) {

		AfxMessageBox( g_cbUnhandeledException );
	}

	if ( result )	InitListen();

	return result;
}
