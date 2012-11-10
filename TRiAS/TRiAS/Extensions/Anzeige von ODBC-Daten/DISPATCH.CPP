/*------------------------------------------------------------------------

File: DISPATCH.CPP

DISPATCH - Implementation
beinhaltet allgemeine Funktionen für die Arbeit mit ODBC-Dateien.

Erarbeitet: J. Benkenstein                      begonnen am: 16. Sept. 1992
												Stand vom 12. März 1994
----------------------------------------------------------------------------*/

#include "pheader.h"
#include "odbcext.hr"    		// Resourcen-Defines            
                        
#include <hpp/toolbar.hpp>      	// CToolBarEx                         
#include <hpp/columnst.hpp>         // CColumns
#include <hpp/collist.hpp>          // CColumnObjArray
#include "recset.hpp"           // CRecSet
#include <hpp/relation.hpp>         // DBaseRel

#include "v_dbase.hpp"      	// für Klasse ShowFile
#include "dispatch.hpp"        	// zugeh. Header

//  Konstanten
const short XTransL = 20;   	// x,y-Verschiebung eines dBase-Fensters
const short YTransL = 20;
const short sMaxTransCnt = 3;	// max. 3 Fenster-Offsetts

// Konstruktor/Destruktor -----------------------------------------------------
dBaseDispatch :: dBaseDispatch (HWND Parent, long lActObj)
		   : CListContainer ()
{
	//_pHD = pHD;                
	_hWnd = Parent;
	_lActObj = lActObj;
}

dBaseDispatch :: ~dBaseDispatch (void)
{
	EveryDelete ();
}

void __export dBaseDispatch :: UserDelete (void *pObj)
{
	// ((ShowFile *)pObj) -> DestroyWindow ();
	((ShowFile *)pObj) -> ~ShowFile();
}

// ShowFile-Ojekte erzeugen und in Liste speichern
ErrCode dBaseDispatch :: ShowDBaseWindowField (const char *pAliasName, const char *pFieldName, 
											   const char *pFieldValue)
{
	ErrCode RC;

    short Cnt = (short) (Count () % sMaxTransCnt);
    CPoint TransL (Cnt * XTransL, Cnt * YTransL);
	ShowFileCreator Cr (*this);  
	ShowFile *pSF = NULL;
	TRY 
	{      
		// CWnd *pParent = _hWnd != NULL ? CWnd :: FromHandle (_hWnd) : NULL;
		ASSERT (NULL != _hWnd);
		CWnd ParentWindow;
		VERIFY (ParentWindow.Attach (_hWnd));
		pSF = :: ContCreate (Cr, ShowFile) (&ParentWindow, this, TransL, (char *)pAliasName,
										   (char *) pFieldName, (char *)pFieldValue);
		ParentWindow.Detach ();
	}                                                 
	CATCH (CMemoryException, cme)
	{                                                                                         
		DEX_Error (RC_ShowOdbcWin, EC_NOMEMORY);
		return EC_NOMEMORY;                     
	}                                   
	END_CATCH

    if ((RC = pSF -> Result ()) != EC_OKAY)
		return RC;              // Fehlermeldg. durch Konstr. ber. ausgegeben

// KK000425 - Fenster Caption modifizieren
	char * pText = new char [_MAX_PATH];
	*pText = '\0';
	CString strFormat;
	strFormat.LoadString (IDS_VIEWFRAMECAPTION);		
	wsprintf (pText, strFormat, (const char *)pAliasName);
	pSF->SetWindowText(pText);
	DELETE_OBJ(pText);


    pSF -> Darstellen ();       // dBase-Fenster darstellen

    return pSF -> Result ();
}

// Funktionen für den Baum der DBaseDispatcher (für jedes ObjRechFenster einer)
DBaseDispatchTree :: DBaseDispatchTree (void)
				   : CTree (RetrievehWnd, CmphWnd)
{
}

DBaseDispatchTree :: ~DBaseDispatchTree (void)
{                          
	EveryDelete ();         // alle Dispatcher
}


void __export DBaseDispatchTree :: UserDelete (void *pObj)
{
	((dBaseDispatch *)pObj) -> ~dBaseDispatch();
}


// Alle Fenster eines Dispatchers löschen -------------------------------------
void DBaseDispatchTree :: AllDelete (HWND hWnd)
{
	CTable t(*this);                                                     

	if (t.Find ((void *)&hWnd)) 
	{
		{
		dBaseDispatchLock l(t);
	
			if (l) l -> EveryDelete();    
		}
		t.Delete();     // Dispatcher für dieses Fenster freigeben
	}                     
}
	 
ErrCode DBaseDispatchTree :: ShowDBaseWindowField (HWND hWnd, char *pAliasName,
							 char *_pDBaseField, char *_pDBaseKey)
{
	CTable t(*this);

	if (t.Find ((void *) &hWnd)) {   // dBaseDispatch suchen
		dBaseDispatchLock l(t);
	
		if (l) 
			return l -> ShowDBaseWindowField (pAliasName,_pDBaseField, _pDBaseKey);
	} 
	
	return EC_OKAY;
}


long DBaseDispatchTree :: ActObj (HWND hWnd)
{
	if (hWnd == 0) 
		return -1L;

	CTable t(*this);

	if (t.Find ((void *) &hWnd)) {
		dBaseDispatchLock l(t);
	
		if (l) 
			return l -> ActObj();
	}
	
	return -1L;
}

void * __export RetrievehWnd (void *pObj)
{
	return (void *) (& ((dBaseDispatch *)pObj) -> hWnd());
}

int __export CmphWnd (void *pObj1, void *pObj2)
{
	return *(HWND *)pObj1 - *(HWND *)pObj2;
}
