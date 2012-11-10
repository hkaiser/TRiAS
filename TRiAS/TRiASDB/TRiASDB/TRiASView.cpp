// TRiASView.cpp : Implementation of CTRiASView

#include "stdafx.h"

#include <ospace/std/set>
#include <Com/MkHelper.h>

#include "PersistEnum.h"
#include "Strings.h"
#include "Wrapper.h"

#include "TRiASProperty.h"
#include "TRiASView.h"
#include "TRiASViewItems.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this clas
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASView);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASView::Dump()
{
	D_OUTF2(1, 
		"CTRiASView: pending %ls, ", m_bstrName,
		"RefCnt(%ld).", m_dwRef);
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
RT_OBJECT_ENTRY(CLSID_TRiASView, CTRiASView)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASViewEvents);			// WTRiASViewEvents
DefineSmartInterface(TRiASConnectionEvents);	// WTRiASConnectionEvents
DefineSmartInterface(ObjectWithSite);			// WObjectWithSite

namespace {
// Feld aller bekannten Objekttypen 
	const OBJECTTYPE g_rgObjTypes[] = {
		{ OBJECTTYPE_Point, },
		{ OBJECTTYPE_Line, },
		{ OBJECTTYPE_Area, },
		{ OBJECTTYPE_Text, },
		{ OBJECTTYPE_Complex, },
		{ OBJECTTYPE_Unknown, },
	};
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASView

STDMETHODIMP CTRiASView::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASView,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

HRESULT CTRiASView::CreateViewItemCollection()
{
	COM_TRY {
	// ViewItem-Collection erzeugen
		m_ViewItems = WTRiASViewItems (CLSID_TRiASViewItems);
		THROW_FAILED_HRESULT(m_ViewItems -> put_Application (m_Application));
		THROW_FAILED_HRESULT(m_ViewItems -> put_Parent (GetTRiASView()));
		THROW_FAILED_HRESULT(m_ViewItems -> SetEventSink (GetUnknown(), VARIANT_TRUE));
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASView::OnFinalRelease()
{
	COM_TRY {
		if (m_ViewItems.IsValid()) {
		WEnumVARIANT Enum;

			THROW_FAILED_HRESULT(m_ViewItems -> _NewEnum (Enum.ppu()));

		CComVariant var;

		// ViewItems informieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&var), NULL); /**/)
			{
				if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) 
					WTRiASViewItem(V_UNKNOWN(&var)) -> put_Parent (NULL);
			}

		// ViewItems freigeben
			m_ViewItems -> SetEventSink (GetUnknown(), VARIANT_FALSE);
			m_ViewItems -> put_Parent (NULL);
			m_ViewItems.Assign(NULL);

		// Properties freigeben
			FreePropertiesCollection();

		// PropertySupportObjekte freigeben
			ReleasePropertySupportObjects();

			m_fIsDirty = false;
			m_fIsInitialized = false;		// muß neu initialisert werden
		} 
		m_Application = NULL;
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASView::get_IsStartView(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::get_IsStartView");

	*pVal = m_fIsStartView ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASView::put_IsStartView(VARIANT_BOOL newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

bool fNewVal = newVal ? true : false;

	if (fNewVal != m_fIsStartView) {
		m_fIsStartView = fNewVal;
		m_fIsDirty = true;
	} 
	return S_OK;
}

STDMETHODIMP CTRiASView::get_Name(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::get_Name");

CComBSTR bstr (m_bstrName);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASView::put_Name(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// der Ansicht einen neuen Namen verpassen
	if (!m_bstrName) {	// das erste mal
		m_bstrName = newVal;
		if (!m_bstrName)
			return Error (g_cbNoMemory, E_OUTOFMEMORY);
	} else {
	// bei NamensÄnderung die Welt benachrichtigen
	VARIANT_BOOL fRename = VARIANT_FALSE;

		RETURN_FAILED_HRESULT(Fire_ChangingView (m_bstrName, newVal, &fRename));
		if (fRename != VARIANT_FALSE)
			return S_FALSE;		// nicht umbenennen
		RETURN_FAILED_HRESULT(Fire_ViewToChange (m_bstrName, newVal));

	// jetzt wirklich umbenennen
		m_bstrName = newVal;
		if (!m_bstrName)
			return Error (g_cbNoMemory, E_OUTOFMEMORY);
		RETURN_FAILED_HRESULT(Fire_ViewChanged((ITRiASView *)this));
	}
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASView::get_RelatedDataSourceName(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::get_RelatedDataSourceName");

CComBSTR bstr (m_bstrRelatedDataSourceName);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASView::put_RelatedDataSourceName(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Namen der Ursprungsdatenquelle setzen
	if (!m_bstrRelatedDataSourceName) {			// nur beim ersten Mal
		m_bstrRelatedDataSourceName = newVal;
		if (!m_bstrRelatedDataSourceName)
			return Error (g_cbNoMemory, E_OUTOFMEMORY);
	} 
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASView::get_ConnectionFilter(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::get_ConnectionFilter");

CComBSTR bstr (m_bstrConnectionFilter);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);

	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASView::put_ConnectionFilter(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// Namen des zugeordneten räumlichen Filters setzen
	m_bstrConnectionFilter = newVal;
	if (!m_bstrConnectionFilter)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASView::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASView::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASView::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::get_Application");

	*pVal = m_Parent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASView::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (m_Parent == WDispatch(newVal))
		return S_OK;	// wenn's kein neuer ist, dann wieder raus

	m_Parent = newVal;
	COM_TRY {
		if (!m_Parent) {
		// das Nullsetzen des Parent wird als Signal zum Freigeben gewertet
		// evtl. alle SubObjekte von ihrem Bezug abhängen
			OnFinalRelease();
		} 
		else {
		// einzelne ViewItems informieren
		WEnumVARIANT Enum;

			THROW_FAILED_HRESULT(m_ViewItems -> _NewEnum (Enum.ppu()));

		CComVariant var;

		// ViewItems erhalten die Ansicht als Parent
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &var, NULL); /**/)
			{
				if (SUCCEEDED(var.ChangeType(VT_UNKNOWN))) 
					WTRiASViewItem(V_UNKNOWN(&var)) -> put_Parent (GetDispatch());
			}

		// ViewItems umhängen
			m_ViewItems -> SetEventSink (NULL, VARIANT_FALSE);			// alten Bezug abklemmen
			m_ViewItems -> SetEventSink (GetUnknown(), VARIANT_TRUE);	// neuen Bezug erzeugen
			m_ViewItems -> put_Parent (GetDispatch());
		}

	} COM_CATCH_IGNORE;		// Fehler einfach ignorieren
	return S_OK;
}

STDMETHODIMP CTRiASView::get_ViewItems(ITRiASViewItems **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::get_ViewItems");

WTRiASViewItems ViewItems (m_ViewItems);

	*pVal = ViewItems.detach();
	return S_OK;
}

STDMETHODIMP CTRiASView::get_ViewItem (VARIANT vItem, VARIANT_BOOL fCreate, BSTR Type, ITRiASViewItem **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::get_ViewItem");

HRESULT hr = m_ViewItems -> Item (vItem, pVal);

	if (TRIASDB_E_UNKNOWN_VIEWITEM == hr && fCreate) {
	CComVariant v;

		if (SUCCEEDED(v.ChangeType (VT_BSTR, &vItem))) {
			hr = m_ViewItems -> Add (V_BSTR(&v), Type, pVal);
			if (S_OK == hr)	hr = S_FALSE;		// ViewItem neu erzeugt
		} 
		else {
		// jetzt kann es nur noch ein IDispatch (ITRiASObjects) sein, Namen besorgen und los
		CComBSTR bstrName;
		WTRiASObjects Objs;

			RETURN_FAILED_HRESULT(v.ChangeType (VT_DISPATCH, &vItem));
			RETURN_FAILED_HRESULT(V_DISPATCH(&v) -> QueryInterface(Objs.ppi()));
			if (FAILED(m_ViewItems -> Item (CComVariant(Objs), pVal))) {	// existiert noch nicht
			// ViewItem wird unter dem Objs-Moniker angelegt
			WMoniker mk;
			CComBSTR bstrMkName;

				RETURN_FAILED_HRESULT(MkGetMoniker (Objs, OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, mk.ppi()));
				RETURN_FAILED_HRESULT(MkGetDisplayName (mk, CLEARED(&bstrMkName)));

				hr = m_ViewItems -> Add (bstrMkName, Type, pVal);
				if (S_OK == hr)	hr = S_FALSE;		// ViewItem neu erzeugt
			}
		} 
	}
	return hr;
}

STDMETHODIMP CTRiASView::AddViewItem(ITRiASViewItem * Item)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	RETURN_FAILED_HRESULT(m_ViewItems -> _Add(Item, VARIANT_TRUE));

	m_fIsDirty = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Liefern aller ObjektMengen, die in dieser Ansicht vertreten sind
STDMETHODIMP CTRiASView::get_ObjectsDefs(ITRiASObjectsCollection **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::get_ObjectsDefs");

	COM_TRY {
	// Neues ObjektmengenObjekt erzeugen
	WTRiASObjectsCollection ObjsColl (CLSID_TRiASObjectsCollection);

		THROW_FAILED_HRESULT(ObjsColl -> put_Application(m_Application));
		THROW_FAILED_HRESULT(ObjsColl -> put_Parent((ITRiASView *)this));

	// Set aller bereits enthaltenen ObjsHandles
	set<INT_PTR> ObjsHandles;

	// alle Elemente dieser Ansicht besorgen
	WEnumVARIANT Enum;
	CComVariant v;

		THROW_FAILED_HRESULT(m_ViewItems -> _NewEnum (Enum.ppu()));
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) 
		{
			if (FAILED(v.ChangeType (VT_DISPATCH)))
				continue;

		WTRiASViewItem Item (V_DISPATCH(&v));

		// alle bekannten Objekttypen durchgehen
			for (const OBJECTTYPE *pEntry = g_rgObjTypes;
				 OBJECTTYPE_Unknown != *pEntry;
				 pEntry++)
			{
			WTRiASObjects Objs;

				if (SUCCEEDED(Item -> get_Objects (*pEntry, Objs.ppi())))
				{
				INT_PTR lHandle = NULL;

					if (FAILED(Objs -> get_Handle (&lHandle)) || NULL == lHandle)
						continue;

				pair<set<INT_PTR>::iterator, bool> p (ObjsHandles.insert (lHandle));

					if (p.second) {	// bereits enthalten ?
						THROW_FAILED_HRESULT(ObjsColl -> _Add(Objs, VARIANT_FALSE));	// !!
					}
				}
			}
		}

	// Resultat liefern
		*pVal = ObjsColl.detach();

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASView::get_Relations (ITRiASRelations * *pVal)
{
	ATLTRACENOTIMPL("CTRiASView::get_Relations");
}

STDMETHODIMP CTRiASView::put_Relations (ITRiASRelations *pVal)
{
	ATLTRACENOTIMPL("CTRiASView::put_Relations");
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASView::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::GetClassID");

	*pClassID = CLSID_TRiASView;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
STDMETHODIMP CTRiASView::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASView::Load (LPSTREAM pStm)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

bool fMakeDirty = false;

	COM_TRY {
	// Version prüfen
	long lSignature = 0L;

		THROW_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
		if (VIEW_SIGNATURE != lSignature)
			return TRIASDB_E_BADOBJECTSIGNATURE;

	long lVersion = 0L;

		THROW_FAILED_HRESULT(LoadLong (pStm, lVersion));			// VersionInfo
		if ((lVersion & ~VIEW_VERSION_MINOR_MASK) > LASTKNOWN_VIEW_VERSION)
			return TRIASDB_W_NEWERVIEW;

		if (lVersion <= VIEW_VERSION_102)
			fMakeDirty = true;				// neue ConnMks, ohne zlib --> alles wirklich speichern

	// Namen der Ansicht laden
	LONG lData = 0;

		m_bstrName.Empty();
		THROW_FAILED_HRESULT(m_bstrName.ReadFromStream (pStm));
		THROW_FAILED_HRESULT(LoadLong (pStm, lData));
		m_fIsStartView = lData ? true : false;

	// die 2 Offsets überspringen (werden z.Zt noch nicht gebraucht)
	LARGE_INTEGER li;

		li.QuadPart = 2*sizeof(ULARGE_INTEGER);
		THROW_FAILED_HRESULT(pStm -> Seek(li, STREAM_SEEK_CUR, NULL));

	// Enumeratoren initialisieren
		THROW_FAILED_HRESULT(CreatePropertiesCollection (false));
		THROW_FAILED_HRESULT(CreateViewItemCollection());

	// Enumeratoren laden	
	CInitProperty<CTRiASView> InitProp(this);

		LoadEnumeratedItemsEx(GetProperties(), pStm, &FMTID_EnumProperties, InitProp, VIEW_VERSION_103 <= lVersion);			// Properties lesen und initialisieren

	// ViewItems lesen
		if (lVersion < VIEW_VERSION_102)
			LoadEnumeratedItems(m_ViewItems, pStm, &FMTID_EnumViewItems, (ITRiASViewItem *)NULL);
		else
			LoadEnumeratedItemsStg(m_ViewItems, pStm, &FMTID_EnumViewItems, (ITRiASViewItem *)NULL, VIEW_VERSION_103 <= lVersion);

	// evtl. Bezugsdatenquelle laden
		m_bstrRelatedDataSourceName.Empty();
		m_bstrRelatedDataSourceName.ReadFromStream (pStm);		// ignore errors

		if (lVersion >= VIEW_VERSION_104)
			m_bstrConnectionFilter.ReadFromStream(pStm);

	} COM_CATCH;

	m_fIsDirty = fMakeDirty;
	m_fIsInitialized = true;
	return S_OK;
}

STDMETHODIMP CTRiASView::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
		THROW_FAILED_HRESULT(SaveLong (pStm, VIEW_SIGNATURE));
		THROW_FAILED_HRESULT(SaveLong (pStm, LASTKNOWN_VIEW_VERSION));

	// Namen der Ansicht und StartView-Flag wegschreiben
		THROW_FAILED_HRESULT(m_bstrName.WriteToStream (pStm));
		THROW_FAILED_HRESULT(SaveLong (pStm, m_fIsStartView ? VARIANT_TRUE : VARIANT_FALSE));

	// 2 LARGE_INTEGER's freihalten, um später Offsets zu Properties und ViewItems wegschreiben zu können
	WStream Strm;

		THROW_FAILED_HRESULT(pStm -> Clone (Strm.ppi()));

	LARGE_INTEGER li;

		li.QuadPart = 2*sizeof(ULARGE_INTEGER);
		THROW_FAILED_HRESULT(pStm -> Seek(li, STREAM_SEEK_CUR, NULL));

	// jetzt gehts ans wegschreiben
	ULARGE_INTEGER liProps, liItems;

		SaveEnumeratedItems (GetProperties(), pStm, &FMTID_EnumProperties, (ITRiASProperty *)NULL, &liProps);			// Properties
		SaveEnumeratedItemsStg (m_ViewItems, pStm, &FMTID_EnumViewItems, (ITRiASViewItem *)NULL, &liItems);			// ViewItems

	// Namen der BezugsDatenquelle schreiben
		THROW_FAILED_HRESULT(m_bstrRelatedDataSourceName.WriteToStream (pStm));
		THROW_FAILED_HRESULT(m_bstrConnectionFilter.WriteToStream (pStm));

	// und zum Schluß Offsets schreiben
		THROW_FAILED_HRESULT(Strm -> Write (&liProps, sizeof(ULARGE_INTEGER), NULL));
		THROW_FAILED_HRESULT(Strm -> Write (&liItems, sizeof(ULARGE_INTEGER), NULL));

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;

	return S_OK;
}

STDMETHODIMP CTRiASView::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pcbSize) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::GetSizeMax");

	pcbSize -> QuadPart = LenForStream(m_bstrName)
			+ LenForStream(m_bstrRelatedDataSourceName)
			+ LenForStream(m_bstrConnectionFilter)
			+ 4*sizeof(long) + 2*sizeof(LARGE_INTEGER);

#pragma MESSAGE("TODO: calculate sizes of viewitems/viewitem-collection.")
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CTRiASView::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	m_fIsDirty = false;
	m_fIsInitialized = true;		// CreatePropertiesCollection erfordert initialisiertes Objekt

// Properties-collection anlegen und initialisieren
	RETURN_FAILED_HRESULT(CreatePropertiesCollection());
	return CreateViewItemCollection();
}

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASView::CreateProperty (BSTR Name, ITRiASProperty **Property)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == Property)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASView::CreateProperty");

	COM_TRY {
	// evtl. abschließende Leerzeichen abschneiden
	CComBSTR bstrName (TrimRight (Name));

	// Events vorher
	VARIANT_BOOL fVal = VARIANT_FALSE;
		
		THROW_FAILED_HRESULT(Fire_CreatingProperty (bstrName, &fVal)); 
		if (VARIANT_TRUE == fVal)
			return S_FALSE;
		THROW_FAILED_HRESULT(Fire_PropertyToCreate (bstrName));

	// eigentliche Aktion
	CComObject<CTRiASProperty> *pNew = NULL;

		THROW_FAILED_HRESULT(CComObject<CTRiASProperty>::CreateInstance (&pNew));

	WTRiASPropertyCallback Supp;
	WTRiASProperty Prop (pNew);		// required AddRef;

		THROW_FAILED_HRESULT(pNew -> put_Name (bstrName));
		THROW_FAILED_HRESULT(GetPropertySupportSite (bstrName, GetUnknown(), NULL, Supp.ppi()));
		THROW_FAILED_HRESULT(pNew -> SetSite (Supp));	// using IObjectWithSite
		*Property = Prop.detach();

	// Events hinterher
		THROW_FAILED_HRESULT(Fire_PropertyCreated (*Property));
		m_fIsDirty = true;
	} COM_CATCH;

	return S_OK;
}

// Die gegebene Property soll gelöscht werden
STDMETHODIMP CTRiASView::RemoveProperty (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);

// evtl. abschließende Leerzeichen abschneiden
CComBSTR bstrName (TrimRight (Name));

// Events vorher
VARIANT_BOOL fVal = VARIANT_FALSE;
	
	RETURN_FAILED_HRESULT(Fire_DeletingProperty (bstrName, &fVal)); 
	if (VARIANT_TRUE == fVal)
		return S_FALSE;
	RETURN_FAILED_HRESULT(Fire_PropertyToDelete (bstrName));

// eigentliche Aktion
HRESULT hr = ReleasePropertySupportSite (bstrName);	// zuständiges Objekt freigeben

	if (S_OK == hr) {
		m_fIsDirty = true;
		RETURN_FAILED_HRESULT(Fire_PropertyDeleted (bstrName));		// Events hinterher
	}
	return hr;
}

HRESULT CTRiASView::Fire_ChangingView(BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASViewEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ChangingView (OldName, NewName, pVal);
	return S_OK;
}

HRESULT CTRiASView::Fire_ViewToChange(BSTR OldName, BSTR NewName)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASViewEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ViewToChange (OldName, NewName);
	return S_OK;
}

HRESULT CTRiASView::Fire_ViewChanged(IDispatch * pIView)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASViewEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ViewChanged (pIView);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASViewItemEvents
STDMETHODIMP CTRiASView::CreatingViewItem (BSTR Name, VARIANT_BOOL *pVal)
{
	return Fire_CreatingViewItem (Name, pVal);
}

STDMETHODIMP CTRiASView::ViewItemToCreate (BSTR Name)
{
	return Fire_ViewItemToCreate (Name);
}

STDMETHODIMP CTRiASView::ViewItemCreated (IDispatch *pIViewItem)
{
	m_fIsDirty = true;
	return Fire_ViewItemCreated (pIViewItem);
}

STDMETHODIMP CTRiASView::ModifyingViewItem (IDispatch *pIViewItem, VARIANT_BOOL *pVal)
{
	m_bstrRelatedDataSourceName.Empty();		// Datasource interessiert nicht mehr
	return Fire_ModifyingViewItem (pIViewItem, pVal);
}

STDMETHODIMP CTRiASView::ViewItemToModify (IDispatch *pIViewItem)
{
	return Fire_ViewItemToModify (pIViewItem);
}

STDMETHODIMP CTRiASView::ViewItemModified (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_ViewItemModified (Name);
}

STDMETHODIMP CTRiASView::DeletingViewItem (IDispatch *pIViewItem, VARIANT_BOOL *pVal)
{
	return Fire_DeletingViewItem (pIViewItem, pVal);
}

STDMETHODIMP CTRiASView::ViewItemToDelete (IDispatch *pIViewItem)
{
	return Fire_ViewItemToDelete (pIViewItem);
}

STDMETHODIMP CTRiASView::ViewItemDeleted (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_ViewItemDeleted (Name);
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASPropertyEvents
STDMETHODIMP CTRiASView::CreatingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return Fire_CreatingProperty (Name, pVal);
}

STDMETHODIMP CTRiASView::PropertyToCreate (BSTR Name)
{
	return Fire_PropertyToCreate (Name);
}

STDMETHODIMP CTRiASView::PropertyCreated (IDispatch *pIProp)
{
	m_fIsDirty = true;
	return Fire_PropertyCreated (pIProp);
}

STDMETHODIMP CTRiASView::ModifyingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return Fire_ModifyingProperty (Name, pVal);
}

STDMETHODIMP CTRiASView::PropertyToModify (BSTR Name)
{
	return Fire_PropertyToModify (Name);
}

STDMETHODIMP CTRiASView::PropertyModified (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_PropertyModified (Name);
}

STDMETHODIMP CTRiASView::DeletingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	return Fire_DeletingProperty (Name, pVal);
}

STDMETHODIMP CTRiASView::PropertyToDelete (BSTR Name)
{
	return Fire_PropertyToDelete (Name);
}

STDMETHODIMP CTRiASView::PropertyDeleted (BSTR Name)
{
	m_fIsDirty = true;
	return Fire_PropertyDeleted (Name);
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASConnectionEvents-Wrapper
STDMETHODIMP CTRiASView::CreatingConnection (BSTR Name, VARIANT_BOOL *pVal)
{ 
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectionToCreate (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectionCreated (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::OpeningConnection (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectionToOpen (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectionOpened (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ClosingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectionToClose (IDispatch *pIConn)
{
	ATLTRY(WTRiASConnectionEvents(m_ViewItems) -> ConnectionToClose (pIConn));
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectionClosed (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::DeletingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectionToDelete (IDispatch *pIConn)
{
	ATLTRY(WTRiASConnectionEvents(m_ViewItems) -> ConnectionToDelete (pIConn));
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectionDeleted (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::RenamingConnection (BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectionToRename (BSTR OldName, BSTR NewName)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectionRenamed (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ChangingConnectedDatasource (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectedDatasourceToChange (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASView::ConnectedDatasourceChanged (IDispatch *pIConn)
{
	return S_OK;
}

