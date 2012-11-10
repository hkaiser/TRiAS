// KreisSet.cpp : implementation file
//

#include "stdafx.h"			//	prec. Header
#include "gak.h"			//	CGakApp

#include "KreisSet.h"		//	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CKreisSet
IMPLEMENT_DYNAMIC(CKreisSet, CDaoRecordset)
CKreisSet::CKreisSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CKreisSet)
	m_Nummer = _T("");
	m_Name = _T("");
	m_Kuerzel = _T("");
	m_AfI = _T("");
	m_nFields = 4;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenSnapshot;
}


CString CKreisSet::GetDefaultDBName()
{
//	lese default-DB-Namen
	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (pApp != NULL);
	return pApp -> DatabaseName ();
}

CString CKreisSet::GetDefaultSQL()
{
	return ((CGakApp *)AfxGetApp ()) -> KreisDefaultSQL ();
}

void CKreisSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CKreisSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP

	if (m_nFields > 1)
	{
		DFX_Text(pFX, _T("[Nummer]"), m_Nummer);
		DFX_Text(pFX, _T("[Name]"), m_Name);
		DFX_Text(pFX, _T("[Kuerzel]"), m_Kuerzel);
	}

	DFX_Text(pFX, _T("[AfI]"), m_AfI);
}

/////////////////////////////////////////////////////////////////////////////
// CKreisSet diagnostics

#ifdef _DEBUG
void CKreisSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CKreisSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
