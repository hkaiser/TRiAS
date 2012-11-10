// Memberfunktionen fuer DoubleNumEditX ----------------------------------------
// File: DBLNUMED.CXX

#include "editobjp.hxx"

#include <numeditx.hxx>
#include <dblnumex.hxx>

extern "C" LPSTR FAR PASCAL DtoAXTN (LPSTR String, LPSTR Format, double Wert);

// Konstruktoren ---------------------------------------------------------------
DoubleNumEditX :: DoubleNumEditX (pDialogWindow p, ResID r)
	       : NumEditX (p, r, 10)
{
	m_NEM = NEM_NoTest;
}

DoubleNumEditX :: DoubleNumEditX (pWindow pW, uint id, Point p, Dimension d)
	       : NumEditX (pW, id, p, d, 10)
{
	m_NEM = NEM_NoTest;
}

// neuer KeyEvent - Handler für DoubleEingabe ---------------------------------
void _XTENSN_EXPORT DoubleNumEditX :: KeyDown (KeyEvt e) 
{
char c = e.ASCIIChar();

	if (c == '.' || c == '\'' || c == '\"' || c == '°') {
		Default ((Event &)e);	// DezimalPunkt oder Gradangabe
		return;
	}
	NumEditX :: KeyDown (e);		// ansonsten weiterleiten
}

DoubleNumEditX :: ~DoubleNumEditX (void) 
{
	// nothing to do 
}

Bool DoubleNumEditX :: GetValue (double &dbl) 
{
char inBuff[40];

	if (GetTextLen() > 0) {
		GetText (inBuff, sizeof(inBuff));
		dbl = atof (inBuff);
		return TRUE;
	}
	dbl = 0.0;

return FALSE;	// Default
}

void DoubleNumEditX :: SetValue (double dbl)
{
char outBuff[40];

	SetText (DtoAXTN (outBuff, "%10.3f", dbl));
}
