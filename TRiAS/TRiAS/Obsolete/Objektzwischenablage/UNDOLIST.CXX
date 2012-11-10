// Liste, die ein einstufuges UnDo der ObjClipboardOperationen erlaubt --------
// File: UNDOLIST.CXX

#include "objclipp.hxx"
extern "C" int __cdecl db_error (int, int, ...);

#include "objmlist.hxx"
#include "undolist.hxx"


// HilfsFunktion -------------------------------------------------------------
short VTypFromOTyp (short iOTyp)
{
	switch (iOTyp) {
	case OGPunkt:		return MODIDENT_PUNKT;
	case OGLinie:		return MODIDENT_LINIE;
	case OGFlaeche:
	case OGKreis:		return MODIDENT_FLAECHE;
	case OGText:		return MODIDENT_TEXT;
	case OGKO:
	case OGUnknown:
	default:		return MODIDENT_TYP;
	}
}


// Ein Element der UndoListe -------------------------------------------------
Undo :: Undo (long lONr, UStatus US)
{
	ResetUStatus (US);
	_pOG = InsertObjectGeometrie (lONr);
	_pOML = InsertObjectMerkmale (lONr);
}


Undo :: ~Undo (void)
{
	DELETE (_pOG);
	DELETE (_pOML);
}


// wieder Rückgängigmachen der in diesem Element gespeicherten Veränderungen
Bool Undo :: PlayUndo (HWND hWnd)
{
// wenn ein neues Objekt erzeugt wurde, dann dieses rauslöschen
	if (GetUStatus() &USNewObject) {
		DEX_DeleteObject (_pOG -> lONr);
		return TRUE;
	}

// wenn ein Objekt modifiziert wurde
	if (GetUStatus() & (USGeometrieModified | USObjectDeleted)) {
	// Geometrie zurückspeichern
		if (GetUStatus() & USObjectDeleted) {
			_pOG -> lONr = -1L;
			_pOG -> iFlags = OGNewObject;
		} else
			_pOG -> iFlags = OGModObject;
		_pOG -> iFlags |= OGForceGeometry;
		DEX_ModObjGeometrie (*_pOG);
	}
	else if (GetUStatus() & USIdentModified) {
	// Identifikator modifizieren
	MODOBJIDENT MOI;

		MOI.dwSize = sizeof (MODOBJIDENT);
		MOI.lONr = _pOG -> lONr;
		MOI.lNewIdent = _pOG -> lIdent;

		if (MOI.lNewIdent) {
			if (hWnd) DEXOR_ModObjectIdent (hWnd, MOI);
			else	  DEX_ModObjectIdent (MOI);
		}
	}

	if (GetUStatus() & (USMerkmaleModified | USObjectDeleted)) {
	// alle jetzigen Merkmale dieses Objektes erstmal löschen
		if (!(GetUStatus() & USObjectDeleted))
			DeleteAllMerkmale (_pOG -> lONr);
	
	// alle Merkmale zurückspeichern
	CTable t(*_pOML);
	TARGETMERKMAL TM;

		TM.dwSize = sizeof (TARGETMERKMAL);
		TM.lTarget = _pOG -> lONr;
		TM.iTTyp = TT_Objekt;

		for (t.First(); t.Valid(); t.Next()) {
		ObjMerkmalLock l(t);

			if (l) {
				TM.lMCode = l -> MCode();
				TM.pMText = l -> pMText();
				TM.imaxLen = strlen (l -> pMText());

//				AnsiToOem (TM.pMText, TM.pMText);
				DEX_ModTextMerkmal (TM);
			}
		}
	}

return TRUE;                                                 
}


extern "C" {

BOOL _XTENSN_EXPORT PASCAL DelObjMerkmal (long MCode, BOOL, void *pData)
{
TARGETMERKMAL TM;

	memset (&TM, '\0', sizeof (TARGETMERKMAL));
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = (long)pData;		// ObjektNummer
	TM.lMCode = MCode;			// MerkmalsCode
	TM.iTTyp = TT_Objekt;

	DEX_GetTextMerkmal (TM);	// Merkmal löschen

return TRUE;		// weitermachen
}

}	// extern "C"


// Löschen aller Merkmale des gegebenen Objektes -----------------------------
void DeleteAllMerkmale (long lONr)
{
ObjMerkmalsListe *pOML = new ObjMerkmalsListe (lONr);

	if (pOML == NULL) {
		db_error (EC_NOMEMORY, RC_InsertObjectMerkmale);
		return;
	}

// alle Merkmale löschen
ENUMLONGKEY ELK;

	ELK.eKey = lONr;	// ObjektNummer
	ELK.eFcn = (ENUMLONGKEYPROC)DelObjMerkmal;	// zu rufende Funktion
	ELK.ePtr = (void *)lONr;	// zusätzliche Daten (ObjektNummer)

	DEX_EnumObjektMerkmale (ELK);
}


// UndoListe enthält alle modifiziereten Objekte -----------------------------
UndoList :: UndoList (HWND hWnd)
	  : CListContainer ()
{
	_hWnd = hWnd; 	// FensterHandle merken 
}


UndoList :: ~UndoList (void)
{
	EveryDelete ();
}


// Gespeichertes ORFensterHandle rücksetzen, wenn dieses Fenster 
// geschlossen wurde
void UndoList :: ResetHandle (HWND hWnd)
{
	if (_hWnd && _hWnd == hWnd) _hWnd = 0;
}

void UndoList :: UserDelete (void *pObj)
{
	((Undo *)pObj) -> ~Undo();
}


Bool UndoList :: PlayUndo (void)
{
CRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	UndoLock l(r);
	
		if (!l) continue;
		if (!l -> PlayUndo (_hWnd)) return FALSE;
	}
	DEX_RePaint();	// neu zeichnen

return TRUE;
}


Bool UndoList :: AddUndo (long lONr, UStatus US)
{
UndoCreator UCr (*this);

	return Create (UCr, Undo)(lONr, US) != NULL;
}


void UndoList :: SetUStatus (long lONr, UStatus US)
{
CRing r(*this);

	for (r.First(); r.Valid(); r.Next()) {
	UndoLock l(r);
	
		if (!l) continue;
		if (l -> ONr() == lONr) {
			l -> SetUStatus (US);
			break;
		}
	}
}

