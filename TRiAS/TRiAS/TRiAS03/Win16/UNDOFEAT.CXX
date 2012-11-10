// Undo/Redo für ein Merkmal --------------------------------------------------
// File: UNDOFEAT.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>		// Enumerator
#include <undoredo.hxx>		// Klassendeklaration

#include "undofeat.hxx"

extern char g_pDLLName[260];

bool ReadTextMerkmal (short iTTyp, DWORD lTarget, ULONG lMCode, LPTSTR pText, int iLen);
bool WriteTextMerkmal (short iTTyp, DWORD lTarget, ULONG lMCode, LPCTSTR pText);

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CUndoRedoObjectFeature :: CUndoRedoObjectFeature (LPFNDESTROYED pfnDestroy)
			: m_pfnDestroy(pfnDestroy), m_lONr(-1L), 
			  m_ulMCode(0L), m_iMkBase(10)
{
	m_dwRefCnt = 0L;
}

CUndoRedoObjectFeature :: ~CUndoRedoObjectFeature (void)
{
	// nothing to do
}

bool CUndoRedoObjectFeature :: FInit (LONG lONr, ULONG ulMCode, LPCTSTR pNew, LPCTSTR pOld)
{
// Parameter testen
	if (lONr == -1L || ulMCode == 0L) return false;

// Member initialisieren
	m_lONr = lONr;
	m_ulMCode = ulMCode;
	m_strNew = pNew;
	
	if (pOld == NULL) {
	// altes Merkmal muß gelesen werden
	TCHAR cbBuffer[_MAX_PATH];
	
		if (ReadTextMerkmal (TT_Objekt, m_lONr, m_ulMCode, cbBuffer, _MAX_PATH))
			m_strOld = cbBuffer;	// altes Merkmal existiert
	} else
		m_strOld = pOld;	// altes Merkmal bereits bekannt

	m_iMkBase = DEX_GetMkBase();

	Initialized (true);

return true;
}


// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoObjectFeature :: Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	char cbBuffer[64];

		if (m_strOld.length() == 0) {
		// Merkmal erzeugen
		ResString resCreateF (ResID (IDS_UNDOCREATEFEATURE, &RF), 128);

			*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf (*pDesc, resCreateF.Addr(), 
					  ultoa (m_ulMCode, cbBuffer, m_iMkBase),  
					  m_lONr);
			}
		} else if (m_strNew.length() == 0) {
		// Merkmal löschen
		ResString resDeleteF (ResID (IDS_UNDODELETEFEATURE, &RF), 128);

			*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf (*pDesc, resDeleteF.Addr(), 
					  ultoa (m_ulMCode, cbBuffer, m_iMkBase),  
					  m_lONr);
			}
		} else {
		// Merkmal editieren
		ResString resEditF (ResID (IDS_UNDOEDITFEATURE, &RF), 128);

			*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf (*pDesc, resEditF.Addr(), 
					  ultoa (m_ulMCode, cbBuffer, m_iMkBase),  
					  m_lONr);
			}
		}
	}

return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;
}

STDMETHODIMP CUndoRedoObjectFeature :: Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

LPCTSTR pTmp = m_strOld.length() > 0 ? m_strOld.c_str() : NULL;

	if (WriteTextMerkmal (TT_Objekt, m_lONr, m_ulMCode, pTmp))
		return NOERROR;

return ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoObjectFeature :: Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

LPCTSTR pTmp = m_strNew.length() > 0 ? m_strNew.c_str() : NULL;

	if (WriteTextMerkmal (TT_Objekt, m_lONr, m_ulMCode, pTmp))
		return NOERROR;

return ResultFromScode (S_FALSE);
}

// *** IUndoRedoObjectFeature *** ---------------------------------------------
STDMETHODIMP CUndoRedoObjectFeature :: Init (LONG lONr, ULONG ulMCode, 
			LPCTSTR pNew, LPCTSTR pOld /* = NULL */)
{
return FInit (lONr, ulMCode, pNew, pOld) ? NOERROR : ResultFromScode (S_FALSE);
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoObjectFeature :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoObjectFeature) {
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

STDMETHODIMP_(ULONG) CUndoRedoObjectFeature :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoObjectFeature :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

// Helperfunktionen -----------------------------------------------------------
bool ReadTextMerkmal (short iTTyp, DWORD lTarget, ULONG ulMCode, LPTSTR pText, int iLen)
{
TARGETMERKMAL gm;

	INITSTRUCT (gm, TARGETMERKMAL);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = (LONG)ulMCode;
	gm.imaxLen = pText != NULL ? iLen : 0;
	gm.pMText = pText;
	gm.iTTyp = iTTyp;
	if (DEX_GetTextMerkmal (gm) == NULL)
		return false;

return true;
}

bool WriteTextMerkmal (short iTTyp, DWORD lTarget, ULONG ulMCode, LPCTSTR pText)
{
TARGETMERKMAL gm;

	INITSTRUCT (gm, TARGETMERKMAL);
	gm.lTarget = (LPARAM)lTarget;
	gm.lMCode = (LONG)ulMCode;
	gm.imaxLen = pText != NULL ? strlen (pText) : 0;
	gm.pMText = (LPTSTR)pText;
	gm.iTTyp = iTTyp;
	if (DEX_ModTextMerkmal (gm) != EC_OKAY)
		return false;

return true;
}

