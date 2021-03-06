// Inlinefunktionen f�r typspezifischenBaum -----------------------------------
// Generiert aus CTTREE.CTT
// File : CLNMTREE.INL

#include "Strings.h"

// ZugriffsFunktion auf den Suchschl�ssel innerhalb der ItemKlasse ------------
inline LPCSTR CClass :: FGetBSTR (void)
{
	return (NULL != m_pName) ? m_pName : g_cbNil;
}

// VergleichsFunktion f�r zwei Suchschl�ssel ----------------------------------
inline int FCmpBSTR (LPCSTR rCls1, LPCSTR rCls2)
{
	_ASSERTE(NULL != rCls1 && NULL != rCls2);
	return strcmp (rCls1, rCls2);
}


