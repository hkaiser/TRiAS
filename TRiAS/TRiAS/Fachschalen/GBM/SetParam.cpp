// SetParam.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetParam

IMPLEMENT_DYNAMIC(CSetParam, CRecordset)

CSetParam::CSetParam(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetParam)
	m_Global = FALSE;
	m_Tiefe = 0.0;
	m_AnrFl_speichern = FALSE;
	m_GesFl_berechnen = FALSE;
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetParam::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetParam::GetDefaultSQL()
{
	return _T("[PARAMETER]");
}

void CSetParam::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetParam)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Bool(pFX, _T("[Global]"), m_Global);
	RFX_Double(pFX, _T("[Tiefe]"), m_Tiefe);
	RFX_Bool(pFX, _T("[AnrFl_speichern]"), m_AnrFl_speichern);
	RFX_Bool(pFX, _T("[GesFl_berechnen]"), m_GesFl_berechnen);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetParam diagnostics

#ifdef _DEBUG
void CSetParam::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetParam::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
