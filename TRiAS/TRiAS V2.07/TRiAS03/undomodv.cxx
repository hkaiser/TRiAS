// Undo/Redo für VisInfo modifizieren -----------------------------------------
// File: UNDOMODV.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>
#include <undoredo.hxx>		// Klassendeklaration
#include <strdup.hxx>
#include <visinfo.hxx>

#include "undomodv.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

///////////////////////////////////////////////////////////////////////////////
// Handling der HANDLEVISINFO-Struktur

// nicht geänderte VisInfos aus alter VisInfo in neue übernehmen --------------
void FillNewVI (VisType rgVTyp, short fFlags, VISINFO *pDest, const VISINFO *pcSrc)
{
	if (!(fFlags & DO_StyleChanged))
		pDest -> m_Style = pcSrc -> m_Style;
	if (!(fFlags & DO_PriorityChanged))
		pDest -> m_Priority = pcSrc -> m_Priority;
	if (!(fFlags & DO_PrimColorChanged))
		pDest -> m_C = pcSrc -> m_C;
	if (!(fFlags & DO_NameChanged))
		strncpy (pDest -> m_VisName, pcSrc -> m_VisName, VISNAMESIZE);

	switch (rgVTyp) {
	case VT_Punkt: 
		{
			if (!(fFlags & DO_SizeChanged))
				((PVISINFO *)pDest) -> m_Size = ((PVISINFO *)pcSrc) -> m_Size;
			if (!(fFlags & DO_SecColorChanged))
				((PVISINFO *)pDest) -> m_SecC = ((PVISINFO *)pcSrc) -> m_SecC;
			if (!(fFlags & DO_OthersChanged))
				((PVISINFO *)pDest) -> m_iRot = ((PVISINFO *)pcSrc) -> m_iRot;
		}
		break;
				
	case VT_Linie:
		{
			if (!(fFlags & DO_SizeChanged))
				((LVISINFO *)pDest) -> m_Width = ((LVISINFO *)pcSrc) -> m_Width;
		}
		break;
				
	case VT_Flaeche: 
		{
			if (!(fFlags & DO_SecColorChanged))
				((FVISINFO *)pDest) -> m_FC = ((FVISINFO *)pcSrc) -> m_FC;
			if (!(fFlags & DO_SizeChanged))
				((FVISINFO *)pDest) -> m_iWidth = ((FVISINFO *)pcSrc) -> m_iWidth;
			if (!(fFlags & DO_StyleChanged))
				((FVISINFO *)pDest) -> m_iAttrEx = ((FVISINFO *)pcSrc) -> m_iAttrEx;
		}
		break;
				
	case VT_Text: 
		{
			if (!(fFlags & DO_StyleChanged))
				((TVISINFO *)pDest) -> m_Type = ((TVISINFO *)pcSrc) -> m_Type;
			if (!(fFlags & DO_SizeChanged))
				((TVISINFO *)pDest) -> m_Size = ((TVISINFO *)pcSrc) -> m_Size;
			if (!(fFlags & DO_OthersChanged)) {
				((TVISINFO *)pDest) -> m_Rot = ((TVISINFO *)pcSrc) -> m_Rot;
				((TVISINFO *)pDest) -> m_Orient = ((TVISINFO *)pcSrc) -> m_Orient;
			}
		}
		break;
				
	case VT_Default:
		((DVISINFO *)pDest) -> m_iDefTypes = ((DVISINFO *)pcSrc) -> m_iDefTypes;
		break;

	default:
		break;
	}
}

VISINFO *ctVISINFO (VisType iVTyp, VISINFO *pVITarget)
{
VISINFO *pVI = NULL;

	switch (iVTyp) {
	case VT_Punkt:
		pVI = (VISINFO *)new PVISINFO;
		memset (pVI, '\0', sizeof(PVISINFO));
		break;
		
	case VT_Linie:
		pVI = (VISINFO *)new LVISINFO;
		memset (pVI, '\0', sizeof(LVISINFO));
		break;
		
	case VT_Flaeche:
		pVI = (VISINFO *)new FVISINFO;
		memset (pVI, '\0', sizeof(FVISINFO));
		break;
		
	case VT_Text:
		pVI = (VISINFO *)new TVISINFO;
		memset (pVI, '\0', sizeof(TVISINFO));
		break;
		
	case VT_Default:
		pVI = new VISINFO;
		memset (pVI, '\0', sizeof(VISINFO));
		break;
	}
	if (pVI) 
		FillNewVI (iVTyp, 0, pVI, pVITarget);

return pVI;	
}

BOOL CopyHVI (HANDLEVISINFO *pDest, const HANDLEVISINFO *pcSrc)
{
	TX_ASSERT(NULL != pDest);
	TX_ASSERT(NULL != pcSrc);

	pDest -> m_lONr = pcSrc -> m_lONr;
	pDest -> m_lIdent = pcSrc -> m_lIdent;
	pDest -> m_fFlags = pcSrc -> m_fFlags;
	pDest -> m_iVTyp = pcSrc -> m_iVTyp;
	pDest -> m_pDesc = StrDupF (pcSrc -> m_pDesc);
	pDest -> m_pView = StrDupF (pcSrc -> m_pView);
	pDest -> m_pVI = ctVISINFO (VisType(pcSrc -> m_iVTyp), pcSrc -> m_pVI);
	pDest -> m_hWnd = pcSrc -> m_hWnd;

return true;
}

void FreeHVI (HANDLEVISINFO *pHVI)
{
	DELETE_OBJ(pHVI -> m_pDesc);
	DELETE_OBJ(pHVI -> m_pView);
	DELETE_OBJ(pHVI -> m_pVI);
}

///////////////////////////////////////////////////////////////////////////////
// Konstruktor/Destruktor/Initialisieriung ------------------------------------
CUndoRedoVisInfo :: CUndoRedoVisInfo (LPFNDESTROYED pfnDestroy)
		       : m_pfnDestroy (pfnDestroy)
{
	INITSTRUCT (m_viOld, HANDLEVISINFO);
	INITSTRUCT (m_viNew, HANDLEVISINFO);
	m_dwRefCnt = 0L;
}

CUndoRedoVisInfo :: ~CUndoRedoVisInfo (void)
{
	FreeHVI (&m_viOld);
	FreeHVI (&m_viNew);
}

BOOL CUndoRedoVisInfo :: FInit (
	const HANDLEVISINFO *pviNew, const HANDLEVISINFO *pviOld)
{
// alte VisInfo hier zwischenspeichern
	if (NULL == pviOld) {
		if (!CopyHVI (&m_viOld, pviNew) || !DEX_GetIdentVisInfo(m_viOld))
			return false;
	} else {
		if (!CopyHVI (&m_viOld, pviOld))
			return false;
	}

// neue VisInfo hier kopieren
	if (!CopyHVI (&m_viNew, pviNew))
		return false;	

// neue VisInfo anhand der Flags vervollständigen
	TX_ASSERT(m_viNew.m_iVTyp == m_viOld.m_iVTyp);

	FillNewVI (VisType(m_viNew.m_iVTyp), m_viNew.m_fFlags, m_viNew.m_pVI, m_viOld.m_pVI);

// alles ok, raus hier
	Initialized();

return true;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoVisInfo :: Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	ResString resUndo (ResID (IDS_UNDOVISINFO, &RF), 128);

		*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
		if (*pDesc) {
		char cbBuffer[32];

			ultoa (m_viOld.m_lIdent, cbBuffer, DEX_GetIdBase());
			wsprintf (*pDesc, resUndo.Addr(), cbBuffer);
		}
	}

return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO|UNDOREDOCAPS_REPAINT;
}

STDMETHODIMP CUndoRedoVisInfo :: Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// VisInfo wiederherstellen
	if (DEX_ModIdentVisInfo(m_viOld)) 
		return NOERROR;

return ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoVisInfo :: Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

// VisInfo wieder neu machen
	if (DEX_ModIdentVisInfo(m_viNew)) 
		return NOERROR;

return ResultFromScode (S_FALSE);
}

// *** IUndoRedoDeleteText *** ------------------------------------------------
STDMETHODIMP CUndoRedoVisInfo :: Init (const HANDLEVISINFO *pviNew, const HANDLEVISINFO *pviOld)
{
	return FInit (pviNew, pviOld) ? NOERROR : ResultFromScode (S_FALSE);
}


// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoVisInfo :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoVisInfo) {
	// Someone is asking us for our controlling IUnknown.
	// CUndoRedo is that IUnknown, so "this" is the answer.
		*ppvObj = this;
	} else {
	// They must have asked for another interface -- something
	// we don't support.  Report the error.
		*ppvObj = NULL;
		return ResultFromScode (E_NOINTERFACE);
	}

// If execution reached this point then no error occurred.
	LPUNKNOWN(*ppvObj) -> AddRef();

return NOERROR;
}

STDMETHODIMP_(ULONG) CUndoRedoVisInfo :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoVisInfo :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

