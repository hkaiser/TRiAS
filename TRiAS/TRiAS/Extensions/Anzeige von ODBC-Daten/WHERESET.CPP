// WhereSet.cpp : implementation file
//

#include "pheader.h"
#include "odbcext.hr"		//	prec. Header

#include "odbcext.h"
#include "WhereSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWhereSet

IMPLEMENT_DYNAMIC(CWhereSet, CRecordset)

CWhereSet::CWhereSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CWhereSet)
	m_Ident = _T("");
	m_Ident2 = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}

CString CWhereSet::GetDefaultConnect()
{
	return _T("ODBC;DSN=TEST_BAHN");
}

CString CWhereSet::GetDefaultSQL()
{
	ASSERT (FALSE);
	return _T("[Tabelle1],[Tabelle2]");
}

void CWhereSet::DoFieldExchange(CFieldExchange* pFX)
{
	ASSERT (!m_strField1.IsEmpty ());
	
	//{{AFX_FIELD_MAP(CWhereSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, m_strField1, m_Ident);

	if (m_nFields == 2)
	{
		ASSERT (!m_strField2.IsEmpty ());
		RFX_Text(pFX, m_strField2, m_Ident2);
	}
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CWhereSet diagnostics

#ifdef _DEBUG
void CWhereSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CWhereSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
