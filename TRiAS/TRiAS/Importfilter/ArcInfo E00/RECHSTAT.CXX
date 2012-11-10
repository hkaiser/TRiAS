// Fenster, welches den ImportStatus anzeigt (in Prozent)
// File: RECHSTATUS.CXX

#include "pheader.h"

#include "arctrias.hr"                           // Resourcen-Defines
#include "rechstat.hxx"
                  
#pragma warning (disable:4355)
                  
RechercheStatus :: RechercheStatus (pWindow pW, ResourceFile *pRF,
				   long AllCnt, pchar pCaption)
				 : ModeLessDialog (pW, ResID (IDD_RECHERCHESTATUS, pRF)),
_Status (this, ResID (IDG_EXPORTSTATUS, pRF)),
_Elem (this, ResID (IDT_ELEMSTAT, pRF)), 
_Elem2 (this, ResID (IDT_ELEMSTAT2, pRF))
{
//  Variablen initialisieren
	_AllCnt = AllCnt;
	_CurrVal = -1;
	_wasInterrupted = FALSE;
	_Status.SetRange (1000);

	if (pCaption)
	{
		char Buffer [50] = "";
		ResString Caption (ResID (IDS_STATCAPTION, pRF), 30);
		wsprintf (Buffer, Caption.Addr (), pCaption);
		SetCaption (Buffer);
	}

	SetValue (0L);
}                             

#pragma warning (default:4355)

void RechercheStatus :: SetValue (long CurrCnt, long ObjNr) 
{
	if (_AllCnt == 0)		// Überlauf verhindern
		return;
	if (CurrCnt > _AllCnt)
		CurrCnt = _AllCnt;

	char Buffer [80] = "";
	short CurrVal = (short) ((CurrCnt * 1000) / _AllCnt);

	if ((ObjNr > 0) || (CurrVal != _CurrVal)) 
	{
		_CurrVal = CurrVal;
		_Status.SetPosition (_CurrVal);
		if (ObjNr)
			wsprintf (Buffer, "Zeile %ld - %%3d%%%% (Objekt: %ld)", CurrCnt, ObjNr);
		else
			wsprintf (Buffer, "Zeile %ld - %%3d%%%%", CurrCnt);					
		_Status.SetText (Buffer);
	}
}

//	Status-Fenster reinit.
void RechercheStatus :: ReInit (long lMaxVal, long lActVal, 
								const char *pCaption, const char *pElemText, const char *pElem2Text)
{
	SetMax (lMaxVal);
	SetValue (lActVal);
	if (pElemText)
		SetElemText (pElemText);
	else
		SetElemText ("");

	if (pCaption)
		SetCaption (pCaption);
	else
		SetCaption ("");

	if (pElem2Text)
		SetElem2Text (pElem2Text);		
	else
		SetElem2Text ("");		
}
