// Klasse, die ein Objekt mit seiner Geometrie enthält ------------------------
// File: CGOBJECT.CXX

#include "stdafx.h"

// Konstruktor/Destruktor -----------------------------------------------------
CGObject :: CGObject (LONG lONr, bool fConverted)
{
	INITSTRUCT (m_ogObj, OBJGEOMETRIE);
	m_ogObj.lONr = lONr;
	m_fInitialized = false;
	m_fConverted = fConverted ? true : false;
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
		} else if (m_ogObj.iObjTyp == OGText || m_ogObj.iObjTyp == OGLabel) {
			((TEXTGEOMETRIE &)m_ogObj).pText = new char [m_ogObj.iKCnt+1];
			if (((TEXTGEOMETRIE &)m_ogObj).pText == NULL) 
				return false;
		}
	}

	if (m_fConverted) m_ogObj.iFlags = OGConverted;

	if (DEX_GetObjGeometrie (m_ogObj)) {
		m_fInitialized = true;
		return true;
	}

return false;
}

void CGObject :: FreeObjGeometrie (void)
{
	DELETE_OBJ (m_ogObj.pdblX);
	DELETE_OBJ (m_ogObj.pdblY);
	DELETE_OBJ (m_ogObj.plCnt);
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
		if (memcmp (O1.lX(), lX(), (size_t)(sizeof(long)*lCnt())))
			return false;		// X-Koordinaten ungleich
		if (memcmp (O1.lY(), lY(), (size_t)(sizeof(long)*lCnt())))
			return false;		// Y-Koordinaten ungleich
	
		switch (iObjTyp()) {
		case OGFlaeche:
			if (memcmp (O1.plCnt(), plCnt(), sizeof(long)*iKCnt()))
				return false;	// KonturFeld ungleich
			break;

		case OGLabel:
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

