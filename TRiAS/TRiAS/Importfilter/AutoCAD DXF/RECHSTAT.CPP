// Fenster, welches den ImportStatus anzeigt (in Prozent)
// File: RECHSTATUS.CPP

#include "pheader.hpp"

extern "C"{
	#include <stdlib.h>
}

#include "rechstat.hpp"
                  
#pragma warning (disable:4355)
RechercheStatus :: RechercheStatus (pWindow pW, ResourceFile *pRF)
				   // ulong AllCnt, char *pCaption, char *pActText)
				 : ModeLessDialog (pW, ResID (IDD_RECHERCHESTATUS, pRF)),
_Status (this, ResID (IDG_EXPORTSTATUS, pRF)),
_ActionText (this, ResID (IDT_ACTIONTEXT, pRF))
{
//  Variablen initialisieren
	_AllCnt = 0;
	_CurrVal = -1;
	_wasInterrupted = FALSE;
	_Status.SetRange (1000);

	SetValue (0L);
}                             

#pragma warning (default:4355)

void RechercheStatus :: SetParams (ulong AllCnt, char *pCaption, char *pActText,
								   ResourceFile *pRF)
{
	char Buffer [128] = "";
	ResString Caption (ResID (IDS_STATCAPTION, pRF), 30);
	wsprintf (Buffer, Caption.Addr (), pCaption);
	SetCaption (Buffer);
	if (pActText)
		_ActionText.SetText (pActText);

	_AllCnt = AllCnt;
	_CurrVal = -1;
	SetValue (0L);
}

void RechercheStatus :: SetValue (ulong CurrCnt, long ObjNr) 
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

inline void __export RechercheStatus :: ButtonClick (ControlEvt) 
{ 
	_wasInterrupted = TRUE; 
}	
