// TRiASViewItem.cpp : Implementation of CTRiASViewItem

#include "stdafx.h"

#include <VisInfo_i.c>

#include <Atl/Ciid.h>
#include <Com/MemoryHelper.h>
#include <Com/MkHelper.h>

#include "PersistEnum.h"
#include "TRiASDBDispIds.h"
#include "Strings.h"
#include "Wrapper.h"

#include "TRiASProperty.h"
#include "TRiASViewItem.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this clas
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASViewItem);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASViewItem::Dump()
{
CComBSTR bstrName("<Unknown>");

	if (m_bstrMkName.Length() > 0)
		bstrName = m_bstrMkName;
	else if (m_bstrDesc.Length() > 0)
		bstrName = m_bstrDesc;

	D_OUTF2(1, 
		"CTRiASViewItem: pending %ls, ", bstrName,
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
RT_OBJECT_ENTRY(CLSID_TRiASViewItem, CTRiASViewItem)

/////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASViewItemEvents);		// WTRiASViewItemEvents
DefineSmartInterface(TRiASQueryVisInfo);		// WTRiASQueryVisInfo

DefineSmartInterface(OleObject);				// WOleObject
DefineSmartInterface(BindCtx);					// WBindCtx
DefineSmartInterface(EnumMoniker);				// WEnumMoniker

/////////////////////////////////////////////////////////////////////////////
// lokale Daten

namespace {
// Feld aller bekannten Objekttypen mit zugehörigen CLSID's
	typedef struct tagVISTYPES {
		OBJECTTYPE rgType;
		const CLSID *pClsId;
	} VISTYPES;

	const VISTYPES g_rgVisTypes[] = {
		{ OBJECTTYPE_Point, &CLSID_PointVisInfo, },
		{ OBJECTTYPE_Line, &CLSID_LineVisInfo, },
		{ OBJECTTYPE_Area, &CLSID_AreaVisInfo, },
		{ OBJECTTYPE_Text, &CLSID_TextVisInfo, },
		{ OBJECTTYPE_Complex, &CLSID_DefaultVisInfo, },
		{ OBJECTTYPE_Unknown, &GUID_NULL, },
	};

	inline int GetMatchingIndex (OBJECTTYPE rgType)
	{
		switch (rgType) {
		case OBJECTTYPE_Point:
			return 0;
		case OBJECTTYPE_Line:
			return 1;
		case OBJECTTYPE_Area:
	//	case OBJECTTYPE_Circle:
			return 2;
		case OBJECTTYPE_Text:
			return 3;
		case OBJECTTYPE_Complex:		// all at once
		case OBJECTTYPE_Unknown:		// dont care
			return 4;
		default:
			break;
		}
		return -1;		// Fehlerhafter bzw. mehr als ein Objekttyp
	}

///////////////////////////////////////////////////////////////////////////////
// _lokales_ Binden einer Objektklasse über einen gegebenen Moniker
	inline 
	HRESULT MkBindToObjectLocal(IMoniker *pIMk, ITRiASObjects **ppIObjs)
	{
	WBindCtx ctx;

		RETURN_FAILED_HRESULT(CreateBindCtx (0, ctx.ppi()));

	BIND_OPTS2 bndOpts;

		bndOpts.cbStruct = sizeof(BIND_OPTS2);
		RETURN_FAILED_HRESULT(ctx -> GetBindOptions(&bndOpts));
		bndOpts.dwClassContext = CLSCTX_INPROC;		// nur lokal instantiieren
		RETURN_FAILED_HRESULT(ctx -> SetBindOptions(&bndOpts));

	WMoniker mkPid, mk;

		RETURN_FAILED_HRESULT(CreatePIDMoniker (mkPid.ppi()));
		RETURN_FAILED_HRESULT(mkPid -> ComposeWith(pIMk, FALSE, mk.ppi()));

	// zuerst nachsehen, ob die Objektklasse überhaupt existiert
		if (S_OK == mk -> IsRunning(ctx, NULL, NULL))
			return MkBindToObject(mk, ppIObjs, NULL, ctx);
			
		return TRIASDB_E_UNKNOWN_OBJECTS;	// Objektklasse existiert nicht (mehr)
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTRiASViewItem

STDMETHODIMP CTRiASViewItem::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASViewItem,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// IPersist
STDMETHODIMP CTRiASViewItem::GetClassID (CLSID *pClassID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pClassID) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::GetClassID");

	*pClassID = CLSID_TRiASViewItem;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStream
STDMETHODIMP CTRiASViewItem::IsDirty (void)
{
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASViewItem::Load (LPSTREAM pStm)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

// Version prüfen
long lSignature = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lSignature));			// Signatur
	if (VIEWITEM_SIGNATURE != lSignature)
		return TRIASDB_E_BADOBJECTSIGNATURE;

long lVersion = 0L;

	RETURN_FAILED_HRESULT(LoadLong (pStm, lVersion));				// VersionInfo
	if ((lVersion & ~VIEWITEM_VERSION_MINOR_MASK) > LASTKNOWN_VIEWITEM_VERSION)
		return TRIASDB_W_NEWERVIEWITEM;

	m_bstrDesc.Empty();
	RETURN_FAILED_HRESULT(m_bstrDesc.ReadFromStream (pStm));		// Name

// VisInfos einlesen
	_ASSERTE(sizeof(LONG) == sizeof(OBJECTTYPE));
	RETURN_FAILED_HRESULT(LoadLong (pStm, (LONG &)m_rgTypes));		// VisTypes
	RETURN_FAILED_HRESULT(LoadLong (pStm, (LONG &)m_rgDefTypes));	// DefaultVisTypes
	if (lVersion >= VIEWITEM_VERSION_101) {
	// vordefinierte Typen sind jetzt erst dazugekommen
		RETURN_FAILED_HRESULT(LoadLong (pStm, (LONG &)m_rgPreDefinedTypes));	// DefaultVisTypes
	}

// Enumeratoren initialisieren
	RETURN_FAILED_HRESULT(CreatePropertiesCollection (false));

// jetzt alles laden, was zu diesem ViewItem gehört
CTRiASObjectsWrapper Objects (this);
WTRiASObjects Objs;

	_ASSERTE(_countof(m_VisInfo) == _countof(m_ObjsHandles));
	for (int i = 0; i < _countof(m_VisInfo); i++) {
		if (g_rgVisTypes[i].rgType & m_rgTypes) {
		// VisInfo einlesen
			RETURN_FAILED_HRESULT(::OleLoadFromStream (pStm, IID_DVisInfo, m_VisInfo[i].ppv()));

		// Objektmenge nur dann laden, wenn wirklich eine existiert hat
		SAVEMODE rgMode;

			RETURN_FAILED_HRESULT(LoadLong(pStm, (LONG &)rgMode));

			if (SAVEMODE_SAVEOBJECTMONIKER == rgMode) {
			WMoniker mk;

				_ASSERTE(!m_mkName[i].IsValid());		// darf noch nicht initialisiert sein
				RETURN_FAILED_HRESULT(::OleLoadFromStream (pStm, IID_IMoniker, mk.ppv()));

#if defined(_DEBUG)
			// DisplayName für DEBUG-Zwecke erzeugen
			CComBSTR bstrDebug;

				RETURN_FAILED_HRESULT(MkGetDisplayName (mk, CLEARED(&bstrDebug)));
#endif // _DEBUG

			// evtl. altes Monikerformat konvertieren
				if (lVersion < VIEWITEM_VERSION_103) {
				WTRiASObjects Objs;

					if (SUCCEEDED(MkBindToObjectLocal (mk, Objs.ppi()))) {
					WMoniker mkNew;

						THROW_FAILED_HRESULT(MkGetMoniker (Objs, OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, mkNew.ppi()));
						mk = mkNew;			// neuen Moniker weiterverwenden
						Objects[i] = Objs;	// da wir es einmal gebunden haben ...

					// beim ConnPnt anmelden
						if (0 == m_dwObjsCookie && Objs.IsValid())
						{
							THROW_FAILED_HRESULT(AtlAdvise(Objs, GetUnknown(), IID_ITRiASObjectsEvents, &m_dwObjsCookie));
						}
					}
				} 
				else {
				// hier künstlich als vordefiniert kennzeichnen
					SetType (m_rgPreDefinedTypes, g_rgVisTypes[i].rgType);
				}

			// erstmal nur Moniker einlesen, wird später bei Bedarf instantiiert
				m_mkName[i] = mk;			// Moniker für spätere Verwendung festhalten
			} 
			else if (SAVEMODE_SAVEOBJECTDIRECTLY == rgMode) {
			// Objects-collection direkt einlesen
				RETURN_FAILED_HRESULT(::OleLoadFromStream (pStm, IID_ITRiASObjects, Objs.ppv()));
				Objects[i] = Objs;

			// beim ConnPnt anmelden
				if (0 == m_dwObjsCookie && Objs.IsValid())
				{
					THROW_FAILED_HRESULT(AtlAdvise(Objs, GetUnknown(), IID_ITRiASObjectsEvents, &m_dwObjsCookie));
				}
			}
		    else if (SAVEMODE_UNKNOWN == rgMode) {
            // nur VisInfo gegeben
                SetType (m_rgPreDefinedTypes, g_rgVisTypes[i].rgType);
            }
        }
	}

	if (lVersion >= VIEWITEM_VERSION_102) {
	// Enumerator laden (Identifikator-Merkmale), erst ab V1.02
	CInitProperty<CTRiASViewItem> InitProp(this);

		LoadEnumeratedItemsEx(GetProperties(), pStm, &FMTID_EnumProperties, InitProp, VIEWITEM_VERSION_104 <= lVersion);			// Properties lesen und initialisieren
	}

	if (lVersion >= VIEWITEM_VERSION_103) {
		m_bstrMkName.Empty();
		RETURN_FAILED_HRESULT(m_bstrMkName.ReadFromStream (pStm));		// MkName (ab VIEWITEM_VERSION_103)
	}

	m_fIsDirty = false;
	m_fIsInitialized = true;

	return S_OK;
}

STDMETHODIMP CTRiASViewItem::Save (LPSTREAM pStm, BOOL fClearDirty)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	COM_TRY {
		THROW_FAILED_HRESULT(SaveLong (pStm, VIEWITEM_SIGNATURE));
		THROW_FAILED_HRESULT(SaveLong (pStm, LASTKNOWN_VIEWITEM_VERSION));

		THROW_FAILED_HRESULT(m_bstrDesc.WriteToStream (pStm));		// Name

	// VisInfos wegschreiben
		THROW_FAILED_HRESULT(SaveLong (pStm, m_rgTypes));			// Types
		THROW_FAILED_HRESULT(SaveLong (pStm, m_rgDefTypes));		// DefaultTypes
		THROW_FAILED_HRESULT(SaveLong (pStm, m_rgPreDefinedTypes));	// Types ohne zugehörige Objekte (ab VIEWITEM_VERSION_101)

	CTRiASObjectsWrapper Objects (this);

		_ASSERTE(_countof(m_VisInfo) == _countof(m_ObjsHandles));
		for (int i = 0; i < _countof(m_VisInfo); i++) {
			if (m_VisInfo[i].IsValid()) {
			// VisInfo wegschreiben
				THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(m_VisInfo[i]), pStm));

			// Objects-collection speichern (wenn eine existiert)
			WTRiASObjects Objs (Objects[i]);

				_ASSERTE(Objs.IsValid() || HasType(m_rgPreDefinedTypes, g_rgVisTypes[i].rgType));
				if (Objs.IsValid()) {
				WMoniker mk;

					if (SUCCEEDED(MkGetMoniker (Objs, OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, mk.ppi()))) {
						THROW_FAILED_HRESULT(SaveLong (pStm, SAVEMODE_SAVEOBJECTMONIKER));
						THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(mk), pStm));
					} else {
						THROW_FAILED_HRESULT(SaveLong (pStm, SAVEMODE_SAVEOBJECTDIRECTLY));
						THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(Objs), pStm));
					}
				} 
				else if (m_mkName[i].IsValid()) {
					THROW_FAILED_HRESULT(SaveLong (pStm, SAVEMODE_SAVEOBJECTMONIKER));
					THROW_FAILED_HRESULT(::OleSaveToStream (WPersistStream(m_mkName[i]), pStm));
				} 
				else {
                    // irgend was muß gegeben sein
					_ASSERTE(Objs.IsValid() || m_mkName[i].IsValid() || 
                        HasType(m_rgPreDefinedTypes, g_rgVisTypes[i].rgType));
					THROW_FAILED_HRESULT(SaveLong (pStm, SAVEMODE_UNKNOWN));
				}
			}
		}

	// Properties auf jeden Fall wegschreiben (ab VIEWITEM_VERSION_102)
		SaveEnumeratedItems (GetProperties(), pStm, &FMTID_EnumProperties, (ITRiASProperty *)NULL);		// Properties
		THROW_FAILED_HRESULT(m_bstrMkName.WriteToStream (pStm));		// MkName (ab VIEWITEM_VERSION_103)

	} COM_CATCH;

	if (fClearDirty)
		m_fIsDirty = false;

	return S_OK;
}

STDMETHODIMP CTRiASViewItem::GetSizeMax (ULARGE_INTEGER *pcbSize)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pcbSize) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::GetSizeMax");

	pcbSize -> QuadPart = LenForStream(m_bstrDesc) + 2*sizeof(long);

	COM_TRY {
	ULARGE_INTEGER uli;
	CTRiASObjectsWrapper Objects (this);

		_ASSERTE(_countof(m_VisInfo) == _countof(m_ObjsHandles));
		for (int i = 0; i < _countof(m_VisInfo); i++) {
			if (m_VisInfo[i].IsValid()) {
				THROW_FAILED_HRESULT(WPersistStream(m_VisInfo[i]) -> GetSizeMax (&uli));
				pcbSize -> QuadPart += uli.QuadPart;

			WTRiASObjects Objs (Objects[i]);

				_ASSERTE(Objs.IsValid());
				if (Objs.IsValid()) {
					THROW_FAILED_HRESULT(WPersistStream(Objs) -> GetSizeMax (&uli));
					pcbSize -> QuadPart += uli.QuadPart;
				}
			}
		}
		pcbSize -> QuadPart += LenForStream(m_bstrMkName);		// (ab VIEWITEM_VERSION_103)

	} COM_CATCH;

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// IPersistStreamInit
STDMETHODIMP CTRiASViewItem::InitNew (void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (m_fIsInitialized)
		return E_UNEXPECTED;

	m_fIsDirty = false;			// damit das Objekt vom ObjMan weggeschrieben wird
	m_fIsInitialized = true;		// CreatePropertiesCollection erfordert initialisiertes Objekt

// Properties-collection anlegen und initialisieren
	RETURN_FAILED_HRESULT(CreatePropertiesCollection());
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CTRiASViewItem::get_Application(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_Application");

	*pVal = m_Application;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::put_Application(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Application = newVal;

// auch alle untergeordneten Objekte befrieden
	if (!!m_Application) {
		_ASSERTE(_countof(m_VisInfo) == _countof(m_ObjsHandles));
		for (int i = 0; i < _countof(m_VisInfo); i++) {
			if (m_VisInfo[i].IsValid()) 
				m_VisInfo[i] -> put_Application (newVal);
		}
	}
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::get_Parent(IDispatch **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_Application");

	*pVal = m_Parent;
	if (NULL != *pVal) LPUNKNOWN(*pVal) -> AddRef();

	return S_OK;
}

STDMETHODIMP CTRiASViewItem::put_Parent(IDispatch *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	if (m_Parent == WDispatch(newVal))
		return S_OK;	// wenn's kein neuer ist, dann wieder raus

	m_Parent = newVal;

// evtl. alle SubObjekte von ihrem Bezug abhängen
CTRiASObjectsWrapper Objects (this);

	if (NULL == newVal) {
		_ASSERTE(_countof(m_VisInfo) == _countof(m_ObjsHandles));
		for (int i = 0; i < _countof(m_VisInfo); i++) {
			if (m_VisInfo[i].IsValid()) 
				m_VisInfo[i] -> put_Parent (NULL);

			if (0 != m_dwObjsCookie && Objects[i].IsValid()) {
				if (SUCCEEDED(AtlUnadvise(Objects[i], IID_ITRiASObjectsEvents, m_dwObjsCookie)))
					m_dwObjsCookie = 0;
			}
		}

	// Properties freigeben
		FreePropertiesCollection();

	// PropertySupportObjekte freigeben
		ReleasePropertySupportObjects();

		m_fIsDirty = false;
		m_fIsInitialized = false;		// muß neu initialisert werden

	} else {
	// Parent muß ViewItemEvents verschicken können
		_ASSERTE(SupportsInterface(m_Parent, (ITRiASViewItemEvents *)NULL));
		_ASSERTE(_countof(m_VisInfo) == _countof(m_ObjsHandles));

		for (int i = 0; i < _countof(m_VisInfo); i++) {
			if (m_VisInfo[i].IsValid()) 
				m_VisInfo[i] -> put_Parent (m_Parent);

		// evtl. beim ConnectionPoint anmelden
			if (0 == m_dwObjsCookie && Objects[i].IsValid()) 
			{
				RETURN_FAILED_HRESULT(AtlAdvise(Objects[i], GetUnknown(), IID_ITRiASObjectsEvents, &m_dwObjsCookie));
			}

		// der Parent der Objects-Objekte wird separat behandelt !
		}
	}
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::get_Description(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_Description");

// Wenn keine BeschreibungsInfo gesetzt ist, dann liefert diese Funktion den Namen
	if (!m_bstrDesc || 0 == m_bstrDesc.Length())
		return get_Name(pVal);

// Beschreibungsinfo ist gesetzt
CComBSTR bstr (m_bstrDesc);

	if (!bstr)
		return Error(g_cbNoMemory, E_OUTOFMEMORY);
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::put_Description(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

VARIANT_BOOL fModify = VARIANT_FALSE;

	RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), &fModify));
	if (fModify != VARIANT_FALSE)
		return S_FALSE;		// nicht umbenennen
	RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));

// evtl. ist die neue Beschreibung ein MkString: letzten Teilstring herauslösen
CComBSTR bstrDesc (newVal);

	COM_TRY {
	// die Zeichenkette ist (vielleicht) ein Moniker (beginnt mit MkConnection)
	WMoniker mk;
	WBindCtx Ctx;
	ULONG ulEaten = 0L;

		THROW_FAILED_HRESULT(CreateBindCtx (0, Ctx.ppi()));
		if (SUCCEEDED(MkParseDisplayName(Ctx, g_cbMkDel[0] == newVal[0] ? &newVal[1] : newVal, &ulEaten, mk.ppi()))) {
		WEnumMoniker mkEnum;

			THROW_FAILED_HRESULT(mk -> Enum (FALSE, mkEnum.ppi()));
			if (mkEnum.IsValid()) {
			WMoniker mkLast;
			CComBSTR bstr, bstrName;

				THROW_FAILED_HRESULT(mkEnum -> Reset());
				THROW_FAILED_HRESULT(mkEnum -> Next(1, mkLast.ppi(), NULL));
				THROW_FAILED_HRESULT(MkGetDisplayName (mkLast, CLEARED(&bstr)));
				if (StringIsOKS (bstr, NULL, CLEARED(&bstrName))) {
					if (bstrName.Length() > 0) 
						bstrDesc = bstrName;
					m_bstrMkName = newVal;
					if (!m_bstrMkName)
						return Error (g_cbNoMemory, E_OUTOFMEMORY);
				}
			}
		}
	} COM_CATCH;

// neuen Beschreibungstext setzen
	m_bstrDesc = bstrDesc;
	if (!m_bstrDesc)
		return Error (g_cbNoMemory, E_OUTOFMEMORY);

	RETURN_FAILED_HRESULT(Fire_ViewItemModified(m_bstrDesc));
	m_fIsDirty = true;
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::get_Name(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_Name");

int iColl = HasObjectsCollection();

// Name entspricht (sollte) MonikerString der Objs-Objekte
	if (-1 == iColl) {
		if (m_bstrMkName.Length() > 0) {
		CComBSTR bstr (m_bstrMkName);

			if (!bstr)
				return Error(g_cbNoMemory, E_OUTOFMEMORY);
			*pVal = bstr.Detach();
			return S_FALSE;
		} 
		else if (m_bstrDesc.Length() > 0) {
		CComBSTR bstr (m_bstrDesc);

			if (!bstr)
				return Error(g_cbNoMemory, E_OUTOFMEMORY);
			*pVal = bstr.Detach();
			return S_FALSE;
		} 
		else
			return REPORT_DBERROR_ROUT(TRIASDB_E_OBJECT_NOT_INITIALIZED, "CTRiASViewItem::get_Name");
	}

// da alle Objektmengen (per Definition) einen identischen Namen haben, 
// wird der erste genommen, den wir finden können
	if (!m_bstrMkName || 0 == m_bstrMkName.Length()) {
	CTRiASObjectsWrapper Objects (this);

		_ASSERTE(0 <= iColl && iColl < _countof(m_ObjsHandles));
		if (Objects[iColl].IsValid()) {
		// instantiierte Objektmenge nach ihrem MonikerString befragen
		WMoniker mk;

			RETURN_FAILED_HRESULT(MkGetMoniker (Objects[iColl], OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, mk.ppi()));
			RETURN_FAILED_HRESULT(MkGetDisplayName (mk, CLEARED(&m_bstrMkName)));			// ist immer identisch mit Moniker der Objektmenge
		}
		else if (m_mkName[iColl].IsValid()) {
		// erstmal nur ein Moniker vorhanden
			RETURN_FAILED_HRESULT(MkGetDisplayName (m_mkName[iColl], CLEARED(&m_bstrMkName)));
		}
	} 
	
CComBSTR bstrResult (m_bstrMkName);

	*pVal = bstrResult.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::get_ObjectTypes (OBJECTTYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_ObjectTypes");

	*pVal = OBJECTTYPE_Unknown;
	if (-1 == HasObjectsCollection() && 0 == BitCount(m_rgPreDefinedTypes))
		return S_FALSE;		// nothing else to do
//		return REPORT_DBERROR_ROUT(TRIASDB_E_OBJECT_NOT_INITIALIZED, "CTRiASViewItem::get_ObjectTypes");

CTRiASObjectsWrapper Objects (this);

	for (int i = 0; i < _countof(m_ObjsHandles); i++) 
	{
	WTRiASObjects Objs (Objects[i]);

		if (Objs.IsValid()) {
		// Objektmenge fertig instantiiert
		OBJECTTYPE rgType = OBJECTTYPE_Unknown;

			RETURN_FAILED_HRESULT(Objs -> get_Types (&rgType));
			SetType (*pVal, rgType);
		} 
		else if (m_mkName[i].IsValid()) {
		// lediglich Moniker vorhanden, nur diesen Objekttyp annehmen
			SetType (*pVal, g_rgVisTypes[i].rgType);
		}
	}
	return S_OK;
}

// 
STDMETHODIMP CTRiASViewItem::put_ObjectTypes (OBJECTTYPE rgType)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

int iIndex = GetMatchingIndex(rgType);

	if (-1 == iIndex)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::put_ObjectTypes");

CTRiASObjectsWrapper Objects (this);

	if (Objects[iIndex].IsValid())
		return S_FALSE;		// bereits Objektmenge vorhanden, Defaulteintrag nicht notwendig

	SetType (m_rgPreDefinedTypes, g_rgVisTypes[iIndex].rgType);
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::get_Types (OBJECTTYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_Types");

#if defined(_DEBUG)
// Gesetzte VisInfos müssen mit gesetzten Flags übereinstimmen
const VISTYPES *pEntry = g_rgVisTypes;
OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;

	for (int i = 0; OBJECTTYPE_Unknown != pEntry -> rgType; pEntry++, i++) 
	{
		if (m_VisInfo[i].IsValid())
			SetType (rgTypes, pEntry -> rgType);
	}
	_ASSERTE(m_rgTypes == rgTypes);
#endif // _DEBUG

	*pVal = m_rgTypes;	
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::put_Types(OBJECTTYPE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	// abgleichen der geforderten mit den existierenden VisTypen
	const VISTYPES *pEntry = g_rgVisTypes;

		for (int i = 0; OBJECTTYPE_Unknown != pEntry -> rgType; pEntry++, i++)
		{
		bool fHasType = HasType(newVal, pEntry -> rgType);

			if (fHasType && !m_VisInfo[i]) {
			VARIANT_BOOL fModify = VARIANT_FALSE;

				RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), &fModify));
				if (fModify != VARIANT_FALSE)
					return S_FALSE;		// nicht umbenennen
				RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));

				m_VisInfo[i] = WDVisInfo (*pEntry -> pClsId);
				SetType (m_rgTypes, pEntry -> rgType);
				SetType (m_rgDefTypes, pEntry -> rgType);

				RETURN_FAILED_HRESULT(Fire_ViewItemModified(m_bstrDesc));
				m_fIsDirty = true;

			} else if (!fHasType && m_VisInfo[i].IsValid()) {
			VARIANT_BOOL fModify = VARIANT_FALSE;

				RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), &fModify));
				if (fModify != VARIANT_FALSE)
					return S_FALSE;		// nicht umbenennen
				RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));

				m_VisInfo[i].Assign(NULL);
				ClearType (m_rgTypes, pEntry -> rgType);
				ClearType (m_rgDefTypes, pEntry -> rgType);

				RETURN_FAILED_HRESULT(Fire_ViewItemModified(m_bstrDesc));
				m_fIsDirty = true;
			}
		}
		_ASSERTE(m_rgTypes == newVal);
		_ASSERTE(0 == (~m_rgTypes & m_rgDefTypes));	// mehr deftypes als types !

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::get_DefaultTypes (OBJECTTYPE *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_DefaultTypes");

	*pVal = m_rgDefTypes;	
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::put_DefaultTypes(OBJECTTYPE newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	COM_TRY {
	// abgleichen der geforderten mit den existierenden VisTypen
	const VISTYPES *pEntry = g_rgVisTypes;

		for (int i = 0; OBJECTTYPE_Unknown != pEntry -> rgType; pEntry++, i++)
		{
		bool fHasDefType = (newVal & pEntry -> rgType) ? true : false;

			if (fHasDefType && !m_VisInfo[i]) {
			// noch keine VisInfo gegeben, aber soll DefaultVisInfo erhalten
			VARIANT_BOOL fModify = VARIANT_FALSE;

				RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), &fModify));
				if (fModify != VARIANT_FALSE)
					return S_FALSE;		// nicht umbenennen
				RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));

				m_VisInfo[i] = WDVisInfo (*pEntry -> pClsId);
				SetType (m_rgTypes, pEntry -> rgType);
				SetType (m_rgDefTypes, pEntry -> rgType);

				RETURN_FAILED_HRESULT(Fire_ViewItemModified(m_bstrDesc));
				m_fIsDirty = true;
			} else if (fHasDefType && m_VisInfo[i].IsValid() && !HasType(m_rgDefTypes, pEntry -> rgType)) {
			// VisInfo gegeben, aber soll DefaultVisInfo werden
			VARIANT_BOOL fModify = VARIANT_FALSE;

				RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), &fModify));
				if (fModify != VARIANT_FALSE)
					return S_FALSE;		// nicht umbenennen
				RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));

				m_VisInfo[i] = WDVisInfo (*pEntry -> pClsId);
				SetType (m_rgTypes, pEntry -> rgType);
				SetType (m_rgDefTypes, pEntry -> rgType);

				RETURN_FAILED_HRESULT(Fire_ViewItemModified(m_bstrDesc));
				m_fIsDirty = true;
			} else if (!fHasDefType && m_VisInfo[i].IsValid() && HasType (m_rgDefTypes, pEntry -> rgType)) {
			// existierende DefaultVisInfo soll freigegeben werden
			VARIANT_BOOL fModify = VARIANT_FALSE;

				RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), &fModify));
				if (fModify != VARIANT_FALSE)
					return S_FALSE;		// nicht umbenennen
				RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));

				m_VisInfo[i].Assign(NULL);
				ClearType (m_rgTypes, pEntry -> rgType);
				ClearType (m_rgDefTypes, pEntry -> rgType);

				RETURN_FAILED_HRESULT(Fire_ViewItemModified(m_bstrDesc));
				m_fIsDirty = true;
			}
		}
		_ASSERTE(m_rgTypes == newVal);
		_ASSERTE(0 == (~m_rgTypes & m_rgDefTypes));	// mehr deftypes als types !

	} COM_CATCH;

	return S_OK;
}

STDMETHODIMP CTRiASViewItem::get_ItemCount(long * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_ItemCount");

// und jetzt die Collection durchgehen
long lItemCount = 0;

	_ASSERTE(_countof(m_VisInfo) == _countof(m_ObjsHandles));
	for (int i = 0; i < _countof(m_ObjsHandles); i++) {
		if(NULL != m_ObjsHandles[i])
			lItemCount++;
	}

#if defined(_DEBUG)
long lTstCount = 0;

	for (int j = 0; j < _countof(m_VisInfo); j++) {
		if(m_VisInfo[j].IsValid())
			lTstCount++;
	}
	_ASSERTE(lTstCount == lItemCount + BitCount(m_rgPreDefinedTypes));
#endif // _DEBUG

	*pVal = lItemCount + BitCount(m_rgPreDefinedTypes);		// lieber zu viele als zu wenig
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::get_VisInfo(OBJECTTYPE rgType, DVisInfo **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

int iIndex = GetMatchingIndex(rgType);

	if (-1 == iIndex)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_VisInfo");
		
	_ASSERTE(0 <= iIndex && iIndex < _countof(m_VisInfo));

	*pVal = m_VisInfo[iIndex];
	if (NULL != *pVal) {
		LPUNKNOWN(*pVal) -> AddRef();
		return S_OK;
	} 
	return REPORT_DBERROR(TRIASDB_W_NOVISINFO);
}

#if defined(_DEBUG)
static bool MatchingInfos (OBJECTTYPE rgTypeObj, long lTypeVis)
{
	switch (lTypeVis) {
	case RTTI_VisInfo:
		return true;		// allgemeine VisInfo paßt immer

	case RTTI_PointVisInfo:
		if (rgTypeObj & OBJECTTYPE_Point)
			return true;
		break;

	case RTTI_LineVisInfo:
		if (rgTypeObj & OBJECTTYPE_Line)
			return true;
		break;

	case RTTI_AreaVisInfo:
		if (rgTypeObj & OBJECTTYPE_Area)
			return true;
		break;

	case RTTI_TextVisInfo:
		if (rgTypeObj & OBJECTTYPE_Text)
			return true;
		break;

	default:
		break;
	}
	return false;	// types do not match
}
#endif // _DEBUG

STDMETHODIMP CTRiASViewItem::put_VisInfo(OBJECTTYPE rgType, DVisInfo *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

int iIndex = GetMatchingIndex(rgType);

	if (-1 == iIndex)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_VisInfo");

	_ASSERTE(0 <= iIndex && iIndex < _countof(m_VisInfo));

// Rundrufen
VARIANT_BOOL fModify = VARIANT_FALSE;

	RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), &fModify));
	if (fModify != VARIANT_FALSE)
		return S_FALSE;		// nicht umbenennen
	RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));

// wirklich neue Info speichern
	m_VisInfo[iIndex] = newVal;
	if (NULL != newVal) {
		SetType (m_rgTypes, g_rgVisTypes[iIndex].rgType);

	// immer davon ausgehen, daß eine explizit gesetzte VisInfo nicht default ist
		ClearType (m_rgDefTypes, g_rgVisTypes[iIndex].rgType);

	} else {
		ClearType (m_rgTypes, g_rgVisTypes[iIndex].rgType);

	// wenn VisInfo für existierende Objektmenge gelöscht werden soll, dann 
	// DefaulVisInfo generieren
	CTRiASObjectsWrapper Objects (this);

		if (Objects[iIndex].IsValid()) {
			COM_TRY {
				m_VisInfo[iIndex] = WDVisInfo (*g_rgVisTypes[iIndex].pClsId);	// throws hr
				SetType (m_rgTypes, g_rgVisTypes[iIndex].rgType);
				SetType (m_rgDefTypes, g_rgVisTypes[iIndex].rgType);
			} COM_CATCH;
		}
	}

// allen 'Bescheid' sagen
	RETURN_FAILED_HRESULT(Fire_ViewItemModified(m_bstrDesc));
	m_fIsDirty = true;

#if defined(_DEBUG)
// Testen, ob VisInfo mit Objekttypen übereinstimmt
CTRiASObjectsWrapper Objects (this);

// keine Objekte, keine VisInfo
	if (Objects[iIndex].IsValid() && m_VisInfo[iIndex].IsValid()) {
	OBJECTTYPE rgTypeObjs = OBJECTTYPE_Unknown;
	LONG lTypeVis = RTTI_Unknown;
		
		Objects[iIndex] -> get_Types (&rgTypeObjs);

	OBJECTTYPE rgHasVis = (OBJECTTYPE)(rgTypeObjs & g_rgVisTypes[Objects[iIndex].IsValid()].rgType);

		if (m_VisInfo[iIndex] && !(OBJECTTYPE_Unknown == rgHasVis)) {
			m_VisInfo[iIndex] -> get_isA (&lTypeVis);
			_ASSERTE(MatchingInfos (rgTypeObjs, lTypeVis));
		}
	}
#endif // _DEBUG
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::get_Objects(OBJECTTYPE rgType, ITRiASObjects **pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_Objects");
	if (-1 == HasObjectsCollection() && 0 == BitCount(m_rgPreDefinedTypes))
		return REPORT_DBERROR_ROUT(TRIASDB_W_NOOBJECTS, "CTRiASViewItem::get_Objects");

int iIndex = GetMatchingIndex(rgType);

	if (-1 == iIndex)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_Objects");

// versuchen diese nachzuinstantiieren (evtl. ist betreffende connection jetzt verfügbar)
CTRiASObjectsWrapper Objects (this);

	if (HasType (m_rgPreDefinedTypes, g_rgVisTypes[iIndex].rgType) && m_mkName[iIndex].IsValid()) {
	WTRiASObjects Objs;

		_ASSERTE(!Objects[iIndex]);			// darf nicht gesetzt sein
		if (SUCCEEDED(MkBindToObjectLocal (m_mkName[iIndex], Objs.ppi())))
		{
			Objects[iIndex] = Objs;
			_ASSERTE(!HasType(m_rgPreDefinedTypes, g_rgVisTypes[iIndex].rgType));

		// beim ConnPnt anmelden
			if (0 == m_dwObjsCookie && Objects[iIndex].IsValid())
			{
				RETURN_FAILED_HRESULT(AtlAdvise(Objects[iIndex], GetUnknown(), IID_ITRiASObjectsEvents, &m_dwObjsCookie));
			}
		}
	}

// gecachte Objektmenge liefern
	*pVal = Objects[iIndex];
	if (NULL != *pVal) {
		LPUNKNOWN(*pVal) -> AddRef();
		return S_OK;
	}
	return REPORT_DBERROR(TRIASDB_W_NOOBJECTS);
}

STDMETHODIMP CTRiASViewItem::put_Objects(OBJECTTYPE rgType, ITRiASObjects *newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

VARIANT_BOOL fModify = VARIANT_FALSE;

	RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), &fModify));
	if (fModify != VARIANT_FALSE)
		return S_FALSE;		// nicht umbenennen
	RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));

const VISTYPES *pEntry = g_rgVisTypes;
CTRiASObjectsWrapper Objects (this);

	for (int i = 0; OBJECTTYPE_Unknown != pEntry -> rgType; pEntry++, i++)
	{
		if (!HasType (pEntry -> rgType, rgType))
			continue;		// nur gewünschte Typen behandeln

	int iIndex = GetMatchingIndex(pEntry -> rgType);

		_ASSERTE(i == iIndex);
		Objects[iIndex] = newVal;

	// Abgleich mit VisInfo 
		if (NULL != newVal) {
		// beim ConnPnt anmelden
			if (0 == m_dwObjsCookie && Objects[iIndex].IsValid())
			{
				RETURN_FAILED_HRESULT(AtlAdvise(Objects[iIndex], GetUnknown(), IID_ITRiASObjectsEvents, &m_dwObjsCookie));
			}

			if (!m_VisInfo[iIndex])	{	
			// noch keine VisInfo, entweder von Objektklasse geben lassen oder Standard generieren
			WTRiASQueryVisInfo QVI;

				if (SUCCEEDED(newVal -> QueryInterface (QVI.ppi()))) {
				WDVisInfo VI;

					if (SUCCEEDED(QVI -> get_VisInfo (pEntry -> rgType, VI.ppi()))) 
						m_VisInfo[iIndex] = VI;
				}

			// wenn immer noch nichts da ist, dann defazult verwenden
				if (!m_VisInfo[iIndex])	{	
					m_VisInfo[iIndex] = WDVisInfo (*pEntry -> pClsId);
					SetType (m_rgDefTypes, pEntry -> rgType);
				}
			}
			SetType (m_rgTypes, pEntry -> rgType);

		} else {
		// VisInfo wird nicht mehr benötigt
			m_VisInfo[iIndex].Assign(NULL);
			ClearType (m_rgTypes, pEntry -> rgType);
			ClearType (m_rgDefTypes, pEntry -> rgType);
		}
		ClearType (m_rgPreDefinedTypes, pEntry -> rgType);
	}

	RETURN_FAILED_HRESULT(Fire_ViewItemModified(m_bstrDesc));
	m_fIsDirty = true;

#if defined(_DEBUG)
// Testen, ob VisInfo mit Objekttypen übereinstimmt
	if (0 <= HasObjectsCollection()) {
		_ASSERTE(_countof(m_VisInfo) == _countof(m_ObjsHandles));
		for (int i = 0; i < _countof(m_VisInfo); i++) {
			if (!Objects[i].IsValid()) {
			// keine Objekte, keine VisInfo
				_ASSERTE(!m_VisInfo[i] || HasType(m_rgPreDefinedTypes, g_rgVisTypes[i].rgType));
				continue;
			}

		OBJECTTYPE rgTypeObjs = OBJECTTYPE_Unknown;
		LONG lTypeVis = RTTI_Unknown;

			Objects[i] -> get_Types (&rgTypeObjs);

		OBJECTTYPE rgHasVis = (OBJECTTYPE)(rgTypeObjs & g_rgVisTypes[i].rgType);

			_ASSERTE(m_VisInfo[i].IsValid() || OBJECTTYPE_Unknown == rgHasVis);
			if (!m_VisInfo[i] || OBJECTTYPE_Unknown == rgHasVis)
				continue;

			m_VisInfo[i] -> get_isA (&lTypeVis);
			_ASSERTE(MatchingInfos (rgHasVis, lTypeVis));
		}
	}
#endif // _DEBUG
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Objektmenge setzen, wobei lediglich der Moniker übergeben wird, aus dem die 
// gewünschte Objektmenge erzeugt werden kann
STDMETHODIMP CTRiASViewItem::get_ObjectsMoniker(OBJECTTYPE rgType, BSTR *pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (NULL == pVal) 
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_ObjectsMoniker");
	if (-1 == HasObjectsCollection() && 0 == BitCount(m_rgPreDefinedTypes))
		return REPORT_DBERROR_ROUT(TRIASDB_W_NOOBJECTS, "CTRiASViewItem::get_ObjectsMoniker");

int iIndex = GetMatchingIndex(rgType);

	if (-1 == iIndex)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASViewItem::get_ObjectsMoniker");

	if (!HasType (m_rgPreDefinedTypes, g_rgVisTypes[iIndex].rgType) || !m_mkName[iIndex].IsValid()) 
		return REPORT_DBERROR(TRIASDB_W_NOOBJECTS);
		
// gecachten Moniker liefern
	RETURN_FAILED_HRESULT(MkGetDisplayName (m_mkName[iIndex], pVal));
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::put_ObjectsMoniker(OBJECTTYPE rgType, BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

VARIANT_BOOL fModify = VARIANT_FALSE;

	RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), &fModify));
	if (fModify != VARIANT_FALSE)
		return S_FALSE;		// nicht modifizieren
	RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));

const VISTYPES *pEntry = g_rgVisTypes;
WBindCtx ctx;

	RETURN_FAILED_HRESULT(::CreateBindCtx (0, ctx.ppi()));
	for (int i = 0; OBJECTTYPE_Unknown != pEntry -> rgType; pEntry++, i++)
	{
		if (!HasType (pEntry -> rgType, rgType))
			continue;		// nur gewünschte Typen behandeln

	// Objektmenge setzen
	int iIndex = GetMatchingIndex(pEntry -> rgType);
	WMoniker mk;
	ULONG ulEaten = 0L;

		RETURN_FAILED_HRESULT(MkParseDisplayName (ctx, g_cbMkDel[0] == newVal[0] ? &newVal[1] : newVal, &ulEaten, mk.ppi()));

		_ASSERTE(i == iIndex);
		m_mkName[iIndex] = mk;
		m_ObjsHandles[iIndex] = NULL;

	// Abgleich mit VisInfo 
		if (NULL != newVal) {
			if (!m_VisInfo[iIndex])	{	
			// noch keine VisInfo, entweder von Objektklasse geben lassen oder Standard generieren
			CTRiASObjectsWrapper Objects (this);
			WTRiASQueryVisInfo QVI;

				if (SUCCEEDED(Objects[iIndex] -> QueryInterface (QVI.ppi()))) {
				WDVisInfo VI;

					if (SUCCEEDED(QVI -> get_VisInfo (pEntry -> rgType, VI.ppi()))) 
						m_VisInfo[iIndex] = VI;
				}

			// wenn immer noch nichts da ist, dann defazult verwenden
				if (!m_VisInfo[iIndex])	{	
					m_VisInfo[iIndex] = WDVisInfo (*pEntry -> pClsId);
					SetType (m_rgDefTypes, pEntry -> rgType);
				}
			}
			SetType (m_rgTypes, pEntry -> rgType);

		} else {
		// VisInfo wird nicht mehr benötigt
			m_VisInfo[iIndex].Assign(NULL);
			ClearType (m_rgTypes, pEntry -> rgType);
			ClearType (m_rgDefTypes, pEntry -> rgType);
		}
		ClearType (m_rgPreDefinedTypes, pEntry -> rgType);
	}

	RETURN_FAILED_HRESULT(Fire_ViewItemModified(m_bstrDesc));
	m_fIsDirty = true;

#if defined(_DEBUG)
// Testen, ob VisInfo mit Objekttypen übereinstimmt
CTRiASObjectsWrapper Objects (this);

	if (0 <= HasObjectsCollection()) {
		_ASSERTE(_countof(m_VisInfo) == _countof(m_ObjsHandles));
		for (int i = 0; i < _countof(m_VisInfo); i++) {
			if (!Objects[i].IsValid()) {
			// keine Objekte, keine VisInfo
				_ASSERTE(!m_VisInfo[i] || HasType(m_rgPreDefinedTypes, g_rgVisTypes[i].rgType));
				continue;
			}

		OBJECTTYPE rgTypeObjs = OBJECTTYPE_Unknown;
		LONG lTypeVis = RTTI_Unknown;

			Objects[i] -> get_Types (&rgTypeObjs);

		OBJECTTYPE rgHasVis = (OBJECTTYPE)(rgTypeObjs & g_rgVisTypes[i].rgType);

			_ASSERTE(m_VisInfo[i].IsValid() || OBJECTTYPE_Unknown == rgHasVis);
			if (!m_VisInfo[i] || OBJECTTYPE_Unknown == rgHasVis)
				continue;

			m_VisInfo[i] -> get_isA (&lTypeVis);
			_ASSERTE(MatchingInfos (rgHasVis, lTypeVis));
		}
	}
#endif // _DEBUG
	return S_OK;
}

HRESULT CTRiASViewItem::RefreshNameOrOKS (BSTR bstrOldName)
{
	COM_TRY {
	// alle durchgehen
	CTRiASObjectsWrapper Objects (this);
	bool fFirst = true;

		for (int i = 0; i < _countof(m_ObjsHandles); i++) {
		// nur existierende Einträge behandeln
			if (NULL == m_ObjsHandles[i] && !m_mkName[i].IsValid())
				continue;

		// diesen Eintrag behandeln
		WTRiASObjects Objs (Objects[i]);

			if (Objs.IsValid()) {
			WMoniker mk;

				THROW_FAILED_HRESULT(MkGetMoniker (Objs, OLEGETMONIKER_FORCEASSIGN, OLEWHICHMK_OBJFULL, mk.ppi()));
				m_mkName[i] = mk;

				if (fFirst) {
				CComBSTR bstrDesc, bstrMkName;

					THROW_FAILED_HRESULT(Objs -> get_Name (CLEARED(&bstrDesc)));

				// alter Name muß stimmen (wenn er gegeben war)!
					_ASSERTE(0 == SysStringLen(bstrOldName) || !wcscmp (bstrOldName, m_bstrDesc) || !wcscmp (bstrOldName, bstrDesc));
					THROW_FAILED_HRESULT(MkGetDisplayName (mk, CLEARED(&bstrMkName)));

				// neue Werte speichern
					m_bstrDesc = bstrDesc;
					m_bstrMkName = bstrMkName;
					fFirst = false;		// nur beim jeweils ersten gefundenen 
				}
			}
			m_fIsDirty = true;
		}
	} COM_CATCH;
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// PropertySupport
// Callback-interface, welches für die Konkretheit der Properties zuständig ist

STDMETHODIMP CTRiASViewItem::CreateProperty (BSTR Name, ITRiASProperty **Property)
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
STDMETHODIMP CTRiASViewItem::RemoveProperty (BSTR Name)
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

///////////////////////////////////////////////////////////////////////////////
// Events verschicken

HRESULT CTRiASViewItem::Fire_ModifyingViewItem (IDispatch *pIViewItem, VARIANT_BOOL *pVal)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASViewItemEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ModifyingViewItem (pIViewItem, pVal);
	return S_OK;
}

HRESULT CTRiASViewItem::Fire_ViewItemToModify (IDispatch *pIViewItem)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASViewItemEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ViewItemToModify (pIViewItem);
	return S_OK;
}

HRESULT CTRiASViewItem::Fire_ViewItemModified (BSTR Name)
{
	_ASSERTE(m_Parent);
	if (!m_Parent) return E_POINTER;

WTRiASViewItemEvents Events;

	if (SUCCEEDED(m_Parent -> QueryInterface (Events.ppi())))
		return Events -> ViewItemModified (Name);
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASPropertyEvents
STDMETHODIMP CTRiASViewItem::CreatingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), pVal));
	if (*pVal != VARIANT_FALSE) 
		return S_OK;
	return Fire_CreatingProperty (Name, pVal);
}

STDMETHODIMP CTRiASViewItem::PropertyToCreate (BSTR Name)
{
	RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));
	return Fire_PropertyToCreate (Name);
}

STDMETHODIMP CTRiASViewItem::PropertyCreated (IDispatch *pIProp)
{
	m_fIsDirty = true;
	RETURN_FAILED_HRESULT(Fire_ViewItemModified (m_bstrDesc));
	return Fire_PropertyCreated (pIProp);
}

STDMETHODIMP CTRiASViewItem::ModifyingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), pVal));
	if (*pVal != VARIANT_FALSE) 
		return S_OK;
	return Fire_ModifyingProperty (Name, pVal);
}

STDMETHODIMP CTRiASViewItem::PropertyToModify (BSTR Name)
{
	RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));
	return Fire_PropertyToModify (Name);
}

STDMETHODIMP CTRiASViewItem::PropertyModified (BSTR Name)
{
	m_fIsDirty = true;
	RETURN_FAILED_HRESULT(Fire_ViewItemModified (m_bstrDesc));
	return Fire_PropertyModified (Name);
}

STDMETHODIMP CTRiASViewItem::DeletingProperty (BSTR Name, VARIANT_BOOL *pVal)
{
	RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), pVal));
	if (*pVal != VARIANT_FALSE) 
		return S_OK;
	return Fire_DeletingProperty (Name, pVal);
}

STDMETHODIMP CTRiASViewItem::PropertyToDelete (BSTR Name)
{
	RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));
	return Fire_PropertyToDelete (Name);
}

STDMETHODIMP CTRiASViewItem::PropertyDeleted (BSTR Name)
{
	m_fIsDirty = true;
	RETURN_FAILED_HRESULT(Fire_ViewItemModified (m_bstrDesc));
	return Fire_PropertyDeleted (Name);
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASObjectsEvents
STDMETHODIMP CTRiASViewItem::CreatingObjects (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::ObjectsToCreate (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::ObjectsCreated (IDispatch *pIProp)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::ModifyingObjects (CHANGEDOBJECTS rgMode, IDispatch *Objects, VARIANT_BOOL *pVal)
{
	switch (rgMode) {
	case CHANGEDOBJECTS_Name:
	case CHANGEDOBJECTS_OKS:
		RETURN_FAILED_HRESULT(Fire_ModifyingViewItem (GetDispatch(), pVal));
		break;
		
	default:
	// nothing relevant to do
		break; 
	}
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::ObjectsToModify (CHANGEDOBJECTS rgMode, IDispatch *Objects)
{
	switch (rgMode) {
	case CHANGEDOBJECTS_Name:
	case CHANGEDOBJECTS_OKS:
		RETURN_FAILED_HRESULT(Fire_ViewItemToModify (GetDispatch()));
		break;
		
	default:
	// nothing relevant to do
		break; 
	}
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::ObjectsModified (CHANGEDOBJECTS rgMode, BSTR Name)
{
	switch (rgMode) {
	case CHANGEDOBJECTS_Name:
	case CHANGEDOBJECTS_OKS:
		RETURN_FAILED_HRESULT(RefreshNameOrOKS (Name));
		RETURN_FAILED_HRESULT(Fire_ViewItemModified (m_bstrDesc));
		break;
		
	default:
	// nothing relevant to do
		break; 
	}
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::DeletingObjects (IDispatch *Objects, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::ObjectsToDelete (IDispatch *Objects)
{
	return S_OK;
}

STDMETHODIMP CTRiASViewItem::ObjectsDeleted (BSTR Name)
{
	return S_OK;
}


