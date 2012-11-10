// @doc 
// @module TRiASDataServerRegEntries.cpp | Implementation of the <c CTRiASDataServerRegEntries> class

#include "stdafx.h"

#include <comcat.h>

#include "Strings.h"

#include "TRiASDataServerRegEntry.h"
#include "TRiASDataServerRegEntries.h"
#include "MakeEnumVariant.h"

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASDataServerRegEntries, CTRiASDataServerRegEntries)

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(CatInformation);
DefineSmartInterface(EnumGUID);
DefineSmartInterface(EnumString);
DefineSmartInterface(TRiASDataServerRegEntries);
DefineSmartInterface(TRiASDBEngine);

///////////////////////////////////////////////////////////////////////////////
// ComponentCategory
const CATID CATID_TRiASDBEngine = {0x079639C6,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};
const CLSID CLSID_CatSimpleCache = {0xEA68A685,0x5166,0x4E55,{0x90,0x62,0x0B,0x13,0x06,0x81,0x33,0x93}};

///////////////////////////////////////////////////////////////////////////////
// CTRiASDataServerRegEntries

STDMETHODIMP CTRiASDataServerRegEntries::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASDataServerRegEntries,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CTRiASDataServerRegEntries::get_Count(LONG * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntries::get_Count");

	*pVal = m_Enum -> Count();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Methods

STDMETHODIMP CTRiASDataServerRegEntries::Item(VARIANT Which, ITRiASDataServerRegEntry **ppIEntry)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEntry) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntries::Item");

CComVariant vIndex;
bool fFound = false;
WEnumWTRiASDataServerRegEntry Enum;
WTRiASDataServerRegEntry Entry;

// Verhindern, daß als Nummern als Zeichenkette falsch interpretiert werden
	*ppIEntry = NULL;
	if (VT_BSTR != V_VT(&Which) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Which))) {
		if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > m_Enum -> Count())
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntries::Item");

	// Index ist eine Zahl
		COM_TRY {
			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(Enum -> Reset());

			if (V_I4(&vIndex) > 1)
			{
				THROW_FAILED_HRESULT(Enum -> Skip (V_I4(&vIndex)-1));
			}
			if (S_OK == Enum -> Next (1, &Entry, NULL))
			{
				*ppIEntry = Entry.detach();
				fFound = true;
			}

		} COM_CATCH;

	} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Which))) {
	// Index ist Name der Property
		COM_TRY {
			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Entry, NULL); /**/)
			{
			CComBSTR bstr;

				THROW_FAILED_HRESULT(Entry -> get_ShortName (CLEARED(&bstr)));
				if (!wcscmp (bstr, V_BSTR(&vIndex))) {
					*ppIEntry = Entry.detach();
					fFound = true;
					break;
				}
			}

		} COM_CATCH;

	} else 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntries::Item");

	if (!fFound)
		return REPORT_DBERROR(TRIASDB_E_UNKNOWN_DATASERVER);

	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntries::FindFromServerProgID(BSTR bstrProgID, ITRiASDataServerRegEntry **ppIEntry)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEntry) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntries::FindFromServerProgID");

bool fFound = false;

	*ppIEntry = NULL;
	COM_TRY {
	WEnumWTRiASDataServerRegEntry Enum;
	WTRiASDataServerRegEntry Entry;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &Entry, NULL); /**/)
		{
		CComBSTR bstr;

			THROW_FAILED_HRESULT(Entry -> get_DataServerClass (CLEARED(&bstr)));
			if (!wcscmp (bstr, bstrProgID)) {
				*ppIEntry = Entry.detach();
				fFound = true;
				break;
			}
		}

	} COM_CATCH;

	if (!fFound)
		return REPORT_DBERROR(TRIASDB_E_UNKNOWN_DATASERVER);

	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntries::_NewEnum(IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEnum) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntries::_NewEnum");

	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

STDMETHODIMP CTRiASDataServerRegEntries::_Clone(ITRiASDataServerRegEntries **ppIEntries)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEntries) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntries::_Clone");

// Da dieser Enumerator genau einmal erzeugt wird (singleton-classfactory), 
// wird hier lediglich das aktuelle Objekt AddRef'ed und zurückgeliefert.
	COM_TRY {
	WTRiASDataServerRegEntries Entries (GetUnknown());

		*ppIEntries = Entries.detach();

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntries::Refresh()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
	WEnumWTRiASDataServerRegEntry Enum;

		THROW_FAILED_HRESULT(CreateNewEnum (Enum.ppi()));
		THROW_FAILED_HRESULT(FillWithServerEntries (Enum));

		m_Enum = Enum;		// neuer Enumerator

	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen

HRESULT CTRiASDataServerRegEntries::FillWithServerEntries (IEnum<WTRiASDataServerRegEntry> *pIEnum)
{
// DBEngines über CATID enumerieren
BOOL fNotEmpty = FALSE;

	COM_TRY {
	WEnumGUID EnumGuids;		// Enumerator der DBEngine-Objekte
	WCatInformation CatInfo (CLSID_CatSimpleCache);	// throws hr
	GUID guidImpl[1]; 

		guidImpl[0] = CATID_TRiASDBEngine;
		THROW_FAILED_HRESULT(CatInfo -> EnumClassesOfCategories (1, guidImpl, 0, NULL, EnumGuids.ppi()));

	GUID guid;

		for (EnumGuids -> Reset(); S_OK == EnumGuids -> Next (1, &guid, NULL); /**/)
		{
			if (SUCCEEDED(InitDataServers (guid, pIEnum)))		// Fehler nicht fatal
				fNotEmpty = TRUE;
		}

	} COM_CATCH;

	return fNotEmpty ? S_OK : S_FALSE;
}

HRESULT CTRiASDataServerRegEntries::InitDataServers (REFGUID rGuid, IEnum<WTRiASDataServerRegEntry> *pIEnum)
{
LPOLESTR poleStr = NULL;

	USES_CONVERSION;

	COM_TRY {
	// DBEngine instantiieren und nach EnumString fragen
	WTRiASDBEngine DBEng;
	
		if (FAILED(DBEng.CreateInstance(rGuid)))
			return S_FALSE;	// registriert, aber nicht instantiierbar

	WUnknown Unk;
	WEnumString EnumStr;
	HRESULT hr = S_OK, hr_global = HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);
	bool fFound = false;

		if (FAILED(hr = DBEng -> EnumDataBaseTypes (Unk.ppi())))
			return hr;

		EnumStr = Unk;				// throws hr
		for (EnumStr -> Reset(); S_OK == EnumStr -> Next (1, &poleStr, NULL); /**/)
		{
		WTRiASDataServerRegEntry Entry;

			hr = InitDataServer(OLE2A(poleStr), Entry.ppi());
			if (SUCCEEDED(hr)) {		// evtl. Fehler nicht fatal
				THROW_FAILED_HRESULT(pIEnum -> AddItem (Entry));
				fFound = true;
			} else
				hr_global = hr;

			CoTaskMemFree (poleStr);
			poleStr = NULL;
		}

	// wenn nicht wenigstens einer gültig ist, dann mit Fehler raus
		if (!fFound) 
			return hr_global;		// liefert den letzten der FehlerCodes

	} COM_CATCH_OP(CoTaskMemFree (poleStr));
	
	return S_OK;
}

HRESULT CTRiASDataServerRegEntries::InitDataServer (LPCSTR pcProgID, ITRiASDataServerRegEntry **ppIEntry)
{
	if (NULL == ppIEntry) return E_POINTER;

	COM_TRY {
	// neuen ServerEntry erzeugen
	CComObject<CTRiASDataServerRegEntry> *pEntry = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASDataServerRegEntry>::CreateInstance (&pEntry));

	WTRiASDataServerRegEntry Entry (pEntry);	// pending AddRef

		THROW_FAILED_HRESULT(pEntry -> InitFromRegistry (pcProgID));
		*ppIEntry = Entry.detach();

	} COM_CATCH;

	return S_OK;
}

