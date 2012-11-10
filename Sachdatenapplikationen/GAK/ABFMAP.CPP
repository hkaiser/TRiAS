// abfmap.cpp : implementation of the CAbfallInfo class
//

#include "stdafx.h"		//	prec. Header
#include "res.h"		//	Ressource-Konstanten	
//#include "abfarset.h"	// 	CAbfartSet
#include "abfarmap.h"	//	CAbfallArtenMap	// JG merge
#include "outset.h"		//	COutputSet
#include "abfmap.h"		// 	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAbfallInfo implementation

IMPLEMENT_DYNAMIC(CAbfallInfo, CObject)

CAbfallInfo::CAbfallInfo (const CString& strAbfArt,
						  const CString& strTransp, const CString& strEntsorger, 
						  const double& dMenge, const double dMengeEn,
						  const CString& strNachweisNr, const CString &strVerfahren, 
						  const CString& strPrio, BOOL bSonderAbfall, 
						  const CString& strEntsorgerBemerkungen,
						  const CString& strTransporteurBemerkungen,	
						  BOOL bIsSelected)
{
	m_strAbfArt = strAbfArt;
	m_strTransp = strTransp;
	m_strEntsorger = strEntsorger; 
	m_strNachweis = strNachweisNr;
	m_strVerfahren = strVerfahren;
	m_strPrio = strPrio;

	m_dMenge = dMenge;	
	m_dMengeEn = dMengeEn;	

	m_bIsSelected = bIsSelected;	
	m_strEntsorgerBemerkungen = strEntsorgerBemerkungen;
	m_strTransporteurBemerkungen = strTransporteurBemerkungen;
	m_bSonderAbfall = bSonderAbfall;
}             
                                
IMPLEMENT_DYNAMIC(CAbfallMap, CMapStringToOb)
CAbfallMap::CAbfallMap (CAbfallArtenMap *pMap, CListCtrl *pList, 
						BOOL bOnlySonderAbfall, double dMinMenge)
{                       
	ASSERT (NULL != pList);
	ASSERT (NULL != pMap);
	ASSERT (dMinMenge >= 0);
	// ASSERT (pSet -> IsOpen ());
	m_pAbfArtMap = pMap;
	m_bOnlySonderAbf = 	bOnlySonderAbfall;
	m_dSumMenge = m_dSelSumMenge = 0.0;	
	m_pListBox = pList;
	m_dMinMengeRec = dMinMenge;
}                                      

CAbfallMap::~CAbfallMap(void)
{
	if (!IsEmpty ())	
	{                                  
		CString strKey;
		POSITION Pos = NULL;			
		CAbfallInfo* pInfo = NULL;
		
		for (Pos = GetStartPosition(); Pos != NULL;)
		{
			GetNextAssoc (Pos, strKey, (CObject *&) pInfo);
			ASSERT (NULL != pInfo);
			DELETE_OBJ (pInfo);				
		}
	}                    
	
	ASSERT (NULL != m_pListBox);
	if (m_pListBox->m_hWnd && m_pListBox->IsWindowVisible ())
		VERIFY (m_pListBox -> DeleteAllItems ());
}	

//	neue Info in Map aufnehmen: prüft Parameter	                       
BOOL CAbfallMap::AddInfo (const char *pAbfArt, const CString& strTransp,
				  		  const CString& strEntsorger, const double& dMenge, const double dMengeEn,
						  const CString& strNachweisNr, const CString &strVerfahren, 
						  const CString& strPrio, 
						  const CString& strEntsorgerBemerkungen,
						  const CString& strTransporteurBemerkungen,	
					  BOOL bSelect)
{   
//	prüfe interne Parameter
	ASSERT (NULL != m_pAbfArtMap);
	ASSERT (NULL != pAbfArt);
	ASSERT (AfxIsValidString (pAbfArt));
	
//	prüfe übergebene Parameter
	if ((dMenge < m_dMinMengeRec) || (!*pAbfArt))
		return FALSE;		// keine Mengen vorhanden oder ungültig		
		
//	gültige Abfallart ?
	/*
	m_pAbfArtSet -> m_strAbfArtParam = pAbfArt;
	m_pAbfArtSet -> Requery ();
	if (m_pAbfArtSet -> IsEOF ())
		return FALSE;	
	*/

	CAbfallArt *pArtInfo = NULL;
	if (!m_pAbfArtMap -> Lookup (pAbfArt, (CObject *&) pArtInfo))
		return FALSE;
	ASSERT (NULL != pArtInfo);
	
//	nur Sonderabfall ?
	if (m_bOnlySonderAbf && !pArtInfo -> m_bSonderAbfall)
		return FALSE;

//	Key bilden und suchen, wenn bereits vorhanden, nur Menge korrigieren
	CString strKey (strTransp+strEntsorger+strVerfahren);
	CAbfallInfo *pInfo = NULL;
	if (Lookup (strKey, (CObject *&) pInfo))
		pInfo -> m_dMenge += dMenge;
	else
	{   
		pInfo = new CAbfallInfo (pAbfArt,strTransp, strEntsorger, dMenge, dMengeEn,
								 strNachweisNr, strVerfahren, strPrio, 
								 pArtInfo->m_bSonderAbfall,
								 strEntsorgerBemerkungen,
								 strTransporteurBemerkungen,
								 bSelect);
		SetAt (strKey, pInfo);			
	}		 	

//	Gesamtmenge korrigieren
	m_dSumMenge += dMenge;

//	Menge der selektierten ändern
	if (bSelect)
		m_dSelSumMenge += dMenge;
		
	return TRUE;		
}

//	Datensätze in ListBox ausgeben          
//	Key über SetItemDataPtr speichern                          
//	Datensätze ggf.selektieren und Menge korrigieren        
BOOL CAbfallMap::OutputInListBox (BOOL bSelect, BOOL bIgnoreSelect)
{               
	ASSERT (NULL != m_pListBox);

//	ListBox-Inhalt immer löschen
	VERIFY (m_pListBox -> DeleteAllItems ());		
	
	try
	{
		if (!IsEmpty ())	
		{   
			CWaitCursor wc;
			CString strKey, strVal, strJa, strNein;
			POSITION Pos = NULL;			
			CAbfallInfo* pInfo = NULL;            
			
		//  Konstanten laden
			VERIFY (strJa.LoadString (IDS_JA));
			VERIFY (strNein.LoadString (IDS_NEIN));

		//	Selektsumme rücksetzen
			m_dSelSumMenge = 0.0;		
			
			int iItem = 0;	// akt. ListBox-Index
			for (Pos = GetStartPosition(); Pos != NULL; iItem++)
			{
				GetNextAssoc (Pos, strKey, (CObject *&) pInfo);
				ASSERT (NULL != pInfo);
				
			//	Select-Flag setzen
				if (!bIgnoreSelect)
					pInfo -> m_bIsSelected = bSelect;

			//	Werte in ListBox ausgeben: zuerst lfd. Nr.
				strVal.Format ("%d", iItem + 1);
				if (m_pListBox -> InsertItem (iItem, strVal) != iItem)
					AfxThrowMemoryException ();

			//	ASN
				if (!m_pListBox -> SetItemText (iItem, 1, pInfo->m_strAbfArt))
					AfxThrowMemoryException ();

			//	Sonderabfall
				if (!m_pListBox -> SetItemText (iItem, 2, 
												pInfo->m_bSonderAbfall ? strJa : strNein))
					AfxThrowMemoryException ();

			//	NachweisNr
				if (!m_pListBox -> SetItemText (iItem, 3, pInfo->m_strNachweis))
					AfxThrowMemoryException ();

			//	Menge
				strVal.Format (szMengenFormat, pInfo->m_dMenge);
				if (!m_pListBox -> SetItemText (iItem, 4, strVal))
					AfxThrowMemoryException ();
		
			//	MengeEn
				strVal.Format (szMengenFormat, pInfo->m_dMengeEn);
				if (!m_pListBox -> SetItemText (iItem, 5, strVal))
					AfxThrowMemoryException ();

			//	Transp
				if (!m_pListBox -> SetItemText (iItem, 6, pInfo->m_strTransp))
					AfxThrowMemoryException ();	

			//	Entsorger
				if (!m_pListBox -> SetItemText (iItem, 7, pInfo->m_strEntsorger))
					AfxThrowMemoryException ();	

			//	Verfahren
				if (!m_pListBox -> SetItemText (iItem, 8, pInfo->m_strVerfahren))
					AfxThrowMemoryException ();	

			//	Prio
				if (!m_pListBox -> SetItemText (iItem, 9, pInfo->m_strPrio))
					AfxThrowMemoryException ();	

			//	Key speichern		
				char *pKey = new char [strKey.GetLength () + 1];
				*pKey = '\0';
				strcpy (pKey, strKey);
				if (!m_pListBox -> SetItemData (iItem, (DWORD) pKey))
					AfxThrowMemoryException ();							
				
			//	sel. Menge ggf. erhöhen			
				if (!bIgnoreSelect && bSelect)			                                     
					m_dSelSumMenge += pInfo -> m_dMenge;			
			}       
			
		//	Selektion aller Einträge in ListBox setzen
			if (bIgnoreSelect)
			{
				int iCnt = m_pListBox -> GetItemCount ();     
				const char *pItemData = NULL;
				CAbfallInfo *pInfo = NULL;			
				for (int iIndex = 0; iIndex < iCnt; iIndex++)
				{
					pItemData = (const char *) m_pListBox -> GetItemData (iIndex);
					ASSERT (NULL != pItemData);
					VERIFY (Lookup (pItemData, (CObject *&) pInfo));
					ASSERT (NULL != pInfo);
					if (pInfo -> m_bIsSelected)
					{   
						VERIFY(m_pListBox->SetItemState (iIndex, LVIS_SELECTED, LVIS_SELECTED));
						m_dSelSumMenge += pInfo -> m_dMenge;								
					}					
				}
			}
			else
			{
				int iMax = 	m_pListBox -> GetItemCount ();
				UINT uiAttrib = bSelect ? LVIS_SELECTED : 0;
				for (int i = 0; i < iMax; i++)
					VERIFY (m_pListBox->SetItemState (i, LVIS_SELECTED, uiAttrib));
			}
		}

	//	Spaltenbreiten setzen
		/*
		UINT uiAttrib = iItemCnt > 0 ? LVSCW_AUTOSIZE : LVSCW_AUTOSIZE_USEHEADER;
		for (int j = 0; j < iColumnsCount; j++)
			VERIFY (m_pListBox -> SetColumnWidth (j, uiAttrib));
		*/

	//	ListBox akt./deakt.
		m_pListBox -> EnableWindow (m_pListBox -> GetItemCount ());
	}
	catch (CException *e)
	{
		e -> ReportError ();
		e -> Delete ();
		return FALSE;
	}

	return TRUE;
}                           

// selektierte Datensätze in den übergebenen Set ausgeben                                         
BOOL CAbfallMap::OutputInSet (COutputSet *pSet, const CString &strErzNummer,
							  BOOL bSelect, CStatic &stInfo, long &lCnt, BOOL bReverse)
{
//	prüfe Parameter
	ASSERT (NULL != pSet);
	ASSERT (pSet -> IsOpen ());
	ASSERT (!strErzNummer.IsEmpty ());
	ASSERT (NULL != m_pListBox);
	
	BOOL bRet = FALSE;		// noch nichts getan
	           
	TRY
	{	    
		CWaitCursor wc;
		int iMaxItem = m_pListBox -> GetItemCount ();
		if (iMaxItem <= 0)
			return TRUE;

	//	Info an Nutzer ausgeben
		CString strInfo;
		AfxFormatString1 (strInfo, IDS_OUTPUT_RECORDS, strErzNummer);
		stInfo.SetWindowText (strInfo);

	//	Items ausgeben
		BOOL bOutput = FALSE;
		BOOL bIsSelected = FALSE;
		const char *pItemData = NULL;
		CAbfallInfo *pInfo = NULL;
		for (int iItem = 0; iItem < iMaxItem; iItem++)
		{
		//	Item ausgeben ?
			if (!bSelect)				//	unabhängig von der Selektion
				bOutput = TRUE;
			else
			//	Ausgabe in Abhängigkeit von der Selektion
			{
				bIsSelected = m_pListBox -> GetItemState (iItem, LVIS_SELECTED) & LVIS_SELECTED ? TRUE : FALSE;				
				bOutput = bReverse ? !bIsSelected : bIsSelected;
			}

		//	prüfe Selektionstest
			if (!bOutput)
				continue;

		//	lese zugeh. ItemData
			pItemData = (const char *) m_pListBox -> GetItemData (iItem);
			ASSERT (NULL != pItemData);
			VERIFY (Lookup (pItemData, (CObject *&) pInfo));
			ASSERT (NULL != pInfo);

		// 	Addnew starten
			pSet -> AddNew ();		

		//	Feldinfos übernehmen
			pSet -> m_strNummer = strErzNummer;		//	zuerst Erzeuger

			pSet -> m_strAbfallnummer = pInfo -> m_strAbfArt;
			pSet -> m_strTransporteurnummer = pInfo -> m_strTransp;
			pSet -> m_strEntsorgernummer = pInfo -> m_strEntsorger;
			pSet -> m_strEntsorgungsverfahren = pInfo -> m_strVerfahren;
			pSet -> m_strPrioritaet = pInfo -> m_strPrio;
			pSet -> m_strNachweisnummer = pInfo -> m_strNachweis;

		//	Menge
			pSet -> m_dMenge_t = pInfo -> m_dMenge;

		//	Systemfelder
			pSet -> m_tErfassungsdatum = CTime::GetCurrentTime();						
			pSet -> m_bBearbeitet = FALSE;
												
			pSet -> Update ();		//  Daten speichern

			lCnt++;
		}
		
	/*	alte Version
		if (!IsEmpty ())	
		{   
			CWaitCursor wc;
	                               
			CString strKey, strVal, strInfo;
			
		//	Info an Nutzer ausgeben
			AfxFormatString1 (strInfo, IDS_OUTPUT_RECORDS, strErzNummer);
			stInfo.SetWindowText (strInfo);
			
			POSITION Pos = NULL;			
			CAbfallInfo* pInfo = NULL;             
		
			for (Pos = GetStartPosition(); Pos != NULL;)
			{
				GetNextAssoc (Pos, strKey, (CObject *&) pInfo);
				ASSERT (NULL != pInfo);
			
			//	nur selektierte ausgeben
				if (!bSelect || (bSelect && pInfo -> m_bIsSelected))
				{
					pSet -> AddNew ();		// 	Addnew starten
					
				//	Daten umkopieren
					pSet -> m_strAbfallnummer = pInfo -> m_strAbfArt;
					pSet -> m_dMenge_t = pInfo -> m_dMenge;
					pSet -> m_strTransporteurnummer = pInfo -> m_strTransp;
					pSet -> m_strEntsorgernummer = pInfo -> m_strEntsorger;
					pSet -> m_strNummer = strErzNummer;
					pSet -> m_strEntsorgungsverfahren = pInfo -> m_strVerfahren;
					pSet -> m_strPrioritaet = pInfo -> m_strPrio;
					pSet -> m_strNachweisnummer = pInfo -> m_strNachweis;

					pSet -> m_tErfassungsdatum = CTime::GetCurrentTime();						
					pSet -> m_bBearbeitet = FALSE;
														
					pSet -> Update ();		//  Daten speichern
					lCnt++;
				}
			}
		}
	alte Version
	*/
									                
		bRet = TRUE;		// alles OK
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

//	Selektion umkehren
/*
void CAbfallMap::ReverseSelection ()
{
	ASSERT (NULL != m_pListBox);

	if (IsEmpty ())
		return;

	CString strKey;
	POSITION Pos = NULL;			
	CAbfallInfo* pInfo = NULL;
		
	for (Pos = GetStartPosition(); Pos != NULL;)
	{
		GetNextAssoc (Pos, strKey, (CObject *&) pInfo);
		ASSERT (NULL != pInfo);
		pInfo->m_bIsSelected = !pInfo->m_bIsSelected;
	}	
}
*/

// 	Selektionsflag setzen, rücksetzen: m_dSelSumMenge wird neu berechnet				  
void CAbfallMap::ChangeSelection ()
{
	ASSERT (NULL != m_pListBox);

	if (IsEmpty ())
		return;

//	alles rücksetzen
	CString strKey;
	POSITION Pos = NULL;			
	CAbfallInfo* pInfo = NULL;
		
	for (Pos = GetStartPosition(); Pos != NULL;)
	{
		GetNextAssoc (Pos, strKey, (CObject *&) pInfo);
		ASSERT (NULL != pInfo);
		pInfo -> m_bIsSelected = FALSE;
	}	
	m_dSelSumMenge = 0.0;

//	alles neu berechnen
	if (m_pListBox -> GetSelectedCount () <= 0)	//	keine selektierten
		return;

//	Selektionsmenge neu berechnen
	const char *pKey = NULL;
	int iItemCnt = m_pListBox -> GetItemCount ();
	for (int iItem = 0; iItem < iItemCnt; iItem++)
	{
		if (!(m_pListBox -> GetItemState (iItem, LVIS_SELECTED) & LVIS_SELECTED))
			continue;

		pKey = (const char *) m_pListBox -> GetItemData (iItem);
		ASSERT (NULL != pKey);

	//	suche Info in der Map
		VERIFY (Lookup (pKey, (CObject *&) pInfo));
		ASSERT (NULL != pInfo);
		pInfo -> m_bIsSelected = TRUE;			//	Flag neu setzen
		
	//	SelectedMenge korr.
		m_dSelSumMenge += pInfo -> m_dMenge;			
	}
}

//	Vergleiche Inhalte beider Maps
CAbfallMap *CAbfallMap::IsEqual (CAbfallMap *pMap)
{
	ASSERT (NULL != pMap);
	ASSERT (this != pMap);		//	kein Vergleich mit sich selbst

//	Spezialfall, eine der beiden Mengen ist leer
	if (IsEmpty () || pMap->IsEmpty ())
		return NULL;
	
//	vergleiche Inhalte der Maps: wobei auch Identität besteht, wenn der Inhalt der Map
//	mit den kleineren Anzahl von Einträgen vollständig in der anderen existiert !
	CAbfallMap *pLookMap = this;
	CAbfallMap *pValMap = pMap;

	if (pLookMap->GetCount() < pValMap->GetCount())
	{
		pLookMap = pMap;
		pValMap = this;       
	}	
	
//	Vergleich starten					
	CString strKey;
	POSITION Pos = NULL;			
	CAbfallInfo* pInfo = NULL;
	double dValMenge = 0.0;
	for (Pos = pValMap->GetStartPosition(); Pos != NULL;)
	{
		pValMap->GetNextAssoc (Pos, strKey, (CObject *&) pInfo);
		ASSERT (NULL != pInfo);
		
	//	Menge speichern
		dValMenge = pInfo -> m_dMenge;		
		
	//	Eintrag in der anderen Map vorhanden ?		
		if (!pLookMap->Lookup (strKey, (CObject *&) pInfo) ||
		   (dValMenge != pInfo -> m_dMenge))		
			return NULL;
	}

	return pLookMap;
}

				  		  



                                