// @doc
// @module TRiASProperties.cpp | Implementation of <c CTRiASProperties>

#include "stdafx.h"

#include "Strings.h"
#include "Wrapper.h"

#include "TRiASProperties.h"
#include "MakeEnumVariant.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this class
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASProperties);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASProperties::Dump()
{
	return S_OK;
}
#endif // defined(_DUMP_PENDING_OBJECTS)

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASProperties, CTRiASProperties)

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_PERFINSTANCE_MAP
RT_PERFINSTANCEDATA_ENTRY(CTRiASProperties, g_cbCounts)

/////////////////////////////////////////////////////////////////////////////
// CTRiASProperties

STDMETHODIMP CTRiASProperties::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASProperties,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

void CTRiASProperties::FinalRelease()
{
// da während dem Freigeben der Properties diverse andere Objekte freigegeben werden 
// können, die ihrerseits u.U. wieder auf diese PropertyCollection zugreifen muß das 
// Freigeben etwas listiger vor sich gehen.
// eben nicht nur so:
//	m_Enum.Assign(NULL);

	COM_TRY {
	WTRiASProperty Prop;

		for (m_Enum -> Reset(); S_OK == m_Enum -> Next(1, &Prop, NULL); m_Enum -> Reset()) {
		// immer den jeweils ersten freigeben
		CComBSTR bstrName;
		
			THROW_FAILED_HRESULT(Prop -> get_Name (CLEARED(&bstrName)));
			THROW_FAILED_HRESULT(m_Enum -> RemoveItem (bstrName));	// erst aus der Collection entfernen
			Prop.Assign (NULL);									// danach Property selbst freigeben
		}
		m_Enum.Assign(NULL);	/*lint !e534*/		// jetzt Enumerator selbst freigeben
	} COM_CATCH_NORETURN;
}

/////////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CTRiASProperties::get_Application(IDispatch * * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProperties::put_Application(IDispatch * newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProperties::get_Parent(IDispatch * * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProperties::put_Parent(IDispatch * newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASProperties::get_Count(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperties::get_Count");

	return m_Enum -> Count((ULONG *)pVal);
}

STDMETHODIMP CTRiASProperties::SetEventSink (IUnknown *pIUnk, VARIANT_BOOL fAdvise)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (fAdvise) {
	// PropertySupport nur dann initialisieren, wenn's noch nicht passiert ist
		if (!m_Support) {
		WTRiASPropertySupport Support;

			if (SUCCEEDED(pIUnk -> QueryInterface (Support.ppi())))
				m_Support = Support;
		}

	// bei Bedarf am ConnectionPoint anmelden
		if (NULL != pIUnk) {
			_ASSERTE(m_dwCookie == 0);
			return AtlAdvise (pIUnk, GetUnknown(), IID_ITRiASPropertyEvents, &m_dwCookie);
		}
	} else {
	// PropertySupport freigeben, wenn kein neues gegeben ist oder wenn altes gleich neuem ist
	WUnknown Unk (pIUnk);

		if (!Unk.IsValid()) {
			Unk = m_Support;	// ggf. altes Bezugsobjekt verwenden
			m_Support.Assign(NULL);
		} else if (m_Support == WTRiASPropertySupport(Unk)) {
			m_Support.Assign(NULL);
		} else {
			Unk.Assign(NULL);
		}

	// bei Bedarf am ConnectionPoint abmelden
		if (Unk.IsValid() && 0 != m_dwCookie) {		// nicht doppelt freigeben
		DWORD dwCookie = m_dwCookie;

			m_dwCookie = 0L;
			return AtlUnadvise (Unk, IID_ITRiASPropertyEvents, dwCookie);
		}
	}
	return S_OK;
}

STDMETHODIMP CTRiASProperties::Item(VARIANT Which, ITRiASProperty **Property)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Property) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperties::Item");
	if (!m_Enum.IsValid())		// InitialisierungsPhase 
		return REPORT_DBERROR(E_UNEXPECTED);

CComVariant vIndex;
bool fFound = false;
WEnumWTRiASProperty Enum;
WTRiASProperty Prop;

// Verhindern, daß als Nummern als Zeichenkette falsch interpretiert werden
	*Property = NULL;

	if (VT_BSTR != V_VT(&Which) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Which))) {
	ULONG ulCnt = 0;

		THROW_FAILED_HRESULT(m_Enum -> Count(&ulCnt));
		if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > ulCnt)
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperties::Item");

	// Index ist eine Zahl
		COM_TRY {
			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(Enum -> Reset());

			if (V_I4(&vIndex) > 1)
			{
				THROW_FAILED_HRESULT(Enum -> Skip (V_I4(&vIndex)-1));
			}
			if (S_OK == Enum -> Next (1, &Prop, NULL))
			{
				*Property = Prop.detach();
				fFound = true;
			}
		} COM_CATCH;

	} else if (VT_BSTR == V_VT(&Which)) {
	// Which ist Name der Property
	CComBSTR bstrName (TrimRight (V_BSTR(&Which)));		// evtl. abschließende Leerzeichen abschneiden

		if (S_OK == m_Enum -> FindItem (bstrName, &Prop)) {
			*Property = Prop.detach();
			fFound = true;
		}

	} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Which))) {
	// Index ist Name der Property
	CComBSTR bstrName (TrimRight (V_BSTR(&vIndex)));	// evtl. abschließende Leerzeichen abschneiden

		if (S_OK == m_Enum -> FindItem (bstrName, &Prop)) {
			*Property = Prop.detach();
			fFound = true;
		}

	} else
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperties::Item");

	if (!fFound)
		return TRIASDB_E_UNKNOWN_PROPERTY;
	return S_OK;
}

STDMETHODIMP CTRiASProperties::_NewEnum(IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEnum) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperties::_NewEnum");

	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

STDMETHODIMP CTRiASProperties::Add(VARIANT Which, ITRiASProperty **Property)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == Property) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperties::Add");
	if (NULL == (IUnknown *)m_Support) 
		return REPORT_DBERROR(E_UNEXPECTED);

WTRiASProperty Prop;
CComVariant vName;

	RETURN_FAILED_HRESULT(vName.ChangeType (VT_BSTR, &Which));

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (V_BSTR(&vName)));

// Überprüfen, ob Property bereits existiert
	if (S_OK == m_Enum -> FindItem (bstrName, &Prop)) {
		*Property = Prop.detach();
		return S_FALSE;		// existiert bereits
	}

	{
	CComSemaphore<_ThreadModel> Sem (m_lSemAdd);
	HRESULT hr = m_Support -> CreateProperty (bstrName, Prop.ppi());

		if (S_OK != hr) 
			return hr;		// jemand hat was dagegen
	}
	RETURN_FAILED_HRESULT(m_Enum -> AddItem (bstrName, Prop));
	*Property = Prop.detach();

	return S_OK;
}

STDMETHODIMP CTRiASProperties::Remove(VARIANT Which)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == (IUnknown *)m_Support) 
		return REPORT_DBERROR(E_UNEXPECTED);

CComVariant vIndex;
#if defined(_DEBUG)
BOOL fItemFound = FALSE;
#endif // _DEBUG

	if (VT_BSTR != V_VT(&Which) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Which))) {
	ULONG ulCnt = 0;

		THROW_FAILED_HRESULT(m_Enum -> Count(&ulCnt));
		if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > ulCnt)
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperties::Item");

	// Index ist eine Zahl
		COM_TRY {
		WEnumWTRiASProperty Enum;
		WTRiASProperty Prop;
		CComBSTR bstr;
		long lCnt = 1;

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(m_Enum -> Clear());

			for (Enum -> Reset(); S_OK == Enum -> Next (1, &Prop, NULL); lCnt++)
			{
				THROW_FAILED_HRESULT(Prop -> get_Name(CLEARED(&bstr)));
				if (lCnt != V_I4(&vIndex)) 
					m_Enum -> AddItem (bstr, Prop);
				else {
				CComSemaphore<_ThreadModel> Sem (m_lSemDel);

					if (S_OK != m_Support -> RemoveProperty (bstr)) {
#if defined(_DEBUG)
						fItemFound = FALSE;				// _ASSERTE verhindern
#endif // _DEBUG
						m_Enum -> AddItem (bstr, Prop);		// jemand hat was dagegen
					}
				}
			}
#if defined(_DEBUG)
		ULONG ulCntOldDeb = 0;
		ULONG ulCntNewDeb = 0;

			THROW_FAILED_HRESULT(m_Enum -> Count(&ulCntOldDeb));
			THROW_FAILED_HRESULT(Enum -> Count(&ulCntNewDeb));
#endif // _DEBUG
			_ASSERTE(!fItemFound || 0 == ulCntNewDeb || ulCntNewDeb == ulCntOldDeb +1);

		} COM_CATCH;

	} else if (FAILED(vIndex.ChangeType (VT_BSTR, &Which))) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASProperties::Item");

	COM_TRY {
	// evtl. abschließende Leerzeichen abschneiden
	CComBSTR bstrName (TrimRight (V_BSTR(&vIndex)));

#if defined(_DEBUG)
	// feststellen, ob das zu entfernende Item überhaupt zur Collection gehört
	WEnumWTRiASProperty Enum;
	WTRiASProperty PropDeb;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		if (S_OK == Enum -> FindItem (bstrName, &PropDeb)) 
			fItemFound = TRUE;
#endif // _DEBUG

		{
		CComSemaphore<_ThreadModel> Sem (m_lSemDel);
		
			if (S_OK == m_Support -> RemoveProperty (bstrName))		// TargetObjekt arbeiten lassen
				VERIFY(S_OK == m_Enum -> RemoveItem (bstrName));
		}

#if defined(_DEBUG)
	ULONG ulCntOldDeb = 0;
	ULONG ulCntNewDeb = 0;

		THROW_FAILED_HRESULT(m_Enum -> Count(&ulCntOldDeb));
		THROW_FAILED_HRESULT(Enum -> Count(&ulCntNewDeb));
		_ASSERTE(!fItemFound || 0 == ulCntNewDeb || ulCntNewDeb == ulCntOldDeb +1);
#endif // _DEBUG

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProperties::_Add(ITRiASProperty *pIProp, VARIANT_BOOL fFullAdd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	_ASSERTE(NULL != pIProp);
	
// testen, ob dieses Objekt noch nicht in der collection enthalten ist
	_ASSERTE(IsFirstOccurence (m_Enum, pIProp, ITRiASProperty::get_Name, (CComBSTR *)NULL));

CComBSTR bstrName;

	RETURN_FAILED_HRESULT(pIProp -> get_Name(CLEARED(&bstrName)));
	return m_Enum -> AddItem (bstrName, WTRiASProperty(pIProp));
}

STDMETHODIMP CTRiASProperties::_Clone(ITRiASProperties **ppIProps)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIProps) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDatabaseProperties::_Clone");
	if (NULL == (IUnknown *)m_Support) 
		return REPORT_DBERROR(E_UNEXPECTED);

CComObject<CTRiASProperties> *pNew = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASProperties>::CreateInstance (&pNew));
		THROW_FAILED_HRESULT(pNew -> SetPropertySupportSite (m_Support));
		THROW_FAILED_HRESULT(pNew -> InitEnum (m_Enum));

	WTRiASProperties Props (pNew);		// pending AddRef

		*ppIProps = Props.detach();

	} COM_CATCH_OP(delete pNew);

	return S_OK;
}

STDMETHODIMP CTRiASProperties::Refresh()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == (IUnknown *)m_Support) 
		return REPORT_DBERROR(E_UNEXPECTED);

CComSemaphore<_ThreadModel> Sem (m_lSemAdd);
WEnumWTRiASProperty Enum;

	RETURN_FAILED_HRESULT(CreateNewEnum (Enum.ppi()));
	
// alle Properties, die nicht persistent sind, übernehmen
	if (m_Enum.IsValid()) {
		COM_TRY {
		WEnumVARIANT EnumV;
		CComVariant v;

			THROW_FAILED_HRESULT(_NewEnum (EnumV.ppu()));
			for (EnumV -> Reset(); S_OK == EnumV -> Next (1, CLEARED(&v), NULL); /**/)
			{
				if (FAILED(v.ChangeType(VT_UNKNOWN)))
					continue;

			WTRiASProperty Prop (V_UNKNOWN(&v));
			PROPERTY_TYPE rgType = PROPERTY_TYPE_Normal;

				if (SUCCEEDED(Prop -> get_Type(&rgType)) && (rgType & PROPERTY_TYPE_NeedsSavingHelp))
				{
				// auch diese Property neu einlesen
					THROW_FAILED_HRESULT(Prop -> Refresh());

				CComBSTR bstrName;

					THROW_FAILED_HRESULT(Prop -> get_Name (CLEARED(&bstrName)));
					THROW_FAILED_HRESULT(Enum -> AddItem (bstrName, Prop));
				}
			}
		} COM_CATCH;
	}

// jetzt noch alle anderen neu erzeugen
HRESULT hr = m_Support -> FillWithProperties ((IUnknown **)&Enum);

	if (FAILED(hr) && E_NOTIMPL != hr)
		return hr;

// E_NOTIMPL gilt als iO
	m_Enum = Enum;		// neuer Enumerator
	return (S_OK == hr) ? S_OK : S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASPropertyEvents
STDMETHODIMP CTRiASProperties::CreatingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASProperties::PropertyToCreate (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASProperties::PropertyCreated (IDispatch *pIProp)
{
// nur behandeln, wenn nicht wir derzeit bearbeitet werden
	if (IsSemaphoreSignaled (m_lSemAdd, *this)) 
		return S_OK;

	_ASSERTE(NULL != pIProp);
	COM_TRY {
	WTRiASProperty Prop (pIProp);
	CComBSTR bstrName;

		RETURN_FAILED_HRESULT(Prop -> get_Name(CLEARED(&bstrName)));
		return m_Enum -> AddItem (bstrName, Prop);
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASProperties::ModifyingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASProperties::PropertyToModify (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASProperties::PropertyModified (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASProperties::DeletingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASProperties::PropertyToDelete (BSTR Name)
{
// nur behandeln, wenn nicht wir derzeit bearbeitet werden
	if (IsSemaphoreSignaled (m_lSemDel, *this)) 
		return S_OK;

	COM_TRY {
	WEnumWTRiASProperty Enum;
	WTRiASProperty Prop;

		THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
		THROW_FAILED_HRESULT(m_Enum -> Clear());

		for (Enum -> Reset(); S_OK == Enum -> Next (1, &Prop, NULL); /**/)
		{
		CComBSTR bstr;

			THROW_FAILED_HRESULT(Prop -> get_Name (CLEARED(&bstr)));
			if (wcscmp (bstr, Name)) 
				m_Enum -> AddItem (bstr, Prop);
		}

#if defined(_DEBUG)
	ULONG ulCntOldDeb = 0;
	ULONG ulCntNewDeb = 0;

		THROW_FAILED_HRESULT(m_Enum -> Count(&ulCntOldDeb));
		THROW_FAILED_HRESULT(Enum -> Count(&ulCntNewDeb));
#endif // _DEBUG
		_ASSERTE(ulCntNewDeb == ulCntOldDeb +1);

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASProperties::PropertyDeleted (BSTR Name)
{
	return S_OK;
}

