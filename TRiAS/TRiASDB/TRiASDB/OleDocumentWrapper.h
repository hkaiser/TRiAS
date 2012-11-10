// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 10.02.2000 13:04:52 
//
// @doc
// @module OleDocumentWrapper.h | Declaration of the <c COleDocumentWrapper> class
// @comm Die hier definierte Klasse dient der Zusammenfassung der historisch 
// entstandenen Objekte, welche ein <tr> -Workspace repräsentieren: 
// <c CTRiASProject> (in TRiASDB.dll) und <c CGeoDocument> (in OleAuto.ext). 
// Die Notwendigkeit einer solchen Zusammenfassung ergab sich im Zusammenhang
// mit dem Versuch OLE-Funktionalität zu implementieren. 
// Wird das Object <o OleDocumentWrapper> durch <tr> instantiiert (der in der
// Funktion SetClientSite übergebene Interfacepointer kennt das Interface ITRiASDBEngine)
// dann wird ein <c CTRiASProject> aggregiert. Ansonsten wird davon ausgegangen, daß
// ein Dokument im Zusammenhang mit einem OLE-Vorgang instantiiert werden soll. 
// In diesem Fall wird ein <c CGeoDocument> aggregiert.

#if !defined(_OLEDOCUMENTWRAPPER_H__83F70962_8C90_486F_9A84_1BE463622DDA__INCLUDED_)
#define _OLEDOCUMENTWRAPPER_H__83F70962_8C90_486F_9A84_1BE463622DDA__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Header include diagnostics
#if defined(_TRIAS_DBG_HEADER_DIAGNOSTICS)
#pragma message(__TIME__": include " __FILE__ )
#endif

#include "resource.h"       // main symbols
#include "dirisole.h"

DefineSmartInterface(Storage);
DefineSmartInterface(PersistStorage);
DefineSmartInterface(PersistFile);
DefineSmartInterface(Persist);
DefineSmartInterface(OleObject);

DefineSmartInterface(TRiASDBEngine);

///////////////////////////////////////////////////////////////////////////////
// {D4752D2F-6067-442C-87E8-8C9417B99955}
extern "C" const IID __declspec(selectany) CLSID_GeoDocumentIntern = 
	{0xd4752d2f,0x6067,0x442c,{0x87,0xe8,0x8c,0x94,0x17,0xb9,0x99,0x55}};

/////////////////////////////////////////////////////////////////////////////
// COleDocumentWrapper
class ATL_NO_VTABLE COleDocumentWrapper : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public CComCoClass<COleDocumentWrapper, &CLSID_OleDocumentWrapper>,
	public IOleObject,
	public IPersistStorage,
	public IPersistFile
{
public:
	COleDocumentWrapper() :
		m_bstrFileName(g_cbNil),
		m_dwMode(0),
		m_fInitThroughStorage(false),
		m_fLoadThroughStorage(false),
		m_fInitThroughFile(false)
	{
	}

//	DECLARE_REGISTRY_RESOURCEID(IDR_OLEDOCUMENTWRAPPER)
	static HRESULT WINAPI UpdateRegistry (BOOL bRegister);

	DECLARE_PROTECT_FINAL_CONSTRUCT()
	DECLARE_GET_CONTROLLING_UNKNOWN()

	BEGIN_COM_MAP(COleDocumentWrapper)
		COM_INTERFACE_ENTRY(IOleObject)
		COM_INTERFACE_ENTRY(IPersistStorage)
		COM_INTERFACE_ENTRY(IPersistFile)
		COM_INTERFACE_ENTRY2(IPersist, IPersistStorage)
		COM_INTERFACE_ENTRY_AGGREGATE_BLIND(m_BaseUnk.p)
	END_COM_MAP()

	void FinalRelease()
	{
		m_BaseUnk.Assign(NULL);
	}

public:
// IPersist
	STDMETHODIMP GetClassID (CLSID *pClassID)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WPersist(m_BaseUnk) -> GetClassID(pClassID));
		} COM_CATCH;
		return S_OK;
	}

// IPersistStorage
	STDMETHODIMP IsDirty (void)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WPersistStorage(m_BaseUnk) -> IsDirty());
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP InitNew (IStorage *pStorage)
	{
		COM_TRY {
			if (m_BaseUnk.IsValid()) {
			// SetClientSite wurde bereits gerufen
				THROW_FAILED_HRESULT(WPersistStorage(m_BaseUnk) -> InitNew(pStorage));
			} else {
				m_StgToInit = pStorage;
				m_fInitThroughStorage = true;
			}
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP Load (IStorage *pStorage)
	{
		COM_TRY {
			if (m_BaseUnk.IsValid()) {
			// SetClientSite wurde bereits gerufen
				THROW_FAILED_HRESULT(WPersistStorage(m_BaseUnk) -> Load(pStorage));
			} else {
				m_StgToInit = pStorage;
				m_fLoadThroughStorage = true;
			}
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP Save (IStorage *pStorage, BOOL fSameAsLoad)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WPersistStorage(m_BaseUnk) -> Save (pStorage, fSameAsLoad));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP SaveCompleted (IStorage *pStorage)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WPersistStorage(m_BaseUnk) -> IsDirty());
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP HandsOffStorage (void)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WPersistStorage(m_BaseUnk) -> IsDirty());
		} COM_CATCH;
		return S_OK;
	}

// IPersistFile
	STDMETHODIMP Load (LPCOLESTR pszFileName, DWORD dwMode)
	{
		COM_TRY {
			if (m_BaseUnk.IsValid()) {
			// SetClientSite wurde bereits gerufen
				THROW_FAILED_HRESULT(WPersistFile(m_BaseUnk) -> Load(pszFileName, dwMode));
			} else {
				m_bstrFileName = pszFileName;
				m_dwMode = dwMode;
				m_fInitThroughFile = true;
			}
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP Save (LPCOLESTR pszFileName, BOOL fRemember)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WPersistFile(m_BaseUnk) -> Save (pszFileName, fRemember));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP SaveCompleted (LPCOLESTR pszFileName)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WPersistFile(m_BaseUnk) -> SaveCompleted (pszFileName));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP GetCurFile (LPOLESTR *ppszFileName)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WPersistFile(m_BaseUnk) -> GetCurFile (ppszFileName));
		} COM_CATCH;
		return S_OK;
	}

// IOleObject
	STDMETHODIMP SetClientSite (IOleClientSite *pClientSite)
	{
		COM_TRY {
		// entweder CTRiASProject oder CGeoDocument aggregieren (je nach Kontext)
			if (NULL != pClientSite && !m_BaseUnk.IsValid()) {
			WTRiASDBEngine DBEng;

				if (SUCCEEDED(pClientSite -> QueryInterface (DBEng.ppi()))) {
				// Instantiierung im Rahmen des normalen TRiAS-Ladeprozesses
					THROW_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_TRiASProject, CLSCTX_INPROC_SERVER, GetControllingUnknown()))
				} else {
				// Instantiierung im Rahmen eines OLE-Ladevorganges
					THROW_FAILED_HRESULT(m_BaseUnk.CreateInstance (CLSID_GeoDocumentIntern, CLSCTX_INPROC_SERVER, GetControllingUnknown()))
				}
			}

		// evtl. Initialisierung nachholen
			if (m_fInitThroughStorage) {
			// Objekt sollte neu initialisiert werden
				_ASSERTE(m_StgToInit.IsValid());

				THROW_FAILED_HRESULT(WPersistStorage (m_BaseUnk) -> InitNew (m_StgToInit));

				m_StgToInit.Assign(NULL);
				m_fInitThroughStorage = false;
			} 
			else if (m_fLoadThroughStorage) {
			// Objekt sollte geladen werden
				_ASSERTE(m_StgToInit.IsValid());

				THROW_FAILED_HRESULT(WPersistStorage(m_BaseUnk) -> Load (m_StgToInit));
			
				m_StgToInit.Assign(NULL);
				m_fLoadThroughStorage = false;
			} 
			else if (m_fInitThroughFile) {
			// Objekt sollte aus Datei geladen werden
				_ASSERTE(!m_StgToInit.IsValid());

				THROW_FAILED_HRESULT(WPersistFile(m_BaseUnk) -> Load (m_bstrFileName, m_dwMode));

				m_bstrFileName.Empty();
				m_fInitThroughFile = false;
			}

		// SetClientSite nachholen
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> SetClientSite (pClientSite));

		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP GetClientSite (IOleClientSite **ppClientSite)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> GetClientSite (ppClientSite));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP SetHostNames (LPCOLESTR szContainerApp, LPCOLESTR szContainerObj)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> SetHostNames (szContainerApp, szContainerObj));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP Close (DWORD dwSaveOption)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> Close (dwSaveOption));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP SetMoniker (DWORD dwWhichMoniker, IMoniker *pmk)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> SetMoniker (dwWhichMoniker, pmk));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP GetMoniker (DWORD dwAssign, DWORD dwWhich, IMoniker **ppIMk)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> GetMoniker (dwAssign, dwWhich, ppIMk));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP InitFromData (IDataObject *pDataObject, BOOL fCreation, DWORD dwReserved)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> InitFromData (pDataObject, fCreation, dwReserved));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP GetClipboardData (DWORD dwReserved, IDataObject **ppDataObject)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> GetClipboardData (dwReserved, ppDataObject));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP DoVerb (LONG iVerb, LPMSG lpmsg, IOleClientSite *pActiveSite, LONG lindex, HWND hwndParent,  LPCRECT lprcPosRect)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> DoVerb (iVerb, lpmsg, pActiveSite, lindex, hwndParent, lprcPosRect),);
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP EnumVerbs (IEnumOLEVERB **ppEnumOleVerb)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> EnumVerbs (ppEnumOleVerb));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP Update ()
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> Update());
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP IsUpToDate ()
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> IsUpToDate());
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP GetUserClassID (CLSID *pClsid)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> GetUserClassID (pClsid));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP GetUserType (DWORD dwFormOfType, LPOLESTR *pszUserType)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> GetUserType (dwFormOfType, pszUserType));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP SetExtent (DWORD dwDrawAspect, SIZEL *psizel)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> SetExtent (dwDrawAspect, psizel));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP GetExtent (DWORD dwDrawAspect, SIZEL *psizel)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> GetExtent (dwDrawAspect, psizel));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP Advise (IAdviseSink *pAdvSink, DWORD *pdwConnection)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> Advise (pAdvSink, pdwConnection));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP Unadvise (DWORD dwConnection)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> Unadvise (dwConnection));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP EnumAdvise (IEnumSTATDATA **ppenumAdvise)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> EnumAdvise (ppenumAdvise));
		} COM_CATCH;
		return S_OK;
	}

	STDMETHODIMP GetMiscStatus (DWORD dwAspect, DWORD *pdwStatus)
	{
		COM_TRY {
			if (m_BaseUnk.IsValid()) {
			// wird komischerweise ggf. _vor_ InitNew/Load gerufen
				THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> GetMiscStatus (dwAspect, pdwStatus));
			} else {
				if (NULL == pdwStatus)
					return E_POINTER;
#pragma MESSAGE("TODO: Alle noch fehlenden OLEMISC-Bits hier mit eintragen.")
				*pdwStatus = OLEMISC_SETCLIENTSITEFIRST;
			}
		} COM_CATCH;	
		return S_OK;
	}

	STDMETHODIMP SetColorScheme (LOGPALETTE *pLogpal)
	{
		COM_TRY {
			THROW_FAILED_HRESULT(WOleObject(m_BaseUnk) -> SetColorScheme (pLogpal));
		} COM_CATCH;
		return S_OK;
	}

private:
	WUnknown m_BaseUnk;		// aggregiertes Objekt

// Initialisierungsinformationen
	CComBSTR m_bstrFileName;		// specifics for IPersistFile
	DWORD m_dwMode;
	WStorage m_StgToInit;			// specifics for IPersistStorage
	bool m_fInitThroughStorage;
	bool m_fLoadThroughStorage;
	bool m_fInitThroughFile;
};

#endif // !defined(_OLEDOCUMENTWRAPPER_H__83F70962_8C90_486F_9A84_1BE463622DDA__INCLUDED_)
