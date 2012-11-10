// SetZW_PG1GB.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetZW_PG1GB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetZW_PG1GB

IMPLEMENT_DYNAMIC(CSetZW_PG1GB, CRecordset)

CSetZW_PG1GB::CSetZW_PG1GB(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetZW_PG1GB)
	m_NFP1_IDE = _T("");
	m_NFP1_GNR = 0.0;
	m_NFP1_GFL = 0.0;
	m_NFP1_VOL = 0.0;
	m_NFP1_HOH = 0.0;
	m_NFP1_ANL = _T("");
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strSort = "NFP1_IDE";
}


CString CSetZW_PG1GB::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetZW_PG1GB::GetDefaultSQL()
{
	return _T("[ZW_PG1GB]");
}

void CSetZW_PG1GB::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetZW_PG1GB)
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
// CSetZW_PG1GB diagnostics

#ifdef _DEBUG
void CSetZW_PG1GB::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetZW_PG1GB::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
