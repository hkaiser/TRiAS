// @doc
// @module MemDiffExt.cpp | Implementation of the <c CMemDiffExtExtension> class

#include "stdafx.h"

#include "Mem/MemDiff.h"

#include "MemDiffExt.h"
#include "MemDiffExtExt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// für XtensionBasisLib benötigte globale Funktionen

// Liefert den CLSID des TRiAS-Zusatzmodules MemDiffExt
BOOL GetExtensionCLSID (CLSID &rClsID)
{
	rClsID = CLSID_MemDiffExt;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMemDiffExtExtension

inline void FreeSnapShot (HANDLE &rhSnapShot)
{
	if (NULL != rhSnapShot) {
		MDFreeSnapshot(rhSnapShot);
		rhSnapShot = NULL;
	}
}

// InitExtension Wird nach erfolgreichem Laden des Zusatzmodules gerufen 
STDMETHODIMP_(BOOL) CMemDiffExtExtension::InitExtension (short iMode)
{
	if (!CTriasExtension::InitExtension (iMode))
		return FALSE;

	m_hSnapShot1 = NULL;
	m_hSnapShot2 = NULL;
	m_fVerbose = true;
	m_pStartMenu = NULL;

	return InstallPopupMenu(IMIStartUpMenu, m_pStartMenu) && InstallPopupMenu(IMINormalMenu, m_pPopupMenu);
}

BOOL CMemDiffExtExtension::InstallPopupMenu(UINT uiWhere, CMenu *& pPopupMenu)
{
// PopupMenu einbauen
	if (NULL == pPopupMenu) {
		ATLTRY(pPopupMenu = new CMenu());
		if (NULL == pPopupMenu || !pPopupMenu -> LoadMenu (IDR_MEMDIFFEXT))
			return FALSE;
	}

INSTALLMENUITEMEX imi;

	INITSTRUCT(imi, INSTALLMENUITEMEX);
	imi.hDex = hDex();
	imi.iMenuID = -1;
	imi.iFlag = uiWhere;
	imi.iMenuNum = PROJECT_MENU_POS;
	imi.iMenuPos = -1;

// PopUpMenu und MenuText holen
char cbBuffer[64];

	imi.hMenu = GetSubMenu (pPopupMenu -> m_hMenu, 0);
	ASSERT(NULL != imi.hMenu);
	GetMenuString (pPopupMenu -> m_hMenu, 0, cbBuffer, sizeof(cbBuffer), MF_BYPOSITION);

	imi.pMenuText = cbBuffer;
	return (NULL != DEX_InstallMenuItem (imi)) ? TRUE : FALSE;
}

// UnLoadExtension wird vor dem entladen des Zusatzmodules gerufen
STDMETHODIMP_(BOOL) CMemDiffExtExtension::UnLoadExtension (void)
{
	FreeSnapShot (m_hSnapShot1);
	FreeSnapShot (m_hSnapShot2);
	RemovePopupMenu (IMIStartUpMenu);
	RemovePopupMenu (IMINormalMenu);

	return CTriasExtension::UnLoadExtension();
}

void CMemDiffExtExtension::RemovePopupMenu(UINT uiWhere)
{
REMOVEMENUITEMEX rmi;

	INITSTRUCT(rmi, REMOVEMENUITEMEX);
	rmi.hDex = hDex();
	rmi.iMenuID = -1;
	rmi.iMenuNum = PROJECT_MENU_POS;
	rmi.iFlag = uiWhere;
	rmi.iMenuPos = -1;
	DEX_RemoveMenuItem (rmi);
}

bool CMemDiffExtExtension::FindMenuItem (CMenu *pMenu, UINT uiID)
{
UINT uiCnt = pMenu -> GetMenuItemCount();

	uiID += MenuOffset();
	for (UINT uiLoop = 0; uiLoop < uiCnt; uiLoop++) {
		if (uiID == pMenu->GetMenuItemID (uiLoop))
			return true;
	}

	return false;		// nichts gefunden
}

STDMETHODIMP_(BOOL) CMemDiffExtExtension::MenuInit (THIS_ HMENU hMenu, LPARAM lParam, HWND hWnd) 
{
CMenu *pMenu = CMenu::FromHandle (hMenu);

	_ASSERTE(NULL != pMenu);
	if (FindMenuItem (pMenu, ID_TAKE_SNAPSHOT_1)) {
	// unser Menu
		pMenu -> EnableMenuItem (ID_TAKE_SNAPSHOT_1+MenuOffset(), MF_ENABLED);
		pMenu -> EnableMenuItem (ID_TAKE_SNAPSHOT_2+MenuOffset(), 
			((NULL != m_hSnapShot1) ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND);
		pMenu -> EnableMenuItem (ID_FREE_SNAPSHOTS+MenuOffset(), 
			((NULL != m_hSnapShot1 || NULL != m_hSnapShot2) ? MF_ENABLED : MF_GRAYED) | MF_BYCOMMAND);
		pMenu -> CheckMenuItem (ID_VERBOSE_SNAPSHOT+MenuOffset(), 
			(m_fVerbose ? MF_CHECKED : MF_UNCHECKED) | MF_BYCOMMAND);
		return TRUE;
	}
	return FALSE;
}

STDMETHODIMP_(BOOL) CMemDiffExtExtension::MenuSelect (THIS_ UINT uiMenuID, HMENU hMenu, HWND hWnd) 
{
	return FALSE;
}

STDMETHODIMP_(BOOL) CMemDiffExtExtension::MenuCommand (THIS_ UINT uiMenuID, HWND hWnd) 
{
	switch (uiMenuID) {
	case ID_TAKE_SNAPSHOT_1:
		FreeSnapShot (m_hSnapShot1);
		m_hSnapShot1 = MDTakeSnapshot (GetCurrentProcess());
		break;

	case ID_TAKE_SNAPSHOT_2:
		FreeSnapShot (m_hSnapShot2);
		m_hSnapShot2 = MDTakeSnapshot (GetCurrentProcess());
		CompareSnapShots();
		m_hSnapShot1 = MDTakeSnapshot (GetCurrentProcess());
		break;

	case ID_FREE_SNAPSHOTS:
		_ASSERTE(NULL != m_hSnapShot1 || NULL != m_hSnapShot2);
		FreeSnapShot (m_hSnapShot1);
		FreeSnapShot (m_hSnapShot2);
		break;

	case ID_VERBOSE_SNAPSHOT:
		m_fVerbose = !m_fVerbose;
		break;
	}
	return FALSE;
}

BOOL CMemDiffExtExtension::OutputLine (LPCSTR pcOutStr, size_t uiLen)
{
	OutputDebugString (pcOutStr);
	return TRUE;
}

void CMemDiffExtExtension::CompareSnapShots ()
{
	MDCompareSnapshot (m_hSnapShot1, m_hSnapShot2, GetOutputProc(), m_fVerbose);
	FreeSnapShot (m_hSnapShot1);
	FreeSnapShot (m_hSnapShot2);
}

