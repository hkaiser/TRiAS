// Fensterklasse fuer ObjektZwischenAblage -------------------------------------
// File: OBJCLDLG.CXX

#include "objclipp.hxx"

#include <errinstx.hxx>

#include "objclip.h"
#include "objcldlg.h"
#include "defabout.h"

#include "objcldlg.hxx"
#include "defabout.hxx"
#include "objmlist.hxx"
#include "objmdlg.hxx"
#include "undolist.hxx"

extern "C" {

// ErsatzVariante für Erweiterung ---------------------------------------------
int __cdecl db_error (int ErrC, int RC, ...)
{
ErrCode EC;

	DEX_SetError (EC, RC, ErrC, 0);

return EC;
}

}	// extern "C"

// globale Daten --------------------------------------------------------------

extern short VTypFromOTyp (short);

// Konstruktor ----------------------------------------------------------------
#pragma warning (disable: 4355)

ObjClipboardViewer :: ObjClipboardViewer (pWindow pW, ResourceFile *pRF)
		    : DialogWindow (pW, ResID (OBJCLIPBOARDDLG, pRF), FALSE),
		      _ObjClpMenu (ResID (OBJCLPMENU, pRF)),
		      _ObjClpStatusField (this, IDT_OBJCLPSTATUS),
		      _Lage (this, IDCB_OBJLAGE),
		      _Form (this, IDCB_OBJFORM),
		      _Ident (this, IDCB_OBJIDENTIFIKATOR),
		      _CBIdent (this, IDC_OBJIDENTIFIKATOR),
		      _Merkmale (this, IDCB_OBJMERKMALE),
		      _LBMerkmale (this, IDL_OBJMERKMALE),
		      _CBMerkmal (this, IDC_OBJMERKMAL),
//		      _Relationen (this, IDCB_OBJRELATIONEN),
//		      _LBRelationen (this, IDL_OBJRELATIONEN),
//		      _CopyRelObjs (this, IDCB_COPYRELOBJS),
		      _RF (*pRF),
		      _OCS (OCVInValid)		// für alle Fälle
{
// Variablen initialisieren
	_pOG = NULL;
	_pOML = NULL;
	_pUList = NULL;
	
	DeleteClipboard();		// AnfangsInitialisierung

// alles, was noch nicht implementiert ist, passivieren
//	_Relationen.Disable();
//	_LBRelationen.Disable();
//	_CopyRelObjs.Disable();

// Status setzen
	_ObjClpStatusField.SetText (ResString (ResID (IDS_NOGEOMETRIE, &_RF), 30));

Pointer waitPointer (HourGlass);
Pointer *pOldPointer = ChangePointer (&waitPointer);

// IdentBase besorgen
	m_iMkBase = DEX_GetMkBase();
	
	ReReadIdents();			// ComboBox (Idents) füllen
	ReReadMCodes();			// ComboBox (MCodes) füllen

	ChangePointer (pOldPointer);

	_Ident.SetChecked (FALSE);
	_Merkmale.SetChecked (FALSE);

// AnzeigeFlags richten
	_wasViewerShown = FALSE;
	_isViewerShown = FALSE;

	ChangePosition (Point (0, 0));
	ChangeMenu (&_ObjClpMenu);

// Status setzen
	_OCS = OCVIdle;
}

#pragma warning (default: 4355)

// Destruktor ----------------------------------------------------------------
ObjClipboardViewer :: ~ObjClipboardViewer (void)
{
	DeleteClipboard();
}


// EventHandler --------------------------------------------------------------
void _XTENSN_EXPORT ObjClipboardViewer :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDCB_OBJMERKMALE:
		if (_Merkmale.isChecked() && _pOML) {	// alle Merkmale aktivieren
			_pOML -> SelectAll();
			UpdateViewer();
		}
		break;
	}
	EvalStatus();
}


void _XTENSN_EXPORT ObjClipboardViewer :: MenuCommand (MenuCommandEvt e)
{
	switch (e.GetItemID()) {
	case IDM_OPENOBJCLP:
	case IDM_SAVEOBJCLP:
	case IDM_SAVEASOBJCLP:
		break;

	case IDM_CLOSEOBJCLP:
		HideViewer();
		break;

	case IDM_UNDO:
	// Undo auslösen
		if (_pUList) {
			_pUList -> PlayUndo();
			DEX_RePaint();		// wieder neu zeichnen
		}
		DELETE (_pUList);	// nur einmal erlauben
		break;
		
	case IDM_CUTOBJCLP:
	case IDM_COPYOBJCLP:
	case IDM_PASTEOBJCLP:
		break;

	case IDM_DELETEOBJCLP:
		DeleteClipboard();
		break;

	case IDM_OBJCLPABOUT:
		AboutBox (this, ResID (DEFIDABOUT, &_RF)).Show();
		break;

	case IDM_ADDMERKMAL:
		EditMWert (TRUE);
		break;

	case IDM_EDITMERKMAL:
	// aktiviertes Merkmal editieren
		EditMWert ();
		break;

	case IDM_DELMERKMAL:
	// alle selektierten Merkmal löschen
		DeleteMerkmale();
		break;

	case IDM_DELMWERT:
	// alle selektierten Merkmalswerte löschen
		DeleteMerkmalsWerte();
		break;
	}
}


inline void EnableItem (pMenu pM, UINT iMenuID, Bool iFlag)
{
	if (iFlag) pM -> EnableItem (iMenuID);
	else	   pM -> DisableItem (iMenuID);
}


void _XTENSN_EXPORT ObjClipboardViewer :: MenuInit (MenuInitEvt)
{
// Undo erlauben, wenn UndoInfo da ist
	EnableItem (&_ObjClpMenu, IDM_UNDO, _pUList != NULL);

// MerkmalsEdit beeinflussen
	EnableItem (&_ObjClpMenu, IDM_DELMERKMAL, _LBMerkmale.GetNoSelected());
	EnableItem (&_ObjClpMenu, IDM_DELMWERT, _LBMerkmale.GetNoSelected());
	EnableItem (&_ObjClpMenu, IDM_EDITMERKMAL, 
		    _LBMerkmale.GetCount() && 
		    SendMessage (_LBMerkmale.Handle(), LB_GETCARETINDEX, 0, 0) != -1);
	EnableItem (&_ObjClpMenu, IDM_ADDMERKMAL, isNotMCodeUsed (GetCurrentPBDMCode()));
}


void _XTENSN_EXPORT ObjClipboardViewer :: ListBoxSel (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDL_OBJMERKMALE:		// ObjektMerkmal gewählt
		{
		// MComboBox nachführen
			if (!UpdateMList()) break;

		// Baum laufendhalten
		short iIndex = _LBMerkmale.GetFirstSelected();
		char *pInBuff = new char [1025];

			if (pInBuff == NULL) break;

			_pOML -> ResetSelection();
			while (iIndex != -1) {
				_LBMerkmale.GetString (pInBuff, iIndex, 1024);
				_pOML -> SetSelection (strtoul (pInBuff, NULL, m_iMkBase));
				iIndex = _LBMerkmale.GetNextSelected();
			}

			DELETE (pInBuff);

		// Merkmale aktivieren
			_Merkmale.SetChecked (TRUE);
			EvalStatus();
		}
		break;

	case IDC_OBJIDENTIFIKATOR:
		_Ident.SetChecked (TRUE);
		EvalStatus();
		break;
	}
}


void _XTENSN_EXPORT ObjClipboardViewer :: ListBoxClk (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDL_OBJMERKMALE:		// ObjektMerkmal gewählt
		EditMWert();
		break;
	}
}



Bool _XTENSN_EXPORT ObjClipboardViewer :: QueryClose (Event)
{
	_isViewerShown = FALSE;

return TRUE;	// immer schließen
}


// sonstige Memberfunktionen --------------------------------------------------
void ObjClipboardViewer :: OpenedProject (void)
{
// kann alles 'ne Weile dauern
Pointer waitPointer (HourGlass);
Pointer *pOldPointer = ChangePointer (&waitPointer);

// IdentBase besorgen
	m_iMkBase = DEX_GetMkBase();

	ReReadIdents();		// Idents neu lesen
	ReReadMCodes();		// MCodes neu lesen

	ChangePointer (pOldPointer);

	_Ident.SetChecked (FALSE);
	_Merkmale.SetChecked (FALSE);

// wenn das Fenster im vorherigen Leben angezeigt war, dann wieder anzeigen
	if (_wasViewerShown) ShowViewer();
}


void ObjClipboardViewer :: ClosingProject (void)
{
// alte PBD vergessen
	_CBIdent.Clear();
	_CBMerkmal.Clear();

// Fenster ausblenden, wenn es angezeigt ist
	if (HideViewer()) 
		_wasViewerShown = TRUE;
	else
		_wasViewerShown = FALSE;
}


// Anzeigen/Verstecken des Fensters -------------------------------------------
Bool ObjClipboardViewer :: ShowViewer (void)
{
	if (!_isViewerShown) {
		Show();
		_isViewerShown = TRUE;		
		return TRUE;
	}

return FALSE;
}

Bool ObjClipboardViewer :: HideViewer (void)
{
	if (_isViewerShown) {
		Hide();
		_isViewerShown = FALSE;		
		return TRUE;
	}

return FALSE;
}

void ObjClipboardViewer :: ToggleStatus (void)
{
	if (_isViewerShown) HideViewer();
	else		    ShowViewer();
}


// Löschen des ClipboardInhaltes ----------------------------------------------
Bool ObjClipboardViewer :: DeleteClipboard (void)
{
// Identifikator rücksetzen
	_CBIdent.ChangeCurrentIndex (-1);

// Merkmale zurücksetzen
	_CBMerkmal.ChangeCurrentIndex (-1);
	_LBMerkmale.Clear();
	DELETE (_pOML);

// Geometrie rücksetzen
	if (_pOG) {
	// GeometrieInfo löschen
		DELETE (_pOG -> pdblX);
		DELETE (_pOG -> pdblY);
		DELETE (_pOG -> plCnt);
		DELETE (_pOG);
	}

	_ObjClpStatusField.SetText (
		ResString (ResID (IDS_NOGEOMETRIE, &_RF), 30));

// UndoListe zerlegen
	DELETE (_pUList);
	
// hier aufhören, wenn sowieso nichts aktiv ist
	if (Status() == OCVIdle) return TRUE;

	_iCopyLage = _Lage.isChecked();
	_Lage.SetChecked (FALSE);
	_Lage.Disable();

	_iCopyForm = _Form.isChecked();
	_Form.SetChecked (FALSE);
	_Form.Disable();

	Status() = OCVIdle;

return TRUE;
}

// Eigentliche ClipBoardFunktionen --------------------------------------------
Bool ObjClipboardViewer :: InsertObject (long lONr, IMode IM)
{
// wenn kein Objekt aktiviert ist, dann ohne Kommentar wieder raus
	if (lONr == -1L) return FALSE;

// ClipBoard löschen, um Platz für den Neuen zu machen
	if (!DeleteClipboard()) 
		return FALSE;

// Objekt anfordern: 1. Geometrie holen
	_pOG = InsertObjectGeometrie (lONr);
	if (_pOG == NULL) 
		return FALSE;

// UndoList füllen, wenn Objekt herausgeschnitten wurde
	if (IM == IMDelete) {
		DELETE (_pUList);		// alte UndoListe freigeben
		_pUList = new UndoList ();	// neue UndoListe bilden
		if (_pUList) 
			_pUList -> AddUndo (_pOG -> lONr, USObjectDeleted);
	}
	
// Checkmarks wieder richten
	_Lage.Enable();
	_Lage.SetChecked (_iCopyLage);

	if (_pOG -> iObjTyp != OGPunkt && _pOG -> iObjTyp != OGText) {
	// Punkte haben keine Form
		_Form.Enable();
		_Form.SetChecked (_iCopyForm);
	} 

// Merkmale einlesen
	_LBMerkmale.Clear();			// alte Merkmale löschen
	DELETE (_pOML);
	_pOML = InsertObjectMerkmale (lONr);
	if (_pOML == NULL)
		return FALSE;

// Anzeige aktualisieren
	UpdateViewer ();
	EvalStatus();

// erstes Element aktivieren
	SendMessage (_LBMerkmale.Handle(), LB_SETCARETINDEX, 0, 0L);
	UpdateMList (0);

return TRUE;
}


// Objektgeometrie besorgen ---------------------------------------------------
OBJGEOMETRIE *InsertObjectGeometrie (long lONr)
{
// Eigenschaften des Objektes anfordern
OBJGEOMETRIE *pOG = new OBJGEOMETRIE;

	if (pOG == NULL) {
		db_error (EC_NOMEMORY, RC_InsertObjectGeometrie);
		return NULL;
	}

	memset (pOG, '\0', sizeof (OBJGEOMETRIE));
	pOG -> dwSize = sizeof (OBJSTATISTIK);
	pOG -> lONr = lONr;
	DEX_GetObjStatistik (*pOG);

// Geometrie dazuholen
	pOG -> dwSize = sizeof(OBJGEOMETRIE);

// Felder anfordern
	pOG -> pdblX = new long [pOG -> lCnt];
	pOG -> pdblY = new long [pOG -> lCnt];
	if (pOG -> pdblX == NULL || pOG -> pdblY == NULL) {
		DELETE (pOG -> pdblX);
		db_error (EC_NOMEMORY, RC_InsertObjectGeometrie);
		return NULL;
	}
		
	if (pOG -> iKCnt > 0) {
		if (pOG -> iObjTyp == OGFlaeche) {
			pOG -> plCnt = new long [pOG -> iKCnt];
			if (pOG -> plCnt == NULL) {
				db_error (EC_NOMEMORY, RC_InsertObjectGeometrie);
				return NULL;
			}
		} else if (pOG -> iObjTyp == OGText) {
			((TEXTGEOMETRIE *)pOG) -> pText = new char [pOG -> iKCnt];
			if (((TEXTGEOMETRIE *)pOG) -> pText == NULL) {
				db_error (EC_NOMEMORY, RC_InsertObjectGeometrie);
				return NULL;
			}
		}
	}
	DEX_GetObjGeometrie (*pOG);

return pOG;
}

extern "C" {

BOOL _XTENSN_EXPORT PASCAL GetObjMerkmale (long MCode, BOOL, void *pData)
{
TARGETMERKMAL TM;
ObjMerkmalsListe *pOML  = (ObjMerkmalsListe *)pData;
char *pText = new char [1025];

	if (pOML == NULL || pText == NULL) {
		DELETE (pText);
		return FALSE;
	}

	memset (&TM, '\0', sizeof (TARGETMERKMAL));
	TM.dwSize = sizeof (TARGETMERKMAL);
	TM.lTarget = pOML -> lONr();		// ObjektNummer
	TM.lMCode = MCode;			// MerkmalsCode
	TM.imaxLen = 1024;
	TM.pMText = pText;
	TM.iTTyp = TT_Objekt;

	DEX_GetTextMerkmal (TM);		// Merkmal holen
//	OemToAnsi (pText, pText);

ObjMerkmalCreator OMCr (*pOML);
ObjMerkmal *pOM = Create (OMCr, ObjMerkmal) (MCode, pText);

	DELETE (pText);

return pOM != NULL;
}

}	// extern "C"


// Einlesen aller Merkmale des gegebenen Objektes -----------------------------
ObjMerkmalsListe *InsertObjectMerkmale (long lONr)
{
ObjMerkmalsListe *pOML = new ObjMerkmalsListe (lONr);

	if (pOML == NULL) {
		db_error (EC_NOMEMORY, RC_InsertObjectMerkmale);
		return NULL;
	}

// alle Merkmale liefern lassen
ENUMLONGKEY ELK;

	ELK.eKey = lONr;	// ObjektNummer
	ELK.eFcn = (ENUMLONGKEYPROC)GetObjMerkmale;	// zu rufende Funktion
	ELK.ePtr = pOML;	// zusätzliche Daten

	DEX_EnumObjektMerkmale (ELK);

return pOML;
}


// Aktualisieren der Anzeige des Viewers --------------------------------------
Bool ObjClipboardViewer :: UpdateViewer (void)
{
	if (_pOG == NULL) return FALSE;

// Statusanzeige richten
	switch (_pOG -> iObjTyp) {
	case OGPunkt:
		_ObjClpStatusField.SetText (
			ResString (ResID (IDS_PUNKTGEOMETRIE, &_RF), 30));
		break;

	case OGLinie:
		_ObjClpStatusField.SetText (
			ResString (ResID (IDS_LINIENGEOMETRIE, &_RF), 30));
		break;

	case OGFlaeche:
		_ObjClpStatusField.SetText (
			ResString (ResID (IDS_FLAECHENGEOMETRIE, &_RF), 30));
		break;

	case OGText:
		_ObjClpStatusField.SetText (
			ResString (ResID (IDS_TEXTGEOMETRIE, &_RF), 30));
		break;

	case OGKO:
	case OGKreis:
	case OGUnknown:
	default:
		_ObjClpStatusField.SetText (
			ResString (ResID (IDS_UNKNOWNGEOMETRIE, &_RF), 30));
		break;
	}

// Identifikator einstellen
	{
	char pTmp[MAX_OKS_LENX+2];

		ClassFromIdentX (_pOG -> lIdent, pTmp);

	short iIndex = _CBIdent.FindString (pTmp);

		if (iIndex == -1) {
		// Identifikator nicht in der PBD: hinzufügen

			strcat (pTmp, ":");
			iIndex = _CBIdent.AddString (pTmp);
		}
		_CBIdent.ChangeCurrentIndex (iIndex);
	}

// ListBox mit allen Merkmalen füllen
	return FillMerkmale (TRUE);
}


// ----------------------------------------------------------------------------
// Paste des Clipboards an alle selektierten Objekte des gegebenen Fensters ---

extern "C" {

typedef struct tagPASTEOBJECT {
	HWND hWnd;
	ObjClipboardViewer *pOCV;
} PASTEOBJECT; 


// Beeinflussen eines der selektierten Objekte des gegebenen ORFensters -------
BOOL _XTENSN_EXPORT PASCAL PasteObject (long lONr, BOOL, void *pData)
{
ObjClipboardViewer *pOCV = ((PASTEOBJECT *)pData) -> pOCV;
HWND hWnd = ((PASTEOBJECT *)pData) -> hWnd;

// UndoElement in UndoListe generieren
	pOCV -> _pUList -> AddUndo (lONr);

// Geometrie zurückspeichern
	if (pOCV -> _Lage.isChecked() && 
	    (pOCV -> _Form.isChecked() || pOCV -> _pOG -> iObjTyp == OGPunkt || 
	    				  pOCV -> _pOG -> iObjTyp == OGText) &&
	// wenn Objekt mit sich selbst überlagert werden soll, dann 
	// diesen Punkt übergehen
	    pOCV -> _pOG -> lONr != lONr)
	{
	// Geometrie vollständig übernehmen (Overlay)
	OBJGEOMETRIE *pOG = pOCV -> _pOG;

		if (pOG != NULL) {	// Geometrie vorhanden
		COPYGEOMETRIE CG;

			memset (&CG, '\0', sizeof (COPYGEOMETRIE));
			CG.dwSize = sizeof (COPYGEOMETRIE);
			CG.lONr = lONr;		// zu modifizierendes Objekt
			CG.lIdent = 0L;		// nicht verändern
			CG.iFlags = OGOverlay | OGModObject;
			CG.lTargetONr = pOG -> lONr;	// Inhalt der Ablage

			DEX_ModObjGeometrie (CG);
			pOCV -> _pUList -> SetUStatus (lONr, USGeometrieModified);
		}
	}

// Identifikator modifizieren
	if (pOCV -> _Ident.isChecked()) {
	MODOBJIDENT MOI;
	char inBuff[80];

		pOCV -> _CBIdent.GetText (inBuff, sizeof (inBuff));	
		MOI.dwSize = sizeof (MODOBJIDENT);
		MOI.lONr = lONr;
		IdentFromClassX (inBuff, (ULONG *)&MOI.lNewIdent);
		MOI.iMode = VTypFromOTyp (pOCV -> _pOG -> iObjTyp);

		if (MOI.lNewIdent) {
			DEXOR_ModObjectIdent (hWnd, MOI);
			pOCV -> _pUList -> SetUStatus (lONr, USIdentModified);
		}
	}

	if (pOCV -> _Merkmale.isChecked() && 
	    pOCV -> _LBMerkmale.GetNoSelected() &&
	    pOCV -> _pOML != NULL) 
	{
	// alle selektierten Merkmale zurückspeichern
	CTable t(*(pOCV -> _pOML));
	TARGETMERKMAL TM;

		TM.dwSize = sizeof (TARGETMERKMAL);
		TM.lTarget = lONr;
		TM.iTTyp = TT_Objekt;

		for (t.First(); t.Valid(); t.Next()) {
		ObjMerkmalLock l(t);

			if (!l || !l -> isSelected()) continue;
			TM.lMCode = l -> MCode();
			TM.pMText = l -> pMText();
			TM.imaxLen = l -> pMText() != NULL ? strlen (l -> pMText()) : 0;

//			if (TM.pMText) AnsiToOem (TM.pMText, TM.pMText);
			DEX_ModTextMerkmal (TM);
			pOCV -> _pUList -> SetUStatus (lONr, USMerkmaleModified);
		}
	}

return TRUE;	// weitermachen
}

} // extern "C"

// Beeinflussen aller selektierten Objekte des gegebenen ORFensters -----------
Bool ObjClipboardViewer :: PasteObjectLocal (HWND hWnd)
{
	DELETE (_pUList);		// alte UndoListe freigeben
	_pUList = new UndoList (hWnd);	// neue UndoListe bilden
	
ENUMLONGKEY ELK;
PASTEOBJECT PO;

	PO.pOCV = this;
	PO.hWnd = hWnd;

	ELK.eFcn = (ENUMLONGKEYPROC)PasteObject;
	ELK.ePtr = &PO;
	ELK.eKey = (long)(void *)hWnd;		// dieses FensterHandle
	DEX_EnumSelectedObjects (ELK);

	DEX_RePaint();		// alles neu zeichnen

return TRUE;
}

// Neueinspeichern der Objektzwischenablage in die aktuelle GeoDB -------------
Bool ObjClipboardViewer :: PasteObjectGlobal (void)
{
	DELETE (_pUList);		// alte UndoListe freigeben
	
// Geometrie speichern/neues Objekt erzeugen
	if (_Lage.isChecked() && 
	    (_Form.isChecked() || 
	    (_pOG -> iObjTyp == OGPunkt || _pOG -> iObjTyp == OGText)))
	{
	// Geometrie als neues Objekt wegschreiben
		if (_pOG != NULL) {	// Geometrie vorhanden
			_pOG -> iFlags = OGNewObject | OGForceGeometry;
			_pOG -> lONr = -1;

			DEX_ModObjGeometrie (*_pOG);

		// UndoElement und UndoListe generieren
			_pUList = new UndoList ();	// neue UndoListe bilden
			if (_pUList) 
				_pUList -> AddUndo (_pOG -> lONr, USNewObject);
		}
	}

// Identifikator modifizieren
	if (_Ident.isChecked()) {
	MODOBJIDENT MOI;
	char inBuff[80];

		_CBIdent.GetText (inBuff, sizeof (inBuff));	
		MOI.dwSize = sizeof (MODOBJIDENT);
		MOI.lONr = _pOG -> lONr;
		IdentFromClassX (inBuff, (ULONG *)&MOI.lNewIdent);
		MOI.iMode = VTypFromOTyp (_pOG -> iObjTyp);

		if (MOI.lNewIdent) {
			DEX_ModObjectIdent (MOI);
			_pUList -> SetUStatus (_pOG -> lONr, USIdentModified);
		}
	}

// alle selektierten Merkmale zurückspeichern
	if (_Merkmale.isChecked() && 
	    _LBMerkmale.GetNoSelected() &&
	    _pOML != NULL) 
	{
	CTable t(*_pOML);
	TARGETMERKMAL TM;

		TM.dwSize = sizeof (TARGETMERKMAL);
		TM.lTarget = _pOG -> lONr;
		TM.iTTyp = TT_Objekt;

		for (t.First(); t.Valid(); t.Next()) {
		ObjMerkmalLock l(t);

			if (!l || !l -> isSelected()) 
				continue;
			TM.lMCode = l -> MCode();
			TM.pMText = l -> pMText();
			TM.imaxLen = l -> pMText() != NULL ? strlen (l -> pMText()) : 0;

			DEX_ModTextMerkmal (TM);
			_pUList -> SetUStatus (_pOG -> lONr, USMerkmaleModified);
		}
	}

// neu zeichnen
	DEX_RePaint();

return TRUE;
}

// ----------------------------------------------------------------------------
// PBD-Daten einlesen ---------------------------------------------------------

// IdentifikatorBeschreibungen aus der PBD lesen ------------------------------

extern "C" {

typedef struct tagFILLIDENT {
	ComboBox *m_pCB;
} FILLIDENT;

BOOL _XTENSN_EXPORT PASCAL FillIdentsListBox (long Ident, BOOL, void *pData)
{
ErrInstall EC (WC_NOIDENT);
PBDDATA pbdData;
char KText[34];
FILLIDENT *pFI = (FILLIDENT *)pData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'i';
	pbdData.pbdCode = Ident;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	if (EC_OKAY != DEX_GetPBDData (pbdData))
		return true;	// trotzdem weitermachen

char outBuff[80];

	ClassFromIdentX (Ident, outBuff);
	strcat (outBuff, ":");
	strcat (outBuff, pbdData.pbdKText);
	pFI -> m_pCB -> AddString (outBuff);

return TRUE;	// weitermachen
}

} 	// extern "C"


void ObjClipboardViewer :: ReReadIdents (long Id)
{
// wenn noch kein Projekt eröffnet ist, dann wieder raus
char cbBuffer[_MAX_PATH+1];

	if (NULL == DEX_GetActiveProject (cbBuffer)) return;	// nichts eröffnet

// Liste aller Identifikatoren der PBD füllen
char *pInBuff = new char [1025];

	if (pInBuff == NULL) return;

short iIndex = _CBIdent.GetCurrentIndex();

	if (iIndex != -1) {
	char *cptr = NULL;

		_CBIdent.GetString (pInBuff, iIndex, 1024);
		if (cptr = strchr (pInBuff, ':')) *(cptr+1) = '\0';
	} else
		pInBuff[0] = '\0';

FILLIDENT FI;

	FI.m_pCB = &_CBIdent;

	if (Id == 0) {
	// alles neu lesen
		_CBIdent.Clear();	// erstmal alles löschen
	
	ENUMLONGKEY ELK;
	
		memset (&ELK, '\0', sizeof (ENUMLONGKEY));
		ELK.eKey = 'i';
		ELK.eFcn = (ENUMLONGKEYPROC)FillIdentsListBox;
		ELK.ePtr = &FI;
		DEX_EnumPBDData (ELK);

		if (iIndex != -1) iIndex = _CBIdent.FindString (pInBuff);
	} else {
	// nur einen neu lesen
	short iIndex2 = -1;
	ULONG ulIdent = 0L;

		IdentFromClassX (pInBuff, &ulIdent);
		if (ulIdent != (ULONG)Id) 
		// nicht aktuelle Selektion wurde geändert, Eintrag suchen
			ClassFromIdentX (Id, pInBuff);
			iIndex2 = _CBIdent.FindString (pInBuff);

		if (iIndex2 != -1) 	// wenn gefunden, Eintrag löschen
			_CBIdent.DelString (iIndex2);
		
		FillIdentsListBox (Id, TRUE, &FI);	// neuen Eintrag hinzufügen
	}

// wieder auf vorherige Selektion stellen
	_CBIdent.ChangeCurrentIndex (iIndex);

	DELETE (pInBuff);
}


// Merkmale aus der PBD lesen -------------------------------------------------
extern "C" {

typedef struct tagFILLMCODEDATA {
	ListBox *m_pLB;
	short m_iMkBase;
} FILLMCODEDATA;

BOOL _XTENSN_EXPORT PASCAL FillMCodesListBox (long MCode, BOOL, void *pData)
{
ErrInstall EC (WC_NOMERKMAL);
PBDMERKMAL pbdData;
char KText[34];
FILLMCODEDATA *pFMD = (FILLMCODEDATA *)pData;

	INITSTRUCT(pbdData, PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = MCode;
	pbdData.pbdKText = KText;
	pbdData.pbdKTextLen = sizeof(KText) -1;
	pbdData.pbdLTextLen = 0;
	pbdData.ipbdMTyp = 'u';

	if (EC_OKAY != DEX_GetPBDData (pbdData))
		return true;		// trotzdem weitermachen

char outBuff[80];

	if (pFMD -> m_iMkBase == 10)
		wsprintf (outBuff, "%08ld:%s", MCode, pbdData.pbdKText);
	else
		wsprintf (outBuff, "%08lx:%s", MCode, pbdData.pbdKText);
	pFMD -> m_pLB -> AddString (outBuff);

return TRUE;	// weitermachen
}

} // extern "C"


// Füllen der ComboBox für die PBDMerkmalsInfo --------------------------------
void ObjClipboardViewer :: ReReadMCodes (long MCode)
{
// wenn noch kein Projekt eröffnet ist, dann wieder raus
char cbBuffer[_MAX_PATH+1];

	if (NULL == DEX_GetActiveProject (cbBuffer)) return;	// nichts eröffnet


// Liste aller Merkmale der PBD füllen
char *pInBuff = new char [1025];

	if (pInBuff == NULL) return;

short iIndex = _CBMerkmal.GetCurrentIndex();

	if (iIndex != -1) {
	char *cptr = NULL;

		_CBMerkmal.GetString (pInBuff, iIndex, 1024);
		if (cptr = strchr (pInBuff, ':')) *(cptr+1) = '\0';
	} else
		pInBuff[0] = '\0';

	if (MCode == 0) {
	// alles neu lesen
		_CBMerkmal.Clear();	// erstmal alles löschen
	
	FILLMCODEDATA FMD;
	
		FMD.m_pLB = &_CBMerkmal;
		FMD.m_iMkBase = m_iMkBase;
		
	ENUMLONGKEY ELK;

		memset (&ELK, '\0', sizeof (ENUMLONGKEY));
		ELK.eKey = 'm';
		ELK.eFcn = (ENUMLONGKEYPROC)FillMCodesListBox;
		ELK.ePtr = &FMD;
		DEX_EnumPBDData (ELK);

		if (iIndex != -1) iIndex = _CBMerkmal.FindString (pInBuff);
	} else {
	// nur einen neu lesen
	short iIndex2 = -1;

		if (strtoul (pInBuff, NULL, m_iMkBase) != (ulong)MCode) 
		// nicht aktuelle Selektion wurde geändert, Eintrag suchen
			iIndex2 = _CBMerkmal.FindString (ultoa (MCode, pInBuff, m_iMkBase));

		if (iIndex2 != -1) 	// wenn gefunden, Eintrag löschen
			_CBMerkmal.DelString (iIndex2);

	FILLMCODEDATA FMD;
	
		FMD.m_pLB = &_CBMerkmal;
		FMD.m_iMkBase = m_iMkBase;
		FillMCodesListBox (MCode, TRUE, &FMD);	// neuen Eintrag hinzufügen
	}

// wieder auf vorherige Selektion stellen
	_CBMerkmal.ChangeCurrentIndex (iIndex);

	DELETE (pInBuff);
}


// Berechnet den Status der ObjektZwischenablage ------------------------------
ObjClpStatus ObjClipboardViewer :: EvalStatus (void)
{
// Invalid bleibt immer Invalid
	if (Status() == OCVInValid)
		return OCVInValid;

// wenn Geometrie vollständig da ist, dann Objekt gültig
	if (_Lage.isChecked() && 
	    (_Form.isChecked() || 
	    (_pOG -> iObjTyp == OGPunkt || _pOG -> iObjTyp == OGText)))
		return Status() = OCVObjectValid;

// wenn sonst wenigstens ein Feature aktiv ist, dann Info gültig
	if (_Lage.isChecked() || _Form.isChecked() ||
	    (_Merkmale.isChecked() && _LBMerkmale.GetNoSelected()) || 
	    _Ident.isChecked() /*|| _Relationen.isChecked()*/)
		return Status() = OCVInfoValid;

// sonst eben Idle
	return Status() = OCVIdle;
}


// Editieren eines der MerkmalsWerte ------------------------------------------
void ObjClipboardViewer :: EditMWert (Bool iNewMCode)
{
char *pMDesc = NULL;
long lMCode = GetCurrentPBDMCode (&pMDesc);

	if (lMCode == -1L) return;		// kein MCode gegeben

	if (_pOML == NULL) _pOML = new ObjMerkmalsListe ();
	if (_pOML == NULL) return;

CTable t(*_pOML);

	if (t.Find (&lMCode) || iNewMCode) {
	char *pInBuff = new char [1025];
	Bool oldSelection = FALSE;

		if (pInBuff == NULL) return;
		if (!iNewMCode) {
		ObjMerkmalLock l(t);

			if (!l) return;
			if (l -> pMText())
				strcpy (pInBuff, l -> pMText());
			else
				*pInBuff = '\0';
			oldSelection = l -> isSelected();
		} else
			*pInBuff = '\0';

	// DialogFenster anlegen und anzeigen
	ObjMerkmalDlg OMDlg (this, &_RF, pInBuff, pMDesc);

		OMDlg.Show();		// Fenster anzeigen

		if (OMDlg.Result()) {
			OMDlg.GetNewText (pInBuff, 1024);

		// neuer MerkmalsWert wurde eingegeben
			if (!iNewMCode) t.Delete();	// Merkmal aus Baum löschen

			{	// neu in Baum einhängen
			ObjMerkmalCreator OMCr (*_pOML);
			ObjMerkmal *pOM = Create (OMCr, ObjMerkmal) (lMCode, pInBuff);

				if (pOM) pOM -> isSelected() = oldSelection;
			}	// in den Baum speichern
			FillMerkmale (TRUE);
		}
		DELETE (pInBuff);
	}

// Speicher freigeben
	DELETE (pMDesc);
}


Bool ObjClipboardViewer :: FillMerkmale (Bool iClear)
{
	if (_pOML == NULL) return FALSE;

	if (iClear) _LBMerkmale.Clear();

CTable t(*_pOML);

	for (t.First(); t.Valid(); t.Next()) {
	ObjMerkmalLock l(t);
	char outBuff[80];

		if (!l) continue;
		if (l -> pMText() == NULL) {
			if (m_iMkBase == 10) 
				wsprintf (outBuff, "%08ld:", l -> MCode());
			else
				wsprintf (outBuff, "%08lx:", l -> MCode());
		} else {
			if (m_iMkBase == 10) 
				wsprintf (outBuff, "%08ld:%-40.40s", l -> MCode(), l -> pMText());
			else
				wsprintf (outBuff, "%08lx:%-40.40s", l -> MCode(), l -> pMText());
		}

	short iIndex =_LBMerkmale.AddString (outBuff);

		if (l -> isSelected())
			_LBMerkmale.ChangeSelected (iIndex);
	}

return TRUE;
}

// Löschen aller selektierten Merkmale ----------------------------------------
void ObjClipboardViewer :: DeleteMerkmale (void)
{
	if (_pOML == NULL) return;

CTable t(*_pOML);

	for (t.First(); t.Valid(); ) {
	Bool toDelete = FALSE;

		{
		ObjMerkmalLock l(t);

			if (l && l -> isSelected()) toDelete = TRUE;
		}
		if (toDelete) 	t.Delete();
		else		t.Next();
	}

	FillMerkmale (TRUE);
}


// Löschen aller selektierten MerkmalsWerte -----------------------------------
void ObjClipboardViewer :: DeleteMerkmalsWerte (void)
{
	if (_pOML == NULL) return;

CTable t(*_pOML);

	for (t.First(); t.Valid(); t.Next()) {
	ObjMerkmalLock l(t);

		if (l && l -> isSelected()) 
			l -> ResetMWert();
	}

	FillMerkmale (TRUE);
}


Bool ObjClipboardViewer :: UpdateMList (short iDefIndex)
{
char *pInBuff = new char [1025];
short iIndex;
char *cptr;

	if (pInBuff == NULL) return FALSE;

	if (iDefIndex == -1) iIndex = (short)SendMessage (_LBMerkmale.Handle(), LB_GETCARETINDEX, 0, 0L);
	else		     iIndex = iDefIndex;

	_LBMerkmale.GetString (pInBuff, iIndex, 1024);
	if ((cptr = strchr (pInBuff, ':')) != NULL) *(cptr+1) = '\0';

	iIndex = _CBMerkmal.FindString (pInBuff);
	if (iIndex == -1) 
		iIndex = _CBMerkmal.AddString (pInBuff);

	_CBMerkmal.ChangeCurrentIndex (iIndex);

	DELETE (pInBuff);

return TRUE;
}

// Rücksetzen des FensterHandles in der UndoListe -----------------------------
void ObjClipboardViewer :: ResetUndoHandle (HWND hWnd)
{
	if (_pUList) _pUList -> ResetHandle (hWnd);
}


// Feststellen, ob ein MerkmalsCode breits belegt ist -------------------------
Bool ObjClipboardViewer :: isNotMCodeUsed (long MCode)
{
	if (_pOML == NULL) _pOML = new ObjMerkmalsListe();
	if (_pOML == NULL) return TRUE;

	if (MCode == -1L) return FALSE;

CTable t(*_pOML);

	return !t.Find (&MCode);
}


// holt den aktuellen PBDMCode aus der Combobox -------------------------------
long ObjClipboardViewer :: GetCurrentPBDMCode (char **ppMDesc)
{
short iIndex = _CBMerkmal.GetCurrentIndex();
long lMCode = -1L;

	if (iIndex == -1 || (ppMDesc == NULL && _pOML == NULL)) {
		if (ppMDesc) *ppMDesc = NULL;
		return -1L;
	}

// besorgen von MCode, KurzText und MWert
char *pMDesc = new char [80];

	if (pMDesc == NULL) {
		if (ppMDesc) *ppMDesc = NULL;
		return -1L;
	}

	_CBMerkmal.GetString (pMDesc, iIndex, 79);
	if ((lMCode = strtoul (pMDesc, NULL, m_iMkBase)) == 0) 
		lMCode = -1L;

	if (ppMDesc) 
		*ppMDesc = pMDesc;	// Pointer wird noch gebraucht
	else	     
		delete pMDesc;		// Pointer freigeben

return lMCode;
}
