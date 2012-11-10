// AuxUIOwner.cpp : Implementation of the CAuxUIOwner

#include "stdafx.h"

#include "GbmTRiAS.h"

#include "resource.h"

#include <itoolbar.h>
#include <toolguid.h>
#include <triastlb.h>
#include <dirisole.h>
#include <xtsnguid.h>

extern CComModule _Module;

#pragma warning (disable: 4304)
#pragma warning (disable: 4114)
#pragma warning (disable: 4786)
#include <ospace/std/map>		// STL related stuff
#include "AuxUIOwner.h"

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const IID IID_ITRiASNotificationSink = {0x0796385A,0x3123,0x101C,{0xBB,0x62,0x00,0xAA,0x00,0x18,0x49,0x7C}};

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(ConnectionPoint);
DefineSmartInterface(TRiASNotificationSink);
DefineSmartInterface(TriasXtensionSite);

///////////////////////////////////////////////////////////////////////////////
// Statische Teballe, aus der zur Laufzeit die map aufgebaut wird
// über die die Aktionen für ein Control ausgewählt werden
const UIOWNERDATA CAuxUIOwner::m_rgUIOwnerData[] = {
//
// GBM Dialogs
// IDM_INCLUDEPROJECT
// IDM_OPENPROJEKT
// IDM_DATEN
// IDM_BEARBEITEN
// IDM_EDIT
// IDM_EDITIDE
// IDM_SUCHEN
// IDM_PRINT
// IDM_PRINT_PREVIEW
// IDM_TIEFENBEGR
// IDM_FLAECHEN
// IDM_BEITRAG
// IDM_EXTRAS
// IDM_VISU
// IDM_STATISTIK
// IDM_ABOUT
	{ IDM_INCLUDEPROJECT,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMIncludeProject, 
		}, 
	},
	{ IDM_OPENPROJEKT,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMOpenProject, 
		}, 
	},
	{ IDM_DATEN,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest,
			CAuxUIOwner::CheckOnRequest, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMDaten, 
		}, 
	},
	{ IDM_BEARBEITEN,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMBearbeiten, 
		}, 
	},
	{ IDM_EDIT,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMEdit, 
		}, 
	},
	{ IDM_EDITIDE,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMEditIDE, 
		}, 
	},
	{ IDM_SUCHEN,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMSuchen, 
		}, 
	},
	{ IDM_PRINT,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMPrint, 
		}, 
	},
	{ IDM_PRINT_PREVIEW,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMPrintPreview, 
		}, 
	},
	{ IDM_TIEFENBEGR,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMTiefenbegr, 
		}, 
	},
	{ IDM_FLAECHEN,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMFlaechen, 
		}, 
	},
	{ IDM_BEITRAG,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMBeitrag, 
		}, 
	},
	{ IDM_EXTRAS,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMExtras, 
		}, 
	},
	{ IDM_VISU,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMVisu, 
		}, 
	},
	{ IDM_STATISTIK,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMStatistik, 
		}, 
	},
	{ IDM_ABOUT,
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnRequest, NULL, CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnGBMAbout, 
		}, 
	},
//
// Endekennung ////////////////////////////////////////////////////////////////
	{ 0L, { NULL, NULL, NULL, NULL, NULL, NULL, }, },
};

///////////////////////////////////////////////////////////////////////////////
// Dynamische Daten initialisieren

CAuxUIOwner::CAuxUIOwner (void)
{
	m_fOpenProject = false;
	m_fIsRO = false;
	m_dwCookie = 0L;
}

HRESULT CAuxUIOwner::FinalConstruct (void)
{
	m_pXtsn = NULL;

// alles, was definiert ist, in der map speichern
	for (const UIOWNERDATA *pcData = m_rgUIOwnerData; 
		 pcData -> uiCtrlID != 0L; pcData++)
	{
	pair<UIOwnerData::iterator, bool> p = m_Data.insert (pcData -> uiCtrlID, &pcData -> Procs);

		TX_ASSERT(p.second);		// muß erfolgreich sein
	}

return NOERROR;
}

HRESULT CAuxUIOwner::SetExtension (CGbmTRiASExtension *pExt)
{
	TX_ASSERT(NULL != pExt);
	m_pXtsn = pExt;			// no AddRef

	try {
	WTriasXtensionSite Site;
	HRESULT	hr = pExt -> GetXtensionSite (Site.ppi());

		if (FAILED(hr)) throw hr;

		m_Cont = Site;		// throws HRESULT

	WConnectionPoint ConnPnt;
	
		hr = m_Cont -> FindConnectionPoint (IID_ITRiASNotificationSink, ConnPnt.ppi());
		if (FAILED(hr)) throw hr;

		{
		WTRiASNotificationSink Sink (this);		// throws HRESULT

			hr = ConnPnt -> Advise (Sink, &m_dwCookie);
			if (FAILED(hr)) throw hr;
		}
			
	} catch (HRESULT hr) {
		return hr;
	}

return NOERROR;
}

HRESULT CAuxUIOwner::DisConnectFromServer (void)
{
HRESULT hr = NOERROR;

	if (NULL != (IUnknown *)m_Cont && 0 != m_dwCookie) {
	WConnectionPoint ConnPnt;
		
		hr = m_Cont -> FindConnectionPoint (IID_ITRiASNotificationSink, ConnPnt.ppi());
		if (SUCCEEDED(hr)) {
			hr = ConnPnt -> Unadvise (m_dwCookie);
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

	TX_ASSERT(it != m_Data.end());

// Testen, ob überhaupt ein Projekt geöffnet ist
const UIOWNERPROCS *pProcs = (*it).second;

	TX_ASSERT(NULL != pProcs);

	if (!m_fOpenProject) {
		TX_ASSERT(NULL != pProcs -> pFcnClosed);
		return pICmdUI -> put_IsEnabled ((this ->* pProcs -> pFcnClosed)(pIBar, (UINT)uiID));
	}

// Projekt ist geöffnet
	TX_ASSERT(NULL != pProcs -> pFcnOpened);

HRESULT hr = pICmdUI -> put_IsEnabled ((this ->* pProcs -> pFcnOpened)(pIBar, (UINT)uiID));
	
	if (SUCCEEDED(hr) && NULL != pProcs -> pFcnCheck)
		return pICmdUI -> put_CheckState ((this ->* pProcs -> pFcnCheck)(pIBar, (UINT)uiID));

return hr;
}

HRESULT CAuxUIOwner::OnSelect (ITRiASBar *pIBar, UINT uiID, LPSTR pBuffer, ULONG ulLen, ULONG *pulWritten)
{
	if (NULL == pIBar || NULL == pBuffer || 0 == ulLen) 
		return E_POINTER;

// Select behandeln, dazu ResID oder String besorgen
UIOwnerData::iterator it = m_Data.find (uiID);

	TX_ASSERT(it != m_Data.end());

const UIOWNERPROCS *pProcs = (*it).second;

	TX_ASSERT(NULL != pProcs);
	TX_ASSERT(NULL != pProcs -> pFcnResID || NULL != pProcs -> pFcnResStr);

	try {
	ULONG ulToWrite = 0L;

		if (NULL != pProcs -> pFcnResID) {
		UINT uiResID = (this ->* pProcs -> pFcnResID)(pIBar, uiID);

			TX_ASSERT(0 != uiResID);
		
//		ResString str (ResID (uiResID, &g_pTE -> RF()), 255);
		CString str;
			str.LoadString( uiResID );
			
//			ulToWrite = min (ulLen-1, ULONG(str.Len()));
			ulToWrite = min (ulLen-1, ULONG(str.GetLength()));
			strncpy (pBuffer, str, ulToWrite);
			pBuffer[ulToWrite] = '\0';
		} else {
			(this ->* pProcs -> pFcnResStr)(pIBar, uiID, pBuffer, ulLen);
			ulToWrite = strlen (pBuffer);
		}
		if (pulWritten)
			*pulWritten = ulToWrite;

	} catch (...) {
		return E_OUTOFMEMORY;
	} 

return NOERROR;
}

HRESULT CAuxUIOwner::OnCommand (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (NULL == pIBar) return E_POINTER;

UIOwnerData::iterator it = m_Data.find (uiID);

	TX_ASSERT(it != m_Data.end());

const UIOWNERPROCS *pProcs = (*it).second;

	TX_ASSERT(NULL != pProcs);
	TX_ASSERT(NULL != pProcs -> pFcnCmd);

return (this ->* pProcs -> pFcnCmd)(pIBar, uiID, nCode);		// Befehl ausführen
}

///////////////////////////////////////////////////////////////////////////////
// *** ITRiASNotificationSink specific functions ***
STDMETHODIMP CAuxUIOwner::ServerEvent (SERVEREVT se)
{
	switch (se) {
	case SERVEREVT_ServerToClose:	// das letzte vom Tage
		DisConnectFromServer();		// ConnectionPoint abmelden
		break;
	}

return NOERROR;
}

STDMETHODIMP CAuxUIOwner::ProjectEvent (long hPr, PROJECTEVT pe, VARIANT)
{
	switch (pe) {
	case PROJECTEVT_ProjectOpened:
		m_fOpenProject = true;
		m_fIsRO = DEX_GetROMode() ? true : false;
		break;

	case PROJECTEVT_ProjectToClose:
		m_fOpenProject = false;
		m_fIsRO = true;
		break;
	}

return NOERROR;
}

STDMETHODIMP CAuxUIOwner::GeoViewEvent (long hPr, GEOVIEWEVT ve, VARIANT)
{
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::GeoClassEvent (long hPr, GEOCLASSEVT ce, long ulIdent)
{
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::GeoObjectEvent (long hPr, GEOOBJECTEVT oe, long lONr)
{
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::GeoFeatureEvent (long hPr, GEOFEATUREEVT fe, long ulMCode)
{
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::GeoRelationEvent (long hPr, GEORELATIONEVT re, long ulRCode)
{
	return NOERROR;
}

STDMETHODIMP CAuxUIOwner::ObjectWindowEvent (OBJWNDEVT oe, long hORWnd)
{
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
	return DEX_GetROMode() ? false : true;
}

// true wenn Bedingungen erfüllt sind
bool CAuxUIOwner::EnableOnRequest (ITRiASBar *pIBar, UINT uiID)
{
	if ( !DEX_GetROMode())
		return m_pXtsn -> CommandToEnable( uiID );
	else
		return false;
}

int CAuxUIOwner::CheckOnRequest( ITRiASBar* pIBar, UINT uiID )
{
	if ( !DEX_GetROMode())
		return m_pXtsn -> CommandToCheck( uiID );
	else
		return 0;
}

///////////////////////////////////////////////////////////////////////////////
// SELECTSTRINGIDPROC
UINT CAuxUIOwner::CtrlIdIsStringID (ITRiASBar *pIBar, UINT uiID)
{
	return uiID;		// ControlID ist gleichzeitig StringID
}

///////////////////////////////////////////////////////////////////////////////
// SELECTSTRINGSTRINGPROC

///////////////////////////////////////////////////////////////////////////////
// COMMANDPROC 

/*
HRESULT CAuxUIOwner::OnMetaCmdModIdent (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	return m_pXtsn -> DefineIdentifier() ? NOERROR : E_FAIL;
}
*/

HRESULT CAuxUIOwner::OnGBMIncludeProject(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMOpenProject(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMDaten(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMBearbeiten(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMEdit(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMEditIDE(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMSuchen(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMPrint(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMPrintPreview(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMTiefenbegr(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMFlaechen(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMBeitrag(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMExtras(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMVisu(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMStatistik(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}

HRESULT CAuxUIOwner::OnGBMAbout(ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if ( nCode != 0 )	return S_FALSE;		// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	m_pXtsn -> ExecCommand( uiID );
	return NOERROR;
}
