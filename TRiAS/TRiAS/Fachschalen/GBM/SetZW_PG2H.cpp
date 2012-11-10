// SetZW_PG2H.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetZW_PG2H.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetZW_PG2H

IMPLEMENT_DYNAMIC(CSetZW_PG2H, CRecordset)

CSetZW_PG2H::CSetZW_PG2H(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetZW_PG2H)
	m_NFP2_IDE = _T("");
	m_NFP2_FLN = _T("");
	m_NFP2_FLG = 0.0;
	m_NFP2_ABF = 0.0;
	m_NFP2_ANS = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strSort = "NFP2_IDE";
}


CString CSetZW_PG2H::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetZW_PG2H::GetDefaultSQL()
{
	return _T("[ZW_PG2H]");
}

void CSetZW_PG2H::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetZW_PG2H)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NFP2_IDE]"), m_NFP2_IDE);
	RFX_Text(pFX, _T("[NFP2_FLN]"), m_NFP2_FLN);
	RFX_Double(pFX, _T("[NFP2_FLG]"), m_NFP2_FLG);
	RFX_Double(pFX, _T("[NFP2_ABF]"), m_NFP2_ABF);
	RFX_Text(pFX, _T("[NFP2_ANS]"), m_NFP2_ANS);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetZW_PG2H diagnostics

#ifdef _DEBUG
void CSetZW_PG2H::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetZW_PG2H::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
