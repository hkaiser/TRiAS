// @doc
// @module TRiASDataServerRegEntry.cpp | Implementation of the <c > class

#include "stdafx.h"

#include <Atl/Ciid.h>

#include "Strings.h"

#include "TRiASDataServerRegEntry.h"

/////////////////////////////////////////////////////////////////////////////
// local heap for this clas
IMPLEMENT_ONE_SIZE_PRIVATE_LOCAL_HEAP_LIST(CTRiASDataServerRegEntry);

#if defined(_DUMP_PENDING_OBJECTS)
HRESULT CTRiASDataServerRegEntry::Dump()
{
	return S_OK;
}
#endif // defined(_DUMP_PENDING_OBJECTS)

#if defined(_DEBUG)
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

///////////////////////////////////////////////////////////////////////////////
// @topic Registryeinträge für einen TRiASDB-DataServer |
// Jeder auf einem System installierte TRiASDB-DataServer muß in der Registry
// verschiedene statische Informationen ablegen, die es ermöglichen, diesen 
// TRiASDB-DataServer in <tr> zu integrieren.
// <nnl>Der Zugriff auf diese Informationen sollte jedoch niemals direkt, sondern immer
// über das Objekt <o TRiASDataServerRegEntry> bzw. sein Interface <i ITRiASDataServerRegEntry> 
// erfolgen.
// <nnl>Der Übersicht halber wird im folgenden das Format beschrieben, mit welchem zur Zeit die
// statischen Informationen eines TRiASDB-DataServers in der Registry gespeichert werden.
// <nnl>Sämtliche Informationen sind unter einem zusätzlichen Registry-Schlüssel mit
// dem Namen 'TRiASDB' gespeichert, welcher sich jeweils unter dem ProgID des zugehörigen
// COM-Objektes befinden muß, das das jeweilige Targetdokument repräsentiert.
// <nl>Dieses Targetdokument kann in Abhängigkeit vom konkreten TRiASDB-DataServer
// unterschiedliche inhaltliche Funktionen ausüben. So ist z.B. für der TRiASDB-DataServer 
// für originale <tr>-Datenbanken das Targetdokument die Datenbank selbst, für
// einen TRiASDB-DataServer, der auf einem GDO-DataServer basiert dagegen ist das
// Targetdokument die GDO-Datenbank.
// <nl>Dieser Schlüssel besitzt seinerseits zwei weitere Unterschlüssel: 'CLSID' und 'Description'.
// <nnl>Der angegebene ClassID repräsentiert das zu diesem DataServer gehörende Objekt, welches
// das Interface <i ITRiASDatabase> implementiert hat und damit den Zugriff auf die 
// eigentlichen Daten liefert. 
// <nl>Der SubKey "OpenWizPages" ist dann vorhanden, wenn zusätzliche
// Pages zum Start-Dialog hinzugefügt werden sollen. Der zugehörige Wert ist in diesem Fall
// der CLSID eines Objektes, welches die Pages zur Verfügung stellt (s. <i ITriasPropSheetExt> und
// <i ITRiASOpenWizardPropExt>).
// <nnl>Die zusätzlichen Informationen unter dem Schlüssel 'Description' beschreiben verschiedene 
// Aspekte des betreffenden TRiASDB-DataServers. Die möglichen Einträge werden unter dem
// Kapitel <l Zusätzliche Informationen zu einem TRiASDB-DataServer> beschrieben.
// @ex Der Registryeintrag für der TRiASDB-DataServer einer <tr>-Datenbank sieht beispielsweise
// folgendermaßen aus: |
// HKEY_CLASSES_ROOT 
//	TRiAS.Document.2
//		TRiASDB
//			CLSID
//				(Default) = "{6ACC24A4-3969-11D1-96B8-00A024D6F582}"
//				"OpenWizPages" = "[clsid des zuständigen Objektes]"	
//				"ReconnectDialog" = "[clsid des zuständigen Objektes]"	
//				"CreateDatabase" = "[clsid des zuständigen Objektes]"	
//			Description
//				(Default) = <value not set>
//				"DefaultExtension" = ".ris"
//				"LongName" = "Einheitliche Datenbank-Schnittstelle für TRiAS Projekte"
//				"ShortName" = "TRiAS 2.0"
//				"NameDescription" = "TRiAS 2.0 GIS-Datenbank"
//				"NameIsDirectory" = "0"
//				"NameIsFile" = "1"
//				"NameIsSubStoarage = "0"
//				"MultipleFiles" = "0"
//				"ReadWrite" = "1"
//				"FilterString" = "TRiAS 2.0 GIS-Datenbank (*.ris)|*.ris|"
//				"Version" = "2.0"
//				"ToolboxBitmap32" = dword:00000004
//				"TempName" = "Ohne Namen.ris"
//				"LastDirUsed" = "E:\\TRIAS\\PROJEKTE\\"
//				"NeedsCoordSysNew = "1"
//				"NeedsCoordSysExisting = "0"
// @xref <l Zusätzliche Informationen zu einem TRiASDB-DataServer>, <i ITRiASDataServerRegEntry>,
// <o TRiASDataServerRegEntry>, <i ITRiASDatabase>
//
// @topic Zusätzliche Informationen zu einem TRiASDB-DataServer |
// Im folgenden werden die möglichen Einträge beschrieben, die unter dem 
// Registryeintrag 'TRiASDB\Description' eines TRiASDB-DataServers gespeichert
// sein können.
// @regval ReadWrite | REGSZ | Wenn ungleich "0", dann kann der TRiASDB-DatenServer
// kann Daten in die Datenbank schreiben
// @regval ShortName | REGSZ | Kurzbezeichnung dieses TRiASDB-DataServers
// @regval LongName | REGSZ | Langbezeichnung dieses TRiASDB-DataServers
// @regval NameIsFile | DWORD | Wenn ungleich '0', dann beschreibt der 
// Datenbankname eine Datei
// @regval NameIsDirectory | DWORD | Wenn ungleich '0', dann beschreibt 
// der Datenbankname ein Verzeichnis
// @regval NameIsSubStorage | DWORD | Wenn ungleich '0', dann beschreibt 
// der Datenbankname ein Substorage in der aktuellen Projektdatei (*.riw)
// @regval MultipleFiles | DWORD | Wenn ungleich '0', dann können mehrere Dateien
// als eine Datenbank betrachtet werden (z.B. Importmodule)
// @regval SourceStringUsed | DWORD | Wenn ungleich '0', dann wird bei Aufruf 
// der OpenDatabase-Methode der Parameter 'SourceString' ausgewertet
// @regval SourceDescription | REGSZ | Beschreibt den Parameter 'SourceString' 
// der OpenDatabase-Methode
// @regval NameDescription | REGSZ | Dateibeschreibung für diesen TRiASDB-DataServer
// @regval FilterString | REGSZ | FilterString für Datei Öffnen/Datei Speichern Dialoge
// @regval DefaultExtension | REGSZ | Standard-Dateierweiterung für Datenbank bei 'NameIsFile'
// @regval TempName | REGSZ | Wenn temporäre Datenquellen unterstützt werden, dann liefert 
// diese Eigenschaft den zu verwendenden temporären Basisnamen
// @regval LastDirUsed | REGSZ | Zuletzt benutztes Dateiverzeichnis
// @regval Version | REGSZ | Version dieses TRiASDB-DataServers
// @regval ToolBoxBitmap32 | DWORD | Nummer des im Nutzerinterface für diesen 
// TRiASDB-DataServer zu verwendenden Piktogramms
// @regval ExtendedProperties | DWORD | Wenn ungleich '0', dann kann beim Erzeugen einer 
// neuen Datenbank ein Dialog zur Eingabe zusätzlicher Optionen angezeigt werden.
// @regval RestrictInstances | DWORD | Wenn ungleich '0', dann kann gleichzeitig nur die 
// angegebene Anzahl von Datenquellen in einem Projekt geöffnet werden.
// @regval NeedsCoordSysNew | DWORD | Wenn ungleich '0', dann wird beim Anlegen einer
// neuen Datenquelle ein Fenster zur Auswahl des zu verwendenden Koordinatensystemes 
// angezeigt.
// @regval NeedsCoordSysExisting | DWORD | Wenn ungleich '0', dann wird beim Einfügen 
// einer existierenden Datenquelle ein Fenster zur Auswahl des zu verwendenden 
// Koordinatensystemes angezeigt.
//
// @xref <l Registryeinträge für einen TRiASDB-DataServer>, <i ITRiASDataServerRegEntry>,
// <o TRiASDataServerRegEntry>
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// CTRiASDataServerRegEntry

STDMETHODIMP CTRiASDataServerRegEntry::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_ITRiASDataServerRegEntry,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////////
// sonstige Funktionen

HRESULT CTRiASDataServerRegEntry::InitFromRegistry (LPCSTR pcProgID)
{
	COM_TRY {
	// ProgID der DataBaseClass im OriginalSystem (Document/GDatabase)
		m_strProgID = pcProgID;

	// ProgID der DataBaseClass des TRiASDatabase-Objektes
	CRegKey key;

		if (ERROR_SUCCESS != key.Open(HKEY_CLASSES_ROOT, pcProgID, KEY_READ) ||
			ERROR_SUCCESS != key.Open (key, g_cbTRiASDB, KEY_READ))
		{
			_com_issue_error(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));		// sollte existieren
		}

	// ClsId der TRiASDatabase-class aus Registry lesen
	TCHAR cbBuffer[_MAX_PATH];
	DWORD dwCnt = _countof(cbBuffer);

		{
		CRegKey keyClsId;			// HKCR\\DataServerProgID\\TRiASDB\\CLSID

			if (ERROR_SUCCESS != keyClsId.Open(key, g_cbCLSID, KEY_READ) ||
				ERROR_SUCCESS != keyClsId.QueryValue(cbBuffer, NULL, &dwCnt))
			{
				_com_issue_error(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));		// sollte existieren
			}
			m_strDBClass = CIID(cbBuffer).ProgID().c_str();	// ProgID geben lassen
			if (0 == m_strDBClass.GetLength())
				_com_issue_error(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));		// sollte existieren

		CRegKey keySubKey;

			dwCnt = _countof(cbBuffer);
			if (ERROR_SUCCESS == keySubKey.Open(keyClsId, g_cbOpenWizExt, KEY_READ) &&
				ERROR_SUCCESS == keySubKey.QueryValue (cbBuffer, NULL, &dwCnt))
			{
			CIID Guid (cbBuffer);

				if (Guid.IsValid())
					m_strOpenWizExtClass = Guid.ProgID().c_str();	// ProgID geben lassen
			}

			dwCnt = _countof(cbBuffer);
			if (ERROR_SUCCESS == keySubKey.Open(keyClsId, g_cbReconnectDialog, KEY_READ) &&
				ERROR_SUCCESS == keySubKey.QueryValue (cbBuffer, NULL, &dwCnt))
			{
			CIID Guid (cbBuffer);

				if (Guid.IsValid())
					m_strReconnectDialogClass = Guid.ProgID().c_str();	// ProgID geben lassen
			}

			dwCnt = _countof(cbBuffer);
			if (ERROR_SUCCESS == keySubKey.Open(keyClsId, g_cbCreateDatabase, KEY_READ) &&
				ERROR_SUCCESS == keySubKey.QueryValue (cbBuffer, NULL, &dwCnt))
			{
			CIID Guid (cbBuffer);

				if (Guid.IsValid())
					m_strCreateDatabaseClass = Guid.ProgID().c_str();	// ProgID geben lassen
			}
		}

	// Decription's aus Registry lesen
	CRegKey keyDesc;			// HKCR\\DataServerProgID\\TRiASDB\\Description

		if (ERROR_SUCCESS != keyDesc.Open(key, g_cbDescription, KEY_READ))
			_com_issue_error(HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND));		// sollte existieren

	// ab hier die eigentliche Info einlesen
	// IsReadWrite
		dwCnt = _countof(cbBuffer);
		m_fIsReadWrite = false;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbReadWrite, &dwCnt))
			m_fIsReadWrite = _ttol(cbBuffer) ? true : false;

	// NameIsFile
		dwCnt = _countof(cbBuffer);
		m_fNameIsFile = false;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbNameIsFile, &dwCnt))
			m_fNameIsFile = _ttol(cbBuffer) ? true : false;

	// NameIsDirectory
		dwCnt = _countof(cbBuffer);
		m_fNameIsDir = false;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbNameIsDirectory, &dwCnt))
			m_fNameIsDir = _ttol(cbBuffer) ? true : false;

	// NameIsDirectory
		dwCnt = _countof(cbBuffer);
		m_fNameIsSubStorage = false;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbNameIsSubStorage, &dwCnt))
			m_fNameIsSubStorage = _ttol(cbBuffer) ? true : false;

		_ASSERTE(m_fNameIsDir + m_fNameIsFile + m_fNameIsSubStorage <= 1);		// max. einer darf gesetzt sein

	// MultipleFiles
		dwCnt = _countof(cbBuffer);
		m_fMultipleFiles = false;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbMultipleFiles, &dwCnt))
			m_fMultipleFiles = _ttol(cbBuffer) ? true : false;

	// NeedsCoordSysNew
		dwCnt = _countof(cbBuffer);
		m_fNeedsCoordSysNew = false;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbNeedsCoordSysNew, &dwCnt))
			m_fNeedsCoordSysNew = _ttol(cbBuffer) ? true : false;

	// NeedsCoordSysExisting
		dwCnt = _countof(cbBuffer);
		m_fNeedsCoordSysExisting = false;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbNeedsCoordSysExisting, &dwCnt))
			m_fNeedsCoordSysExisting = _ttol(cbBuffer) ? true : false;

	// SourceStringUsed
		dwCnt = _countof(cbBuffer);
		m_fSourceStringUsed = false;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbSourceStringUsed, &dwCnt))
			m_fSourceStringUsed = _ttol(cbBuffer) ? true : false;

	// RestrictInstances
		dwCnt = _countof(cbBuffer);
		m_lInstances = 0;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbRestrictInstances, &dwCnt))
			m_lInstances = _ttol(cbBuffer);

	// ShortName
		dwCnt = _countof(cbBuffer);
		m_strShortName = g_cbNil;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbShortName, &dwCnt))
			m_strShortName = cbBuffer;

	// LongName
		dwCnt = _countof(cbBuffer);
		m_strLongName = g_cbNil;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbLongName, &dwCnt))
			m_strLongName = cbBuffer;

	// NameDescription
		dwCnt = _countof(cbBuffer);
		m_strFileDesc = g_cbNil;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbNameDescription, &dwCnt))
			m_strFileDesc = cbBuffer;

	// FilterString
		dwCnt = _countof(cbBuffer);
		m_strFilter = g_cbNil;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbFilterString, &dwCnt))
			m_strFilter = cbBuffer;

	// DefaultExtension
		dwCnt = _countof(cbBuffer);
		m_strDefExt = g_cbNil;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbDefaultExtension, &dwCnt))
			m_strDefExt = cbBuffer;

	// SourceDescription
		dwCnt = _countof(cbBuffer);
		m_strSourceDesc = g_cbNil;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbSourceDescription, &dwCnt))
			m_strSourceDesc = cbBuffer;

	// TempName
		dwCnt = _countof(cbBuffer);
		m_strTempName = g_cbNil;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbTempName, &dwCnt))
			m_strTempName = cbBuffer;

#if _TRiAS_VER > 0x0420
	// LastDirUsed ab V5.00 in HKCU
		{
		// ProgID der DataBaseClass des TRiASDatabase-Objektes
		CRegKey keyCU;

			if (ERROR_SUCCESS == keyCU.Open(HKEY_CURRENT_USER, "Software", KEY_READ) &&
				ERROR_SUCCESS == keyCU.Open(keyCU, REG_COMPANY_KEY, KEY_READ) &&
				ERROR_SUCCESS == keyCU.Open(keyCU, REG_PRODUCT_KEY, KEY_READ) &&
				ERROR_SUCCESS == keyCU.Open(keyCU, g_cbTRiASDB, KEY_READ) && 
				ERROR_SUCCESS == keyCU.Open(keyCU, pcProgID, KEY_READ))
			{
				dwCnt = _countof(cbBuffer);
				if (ERROR_SUCCESS == keyCU.QueryValue (cbBuffer, g_cbLastDirUsed, &dwCnt))
					m_strLastDirUsed = cbBuffer;
			}
		}
		if (m_strLastDirUsed.GetLength() == 0)
#endif
		{
		// LastDirUsed
			dwCnt = _countof(cbBuffer);
			m_strLastDirUsed = g_cbNil;
			if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbLastDirUsed, &dwCnt))
				m_strLastDirUsed = cbBuffer;
		}

	// Version
		dwCnt = _countof(cbBuffer);
		m_strVersion = g_cbNil;
		if (ERROR_SUCCESS == keyDesc.QueryValue (cbBuffer, g_cbVersion, &dwCnt))
			m_strVersion = cbBuffer;

	// ToolboxBitmap32
	DWORD dwData = 5;		// StandardBildchen

		keyDesc.QueryValue (dwData, g_cbToolboxBitmap32);
		m_lToolBox = dwData;

	} COM_CATCH;

	m_fIsInitialized = true;
	return S_OK;
}

///////////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CTRiASDataServerRegEntry::get_DataServerClass(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_DataServerClass");

CComBSTR bstr (m_strProgID);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_DatabaseClass(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_DatabaseClass");

CComBSTR bstr (m_strDBClass);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_DefaultExtension(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_DefaultExtension");

CComBSTR bstr (m_strDefExt);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_FilterString(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_FilterString");

CComBSTR bstr (m_strFilter);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_ShortName(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_ShortName");

CComBSTR bstr (m_strShortName);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_LongName(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_LongName");

CComBSTR bstr (m_strLongName);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_FileDescription(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_FileDescription");

CComBSTR bstr (m_strFileDesc);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_TempName(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_TempName");

CComBSTR bstr (m_strTempName);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_LastDirUsed(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_LastDirUsed");

CComBSTR bstr (m_strLastDirUsed);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::put_LastDirUsed(BSTR newVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);

	USES_CONVERSION;
	COM_TRY {
		m_strLastDirUsed = OLE2A(newVal);
		
	// am richtigen Platz wegschreiben
	CRegKey key;

		if (ERROR_SUCCESS != key.Open (HKEY_CLASSES_ROOT, m_strProgID, KEY_READ) ||
			ERROR_SUCCESS != key.Open (key, g_cbTRiASDB, KEY_READ) ||
			ERROR_SUCCESS != key.Open (key, g_cbDescription, KEY_READ) || 
			ERROR_SUCCESS != key.SetValue (m_strLastDirUsed, g_cbLastDirUsed))
		{
			return HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND);		// sollte existieren
		}

	} COM_CATCH;
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_IsReadWrite(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_IsReadWrite");

	*pVal = m_fIsReadWrite ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_NameIsFile(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_NameIsFile");

	*pVal = m_fNameIsFile ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_NameIsDirectory(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_NameIsDirectory");

	*pVal = m_fNameIsDir ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_NameIsSubStorage(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_NameIsSubStorage");

	*pVal = m_fNameIsSubStorage ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_SourceStringUsed(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_SourceStringUsed");

	*pVal = m_fSourceStringUsed ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_MultipleFiles(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_SourceStringUsed");

	*pVal = m_fMultipleFiles ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_SourceStringDescription(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_SourceStringDescription");

CComBSTR bstr (m_strSourceDesc);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_OpenWizPages(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_OpenWizPages");

	if (m_strOpenWizExtClass.IsEmpty())
		return E_FAIL;		// nicht gegeben

CComBSTR bstr (m_strOpenWizExtClass);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_Version(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_Version");

CComBSTR bstr (m_strVersion);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_ToolboxBitmap32(LONG * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_ToolboxBitmap32");

	*pVal = m_lToolBox;
	return (m_lToolBox != 0) ? S_OK : S_FALSE;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_RestrictInstances(LONG * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_RestrictInstances");

	*pVal = m_lInstances;
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_NeedsCoordSystemNew(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_NeedsCoordSystemNew");

	*pVal = m_fNeedsCoordSysNew ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_NeedsCoordSystemExisting(VARIANT_BOOL * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_NeedsCoordSystemExisting");

	*pVal = m_fNeedsCoordSysExisting ? VARIANT_TRUE : VARIANT_FALSE;
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_ReconnectDialog(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_ReconnectDialog");

	if (m_strReconnectDialogClass.IsEmpty())
		return E_FAIL;		// nicht gegeben

CComBSTR bstr (m_strReconnectDialogClass);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

STDMETHODIMP CTRiASDataServerRegEntry::get_CreateDatabase(BSTR * pVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if (!m_fIsInitialized)
		return REPORT_DBERROR(TRIASDB_E_OBJECT_NOT_INITIALIZED);
	if (NULL == pVal)
		return REPORT_DBERROR_ROUT(TRIASDB_E_INVALID_PARAMETER, "CTRiASDataServerRegEntry::get_CreateDatabase");

	if (m_strCreateDatabaseClass.IsEmpty())
		return E_FAIL;		// nicht gegeben

CComBSTR bstr (m_strCreateDatabaseClass);

	if (!bstr) 
		return REPORT_OUTOFMEMORY();
	*pVal = bstr.Detach();
	return S_OK;
}

