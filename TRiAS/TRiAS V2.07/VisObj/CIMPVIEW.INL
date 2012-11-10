// Inlinefunktionen für typspezifischenBaum -----------------------------------
// Generiert aus TTREE.CTT

// Member für ItemKlasse, die im Baum hängt ----------------------------------
// Normaler Konstruktor (evtl. notwendig) ------------------------------------
inline CImpView :: CImpView (char *pView, short cnCnt)
{
	m_cnIdents = cnCnt;
	m_pView = NULL;
	m_fImport = 0;
	if (pView) {
		m_pView = new char [strlen (pView)+1];
		if (m_pView) strcpy (m_pView, pView);
	}
}

// Destruktor -----------------------------------------------------------------
inline CImpView :: ~CImpView (void)
{
	if (m_pView) delete m_pView;
}

// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline pchar &CImpView :: FGetpChar (void)
{
	return m_pView;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmppChar (pChar &rObj1, pChar &rObj2)
{
	return strcmp (rObj1, rObj2);
}


