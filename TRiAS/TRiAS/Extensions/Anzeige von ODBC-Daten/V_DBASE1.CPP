/*------------------------------------------------------------------------
File: V_DBASE1.CPP

View_dBase -
gibt den Inhalt einer ODBC-Tabelle satzweise in eine Listbox aus.

Erarbeitet: J. Benkenstein              am: 19. Dez. 1991
								 Stand vom: 1. Juni 1994
---------------------------------------------------------------------------*/

#include "pheader.h"                    // vorübersetzten Header
#include "odbcext.hr"					// Resource-Konstanten
					    
#include <hpp/getodbci.hpp>
#include "profile.hpp"                 	// DBaseProFile
#include <hpp/toolbar.hpp>					// CToolBarEx
#include <hpp/waitcur.hpp>                  // CWaitCursor 
#include <hpp/columnst.hpp>                 // CColumns
#include "recset.hpp"                   // CRecSet
#include <hpp/collist.hpp>                  // CColumnObjArray

#include "v_dbase.hpp"                  // zugeh. Header

// externe Funktionen
void CallMessageQueue (void);		// Steuerung an Windows zum Nachzeichnen

// globalen Speicher anfordern
char * Alloc (long Count)
{
    HGLOBAL handle = GlobalAlloc (GHND, (DWORD) Count);
    if (!handle)
		return NULL;
    else
		return (char *) GlobalLock (handle);
}

// globalen Speicher wieder freigeben
BOOL FreeMemory (char * pChars)
{
#ifdef WIN32
    HGLOBAL handle = (HGLOBAL) GlobalHandle (pChars);
#else                                                
	HGLOBAL handle = (HGLOBAL) GlobalHandle (HIWORD (pChars));
#endif    
    if (! handle)
		return FALSE;
    if (! GlobalUnlock (handle))    // wenn Speicher nicht mehr benötigt
		return GlobalFree (handle) == NULL;
	else
		return FALSE;		
}

// globalen Speicher vergrößern
char * ReAlloc (char * pChars, long Count)
{
#ifdef WIN32
    HGLOBAL handle = (HGLOBAL) GlobalHandle (pChars);
#else 
	HGLOBAL handle = (HGLOBAL) GlobalHandle (HIWORD (pChars));
#endif    
    if (! handle)
		return NULL;
    if (GlobalUnlock (handle))
		return NULL;            // kann keinen gelockten Speicher freigeben
    if (handle = GlobalReAlloc (handle, (DWORD) Count, GMEM_MOVEABLE))
		return (char *) GlobalLock (handle);
    else
		return NULL;
}

// Inhalt der Listbox ins Clipboard kopieren
void ShowFile :: ListToClip (void)
{

#ifndef __UseOGX__
	    const long lMinBuff = 512;           	// min Puffergröße
	    long lMaxLen = lMinBuff * 2,          	// Puffer-Anfangs-Länge
	    	 lAktLen = 0;                    	// akt. Pufferlänge
	
	    char *pText = NULL;                 	// Puffer-Zeiger
	    
	//	zuerst "Nachzeichnen"
	   	CallMessageQueue ();
	    
	//  Puffer init.
	    if (!(pText = Alloc (lMaxLen)))
	    {
			DEX_Error (RC_DarstShowFile, EC_NOMEMORY);
			return;
	    }
	
	//  Clipboard init.
		if (!OpenClipboard () || ! ::EmptyClipboard ())
		{
			DEX_Error (RC_DarstShowFile, EC_SYSERROR);
			return;		
		}		
	
	//  Kopier-Variablen init.
		CString strOneRow;
	    int nMax = m_lbRowList.GetCount ();   	// Max. Anzahl Einträge
	    if (nMax == LB_ERR)
	    {
	    	DEX_Error (RC_DarstShowFile, EC_NOREAD);
	    	return;
	    }
	    
	//  Stundenglass aktivieren
		CWaitCursor wc;
		int nTextLen = 0;
	
	//  kompletten Listeninhalt lesen un kopieren
	    for (int nIndex = 0; nIndex < nMax; nIndex++)
	    {       
	 
		   	m_lbRowList.GetText (nIndex, strOneRow);
	
			if ((nTextLen = strOneRow.GetLength ()) > 0)
			{
		    	if ((lMaxLen - lAktLen) <= lMinBuff)   	// wenn Puffer zu klein
		    	{
					lMaxLen *= 2;                   	// neue Puffergröße
					if (!(pText = ReAlloc (pText, lMaxLen)))
					{                                 
						DEX_Error (RC_DarstShowFile, EC_NOMEMORY);
			    		break;
					}
		    	}                                   
		    	
			// 	aktuelle Zeile kopieren	    	
				memcpy (pText + lAktLen, strOneRow, nTextLen);
		    	lAktLen += nTextLen;
		    	memcpy (pText + lAktLen, "\r\n", 2);
		    	lAktLen += 2;
			}
			else
			{
		    	DEX_Error (RC_DarstShowFile, EC_NOREAD);
		    	break;
			}
	    }
	
	    if (nIndex && pText)          			// wenn gültige Einträge in Liste gefunden
	    {
			memcpy (pText + lAktLen, "\0", 1); 	// EKZ
	#ifdef WIN32		
			HGLOBAL hText = (HGLOBAL) GlobalHandle (pText);         
	#else		
			HGLOBAL hText = (HGLOBAL) GlobalHandle (HIWORD (pText));
	#endif		
	    	if (hText && GlobalUnlock (hText) == 0)
	    	{
				if (SetClipboardData (CF_TEXT, hText))
				{
					:: CloseClipboard ();		// Clipboard wieder schließen
					pText = NULL;				// Clipboard ist owner der Daten
				}					
			}			
	    }
	
	    if (pText)                  
		FreeMemory (pText);      	// Puffer wieder freigeben
#else
	m_wndRecord.Copy();
#endif //__UseOGX__
}


