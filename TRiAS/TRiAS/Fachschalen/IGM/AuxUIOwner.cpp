// AuxUIOwner.cpp : Implementation of the CAuxUIOwner

#include "kompp.hxx"

#include "kompaktr.h"


// BasicScript
#include <eb.h>
#include <ibscript.hxx>
#include <bscrguid.h>

//#include <triastlb_i.c>
//#include <triastlb.h>

#include <itoolbar.h>

#include <toolguid.h>

#include <dirisole.h>
#include <xtsnguid.h>
#include <oleguid.h>
#include "kompguid.h"

#include <shlobj.h>
#include <ixtnext.hxx>
#include <xtsnaux.hxx>
#include <initguid.h>
#include <istatus.h>
#include <igeometr.hxx>


#include "cobjtree.hxx"
#include "ctopobj.hxx"
#include "triasdef.h"
#include "kompdef.h"
#include "gewbaum.hxx"
#include "komphead.hxx"
#include "kompdll.hxx"
#include "kompgew.hxx"
#include "kompias.hxx"

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
// MetaData Dialogs
	{ ID_KOMPDATA_EREIGNIS,
//		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnWriteAble, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableAlways, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnCmdEreignis, 
		}, 
	},
	{ ID_KOMPDATA_WASSER,
//		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableOnWriteAble, 
		{	CAuxUIOwner::DisableAlways, CAuxUIOwner::EnableAlways, 
			NULL, 
			CAuxUIOwner::CtrlIdIsStringID, NULL, 
			CAuxUIOwner::OnCmdWasser, 
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

// Korrektur 26.11.98
	m_fOpenEreignis = false;
	m_fOpenWasser = false;

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

HRESULT CAuxUIOwner::SetExtension (CKompiasExtension *pExt)
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

// Meine Button - Korrektur 27.11.98


	int RefID = 0;

	pIBar->CommandToIndex((UINT)uiID,&RefID);

	if ( m_fOpenEreignis && 0 == RefID ) {
		TX_ASSERT(NULL != pProcs -> pFcnOpened);
		return pICmdUI -> put_IsEnabled ((this ->* pProcs -> pFcnOpened)(pIBar, (UINT)uiID));
	} else
		hr = pICmdUI -> put_IsEnabled ((this ->* pProcs -> pFcnClosed)(pIBar, (UINT)uiID));


	if ( m_fOpenWasser && 1 == RefID ) {
		TX_ASSERT(NULL != pProcs -> pFcnOpened);
		return pICmdUI -> put_IsEnabled ((this ->* pProcs -> pFcnOpened)(pIBar, (UINT)uiID));
	} else
		hr = pICmdUI -> put_IsEnabled ((this ->* pProcs -> pFcnClosed)(pIBar, (UINT)uiID));

	
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
		
		ResString str (ResID (uiResID, &g_pTE -> RF()), 255);
			
			ulToWrite = min (ulLen-1, ULONG(str.Len()));
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
		m_fOpenWasser = false;
		m_fOpenEreignis = false;
		m_fOpenProject = true;
		m_fIsRO = DEX_GetROMode() ? true : false;
		break;

	case PROJECTEVT_ProjectToClose:
		m_fOpenWasser = false;
		m_fOpenEreignis = false;
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

	switch (oe) {


	case GEOOBJECTEVT_ObjectActivated:	
		if ( m_pXtsn ) {
			if (!m_fOpenProject)
				m_fOpenProject = true;
			if ( !m_pXtsn->DefineEreignisObjekt(lONr)) {
				if( m_pXtsn->DefineGewaesserObjekt(lONr)) {
					m_fOpenWasser = true;
					m_fOpenEreignis = false;
				} else {
					m_fOpenWasser = false;
					m_fOpenEreignis = false;
				}

			} else {
				m_fOpenWasser = false;
				m_fOpenEreignis = true;
			}
		
		}
		break;

// KK991123
	case GEOOBJECTEVT_ObjectToDelete:

		if ( m_pXtsn ) {
				m_pXtsn->ExtModifyUnRegisterNotification();
				m_fOpenWasser = false;
				m_fOpenEreignis = false;
		}
		break;
	}
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

	switch (oe) {


	case OBJWNDEVT_WindowCreated:
		{
		if ( m_pXtsn) {
			if (!m_fOpenProject)
				m_fOpenProject = true;
			long lONr = DEX_GetActiveObject((LPARAM)(void*)hORWnd);
			if ( !m_pXtsn->DefineEreignisObjekt(lONr)) {
				if( m_pXtsn->DefineGewaesserObjekt(lONr)) {
					m_fOpenWasser = true;
					m_fOpenEreignis = false;
				} else {
					m_fOpenWasser = false;
					m_fOpenEreignis = false;
				}

			} else {
				m_fOpenWasser = false;
				m_fOpenEreignis = true;
			}
		
		}
		}
		break;

	case OBJWNDEVT_WindowDestroyed:	
		{
			m_fOpenWasser = false;
			m_fOpenEreignis = false;
			
		}
		break;
	}

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

HRESULT CAuxUIOwner::OnCmdEreignis (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != 0 /*CN_COMMAND*/)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	return m_pXtsn -> DefineEreignis() ? NOERROR : E_FAIL;
}

HRESULT CAuxUIOwner::OnCmdWasser (ITRiASBar *pIBar, UINT uiID, int nCode)
{
	if (nCode != 0 /*CN_COMMAND*/)
		return S_FALSE;			// nur WM_COMMAND's bearbeiten

	TX_ASSERT(NULL != m_pXtsn);
	return m_pXtsn -> DefineWasser() ? NOERROR : E_FAIL;
}


