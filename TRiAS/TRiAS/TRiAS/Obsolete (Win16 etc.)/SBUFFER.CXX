// Memberroutinen fuer Buffering-ParameterEingabe
// File: SBUFFER.CXX

#if defined(sccs)
static char SccsId[] = "IRISWIN: %W%	%E%";
#endif

#include "sbuffer.htp"

#include <commonvu.hxx>
#include <cvext.hxx>

extern "C" {
	#include <stdlib.h>
	#include <string.h>
}

#include <ristypes.hxx>
#include <errcodes.hxx>
#include <numedit.hxx>

#include "iris.h"
#include "sbuffer.hxx"
#include "hdrentry.hxx"

// globale Daten
extern HelpDisplay *IrisHD;

// Konstruktor ---------------------------------------------------------------
BufferParDlg :: BufferParDlg (pWindow pW, GeoDB &geoDB) 
	      : DialogWindow (pW, BUFFERPARS),
	        OKButton (this, IDOK),
		CancelButton (this, IDCANCEL),
		HelpButton (this, IDB_BUFFHELP),
		Units (this, IDC_BUFFDIM),
		SLEDistances (this, IDE_BUFFSTEPS),
		_DB (geoDB)
{
// EditControl initialisieren
	SLEDistances.GetEditControl() -> SetTextLimit (BUFFERPARLEN);	// Zeichen begrenzen
	SLEDistances.SetNumEditMode (NumEdit :: NEM_NoTest);

// ComboBox initialisieren
	Units.AddString (ResString (IDS_METER, 3));
	Units.AddString (ResString (IDS_KILOMETER, 3));
	Units.ChangeCurrentIndex (0);

// sonstige Daten initialisieren
	_Distances = NULL;
	_NumDists = 0;
}

// Memberfunktionen
void BufferParDlg :: ButtonClick (ControlEvt e) 
{
char DistStr[BUFFERPARLEN+1];

	switch ((uint)e.GetControlID()) {
	case IDOK:		// OK - PassWord eingegeben
		SLEDistances.GetEditControl() -> GetText (DistStr, BUFFERPARLEN);
		_Distances = ReadDistances (DistStr, _NumDists);
		EndDlg (_NumDists);	// liefert Anzahl der Abst„nde
		break;

	case IDCANCEL:
		EndDlg ();	// raus und vorbei
		break;

	case IDB_BUFFHELP:
		IrisHD -> Show (IDB_BUFFHELP);
		break;
	}
}

long *BufferParDlg :: ReadDistances (char *InString, short &num) 
{
long *Result = new long [NUMDISTS];
char *cptr = strtok (InString, ",;: ");
short i = 0;
short CurrentUnit = Units.GetCurrentIndex();
double Scale = 1.0 / HeaderEntry (_DB, ResString (IDS_KOEFF11, 17)).EntryDouble (1.0);

	while (cptr != NULL && i < NUMDISTS) {
		Result[i] = (double)atol(cptr) * Scale;	// konvertieren
		if (CurrentUnit == 1) 			// Kilometer
			Result[i] *= 1000.0;
		i++;
		cptr = strtok (NULL, ",;: ");
	}
	num = i;

return Result;
}
