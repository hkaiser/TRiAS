// PropertySheet für RecherchePages 
// File: XmlPropertySequences.cpp

#include "triaspre.hxx"
#include "triasres.h"

#include <shlwapi.h>
#include <shfolder.h>

#include <ospace/file/path.h>

#include <funcs03.h>
#include <registry.hxx>
#include <dirisole.h>

#include "strings.h"
#include "extmain3.hxx"

#if defined(_DEBUG) && !defined(WIN16)
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#if defined(_USE_XML_GEOCOMPONENTS)

///////////////////////////////////////////////////////////////////////////////
// SmartIF's
DefineSmartInterface(ProgressIndicator);

///////////////////////////////////////////////////////////////////////////////
// Allgemeine Routine für Sequences aus Hauptmenu und ORWnd
namespace {
// Variante lediglich für das Hauptfenster
	HRESULT DoPropertySequenceMain (
		HWND hWnd, UINT uiResMain, LPCSTR pcRscMain, 
		IProgressIndicator *pIStatus = NULL, bool fForceReload = false, 
		IDataObject *pIDataIn = NULL, IDataObject **ppIDataOut = NULL)
	{
	// gesamte Sequence erzeugen und abarbeiten
	ResString resCap (uiResMain, 128);

		_ASSERTE(resCap.Len() > 0);

	// 'normale' Sequence
		return RunPropertyActionSequence (hWnd, pcRscMain, NULL, resCap, NULL, 
			pIStatus, pIDataIn, ppIDataOut, fForceReload);
	}


	HRESULT DoPropertySequenceMainFromFile (
		HWND hWnd, LPCSTR pcRscMain, IProgressIndicator *pIStatus = NULL, 
		bool fForceReload = true, IDataObject *pIDataIn = NULL, 
		IDataObject **ppIDataOut = NULL)
	{
		return RunPropertyActionSequence (hWnd, pcRscMain, NULL, NULL, NULL, 
			pIStatus, pIDataIn, ppIDataOut, fForceReload, NULL, TRUE);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Recherche
bool IrisWind::doTextRech (void)
{
os_string strKey ("Software\\" REG_COMPANY_KEY "\\" REG_PRODUCT_KEY "\\");

	strKey += "TRiASEx";
	strKey += g_cbDel;
	strKey += g_cbAppKey;
	strKey += g_cbDel;
	strKey += "SearchEngines";

CCurrentUser regSI (KEY_READ, strKey.c_str());
DWORD dwForceReload = 0;

	if (regSI.isValid())
		regSI.GetDWORD(g_cbForceReload, dwForceReload);

HRESULT hr = DoPropertySequenceMain(Handle(API_WINDOW_HWND), IDS_SEARCHCAP, "SearchObjectsOKS.xml", NULL, dwForceReload ? true : false);

	if (SUCCEEDED(hr) && dwForceReload) {
	// ggf. existierendes Flag löschen
	CCurrentUser regSIWrite (strKey.c_str());

		if (regSIWrite.isValid())
			regSIWrite.DeleteValue(g_cbForceReload);
	}
	return hr;
}

///////////////////////////////////////////////////////////////////////////////
// Suchen und Ersetzen
bool IrisWind::doTextReplace (void)
{
HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceMain(hWnd, IDS_REPLACECAP, "SearchAndReplaceOKS.xml", Status));
}

///////////////////////////////////////////////////////////////////////////////
// Klassifikation von Objekten über eine Objekteigenschaft
bool IrisWind::doClassify (void)
{
HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceMain(hWnd, IDS_CLASSIFYCAP, "ClassifyOKS.xml", Status));
}

/////////////////////////////////////////////////////////////////////////////
// Textobjekte erzeugen
bool IrisWind::doGenTextObjects (void)
{
HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceMain(hWnd, IDS_GENERATETEXT, "GenerateLabelsOKS.xml", Status));
}

/////////////////////////////////////////////////////////////////////////////
// Objekte umklassifizieren
bool IrisWind::doModIdents (void)
{
HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceMain(hWnd, IDS_MODIDENTCAP, "ModifyObjClassOKS.xml", Status));
}

/////////////////////////////////////////////////////////////////////////////
// Objekte kopieren
bool IrisWind::doCopyObjectsIdent (void)
{
HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceMain(hWnd, IDS_COPYOBJECTSCAP, "CopyObjectsOKS.xml", Status));
}

///////////////////////////////////////////////////////////////////////////////
// Objekte löschen
bool IrisWind::doDelIdents (void)
{
HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceMain(hWnd, IDS_DELETEIDENT_CAPTION, "DeleteObjectsOKS.xml", Status));
}

///////////////////////////////////////////////////////////////////////////////
// Objekte anzeigen
bool IrisWind::doSelIdents (void)
{
HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceMain(hWnd, IDS_SELECTIDENT_CAPTION, "SelectObjectsOKS.xml", Status));
}

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaften löschen
bool IrisWind::doDeleteObjProps (void)
{
HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceMain(hWnd, IDS_DELETEOBJEPROP_CAPTION, "DeleteObjectPropertiesOKS.xml", Status));
}

///////////////////////////////////////////////////////////////////////////////
// Objekteigenschaften löschen
bool ExtDirisWindow::doLoadObjColl (void)
{
HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceMain(hWnd, IDS_LOADOBJCOLL_CAPTION, "LoadObjectCollection.xml", Status));
}

///////////////////////////////////////////////////////////////////////////////
// Objekte importieren
bool ExtDirisWindow::doImport (void)
{
	return SUCCEEDED(DoPropertySequenceMain(Handle(API_WINDOW_HWND), IDS_DATAIMPORTCAP, "ImportData.xml"));
}

bool ExtDirisWindow::GenObjectProperties (void)
{
HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);
	return SUCCEEDED(DoPropertySequenceMain(hWnd, IDS_GENOBJPROPS, "GenerateObjPropsOKS.xml", Status));
}

///////////////////////////////////////////////////////////////////////////////
// Ladbaren Befehl ausführen

///////////////////////////////////////////////////////////////////////////////
// Xml-Config Verzeichnis aus Registry einlesen
HRESULT EnsureXmlPath (os_path &pathXml)
{
CRegKey regKey;

	if (ERROR_SUCCESS == regKey.Open (HKEY_CURRENT_USER, "Software", KEY_READ) &&
		ERROR_SUCCESS == regKey.Open (regKey, REG_COMPANY_KEY, KEY_READ) &&
		ERROR_SUCCESS == regKey.Open (regKey, REG_PRODUCT_KEY, KEY_READ) &&
		ERROR_SUCCESS == regKey.Open (regKey, "Directories"))
	{
	char cbBuffer[_MAX_PATH];
	DWORD dwLen = sizeof(cbBuffer);

		if (ERROR_SUCCESS == regKey.QueryValue (cbBuffer, "XmlConfigDir", &dwLen)) {
			pathXml = cbBuffer;
			return S_OK;
		}
		else {
		// VerzeichnisPfad neu erzeugen und anlegen
			if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA|CSIDL_FLAG_CREATE, NULL, 0, cbBuffer))) {
				PathAppend(cbBuffer, REG_COMPANY_KEY);
				CreateDirectory (cbBuffer, NULL);
				PathAppend(cbBuffer, REG_PRODUCT_KEY);
				CreateDirectory (cbBuffer, NULL);
				PathAppend(cbBuffer, "XmlConfigDir");
				CreateDirectory (cbBuffer, NULL);

				if (ERROR_SUCCESS == regKey.SetValue(cbBuffer, "XmlConfigDir")) {
					pathXml = cbBuffer;
					return S_OK;
				}
			}
		}
	}
	return E_FAIL;
}

extern "C" 
UINT _XTENSN_EXPORT APIENTRY XmlHookFcn (HWND hDlg, UINT wMsg, WPARAM wParam, 
	LPARAM lParam)
{
	if (WM_NOTIFY == wMsg) {
	LPOFNOTIFY pofn = (LPOFNOTIFY)lParam;

		if (CDN_INITDONE == pofn->hdr.code) {
		HWND hDlgP = ::GetParent(hDlg);
					
			CentreWindow (::GetParent (hDlgP), hDlgP);
			return true;
		}
	}
	return false;	// erstmal alles weiterleiten
}

bool ExtDirisWindow::ExecuteSequence()
{
ResString resTpl (IDS_LOADABLE_OPERATIONS, 128);
COpenDialog OpenDlg (this, (char *)resTpl.Addr());
os_path path;

	if (SUCCEEDED(EnsureXmlPath(path)))
		OpenDlg.SetInitialDir((LPCSTR)path);

#if defined(OFN_ENABLESIZING)
		if (IsWin41() || (IsWinNT() && IsWin50()))
			OpenDlg.AddFlags (OFN_ENABLESIZING);
#endif // OFN_ENABLESIZING

	OpenDlg.SetHookFcn ((HOOKFCN)XmlHookFcn);

os_string strCap (FakeTRiASName(IDS_EXECUTE_SEQUENCE, g_cbTRiAS));

	OpenDlg.SetCaption(strCap.c_str());
	OpenDlg.AddFlags(OFN_EXPLORER|OFN_LONGNAMES|OFN_HIDEREADONLY);
 	OpenDlg.Show();
	if (!OpenDlg.Result()) 
		return false;		// abgebrochen

// Xml-Dateinamen abholen
char cbBuffer[_MAX_PATH];

	OpenDlg.GetFileName (cbBuffer, sizeof(cbBuffer));
	if ('\0' == cbBuffer[0])
		return false;

HWND hWnd = Handle(API_WINDOW_HWND);
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceMainFromFile(hWnd, cbBuffer, Status));
}

#endif // defined(_USE_XML_GEOCOMPONENTS)
