/*
File: TMERKMAL.CPP
realiert die Verwaltung einer Textmerkmals-Liste

erarbeitet : J. Benkenstein				 Stand vom 28.8.1995
*/

#include "pheader.hpp"		// vorübersetzter Header

#include <assert.h>			// assert ()
#include <new>				// bad_alloc

#include "tmerkmal.hpp"		// zugeh. Header

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

//  externe Funktionen
void yyerror (short);

//  externe Variablen
extern Params OptParams;			// globales Parameter-Halter-Objekt

// TextMerkmal ------------------------------------------------------------
Bool TextMerkmal :: Init (char *pMName, char *pMValue)
{
//	prüfe Parameter
	if (!pMName || !pMValue)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}

	try
	{
		m_pMValue = new char [lstrlen (pMValue) + 1];
		m_pMName = new char [lstrlen (pMName) + 1];
		
	//	Werte übernehmen
		lstrcpy (m_pMValue, pMValue);
		lstrcpy (m_pMName, pMName);		
		
		return True;
	}
	catch (bad_alloc)
	{
		yyerror (IDS_NOMEMORY);
	}

	return False;
}

TextMerkmal :: ~ TextMerkmal (void) 
{//	Speicher wieder freigeben
	DELETE_VEC (m_pMValue);
	DELETE_VEC (m_pMValue);
}

// TextMerkmalsListe ---------------------------------------------------------
TextMerkmalsListe :: TextMerkmalsListe (void)
				   : CListContainer ()
{
	// nothing to do
}

void TextMerkmalsListe :: UserDelete (void *pObj)
{
	((TextMerkmal *) pObj) -> ~TextMerkmal ();
}

TextMerkmalsListe :: ~TextMerkmalsListe (void)
{
	EveryDelete ();
}

// neues TextMerkmal in Liste aufnehmen
Bool TextMerkmalsListe :: AddMerkmal (char *pMName, char *pMValue, Bool bKonvert)
{
//	prüfe Parameter
	if (!pMName || !pMValue)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}				

//	prüfe Info
	if (!*pMValue || !*pMName)
		return True;		// nicht Speichern

//	ggf. Ansi-Text erzeugen
	if (bKonvert && OptParams.bAnsiiText)
	{
		OemToAnsi (pMName, pMName);
		OemToAnsi (pMValue, pMValue);
	}		

	TextMerkmalCreator IDT (*this);
	TextMerkmal *pID = ContCreate (IDT, TextMerkmal);
	return (pID && pID -> Init (pMName, pMValue));
}

Bool TextMerkmalsListe :: operator += (TextMerkmalsListe& Liste)
{
//	prüfe Parameter
	assert (&Liste != this);
	if (&Liste == this)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}			

//	prüfe Anzahl Einträge
	if (Liste.Count () < 1)
		return True;

//	Einträge umkopieren
	CRing r (Liste);		
	for (r.First(); r.Valid(); r.Next()) 
	{
		TextMerkmalLock l (r);
		if (l) 
		{
			if (!AddMerkmal (l -> GetName (), l -> GetValue (), False))
				return False;
		}
		else
		{
			yyerror (IDS_SYSERROR);
			return False;
		}
	}

	return True;
}

Bool TextMerkmalsListe :: operator = (TextMerkmalsListe& Liste)
{
//	prüfe Parameter
	assert (&Liste != this);
	if (&Liste == this)
	{
		yyerror (IDS_SYSERROR);
		return False;
	}			

//	alle Einträge löschen
	EveryDelete ();

	return operator += (Liste);
}
