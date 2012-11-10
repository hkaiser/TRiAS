// Inlinefunktionen für typspezifischenBaum -----------------------------------
// Generiert aus TTREE.CTT

// Member für ItemKlasse, die im Baum hängt ----------------------------------
// Normaler Konstruktor (evtl. notwendig) ------------------------------------
inline CVisErrorItem :: CVisErrorItem (long lIdent, short iVTyp, char *pView)
		      : m_Key (lIdent, iVTyp, pView)
{
}

// Destruktor -----------------------------------------------------------------
inline CVisErrorItem :: ~CVisErrorItem (void)
{
}

// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline CVisError &CVisErrorItem :: FGetVisError (void)
{
	return m_Key;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmpVisError (CVisError &rObj1, CVisError &rObj2)
{
int iRet = 0;

	if (rObj1.m_lIdent > rObj2.m_lIdent) iRet = 1;
	else if (rObj1.m_lIdent < rObj2.m_lIdent) iRet = -1;
	else if (rObj1.m_iVTyp > rObj2.m_iVTyp) iRet = 1;
	else if (rObj1.m_iVTyp < rObj2.m_iVTyp) iRet = -1;
	else if (rObj1.m_pView && rObj2.m_pView)
		iRet = strcmp (rObj1.m_pView, rObj2.m_pView);
		
return iRet;	// ansonsten sind Schlüssel sind gleich
}


