// Inlinefunktionen für typspezifischenBaum -----------------------------------
// Generiert aus CTTREE.CTT
// File: CLIDTREE.INL

// Member für ItemKlasse, die im Baum hängt ----------------------------------
// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline ULONG &CClass :: FGetULONG (void)
{
	return m_lIdent;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmpULONG (const ULONG &rCls1, const ULONG &rCls2)
{
	if (rCls1 > rCls2) 	return (+1);
	if (rCls1 == rCls2) 	return (0);
	if (rCls1 < rCls2) 	return (-1);
	return 0;
}


