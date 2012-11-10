// Memberfunktionen fuer Drucken abbrechen
// File: PRNTABRT.CXX

#include "triaspre.hxx"

#include "prntabrt.hxx"

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable:4355)

PrintAbort :: PrintAbort (pWindow pW, Printer *p, const char *pcDevice) 
	    : ModeLessDialog (pW, PRINTER_ABORT),
	      m_DeviceName (this, IDT_PRINTERNAME),
	      m_PrintStatus (this, IDT_PRNTSTATUS)
{
	m_P = p;
	m_DeviceName.SetText (pcDevice);
}

#pragma warning (default:4355)

// Memberfunktionen -----------------------------------------------------------
void PrintAbort :: SetStatus (const char *StatusString) 
{
	m_PrintStatus.SetText (StatusString);
}


// AbbrechenKnopf wurde gedrückt ----------------------------------------------
void EXPORTTRIAS PrintAbort :: ButtonClick (ControlEvt)
{
	m_P -> Abort();
	EndDlg (1);
}
