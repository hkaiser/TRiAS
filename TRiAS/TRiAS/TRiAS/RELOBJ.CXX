// Memberfunktionen fuer RelationsObjekte
// File: RELOBJ.CXX

#include "triaspre.hxx"

#include <xtensnxx.h>

#include "relobj.hxx"

extern bool g_fDrawTextObjs;
extern bool GenerateLegendOnly;

// Konstruktor ----------------------------------------------------------------
RelationsObjekt :: RelationsObjekt (KomplexObjekt &KO) 
		 : ExtShapeObject (Point (0, 0), Dimension(), NULL, NULL)
{
// GeometrieObjekt anhängen
	_pKO = &KO;

// Größe ist erst mal Null
	_Box = Rectangle (0, 0, 0, 0);
}

// Destruktor -----------------------------------------------------------------
EXPORTTRIAS RelationsObjekt :: ~RelationsObjekt (void) 
{
	ResetBase();	// ExtShapeObjekt zurücksetzen
	DELETE_OBJ (_pKO);
}

void RelationsObjekt :: ResetAttributes (void) {}

// Routine, die ZeichenAttribute einstellt ------------------------------------
VisInfo *RelationsObjekt::SetAttributes (
	DatenBasisObjekt *pDBO, CIdentifikator *pId, CONrTable &tabONr, VisType, short fFlags) 
{
	if (!pId) return NULL;	// wenn kein Ident, dann nicht zeichnen

	_pId = pId;								// Identifikator für Draw() merken
	_DotsPerMM = pDBO -> DotsPerMM();		// Auflösung für Draw merken
	_pTabONr = &tabONr;						// Table enthält alle geladenen Objekte
	m_fFlags = fFlags;
	SetVisible (TRUE);
	return VI_NotChanged;					// erstmal immer zeichnen
}

// Umrechnen der verschiedenen Darstellungsformen der Objekttypen -------------
short OTypToBits (ObjTyp iOTyp)
{
	switch (iOTyp) {
	case OT_PUNKT:	return TPPunkt;
	case OT_KANTE:	return TPLinie;
	case OT_FLAECHE:
	case OT_KREIS:	return TPFlaeche;
	case OT_LABEL:
	case OT_TEXT:	return TPText;
	case OT_KO:		return TPAll;
	case OT_UNKNOWN:
	default:
		break;
	}
	return TPUnknown;
}

///////////////////////////////////////////////////////////////////////////////
// Bits in Objekttyp umrechnen (funktioniert nur, wenn genau ein Objekttyp gegeben ist)

#if defined(_DEBUG)
// Bits in einem Objekttype (OBJECTTYPE) zählen
const int g_iBitCount[] = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, };
inline int BitCount(int iBits) 
{
	_ASSERTE(0 <= iBits && iBits < 16);
	return g_iBitCount[iBits & 0xF];
}
#endif // defined(_DEBUG)

ObjTyp BitsToOTyp (short iBits)
{
	_ASSERTE(1 == BitCount(iBits));
	switch (iBits) {
	case TPPunkt:	return OT_PUNKT;
	case TPLinie:	return OT_KANTE;
	case TPFlaeche:	return OT_FLAECHE;
	case TPText:	return OT_TEXT;
	default:
		break;
	}
	return OT_UNKNOWN;
}

// Routine, die RelationsObjekte zeichnet -------------------------------------
void RelationsObjekt :: DrawEx (DWORD dwData) 
{
#if defined(_USE_KOMPLEX_OBJECTS)
ObjektListeIterator KOI (KO().OL());
long lONr = KOI.FirstONr();

	while (lONr != -1L) {
	// für alle Objekte dieses KomplexObjektes

		if (_pTabONr -> Find (&lONr)) {
		// dieses Objekt zeichnen
		ExtShapeObjectONrLock LockObj (*_pTabONr);
		VisInfo *pVI;

			if (!LockObj) continue;
			
		ExtShapeObject *pObj = (ExtShapeObject *)LockObj;
		
		// testen, ob dieser Objekttyp gezeichnet werden soll
			if (!(_pId -> toPaint() & OTypToBits (pObj -> isTyp()))) 
			{
			// wenn nicht, dann nächste ObjektNummer holen, weiter
				lONr = KOI.NextONr();
				continue;
			}
			
		// TeilObjekt zeichen/in Legende aufnehmen
			if (GenerateLegendOnly || m_fFlags & DF_Blinking) 
			{
				pVI = pObj -> SetAttributes ((DatenBasisObjekt *)dwData, _pId, *_pTabONr, VT_Default, DF_Analyze);
				if (pVI && pVI != VI_NotChanged) {
					pVI = _pId -> ChangeVisInfo (pVI);
					DELETE_OBJ (pVI);
				}
			} else if ((pVI = pObj -> SetAttributes ((DatenBasisObjekt *)dwData, _pId, *_pTabONr)) != NULL) 
			{
				GetCanvas() -> DrawEx (pObj, dwData);
				if (pVI != VI_NotChanged) {
					pVI = _pId -> ChangeVisInfo (pVI);
					DELETE_OBJ (pVI);
				}
			}
		}

	// nächste ObjektNummer holen
		lONr = KOI.NextONr();
	}
#endif // defined(_USE_KOMPLEX_OBJECTS)
}


// sonstige virtuelle Funktionen ----------------------------------------------
RelationsObjekt :: operator GeoObjekt * (void) { return &KO(); }
GeoObjekt *RelationsObjekt :: operator -> (void) { return &KO(); }
ObjTyp RelationsObjekt :: isTyp (void) { return KO().isA(); }
INT_PTR &RelationsObjekt :: Id (void) { return KO().Id(); }
INT_PTR &RelationsObjekt :: ObjNr (void) { return KO().ObjNr(); }
GeoObjekt *RelationsObjekt :: NewGI (GeoObjekt *) { return NULL; }
