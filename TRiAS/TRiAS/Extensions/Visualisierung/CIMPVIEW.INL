// Inlinefunktionen f�r typspezifischenBaum -----------------------------------
// Generiert aus TTREE.CTT

// Member f�r ItemKlasse, die im Baum h�ngt ----------------------------------
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

// ZugriffsFunktion auf den Suchschl�ssel innerhalb der ItemKlasse ------------
inline pchar &CImpView :: FGetpChar (void)
{
	return m_pView;
}

// VergleichsFunktion f�r zwei Suchschl�ssel ----------------------------------
inline int FCmppChar (pChar &rObj1, pChar &rObj2)
{
	return strcmp (rObj1, rObj2);
}


