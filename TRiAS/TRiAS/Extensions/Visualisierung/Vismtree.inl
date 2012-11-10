// Inlinefunktionen für typspezifischenBaum -----------------------------------
// File VISMTREE.INL
// Generiert aus TTREE.CTT

// Member für ItemKlasse, die im Baum hängt ----------------------------------
// Normaler Konstruktor (evtl. notwendig) ------------------------------------
inline CVisModule :: CVisModule (void)
{
	m_Key = NULL;
	m_pVCSModule = NULL;
	m_pIVisModule = NULL;
}


// Destruktor -----------------------------------------------------------------
inline CVisModule :: ~CVisModule (void)
{
	DELETE_OBJ (m_Key);				// Speicher freigeben
	if (m_pIVisModule) {
		m_pIVisModule -> Release();	// Interface freigeben
		m_pIVisModule = NULL;
	}
	DELETE_OBJ (m_pVCSModule);			// DLL entladen
}

// ZugriffsFunktion auf den Suchschlüssel innerhalb der ItemKlasse ------------
inline pChar &CVisModule :: FGetpChar (void)
{
	return m_Key;
}

// VergleichsFunktion für zwei Suchschlüssel ----------------------------------
inline int FCmppChar (pChar &rObj1, pChar &rObj2)
{
	return _stricmp (rObj1, rObj2);		// lower case compare !
}


// Testen, ob VisModule erfolgreich geladen wurde -----------------------------
inline bool CVisModule :: isValid (void)
{
	return (m_pIVisModule != NULL) ? true : false;
}
