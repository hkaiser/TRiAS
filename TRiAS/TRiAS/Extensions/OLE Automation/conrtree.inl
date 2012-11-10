// Inlinefunktionen für typspezifischenBaum -----------------------------------
// Generiert aus CTTREE.CTT
// File: CONRTREE.INL

// Member für ItemKlasse, die im Baum hängt ----------------------------------
// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline LONG &CGeoObject :: FGetLONG (void)
{
	return m_lONr;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmpLONG (const LONG &rObj1, const LONG &rObj2)
{
	if (rObj1 > rObj2) 	return (+1);
	if (rObj1 == rObj2) 	return (0);
	if (rObj1 < rObj2) 	return (-1);

return 0;
}


