/*------------------------------------------------------------------------

File: TABLENAM.CPP

Realisiert die Verwaltung von Tabellennamen in einem Baum.
(Groß/Kleinschreibung wird nicht beachtet !) 

Erarbeitet: J. Benkenstein                      begonnen am: 17.10.1995
----------------------------------------------------------------------------*/

#include "pheader.h"		// vorübersetzter Header

#include <containr.hxx>
#include "tablenam.hxx"		// zugeh. Header

// globale Funktionen ---------------------------------------------------------
void* __export GetTable (void *pObj)
{
	return (void *) (((CTableName *) pObj) -> GetTableName ());
}

int __export CompTableNames (void *pKey1, void *pKey2)
{
	return lstrcmpi ((char *) pKey1, (char *) pKey2);
}

//	CTableName ----------------------------------------------------------------
CTableName :: ~CTableName (void)
{
	DELETE_VEC (m_pTableName);
}

BOOL CTableName :: Init (char *pTableName) 
{
//	prüfe Parameter
	if (!pTableName)
		return FALSE;

	m_pTableName = new char [lstrlen (pTableName) + 1];
	if (!m_pTableName)
		return FALSE;

	lstrcpy (m_pTableName, pTableName);
	return TRUE;
}

// CTableNameTree --------------------------------------------------------------
CTableNameTree :: CTableNameTree (void)
				: CTree (GetTable, CompTableNames)
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
BOOL CTableNameTree :: Exist (char *pTableName)
{
//	prüfe Parameter
	if (!pTableName || !*pTableName)
		return FALSE;

	CTable t(*this);         
	return t.Find (pTableName);                                            
}

// Tabellennamen speichern
BOOL CTableNameTree :: AddTable (char *pTableName)
{
//	prüfe Parameter
	if (!pTableName || !*pTableName)
		return FALSE;
		
//	Name bereits vorh. ?
	CTable t(*this);         
	if (t.Find (pTableName))
		return TRUE;
		
//	neuen Namen speichern
	CTableNameCreator Cr (*this);  
	CTableName *pTN = :: Create (Cr, CTableName); 
	return pTN -> Init (pTableName); 	                                            				
}

 
