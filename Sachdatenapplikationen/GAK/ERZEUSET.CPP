// erzeuset.cpp : implementation of the CErzeugerSet class
//

#include "stdafx.h"			// 	prec. Header 
#include "res.h"			//	Resource-Konstanten
#include "recset.h"			// 	CRecordsetExt
#include "erzeuset.h"		// 	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif              


//	Filter anhängen
extern void AppendFilter (CString &strFilter, const CString& strExtension);


/////////////////////////////////////////////////////////////////////////////
// CErzeugerSet implementation
IMPLEMENT_DYNAMIC(CErzeugerSet, CRecordsetExt)

CErzeugerSet:: CErzeugerSet  (CDatabase* pdb)
			 : CRecordsetExt (pdb)   
{
	//{{AFX_FIELD_INIT(CErzeugerSet)
	m_strTableName = "";
	m_strErzNr = "";
	m_strBezAnfall = "";
	m_strOrtAnfall = "";
	m_strAnspr = "";
	m_strTelAnspr = "";
	m_strFaxAnspr = "";
	m_bBearbeitet = FALSE;
	m_nFields = 1;
	//}}AFX_FIELD_INIT
	
	m_strErzNrParam = "";
	m_strAsnParam = "";
	m_nParams = 0;
}            

CString CErzeugerSet::GetDefaultConnect()
{
	ASSERT (FALSE);
	return "";
}

CString CErzeugerSet::GetDefaultSQL()
{                          
	ASSERT (!m_strTableName.IsEmpty ());
	CString strSQL;
	AfxFormatString1 (strSQL, IDS_SELECT_ERZSET, m_strTableName);	           
	return strSQL;
}

void CErzeugerSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CErzeugerSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP

	RFX_Text(pFX, "Nummer", m_strErzNr);   
}

//	CErzeugerSetErzeugerListe -------------------------------------------------
CErzeugerSetErzeugerListe :: CErzeugerSetErzeugerListe (CDatabase* pdb)
			 			   : CErzeugerSet (pdb)   
{
	m_nFields = 7;
	m_nParams = 1;
}			 			   
                
CString CErzeugerSetErzeugerListe::GetDefaultSQL()
{                          
	ASSERT (!m_strTableName.IsEmpty ());
	CString strSQL;
	AfxFormatString1 (strSQL, IDS_ERZ_LISTE, m_strTableName);	           
	return strSQL;
}

void CErzeugerSetErzeugerListe::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CErzeugerSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, "Nummer", m_strErzNr);   
	RFX_Text(pFX, "Anfallstelle", m_strBezAnfall);
	RFX_Text(pFX, "Ortsname", m_strOrtAnfall);		
	RFX_Text(pFX, "Ansprechpartner", m_strAnspr);
	RFX_Text(pFX, "Partnertelefon", m_strTelAnspr);
	RFX_Text(pFX, "Partnertelefax", m_strFaxAnspr);	
	RFX_Text(pFX, "Branchennummer", m_strBranche);   
	//}}AFX_FIELD_MAP

	pFX->SetFieldType(CFieldExchange::param);	
	RFX_Text(pFX, "Nummer", m_strErzNrParam, sMaxErzNrLen);   
}

//	CErzeugerSetListeOhne -------------------------------------------------
/*
CErzeugerSetListeOhne :: CErzeugerSetListeOhne (CDatabase* pdb)
			 		   : CErzeugerSet (pdb)   
{
	m_nFields = 1;
	m_nParams = 2;
}			 			   
                
CString CErzeugerSetListeOhne::GetDefaultSQL()
{                          
	ASSERT (!m_strTableName.IsEmpty ());
	CString strSQL;
	AfxFormatString1 (strSQL, IDS_LISTE_OHNE, m_strTableName);	           
	return strSQL;
}

void CErzeugerSetListeOhne::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CErzeugerSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);        
	RFX_Bool(pFX, "Bearbeitet", m_bBearbeitet);				
	//}}AFX_FIELD_MAP

	pFX->SetFieldType(CFieldExchange::param);		
	RFX_Text(pFX, "Nummer", m_strErzNrParam, sMaxErzNrLen);   
}
*/

//	CErzeugerSetListeListe -------------------------------------------------
CErzeugerSetListeListe :: CErzeugerSetListeListe (CDatabase* pdb)
			 		    : CErzeugerSet (pdb)   
{
	m_nFields = 8;
	m_nParams = 2;
}			 			   
                
CString CErzeugerSetListeListe::GetDefaultSQL()
{                          
	ASSERT (!m_strTableName.IsEmpty ());
	CString strSQL;
	AfxFormatString1 (strSQL, IDS_LISTE_LISTE, m_strTableName);	           
	return strSQL;
}

void CErzeugerSetListeListe::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CErzeugerSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);        
	RFX_Text(pFX, "Nummer", m_strErzNr);
	RFX_Text(pFX, "Anfallstelle", m_strBezAnfall);
	RFX_Text(pFX, "Ortsname", m_strOrtAnfall);		
	RFX_Text(pFX, "Ansprechpartner", m_strAnspr);
	RFX_Text(pFX, "Partnertelefon", m_strTelAnspr);
	RFX_Text(pFX, "Partnertelefax", m_strFaxAnspr);
	RFX_Bool(pFX, "Bearbeitet", m_bBearbeitet);				
	RFX_Text(pFX, "Branchennummer", m_strBranche);   
	//}}AFX_FIELD_MAP

	pFX->SetFieldType(CFieldExchange::param);		
	RFX_Text(pFX, "Nummer", m_strErzNrParam, sMaxErzNrLen);   
	RFX_Text(pFX, "Abfallnummer", m_strAsnParam, sMaxAsnNrLen);   
}


CString CAbgleichCntSetFilter::GetFilter(	const CString& strBilanztable, const CString& strErzeugerTable)
{
	CString strFilter;

	// SonderabfallString
	if (m_bOnlySonderAbfall)
		VERIFY (strFilter.LoadString (IDS_ONLY_SONDER_ABFALL));

	CString strTemp;
	if (/*(0 == m_iModus) &&*/ !m_strLastErzeuger.IsEmpty ())
	{
	//	Operator laden
		CString strOp (m_bOnlyThisErzeuger ? "=" : ">=");
		VERIFY (strTemp.LoadString (IDS_FILTER_ERZNZ_BILANZ));
		CString strErzFilter;
		strErzFilter.Format (strTemp, (const char*)	strErzeugerTable, 
									  (const char*)	strOp, 
									  (const char*)	m_strLastErzeuger);

	//	ggf. jetzt noch Abfallschlüsselnummer anhängen
		if (/*(0 == m_iModus) &&*/ !m_strLastAsn.IsEmpty ())
		{					
			CString strAsnFilter;
			VERIFY (strTemp.LoadString (IDS_FILTER_ASN_BILANZ));
			strAsnFilter.Format (strTemp, (const char*)	strBilanztable, 
										  (const char*)	m_strLastAsn);
			AppendFilter (strErzFilter, strAsnFilter);
		}

		AppendFilter (strFilter, strErzFilter);
	}
	
	if (!strFilter.IsEmpty())
		strFilter = CString(" WHERE ") + strFilter;

	return strFilter;
}

/////////////////////////////////////////////////////////////////////////////
// CAbgleichCntSet implementation
IMPLEMENT_DYNAMIC(CAbgleichCntSet, CRecordsetExt)
CAbgleichCntSet:: CAbgleichCntSet  (CDatabase* pdb, 
									const CString& strErzeugerTable,
									const CString& strBilanztable,
									const CString &strBgsTable,
									CAbgleichCntSetFilter &filter)
				: CRecordsetExt (pdb)   
{
	//{{AFX_FIELD_INIT(CErzeugerSet)
	m_strErzNr = "";
	m_strAsn = "";
	m_nFields = 2;
	//}}AFX_FIELD_INIT
	
	m_strErzNrParam = "";
	m_strAsnParam = "";
	m_nParams = 2;

//	prüfe Parameter
	ASSERT (!strErzeugerTable.IsEmpty ());
	ASSERT (!strBilanztable.IsEmpty ());

//	Select-Statement aufbauen
	if (strBilanztable == strErzeugerTable)
		AfxFormatString1 (m_strSelect, IDS_SELECT_SET_ABGL1, strBilanztable);
	else
		AfxFormatString2 (m_strSelect, IDS_SELECT_SET_ABGL, strBilanztable, strErzeugerTable);

//	JG an diesen TeilBefehl die Bedingung anfügen
	m_strSelect += filter.GetFilter(strBilanztable, strErzeugerTable);
	
//	Union mit BGS-Tabelle	
	ASSERT (!strBgsTable.IsEmpty ());
	CString strTemp;
	AfxFormatString2 (strTemp, IDS_SELECT_SET_ABGL, strBgsTable, strErzeugerTable);
	m_strSelect += " UNION " + strTemp;
	
//	JG an diesen TeilBefehl die Bedingung anfügen
	m_strSelect += filter.GetFilter(strBgsTable, strErzeugerTable);

//	Sortierung 
	AfxFormatString1 (m_strSort, IDS_SORT_ERZNR_ASN, strBilanztable);
}            

CString CAbgleichCntSet::GetDefaultConnect()
{
	ASSERT (FALSE);
	return "";
}

CString CAbgleichCntSet::GetDefaultSQL()
{                          
	ASSERT (!m_strSelect.IsEmpty ());
	return m_strSelect;
}
                 
void CAbgleichCntSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CErzeugerSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, "Nummer", m_strErzNr);   
	RFX_Text(pFX, "Abfallnummer", m_strAsn);
	//}}AFX_FIELD_MAP

	pFX->SetFieldType(CFieldExchange::param);	
	RFX_Text(pFX, "Nummer", m_strErzNrParam, sMaxErzNrLen);   
	RFX_Text(pFX, "Abfallnummer", m_strAsnParam, sMaxAsnNrLen);   
}
