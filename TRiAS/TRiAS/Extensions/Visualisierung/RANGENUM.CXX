// Numedit, welches automatisch vorgegebene Grenzwerte überprüft --------------
// File: RANGENUM.CXX

#include "visobjp.hxx"

#include <ctype.h>


// Konstruktor/Destruktor -----------------------------------------------------
RangeNumEdit :: RangeNumEdit (pDialogWindow p, ResID r, Range range, short iBase)
	      : NumEditX (p, r, iBase)
{
	m_R = range;
}


RangeNumEdit :: RangeNumEdit (pWindow parent, uint id, Point p, 
			      Dimension d, Range r, short iBase)
	      : NumEditX (parent, id, p, d, iBase)
{
	m_R = r;
}

// Destruktor -----------------------------------------------------------------
RangeNumEdit :: ~RangeNumEdit (void)
{
	// nothing to do
}


// Validierungsfunktion -------------------------------------------------------
int RangeNumEdit :: PostValidate (int iVal)
{
	if (iVal > m_R.Max()) return m_R.Max();
	if (iVal < m_R.Min()) return m_R.Min();

return iVal;
}


