// Dialogfenster fuer die PunktObjektEditierung -------------------------------
// File: EDITPNT.CXX

#include "editobjp.hxx"

#include "editpnt.h"

#include <dllbindx.hxx>
#include <dblpair.hxx>
#include <objcontx.hxx>
#include <ctfx.hxx>
#include <numeditx.hxx>
#include <dblnumex.hxx>

#include "identlst.hxx"
#include "editpnt.hxx"

// Konstruktor/Destruktor -----------------------------------------------------
#pragma warning (disable: 4355)

EditPointObjDlg :: EditPointObjDlg (pWindow pW, ResourceFile *pRF, IdentList &IL,
				    long Ident, Punkt &Pkt)
		 : DialogWindow (pW, ResID (POINTEDITDLG, pRF)),
		   _IDList (this, IDCB_POINTIDENT),
		   _X (this, IDE_POINTX),
		   _Y (this, IDE_POINTY),
		   _HelpButton (this, IDB_EDITPOINTOBJHELP),
		   _IL (IL),
		   _Pkt (Pkt),
		   _Ident (Ident)
{
// Contrrols initialisieren
	_HelpButton.Disable();
	
// Variablen initialisieren
	_pCTFX = new CoordTransX ();

// ComboBox füllen
CTable t(_IL);
char *pOutBuff = new char [64];

	if (pOutBuff == NULL) {
		_IDList.Disable();
		return;
	}

	for (t.First(); t.Valid(); t.Next()) {
	IdentListEntryLock l(t);                                        
	
		if (!l) continue;

		ClassFromIdentX (l -> Ident(), pOutBuff);
		strcat (pOutBuff, ":");
		strcat (pOutBuff, l -> KText());
		_IDList.AddString (pOutBuff);
	}       

// Voreinstellungen                 
	if (Ident != -1L) {
		ClassFromIdentX (Ident, pOutBuff);

	short iIndex = _IDList.FindString (pOutBuff);
	
		if (iIndex != -1) _IDList.ChangeCurrentIndex (iIndex);
	}

	_X.SetNumEditMode (NumEditX :: NEM_NoTest);
	_Y.SetNumEditMode (NumEditX :: NEM_NoTest);

	if (Pkt.X() != -1 && Pkt.Y() != -1) {
		if (_pCTFX) {
		double X, Y;

			_pCTFX -> UnScale (Pkt.X(), Pkt.Y(), &X, &Y);
			_pCTFX -> Transform (&X, &Y);
			_pCTFX -> CoordTransToString (X, TRUE, pOutBuff, 64);
			_X.SetText (pOutBuff);
			_pCTFX -> CoordTransToString (Y, FALSE, pOutBuff, 64);
			_Y.SetText (pOutBuff);
		} else {
			_X.SetText (ltoa (Pkt.X(), pOutBuff, 10));
			_Y.SetText (ltoa (Pkt.Y(), pOutBuff, 10));
		}
	}

	DELETE (pOutBuff);
}

#pragma warning (default: 4355)

EditPointObjDlg :: ~EditPointObjDlg (void)
{
	DELETE (_pCTFX);
}



// EventHandler ---------------------------------------------------------------
void _XTENSN_EXPORT EditPointObjDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetControlID()) {
	case IDOK:
		EndDlg (1);
		break;
		
	case IDCANCEL:
		EndDlg (0);
		break;
	}
}


// Click auf ListBox ----------------------------------------------------------
void _XTENSN_EXPORT EditPointObjDlg :: ListBoxClk (ControlEvt)
{

}

// DoppelClick auf ListBox ----------------------------------------------------
void _XTENSN_EXPORT EditPointObjDlg :: ListBoxSel (ControlEvt)
{

}

// Resultatsfunktionen --------------------------------------------------------
Bool EditPointObjDlg :: GetIdent (long &ResultID)
{
char *pInBuff = new char [64];
short iIndex = _IDList.GetCurrentIndex();

	if (iIndex == -1 || pInBuff == NULL) return FALSE;

	_IDList.GetString (pInBuff, iIndex, 64);
	IdentFromClassX (pInBuff, (ULONG *)&ResultID);

	DELETE (pInBuff);

return TRUE;
}


Bool EditPointObjDlg :: GetPunkt (Punkt &ResultPkt)
{
	if (!_X.GetEditControl() -> isModified() &&
	    !_Y.GetEditControl() -> isModified())
	// keine der Koordinaten wurde geändert             
		return FALSE;

char *pInBuff = new char [64];

	if (pInBuff == NULL) return FALSE;

	if (_pCTFX) {
	double X, Y;

		_X.GetText (pInBuff, 64);
		X = _pCTFX -> CoordTransToValue (pInBuff);
		_Y.GetText (pInBuff, 64);
		Y = _pCTFX -> CoordTransToValue (pInBuff);

		_pCTFX -> InvTransform (&X, &Y);
		_pCTFX -> Scale (X, Y, ResultPkt);
	} else {
		_X.GetText (pInBuff, 64);
		ResultPkt.X() = atol (pInBuff);
		_Y.GetText (pInBuff, 64);
		ResultPkt.Y() = atol (pInBuff);
	}

	DELETE (pInBuff);

return TRUE;
}

