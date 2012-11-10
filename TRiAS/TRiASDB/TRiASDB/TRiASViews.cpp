// TRiASViews.cpp : Implementation of CTRiASViews

#include "stdafx.h"

#include "Strings.h"
#include "Wrapper.h"			// SmartIF's

#include "TRiASViews.h"
#include "MakeEnumVariant.h"

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

/////////////////////////////////////////////////////////////////////////////
// RUNTIME_OBJECT_MAP
RT_OBJECT_ENTRY(CLSID_TRiASViews, CTRiASViews)

/////////////////////////////////////////////////////////////////////////////
// SmartInterface's
DefineSmartInterface(TRiASViewEvents);
DefineSmartInterface(TRiASConnectionEvents);

/////////////////////////////////////////////////////////////////////////////
// CTRiASViews
STDMETHODIMP CTRiASViews::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASViews,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}


HRESULT CTRiASViews::FinalConstruct (void)
{
// init base instance data
HRESULT hr = IPersistStorageOMImpl<CTRiASViews>::FinalConstruct();

	if (FAILED(hr)) return hr;

// instance data
	ATLTRY(m_Enum = new TEnumWTRiASView());
	if (!m_Enum) 
		return E_OUTOFMEMORY;

	m_Enum -> Release();	// Konstruktor hinterläßt RefCnt==1
	return S_OK;
}

void CTRiASViews::FinalRelease()
{
	OnFinalRelease();
	m_Enum.Assign(NULL);	// Enumerator freigeben
	m_Application = NULL;
}

STDMETHODIMP CTRiASViews::OnFinalRelease()
{
	if (NULL != m_pIParent) {
	WEnumWTRiASView Enum;
	WTRiASView View;

		if (SUCCEEDED(GetClonedEnum(Enum.ppi()))) {
			for (Enum -> Reset(); S_OK == Enum -> Next(1, &View, NULL); /**/) {
			WDispatch Parent;

				RETURN_FAILED_HRESULT(View -> get_Parent (Parent.ppi()));
				if (Parent.IsValid() && Parent != WDispatch(m_pIParent))
					continue;		// Ansicht gehört nicht zu uns

				RETURN_FAILED_HRESULT(View -> put_Application (NULL));
				RETURN_FAILED_HRESULT(View -> OnFinalRelease());
			}
		}
		m_pIParent = NULL;
	} 
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASViews::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASViews::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASViews::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::get_Application");

	*pVal = m_pIParent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASViews::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pIParent = newVal;		// no AddRef !

// zu allen Ansichten etc. propagieren
	{
	WEnumWTRiASView Enum;
	WTRiASView View;

		if (SUCCEEDED(GetClonedEnum(Enum.ppi()))) {
			for (Enum -> Reset(); S_OK == Enum -> Next(1, &View, NULL); /**/) {
				RETURN_FAILED_HRESULT(View -> put_Application ((NULL != newVal) ? m_Application : NULL));
				RETURN_FAILED_HRESULT(View -> put_Parent (newVal));
			}
		}
	}
	return S_OK;
}

STDMETHODIMP CTRiASViews::get_StartViewName(BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::get_StartViewName");

	COM_TRY {
	WEnumWTRiASView Enum;
	WTRiASView View;

		THROW_FAILED_HRESULT(GetClonedEnum(Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &View, NULL); /**/)
		{
		VARIANT_BOOL fIsStartView = VARIANT_FALSE;
		
			THROW_FAILED_HRESULT(View -> get_IsStartView (&fIsStartView));
			if (fIsStartView) {
			// Start-Ansicht gefunden
			CComBSTR bstr;

				THROW_FAILED_HRESULT(View -> get_Name (CLEARED(&bstr)));
				*pVal = bstr.Detach();
				return S_OK;
			}
		}

	} COM_CATCH;

CComBSTR bstr (g_cbNil);

	if (!bstr)
		return E_OUTOFMEMORY;

	*pVal = bstr.Detach();
	return S_FALSE;		// keine StartAnsicht gefunden
}

STDMETHODIMP CTRiASViews::put_StartViewName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
	WEnumWTRiASView Enum;
	WTRiASView View;

		THROW_FAILED_HRESULT(GetClonedEnum(Enum.ppi()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, &View, NULL); /**/)
		{
		CComBSTR bstr;

			THROW_FAILED_HRESULT(View -> get_Name (CLEARED(&bstr)));
			THROW_FAILED_HRESULT(View -> put_IsStartView (!wcscmp (newVal, bstr) ? VARIANT_TRUE : VARIANT_FALSE));
		}

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASViews::get_Count(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::get_Application");

	_ASSERTE(sizeof(LONG) == sizeof(ULONG));	// verify safeness of the following cast
	return m_Enum -> Count((ULONG *)pVal);
}

STDMETHODIMP CTRiASViews::_Add(ITRiASView *View, VARIANT_BOOL fFullAdd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// testen, ob dieses Objekt noch nicht in der collection enthalten ist
	_ASSERTE(IsFirstOccurence (m_Enum, View, ITRiASView::get_Name, (CComBSTR *)NULL));

// jetzt einfach bei uns zuordnen
	if (fFullAdd) {
		RETURN_FAILED_HRESULT(View -> put_Application (m_Application));
		RETURN_FAILED_HRESULT(View -> put_Parent (m_pIParent));
	}

CComBSTR bstrName;

	RETURN_FAILED_HRESULT(View -> get_Name (CLEARED(&bstrName)));

	if (!!m_ObjMan)	{	// wenn's eine StorageBasierte View ist
	// wenn ObjMan diese Ansicht noch nicht kennt, dann hinzufügen
	WUnknown Unk;

		if (FAILED(m_ObjMan -> GetObject (bstrName, Unk.ppi()))) {
		// darf hinzugefügt werden ?
		VARIANT_BOOL fCreate = VARIANT_FALSE;

			RETURN_FAILED_HRESULT(Fire_CreatingView (bstrName, &fCreate));
			if (fCreate != VARIANT_FALSE)
				return S_FALSE;		// abgebrochen oder Fehler
			RETURN_FAILED_HRESULT(Fire_ViewToCreate (bstrName));

		// zum ObjMan hinzufügen
			RETURN_FAILED_HRESULT(m_ObjMan -> SetObject (View, bstrName, STGM_CREATE, false));

		// nun einfach zu den anderen werfen (muß _vor_ Fire_ViewCreated geschehen)
			RETURN_FAILED_HRESULT(m_Enum -> AddItem (bstrName, View));

		// erfolgreich hinzugefügt
			{
			CComSemaphore<_ThreadModel> Sem (m_lSemAdd);	// doppeltes löschen verhindern

				RETURN_FAILED_HRESULT(Fire_ViewCreated (View));
			}
			return S_OK;
		}
	}

// nun einfach zu den anderen werfen
	return m_Enum -> AddItem (bstrName, View);
}

STDMETHODIMP CTRiASViews::RemoveView(ITRiASView *pIView)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

CComBSTR bstrName;

	RETURN_FAILED_HRESULT(pIView -> get_Name (CLEARED(&bstrName)));
	RETURN_FAILED_HRESULT(pIView -> put_Application (NULL));
	RETURN_FAILED_HRESULT(pIView -> put_Parent (NULL));

	VERIFY(S_OK == m_Enum -> RemoveItem (bstrName));
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CTRiASViews::Add(BSTR Name, ITRiASView **ppIView)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIView) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::Add");

// Erzeugen einer neuen View und hinzufügen zur Collection
	COM_TRY {
	// Überprüfen, ob Ansicht bereits existiert
	WTRiASView View;

		if (S_OK == m_Enum -> FindItem (Name, &View)) {
			*ppIView = View.detach();
			return S_FALSE;		// existiert bereits
		}

	// darf erzeugt werden ?
	VARIANT_BOOL fCreate = VARIANT_FALSE;

		THROW_FAILED_HRESULT(Fire_CreatingView (Name, &fCreate));
		if (fCreate != VARIANT_FALSE)
			return S_FALSE;		// abgebrochen oder Fehler
		THROW_FAILED_HRESULT(Fire_ViewToCreate (Name));

	// jetzt wirklich erzeugen
		if (!!m_ObjMan)	{	// wenn's eine StorageBasierte View ist
			THROW_FAILED_HRESULT(m_ObjMan -> CreateObject (CLSID_TRiASView, Name, STGM_CREATE, View.ppu(), false));
		} else {
		// völlig neu erzeugen
			View = WTRiASView(CLSID_TRiASView);
			THROW_FAILED_HRESULT(WPersistStreamInit(View) -> InitNew());
		}

		THROW_FAILED_HRESULT(View -> put_Parent(m_pIParent));
		THROW_FAILED_HRESULT(View -> put_Application(m_Application));
		THROW_FAILED_HRESULT(View -> put_Name(Name));

		THROW_FAILED_HRESULT(m_Enum -> AddItem (Name, View));

	// erfolgreich erzeugt
		{
		CComSemaphore<_ThreadModel> Sem (m_lSemAdd);	// doppeltes Einfügen verhindern

			THROW_FAILED_HRESULT(Fire_ViewCreated (View));
		}
		*ppIView = View.detach();

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASViews::Item(VARIANT Index, ITRiASView **ppIView)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIView) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::Item");

CComVariant vIndex;
bool fFound = false;

	*ppIView = NULL;
	COM_TRY {
	WTRiASView View;

	// Verhindern, daß als Nummern als Zeichenkette falsch interpretiert werden
		if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
		WEnumWTRiASView Enum;
		ULONG ulCnt = 0;

			THROW_FAILED_HRESULT(m_Enum -> Count(&ulCnt));
			if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > ulCnt)
				return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::Item");

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(Enum -> Reset());

			if (V_I4(&vIndex) > 1)
			{
				THROW_FAILED_HRESULT(Enum -> Skip (V_I4(&vIndex)-1));
			}
			if (S_OK == Enum -> Next (1, &View, NULL))
			{
				*ppIView = View.detach();
				fFound = true;
			}

		} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {

			if (S_OK == m_Enum -> FindItem (CComBSTR(V_BSTR(&vIndex)), &View)) {
				*ppIView = View.detach();
				fFound = true;
			}

		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::Item");

	} COM_CATCH;

	if (!fFound)
		return REPORT_DBERROR(TRIASDB_E_UNKNOWN_VIEW);

	return S_OK;
}

STDMETHODIMP CTRiASViews::Remove(VARIANT Index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

HRESULT hr_result = S_OK;

	COM_TRY {
	// darf gelöscht werden ?
	VARIANT_BOOL fDelete = VARIANT_FALSE;

	// Verbindung herauslöschen
	WEnumWTRiASView Enum;
	WTRiASView View;
	long lCnt = 1;

		THROW_FAILED_HRESULT(GetClonedEnum(Enum.ppi()));
		THROW_FAILED_HRESULT(m_Enum -> Clear());

	CComVariant vIndex;
	CComBSTR bstrName;

		if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
		ULONG ulCnt = 0;

			THROW_FAILED_HRESULT(Enum -> Count(&ulCnt));
			if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > ulCnt) {
				m_Enum = Enum;
				return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::Item");
			}

		// alle außer dem einen Kopieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &View, NULL); lCnt++)
			{
				if (lCnt == V_I4(&vIndex)) {
					THROW_FAILED_HRESULT(Fire_DeletingView (View, &fDelete));
					if (fDelete == VARIANT_FALSE) {
					CComSemaphore<_ThreadModel> Sem (m_lSemDel);	// doppeltes löschen verhindern

						THROW_FAILED_HRESULT(Fire_ViewToDelete (View));

					// wir haben den Parent/App gesetzt, also setzen wirs zurück
						THROW_FAILED_HRESULT(View -> put_Application (NULL));
						THROW_FAILED_HRESULT(View -> put_Parent (NULL));

						continue;
					}
					hr_result = S_FALSE;		// abgebrochen oder Fehler
				}

			// nicht aus collection entfernen
				THROW_FAILED_HRESULT(View -> get_Name (CLEARED(&bstrName)));
				THROW_FAILED_HRESULT(m_Enum -> AddItem(bstrName, View));
			}

#if defined(_DEBUG)
		ULONG ulCntDeb = 0L;
		ULONG ulCntDebN = 0L;

			THROW_FAILED_HRESULT(m_Enum -> Count (&ulCntDeb));
			THROW_FAILED_HRESULT(Enum -> Count (&ulCntDebN));
			_ASSERTE(0 == ulCntDebN || ulCntDebN == ulCntDeb + 1);
#endif // _DEBUG

		} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {

		// das gewünschte herauslöschen
//			VERIFY(S_OK == m_Enum -> RemoveItem (CComBSTR(V_BSTR(&vIndex))));
//			bstrName = V_BSTR(&vIndex);

		// alle außer dem einen Kopieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &View, NULL); lCnt++)
			{
				THROW_FAILED_HRESULT(View -> get_Name (CLEARED(&bstrName)));
				if (!wcscmp(bstrName, V_BSTR(&vIndex))) {
					THROW_FAILED_HRESULT(Fire_DeletingView (View, &fDelete));
					if (fDelete == VARIANT_FALSE) {
					CComSemaphore<_ThreadModel> Sem (m_lSemDel);	// doppeltes löschen verhindern

						THROW_FAILED_HRESULT(Fire_ViewToDelete (View));

					// wir haben den Parent/App gesetzt, also setzen wirs zurück
						THROW_FAILED_HRESULT(View -> put_Application (NULL));
						THROW_FAILED_HRESULT(View -> put_Parent (NULL));
						continue;
					}
				
					hr_result = S_FALSE;	// abgebrochen oder Fehler
				}

			// nicht aus collection entfernen
				m_Enum -> AddItem(bstrName, View);
			}
			bstrName = V_BSTR(&vIndex);

		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::Item");

	// erfolgreich gelöscht
		if (!!m_ObjMan)		// wenn's eine StorageBasierte View ist
			THROW_FAILED_HRESULT(m_ObjMan -> DelObject (bstrName));
		THROW_FAILED_HRESULT(Fire_ViewDeleted (bstrName));

	} COM_CATCH;

	return hr_result;
}

STDMETHODIMP CTRiASViews::_NewEnum (IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEnum) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::_NewItem");

	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

STDMETHODIMP CTRiASViews::_Clone(ITRiASViews **ppIViews)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIViews) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViews::_Clone");

CComObject<CTRiASViews> *pNew = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASViews>::CreateInstance (&pNew));
		THROW_FAILED_HRESULT(pNew -> InitObjMan (m_ObjMan, m_Stg, m_StgMode));
		THROW_FAILED_HRESULT(pNew -> InitEnum (m_Enum));

		THROW_FAILED_HRESULT(pNew -> put_Application (m_Application));
		THROW_FAILED_HRESULT(pNew -> put_Parent (m_pIParent));

	WTRiASViews Views (pNew);		// pending AddRef

		*ppIViews = Views.detach();

	} COM_CATCH_OP(delete pNew);

	return S_OK;
}

STDMETHODIMP CTRiASViews::SetEventSink (IUnknown *pIUnk, VARIANT_BOOL fAdvise)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (fAdvise) {
	// ViewEvents
		_ASSERTE(0 == m_dwCookie);
		RETURN_FAILED_HRESULT(AtlAdvise (pIUnk, GetUnknown(), IID_ITRiASViewEvents, &m_dwCookie));

	// ConnEvents
		_ASSERTE(0 == m_dwCookieConns);
		RETURN_FAILED_HRESULT(AtlAdvise (pIUnk, GetUnknown(), IID_ITRiASConnectionEvents, &m_dwCookieConns));
	} 
	else {
	// alle Ansichten etc. freigeben
		{
		WEnumWTRiASView Enum;
		WTRiASView View;

			if (SUCCEEDED(m_Enum -> Clone (Enum.ppi()))) {
				for (Enum -> Reset(); S_OK == Enum -> Next(1, &View, NULL); /**/) {
				// wir haben den Parent/App gesetzt, also setzen wirs zurück
					RETURN_FAILED_HRESULT(View -> put_Application (NULL));
					RETURN_FAILED_HRESULT(View -> put_Parent (NULL));
				}
			}
		}

	// ConnPt's abmelden
		_ASSERTE(m_dwCookie != 0);
		_ASSERTE(m_dwCookieConns != 0);

	DWORD dwCookie = m_dwCookie;

		m_dwCookie = 0L;
		RETURN_FAILED_HRESULT(AtlUnadvise (pIUnk, IID_ITRiASViewEvents, dwCookie));

		dwCookie = m_dwCookieConns;
		m_dwCookieConns = 0L;
		RETURN_FAILED_HRESULT(AtlUnadvise (pIUnk, IID_ITRiASConnectionEvents, dwCookie));
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Events verschicken
HRESULT CTRiASViews::Fire_CreatingView (BSTR Name, VARIANT_BOOL *pVal)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> CreatingView (Name, pVal);
	return S_OK;
}

HRESULT CTRiASViews::Fire_ViewToCreate (BSTR Name)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ViewToCreate (Name);
	return S_OK;
}

HRESULT CTRiASViews::Fire_ViewCreated (IDispatch * pIView)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ViewCreated (pIView);
	return S_OK;
}

HRESULT CTRiASViews::Fire_DeletingView (IDispatch *pIView, VARIANT_BOOL * pVal)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> DeletingView (pIView, pVal);
	return S_OK;
}

HRESULT CTRiASViews::Fire_ViewToDelete (IDispatch * pIView)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ViewToDelete (pIView);
	return S_OK;
}

HRESULT CTRiASViews::Fire_ViewDeleted(BSTR Name)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ViewDeleted (Name);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
//
// ITRiASViewEvents
STDMETHODIMP CTRiASViews::CreatingView (BSTR Name, VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASViews::ViewToCreate (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASViews::ViewCreated (IDispatch *pIView)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// nur behandeln, wenn nicht wir derzeit bearbeitet werden
	if (IsSemaphoreSignaled (m_lSemAdd, *this)) 
		return S_OK;

	COM_TRY {
	WTRiASView View (pIView);

		THROW_FAILED_HRESULT(_Add(View, VARIANT_TRUE));

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASViews::ChangingView (BSTR NewName, BSTR OldName, VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASViews::ViewToChange (BSTR Name, BSTR NewName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Ansicht wird umbennant werden
	COM_TRY {
	// erstmal in der collection nachführen
	WTRiASView View;

		if (S_OK == m_Enum -> FindItem (Name, &View)) {
		// dazu herausnehemen und wieder einbauen
			THROW_FAILED_HRESULT(m_Enum -> RemoveItem (Name));
			THROW_FAILED_HRESULT(m_Enum -> AddItem (NewName, View));
		}
				
	// jetzt auch auf der Platte umbenennen
		if (!!m_ObjMan)	{	// wenn's eine StorageBasierte View ist
		WUnknown Unk;

			if (SysStringLen(Name) > 0 && SUCCEEDED(m_ObjMan -> GetObject (Name, Unk.ppi()))) {
			// nur umbenennen, wenns wirklich schon existiert
				THROW_FAILED_HRESULT(m_ObjMan -> RenameObject (Name, NewName));
			}
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASViews::ViewChanged (IDispatch *pIConn)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASViews::DeletingView (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASViews::ViewToDelete (IDispatch *pIView)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// nur behandeln, wenn nicht wir derzeit bearbeitet werden
	if (IsSemaphoreSignaled (m_lSemDel, *this)) 
		return S_OK;

	COM_TRY {
	WTRiASView View (pIView);

		THROW_FAILED_HRESULT(RemoveView (View));

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASViews::ViewDeleted (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASConnectionEvents-Wrapper
STDMETHODIMP CTRiASViews::CreatingConnection (BSTR Name, VARIANT_BOOL *pVal)
{ 
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectionToCreate (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectionCreated (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::OpeningConnection (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectionToOpen (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectionOpened (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ClosingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectionToClose (IDispatch *pIConn)
{
	COM_TRY {
	WEnumWTRiASView Enum;
	WTRiASView View;

		if (SUCCEEDED(GetClonedEnum(Enum.ppi()))) {
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &View, NULL); /**/)
			{
				WTRiASConnectionEvents(View) -> ConnectionToClose (pIConn);
			}
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectionClosed (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::DeletingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectionToDelete (IDispatch *pIConn)
{
	COM_TRY {
	WEnumWTRiASView Enum;
	WTRiASView View;

		if (SUCCEEDED(GetClonedEnum(Enum.ppi()))) {
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &View, NULL); /**/)
			{
				WTRiASConnectionEvents(View) -> ConnectionToDelete (pIConn);
			}
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectionDeleted (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::RenamingConnection (BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectionToRename (BSTR OldName, BSTR NewName)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectionRenamed (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ChangingConnectedDatasource (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectedDatasourceToChange (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASViews::ConnectedDatasourceChanged (IDispatch *pIConn)
{
	return S_OK;
}

