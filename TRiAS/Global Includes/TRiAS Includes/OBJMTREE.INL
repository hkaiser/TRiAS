// Inlinefunktionen für typspezifischenBaum -----------------------------------
// Generiert aus CTTREE.CTT, File: OBJMTREE.INL

// Member für ItemKlasse, die im Baum hängt ----------------------------------
// Normaler Konstruktor (evtl. notwendig) ------------------------------------
inline CFeature :: CFeature (long lMCode, char *pMText)
{
	m_Key = lMCode;
	if (pMText) {
		m_pFText = new char [strlen(pMText) +1];
		if (m_pFText) strcpy (m_pFText, pMText);
	}
}


// Destruktor -----------------------------------------------------------------
inline CFeature :: ~CFeature (void)
{
	if (m_pFText) delete m_pFText;
}

// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline MCODE &CFeature :: FGetMCODE (void)
{
	return m_Key;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmpMCODE (MCODE &rObj1, MCODE &rObj2)
{
	if (rObj1 > rObj2) 	return (+1);
	if (rObj1 == rObj2) 	return (0);
	return (-1);
}


