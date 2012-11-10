/*
File: MERKMAL.CPP
realiert die Verwaltung einer Merkmals-Tabelle.

erarbeitet : J. Benkenstein					Stand vom 28.08.1995
*/

#include "pheader.hpp"

#include "tmerkmal.hpp"			// TextMerkmalsListe 	
#include "tools.hpp"			// CreateMerkmal () 
#include "optparam.hpp"         // Params
#include "merkmal.hpp"	  		// zugeh. Header-File

//	Konstanten
const short MaxMerkmalsLen = 80;		// max. Länge eines Merkmalswertes

//  externe Variablen
extern Params OptParams;				// Speicher für allg. Parameter

//  Prototypen
void yyerror (short);

extern "C" {
	BOOL CALLBACK __export EnumMerkmaleProc (long Key, BOOL iNotLast, void *pData);	
}

//  globale Funktionen ---------------------------------------------------------
void* __export GetMName (void *pObj) 
{
	return ((Merkmal *) pObj) -> MerkmalsName ();
}

int __export CompareNames (void *pObj1, void *pObj2)
{
	return strcmpi ((char *) pObj1, (char *) pObj2);
}	

//  enumerieren aller Merkmale eines Projekts
BOOL CALLBACK EnumMerkmaleProc (long MKode, BOOL, void *pData) 
{               
//	KurzText zum Mkode lesen
	char Buffer [80] = "";
	PBDDATA Data;
	memset (&Data, 0, sizeof (PBDDATA));        // init.
	Data.dwSize = sizeof (PBDDATA);
	Data.pbdTyp = 'm';                          // Merkmal
	Data.pbdCode = MKode;
	Data.pbdKText = Buffer;
	Data.pbdKTextLen = sizeof (Buffer);

#if _MSC_VER < 1100
	if (DEX_GetPBDData (Data) != EC_OKAY)
#else
	HPROJECT hPr = DEX_GetDataSourceHandle();
	if (DEX_GetPBDDataEx (hPr,Data) != EC_OKAY)
#endif
		return FALSE;		
		
//	MKode und Kurztext speichern
	return ((MerkmalsBaum *) pData) -> AddMerkmal (Data.pbdKText, MKode);   
}

// Merkmal ---------------------------------------------------------------------
Bool Merkmal :: Init (char *pMName, ulong ulMK) 
{
// 	prüfe Parameter
	if (!pMName)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}

//	ist der Wert gültig
	if (!*pMName)
		return True;

//	Werte übernehmen
	m_pMName = new char [lstrlen (pMName) + 1];
	if (!m_pMName)
	{
		yyerror (IDS_NOMEMORY);
		return False;
	}
				
	lstrcpy (m_pMName, pMName);
   	m_ulMKode = ulMK;

	return True;
}

Merkmal :: ~ Merkmal (void) 
{	// Speicher wieder freigeben
	DELETE_VEC (m_pMName);
}

// MerkmalsBaum ------------------------------------------------------------
MerkmalsBaum ::  MerkmalsBaum (void)
			  :  CTree (GetMName, CompareNames) 
{	// nothing to do
}

void MerkmalsBaum :: UserDelete (void *pObj) 
{
	((Merkmal *) pObj) -> ~ Merkmal ();
}

MerkmalsBaum :: ~ MerkmalsBaum (void) 
{
	EveryDelete ();
}

//	alle Projekt-Merkmale lesen    
Bool MerkmalsBaum :: Init (void) 
{                                   
//	Daten init.
	ENUMLONGKEY Data;
	memset (&Data, 0, sizeof (Data));
	Data.eKey = 'm';									// alle Merkmale
	Data.ePtr = (void *) this;							// User-Daten	                                                                       
	Data.eFcn = (ENUMLONGKEYPROC) EnumMerkmaleProc; 	// zu rufende Funktion
			                    
	if (DEX_EnumPBDData (Data))						// alle Merkmalskodes lesen
	{
		Optimize ();
		return True;
	}

	return False;
}                     

// 	neues Merkmal in Baum aufnehmen
Bool MerkmalsBaum :: AddMerkmal (char *pKurzText, ulong MKode)
{                    
 	MerkmalCreator MC (*this);
	Merkmal *pM = ContCreate (MC, Merkmal);
	return pM && pM -> Init (pKurzText, MKode);
}

// 	lese Merkmalskode aus dem Baum
//	wenn nicht vorhanden, einen neuen von Trias holen und diesen in der PBD
//	speichern
//Bool MerkmalsBaum :: GetMerkmalsKode (char *pMName, ulong &MKode) 
Bool MerkmalsBaum :: GetMerkmalsKode (char *pMName, ulong &MKode, long lONr) 
// KK990927
{
	const short MaxLen = 20; 		// max. Namenslänge

//  gültiger Name ?
	if (!pMName)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}

//	gültiger Wert ?
	char *pTempName = NULL;
	if (!*pMName)	// evtl. Standard-Namen erzeugen
	{
		ResString strStandard (ResID (IDS_ST_MK_KT, &g_pTE -> RF ()), MaxLen);				
		pTempName = new char [MaxLen + 1];
		if (!pTempName)
		{
			yyerror (IDS_NOMEMORY);
			return False;
		}
		lstrcpy (pTempName, (char *) strStandard.Addr ());
		pMName = pTempName;
	}

//  prüfen, ob Eintrag existiert ?
	Bool bRet = False;		// noch nichts getan	
	CTable Tb (*this);

	if (Tb.Find (pMName)) 	 // Namen suchen
	{
		if (Tb.Valid ())
		{
			MerkmalLock pM (Tb);		
			if (pM)
			{
				MKode = pM -> MerkmalsKode ();
				bRet = True;					
			}
		}
	}
	else
	{// neuen Eintrag erzeugen
		MKode = DEX_GetUniqueMCode ();		// unique MK von Trias holen
// KK990927
		ulong lIdent = DEX_GetObjIdent(lONr);
//		if (CreateMerkmal (MKode, pMName, MaxMerkmalsLen) == EC_OKAY)
		if (CreateMerkmal (MKode, pMName, MaxMerkmalsLen, lIdent) == EC_OKAY)
		{
			MerkmalCreator MC (*this);
			Merkmal *pM = ContCreate (MC, Merkmal);
			bRet = pM && pM -> Init (pMName, MKode);
		}
	}

//	ggf. Speicher freigeben
	DELETE_VEC (pTempName);

//	ggf. Fehlermeldung ausgeben
 	if (bRet == False)
		yyerror (IDS_SYSERROR);

	return bRet;
}

// 	alle Merkmale des übergebenen Objekts ausgeben				
Bool MerkmalsBaum :: OutputMerkmale (long ObjNr, TextMerkmalsListe* pML)
{
//	prüfe Parameter
	if (!pML || ObjNr <= 0)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}

//	Werte in Liste vorhanden ?
	if (!pML -> Count ())		// wenn keine Einträge 
		return True;			// vorh., zurück

//	alle Merkmale ausgeben
	CRing r (*pML);	
	ulong ulMK = 0;
	Bool bRet = True;			// bisher alles Ok
	for (r.First (); bRet && r.Valid (); r.Next ())
	{
		TextMerkmalLock pTM (r);
//		if (pTM && GetMerkmalsKode (pTM -> GetName (), ulMK) &&
		if (pTM && GetMerkmalsKode (pTM -> GetName (), ulMK, ObjNr) &&
		   (OutputMerkmal (ObjNr, ulMK, pTM -> GetValue ()) == EC_OKAY))
			continue;
		else
			bRet = False;
	}

//	ggf. Fehler ausgeben	
	if (bRet == False)
		yyerror (IDS_SYSERROR);

	return bRet;
}
