// Copyright© 1999-2002 Geopunkt GmbH & Co. KG, NL Potsdam, All rights reserved
// Created: 27.01.2003
//
// @doc    Dialog zu PropertyAction für topologische Relationen von GeoObjekten
//         Zusatzbedingungen bei mehreren Bezugsobjekten
// @module TopoRelRefDlg.cpp | Implementation of the <c CTopoRelRefDlg> class

#include "TopoRelP.hxx"

#include "TopoRelR.h"
#include "TopoRelRefDlg.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif




///////////////////////////////////////////////////////////////////////////////////////////////
// MultiReferenceDialog CTopoRelRefDlg

CTopoRelRefDlg* CTopoRelRefDlg::CreateInstance (LPCSTR pcCaption)
{
CTopoRelRefDlg* pMultiRefDlg = NULL;

	COM_TRY
	{
	// Dialog erzeugen
	ResourceFile RF (g_pDLLName);

		pMultiRefDlg = new CTopoRelRefDlg (ResID(CTopoRelRefDlg::IDD, &RF), pcCaption);
		if (NULL == pMultiRefDlg || !pMultiRefDlg -> FInit())
		{
			DELETE_OBJ(pMultiRefDlg);
			return NULL;
		}

	}
	COM_CATCH_OP_RETURN(delete pMultiRefDlg, NULL);

	return pMultiRefDlg; 
}


// --------------------------------------------------------------------------------------------
CTopoRelRefDlg::CTopoRelRefDlg(ResID uiDlg, LPCSTR pcCaption)
			  : CPropertyPage(uiDlg, pcCaption),
			    m_RBttnAllRefs (this, IDR_ALLREFOBJECTS),
				m_RBttnSomeRefs (this, IDR_SOMEREFOBJECTS),
				m_RefTypeList (this, IDC_REFTYPELIST),
				m_SpinCount(this, IDC_LIMITCOUNT, IDC_SPINREF, Range(1, UD_MAXVAL)),
				m_Descript (this, IDT_REFDESCRIPT)
{
	m_dwFlags = 0;
	m_iReferenceType = Least;
	m_iRefListIndex = 0;
	m_lLimitCnt = 1;
}


// --------------------------------------------------------------------------------------------
CTopoRelRefDlg::~CTopoRelRefDlg()
{
}


// --------------------------------------------------------------------------------------------
// Die Haupt-Button "Zurück", "Weiter" bzw. "Fertig stellen" und "Abbrechen" de/aktivieren
void CTopoRelRefDlg::AdjustSheetButtons()
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
BOOL CTopoRelRefDlg::GetDisableNextPage()
{
	// TODO: return TRUE, if 'Next >' - button should be disabled

	return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////////
// CTopoRelRefDlg message handlers

// wird gerufen, wenn diese Page aktiviert werden soll (i. a. dann, wenn in der vorangehenden
// Page der Button "Weiter" bzw. in der nachfolgenden Page der Button "Zurück" gedrückt wurde)
BOOL CTopoRelRefDlg::OnSetActive (NotifyEvt e) 
{
	AdjustSheetButtons();
	return FALSE;		// bei Gültigkeit "FALSE" sonst "TRUE" (???)
}


///////////////////////////////////////////////////////////////////////////////////////////////
// EventHandler 
// Call-Back-Funktion für die Initialisierung der Controls
void CTopoRelRefDlg::WindowInit (Event)
{
ResourceFile RF (g_pDLLName);

    // explizite Initialisierung der Controls
    m_RBttnAllRefs.FInit();
	m_RBttnSomeRefs.FInit();
	m_RefTypeList.FInit();
	m_SpinCount.FInit();
	m_Descript.FInit();

	// Controls setzen
	FillComboBox();

	switch (m_iReferenceType)
	{
		case All:
			m_RBttnAllRefs.SetState (true);
			m_SpinCount.Disable();
			m_Descript.SetText (ResString (ResID (IDS_COMMALL, &RF), 250).Addr());
			break;

		case Least:
			m_RBttnSomeRefs.SetState (true);
			m_SpinCount.Enable();
			m_Descript.SetText (ResString (ResID (IDS_COMMLEAST, &RF), 250).Addr());
			break;

		case Most:
			m_RBttnSomeRefs.SetState (true);
			m_SpinCount.Enable();
			m_Descript.SetText (ResString (ResID (IDS_COMMMOST, &RF), 250).Addr());
			break;

		case Exact:
			m_RBttnSomeRefs.SetState (true);
			m_SpinCount.Enable();
			m_Descript.SetText (ResString (ResID (IDS_COMMEXACT, &RF), 250).Addr());
	}

	m_RefTypeList.ChangeCurrentIndex (m_iRefListIndex);
	m_RefTypeList.SetFocus();
	m_SpinCount.SetValue(m_lLimitCnt);

} // WindowInit


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn die diese Page deaktiviert werden soll; deshalb wird hier die Gültigkeit
// der Daten dieser Page überprüft (bei Gültigkeit "return FALSE" sonst "return TRUE")
BOOL CTopoRelRefDlg::OnKillActive (NotifyEvt)
{
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Zurück" gedrückt wurde
// -1: cancel
int CTopoRelRefDlg::OnWizBack (NotifyEvt)
{
	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn der Button "Weiter" gedrückt wurde
// Rückgabe von
//    0: für OK
//   -1: für cancel
int CTopoRelRefDlg::OnWizNext (NotifyEvt)
{
	GetSelection();
	return 0;
}


// --------------------------------------------------------------------------------------------
// wird gerufen, wenn Button "Fertig stellen" gedrückt wurde
//    FALSE: für OK
//    TRUE:  für cancel
BOOL CTopoRelRefDlg::OnWizFinish (NotifyEvt)
{
	GetSelection();
	return FALSE;
}


// --------------------------------------------------------------------------------------------
// Reaktion bei Click auf einen Button
void CTopoRelRefDlg::ButtonClick (ControlEvt e)
{
ResourceFile RF (g_pDLLName);

	switch ((uint) e.GetControlID())
	{
		case IDR_ALLREFOBJECTS:
			// nachfolgende if-Anweisung ist erforderlich, weil irgendwoher ein unerklärlicher
			// ButtoClick auf den m_RBttnAllRefs-Button kommt (#WM030131)
			if (m_RBttnAllRefs.GetState())
			{
				m_SpinCount.Disable();
				m_Descript.SetText (ResString (ResID (IDS_COMMALL, &RF), 250).Addr());
			}
			break;

		case IDR_SOMEREFOBJECTS:
			m_SpinCount.Enable();
			m_RefTypeList.SetFocus();
			m_Descript.SetText (ResString (ResID (IDS_COMMSOME, &RF), 250).Addr());
	}
} // ButtonClick


// --------------------------------------------------------------------------------------------
// Reaktion bei Click in die ComboBox
void CTopoRelRefDlg :: ListBoxSel (ControlEvt)
{
	m_RBttnAllRefs.SetState (false);
	m_RBttnSomeRefs.SetState (true);
	m_SpinCount.Enable();

ResourceFile RF (g_pDLLName);

	switch (m_RefTypeList.GetCurrentIndex())
	{
		case 0:
			m_Descript.SetText (ResString (ResID (IDS_COMMLEAST, &RF), 250).Addr());
			break;

		case 1:
			m_Descript.SetText (ResString (ResID (IDS_COMMMOST, &RF), 250).Addr());
			break;

		case 2:
			m_Descript.SetText (ResString (ResID (IDS_COMMEXACT, &RF), 250).Addr());
	}
}


// --------------------------------------------------------------------------------------------
// Editierfeld erhält den Focus
void CTopoRelRefDlg :: EditFocusChg (EditFocusChgEvt e)
{
	if (!e.gotFocus())
		return;		// Focus wurde entfernt

	if (IDC_LIMITCOUNT == (uint) e.GetControlID())
	{
	ResourceFile RF (g_pDLLName);

		m_Descript.SetText (ResString (ResID (IDS_COMMLIMITCOUNT, &RF), 250).Addr());
	}
} // EditFocusChg


// --------------------------------------------------------------------------------------------
// Die Einstellungen abfragen und in m_iReferenceType bzw. m_lLimitCnt abspeichern.
void CTopoRelRefDlg :: GetSelection (void)
{
	m_iRefListIndex = m_RefTypeList.GetCurrentIndex();

	if (m_RBttnAllRefs.GetState())
		m_iReferenceType = All;

	else if (m_RBttnSomeRefs.GetState())
		switch (m_iRefListIndex)
		{
			case 0:
				m_iReferenceType = Least;
				break;

			case 1:
				m_iReferenceType = Most;
				break;

			case 2:
				m_iReferenceType = Exact;
		}

	m_lLimitCnt = m_SpinCount.GetValue();

} // GetSelection


// --------------------------------------------------------------------------------------------
// ComboBox füllen
void CTopoRelRefDlg :: FillComboBox (void)
{
ResourceFile RF (g_pDLLName);

ResString resNewItem (ResID(IDS_ATLEAST, &RF), 20);

	m_RefTypeList.AddString (resNewItem, 0);
	resNewItem = ResString (ResID(IDS_ATMOST, &RF), 20);
	m_RefTypeList.AddString (resNewItem, 1);
	resNewItem = ResString (ResID(IDS_EXACTLY, &RF), 204);
	m_RefTypeList.AddString (resNewItem, 2);
}


// --------------------------------------------------------------------------------------------
// Initialisierungsdaten für den Dialog aus pSelInfo übernehmen
HRESULT CTopoRelRefDlg::SetSelectedInfo (MULTIREFRESULT* pSelInfo, bool bNoShow)
{
	if (NULL == pSelInfo) return E_POINTER;

	m_iReferenceType = pSelInfo->iReferenceType;
	m_iRefListIndex = pSelInfo->iRefListIndex;
	m_lLimitCnt = pSelInfo->lLimitCnt;

	return S_OK;
}


// --------------------------------------------------------------------------------------------
// Zustand des Dialogs für evtl. Save() zwischenspeichern
HRESULT CTopoRelRefDlg::GetSelectedInfo (MULTIREFRESULT* pSelInfo, bool& bIsDirty)
{
	if (NULL == pSelInfo) return E_POINTER;

	if (pSelInfo->iReferenceType != m_iReferenceType ||
		pSelInfo->iRefListIndex != m_iRefListIndex ||
		pSelInfo->lLimitCnt != m_lLimitCnt)
	{
		pSelInfo->iReferenceType = m_iReferenceType;
		pSelInfo->iRefListIndex = m_iRefListIndex;
		pSelInfo->lLimitCnt = m_lLimitCnt;
		bIsDirty = true;	// Änderungen im Dialog
	}
	else
		bIsDirty = false;	// keine Änderungen

	return S_OK;
}
