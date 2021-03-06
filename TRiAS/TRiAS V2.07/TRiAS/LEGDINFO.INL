// Inlinefunktionen f�r typspezifischenBaum -----------------------------------
// Generiert aus CTTREE.CTT
// File: LEGDINFO.INL

// Member f�r ItemKlasse, die im Baum h�ngt ----------------------------------
// Normaler Konstruktor (evtl. notwendig) ------------------------------------
inline CLegendInfoEntry :: CLegendInfoEntry (WORD iSrt, BOOL fShow, BOOL fSpace, 
					     VisType rgType)
{
	m_Key = iSrt;
	m_rgType = rgType;
	m_pText = NULL;		// StandardTexte anzeigen

	isShown (fShow);
	hasSpace (fSpace);
	m_fDirty = TRUE;
	m_fCustText = FALSE;
}

inline CLegendInfoIdent :: CLegendInfoIdent (WORD iSrt, BOOL fShow, BOOL fSpace,
					     VisType rgType, long lIdent)
			 : CLegendInfoEntry (iSrt, fShow, fSpace, rgType)
{
	m_lIdent = lIdent;
}

inline CLegendInfoObject :: CLegendInfoObject (WORD iSrt, BOOL fShow, BOOL fSpace, 
					       VisType rgType, long lONr)
			  : CLegendInfoEntry (iSrt, fShow, fSpace, rgType)
{
	m_lONr = lONr;
	m_iIconWidth = 0;
}

inline CLegendInfoText :: CLegendInfoText (WORD iSrt, bool fSpace)
			: CLegendInfoEntry (iSrt, true, fSpace, VT_Default)
{
}

// Destruktoren ---------------------------------------------------------------
inline CLegendInfoEntry :: ~CLegendInfoEntry (void) 
{
	DELETE (m_pText);
}

inline CLegendInfoIdent :: ~CLegendInfoIdent (void) {}
inline CLegendInfoObject :: ~CLegendInfoObject (void) {}
inline CLegendInfoText :: ~ CLegendInfoText (void) {}

// ZugriffsFunktion auf den Suchschl�ssel innerhalb der ItemKlasse ------------
inline WORD &CLegendInfoEntry :: FGetWORD (void)
{
	return m_Key;
}

// VergleichsFunktion f�r zwei Suchschl�ssel ----------------------------------
inline int FCmpWORD (WORD &rObj1, WORD &rObj2)
{
	if (rObj1 > rObj2) 	return (+1);
	if (rObj1 == rObj2) 	return (0);
	if (rObj1 < rObj2) 	return (-1);

return 0;
}


