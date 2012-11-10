// Undo/Redo für einen PBD-Eintrag --------------------------------------------
// File: UNDOPBD.CXX

#include "trias03p.hxx"

#include "trias03.h"

#include <containr.hxx>
#include <errinst.hxx>
#include <xtensnn.h>
#include <funcs03.h>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface
#include <enumundo.hxx>		// Enumerator
#include <undoredo.hxx>		// Klassendeklaration

#include "undopbd.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char g_pDLLName[_MAX_PATH];

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

	m_fOldROMode = FALSE;
	m_fNewROMode = FALSE;
}

CUndoRedoPBDData :: ~CUndoRedoPBDData (void)
{
	__dtPBDDATA (m_pNewPBDData);
	__dtPBDDATA (m_pOldPBDData);
}

BOOL CUndoRedoPBDData :: FInitModify (const PBDDATA *pNewData, const PBDDATA *pOldData)
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
	m_fNewROMode = GetROModeIdent(m_rgType, pNewData -> pbdCode);
	
	m_pNewPBDData = CopyPBDData (m_rgType, pNewData);
	if (NULL == m_pNewPBDData) return false;	// muß da sein

	if (NULL != pOldData) {
	// auf jeden Fall modifiziert
		m_pOldPBDData = CopyPBDData (m_rgType, pOldData);
		if (NULL == m_pOldPBDData)
			return false;				// Initialisierungfehler
		m_fOldROMode = GetROModeIdent(m_rgType, pOldData -> pbdCode);

	} else {
	// entweder erzeugt oder modifiziert
		m_pOldPBDData = ReadPBDData (m_rgType, pNewData -> pbdCode);
		m_fOldROMode = GetROModeIdent(m_rgType, pNewData -> pbdCode);
	}

// fertig initialisiert
	Initialized (true);

return true;
}

BOOL CUndoRedoPBDData :: FInitDelete (PBDDATATYPE rgType, HGENERIC ulTarget)
{
// für alle Fälle freigeben
	__dtPBDDATA (m_pNewPBDData);
	__dtPBDDATA (m_pOldPBDData);
	Initialized (false);

// neu initialisieren
	m_pOldPBDData = ReadPBDData (rgType, ulTarget);
	if (NULL == m_pOldPBDData) return false;	// alter Eintrag muß existieren
	m_fOldROMode = GetROModeIdent(rgType, ulTarget);

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
		if (sizeof(PBDMERKMAL) == pData -> dwSize || sizeof(PBDMERKMALEX) == pData -> dwSize) {
			((PBDMERKMAL *)pPBDData) -> ipbdMTyp = ((PBDMERKMAL *)pData) -> ipbdMTyp;
			((PBDMERKMAL *)pPBDData) -> ipbdMLen = ((PBDMERKMAL *)pData) -> ipbdMLen;
			if (sizeof(PBDMERKMALEX) == pData -> dwSize)
				((PBDMERKMALEX *)pPBDData) -> lIdent = ((PBDMERKMALEX *)pData) -> lIdent;
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
PBDDATA *CUndoRedoPBDData :: ReadPBDData (PBDDATATYPE rgType, HGENERIC ulTarget)
{
PBDDATA *pPBDData = __ctPBDDATA (rgType, ulTarget);
ErrCode RC;

	if (NULL == pPBDData || ((EC_OKAY != (RC = DEX_GetPBDData (*pPBDData))) && WC_RETURN != RC)) {
		__dtPBDDATA (pPBDData);
		return NULL;
	}
	return pPBDData;
}

// Zu implementierende InterfaceFunktionen ------------------------------------
STDMETHODIMP_(DWORD) CUndoRedoPBDData :: Capabilities (signed char **pDesc)
{
	if (!isInitialized()) return UNDOREDOCAPS_NOFLAGS;

	if (pDesc) {
	ResourceFile RF (g_pDLLName);
	char cbOKS[64];

		if (PBDDATATYPE_IDENT == m_rgType)
			ClassFromIdent(m_ulTarget, cbOKS, sizeof(cbOKS));
		else
			ultoa (m_ulTarget, cbOKS, m_rgBase);
		if (NULL == m_pOldPBDData) {
		// PBD-Eintrag erzeugt
		ResString resCreateF (ResID (IDS_UNDOCREATEPBDDATA+m_rgType, &RF), 128);

			*pDesc = (signed char *)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf ((char *)*pDesc, resCreateF.Addr(), cbOKS);
			}
		} else if (NULL == m_pNewPBDData) {
		// PBD-Eintrag gelöscht
		ResString resDeleteF (ResID (IDS_UNDODELETEPBDDATA+m_rgType, &RF), 128);

			*pDesc = (signed char *)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf ((char *)*pDesc, resDeleteF.Addr(), cbOKS);
			}
		} else {
		// PBD-Einrag modifiziert
		ResString resEditF (ResID (IDS_UNDOEDITPBDDATA+m_rgType, &RF), 128);

			*pDesc = (signed char *)CoTaskMemAlloc (_MAX_PATH);
			if (*pDesc) {
				wsprintf ((char *)*pDesc, resEditF.Addr(), cbOKS);
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
			if (PBDDATATYPE_IDENT == m_rgType) {
			MODIFYROMODE MRM;

				INITSTRUCT(MRM, MODIFYROMODE);
				MRM.lTarget = m_pNewPBDData -> pbdCode;
				MRM.fROMode = m_fNewROMode;
				DEX_SetROModeIdent (MRM);
			}
			NotifyChanged (m_rgType, m_pNewPBDData -> pbdCode);
			return NOERROR;
		}
	} 
	else {
	ErrCode RC = DEX_ModPBDData (*m_pOldPBDData);

		if (EC_OKAY == RC || WC_RETURN == RC) {
		// gelöschten Eintrag wieder erzeugen oder modifizieren
			if (PBDDATATYPE_IDENT == m_rgType) {
			MODIFYROMODE MRM;

				INITSTRUCT(MRM, MODIFYROMODE);
				MRM.lTarget = m_pOldPBDData -> pbdCode;		// kann sich geändert haben !
				MRM.fROMode = m_fOldROMode;
				DEX_SetROModeIdent (MRM);
			}
			NotifyChanged (m_rgType, m_pOldPBDData -> pbdCode);
			return NOERROR;
		}
	}
	return S_FALSE;
}

STDMETHODIMP CUndoRedoPBDData :: Redo (void)
{
	if (!isInitialized()) return ResultFromScode (S_FALSE);

ErrInstall EI (m_ecIgnoreCode);

	if (NULL == m_pNewPBDData) {
	// alten Eintrag wieder löschen
		TX_ASSERT(NULL != m_pOldPBDData);

		if (EC_OKAY == DEX_DelPBDData (*m_pOldPBDData)) {
			if (PBDDATATYPE_IDENT == m_rgType) {
			MODIFYROMODE MRM;

				INITSTRUCT(MRM, MODIFYROMODE);
				MRM.lTarget = m_pOldPBDData -> pbdCode;
				MRM.fROMode = m_fOldROMode;
				DEX_SetROModeIdent (MRM);
			}
			NotifyChanged (m_rgType, m_pOldPBDData -> pbdCode);
			return NOERROR;
		}
	} 
	else {
	ErrCode RC = DEX_ModPBDData (*m_pNewPBDData);

		if (EC_OKAY == RC || WC_RETURN == RC) {
		// neu zu erzeugenden Eintrag wieder erzeugen oder modifizieren
			if (PBDDATATYPE_IDENT == m_rgType) {
			MODIFYROMODE MRM;

				INITSTRUCT(MRM, MODIFYROMODE);
				MRM.lTarget = m_pNewPBDData -> pbdCode;		// kann sich geändert haben!
				MRM.fROMode = m_fNewROMode;
				DEX_SetROModeIdent (MRM);
			}
			NotifyChanged (m_rgType, m_pNewPBDData -> pbdCode);
			return NOERROR;
		}
	}
	return S_FALSE;
}

// *** IUndoRedoObjectFeature *** ---------------------------------------------
STDMETHODIMP CUndoRedoPBDData :: InitDelete (PBDDATATYPE rgType, HGENERIC ulTarget)
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
PBDDATA *__ctPBDDATA (PBDDATATYPE rgType, HGENERIC lTarget, BOOL fInitStrings)
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
		pPBDData = (PBDDATA *)new PBDMERKMALEX;
		if (NULL == pPBDData) 
			return NULL;

		INITSTRUCT (*pPBDData, PBDMERKMALEX);
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
		pPBDData -> pbdKText = new char [256];
		if (NULL != pPBDData -> pbdKText)
			pPBDData -> pbdKTextLen = 256;
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

BOOL GetROModeIdent (PBDDATATYPE rgType, long lIdent)
{
	switch (rgType) {
	default:
	case PBDDATATYPE_IDENT:
		return DEX_GetROModeIdent(lIdent);

	case PBDDATATYPE_FEATURE:
		break;

	case PBDDATATYPE_RELATION:
		break;
	}
	return FALSE;
}

void NotifyChanged (PBDDATATYPE rgType, long lTarget)
{
	switch (rgType) {
	default:
	case PBDDATATYPE_IDENT:
		DEXN_PBDIdentChanged(lTarget);

	case PBDDATATYPE_FEATURE:
		DEXN_PBDMCodeChanged(lTarget);

	case PBDDATATYPE_RELATION:
		DEXN_PBDRCodeChanged(lTarget);
	}
}
