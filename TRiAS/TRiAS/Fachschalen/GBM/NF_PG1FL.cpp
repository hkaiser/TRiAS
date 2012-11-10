// NF_PG1FL.cpp : implementation file
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
// CSetNF_PG1FL

IMPLEMENT_DYNAMIC(CSetNF_PG1FL, CRecordset)

CSetNF_PG1FL::CSetNF_PG1FL(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetNF_PG1FL)
	m_NFP1_IDE = _T("");
	m_NFP1_FST = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
//	m_nDefaultType = dynaset;
	m_nDefaultType = snapshot;
	m_strSort = "NFP1_IDE";
}


CString CSetNF_PG1FL::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetNF_PG1FL::GetDefaultSQL()
{
	return _T("[NF_PG1FL]");
}

void CSetNF_PG1FL::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetNF_PG1FL)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NFP1_IDE]"), m_NFP1_IDE);
	RFX_Text(pFX, _T("[NFP1_FST]"), m_NFP1_FST);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetNF_PG1FL diagnostics

#ifdef _DEBUG
void CSetNF_PG1FL::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetNF_PG1FL::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CSetNF_PG1FL::ModIDE( const char* alt, const char* neu )
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
//	InitListen( init );

	return TRUE;
}

void CSetNF_PG1FL::DeleteIDE( const char* ide )
{
	ASSERT( ide != NULL );
	ASSERT( *ide != '\0' );

	if (( ide == NULL ) || ( *ide == '\0' ))	return;

	CString		sql;

	sql = "DELETE FROM NF_PG1FL WHERE (NFP1_IDE = '";
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
