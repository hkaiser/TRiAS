/*------------------------------------------------------------------------

File: TABLENAM.CPP

Realisiert die Verwaltung von Tabellennamen in einem Baum.
(Groß/Kleinschreibung wird nicht beachtet !) 

Erarbeitet: J. Benkenstein                      begonnen am: 17.10.1995
----------------------------------------------------------------------------*/

#include "pheader.h"		// vorübersetzter Header

#include "tablenam.hpp"		// zugeh. Header

// globale Funktionen ---------------------------------------------------------
void* __export GetTable (void *pObj)
{
	return (void *)(const char *)(((CTableName *) pObj) -> m_strTableName);
}

int __export CompareTableNames (void *pKey1, void *pKey2)
{
	return strcmpi ((char *) pKey1, (char *) pKey2);
}

//	CTableName ----------------------------------------------------------------
BOOL CTableName :: Init (const char *pTableName) 
{
//	prüfe Parameter
	if (!pTableName || !*pTableName)
		return FALSE;

	TRY
	{
		m_strTableName = pTableName;
	}
	CATCH (CMemoryException, me)
	{
		THROW_LAST ();	// Exception weitergeben				
	}
	END_CATCH

	return TRUE;
}

// CTableNameTree --------------------------------------------------------------
CTableNameTree :: CTableNameTree (void)
				: CTree (GetTable, CompareTableNames)
{
	// nothing to do	
}

CTableNameTree :: ~CTableNameTree (void) 
{ 
	EveryDelete (); 
}	

void __export CTableNameTree :: UserDelete (void *pObj)
{
	((CTableName *) pObj) -> ~CTableName ();	
}

// Tabelle bereits vorhanden
BOOL CTableNameTree :: Exist (const char *pTableName)
{
//	prüfe Parameter
	if (!pTableName || !*pTableName)
		return FALSE;

	CTable t(*this);         
	return t.Find ((void *)pTableName);                                            
}

// Tabellennamen speichern
BOOL CTableNameTree :: AddTable (const char *pTableName)
{
//	prüfe Parameter
	if (!pTableName || !*pTableName)
		return FALSE;
		
//	Name bereits vorh. ?
	CTable t(*this);         
	if (t.Find ((void *)pTableName))
		return TRUE;
		
//	neuen Namen speichern
	TRY
	{
		CTableNameCreator Cr (*this);  
		CTableName *pTN = :: ContCreate (Cr, CTableName); 
		pTN -> Init (pTableName);
	}
	CATCH (CMemoryException, me)
	{
		THROW_LAST ();	// Exception weitergeben
	}
	END_CATCH

	return TRUE; 	                                            				
}

 
