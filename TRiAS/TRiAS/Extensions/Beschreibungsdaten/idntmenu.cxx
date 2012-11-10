// Menubefehle abarbeiten -----------------------------------------------------
// File: IDNTMENU.CXX

#include "idntsdbp.hxx"

#if defined(WIN32)
#pragma warning (disable: 4304)
#include <ospace/std/set>
#endif // WIN32

#include <eieruhr.hxx>

#include "newident.hxx"
#include "newmcode.hxx"
#include "newrcode.hxx"

#include "identsdb.hxx"

#include "identsdb.h"
#include "identres.h"
#include "newident.h"
#include "newmcode.h"
#include "newrcode.h"

// Identifikatoren neu definieren oder modifizieren ---------------------------
bool CIdentsDBExtension :: DefineIdentifier (void)
{
NewIdentDlg NIDlg (MWind(), ResID (DEFINEIDENTDLG, &RF()));

#if defined(WIN32)
ResString resUndo (ResID (IDS_UNDOMODIDENTS, &RF()), 128);
HRESULT hr = DEX_BeginUndoLevel (resUndo.Addr());

	NIDlg.Show (Centre);
	if (NIDlg.Result()) {
		if (SUCCEEDED(hr))
			DEX_EndUndoLevel();
		return true;
	} else if (SUCCEEDED(hr))
		DEX_CancelUndoLevel(false);	// wird nicht gebraucht

return false;
#else
	NIDlg.Show (Centre);

return NIDlg.Result();
#endif // WIN32
}

// Merkmale neu definieren oder modifizieren ----------------------------------
bool CIdentsDBExtension :: DefineMerkmal (void)
{
NewMCodeDlg NMCDlg (MWind(), ResID (DEFMERKMALDLG, &RF()), m_iMkBase);

#if defined(WIN32)
ResString resUndo (ResID (IDS_UNDOMODMCODES, &RF()), 128);
HRESULT hr = DEX_BeginUndoLevel (resUndo.Addr());

	NMCDlg.Show (Centre);
	if (NMCDlg.Result()) {
		if (SUCCEEDED(hr))
			DEX_EndUndoLevel();
		return true;
	} else if (SUCCEEDED(hr))
		DEX_CancelUndoLevel(false);	// wird nicht gebraucht

return false;
#else
	NMCDlg.Show (Centre);

return NMCDlg.Result();
#endif
}

// Identifikator(en) löschen --------------------------------------------------
bool CIdentsDBExtension :: DeleteIdentifier (void)
{
pWindow pW = MWind();		// HauptFenster
DelIdentDlg DIDlg (pW, ResID (DELIDENTDLG, &RF()));

	DIDlg.Show (Centre);
	if (!DIDlg.Result()) return false;

long Id = DIDlg.FirstIdent();
CEierUhr Wait (pW);
#if defined(WIN32)
ResString resUndo (ResID (IDS_UNDODELIDENTS, &RF()), 128);
HRESULT hr = DEX_BeginUndoLevel (resUndo.Addr());
#endif // WIN32
	
// Sätze aus Pbd herauslöschen
	DEX_BeginPBDTransaction();
	while (Id != -1L) {
		if (!DeleteIdent (Id)) {
		// Fehler: Zustand wieder herstellen
			DEX_BreakPBDTransaction();
#if defined(WIN32)
			if (SUCCEEDED(hr)) 
				DEX_CancelUndoLevel (false);	// nicht mehr gebraucht
#endif // WIN32
			return false;
		}
		Id = DIDlg.NextIdent();
	}

	DEX_EndPBDTransaction();
	DEXN_PBDIdentsChanged();
#if defined(WIN32)
	if (SUCCEEDED(hr)) DEX_EndUndoLevel();
#endif // WIN32

return true;
}

// Merkmalsbeschreibung(en) löschen -------------------------------------------
bool CIdentsDBExtension :: DeleteMerkmal (void)
{
pWindow pW = MWind();		// HauptFenster
DelMCodeDlg DMCDlg (pW, ResID (DELMERKMALDLG, &RF()), m_iMkBase);

	DMCDlg.Show (Centre);
	return DMCDlg.Result();
}

