// @doc
// @module DBObjCom.cpp | COM-Spezifika eines <c DatenBasisObjekt> Objektes

#include "TriasPre.hxx"
#include "TRiASRes.h"
#include "Strings.h"

#include <registry.hxx>
#include <PropertyHelper.h>

#if defined(_DEBUG)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

///////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern short g_iHideFlags;

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(TRiASProperty);
DefineSmartInterface(Storage);

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
		ATLTRY(_Idents = new CIdTree());
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

	IrisWind *pW = GetViewWindow();

		TX_ASSERT(NULL != pW);
		THROW_FAILED_HRESULT(RePrepareDBO(pW, pW -> GetAspectRatio()));

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

		THROW_FAILED_HRESULT(Conn -> get_Location (&bstrName));

	HPROJECT hPr = m_pGeoDBs -> IsOpened (OLE2A(bstrName));

		if (NULL != hPr) {
		GeoDB &rDB = m_pGeoDBs -> DB(hPr);
		int iIndex = m_pGeoDBs -> FFindItem (hPr);

			TX_ASSERT(-1 != iIndex);

			CloseConnection (rDB, false);	// sollte bereits gespeichert sein
			m_pGeoDBs -> FDelItem (iIndex);	// jetzt aus Liste herausnehmen
		}

	} catch (_com_error &e) {
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP DatenBasisObjekt::ConnectionClosed (BSTR Name)
{
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

///////////////////////////////////////////////////////////////////////////////
// Zugehöriges TRiASProject behandeln
HRESULT DatenBasisObjekt::AttachTRiASProject (ITRiASProject *pIPrj, ITRiASProject **ppIPrj)
{
	try {
	// Projekt speichern
	WTRiASProject Prj (m_Prj);

		m_Prj = pIPrj;			// throws hr
		if (NULL != ppIPrj)
			*ppIPrj = Prj.detach();

		if (!m_Prj)		// Detach
			return S_OK;

	// alle notwendigen Properties des Projektes abfragen
	WTRiASProperties Props;

		THROW_FAILED_HRESULT(m_Prj -> get_Properties (Props.ppi()));

	// FullRedrawOnScroll
	VARIANT_BOOL fFlag = GetProperty (Props, IDS_SCROLLMODE, VARIANT_FALSE);

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

			dwColor = GetProperty (Props, IDS_BACKGROUNDCOLOR, (LONG)dwColor);
			SetBkColor ((Color &)dwColor);

		Brush *pB = NULL;
		
			TX_TRY(pB = new Brush((Color &)dwColor));
			if (NULL != pB) m_pViewWnd -> SetBackground (pB);
		}

	// HideFlags einlesen
	CCurrentUser regCfg (g_cbRegConfig);

		{
		DWORD dwData = DWORD(ROSortObjNr|ROHideIdent);

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
			strcpy (cbBuffer, OLE2A(GetProperty (Props, g_cbShowObjProp, (BSTR)bstr)));
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

#if defined(_USE_LEGACY_CODE)
	if (NULL == (IDispatch *)m_Prj) {
		if (!DB().isOpened())			// evtl. während der SchließPhase
			return E_FAIL;
		
		return DB().GetProjectStorage(ppIStg);
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(NULL != (IDispatch *)m_Prj);
		try {
		// alle notwendigen Properties des Projektes abfragen
		WTRiASProperties Props;

			THROW_FAILED_HRESULT(m_Prj -> get_Properties (Props.ppi()));

		// GetProperty liefert ohne AddRef ab!
		WStorage Stg (GetProperty (Props, g_cbStgService, (IUnknown *)NULL));

			*ppIStg = Stg.detach();

		} catch (_com_error &e) {
			return _COM_ERROR(e);
		}
	}
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Storage einer Datenquelle besorgen
HRESULT DatenBasisObjekt::GetDataSourceStorage (HPROJECT hPr, IStorage **ppIStg)
{
	if (NULL == ppIStg) return E_POINTER;

#if defined(_USE_LEGACY_CODE)
	if (NULL == (IDispatch *)m_Prj) 
	{
		return E_FAIL;
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(NULL != (IDispatch *)m_Prj);
	
	int iItem = m_pGeoDBs -> FFindItem (hPr);

		if (-1 == iItem || !DB(hPr).isOpened())			// evtl. während der SchließPhase
			return E_FAIL;
		return DB(hPr).GetProjectStorage(ppIStg);
	}
	return S_OK;
}

HRESULT DatenBasisObjekt::GetDataSourceDescription (HPROJECT hPr, char *pDesc)
{
	TX_ASSERT(NULL != (IDispatch *)m_Prj);

int iItem = m_pGeoDBs -> FFindItem (hPr);

	if (-1 == iItem || !DB(hPr).isOpened())			// evtl. während der SchließPhase
		return E_FAIL;
	return DB(hPr).GetDataSourceDescription (pDesc) ? S_OK : E_FAIL;
}


HRESULT DatenBasisObjekt::GetDataSourceName (HPROJECT hPr, char *pName)
{
	TX_ASSERT(NULL != (IDispatch *)m_Prj);

int iItem = m_pGeoDBs -> FFindItem (hPr);

	if (-1 == iItem || !DB(hPr).isOpened())			// evtl. während der SchließPhase
		return E_FAIL;
	
	strcpy (pName, DB(hPr).GetDBName());
	return S_OK;
}

HRESULT DatenBasisObjekt::RetrieveActiveProject (char *pBuffer, int iLen)
{
#if defined(_USE_LEGACY_CODE)
	if (NULL == (IDispatch *)m_Prj) 
	{
	int iNameLen = strlen(DB().GetDBName());
	int iToCopy = min(iLen-1, iNameLen);

		strncpy (pBuffer, DB().GetDBName(), iToCopy);	// DBNamen kopieren
		pBuffer[iToCopy] = '\0';
		return S_OK;
	} else
#endif // _USE_LEGACY_CODE
	{
		TX_ASSERT(NULL != (IDispatch *)m_Prj);

		USES_CONVERSION;
		try {
		CComBSTR bstrName;

			THROW_FAILED_HRESULT(m_Prj -> get_Name (&bstrName));

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

