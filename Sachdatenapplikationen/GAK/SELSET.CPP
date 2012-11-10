// SelSet.cpp : implementation file
//

#include "stdafx.h"			// prec. Header
#include "gak.h"			// CGakApp
#include "SelSet.h"			// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectSet

IMPLEMENT_DYNAMIC(CSelectSet, CDaoRecordset)

CSelectSet::CSelectSet(CDaoDatabase* pdb, const char *pTableName)
		   :CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSelectSet)
	m_Nummer = _T("");
	m_Name = _T("");
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenSnapshot;

	ASSERT (pTableName != NULL && AfxIsValidString (pTableName));
	m_strTableName = pTableName;   // kein TRY/CATCH !
}

CString CSelectSet::GetDefaultDBName()
{
//	lese DB-Namen
	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (pApp != NULL);
	return pApp -> DatabaseName ();
}

CString CSelectSet::GetDefaultSQL()
{
	ASSERT (! m_strTableName.IsEmpty ());
	CString strSelect;
	AfxFormatString1 (strSelect, IDS_SELECT_AUSWAHL, m_strTableName);
	return strSelect;		// SELECT Name,Nummer FROM %1 ORDER BY Name
}

void CSelectSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSelectSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nummer]"), m_Nummer);
	DFX_Text(pFX, _T("[Name]"), m_Name);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CSelectSet diagnostics

#ifdef _DEBUG
void CSelectSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSelectSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

CSelectSet::~CSelectSet (void)
{
	Close ();
}

void CSelectSet::Close() 
{
	// TODO: Add your specialized code here and/or call the base class
	if (IsOpen ())	
		CDaoRecordset::Close();
}
