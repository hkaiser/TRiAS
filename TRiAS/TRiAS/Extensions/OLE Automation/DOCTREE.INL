// Inlinefunktionen für typspezifischenBaum -----------------------------------
// File : DOCTREE.INL

#include "Strings.h"

// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline LPCSTR CGeoDoc :: FGetBSTR (void)
{
	return (NULL != m_pName) ? m_pName : g_cbNil;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmpBSTR (LPCSTR rDoc1, LPCSTR rDoc2)
{
	_ASSERTE(NULL != rDoc1 && NULL != rDoc2);
	return strcmp (rDoc1, rDoc2);
}


