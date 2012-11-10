// Dialogfenster zur Auswahl mehrer Undo/Redo's -------------------------------
// File: UNDODLG.CXX

#include "triaspre.hxx"

#include "triasres.h"

#if !defined(WIN16)
#include <dirisole.h>
#include "extmain3.hxx"
#endif

#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>		// Enumerator
#include <undoredo.hxx>		// Klassendeklaration
#include <undohelp.hxx>

#include "undodlg.hxx"

#if defined(_DEBUG)
#include "UndoRedoDetails.h"
#endif // _DEBUG

// Funktionen, die Undo/Redo-Dialoge anzeigen ---------------------------------
bool ExtDirisWindow :: ShowUndoList (void)
{
LPENUMUNKNOWN pIUndos;

	if (FAILED(m_pUndoRedo -> GetUndoList (&pIUndos)))
		return false;

CUndoRedoDlg *pDlg = CUndoRedoDlg :: CreateInstance (this, pIUndos, true);
int iCnt = -1;

	if (pDlg != NULL) {
		pDlg -> Show (Centre);

		iCnt = pDlg -> Result();
		if (iCnt >= 0) {
		CEierUhr Wait(this);
		DWORD dwCaps = m_pUndoRedo -> GetNextUndoDesc (NULL);

			m_pUndoRedo -> Undo (iCnt+1);
			if (dwCaps & UNDOREDOCAPS_REPAINT)
				DEX_RePaint();
		}
	}
	DELETE_OBJ (pDlg);
	pIUndos -> Release();

return iCnt >= 0;
}

bool ExtDirisWindow :: ShowRedoList (void)
{
LPENUMUNKNOWN pIRedos;

	if (FAILED(m_pUndoRedo -> GetRedoList (&pIRedos)))
		return false;

CUndoRedoDlg *pDlg = CUndoRedoDlg :: CreateInstance (this, pIRedos, false);
int iCnt = -1;

	if (pDlg != NULL) {
		pDlg -> Show (Centre);
	
		iCnt = pDlg -> Result();
		if (iCnt >= 0) {
		CEierUhr Wait(this);
		DWORD dwCaps = m_pUndoRedo -> GetNextRedoDesc (NULL);
		
			m_pUndoRedo -> Redo (iCnt+1);
			if (dwCaps & UNDOREDOCAPS_REPAINT)
				DEX_RePaint();
		}
	}
	DELETE_OBJ (pDlg);
	pIRedos -> Release();

return iCnt >= 0;
}

// Spezielle ListBox ----------------------------------------------------------
CUndoRedoListBox :: CUndoRedoListBox (DialogWindow *pDlg, ResID uiRes)
		  : ControlWindow (new MultiSelListBox (pDlg, uiRes))
{
}

CUndoRedoListBox :: ~CUndoRedoListBox (void)
{
	if (GetControl()) delete GetControl();
}

void CUndoRedoListBox :: MouseButtonDn (MouseEvt e)
{
	HandleMouseEvt (e);
}

void CUndoRedoListBox :: MouseDrag (MouseEvt e)
{
	HandleMouseEvt (e);
}

void CUndoRedoListBox :: HandleMouseEvt (MouseEvt e)
{
	if (e.isLeftButton()) {
	// Index des getroffenen ListBoxItems berechnen
	int iIndex = CalcIndex (e.Where().Y());

		if (iIndex >= 0) {
		int iCnt = GetLB() -> GetCount();

			GetLB() -> ChangeSelected (Range (0, iIndex), true);
			if (iIndex+1 < iCnt)
				GetLB() -> ChangeSelected (Range (iIndex+1, iCnt-1), false);
			GetLB() -> SetCaretIndex (iIndex);

			GetParent() -> PostEvent (Event(WM_USER+1000, iIndex));
		}
	}
}

int CUndoRedoListBox :: CalcIndex (CoOrd Y)
{
int iItemHeight = ListBox_GetItemHeight (GetHandle(), 0);
int iFirst = ListBox_GetTopIndex (GetHandle());
Rectangle Rc = CanvasRect();			// Größe der ListBox

// in WindowsKoord umrechnen, ListBox hat links-unten ihren (0, 0) - Punkt
int iIndex = int(iFirst + ((Rc.Top()-Y) / iItemHeight));

	if (iIndex >= GetLB() -> GetCount()) 
		return -1;	// Index größer als letzter Eintrag
		
return iIndex;
}

// Konstruktor/Destruktor/Initialisierung -------------------------------------
#pragma warning (disable: 4355)

CUndoRedoDlg :: CUndoRedoDlg (pWindow pW, bool fUndo)
	      : DialogWindow (pW, UNDOREDOLIST),
#if defined(WIN16)
		m_pbHelp (this, IDHELP),
#endif
		m_mslbUndoRedos (this, IDL_UNDOREDOLIST),
		m_strPrefix (ResString (fUndo ? IDS_UNDOCAPTION : IDS_REDOCAPTION, 20).Addr()),
		m_strOneAction (ResString (IDS_ONEACTION, 20).Addr()),
		m_strActions (ResString (IDS_ACTIONS, 20).Addr())
{
	m_fUndo = fUndo ? true : false;
	m_pIUndoRedos = NULL;
	m_iActIndex = -1;

// Controls initialisieren
#if defined(WIN16)
	m_pbHelp.Disable();
#endif // WIN16
}

#pragma warning (default: 4355)

CUndoRedoDlg :: ~CUndoRedoDlg (void)
{
	m_pIUndoRedos -> Release();	// Liste freigeben
}

CUndoRedoDlg *CUndoRedoDlg :: CreateInstance (
		pWindow pW, LPENUMUNKNOWN pIUndoRedos, bool fUndo)
{
CUndoRedoDlg *pDlg = new CUndoRedoDlg (pW, fUndo);

	if (pDlg == NULL || !pDlg -> FInit (pIUndoRedos)) {
		DELETE_OBJ (pDlg);
		return NULL;
	}

return pDlg;
}

bool CUndoRedoDlg :: FInit (LPENUMUNKNOWN pIUndoRedos)
{
// Liste merken
	if (pIUndoRedos == NULL || !m_mslbUndoRedos.isValid()) 
		return false;

	m_pIUndoRedos = pIUndoRedos;
	m_pIUndoRedos -> AddRef();

// ListBox füllen
LPENUMUNKNOWN pEnum;
LPUNDOREDO pIUndo;
LPTSTR pDesc = NULL;
HRESULT hr = m_pIUndoRedos -> QueryInterface (IID_IEnumUnknown, (LPVOID *)&pEnum);

	if (FAILED(hr)) return false;

	pEnum -> Reset();
	while (pEnum -> Next (1, (LPUNKNOWN *)&pIUndo, NULL) == S_OK) {
	DWORD dwCaps = pIUndo -> Capabilities ((signed char **)&pDesc);

		if (m_fUndo && !(dwCaps & UNDOREDOCAPS_CANUNDO))
			break;
		if (!m_fUndo && !(dwCaps & UNDOREDOCAPS_CANREDO))
			break;

	LPTSTR pLongDesc = strtok (pDesc, "|");

		if (pLongDesc == NULL) pLongDesc = pDesc;
		else		       pLongDesc = strtok (NULL, "|");

	// zur Liste hinzufügen
		if (pLongDesc == NULL) pLongDesc = pDesc;

		m_mslbUndoRedos.GetLB() -> AddString (pLongDesc);
	
	// Speicher freigeben
		if (NULL != pDesc) {
			CoTaskMemFree (pDesc);
			pDesc = NULL;
		}
	}

// Speicher freigeben
	pEnum -> Release();
	if (NULL != pDesc) {
		CoTaskMemFree (pDesc);
		pDesc = NULL;
	}

// ListBox initialisieren
	if (m_mslbUndoRedos.GetLB() -> GetCount() > 0) {
		m_mslbUndoRedos.GetLB() -> ChangeSelected (0);
		m_mslbUndoRedos.GetLB() -> SetCaretIndex (0);

	// Caption initialisieren
		AdjustCaption (0);
	} else
		return false;

return true;
}

void CUndoRedoDlg :: ButtonClick (ControlEvt e)
{
	switch (e.GetControlID()) {
	case IDOK:
		EndDlg (m_mslbUndoRedos.GetLB() -> GetCaretIndex());
		break;

	case IDCANCEL:
		EndDlg (-1);
		break;

	case IDHELP:
		break;

#if defined(_DEBUG)
	case IDB_DETAILS:
		{
		CUndoRedoDetails Dlg (this, m_pIUndoRedos, m_fUndo);

			Dlg.Show(Centre);
		}
		break;
#endif // _DEBUG
	}
}

long CUndoRedoDlg :: Dispatch (Event e)
{
	if (e.Msg() == WM_USER+1000) {
		AdjustCaption (e.WParam());	// Caption richten
		return true;
	}

	return DialogWindow :: Dispatch (e);
}


void CUndoRedoDlg :: AdjustCaption (int iIndex)
{
	if (iIndex == m_iActIndex)	// nichts tun, wenn nicht notwendig
		return;

char cbBuffer[_MAX_PATH];
string strCaption = m_strPrefix;

	if (iIndex == 0) {
		strCaption += m_strOneAction;
		SetCaption (strCaption.c_str());
	} else if (iIndex > 0) {
		strCaption += m_strActions;
		wsprintf (cbBuffer, strCaption.c_str(), iIndex+1);
		SetCaption (cbBuffer);
	} else
		SetCaption (strCaption.c_str());

	m_iActIndex = iIndex;
}


