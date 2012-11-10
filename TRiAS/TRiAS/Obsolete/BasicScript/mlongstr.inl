// Inlinefunktionen für typspezifischenBaum -----------------------------------
// Generiert aus CTTREE.CTT

// Member für ItemKlasse, die im Baum hängt ----------------------------------
// Normaler Konstruktor (evtl. notwendig) ------------------------------------
inline CLongString :: CLongString (LONG lKey, LPCTSTR pData)
		    : m_Data(pData), m_Key(lKey)
{
}

// Destruktor -----------------------------------------------------------------
inline CLongString :: ~CLongString (void) {}

// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline LONG &CLongString :: FGetLONG (void)
{
	return m_Key;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmpLONG (LONG &rObj1, LONG &rObj2)
{
// --> VergleichsCode einfügen 
	if (rObj1 > rObj2) 	return (+1);
	if (rObj1 == rObj2) 	return (0);
	if (rObj1 < rObj2) 	return (-1);

return 0;
}


