/*
File: TEXTCONN.HXX

Realisiert die Ausgabe aller Informationen in der aktuellen Projekt-INI-Datei 
und den ODBC-Dateien, die zur Anbindung von Texdateien über ODBC notwendig sind.

Erarbeitet: J. Benkenstein				Stand vom: 30. August 1994
*/
    
#ifndef _TEXT_CONN_HXX
#define _TEXT_CONN_HXX    

#ifndef NO_TEXTDATINFO    
class CTextDatInfo
{
private:
	char *m_pName;			// i.a. AliasName der Slave-Datei
	BOOL m_bOpFlag;			// Konstruktor-Flag
	   
public:	    
//	Konstruktor/Destruktor
	CTextDatInfo (char *pName);
	~ CTextDatInfo (void);
	
//	weitere Zugriffs-Funktionen
	Bool OpFlag (void) { return m_bOpFlag; }
	char *GetName (void) { return m_pName; }	
};                  
#endif 		// NO_TEXTDATINFO                        
               
#ifndef NO_TEXTDATINFOLIST               
//	Liste speichert 'TextDatInfos'-Objekte     
class ResourceFile;

class CTextDatInfoList : public CListContainer
{
private:                                                       
	ResourceFile *m_pRF;			
	char *m_pMaster;			// AliasName der Master-Datei
	char *m_pKoppelFeld;		// Koppelfeld
	ulong m_lMKode;				// zugeh. Merkmalskode
	ulong m_lIdent;				// zugeh. Trias-ID
	short m_TextDatLength;		// Länge aller TextDat-Einträge
	
protected:
	void __export UserDelete (void *pObj);	
	
public:
//	Konstrutkro/Destruktor
	CTextDatInfoList (ResourceFile *pRF);
	~ CTextDatInfoList (void);
	
//	weitere Zugriffs-Funktionen
	BOOL SetMaster (char *pNewMaster);
	BOOL SetKoppelFeld (char *pKoppelFeld);
	void SetIdent (ulong lNewIdent);
	void SetMKode (ulong lNewMKode);		
	                              
	ErrCode OutputConnectInfos (void); // Alle Infos zur Anbindung ausgeben
};
DeclareLock (CTextDatInfoList, CTextDatInfo);
#endif		// NO_TEXTDATINFOLIST

#endif 		// _TEXT_CONN_HXX

					



