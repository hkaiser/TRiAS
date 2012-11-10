// NF_PG2D.cpp : implementation file
//

#include <bool.h>
#include "stdafx.h"
#include "GbmTRiAS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern COPAngeschlGS* g_pOPAngeschlGS;

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG2D

IMPLEMENT_DYNAMIC(CSetNF_PG2D, CRecordset)

CSetNF_PG2D::CSetNF_PG2D(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetNF_PG2D)
	m_NFP2_IDE = _T("");
	m_NFP2_FLN = _T("");
	m_NFP2_FLG = 0.0;
	m_NFP2_ABF = 0.0;
	m_NFP2_ANS = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
//	m_nDefaultType = dynaset;
	m_nDefaultType = snapshot;
	m_strSort = "NFP2_IDE";
}

CSetNF_PG2D::~CSetNF_PG2D()
{
	if ( IsOpen())		Close();
}

CString CSetNF_PG2D::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetNF_PG2D::GetDefaultSQL()
{
	return _T("[NF_PG2D]");
}

void CSetNF_PG2D::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetNF_PG2D)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NFP2_IDE]"), m_NFP2_IDE);
	RFX_Text(pFX, _T("[NFP2_FLN]"), m_NFP2_FLN);
	RFX_Double(pFX, _T("[NFP2_FLG]"), m_NFP2_FLG);
	RFX_Double(pFX, _T("[NFP2_ABF]"), m_NFP2_ABF);
	RFX_Text(pFX, _T("[NFP2_ANS]"), m_NFP2_ANS);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG2D diagnostics

#ifdef _DEBUG
void CSetNF_PG2D::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetNF_PG2D::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CSetNF_PG2D::InitListen( const char* id )
{
	if ( !IsOpen())		Open();
	else				Requery();
}	// InitListen

void CSetNF_PG2D::InitArray( const char* id, CPG2DArray* array )
{
	CxString	filter, oldFilter;
	BOOL		bOpened = FALSE;

	filter = "NFP2_IDE = '";
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
//		Requery();
		Close();
		Open();
	}

	ASSERT( AfxIsValidString( id ));
	CString		test, txt = id;
	if ( txt.GetLength() < 2 )	return;
	CPG2DSatz	*pS;

	array -> Clear();
//	while ( !IsEOF() && ( m_NFP2_IDE != id ))	MoveNext();
	while ( !IsEOF() && ( m_NFP2_IDE == id ))
	{
		pS = new CPG2DSatz;
		if ( pS )
		{
			pS -> m_NFP2_IDE = m_NFP2_IDE;
			pS -> m_NFP2_FLN = m_NFP2_FLN;
//			pS -> m_NFP2_FLG = m_NFP2_FLG;
//			if ( IsFieldNull( &m_NFP2_FLG ))	pS -> m_NFP2_FLG = 0;
			if ( !IsDoubleOK( m_NFP2_FLG ))		pS -> m_NFP2_FLG = 0;
			else								pS -> m_NFP2_FLG = m_NFP2_FLG;
//			pS -> m_NFP2_ABF = m_NFP2_ABF;
//			if ( IsFieldNull( &m_NFP2_ABF ))	pS -> m_NFP2_ABF = 0;
			if ( !IsDoubleOK( m_NFP2_ABF ))		pS -> m_NFP2_ABF = 0;
			else								pS -> m_NFP2_ABF = m_NFP2_ABF;
//			pS -> m_NFP2_ANS = m_NFP2_ANS;
			if ( TestYES( m_NFP2_ANS ))		pS -> m_NFP2_ANS = "Y";
			else							pS -> m_NFP2_ANS = "N";

			array -> Add( pS );
		}
		MoveNext();
	}

	m_strFilter = oldFilter;
	if ( bOpened )	Close();
	else
	{
//		Requery();
		Close();
		Open();
	}

	short	i, j;
	int		idx, jdx;
	// noch schnell sortieren
	for ( i = 0; i < array -> GetSize() - 1; i++ )
		for ( j = i + 1; j < array -> GetSize(); j++ )
		{
			idx = atoi( ((CPG2DSatz*)array -> GetAt(i)) -> m_NFP2_FLN.Mid( 1 ));
			jdx = atoi( ((CPG2DSatz*)array -> GetAt(j)) -> m_NFP2_FLN.Mid( 1 ));
			if ( idx > jdx )
			{
				pS = (CPG2DSatz*)array -> GetAt(j);
				array -> SetAt( j, array -> GetAt(i));
				array -> SetAt( i, pS );
		}	}
}	// InitArray

void CSetNF_PG2D::RewriteArray( CPG2DArray* array )
{
	CxString	filter, oldFilter, test;
	BOOL		bOpened = FALSE;
	CPG2DSatz	*pS;

	TRY {
		if ( !IsOpen())
		{
			Open();
			bOpened = TRUE;
		}
		oldFilter = m_strFilter;

		for ( short i = 0; i < array -> GetSize(); i++ )
		{
			pS = (CPG2DSatz*)array -> GetAt( i );

			filter = "(NFP2_IDE = '";
			filter += pS -> m_NFP2_IDE;
			filter += "') AND (NFP2_FLN = '";
			filter += pS -> m_NFP2_FLN;
			filter += "')";

			m_strFilter = filter;
			Requery();

			if ( IsEOF())	AddNew();
			else			Edit();

			m_NFP2_IDE = pS -> m_NFP2_IDE;
			m_NFP2_FLN = pS -> m_NFP2_FLN;
			m_NFP2_FLG = pS -> m_NFP2_FLG;
			m_NFP2_ABF = pS -> m_NFP2_ABF;
//			m_NFP2_ANS = pS -> m_NFP2_ANS;
			if ( TestYES( pS -> m_NFP2_ANS ))		m_NFP2_ANS = "Y";
			else									m_NFP2_ANS = "N";

			Update();

			g_pOPAngeschlGS -> SetName( pS -> m_NFP2_IDE, pS -> m_NFP2_FLN, 'D', ( test == "Y" ));
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

BOOL CSetNF_PG2D::ModIDE( const char* alt, const char* neu )
{
	CString		text, init, oldFilter;
	BOOL		result = FALSE;
	BOOL		opened = FALSE;

	ASSERT( AfxIsValidString( alt ));
	ASSERT( AfxIsValidString( neu ));
	init = neu;
	if ( init.GetLength() > 2 )
		init = init.Left( 2 );

	InitListen( init );

	oldFilter = m_strFilter;
	m_strFilter = "( NFP2_IDE = '";
	m_strFilter += alt;
	m_strFilter += "' )";
	if ( opened = !IsOpen())	Open();
	else						Requery();

	while ( !IsEOF())
	{
		Edit();
		m_NFP2_IDE = neu;
		Update();

		MoveNext();
	}

	m_strFilter = oldFilter;
	if ( opened )	Close();
	else			Requery();

//	m_bInitialisiert = FALSE;
	InitListen( init );

	return TRUE;
}

void CSetNF_PG2D::DeleteIDE( const char* ide )
{
	ASSERT( ide != NULL );
	ASSERT( *ide != '\0' );

	if (( ide == NULL ) || ( *ide == '\0' ))	return;

	CString		sql;

	sql = "DELETE FROM NF_PG2D WHERE (NFP2_IDE = '";
	sql += ide;
	sql += "')";

	TRY
	{
		m_pDatabase -> ExecuteSQL( sql );
	}
	CATCH(CDBException, e)
	{
		AfxFormatString2( sql, IDS_DBERROR,
			e -> m_strError, e -> m_strStateNativeOrigin );
		AfxMessageBox( sql );
	}
	END_CATCH
}

BOOL CSetNF_PG2D::IstAngeschlossen( const char* ide, const char* nr )
{
	CxString	filter, oldFilter, text;
	BOOL		result = FALSE;

	filter = "(NFP2_IDE = '";
	filter += ide;
	filter += "') AND (NFP2_FLN = 'D";
	filter += nr;
	filter += "')";
	oldFilter = m_strFilter;
	m_strFilter = filter;

	TRY {
		if ( !IsOpen())		Open();
		else				Requery();

		if ( !IsEOF())
		{
//			text = m_NFP2_ANS;
//			text.MakeUpper();
//			result = ( text != "N" );
			result = TestYES( m_NFP2_ANS );
		}

		m_strFilter = oldFilter;
		Requery();
	}
	CATCH(CDBException, e)
	{
		AfxFormatString2( text, IDS_DBERROR,
			e -> m_strError, e -> m_strStateNativeOrigin );
		AfxMessageBox( text );
	}
	CATCH(CMemoryException, e)
	{
		AfxMessageBox( g_cbMemoryException );
	}
	END_CATCH

	return result;
}

long CSetNF_PG2D::GetCount()
{
	long	result = 0L;
	SDWORD	n;

	SQLRETURN	status;
	HSTMT		hSTMT = NULL;
	CString		request, text;

	if ( SQL_SUCCESS != ::SQLAllocStmt( m_pDatabase -> m_hdbc, &hSTMT ))
	{
		text = "Fehler in NF_PG2D::GetCount()";
		AfxMessageBox( text );
		goto cleanup;
	}

	request = "SELECT Count(*) FROM NF_PG2D";
	status = ::SQLExecDirect( hSTMT, (UCHAR FAR *)(const char*)request, request.GetLength());
	if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
	{
		text = "Fehler in NF_PG2D::GetCount()";
		AfxMessageBox( text );
		goto cleanup;
	}

	status = ::SQLBindCol( hSTMT, 1, SQL_C_LONG, &result, sizeof(long), &n );
	if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
	{
		text = "Fehler in NF_PG2D::GetCount()";
		AfxMessageBox( text );
		goto cleanup;
	}

	status = ::SQLFetch( hSTMT );
	if ( status == SQL_NO_DATA_FOUND )
	{
		result = 0L;
	}
	else if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
	{
		text = "Fehler in NF_PG2D::GetCount()";
		AfxMessageBox( text );
	}

cleanup:
	if ( hSTMT )
	{
		status = ::SQLFreeStmt( hSTMT, SQL_CLOSE );
		if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
		{
			text = "Fehler in NF_PG2D::GetCount()\nSQLFreeStmt( hSTMT, SQL_CLOSE ) fehlgeschlagen!";
			AfxMessageBox( text );
		}

		status = ::SQLFreeStmt( hSTMT, SQL_DROP );
		if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
		{
			text = "Fehler in NF_PG2D::GetCount()\nSQLFreeStmt( hSTMT, SQL_DROP ) fehlgeschlagen!";
			AfxMessageBox( text );
		}
		hSTMT = NULL;
	}

	return result;
}
