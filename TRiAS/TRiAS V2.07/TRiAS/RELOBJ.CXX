// Memberfunktionen fuer RelationsObjekte
// File: RELOBJ.CXX

#include "triaspre.hxx"

#include <xtensnxx.h>

#include "relobj.hxx"

extern Bool DrawTextObjs;
extern Bool GenerateLegendOnly;

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
	DELETE (_pKO);
}

void RelationsObjekt :: ResetAttributes (void) {}

// Routine, die ZeichenAttribute einstellt ------------------------------------
VisInfo *RelationsObjekt :: SetAttributes (CIdentifikator *pId, 
					   Dimension DotsPerMM,
					   CTable &tabONr, VisType, short fFlags) 
{
	if (!pId) return NULL;	// wenn kein Ident, dann nicht zeichnen

	_pId = pId;			// Identifikator für Draw() merken
	_DotsPerMM = DotsPerMM;		// Auflösung für Draw merken
	_pTabONr = &tabONr;		// Table enthält alle geladenen Objekte
	m_fFlags = fFlags;
	SetVisible (TRUE);
	
return VI_NotChanged;	// erstmal immer zeichnen
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


// Routine, die RelationsObjekte zeichnet -------------------------------------
void RelationsObjekt :: DrawEx (DWORD dwData) 
{
ObjektListeIterator KOI (KO().OL());
long lONr = KOI.FirstONr();

	while (lONr != -1L) {
	// für alle Objekte dieses KomplexObjektes

		if (_pTabONr -> Find (&lONr)) {
		// dieses Objekt zeichnen
		ExtShapeObjectLock LockObj (*_pTabONr);
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
				pVI = pObj -> SetAttributes (_pId, _DotsPerMM, *_pTabONr, VT_Default, DF_Analyze);
				if (pVI && pVI != VI_NotChanged) {
					pVI = _pId -> ChangeVisInfo (pVI);
					DELETE (pVI);
				}
			} else if ((pVI = pObj -> SetAttributes (_pId, _DotsPerMM, *_pTabONr)) != NULL) 
			{
				GetCanvas() -> DrawEx (pObj, dwData);
				if (pVI != VI_NotChanged) {
					pVI = _pId -> ChangeVisInfo (pVI);
					DELETE (pVI);
				}
			}
		}

	// nächste ObjektNummer holen
		lONr = KOI.NextONr();
	}
}


// sonstige virtuelle Funktionen ----------------------------------------------
RelationsObjekt :: operator GeoObjekt * (void) { return &KO(); }
GeoObjekt *RelationsObjekt :: operator -> (void) { return &KO(); }
ObjTyp RelationsObjekt :: isTyp (void) { return KO().isA(); }
long &RelationsObjekt :: Id (void) { return KO().Id(); }
long &RelationsObjekt :: ObjNr (void) { return KO().ObjNr(); }
GeoObjekt *RelationsObjekt :: NewGI (GeoObjekt *) { return NULL; }
