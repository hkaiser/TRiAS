// Aufloesen eines Komplexobjektes --------------------------------------------
// File: DELRELKO.CXX

#include "trias02p.hxx"

#include <objfeld.hxx>

#include "getrcode.hxx"
#include "relliste.hxx"

// Löschen aller Relationen eines Objektes ------------------------------------
extern "C" long EXPORT02 FUNCTYPE DelAllRelations (HPROJECT hPr, long ONr) 
{
RCodes RelC;	// Liste der Relationen
ErrCode RC;

// Relationen dieses Objektes aufsammeln
	{
	ErrInstall EI (WC_NOTFOUND);	// wenn Textobjekt vorliegt

		if ((RC = GetRelationsCodes (hPr, ONr, RelC)) != EC_OKAY)
			if (RC != WC_NOTFOUND) 
				return RC;
	}

// für jede der gefundenen Relationen die zugehörigen Objekte und Relations-
// Typen finden und rauslöschen
CTable t(RelC);

	DEX_SetDirtyGeoDB (true);

	for (t.First(); t.Valid(); t.Next()) {
	RCodeLock l(t);
	ObjRelFeld OF;	// Feld in dem Objekte gesammelt werden

		if (!l) continue;
		DBASSERT (GetRelation (hPr, ONr, l -> RelCode(), OF));
		DBASSERT (DelRelationCode (hPr, ONr, OF));
	}

// eventuell angehängtes Textobjekt bzw. Begleitrelation löschen
long AssocON = AssociatedObjekt (hPr, ONr);

	if (AssocON != 0) {
	// Begleitrelation existiert
	short RelTyp = AssocON > 0 ? BRELP : BRELA;

		DBASSERT (DelRelation (hPr, ONr, labs(AssocON), 0, RelTyp));
	}

return S_OKAY;
}


// Funktion, die alle identischen Relationen eines Objektes auflöst -----------
ErrCode DelRelationCode (HPROJECT hPr, long ONr, ObjRelFeld &OF) 
{
CRing r(OF);
ErrCode RC;

	for (r.First(); r.Valid(); r.Next()) {
	ObjRelNummerLock l(r);

		if (!l) continue;
		DBASSERT (DelRelation (hPr, ONr, l -> _ON, l -> RelCode(), l -> RelTyp()));
	}

return EC_OKAY;
}
