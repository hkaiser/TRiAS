///////////////////////////////////////////////////////////////////////////
// @doc 
// @module TRiASDataServerRegEntry.h | Declaration of the <c CTRiASDataServerRegEntry> class

#if !defined(_TRIASDATASERVERREGENTRY_H__F4B3F94A_810E_11D1_9776_00A024D6F582__INCLUDED_)
#define _TRIASDATASERVERREGENTRY_H__F4B3F94A_810E_11D1_9776_00A024D6F582__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTRiASDataServerRegEntry
class ATL_NO_VTABLE CTRiASDataServerRegEntry : 
	public CComObjectRootEx<CComObjectThreadModel>,
	public ISupportErrorInfo,
	public CReportErrorComCoClass<CTRiASDataServerRegEntry, &CLSID_TRiASDataServerRegEntry, &IID_ITRiASDataServerRegEntry>, 
	public IDispatchImpl<ITRiASDataServerRegEntry, &IID_ITRiASDataServerRegEntry, &LIBID_TRiASDB,
		TYPELIB_TRIASDB_VERSION_MAJOR, TYPELIB_TRIASDB_VERSION_MINOR>
{
public:
	_ATLX_DEBUG_OBJECTCOUNT_IMPL(CTRiASDataServerRegEntry)
	DECLARE_ONE_SIZE_PRIVATE_HEAP()
//	DECLARE_REGISTRY_RESOURCEID(IDR_TRIASDATASERVERREGENTRY)
	DECLARE_NO_REGISTRY()

	CTRiASDataServerRegEntry()
		: m_fIsInitialized(false)
	{
	}

	BEGIN_COM_MAP(CTRiASDataServerRegEntry)
		COM_INTERFACE_ENTRY(ITRiASDataServerRegEntry)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ISupportErrorInfo)
	END_COM_MAP()

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid);

// ITRiASDataServerRegEntry
public:
	STDMETHOD(get_RestrictInstances)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_ToolboxBitmap32)(/*[out, retval]*/ LONG *pVal);
	STDMETHOD(get_Version)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_SourceStringDescription)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_SourceStringUsed)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_NameIsDirectory)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_NameIsFile)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_NameIsSubStorage)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_IsReadWrite)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_LastDirUsed)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_LastDirUsed)(/*[in]*/ BSTR newVal);
	STDMETHOD(get_TempName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_FileDescription)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_LongName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_ShortName)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_FilterString)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_DefaultExtension)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_DatabaseClass)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_DataServerClass)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_MultipleFiles)(/*[out, retval]*/ VARIANT_BOOL * pVal);
	STDMETHOD(get_OpenWizPages)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_NeedsCoordSystemNew)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_NeedsCoordSystemExisting)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_ReconnectDialog)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(get_CreateDatabase)(/*[out, retval]*/ BSTR *pVal);

// InitialisierungsFunktion
	HRESULT InitFromRegistry (LPCSTR pcProgID);

protected:
	bool m_fIsInitialized;

	bool m_fIsReadWrite;
	bool m_fNameIsFile;
	bool m_fNameIsDir;
	bool m_fNameIsSubStorage;
	bool m_fSourceStringUsed;
	bool m_fMultipleFiles;
	bool m_fNeedsCoordSysNew;
	bool m_fNeedsCoordSysExisting;

	LONG m_lToolBox;			// Anzuzeigende Bitmap
	LONG m_lInstances;			// Anzahl der einfügbaren Instanzen

	CString m_strProgID;		// ProgID der DataBaseClass im OriginalSystem (Document/GDatabase)
	CString m_strDBClass;		// ProgID der DataBaseClass des TRiASDatabase-Objektes
	CString m_strOpenWizExtClass;	// evtl. ProgID für zusätzliche OpenPages
	CString m_strFilter;		// FilterString für 'Datei öffnen'
	CString m_strDefExt;		// Standard Dateierweiterung
	CString m_strLongName;		// Langbezeichner des DatenServers
	CString m_strShortName;		// Kurzbezeichner des DatenServers
	CString m_strFileDesc;		// Bezeichner des Dateiformates
	CString m_strTempName;		// Temporäre Datenquelle möglich, das ist der DefaultName
	CString m_strLastDirUsed;	// Beim letzten mal benutztes Verzeichnis
	CString m_strSourceDesc;	// Beschreibung des SourceString
	CString m_strVersion;		// Version des DataServers
	CString m_strReconnectDialogClass;	// evtl. ProgID für ReconnectDialog
	CString m_strCreateDatabaseClass;	// evtl. ProgID für CreateDatabase
};

#endif // !defined(_TRIASDATASERVERREGENTRY_H__F4B3F94A_810E_11D1_9776_00A024D6F582__INCLUDED_)
