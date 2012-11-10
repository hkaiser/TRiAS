// abfarset.cpp : implementation of the CAbfartSet class
//

#include "stdafx.h"		// 	prec. Header
#include "res.h"		//	Resource-Konstanten	
#include "abfarsetodbc.h"	// 	zugeh. Header	angepaßt

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

//	Konstanten
//  const int iMaxNrLen = 11;		// max. Länge des Parameterfeldes

/////////////////////////////////////////////////////////////////////////////
// CAbfartSet implementation

IMPLEMENT_DYNAMIC(CAbfartSet, CRecordset)

CAbfartSet::CAbfartSet(CDatabase* pdb)
		   : CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CAbfartSet)
	m_bSonderAbfall = FALSE;
	m_dDichte = 0.0;
	m_nFields = 3; 
	//}}AFX_FIELD_INIT
	
	// m_strAbfArtParam = "";              
	// m_nParams = 1;
	
	/*
	m_LABFGMASS = FALSE;
	m_ABFALL_ART = "";
	m_HERKUNFT = "";
	m_CPB = "";
	m_HMV = "";
	m_SAV = "";
	m_HMD = "";
	m_SAD = "";
	m_UTD = "";
	m_SONSTIGES = "";
	m_nFields = 13;
	*/             
}                

CAbfartSet::~CAbfartSet ()
{
	if (IsOpen ())
		Close ();
}

CString CAbfartSet::GetDefaultConnect()
{
	return "ODBC;DSN=BGS-Abgleich - FoxPro;";
}

CString CAbfartSet::GetDefaultSQL()
{
	CString strSelect, strTable;
	VERIFY (strTable.LoadString (IDS_ABFART_TABLE));                  
	AfxFormatString1 (strSelect, IDS_SELECT_ABFART, strTable);
	return strSelect;
}

void CAbfartSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CAbfartSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	//}}AFX_FIELD_MAP

	RFX_Text(pFX, "Nummer", m_strAbfallArt);
	RFX_Bool(pFX, "Sonderabfall", m_bSonderAbfall);
	RFX_Double(pFX, "Dichte", m_dDichte);
	
	// pFX->SetFieldType(CFieldExchange::param);
	// RFX_Text(pFX, "NRABFART", m_strAbfArtParam, iMaxNrLen);
	
/*	
	RFX_Text(pFX, "NRABFART", m_strNrAbfArt);
	RFX_Bool(pFX, "LABFGMASS", m_LABFGMASS);
	RFX_Text(pFX, "ABFALL_ART", m_ABFALL_ART);
	RFX_Text(pFX, "HERKUNFT", m_HERKUNFT);
	RFX_Text(pFX, "CPB", m_CPB);
	RFX_Text(pFX, "HMV", m_HMV);
	RFX_Text(pFX, "SAV", m_SAV);
	RFX_Text(pFX, "HMD", m_HMD);
	RFX_Text(pFX, "SAD", m_SAD);
	RFX_Text(pFX, "UTD", m_UTD);
	RFX_Text(pFX, "SONSTIGES", m_SONSTIGES);
*/	
}
