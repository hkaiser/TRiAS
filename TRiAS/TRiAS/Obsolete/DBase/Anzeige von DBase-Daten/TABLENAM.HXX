/*------------------------------------------------------------------------

File: TABLENAM.HPP

Realisiert die Verwaltung von Tabellennamen in einem Baum.
(Groﬂ/Kleinschreibung wird nicht beachtet !) 

Erarbeitet: J. Benkenstein                      begonnen am: 17.10.1995
----------------------------------------------------------------------------*/

#ifndef _TABLENAM_HPP
#define _TABLENAM_HPP

class CTableName
{
	char *m_pTableName;

public:	
//	Konstruktor/Destruktor 
	CTableName	(void) { m_pTableName = NULL; }
	~CTableName (void);
	BOOL Init (char *pTableName); 			
	char *GetTableName (void) { return m_pTableName; }
};

class CTableNameTree : public CTree
{
protected:
	void UserDelete (void *pObj);

public:
	CTableNameTree  (void);
	~CTableNameTree (void);	

	BOOL AddTable (char *pTableName);	// Tabellennamen speichern
	BOOL Exist (char *pTableName);		// Tabelle bereits vorhanden
	
	friend void *GetTable (void *pObj);
	friend int CompTableNames (void *pKey1, void *pKey2);
};
DeclareLock (CTableNameTree, CTableName);

#endif // _TABLENAM_HPP
