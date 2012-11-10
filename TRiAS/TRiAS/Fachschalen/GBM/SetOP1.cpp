// SetOP1.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetOP1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetOP1

IMPLEMENT_DYNAMIC(CSetOP1, CRecordset)

CSetOP1::CSetOP1(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetOP1)
	m_IDE = _T("");
	m_AGGS = 0.0;
	m_GEFS = 0.0;
	m_KAT = 0.0;
	m_TIEB = 0.0;
	m_TIEF = _T("");
	m_B_GEDR = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetOP1::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetOP1::GetDefaultSQL()
{
	return _T("[NF_PG1]");
}

void CSetOP1::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetOP1)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NFP1_IDE]"), m_IDE);
	RFX_Double(pFX, _T("[NFP1_AGGS]"), m_AGGS);
	RFX_Double(pFX, _T("[NFP1_GEFS]"), m_GEFS);
	RFX_Double(pFX, _T("[NFP1_KAT]"), m_KAT);
	RFX_Double(pFX, _T("[NFP1_TIEB]"), m_TIEB);
	RFX_Text(pFX, _T("[NFP1_TIEF]"), m_TIEF);
	RFX_Text(pFX, _T("[B_GEDR]"), m_B_GEDR);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetOP1 diagnostics

#ifdef _DEBUG
void CSetOP1::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOP1::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CSetOP1::SelectONr( long onr )
{
	BOOL	result = FALSE;

	CString		ide;
	
	if ( IDEfromONr( onr, ide ))
		if ( !ide.IsEmpty())
	{
		if ( IsOpen())
			if ( m_IDE == ide )		return TRUE;

		m_strFilter = "NFP1_IDE = '";
		m_strFilter += ide;
		m_strFilter += "'";
		if ( !IsOpen())		Open();
		else				Requery();
		if ( !IsEOF())		result = TRUE;
	}

	return result;
}
