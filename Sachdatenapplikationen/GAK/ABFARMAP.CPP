/*
Datei: ABFARMAP.CPP

Das Modul relisert die Verwaltung einer Abfallartenmap.

Erarbeitet: J. Benkenstein		Stand vom: 7.1.1997
*/

#include "stdafx.h"		//	prec. Header
#include "abfarmap.h"		// 	zugeh. Header

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CAbfallArtenMap::~CAbfallArtenMap(void)
{
	if (!IsEmpty ())	
	{                                  
		CString strKey;
		POSITION Pos = NULL;			
		CAbfallArt* pInfo = NULL;
		
		for (Pos = GetStartPosition(); Pos != NULL;)
		{
			GetNextAssoc (Pos, strKey, (CObject *&) pInfo);
			ASSERT (NULL != pInfo);
			DELETE_OBJ (pInfo);				
		}
	}                    
}	

//	neue Info speichern
BOOL CAbfallArtenMap::AddAbfallArt (const CString &strAbfallArt, double dDichte, BOOL bSonderAbfall)
{
//	prüfe Parameter
	if (strAbfallArt.IsEmpty () || (dDichte <= 0))
		return FALSE;

//	neue Info in Map einhängen: bereits vorhandene wird ersetzt
	CAbfallArt* pInfo = new CAbfallArt (dDichte, bSonderAbfall);
	if (NULL == pInfo)
		AfxThrowMemoryException ();
	SetAt (strAbfallArt, pInfo);			

	return TRUE;
}
