/*------------------------------------------------------------------------

File: DBASE.CXX

DBASE - Implementation
beinhaltet allgemeine Funktionen für die Arbeit mit dBase-Dateien.

Erarbeitet: J. Benkenstein					  begonnen am: 16. Sept. 1992
----------------------------------------------------------------------------*/
				  
#include "pheader.h"

#include "dbase.htp"	   	// Selektion der zu komp. Klassen
#include <commonvu.hxx>
#include <containr.hxx>
#include <objfeld.hxx>	 	// für Klasse ObjNummer
#include <dbliste.hxx>	  	// für Klasse DB_Filter

#include "dbase.hxx"		// zugeh. Header
#include "exttabl.hxx"	  	// für Klasse ExtTabularListBox
#include "v_memofd.hxx"	 	// für Klasse MultiLineDialog
#include "v_dbase.hxx"	  	// für Klasse ShowFile

//  Konstanten
const short sMaxMovCnt = 3;		// max. 3mal Offsett für offenene Fenster erzeugen
const CoOrd XTransL =  20;		// x,y-Verschiebung eines dBase-Fensters
const CoOrd YTransL = -20;

// externe Variablen
extern "C" {
extern HINSTANCE g_hInstance;
}

// Konstruktor/Destruktor -----------------------------------------------------
dBaseDispatch :: dBaseDispatch (pWindow pParent, long lActObj)
			   : CListContainer ()
{
		_pW = pParent;
		_hWnd = pParent -> Handle (API_WINDOW_HWND);
		_pCB = CreateCodeBaseObj (g_hInstance);					 
		_lActObj = lActObj;
}

dBaseDispatch :: ~dBaseDispatch (void)
{
		EveryDelete ();
		DeleteCodeBaseObj ();
}

void __export dBaseDispatch :: UserDelete (void *pObj)
{
		((ShowFile *)pObj) -> ~ShowFile();
}

void dBaseDispatch :: DeleteOldWindows (void)
{
CRing r(*this);

		for (r.First(); r.Valid(); ) {
		Bool toDelete = FALSE;
				{
				ShowFileLock l(r);

						if (!l) { r.Next (); continue; }
						if (l -> ToDelete ()) toDelete = TRUE;
				}
				if (toDelete)   { r.Delete(); }
				else			{ r.Next(); }
		}
}

// ShowFile-Ojekte erzeugen und in Liste speichern
ErrCode dBaseDispatch :: ShowDBaseWindowField (char *pDBaseName,
						 char *pFieldName, char *pValue, ResourceFile *pRF,
						 short Type)
{
	ErrCode RC;

//  CodeBase-Fehler-Test
	if (RC = (ErrCode) _pCB -> error ())
		return RC;

	ShowFileCreator Cr(*this);
	short sCnt = (short) (Count () % sMaxMovCnt);
	Point TransL (sCnt * XTransL, sCnt * YTransL);
	ShowFile *pSF = Create (Cr, ShowFile) (_pW, _pCB, pDBaseName, pFieldName,
								pValue, this, pRF, Type, TransL);
	if (pSF == NULL)
	{		
		DEX_Error (RC_ShowDBaseWin, EC_NOMEMORY);
		return EC_NOMEMORY;			
	}

	if ((RC = pSF -> Result ()) != EC_OKAY)
		return RC;			  // Fehlermeldg. durch Konstr. ber. ausgegeben

	pSF -> Darstellen ();	   // dBase-Fenster darstellen

	return pSF -> Result ();
}

/*
Diese Funktion könnte als 2. Memberfunktion für die Klasse dBaseDispatch
verwendet werden.
// Selektion über boolschen dBase-Expression
ErrCode ShowDBaseWindowExpr (pWindow pW, HelpDisplay *pHD, pchar FullDBaseName,
							 pchar pTagName, pchar pKeyStr, pchar pExprStr,
							 ResourceFile *pRF)
{
	ErrCode RC;
	DataMemo *pMemo = NULL;

//  CodeBase-Objekt erzeugen
	CodeBase *pCBase = GetCodeBaseObj ();
	if (!pCBase)
		return (ErrCode) db_error (RC = EC_NOMEMORY, RC_ShowDBaseWin);

//  Memo-Objekt erzeugen
	pMemo = new DataMemo (pCBase, FullDBaseName);
	if (!pMemo || (RC = (ErrCode) pCBase -> error ()))
		db_error (RC, RC_ShowDBaseWin);
	else {
		// Filter init.
		DBaseObjNummer ON (0);
		DB_Filter DBF (pCBase, *(DataIndex *)pMemo, ON, pTagName, pKeyStr, pExprStr);
		if ((RC = DBF.Result ()) == EC_OKAY)
			RC = DBF.Check (); // nicht OR, nicht unique
		if (RC != EC_OKAY)
			db_error (RC, RC_ShowDBaseWin);
		else {
			// dBase-Sätze im Fenster anzeigen
			ShowFile SF (pW, pHD, pCBase, pMemo, pRF);
			if ((RC = SF.Result ()) != EC_OKAY)
				db_error (RC, RC_ShowDBaseWin);
			else {
				SF.Darstellen (FullDBaseName, &ON.RA ());
				RC = SF.Result ();
			}
		}
	}
	DELETE (pMemo);

	return RC;
}
*/

// Funktionen für den Baum der DBaseDispatcher (für jedes ObjRechFenster einer)
DBaseDispatchTree :: DBaseDispatchTree (void)
				   : CTree (RetrievehWnd, CmphWnd)
{
		// nothing to do
}

DBaseDispatchTree :: ~DBaseDispatchTree (void)
{						  
		EveryDelete ();		 // alle Dispatcher
}


void __export DBaseDispatchTree :: UserDelete (void *pObj)
{
		((dBaseDispatch *)pObj) -> ~dBaseDispatch();
}


// Alle Fenster eines Dispatchers löschen -------------------------------------
void DBaseDispatchTree :: AllDelete (HWND hWnd)
{
CTable t(*this);													 

		if (t.Find ((void *) &hWnd)) {
				{
				dBaseDispatchLock l(t);
		
						if (l) l -> EveryDelete();	
				}
				t.Delete();	 // Dispatcher für dieses Fenster freigeben
		}					 
}
		 

ErrCode DBaseDispatchTree :: ShowDBaseWindowField (HWND hWnd, char *pName, 
												char *_pDBaseField, char *_pDBaseKey, 
												ResourceFile *pRF, short Type)
{
CTable t(*this);

		if (t.Find ((void *) &hWnd)) {   // dBaseDispatch suchen
		dBaseDispatchLock l(t);
		
				if (l) 
						return l -> ShowDBaseWindowField (pName, _pDBaseField, _pDBaseKey, pRF, Type);
		} 
		
return EC_OKAY;
}


long DBaseDispatchTree :: ActObj (HWND hWnd)
{
		if (hWnd == 0) return -1L;

CTable t(*this);

		if (t.Find ((void *) &hWnd)) {
		dBaseDispatchLock l(t);
		
				if (l) return l -> ActObj();
		}
		
return -1L;
}

void *RetrievehWnd (void *pObj)
{
		return (void *) (& ((dBaseDispatch *)pObj) -> hWnd());
}

int CmphWnd (void *pObj1, void *pObj2)
{
		return *(HWND *)pObj1 - *(HWND *)pObj2;
}
