/*
File: AFNAMEL.HXX

Das Mudul verwaltet Einträge einer Text-Datei in der Section
	<FeldName>=<AliasFeldName>    
die einer dBASE-Datei in der Projekt-INI über den Eintrag
	[dBASE-AliasFiles]
	<AliasName>=<AliasDateiName>
zugeordnet werden können.

Erarbeitet: J. Benkenstein						Stand vom 11.9.1995		
*/             

#ifndef AFNAMEL_HXX
#define AFNAMEL_HXX

class CAliasFieldName
{            
private:	
	char *m_pFieldName;			// dBASE-FeldName
	char *m_pAliasName;			// zugeh. AliasName

public:	                       
//	Konstruktor/Destruktor	                       
	CAliasFieldName (void) { m_pFieldName = m_pAliasName = NULL; }
	~ CAliasFieldName (void);	
                            
// 	weitere Member
	Bool Init (char *pFieldName, char *pAliasName);
	char *FieldName (void) { return m_pFieldName; }
	char *AliasName (void) { return m_pAliasName; }

//  friend Funktionen
    friend void* GetFieldName (void *pObj);            // Get-Key-Funktion
};  

//	verwalte o.g. Einträge in einem Baum
class CAliasFieldNameTree : public CTree 
{
private:
	short m_sMaxAlCnt;				// max. Anzahl von Zeichen in einem AliasNamen
	
protected:
#ifdef WIN32
	void UserDelete (void *pObj);
#else
	void __export UserDelete (void *pObj);
#endif

public:
//  Konstruktor/Destruktor
    CAliasFieldNameTree (void);       	
    ~ CAliasFieldNameTree (void);      // Tabelleninhalt löschen

// 	Beschreibungsliste über AliasNamen einlesen		
	Bool Init (char *pAliasFileName);
	
//	max. Größe der AliasNamen lesen
	short GetMaxAliasSize (void) { return m_sMaxAlCnt; }						
	                                      
//	lese zugeh. AliasNamen über Feldnamen	                                      
	char* GetAliasName (char *pFieldName);
};
DeclareLock (CAliasFieldNameTree, CAliasFieldName);

#endif // AFNAMEL_HXX