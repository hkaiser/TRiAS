// PropertySheet für GeoComponentSequences aus winem ORWNd
// File: XmlPropertySequencesORWnd.cpp

#include "triaspre.hxx"
#include "triasres.h"

#include <Atl/Ciid.h>

#include <ospace/file/path.h>

#include <funcs03.h>
#include <registry.hxx>
#include <dirisole.h>
#include <selidprp.h>
#include <selobwnd.h>

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
// Variante für ein Objektrecherchefenster
	HRESULT DoPropertySequenceORWnd (
		HWND hWnd, UINT uiResMain, UINT uiResOR, LPCSTR pcRscOR, 
		IProgressIndicator *pIStatus = NULL, bool fForceReload = false, 
		IDataObject *pIDataIn = NULL, IDataObject **ppIDataOut = NULL,
		IDataObject *pIDataCtx = NULL)
	{
		COM_TRY {
		// gesamte Sequence erzeugen und abarbeiten
		ResString resCap (uiResMain, 128);
		ResString resCapOR (uiResOR, 128);

			_ASSERTE(resCap.Len() > 0);
			_ASSERTE(resCapOR.Len() > 0);

		// Sequence aus einem ORWnd
		WDataObject DataCtx (pIDataCtx);

			if (!DataCtx.IsValid())
				THROW_FAILED_HRESULT(DataCtx.CreateInstance(CLSID_DataTransferObject));
			THROW_FAILED_HRESULT(SetHWNDData (hWnd, DataCtx));

		HRESULT hr = RunPropertyActionSequence (hWnd, pcRscOR, NULL, resCap, 
			resCapOR, pIStatus, pIDataIn, ppIDataOut, fForceReload, DataCtx);

			if (FAILED(hr))
				return hr;

		} COM_CATCH;
		return S_OK;
	}

	HRESULT DoPropertySequenceORWndFromFile (
		HWND hWnd, LPCSTR pcRscOR, IProgressIndicator *pIStatus = NULL, 
		bool fForceReload = true, IDataObject *pIDataIn = NULL, 
		IDataObject **ppIDataOut = NULL, IDataObject *pIDataCtx = NULL)
	{
		// Sequence aus einem ORWnd
		COM_TRY {
		WDataObject DataCtx (pIDataCtx);

			if (!DataCtx.IsValid())
				THROW_FAILED_HRESULT(DataCtx.CreateInstance(CLSID_DataTransferObject));
			THROW_FAILED_HRESULT(SetHWNDData (hWnd, DataCtx));

		HRESULT hr = RunPropertyActionSequence (hWnd, pcRscOR, NULL, NULL, NULL, 
			pIStatus, pIDataIn, ppIDataOut, fForceReload, NULL, TRUE);

			if (FAILED(hr))
				return hr;

		} COM_CATCH;
		return S_OK;
	}
}

///////////////////////////////////////////////////////////////////////////////
// Recherche
bool ObjektInfo::doRecherche (void)
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

HRESULT hr = DoPropertySequenceORWnd(m_hWnd, IDS_SEARCHCAP, IDS_SEARCHCAP_OR, 
	"SearchObjectsORWnd.xml", NULL, dwForceReload ? true : false);

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
bool ObjektInfo::doReplace (void)			// Suchen und ersetzen
{
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (m_hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceORWnd(m_hWnd, IDS_REPLACECAP, IDS_REPLACECAP_OR, 
		"SearchAndReplaceORWnd.xml", Status));
}

///////////////////////////////////////////////////////////////////////////////
// Klassifikation von Objekten über eine Objekteigenschaft
bool ObjektInfo::doClassify (void)			// Klassifikation
{
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (m_hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceORWnd(m_hWnd, IDS_CLASSIFYCAP, IDS_CLASSIFYCAP_OR, 
		"ClassifyORWnd.xml", Status));
}

/////////////////////////////////////////////////////////////////////////////
// Textobjekte erzeugen
bool ObjektInfo::doGenTextObjects (void)
{
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (m_hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceORWnd(m_hWnd, IDS_GENERATETEXT, IDS_GENERATETEXT_OR, 
		"GenerateLabelsORWnd.xml", Status));
}

/////////////////////////////////////////////////////////////////////////////
// Objekte umklassifizieren
bool ObjektInfo::doModAllIdents (void) 
{
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (m_hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceORWnd(m_hWnd, IDS_MODIDENTCAP, IDS_MODIDENTCAP_OR, 
		"ModifyObjClassORWnd.xml", Status));
}

/////////////////////////////////////////////////////////////////////////////
// Objekte kopieren
bool ObjektInfo::doCopyObjects (void) 
{
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (m_hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceORWnd(m_hWnd, IDS_COPYOBJECTSCAP, IDS_COPYOBJECTSCAP_OR, 
		"CopyObjectsORWnd.xml", Status));
}

///////////////////////////////////////////////////////////////////////////////
// Objekte löschen
bool ObjektInfo::doObjDelete (void) 
{
int oldIndex = m_pKurzInfo -> GetCaretIndex ();
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status -> InitNew (m_hWnd, PIFLAG_RESULT);

HRESULT hr = DoPropertySequenceORWnd(m_hWnd, IDS_DELETEIDENT_CAPTION, IDS_DELOBJECTCAP_OR, 
	"DeleteObjectsORWnd.xml", Status);

	if (SUCCEEDED(hr)) {
		ActivateNextItem (oldIndex);		// neues Objekt in ListBox markieren und aktivieren
		UpdateCaption();					// alles gelöscht: IrisWind neuzeichnen
	}
	DEX_RePaint();
	return SUCCEEDED(hr);
}

///////////////////////////////////////////////////////////////////////////////
// Objekte löschen
bool ObjektInfo::doDeleteObjProps (void) 
{
int oldIndex = m_pKurzInfo -> GetCaretIndex ();
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status -> InitNew (m_hWnd, PIFLAG_RESULT);

HRESULT hr = DoPropertySequenceORWnd(m_hWnd, IDS_DELETEOBJEPROP_CAPTION, IDS_DELETEOBJEPROP_CAPTION_OR, 
	"DeleteObjectPropertiesORWnd.xml", Status);

	if (SUCCEEDED(hr)) {
		ActivateNextItem (oldIndex);		// neues Objekt in ListBox markieren und aktivieren
		UpdateCaption();					// alles gelöscht: IrisWind neuzeichnen
	}
	DEX_RePaint();
	return SUCCEEDED(hr);
}

///////////////////////////////////////////////////////////////////////////////
// Objektmenge speichern
bool ObjektInfo::doSaveObjColl (void) 
{
WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status -> InitNew (m_hWnd, PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceORWnd(m_hWnd, IDS_SAVEOBJCOLL_CAPTION, 
		IDS_SAVEOBJCOLL_CAPTION, "SaveObjectCollection.xml", Status));
}

///////////////////////////////////////////////////////////////////////////////
// Differenz zweier Recherchefenster bilden
bool ObjektInfo::WindowOperations (IEnum<LONG> *pIEnumObj, UINT uiResMain, 
	UINT uiResOR, LPCSTR pcRscOR)
{
HWND hWndDropSrc = DEX_GetDropSourceORWnd();
HRESULT hr = S_OK;

	_ASSERTE(IsWindow(hWndDropSrc));

	COM_TRY {
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (m_hWnd, PIFLAG_RESULT);

	// Einträge selektieren, Initialisierungsdaten setzen
	WDataObject DataObj(CLSID_DataTransferObject);
	WDataObject DataCtx(CLSID_DataTransferObject);

		THROW_FAILED_HRESULT(SetEnumLONGData (pIEnumObj, DataObj));
		THROW_FAILED_HRESULT(SetHWND(hWndDropSrc, DataCtx, &c_feIgnoreWindow));

		hr = DoPropertySequenceORWnd(m_hWnd, uiResMain, uiResOR, pcRscOR, 
			Status, false, DataObj, NULL, DataCtx);

	} COM_CATCH_RETURN(false);
	return SUCCEEDED(hr);
}

bool ObjektInfo::BuildDifferenceInNewWindow (IEnum<LONG> *pIEnumObj)
{
	return WindowOperations(pIEnumObj, IDS_DIFFERENCE_OR, IDS_DIFFERENCE_OR, 
		"ORWndDifference.xml");
}

bool ObjektInfo::BuildInvDifferenceInNewWindow (IEnum<LONG> *pIEnumObj)
{
	return WindowOperations(pIEnumObj, IDS_DIFFERENCE_OR, IDS_DIFFERENCE_OR, 
		"ORWndInvDifference.xml");
}

///////////////////////////////////////////////////////////////////////////////
// Symmtrische Differenz zweier Recherchefenster bilden
bool ObjektInfo::BuildXorInNewWindow (IEnum<LONG> *pIEnumObj)
{
	return WindowOperations(pIEnumObj, IDS_SYMMDIFFERENCE_OR, IDS_SYMMDIFFERENCE_OR, 
		"ORWndSymmetricDifference.xml");
}

///////////////////////////////////////////////////////////////////////////////
// Schnittmenge zweier Recherchefenster bilden
bool ObjektInfo::BuildIntersectionInNewWindow (IEnum<LONG> *pIEnumObj)
{
	return WindowOperations(pIEnumObj, IDS_INTERSECTION_OR, IDS_INTERSECTION_OR, 
		"ORWndIntersection.xml");
}

///////////////////////////////////////////////////////////////////////////////
// Vereinigungsmenge zweier Recherchefenster bilden
bool ObjektInfo::AddObjectsToNewWindow (IEnum<LONG> *pIEnumObj)
{
	return WindowOperations(pIEnumObj, IDS_UNION_OR, IDS_UNION_OR, 
		"ORWndUnion.xml");
}

///////////////////////////////////////////////////////////////////////////////
// Komplementäre Objektmenge bilden und anzeigen
inline 
void FormatAndAdd (os_string &rStr, LPCSTR pcOks, DWORD dwType, bool fComma)
{
char cbBuffer[64];

	wsprintf(cbBuffer, "%s[%s]:%02x", fComma ? "," : "", pcOks, dwType);
	rStr += cbBuffer;
}

BOOL EXPORTTRIAS WINAPI SelectIdents (long lIdent, DWORD dwTypes, void *pData)
{
char cbOks[MAX_OKS_LEN];

	if (SUCCEEDED(ClassFromIdent ((ULONG)lIdent, cbOks))) {
	os_string *pStr = reinterpret_cast<os_string *>(pData);
	bool fComma = (*pStr == g_cbSelect) ? false : true;		// nur beim Ersten kein Komma

		if (dwTypes & OTPunkt) {
			FormatAndAdd (*pStr, cbOks, OTPunkt, fComma);
			fComma = true;
		}
		if (dwTypes & OTLinie) {
			FormatAndAdd (*pStr, cbOks, OTLinie, fComma);
			fComma = true;
		}
		if (dwTypes & OTFlaeche) {
			FormatAndAdd (*pStr, cbOks, OTFlaeche, fComma);
			fComma = true;
		}
		if (dwTypes & OTText)
			FormatAndAdd (*pStr, cbOks, OTText, fComma);
	}
	return TRUE;
}

bool ObjektInfo::doComplementObjects (void)
{
HRESULT hr = S_OK;

	COM_TRY {
	WProgressIndicator Status;

		Status.CreateInstance(CLSID_ProgressIndicator);
		if (Status.IsValid()) 
			Status -> InitNew (m_hWnd, PIFLAG_RESULT);

	// Einträge selektieren
	WDataObject DataObj(CLSID_DataTransferObject);
	os_string str (g_cbSelect);
	ENUMNOKEYLONG ENK;
		
		ENK.eFcn = (ENUMLONGKEYPROC)SelectIdents;
		ENK.ePtr = &str;
		DEXOR_EnumIdentsSelectedEx (m_hWnd, ENK);
	
	// Initialisierungsdaten setzen
	CIID Guid (CLSID_SelectIdentObjTyp);
	FORMATETC c_feProgID = {
			RegisterClipboardFormat (Guid.ProgID().c_str()),	// CLIPFORMAT cf
			NULL,											// DVTARGETDEVICE *ptd
			DVASPECT_CONTENT,								// DWORD dwAspect
			-1,												// LONG lindex	
			TYMED_ISTREAM,									// DWORD tymed
		};

	CComVariant v1 (str.c_str());

		THROW_FAILED_HRESULT(SetVariantData (v1, DataObj, &c_feProgID));
		hr = DoPropertySequenceORWnd(m_hWnd, IDS_COMPLEMENTOBJS_OR, IDS_COMPLEMENTOBJS_OR, 
			"ComplementaryObjectsORWnd.xml", Status, false, DataObj);

	} COM_CATCH_RETURN(false);
	return SUCCEEDED(hr);
}

///////////////////////////////////////////////////////////////////////////////
// Ladbaren Befehl ausführen

HRESULT EnsureXmlPath (os_path &pathXml);
extern "C" UINT _XTENSN_EXPORT APIENTRY XmlHookFcn (HWND hDlg, UINT wMsg, 
    WPARAM wParam, LPARAM lParam);

bool ObjektInfo::ExecuteSequence()
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

WProgressIndicator Status;

	Status.CreateInstance(CLSID_ProgressIndicator);
	if (Status.IsValid()) 
		Status ->InitNew (hWnd(), PIFLAG_RESULT);

	return SUCCEEDED(DoPropertySequenceORWndFromFile(hWnd(), cbBuffer, Status));
}


#endif // defined(_USE_XML_GEOCOMPONENTS)
