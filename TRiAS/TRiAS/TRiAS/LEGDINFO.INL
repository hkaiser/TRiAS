// Inlinefunktionen für typspezifischenBaum -----------------------------------
// Generiert aus CTTREE.CTT
// File: LEGDINFO.INL

// Member für ItemKlasse, die im Baum hängt ----------------------------------
// Normaler Konstruktor (evtl. notwendig) ------------------------------------
inline CLegendInfoEntry::CLegendInfoEntry (WORD iSrt, BOOL fShow, BOOL fSpace, VisType rgType)
{
	m_Key = iSrt;
	m_rgType = rgType;
	m_pText = NULL;		// StandardTexte anzeigen

	isShown (fShow);
	hasSpace (fSpace);
	m_fDirty = TRUE;
	m_fCustText = FALSE;

	m_lPosition = 0;
	m_lHeight = 0;
}

inline CLegendInfoIdent::CLegendInfoIdent (
		WORD iSrt, BOOL fShow, BOOL fSpace, VisType rgType, INT_PTR lIdent)
	: CLegendInfoEntry (iSrt, fShow, fSpace, rgType)
{
	m_lIdent = lIdent;
}

inline CLegendInfoObject::CLegendInfoObject (
		WORD iSrt, BOOL fShow, BOOL fSpace, VisType rgType, INT_PTR lONr)
	: CLegendInfoEntry (iSrt, fShow, fSpace, rgType)
{
	m_lONr = lONr;
	m_iIconWidth = 0;
}

inline CLegendInfoText::CLegendInfoText (
	WORD iSrt, BOOL fSpace, LPCSTR pcView, INT_PTR lMCode)
	: CLegendInfoEntry (iSrt, true, fSpace, VT_Default), 
	  m_lMCode(lMCode), m_strView(pcView)
{
}

// Destruktoren ---------------------------------------------------------------
inline CLegendInfoEntry::~CLegendInfoEntry (void) 
{
	DELETE_OBJ (m_pText);
}

inline CLegendInfoIdent::~CLegendInfoIdent (void) {}
inline CLegendInfoObject::~CLegendInfoObject (void) {}
inline CLegendInfoText::~ CLegendInfoText (void) {}

// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline WORD &CLegendInfoEntry::FGetWORD (void)
{
	return m_Key;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmpWORD (WORD &rObj1, WORD &rObj2)
{
	if (rObj1 > rObj2) 	return (+1);
	if (rObj1 == rObj2) 	return (0);
	if (rObj1 < rObj2) 	return (-1);
	return 0;
}


