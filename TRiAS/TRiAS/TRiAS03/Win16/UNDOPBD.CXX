// Undo/Redo für einen PBD-Eintrag --------------------------------------------
// File: UNDOPBD.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>
#include <errinst.hxx>
#include <xtensnn.h>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>		// Enumerator
#include <undoredo.hxx>		// Klassendeklaration

#include "undopbd.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[260];

// Konstruktor/Destruktor/Initialisierung -------------------------------------
CUndoRedoPBDData :: CUndoRedoPBDData (LPFNDESTROYED pfnDestroy)
		  : m_pfnDestroy(pfnDestroy), 
		    m_rgType(PBDDATATYPE_UNKNOWN), m_ulTarget(0L)
{
	m_dwRefCnt = 0L;
	m_pNewPBDData = NULL;
	m_pOldPBDData = NULL;

	m_rgBase = 10;
	m_ecIgnoreCode = WC_NOIDENT;
}

CUndoRedoPBDData :: ~CUndoRedoPBDData (void)
{
	__dtPBDDATA (m_pNewPBDData);
	__dtPBDDATA (m_pOldPBDData);
}

bool CUndoRedoPBDData :: FInitModify (const PBDDATA *pNewData, const PBDDATA *pOldData)
{
// für alle Fälle freigeben
	__dtPBDDATA (m_pNewPBDData);
	__dtPBDDATA (m_pOldPBDData);
	Initialized (false);

// neu initialisieren
	m_rgType = GetPBDType (pNewData -> pbdTyp);
	m_ulTarget = pNewData -> pbdCode;
	m_rgBase = GetPBDBase (m_rgType);
	m_ecIgnoreCode = GetPBDIgnoreCode (m_rgType);

	m_pNewPBDData = CopyPBDData (m_rgType, pNewData);
	if (NULL == m_pNewPBDData) return false;	// muß da sein

	if (NULL != pOldData) {
	// auf jeden Fall modifiziert
		m_pOldPBDData = CopyPBDData (m_rgType, pOldData);
		if (NULL == m_pOldPBDData)
			return false;				// Initialisierungfehler
	} else {
	// entweder erzeugt oder modifiziert
		m_pOldPBDData = ReadPBDData (m_rgType, pNewData -> pbdCode);
	}

// fertig initialisiert
	Initialized (true);

return true;
}

bool CUndoRedoPBDData :: FInitDelete (PBDDATATYPE rgType, ULONG ulTarget)
{
// für alle Fälle freigeben
	__dtPBDDATA (m_pNewPBDData);
	__dtPBDDATA (m_pOldPBDData);
	Initialized (false);

// neu initialisieren
	m_pOldPBDData = ReadPBDData (rgType, ulTarget);
	if (NULL == m_pOldPBDData) return false;	// alter Eintrag muß existieren

	m_rgType = rgType;
	m_ulTarget = ulTarget;
	m_rgBase = GetPBDBase (rgType);
	m_ecIgnoreCode = GetPBDIgnoreCode (rgType);

// fertig initialisiert
	Initialized (true);

return true;
}

inline char *CopyString (LPCSTR pStr, int iLen)
{
	if (NULL == pStr) return NULL;

char *pNew = new char[iLen+1];

	if (NULL != pNew) {
		strncpy (pNew, pStr, iLen);
		pNew[iLen] = '\0';
	}

return pNew;
}

PBDDATA *CUndoRedoPBDData :: CopyPBDData (PBDDATATYPE rgType, const PBDDATA *pData)
{
	if (NULL == pData) return NULL;

PBDDATA *pPBDData = __ctPBDDATA (rgType, pData -> pbdCode, false);

	if (NULL == pPBDData) return NULL;

	switch (rgType) {
	case PBDDATATYPE_IDENT:
		pPBDData -> pbdTemp = pData -> pbdTemp;
		break;

	case PBDDATATYPE_FEATURE:
		if (sizeof(PBDMERKMAL) == pData -> dwSize) {
			((PBDMERKMAL *)pPBDData) -> ipbdMTyp = ((PBDMERKMAL *)pData) -> ipbdMTyp;
			((PBDMERKMAL *)pPBDData) -> ipbdMLen = ((PBDMERKMAL *)pData) -> ipbdMLen;
		} else
			pPBDData -> dwSize = sizeof(PBDDATA);
		break;

	case PBDDATATYPE_RELATION:
		if (sizeof(PBDRELATION) == pData -> dwSize) 
			((PBDRELATION *)pPBDData) -> ipbdRTyp = ((PBDRELATION *)pData) -> ipbdRTyp;
		else
			pPBDData -> dwSize = sizeof(PBDDATA);
		break;

	default:
		__dtPBDDATA(pPBDData);
		return NULL;
	}

	pPBDData -> pbdKText = CopyString (pData -> pbdKText, pData -> pbdKTextLen);
	pPBDData -> pbdLText = CopyString (pData -> pbdLText, pData -> pbdLTextLen);
	pPBDData -> pbdKTextLen = (NULL != pPBDData -> pbdKText) ? pData -> pbdKTextLen : 0;
	pPBDData -> pbdLTextLen = (NULL != pPBDData -> pbdLText) ? pData -> pbdLTextLen : 0;

return pPBDData;
}

// Funktionen für das Lesen und Löschen eines PBD-Eintrages -------------------
PBDDATA *CUndoRedoPBDData :: ReadPBDData (PBDDATATYPE rgType, ULONG ulTarget)
{
PBDDATA *pPBDData = __ctPBDDATA (rgType, ulTarget);

	if (NULL == pPBDData || (EC_OKAY != DEX_GetPBDData (*pPBDData))) {
		__dtPBDDATA (pPBDData);
		return NULL;
	}

return pPBDData;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoPBDData :: Capabilities (LPTSTR *pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	char cbBuffer[64];

		if (NULL == m_pOldPBDData) {
		// PBD-Eintrag erzeugt
		ResString resCreateF (ResID (IDS_UNDOCREATEPBDDATA+m_rgType, &RF), 128);

			*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf (*pDesc, resCreateF.Addr(), 
					  ultoa (m_ulTarget, cbBuffer, m_rgBase));
			}
		} else if (NULL == m_pNewPBDData) {
		// PBD-Eintrag gelöscht
		ResString resDeleteF (ResID (IDS_UNDODELETEPBDDATA+m_rgType, &RF), 128);

			*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf (*pDesc, resDeleteF.Addr(), 
					  ultoa (m_ulTarget, cbBuffer, m_rgBase));  
			}
		} else {
		// PBD-Einrag modifiziert
		ResString resEditF (ResID (IDS_UNDOEDITPBDDATA+m_rgType, &RF), 128);

			*pDesc = (LPTSTR)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf (*pDesc, resEditF.Addr(), 
					  ultoa (m_ulTarget, cbBuffer, m_rgBase));
			}
		}
	}

return UNDOREDOCAPS_CANUNDO|UNDOREDOCAPS_CANREDO;
}

STDMETHODIMP CUndoRedoPBDData :: Undo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

ErrInstall EI (m_ecIgnoreCode);

	if (NULL == m_pOldPBDData) {
	// neu erzeugten Eintrag wieder löschen
		TX_ASSERT(NULL != m_pNewPBDData);

		if (EC_OKAY == DEX_DelPBDData (*m_pNewPBDData)) {
			DEXN_PBDMCodeChanged (m_pNewPBDData -> pbdCode);
			return NOERROR;
		}
	} else if (EC_OKAY == DEX_ModPBDData (*m_pOldPBDData)) {
	// gelöschten Eintrag wieder erzeugen oder modifizieren
		DEXN_PBDMCodeChanged (m_pOldPBDData -> pbdCode);
		return NOERROR;
	}

return ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoPBDData :: Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

ErrInstall EI (m_ecIgnoreCode);

	if (NULL == m_pNewPBDData) {
	// alten Eintrag wieder löschen
		TX_ASSERT(NULL != m_pOldPBDData);

		if (EC_OKAY == DEX_DelPBDData (*m_pOldPBDData)) {
			DEXN_PBDMCodeChanged (m_pOldPBDData -> pbdCode);
			return NOERROR;
		}
	} else if (EC_OKAY == DEX_ModPBDData (*m_pNewPBDData)) {
	// neu zu erzeugenden Eintrag wieder erzeugen oder modifizieren
		DEXN_PBDMCodeChanged (m_pNewPBDData -> pbdCode);
		return NOERROR;
	}
	
return ResultFromScode (S_FALSE);
}

// *** IUndoRedoObjectFeature *** ---------------------------------------------
STDMETHODIMP CUndoRedoPBDData :: InitDelete (PBDDATATYPE rgType, ULONG ulTarget)
{
	return FInitDelete (rgType, ulTarget) ? NOERROR : ResultFromScode (S_FALSE);
}

STDMETHODIMP CUndoRedoPBDData :: InitModify (const PBDDATA *pNewData, const PBDDATA *pOldData)
{
	return FInitModify (pNewData, pOldData) ? NOERROR : ResultFromScode (S_FALSE);
}

// *** IUnknown methods *** ---------------------------------------------------
STDMETHODIMP CUndoRedoPBDData :: QueryInterface (REFIID riid, LPVOID *ppvObj)
{
// riid identifies an interface type.  Do we support it?
	if (riid == IID_IUnknown || riid == IID_IUndoRedo || 
	    riid == IID_IUndoRedoPBDData) {
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

STDMETHODIMP_(ULONG) CUndoRedoPBDData :: AddRef (void)
{
	return ++m_dwRefCnt;
}

STDMETHODIMP_(ULONG) CUndoRedoPBDData :: Release (void)
{
	if(--m_dwRefCnt == 0) {
		if (m_pfnDestroy) 
			(*m_pfnDestroy)();
		delete this;
	  	return 0;
	}

return m_dwRefCnt;
}

// Funktionen für das Erzeugen und Freigeben einer typspezifischen PBDDATA-Struktur
PBDDATA *__ctPBDDATA (PBDDATATYPE rgType, ULONG lTarget, bool fInitStrings)
{
PBDDATA *pPBDData = NULL;

	switch (rgType) {
	case PBDDATATYPE_IDENT:
		pPBDData = new PBDDATA;
		if (NULL == pPBDData) 
			return NULL;

		INITSTRUCT (*pPBDData, PBDDATA);
		pPBDData -> pbdTyp = 'i';
		break;

	case PBDDATATYPE_FEATURE:
		pPBDData = (PBDDATA *)new PBDMERKMAL;
		if (NULL == pPBDData) 
			return NULL;

		INITSTRUCT (*pPBDData, PBDMERKMAL);
		pPBDData -> pbdTyp = 'm';
		break;

	case PBDDATATYPE_RELATION:
		pPBDData = (PBDDATA *)new PBDRELATION;
		if (NULL == pPBDData) 
			return NULL;

		INITSTRUCT (*pPBDData, PBDRELATION);
		pPBDData -> pbdTyp = 'r';
		break;

	default:
		return NULL;
	}

	pPBDData -> pbdCode = long(lTarget);

	if (fInitStrings) {
		pPBDData -> pbdKText = new char [33];
		if (NULL != pPBDData -> pbdKText)
			pPBDData -> pbdKTextLen = 33;
		pPBDData -> pbdLText = new char [1025];
		if (NULL != pPBDData -> pbdLText)
			pPBDData -> pbdLTextLen = 1025;
	}

return pPBDData;
}

void __dtPBDDATA (PBDDATA *&rpPBDData)
{
	if (NULL == rpPBDData) return;

	if (rpPBDData -> pbdKText) delete [] rpPBDData -> pbdKText;
	if (rpPBDData -> pbdLText) delete [] rpPBDData -> pbdLText;

	delete rpPBDData;
	rpPBDData = NULL;
}

PBDDATATYPE GetPBDType (int iType)
{
	switch (iType) {
	case 'i':
		return PBDDATATYPE_IDENT;

	case 'm':
		return PBDDATATYPE_FEATURE;

	case 'r':
		return PBDDATATYPE_RELATION;

	default:
		break;
	}

return PBDDATATYPE_IDENT;	// Standardmäßig Ident
}

int GetPBDBase (PBDDATATYPE rgType)
{
	switch (rgType) {
	case PBDDATATYPE_IDENT:
		return DEX_GetIdBase();

	case PBDDATATYPE_FEATURE:
		return DEX_GetMkBase();

	case PBDDATATYPE_RELATION:
	default:
		break;
	}

return 10;
}

ErrCode GetPBDIgnoreCode (PBDDATATYPE rgType)
{
	switch (rgType) {
	default:
	case PBDDATATYPE_IDENT:
		break;

	case PBDDATATYPE_FEATURE:
		return WC_NOMERKMAL;

	case PBDDATATYPE_RELATION:
		return WC_NORELATION;
	}

return WC_NOIDENT;
}

