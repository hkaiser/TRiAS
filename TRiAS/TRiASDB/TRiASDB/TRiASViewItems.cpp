// $Header: /TRiAS/TRiASDB/TRiASDB/TRiASViewItems.cpp 14    15.06.98 21:34 Hartmut Kaiser $
// Copyright © 1998 TRiAS GmbH Potsdam, All rights reserved
// Created: 05/18/1998 08:02:08 PM
//
// @doc
// @module TRiASViewItems.cpp | Implementation of <c CTRiASViewItems>

#include "stdafx.h"

#include <Atl/Ciid.h>
#include <Com/MkHelper.h>

#include "Strings.h"
#include "Wrapper.h"

#include "TRiASViewItems.h"
#include "TRiASViewItem.h"
#include "MakeEnumVariant.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this clas
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASViewItems);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASViewItems::Dump()
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
RT_OBJECT_ENTRY(CLSID_TRiASViewItems, CTRiASViewItems)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASViewItems);
DefineSmartInterface(TRiASViewItemEvents);

namespace {
// Bezeichner zweier ViewItem's vergleichen, dabei evtl. alte Mk's tolerieren (#HK000204)
	inline int CompareViewItemNames (BSTR bstr1, BSTR bstr2)
	{
	int iIndex1 = (*bstr1 == g_cbMkDel[0]) ? 1 : 0;
	int iIndex2 = (*bstr2 == g_cbMkDel[0]) ? 1 : 0;

		return wcscmp (bstr1+iIndex1, bstr2+iIndex2);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASViewItems

STDMETHODIMP CTRiASViewItems::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASViewItems,
		&IID_ITRiASViewItemEvents,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
//
HRESULT CTRiASViewItems::FinalConstruct (void)
{
// instance data
	ATLTRY(m_Enum = new TEnumWTRiASViewItem());
	if (!m_Enum) return E_OUTOFMEMORY;

	m_Enum -> Release();	// Konstruktor hinterläßt RefCnt==1
	return S_OK;
}

void CTRiASViewItems::FinalRelease()
{
	m_Enum.Assign(NULL);	// Enumerator freigeben
	m_pIParent = NULL;
	m_Application = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CTRiASViewItems::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::get_Application");

	*pVal = m_pIParent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASViewItems::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pIParent = newVal;		// no AddRef !
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::get_Count(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::get_Count");

	_ASSERTE(sizeof(LONG) == sizeof(ULONG));	// verify safeness of the following cast
	return m_Enum -> Count((ULONG *)pVal);
}

STDMETHODIMP CTRiASViewItems::get_ItemCount(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::get_ItemCount");

// und jetzt die Collection durchgehen
WEnumWTRiASViewItem Enum;
WTRiASViewItem ViewItem;
long lItemCount = 0;

	RETURN_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
	for (Enum -> Reset(); S_OK == Enum -> Next(1, &ViewItem, NULL); /**/) 
	{
	long lCount = 0;

		if(SUCCEEDED(ViewItem -> get_ItemCount (&lCount)))
			lItemCount += lCount;
	}
	*pVal = lItemCount;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Merge zweier ViewItems
inline 
HRESULT HandleVisType (int iType, ITRiASViewItem *pINew, ITRiASViewItem *pIOld)
{
	if (0 == iType)
		return S_OK;		// nothing to do

// es existiert eine VisualisierungsInfo für diesen Objekttyp im neuen Legendeneintrag
OBJECTTYPE rgType = (OBJECTTYPE)iType;
WDVisInfo VisInfo;
WTRiASObjects Objs;
HRESULT hr = pINew -> get_Objects (rgType, Objs.ppi());

	if (SUCCEEDED(hr)) {
	// es sind Objekte dieses Typs in dieser Objektklasse vorhanden
		RETURN_FAILED_HRESULT(pIOld -> put_Objects (rgType, Objs));
	} 
	else if (TRIASDB_W_NOOBJECTS == hr) {
	// keine Objekte dieses Objekttypes in diesem Legendeneintrag vorhanden
	WTRiASObjects ObjsOld;

		if (FAILED(pIOld -> get_Objects (rgType, ObjsOld.ppi()))) {
		// alter Legendeneintrag besitzt hier noch keine Objektmenge
			RETURN_FAILED_HRESULT(pIOld -> put_ObjectTypes (rgType));
		}
	} else 
		RETURN_FAILED_HRESULT(hr);

	RETURN_FAILED_HRESULT(pINew -> get_VisInfo (rgType, VisInfo.ppi()));
	return pIOld -> put_VisInfo (rgType, VisInfo);
}

STDMETHODIMP CTRiASViewItems::_Add(ITRiASViewItem *pViewItem, VARIANT_BOOL fFullAdd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (fFullAdd) {
		RETURN_FAILED_HRESULT(pViewItem -> put_Application (m_Application));
		RETURN_FAILED_HRESULT(pViewItem -> put_Parent (m_pIParent));
	}

// Feststellen, ob dieses ViewItem bereits vertreten ist
CComBSTR bstr;
WTRiASViewItem Item;

	RETURN_FAILED_HRESULT(pViewItem -> get_Name(CLEARED(&bstr)));
	if (S_OK == m_Enum -> FindItem (bstr, &Item)) {
	// Mergen der VisInfos
	OBJECTTYPE rgOldTypes = OBJECTTYPE_Unknown;
	OBJECTTYPE rgNewTypes = OBJECTTYPE_Unknown;

		RETURN_FAILED_HRESULT(pViewItem -> get_Types(&rgNewTypes));
		RETURN_FAILED_HRESULT(Item -> get_Types(&rgOldTypes));

		RETURN_FAILED_HRESULT(HandleVisType (rgNewTypes & OBJECTTYPE_Point, pViewItem, Item));
		RETURN_FAILED_HRESULT(HandleVisType (rgNewTypes & OBJECTTYPE_Line, pViewItem, Item));
		RETURN_FAILED_HRESULT(HandleVisType (rgNewTypes & OBJECTTYPE_Area, pViewItem, Item));
		RETURN_FAILED_HRESULT(HandleVisType (rgNewTypes & OBJECTTYPE_Text, pViewItem, Item));
		RETURN_FAILED_HRESULT(HandleVisType (rgNewTypes & OBJECTTYPE_Complex, pViewItem, Item));

		return Item -> put_Types ((OBJECTTYPE)(rgOldTypes | rgNewTypes));

	} else
		return m_Enum -> AddItem (bstr, pViewItem);
}

HRESULT CTRiASViewItems::RemoveViewItem(ITRiASViewItem *pIViewItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(pIViewItem -> get_Name (CLEARED(&bstrName)));
		VERIFY(S_OK == m_Enum -> RemoveItem (bstrName));

	} COM_CATCH;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Methods
STDMETHODIMP CTRiASViewItems::Add(BSTR Name, BSTR Type, ITRiASViewItem **ppIViewItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIViewItem) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::Add");

// Erzeugen einer neuen ViewItem und hinzufügen zur Collection
	*ppIViewItem = NULL;
	COM_TRY {
	// Überprüfen, ob ViewItem bereits existiert
	WTRiASViewItem Item;
		
		if (S_OK == m_Enum -> FindItem (Name, &Item)) {
			*ppIViewItem = Item.detach();
			return S_FALSE;		// existiert bereits
		}

	// darf erzeugt werden ?
	VARIANT_BOOL fCreate = VARIANT_FALSE;

		THROW_FAILED_HRESULT(Fire_CreatingViewItem (Name, &fCreate));
		if (fCreate != VARIANT_FALSE)
			return S_FALSE;		// abgebrochen oder Fehler
		THROW_FAILED_HRESULT(Fire_ViewItemToCreate (Name));

	// jetzt wirklich erzeugen
	CIID ClsId (Type, CIID::INITCIID_InitFromProgId);

		if (!ClsId)	ClsId = CLSID_TRiASViewItem;	// default ClsId
	
	WTRiASViewItem ViewItem (ClsId);		// throws hr

		THROW_FAILED_HRESULT(WPersistStreamInit(ViewItem) -> InitNew());

		THROW_FAILED_HRESULT(ViewItem -> put_Application(m_Application));
		THROW_FAILED_HRESULT(ViewItem -> put_Parent(m_pIParent));
		THROW_FAILED_HRESULT(ViewItem -> put_Description(Name));

	// AddViewItem(ViewItem) in ViewItemEvent

	// erfolgreich erzeugt
		THROW_FAILED_HRESULT(Fire_ViewItemCreated (ViewItem));
		*ppIViewItem = ViewItem.detach();

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASViewItems::Item(VARIANT Index, ITRiASViewItem **ppIViewItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIViewItem) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::Item");

CComVariant vIndex;
bool fFound = false;

	*ppIViewItem = NULL;
	COM_TRY {
	WTRiASViewItem ViewItem;
	WTRiASObjects Objs;
	WEnumWTRiASViewItem Enum;

	// die erste Variante ist eine Objektmenge, die wiederzufinden ist
		if (SUCCEEDED(vIndex.ChangeType (VT_DISPATCH, &Index)) &&
		   (SUCCEEDED(V_DISPATCH(&vIndex) -> QueryInterface (Objs.ppi()))))
		{
		// den Namen und die Objekttypen des gesuchten TRiASObjects besorgen
		WMoniker mk;
		CComBSTR bstrMkName, bstrName;
		OBJECTTYPE rgType = OBJECTTYPE_Unknown;

			THROW_FAILED_HRESULT(MkGetMoniker (Objs, OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, mk.ppi()));
			THROW_FAILED_HRESULT(MkGetDisplayName (mk, CLEARED(&bstrMkName)));

			THROW_FAILED_HRESULT(Objs -> get_Types(&rgType));

		// und jetzt in der Collection wiederfinden
			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			for (Enum -> Reset(); S_OK == Enum -> Next(1, &ViewItem, NULL); /**/) 
			{
			CComBSTR bstrItemName;
			OBJECTTYPE rgItemType = OBJECTTYPE_Unknown;
			HRESULT hr = S_OK;

				THROW_FAILED_HRESULT(ViewItem -> get_ObjectTypes(&rgItemType));
				THROW_FAILED_HRESULT(hr = ViewItem -> get_Name(CLEARED(&bstrItemName)));

				if (S_FALSE == hr) {	// keine Objektmenge drin, also ist dies die Description
					if (!bstrName) 		// nur einmal besorgen
						THROW_FAILED_HRESULT(Objs -> get_Name (CLEARED(&bstrName)));

				// über ObjsName vergleichen
				// die übergebenen Objekttypen müssen _alle_ hier enthalten sein.
					if (rgType == (rgType & rgItemType) && !CompareViewItemNames (bstrName, bstrItemName)) {
						*ppIViewItem = ViewItem.detach();
						fFound = true;
						break;
					}
				} else {
				// über monikerName vergleichen
				// die übergebenen Objekttypen müssen _alle_ hier enthalten sein.
					if (rgType == (rgType & rgItemType) && !CompareViewItemNames (bstrMkName, bstrItemName)) {
						*ppIViewItem = ViewItem.detach();
						fFound = true;
						break;
					}
				}
			}

		} else if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
		// Verhindern, daß als Nummern als Zeichenkette falsch interpretiert werden
		ULONG ulCnt = 0;

			THROW_FAILED_HRESULT(m_Enum -> Count(&ulCnt));
			if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > ulCnt)
				return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::Item");

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(Enum -> Reset());

			if (V_I4(&vIndex) > 1)
			{
				THROW_FAILED_HRESULT(Enum -> Skip (V_I4(&vIndex)-1));
			}
			if (S_OK == Enum -> Next (1, &ViewItem, NULL))
			{
				*ppIViewItem = ViewItem.detach();
				fFound = true;
			}

		} else if (SUCCEEDED(vIndex.ChangeType (VT_BSTR, &Index))) {
		// ViewItem über seinen Namen suchen
			if (S_OK == m_Enum -> FindItem (CComBSTR(V_BSTR(&vIndex)), &ViewItem)) {
				*ppIViewItem = ViewItem.detach();
				fFound = true;
			}

		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::Item");

	} COM_CATCH;

	if (!fFound)
		return REPORT_DBERROR(TRIASDB_E_UNKNOWN_VIEWITEM);

	return S_OK;
}

STDMETHODIMP CTRiASViewItems::Remove(VARIANT Index)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

HRESULT hr_return = S_OK;

	COM_TRY {
	// darf gelöscht werden ?
	VARIANT_BOOL fDelete = VARIANT_FALSE;
	WEnumWTRiASViewItem Enum;
	WTRiASViewItem ViewItem;
	WTRiASObjects Objs;

	CComVariant vIndex;
	CComBSTR bstrName;

	// die erste Variante ist eine Objektmenge, die wiederzufinden ist
		if (SUCCEEDED(vIndex.ChangeType (VT_DISPATCH, &Index)) &&
		   (SUCCEEDED(V_DISPATCH(&vIndex) -> QueryInterface (Objs.ppi()))))
		{
		// den Namen und die Objekttypen des gesuchten TRiASObjects besorgen
		CComBSTR bstrName;
		OBJECTTYPE rgType = OBJECTTYPE_Unknown;

			THROW_FAILED_HRESULT(Objs -> get_Name(CLEARED(&bstrName)));
			THROW_FAILED_HRESULT(Objs -> get_Types(&rgType));

		// und jetzt in der Collection wiederfinden
			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));

			for (Enum -> Reset(); S_OK == Enum -> Next(1, &ViewItem, NULL); /**/) 
			{
			CComBSTR bstrItemName;
			OBJECTTYPE rgItemType = OBJECTTYPE_Unknown;

				THROW_FAILED_HRESULT(ViewItem -> get_Name(CLEARED(&bstrItemName)));
				THROW_FAILED_HRESULT(ViewItem -> get_ObjectTypes(&rgItemType));

				if (rgType == rgItemType && !CompareViewItemNames (bstrName, bstrItemName)) {
					THROW_FAILED_HRESULT(Fire_DeletingViewItem (ViewItem, &fDelete));
					if (fDelete == VARIANT_FALSE) {
					CComSemaphore<_ThreadModel> Sem (m_lSemDel);	// doppeltes löschen verhindern

						THROW_FAILED_HRESULT(Fire_ViewItemToDelete (ViewItem));
						continue;
					}
				// wenn nicht gelöscht werden soll, dann einfach durchfallen
				// ...
					hr_return = S_FALSE;
				} 
				THROW_FAILED_HRESULT(m_Enum -> AddItem(bstrName, ViewItem));
			}

		} else if (VT_BSTR != V_VT(&Index) && SUCCEEDED(vIndex.ChangeType (VT_I4, &Index))) {
		// Verhindern, daß als Nummern als Zeichenkette falsch interpretiert werden
		ULONG ulCnt = 0L;

			THROW_FAILED_HRESULT(m_Enum -> Count(&ulCnt));
			if (V_I4(&vIndex) <= 0 || (ULONG)V_I4(&vIndex) > ulCnt)
				return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::Remove");

		// Verbindung herauslöschen
		long lCnt = 1;

			THROW_FAILED_HRESULT(m_Enum -> Clone (Enum.ppi()));
			THROW_FAILED_HRESULT(m_Enum -> Clear());

		// alle außer dem einen Kopieren
			for (Enum -> Reset(); S_OK == Enum -> Next (1, &ViewItem, NULL); lCnt++)
			{
				THROW_FAILED_HRESULT(ViewItem -> get_Name (CLEARED(&bstrName)));
				if (lCnt == V_I4(&vIndex)) {
					THROW_FAILED_HRESULT(Fire_DeletingViewItem (ViewItem, &fDelete));
					if (fDelete == VARIANT_FALSE) {
					CComSemaphore<_ThreadModel> Sem (m_lSemDel);	// doppeltes löschen verhindern

						THROW_FAILED_HRESULT(Fire_ViewItemToDelete (ViewItem));
						continue;
					}
				// wenn nicht gelöscht werden soll, dann einfach durchfallen
				// ...
					hr_return = S_FALSE;
				} 
				THROW_FAILED_HRESULT(m_Enum -> AddItem(bstrName, ViewItem));
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
			THROW_FAILED_HRESULT(Fire_DeletingViewItem (ViewItem, &fDelete));
			if (fDelete != VARIANT_FALSE) 
				return S_FALSE;		// soll nicht gelöscht werden
			{
			CComSemaphore<_ThreadModel> Sem (m_lSemDel);	// doppeltes löschen verhindern

				THROW_FAILED_HRESULT(Fire_ViewItemToDelete (ViewItem));
			}
			VERIFY(S_OK == m_Enum -> RemoveItem (CComBSTR(V_BSTR(&vIndex))));
			bstrName = V_BSTR(&vIndex);

		} else
			return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::Remove");

	// erfolgreich gelöscht
		THROW_FAILED_HRESULT(Fire_ViewItemDeleted (bstrName));

	} COM_CATCH;

	return hr_return;
}

STDMETHODIMP CTRiASViewItems::_NewEnum (IUnknown **ppIEnum)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIEnum) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::_NewItem");

	return MakeEnumVARIANT (m_Enum, GetUnknown(), ppIEnum);
}

STDMETHODIMP CTRiASViewItems::_Clone(ITRiASViewItems **ppIViewItems)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == ppIViewItems) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItems::_Clone");

CComObject<CTRiASViewItems> *pNew = NULL;

	COM_TRY {
		THROW_FAILED_HRESULT(CComObject<CTRiASViewItems>::CreateInstance (&pNew));
		THROW_FAILED_HRESULT(pNew -> InitEnum (m_Enum));

		THROW_FAILED_HRESULT(pNew -> put_Application (m_Application));
		THROW_FAILED_HRESULT(pNew -> put_Parent (m_pIParent));

	WTRiASViewItems ViewItems (pNew);		// pending AddRef

		*ppIViewItems = ViewItems.detach();

	} COM_CATCH_OP(delete pNew);

	return S_OK;
}

STDMETHODIMP CTRiASViewItems::SetEventSink (IUnknown *pIUnk, VARIANT_BOOL fAdvise)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (fAdvise) {
		_ASSERTE(0 == m_dwCookie);
		return AtlAdvise (pIUnk, GetUnknown(), IID_ITRiASViewItemEvents, &m_dwCookie);
	} 
	else {
		if (NULL == pIUnk && NULL == m_pIParent) {
			_ASSERTE(0 == m_dwCookie);
			return S_OK;		// Erstinitialisierung der Ansicht
		}

	WUnknown Unk (pIUnk);

		if (!Unk.IsValid()) {
			Unk = m_pIParent;		// altes Bezugsobjekt verwenden
			_ASSERTE(Unk.IsValid());
		}
		_ASSERTE(m_dwCookie != 0);

	DWORD dwCookie = m_dwCookie;

		m_dwCookie = 0L;
		return AtlUnadvise (Unk, IID_ITRiASViewItemEvents, dwCookie);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Events verschicken
HRESULT CTRiASViewItems::Fire_CreatingViewItem (BSTR Name, VARIANT_BOOL *pVal)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewItemEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> CreatingViewItem (Name, pVal);
	return S_OK;
}

HRESULT CTRiASViewItems::Fire_ViewItemToCreate (BSTR Name)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewItemEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ViewItemToCreate (Name);
	return S_OK;
}

HRESULT CTRiASViewItems::Fire_ViewItemCreated (IDispatch * pIConn)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewItemEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ViewItemCreated (pIConn);
	return S_OK;
}

HRESULT CTRiASViewItems::Fire_DeletingViewItem (IDispatch *pIConn, VARIANT_BOOL * pVal)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewItemEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> DeletingViewItem (pIConn, pVal);
	return S_OK;
}

HRESULT CTRiASViewItems::Fire_ViewItemToDelete (IDispatch * pIConn)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewItemEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ViewItemToDelete (pIConn);
	return S_OK;
}

HRESULT CTRiASViewItems::Fire_ViewItemDeleted(BSTR Name)
{
	_ASSERTE(NULL != m_pIParent);
	if (!m_pIParent) return E_POINTER;

WTRiASViewItemEvents Events;

	if (SUCCEEDED(m_pIParent -> QueryInterface (Events.ppi())))
		return Events -> ViewItemDeleted (Name);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASViewItemEvents
STDMETHODIMP CTRiASViewItems::CreatingViewItem (BSTR Name, VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ViewItemToCreate (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ViewItemCreated (IDispatch *pIViewItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	WTRiASViewItem ViewItem (pIViewItem);

		THROW_FAILED_HRESULT(_Add(ViewItem, VARIANT_TRUE));

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ModifyingViewItem (IDispatch *pIViewItem, VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ViewItemToModify (IDispatch *pIViewItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

#pragma MESSAGE("TODO: Umbenennen von ViewItem's muß in der zugehörigen collection nachgezogen werden !")

	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ViewItemModified (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::DeletingViewItem (IDispatch *pIViewItem, VARIANT_BOOL *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ViewItemToDelete (IDispatch *pIViewItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

// nur behandeln, wenn nicht wir derzeit bearbeitet werden
	if (IsSemaphoreSignaled (m_lSemDel, *this)) 
		return S_OK;

	COM_TRY {
	WTRiASViewItem ViewItem (pIViewItem);

		THROW_FAILED_HRESULT(RemoveViewItem (ViewItem));

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ViewItemDeleted (BSTR Name)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASConnectionEvents-Wrapper
STDMETHODIMP CTRiASViewItems::CreatingConnection (BSTR Name, VARIANT_BOOL *pVal)
{ 
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectionToCreate (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectionCreated (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::OpeningConnection (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectionToOpen (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectionOpened (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ClosingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

namespace {
// Feststellen, ob ein ViewItem zu einer bestimmten Connection gehört
	HRESULT ShouldRemoveViewItem (ITRiASViewItem *pIViewItem, ITRiASConnection *pIConn)
	{
	WTRiASConnection TargetConn (pIConn);

		for (int i = 0; i < _countof(g_cbObjectTypes); ++i) {
		WTRiASObjects Objs;

			if (SUCCEEDED(pIViewItem -> get_Objects(g_cbObjectTypes[i], Objs.ppi()))) {
			WTRiASConnection Conn;

				if (SUCCEEDED(FindSpecificParent (Objs, Conn.ppi())) && Conn == TargetConn)
					return S_OK;		// jawohl, gehört dazu
			}
		}
		return S_FALSE;		// nicht entfernen
	}
}

STDMETHODIMP CTRiASViewItems::ConnectionToClose (IDispatch *pIConn)
{
	COM_TRY {
	WTRiASConnection Conn (pIConn);
	WEnumWTRiASViewItem Enum;
	WTRiASViewItem ViewItem;

		if (SUCCEEDED(m_Enum -> Clone (Enum.ppi()))) {
			for (Enum -> Reset(); S_OK == Enum -> Next(1, &ViewItem, NULL); /**/) 
			{
			CTRiASViewItem *pItem = NULL;

				QueryImplementation(ViewItem, &pItem);
				_ASSERTE(NULL != pItem);

				if (S_OK == ShouldRemoveViewItem(ViewItem, Conn)) 
					pItem -> SetShouldRemoved(true);
				else
					pItem -> SetShouldRemoved(false);
			}
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectionClosed (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::DeletingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectionToDelete (IDispatch *pIConn)
{
	COM_TRY {
	WTRiASConnection Conn (pIConn);
	WEnumWTRiASViewItem Enum;
	WTRiASViewItem ViewItem;

		if (SUCCEEDED(m_Enum -> Clone (Enum.ppi()))) {
			for (Enum -> Reset(); S_OK == Enum -> Next(1, &ViewItem, NULL); /**/) 
			{
			CTRiASViewItem *pItem = NULL;

				if (SUCCEEDED(QueryImplementation(ViewItem, &pItem)) && pItem -> GetShouldRemoved())
				{
					THROW_FAILED_HRESULT(RemoveViewItem (ViewItem));
				}
			}
		}
	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectionDeleted (BSTR bstrName)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::RenamingConnection (BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectionToRename (BSTR OldName, BSTR NewName)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectionRenamed (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ChangingConnectedDatasource (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectedDatasourceToChange (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItems::ConnectedDatasourceChanged (IDispatch *pIConn)
{
	return S_OK;
}

