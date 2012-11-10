// SetOP2.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetOP2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetOP2

IMPLEMENT_DYNAMIC(CSetOP2, CRecordset)

CSetOP2::CSetOP2(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetOP2)
	m_IDE = _T("");
	m_GFL = 0.0;
	m_GNR = 0.0;
	m_ANL = _T("");
	m_HOH = 0.0;
	m_VOL = 0.0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_lFLN = 0L;
	m_nDefaultType = snapshot;
}


CString CSetOP2::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetOP2::GetDefaultSQL()
{
	return _T("[NF_PG1GB]");
}

void CSetOP2::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetOP2)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NFP1_IDE]"), m_IDE);
	RFX_Double(pFX, _T("[NFP1_GFL]"), m_GFL);
	RFX_Double(pFX, _T("[NFP1_GNR]"), m_GNR);
	RFX_Text(pFX, _T("[NFP1_ANL]"), m_ANL);
	RFX_Double(pFX, _T("[NFP1_HOH]"), m_HOH);
	RFX_Double(pFX, _T("[NFP1_VOL]"), m_VOL);
	//}}AFX_FIELD_MAP
	m_lFLN = (long)m_GNR;
}

BOOL CSetOP2::Update()
{
	m_GNR = (double)m_lFLN;
	return CRecordset::Update();
}

/////////////////////////////////////////////////////////////////////////////
// CSetOP2 diagnostics

#ifdef _DEBUG
void CSetOP2::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOP2::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CSetOP2::SelectONr( long onr )
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
