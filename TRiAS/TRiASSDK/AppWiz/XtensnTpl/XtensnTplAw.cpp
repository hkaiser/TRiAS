// XtensnTplaw.cpp : implementation file
//

#include "stdafx.h"
#include "XtensnTpl.h"
#include "XtensnTplaw.h"

#ifdef _PSEUDO_DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// This is called immediately after the custom AppWizard is loaded.  Initialize
//  the state of the custom AppWizard here.
void CXtensnTplAppWiz::InitCustomAppWiz()
{
	// There are no steps in this custom AppWizard.
	SetNumberOfSteps(0);

	// Add build step to .hpj if there is one
	m_Dictionary[_T("HELP")] = _T("1");

	// Inform AppWizard that we're making a DLL.
	m_Dictionary[_T("PROJTYPE_DLL")] = _T("1");

	// TODO: Add any other custom AppWizard-wide initialization here.
}

// This is called just before the custom AppWizard is unloaded.
void CXtensnTplAppWiz::ExitCustomAppWiz()
{
	// TODO: Add code here to deallocate resources used by the custom AppWizard
}

// This is called when the user clicks "Create..." on the New Project dialog
CAppWizStepDlg* CXtensnTplAppWiz::Next(CAppWizStepDlg* pDlg)
{
	ASSERT(pDlg == NULL);	// By default, this custom AppWizard has no steps

	// Set template macros based on the project name entered by the user.

	// Get value of $$root$$ (already set by AppWizard)
	CString strRoot;
	m_Dictionary.Lookup(_T("root"), strRoot);
	
	// Set value of $$Doc$$, $$DOC$$
	CString strDoc = strRoot.Left(6);
	m_Dictionary[_T("Doc")] = strDoc;
	strDoc.MakeUpper();
	m_Dictionary[_T("DOC")] = strDoc;

	// Set value of $$MAC_TYPE$$
	strRoot = strRoot.Left(4);
	int nLen = strRoot.GetLength();
	if (strRoot.GetLength() < 4)
	{
		CString strPad(_T(' '), 4 - nLen);
		strRoot += strPad;
	}
	strRoot.MakeUpper();
	m_Dictionary[_T("MAC_TYPE")] = strRoot;

// diverse Guids zum dictionary hinzufügen
	AddGuid (_T("LIBID_GUID"));
	AddGuid (_T("XTENSION_GUID"));

	AddGuid (_T("STDAFX_H_GUID"), TRUE);
	AddGuid (_T("CONFIG_H_GUID"), TRUE);
	AddGuid (_T("VERSION_H_GUID"), TRUE);
	AddGuid (_T("XTENSION_H_GUID"), TRUE);
	AddGuid (_T("XTENSIONUTIL_H_GUID"), TRUE);

// aktuelles Datum erzeugen (für VersionsInfo)
char buf[128];
time_t timeval;

	time(&timeval);
	buf[strftime(buf, sizeof(buf) - 1, "%y%m%d", localtime(&timeval))] = 0;
	m_Dictionary[_T("version_date")] = buf;

	buf[strftime(buf, sizeof(buf) - 1, "%d.%m.%Y %H:%M:%S", localtime(&timeval))] = 0;
	m_Dictionary[_T("date_n_time")] = buf;

// Return NULL to indicate there are no more steps.  (In this case, there are
//  no steps at all.)
	return NULL;
}

void CXtensnTplAppWiz::CustomizeProject(IBuildProject* pProject)
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

	// midl Einstellungen korrigieren
		Cfg -> RemoveToolSettings (CComBSTR("midl.exe"), CComBSTR("/mktyplib203"), vtMissing);

	CString str ("/Oicf /h ");
	CString strRoot;
		
		m_Dictionary.Lookup(_T("root"), strRoot);
		str += "\"";
		str += strRoot;
		str += ".h";
		str += "\"";
		Cfg -> AddToolSettings (CComBSTR("midl.exe"), CComBSTR(str), vtMissing);

	// C++ Einstellungen korrigieren
		Cfg -> RemoveToolSettings (CComBSTR("cl.exe"), CComBSTR("/D \"_USRDLL\""), vtMissing);
		Cfg -> AddToolSettings (CComBSTR("cl.exe"), CComBSTR("/D \"_AFXEXT\""), vtMissing);
		
	// Versioning erzeugen
		Cfg -> AddCustomBuildStepToFile (CComBSTR("Version.tpl"), CComBSTR("nmake -nologo -f version.mak Version.h"), CComBSTR("Version.h"), CComBSTR("Performing Custom Build Step on $(InputPath)"), vtMissing);

	CString strTpl = strRoot;
	CString strToBuild = strRoot;
	CString strBuild = "nmake -nologo -f version.mak ";

		strTpl += ".tpl";
		strToBuild += ".def";
		Cfg -> AddCustomBuildStepToFile (CComBSTR(strTpl), CComBSTR(strBuild + strToBuild), CComBSTR(strToBuild), CComBSTR("Performing Custom Build Step on $(InputPath)"), vtMissing);

		strTpl = strRoot + "v.tpl";
		strToBuild = strRoot + ".rcv";
		Cfg -> AddCustomBuildStepToFile (CComBSTR(strTpl), CComBSTR(strBuild + strToBuild), CComBSTR(strToBuild), CComBSTR("Performing Custom Build Step on $(InputPath)"), vtMissing);
	}
}


// Here we define one instance of the CXtensnTplAppWiz class.  You can access
//  m_Dictionary and any other public members of this class through the
//  global XtensnTplaw.
CXtensnTplAppWiz XtensnTplaw;

///////////////////////////////////////////////////////////////////////////////
// AddGuid
BOOL CXtensnTplAppWiz::AddGuid (LPCTSTR pcEntry, BOOL fReplaceDash)
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
	m_Dictionary[pcEntry] = str;
	return TRUE;
}

