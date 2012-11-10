// $Header: $
// Copyright© 1999-2000 TRiAS GmbH Potsdam, All rights reserved
// Created: 12.01.2000 00:11:24
//
// @doc
// @module TRiASDBDSAw.cpp | Implementation of the <c CTRiASDBDSAppWiz> class

#include "stdafx.h"

#include "Version.h"
#include "TRiASDBDS.h"
#include "TRiASDBDSaw.h"
#include "ConfigDlg.h"
#include "Chooser.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
END_OBJECT_MAP()

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CTRiASDBDSAppWiz::InitCustomAppWiz()
{
	m_pChooser = new CDialogChooser;

	// There are no steps in this custom AppWizard.
	SetNumberOfSteps(1);

	// Add build step to .hpj if there is one
	DefineBoolMacro(_T("HELP"), TRUE);

	// Inform AppWizard that we're making a DLL.
	DefineBoolMacro(_T("PROJTYPE_DLL"), TRUE);

// Variablen, die vom Nutzer abgefragt werden
	m_Initials = _T("HK");
}

// This is called just before the custom AppWizard is unloaded.
void CTRiASDBDSAppWiz::ExitCustomAppWiz()
{
	delete m_pChooser;
	m_pChooser = NULL;	
}

// This custom AppWizard only targets Win32 platform, so don't display
//  any others.
void CTRiASDBDSAppWiz::GetPlatforms(CStringList& Platforms)
{
	POSITION pos = Platforms.GetHeadPosition();
	while (pos != NULL)
	{
		POSITION posCurr = pos;
		CString strPlatform = Platforms.GetNext(pos);
		if (strPlatform.Left(5) != _T("Win32"))
			Platforms.RemoveAt(posCurr);
	}
}

// If the end-user clicks next, let the dialog chooser decide
//  what to pop up next.
CAppWizStepDlg* CTRiASDBDSAppWiz::Next(CAppWizStepDlg* pDlg)
{
	if (pDlg == NULL) 
		SetRootOptions();

	return m_pChooser->Next(pDlg);
}

// If the end-user clicks back, let the dialog chooser decide
//  what to pop up.
CAppWizStepDlg* CTRiASDBDSAppWiz::Back(CAppWizStepDlg* pDlg)
{
	return m_pChooser->Back(pDlg);
}

void CTRiASDBDSAppWiz::SetRootOptions()
{
// Get value of $$root$$ (already set by AppWizard)
CString strRoot;

	m_Dictionary.Lookup(_T("root"), strRoot);

// Set value of $$Doc$$, $$DOC$$
CString strDoc = strRoot.Left(6);

	DefineStringMacro(_T("Doc"), strDoc);
	strDoc.MakeUpper();
	DefineStringMacro(_T("DOC"), strDoc);

// diverse Guids zum dictionary hinzufügen
	AddGuid (_T("GUID_STDAFX_H"), TRUE);
	AddGuid (_T("GUID_DLLDATA_H"), TRUE);
	AddGuid (_T("GUID_CONFIG_H"), TRUE);
	AddGuid (_T("GUID_DBUTIL_H"), TRUE);
	AddGuid (_T("GUID_VERSION_H"), TRUE);
	AddGuid (_T("GUID_STRINGS_H"), TRUE);
	AddGuid (_T("GUID_SAMPLEDATATYPES_H"), TRUE);
	AddGuid (_T("GUID_PROPERTYBASE_H"), TRUE);
	AddGuid (_T("GUID_PROPERTYSUPPORT_H"), TRUE);
	AddGuid (_T("GUID_GEOMETRYBLOB_H"), TRUE);
	AddGuid (_T("GUID_SMARTIFS_H"), TRUE);

	AddGuid (_T("GUID_DBENGINE_H"), TRUE);
	AddGuid (_T("GUID_DATABASE_H"), TRUE);
	AddGuid (_T("GUID_OBJECTSCOLLECTION_H"), TRUE);
	AddGuid (_T("GUID_OBJECTS_H"), TRUE);
	AddGuid (_T("GUID_OBJECT_H"), TRUE);
	AddGuid (_T("GUID_FEATURES_H"), TRUE);
	AddGuid (_T("GUID_FEATURE_H"), TRUE);
	AddGuid (_T("GUID_GEOFEATURES_H"), TRUE);
	AddGuid (_T("GUID_GEOFEATURE_H"), TRUE);
	AddGuid (_T("GUID_OBJECTCURSORPROPERTY_H"), TRUE);
	AddGuid (_T("GUID_CURSORPROPERTY_H"), TRUE);
	AddGuid (_T("GUID_CPDBENGINEEVENTS_H"), TRUE);

	DefineStringMacro(_T("initials"), m_Initials);

// aktuelles Datum erzeugen (für VersionsInfo)
TCHAR buf[128], vdate[128];
time_t timeval;

	time(&timeval);
	vdate[strftime(vdate, sizeof(vdate) - 1, "%y%m%d", localtime(&timeval))] = 0;
	DefineStringMacro(_T("version_date"), vdate);

	buf[strftime(buf, sizeof(buf) - 1, "%d.%m.%Y %H:%M:%S", localtime(&timeval))] = 0;
	DefineStringMacro(_T("date_n_time"), buf);
	
	buf[strftime(buf, sizeof(buf) - 1, "%Y", localtime(&timeval))] = 0;
	DefineStringMacro(_T("year"), buf);
	
// Version dieses Wizards
	wsprintf (buf, "V%s.%s.%s (#%s%s)", TRIASDBDS_VERSION, TRIASDBDS_RELEASE, TRIASDBDS_BUILD, m_Initials, BUILD_DATE);
	DefineStringMacro(_T("this_version"), buf);

// Firmennamen parametrisieren
	DefineStringMacro(_T("company"), COMPANY_NAME);

// Garantieklauses erzeugen
	EmitGaranties();
}

void CTRiASDBDSAppWiz::CustomizeProject(IBuildProject* pProject)
{
CComPtr<IConfigurations> Configs;

	pProject -> get_Configurations (&Configs);

long lCnt = 0;

	Configs -> get_Count (&lCnt);

// für alle Konfigurationen
CComVariant vtMissing (DISP_E_PARAMNOTFOUND, VT_ERROR);

	for (long i = 1; i <= lCnt; i++) {
	CComPtr<IConfiguration> Cfg;

		Configs -> Item (CComVariant(i), &Cfg);

	// midl einstellungen korrigieren
		Cfg -> RemoveToolSettings (CComBSTR("midl.exe"), CComBSTR("/mktyplib203"), vtMissing);

	CString str ("/Oicf /h ");
	CString strRoot;
		
		m_Dictionary.Lookup(_T("root"), strRoot);
		str += "\"" + strRoot;
		str += ".h\"";
		Cfg -> AddToolSettings (CComBSTR("midl.exe"), CComBSTR(str), vtMissing);

	// .def File zum Linker hinzufügen
		str = strRoot;
		str += ".def";
		Cfg -> AddToolSettings (CComBSTR("link.exe"), CComBSTR("/def:\"" + str + "\""), vtMissing);

	// Versioning erzeugen
		Cfg -> AddCustomBuildStepToFile (CComBSTR("Version.tpl"), CComBSTR("nmake -nologo -f version.mak Version.h"), CComBSTR("Version.h"), CComBSTR("Performing Custom Build Step on $(InputPath)"), vtMissing);

	CString strTpl = "\"" + strRoot + ".tpl\"";
	CString strToBuild = "\"" + strRoot + ".def\"";
	CString strBuild = "nmake -nologo -f version.mak ";

		Cfg -> AddCustomBuildStepToFile (CComBSTR("\"" + strTpl + "\""), CComBSTR(strBuild + strToBuild), CComBSTR(strToBuild), CComBSTR("Performing Custom Build Step on $(InputPath)"), vtMissing);

		strTpl = "\"Res/" + strRoot + "v.tpl\"";
		strToBuild = "\"Res/" + strRoot + ".rcv\"";
		Cfg -> AddCustomBuildStepToFile (CComBSTR(strTpl), CComBSTR(strBuild + strToBuild), CComBSTR(strToBuild), CComBSTR("Performing Custom Build Step on $(InputPath)"), vtMissing);
	}
}


// Here we define one instance of the CTRiASDBDSAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global TRiASDBDSaw.
CTRiASDBDSAppWiz TRiASDBDSaw;

///////////////////////////////////////////////////////////////////////////////
// AddGuid
BOOL CTRiASDBDSAppWiz::AddGuid (LPCTSTR pcEntry, BOOL fReplaceDash)
{
GUID Guid;

	if (FAILED(CoCreateGuid (&Guid)))
		return FALSE;

wchar_t cbBuffer[_MAX_PATH];

	if (FAILED(StringFromGUID2(Guid, cbBuffer, _MAX_PATH)))
		return FALSE;

CString str (cbBuffer);

	str.TrimLeft (_T('{'));
	str.TrimRight (_T('}'));

	if (fReplaceDash)
		str.Replace(_T('-'), _T('_'));

// add this Guid
	DefineStringMacro(pcEntry, str);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// FindOrCreateGuid
BOOL CTRiASDBDSAppWiz::FindOrCreateGuid (LPCTSTR pcEntry, LPCSTR pcProgID, BOOL fReplaceDash)
{
char cbBuffer[_MAX_PATH];
CRegKey key;
DWORD dwType = 0;
DWORD dw = _MAX_PATH;

	if (ERROR_SUCCESS != key.Open (HKEY_CLASSES_ROOT, pcProgID, KEY_READ) ||
		ERROR_SUCCESS != key.Open (key, "CLSID", KEY_READ) ||
		ERROR_SUCCESS != RegQueryValueEx(key.m_hKey, (LPTSTR)NULL, NULL, &dwType, (LPBYTE)cbBuffer, &dw))
	{
		return AddGuid (pcEntry, fReplaceDash);
	}
	_ASSERTE(dwType == REG_SZ);

// Registryeintrag existiert bereits
CString str (cbBuffer);

	str.TrimLeft (_T('{'));
	str.TrimRight (_T('}'));

	if (fReplaceDash)
		str.Replace(_T('-'), _T('_'));

// add this Guid
	DefineStringMacro(pcEntry, str);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// FindOrCreateGuid
BOOL CTRiASDBDSAppWiz::FindOrCreateLibID (LPCTSTR pcEntry, LPCSTR pcProgID)
{
char cbBuffer[_MAX_PATH];
CRegKey key;
DWORD dwType = 0;
DWORD dw = _MAX_PATH;

	if (ERROR_SUCCESS != key.Open (HKEY_CLASSES_ROOT, pcProgID, KEY_READ) ||
		ERROR_SUCCESS != key.Open (key, "TRiASDB", KEY_READ) ||
		ERROR_SUCCESS != key.Open (key, "Typelib", KEY_READ) ||
		ERROR_SUCCESS != RegQueryValueEx(key.m_hKey, (LPTSTR)NULL, NULL, &dwType, (LPBYTE)cbBuffer, &dw))
	{
		return AddGuid (pcEntry);
	}
	_ASSERTE(dwType == REG_SZ);

// Registryeintrag existiert bereits
CString str (cbBuffer);

	str.TrimLeft (_T('{'));
	str.TrimRight (_T('}'));

// add this Guid
	DefineStringMacro(pcEntry, str);
	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// Feststellen, ob auf diesem Rechner die Garantiebestimmungen generiert werden 
// sollen
BOOL CTRiASDBDSAppWiz::EmitGaranties()
{
// Garantieklausel generieren
BOOL fEmit = TRUE;
CRegKey key;
DWORD dwValue = 1;

	if (ERROR_SUCCESS == key.Open (HKEY_CURRENT_USER, "TRiAS", KEY_READ) &&
		ERROR_SUCCESS == key.Open (key, "TRiASDBSDK", KEY_READ) &&
		ERROR_SUCCESS == key.Open (key, "TRiASDBDS", KEY_READ) &&
		ERROR_SUCCESS == key.QueryValue(dwValue, "EmitWarranties"))
	{
		fEmit = (0 != dwValue) ? TRUE : FALSE;
	}
	DefineBoolMacro (_T("EMIT_WARRANTIES"), fEmit);
	return TRUE;
}


