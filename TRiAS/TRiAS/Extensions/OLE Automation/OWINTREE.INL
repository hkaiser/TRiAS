// Inlinefunktionen für typspezifischenBaum -----------------------------------
// File: OWINTREE.INL

// Member für ItemKlasse, die im Baum hängt ----------------------------------
// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline HWND& CGeoObjectWin :: FGetHWND (void)
{
	return m_hORWnd;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmpHWND (const HWND &rObjWin1, const HWND &rObjWin2)
{
	if (rObjWin1 >  rObjWin2) return (+1);
	if (rObjWin1 == rObjWin2)	return ( 0);
	if (rObjWin1 <  rObjWin2) return (-1);

return 0;
}
