// $Header: $
// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 20.12.2002 11:31:12
//
// @doc    Dialog zu PropertyAction für topologische Relationen von GeoObjekten
//         Auswahl der gewünschten Relationen
// @module TopoRelDlg.cpp | Implementation of the <c CTopoRelDlg> class

#include "TopoRelP.hxx"

#include "TopoRelR.h"
#include "TopoRelDlg.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




///////////////////////////////////////////////////////////////////////////////////////////////
// CTopoRelDlg

CTopoRelDlg* CTopoRelDlg::CreateInstance (LPCSTR pcCaption)
{
CTopoRelDlg* pRelationDlg = NULL;

	COM_TRY
	{
	// RelationenDialog erzeugen
	ResourceFile RF (g_pDLLName);

		pRelationDlg = new CTopoRelDlg (ResID(CTopoRelDlg::IDD, &RF), pcCaption);
		if (NULL == pRelationDlg || !pRelationDlg -> FInit())
		{
			DELETE_OBJ(pRelationDlg);
			return NULL;
		}

	}
	COM_CATCH_OP_RETURN(delete pRelationDlg, NULL);

	return pRelationDlg; 
}


// --------------------------------------------------------------------------------------------
CTopoRelDlg::CTopoRelDlg(ResID uiDlg, LPCSTR pcCaption) 
           : CPropertyPage(uiDlg, pcCaption),
			 m_CBoxIntersect (this, IDC_INTERSECT),
			 m_CBoxWithin (this, IDC_WITHIN),
			 m_CBoxContain (this, IDC_CONTAIN),
			 m_CBoxOverlap (this, IDC_OVERLAP),
			 m_CBoxEnter (this, IDC_ENTER),
			 m_CBoxTouch (this, IDC_TOUCH),
			 m_CBoxEqual (this, IDC_EQUAL),
			 m_CBoxDisjoint (this, IDC_DISJOINT),
			 m_CBoxRechWindows (this, IDC_RECHWINDOWS),
		     m_Descript (this, IDT_OPTDESCRIPT)
{
	m_dwFlags = 0;
	m_ulSelRelat = WITH;	// default-Werte
	m_bSepaWin = true;
}


// --------------------------------------------------------------------------------------------
CTopoRelDlg::~CTopoRelDlg()
{
}


// --------------------------------------------------------------------------------------------
// Die Haupt-Button "Zurück", "Weiter" bzw. "Fertig stellen" und "Abbrechen" de/aktivieren
void CTopoRelDlg::AdjustSheetButtons()
{
CPropertySheet *pSheet = GetPropertySheet();

	_ASSERTE(NULL != pSheet);	

DWORD dwBttns = 0;

	if (!(m_dwFlags & ADDPAGES_FIRSTPAGE))
		dwBttns = PSWIZB_BACK;			// nicht erste Seite

	if (!GetDisableNextPage()) {
		if (m_dwFlags & ADDPAGES_LASTPAGE) 
			dwBttns |= PSWIZB_FINISH;	// letzte Seite
		else 
			dwBttns |= PSWIZB_NEXT;		// nicht letzte Seite
	} else if (m_dwFlags & ADDPAGES_LASTPAGE)
		dwBttns |= PSWIZB_DISABLEDFINISH;

	pSheet -> SetWizardButtons(dwBttns);
}


// --------------------------------------------------------------------------------------------
BOOL CTopoRelDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled

	return FALSE;
}


///////////////////////////////////////////////////////////////////////////////////////////////
// CTopoRelDlg message handlers

// wird gerufen, wenn diese Page aktiviert werden soll (i. a. dann, wenn in der vorangehenden
// Page der Button "Weiter" bzw. in der nachfolgenden Page der Button "Zurück" gedrückt wurde)
BOOL CTopoRelDlg::OnSetActive (NotifyEvt e) 
{
	AdjustSheetButtons();
	return FALSE;		// bei Gültigkeit "FALSE" sonst "TRUE" (???)
}


///////////////////////////////////////////////////////////////////////////////////////////////
// EventHandler 
// Call-Back-Funktion für die Initialisierung der Controls
void CTopoRelDlg::WindowInit (Event)
{
    // explizite Initialisierung der Controls
	m_CBoxIntersect.FInit();
	m_CBoxWithin.FInit();
	m_CBoxContain.FInit();
	m_CBoxOverlap.FInit();
	m_CBoxEnter.FInit();
	m_CBoxTouch.FInit();
	m_CBoxEqual.FInit();
	m_CBoxDisjoint.FInit();
	m_CBoxRechWindows.FInit();
	m_Descript.FInit();

// Controls setzen
bool bIntersect = true;		// m_CBoxIntersect soll gesetzt werden

	if (m_ulSelRelat & WITH)
		m_CBoxWithin.SetChecked (true);
	else
	{
		m_CBoxWithin.SetChecked (false);
		bIntersect = false;
	}

	if (m_ulSelRelat & CONT)
		m_CBoxContain.SetChecked (true);
	else
	{
		m_CBoxContain.SetChecked (false);
		bIntersect = false;
	}

	if (m_ulSelRelat & OVER)
		m_CBoxOverlap.SetChecked (true);
	else
	{
		m_CBoxOverlap.SetChecked (false);
		bIntersect = false;
	}

	if (m_ulSelRelat & ENTE)
		m_CBoxEnter.SetChecked (true);
	else
	{
		m_CBoxEnter.SetChecked (false);
		bIntersect = false;
	}

	if (m_ulSelRelat & TOUC)
		m_CBoxTouch.SetChecked (true);
	else
	{
		m_CBoxTouch.SetChecked (false);
		bIntersect = false;
	}

	if (m_ulSelRelat & EQUA)
		m_CBoxEqual.SetChecked (true);
	else
	{
		m_CBoxEqual.SetChecked (false);
		bIntersect = false;
	}

	if (bIntersect)
		m_CBoxIntersect.SetChecked (true);
	else
		m_CBoxIntersect.SetChecked (false);

	if (m_ulSelRelat & DISJ)
		m_CBoxDisjoint.SetChecked (true);
	else
		m_CBoxDisjoint.SetChecked (false);

	if (m_bSepaWin)
		m_CBoxRechWindows.SetChecked (true);
	else
		m_CBoxRechWindows.SetChecked (false);
} // WindowInit


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn die diese Page deaktiviert werden soll; deshalb wird hier die Gültigkeit
// der Daten dieser Page überprüft (bei Gültigkeit "return FALSE" sonst "return TRUE")
BOOL CTopoRelDlg::OnKillActive (NotifyEvt)
{
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Zurück" gedrückt wurde
// -1: cancel
int CTopoRelDlg::OnWizBack (NotifyEvt)
{
	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Weiter" gedrückt wurde
// Rückgabe von
//    0: für OK
//   -1: für cancel
int CTopoRelDlg::OnWizNext (NotifyEvt)
{
	GetSelection();
	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn Button "Fertig stellen" gedrückt wurde
//    FALSE: für OK
//    TRUE:  für cancel
BOOL CTopoRelDlg::OnWizFinish (NotifyEvt)
{
	GetSelection();
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// Reaktion auf Click
void CTopoRelDlg::ButtonClick (ControlEvt e)
{
	SetComment (e);

	switch ((uint) e.GetControlID())
	{
		case IDC_INTERSECT:
			m_CBoxWithin.SetChecked (true);
			m_CBoxContain.SetChecked (true);
			m_CBoxOverlap.SetChecked (true);
			m_CBoxEnter.SetChecked (true);
			m_CBoxTouch.SetChecked (true);
			m_CBoxEqual.SetChecked (true);
			break;

		case IDC_WITHIN:
		case IDC_CONTAIN:
		case IDC_OVERLAP:
		case IDC_ENTER:
		case IDC_TOUCH:
		case IDC_EQUAL:

			if (m_CBoxWithin.isChecked() && m_CBoxContain.isChecked() &&
				m_CBoxOverlap.isChecked() && m_CBoxEnter.isChecked() &&
				m_CBoxTouch.isChecked() && m_CBoxEqual.isChecked())
				m_CBoxIntersect.SetChecked (true);
			else
				m_CBoxIntersect.SetChecked (false);
	}
} // ButtonClick


// --------------------------------------------------------------------------------------------
// Kommentar anzeigen
void CTopoRelDlg :: SetComment (ControlEvt e)
{
ResourceFile RF (g_pDLLName);

	switch ((uint) e.GetControlID())
	{
		case IDC_INTERSECT:
			if (m_CBoxIntersect.isChecked())
				m_Descript.SetText (ResString (ResID (IDS_COMMINTERSECT, &RF), 250).Addr());
			else
				m_Descript.SetText (ResString (ResID (IDS_COMMDELETE, &RF), 250).Addr());
			break;

		case IDC_WITHIN:
			if (m_CBoxWithin.isChecked())
				m_Descript.SetText (ResString (ResID (IDS_COMMWITHIN, &RF), 250).Addr());
			else
				m_Descript.SetText (ResString (ResID (IDS_COMMDELETE, &RF), 250).Addr());
			break;

		case IDC_CONTAIN:
			if (m_CBoxContain.isChecked())
				m_Descript.SetText (ResString (ResID (IDS_COMMCONTAIN, &RF), 250).Addr());
			else
				m_Descript.SetText (ResString (ResID (IDS_COMMDELETE, &RF), 250).Addr());
			break;

		case IDC_OVERLAP:
			if (m_CBoxOverlap.isChecked())
				m_Descript.SetText (ResString (ResID (IDS_COMMOVERLAP, &RF), 250).Addr());
			else
				m_Descript.SetText (ResString (ResID (IDS_COMMDELETE, &RF), 250).Addr());
			break;

		case IDC_ENTER:
			if (m_CBoxEnter.isChecked())
				m_Descript.SetText (ResString (ResID (IDS_COMMENTER, &RF), 250).Addr());
			else
				m_Descript.SetText (ResString (ResID (IDS_COMMDELETE, &RF), 250).Addr());
			break;

		case IDC_TOUCH:
			if (m_CBoxTouch.isChecked())
				m_Descript.SetText (ResString (ResID (IDS_COMMTOUCH, &RF), 250).Addr());
			else
				m_Descript.SetText (ResString (ResID (IDS_COMMDELETE, &RF), 250).Addr());
			break;

		case IDC_EQUAL:
			if (m_CBoxEqual.isChecked())
				m_Descript.SetText (ResString (ResID (IDS_COMMEQUAL, &RF), 250).Addr());
			else
				m_Descript.SetText (ResString (ResID (IDS_COMMDELETE, &RF), 250).Addr());
			break;

		case IDC_DISJOINT:
			if (m_CBoxDisjoint.isChecked())
				m_Descript.SetText (ResString (ResID (IDS_COMMDISJOINT, &RF), 250).Addr());
			else
				m_Descript.SetText (ResString (ResID (IDS_COMMDELETE, &RF), 250).Addr());
			break;

		case IDC_RECHWINDOWS:
			if (m_CBoxRechWindows.isChecked())
				m_Descript.SetText (ResString (ResID (IDS_COMMSEPARWINDOWS, &RF), 250).Addr());
			else
				m_Descript.SetText (ResString (ResID (IDS_COMMSINGLEWINDOW, &RF), 250).Addr());
	}
} // SetComment


// --------------------------------------------------------------------------------------------
// Die ausgewählten Relationen abfragen und in m_ulSelRelat bzw. m_bSepaWin abspeichern.
void CTopoRelDlg :: GetSelection (void)
{
	m_ulSelRelat = 0x00;		// ausgewählte Relationen ermitteln

	if (m_CBoxIntersect.isChecked())
		m_ulSelRelat |= WITH | CONT | OVER | ENTE | TOUC | EQUA;
	else
	{
		if (m_CBoxWithin.isChecked())
			m_ulSelRelat |= WITH;
		if (m_CBoxContain.isChecked())
			m_ulSelRelat |= CONT;
		if (m_CBoxOverlap.isChecked())
			m_ulSelRelat |= OVER;
		if (m_CBoxEnter.isChecked())
			m_ulSelRelat |= ENTE;
		if (m_CBoxTouch.isChecked())
			m_ulSelRelat |= TOUC;
		if (m_CBoxEqual.isChecked())
			m_ulSelRelat |= EQUA;
	}
	if (m_CBoxDisjoint.isChecked())
		m_ulSelRelat |= DISJ;

	if (m_CBoxRechWindows.isChecked())
		m_bSepaWin = true;
	else
		m_bSepaWin = false;

} // GetSelection


// --------------------------------------------------------------------------------------------
// Initialisierungsdaten für den Dialog aus pSelInfo übernehmen
HRESULT CTopoRelDlg::SetSelectedInfo (TOPORELRESULT* pSelInfo, bool bNoShow)
{
	if (NULL == pSelInfo) return E_POINTER;

	m_ulSelRelat = pSelInfo->ulSelRelat;
	m_bSepaWin = pSelInfo->bSepaWin;

	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Zustand des Dialogs für evtl. Save() zwischenspeichern
HRESULT CTopoRelDlg::GetSelectedInfo (TOPORELRESULT* pSelInfo, bool& bIsDirty)
{
	if (NULL == pSelInfo) return E_POINTER;

	if (pSelInfo->ulSelRelat != (ULONG)m_ulSelRelat ||
		pSelInfo->bSepaWin != m_bSepaWin)
	{
		pSelInfo->ulSelRelat = (ULONG)m_ulSelRelat;
		pSelInfo->bSepaWin = m_bSepaWin;
		bIsDirty = true;	// Änderungen im Dialog
	}
	else
		bIsDirty = false;	// keine Änderungen

	return S_OK;
}
