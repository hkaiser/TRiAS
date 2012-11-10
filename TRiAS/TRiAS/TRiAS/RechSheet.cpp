// PropertySheet für RecherchePages 
// File: RechSheet.cpp

#include "triaspre.hxx"

#if !defined(_USE_XML_GEOCOMPONENTS)

#include <new>		// bad_alloc

#include <xtsnguid.h>
#include <ipropseq.hxx>
#include <selidprp.h>
#include <dstobwnd.h>
#include <SrChoice.h>
#include <propguid.h>
#include <gentguid.h>
#include <TextReplacePrp.h>
#include <clsfyprp.h>

#include "triasres.h"
#include "strings.h"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// Verwendete SmartInterfaces
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(PropertyAction);
DefineSmartInterface(PersistStreamInit);

///////////////////////////////////////////////////////////////////////////////
// Helperroutinen
HRESULT LoadSearchEngine (IPropertyActionSequence *pISeq, LPCSTR pcKey)
{
// ClassID aus Registry besorgen
CLSID clsID;
HRESULT hr = CLSIDFromProgID (WideString(pcKey), &clsID);

	if (FAILED(hr)) return hr;		// nichts gefunden

	COM_TRY {
	// Objekt instantiieren
	WPropertyAction WAct (clsID);		// throws hr

	// Objekt initialisieren
		{
		WPersistStreamInit Init (WAct);	// throws hr;
		HRESULT hr = Init -> InitNew();

			if (FAILED(hr)) {
				if (hr != E_ABORT)
					return hr;
				return S_FALSE;			// darf mit E_ABORT fehlschlagen
			}
		}
		
	// zur Sequence hinzufügen
		THROW_FAILED_HRESULT(pISeq -> AddAction (WAct));
		
	} COM_CATCH;
	return S_OK;
}

HRESULT AddSearchEngines (IPropertyActionSequence *pISeq)
{
// Key zusammenbauen
string strKey = string(g_cbAppKey) + g_cbDel + g_cbSearchSubKey;

// Registrierte Pages enumerieren
HKEY hKey = NULL;
DWORD i = 0, dwCnt = 0;
char cbEnumKey[_MAX_PATH];
DWORD retCode = RegOpenKeyEx (HKEY_CLASSES_ROOT, strKey.c_str(), 0L, KEY_READ, &hKey);

	if (retCode == ERROR_SUCCESS) {
	// alle registrierten Einträge durchgehen
		while (RegEnumKey (hKey, i, cbEnumKey, _MAX_PATH) == ERROR_SUCCESS) {
			if (SUCCEEDED(LoadSearchEngine (pISeq, cbEnumKey)))	// evtl. Fehler ignorieren
				dwCnt++;
			i++;
		}

	// Schlüssel wieder abschließen
		RegCloseKey (hKey);   // Close the key handle.
	}

	if (0 == dwCnt) {
	// keine registrierten SearchEngines gefunden
		VMessageBox (NULL, FakeTRiASName(IDS_BADREGISTRATION_CAP, g_cbTRiAS).c_str(), 
			ExclamationIcon|OkayButton, IDS_BADREGISTRATION, g_cbTRiAS);
		return E_FAIL;
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// RechercheDialog
static const CLSID *cbRechClsIds[] = 
{
	&CLSID_SelectIdentObjTyp,
	NULL,
	&CLSID_DestinationObjectWindow,
};
static const CLSID *cbRechObjWnd[] = 
{
	&CLSID_SelectFromObjectWindow,
	NULL,
	&CLSID_DestinationObjectWindow,
};
static const IPropertyAction *cbRechPropActs[] = 
{
	NULL,
	NULL,
	NULL,
};

static CALPCLSID calRechClsIds = 
{
	_countof(cbRechClsIds),
	cbRechClsIds,
	(const IUnknown **)cbRechPropActs,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};
static CALPCLSID calRechObjWnd = 
{
	_countof(cbRechObjWnd),
	cbRechObjWnd,
	(const IUnknown **)cbRechPropActs,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool TextRecherche (HWND hWnd, bool fORWnd) 
{
	TX_ASSERT(_countof(cbRechClsIds) == _countof(cbRechPropActs));
	TX_ASSERT(_countof(cbRechObjWnd) == _countof(cbRechPropActs));

// RecherchePages zu PropertyChoice zusammenfügen
	COM_TRY {
	WPropertyActionSequence Choice (CLSID_PropertyChoice);
	
		THROW_FAILED_HRESULT(AddSearchEngines (Choice));

	WPropertyAction Action (Choice);	// throws hr
		
		cbRechPropActs[1] = Action;
	
	// gesamte Sequence erzeugen und abarbeiten
	HRESULT hr = S_OK;

		if (!fORWnd) {
		ResString resCap (IDS_SEARCHCAP, 128);
			
			hr = RunPropertyActionSequence (hWnd, resCap, &calRechClsIds, NULL, NULL, NULL);

		} else {
		ResString resCap (IDS_SEARCHCAP_OR, 128);
		
			hr = RunPropertyActionSequence (hWnd, resCap, &calRechObjWnd, NULL, NULL, NULL);
		}
		if (hr == E_ABORT)
			return false;
		THROW_FAILED_HRESULT(hr);

	} COM_CATCH_RETURN(false);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Suchen und ersetzen
static const CLSID *cbReplaceClsIds[] = 
{
	&CLSID_SelectIdentObjTyp,
	&CLSID_TextReplaceEngine,
	&CLSID_DestinationObjectWindow,
};
static const CLSID *cbReplaceObjWnd[] = 
{
	&CLSID_SelectFromObjectWindow,
	&CLSID_TextReplaceEngine,
	&CLSID_DestinationObjectWindow,
};

static CALPCLSID calReplaceClsIds = 
{
	_countof(cbReplaceClsIds),
	cbReplaceClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};
static CALPCLSID calReplaceObjWnd = 
{
	_countof(cbReplaceObjWnd),
	cbReplaceObjWnd,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool TextReplace (HWND hWnd, bool fORWnd) 
{
// RecherchePages zu PropertyChoice zusammenfügen
	COM_TRY {
	// gesamte Sequence erzeugen und abarbeiten
	HRESULT hr = S_OK;

		if (!fORWnd) {
		ResString resCap (IDS_REPLACECAP, 128);
			
			hr = RunPropertyActionSequence (hWnd, resCap, &calReplaceClsIds, NULL, NULL, NULL);

		} else {
		ResString resCap (IDS_REPLACECAP_OR, 128);
		
			hr = RunPropertyActionSequence (hWnd, resCap, &calReplaceObjWnd, NULL, NULL, NULL);
		}
		if (hr == E_ABORT)
			return false;
		THROW_FAILED_HRESULT(hr);

	} COM_CATCH_RETURN(false);
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// Klassifikation
static const CLSID *cbClassifyClsIds[] = 
{
	&CLSID_SelectIdentObjTyp,
	&CLSID_ClassifyByObjProp,
	&CLSID_DestinationObjectWindow,
};
static const CLSID *cbClassifyObjWnd[] = 
{
	&CLSID_SelectFromObjectWindow,
	&CLSID_ClassifyByObjProp,
	&CLSID_DestinationObjectWindow,
};

static CALPCLSID calClassifyClsIds = 
{
	_countof(cbClassifyClsIds),
	cbClassifyClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};
static CALPCLSID calClassifyObjWnd = 
{
	_countof(cbClassifyObjWnd),
	cbClassifyObjWnd,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool ClassifyObjects (HWND hWnd, bool fORWnd) 
{
// RecherchePages zu PropertyChoice zusammenfügen
	COM_TRY {
	// gesamte Sequence erzeugen und abarbeiten
	HRESULT hr = S_OK;

		if (!fORWnd) {
		ResString resCap (IDS_CLASSIFYCAP, 128);
			
			hr = RunPropertyActionSequence (hWnd, resCap, &calClassifyClsIds, NULL, NULL, NULL);

		} else {
		ResString resCap (IDS_CLASSIFYCAP_OR, 128);
		
			hr = RunPropertyActionSequence (hWnd, resCap, &calClassifyObjWnd, NULL, NULL, NULL);
		}
		if (hr == E_ABORT)
			return false;
		THROW_FAILED_HRESULT(hr);

	} COM_CATCH_RETURN(false);
	return true;
}

/////////////////////////////////////////////////////////////////////////////
// Textobjekte erzeugen
static const CLSID *cbGenTextClsIds[] = 
{
	&CLSID_SelectIdentObjTyp,
	&CLSID_GenTextPropAct,
	&CLSID_ModifyIdent,
	&CLSID_DestinationObjectWindow,
};
static const CLSID *cbGenTextObjWnd[] = 
{
	&CLSID_SelectFromObjectWindow,
	&CLSID_GenTextPropAct,
	&CLSID_ModifyIdent,
	&CLSID_DestinationObjectWindow,
};

static CALPCLSID calGenTextClsIds = 
{
	_countof(cbGenTextClsIds),
	cbGenTextClsIds,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};
static CALPCLSID calGenTextObjWnd = 
{
	_countof(cbGenTextObjWnd),
	cbGenTextObjWnd,
	NULL,
#if !defined(_TRIAS_OLDIMPLEMTATION1)
	NULL,
#endif // _TRIAS_OLDIMPLEMTATION1
};

bool GenerateTextObjects (HWND hWnd, bool fORWnd) 
{
// RecherchePages zu PropertyChoice zusammenfügen
	COM_TRY {
	// gesamte Sequence erzeugen und abarbeiten
	HRESULT hr = E_FAIL;

		if (!fORWnd) {
		ResString resCap (IDS_GENERATETEXT, 128);

			hr = RunPropertyActionSequence (hWnd, resCap, 
							 &calGenTextClsIds, NULL, NULL, NULL);
		} else {
		ResString resCap (IDS_GENERATETEXT_OR, 128);

			hr = RunPropertyActionSequence (hWnd, resCap, 
							 &calGenTextObjWnd, NULL, NULL, NULL);
		}
		if (hr == E_ABORT)
			return false;
		THROW_FAILED_HRESULT(hr);

	} COM_CATCH_RETURN(false);
	return true;
}

#endif // !defined(_USE_XML_GEOCOMPONENTS)

