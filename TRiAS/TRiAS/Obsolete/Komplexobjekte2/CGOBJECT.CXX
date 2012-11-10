// Klasse, die ein Objekt mit seiner Geometrie enthält ------------------------
// File: CGOBJECT.CXX

#include "featurep.hxx"

#include "cgobject.hxx"

// Konstruktor/Destruktor -----------------------------------------------------
CGObject :: CGObject (LONG lONr)
{
	INITSTRUCT (m_ogObj, OBJGEOMETRIE);
	m_ogObj.lONr = lONr;
	m_fInitialized = false;
}


CGObject :: ~CGObject (void)
{
	FreeObjGeometrie();	// Geometrie freigeben
}


// Objektgeometrie besorgen ---------------------------------------------------
bool CGObject :: FInit (void)
{
	if (m_fInitialized) return true;

// Statistik anfordern
	if (!DEX_GetObjStatistik (m_ogObj))
		return false;

// Felder anfordern
	m_ogObj.pdblX = new long [m_ogObj.lCnt];
	m_ogObj.pdblY = new long [m_ogObj.lCnt];
	if (m_ogObj.pdblX == NULL || m_ogObj.pdblY == NULL) 
		return false;
		
	if (m_ogObj.iKCnt > 0) {
		if (m_ogObj.iObjTyp == OGFlaeche) {
			m_ogObj.plCnt = new long [m_ogObj.iKCnt];
			if (m_ogObj.plCnt == NULL) 
				return false;
		} else if (m_ogObj.iObjTyp == OGText) {
			((TEXTGEOMETRIE &)m_ogObj).pText = new char [m_ogObj.iKCnt+1];
			if (((TEXTGEOMETRIE &)m_ogObj).pText == NULL) 
				return false;
		}
	}

	if (DEX_GetObjGeometrie (m_ogObj)) {
		m_fInitialized = true;
		return true;
	}

return false;
}

void CGObject :: FreeObjGeometrie (void)
{
	DELETE (m_ogObj.pdblX);
	DELETE (m_ogObj.pdblY);
	DELETE (m_ogObj.plCnt);
}


// Vergleich zweier Objekte auf Identität -------------------------------------
bool CGObject :: isEqual (CGObject &O1, int fFlags)
{
	if (!O1.FInit() || !FInit()) return false;	// Initialisierungsfehler ?

	if ((fFlags & CMP_IDENT) && (O1.lIdent() != lIdent())) 
		return false;	// Idents ungleich
	if ((fFlags & CMP_OBJTYP) && (O1.iObjTyp() != iObjTyp())) 
		return false;	// ObjektTyp ungleich

	if (fFlags & CMP_GEOMETRY) {
		if (O1.lCnt() != lCnt()) 
			return false;	// ungleiche Stützpunktanzahl
		if (O1.iKCnt() != iKCnt()) 
			return false;	// ungleiche KonturAnzahl

	// so weit, so gut, jetzt Geometrie selbst vergleichen
		if (memcmp (O1.X(), X(), (size_t)(sizeof(long)*lCnt())))
			return false;		// X-Koordinaten ungleich
		if (memcmp (O1.Y(), Y(), (size_t)(sizeof(long)*lCnt())))
			return false;		// Y-Koordinaten ungleich
	
		switch (iObjTyp()) {
		case OGFlaeche:
			if (memcmp (O1.plCnt(), plCnt(), sizeof(long)*iKCnt()))
				return false;	// KonturFeld ungleich
			break;

		case OGText:
			if (strncmp (O1.Text(), Text(), iKCnt()))
				return false;	// Text ungleich
			break;

		default:
			break;
		}
	}

// hier bei Bedarf noch Merkmale/Relationen vergleichen
// ...

return true;
}

// RechercheStatus abfragen ---------------------------------------------------
bool isSelected (HWND hWnd, LONG lONr)
{
RECHOBJECT ro;

	INITSTRUCT (ro, RECHOBJECT);
	ro.lONr = lONr;
        DEXOR_QueryRechercheStatus (hWnd, ro);

	if (!(ro.iFlags & RSListed)) 
		return false;		// nicht in ORFenster

// RechercheStatusprüfen
	if (!(ro.iFlags & RSSelected))
		return false;		// nicht selektiert

return true;
}

