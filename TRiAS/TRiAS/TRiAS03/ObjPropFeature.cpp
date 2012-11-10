// $Header: $
// Copyright© 1998 Fernerkundungszentrum Potsdam GmbH, All rights reserved
// Created: 11/12/1998 07:27:09 PM
//
// @doc
// @module ObjPropFeature.cpp | TRiAS-interne Merkmale als ReadWrite-Objekteigenschaft 

#include "trias03p.hxx"

#include "trias03.h"		// Resourcen
#include "Strings.h"
#include <Funcs03.h>

#include <Com/MkHelper.h>

#include <containr.hxx>
#include <ixtensn.hxx>
#include <ioprpini.hxx>

#include <xtsnguid.h>
#include <oprpguid.h>
#include <triastlb.h>
#include <xtensnn.h>

#include <Com/PropertyHelper.h>
#include <Com/VariantHelpers.h>

#include <errinst.hxx>
#include <PropName.hxx>

#include <undoguid.h>		// GUID
#include <iunredo.hxx>		// Interface

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
DefineSmartInterface(TRiASFeatures);
DefineSmartInterface(TRiASFeature);
DefineSmartInterface(PersistStream);
DefineSmartInterface(Moniker);
DefineSmartInterface(OleObject);

DefineSmartInterface(UndoRedoObjectFeature);

///////////////////////////////////////////////////////////////////////////////
//
extern LONG g_cObj;		// globaler ObjektZähler

_TRIAS03_ENTRY LPCSTR MCodeObjPropFuncName (LPSTR pBuffer, long lMCode, short *piMTyp, short *piMLen)
{
ErrInstall EI (WC_NOMERKMAL);
PBDMERKMAL pbdData;

	INITSTRUCT(pbdData, PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = lMCode;
	pbdData.pbdKText = pBuffer;	// gesucht
	pbdData.pbdLText = NULL;
	pbdData.pbdKTextLen = _MAX_PATH;
	pbdData.pbdLTextLen = 0;
	pbdData.ipbdMTyp = 'a';
	pbdData.ipbdMLen = _MAX_PATH;

// PBD-Info holen
ErrCode RC = DEX_GetPBDData (pbdData);

	if (EC_OKAY != RC && WC_RETURN != RC) {
	string strFmt = ResString (IDM_MCODEFORMAT, 32);

		if (10 == DEX_GetMkBase()) {
			strFmt += "%ld";
			wsprintf (pBuffer, strFmt.c_str(), lMCode);
		} else {
			strFmt += "%lx";
			wsprintf (pBuffer, strFmt.c_str(), lMCode);
		}
	}

	if (NULL != piMTyp)
		*piMTyp = pbdData.ipbdMTyp;
	if (NULL != piMLen)
		*piMLen = pbdData.ipbdMLen;

	return pBuffer;
}

#pragma warning (disable:4355)

CObjPropMerkmal::CObjPropMerkmal (void)
		 : CBaseObjectProperty (NULL, IDS_OBJPROPMCODEHELP)
{
	m_lCum = 0L;

	m_iMTyp = 0;
	m_iMLen = _MAX_PATH;	// ??!!

	m_fTemplateValid = false;
	m_fInitialized = false;
}

// CopyConstruktor (für CloneTemplate) ----------------------------------------
bool CObjPropMerkmal::FInit (const CObjPropMerkmal &rOP)
{
	if (!CBaseObjectProperty::FInit(rOP))
		return false;

	m_lCum = rOP.m_lCum;

	m_ConnProps = rOP.m_ConnProps;		// MerkmalsCode
	m_iMTyp = rOP.m_iMTyp;
	m_iMLen = rOP.m_iMLen;

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
		if (SUCCEEDED(hr) && !V_ISNULL(&vVal)) {
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
		} else {
			if (pulWritten) 
				*pulWritten = 0;

		// GDO kann das ! nicht existierende Objekteigenschaften, die gültig sind
//			if (SUCCEEDED(hr))
				hr = E_FAIL;		// V_ISNULL: existiert nicht
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

	if (GetDescription(strT))		// ggf. Langtext anzeigen
		wsprintf (cbBuffer, resHelp, strT.c_str());
	else
		wsprintf (cbBuffer, resHelp, GetName());
	strT = cbBuffer;

ULONG ul = min(ulLen-1, ULONG(strT.length()));

	strncpy (pBuffer, strT.c_str(), ul);
	pBuffer[ul] = '\0';

	if (pHelpFile) *pHelpFile = '\0';
	if (pulHelpCtx) *pulHelpCtx = 0;

	return NOERROR;
}

bool CObjPropMerkmal::GetDescription(INT_PTR hFeat)
{
	m_strDesc = g_cbNil;

char cbBuffer[4*_MAX_PATH];	
ErrInstall EI (WC_NOMERKMAL);
PBDMERKMAL pbdData;

	cbBuffer[0] = '\0';

	INITSTRUCT(pbdData, PBDMERKMAL);
	pbdData.pbdTyp = 'm';
	pbdData.pbdCode = hFeat;
	pbdData.pbdKText = NULL;
	pbdData.pbdLText = cbBuffer;
	pbdData.pbdKTextLen = 0;
	pbdData.pbdLTextLen = sizeof(cbBuffer);
	pbdData.ipbdMTyp = 'a';
	pbdData.ipbdMLen = _MAX_PATH;

// PBD-Info holen
ErrCode RC = DEX_GetPBDData (pbdData);

	if (EC_OKAY != RC) 
		return false;

	m_strDesc = cbBuffer;
	return true;
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
HRESULT hr = RetrieveFeature (lONr, Feat.ppi(), Obj.ppi(), true);

	if (FAILED(hr)) return hr;		// Merkmal gehört nicht zu dieser Objektklasse

// jetzt eigentliches Merkmal setzen
CComVariant vVal(DISP_E_PARAMNOTFOUND, VT_ERROR);

	if (NULL != pcBuffer)		// wenn Text gleich NULL, dann löschen
		vVal = pcBuffer;

	RETURN_FAILED_HRESULT(Feat -> Update (Obj, vVal));

// die Welt in Kenntnis setzen
CComBSTR bstrName;
FEATUREMODIFIED FM;

	RETURN_FAILED_HRESULT(Feat -> get_Name(CLEARED(&bstrName)));

	INITSTRUCT(FM, FEATUREMODIFIED);
	FM.lONr = lONr;
	FM.pcName = OLE2A(bstrName);
	DEXN_FeatureModifiedEx (FM);		// Merkmal wurde modifiziert

// Merkmal wurde modifiziert (alte Variante)
	DEXN_FeatureModified (lONr);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Schreiben des Attributes mit Undo
STDMETHODIMP CObjPropMerkmal::SetWithUndo (LONG lONr, LPCSTR pcBuffer)
{
	if (!m_fInitialized) 
		return E_UNEXPECTED;

	USES_CONVERSION;

// Feature besorgen
WTRiASObject Obj;
WTRiASFeature Feat;
INT_PTR lMCode = 0L;
HRESULT hr = RetrieveFeature (lONr, Feat.ppi(), Obj.ppi(), true, &lMCode);

	if (FAILED(hr))
		return hr;		// Merkmal gehört nicht zu dieser Objektklasse

	{
	WUndoRedoObjectFeature Undo;		// UndoRedo
	HRESULT hr = UndoCreateInstance (IID_IUndoRedoObjectFeature, Undo.ppv());

		if (SUCCEEDED(hr))
			hr = Undo -> Init (lONr, lMCode, pcBuffer, NULL); 

	// jetzt eigentliches Merkmal setzen
	CComVariant vVal(DISP_E_PARAMNOTFOUND, VT_ERROR);

		if (NULL != pcBuffer)		// wenn Text gleich NULL, dann löschen
			vVal = pcBuffer;

		RETURN_FAILED_HRESULT(Feat -> Update (Obj, vVal));

		if (S_OK == hr) 
			DEX_AddUndoRedo ((IUnknown *)Undo);
	}

// die Welt in Kenntnis setzen
CComBSTR bstrName;
FEATUREMODIFIED FM;

	RETURN_FAILED_HRESULT(Feat -> get_Name(CLEARED(&bstrName)));

	INITSTRUCT(FM, FEATUREMODIFIED);
	FM.lONr = lONr;
	FM.pcName = OLE2A(bstrName);
	DEXN_FeatureModifiedEx (FM);		// Merkmal wurde modifiziert

// Merkmal wurde modifiziert (alte Variante)
	DEXN_FeatureModified (lONr);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// aus MerkmalsCode das zugehörige Feature Objekt besorgen
HRESULT CObjPropMerkmal::RetrieveFeature (
	INT_PTR lONr, ITRiASFeature **ppIFeat, ITRiASObject **ppIObj, bool fCreate, INT_PTR *plMCode)
{
	if (NULL == ppIFeat)
		return E_POINTER;

WTRiASObjectHandleMap MapObj (CLSID_TRiASObjectHandleMap);
WTRiASObject Obj;			// gesuchtes Objekt

	RETURN_FAILED_HRESULT(MapObj -> GetObject (lONr, Obj.ppu()));

// Feature von zugehöriger Objektklasse geben lassen
WTRiASObjectHandleMap MapFeat (CLSID_TRiASFeatureHandleMap);
WTRiASFeature Feat;
INT_PTR hObjs = DEX_GetObjIdent(lONr);
INT_PTR hFeat = GetMCode(hObjs);

	if (NULL == hFeat)
		return E_UNEXPECTED;

HRESULT hr = S_OK;

	if (FAILED(hr = MapFeat -> GetObject (hFeat, Feat.ppu())) && fCreate) {
	// Attribut neu erzeugen
	WTRiASObjectHandleMap MapObjs (CLSID_TRiASObjectsHandleMap);
	WTRiASObjects Objs;			// zugehörige Objektklasse

		RETURN_FAILED_HRESULT(Obj -> get_ObjectsHandle (&hObjs));
		RETURN_FAILED_HRESULT(MapObjs -> GetObject (hObjs, Objs.ppu()));
		RETURN_FAILED_HRESULT(Objs -> get_Feature (CComVariant(hFeat), VARIANT_TRUE, CComBSTR(g_cbNil), Feat.ppi()));
	}

	if (NULL != ppIObj)
		*ppIObj = Obj.detach();
	if (NULL != plMCode)
		*plMCode = hFeat;
		
	*ppIFeat = Feat.detach();
	return hr;
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

		switch (m_iMTyp & 0x7f) {
		case 'i':		// Objekteigenschaft liefert Integer Werte
			*pdwData |= PROPCAPS_OBJPROPTYPE_INTEGER;
			break;

		case 'f':		// Objekteigenschaft liefert double Werte
			*pdwData |= PROPCAPS_OBJPROPTYPE_DOUBLE;
			break;

		default:		// ansonsten als Zeichenkette auswerten
			break;
		}
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

// Signaturen laden und abgleichen
DWORD dwSignature = 0;

	RETURN_FAILED_HRESULT(pIStream -> Read (&dwSignature, sizeof(DWORD), NULL));
	if (OBJPROP_SIGNATURE != dwSignature)
		return E_UNEXPECTED;

DWORD dwVersion = 0L;

	RETURN_FAILED_HRESULT(pIStream -> Read (&dwVersion, sizeof(DWORD), NULL));
	if (OBJPROP_LASTVERSION < (dwVersion & ~OBJPROP_VERSION_MINOR_MASK))		// Version zu neu
		return E_UNEXPECTED;

	try {
	// BezugsObjekt laden
	ULONG ulCnt = 0;

		THROW_FAILED_HRESULT(pIStream -> Read (&ulCnt, sizeof(ULONG), NULL));
		for (ULONG ul = 0; ul < ulCnt; ul++) {
		WTRiASObjects Objs;
		WTRiASFeature Feat;
		WMoniker mk;

			THROW_FAILED_HRESULT(OleLoadFromStream(pIStream, IID_IMoniker, mk.ppv()));
			THROW_FAILED_HRESULT(MkBindToObject(mk, IID_ITRiASObjects, Objs.ppv()));

			THROW_FAILED_HRESULT(OleLoadFromStream(pIStream, IID_IMoniker, mk.ppv()));
			THROW_FAILED_HRESULT(MkBindToObject(mk, IID_ITRiASFeature, Feat.ppv()));

		INT_PTR hObjs = NULL;
		INT_PTR hFeat = NULL;
		VARIANT_BOOL fWriteable = VARIANT_FALSE;

			THROW_FAILED_HRESULT(Objs -> get_Handle (&hObjs));
			THROW_FAILED_HRESULT(Feat -> get_Handle (&hFeat));
			THROW_FAILED_HRESULT(Feat -> get_Updatable (&fWriteable));

			m_ConnProps.insert (CObjectsFeaturesMap::value_type(hObjs, CObjectsFeature(hFeat, fWriteable ? FALSE : TRUE)));
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

// Signaturen speichern
	RETURN_FAILED_HRESULT(pIStream -> Write (&OBJPROP_SIGNATURE, sizeof(DWORD), NULL));
	RETURN_FAILED_HRESULT(pIStream -> Write (&OBJPROP_LASTVERSION, sizeof(DWORD), NULL));

// BezugsObjekte speichern
WTRiASObjectHandleMap MapFeat(CLSID_TRiASFeatureHandleMap);
WTRiASObjectHandleMap MapObjs(CLSID_TRiASObjectsHandleMap);
ULONG ulCnt = m_ConnProps.size();	// Anzahl der Features

	RETURN_FAILED_HRESULT(pIStream -> Write (&ulCnt, sizeof(ULONG), NULL));

	for (CObjectsFeaturesMap::iterator it = m_ConnProps.begin(); it != m_ConnProps.end(); ++it) {
	WTRiASObjects Objs;
	WTRiASFeature Feat;

		RETURN_FAILED_HRESULT(MapObjs -> GetObject ((*it).first, Objs.ppu()));
		RETURN_FAILED_HRESULT(MapFeat -> GetObject ((*it).second.first, Feat.ppu()));

	WMoniker mkObj, mkFeat;

		RETURN_FAILED_HRESULT(WOleObject(Objs) -> GetMoniker(OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, mkObj.ppi()));
		RETURN_FAILED_HRESULT(OleSaveToStream (mkObj, pIStream));

		RETURN_FAILED_HRESULT(WOleObject(Feat) -> GetMoniker(OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, mkFeat.ppi()));
		RETURN_FAILED_HRESULT(OleSaveToStream (mkFeat, pIStream));

#if defined(_DEBUG)
	CComBSTR bstrMkObj, bstrMkFeat;

		MkGetDisplayName(mkObj, &bstrMkObj);
		MkGetDisplayName(mkFeat, &bstrMkFeat);
#endif // defined(_DEBUG)
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

ULARGE_INTEGER cbSize;

	pcbSize -> QuadPart = 0;

// BezugsObjekt speichern
WTRiASObjectHandleMap MapFeat(CLSID_TRiASFeatureHandleMap);

	for (CObjectsFeaturesMap::iterator it = m_ConnProps.begin(); it != m_ConnProps.end(); ++it) {
	WTRiASFeature Feat;

		RETURN_FAILED_HRESULT(MapFeat -> GetObject ((*it).second.first, Feat.ppu()));

	WPersistStream PS;

		if (SUCCEEDED(Feat -> QueryInterface(IID_IPersistStream, PS.ppv()))) {
			cbSize.QuadPart = 0;
			PS -> GetSizeMax (&cbSize);
			pcbSize -> QuadPart += cbSize.QuadPart;
		}
	}

	cbSize.QuadPart = 0;
	CBaseObjectProperty::GetSizeMax (&cbSize);
	pcbSize -> QuadPart += cbSize.QuadPart + 2*sizeof(ULONG) + GetTemplStr().length()+1;

	return S_OK;
}

// InitialisierungsInterface //////////////////////////////////////////////////
// *** IInitObjPropMerkmal method *** 
STDMETHODIMP CObjPropMerkmal::Init (LONG lMCode, BOOL fReadOnly)
{
//short iMTyp = 0;
//short iMLen = 0;
//
//	SetMCode (lMCode);
//	SetName (MCodeObjPropFuncName(lMCode, iMTyp, iMLen));
//	SetParams (iMLen, iMTyp);
//	SetRO (iMTyp & PBDMERKMAL_READONLY ? true : false);
//	SetDirty (true);
//
//	SetInitialized (true);

	TX_ASSERT(FALSE);		// obsolete: nicht mehr rufen
	return S_OK;
}

// die Objekteigenschaft speichert jetzt für jede übergebene Objektklasse das zugehörigen 
// FeatureHandle
#if defined(_DEBUG)
void DumpFeature (INT_PTR hFeat, LPCSTR pcComment)
{
	TX_TRACE2("Featuredump for %s (%ld):\r\n", pcComment, hFeat);
	TX_TRACE1("  HPROJECT: %lx\r\n", DEX_GetFeatureProject(hFeat));

PBDDATA PbdData;
char cbBuffer[64];

	strcpy (cbBuffer, "<Unknown>");

	INITSTRUCT(PbdData, PBDDATA);
	PbdData.pbdTyp = 'm';
	PbdData.pbdCode = hFeat;
	PbdData.pbdKText = cbBuffer;
	PbdData.pbdKTextLen = sizeof(cbBuffer);
	DEX_GetPBDData(PbdData);
	TX_TRACE1("  Name: '%s'\r\n", cbBuffer);
}
#endif // _DEBUG

STDMETHODIMP CObjPropMerkmal::InitWithObjects (INT_PTR hObjs, INT_PTR hFeat, BOOL fReadOnly)
{
CObjectsFeaturesMap::iterator it = m_ConnProps.find (hObjs);

	if (it != m_ConnProps.end()) {
	// evtl. Daten abgleichen
#if defined(_DEBUG)
		if (hFeat != (*it).second.first) {
			DumpFeature (hFeat, "new code");
			DumpFeature ((*it).second.first, "existing code");
		}
		TX_ASSERT(hFeat == (*it).second.first);
#endif // _DEBUG

		if ((*it).second.second != (fReadOnly ? true : false)) {
			(*it).second.second = fReadOnly;
			SetRO (fReadOnly);
		}
		return S_FALSE;		// existiert bereits
	}

pair<CObjectsFeaturesMap::iterator, bool> p = m_ConnProps.insert (CObjectsFeaturesMap::value_type(hObjs, CObjectsFeature(hFeat, fReadOnly)));

	if (!p.second)
		return E_OUTOFMEMORY;

	if (1 == m_ConnProps.size() || !m_fInitialized) {
	// beim ersten Initialisierung vervollständigen
	short iMTyp = 0;
	short iMLen = 0;
	char cbBuffer[_MAX_PATH];

		SetName (MCodeObjPropFuncName(cbBuffer, hFeat, &iMTyp, &iMLen));
		SetParams (iMLen, iMTyp);
		GetDescription (hFeat);
		SetRO (iMTyp & PBDMERKMAL_READONLY ? true : false);
		SetInitialized (true);
	}

	SetDirty (true);
	return S_OK;
}

STDMETHODIMP CObjPropMerkmal::InitWithObjectsEx (LONG lCnt, INT_PTR *phObjs, INT_PTR hFeat, BOOL fReadOnly)
{
// alle übergebenen Objektklassen durchgehen
HRESULT hr = S_OK;
bool fAllResultsEqual = true;

	for (long i = 0; i < lCnt; ++i) {
	// einfach für alle das Gleiche machen
	HRESULT hr2;

		RETURN_FAILED_HRESULT(hr2 = InitWithObjects (phObjs[i], hFeat, fReadOnly));
		if (0 == i)
			hr = hr2;
		else if (hr != hr2)
			fAllResultsEqual = false;
	}
	return fAllResultsEqual ? hr : S_OK;
}

HRESULT CObjPropMerkmal::HasObjects (INT_PTR hObjs, VARIANT_BOOL *pfRegistered)
{
	if (NULL == pfRegistered)
		return E_POINTER;

CObjectsFeaturesMap::iterator it = m_ConnProps.find (hObjs);

	*pfRegistered = (it != m_ConnProps.end()) ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

HRESULT CObjPropMerkmal::RemoveObjects (INT_PTR hObjs)
{
CObjectsFeaturesMap::iterator it = m_ConnProps.find (hObjs);

	if (it != m_ConnProps.end()) {
#if defined(_DEBUG)
	INT_PTR hFeat = (*it).second.first;
#endif // define(_DEBUG)

		m_ConnProps.erase(it);			// aus der Liste der bekannten entfernen
		return S_OK;
	}
	return S_FALSE;
}

extern "C" 
BOOL CALLBACK EnumClassesForProject (long hObjs, BOOL iNotLast, void *pData)
{
CObjPropMerkmal *pProp = (CObjPropMerkmal *)pData;

	pProp -> RemoveObjects (hObjs);
	return TRUE;
}

HRESULT CObjPropMerkmal::RemoveAllObjects (INT_PTR hPr)
{
ENUMNOKEYLONG ENK;

	ENK.eFcn = (ENUMNOKEYLONGPROC)EnumClassesForProject;
	ENK.ePtr = this;
	return DEX_EnumClasses((HPROJECT)hPr, ENK) ? S_OK : E_FAIL;
}

INT_PTR CObjPropMerkmal::GetMCode (INT_PTR hObjs)
{
CObjectsFeaturesMap::iterator it = m_ConnProps.find (hObjs);

	if (it != m_ConnProps.end()) 
		return (*it).second.first;

	return NULL;
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

set<INT_PTR> MCodes;

	for (CObjectsFeaturesMap::iterator it = m_ConnProps.begin(); it != m_ConnProps.end(); ++it) 
		MCodes.insert ((*it).second.first);

// derzeitigen Langtext besorgen
PBDMERKMAL pbdData;
char cbBuffer[_MAX_PATH];

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdKText = NULL;
	pbdData.pbdLText = cbBuffer;
	pbdData.pbdKTextLen = 0;
	pbdData.pbdLTextLen = sizeof(cbBuffer);

// alles zurückschreiben
CPropertyName PName (pcBuffer);

	SetName (pcBuffer);

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdKText = (char *)PName.GetName().c_str();	// neuer Name
	pbdData.pbdKTextLen = (NULL != pcBuffer) ? PName.GetName().length() : 0;
	pbdData.ipbdMTyp = iMTyp;
	pbdData.ipbdMTyp = iMLen;

	for (set<INT_PTR>::iterator itm = MCodes.begin(); itm != MCodes.end(); ++itm) {
	// PBD-Info setzen
		pbdData.pbdCode = *itm;
		DEX_ModPBDData(pbdData);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Langtext setzen
STDMETHODIMP CObjPropMerkmal::SetHelpInfo (LPCSTR pcBuffer, LPCSTR pHelpFile, ULONG ulHelpCtx)
{
ErrInstall EI (WC_NOMERKMAL);
short iMTyp = 0;
short iMLen = 0;

	GetParams (iMLen, iMTyp);

set<INT_PTR> MCodes;

	for (CObjectsFeaturesMap::iterator it = m_ConnProps.begin(); it != m_ConnProps.end(); ++it) 
		MCodes.insert ((*it).second.first);

PBDMERKMAL pbdData;

	INITSTRUCT(pbdData, PBDDATA);
	pbdData.pbdTyp = 'm';
	pbdData.pbdKText = const_cast<char *>(m_strName.c_str());
	pbdData.pbdLText = const_cast<char *>(pcBuffer);
	pbdData.pbdKTextLen = m_strName.size();
	pbdData.pbdLTextLen = (NULL != pcBuffer) ? strlen(pcBuffer) : 0;
	pbdData.ipbdMTyp = iMTyp;
	pbdData.ipbdMTyp = iMLen;

	for (set<INT_PTR>::iterator itm = MCodes.begin(); itm != MCodes.end(); ++itm) {
	// PBD-Info setzen
		pbdData.pbdCode = *itm;
		DEX_ModPBDData(pbdData);
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// *** IPropertyInfo2 specific functions 
STDMETHODIMP CObjPropMerkmal::GetConfigData (VARIANT *pvOptData)
{
	if (NULL == pvOptData) return E_POINTER;

	V_VT(pvOptData) = VT_ERROR;
	V_I4(pvOptData) = DISP_E_PARAMNOTFOUND;

	TX_ASSERT(FALSE);		// obsolete: do not use anymore
	return S_OK;
}

STDMETHODIMP CObjPropMerkmal::GetConfigDataEx (INT_PTR hObjs, VARIANT *pvOptData)
{
	if (NULL == pvOptData) return E_POINTER;

	V_VT(pvOptData) = VT_I4;
	V_I4(pvOptData) = GetMCode(hObjs);

	return S_OK;
}

STDMETHODIMP CObjPropMerkmal::EvaluatesForClass (INT_PTR hObjs)
{
	COM_TRY {
	WTRiASObjectHandleMap Map (CLSID_TRiASObjectsHandleMap);
	WTRiASObjects Objs;

		THROW_FAILED_HRESULT(Map -> GetObject (hObjs, Objs.ppu()));

	WTRiASFeatures Feats;
	WTRiASFeature Feat;

		THROW_FAILED_HRESULT(Objs -> get_Features (Feats.ppi()));
		if (FAILED(Feats -> Item (CComVariant(GetMCode(hObjs)), Feat.ppi())))
			return S_FALSE;		// gehört nicht zu der gegebenen Objektklasse

	} COM_CATCH;
	return S_OK;		// ghört zur angegebenen Objektklasse
}

STDMETHODIMP CObjPropMerkmal::GetPropInfoEx (INT_PTR hObjs, LPSTR pBuffer, WORD wLen, DWORD *pdwData)
{
// zuerst allgemeine Infos besorgen
	RETURN_FAILED_HRESULT(GetPropInfo (pBuffer, wLen, pdwData));

// Schreibschutz ist objektklassenspezifisch
CObjectsFeaturesMap::iterator it = m_ConnProps.find (hObjs);

	if (it != m_ConnProps.end()) {
		*pdwData &= ~PROPCAPS_NOTREADONLY;
		*pdwData |= (*it).second.second ? PROPCAPS_NONE : PROPCAPS_NOTREADONLY;
	}
	return S_OK;
}

// *** IPropertyInfo3 specific functions ***
STDMETHODIMP CObjPropMerkmal::GetEnumConfigData (IEnumLONG **ppIFeatures)
{
	if (NULL == ppIFeatures)
		return E_POINTER;
	*ppIFeatures = NULL;

	COM_TRY {
	WEnumObjectsByNumber MCodes(CLSID_EnumObjectsByNumber); // Enumerator generieren
	CObjectsFeaturesMap::iterator end = m_ConnProps.end();

		for (CObjectsFeaturesMap::iterator it = m_ConnProps.begin(); it != end; ++it)
		{
			MCodes->AddItem ((*it).second.first);
		}
		THROW_FAILED_HRESULT(MCodes->QueryInterface(ppIFeatures));

	} COM_CATCH;
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
		if (rgFlags & SEARCHMODE_PARTIALMATCH)
			iMode = SMSubRegularExpression;
		else
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

	case SMExistanceOnly:
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
	case SMSubRegularExpression:
		hr = E_NOTIMPL;	// not impl (yet)
		break;
	}
	return hr;
}

extern "C" 
BOOL CALLBACK SearchObjectsMCode (long lONr, BOOL, void *pData)
{
IEnumObjectsByNumber* pIEnum = reinterpret_cast<IEnumObjectsByNumber *>(pData);

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

	// für alle MCodes jeweils einmal recherchieren
	set<INT_PTR> MCodes;
	WEnumObjectsByNumber IObjs (CLSID_EnumObjectsByNumber); // Enumerator generieren

		for (CObjectsFeaturesMap::iterator it = m_ConnProps.begin(); 
			 it != m_ConnProps.end(); 
			 ++it) 
		{
			MCodes.insert ((*it).second.first);
		}

	ENUMRECHTEXTMERKMALEX ERT;

		INITSTRUCT(ERT, ENUMRECHTEXTMERKMALEX);
		ERT.pMWert = OLE2A(bstrToMatch);
		ERT.iMode = ModeFromSearchMode(rgFlags) | SMActViewOnly;
		ERT.eFcn = reinterpret_cast<RECHTEXTMERKMALCALLBACK>(SearchObjectsMCode);
		ERT.pData = static_cast<IEnumObjectsByNumber *>(IObjs);

		for (set<INT_PTR>::iterator itm = MCodes.begin(); 
			 itm != MCodes.end() && !ERT.fFilteredColl; 
			 ++itm) 
		{
			ERT.lMCode = *itm;
			DEX_EnumRechTextMerkmal(ERT); 
		}
		*ppvObj = IObjs.detach();

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	} 

	return S_OK;
}

