// Memberfunktionen fuer DoubleNumEditX ----------------------------------------
// File: DBLNUMED.CXX

#include "besslgkp.hxx"

#include <numeditx.hxx>
#include <dblnumex.hxx>

extern "C" LPSTR PASCAL DtoACTF (LPSTR, LPSTR, double);

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
void DoubleNumEditX :: KeyDown (KeyEvt e) 
{
char c = e.ASCIIChar();

	if ('.' == c) {
		Default ((Event &)e);	// DezimalPunkt oder Gradangabe
		return;
	}
	NumEditX :: KeyDown (e);		// ansonsten weiterleiten
}

DoubleNumEditX :: ~DoubleNumEditX (void) 
{
	// nothing to do 
}

bool DoubleNumEditX :: GetValue (double &dbl) 
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
// Formatieren und Ausgeben des neuen Wertes
char outBuff[40];

	DtoACTF (outBuff, "%10.2f", dbl);

string strOut = outBuff;
int iPos = strOut.find_first_not_of (" ");

	if (NPOS != iPos)
		strOut = strOut.substr (iPos);
	SetText (strOut.c_str());
}
