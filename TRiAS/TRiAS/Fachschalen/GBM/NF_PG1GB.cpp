// NF_PG1GB.cpp : implementation file
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
// CSetNF_PG1GB

IMPLEMENT_DYNAMIC(CSetNF_PG1GB, CRecordset)

CSetNF_PG1GB::CSetNF_PG1GB(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetNF_PG1GB)
	m_NFP1_IDE = _T("");
	m_NFP1_GNR = 0.0;
	m_NFP1_GFL = 0.0;
	m_NFP1_VOL = 0.0;
	m_NFP1_HOH = 0.0;
	m_NFP1_ANL = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
//	m_nDefaultType = dynaset;
	m_nDefaultType = snapshot;
	m_strSort = "NFP1_IDE";
}

CSetNF_PG1GB::~CSetNF_PG1GB()
{
	if ( IsOpen())		Close();
}

CString CSetNF_PG1GB::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetNF_PG1GB::GetDefaultSQL()
{
	return _T("[NF_PG1GB]");
}

void CSetNF_PG1GB::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetNF_PG1GB)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NFP1_IDE]"), m_NFP1_IDE);
	RFX_Double(pFX, _T("[NFP1_GNR]"), m_NFP1_GNR);
	RFX_Double(pFX, _T("[NFP1_GFL]"), m_NFP1_GFL);
	RFX_Double(pFX, _T("[NFP1_VOL]"), m_NFP1_VOL);
	RFX_Double(pFX, _T("[NFP1_HOH]"), m_NFP1_HOH);
	RFX_Text(pFX, _T("[NFP1_ANL]"), m_NFP1_ANL);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG1GB diagnostics

#ifdef _DEBUG
void CSetNF_PG1GB::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetNF_PG1GB::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

void CSetNF_PG1GB::InitListen( const char* id )
{
	if ( !IsOpen())		Open();
	else				Requery();
}	// InitListen

void CSetNF_PG1GB::InitArray( const char* id, CPG1GBArray* array )
{
	CxString	filter, oldFilter;
	BOOL		bOpened = FALSE;

	filter = "NFP1_IDE = '";
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
	CPG1GBSatz	*pS;

	array -> Clear();
//	while ( !IsEOF() && ( m_NFP1_IDE != id ))	MoveNext();
	while ( !IsEOF() && ( m_NFP1_IDE == id ))
	{
		pS = new CPG1GBSatz;
		if ( pS )
		{
			pS -> m_NFP1_IDE = m_NFP1_IDE;
			pS -> m_NFP1_GNR = m_NFP1_GNR;
//			pS -> m_NFP1_GFL = m_NFP1_GFL;
//			if ( IsFieldNull( &m_NFP1_GFL ))	pS -> m_NFP1_GFL = 0;
			if ( !IsDoubleOK( m_NFP1_GFL ))		pS -> m_NFP1_GFL = 0;
			else								pS -> m_NFP1_GFL = m_NFP1_GFL;
//			pS -> m_NFP1_HOH = m_NFP1_HOH;
//			if ( IsFieldNull( &m_NFP1_HOH ))	pS -> m_NFP1_HOH = 0;
			if ( !IsDoubleOK( m_NFP1_HOH ))		pS -> m_NFP1_HOH = 0;
			else								pS -> m_NFP1_HOH = m_NFP1_HOH;
//			pS -> m_NFP1_VOL = m_NFP1_VOL;
//			if ( IsFieldNull( &m_NFP1_VOL ))	pS -> m_NFP1_VOL = 0;
			if ( !IsDoubleOK( m_NFP1_VOL ))		pS -> m_NFP1_VOL = 0;
			else								pS -> m_NFP1_VOL = m_NFP1_VOL;
//			pS -> m_NFP1_ANL = m_NFP1_ANL;
			if ( TestYES( m_NFP1_ANL ))		test = "Y";
			else							test = "N";
			pS -> m_NFP1_ANL = test;

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
	double	idx, jdx;
	// noch schnell sortieren
	for ( i = 0; i < array -> GetSize() - 1; i++ )
		for ( j = i + 1; j < array -> GetSize(); j++ )
		{
			idx = ((CPG1GBSatz*)array -> GetAt(i)) -> m_NFP1_GNR;
			jdx = ((CPG1GBSatz*)array -> GetAt(j)) -> m_NFP1_GNR;
			if ( idx > jdx )
			{
				pS = (CPG1GBSatz*)array -> GetAt(j);
				array -> SetAt( j, array -> GetAt(i));
				array -> SetAt( i, pS );
		}	}
}	// InitArray



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	CPG1GBArray

BOOL CPG1GBArray :: Add( CPG1GBSatz *pS )
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

void CPG1GBArray :: Clear()
{
	for ( short i = 0; i < GetSize(); i++ )
		delete (CPG1GBSatz*) GetAt( i );
	CObArray::RemoveAll();
}       // Clear

void CPG1GBArray :: Remove( const char *nr )
{
	ASSERT( nr );
	ASSERT( AfxIsValidString( nr ));

	CString text;
	char    *txt;
	double  id = 0;

	text = nr;
	txt = text.GetBuffer( 0 );
	while ( *txt && ( *txt != ' ' ))		txt++;
	if ( *txt )		id = atoi( ++txt );
	text.ReleaseBuffer();

	for ( short i = 0; i < GetSize(); i++ )
	{
		if (((CPG1GBSatz*) GetAt( i )) -> m_NFP1_GNR == id )
		{
			delete (CPG1GBSatz*) GetAt( i );
			CObArray::RemoveAt( i );
			break;
		}
	}

}	// Remove

const CPG1GBArray&  CPG1GBArray :: operator = ( const CPG1GBArray &o )
{
	CPG1GBSatz      *pS;

	Clear();
	for ( short i = 0; i < o.GetSize(); i++ )
	{
		pS = new CPG1GBSatz((CPG1GBSatz*)o.GetAt( i ));
		Add( pS );
	}

	return *this;
}	// operator =

// Summe über NFP1_GFL bei (NFP1_ANL == "Y")
double CPG1GBArray::GFL()
{
	CPG1GBSatz	*pS;
	double		result = 0;

	for ( short i = 0; i < GetSize(); i++ )
	{
		pS = (CPG1GBSatz*) GetAt( i );
		if ( TestYES( pS -> m_NFP1_ANL ))
			result += pS -> m_NFP1_GFL;
	}
	return result;
}

// Max aus NFP1_VOL bei  (NFP1_ANL == "Y")
double CPG1GBArray::VOL()
{
	CPG1GBSatz	*pS;
	double		result = 0;

	for ( short i = 0; i < GetSize(); i++ )
	{
		pS = (CPG1GBSatz*) GetAt( i );
		if ( TestYES( pS -> m_NFP1_ANL ))
			result += pS -> m_NFP1_VOL;
	}
	return result;
}

CPG1GBSatz :: CPG1GBSatz( CPG1GBSatz *o )
{
	m_NFP1_IDE = o -> m_NFP1_IDE;
	m_NFP1_GNR = o -> m_NFP1_GNR;
	m_NFP1_GFL = o -> m_NFP1_GFL;
	m_NFP1_VOL = o -> m_NFP1_VOL;
	m_NFP1_HOH = o -> m_NFP1_HOH;
	m_NFP1_ANL = o -> m_NFP1_ANL;
}	// Copy-Konstruktor



/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//	CPG2DArray

BOOL CPG2DArray :: Add( CPG2DSatz *pS )
{
	BOOL	result = TRUE;
	int		n;

	TRY		//Für eventuelle Fehler (Speicherplatz)
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

void CPG2DArray :: Clear()
{
	for ( short i = 0; i < GetSize(); i++ )
		delete (CPG2DSatz*) GetAt( i );
	CObArray::RemoveAll();
}	// Clear

void CPG2DArray :: Remove( const char *nr )
{
	ASSERT( nr );
	ASSERT( AfxIsValidString( nr ));

	for ( short i = 0; i < GetSize(); i++ )
	{
		if (((CPG2DSatz*) GetAt( i )) -> m_NFP2_FLN == nr )
		{
			delete (CPG2DSatz*) GetAt( i );
			CObArray::RemoveAt( i );
			break;
		}
	}

}	// Remove

const CPG2DArray&  CPG2DArray :: operator = ( const CPG2DArray &o )
{
	CPG2DSatz		*pS;

	Clear();
	for ( short i = 0; i < o.GetSize(); i++ )
	{
		pS = new CPG2DSatz( (CPG2DSatz*)o.GetAt( i ));
		Add( pS );
	}

	return *this;
}	// operator =

CPG2DSatz :: CPG2DSatz( CPG2DSatz *o )
{
	m_NFP2_IDE = o -> m_NFP2_IDE;
	m_NFP2_FLN = o -> m_NFP2_FLN;
	m_NFP2_FLG = o -> m_NFP2_FLG;
	m_NFP2_ABF = o -> m_NFP2_ABF;
	m_NFP2_ANS = o -> m_NFP2_ANS;
}	// Copy-Konstruktor

void CSetNF_PG1GB::RewriteArray( const char* ide, CPG1GBArray* array )
{
	CxString	filter, oldFilter, test, nr;
	BOOL		bOpened = FALSE;
	CPG1GBSatz	*pS;

	TRY {
		if ( !IsOpen())
		{
			Open();
			bOpened = TRUE;
		}
		oldFilter = m_strFilter;

		for ( short i = 0; i < array -> GetSize(); i++ )
		{
			pS = (CPG1GBSatz*)array -> GetAt( i );

			filter = "(NFP1_IDE = '";
			filter += ide;
			filter += "') AND (NFP1_GNR = ";
			filter.AppendF( pS -> m_NFP1_GNR, -1, 0 );
			filter += ")";

			m_strFilter = filter;
			Requery();

			if ( IsEOF())	AddNew();
			else			Edit();

			m_NFP1_IDE = ide;
			m_NFP1_GNR = pS -> m_NFP1_GNR;
			m_NFP1_GFL = pS -> m_NFP1_GFL;
			m_NFP1_HOH = pS -> m_NFP1_HOH;
			m_NFP1_VOL = pS -> m_NFP1_VOL;
//			m_NFP1_ANL = pS -> m_NFP1_ANL;
			if ( TestYES( pS -> m_NFP1_ANL ))		test = "Y";
			else									test = "N";
			m_NFP1_ANL = test;

			Update();

			nr.Empty();		nr.AppendF( pS -> m_NFP1_GNR, -1, 0 );
			g_pOPAngeschlGS -> SetName( ide, nr, 'G', ( test == "Y" ));
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

BOOL CSetNF_PG1GB::ModIDE( const char* alt, const char* neu )
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
	m_strFilter = "( NFP1_IDE = '";
	m_strFilter += alt;
	m_strFilter += "' )";
	if ( opened = !IsOpen())	Open();
	else						Requery();

	while ( !IsEOF())
	{
		Edit();
		m_NFP1_IDE = neu;
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

void CSetNF_PG1GB::DeleteIDE( const char* ide )
{
	ASSERT( ide != NULL );
	ASSERT( *ide != '\0' );

	if (( ide == NULL ) || ( *ide == '\0' ))	return;

	CString		sql;

	sql = "DELETE FROM NF_PG1GB WHERE (NFP1_IDE = '";
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

BOOL CSetNF_PG1GB::IstAngeschlossen( const char* ide, const char* nr )
{
	CxString	filter, oldFilter, text;
	BOOL		result = FALSE;

	filter = "(NFP1_IDE = '";
	filter += ide;
	filter += "') AND (NFP1_GNR = ";
	filter += nr;
	filter += ")";
	oldFilter = m_strFilter;
	m_strFilter = filter;

	TRY {
		if ( !IsOpen())		Open();
		else				Requery();

		if ( !IsEOF())
		{
//			text = m_NFP1_ANL;
//			text.MakeUpper();
//			result = ( text != "N" );
			result = TestYES( m_NFP1_ANL );
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

long CSetNF_PG1GB::GetCount()
{
	long	result = 0L;
	SDWORD	n;

	SQLRETURN	status;
	HSTMT		hSTMT = NULL;
	CString		request, text;

	if ( SQL_SUCCESS != ::SQLAllocStmt( m_pDatabase -> m_hdbc, &hSTMT ))
	{
		text = "Fehler in NF_PG1GB::GetCount()";
		AfxMessageBox( text );
		goto cleanup;
	}

	request = "SELECT Count(*) FROM NF_PG1GB";
	status = ::SQLExecDirect( hSTMT, (UCHAR FAR *)(const char*)request, request.GetLength());
	if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
	{
		text = "Fehler in NF_PG1GB::GetCount()";
		AfxMessageBox( text );
		goto cleanup;
	}

	status = ::SQLBindCol( hSTMT, 1, SQL_C_LONG, &result, sizeof(long), &n );
	if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
	{
		text = "Fehler in NF_PG1GB::GetCount()";
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
		text = "Fehler in NF_PG1GB::GetCount()";
		AfxMessageBox( text );
	}

cleanup:
	if ( hSTMT )
	{
		status = ::SQLFreeStmt( hSTMT, SQL_CLOSE );
		if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
		{
			text = "Fehler in NF_PG1GB::GetCount()\nSQLFreeStmt( hSTMT, SQL_CLOSE ) fehlgeschlagen!";
			AfxMessageBox( text );
		}

		status = ::SQLFreeStmt( hSTMT, SQL_DROP );
		if (( SQL_SUCCESS != status ) && ( SQL_SUCCESS_WITH_INFO != status ))
		{
			text = "Fehler in NF_PG1GB::GetCount()\nSQLFreeStmt( hSTMT, SQL_DROP ) fehlgeschlagen!";
			AfxMessageBox( text );
		}
		hSTMT = NULL;
	}

	return result;
}
