// SetSI.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetSI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetStrIndex

IMPLEMENT_DYNAMIC(CSetStrIndex, CRecordset)

CSetStrIndex::CSetStrIndex(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetStrIndex)
	m_SCHL = _T("");
	m_LISTE = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetStrIndex::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetStrIndex::GetDefaultSQL()
{
	return _T("[STR_INDEX]");
}

void CSetStrIndex::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetStrIndex)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[SCHL]"), m_SCHL);
	RFX_Text(pFX, _T("[LISTE]"), m_LISTE);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetStrIndex diagnostics

#ifdef _DEBUG
void CSetStrIndex::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetStrIndex::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
