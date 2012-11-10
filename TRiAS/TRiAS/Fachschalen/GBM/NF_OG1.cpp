// NF_OG1.cpp : implementation file
//

#include "stdafx.h"
#include "GbmTRiAS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetNF_OG1

IMPLEMENT_DYNAMIC(CSetNF_OG1, CRecordset)

CSetNF_OG1::CSetNF_OG1(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSetNF_OG1)
	m_NFO1_PRO = _T("");
	m_NFO1_IDE = _T("");
	m_NFO1_ORT = _T("");
	m_NFO1_STR = _T("");
	m_NFO1_FLU = _T("");
	m_NFO1_FST = _T("");
	m_NFO1_BLT = 0.0;
	m_NFO1_FLG = 0.0;
	m_NFO1_PFA = 0.0;
	m_NFO1_PFU = 0.0;
	m_NFO1_PGR = 0.0;
	m_NFO1_AFA = _T("");
	m_NFO1_AFU = _T("");
	m_NFO1_ART = 0.0;
	m_NFO1_VFL = 0.0;
	m_NFO1_BEM = _T("");
	m_nFields = 16;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
	m_strSort = "NFO1_IDE";
}


CString CSetNF_OG1::GetDefaultConnect()
{
	return _T("ODBC;DSN=GBM-TRiAS");
}

CString CSetNF_OG1::GetDefaultSQL()
{
	return _T("[NF_OG1]");
}

void CSetNF_OG1::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSetNF_OG1)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[NFO1_PRO]"), m_NFO1_PRO);
	RFX_Text(pFX, _T("[NFO1_IDE]"), m_NFO1_IDE);
	RFX_Text(pFX, _T("[NFO1_ORT]"), m_NFO1_ORT);
	RFX_Text(pFX, _T("[NFO1_STR]"), m_NFO1_STR);
	RFX_Text(pFX, _T("[NFO1_FLU]"), m_NFO1_FLU);
	RFX_Text(pFX, _T("[NFO1_FST]"), m_NFO1_FST);
	RFX_Double(pFX, _T("[NFO1_BLT]"), m_NFO1_BLT);
	RFX_Double(pFX, _T("[NFO1_FLG]"), m_NFO1_FLG);
	RFX_Double(pFX, _T("[NFO1_PFA]"), m_NFO1_PFA);
	RFX_Double(pFX, _T("[NFO1_PFU]"), m_NFO1_PFU);
	RFX_Double(pFX, _T("[NFO1_PGR]"), m_NFO1_PGR);
	RFX_Text(pFX, _T("[NFO1_AFA]"), m_NFO1_AFA);
	RFX_Text(pFX, _T("[NFO1_AFU]"), m_NFO1_AFU);
	RFX_Double(pFX, _T("[NFO1_ART]"), m_NFO1_ART);
	RFX_Double(pFX, _T("[NFO1_VFL]"), m_NFO1_VFL);
	RFX_Text(pFX, _T("[NFO1_BEM]"), m_NFO1_BEM);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSetNF_OG1 diagnostics

#ifdef _DEBUG
void CSetNF_OG1::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSetNF_OG1::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL CSetNF_OG1::FindIDE( const char* ide )
{
	if ( !IsOpen())	return FALSE;

	MoveFirst();
	while ( !IsEOF() && ( m_NFO1_IDE < ide ))	MoveNext();
	if ( m_NFO1_IDE == ide )	return TRUE;
	return FALSE;
}	// FindIDE
