// FirmaSet.cpp : implementation file
//

#include "stdafx.h"		//	prec. Header
#include "gak.h"		//	CGakApp

#include "FirmaSet.h"	// zugeh. Header	

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFirmaSet

IMPLEMENT_DYNAMIC(CFirmaSet, CDaoRecordset)

CFirmaSet::CFirmaSet(CDaoDatabase* pdb)
	: CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CFirmaSet)
	m_Nummer = _T("");
	m_Firmenname = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenSnapshot;
}

CFirmaSet :: ~CFirmaSet ()
{
	if (IsOpen ())
		Close ();
}

CString CFirmaSet::GetDefaultDBName()
{
	ASSERT (FALSE);
	return _T("C:\\GAK\\WIN32\\DATEN\\Test.mdb");
}

CString CFirmaSet::GetDefaultSQL()
{
	return ((CGakApp *) AfxGetApp ()) -> ErzeugerDefaultSQL ();
}

void CFirmaSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CFirmaSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nummer]"), m_Nummer);
	DFX_Text(pFX, _T("[Firmenname]"), m_Firmenname);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CFirmaSet diagnostics

#ifdef _DEBUG
void CFirmaSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CFirmaSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG
