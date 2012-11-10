// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/12/1998 07:27:09 PM
//
// @doc
// @module ObjPropFeature.cpp | TRiAS-interne Merkmale als ReadWrite-Objekteigenschaft 

#include "trias03p.hxx"

#include "trias03.h"		// Resourcen
#include "Strings.h"

#include <containr.hxx>
#include <ixtensn.hxx>
#include <ioprpini.hxx>

#include <xtsnguid.h>
#include <oprpguid.h>
#include <triastlb.h>
#include <xtensnn.h>

#include <Com/PropertyHelper.h>

#include <errinst.hxx>
#include <PropName.hxx>

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

DefineSmartInterface(TRiASObjectHandleMap);
DefineSmartInterface(TRiASObjects);
DefineSmartInterface(TRiASObject);
DefineSmartInterface(TRiASFeature);
DefineSmartInterface(PersistStream);

///////////////////////////////////////////////////////////////////////////////
//
extern LONG g_cObj;		// globaler ObjektZähler

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

CObjPropMerkmal::CObjPropMerkmal (void)
		 : CBaseObjectProperty (NULL, IDS_OBJPROPMCODEHELP)
{
	m_lCum = 0L;

	m_lMCode = 0L;			// MerkmalsCode
	m_iMTyp = 0;

	m_fTemplateValid = false;
	m_fInitialized = false;
}

// CopyConstruktor (für CloneTemplate) ----------------------------------------
bool CObjPropMerkmal::FInit (const CObjPropMerkmal &rOP)
{
	if (!CBaseObjectProperty::FInit(rOP))
		return false;

	m_lCum = rOP.m_lCum;

	m_lMCode = rOP.m_lMCode;		// MerkmalsCode
	m_iMTyp = rOP.m_iMTyp;

	m_fTemplateValid = rOP.m_fTemplateValid;
	m_fInitialized = rOP.m_fInitialized;

	m_strTemplate = rOP.m_strTemplate;
	return true;
}


#pragma warning (default:4355)

STDMETHODIMP CObjPropMerkmal::Reset (void)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	m_lCum = 0L;
	m_strTemplate.remove();
	m_fTemplateValid = false;

	return CBaseObjectProperty::Reset();
}

STDMETHODIMP CObjPropMerkmal::Eval(
	LONG lONr, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

HRESULT hr = E_FAIL;

	*pBuffer = '\0';
	if (pulWritten) *pulWritten = 0;

// Feature besorgen
WTRiASObject Obj;
WTRiASFeature Feat;

	if (SUCCEEDED(RetrieveFeature (lONr, Feat.ppi(), Obj.ppi()))) {
	// jetzt eigentliches Merkmal abfragen
	CComVariant vVal;
	
		hr = Feat -> Eval (Obj, &vVal);
		if (SUCCEEDED(hr)) {
			RETURN_FAILED_HRESULT(vVal.ChangeType (VT_BSTR));

		size_t iStrLen = ::SysStringLen(V_BSTR(&vVal));	// grundsätzlich Textlänge liefern
		size_t iToCopy = min (iStrLen, (size_t)(ulLen-1));

			if (NULL != pBuffer && iToCopy > 0) {
				USES_CONVERSION;
				strncpy (pBuffer, OLE2A(V_BSTR(&vVal)), iToCopy);
				pBuffer[iToCopy] = '\0';
			}

		// kumulativen Index und Zähler aktualisieren
			m_lCum += atol (pBuffer);
			m_ulCnt++;					// Merkmal existiert

			if (pulWritten) *pulWritten = iToCopy;
		}
	} 
	return hr;
}

STDMETHODIMP CObjPropMerkmal::HelpInfo (
	LPSTR pBuffer, ULONG ulLen, LPSTR pHelpFile, ULONG *pulHelpCtx)
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

STDMETHODIMP CObjPropMerkmal::Cumulation (LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	TX_ASSERT(NULL != pBuffer);
	TX_ASSERT(0 != ulLen);

	ltoa (m_lCum, pBuffer, 10);
	if (pulWritten) *pulWritten = strlen (pBuffer);

	return S_OK;
}

// normales Wegschreiben einer Objekteigenschaft ------------------------------
STDMETHODIMP CObjPropMerkmal::Set (LONG lONr, LPCSTR pcBuffer)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	USES_CONVERSION;

// Feature besorgen
WTRiASObject Obj;
WTRiASFeature Feat;

	RETURN_FAILED_HRESULT(RetrieveFeature (lONr, Feat.ppi(), Obj.ppi(), true));

// jetzt eigentliches Merkmal setzn
CComVariant vVal(DISP_E_PARAMNOTFOUND, VT_ERROR);

	if (NULL != pcBuffer)		// wenn Text gleich NULL, dann löschen
		vVal = pcBuffer;

	RETURN_FAILED_HRESULT(Feat -> Update (Obj, vVal));

// die Welt in Kenntnis setzen
CComBSTR bstrName;
FEATUREMODIFIED FM;

	RETURN_FAILED_HRESULT(Feat -> get_Name(&bstrName));

	INITSTRUCT(FM, FEATUREMODIFIED);
	FM.lONr = lONr;
	FM.pcName = OLE2A(bstrName);
	DEXN_FeatureModifiedEx (FM);		// Merkmal wurde modifiziert

	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// aus MerkmalsCode das zugehörige Feature Objekt besorgen
HRESULT CObjPropMerkmal::RetrieveFeature (
	INT_PTR lONr, ITRiASFeature **ppIFeat, ITRiASObject **ppIObj, bool fCreate)
{
	if (NULL == ppIFeat)
		return E_POINTER;

WTRiASObjectHandleMap MapObj (CLSID_TRiASObjectHandleMap);
WTRiASObject Obj;			// gesuchtes Objekt

	RETURN_FAILED_HRESULT(MapObj -> GetObject (lONr, Obj.ppu()));

// Feature von zugehöriger Objektklasse geben lassen
WTRiASObjectHandleMap MapFeat (CLSID_TRiASFeatureHandleMap);
WTRiASFeature Feat;

	if (FAILED(MapFeat -> GetObject (GetMCode(), Feat.ppu())) && fCreate) {
	// Attribut neu erzeugen
	WTRiASObjectHandleMap MapObjs (CLSID_TRiASObjectsHandleMap);
	INT_PTR hObjs = NULL;
	WTRiASObjects Objs;			// zugehörige Objektklasse

		RETURN_FAILED_HRESULT(Obj -> get_ObjectsHandle (&hObjs));
		RETURN_FAILED_HRESULT(MapObjs -> GetObject (hObjs, Objs.ppu()));
		RETURN_FAILED_HRESULT(Objs -> get_Feature (CComVariant(GetMCode()), VARIANT_TRUE, CComBSTR(g_cbNil), Feat.ppi()));
	}

	if (NULL != ppIObj)
		*ppIObj = Obj.detach();

	*ppIFeat = Feat.detach();
	return S_OK;
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
STDMETHODIMP CObjPropMerkmal::GetPropInfo (LPSTR pBuffer, WORD wLen, DWORD *pdwData)
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
	// BezugsObjekt speichern
	WTRiASObjectHandleMap MapFeat(CLSID_TRiASFeatureHandleMap);
	WTRiASFeature Feat;

		RETURN_FAILED_HRESULT(MapFeat -> GetObject (GetMCode(), Feat.ppu()));

	WPersistStream PS;

		if (SUCCEEDED(Feat -> QueryInterface(IID_IPersistStream, PS.ppv())))
		{
			RETURN_FAILED_HRESULT(PS -> Load (pIStream));
		}

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

	return S_OK;
}

STDMETHODIMP CObjPropMerkmal::Save (IStream *pIStream, BOOL fClearDirty)
{
HRESULT hr = CBaseObjectProperty::Save (pIStream, fClearDirty);

	if (FAILED(hr)) return hr;

// BezugsObjekt speichern
WTRiASObjectHandleMap MapFeat(CLSID_TRiASFeatureHandleMap);
WTRiASFeature Feat;

	RETURN_FAILED_HRESULT(MapFeat -> GetObject (GetMCode(), Feat.ppu()));

WPersistStream PS;

	if (SUCCEEDED(Feat -> QueryInterface(IID_IPersistStream, PS.ppv())))
	{
		RETURN_FAILED_HRESULT(PS -> Save(pIStream, fClearDirty));
	}

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

	return S_OK;
}

STDMETHODIMP CObjPropMerkmal::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	if (NULL == pcbSize)
		return E_POINTER;

// BezugsObjekt speichern
WTRiASObjectHandleMap MapFeat(CLSID_TRiASFeatureHandleMap);
WTRiASFeature Feat;

	RETURN_FAILED_HRESULT(MapFeat -> GetObject (GetMCode(), Feat.ppu()));

WPersistStream PS;

	if (SUCCEEDED(Feat -> QueryInterface(IID_IPersistStream, PS.ppv())))
		PS -> GetSizeMax (pcbSize);

ULARGE_INTEGER cbSize;

	cbSize.QuadPart = 0;
	CBaseObjectProperty::GetSizeMax (&cbSize);
	pcbSize -> QuadPart += cbSize.QuadPart + sizeof(ULONG) + GetTemplStr().length()+1;

	return S_OK;
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

	return S_OK;
}

// IPropertytemplate Interface ////////////////////////////////////////////////
// *** IPropertyTemplate specific methods *** 
// Template setzen 
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

	return Set (lONr, m_strTemplate.c_str());
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

CPropertyName PName (pcBuffer);

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = GetMCode();
	pbdData.pbdKText = (char *)PName.GetName().c_str();	// neuer Name
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = (NULL != pcBuffer) ? PName.GetName().length() : 0;
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

///////////////////////////////////////////////////////////////////////////////
// *** IPropertyInfo2 specific functions 
STDMETHODIMP CObjPropMerkmal::GetConfigData (VARIANT *pvOptData)
{
	if (NULL == pvOptData) return E_POINTER;

	V_VT(pvOptData) = VT_I4;
	V_I4(pvOptData) = GetMCode();

	return S_OK;
}

STDMETHODIMP CObjPropMerkmal::EvaluatesForClass (INT_PTR hObjs)
{
	COM_TRY {
	WTRiASObjectHandleMap Map (CLSID_TRiASObjectsHandleMap);
	WTRiASObjects Objs;

		THROW_FAILED_HRESULT(Map -> GetObject (hObjs, Objs.ppu()));

	WTRiASObjectHandleMap MapFeat (GetPropertyFrom (Objs, g_cbFeatureMap, (IDispatch *)NULL), false);	// GetProperty liefert AddRef'ed ab
	WTRiASFeature Feat;

		if (FAILED(MapFeat -> GetObject (GetMCode(), Feat.ppu()))) 
			return S_FALSE;		// gehört nicht zu der gegebenen Objektklasse

	} COM_CATCH;
	return S_OK;		// ghört zur angegebenen Objektklasse
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

