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
	CString m_strTableName;

public:	
//	Konstruktor/Destruktor 
	CTableName	(void) {}
	~CTableName (void) {}
	BOOL Init (const char *pTableName); 			

	friend void *GetTable (void *pObj);
	friend int CompareTableNames (void *pKey1, void *pKey2);
};

class CTableNameTree : public CTree
{
protected:
	void UserDelete (void *pObj);

public:
	CTableNameTree  (void);
	~CTableNameTree (void);	

	BOOL AddTable (const char *pTableName);	// Tabellennamen speichern
	BOOL Exist (const char *pTableName);		// Tabelle bereits vorhanden
};
DeclareLock (CTableNameTree, CTableName);

#endif // _TABLENAM_HPP
