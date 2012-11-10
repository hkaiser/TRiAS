// SearchSe.cpp : implementation file
//

#include "stdafx.h"			// vorübersetzter Header
#include "gak.h"			// CGakapp
#include "SearchSe.h"		// zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchSet

IMPLEMENT_DYNAMIC(CSearchSet, CDaoRecordset)

//	snapshot-Suche über WHERE-Klausel
CSearchSet::CSearchSet(const char *pSearch, CDaoDatabase* pdb /* = NULL */)
		   :CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSearchSet)
	m_strNummer = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenSnapshot;
	// m_pTableDef = NULL;

	ASSERT (pSearch != NULL && AfxIsValidString (pSearch));
	m_strSearch = pSearch;	  // kein TRY/CATCH !
}

//	tableset
CSearchSet::CSearchSet(CDaoDatabase* pdb /* = NULL */)
		   :CDaoRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CSearchSet)
	m_strNummer = _T("");
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dbOpenSnapshot;
	// m_pTableDef = NULL;	
}

CSearchSet :: ~CSearchSet (void)
{
	Close ();
}

void CSearchSet :: Close ()
{
/*
	if (m_pTableDef)
	{
		if (m_pTableDef -> IsOpen ())
			m_pTableDef -> Close ();
		DELETE_OBJ (m_pTableDef);
	}
*/
	if (IsOpen ())
		CDaoRecordset :: Close ();
}

CString CSearchSet::GetDefaultDBName()
{
//	lese DB-Namen
	CGakApp *pApp = (CGakApp *) AfxGetApp ();
	ASSERT (pApp != NULL);
	return pApp -> DatabaseName ();
}

CString CSearchSet::GetDefaultSQL()
{
	CString strTableName;
	strTableName = ((CGakApp *)(AfxGetApp ())) -> ErzeugerDefaultSQL ();

	CString strSelect;
	if (m_strSearch.IsEmpty ())
	//	SELECT Nummer FROM %1 ORDER BY Nummer	
		AfxFormatString1 (strSelect, IDS_SELECT_NUMMER_WW, strTableName);
	else
	//	SELECT Nummer FROM %1 WHERE %2 ORDER BY Nummer
		AfxFormatString2 (strSelect, IDS_SELECT_NUMBER, strTableName, m_strSearch);

	return strSelect;

	// return strTableName;		// tableset
}

void CSearchSet::DoFieldExchange(CDaoFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CSearchSet)
	pFX->SetFieldType(CDaoFieldExchange::outputColumn);
	DFX_Text(pFX, _T("[Nummer]"), m_strNummer);
	//}}AFX_FIELD_MAP
}

/*
//	überlagere Open-Funktion
void CSearchSet :: Open (int nOpenType = AFX_DAO_USE_DEFAULT_TYPE, 
						 LPCTSTR lpszSQL = NULL, 
						 int nOptions = 0)
{
	try
	{
		if ((nOpenType == dbOpenDynaset) || (nOpenType == dbOpenSnapshot))
		{
			CDaoRecordset :: Open (nOpenType, lpszSQL, nOptions);	// Standard-Open rufen
			return;
		}

	//	Database ggf. erzeugen
		AllocDatabase ();								

		CString strIndex;
		if (!strIndex.LoadString (IDS_ST_NUMMER_INDEX))
			AfxThrowResourceException ();

		m_pTableDef = new CDaoTableDef (m_pDatabase);
		m_pTableDef -> Open (GetDefaultSQL());

		CDaoRecordset :: Open (m_pTableDef);			// Set Öffnen
		SetCurrentIndex (strIndex);						// Index setzen
	}
	catch (CMemoryException* me)
	{
		me -> ReportError ();
		throw me;
	}
	catch (CDaoException* de)
	{
		//	de -> ReportError (); Fehlermeldung nicht doppelt ausgeben
		throw de;
	}
	catch (CResourceException* re)
	{
		re -> ReportError ();
		throw re;
	}
}
*/

/////////////////////////////////////////////////////////////////////////////
// CSearchSet diagnostics

#ifdef _DEBUG
void CSearchSet::AssertValid() const
{
	CDaoRecordset::AssertValid();
}

void CSearchSet::Dump(CDumpContext& dc) const
{
	CDaoRecordset::Dump(dc);
}
#endif //_DEBUG

