///////////////////////////////////////////////////////////////////////////////
// PropActSeq.cpp: Support for PropertyActionSequences

#include "precomp.hxx"

#include <dirisole.h>
#include <xtsnguid.h>
#include <srchoice.h>
#include <ipropseq.hxx>

#include <propactn.h>

#include "GlobalFuncs.h"
#include "jumptab.h"
#include "olebsext.hxx"			// function  prototypes

#include <Com/PropertyActionBaseDataImpl.cpp>

#if defined(_DEBUG) && defined(WIN32)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// benötigte Guids
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_PropertyActionJoin = {0xD041DB48,0x4A2F,0x4567,{0x80,0xE9,0x7C,0x42,0x85,0x12,0xB5,0xD1}};
EXTERN_C const CLSID DECLSPEC_SELECTANY CLSID_PropertyActionSplit = {0x52E25FEE,0xD9C8,0x4B3C,{0xAD,0x5A,0x04,0x7E,0xB9,0x2D,0x7D,0x60}};

///////////////////////////////////////////////////////////////////////////////
// benötige Interfaces
DefineSmartInterface(EnumLONG);
DefineSmartInterface(DataObject);
DefineSmartInterface(PropertyAction);
DefineSmartInterface(PropertyAction2);
DefineSmartInterface(PropertyActionSequence);
DefineSmartInterface(Storage);
DefineSmartInterface(Stream);
DefineSmartInterface(PersistStream);
DefineSmartInterface(PersistStreamInit);

///////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen
CComVariant MakeVARIANT (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs, int iArg);

///////////////////////////////////////////////////////////////////////////////
// globale Strings
const TCHAR g_cbPropertySequences[] = TEXT("PropertySequences");

// ----------------------------------------------------------------------------
// PropertySequence_refcnt
// ----------------------------------------------------------------------------
void PropertySequence_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(PropertySequence_refcnt);
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle
			try {
			WPropertyActionSequence PropSeq (CLSID_PropertyActionSequence);		// throws hr
			HPROJECT hPrCtx = reinterpret_cast<HPROJECT>(ebThread_GetLong (hThread, SETLONG_HPROJECT));		// Kontext-Datenquelle

				ebSetObject (lpArgs, 0, (DWORD)PropSeq.detach());
				if (HACTCONNECTION != hPrCtx) {
				WDataObject CtxDO;
				CComVariant vData (reinterpret_cast<long>(hPrCtx), VT_I4);

					THROW_FAILED_HRESULT(PropSeq -> GetSequenceContext (CtxDO.ppi()));
					THROW_FAILED_HRESULT(SetVariantData (vData, CtxDO, &c_feDataSourceHandle));
				}

			} catch (...) {
				TRACE("Couldn't instantiate PropertyActionSequence\r\n");
			}
		}
		break;
		
	case OBJECT_REFINC:
		((IUnknown *)ebGetObject(lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((IUnknown *)ebGetObject(lpArgs, 1)) -> Release();
		break;
	}
}

// ----------------------------------------------------------------------------
// PropertyChoice_refcnt
// ----------------------------------------------------------------------------
void PropertyChoice_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(PropertyChoice_refcnt);
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle
			try {
			WPropertyActionSequence PropSeq (CLSID_PropertyChoice);				// throws hr
			HPROJECT hPrCtx = reinterpret_cast<HPROJECT>(ebThread_GetLong (hThread, SETLONG_HPROJECT));		// Kontext-Datenquelle

				ebSetObject (lpArgs, 0, (DWORD)PropSeq.detach());
				if (HACTCONNECTION != hPrCtx) {
				WDataObject CtxDO;
				CComVariant vData (reinterpret_cast<long>(hPrCtx), VT_I4);

					if (SUCCEEDED(PropSeq -> GetSequenceContext (CtxDO.ppi())))
					{
						THROW_FAILED_HRESULT(SetVariantData (vData, CtxDO, &c_feDataSourceHandle));
					}
				}

			} catch (...) {
				TRACE("Couldn't instantiate PropertyActionChoice\r\n");
			}
		}
		break;
		
	case OBJECT_REFINC:
		((IUnknown *)ebGetObject(lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((IUnknown *)ebGetObject(lpArgs, 1)) -> Release();
		break;
	}
}

// ----------------------------------------------------------------------------
// JoinPropertyActions_refcnt
// ----------------------------------------------------------------------------
void JoinPropertyActions_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(JoinPropertyActions_refcnt);
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle
			try {
			WPropertyActionSequence PropSeq (CLSID_PropertyActionJoin);				// throws hr
			HPROJECT hPrCtx = reinterpret_cast<HPROJECT>(ebThread_GetLong (hThread, SETLONG_HPROJECT));		// Kontext-Datenquelle

				ebSetObject (lpArgs, 0, (DWORD)PropSeq.detach());
				if (HACTCONNECTION != hPrCtx) {
				WDataObject CtxDO;
				CComVariant vData (reinterpret_cast<long>(hPrCtx), VT_I4);

					if (SUCCEEDED(PropSeq -> GetSequenceContext (CtxDO.ppi())))
					{
						THROW_FAILED_HRESULT(SetVariantData (vData, CtxDO, &c_feDataSourceHandle));
					}
				}

			} catch (...) {
				TRACE("Couldn't instantiate JoinPropertyActions\r\n");
			}
		}
		break;
		
	case OBJECT_REFINC:
		((IUnknown *)ebGetObject(lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((IUnknown *)ebGetObject(lpArgs, 1)) -> Release();
		break;
	}
}

// ----------------------------------------------------------------------------
// SplitPropertyActions_refcnt
// ----------------------------------------------------------------------------
void SplitPropertyActions_refcnt (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE_SYS(SplitPropertyActions_refcnt);
	switch (iNumArgs) {
	case OBJECT_REFNEW:
		{
			ebSetObject (lpArgs, 0, NULL);		// für alle Fälle
			try {
			WPropertyActionSequence PropSeq (CLSID_PropertyActionSplit);				// throws hr
			HPROJECT hPrCtx = reinterpret_cast<HPROJECT>(ebThread_GetLong (hThread, SETLONG_HPROJECT));		// Kontext-Datenquelle

				ebSetObject (lpArgs, 0, (DWORD)PropSeq.detach());
				if (HACTCONNECTION != hPrCtx) {
				WDataObject CtxDO;
				CComVariant vData (reinterpret_cast<long>(hPrCtx), VT_I4);

					if (SUCCEEDED(PropSeq -> GetSequenceContext (CtxDO.ppi())))
					{
						THROW_FAILED_HRESULT(SetVariantData (vData, CtxDO, &c_feDataSourceHandle));
					}
				}

			} catch (...) {
				TRACE("Couldn't instantiate SplitPropertyActions\r\n");
			}
		}
		break;
		
	case OBJECT_REFINC:
		((IUnknown *)ebGetObject(lpArgs, 1)) -> AddRef();
		break;
		
	case OBJECT_REFDEC:
		((IUnknown *)ebGetObject(lpArgs, 1)) -> Release();
		break;
	}
}

// ----------------------------------------------------------------------------
// PropertySequence_propget_Description
// ----------------------------------------------------------------------------
void PropertySequence_propget_Description (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_propget_Description);

WPropertyActionSequence Seq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));
char cbBuffer[_MAX_PATH];
ULONG ulWritten = 0;
HRESULT hr = Seq -> GetDescription (cbBuffer, _MAX_PATH, &ulWritten);

	if (FAILED(hr))	{
		ebSetString (lpArgs, 0, NULL);
		return;
	}
	ebSetString (lpArgs, 0, ebCreateString (hThread, cbBuffer));
}

// ----------------------------------------------------------------------------
// PropertySequence_propset_Description
// ----------------------------------------------------------------------------
void PropertySequence_propset_Description (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_propset_Description);

ebHSUB hStr = ebGetString (lpArgs, 2);

	if (NULL != hStr) {
	LPSTR lpstr = ebLockString (hThread, hStr);
	 
		((IPropertyActionSequence *)ebGetObject (lpArgs, 1)) -> SetDescription (lpstr);
		BASIC_OP_TRACE2(lpstr);
		ebUnlockString (hThread, hStr);
	}
}

// ----------------------------------------------------------------------------
// PropertySequence_cmd_AddAction
// ----------------------------------------------------------------------------

HRESULT InitFromData (IPropertyAction *pIAct, CComVariant &rv)
{
	try {
	// mit Daten aus 2. Parameter initialisieren
	WPropertyAction2 Init (pIAct);					// throws hr
	WDataObject Data (CLSID_DataTransferObject);	// throws hr
			
		THROW_FAILED_HRESULT(SetVariantData (rv, Data, &c_feInitPropAct));
		THROW_FAILED_HRESULT(Init -> InitFromData (Data, false, 0L));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return S_OK;
}

void PropertySequence_cmd_AddAction (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_cmd_AddAction);

WPropertyActionSequence Seq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));
ebHSUB hStr = ebGetString (lpArgs, 2);

	if (NULL != hStr) {
		USES_CONVERSION;

	LPSTR lpstr = ebLockString (hThread, hStr);

		BASIC_OP_TRACE2(lpstr);

	CLSID clsID;
	HRESULT hr = CLSIDFromString (A2OLE(lpstr), &clsID);

		if (FAILED(hr))
			hr = CLSIDFromProgID (A2OLE(lpstr), &clsID);

		if (SUCCEEDED(hr)) {
		CComVariant v2 (MakeVARIANT (hThread, iNumArgs, lpArgs, 3));

			if (VT_ERROR == V_VT(&v2)) {
			// nur ein Parameter gegeben
			CALPCLSID cal;
			const CLSID *pClsID = &clsID;

				memset(&cal, '\0', sizeof(CALPCLSID));
				cal.cElems = 1;
				cal.ppElems = &pClsID;
				Seq -> AddActionsByCLSID (&cal);
			
			} else {
			// 2. Parameter auswerten
				try {
				WPropertyAction WAct (clsID);	// throws hr

					if (FAILED(InitFromData (WAct, v2))) {
					// kann nicht mit Daten initialisiert werden, also normales Init
					WPersistStreamInit Init (WAct);			// throws hr

						THROW_FAILED_HRESULT(Init -> InitNew());
					}

					THROW_FAILED_HRESULT(Seq -> AddAction (WAct));

				} catch (_com_error&) {
					;
				}
			}
		}
		ebUnlockString (hThread, hStr);
	}
}

// ----------------------------------------------------------------------------
// PropertySequence_cmd_AddActionSequence
// ----------------------------------------------------------------------------
void PropertySequence_cmd_AddActionSequence (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_cmd_AddActionSequence);

WPropertyActionSequence Seq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));

	try {
	WPropertyAction SeqSub ((IPropertyActionSequence *)ebGetObject (lpArgs, 2));	// throw hr

		Seq -> AddAction (SeqSub);
	} catch (_com_error&) {
		;
	}
}

// ----------------------------------------------------------------------------
// PropertySequence_func_DoActions
// ----------------------------------------------------------------------------
void PropertySequence_func_DoActions (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_func_DoActions);

	ebSetObject (lpArgs, 0, (DWORD)NULL);

WPropertyActionSequence Seq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));
WDataObject InData, OutData;
_DGeoObjects *pIObjs = iNumArgs > 1 ? (_DGeoObjects *)ebGetObject (lpArgs, 2) : NULL;
HRESULT hr = NOERROR;

	if (NULL != pIObjs) {
	WEnumLONG EnumObjs;

		hr = GetEnumLongFromGeoObjects (pIObjs, EnumObjs.ppi());
		if (SUCCEEDED(hr)) {
			hr = CoCreateInstance (CLSID_DataTransferObject, NULL, CLSCTX_INPROC_SERVER, 
								   IID_IDataObject, InData.ppv());
			if (SUCCEEDED(hr))
				hr = SetEnumLONGData (EnumObjs, InData);
			else
				InData.Assign (NULL);		// freigeben
		}
		pIObjs = NULL;		// wird nicht mehr benötigt
	}

	hr = Seq -> DoActions (__hWndM, NULL, InData, OutData.ppi());
	if (SUCCEEDED(hr)) {
	WEnumLONG EnumObjs;

		if (NULL != (IUnknown *)OutData)
			hr = GetEnumLONGData (OutData, EnumObjs.ppi());
		if (SUCCEEDED(hr))		// jetzt Collection der GeoObjects generieren
			hr = GetGeoObjectsFromEnumlong (EnumObjs, &pIObjs);
	}

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)pIObjs);
}

// ----------------------------------------------------------------------------
// PropertySequence_cmd_DoActions
// ----------------------------------------------------------------------------
void PropertySequence_cmd_DoActions (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_cmd_DoActions);

WPropertyActionSequence Seq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));
WDataObject InData;
_DGeoObjects *pIObjs = iNumArgs > 1 ? (_DGeoObjects *)ebGetObject (lpArgs, 2) : NULL;
HRESULT hr = NOERROR;

	if (NULL != pIObjs) {
	WEnumLONG EnumObjs;

		hr = GetEnumLongFromGeoObjects (pIObjs, EnumObjs.ppi());
		if (SUCCEEDED(hr)) {
			hr = CoCreateInstance (CLSID_DataTransferObject, NULL, CLSCTX_INPROC_SERVER, 
								   IID_IDataObject, InData.ppv());
			if (SUCCEEDED(hr))
				hr = SetEnumLONGData (EnumObjs, InData);
			else
				InData.Assign (NULL);		// freigeben
		}
		pIObjs = NULL;		// wird nicht mehr benötigt
	}

	Seq -> DoActions (__hWndM, NULL, InData, NULL);
}

// ----------------------------------------------------------------------------
// PropertySequence_func_RedoActions
// ----------------------------------------------------------------------------
void PropertySequence_func_RedoActions (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_func_RedoActions);

	ebSetObject (lpArgs, 0, (DWORD)NULL);

WPropertyActionSequence Seq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));
WDataObject InData, OutData;
_DGeoObjects *pIObjs = iNumArgs > 1 ? (_DGeoObjects *)ebGetObject (lpArgs, 2) : NULL;
HRESULT hr = NOERROR;

	if (NULL != pIObjs) {
	WEnumLONG EnumObjs;

		hr = GetEnumLongFromGeoObjects (pIObjs, EnumObjs.ppi());
		if (SUCCEEDED(hr)) {
			hr = CoCreateInstance (CLSID_DataTransferObject, NULL, CLSCTX_INPROC_SERVER, 
								   IID_IDataObject, InData.ppv());
			if (SUCCEEDED(hr))
				hr = SetEnumLONGData (EnumObjs, InData);
			else
				InData.Assign (NULL);		// freigeben
		}
		pIObjs = NULL;		// wird nicht mehr benötigt
	}

	hr = Seq -> RedoActions (__hWndM, NULL, InData, OutData.ppi());
	if (SUCCEEDED(hr)) {
	WEnumLONG EnumObjs;

		if (NULL != (IUnknown *)OutData)
			hr = GetEnumLONGData (OutData, EnumObjs.ppi());
		if (SUCCEEDED(hr))		// jetzt Collection der GeoObjects generieren
			hr = GetGeoObjectsFromEnumlong (EnumObjs, &pIObjs);
	}

	if (SUCCEEDED(hr))
		ebSetObject (lpArgs, 0, (DWORD)pIObjs);
}

// ----------------------------------------------------------------------------
// PropertySequence_cmd_RedoActions
// ----------------------------------------------------------------------------
void PropertySequence_cmd_RedoActions (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_cmd_RedoActions);

WPropertyActionSequence Seq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));
WDataObject InData;
_DGeoObjects *pIObjs = iNumArgs > 1 ? (_DGeoObjects *)ebGetObject (lpArgs, 2) : NULL;
HRESULT hr = NOERROR;

	if (NULL != pIObjs) {
	WEnumLONG EnumObjs;

		hr = GetEnumLongFromGeoObjects (pIObjs, EnumObjs.ppi());
		if (SUCCEEDED(hr)) {
			hr = CoCreateInstance (CLSID_DataTransferObject, NULL, CLSCTX_INPROC_SERVER, 
								   IID_IDataObject, InData.ppv());
			if (SUCCEEDED(hr))
				hr = SetEnumLONGData (EnumObjs, InData);
			else
				InData.Assign (NULL);		// freigeben
		}
		pIObjs = NULL;		// wird nicht mehr benötigt
	}

	Seq -> RedoActions (__hWndM, NULL, InData, NULL);
}

///////////////////////////////////////////////////////////////////////////////
// Konvertieren eines PropAct-Bezeichners in einen Stream-Namen
static string MakeStreamName (LPCSTR pcDesc)
{
char str[32];

	for (int i = 0; i < sizeof(str); i++) {
	char c = pcDesc[i];

		switch (c) {
		case '.':
		case '\\':
		case '/':
		case ':':
		case '!':
			str[i] = '_';
			break;

		case '\0':
			str[i] = '\0';
			return string(str);		// Ende der Vorstellung

		default:
			if (c > ' ')
				str[i] = c;
			else
				str[i] = '_';
			break;
		}
	}

	return string(str);
}

// Öffnen des PropertySequenceSubStorages
static HRESULT GetSubPropSeqStorage (IStorage **ppIStg, bool fCreate = false)
{
	if (NULL == ppIStg) return E_POINTER;

WStorage IRootStg;

	if (!DEX_GetProjectStorage(*IRootStg.ppv()))
		return E_FAIL;

	USES_CONVERSION;

WStorage IStg;
HRESULT hr = E_FAIL;

	{
	bool fRO = false;

		hr = IRootStg -> OpenStorage (A2OLE(g_cbPropertySequences), NULL, 
							STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
							NULL, 0L, IStg.ppi());
		if (FAILED(hr)) {
			if (STG_E_FILENOTFOUND == GetScode(hr) && fCreate) {
			// existiert nicht, evtl. neu erzeugen
				hr = IRootStg -> CreateStorage (A2OLE(g_cbPropertySequences), 
									STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED|STGM_CREATE, 
									0L, 0L, IStg.ppi());
				if (SUCCEEDED(hr))
					hr = WriteClassStg (IStg, CLSID_PropertyActionSequence);
			
			} else if (STG_E_ACCESSDENIED == GetScode(hr)) {
			// mit Schreibschutz versuchen
				hr = IRootStg -> OpenStorage (A2OLE(g_cbPropertySequences), NULL, 
								STGM_READ|STGM_SHARE_EXCLUSIVE|STGM_TRANSACTED, 
								NULL, 0L, IStg.ppi());
				fRO = true;
			
			} else
				return hr;
		} 

		if (SUCCEEDED(hr)) {
		CLSID clsId;

			hr = ReadClassStg (IStg, &clsId);
			if (FAILED(hr)) return hr;

			if (!IsEqualCLSID(clsId, CLSID_PropertyActionSequence) && 
				!IsEqualCLSID(clsId, CLSID_NULL))
			{
				return E_FAIL;
			}

			if (IsEqualCLSID(clsId, CLSID_NULL) && !fRO)
				hr = WriteClassStg (IStg, CLSID_PropertyActionSequence);
		}
	}

	if (FAILED(hr)) return hr;

	*ppIStg = IStg.detach();

return hr;
}

// ----------------------------------------------------------------------------
// PropertySequence_cmd_Save
// ----------------------------------------------------------------------------
namespace {

template<class T>
inline HRESULT SaveData (IStream *pIStm, T &riVal)
{
	return pIStm -> Write (&riVal, sizeof(T), NULL);
}

	HRESULT SaveString (IStream *pIStm, os_string str)
	{
	long lCnt = str.size()+1;
	HRESULT hr = pIStm -> Write (&lCnt, sizeof(long), NULL);

		if (FAILED(hr)) return hr;

		return pIStm -> Write (str.c_str(), lCnt, NULL);
	}

}	// namespace

void PropertySequence_cmd_Save (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_cmd_Save);

	if (NULL != lpArgs[0]) // als Funktion gerufen
		ebSetBool (lpArgs, 0, 0);		// für alle Fälle

WPropertyActionSequence ISeq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));
HRESULT hr = E_FAIL;

// Versuchen aus SubStream einzulesen
	try {
	// SubStorage eröffnen/erzeugen
	WStorage IStg;

		hr = GetSubPropSeqStorage (IStg.ppi(), true);
		if (FAILED(hr)) _com_issue_error(hr);

	// Description geben lassen
	char cbBuffer[_MAX_PATH];

		hr = ISeq -> GetDescription (cbBuffer, _MAX_PATH, NULL);
		if (FAILED(hr)) _com_issue_error(hr);

	WStream IStm;
	WPersistStream IPersistStm (ISeq);		// throw hr
	string strName = MakeStreamName(cbBuffer);

	// Stream erzeugen
		USES_CONVERSION;
		hr = IStg -> CreateStream (A2OLE(strName.c_str()), 
						STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE, 
						0L, 0L, IStm.ppi());
		if (FAILED(hr)) _com_issue_error(hr);
		
		hr = OleSaveToStream (IPersistStm, IStm);
		if (FAILED(hr)) _com_issue_error(hr);
			
		hr = IStg -> Commit (STGC_DEFAULT);
		if (FAILED(hr)) _com_issue_error(hr);
		
		DEX_SetDirtyGeoDB(true);

	} catch (...) {
		TRACE("Couldn't OleSaveToStream for IPropertyActionSequence\n");
		return;			// Fehler
	}

	if (NULL != lpArgs[0]) // als Funktion gerufen
		ebSetBool (lpArgs, 0, -1);
}

// ----------------------------------------------------------------------------
// PropertySequence_cmd_Load
// ----------------------------------------------------------------------------
namespace {

	template<class T>
	inline HRESULT LoadData (IStream *pIStm, T &riVal)
	{
		return pIStm -> Read (&riVal, sizeof(T), NULL);
	}

	HRESULT LoadString (IStream *pIStm, os_string &rStr)
	{
	long lCnt = 0;
	HRESULT hr = pIStm -> Read (&lCnt, sizeof(long), NULL);

		if (FAILED(hr)) return hr;

	char cbBuffer[256];

		_ASSERTE(lCnt < sizeof(cbBuffer));
		hr = pIStm -> Read (cbBuffer, lCnt, NULL);
		if (FAILED(hr)) return hr;

		rStr = cbBuffer;
		return S_OK;
	}

}	// namespace

// vor dem SequenceStream zur Versionskontrolle mit dem XML Configfile
// ACHTUNG: mit propseq.hxx synchronisieren
#define PROPERTYSEQUENCE_VERSION_0100			0x0100
#define PROPERTYSEQUENCE_LASTKNOWNVERSION		PROPERTYSEQUENCE_VERSION_0100
#define PROPERTYSEQUENCE_MINORVERSIONMASK		0xff
#define PROPERTYSEQUENCE_SIGNATURE				0x53505250		// PRPS

void PropertySequence_cmd_Load (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_cmd_Load);

	ebSetBool (lpArgs, 0, 0);		// für alle Fälle

WPropertyActionSequence ISeq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));
HRESULT hr = E_FAIL;

// Versuchen aus SubStream einzulesen
	try {
	// SubStorage eröffnen
	WStorage IStg;

		hr = GetSubPropSeqStorage (IStg.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

	// Description wurde als Parameter übergeben
	string strDesc;
	ebHSUB hStr = ebGetString (lpArgs, 2);

		if (NULL != hStr) {
			strDesc = ebLockString (hThread, hStr);
			ebUnlockString (hThread, hStr);
		}
	 
	WStream IStm;
	string strName = MakeStreamName(strDesc.c_str());

	// Stream erzeugen
		USES_CONVERSION;
		hr = IStg -> OpenStream (A2OLE(strName.c_str()), NULL, 
						STGM_READ|STGM_SHARE_EXCLUSIVE, 0L, IStm.ppi());
		if (FAILED(hr)) _com_issue_error(hr);

	// ggf. XML-Version einlesen, testen nicht möglich

	// aktuelle Streamposition speichern
	LARGE_INTEGER liToPos;
	ULARGE_INTEGER liPos;

		liPos.QuadPart = liToPos.QuadPart = 0;
		if (FAILED(hr = IStm -> Seek(liToPos, STREAM_SEEK_CUR, &liPos)))
			_com_issue_error(hr);

	DWORD dwSignature = 0;
	DWORD dwVersion = 0;
	bool fMustReset = true;

		LoadData(IStm, dwSignature);
		if (dwSignature == PROPERTYSEQUENCE_SIGNATURE) {
			LoadData(IStm, dwVersion);
			if ((dwVersion & ~PROPERTYSEQUENCE_MINORVERSIONMASK) 
				<= PROPERTYSEQUENCE_LASTKNOWNVERSION)
			{
			// Versionsvergleich ist möglich (wird hier aber nicht gemacht)
			os_string strVersion;

				LoadString(IStm, strVersion);
				fMustReset = false;
			}
		}

		if (fMustReset) {
		// Stream zurückpositionieren, damit alte Streams geladen werden können
			liToPos.QuadPart = liPos.QuadPart;
			if (FAILED(hr = IStm -> Seek(liToPos, STREAM_SEEK_SET, NULL)))
				_com_issue_error(hr);
		}

	// anstelle von OleLoadFromStrem ::Load direkt rufen, da Objekt
	// schon existiert
	CLSID clsId;

		hr = ReadClassStm (IStm, &clsId);
		if (FAILED(hr)) _com_issue_error(hr);

		if (!IsEqualCLSID(clsId, CLSID_PropertyActionSequence) && 
			!IsEqualCLSID(clsId, CLSID_NULL))
		{
			_com_issue_error(E_FAIL);
		}

		{
		WPersistStream PersStm (ISeq);	// throws hr

			hr = PersStm -> Load (IStm);		// Objekt laden
			if (FAILED(hr)) _com_issue_error(hr);
		}

	} catch (...) {
		TRACE("Couldn't OleLoadFromStream for IPropertyActionSequence\n");
		return;			// Fehler
	}

	ebSetBool (lpArgs, 0, -1);
}

// ----------------------------------------------------------------------------
// PropertySequence_cmd_Init
// ----------------------------------------------------------------------------
void PropertySequence_cmd_Init (ebHTHREAD hThread, int iNumArgs, ebARGS lpArgs)
{
	BASIC_OP_TRACE(PropertySequence_cmd_Init);

// Rücksetzen der AktionsFolge
WPropertyActionSequence ISeq ((IPropertyActionSequence *)ebGetObject (lpArgs, 1));

	if (NULL != lpArgs[0])		// als Funktion gerufen
		ebSetBool (lpArgs, 0, 0);		// für alle Fälle
	
	try {
	WPersistStreamInit Init = ISeq;		// throws hr
	HRESULT hr = Init -> InitNew();

		if (FAILED(hr)) _com_issue_error(hr);
	
	} catch (...) {
		TRACE("Couldn't QI IPersistStreamInit from IPropertyActionSequence\n");
		return;			// Fehler
	}

	if (NULL != lpArgs[0])	// als Funktion gerufen
		ebSetBool (lpArgs, 0, -1);
}

