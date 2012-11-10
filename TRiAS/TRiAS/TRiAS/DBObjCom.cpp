// @doc
// @module DBObjCom.cpp | COM-Spezifika eines <c DatenBasisObjekt> Objektes

#include "TriasPre.hxx"
#include "TRiASRes.h"
#include "Strings.h"

#include <fprotos.h>		// Flex etc.
#include <registry.hxx>
#include <Com/PropertyHelper.h>
#include <Com/ComBool.h>
#include <Atl/Ciid.h>

#define __IStaticCollection_INTERFACE_DEFINED__
#include <idl/Collection.h>

#include "extmain3.hxx"
#include "viewtree.hxx"	// KlassenDeklarationen

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern DWORD g_iHideFlags;
extern DWORD g_dwMenu;					// Menu's selbst behandeln

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASProperty);
DefineSmartInterface(TRiASPropertyBase);
DefineSmartInterface(TRiASProperties);
DefineSmartInterface(TRiASPropertyCallback);
DefineSmartInterface(TRiASPropertySupport);
DefineSmartInterface(TRiASView);
DefineSmartInterface(TRiASConnections);
DefineSmartInterface(TRiASConnection);
DefineSmartInterface(TRiASDatabase);
DefineSmartInterface(TRiASObjectsEx);
DefineSmartInterface(TRiASObjectsCollection);

DefineSmartInterface(ObjectProps);
DefineSmartInterface(EnumObjProps);
DefineSmartInterface(ObjectProperty);

DefineSmartInterface(Storage);
DefineSmartInterface(PersistStorage);
DefineSmartInterface(EnumVARIANT);
DefineSmartInterface(Dispatch);

DefineSmartInterface(TRiASConnectionFilters);
DefineSmartInterface(TRiASConnectionFilter);
DefineSmartInterface(DynamicCollection);

DefineSmartInterface(TRiASCSTransform);
DefineSmartInterface(TRiASCS);
DefineSmartInterface(TRiASTransformGeometry);
DefineSmartInterface(TRiASCloneGeometry);

///////////////////////////////////////////////////////////////////////////////
// OBJECTTYPE zu TRiAS-Objektbits konvertieren
DWORD OBJECTTYPEToBits (OBJECTTYPE rgType);

///////////////////////////////////////////////////////////////////////////////
// ISupportsErrorInfo
STDMETHODIMP DatenBasisObjekt::InterfaceSupportsErrorInfo (REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASConnectionEvents,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
//
HRESULT DatenBasisObjekt::FinalConstruct()
{
	ATLTRY(m_pGeoDBs = new CGeoDBArray);
	if (NULL != m_pGeoDBs) {
		m_pGeoDBs -> FAddItem();				// GeoDB erzeugen
		ATLTRY(_Idents = new CIdTree(*this));
		ATLTRY(_Shapes = new ObjektListe());
	}
	if (!_Idents || !_Shapes || !m_pGeoDBs) 
		return E_OUTOFMEMORY;

	return S_OK;
}

void DatenBasisObjekt::FinalRelease (void)
{
}

///////////////////////////////////////////////////////////////////////////////
// ITRiASConnectionEvents
STDMETHODIMP DatenBasisObjekt::CreatingConnection (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ConnectionToCreate (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ConnectionCreated (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::OpeningConnection (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ConnectionToOpen (BSTR Name)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// eine neue Verbindung zu einer Datenquelle wurde hergestellt
STDMETHODIMP DatenBasisObjekt::ConnectionOpened (IDispatch *pIConn)
{
	try {
		THROW_FAILED_HRESULT(AddConnection (pIConn));

	// neue Connection erˆffnen
	IrisWind *pW = GetViewWindow();

		TX_ASSERT(NULL != pW);
		THROW_FAILED_HRESULT(RePrepareDBO(pW, pW -> GetAspectRatio()));

	// alles neu generieren
		DEXN_ReReadSights(FALSE);
		pW -> doRebuild();

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ClosingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Eine Verbindung soll geschlossen werden
STDMETHODIMP DatenBasisObjekt::ConnectionToClose (IDispatch *pIConn)
{
	USES_CONVERSION;
	try {
	CComBSTR bstrName;
	WTRiASConnection Conn (pIConn);

		THROW_FAILED_HRESULT(Conn -> get_Location (CLEARED(&bstrName)));

	string str (OLE2A(bstrName));
	HPROJECT hPr = m_pGeoDBs -> IsOpened (str.c_str());

		if (HACTCONNECTION != hPr) {
		GeoDB &rDB = m_pGeoDBs -> DB(hPr);
		int iIndex = m_pGeoDBs -> FFindItem (hPr);

			TX_ASSERT(-1 != iIndex);

		// neue Connection erˆffnen
		IrisWind *pW = GetViewWindow();

			if (NULL != pW)	{
			// alles neu generieren
				THROW_FAILED_HRESULT(RePrepareDBO(pW, pW -> GetAspectRatio(), hPr));
				pW -> doRebuild(hPr);
			}

			rDB.DetachConnection();			// sollte bereits gespeichert sein
			m_pGeoDBs -> FDelItem (iIndex);	// jetzt aus Liste herausnehmen

		// die Welt informieren
//			DEXN_isClosedProject(str.c_str());
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ConnectionClosed (BSTR Name)
{
	DEXN_ReReadSights(FALSE);
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::DeletingConnection (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ConnectionToDelete (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ConnectionDeleted (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::RenamingConnection (BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ConnectionToRename (BSTR OldName, BSTR NewName)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ConnectionRenamed (IDispatch *pIConn)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ChangingConnectedDatasource (IDispatch *pIConn, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ConnectedDatasourceToChange (IDispatch *pIConn)
{
// alles neu einlesen
//	COM_TRY {
//	WTRiASConnection Conn (pIConn);
//	WTRiASDatabase DBase;
//	HPROJECT hPr = NULL;
//
//		THROW_FAILED_HRESULT(Conn -> get_Database(DBase.ppi()));
//		THROW_FAILED_HRESULT(DBase -> get_Handle((INT_PTR *)&hPr));
//
//	IrisWind *pW = GetViewWindow();
//
//		if (NULL != pW)	{
//		// alles neu generieren
//			THROW_FAILED_HRESULT(RePrepareDBO(pW, pW -> GetAspectRatio(), hPr));
//			pW -> doRebuild(hPr);
//		}
//	} COM_CATCH;
	return ConnectionToClose(pIConn);
}

STDMETHODIMP DatenBasisObjekt::ConnectedDatasourceChanged (IDispatch *pIConn)
{
	return ConnectionOpened(pIConn);
}


///////////////////////////////////////////////////////////////////////////////
// ITRiASViewEvents
STDMETHODIMP DatenBasisObjekt::CreatingView (BSTR Name, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ViewToCreate (BSTR Name)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ViewCreated (IDispatch *pIView)
{
	USES_CONVERSION;
	try {
	ExtDirisWindow *pFrame = GetViewWindow() -> GetFrame();
	WTRiASView View (pIView);	// throws hr
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(View -> get_Name (CLEARED(&bstrName)));

	LPCSTR pcName = OLE2A(bstrName);

	// Die Welt von diesem Ereignis in Kenntnis setzen
		if (m_pViews -> ShouldAddView (pcName)) {
		// nicht StartAnsicht und keine SystemAnsicht (__[Name])
		VIEWCREATED VC;

			INITSTRUCT (VC, VIEWCREATED);
			VC.m_pTarget = g_cbNil;
			VC.m_pNewName = (char *)pcName;
			DEXN_SightCreated(VC);
		}

	// jetzt Menupunkt etc. erzeugen
		if (pFrame && AddItemToSightMenu (pFrame, pFrame -> MainMenu(), pcName) &&
			!(g_dwMenu & HANDLEMENU_MainMenu))
		{
			::DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);		// snh
	}
	return S_OK;
}

// Ansicht umbenennen
STDMETHODIMP DatenBasisObjekt::ChangingView (BSTR OldName, BSTR NewName, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ViewToChange (BSTR Name, BSTR NewName)
{
	USES_CONVERSION;

ExtDirisWindow *pFrame = GetViewWindow() -> GetFrame();

	if (NULL == pFrame) return E_UNEXPECTED;

// alte Ansicht aus Menu etc. herausnehmen und neu einf¸gen
bool fDelete = DeleteSightMenuItem (pFrame, pFrame -> MainMenu(), OLE2A(Name));
bool fAdd = AddItemToSightMenu (pFrame, pFrame -> MainMenu(), OLE2A(NewName));

	if ((fDelete || fAdd) && !(g_dwMenu & HANDLEMENU_MainMenu))
		::DrawMenuBar (pFrame -> Handle (API_WINDOW_HWND));

	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ViewChanged (IDispatch *pIView)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::DeletingView (IDispatch *pIView, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ViewToDelete (IDispatch *pIView)
{
	USES_CONVERSION;
	try {
	ExtDirisWindow *pFrame = GetViewWindow() -> GetFrame();
	WTRiASView View (pIView);	// throws hr
	CComBSTR bstrName;

		THROW_FAILED_HRESULT(View -> get_Name (CLEARED(&bstrName)));
		DeleteView (pFrame -> MainMenu(), OLE2A(bstrName));
		
	} catch (_com_error &e) {
		return _COM_ERROR(e);		// snh
	}
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ViewDeleted (BSTR Name)
{
	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////
// ICoordTransformEvents
STDMETHODIMP DatenBasisObjekt::CoordParamsToChange (IDispatch *pICoordSys, VARIANT_BOOL *pVal)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ChangingCoordParams (IDispatch *pICoordSys)
{
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ChangedCoordParams (IDispatch *pICoordSys)
{
	DEXN_CoordFormatChanged();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Zugehˆriges TRiASProject behandeln
HRESULT DatenBasisObjekt::AttachTRiASProject (ITRiASProject *pIPrj, ITRiASProject **ppIPrj)
{
	try {
	// Projekt speichern
	WTRiASProject Prj (m_Prj);

		m_Prj = pIPrj;			// throws hr
		if (NULL != ppIPrj) 
			*ppIPrj = Prj.detach();

		if (m_Prj.IsValid()) {
			m_ObjMap = WTRiASObjectHandleMap (CLSID_TRiASObjectHandleMap);
			m_ObjsMap = WTRiASObjectHandleMap (CLSID_TRiASObjectsHandleMap);
			m_FeatMap = WTRiASObjectHandleMap (CLSID_TRiASFeatureHandleMap);
			m_Service = WTRiASCSStorageService (CLSID_TRiASCSStorageService);
		} else {
			m_ObjMap.Assign(NULL);
			m_ObjsMap.Assign(NULL);
			m_FeatMap.Assign(NULL);
			m_Service.Assign (NULL);
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::ReReadHeader (void)
{
	TX_ASSERT(IsTRiASDBBased());
	try {
	// alle notwendigen Properties des Projektes abfragen
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(WTRiASPropertyBase(m_Prj) -> get_Properties (Props.ppi()));
		THROW_FAILED_HRESULT(Props -> Refresh());
		THROW_FAILED_HRESULT(WTRiASPropertyCallback(m_Prj) -> Refresh(CComBSTR(g_cbNil)));

	// allen mitteilen, ob SysAdmin aktiv ist
		if (DEX_QueryMode() & QMSysAdmin)
			SetProperty (Props, g_cbSysAdmin,  VARIANT_TRUE, true);		// notfalls erzeugen

	// alle Datenquellen auch neu einlesen lassen
	CRing r (*m_pGeoDBs);

		for (r.First(); r.Valid(); r.Next()) {
		GeoDBLock l(r);

			TX_ASSERT(NULL != (GeoDB *)l);
			if (l -> isOpened())
				l -> ReReadHeader();
		}

#if defined(_USE_LEGACY_CODE)
	// die folgenden Properties m¸ssen vollst‰ndig von der GeoDB abgebildet werden
	int iIdentBase = GetProperty (Props, ResString(IDS_IDENTBASE, _MAX_PATH).Addr(), 16, LOCALE_ENGLISH);

		if (10 != iIdentBase && 16 != iIdentBase)
			iIdentBase = 16;
		SetIdBase (iIdentBase);

	int iMkBase = GetProperty (Props, ResString(IDS_MCODEBASE, _MAX_PATH).Addr(), 10, LOCALE_ENGLISH);

		if (10 != iMkBase && 16 != iMkBase)
			iMkBase = 10;
		SetMkBase(iMkBase);
#endif // _USE_LEGACY_CODE

	VARIANT_BOOL fPos = GetProperty (Props, g_cbPosTxtAtBaseLine, VARIANT_FALSE);

		PosTextAtBaseLine (fPos ? true : false);

	VARIANT_BOOL fComp = GetProperty (Props, g_cbCompatibility16, VARIANT_FALSE);

		Compatibility (fComp ? true : false);

	// FullRedrawOnScroll
	VARIANT_BOOL fFlag = GetProperty (Props, g_cbScrollMode, VARIANT_FALSE);

		m_pViewWnd -> SetFullRedrawOnScroll (fFlag ? true : false);

	// HintergrundFarbe einlesen und setzen
		{
		DWORD dwColor = 0x00C0C0C0L;

#if defined(ENABLE_WIN32S_CODE)
			if (!IsWin32s()) 
#endif // ENABLE_WIN32S_CODE
			{
			CCurrentUser resBkColor (g_cbRegConfig);

				resBkColor.GetDWORD (g_cbBackGroundColor, dwColor);
			} 

			dwColor = GetProperty (Props, g_cbBackGroundColor, (LONG)dwColor);
			SetBkColor ((Color &)dwColor);

		Brush *pB = NULL;
		
			TX_TRY(pB = new Brush((Color &)dwColor));
			if (NULL != pB) m_pViewWnd -> SetBackground (pB);
		}

	// HideFlags einlesen
	CCurrentUser regCfg (g_cbRegConfig);

		{
		DWORD dwData = DWORD(RODefaultFlags);

			regCfg.GetDWORD (g_cbHideFlags, dwData);
			g_iHideFlags = GetProperty (Props, g_cbHideFlags, (LONG)dwData);
		}

	// ShowObjProp 
		{
		char cbBuffer[64] = { '\0' };
		DWORD dwLen = sizeof(cbBuffer);

			regCfg.GetSubSZ (g_cbShowObjProp, cbBuffer, dwLen);

		CComBSTR bstr (cbBuffer);

			USES_CONVERSION;
			strcpy (cbBuffer, OLE2A(GetProperty (Props, g_cbShowObjProp, bstr)));
			DEX_SetActObjPropName (cbBuffer);
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::GetTRiASProject (ITRiASProject **ppIPrj)
{
	if (NULL == ppIPrj) 
		return E_POINTER;
	
WTRiASProject Prj (m_Prj);

	*ppIPrj = Prj.detach();
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Storage des Projektes besorgen
HRESULT DatenBasisObjekt::GetProjectStorage (IStorage **ppIStg)
{
	if (NULL == ppIStg) return E_POINTER;

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) {
		if (!DB().isOpened())			// evtl. w‰hrend der SchlieﬂPhase
			return E_FAIL;
		
		return DB().GetProjectStorage(ppIStg);
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

	// alle notwendigen Properties des Projektes abfragen
	WTRiASProperties Props;

		RETURN_FAILED_HRESULT(WTRiASPropertyBase(m_Prj) -> get_Properties (Props.ppi()));

	// GetProperty liefert mit AddRef ab!
		*ppIStg = (IStorage *)GetProperty (Props, g_cbStgService, (IUnknown *)NULL);
		if (NULL == *ppIStg)
			return E_FAIL;				
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Storage einer Datenquelle besorgen
HRESULT DatenBasisObjekt::GetDataSourceStorage (HPROJECT hPr, IStorage **ppIStg)
{
	if (NULL == ppIStg) return E_POINTER;

#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) 
	{
		return E_FAIL;
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());
		if (HACTPROJECT == hPr)
			return E_UNEXPECTED;
	
	int iItem = m_pGeoDBs -> FFindItem (hPr);

		if (-1 == iItem || !DB(hPr).isOpened())			// evtl. w‰hrend der SchlieﬂPhase
			return E_FAIL;
		return DB(hPr).GetProjectStorage(ppIStg);
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::GetDataSourceDescription (HPROJECT hPr, char *pDesc)
{
	TX_ASSERT(IsTRiASDBBased());
	if (HACTPROJECT == hPr) 
		return E_UNEXPECTED;

int iItem = m_pGeoDBs -> FFindItem (hPr);

	if (-1 == iItem || !DB(hPr).isOpened())			// evtl. w‰hrend der SchlieﬂPhase
		return E_FAIL;
	return DB(hPr).GetDataSourceDescription (pDesc);
}

HRESULT DatenBasisObjekt::GetDataSourceShortName (HPROJECT hPr, char *pDesc)
{
	TX_ASSERT(IsTRiASDBBased());
	if (HACTPROJECT == hPr) {
	// Projekt f¸r Zuordnungsobjektklasse 
	ResString resZOK (IDS_QUERYDEF_OBJECTS, 32);

		strcpy (pDesc, resZOK);
		return S_OK;
	}

int iItem = m_pGeoDBs -> FFindItem (hPr);

	if (-1 == iItem || !DB(hPr).isOpened())			// evtl. w‰hrend der SchlieﬂPhase
		return E_FAIL;
	return DB(hPr).GetDataSourceName (pDesc);
}


HRESULT DatenBasisObjekt::GetDataSourceName (HPROJECT hPr, char *pName)
{
	TX_ASSERT(IsTRiASDBBased());
	if (HACTPROJECT == hPr)
		return E_UNEXPECTED;

int iItem = m_pGeoDBs -> FFindItem (hPr);

	if (-1 == iItem || !DB(hPr).isOpened())			// evtl. w‰hrend der SchlieﬂPhase
		return E_FAIL;
	
	strcpy (pName, DB(hPr).GetDBName());
	return S_OK;
}

HRESULT DatenBasisObjekt::GetTRiASConnection (HPROJECT hPr, ITRiASConnection **ppIConn)
{
	TX_ASSERT(IsTRiASDBBased());

int iItem = m_pGeoDBs -> FFindItem (hPr);

	if (-1 == iItem || !DB(hPr).isOpened())			// evtl. w‰hrend der SchlieﬂPhase
		return E_FAIL;

	return DB(hPr).GetConnection (ppIConn);	
}

HRESULT DatenBasisObjekt::RetrieveActiveProject (char *pBuffer, int iLen)
{
#if defined(_FORCE_LEGACY_CODE)
	if (!IsTRiASDBBased()) 
	{
	int iNameLen = strlen(DB().GetDBName());
	int iToCopy = min(iLen-1, iNameLen);

		strncpy (pBuffer, DB().GetDBName(), iToCopy);	// DBNamen kopieren
		pBuffer[iToCopy] = '\0';
		return S_OK;
	} else
#endif // _FORCE_LEGACY_CODE
	{
		TX_ASSERT(IsTRiASDBBased());

		USES_CONVERSION;
		try {
		CComBSTR bstrName;

			THROW_FAILED_HRESULT(m_Prj -> get_Name (CLEARED(&bstrName)));

		char *pStr = OLE2A(bstrName);
		int iNameLen = strlen(pStr);
		int iToCopy = min(iLen-1, iNameLen);

			strncpy (pBuffer, pStr, iToCopy);	// DBNamen kopieren
			pBuffer[iToCopy] = '\0';

		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	}
	return S_OK;
}

ULONG DatenBasisObjekt::GetDataSourceCount (LONG rgWhat)
{
ULONG ulCnt = 0;

	TX_ASSERT(IsTRiASDBBased());
	COM_TRY {
	WTRiASConnections Conns;
	LONG lCnt = 0;

		THROW_FAILED_HRESULT(m_Prj -> get_Connections (Conns.ppi()));
		THROW_FAILED_HRESULT(Conns -> get_Count(&lCnt));

		for (long i = 1; i <= lCnt; i++) {
		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (CComVariant(i), Conn.ppi()));

		CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

			THROW_FAILED_HRESULT(Conn -> get_Status (&rgStatus));
			if (CONNECTSTATUS_Opened == rgStatus) {
			VARIANT_BOOL fUpdatable = VARIANT_FALSE;

				THROW_FAILED_HRESULT(Conn -> get_Updatable (&fUpdatable));
				if (QDCReadOnly & rgWhat) {
					if (!fUpdatable) 
						ulCnt++;		// nur RO-Connections z‰hlen
				} else if (QDCWriteAble & rgWhat) {
					if (fUpdatable) 
						ulCnt++;		// nur beschreibbare Connections z‰hlen
				} else {
					TX_ASSERT(QDCAllOpen == (rgWhat & ~QDCCountQueryDefs));
					ulCnt++;			// alle z‰hlen
				}
			}
		}

	// evtl. Zuordnungsobjektklassen mitz‰hlen
		if (QDCCountQueryDefs & rgWhat) {
		WTRiASObjectsCollection QueryDefs;

			THROW_FAILED_HRESULT(m_Prj -> get_ObjectsDefs (QueryDefs.ppi()));
			THROW_FAILED_HRESULT(QueryDefs -> get_Count (&lCnt));
			if (lCnt > 0)
				ulCnt++;
		}

	} COM_CATCH;
	return ulCnt;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob die Objekteigenschaft beschreibbar (schreibgesch¸tt) ist
bool DatenBasisObjekt::GetROModeIdent (INT_PTR lIdent)
{
VARIANT_BOOL fCanUpdate = VARIANT_FALSE;

	COM_TRY {
	// Feature von zugehˆriger Objektklasse geben lassen
	WTRiASObjects Objs;

		if (SUCCEEDED(GetObjectsFromMap (lIdent, Objs))) 
		{
			THROW_FAILED_HRESULT(Objs -> get_Updatable (&fCanUpdate));
		}

	} COM_CATCH_RETURN(true);	// bei Fehler so gut wie schreibgesch¸tzt
	return fCanUpdate ? false : true;
}

HRESULT DatenBasisObjekt::SetROModeIdent (INT_PTR lIdent, bool fROMode)
{
	COM_TRY {
	// Feature von zugehˆriger Objektklasse geben lassen
	WTRiASObjects Objs;

		if (SUCCEEDED(GetObjectsFromMap (lIdent, Objs))) 
		{
			THROW_FAILED_HRESULT(Objs -> put_Updatable (CComBool(!fROMode)));
		}

	} COM_CATCH;	// bei Fehler so gut wie schreibgesch¸tzt
	return S_OK;
}

bool DatenBasisObjekt::GetSchemaUpdatable (HPROJECT hPr)
{
	TX_ASSERT(IsTRiASDBBased());

int iItem = m_pGeoDBs -> FFindItem (hPr);

	if (-1 == iItem || !DB(hPr).isOpened())			// evtl. w‰hrend der SchlieﬂPhase
		return false;

	return DB(hPr).GetSchemaUpdatable() ? true : false;
}

///////////////////////////////////////////////////////////////////////////////
// Implementation of IPersistStorage-related functionality
HRESULT DatenBasisObjekt::Save (IStorage *pIStg, BOOL fSameAsLoad)
{
	COM_TRY {
		_ASSERTE(m_Prj.IsValid());
		THROW_FAILED_HRESULT(WPersistStorage(m_Prj) -> Save (pIStg, fSameAsLoad));
	} COM_CATCH;
	return S_OK;
}

HRESULT DatenBasisObjekt::SaveCompleted (IStorage *pIStg)
{
	COM_TRY {
		_ASSERTE(m_Prj.IsValid());
		THROW_FAILED_HRESULT(WPersistStorage(m_Prj) -> SaveCompleted (pIStg));
	} COM_CATCH;
	return S_OK;
}

HRESULT DatenBasisObjekt::HandsOffStorage ()
{
	COM_TRY {
		_ASSERTE(m_Prj.IsValid());
		THROW_FAILED_HRESULT(WPersistStorage(m_Prj) -> HandsOffStorage());
	} COM_CATCH;
	return S_OK;
}

ErrCode DatenBasisObjekt::FindId (long lIdent, long *plFlexNum, short *pOTyp, long *plObjCnts) 
{
ErrCode RC;

// dynamisches Feld anfordern
	if (NULL != plFlexNum && 0 == *plFlexNum) 
		DBASSERT (feini_ (plFlexNum));

	TX_ASSERT(IsTRiASDBBased());
	try {
	// Heraussuchen der Objektmenge ¸ber ihr Handle
	WTRiASObjects Objs;

		THROW_FAILED_HRESULT(GetObjectsFromMap (lIdent, Objs));

	// alle Objekte liefern
		if (NULL != plFlexNum || (NULL != plObjCnts && NULL != pOTyp)) {
		long lObjs = 0;

		// auf TRiAS-Datenbanken optimiert zugreifen
		WTRiASObjectsEx SimpleObjs;

			if (SUCCEEDED(Objs -> QueryInterface (SimpleObjs.ppi()))) {
			// ObjektHandles liefern
				THROW_FAILED_HRESULT(SimpleObjs -> get_Count (OBJECTTYPE_All, &lObjs));
				if (0 == lObjs) return WC_NOTFOUND;

				if (NULL != plFlexNum) {
					if (lObjs != FlexReserve (*plFlexNum, lObjs))
						return EC_NOMEMORY;

				long *pAdr = NULL;
				unsigned long *puLen = NULL;

					FlexAccessAdr (*plFlexNum, &pAdr, &puLen);
					THROW_FAILED_HRESULT(SimpleObjs -> get_Handles (lObjs, (INT_PTR *)pAdr));
					*puLen = lObjs;
				}

				if (NULL != pOTyp) {
				OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;

					THROW_FAILED_HRESULT(Objs -> get_Types (&rgTypes)); 	// _nach_ get_Count rufen, da dort Typen nochmal abgeglichen werden
					*pOTyp = OBJECTTYPEToBits(rgTypes);

				// Anzahl der Objekte der einzelnen Objekttypen abfragen
					if (NULL != plObjCnts) {
						if (*pOTyp & TPPunkt) { THROW_FAILED_HRESULT(SimpleObjs -> get_Count (OBJECTTYPE_Point, &plObjCnts[0])); }
						if (*pOTyp & TPLinie) { THROW_FAILED_HRESULT(SimpleObjs -> get_Count (OBJECTTYPE_Line, &plObjCnts[1])); }
						if (*pOTyp & TPFlaeche) { THROW_FAILED_HRESULT(SimpleObjs -> get_Count (OBJECTTYPE_Area, &plObjCnts[2])); }
						if (*pOTyp & TPText) { THROW_FAILED_HRESULT(SimpleObjs -> get_Count (OBJECTTYPE_Text, &plObjCnts[3])); }
					}
				}
			} else {
			// ansonsten einfach alles der Reihe nach durchgehen
				THROW_FAILED_HRESULT(Objs -> get_Count (&lObjs));
				if (0 == lObjs) return WC_NOTFOUND;

				if (NULL != pOTyp) {
				OBJECTTYPE rgTypes = OBJECTTYPE_Unknown;

					THROW_FAILED_HRESULT(Objs -> get_Types (&rgTypes)); 	// _nach_ get_Count rufen, da dort Typen nochmal abgeglichen werden
					*pOTyp = OBJECTTYPEToBits(rgTypes);
				}

			// bei Bedarf Objekte laden
				if (NULL != plFlexNum) {
					if (NULL != plFlexNum && lObjs != FlexReserve (*plFlexNum, lObjs))
						return EC_NOMEMORY;

				WEnumVARIANT Enum;
				CComVariant v;

					THROW_FAILED_HRESULT(Objs -> _NewEnum (Enum.ppu()));
					for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) 
					{
						if (FAILED(v.ChangeType (VT_DISPATCH)))
							continue;

					// ObjektHandles liefern
					WTRiASObject Item (V_DISPATCH(&v));
					HOBJECT lHandle = NULL;

						THROW_FAILED_HRESULT(Item -> get_Handle ((INT_PTR *)&lHandle));
						DBASSERTM(feput_ (plFlexNum, (long *)&lHandle));

					// Objekttypenweise z‰hlen
						if (NULL != plObjCnts) {
						OBJECTTYPE rgType = OBJECTTYPE_Unknown;

							THROW_FAILED_HRESULT(Item -> get_Type (&rgType))
							if (rgType & OBJECTTYPE_Point) 
								plObjCnts[0]++; 
							if (rgType & OBJECTTYPE_Line) 
								plObjCnts[1]++; 
							if (rgType & OBJECTTYPE_Area) 
								plObjCnts[2]++; 
							if (rgType & OBJECTTYPE_Text) 
								plObjCnts[3]++; 
						}
					}
#if defined(_DEBUG)
					if (NULL != plObjCnts && NULL != pOTyp) {
					// wenn der Objekttyp vertreten ist, dann muﬂ der Z‰hler positiv sein
						TX_ASSERT(!(*pOTyp & TPPunkt) || 0 < plObjCnts[0]);
						TX_ASSERT(!(*pOTyp & TPLinie) || 0 < plObjCnts[1]);
						TX_ASSERT(!(*pOTyp & TPFlaeche) || 0 < plObjCnts[2]);
						TX_ASSERT(!(*pOTyp & TPText) || 0 < plObjCnts[3]);
					}
#endif // _DEBUG
				}
			}
		}
	} catch (_com_error &) {
		return EC_FAIL;
	}

	if (NULL != plFlexNum) {
	long iLen = 0;

		DBASSERT (felen_ (plFlexNum, &iLen));
		if (iLen == 0) 
			return WC_NOTFOUND;
	}
	return EC_OKAY;
}

///////////////////////////////////////////////////////////////////////////////
// Connectionfilter
HRESULT DatenBasisObjekt::CreateConnectionFilter (CONNECTIONFILTER *pCF)
{
HRESULT hr = E_FAIL;

	COM_TRY {
	// Filtergeometrie ins Projektkoordinatensystem umsetzen
	WDispatch Geom (pCF -> pIGeometry);

		if (NULL != pCF -> pICS) {
		WDispatch dispPipe;
		WTRiASCSTransform Pipe;

			THROW_FAILED_HRESULT(pCT() -> GetCoordTransformPipe(dispPipe.ppi()));
			THROW_FAILED_HRESULT(dispPipe -> QueryInterface(Pipe.ppi()));

		WTRiASCS CS (pCF -> pICS);
		CComBSTR bstrGuid;

			THROW_FAILED_HRESULT(CS -> get_GUID(&bstrGuid));

		// neues CS ggf. zur Pipe hinzuf¸gen
		CComVariant vCSDummy;

			if (FAILED(Pipe -> get_Item(CComVariant(bstrGuid), &vCSDummy))) {
				THROW_FAILED_HRESULT(Pipe -> AddInputCS (CS));
			}

		// Koordinaten konvertieren
		CIID Guid (bstrGuid, CIID::INITCIID_InitFromGuid);
		WDispatch disp;

			THROW_FAILED_HRESULT(WTRiASCloneGeometry(Geom) -> Clone (disp.ppi()));
			THROW_FAILED_HRESULT(WTRiASTransformGeometry(disp) -> Transform(*(CSID *)&Guid, Pipe));
			Geom = disp;
		}

	// Filter erzeugen
	CComVariant vItem(pCF -> pcName);
	WTRiASConnectionFilter Filter;

		THROW_FAILED_HRESULT(hr = m_Prj -> get_ConnectionFilter(vItem, VARIANT_TRUE, Filter.ppi()));
		THROW_FAILED_HRESULT(Filter -> put_Geometry(Geom));
		THROW_FAILED_HRESULT(Filter -> put_Type(CONNECTIONFILTERTYPE(pCF->iMode)));
		
	} COM_CATCH;
	return hr;
}

HRESULT DatenBasisObjekt::GetConnectionFilter (CONNECTIONFILTER *pCF)
{
	COM_TRY {
	// Filter geben lassen
	CComVariant vItem(pCF -> pcName);
	WTRiASConnectionFilter Filter;
	CONNECTIONFILTERTYPE rgType = CONNECTIONFILTERTYPE_Rectangle_OverlappedContainers;
	WDispatch Geom;

		THROW_FAILED_HRESULT(m_Prj -> get_ConnectionFilter(vItem, VARIANT_FALSE, Filter.ppi()));
		THROW_FAILED_HRESULT(Filter -> get_Geometry(Geom.ppi()));
		THROW_FAILED_HRESULT(Filter -> get_Type(&rgType));

	// ggf. Koordinaten konvertieren
		if (NULL != pCF -> pICS) {
		WDispatch dispPipe;
		WTRiASCSTransform Pipe;

			THROW_FAILED_HRESULT(pCT() -> GetCoordTransformPipe(dispPipe.ppi()));
			THROW_FAILED_HRESULT(dispPipe -> QueryInterface(Pipe.ppi()));

		WTRiASCS CS (pCF -> pICS);
		CComBSTR bstrGuid;

			THROW_FAILED_HRESULT(CS -> get_GUID(&bstrGuid));

		// neues CS ggf. zur Pipe hinzuf¸gen
		CComVariant vCSDummy;

			if (FAILED(Pipe -> get_Item(CComVariant(bstrGuid), &vCSDummy))) {
				THROW_FAILED_HRESULT(Pipe -> AddInputCS (CS));
			}

		CIID Guid (bstrGuid, CIID::INITCIID_InitFromGuid);
		WDispatch disp;

			THROW_FAILED_HRESULT(WTRiASCloneGeometry(Geom) -> Clone (disp.ppi()));
			THROW_FAILED_HRESULT(WTRiASTransformGeometry(disp) -> TransformInverse(*(CSID *)&Guid, Pipe));
			Geom = disp;
		}

	// Werte in STruktur ablegen und zur¸ckliefern
		pCF -> pIGeometry = Geom.detach();
		pCF -> iMode = rgType;

	} COM_CATCH;
	return S_OK;
}

HRESULT DatenBasisObjekt::DeleteConnectionFilter (CONNECTIONFILTER *pCF)
{
HRESULT hr = E_UNEXPECTED;

	COM_TRY {
	// sicherstellen, daﬂ der Verbindungsfilter in keiner Connection selektiert
	// ist
	CComVariant vItem(pCF -> pcName);
	WTRiASConnections Conns;
	LONG lCnt = 0;

		THROW_FAILED_HRESULT(m_Prj -> get_Connections (Conns.ppi()));
		THROW_FAILED_HRESULT(Conns -> get_Count(&lCnt));

		for (long i = 1; i <= lCnt; i++) {
		WTRiASConnection Conn;

			THROW_FAILED_HRESULT(Conns -> Item (CComVariant(i), Conn.ppi()));

		WTRiASConnectionFilter Filter (GetPropertyFrom(WTRiASPropertyBase(Conn), 
			L"TRiASConnectFilter", (IDispatch *)NULL), false);
		CComBSTR bstrName;

			if (Filter.IsValid()) {
			// nicht alle Connections haben ein Verbindungsfilter gesetzt
				THROW_FAILED_HRESULT(Filter -> get_Name(&bstrName));
				if (bstrName == V_BSTR(&vItem))
					return E_INVALIDARG;		// Verbindungsfilter ist noch selektiert
			}
		}

	// Verbindungsfilter lˆschen
	WTRiASConnectionFilters Filters;

		THROW_FAILED_HRESULT(m_Prj -> get_ConnectionFilters(Filters.ppi()));
		THROW_FAILED_HRESULT(hr = WDynamicCollection(Filters) -> DeleteByIndex(vItem));

	} COM_CATCH;
	return hr;
}

namespace {
	inline BOOL 
	EnumConnectionFilterCallback (
		BOOL (*pFcn)(char *, BOOL, void *), char *pName, BOOL fNotLast, void *pData) 
	{
		return ((ENUMNOKEYCALLBACK)pFcn)(pName, fNotLast, pData);
	}
}

BOOL DatenBasisObjekt::EnumConnectionFilters (ENUMNOKEY *pENK)
{
	COM_TRY {
	WTRiASConnectionFilters Filters;
	WEnumVARIANT Enum;

		THROW_FAILED_HRESULT(m_Prj -> get_ConnectionFilters(Filters.ppi()));
		THROW_FAILED_HRESULT(WDynamicCollection(Filters) -> _NewEnum(Enum.ppu()));

	CComVariant v;

		USES_CONVERSION;
		for (Enum -> Reset(); S_OK == Enum -> Next (1, CLEARED(&v), NULL); /**/) 
		{
			if (FAILED(v.ChangeType (VT_DISPATCH)))
				continue;

		WTRiASConnectionFilter Filter (V_DISPATCH(&v));
		CComBSTR bstrName;

			THROW_FAILED_HRESULT(Filter -> get_Name(&bstrName));
			if (!EnumConnectionFilterCallback(pENK -> eFcn, OLE2A(bstrName), FALSE, pENK -> ePtr))
				return FALSE;
		}

	} COM_CATCH_RETURN(FALSE);
	return TRUE;
}

HRESULT DatenBasisObjekt::AttachConnectionFilter (ATTACHCONNECTIONFILTER *pACF)
{
HRESULT hr = S_OK;

	COM_TRY {
	// Verbindungsfilter wiederfinden (muﬂ bereits definiert sein)
	CComVariant vItem(pACF -> pcName);
	WTRiASConnectionFilter Filter;

		if (FAILED(m_Prj -> get_ConnectionFilter(vItem, VARIANT_FALSE, Filter.ppi())))
			return E_INVALIDARG;

	// passende Connection finden
	CComVariant vConnection(pACF -> pcConnName);
	WTRiASConnection Connection;

		if (FAILED(m_Prj -> get_Connection(vConnection, Connection.ppi())))
			return E_INVALIDARG;

	CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

		THROW_FAILED_HRESULT(Connection -> get_Status (&rgStatus));
		if (CONNECTSTATUS_Opened != rgStatus) 
			return E_INVALIDARG;		// DB nicht geˆffnet

	// Verbindungsfilter setzen
		THROW_FAILED_HRESULT(SetPropertyBy(WTRiASPropertyBase(Connection), 
			L"TRiASConnectFilter", WDispatch(Filter), true));

	// Datenquelle auffordern, den Verbindungsfilter einzubauen
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(Connection -> get_Database(DBase.ppi()));

	// may return E_NOTIMPL
		hr = WTRiASPropertyCallback(DBase) -> Refresh(CComBSTR(L"TRiASConnectFilter"));

	} COM_CATCH;
	return hr;
}

HRESULT DatenBasisObjekt::DetachConnectionFilter (ATTACHCONNECTIONFILTER *pACF)
{
HRESULT hr = S_OK;

	COM_TRY {
	// passende Connection finden
	CComVariant vConnection(pACF -> pcConnName);
	WTRiASConnection Connection;

		if (FAILED(m_Prj -> get_Connection(vConnection, Connection.ppi())))
			return E_INVALIDARG;

	CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

		THROW_FAILED_HRESULT(Connection -> get_Status (&rgStatus));
		if (CONNECTSTATUS_Opened != rgStatus) 
			return E_INVALIDARG;				// DB nicht geˆffnet

	// ggf. Verbindungsfilter lˆschen
		THROW_FAILED_HRESULT(DelPropertyBy(WTRiASPropertyBase(Connection), 
			L"TRiASConnectFilter"));

	// Datenquelle auffordern, ggf. den Verbindungsfilter zu entfernen
	WTRiASDatabase DBase;

		THROW_FAILED_HRESULT(Connection -> get_Database(DBase.ppi()));

	// may return E_NOTIMPL
		hr = WTRiASPropertyCallback(DBase) -> Refresh(CComBSTR(L"TRiASConnectFilter"));

	} COM_CATCH;
	return hr;
}

HRESULT DatenBasisObjekt::GetAttachedConnectionFilter (GETATTACHEDCONNECTIONFILTER *pGACF)
{
	COM_TRY {
	// passende Connection finden
	CComVariant vConnection(pGACF -> pcConnName);
	WTRiASConnection Connection;

		if (FAILED(m_Prj -> get_Connection(vConnection, Connection.ppi())))
			return E_INVALIDARG;

	CONNECTSTATUS rgStatus = CONNECTSTATUS_Closed;

		THROW_FAILED_HRESULT(Connection -> get_Status (&rgStatus));
		if (CONNECTSTATUS_Opened != rgStatus) 
			return E_INVALIDARG;		// DB nicht geˆffnet

	// Verbindungsfilter setzen
	WTRiASConnectionFilter Filter (GetPropertyFrom(WTRiASPropertyBase(Connection), 
			L"TRiASConnectFilter", (IDispatch *)NULL), true);
	CComBSTR bstrName;

		if (Filter.IsValid()) {
		// ggf. den Namen des verbindungsfilters liefern
			THROW_FAILED_HRESULT(Filter -> get_Name(&bstrName));

			if (NULL != pGACF -> pName) {
				USES_CONVERSION;
			
			char const *pcName = OLE2A(bstrName);
			int iToCopy = min(pGACF -> iLen-1, (int)bstrName.Length());

				strncpy (pGACF -> pName, pcName, iToCopy);
				pGACF -> pName[iToCopy] = '\0';
			}

		// in jeden Fall die benˆtigte Puffergrˆﬂe liefern
			pGACF -> iLen = bstrName.Length()+1;
		}
		else {
			pGACF -> iLen = 0;		// no ConnectionFilter at all
			return E_INVALIDARG;
		}

	} COM_CATCH;
	return S_OK;
}

