// erzliste.cpp : implementation of the CErzListeSet class
//

#include "stdafx.h"			//	prec. Header
#include "res.h"			//	Resource-Konstanten
#include "recset.h"			// 	CRecordsetExt	   
#include "erzeuset.h"		//	CErzeugerSet
#include "abfarmap.h"		//	CAbfallArtenMap
#include "abfmap.h"			// 	CAbfallMap
#include "erzliste.h"		//	zugeh. Header

/////////////////////////////////////////////////////////////////////////////
// CErzListeSet implementation

IMPLEMENT_DYNAMIC(CErzListeSet, CRecordsetExt)

CErzListeSet::CErzListeSet(CDatabase* pdb)
		     :CRecordsetExt(pdb)
{
	//{{AFX_FIELD_INIT(CErzListeSet)
	m_strNummer = _T("");
	m_strAnfallstelle = _T("");
	m_strOrtsname = _T("");
	m_strAnsprechpartner = _T("");
	m_strPartnertelefon = _T("");
	m_strPartnertelefax = _T("");
	m_strAbfallnummer = _T("");
	m_strTransporteurnummer = _T("");
	m_strEntsorgernummer = _T("");
	m_dMenge = 0.0;
	m_bSonderabfall = FALSE;
	m_bBilanzdaten = FALSE;
	m_bBearbeitet = FALSE;
	m_strBranchennummer = _T("");
	m_strVerfahren = _T("");
	m_strPrioritaet = _T("");
	m_strNachweisnummer = _T("");
	m_nFields = 17;	//}}AFX_FIELD_INIT
}

CString CErzListeSet::GetDefaultConnect()
{
	return "ODBC;DSN=BGS-Abgleich - FoxPro;";
}

CString CErzListeSet::GetDefaultSQL()
{
	// return "ERZLISTE"; 
	ASSERT (!m_strTableName.IsEmpty ());
	return m_strTableName;
}

void CErzListeSet::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CErzListeSet)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Nummer]"), m_strNummer);
	RFX_Text(pFX, _T("[Anfallstelle]"), m_strAnfallstelle);
	RFX_Text(pFX, _T("[Ortsname]"), m_strOrtsname);
	RFX_Text(pFX, _T("[Ansprechpartner]"), m_strAnsprechpartner);
	RFX_Text(pFX, _T("[Partnertelefon]"), m_strPartnertelefon);
	RFX_Text(pFX, _T("[Partnertelefax]"), m_strPartnertelefax);
	RFX_Text(pFX, _T("[Abfallnummer]"), m_strAbfallnummer);
	RFX_Text(pFX, _T("[Transporteurnummer]"), m_strTransporteurnummer);
	RFX_Text(pFX, _T("[Entsorgernummer]"), m_strEntsorgernummer);
	RFX_Double(pFX, _T("[Menge]"), m_dMenge);
	RFX_Bool(pFX, _T("[Sonderabfall]"), m_bSonderabfall);
	RFX_Bool(pFX, _T("[Bilanzdaten]"), m_bBilanzdaten);
	RFX_Bool(pFX, _T("[Bearbeitet]"), m_bBearbeitet);
	RFX_Text(pFX, _T("[Branchennummer]"), m_strBranchennummer);
	RFX_Text(pFX, _T("[Verfahren]"), m_strVerfahren);
	RFX_Text(pFX, _T("[Prioritaet]"), m_strPrioritaet);
	RFX_Text(pFX, _T("[Nachweisnummer]"), m_strNachweisnummer);
	//}}AFX_FIELD_MAP
}

//	Ausgabe der selektierten Sätze beider Maps	
BOOL CErzListeSet::Output (const CString &strErzNr, const CString& strAsn,CErzeugerSet *pInfoSet, CAbfallMap *pMap1, 
				   		   CAbfallMap *pMap2, CStatic &stUserInfo, long &lCnt)
{               
//	prüfe Parameter	    
	ASSERT (!strErzNr.IsEmpty ());
	ASSERT (NULL != pInfoSet && pInfoSet -> IsOpen ());
	ASSERT (NULL != pMap1);
	ASSERT (NULL != pMap2);	                                                 
	
//	haben Maps Sätze ?
	if (pMap1 -> IsEmpty () && pMap2 -> IsEmpty ())
		return TRUE;
	
	BOOL bRet = FALSE;		// noch nichts getan
	TRY
	{	    
		CWaitCursor wc;		// 	Sanduhr ein	
	             
	//	Info an Nutzer ausgeben
		CString strInfo;
		AfxFormatString1 (strInfo, IDS_OUTPUT_RECORDS, strErzNr);
		stUserInfo.SetWindowText (strInfo);
	
	//	suche Erzeuger-Info in Erzeugerset
		pInfoSet -> m_strErzNrParam = strErzNr;
		pInfoSet -> m_strAsnParam   = strAsn;
		VERIFY (pInfoSet -> Requery ());
		
		if (OutputMap (strErzNr, pInfoSet, pMap1, TRUE, lCnt))
			bRet = OutputMap (strErzNr, pInfoSet, pMap2, FALSE, lCnt);		
	}		
	CATCH (CMemoryException, me)
	{                       
		OutputMemoryError ();         
	}
	AND_CATCH (CDBException, db)
	{                  
		OutputError (db -> m_strError);      
	}                                           
	AND_CATCH (CFileException, fe)
	{                  
		CString strFileErr;
		VERIFY (strFileErr.LoadString (IDS_FILE_ERROR));
		OutputError (strFileErr);		
	}
	END_CATCH                   
				
	return bRet;
}				   
                                                
//	Ausgabe der selektierten Sätze einer Map	                                                
BOOL CErzListeSet::OutputMap (const CString &strErzNr, CErzeugerSet *pInfoSet, CAbfallMap *pMap,
							  BOOL bBilanz, long &lCnt, bool bOnlySelected)
{
//	prüfe Parameter	    
	ASSERT (!strErzNr.IsEmpty ());
	ASSERT (NULL != pInfoSet && pInfoSet -> IsOpen () /*&& !pInfoSet -> IsEOF ()*/);
	if (!pInfoSet->IsEOF ())
		pInfoSet->MoveLast();

	ASSERT (NULL != pMap);
                    
//	hat Map Sätze ?                        
	if (pMap -> IsEmpty ())
		return TRUE;       

	TRY
	{		
		CString strKey, strVal, strInfo;
		POSITION Pos = NULL;			
		CAbfallInfo* pInfo = NULL;             
		
		for (Pos = pMap -> GetStartPosition(); Pos != NULL;)
		{
			pMap -> GetNextAssoc (Pos, strKey, (CObject *&) pInfo);
			ASSERT (NULL != pInfo);
			
		//	nur selektierte Sätze ausgeben
			if ((pInfo -> m_bIsSelected) || (!bOnlySelected))
			{
				AddNew ();		// 	Addnew starten
					
			//	Daten umkopieren: Daten aus Erzeugerset
				m_strNummer = strErzNr;
				m_strAnfallstelle = pInfoSet -> m_strBezAnfall;
				m_strOrtsname = pInfoSet -> m_strOrtAnfall;
				m_strAnsprechpartner = pInfoSet -> m_strAnspr;
				m_strPartnertelefon = pInfoSet -> m_strTelAnspr;
				m_strPartnertelefax = pInfoSet -> m_strFaxAnspr;
				m_strBranchennummer = pInfoSet -> m_strBranche;
				
			//	Daten aus Map	
				m_strAbfallnummer = pInfo -> m_strAbfArt;
				m_strTransporteurnummer = pInfo -> m_strTransp;
				m_strEntsorgernummer = pInfo -> m_strEntsorger;
				m_strVerfahren = pInfo -> m_strVerfahren;
				m_strPrioritaet = pInfo -> m_strPrio;
				m_strNachweisnummer = pInfo -> m_strNachweis;
				m_dMenge = pInfo -> m_dMenge;
				m_bSonderabfall = pInfo -> m_bSonderAbfall;

			//	Daten aus Abfallbilanz				
				m_bBilanzdaten = bBilanz;				
				  
			//	niemals bearbeitet				  
				m_bBearbeitet = FALSE;
														
				Update ();		//  Daten speichern
				lCnt++;
			}
		}   
	}		
	CATCH_ALL(e)
	{
		TRACE0 ("Fehler bei Ausgabe in Erzeugerliste !\n");
        THROW_LAST();
	}
	END_CATCH_ALL

	return TRUE;									                
}
		