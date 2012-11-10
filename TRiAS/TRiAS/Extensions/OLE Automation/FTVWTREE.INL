// Inlinefunktionen für typspezifischenBaum -----------------------------------
// File : FTVWTREE.INL

#include "Strings.h"

// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline LPCSTR CGeoFeatureBase :: FGetBSTR (void)
{
	return (NULL != m_pName) ? m_pName : g_cbNil;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmpBSTR (LPCSTR rFeat1, LPCSTR rFeat2)
{
	_ASSERTE(NULL != rFeat1 && NULL != rFeat2);
	return strcmp (rFeat1, rFeat2);
}


