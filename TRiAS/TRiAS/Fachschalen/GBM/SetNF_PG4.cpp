// SetNF_PG4.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetNF_PG4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG4

IMPLEMENT_DYNAMIC(CSetNF_PG4, CRecordset)

CSetNF_PG4::CSetNF_PG4(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetNF_PG4)
	m_NFP4_BDM = 0.0;
	m_NFP4_EAN = _T("");
	m_NFP4_ENA = _T("");
	m_NFP4_EOR = _T("");
	m_NFP4_EPL = _T("");
	m_NFP4_HER = _T("");
	m_NFP4_IDE = _T("");
	m_NFP4_TFL = 0.0;
	m_NFP4_PN = 1.0;
	m_NFP4_PZ = 1.0;
	m_NFP4_NR = 0;
	m_NFP4_KASS = _T("");
	m_nFields = 12;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetNF_PG4::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetNF_PG4::GetDefaultSQL()
{
	return _T("[NF_PG4]");
}

void CSetNF_PG4::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetNF_PG4)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Double(pFX, _T("[NFP4_BDM]"), m_NFP4_BDM);
	RFX_Text(pFX, _T("[NFP4_EAN]"), m_NFP4_EAN);
	RFX_Text(pFX, _T("[NFP4_ENA]"), m_NFP4_ENA);
	RFX_Text(pFX, _T("[NFP4_EOR]"), m_NFP4_EOR);
	RFX_Text(pFX, _T("[NFP4_EPL]"), m_NFP4_EPL);
	RFX_Text(pFX, _T("[NFP4_HER]"), m_NFP4_HER);
	RFX_Text(pFX, _T("[NFP4_IDE]"), m_NFP4_IDE);
	RFX_Double(pFX, _T("[NFP4_TFL]"), m_NFP4_TFL);
	RFX_Double(pFX, _T("[NFP4_PN]"), m_NFP4_PN);
	RFX_Double(pFX, _T("[NFP4_PZ]"), m_NFP4_PZ);
	RFX_Long(pFX, _T("[NFP4_NR]"), m_NFP4_NR);
	RFX_Text(pFX, _T("[NFP4_KASS]"), m_NFP4_KASS);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG4 diagnostics

#ifdef _DEBUG
void CSetNF_PG4::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetNF_PG4::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


// CEigentuemer
CEigentuemer::CEigentuemer()
{
	m_NFP4_HER = "Y";
	m_NFP4_BDM = 0.0;
	m_NFP4_TFL = 0.0;
	m_NFP4_PN  = 1L;
	m_NFP4_PZ  = 1L;
	m_NFP4_NR  = 0L;
}

CEigentuemer::CEigentuemer( CEigentuemer* o )
{
	ASSERT( o );

	m_NFP4_BDM  = o -> m_NFP4_BDM;
	m_NFP4_EAN  = o -> m_NFP4_EAN;
	m_NFP4_ENA  = o -> m_NFP4_ENA;
	m_NFP4_EOR  = o -> m_NFP4_EOR;
	m_NFP4_EPL  = o -> m_NFP4_EPL;
	m_NFP4_HER  = o -> m_NFP4_HER;
	m_NFP4_IDE  = o -> m_NFP4_IDE;
	m_NFP4_TFL  = o -> m_NFP4_TFL;
	m_NFP4_PN   = o -> m_NFP4_PN;
	m_NFP4_PZ   = o -> m_NFP4_PZ;
	m_NFP4_NR   = o -> m_NFP4_NR;
	m_NFP4_KASS = o -> m_NFP4_KASS;
}

// CEigentuemerArray

BOOL CEigentuemerArray::Add( CEigentuemer* pS )
{
	BOOL    result = TRUE;
	int             n;

	TRY //Für eventuelle Fehler (Speicherplatz)
	{
		n = CObArray::Add(pS);
	}
	CATCH(CMemoryException,e)
	{
		result = FALSE;
		delete pS;
	}
	END_CATCH

	return result;
}	// Add

void CEigentuemerArray::Remove( const char* nr )
{
	ASSERT( nr );
	ASSERT( AfxIsValidString( nr ));

	CString text;
	char    *txt;
	double  id = 0;

	text = nr;
	txt = text.GetBuffer( 0 );
	while ( *txt && ( *txt != ' ' ))		txt++;
	if ( *txt )		id = atoi( ++txt ) - 1;
	text.ReleaseBuffer();

	if (( id >= 0 ) && ( id < GetSize()))
	{
		delete (CEigentuemer*) GetAt( id );
		CObArray::RemoveAt( id );
	}

}	// Remove

void CEigentuemerArray::Clear()
{
	for ( short i = 0; i < GetSize(); i++ )
		delete (CEigentuemer*) GetAt( i );
	CObArray::RemoveAll();
}

const CEigentuemerArray& CEigentuemerArray::operator = ( const CEigentuemerArray &o )
{
	CEigentuemer	*pS;

	Clear();
	for ( short i = 0; i < o.GetSize(); i++ )
	{
		pS = new CEigentuemer((CEigentuemer*)o.GetAt( i ));
		Add( pS );
	}

	return *this;
}	// operator =

void CSetNF_PG4::InitArray( const char *id, CEigentuemerArray *array )
{
	CxString	filter, oldFilter;
	BOOL		bOpened = FALSE;

	filter = "NFP4_IDE = '";
	filter += id;
	filter += "'";
	oldFilter = m_strFilter;
	m_strFilter = filter;

	if ( !IsOpen())
	{
		Open();
		bOpened = TRUE;
	}
	else
	{
		Close();
		Open();
	}

	ASSERT( AfxIsValidString( id ));
	CString		test, txt = id;
	if ( txt.GetLength() < 2 )	return;
	CEigentuemer	*pS;

	array -> Clear();
	while ( !IsEOF() && ( m_NFP4_IDE == id ))
	{
		pS = new CEigentuemer;
		if ( pS )
		{
			pS -> m_NFP4_KASS = m_NFP4_KASS;
			pS -> m_NFP4_EAN  = m_NFP4_EAN;
			pS -> m_NFP4_ENA  = m_NFP4_ENA;
			pS -> m_NFP4_EOR  = m_NFP4_EOR;
			pS -> m_NFP4_EPL  = m_NFP4_EPL;
			pS -> m_NFP4_HER  = m_NFP4_HER;
			if ( !IsDoubleOK( m_NFP4_PN ))		pS -> m_NFP4_PN = 0L;
			else								pS -> m_NFP4_PN = long( m_NFP4_PN );
			if ( !IsDoubleOK( m_NFP4_PZ ))		pS -> m_NFP4_PZ = 0L;
			else								pS -> m_NFP4_PZ = long( m_NFP4_PZ );
			if ( !IsDoubleOK( m_NFP4_BDM ))		pS -> m_NFP4_BDM = 0.0;
			else								pS -> m_NFP4_BDM = m_NFP4_BDM;
			if ( !IsDoubleOK( m_NFP4_TFL ))		pS -> m_NFP4_TFL = 0.0;
			else								pS -> m_NFP4_TFL = m_NFP4_TFL;
			pS -> m_NFP4_NR  = m_NFP4_NR;

			array -> Add( pS );
		}
		MoveNext();
	}

	m_strFilter = oldFilter;
	if ( bOpened )	Close();
	else
	{
		Close();
		Open();
	}
}

void CSetNF_PG4::RewriteArray( const char* ide, CEigentuemerArray* array )
{
	CxString		filter, oldFilter, test, nr;
	BOOL			bOpened = FALSE;
	BOOL			bAdded;
	CEigentuemer	*pS;

	TRY {
		if ( !IsOpen())
		{
			Open();
			bOpened = TRUE;
		}
		oldFilter = m_strFilter;

		filter = "(NFP4_IDE = '";
		filter += ide;
		filter += "')";

		m_strFilter = filter;
		Requery();

		for ( short i = 0; i < array -> GetSize(); i++ )
		{
			pS = (CEigentuemer*)array -> GetAt( i );

			if ( bAdded = IsEOF())	AddNew();
			else					Edit();

			m_NFP4_IDE = ide;

			m_NFP4_EAN  = pS -> m_NFP4_EAN;
			m_NFP4_ENA  = pS -> m_NFP4_ENA;
			m_NFP4_EOR  = pS -> m_NFP4_EOR;
			m_NFP4_EPL  = pS -> m_NFP4_EPL;
			m_NFP4_PN   = pS -> m_NFP4_PN;
			m_NFP4_PZ   = pS -> m_NFP4_PZ;
			m_NFP4_BDM  = pS -> m_NFP4_BDM;
			m_NFP4_TFL  = pS -> m_NFP4_TFL;
			m_NFP4_NR   = pS -> m_NFP4_NR;
			m_NFP4_KASS = pS -> m_NFP4_KASS;

//			m_NFP4_HER = pS -> m_NFP4_HER;
			if ( TestYES( pS -> m_NFP4_HER ))		test = "Y";
			else									test = "N";
			m_NFP4_HER = test;

			Update();
			if ( !bAdded )		MoveNext();
		}

		m_strFilter = oldFilter;
		if ( bOpened )	Close();
		else
		{
//			Requery();
			Close();
			Open();
		}
	}
	CATCH(CDBException, e)
	{
		AfxFormatString2( test, IDS_DBERROR,
			e -> m_strError, e -> m_strStateNativeOrigin );
		AfxMessageBox( test );
	}
	CATCH(CMemoryException, e)
	{
		AfxMessageBox( g_cbMemoryException );
	}
	END_CATCH
}

BOOL CSetNF_PG4::ModIDE( const char* alt, const char* neu )
{
	CString		text, init, oldFilter;
	BOOL		result = FALSE;
	BOOL		opened = FALSE;

	ASSERT( AfxIsValidString( alt ));
	ASSERT( AfxIsValidString( neu ));
	init = neu;
	if ( init.GetLength() > 2 )
		init = init.Left( 2 );

//	InitListen( init );

	oldFilter = m_strFilter;
	m_strFilter = "( NFP4_IDE = '";
	m_strFilter += alt;
	m_strFilter += "' )";
	if ( opened = !IsOpen())	Open();
	else						Requery();

	while ( !IsEOF())
	{
		Edit();
		m_NFP4_IDE = neu;
		Update();

		MoveNext();
	}

	m_strFilter = oldFilter;
	if ( opened )	Close();
	else			Requery();

//	m_bInitialisiert = FALSE;
//	InitListen( init );

	return TRUE;
}

bool CSetNF_PG4::Find( const char* ide )
{
	CString		filter;
	bool		result = false;

	ASSERT( AfxIsValidString( ide ));

	filter = "(NFP4_IDE = '";
	filter += ide;
	filter += "')";
	m_strFilter = filter;
	if ( IsOpen())
		Requery();
	else
		Open();

	if ( !IsEOF())
		result = true;

	return result;
}

void CSetNF_PG4::TestPrintIDE( CStringArray* array )
{
	CStringArray	temp;
	CString			filter, oldFilter;
	CString			ide;
	CxString		kenn;
	int				i;

	if ( array -> GetSize() == 0 )		return;

	if ( !IsOpen())		Open();

	for ( i = 0; i < array -> GetSize(); i++ )
	{
		ide = array -> GetAt( i );

		filter = "( NFP4_IDE = '";
		filter += ide;
		filter += "')";
		m_strFilter = filter;
		Requery();

		while ( !IsEOF())
		{
			if ( TestYES( m_NFP4_HER ))
			{
				kenn = "(";
				kenn.AppendF( m_NFP4_NR, -1 );
				kenn += ")";
				kenn += m_NFP4_IDE;
				temp.Add( kenn );
			}
			MoveNext();
		}
	}

	array -> RemoveAll();
	for ( i = 0; i < temp.GetSize(); i++ )
		array -> Add( temp[i]);
}

CEigentuemer* CSetNF_PG4::FindEigentuemer( const char* ide, long nr )
{
	CxString	filter, oldFilter;
	BOOL		bOpened = FALSE;

	filter = "(NFP4_IDE = '";
	filter += ide;
	filter += "') AND (NFP4_NR = ";
	filter.AppendF( nr, -1 );
	filter += ")";
	oldFilter = m_strFilter;
	m_strFilter = filter;

	if ( !IsOpen())
	{
		Open();
		bOpened = TRUE;
	}
	else
	{
		Close();
		Open();
	}

	ASSERT( AfxIsValidString( ide ));
	CString		test, txt = ide;
	if ( txt.GetLength() < 2 )	return NULL;
	CEigentuemer	*pS;

	if ( !IsEOF() && ( m_NFP4_IDE == ide ))
	{
		pS = new CEigentuemer;
		if ( pS )
		{
			pS -> m_NFP4_KASS = m_NFP4_KASS;
			pS -> m_NFP4_EAN  = m_NFP4_EAN;
			pS -> m_NFP4_ENA  = m_NFP4_ENA;
			pS -> m_NFP4_EOR  = m_NFP4_EOR;
			pS -> m_NFP4_EPL  = m_NFP4_EPL;
			pS -> m_NFP4_HER  = m_NFP4_HER;
			if ( !IsDoubleOK( m_NFP4_PN ))		pS -> m_NFP4_PN = 0L;
			else								pS -> m_NFP4_PN = long( m_NFP4_PN );
			if ( !IsDoubleOK( m_NFP4_PZ ))		pS -> m_NFP4_PZ = 0L;
			else								pS -> m_NFP4_PZ = long( m_NFP4_PZ );
			if ( !IsDoubleOK( m_NFP4_BDM ))		pS -> m_NFP4_BDM = 0.0;
			else								pS -> m_NFP4_BDM = m_NFP4_BDM;
			if ( !IsDoubleOK( m_NFP4_TFL ))		pS -> m_NFP4_TFL = 0.0;
			else								pS -> m_NFP4_TFL = m_NFP4_TFL;
			pS -> m_NFP4_NR  = m_NFP4_NR;
		}
	}

	m_strFilter = oldFilter;
	if ( bOpened )	Close();
	else
	{
		Close();
		Open();
	}

	return pS;
}
