// Unser ToolBarManager
// File: ToolBarManager.cpp

#include "fakemfcp.hxx"

#if defined(_USE_SEC_CLASSES)
#include "fakemfc.h"

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Wrapper.h"
#include "mainfrm.h"

#include <secdll.h>

#include "TRiASBarObj.h"
#include "TRiASToolBar.h"
#include "ToolBarManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTRiASToolBarManager, SECToolBarManager)

BEGIN_MESSAGE_MAP(CTRiASToolBarManager, SECToolBarManager)
    //{{AFX_MSG_MAP(CTRiASToolBarManager)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

#define NOELEMENTS(a)	(sizeof(a)/sizeof(a[0]))

///////////////////////////////////////////////////////////////////////////////
// Function to load a bitmap changing it's colors to the current system color
// scheme.
//
BOOL TRiASLoadSysColorBitmap (CBitmap& bmp, LPCTSTR lpszName, HINSTANCE hInst);

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor

CTRiASToolBarManager::CTRiASToolBarManager() 
{
	m_pToolBarClass = RUNTIME_CLASS(CTRiASToolBarObj);
}

CTRiASToolBarManager::CTRiASToolBarManager(CFrameWnd* pFrameWnd) 
	: SECToolBarManager (pFrameWnd)
{
	m_pToolBarClass = RUNTIME_CLASS(CTRiASToolBarObj);	
}

CTRiASToolBarManager::~CTRiASToolBarManager (void) 
{
// ButtonMap freigeben
	if (NULL != m_pBtnMap) {
		delete const_cast<SECBtnMapEntry *>(m_pBtnMap);
		m_pBtnMap = NULL;
	}

// DefaultToolBarButtonTables freigeben
	for(int i = 0; i < m_defaultBars.GetSize(); i++)
	{
	SECDefaultToolBar* pDefault = (SECDefaultToolBar*) m_defaultBars[i];

		DELETE_VEC(pDefault -> lpBtnIDs);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Erzeugen einer neuen Toolbar
HRESULT CTRiASToolBarManager::CreateToolBar (
	UINT uiID, LPCTSTR lpszTitle, ITRiASToolBar **ppITools)
{
	TEST_E_POINTER("CTRiASToolBarManager::CreateToolBar", ppITools);
	ASSERT(m_pToolBarClass != NULL);

CTRiASToolBar* pToolBar = (CTRiASToolBar *)m_pToolBarClass->CreateObject();

	if(NULL == pToolBar) 
		return E_OUTOFMEMORY;

	ASSERT_KINDOF(CTRiASToolBar, pToolBar);

	pToolBar->SetManager(this);

DWORD dwStyle = /*WS_VISIBLE|*/WS_CHILD|CBRS_SIZE_DYNAMIC|CBRS_TOP|CBRS_FLOATING;
DWORD dwExStyle = 0L;

	if(m_bFlyBy)
		dwStyle |= CBRS_FLYBY;
	if(m_bToolTips)
		dwStyle |= CBRS_TOOLTIPS;
	if(m_bCoolLook)
		dwExStyle |= (CBRS_EX_COOLBORDERS|CBRS_EX_GRIPPER);

	pToolBar -> CreateEx (dwExStyle, m_pFrameWnd, dwStyle, uiID, lpszTitle);

	SetToolBarInfo(pToolBar);

	pToolBar->EnableConfigMode(m_bConfig);
	pToolBar->EnableDocking(CBRS_ALIGN_ANY);
	pToolBar->m_bAutoDelete = TRUE;

	*ppITools = pToolBar -> GetToolBarObj();

	((CMainFrame *)m_pFrameWnd) -> ShowControlBar (pToolBar, false, false);
	((CMainFrame *)m_pFrameWnd) -> DockControlBar (pToolBar);

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefern der voreingestellten StyleBits
DWORD CTRiASToolBarManager::GetDefaultBarStyleEx()
{
DWORD dwExStyle = 0L;

/*	if(m_bFlyBy) dwStyle |= CBRS_FLYBY;
	if(m_bToolTips) dwStyle |= CBRS_TOOLTIPS;
*/
	if(m_bCoolLook)
		dwExStyle |= (CBRS_EX_COOLBORDERS|CBRS_EX_GRIPPER);

	return dwExStyle;
}

///////////////////////////////////////////////////////////////////////////////
// do not use the following functions


///////////////////////////////////////////////////////////////////////////////
//
// Handles system color changes, reload all bitmaps
void CTRiASToolBarManager::SysColorChange ()
{
// Need to reload bitmap
	if(!m_bmp.m_hObject)
		return;

	m_bmp.DeleteObject();

// alle Bitmaps durchgehen
int iLast = 0;

	for (CResources::iterator it = m_Rscs.begin(); it != m_Rscs.end(); ++it) 
		AddBitmap ((*it).GetInstanceHandle(), (*it).GetResourceId(), (*it).GetCount(), &iLast);
}

HRESULT CTRiASToolBarManager::AddBitmap (HINSTANCE hInst, UINT uiRsc, int iBttnCnt, int *piOffset)
{
// neue Bitmap laden
CAttachedBitmap bmp;

	if (NULL == hInst) {
	// Bitmap ist bereits geladen und wird übergeben
		ASSERT(NULL != (HBITMAP)uiRsc);
		bmp.Attach ((HBITMAP)uiRsc);
	} else {
		if (!TRiASLoadSysColorBitmap (bmp, MAKEINTRESOURCE(uiRsc), hInst))
			return E_FAIL;	// Resource existiert nicht
	}

// größe der Bitmap rauskriegen und mit den aktuellen Größen vergleichen
BITMAP bm;

	if (!bmp.GetBitmap (&bm)) 
		return E_UNEXPECTED;

int iWidth = bm.bmWidth / iBttnCnt;
int iHeight = bm.bmHeight;

	if (m_bmp.m_hObject) {
		if (iWidth != m_nImgWidth || iHeight != m_nImgHeight) {
		// alle Bmps müssen ein und die selbe Größe besitzen
			ASSERT(iWidth == m_nImgWidth || iHeight == m_nImgHeight);
			return E_INVALIDARG;
		}
	} else {
		m_nImgWidth = iWidth;		// das ist die erste Bitmap
		m_nImgHeight = iHeight;
	}

// jetzt an existierende Bitmap dranhängen
	if (!AppendToExisting (bmp, piOffset))
		return E_FAIL;

// diese Bitmap Resource speichern
	m_Rscs.push_back (CResource(hInst, uiRsc, iBttnCnt));

// Build global array mapping toolbar IDs to bitmap indexes.
UINT *pBmpItems = NULL;

	ATLTRY(pBmpItems = new UINT [m_nBmpItems + iBttnCnt]);
	if (NULL == pBmpItems) return E_OUTOFMEMORY;

// existierende ButtonItems umkopieren
	ZeroMemory (pBmpItems, sizeof(UINT)*(m_nBmpItems + iBttnCnt));
	if (NULL != m_pBmpItems) {
		for (int iCnt = 0; iCnt < m_nBmpItems; iCnt++) 
			pBmpItems[iCnt] = m_pBmpItems[iCnt];
		
		delete [] m_pBmpItems;
	}
	m_pBmpItems = pBmpItems;
	m_nBmpItems += iBttnCnt;

// alle existierenden Toolbars von der neuen Bitmap informieren
POSITION pos = m_pFrameWnd -> m_listControlBars.GetHeadPosition();

	while(pos != NULL) {
	CControlBar* pBar = (CControlBar*)m_pFrameWnd->m_listControlBars.GetNext(pos);

		if(pBar->IsKindOf(RUNTIME_CLASS(SECCustomToolBar)))
			((SECCustomToolBar *)pBar) -> SetBitmap (m_bmp);
	}

	return S_OK;
}

BOOL CTRiASToolBarManager::AppendToExisting (CAttachedBitmap &rBmp, int *piOffset)
{
	if (NULL == piOffset) return FALSE;

// erstmal berechnen, wieviele Bildchen schon da sind
	if (NULL == m_bmp.m_hObject) {
	// die erste Bitmap, also lediglich umhängen
		*piOffset = 0;
		m_bmp.Attach (rBmp.Detach());
		return TRUE;
	}

// ansonsten geht's eben zur Sache
BITMAP bm;

	*piOffset = -1;		// error condition
	VERIFY(m_bmp.GetBitmap (&bm));

int iOffset = (bm.bmWidth / m_nImgWidth);
int iWidth = bm.bmWidth;
int iHeight = bm.bmHeight;

// Parameter der hinzuzufügendenden Bitmap
	VERIFY(rBmp.GetBitmap (&bm));
	ASSERT(iHeight == bm.bmHeight);		// Höhen müssen identisch sein

CBitmap newbmp;
CWindowDC screenDC(NULL);
CDC dcSrc, dcDest;

	if(!newbmp.CreateCompatibleBitmap (&screenDC, iWidth + bm.bmWidth, iHeight) ||
	   !dcSrc.CreateCompatibleDC (NULL) || !dcDest.CreateCompatibleDC (NULL))
	{
		return FALSE;
	}

// jetzt zusammenkopieren
CBitmap *pBmpOldDest = (CBitmap *)dcDest.SelectObject (&newbmp);
CBitmap *pBmpOldSrc = (CBitmap *)dcSrc.SelectObject (&m_bmp);

	dcDest.BitBlt (0, 0, iWidth, iHeight, &dcSrc, 0, 0, SRCCOPY);
	dcSrc.SelectObject (&rBmp);
	dcDest.BitBlt (iWidth, 0, bm.bmWidth, iHeight, &dcSrc, 0, 0, SRCCOPY);

	dcDest.SelectObject (pBmpOldDest);
	dcSrc.SelectObject (pBmpOldSrc);

	m_bmp.DeleteObject();
	m_bmp.Attach (newbmp.Detach());

	if (!rBmp.IsAttached())
		rBmp.DeleteObject();		// der Symmetrie halber

	*piOffset = iOffset;		// first Image of new Bitmap

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Kopieren bzw. vergrößern der Buttonmap
SECBtnMapEntry *CopyButtonMap (const SECBtnMapEntry *pToCopy, int *piSize = NULL, int iAdd = 0)
{
// feststellen, wie groß die Map ist
const SECBtnMapEntry *pCurr = pToCopy;
int iCnt = 1;

	if (NULL != pToCopy) {
		for (iCnt = 1; NULL != pCurr -> m_pBtnClass; iCnt++, pCurr++)
			;	// counting only
	}

SECBtnMapEntry *pNew = NULL;

	ATLTRY(pNew = new SECBtnMapEntry[iCnt + iAdd]);
	if (NULL == pNew) return NULL;

	ZeroMemory (pNew, sizeof(SECBtnMapEntry)*(iCnt+iAdd));

// jetzt umkopieren
	for (int i = 0; i < iCnt-1; i++)
		pNew[i] = pToCopy[i];

	if (NULL != piSize)
		*piSize = iCnt + iAdd;

	return pNew;
}

///////////////////////////////////////////////////////////////////////////////
// Hinzufügen von mehreren Buttons zu einer Toobar
HRESULT CTRiASToolBarManager::AddButtons (
	CTRiASToolBar *pBar, int iBttnCnt, const TBBUTTON *pBttns,
	ITRiASUIOwner *pUIOwner)
{
// neue Buttons den Bitmaps zuordnen
const TBBUTTON *pItem = pBttns;

	for (int i = 0; i < iBttnCnt; i++, pItem++)
	{
		if (!(pItem -> fsStyle & TBSTYLE_SEP) || 0 != pItem -> idCommand) {
			ASSERT(pItem -> iBitmap >= 0 && pItem -> iBitmap < m_nBmpItems);
			m_pBmpItems[pItem -> iBitmap] = pItem -> idCommand;
		} 
	}

// alle Buttons zur ButtonMap hinzufügen
	pItem = pBttns;
	for (int j = 0; j < iBttnCnt; j++, pItem++)
	{
	ADDBUTTON rgAddButton = AddToButtonMap (pItem);

		VERIFY(ADDBUTTON_FAILED != rgAddButton);
		if (pItem -> fsStyle != TBSTYLE_SEP || 0 != pItem -> dwData)
			VERIFY(AddToOwnerList (pItem -> iBitmap, pUIOwner));

	// evtl. als StandardButton hinzufügen
		if (ADDBUTTON_ADDED == rgAddButton && pBar -> IsDefaultBar()) 
			VERIFY(AddToDefaultButtonList (pBar, pItem, 1));
	}

// alle existierenden Toolbars von den neuen Buttons informieren
POSITION pos = m_pFrameWnd->m_listControlBars.GetHeadPosition();

	while(pos != NULL) {
	CControlBar* pNextBar = (CControlBar*)m_pFrameWnd -> m_listControlBars.GetNext (pos);

		if(pNextBar -> IsKindOf(RUNTIME_CLASS(SECCustomToolBar))) 
			SetToolBarInfo ((SECCustomToolBar *)pNextBar);
	}

// jetzt toolbarbezogene ButtonListe erzeugen und einstellen
UINT *pIds = NULL;
HRESULT hr = GetButtonIds (pBttns, iBttnCnt, &pIds);

	if (FAILED(hr)) return hr;

	ASSERT(NULL != pIds);

	if (0 == pBar -> GetBtnCount()) {
	// erste Buttons für diese Toolbar
		VERIFY(pBar -> SetButtons (pIds, iBttnCnt));
	} else {
	// einzeln hinten dran hängen
		for (int i = 0; i < iBttnCnt; i++) {
		bool fIsSeparator = ((ID_SEPARATOR == pIds[i]) && (0 == pBttns -> dwData)) ? true : false;

			pBar -> AddButton (pBar -> GetBtnCount(), pIds[i], fIsSeparator);
		}
	}
	delete [] pIds;

	pBar -> PropagateMode();
	return S_OK;
}

HRESULT CTRiASToolBarManager::GetButtonIds (const TBBUTTON *pBttns, int iBttnCnt, UINT **ppIds)
{
	if (NULL == ppIds) return E_POINTER;

UINT *pIds = NULL;
const TBBUTTON *pItem = pBttns;

	ATLTRY(pIds = new UINT[iBttnCnt]);
	if (NULL == pIds) return E_OUTOFMEMORY;

	ZeroMemory (pIds, sizeof(UINT) * iBttnCnt);
	for (int iId = 0; iId < iBttnCnt; iId++, pItem++) 
	// nur zeitweilig ...
		pIds[iId] = ((pItem -> fsStyle & TBSTYLE_SEP) && (0 == pItem -> dwData)) ? ID_SEPARATOR : pItem -> idCommand;

	*ppIds = pIds;
	return S_OK;
}

// Set/Get the current button map.
void CTRiASToolBarManager::SetButtonMap (const SECBtnMapEntry *pMap)
{
	ASSERT(pMap != NULL);

SECBtnMapEntry *pBtnMap = CopyButtonMap (m_pBtnMap);

	if (NULL != pBtnMap) {
		if (NULL != m_pBtnMap) 
			delete [] const_cast<SECBtnMapEntry *>(m_pBtnMap);
		m_pBtnMap = pBtnMap;
	}
}

BOOL CTRiASToolBarManager::AddToOwnerList (int iIndex, ITRiASUIOwner *pUIOwner)
{
	try {
		ASSERT(0 <= iIndex && iIndex < m_nBmpItems);

	UINT uiCmd = m_pBmpItems[iIndex];
	CBttnOwners::iterator it = m_Owner.find (uiCmd);

		if (it != m_Owner.end())	// evtl. derzeit enthaltenen Button freigeben
			m_Owner.erase (it);
		m_Owner.insert (uiCmd, WTRiASUIOwner(pUIOwner));

	} catch (...) {
		ASSERT(FALSE);
		return FALSE;
	}
	return TRUE;
}

BOOL CTRiASToolBarManager::RemoveFromOwnerList (int iIndex)
{
	try {
		ASSERT(0 <= iIndex && iIndex < m_nBmpItems);

	UINT uiCmd = m_pBmpItems[iIndex];
	CBttnOwners::iterator it = m_Owner.find (uiCmd);

		if (it == m_Owner.end()) 	
			return FALSE;
		m_Owner.erase (it);		// freigeben

	} catch (...) {
		ASSERT(FALSE);
		return FALSE;
	}
	return TRUE;
}

CTRiASToolBarManager::ADDBUTTON CTRiASToolBarManager::AddToButtonMap (const TBBUTTON *pBttn)
{
// erstmal nachsehen, ob dieser Button schon existiert
SECBtnMapEntry *pCurr = const_cast<SECBtnMapEntry *>(m_pBtnMap);

	if (NULL != pCurr) {
		for (; NULL != pCurr -> m_pBtnClass; pCurr++)
		{
			if (pCurr -> m_nID == pBttn -> idCommand) {
			// Eintrag aktualisieren
				if (0 == pBttn -> dwData) {
					pCurr -> m_pBtnClass = BUTTON_CLASS(SECStdBtn);
				// TBSTATE_ENABLED == TBBS_DISABLED so invert it
					pCurr -> m_nStyle = MAKELONG(pBttn -> fsStyle, pBttn -> fsState ^ TBSTATE_ENABLED); 
				} else 
					*pCurr = *(const SECBtnMapEntry *)(pBttn -> dwData);

				return ADDBUTTON_REPLACED;
			}
		}
	}

// ButtonMap um einen vergrößern (wie uneffektiv !)
int iSize = 0;
SECBtnMapEntry *pBtnMap = CopyButtonMap (m_pBtnMap, &iSize, 1);

	ASSERT(iSize >= 2);
	if (NULL == pBtnMap) 
		return ADDBUTTON_FAILED;

// neuen Eintrag hinzufügen
	if (0 == pBttn -> dwData) {
		pBtnMap[iSize - 2].m_pBtnClass = BUTTON_CLASS(SECStdBtn);
		pBtnMap[iSize - 2].m_nID = pBttn -> idCommand;

	// TBSTATE_ENABLED == TBBS_DISABLED so invert it
		pBtnMap[iSize - 2].m_nStyle = MAKELONG(pBttn -> fsStyle, pBttn -> fsState ^ TBSTATE_ENABLED); 
	} else
		pBtnMap[iSize - 2] = *(const SECBtnMapEntry *)(pBttn -> dwData);

	if (NULL != m_pBtnMap)
		delete [] const_cast<SECBtnMapEntry *>(m_pBtnMap);
	m_pBtnMap = pBtnMap;
	return ADDBUTTON_ADDED;
}

CTRiASToolBarManager::ADDBUTTON CTRiASToolBarManager::AddToButtonMap (
	const SECBtnMapEntry *pBttn, int iCnt)
{
	ASSERT(NULL != pBttn);

// erstmal nachsehen, ob dieser Button schon existiert
SECBtnMapEntry *pCurr = const_cast<SECBtnMapEntry *>(m_pBtnMap);

	if (NULL != pCurr) {
		for (; NULL != pCurr -> m_pBtnClass; pCurr++)
		{
			if (pCurr -> m_nID == pBttn -> m_nID) {
			// Eintrag aktualisieren
				*pCurr = *pBttn;
				return ADDBUTTON_REPLACED;
			}
		}
	}

// ButtonMap vergrößern (wie uneffektiv !)
int iSize = 0;
SECBtnMapEntry *pBtnMap = CopyButtonMap (m_pBtnMap, &iSize, iCnt);

	ASSERT(iSize >= iCnt);
	if (NULL == pBtnMap) 
		return ADDBUTTON_FAILED;

// neue Einträge hinzufügen
int j = 0;

	for (int i = iSize - iCnt; i < iSize; i++, j++)
		pBtnMap[i] = pBttn[j];

	if (NULL != m_pBtnMap)
		delete [] const_cast<SECBtnMapEntry *>(m_pBtnMap);
	m_pBtnMap = pBtnMap;
	return ADDBUTTON_ADDED;
}

BOOL CTRiASToolBarManager::RemoveFromButtonMap (const TBBUTTON *pBttn)
{
// erstmal nachsehen, ob dieser Button schon existiert
SECBtnMapEntry *pCurr = const_cast<SECBtnMapEntry *>(m_pBtnMap);

	ASSERT(NULL != pCurr);
	if (NULL == pCurr) return FALSE;

int iIndex = 0;
int iCnt = 1;

	for (; NULL != pCurr -> m_pBtnClass; iCnt++, pCurr++)
		;	// counting only
	ASSERT(iCnt > 0);		// wenigstens einer muß da sein

	pCurr = const_cast<SECBtnMapEntry *>(m_pBtnMap);
	for (; NULL != pCurr -> m_pBtnClass; pCurr++, iIndex++)
	{
		if (pCurr -> m_nID == pBttn -> idCommand) 
			break;		// found
	}

	ASSERT(NULL != pCurr -> m_pBtnClass);
	if (NULL == pCurr -> m_pBtnClass)
		return FALSE;

// Eintrag herausnehmen
	TX_ASSERT(iIndex < iCnt);
	
// einen mehr kopieren
	CopyMemory (&pCurr[0], &pCurr[1], sizeof(SECBtnMapEntry)*(iCnt-iIndex));
	return TRUE;
}

// Buttons in Liste der DefaultButtons für eine ToolBar einhängen
BOOL CTRiASToolBarManager::AddToDefaultButtonList (
		CTRiASToolBar *pBar, const TBBUTTON *pBttns, int iCnt, int iIndex)
{
UINT nID = 0;

	if (FAILED(pBar -> GetBarID (&nID)))
		return FALSE;

// Find this Bar as default bar
SECDefaultToolBar *pThisBar = NULL;

	for(int i = 0; i < m_defaultBars.GetSize(); i++)
	{
	SECDefaultToolBar *pDefault = (SECDefaultToolBar *)m_defaultBars[i];

		if(pDefault -> nID == nID) {
			pThisBar = pDefault;
			break;		// found
		}
	}
	if (NULL == pThisBar) return TRUE;		// not a default bar

// jetzt neue Buttons in Liste einfügen
UINT *pIds = NULL;

	ATLTRY(pIds = new UINT [pThisBar -> nBtnCount + iCnt]);
	if (NULL == pIds) return FALSE;

// alle bis zur Einfügestelle kopieren
int iBefore = (iIndex != -1) ? iIndex : pThisBar -> nBtnCount;

	iBefore = min((UINT)iBefore, pThisBar -> nBtnCount);
	CopyMemory (pIds, pThisBar -> lpBtnIDs, iBefore*sizeof(UINT));

// alle neuen reinkopieren
const TBBUTTON *pItem = pBttns;

	for (int j = 0; j < iCnt; j++, pItem++)
		pIds[j + iBefore] = pItem -> idCommand;

// alle restlichen dranhängen
	CopyMemory (&pIds[iBefore+iCnt], &pThisBar -> lpBtnIDs[iBefore], sizeof(UINT)*(pThisBar -> nBtnCount - iBefore));

	pThisBar -> nBtnCount += iCnt;
	if (NULL != pThisBar -> lpBtnIDs)
		delete [] pThisBar -> lpBtnIDs;
	pThisBar -> lpBtnIDs = pIds;
	return TRUE;
}

// Buttons in Liste der DefaultButtons für eine ToolBar einhängen
BOOL CTRiASToolBarManager::RemoveFromDefaultButtonList (
		CTRiASToolBar *pBar, int iIndex, const TBBUTTON *pTB)
{
UINT nID = 0;

	if (FAILED(pBar -> GetBarID (&nID)))
		return FALSE;

// Find this Bar as default bar
SECDefaultToolBar *pThisBar = NULL;

	for(int i = 0; i < m_defaultBars.GetSize(); i++)
	{
	SECDefaultToolBar *pDefault = (SECDefaultToolBar *)m_defaultBars[i];

		if(pDefault -> nID == nID) {
			pThisBar = pDefault;
			break;		// found
		}
	}
	if (NULL == pThisBar) return TRUE;		// not a default bar

// jetzt Button aus der Liste herausnehmen
int iToDel = (iIndex != -1) ? iIndex : pThisBar -> nBtnCount-1;

	ASSERT(0 < pThisBar -> nBtnCount);
	ASSERT(pThisBar -> lpBtnIDs[iToDel] == pTB -> idCommand);

	if (pThisBar -> lpBtnIDs[iToDel] != pTB -> idCommand) {
	// wieder finden des Buttons
	int iFound = -1;

		for (int i = 0; i < pThisBar -> nBtnCount; i++) {
			if (pThisBar -> lpBtnIDs[i] == pTB -> idCommand) {
				iFound = i;
				break;
			}
		}
		ASSERT(-1 != iFound);		// jetzt aber

		iToDel = iFound;		// diesen löschen
	}

	if (0 <= iToDel && iToDel < pThisBar -> nBtnCount-1)	// nur, wenns nicht der letzte ist
		CopyMemory (&pThisBar -> lpBtnIDs[iToDel], &pThisBar -> lpBtnIDs[iToDel+1], (pThisBar -> nBtnCount-iToDel-1)*sizeof(UINT));
	pThisBar -> nBtnCount--;
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// einen Button hinzufügen/aktualisieren
HRESULT CTRiASToolBarManager::InsertButton (
	CTRiASToolBar *pBar, int iIndex, const TBBUTTON *pBttn,
	ITRiASUIOwner *pUIOwner)
{
// neuen Button eintragen 
	if (!(pBttn -> fsStyle & TBSTYLE_SEP) || 0 != pBttn -> idCommand) {
		ASSERT(pBttn -> iBitmap >= 0 && pBttn -> iBitmap < m_nBmpItems);
		m_pBmpItems[pBttn -> iBitmap] = pBttn -> idCommand;
	} 

// neuen Button zur ButtonMap hinzufügen/aktualisieren
ADDBUTTON rgAddButton = AddToButtonMap (pBttn);

	VERIFY(ADDBUTTON_FAILED != rgAddButton);
	if (pBttn -> fsStyle != TBSTYLE_SEP)
		VERIFY(AddToOwnerList (pBttn -> iBitmap, pUIOwner));

// evtl. als StandardButton hinzufügen
	if (ADDBUTTON_ADDED == rgAddButton && pBar -> IsDefaultBar()) 
		VERIFY(AddToDefaultButtonList (pBar, pBttn, 1, iIndex));

// alle existierenden Toolbars von den neuen Buttons informieren
POSITION pos = m_pFrameWnd->m_listControlBars.GetHeadPosition();

	while(pos != NULL) {
	CControlBar* pNextBar = (CControlBar*)m_pFrameWnd -> m_listControlBars.GetNext (pos);

		if(pNextBar -> IsKindOf(RUNTIME_CLASS(SECCustomToolBar))) 
			SetToolBarInfo ((SECCustomToolBar *)pNextBar);
	}

// jetzt toolbarbezogene ButtonListe erzeugen und einstellen
UINT *pIds = NULL;
HRESULT hr = GetButtonIds (pBttn, 1, &pIds);

	if (FAILED(hr)) return hr;

	ASSERT(NULL != pIds);

	if (0 == pBar -> GetBtnCount()) {
	// erste Buttons für diese Toolbar
		VERIFY(pBar -> SetButtons (pIds, 1));
	} else {
	// einzeln hinten dran hängen
	bool fIsSeparator = ((ID_SEPARATOR == pIds[0]) && (0 == pBttn -> dwData)) ? true : false;

		pBar -> AddButton (iIndex, pIds[0], fIsSeparator);
	}
	delete [] pIds;

	pBar -> PropagateMode();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// einen Button aus der Toolbar herauslösen
HRESULT CTRiASToolBarManager::DeleteButton (CTRiASToolBar *pBar, int iIndex)
{
// Button überall herausnehmen
TBBUTTON tb;
HRESULT hr = pBar -> GetButtonEx (iIndex, &tb, NULL);

	VERIFY(RemoveFromDefaultButtonList (pBar, iIndex, &tb));
	if (tb.fsStyle != TBSTYLE_SEP)
		VERIFY(RemoveFromOwnerList (tb.iBitmap));
	VERIFY(RemoveFromButtonMap (&tb));

// Eintrag in BitmapTable ungültig machen
	m_pBmpItems[tb.iBitmap] = -1;
	return pBar -> RemoveButton (iIndex) ? S_OK : E_FAIL;
}

HRESULT CTRiASToolBarManager::ResetToolBar (CTRiASToolBar *pBar)
{
UINT nID = 0L;
HRESULT hr = pBar -> GetBarID (&nID);

	if (FAILED(hr)) return hr;

int nBtnCount;
UINT *pBtnIDs;
		
	if (GetDefaultBtns (nID, nBtnCount, pBtnIDs)) {
		((SECCustomToolBar *)pBar) -> SetButtons (pBtnIDs, nBtnCount);
		pBar -> GetParentFrame() -> RecalcLayout(TRUE);
		pBar -> Invalidate();
		return S_OK;
	}

	return S_FALSE;		// not found
}

HRESULT CTRiASToolBarManager::GetUIOwner (
	CTRiASToolBar *pBar, int iIndex, ITRiASUIOwner **ppIOwner)
{
	TEST_E_POINTER("CTRiASToolBarManager::GetUIOwner", ppIOwner);

	if (iIndex < 0 || iIndex >= m_nBmpItems)
		return E_INVALIDARG;

	try {
	WTRiASUIOwner UIOwner;
	UINT uiCmd = m_pBmpItems[iIndex];
	CBttnOwners::iterator it = m_Owner.find (uiCmd);

		if (it != m_Owner.end())
			UIOwner = (*it).second;
		
		if (NULL != (IUnknown *)UIOwner)
			*ppIOwner = UIOwner.detach();
		else {
			*ppIOwner = NULL;
			return S_FALSE;
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

BOOL CTRiASToolBarManager::HasBmpIndex(UINT nID)
{
// Converts a command ID to a toolbar bitmap index.
	for(UINT j = 0; j < m_nBmpItems; j++)
	{
		if(m_pBmpItems[j] == nID)
			return true;
	}
	return false;
}

HRESULT CTRiASToolBarManager::GetButton (
	const CTRiASToolBar *pBar, int iIndex, TBBUTTON *pBttn)
{
	ZeroMemory (pBttn, sizeof(TBBUTTON));

UINT uiStyle = pBar -> SECCustomToolBar::GetButtonStyle (iIndex);

	pBttn -> fsStyle = LOBYTE(LOWORD(uiStyle));
	pBttn -> fsState = LOBYTE(HIWORD(uiStyle)) ^ TBSTATE_ENABLED;

	if (!(TBSTYLE_SEP & pBttn -> fsStyle)) {
		pBttn -> idCommand = pBar -> GetItemID (iIndex);
		if (HasBmpIndex (pBttn -> idCommand)) 
			pBttn -> iBitmap = const_cast<CTRiASToolBar *>(pBar) -> SECCustomToolBar::IDToBmpIndex (pBttn -> idCommand);
	} 

// hier evtl. noch die dwData (pIUIOwner) besorgen ...
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Default Toolbar definieren

void CTRiASToolBarManager::DefineDefaultToolBar (
	UINT nID, LPCTSTR lpszTitle, const TBBUTTON *pBttns, UINT nBtnCount, 
	DWORD dwAlignment, UINT nDockBarID, UINT nDockNextToID,
	BOOL bDocked, BOOL bVisible)
{
UINT *pIds = NULL;

	if (SUCCEEDED(GetButtonIds (pBttns, nBtnCount, &pIds))) 
	{
		SECToolBarManager::DefineDefaultToolBar (
			nID, lpszTitle, nBtnCount, pIds, dwAlignment, 
			nDockBarID, nDockNextToID, bDocked, bVisible);
	}
//	DELETE_VEC(pIds);		DefaultToolBarButtonTable ist eigentlich const
}

///////////////////////////////////////////////////////////////////////////////
// TRiASLoadSysColorBitmap
//
// Function to load a bitmap changing it's colors to the current system color
// scheme.
//
BOOL TRiASLoadSysColorBitmap (CBitmap& bmp, LPCTSTR lpszName, HINSTANCE hInst)
{
	// Table used to map default system colors onto the system color identifiers.
	static const DWORD sysColorMap[][2] =
	//	      b     g     r
	{{ RGB(0x00, 0x00, 0x00), COLOR_BTNTEXT },
	 { RGB(0x80, 0x80, 0x80), COLOR_BTNSHADOW },
	 { RGB(0xc0, 0xc0, 0xc0), COLOR_BTNFACE },
	 { RGB(0xff, 0xff, 0xff), COLOR_BTNHIGHLIGHT }};

	// Loads the bitmap changing the color table for the current color scheme
	ASSERT(bmp.m_hObject == NULL);

	if (NULL == hInst) {
		hInst = 
#if defined(WIN32) || defined(_AFXDLL)
		AfxFindResourceHandle(lpszName, RT_BITMAP);
#else
		AfxGetResourceHandle();
#endif // WIN32
	}

	HRSRC hRsrc = ::FindResource(hInst, lpszName, RT_BITMAP);
	if(hRsrc == NULL)
		return FALSE;

	HGLOBAL hGlb = ::LoadResource(hInst, hRsrc);
	if(hGlb == NULL)
		return FALSE;

	LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)::LockResource(hGlb);
	if(lpBitmap == NULL)
	{
		::FreeResource(hGlb);
		return FALSE;
	}

	// Take a copy of the BITMAPINFOHEADER structure
	int nColorTableSize = 1 << lpBitmap->biBitCount;
	UINT nSize = (UINT)(lpBitmap->biSize + nColorTableSize * sizeof(RGBQUAD));
	LPBITMAPINFOHEADER lpBitmapInfo = (LPBITMAPINFOHEADER) new char[nSize];
	if(lpBitmapInfo == NULL)
	{
		::FreeResource(hGlb);
		return FALSE;
	}

	memcpy(lpBitmapInfo, lpBitmap, nSize);

	// Modifiy the color table for the current system colors.
	DWORD* pColorTable = (DWORD*)(((LPBYTE)lpBitmapInfo) + (UINT)lpBitmapInfo->biSize);
	for(int i=0; i < nColorTableSize; i++)
	{
		for(int j=0; j<NOELEMENTS(sysColorMap); j++)
		{
			if(pColorTable[i] == sysColorMap[j][0])
			{
				COLORREF newColor = ::GetSysColor((int)sysColorMap[j][1]);
				pColorTable[i] = RGB(GetBValue(newColor),
									 GetGValue(newColor),
									 GetRValue(newColor));
				break;
			}
		}
	}

	int nWidth  = (int)lpBitmapInfo->biWidth;		// Width of bitmap
	int nHeight = (int)lpBitmapInfo->biHeight;		// Height of bitmap

	// Create a new a bitmap and copy the bitmap over with the new color table.
	CWindowDC screenDC(NULL);
	CDC dc;
	if(!bmp.CreateCompatibleBitmap(&screenDC, nWidth, nHeight) ||
	   !dc.CreateCompatibleDC(NULL))
	{
		::FreeResource(hGlb);
		delete (char*)lpBitmapInfo;
		return FALSE;
	}
	
	CBitmap* pBmpOld = (CBitmap*)dc.SelectObject(&bmp);

	LPBYTE lpBits = LPBYTE(lpBitmap+1);
	lpBits += (1 << (lpBitmapInfo->biBitCount)) * sizeof(RGBQUAD);

	StretchDIBits(dc.m_hDC, 0, 0, nWidth, nHeight, 0, 0, nWidth, nHeight, 
				  lpBits, (LPBITMAPINFO)lpBitmapInfo, DIB_RGB_COLORS, SRCCOPY);

	dc.SelectObject(pBmpOld);

	::FreeResource(hGlb);
	delete (char*)lpBitmapInfo;

	return TRUE;
}

#endif // _USE_SEC_CLASSES
