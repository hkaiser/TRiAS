/*
FILE: TABLINFO.HPP

Das Modul stellt allgemeine Klassen für die Verwaltung und Darstellung 
von ODBC-Tabellen bereit.

Erarbeitet: J. Benkenstein 					Stand vom: 30.10.1994
*/
                  
#ifndef _TABLINFO_HPP
#define _TABLINFO_HPP      

class CDatabase;            

class CTableInfo : public CColumns
{                                                             
private:
	ErrCode m_ErrCode;
	
public:
//	Konstruktor/Destruktor              
	CTableInfo (CDatabase *pDataBase, const char *pTableName); // Tabelle "Öffnen"
	~ CTableInfo (void);
	
//	weitere Member                              
	ErrCode Result (void) { return m_ErrCode; }		// Operation-Flag

	// alle möglichen Recherche-Felder in eine Listbox ausgeben
	ErrCode OutputRechercheFields (CListBox &, 
								   int &MaxStringLen, // zählt Zeichenanzahl
								   BOOL bOutputTableName = TRUE);	               
	                                   
	// Beschreibungs-Information eines Feldes (Typ und Länge) ausgeben	                                   
	ErrCode OutputDescription (CEdit &, const char *pFieldName);
	                                       
	// friend-Funktionen	                                       
	friend void *GetTableName (void *pObj);
};                   
 
//	Der Baum speichert CTableInfo-Objekte    
class CTableInfoTree : public CTree
{                                       
private:
	CDatabase *m_pDataBase;
	ErrCode m_ErrCode;
	
protected:
	void UserDelete (void *pObj);	
	
public:        
	// Konstruktor/Destruktor
	CTableInfoTree (CDatabase *pDataBase);
	~ CTableInfoTree (void);	 	
	
	// weitere Member
	ErrCode Result (void) { return m_ErrCode; }	// Operations-Flag			
	   
	//	TabellenInfo-Objekte erzeugen: Tabellen-Namen durch Komma getrennt
	ErrCode CreateTables (const char *pTableNames);			   
	   
	// Recherche-Felder aller Tabellen ausgeben	                                      
	ErrCode OutputRechercheFields (CListBox &, int &MaxStringLen); // zählt Zeichenanzahl
	
	// Beschreibungs-Information eines Feldes (Typ und Länge) einer Tabelle ausgeben
	ErrCode OutputDescription (CEdit &, 					// Tabellen- und Feldname	
							   const char *pTableFieldName);// werden durch "." getrennt
};
DeclareLock (CTableInfoTree, CTableInfo);    

    
#endif 		// _TABLINFO_HPP