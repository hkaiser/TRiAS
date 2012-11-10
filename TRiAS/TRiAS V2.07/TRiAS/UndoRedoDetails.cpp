// Details für Undo/Redo (Debug only)
// File: UNDOREDODETAILS.CPP

#include "TriasPre.hxx"

#include "triasres.h"

#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>		// Enumerator
#include <undoredo.hxx>		// Klassendeklaration
#include <undohelp.hxx>

#include "UndoRedoDetails.h"

#if !defined(_DEBUG)
#error "This file contains debug only code!"
#endif // _DEBUG

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Position der Bildchen im Bmp-Strip
#define IMG_FOLDER		1
#define IMG_FOLDER_OPEN	2
#define IMG_UNDO		3
#define IMG_REDO		4
#define IMG_UNDO_DISABLED	5
#define IMG_REDO_DISABLED	6

#pragma warning (disable: 4355)

CUndoRedoDetails::CUndoRedoDetails (pWindow pW, IEnumUnknown *pIEnum, bool fUndo)
	: DialogWindow (pW, IDD_UNDOREDODETAILS),
	  m_tvDetails (this, IDC_UNDOREDODETAILS),
	  m_fUndo (fUndo)
{
// ImageList erzeugen und einbauen
	if (!m_ilDetails.CreateList (IDB_UNDOREDO_DETAILS, 16, 0, RGB(255, 0, 255)))
		return;

CImageList *pIL = m_tvDetails.SetImageList (&m_ilDetails, TVSIL_NORMAL);
	
	if (pIL) delete pIL;

// TreeControl füllen
	FillTree (pIEnum);
}

#pragma warning (default: 4355)

bool CUndoRedoDetails::FillTree (IEnumUnknown *pIEnum, HTREEITEM hParent)
{
IUndoRedo *pIUndo;
LPTSTR pDesc = NULL;
UINT uiPos = IMG_FOLDER;

	pIEnum -> Reset();
	while (S_OK == pIEnum -> Next (1, (LPUNKNOWN *)&pIUndo, NULL)) {
	DWORD dwCaps = pIUndo -> Capabilities (&pDesc);

	// BildchenTyp feststellen
		if (m_fUndo) {
			if (dwCaps & UNDOREDOCAPS_CANUNDO)
				uiPos = IMG_UNDO;
			else
				uiPos = IMG_UNDO_DISABLED;
		} else {
			if (dwCaps & UNDOREDOCAPS_CANREDO)
				uiPos = IMG_REDO;
			else
				uiPos = IMG_REDO_DISABLED;
		}

	// BeschreibungText (lang) extrahieren
	LPTSTR pLongDesc = strtok (pDesc, "|");

		if (NULL == pLongDesc) 
			pLongDesc = pDesc;
		else {
			pLongDesc = strtok (NULL, "|");
			if (NULL == pLongDesc) 
				pLongDesc = pDesc;
		}

	// Versuchen weiter zu untergliedern
	IEnumUnknown *pISubEnum = NULL;
	HRESULT hr = pIUndo -> QueryInterface (IID_IEnumUnknown, (LPVOID *)&pISubEnum);

		if (SUCCEEDED(hr)) // läßt sich weiter untergliedern
			uiPos = IMG_FOLDER;

	// zur Liste hinzufügen
	HTREEITEM hItem = m_tvDetails.InsertItem (pLongDesc, uiPos, uiPos, hParent, TVI_LAST);

		if (SUCCEEDED(hr)) {
			FillTree (pISubEnum, hItem);
			pISubEnum -> Release();
		}

		pIUndo -> Release();
		CoTaskMemFree (pDesc);
	}
	return true;
}

CUndoRedoDetails::~CUndoRedoDetails (void)
{
// ImageList wird vom Destruktor ~CImageList freigegeben, hier 
// doppeltes Freigeben verhindern
CImageList *pIL = m_tvDetails.SetImageList (NULL, TVSIL_NORMAL);
	
	if (pIL) delete pIL;
}

///////////////////////////////////////////////////////////////////////////////
// Ein Item wurde Expandiert/Collapst 
void CUndoRedoDetails::OnItemExpanded (NotifyEvt e)
{
NM_TREEVIEW *pnmtv = (NM_TREEVIEW *)e.GetNotifyInfo();
HTREEITEM hItem = pnmtv -> itemNew.hItem;

	AdjustImage (hItem);
}

///////////////////////////////////////////////////////////////////////////////
// Bildchen an Parents richten 
void CUndoRedoDetails::AdjustImage (HTREEITEM hItem)
{
	if (!m_tvDetails.ItemHasChildren (hItem)) 
		return;		// nur Parents behandeln

	if (m_tvDetails.GetItemState (hItem, TVIS_EXPANDED) & TVIS_EXPANDED) 
		m_tvDetails.SetItemImage (hItem, IMG_FOLDER_OPEN, IMG_FOLDER_OPEN);	// ist expandiert
	else
		m_tvDetails.SetItemImage (hItem, IMG_FOLDER, IMG_FOLDER);	// ist collabiert
}

void CUndoRedoDetails::ButtonClick (ControlEvt e)
{
	switch (e.GetControlID()) {
	case IDCANCEL:
		EndDlg (-1);
		break;
	}
}

