// Anzeige des Resultats einer Objektrecherche --------------------------------
// File: RECHRES.CXX


extern "C" {
	#include <windows.h>
	#include <string.h>
	
	#include <xtension.h>
	#include <xtensnx.h>
	
	#include "rechres.h"
}

#include <commonvu.hxx>

#include "rechres.hxx"


BOOL ShowRechResultDlg (pWindow pW)
{
CRechResultDlg RRDlg (pW);

	if (!RRDlg.Init()) return FALSE;
	RRDlg.Show();
	
return RRDlg.Result();
}


// Konstruktor/Destruktor -----------------------------------------------------
CRechResultDlg :: CRechResultDlg (pWindow pW)
		: DialogWindow (pW, RECHRESULTDLG),
		  m_cmViews (this, IDC_RECHRES_VIEWS),
		  m_cmObjProps (this, IDC_RECHRES_OBJPROPS),
		  m_cbObjNr (this, IDCB_RECHRES_OBJNR),
		  m_cbObjTyp (this, IDCB_RECHRES_OBJTYP),
		  m_cbIdent (this, IDCB_RECHRES_IDENT),
		  m_bHelp (this, IDB_RECHRES_HELP)
{
// Controls initialisieren
	m_bHelp.Disable();
}


CRechResultDlg :: ~CRechResultDlg (void)
{
	// nothing else to do
}


// Initialisierung der daten dieser DialogBox ---------------------------------
BOOL CRechResultDlg :: Init (void)
{
// Sichten einlesen

// ObjProps einlesen

// Voreinstellungen der aktuellen Sicht einlesen und anzeigen

}


// EventHandler ---------------------------------------------------------------
void CRechResultDlg :: ButtonClick (ControlEvt e)
{
	switch ((uint)e.GetItemID()) {
	case IDOK:
		EndDlg (SaveResultsToView());
		break;
		
	case IDCANCEL:
		EndDlg (0);
		break;
	}
}


BOOL CRechResultDlg :: SaveResultsToView (void)
{
	return TRUE;
}
