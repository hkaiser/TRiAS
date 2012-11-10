// VerzSet2.cpp : implementation file
//

#include <bool.h>
#include "stdafx.h"
#include "GbmTRiAS.h"
#include "VerzSet2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVerzSet2

IMPLEMENT_DYNAMIC(CVerzSet2, CRecordset)

CVerzSet2::CVerzSet2(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CVerzSet2)
	m_TRIDB_NR = _T("");
	m_TRIDB_VZ = _T("");
	m_TRIDB_BZ = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CVerzSet2::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CVerzSet2::GetDefaultSQL()
{
	return _T("[VERZ]");
}

void CVerzSet2::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CVerzSet2)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[TRIDB_NR]"), m_TRIDB_NR);
	RFX_Text(pFX, _T("[TRIDB_VZ]"), m_TRIDB_VZ);
	RFX_Text(pFX, _T("[TRIDB_BZ]"), m_TRIDB_BZ);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CVerzSet2 diagnostics

#ifdef _DEBUG
void CVerzSet2::AssertValid() const
{
	CRecordset::AssertValid();
}

void CVerzSet2::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
