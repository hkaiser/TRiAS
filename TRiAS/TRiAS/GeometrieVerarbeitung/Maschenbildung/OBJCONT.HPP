/*
File: OBJCONT.HPP

Erarbeitet: J. Benkenstein			Stand vom 28.2.1997
*/

#ifndef _OBJCONT_HPP
#define _OBJCONT_HPP

// CObjContainer --------------------------------------------------------------
class CObjContainer 
{
protected:
	long m_lXMin, m_lXMax, m_lYMin, m_lYMax;

public:
//	Konstruktor/Destruktor
	CObjContainer (long  XMin= 0, long XMax = 0, long YMin = 0, long YMax = 0)
	{ m_lXMin=XMin; m_lXMax=XMax; m_lYMin=YMin; m_lYMax=YMax;}				
	
//	Memberfunktionen
	long &XMin (void) { return m_lXMin; }	// liefert Referenzen auf Attribute
	long &XMax (void) { return m_lXMax; }
	long &YMin (void) { return m_lYMin; }
	long &YMax (void) { return m_lYMax; }
};

#endif		//	_OBJCONT_HPP
