// ----------------KompaktFunktionsübersicht -----------------------------
// File: KOMPWIN.CXX

#include "kompp.hxx"
#include "kompias.h"
#include <igeometr.hxx>

#include "triasdef.h"
#include "kompdef.h"

#include "kompwin.hxx"
 
// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

KompaktInformation :: KompaktInformation (pWindow pW, uint res, ResourceFile &RF)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _RF (RF),
		KPAuschr (this, IDB_KPAUSSCHREIBUNG),
		KPAuftrag (this, IDB_KPAUFTRAG),
		KPAufmass (this, IDB_KPAUFMASS),
		KPUnterhaltung (this, IDB_KPUNTERHALTUNG),
		KPOekologie (this, IDB_KPOEKOLOGIE),
		KPRechte (this, IDB_KPRECHTE),
		KPBauwerke (this, IDB_KPBAUWERKE),
		KPKataster (this, IDB_KPKATASTER),
		KPVerband (this, IDB_KPVERBAND),
		KPProjekte (this, IDB_KPPROJEKTE),
		KPHydrologie (this, IDB_KPHYDRAULIK),
		KPKompakt (this, IDB_KPKOMPAKT),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)

{

//	StartWerte
	_pW = pW;
//	pW->Disable();
	return;
}

#pragma warning (default: 4355)


KompaktInformation :: ~KompaktInformation (void)
{
//	_pW->Enable();
}
//---------------------------------------------------------

void _XTENSN_EXPORT KompaktInformation :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDOK: 	// = TRIAS
		{
		EndDlg (KP_TRIAS);
		}
		break;

	case IDCANCEL:	// = Abbrechen = CLOSE
		{
		EndDlg (0);
		}
		break;

	case IDB_KPAUSSCHREIBUNG:
		{
		EndDlg (KP_AUSSCHREIBUNG);
		}
		break;

	case IDB_KPAUFTRAG:
		{
		EndDlg (KP_AUFTRAG);
		}
		break;

	case IDB_KPAUFMASS:
		{
		EndDlg (KP_AUFMASS);
		}
		break;

	case IDB_KPUNTERHALTUNG:
		{
		EndDlg (KP_UNTERHALTUNG);
		}
		break;

	case IDB_KPOEKOLOGIE:
		{
		EndDlg (KP_OEKOLOGIE);
		}
		break;

	case IDB_KPBAUWERKE:
		{
		EndDlg (KP_BAUWERKE);
		}
		break;

	case IDB_KPRECHTE:
		{
		EndDlg (KP_RECHTE);
		}
		break;

	case IDB_KPKATASTER:
		{
		EndDlg (KP_KATASTER);
		}
		break;

	case IDB_KPVERBAND:
		{
		EndDlg (KP_VERBAND);
		}
		break;

	case IDB_KPPROJEKTE:
		{
		EndDlg (KP_PROJEKTE);
		}
		break;

	case IDB_KPHYDRAULIK:
		{
		EndDlg (KP_HYDRAULIK);
		}
		break;

	case IDB_KPKOMPAKT:
		{
		EndDlg (KP_KOMPAKT);
		}
		break;
	}
}
//---------------------------------------------------------------------------

// Konstruktoren/Destruktoren der DialogFenster --------------------------------

#pragma warning (disable: 4355)

DatenAuswahl :: DatenAuswahl (pWindow pW, uint res,  ResourceFile &RF)
	     : DialogWindow (pW, ResID ( res, &RF)),
	       _GewNr (this,IDS_DATENGEWNR),
	       _Pos (this,IDS_DATENPOSITION),
	       _Hoehe (this,IDS_DATENHOEHE),
	       OKButton (this, IDOK),
	       CancelButton (this, IDCANCEL)
{

//	StartWerte
	_pW = pW;
//	pW->Disable();
	_Pos.SetText(NULL);
	_GewNr.SetText(NULL);
	_Hoehe.SetText(NULL);
	_lPos = 0;
	_dHoehe = 0.0;
	_pGewNr = new char [_MAX_PATH];

}

#pragma warning (default: 4355)


DatenAuswahl :: ~DatenAuswahl (void)
{
	DELETE_OBJ (_pGewNr);
//	_pW->Enable();
}



void _XTENSN_EXPORT DatenAuswahl :: ButtonClick (ControlEvt e)
{
	switch ((unsigned int)e.GetControlID()) {
	case IDOK: 
		{
		char *_pWert = new char [50];

		_GewNr.GetText ( _pGewNr , _MAX_PATH-1 );

		_Hoehe.GetText ( _pWert , _MAX_PATH-1 );
		_dHoehe = atof ( _pWert );

		_Pos.GetText ( _pWert , _MAX_PATH-1 );
		_lPos = atol ( _pWert );
		DELETE_OBJ ( _pWert);
		}
		EndDlg(1);
		break;

	case IDCANCEL:
		{
		}
		EndDlg (0);
		break;
	}

}
//---------------------------------------------------------------------
//----------KOMPWIN.CXX-------------------------------------------------
//---------------------------------------------------------------------------
// Ende KOMPWIN.CXX
