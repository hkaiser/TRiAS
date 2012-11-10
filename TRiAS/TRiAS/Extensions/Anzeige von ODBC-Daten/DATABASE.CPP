/*
File: DATABASE.CPP
 - Modul zur Verwaltung eines CDataBase-Objekts.

Erarbeitet: J.Benkenstein						Stand vom: 1. Juni 1994
*/

#include "pheader.h"		
#include "odbcext.hr"	// Resource-Konstanten

#include <containr.hxx>		
#include <hpp/odbcerr.hpp>		// OdbcError
#include <hpp/getodbci.hpp>		// DSNParamOk
#include "database.hpp"		// zugeh. Header
#include "profile.hpp"		// DBaseProFile
#include <hpp/strdup.hxx>		// StringDup

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//	CDataBaseEx ------------------------------------- 
CDataBaseEx :: CDataBaseEx (void)
             : CDatabase ()  
{                   
}                   

CDataBaseEx :: ~CDataBaseEx (void)
{
	Close ();
}                

BOOL CDataBaseEx :: OpenAlias (const char *pAliasName, HPROJECT hProject)
{                          
//	prüfe Parameter
	if (!pAliasName)
	{               
		DEX_Error (RC_OpenCDataBaseEx, EC_ILLPARS);
		return FALSE;
	}	

// 	identifikatorbezogenen DataSourceName laden	
Profile ProFile(hProject);
StringDup strDSN (ProFile.GetDataSourceName (pAliasName, m_tType), FALSE);

	if (! strDSN)
	{   
		DEX_Error (RC_OpenCDataBaseEx, EC_NODSN);
		return FALSE;		
	}		

BOOL bRet = OpenDSN (strDSN, m_tType);
	
	return bRet;
}

//	Data-Source-Name gegeben
BOOL CDataBaseEx :: OpenDSN (const char * pDSN, DataSourceType tType)
{                          
//	prüfe Parameter
	ASSERT (UserDataSource == tType || FileDataSource == tType || SystemDataSource == tType);

	if (!pDSN)
	{               
		DEX_Error (RC_OpenCDataBaseEx, EC_ILLPARS);
		return FALSE;
	}	

//	evtl. bereits geöffnet ?
	if (IsOpen ())
		return TRUE;

//	DefaultDir-Eintrag ok ?
	if (!DSNParamOk (pDSN, tType))		
		return FALSE;

BOOL bRet = TRUE;

	TRY {		           
		// LPCTSTR lpszDSN, BOOL bExclusive = FALSE, BOOL bReadOnly = FALSE, LPCTSTR lpszConnect = “ODBC;”, BOOL bUseCursorLib = TRUE );
		if (FileDataSource == tType)
		{
			CString strConnect;
			AfxFormatString1 (strConnect, IDS_FILE_DSN_FORMAT, pDSN);
			CDatabase::OpenEx(strConnect, useCursorLib);
		}
		else
		{
			if ((SystemDataSource == tType) || (UserDataSource == tType))
				CDatabase::Open(pDSN/*, FALSE, FALSE, "ODBC;", FALSE*/);	
			else
			{
				DEX_Error (RC_OpenCDataBaseEx, EC_ILLPARS);
				bRet = FALSE;
			}				
		}
	}
	CATCH (CDBException, dbe)
	{		 
		OdbcError Err (dbe);
		Err.Show (RC_OpenCDataBaseEx);
		bRet = FALSE;
	}		
	AND_CATCH (CMemoryException, cme)
	{       
		DEX_Error (RC_OpenCDataBaseEx, EC_NOMEMORY);
		bRet = FALSE;
	}
	END_CATCH    
	
//	Type ggf. setzen		
	m_tType = bRet ? tType : NoDataSource;
	return bRet;
}

void CDataBaseEx :: Close (void)
{
	if (IsOpen ())
		CDatabase :: Close ();
}   

// 	globale Funktionen
//	Get-Key-Funktion für ff. Baum
void* __export GetDSN (void *pObj)
{
	return (void *) ((CDataBaseExt *) pObj) -> DataSourceName ();
}                     

int __export CompareDSN (void *pObj1, void *pObj2)
{
	return strcmpi ((char *) pObj1, (char *) pObj2);
}                   

// CDataBaseExt ---------------------------------------------
CDataBaseExt :: CDataBaseExt (const char *pDSN, DataSourceType tType)
		      : CDataBaseEx () 	
{   
	ASSERT_VALID (this);    
	ASSERT (pDSN != NULL && AfxIsValidString (pDSN));
	ASSERT (UserDataSource == tType || FileDataSource == tType || SystemDataSource == tType);

	TRY
	{
		m_strDSN = pDSN;
		m_tType = tType;
	}
	CATCH (CMemoryException, me)
	{
		THROW_LAST ();
	}
	END_CATCH
}                   

BOOL CDataBaseExt :: Open (void)
{
	return OpenDSN (m_strDSN, m_tType);
}

// CDataBaseExTree --------------------------------------------
CDataBaseExtTree :: CDataBaseExtTree (void)
				  : CTree (GetDSN, CompareDSN)
{
	m_lRefCnt = 0;
}                             

CDataBaseExtTree :: ~ CDataBaseExtTree (void)
{
	RemoveAllDataSources ();
}                                                      

void __export CDataBaseExtTree :: UserDelete (void *pObj)
{   
	((CDataBaseExt *) pObj) -> ~CDataBaseExt ();
}    

//	DataSource über DSN laden
CDataBaseExt *CDataBaseExtTree :: GetDataSourceDSN (const char *pDSN, DataSourceType tType)
{
//	prüfe Parameter
	if (!pDSN)
	{               
		DEX_Error (RC_GetDataBaseCDataBaseExTree, EC_ILLPARS);
		return NULL;
	}	

	CTable tb (*this); 
	if (tb.Find ((void *) pDSN))	
	{
		CDataBaseExtLock pDB (tb);
		if (pDB)
		{
			if (pDB -> OpenDSN (pDSN, tType))
			{
#ifdef WIN32			
				InterlockedIncrement (&m_lRefCnt);		
#else 
				m_lRefCnt++;				
#endif				
				return pDB;
			}
		}
		else
		{
			DEX_Error (RC_GetDataBaseCDataBaseExTree, EC_LOCKERROR);
		}

		return NULL;
	}
	
//	sont neues Objekt erzeugen                       
	TRY
	{                                       
		CDataBaseExtCreator cr (*this);
		CDataBaseExt *pCO = :: ContCreate (cr, CDataBaseExt) (pDSN, tType);
		if (pCO -> OpenDSN (pDSN, tType))
		{                   
#ifdef WIN32		
			InterlockedIncrement (&m_lRefCnt);		
#else 
			m_lRefCnt++;			
#endif			
			return pCO;
		}
	}
	CATCH (CMemoryException, cme)
	{        
	    DEX_Error (RC_GetDataBaseCDataBaseExTree, EC_NOMEMORY);
	}
	END_CATCH

	return NULL;
}

// zum geg. AiasNamen das DSN-Objekt lesen (ggf. erzeugen und öffnen)	                                            
CDataBaseExt *CDataBaseExtTree :: GetDataSource (const char *pAliasName, HPROJECT hProject) // JG 9903111
{
//	prüfe Parameter
	if (!pAliasName)
	{               
		DEX_Error (RC_GetDataBaseCDataBaseExTree, EC_ILLPARS);
		return NULL;
	}	
	
// 	identifikatorbezogenen DataSourceName laden	
	Profile ProFile(hProject);
	DataSourceType tType = NoDataSource;
	StringDup strDSN (ProFile.GetDataSourceName (pAliasName, tType), FALSE);
	if (! strDSN)
		return NULL;		

	return GetDataSourceDSN (strDSN, tType);
}				

void CDataBaseExtTree :: RemoveDataSource (CDataBaseExt *pDataBase)
{
	if (!pDataBase)
		return;

	CTable tb (*this); 
	if (tb.Find ((void *) pDataBase -> DataSourceName ()))	
#ifdef WIN32	
		InterlockedDecrement (&m_lRefCnt);
#else 
		m_lRefCnt--;
#endif		
}

void CDataBaseExtTree :: RemoveAllDataSources (void)
{
	ASSERT (!HasReferences ());		// Referenzen dürfen nicht mehr ex.
	EveryDelete ();
	m_lRefCnt = 0;
}

BOOL CDataBaseExtTree :: HasReferences (void)
{
#ifdef WIN32
	return InterlockedExchange (&m_lRefCnt, m_lRefCnt) > 0 ? TRUE : FALSE;
#else
	return m_lRefCnt > 0 ? TRUE : FALSE;
#endif 
}


