// TRiAS-interne Merkmale als ReadWrite-Objekteigenschaft ---------------------
// File: OPRPFEAT.CXX

#include "trias03p.hxx"

#include "trias03.h"		// Resourcen

#include <containr.hxx>
#include <ixtensn.hxx>
#include <ioprpini.hxx>

#include <xtsnguid.h>
#include <oprpguid.h>
#include <triastlb.h>

#include <errinst.hxx>

#include "intoprop.hxx"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(EnumObjectsByNumber);		// WEnumObjectsByNumber
DefineEnumIIDWrapper(LONG);		// CIID_LONGEnum
DefineSmartEnumerator(LONG);	// WEnumLONG

///////////////////////////////////////////////////////////////////////////////
//
extern LONG g_cObj;	// globaler ObjektZähler

static const char *MCodeObjPropFuncName (long lMCode, short &riMTyp, short &riMLen)
{
static char cbFuncName[_MAX_PATH];
ErrInstall EI (WC_NOMERKMAL);
PBDMERKMAL pbdData;
ErrCode RC; 

	INITSTRUCT(pbdData, PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = cbFuncName;	// gesucht
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = _MAX_PATH;
	pbdData.pbdLTextLen = 0;
	pbdData.ipbdMTyp = 'a';
	pbdData.ipbdMLen = _MAX_PATH;

// PBD-Info holen
	if ((RC = DEX_GetPBDData (pbdData)) != EC_OKAY) {
	string strFmt = ResString (IDM_MCODEFORMAT, 32);

		if (10 == DEX_GetMkBase()) {
			strFmt += "%ld";
			wsprintf (cbFuncName, strFmt.c_str(), lMCode);
		} else {
			strFmt += "%lx";
			wsprintf (cbFuncName, strFmt.c_str(), lMCode);
		}
	}

	riMTyp = pbdData.ipbdMTyp;
	riMLen = pbdData.ipbdMLen;

return cbFuncName;
}

#pragma warning (disable:4355)

CObjPropMerkmal :: CObjPropMerkmal (void)
		 : CBaseObjectProperty (NULL, IDS_OBJPROPMCODEHELP)
{
	m_lCum = 0L;

	INITSTRUCT(m_TM, TARGETMERKMAL);
	m_TM.lMCode = 0L;			// MerkmalsCode
	m_TM.iTTyp = TT_Objekt;

	m_fTemplateValid = false;
	m_fInitialized = false;
}

// CopyConstruktor (für CloneTemplate) ----------------------------------------
bool CObjPropMerkmal::FInit (const CObjPropMerkmal &rOP)
{
	if (!CBaseObjectProperty::FInit(rOP))
		return false;

	m_lCum = rOP.m_lCum;

	INITSTRUCT(m_TM, TARGETMERKMAL);
	m_TM.lMCode = rOP.m_TM.lMCode;		// MerkmalsCode
	m_TM.iTTyp = TT_Objekt;

	m_fTemplateValid = rOP.m_fTemplateValid;
	m_fInitialized = rOP.m_fInitialized;

	m_strTemplate = rOP.m_strTemplate;
	return true;
}


#pragma warning (default:4355)

STDMETHODIMP CObjPropMerkmal :: Reset (void)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	m_lCum = 0L;
	m_strTemplate.remove();
	m_fTemplateValid = false;

return CBaseObjectProperty :: Reset();
}

STDMETHODIMP CObjPropMerkmal :: Eval(LONG lONr, LPSTR pBuffer, ULONG ulLen, 
				     ULONG *pulWritten)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

	m_TM.lTarget = (LPARAM)lONr;		// ObjektNummer
	m_TM.imaxLen = short(ulLen);
#if defined(WIN32)
	m_TM.pMText = pBuffer;
#else
	m_TM.pMText = s_cbOPBuffer;
#endif
	if (DEX_GetTextMerkmal (m_TM)) {		// MWert besorgen
#if defined(WIN32)
		if (pulWritten) *pulWritten = strlen (pBuffer);
		m_lCum += atol (pBuffer);
#else
	ULONG ul = hstrlen (s_cbOPBuffer);

		memcpy (pBuffer, s_cbOPBuffer, ul+1);
		if (pulWritten) *pulWritten = ul;
		m_lCum += atol (s_cbOPBuffer);
#endif
		m_ulCnt++;			// Merkmal existiert
	} else {
		*pBuffer = '\0';
		if (pulWritten) *pulWritten = 0;
		return E_FAIL;
	}

return NOERROR;
}

STDMETHODIMP CObjPropMerkmal :: HelpInfo (LPSTR pBuffer, ULONG ulLen, 
					LPSTR pHelpFile, ULONG *pulHelpCtx)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

ResString resHelp (m_resHelpID, _MAX_PATH);
char cbBuffer[4*_MAX_PATH];
string strT;

	wsprintf (cbBuffer, resHelp, GetName());
	strT = cbBuffer;

ULONG ul = min(ulLen-1, ULONG(strT.length()));

	strncpy (pBuffer, strT.c_str(), ul);
	pBuffer[ul] = '\0';

	if (pHelpFile) *pHelpFile = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0;

return NOERROR;
}

STDMETHODIMP CObjPropMerkmal :: Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

#if defined(WIN32)
	ltoa (m_lCum, pBuffer, 10);
	if (pulWritten) *pulWritten = strlen (pBuffer);
#else
	ltoa (m_lCum, s_cbOPBuffer, 10);

ULONG ul = min (ulLen-1, hstrlen(s_cbOPBuffer));

	memcpy (pBuffer, s_cbOPBuffer, ul+1);
	if (pulWritten) *pulWritten = ul;
#endif

return NOERROR;
}

// normales Wegschreiben einer Objekteigenschaft ------------------------------
STDMETHODIMP CObjPropMerkmal :: Set (LONG lONr, LPCSTR pcBuffer)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	m_TM.lTarget = (LPARAM)lONr;		// ObjektNummer
	m_TM.imaxLen = (NULL !=  pcBuffer) ? strlen(pcBuffer) : 0;
	m_TM.pMText = (char *)pcBuffer;
	if (EC_OKAY != DEX_ModTextMerkmal(m_TM)) 	// MWert schreiben
		return E_FAIL;

return NOERROR;
}

// Funktion entscheidet, ob IObjectProperty2 verfügbar ist oder nicht
HRESULT WINAPI CObjPropMerkmal::_Choice (void *pv, REFIID iid, void** ppvObject, DWORD dw)
{
CObjPropMerkmal *pThis = (CObjPropMerkmal *)pv;

	if (pThis -> GetRO()) 
		return E_NOINTERFACE;		// 'Set' ist nicht verfügbar

// ansonsten normales QI
IUnknown* pUnk = (IUnknown*)((int)pThis+dw);

	pUnk->AddRef();
	*ppvObject = pUnk;
	return S_OK;
}

// IUnknown für MerkmalsObjProp -----------------------------------------------
// *** IObjectProperty specific functions *** 
STDMETHODIMP CObjPropMerkmal :: GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

DWORD dwData = 0L;
HRESULT hr = CBaseObjectProperty::GetPropInfo (pBuffer, wLen, &dwData);

	if (pdwData) {
		*pdwData = dwData | PROPCAPS_USEABLEASTEMPLATE;
		if (m_iMTyp & PBDMERKMAL_SYSTEMFLAG)
			*pdwData |= PROPCAPS_RESTRICTED;	// systeminternes Merkmal
	}

return hr;
}

// IPersistStreamInterface ////////////////////////////////////////////////////
// *** IPersist methods *** 
STDMETHODIMP CObjPropMerkmal::GetClassID (CLSID *pClsID)
{
	*pClsID = GetObjectCLSID();
	return NOERROR;
}

// *** IPersistStream methods *** ---------------------------------------------
STDMETHODIMP CObjPropMerkmal::Load (IStream *pIStream)
{
	SetTemplateValid (false);	// für alle Fälle
	GetTemplStr().remove();

char *pT = NULL;
HRESULT hr = CBaseObjectProperty::Load (pIStream);

	if (FAILED(hr)) return hr;

	try {
	// TargetmerkmalStruktur einlesen
	TARGETMERKMAL &rTM = GetTM();

		THROW_FAILED_HRESULT(pIStream -> Read (&rTM, sizeof(TARGETMERKMAL), NULL));

	// Template selbst einlesen
	ULONG ulSize = 0L;

		THROW_FAILED_HRESULT(pIStream -> Read (&ulSize, sizeof(ULONG), NULL));
		if (ulSize > 0) {
		// Template selbst wieder einlesen
			TX_TRY(pT = new char [ulSize+1]);
			if (NULL == pT) return E_OUTOFMEMORY;

			hr = pIStream -> Read (pT, ulSize+1, NULL);
			if (FAILED(hr)) return hr;
		
			GetTemplStr() = pT;
			SetTemplateValid (true);
		}
	} catch (_com_error& hr) {
		DELETE_VEC(pT);
		return _COM_ERROR(hr);
	}

	DELETE_VEC(pT);

// Objekt ist vollständig initialisiert
	SetDirty (false);
	SetInitialized (true);

return NOERROR;
}

STDMETHODIMP CObjPropMerkmal::Save (IStream *pIStream, BOOL fClearDirty)
{
HRESULT hr = CBaseObjectProperty::Save (pIStream, fClearDirty);

	if (FAILED(hr)) return hr;

// TargetMerkmalStruktur wegschreiben
	hr = pIStream -> Write (&GetTM(), sizeof(TARGETMERKMAL), NULL);
	if (FAILED(hr)) return hr;

// PropertyTemplate wegschreiben
const char *pText = GetTemplStr().c_str();
ULONG ulSize = GetTemplStr().length();

	hr = pIStream -> Write (&ulSize, sizeof(ULONG), NULL);
	if (FAILED(hr)) return hr;

	if (NULL != pText && ulSize > 0) {
		hr = pIStream -> Write (pText, ulSize+1, NULL);
		if (FAILED(hr)) return hr;
	}

// evtl. DirtyFlag löschen
	if (fClearDirty) SetDirty (false);

return NOERROR;
}

STDMETHODIMP CObjPropMerkmal::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;

HRESULT hr = CBaseObjectProperty::GetSizeMax (pcbSize);

	if (SUCCEEDED(hr)) 
	{
		pcbSize -> LowPart += sizeof(ULONG) + GetTemplStr().length() + 
							  sizeof(TARGETMERKMAL)+1;
	}
	return hr;
}

// InitialisierungsInterface //////////////////////////////////////////////////
// *** IInitObjPropMerkmal method *** 
STDMETHODIMP CObjPropMerkmal::Init (LONG lMCode, BOOL fReadOnly)
{
short iMTyp = 0;
short iMLen = 0;

	SetMCode (lMCode);
	SetName (MCodeObjPropFuncName(lMCode, iMTyp, iMLen));
	SetParams (iMLen, iMTyp);
	SetRO (iMTyp & PBDMERKMAL_READONLY ? true : false);
	SetDirty (true);

	SetInitialized (true);

return NOERROR;
}

// IPropertytemplate Interface ////////////////////////////////////////////////
// *** IPropertyTemplate specific methods *** 
// Template setzen ------------------------------------------------------------
STDMETHODIMP CObjPropMerkmal::SetTemplate (LPCSTR pcBuffer)
{
	if (!m_fInitialized) return E_FAIL;

// Template bearbeiten
	if (NULL != pcBuffer) 
		m_strTemplate = pcBuffer;
	else
		m_strTemplate.remove();

	m_fTemplateValid = true;
	SetDirty (false);
	return S_OK;
}

STDMETHODIMP CObjPropMerkmal::GetTemplate (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	if (NULL != pBuffer && ulLen > 0) {
	ULONG ulT = min (ulLen-1, ULONG(m_strTemplate.length()));

		strncpy (pBuffer, m_strTemplate.c_str(), ulT);
		pBuffer[ulT] = '\0';

		if (pulWritten)	*pulWritten = ulT;
		return NOERROR;
	}

	return E_FAIL;
}

// Gesetztes Template verwenden -----------------------------------------------
STDMETHODIMP CObjPropMerkmal::ApplyTemplate (LONG lONr)
{
	if (!m_fInitialized || !m_fTemplateValid) 
		return E_UNEXPECTED;

	m_TM.lTarget = (LPARAM)lONr;			// ObjektNummer
	m_TM.imaxLen = m_strTemplate.length();
	m_TM.pMText = (0 == m_strTemplate.length()) ? NULL : (char *)m_strTemplate.c_str();
	if (EC_OKAY != DEX_ModTextMerkmal(m_TM)) 	// MWert schreiben
		return E_FAIL;

	return NOERROR;
}

// Kopie dieses Objektes anlegen ----------------------------------------------
STDMETHODIMP CObjPropMerkmal::CloneTemplate (IPropertyTemplate **ppITempl)
{
// neue Instanz anlegen
CComObject<CObjPropMerkmal> *pOProp = NULL;
HRESULT hr = CComObject<CObjPropMerkmal>::CreateInstance (&pOProp);

	if (FAILED(hr)) return hr;
	if (!pOProp->FInit (*this))		
		return E_FAIL;

	hr = _InternalQueryInterface (IID_IPropertyTemplate, (LPVOID *)ppITempl);
	if (FAILED(hr))
		delete pOProp;
	else if (HasDeleteFcn())
		piInterlockedIncrement (&g_cObj);

	return hr;
}

// IPropertyInfo Interface ////////////////////////////////////////////////////
// *** IPropertyInfo specific functions 
STDMETHODIMP CObjPropMerkmal::SetPropInfo (LPCSTR pcBuffer, DWORD dwFlags) 
{
ErrInstall EI (WC_NOMERKMAL);
PBDMERKMAL pbdData;
short iMTyp = 0;
short iMLen = 0;

	GetParams (iMLen, iMTyp);
	if (dwFlags & PROPERTYCAPS_NOTREADONLY) 
		iMTyp &= ~PBDMERKMAL_READONLY;
	else
		iMTyp |= PBDMERKMAL_READONLY;

	if (dwFlags & PROPERTYCAPS_RESTRICTED) 
		iMTyp |= PBDMERKMAL_SYSTEMFLAG;
	else
		iMTyp &= ~PBDMERKMAL_SYSTEMFLAG;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = GetMCode();
	pbdData.pbdKText = (char *)pcBuffer;	// neuer Name
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = (NULL != pcBuffer) ? strlen(pcBuffer) : 0;
	pbdData.pbdLTextLen = 0;
	pbdData.ipbdMTyp = iMTyp;
	pbdData.ipbdMTyp = iMLen;

	// PBD-Info setzen
	if (EC_OKAY == DEX_ModPBDData(pbdData)) {
		SetName (pcBuffer);
		return NOERROR;
	} else
		return E_FAIL;
}

STDMETHODIMP CObjPropMerkmal::SetHelpInfo (LPCSTR pBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx)
{
	ATLTRACENOTIMPL("CObjPropMerkmal::SetHelpInfo");
}

// IPropertyInfo2 Interface ///////////////////////////////////////////////////
// *** IPropertyInfo2 specific functions 
STDMETHODIMP CObjPropMerkmal::GetConfigData (VARIANT *pvOptData)
{
	if (NULL == pvOptData) return E_POINTER;

	V_VT(pvOptData) = VT_I4;
	V_I4(pvOptData) = GetMCode();

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// *** DSearchObjects specific functions
int ModeFromSearchMode (SEARCHMODE rgFlags)
{
int iMode = SMExactMatch;

	switch (rgFlags & ~SEARCHMODE_SEARCHMODIFIERS) {
	case SEARCHMODE_NORMAL:
		{
			if (rgFlags & SEARCHMODE_PARTIALMATCH)
				iMode = SMSubstringMatch;
			if (rgFlags & SEARCHMODE_PARTIALMATCHBOB)
				iMode = SMSubStringStartMatch;
		}
		break;

	case SEARCHMODE_LIKE:
		iMode = SMInexactMatch;
		break;

	case SEARCHMODE_REGEXPR:
		iMode = SMRegularExpression;
		break;

	case SEARCHMODE_ONLYEXISTANCE:
		iMode = SMExistanceOnly;
		break;

	default:
		TX_ASSERT(false);		// darf nicht passieren
	}

return iMode;
}

STDMETHODIMP CObjPropMerkmal::ConsiderSearch (
	BSTR bstrToMatch, SEARCHMODE rgFlags, ULONG ulCnt)
{
// Eigentlich müßte an dieser Stelle getestet werden, wieviele Objekte überhaupt 
// diese Objekteigenschaft besitzen. Diese Zahl muß mit 'ulCnt' (Anzahl der 
// zu filternden Objekte) verglichen werden, um abzuschätzen, welche Recherche-
// methode effektiver ist.
// Vorläufig werden lediglich die Methoden zur direkten Recherche empfohlen, die
// auf der Grundlage eines Key's in der Datenbasis realisierbar sind.
HRESULT hr = S_FALSE;	// nicht zu empfehlen

	if (rgFlags & SEARCHMODE_NEGATERESULT)
		return E_NOTIMPL;		// Negation wird nie hier gemacht

	switch (ModeFromSearchMode(rgFlags)) {
	case SMExactMatch:
		hr = S_OK;		// geht schnell
		break;

	case SMInexactMatch:
		break;			// einzelner Test

	case SMSubstringMatch:
		break;			// einzelner Test

	case SMSubStringStartMatch:
		hr = S_OK;		// geht schnell
		break;

	case SMRegularExpression:
		hr = E_NOTIMPL;	// not impl (yet)
		break;
	}
	return hr;
}

extern "C" 
BOOL CALLBACK SearchObjectsMCode (long lONr, BOOL, void *pData)
{
IEnumObjectsByNumber* pIEnum = (IEnumObjectsByNumber *)pData;

	pIEnum -> AddItem (lONr);	// throws bad_alloc
	return true;				// ansonsten immer weitermachen
}

STDMETHODIMP CObjPropMerkmal::SearchObjects (
	BSTR bstrToMatch, SEARCHMODE rgFlags, IEnumObjectsByNumber **ppvObj)
{
// kann Objekte nur effektiv raussuchen, wenn keine RegExpr gefordert sind
	if ((rgFlags & ~SEARCHMODE_SEARCHMODIFIERS) == SEARCHMODE_REGEXPR)
		return E_NOTIMPL;

	if (rgFlags & SEARCHMODE_NOMATCHCASE)
		return E_NOTIMPL;

	if (NULL == ppvObj) return E_POINTER;
	
	*ppvObj = NULL;
	try {
		USES_CONVERSION;

	ENUMRECHTEXTMERKMAL ERT;
	WEnumObjectsByNumber IObjs (CLSID_EnumObjectsByNumber); // Enumerator generieren

		INITSTRUCT(ERT, ENUMRECHTEXTMERKMAL);
		ERT.lMCode = GetMCode();
		ERT.pMWert = OLE2A(bstrToMatch);
		ERT.iMode = ModeFromSearchMode(rgFlags) | SMActViewOnly;
		ERT.eFcn = (RECHTEXTMERKMALCALLBACK)SearchObjectsMCode;
		ERT.pData = (IEnumObjectsByNumber *)IObjs;
	
		if (DEX_EnumRechTextMerkmal(ERT)) 
			*ppvObj = IObjs.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	} 

	return S_OK;
}

