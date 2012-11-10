// EditControl fuer die Eingabe von numerischen Werten und Trennzeichen
// File: NUMERIC.CXX

#include "trias03p.hxx"

#include <ctype.h>
#include <cvext.hxx>

#include <numedit.hxx>

// Konstruktoren --------------------------------------------------------------
NumEdit :: NumEdit (pDialogWindow p, ResID r, short iBase) 
	 : ControlWindow (new SingleLineEdit (p, r)),
	   m_iBase (iBase),
	   m_NEM (NEM_Test)
{
}

NumEdit :: NumEdit (pWindow parent, uint id, Point p, Dimension d, short iBase) 
	 : ControlWindow (new SingleLineEdit (parent, id, p, d)),
	   m_iBase (iBase),
	   m_NEM (NEM_Test)
{ 
}

void NumEdit :: KeyDown (KeyEvt e) 
{
char inChar = e.ASCIIChar();

	if (inChar == '\0' || iscntrl(inChar) ||	// Steuerzeichen
	    inChar == '-'  ||				// unäres Minus
	    ( (m_iBase == 10) ? isdigit(inChar) : isxdigit(inChar) )) 
	    // numerisches Zeichen
	{
	// Event weiterleiten
		Default ((Event &)e); 
	} else
		MessageBeep (0);	// FehlerBeep
}

// Destruktor -----------------------------------------------------------------
NumEdit :: ~NumEdit (void) 
{
	delete (SingleLineEdit *)GetControl();
}
