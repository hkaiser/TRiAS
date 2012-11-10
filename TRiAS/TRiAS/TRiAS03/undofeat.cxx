// Undo/Redo für ein Merkmal --------------------------------------------------
// File: UNDOFEAT.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>		// Enumerator
#include <undoredo.hxx>		// Klassendeklaration

#include "Strings.h"
#include "undofeat.hxx"

extern char g_pDLLName[_MAX_PATH];

BOOL ReadTextMerkmal (short iTTyp, DWORD lTarget, ULONG lMCode, LPTSTR pText, int iLen);
BOOL WriteTextMerkmal (short iTTyp, DWORD lTarget, ULONG lMCode, LPCTSTR pText);

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CUndoRedoObjectFeature::CUndoRedoObjectFeature (LPFNDESTROYED pfnDestroy)
			: m_pfnDestroy(pfnDestroy), m_lONr(-1L), 
			  m_ulMCode(0L), m_iMkBase(10)
{
	m_dwRefCnt = 0L;
}

CUndoRedoObjectFeature::~CUndoRedoObjectFeature (void)
{
	// nothing to do
}

BOOL CUndoRedoObjectFeature::FInit (HOBJECT lONr, HFEATURE ulMCode, LPCTSTR pNew, LPCTSTR pOld)
{
// Parameter testen
	if (lONr == -1L || ulMCode == 0L) return false;

// Member initialisieren
	m_lONr = lONr;
	m_ulMCode = ulMCode;
	m_strNew = (NULL != pNew) ? pNew : g_cbNil;
	
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
STDMETHODIMP_(DWORD) CUndoRedoObjectFeature::Capabilities (signed char **pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	char cbBuffer[64];

		if (m_strOld.size() == 0) {
		// Merkmal erzeugen
		ResString resCreateF (ResID (IDS_UNDOCREATEFEATURE, &RF), 128);

			*pDesc = (signed char *)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf ((char *)*pDesc, resCreateF.Addr(), 
					  ultoa (m_ulMCode, cbBuffer, m_iMkBase),  
					  m_lONr);
			}
		} 
		else if (m_strNew.size() == 0) {
		// Merkmal löschen
		ResString resDeleteF (ResID (IDS_UNDODELETEFEATURE, &RF), 128);

			*pDesc = (signed char *)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf ((char *)*pDesc, resDeleteF.Addr(), 
					  ultoa (m_ulMCode, cbBuffer, m_iMkBase),  
					  m_lONr);
			}
		} else {
		// Merkmal editieren
		ResString resEditF (ResID (IDS_UNDOEDITFEATURE, &RF), 128);

			*pDesc = (signed char *)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf ((char *)*pDesc, resEditF.Addr(), 
					  ultoa (m_ulMCode, cbBuffer, m_iMkBase),  
					  m_lONr);
			}
		}
	}
	return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;
}

STDMETHODIMP CUndoRedoObjectFeature::Undo (void)
{
	if (!isInitialized()) return S_FALSE;

LPCTSTR pTmp = m_strOld.size() > 0 ? m_strOld.c_str() : NULL;

	if (WriteTextMerkmal (TT_Objekt, m_lONr, m_ulMCode, pTmp))
		return S_OK;

	return S_FALSE;
}

STDMETHODIMP CUndoRedoObjectFeature::Redo (void)
{
	if (!isInitialized()) return S_FALSE;

LPCTSTR pTmp = m_strNew.size() > 0 ? m_strNew.c_str() : NULL;

	if (WriteTextMerkmal (TT_Objekt, m_lONr, m_ulMCode, pTmp))
		return S_OK;

	return S_FALSE;
}

// *** IUndoRedoObjectFeature *** ---------------------------------------------
STDMETHODIMP CUndoRedoObjectFeature::Init (HOBJECT lONr, HFEATURE ulMCode, 
			LPCTSTR pNew, LPCTSTR pOld /* = NULL */)
{
	return FInit (lONr, ulMCode, pNew, pOld) ? S_OK : S_FALSE;
}

// *** IPropagateObjectNumber
STDMETHODIMP CUndoRedoObjectFeature::GetUndoObjectNumber (INT_PTR *plONr)
{
	if (NULL == plONr)
		return E_POINTER;
	*plONr = 0L;
	return E_NOTIMPL;		// hier nicht implementiert
}

STDMETHODIMP CUndoRedoObjectFeature::SetUndoObjectNumber (INT_PTR lONr)
{
	m_lONr = lONr;		// Objektnummer des neu erzeugten Objektes
	return S_OK;
}

STDMETHODIMP CUndoRedoObjectFeature::GetRedoObjectNumber (INT_PTR *plONr)
{
	if (NULL == plONr)
		return E_POINTER;
	*plONr = 0L;
	return E_NOTIMPL;		// hier nicht implementiert
}

STDMETHODIMP CUndoRedoObjectFeature::SetRedoObjectNumber (INT_PTR lONr)
{
	m_lONr = lONr;		// Objektnummer des neu erzeugten Objektes
	return S_OK;
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoObjectFeature::QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || 
		riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoObjectFeature)
	{
	// Someone is asking us for our controlling IUnknown.
	// CUndoRedo is that IUnknown, so "this" is the answer.
		*ppvObj = static_cast<IUndoRedoObjectFeature *>(this);
	} 
	else if (riid == IID_IPropagateObjectNumber) {
		*ppvObj = static_cast<IPropagateObjectNumber *>(this);
	}
	else {
	// They must have asked for another interface -- something
	// we don't support.  Report the error.
		*ppvObj = NULL;
		return E_NOINTERFACE;
	}

// If execution reached this point then no error occurred.
	LPUNKNOWN(*ppvObj) -> AddRef();
	return S_OK;
}

STDMETHODIMP_(ULONG) CUndoRedoObjectFeature::AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoObjectFeature::Release (void)
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
BOOL ReadTextMerkmal (short iTTyp, DWORD lTarget, ULONG ulMCode, LPTSTR pText, int iLen)
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

BOOL WriteTextMerkmal (short iTTyp, DWORD lTarget, ULONG ulMCode, LPCTSTR pText)
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

