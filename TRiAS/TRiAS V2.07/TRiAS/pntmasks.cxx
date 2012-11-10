// s/w Punktmasken für neue PunktSymbole --------------------------------------
// File: PNTMASKS.CXX

#include "triaspre.hxx"

#include "clbmpobj.hxx"
#include "triasres.h"

extern HINSTANCE hInstance;

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CBitmapBar :: CBitmapBar (void)
{
	m_hMask1 = NULL;
	m_hMask2 = NULL;
	m_iHeight = 0;
	m_iWidth = 0;
	m_pOffsets = NULL;
}

CBitmapBar :: ~CBitmapBar (void)
{
	if (m_hMask1) DeleteObject (m_hMask1);
	if (m_hMask2) DeleteObject (m_hMask2);
	DELETE (m_pOffsets);
}

CBitmapBar *CBitmapBar :: CreateInstance (ResID uiBmpRes, ResID uiBmpOffset)
{
Bitmap BM (uiBmpRes);
CBitmapBar *pMasks = new CBitmapBar();

	if (pMasks == NULL || !pMasks -> FInit (BM, uiBmpOffset)) {
		DELETE (pMasks);
		return NULL;
	}

return pMasks;
}

bool CBitmapBar :: FInit (Bitmap &rB, ResID uiBmpOffset)
{
// OffsetTabelle anlegen
	m_pOffsets = CBmpOffsets :: CreateInstance (uiBmpOffset);
	if (m_pOffsets == NULL) return false;

// MaskenBitmaps aus geladener farbige Bitmap generieren
Dimension dimB = rB.GetSize();

	m_iHeight = dimB.Height();
	m_iWidth = dimB.Width();

	m_hMask1 = CreateBitmap (dimB.Width(), dimB.Height(), 1, 1, NULL);
	m_hMask2 = CreateBitmap (dimB.Width(), dimB.Height(), 1, 1, NULL);
	if (NULL == m_hMask1 || NULL == m_hMask2) 
		return false;

HWND hWnd = GetDesktopWindow();
HDC hDC = GetDC (hWnd);
HDC hDCPts = CreateCompatibleDC (hDC);
HBITMAP hOldBM = (HBITMAP)SelectObject (hDCPts, rB.Handle (API_BITMAP_HBITMAP));	/*BM2S*/

// Weiße Maske erzeugen
// DefaultBkColor ist weiß, also brauchen wir nichts einzustellen
HDC hDCMask = CreateCompatibleDC (hDC);
HBITMAP hOldMask = (HBITMAP)SelectObject (hDCMask, m_hMask1);

	BitBlt (hDCMask, 0, 0, m_iWidth, m_iHeight, hDCPts, 0, 0, NOTSRCCOPY);

// Schwarze Maske erzeugen
DWORD oldBkColorSym = SetBkColor (hDCPts, RGB(0x00, 0x00, 0x00));

	SelectObject (hDCMask, m_hMask2);
	BitBlt (hDCMask, 0, 0, m_iWidth, m_iHeight, hDCPts, 0, 0, NOTSRCCOPY);

// aufräumen
	SelectObject (hDCMask, hOldMask);
	DeleteDC (hDCMask);

	SelectObject (hDCPts, hOldBM);
	SetBkColor (hDCPts, oldBkColorSym);
	DeleteDC (hDCPts);

	ReleaseDC (hWnd, hDC);

return true;
}

// OffsetTabelle für eine BitmapBar -------------------------------------------
CBmpOffsets :: CBmpOffsets (void)
{
	m_pOffsets = NULL;
	m_uiCnt = 0;
}

CBmpOffsets :: ~CBmpOffsets (void)
{
	DELETE (m_pOffsets);
}

CBmpOffsets *CBmpOffsets :: CreateInstance (ResID resTab)
{
CBmpOffsets *pOff = new CBmpOffsets();

	if (pOff == NULL || !pOff -> FInit (resTab)) {
		DELETE (pOff);
		return NULL;
	}

return pOff;
}

bool CBmpOffsets :: FInit (ResID uiTab)
{
DWORD dwSize = 0;

	m_pOffsets = (BMPOFFSET *)ReadResource (hInstance, WORD(uiTab), dwSize);
	if (m_pOffsets == NULL || dwSize == 0) return false;

	m_uiCnt = int(dwSize / sizeof(BMPOFFSET));

return true;
}

// ZugriffsFunktionen ---------------------------------------------------------
CoOrd CBmpOffsets :: FXOffset (unsigned int uiIndex)
{
	if (uiIndex < m_uiCnt && uiIndex >= 0)
		return CoOrd (m_pOffsets[uiIndex].m_cX);

return CoOrd (m_pOffsets[0].m_cX);
}

CoOrd CBmpOffsets :: FYOffset (unsigned int uiIndex)
{
	if (uiIndex < m_uiCnt && uiIndex >= 0)
		return CoOrd (m_pOffsets[uiIndex].m_cY);

return CoOrd (m_pOffsets[0].m_cY);
}

// Zuordnung von BitmapBarIndex zu PunktID und vice versa ---------------------
CMapPunktID :: CMapPunktID (void)
{
	m_pTable = NULL;
	m_iCnt = 0;
	m_pMap = NULL;
}

CMapPunktID :: ~CMapPunktID (void)
{
	DELETE (m_pTable);
	DELETE (m_pMap);
}

CMapPunktID *CMapPunktID :: CreateInstance (ResID uiPktIDs)
{
CMapPunktID *pMap = new CMapPunktID();

	if (pMap == NULL || !pMap -> FInit (uiPktIDs)) {
		DELETE (pMap);
		return NULL;
	}

return pMap;
}

bool CMapPunktID :: FInit (ResID uiPktIDs)
{
DWORD dwSize = 0L;

	m_pTable = (WORD *)ReadResource (hInstance, WORD(uiPktIDs), dwSize);
	if (m_pTable == NULL || dwSize == 0L) return false;
	m_iCnt = (int)(dwSize / sizeof(WORD));

	m_pMap = CIndexMap :: CreateInstance (m_pTable, m_iCnt);
	if (m_pMap == NULL) return false;

return true;
}

int CMapPunktID :: FGetIndex (WORD wPunktID)
{
CIndexPair *pIP = m_pMap -> FFindItem (wPunktID);

	if (pIP) return pIP -> FIndex();

return 0;
}

WORD CMapPunktID :: FGetPunktID (int iIndex)
{
	if (iIndex >= 0 && iIndex < m_iCnt) 
		return (WORD)m_pTable[iIndex];

return m_pTable[0];
}

CIndexPair :: CIndexPair (WORD wPunktID, int iIndex)
	    : m_wPunktID (wPunktID), m_iIndex (iIndex)
{
	// nothing else to do
}

void *GetPunktID (void *pObj)
{
	return & ((CIndexPair *)pObj) -> FPunktID();
}

int PunkIDCmp (void *pObj1, void *pObj2)
{
WORD wObj1 = ((CIndexPair *)pObj1) -> FPunktID();
WORD wObj2 = ((CIndexPair *)pObj2) -> FPunktID();

	if (wObj1 > wObj2) return 1;
	if (wObj1 < wObj2) return -1;
	return 0;
}

CIndexMap :: CIndexMap (void)
	   : CTree (GetPunktID, PunkIDCmp)
{
	// nothing else to do
}

CIndexMap :: ~CIndexMap (void)
{
	EveryDelete();
}

void CIndexMap :: UserDelete (void *pObj)
{
	((CIndexPair *)pObj) -> ~CIndexPair();
}

CIndexMap *CIndexMap :: CreateInstance (WORD *pTable, int iCnt)
{
CIndexMap *pIM = new CIndexMap();

	if (pIM == NULL || !pIM -> FInit (pTable, iCnt)) {
		DELETE (pIM);
		return NULL;
	}

return pIM;
}

bool CIndexMap :: FInit (WORD *pTable, int iCnt)
{
	for (int i = 0; i < iCnt; i++) {
		if (!FAddItem ((WORD)pTable[i], i))
			return false;
	}
	Optimize();

return true;
}

bool CIndexMap :: FAddItem (WORD wPunktID, int iIndex)
{
CIndexPairCreator IMCr (*this);

	return ContCreate (IMCr, CIndexPair)(wPunktID, iIndex) != NULL;
}

CIndexPair *CIndexMap :: FFindItem (WORD wPunktID)
{
CTable t(*this);

	if (t.Find (&wPunktID)) {
	CIndexPairLock l(t);

		if (l) return (CIndexPair *)l;
	}

return NULL;
}

