// Klassifikation der Objekte, die in Komplexrecherche gefunden wurden --------
// File: CLASSIFY.CXX

#include "classify.htp"

extern "C" {
	#include <windows.h>
	#include <zprotos.h>
}

#include <commonvu.hxx>
#include <drawobj.hxx>
#include <cvext.hxx>
#include <containr.hxx>
#include <dcreator.hxx>
#include <deltree.hxx>

#include <ristypes.hxx>
#include <errcodes.hxx>
#include <attribs.hxx>
#include <transfrm.hxx>
#include <geo_obj.hxx>
#include <db.hxx>
#include <ident.hxx>
#include <pbd.hxx>

#include <objliste.hxx>
#include <dbliste.hxx>	// KomplexrechercheDatenTypen

#include "draw_obj.hxx" // DB- spezifische Definitionen
#include "iris.hxx"     // Anwendungsspezifische Definitionen

// externe Variablen ----------------------------------------------------------
extern pWindow pLegende;
extern Bool LegendToRepaint;

ErrCode IrisWind :: ClassifyObjects (ObjFeld &OF) {
Ring rOF (OF);
ErrCode RC;

	for (rOF.First(); rOF.Valid(); rOF.Next()) {
	DBaseObjNummerLock l(rOF);

		if (!l) continue;		// irgend ein Fehler

	long newID = l -> _Id;

		if (newID == -1L) continue;	// nicht klassifiziert

	long ONr = l -> _ON;
	long oldID = RetrieveIdent (ONr);	// alten Ident holen

		if (oldID == 0) return EC_OKAY;

		{
		// wenn der Id nicht temporÑr ist, dann Objekt umklassifizieren
		PBD_Ident PbdID (&pbdDB, newID);

			if (!PbdID.isTemp()) {
			// Modifikation des Idents durchfÅhren
				DBO().DB().Activate();
				DBASSERT (modid (ONr, newID));
			}
		}

	// ist das erste Objekt mit diesem Ident (temporÑrer Identifikator)
	Table t(DBO().Shapes().ObjIdTree());

		if (!t.Find (&newID)) {
			if (!DBO().Idents().AddNewIdent (newID, TRUE))
				continue;
		}

	// Identifikator auch im Speicher Ñndern 
		if (!DBO().Shapes().ModIdent (ONr, oldID, newID))
			continue;

	// war das letzte Objekt mit diesem Ident
		if (!t.Find (&oldID)) {
			if (!DBO().Idents().DeleteIdent (oldID))
				continue;
		}
	}

// alles Neu zeichnen
	LegendToRepaint = TRUE;
	RePaint ();

return EC_OKAY;
}
