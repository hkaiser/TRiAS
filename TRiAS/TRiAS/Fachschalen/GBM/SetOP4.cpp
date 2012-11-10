// SetOP4.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetOP4.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetOP4

IMPLEMENT_DYNAMIC(CSetOP4, CRecordset)

CSetOP4::CSetOP4(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetOP4)
	m_ABF = 0.0;
	m_ANS = _T("");
	m_FLG = 0.0;
	m_FLN = _T("");
	m_IDE = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetOP4::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetOP4::GetDefaultSQL()
{
	return _T("[NF_PG2H]");
}

void CSetOP4::DoFieldExchange(CFieldExchange* pFX)
{
	CxString	text;

	//{{AFX_FIELD_MAP(CSetOP4)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Double(pFX, _T("[NFP2_ABF]"), m_ABF);
	RFX_Text(pFX, _T("[NFP2_ANS]"), m_ANS);
	RFX_Double(pFX, _T("[NFP2_FLG]"), m_FLG);
	RFX_Text(pFX, _T("[NFP2_FLN]"), m_FLN);
	RFX_Text(pFX, _T("[NFP2_IDE]"), m_IDE);
	//}}AFX_FIELD_MAP
	if ( 1 < m_FLN.GetLength())
	{
		text = m_FLN.Mid( 2 );
		m_lFLN = text.Long();
	}
}

BOOL CSetOP4::Update()
{
	CxString	text;

	text = "V";
	text.AppendF( m_lFLN, -1 );
	m_FLN = text;
	return CRecordset::Update();
}

/////////////////////////////////////////////////////////////////////////////
// CSetOP4 diagnostics

#ifdef _DEBUG
void CSetOP4::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOP4::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CSetOP4::SelectONr( long onr )
{
	BOOL	result = FALSE;

	CString		ide;
	
	if ( IDEfromONr( onr, ide ))
		if ( !ide.IsEmpty())
	{
		if ( IsOpen())
			if ( m_IDE == ide )		return TRUE;

		m_strFilter = "NFP2_IDE = '";
		m_strFilter += ide;
		m_strFilter += "'";
		if ( !IsOpen())		Open();
		else				Requery();
		if ( !IsEOF())		result = TRUE;
	}

	return result;
}
