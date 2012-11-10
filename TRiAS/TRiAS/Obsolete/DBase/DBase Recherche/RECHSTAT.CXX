// Fenster, welches den ExportStatus anzeigt (in Prozent)
// File: RECHSTATUS.CXX

#include "pheader.h"

#include "rechstat.htp"
#include <commonvu.hxx>

#include "komplexr.hr"
#include "rechstat.hxx"

#pragma warning (disable:4355)

RechercheStatus :: RechercheStatus (pWindow pW, ResourceFile &RF, long AllCnt)
				 : ModeLessDialog (pW, ResID (IDD_RECHERCHESTATUS, &RF)),
				_Status (this, IDG_EXPORTSTATUS),
				GroupCount (this, ResID (IDT_GROUPTEXT, &RF)) {
// Variablen initialisieren
	_AllCnt = AllCnt;
	_CurrVal = -1;
	_wasInterrupted = FALSE;
	_Status.SetRange (1000);
	SetValue (0L);
}							 

#pragma warning (default:4355)

RechercheStatus :: ~RechercheStatus (void) {
		// nothing to do
}

void RechercheStatus :: SetValue (long CurrCnt) {
	char Buffer [30] = "";
	short CurrVal = (short) ((CurrCnt * 1000) / _AllCnt);

	if (CurrVal != _CurrVal) {
		_CurrVal = CurrVal;
		_Status.SetPosition (_CurrVal);
		wsprintf (Buffer, "%ld - %%3d%%%%", CurrCnt);
		_Status.SetText (Buffer);
	}
}

void RechercheStatus :: SetGroupText (short Cnt) {
	char Buffer [10] = "";

	if (! Cnt)
		GroupCount.SetText ("keine");
	else {
		itoa (Cnt, Buffer, 10);
		GroupCount.SetText (Buffer);
	}
}
