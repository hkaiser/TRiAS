// AuxUIOwner.cpp : Implementation of the CAuxUIOwner

#include "fakemfcp.hxx"
#include "fakemfc.h"

#include <itoolbar.h>
#include <toolguid.h>
#include <dirisole.h>

#include "Wrapper.h"		// SmartInterfaces
#include "fakemfc.hxx"

#include "MainFrm.h"
#include "AuxUIOwner.h"

#if defined(_USE_SEC_CLASSES)
#include "ZoomComboBoxSec.h"
#include "CoordStaticsSec.h"
#else
#include "ZoomComboBox.h"
#include "CoordStatics.h"
#endif // _USE_SEC_CLASSES

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#if _TRiAS_VER < 0x0400
extern DWORD g_dwVer4;		// Version 4 emulieren?
#endif // _TRiAS_VER < 0x0400

///////////////////////////////////////////////////////////////////////////////
// Statische Tabelle, aus der zur Laufzeit die map aufgebaut wird
// über die die Aktionen für ein Control ausgewählt werden
const UIOWNERDATA CAuxUIOwner::m_rgUIOwnerData[] = {
//
// Standard ///////////////////////////////////////////////////////////////////
	{ ID_STANDARD_NEWPRJ, 
		{	CAuxUIOwner::EnableAlways, CAuxUIOwner::EnableAlways, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnNewProject, 
		}, 
	},
	{ ID_STANDARD_OPEN, 
		{	CAuxUIOwner::EnableAlways, CAuxUIOwner::EnableAlways, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnOpenProject, 
		}, 
	},
	{ ID_STANDARD_SAVEDB, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnDirty, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_STANDARD_DATASOURCES, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableAlways, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnManageDataSources, 
		}, 
	},
	{ ID_STANDARD_CLOSE, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableAlways, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_STANDARD_PRINT, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_STANDARD_PRINTPREVIEW, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnPrintPreview, 
		}, 
	},
	{ ID_STANDARD_UNDO,	
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnCanUndo, 
			NULL, 
			NULL, CAuxUIOwner::UndoSelectString, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_STANDARD_REDO, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnCanRedo, 
			NULL, 
			NULL, CAuxUIOwner::RedoSelectString, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_STANDARD_CUSTOMIZE, 
#if _TRiAS_VER >= 0x0400
		{	CAuxUIOwner::EnableAlways, CAuxUIOwner::EnableAlways, 
#else
		{	CAuxUIOwner::EnableWhenVer4, CAuxUIOwner::EnableAlways, 
#endif // _TRiAS_VER >= 0x0400
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_STANDARD_SEARCH, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_STANDARD_REPLACE, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_STANDARD_LEGENDE, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			CAuxUIOwner::LegendeState, 
			CAuxUIOwner::StringIDForLegend, NULL, 
			CN_COMMAND, CAuxUIOwner::OnLegendCmd, 
		}, 
	},
	{ ID_STANDARD_OVERVIEW, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableNotPainting, 
			CAuxUIOwner::OverviewState, 
			CAuxUIOwner::StringIDForOverview, NULL, 
			CN_COMMAND, CAuxUIOwner::OnOverViewCmd, 
		}, 
	},
//
// Ansichten //////////////////////////////////////////////////////////////////
	{ ID_GEOVIEW_ZOOMIN, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOVIEW_ZOOMOUT, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOVIEW_NEW, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnWriteAble, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOVIEW_DELETE, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnViewExist, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOVIEW_NEWCONT, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivatedAndWriteAble, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOVIEW_DELCONT, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnViewCont, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOVIEW_SELECTVIEW, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnViewExist, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
#if !defined(_USE_SEC_CLASSES)
	{ ID_GEOVIEW_SELECTVIEW_BOX, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnViewExist, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnSelectView, 
		}, 
	},
#else
	{ ID_GEOVIEW_SELECTVIEW, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnViewExist, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CBN_SELCHANGE, CAuxUIOwner::OnSelectView, 
		}, 
	},
#endif // _USE_SEC_CLASSES
	{ ID_GEOVIEW_SELSCALE, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
#if !defined(_USE_SEC_CLASSES)
	{ ID_GEOVIEW_SELECTZOOM_BOX, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnSelectZoom, 
		}, 
	},
	{ ID_GEOVIEW_SELECTZOOM_TEXT, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::DefaultStringID, NULL, 
			CN_COMMAND, NULL, 
		}, 
	},
#else
	{ ID_GEOVIEW_SELSCALE, //ID_GEOVIEW_SELECTZOOM_BOX, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CBN_KILLFOCUS, CAuxUIOwner::OnSelectZoom, 
		}, 
	},
	{ ID_GEOVIEW_SELSCALE, //ID_GEOVIEW_SELECTZOOM_BOX, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CBN_HITRETURN, CAuxUIOwner::OnSelectZoom, 
		}, 
	},
	{ ID_GEOVIEW_SELSCALE, //ID_GEOVIEW_SELECTZOOM_BOX, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CBN_SELCHANGE, CAuxUIOwner::OnSelectZoom, 
		}, 
	},
#endif // _USE_SEC_CLASSES
	{ ID_GEOVIEW_HOLDZOOM, 
//		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnORWndsExist, 
//		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			CAuxUIOwner::HoldZoomState, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnHoldZoom, 
		}, 
	},
	{ ID_GEOVIEW_REPAINT, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOVIEW_PREVENT_REPAINT, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			CAuxUIOwner::PreventRepaintState, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnPreventRepaint, 
		}, 
	},
//
// GeoClasses /////////////////////////////////////////////////////////////////
	{ ID_GEOCLASS_SELECT, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOCLASS_DELETE, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivatedAndWriteAble, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOCLASS_MODIFY, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivatedAndWriteAble, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOCLASS_VISPARAMS, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivatedAndWriteAble, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOCLASS_PRIORITY, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivatedAndWriteAble, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOCLASS_COPYOBJECTS, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivatedAndWriteAble, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOCLASS_OBJPROP, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_GEOCLASS_DELOBJPROP, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
//
// FullScreen /////////////////////////////////////////////////////////////////
	{ ID_FULLSCREEN_TOGGLE, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableAlways, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmdFullScreen, 
		}, 
	},
//
// Koordinaten ////////////////////////////////////////////////////////////////
	{ ID_COORDS_SELECTFORMAT, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnCanCTFConfig, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnTRiASCmd, 
		}, 
	},
	{ ID_COORDS_SHOWCOORDS_STATIC, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, NULL, 
		}, 
	},

///////////////////////////////////////////////////////////////////////////////
// ConnectFilter
	{ ID_CONNECTFILTERS_MANAGE, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnManageConnectFilters, 
		}, 
	},
	{ ID_CONNECTFILTERS_CREATE, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableViewActivated, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CN_COMMAND, CAuxUIOwner::OnCreateConnectFilter, 
		}, 
	},
	{ ID_CONNECTFILTERS_TOGGLESHOW, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableConnectFiltersExist, 
			CAuxUIOwner::ShowConnectFilters, 
			CAuxUIOwner::StringIDForConnectFilter, NULL, 
			CN_COMMAND, CAuxUIOwner::OnShowConnectFilters, 
		}, 
	},

//
// Endekennung ////////////////////////////////////////////////////////////////
	{ 0L, { NULL, NULL, NULL, NULL, NULL, 0, NULL, }, },
};

///////////////////////////////////////////////////////////////////////////////
// Dynamische Daten initialisieren

HRESULT CAuxUIOwner::FinalConstruct (void)
{
// alles, was definiert ist, in der map speichern
	for (const UIOWNERDATA *pcData = m_rgUIOwnerData; 
		 pcData -> uiCtrlID != 0L; pcData++)
	{
	UIOwnerData::iterator it = 
		m_Data.insert (pcData -> uiCtrlID, &pcData -> Procs);

		ASSERT(it != m_Data.end());		// muß erfolgreich sein
	}
	return S_OK;
}

CAuxUIOwner::CAuxUIOwner (void)
{
	m_fOpenProject = false;
	m_fIsDirty = false;
	m_fIsRO = false;
	m_fActiveView = false;
	m_fViewPainted = false;
	m_fPaintingView = false;

	m_dwCookie = 0L;
}

///////////////////////////////////////////////////////////////////////////////
// Am TRiAS-ConnectionPoint ankoppeln
HRESULT CAuxUIOwner::SetXtsnSite (ITriasXtensionSite *pSite)
{
	try {
		m_Cont = pSite;		// throws HRESULT
		THROW_FAILED_HRESULT(AtlAdvise (m_Cont, (ITRiASNotificationSink *)this, IID_ITRiASNotificationSink, &m_dwCookie));

	} catch (_com_error& hr) {
		return _COM_ERROR(hr);
	}

	return NOERROR;
}

HRESULT CAuxUIOwner::DisConnectFromServer (void)
{
HRESULT hr = NOERROR;

	if (NULL != (IUnknown *)m_Cont && 0 != m_dwCookie) {
		hr = AtlUnadvise (m_Cont, IID_ITRiASNotificationSink, m_dwCookie);
		if (SUCCEEDED(hr)) {
			m_dwCookie = 0L;
			m_Cont.Assign (NULL);	// Release()
		}
	}

	return hr;
}

/////////////////////////////////////////////////////////////////////////////
// *** ITRiASUIOwner specific functions ***

HRESULT CAuxUIOwner::OnUpdateUI (ITRiASBar *pIBar, ITRiASCmdUI *pICmdUI)
{
	if (NULL == pIBar) return E_POINTER;

int uiID = 0;

	pICmdUI -> get_CmdID (&uiID);		// ID des Buttons besorgen

UIOwnerData::iterator it = m_Data.find ((UINT)uiID);

	ASSERT(it != m_Data.end());

// Testen, ob überhaupt ein Projekt geöffnet ist
HRESULT hr = E_FAIL;
const UIOWNERPROCS *pProcs = (*it).second;

	ASSERT(NULL != pProcs);

	if (!m_fOpenProject) {
		ASSERT(NULL != pProcs -> pFcnClosed);
		hr = pICmdUI -> put_IsEnabled ((this ->* pProcs -> pFcnClosed)(pIBar, (UINT)uiID));

	// #HK010927: nun auch bei geschlossenem Projekt Checkstate abfragen
		if (SUCCEEDED(hr) && NULL != pProcs -> pFcnCheck)
			return pICmdUI -> put_CheckState ((this ->* pProcs -> pFcnCheck)(pIBar, uiID));
		return hr;
	}

// Projekt ist geöffnet
	ASSERT(NULL != pProcs -> pFcnOpened);

	hr = pICmdUI -> put_IsEnabled ((this ->* pProcs -> pFcnOpened)(pIBar, uiID));
	if (SUCCEEDED(hr) && NULL != pProcs -> pFcnCheck)
		return pICmdUI -> put_CheckState ((this ->* pProcs -> pFcnCheck)(pIBar, uiID));

	return hr;
}

HRESULT CAuxUIOwner::OnSelect (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (/*NULL == pIBar ||*/ NULL == pBuffer || 0 == ulLen) 
		return E_POINTER;

// Select behandeln, dazu ResID oder String besorgen
UIOwnerData::iterator it = m_Data.find (uiID);

	ASSERT(it != m_Data.end());

const UIOWNERPROCS *pProcs = (*it).second;

	ASSERT(NULL != pProcs);
//	ASSERT(NULL != pProcs -> pFcnResID || NULL != pProcs -> pFcnResStr);

	TRY {
	CString str;

		if (NULL != pProcs -> pFcnResID) {
		UINT uiResID = (this ->* pProcs -> pFcnResID)(pIBar, uiID);

			ASSERT(0 != uiResID);
			VERIFY(str.LoadString (uiResID));
		} else if (NULL != pProcs -> pFcnResStr) {
		LPSTR pStr = str.GetBuffer(ulLen);

			(this ->* pProcs -> pFcnResStr)(pIBar, uiID, pStr, ulLen);
			str.ReleaseBuffer();
		} else {
			*pBuffer = '\0';
			if (pulWritten)
				*pulWritten = 0;
			return NOERROR;
		}

	ULONG ulToWrite = min (ulLen-1, ULONG(str.GetLength()));

		strncpy (pBuffer, str, ulToWrite);
		pBuffer[ulToWrite] = '\0';

		if (pulWritten)
			*pulWritten = ulToWrite;

	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

return NOERROR;
}

HRESULT CAuxUIOwner::OnCommand (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (NULL == pIBar) return E_POINTER;

UIOwnerData::iterator it = m_Data.find (uiID);

	ASSERT(it != m_Data.end());

// solange in der Tabelle suchen, bis der entsprechende Befehl gefunden wurde
	do {
	const UIOWNERPROCS *pProcs = (*it).second;

		ASSERT(NULL != pProcs);
#if defined(_USE_SEC_CLASSES)
	// nCode nur mit OT vergleichen
		if (pProcs -> iCode == nCode) 
#endif // _USE_SEC_CLASSES
		{
			if (NULL != pProcs -> pFcnCmd)
				return (this ->* pProcs -> pFcnCmd)(pIBar, uiID, nCode);		// Befehl ausführen
		}

		it++;	// der Nächste Bitte
	} while ((*it).first == uiID);

	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASNotificationSink specific functions ***
STDMETHODIMP CAuxUIOwner::ServerEvent (SERVEREVT se)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();		// ConnectionPoint abmelden
		break;
	}
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	switch (pe) {
	case PROJECTEVT_ProjectOpened:
		m_fOpenProject = true;
		m_fIsRO = DEX_GetROModeEx (HACTPROJECT) ? true : false;
		m_fIsDirty = DEX_IsGeoDBDirtyEx (HACTPROJECT) ? true : false;
		m_fViewPainted = false;
		break;

	case PROJECTEVT_ProjectToClose:
		m_fOpenProject = false;
		m_fIsRO = true;
		m_fIsDirty = false;
		m_fViewPainted = false;
		break;

	case PROJECTEVT_ProjectIsDirty:
		m_fIsDirty = true;
		break;

	case PROJECTEVT_ProjectIsNotDirty:
		m_fIsDirty = false;
		break;
	}
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT vData)
{
	AFX_MANAGE_STATE(AfxGetAppModuleState())
	switch (ve) {
	case GEOVIEWEVT_ViewSelected:
		m_fActiveView = (VT_BSTR == vData.vt && NULL != V_BSTR(&vData)) ? true : false;
		if (!m_fActiveView)
			m_fViewPainted = false;
		break;

	case GEOVIEWEVT_PaintingView:
		m_fViewPainted = true;
		m_fPaintingView = true;
		break;

	case GEOVIEWEVT_ViewPainted:
		m_fPaintingView = false;
		break;
	}
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState())
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// ENABLEPROC

// Immer 'true' ---------------------------------------------------------------
bool CAuxUIOwner::EnableAlways (ITRiASBar *pIBar, UINT uiID)
{
	return true;
}

// Immer 'false' --------------------------------------------------------------
bool CAuxUIOwner::DisableAlways (ITRiASBar *pIBar, UINT uiID) 
{
	return false;
}

// wenn RO, dann passiviert ---------------------------------------------------
bool CAuxUIOwner::EnableOnWriteAble (ITRiASBar *pIBar, UINT uiID)
{
	return !m_fIsRO;
}

// Enable, wenn SichtContainer definiert ist ----------------------------------
bool CAuxUIOwner::EnableOnViewCont (ITRiASBar *pIBar, UINT uiID)
{
	if (m_fIsRO) return false;

	return DEX_GetActViewContainer(NULL);		// nur abfragen
}

// Enable, wenn mindestens eine Ansicht existiert -----------------------------
bool CAuxUIOwner::EnableOnViewExist (ITRiASBar *pIBar, UINT uiID)
{
// TODO: to be implemented
	return true;
}

// Enable, wenn Sicht aktiviert ist -------------------------------------------
bool CAuxUIOwner::EnableViewActivated (ITRiASBar *pIBar, UINT uiID)
{
	return m_fActiveView && m_fViewPainted;
}

// Enable, wenn Sicht aktiviert ist -------------------------------------------
bool CAuxUIOwner::EnableViewActivatedAndWriteAble (ITRiASBar *pIBar, UINT uiID)
{
	return (!m_fIsRO && m_fActiveView && m_fViewPainted);
}

// Enable, wenn zumindest ein Objektrecherchefenster existiert
bool CAuxUIOwner::EnableOnORWndsExist (ITRiASBar *pIBar, UINT uiID)
{
	return m_fActiveView && m_fViewPainted && (DEX_ActiveObjectsCount() > 0);
}

#if _TRiAS_VER < 0x0400
// Enable, wenn Version 4 emuliert werden soll
bool CAuxUIOwner::EnableWhenVer4 (ITRiASBar *pIBar, UINT uiID)
{
	return (0 != g_dwVer4) ? true : false;
}
#endif // _TRiAS_VER < 0x0400

// Enable, wenn derzeit nicht gezeichnet wird (für Overview)
bool CAuxUIOwner::EnableNotPainting (ITRiASBar *pIBar, UINT uiID)
{
BOOL fVisible = TRUE;

	DEX_IsOverViewBarVisible(fVisible);
	return (DEX_IsOverviewActive() && fVisible) || (m_fActiveView && m_fViewPainted && !m_fPaintingView);
}

// Enable, wenn Undo möglich ist ----------------------------------------------
bool CAuxUIOwner::EnableOnCanUndo (ITRiASBar *pIBar, UINT uiID)
{
	return S_OK == DEX_CanUndoString(NULL);
}

// Enable, wenn Redo möglich ist ----------------------------------------------
bool CAuxUIOwner::EnableOnCanRedo (ITRiASBar *pIBar, UINT uiID)
{
	return S_OK == DEX_CanRedoString(NULL);
}

// Enable, wenn GeoDB Dirty ist -----------------------------------------------
bool CAuxUIOwner::EnableOnDirty (ITRiASBar *pIBar, UINT uiID)
{
	return DEX_IsGeoDBDirtyEx (HACTPROJECT) ? true : false;
}

// Enable, Sicht aktiv und CTF konfigurierbar ist -----------------------------
bool CAuxUIOwner::EnableOnCanCTFConfig (ITRiASBar *pIBar, UINT uiID)
{
	return /*m_fActiveView && m_fViewPainted && */DEX_CTFCanConfig();
}

// Enable, wenn mindestens ein ConnectFilter existiert ------------------------
namespace {
	BOOL CALLBACK ConnectFiltersExist(char *pPtr, BOOL fNotLast, void *pData)
	{
		*reinterpret_cast<bool *>(pData) = true;
		return FALSE;		// einmal reicht
	}
}

bool ConnectFiltersExist()
{
bool fExists = false;
ENUMNOKEY ENK;

	ENK.eFcn = reinterpret_cast<ENUMNOKEYPROC>(ConnectFiltersExist);
	ENK.ePtr = &fExists;
	DEX_EnumConnectionFilters(ENK);
	return fExists;
}

bool CAuxUIOwner::EnableConnectFiltersExist(ITRiASBar *pIBar, UINT uiID)
{
	return m_fActiveView && m_fViewPainted && ConnectFiltersExist();
}

///////////////////////////////////////////////////////////////////////////////
// CHECKSTATEPROC

// Entscheidet, ob Legende angezeigt ist oder nicht 
int CAuxUIOwner::LegendeState (ITRiASBar *pIBar, UINT uiID)
{
BOOL fVisible = TRUE;

	DEX_IsProjectBarVisible(fVisible);
	return (DEX_IsLegendActive() && fVisible) ? 1 : 0;
}

int CAuxUIOwner::HoldZoomState (ITRiASBar *pIBar, UINT uiID)
{
//	return DEX_GetLimitSearches() ? 1 : 0;
//	return DEX_IsHoldZoomActive() ? 1 : 0;
	return DEX_GetIgnoreSearchOptions() ? 1 : 0;
}

int CAuxUIOwner::OverviewState (ITRiASBar *pIBar, UINT uiID)
{
BOOL fVisible = TRUE;

	DEX_IsOverViewBarVisible(fVisible);
	return (DEX_IsOverviewActive() && fVisible) ? 1 : 0;
}

int CAuxUIOwner::PreventRepaintState (ITRiASBar *pIBar, UINT uiID)
{
	return DEX_IsPreventRepaintActive() ? 1 : 0;
}

// ConnectFilter anzeigen
int CAuxUIOwner::ShowConnectFilters (ITRiASBar *pIBar, UINT uiID)
{
BOOL fFiltersShown = FALSE;

	DEX_ConnectionFiltersShown(fFiltersShown);
	return fFiltersShown && ConnectFiltersExist() ? 1 : 0;
}

///////////////////////////////////////////////////////////////////////////////
// SELECTSTRINGIDPROC
UINT CAuxUIOwner::CtrlIdIsStringID (ITRiASBar *pIBar, UINT uiID)
{
	return uiID;		// ControlID ist gleichzeitig StringID
}

UINT CAuxUIOwner::DefaultStringID (ITRiASBar *pIBar, UINT uiID)
{
	return AFX_IDS_IDLEMESSAGE;		// "Bereit."
}

// Legende mit Checkstate -----------------------------------------------------
UINT CAuxUIOwner::StringIDForLegend (ITRiASBar *pIBar, UINT uiID)
{
BOOL fVisible = TRUE;

	DEX_IsProjectBarVisible(fVisible);
	return (DEX_IsLegendActive() && fVisible) ? ID_STANDARD_LEGENDE_ON : 
		ID_STANDARD_LEGENDE;
}

// Overview mit Checkstate ----------------------------------------------------
UINT CAuxUIOwner::StringIDForOverview (ITRiASBar *pIBar, UINT uiID)
{
BOOL fVisible = TRUE;

	DEX_IsOverViewBarVisible(fVisible);
	return (DEX_IsOverviewActive() && fVisible) ? ID_STANDARD_OVERVIEW_ON : 
		ID_STANDARD_OVERVIEW;
}

// ConnectFilters mit Checkstate ----------------------------------------------
UINT CAuxUIOwner::StringIDForConnectFilter (ITRiASBar *pIBar, UINT uiID)
{
BOOL fFiltersShown = FALSE;

	DEX_ConnectionFiltersShown(fFiltersShown);
	return fFiltersShown ? ID_CONNECTFILTERS_TOGGLESHOW_ON : 
		ID_CONNECTFILTERS_TOGGLESHOW;
}

///////////////////////////////////////////////////////////////////////////////
// SELECTSTRINGSTRINGPROC

// spezielles UndoString generieren -------------------------------------------
bool CAuxUIOwner::UndoSelectString (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen)
{
	if (NULL == pBuffer) return false;

	TRY {
	CString strTpl, strUndo;
	LPSTR pUndo = strUndo.GetBuffer(_MAX_PATH);

		*pUndo = '\0';
		if (S_OK == DEX_CanUndoString (pUndo))	// Undo möglich
			strTpl.Format (ID_STANDARD_UNDO2, (LPCSTR)strUndo, (LPCSTR)strUndo);
		else
			strTpl.Format (ID_STANDARD_UNDO);

	ULONG ul = min(ulLen-1, (ULONG)strTpl.GetLength());
		 
		strncpy (pBuffer, strTpl, ul);
		pBuffer[ul] = '\0';
		return true;

	} CATCH (CMemoryException, e) {
		pBuffer[0] = '\0';
		return false;
	} END_CATCH

return false;
}	

// spezielles RedoString generieren -------------------------------------------
bool CAuxUIOwner::RedoSelectString (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen)
{
	if (NULL == pBuffer) return false;

	TRY {
	CString strTpl, strUndo;
	LPSTR pUndo = strUndo.GetBuffer(_MAX_PATH);

		*pUndo = '\0';
		if (S_OK == DEX_CanRedoString (pUndo))	// Undo möglich
			strTpl.Format (ID_STANDARD_REDO2, (LPCSTR)strUndo, (LPCSTR)strUndo);
		else
			strTpl.Format (ID_STANDARD_REDO);

	ULONG ul = min(ulLen-1, (ULONG)strTpl.GetLength());
		 
		strncpy (pBuffer, strTpl, ul);
		pBuffer[ul] = '\0';
		return true;

	} CATCH (CMemoryException, e) {
		pBuffer[0] = '\0';
		return false;
	} END_CATCH

return false;
}	

///////////////////////////////////////////////////////////////////////////////
// COMMANDPROC 
HRESULT CAuxUIOwner::OnTRiASCmd (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// TRiAS-Menubefehl zuordnen
// der MenuID von TRiAS ist gleich dem ButtonID-RESID_OFFSET
	ForwardMsgToTRiAS (__hWndM, WM_COMMAND, uiID-RESID_OFFSET, 0L);
	return NOERROR;
}

HRESULT CAuxUIOwner::OnTRiASCmdFullScreen (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// TRiAS-Menubefehl zuordnen
UINT uiOffset = g_pTE -> MenuOffset();

	ForwardMsgToTRiAS (__hWndM, WM_COMMAND, uiOffset+IDM_SWITCHFULLSCREENMODE, 0L);
	return NOERROR;
}

HRESULT CAuxUIOwner::OnSelectView (ITRiASBar *pIBar, UINT uiID, int nCode)
{
// Sicht aus ComboBox auswählen
	if (nCode != CBN_SELCHANGE)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// aktuelle Sicht abfragen
	TRY {
	CString strActView;
	LPSTR pActView = strActView.GetBuffer(MAXVIEWNAMESIZE);

		if (NULL == DEX_GetActiveSight (pActView)) 
			strActView.Empty();

	// neue Ansicht aus ComboBox lesen
	HWND hTB = NULL;
	HRESULT hr = pIBar -> GetBarHandle (&hTB);

		if (FAILED(hr)) return S_FALSE;

	HWND hCtrl = ::GetDlgItem (hTB, uiID);

		ASSERT(NULL != hCtrl);

	CComboBox *pCB = (CComboBox *)CWnd::FromHandle (hCtrl);
	int iIndex = pCB -> GetCurSel();

		if (CB_ERR == iIndex) return S_FALSE;	// nichts selektiert

	CString strNewView, strNoView;		// neu einzustellende Ansicht

		pCB -> GetLBText (iIndex, strNewView);
		VERIFY(strNoView.LoadString (IDS_NOACTIVEVIEW));
		if (!strcmp (strNewView, strNoView)) 	// keine Sicht ausgewählt und wieder keine Sicht auswählten
			return true;

		VERIFY(strNoView.LoadString (IDS_TEMPACTIVEVIEW));
		if (!strcmp (strNewView, strNoView)) 	// temporäre Sicht ausgewählt
			return true;

	// evtl. dranhängende Datenquelle abschneiden
	int iViewLen = pCB -> GetItemData (iIndex);

		if (0 != iViewLen && strNewView.GetLength() != iViewLen) {
			_ASSERTE(strNewView.GetLength() > iViewLen);
			strNewView = strNewView.Left (iViewLen);
		}

	// ggf. StartAnsicht setzen (auch, wenn Ansicht bereits aktiv ist)
		if (GetKeyState (VK_CONTROL) < 0) {
			DEX_SetDefaultView (NULL);		// erst evtl. existierende StartAnsicht löschen
			DEX_SetDefaultView ((LPCSTR)strNewView);	// neue einstellen
		}

		if (strcmp (strNewView, strActView)) {
		CWaitCursor Wait;

			DEX_SelectNewSight ((LPCSTR)strNewView);
			DEX_RePaint();

		HWND hWnd = DEX_GetActiveViewWindow();

			ASSERT(::IsWindow(hWnd));
			::SetFocus(hWnd);
		}
	} CATCH (CMemoryException, e) {
		return E_OUTOFMEMORY;
	} END_CATCH

return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Neues Projekt anlegen
HRESULT	CAuxUIOwner::OnNewProject (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// TRiAS-Menubefehl zuordnen
	ForwardMsgToTRiAS (__hWndM, WM_COMMAND, g_pTE->MenuOffset()+IDM_CREATENEWPROJECT, 0L);
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Projekt öffnen
HRESULT	CAuxUIOwner::OnOpenProject (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// TRiAS-Menubefehl zuordnen
	ForwardMsgToTRiAS (__hWndM, WM_COMMAND, g_pTE->MenuOffset()+IDM_OPENPROJECT, 0L);
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
//// Recherchen auf Ausschnitt begrenzen
// Ausschnitt beibehalten
HRESULT	CAuxUIOwner::OnHoldZoom (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

//	DEX_SetLimitSearches(!DEX_GetLimitSearches());
//	DEX_SetHoldZoom(!DEX_IsHoldZoomActive());
	DEX_SetIgnoreSearchOptions(!DEX_GetIgnoreSearchOptions());
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Neuzeichnen unterbinden
HRESULT	CAuxUIOwner::OnPreventRepaint (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

	DEX_SetPreventRepaint(!DEX_IsPreventRepaintActive());
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Datenquellen verwalten
HRESULT	CAuxUIOwner::OnManageDataSources (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// TRiAS-Menubefehl zuordnen
	ForwardMsgToTRiAS (__hWndM, WM_COMMAND, g_pTE->MenuOffset()+IDM_MANAGEDATASOURCES, 0L);
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Druckvorschau anzeigen
HRESULT	CAuxUIOwner::OnPrintPreview (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// TRiAS-Menubefehl zuordnen
	ForwardMsgToTRiAS (__hWndM, WM_COMMAND, g_pTE->MenuOffset()+IDM_PRINTPREVIEW, 0L);
	return NOERROR;
}

///////////////////////////////////////////////////////////////////////////////
// Connectfilter verwalten
HRESULT	CAuxUIOwner::OnManageConnectFilters (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// TRiAS-Menubefehl zuordnen
	ForwardMsgToTRiAS (__hWndM, WM_COMMAND, g_pTE->MenuOffset()+IDM_MANAGECONNECTFILTERS, 0L);
	return NOERROR;
}

HRESULT	CAuxUIOwner::OnCreateConnectFilter (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// TRiAS-Menubefehl zuordnen
	ForwardMsgToTRiAS (__hWndM, WM_COMMAND, g_pTE->MenuOffset()+IDM_CREATECONNECTFILTER, 0L);
	return NOERROR;
}

HRESULT	CAuxUIOwner::OnShowConnectFilters (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// TRiAS-Menubefehl zuordnen
	ForwardMsgToTRiAS (__hWndM, WM_COMMAND, g_pTE->MenuOffset()+IDM_SHOWCONNECTFILTERS, 0L);
	return NOERROR;
}


///////////////////////////////////////////////////////////////////////////////
// Legende behandeln
HRESULT CAuxUIOwner::OnLegendCmd(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// Menubefehl richtig zuordnen
// Das Problem besteht darin, daß u.U. die Legende zwar noch existiert,
// das ProjektDockingFenster jedoch nicht mehr angezeigt ist. In diesem Fall
// muß lediglich die Legende wieder angezeigt werden
	if (DEX_IsLegendActive()) {
	// TRiAS ist der Meninung, daß die Legende noch angezeigt ist
	BOOL fVisible = TRUE;

		DEX_IsProjectBarVisible(fVisible);
		if(fVisible)
			ForwardMsgToTRiAS (__hWndM, WM_COMMAND, uiID-RESID_OFFSET, 0L);		// Legende zerlegen
		else
			ForwardMsgToTRiAS (__hWndM, WM_COMMAND, IDM_SHOWLEGENDE, 0L);		// Legende wieder einblenden	
	} else
		ForwardMsgToTRiAS (__hWndM, WM_COMMAND, uiID-RESID_OFFSET, 0L);			// Legende erzeugen
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Gesamtübersicht behandeln
HRESULT CAuxUIOwner::OnOverViewCmd(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != CN_COMMAND)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

// Menubefehl richtig zuordnen
// Das Problem besteht darin, daß u.U. die Gesamtübersicht zwar noch existiert,
// das ProjektDockingFenster jedoch nicht mehr angezeigt ist. In diesem Fall
// muß lediglich die Gesamtübersicht wieder angezeigt werden
	if (DEX_IsOverviewActive()) {
	// TRiAS ist der Meninung, daß die Gesamtübersicht noch angezeigt ist
	BOOL fVisible = TRUE;

		DEX_IsOverViewBarVisible(fVisible);
		if(fVisible)
			ForwardMsgToTRiAS (__hWndM, WM_COMMAND, uiID-RESID_OFFSET, 0L);		// Gesamtübersicht zerlegen
		else
			ForwardMsgToTRiAS (__hWndM, WM_COMMAND, IDM_SHOWOVERVIEW, 0L);		// Gesamtübersicht wieder einblenden	
	} else
		ForwardMsgToTRiAS (__hWndM, WM_COMMAND, uiID-RESID_OFFSET, 0L);			// Gesamtübersicht erzeugen
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Maßstab aus ComboBox auswählen
// GetMasstab rechnet den ComboBoxIndex in einen Maßstab um -------------------

long GetMasstab (short iIndex) 
{
	ASSERT(iIndex >= (IDS_MASSTAB250-IDS_MASSTAB250) && 
		   iIndex <= (IDS_MASSTAB5000000-IDS_MASSTAB250));

	switch (iIndex) {
	case IDS_MASSTAB250-IDS_MASSTAB250:		return 250L;
	case IDS_MASSTAB500-IDS_MASSTAB250:		return 500L;
	case IDS_MASSTAB1000-IDS_MASSTAB250:	return 1000L;
	case IDS_MASSTAB2000-IDS_MASSTAB250:	return 2000L;
	case IDS_MASSTAB4000-IDS_MASSTAB250:	return 4000L;
	case IDS_MASSTAB5000-IDS_MASSTAB250:	return 5000L;
	case IDS_MASSTAB10000-IDS_MASSTAB250:	return 10000L;
	case IDS_MASSTAB25000-IDS_MASSTAB250:	return 25000L;
	case IDS_MASSTAB50000-IDS_MASSTAB250:	return 50000L;
	case IDS_MASSTAB100000-IDS_MASSTAB250:	return 100000L;
	case IDS_MASSTAB200000-IDS_MASSTAB250:	return 200000L;
	case IDS_MASSTAB500000-IDS_MASSTAB250:	return 500000L;
	case IDS_MASSTAB750000-IDS_MASSTAB250:	return 750000L;
	case IDS_MASSTAB1000000-IDS_MASSTAB250:	return 1000000L;
	case IDS_MASSTAB2000000-IDS_MASSTAB250:	return 2000000L;
	case IDS_MASSTAB5000000-IDS_MASSTAB250:	return 5000000L;
	}

return 0L;
}

long myatol (LPCSTR pcStr) 
{
long lRes = 0L;

	while (*pcStr) {
		if (isdigit (*pcStr)) 
			lRes = 10*lRes + *pcStr - '0';
		pcStr++;
	}

return lRes;
}

HRESULT CAuxUIOwner::OnSelectZoom (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	switch (nCode) {
	case CBN_KILLFOCUS:
	case CBN_HITRETURN:
	case CBN_SELCHANGE:
		{
		long lZoom = 0;

			if (GetZoom (pIBar, uiID, lZoom, CBN_SELCHANGE != nCode) && 0 < lZoom) 
			{
				DEX_SetActiveZoom (lZoom);

			HWND hWnd = DEX_GetActiveViewWindow();

				ASSERT(::IsWindow(hWnd));
				::SetFocus(hWnd);
			}
		}
		return NOERROR;
	}
	return S_FALSE;
}

// neue Vergrößerung einlesen
bool CAuxUIOwner::GetZoom (ITRiASBar *pIBar, UINT uiID, long &rlZoom, bool fTestModify)
{
HWND hTB = NULL;
HRESULT hr = pIBar -> GetBarHandle (&hTB);

	if (FAILED(hr)) return false;

HWND hCtrl = ::GetDlgItem (hTB, uiID);

	ASSERT(NULL != hCtrl);

#if !defined(_USE_SEC_CLASSES)
CZoomComboBox *pCB = DYNAMIC_DOWNCAST (CZoomComboBox, CWnd::FromHandle (hCtrl));

	ASSERT(NULL != pCB);
	if (fTestModify && !pCB -> GetModify())
		return false;		// hat sich nicht geändert

	pCB -> SetModify (false);
#else
CComboBox *pCB = DYNAMIC_DOWNCAST (CComboBox, CWnd::FromHandle (hCtrl));

	ASSERT(NULL != pCB);
	if (fTestModify && !pCB -> SendMessage (WM_GETSETMODIFY, EM_GETMODIFY))
		return false;		// hat sich nicht geändert

	pCB -> SendMessage (WM_GETSETMODIFY, EM_SETMODIFY, false);
#endif // _USE_SEC_CLASSES

int iIndex = pCB -> GetCurSel();
CString strZoom;

	if (CB_ERR == iIndex) 
		pCB -> GetWindowText (strZoom);
	else
		pCB -> GetLBText (iIndex, strZoom);
	
	rlZoom = myatol (strZoom);
	return true;
}

