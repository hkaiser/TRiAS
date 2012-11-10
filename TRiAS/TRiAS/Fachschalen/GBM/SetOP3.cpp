// SetOP3.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"
#include "SetOP3.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetOP3

IMPLEMENT_DYNAMIC(CSetOP3, CRecordset)

CSetOP3::CSetOP3(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetOP3)
	m_ABF = 0.0;
	m_ANS = _T("");
	m_FLG = 0.0;
	m_FLN = _T("");
	m_IDE = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CSetOP3::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetOP3::GetDefaultSQL()
{
	return _T("[NF_PG2D]");
}

void CSetOP3::DoFieldExchange(CFieldExchange* pFX)
{
	CxString	text;

	//{{AFX_FIELD_MAP(CSetOP3)
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

BOOL CSetOP3::Update()
{
	CxString	text;

	text = "D";
	text.AppendF( m_lFLN, -1 );
	m_FLN = text;
	return CRecordset::Update();
}

/////////////////////////////////////////////////////////////////////////////
// CSetOP3 diagnostics

#ifdef _DEBUG
void CSetOP3::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetOP3::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CSetOP3::SelectONr( long onr )
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
