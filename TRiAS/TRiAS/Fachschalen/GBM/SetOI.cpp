// SetOI.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetOI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetOrtIndex

IMPLEMENT_DYNAMIC(CSetOrtIndex, CRecordset)

CSetOrtIndex::CSetOrtIndex(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetOrtIndex)
	m_SCHL = _T("");
	m_LISTE = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetOrtIndex::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetOrtIndex::GetDefaultSQL()
{
	return _T("[ORT_INDEX]");
}

void CSetOrtIndex::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetOrtIndex)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[SCHL]"), m_SCHL);
	RFX_Text(pFX, _T("[LISTE]"), m_LISTE);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetOrtIndex diagnostics

#ifdef _DEBUG
void CSetOrtIndex::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOrtIndex::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
