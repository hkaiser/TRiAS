// abfmap.h : interface of the CAbfallMap
//
/////////////////////////////////////////////////////////////////////////////
                                        
#ifndef _ABFMAP_
#define _ABFMAP_                                         

class CAbfallInfo : public CObject
{                          
	DECLARE_DYNAMIC(CAbfallInfo)
public:
//	Konstruktor/Destruktor
	CAbfallInfo (const CString& strAbfArt,
				 const CString& strTransp, const CString& strEntsorger, 
				 const double& dMenge, const double dMengeEn,
				 const CString& strNachweisNr, const CString &strVerfahren, 
				 const CString& strPrio, BOOL bSonderAbfall, 
			     const CString& strEntsorgerBemerkungen,
				 const CString& strTransporteurBemerkungen,	
				 BOOL bIsSelected = FALSE);       
	virtual ~CAbfallInfo(void) {}				 
	
	CString	m_strTransp,
			m_strEntsorger,
			m_strNachweis,
			m_strVerfahren,
			m_strPrio,
			m_strEntsorgerBemerkungen,
			m_strTransporteurBemerkungen,
			m_strAbfArt;
			
	double m_dMenge, m_dMengeEn;
	BOOL m_bIsSelected, m_bSonderAbfall;
};
                        
class CAbfalArtenMap;               
class COutputSet;                         
class CAbfallMap : public CMapStringToOb
{
DECLARE_DYNAMIC(CAbfallMap)
private:                
	BOOL m_bOnlySonderAbf;			//	nur Sonderabfall prüfen
	double m_dSumMenge;				//	Gesamtmenge	
	double m_dSelSumMenge;			//	Gesamtmenge aller selektierten Infos
	double m_dMinMengeRec;				//	min. Menge eines Eintrags
	CAbfallArtenMap *m_pAbfArtMap;	//	Map mit gültigen Abfallarten
	CListCtrl *m_pListBox;			//	zugeh. Listbox

public:
//	Konstruktor/Destruktor
	CAbfallMap (CAbfallArtenMap *pMap, CListCtrl *pList,
				BOOL bOnlySonderAbfall, double dMinMenge);
	~CAbfallMap (void);				// löschen aller Einträge 
	                    
//	einfache Lesefunktionen	                    
	double& GetSumMenge (void) { return m_dSumMenge; }
    double& GetSelSumMenge (void) { return m_dSelSumMenge; }	
	                       
//	neue Info in Map aufnehmen: prüft Parameter	                       
	BOOL AddInfo (const char *pAbfArt, const CString& strTransp,
				  const CString& strEntsorger, const double& dMengeT, const double dMengeEn,
				  const CString& strNachweisNr, const CString &strVerfahren, 
				  const CString& strPrio, 
				  const CString& strEntsorgerBemerkungen,
				  const CString& strTransporteurBemerkungen,	
				  BOOL bIsSelected = FALSE);
				  
//	Datensätze in ListBox ausgeben                              
//	Key über SetItemDataPtr speichern               
	BOOL OutputInListBox (BOOL bSelect, BOOL bIgnoreSelect = FALSE);	
	
//	selektierte Datensätze in den übergebenen Set ausgeben                                         
    BOOL OutputInSet (COutputSet *pSet, const CString &strErzNummer, BOOL bSelect, 
					  CStatic &stInfo, long &lCnt, BOOL bReverse = FALSE);
	
// 	Selektionsflag setzen, rücksetzen: m_dSelSumMenge wird neu berechnet				  
    void ChangeSelection ();	

//	Selektion umkehren
	// void ReverseSelection ();

//	Maps indentisch    
	CAbfallMap* IsEqual (CAbfallMap *);	
};	

                
#endif	// _ABFMAP_
                