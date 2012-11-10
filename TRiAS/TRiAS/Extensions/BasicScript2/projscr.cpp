// file DebCtrl.cpp

#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <new>
#include <iobjman.h>

#include "macrguid.h"

#include "iscrprop.h"

#include "conststr.h"
#include "projscr.h"
#include "spltree.h" 

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

#define OS_NO_STREAM_SUPPORT

////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(ObjectManagement);
DefineSmartInterface(StreamInfo);
DefineSmartInterface(ScriptProperty);
DefineSmartInterface(AddScriptProperty);
DefineSmartInterface(ObjectProps);
DefineSmartInterface(ObjectProperty);
DefineSmartInterface(BSProperty);
DefineSmartInterface(TreeItem);
DefineSmartInterface(ObjManHelper);
DefineSmartInterface(ExportImportProject);

///////////////////////////////////////////////////////////////////////////
// globale Funktionen
BOOL		LoadString(CString & str, int IDS);
CString		GetDefaultName(int IDS);
CString GetPropertyDefaultScript();
CString GetDefaultScript();
CString GetFilterDefaultScript();

CString		GetFileName (CString &rPath, BOOL fExt);
CString		CorrectExtension (CString &rPath, UINT uiResIDExt);

/////////////////////////////////////////////////////////////////////////////
// globale Variablen
extern SummitModul g_SummitModuls[];


/////////////////////////////////////////////////////////////////////////////
// CProjectScript2
CProjectScript2::CProjectScript2()
	:m_IUnknown(NULL)
{
	m_cRef = 0;

	m_fIsDirty = false;
	m_fInitNew = false;
	m_fSuperItem = false;
	m_fEditOnly = false;
	m_fLoaded = false;
	m_clsid = CLSID_NULL;
	m_hCode = NULL;
	m_fIsLabelEdit	= false;
	m_fIsJustInsert	= false;
	m_fRemovedInstall = false;

	m_pIStreamInfo  = NULL;
	m_pIObjManagement  = NULL;
}

CProjectScript2::~CProjectScript2()
{
	if (m_hCode) CoTaskMemFree(m_hCode); m_hCode = NULL;
	ResetManagement();
}

HRESULT CProjectScript2::Init(IObjectManagement *pIOM, IStreamInfo * pIS, REFIID riid)
{	
	ResetManagement();
	SetManagement(pIOM, pIS);
	m_clsid = riid;
	return S_OK;
}

void CProjectScript2::ResetManagement()
{
	if (m_pIStreamInfo) {
		m_pIStreamInfo -> Release();
		m_pIStreamInfo  = NULL;
	}
	if (m_pIObjManagement) {
		m_pIObjManagement -> Release();
		m_pIObjManagement  = NULL;
	}
}
void CProjectScript2::SetManagement(IObjectManagement *pIObjM, IStreamInfo *pIStreamInfo)
{
	if (pIObjM) {
		m_pIObjManagement = pIObjM;
		m_pIObjManagement -> AddRef();
	}
	if (pIStreamInfo) {
		m_pIStreamInfo = pIStreamInfo;
		m_pIStreamInfo -> AddRef();
	}
}
////////////////////////////////////////////////////////////////////////////
// ITreeItem_Methods
STDMETHODIMP CProjectScript2::Import (REFIID riid, LPCSTR lpcstrFileName, LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui)
{// Importiert ein externes Script in dieses Script
	HRESULT hr = NOERROR;

	*ppcMacroText = NULL;
	*phCode = NULL;
	*lplplp = NULL;
	ui = 0;

	CString str = lpcstrFileName;
	m_strMacroName = GetFileName(str, false);
	// Von File nach Storage kopieren, Code, Text, ...  liefern
	return  CopyTo(riid, lpcstrFileName, m_strMacroName, ppcMacroText, phCode, lplplp, ui);
}

STDMETHODIMP CProjectScript2::Open (LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui, BOOL fCreateTemp)
{
	ASSERT (!m_strMacroName.IsEmpty());

	HRESULT hr = NOERROR;

	*ppcMacroText = NULL;
	*phCode = NULL;
	*lplplp = NULL;
	ui = 0;

	try
	{
		BOOL fDirty = GetDirty(); // Dirty merken
		THROW_FAILED_HRESULT(GetScript (m_strMacroName, m_clsid, fCreateTemp));

		hr = GetProperty (m_strMacroName, ppcMacroText, phCode, lplplp, ui);

		if (FAILED(hr)) 
		{// bei neues Script öffnen
			hr = New(ppcMacroText);
			if (FAILED(hr)) _com_issue_error(hr);
			SetInitNew(true);
		}
		else 
		{// Script ist schon geladen, CoTaskMemAlloc-Kopie
			SetInitNew(false);
		}
			// Dirty generell bei Open wieder zurücksetzen (siehe New())
		SetDirty(fDirty);
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}
STDMETHODIMP CProjectScript2::New (LPSTR *ppcMacroText)
{
	ASSERT (!m_strMacroName.IsEmpty());
		
	CString strDefaultScr (GetDefaultScript());
	if (strDefaultScr.IsEmpty()) return E_FAIL;
		
	*ppcMacroText = NULL;

	*ppcMacroText = (LPSTR)CoTaskMemAlloc(strDefaultScr.GetLength()+1);
	if (NULL == *ppcMacroText) return E_OUTOFMEMORY;

	strcpy(*ppcMacroText, strDefaultScr);

	SetDirty(true);// wenn schon geladen und es überschrieben werden soll
	
	return NOERROR;
}
STDMETHODIMP CProjectScript2::Save(LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)
{
	ASSERT(!m_strMacroName.IsEmpty());

	// wird kopiert, 
	// anderes SetProperty(... als bei Sub
	HRESULT hr = SetProperty(m_strMacroName, pText, hCode, lplpstr, uiCnt, dwSaveFlag);
	// Ist kopiert, 
	if (SUCCEEDED(hr))
	{// in  STREAM speichern	
		hr = SetScript (m_strMacroName);
		if (FAILED(hr)) return hr; 

		SetInitNew(false);
		SetDirty(false);
	// Speichern beendet, aber noch COMMIT()
		DEX_SetDirtyGeoDB(1);
	}

	return hr;
}
CString CProjectScript2::CorrectExtension(LPCSTR lpcstrFileName, DWORD dw)
{
	CString str = lpcstrFileName;
	if (dw & CC_CODE)
		return ::CorrectExtension (str, IDS_COMPLIEDSCRIPTEXT);
	else if (dw & CC_SCRIPT)
		return ::CorrectExtension (str, IDS_SCRIPTEXT);
	return '\0';
}
CString CSubObjFeatProjectScript::CorrectExtension(LPCSTR lpcstrFileName, DWORD dw)
{
	CString str = lpcstrFileName;
	if (dw & CC_CODE)
		return ::CorrectExtension (str, IDS_OEEXTCOMPILED);
	else if (dw & CC_SCRIPT)
		return ::CorrectExtension (str, IDS_OEEXT);
	return '\0';
}
CString CObjFeatProjectScript::CorrectExtension(LPCSTR lpcstrFileName, DWORD dw)
{
	CString str = lpcstrFileName;
	if (dw & CC_CODE)
		return ::CorrectExtension (str, IDS_OEEXTCOMPILED);
	else if (dw & CC_SCRIPT)
		return ::CorrectExtension (str, IDS_OEEXT);
	return '\0';
}
CString CSubFilterProjectScript::CorrectExtension(LPCSTR lpcstrFileName, DWORD dw)
{
	CString str = lpcstrFileName;
	if (dw & CC_CODE)
		return ::CorrectExtension (str, IDS_FILTEREXTCOMPILED);
	else if (dw & CC_SCRIPT)
		return ::CorrectExtension (str, IDS_FILTEREXT);
	return '\0';
}
CString CFilterProjectScript::CorrectExtension(LPCSTR lpcstrFileName, DWORD dw)
{
	CString str = lpcstrFileName;
	if (dw & CC_CODE)
		return ::CorrectExtension (str, IDS_OEEXTCOMPILED);
	else if (dw & CC_SCRIPT)
		return ::CorrectExtension (str, IDS_OEEXT);
	return '\0';
}
STDMETHODIMP CProjectScript2::SaveAs (LPCSTR lpcstrFileName, LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)	// Script unter neuem Namen speichern
{
	ASSERT(lpcstrFileName);
	CString str = CorrectExtension (lpcstrFileName, dwSaveFlag);

	HRESULT hr = SaveAsFromDisc(str, dwSaveFlag);
	if (E_UNEXPECTED == hr) {
		hr = SaveAsFromDebugger(str, pText, hCode, lplpstr, uiCnt, dwSaveFlag);
	}

	return hr;
}

STDMETHODIMP CProjectScript2::Delete ()
{// Wird gelöscht, muß auch deinstalliert werden
	HRESULT hr = RemoveInstall (m_strMacroName);
	if (FAILED(hr)) return hr;
	// Objekt, Stream, Info löschen
	hr = Delete (m_strMacroName);
	if (FAILED(hr)) return hr; 
	// Wenn nicht neues Script, dann TRiAS-Projekt dirty setzen
	if (false == GetInitNew()) 
		// Speichern beendet, aber noch COMMIT()
		DEX_SetDirtyGeoDB(1);
	// Eintrag in Tree löschen
	((ITreeItem *)this) -> Release();
	return hr;
}

STDMETHODIMP CProjectScript2::Rename (LPCSTR lpcstrNewName) 
{ 	
	ASSERT(lpcstrNewName);
	if (NULL == lpcstrNewName) return E_POINTER;

	HRESULT hr = NOERROR;
	USES_CONVERSION;
	try {
	// Objekt an sich umbenennen, wenns ein neuer Name ist
		if (strcmp (m_strMacroName, lpcstrNewName))
		{
			THROW_FAILED_HRESULT(GetObjManagement() -> RenameObject (A2OLE(m_strMacroName), A2OLE(lpcstrNewName)));
		}

	// Streaminfo umbenennen
		if (!GetInitNew()) {
		// nicht Abgespieherter (Neuer) hat noch keine Streaminfo
			THROW_FAILED_HRESULT(GetStreamInfo() -> Rename (A2OLE(m_strMacroName), A2OLE(lpcstrNewName)));		
			DEX_SetDirtyGeoDB(1); // TRiAS_Projekt nun dirty
		}
		m_strMacroName = lpcstrNewName;
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}	
	return hr;
}

STDMETHODIMP_(int) CProjectScript2::AskSaveChanges (HWND hWnd, LPCSTR lpcstrNext)
{// wenn nicht Dirty oder der nächste zu Öffnende er selbst, 
// nicht nach speichern fragen 
	if (!GetDirty() || (NULL != lpcstrNext && m_strMacroName == lpcstrNext)) return 0;

	CString strPrompt, strTemplate, strCaption;
	char Prompt[_MAX_PATH];

	strCaption = GetDefaultName(IDS_LONGCLASSNAME);

	if (m_strMacroName.IsEmpty()) 
	{
		strTemplate = GetDefaultName(IDS_SAVEPROMPTUNTITLED);
		strcpy (Prompt, strTemplate);
	} 
	else 
	{
		strTemplate = GetDefaultName(IDS_SAVEPROMPT);
		wsprintf (Prompt, strTemplate, m_strMacroName);
	}

	return ::MessageBox(hWnd, Prompt, strCaption, MB_YESNOCANCEL | MB_TASKMODAL);
}

STDMETHODIMP CProjectScript2::GetCode(ebHCODE *phCode)
{
	return CopyCodeMember(phCode);
}
STDMETHODIMP CProjectScript2::SetCode(ebHCODE hCode)
{
	return CopyCode(hCode);
}
HRESULT CProjectScript2::Delete (LPCSTR lpcstr)
{
	USES_CONVERSION;
	GetStreamInfo() -> Set (A2OLE(lpcstr), 0);
	GetObjManagement() -> DelObject (A2OLE(lpcstr));
	return S_OK;
}

////////////////////////////////////////////////////////////////////////////////
// CProjectScript2 protected
HRESULT CProjectScript2::CopyCode(ebHCODE hCode)
{
	if (m_hCode) CoTaskMemFree(m_hCode); m_hCode = NULL;

	if (NULL == hCode) return S_FALSE;

	UINT uiSize = 0;
	LPVOID lpCodeNew = NULL;
	LPVOID lpCode = NULL;

	try 
	{
		uiSize = ebCode_GetSize(hCode);
		if (0 == uiSize) _com_issue_error(E_FAIL);

		lpCodeNew = CoTaskMemAlloc (uiSize);
		if (NULL == lpCodeNew) _com_issue_error(E_OUTOFMEMORY);

		lpCode = ebCode_GetPointer(hCode);
		if (NULL == lpCode) _com_issue_error(E_OUTOFMEMORY);

		memcpy(lpCodeNew, lpCode, uiSize);

		m_hCode = ebCode_Create(lpCodeNew);
		if (NULL == m_hCode) _com_issue_error(E_HANDLE);
	} 
	catch (_com_error &e)
	{
		if (lpCodeNew) CoTaskMemFree(lpCodeNew);
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CProjectScript2::CopyCodeMember(ebHCODE *phCode)
{// Noch nicht übergeben worden, kein FEHLER
	if (NULL == m_hCode) return S_FALSE;

	UINT uiSize = 0;
	LPVOID lpCodeNew = NULL;
	LPVOID lpCode = NULL;

	try 
	{
		uiSize = ebCode_GetSize(m_hCode);
		if (0 == uiSize) _com_issue_error(E_FAIL);

		lpCodeNew = CoTaskMemAlloc (uiSize);
		if (NULL == lpCodeNew) _com_issue_error(E_OUTOFMEMORY);

		lpCode = ebCode_GetPointer(m_hCode);
		if (NULL == lpCode) _com_issue_error(E_OUTOFMEMORY);

		memcpy(lpCodeNew, lpCode, uiSize);

		*phCode = ebCode_Create(lpCodeNew);
		if (NULL == *phCode) _com_issue_error(E_HANDLE);
	} 
	catch (_com_error &e)
	{
		if (lpCodeNew) CoTaskMemFree(lpCodeNew);
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CProjectScript2::RemoveInstall (LPCSTR lpcstr)
{
	if (GetInitNew()) return S_FALSE;

	USES_CONVERSION;

	HRESULT hr = S_OK;

	try
	{
	WUnknown IU;

		THROW_FAILED_HRESULT(GetObjManagement() -> GetObject(A2OLE(lpcstr), IU.ppi()));

	// kein ObjektPropertyScript, Info geben lassen
	WAddScriptProperty IASP (IU); // throw QI_Ex...
	DWORD dwInfo = 0;

		GetStreamInfo() -> Get (A2OLE(lpcstr), &dwInfo);
	
	// Sind Objekteigenschaften überhaupt installiert ?
		if (!(dwInfo & OBJFEAT_INSTALLED)) 
			_com_issue_error(S_FALSE);
	
	// Ident geben lassen
	DWORD dwID = 0;
	
		THROW_FAILED_HRESULT(IASP -> GetCooky(&dwID));
		if (dwID == 0) _com_issue_error(E_UNEXPECTED);	// dwID muß an dieser Stelle != 0 sein

	// RunThread -> EndProperty()
	// immer deinstallieren !!!
		IASP -> Uninstall();

	////////////////////////////////////////////
	// Deinstallieren			
		g_pBSE -> RemovePropertyFunction (dwID);

	// Ident für nächstes Install zurücksetzen
		THROW_FAILED_HRESULT(IASP -> SetCooky(0));

	// StreamInfo zurücksetzen
		dwInfo &= OBJFEAT_UNINSTALLED;
		hr = GetStreamInfo() -> Set (A2OLE(lpcstr), dwInfo);
	}
	catch (_com_error &e)
	{
		m_fRemovedInstall = false;
		hr = _COM_ERROR(e);
		if (E_NOINTERFACE == hr) 
			hr = S_FALSE; // Kein Fehler, WEITERmachen
	}

	if (S_OK == hr) m_fRemovedInstall = true;

	return hr;
}

HRESULT CProjectScript2::Install (LPCSTR lpcstr)
{
	if (GetInitNew() || !m_fRemovedInstall) return S_FALSE;

	USES_CONVERSION;

HRESULT hr = NOERROR;

	try	{
	WUnknown IU;

		THROW_FAILED_HRESULT(GetObjManagement() -> GetObject(A2OLE(lpcstr), IU.ppi()));

	// kein ObjektPropertyScript, RAUS
	WAddScriptProperty IASP (IU); // throw QI_Ex...
	
	// Info geben lassen
	// Sind diese Objekteigenschaften schon installiert ?
	DWORD dwInfo = 0;
	
		THROW_FAILED_HRESULT(GetStreamInfo() -> Get (A2OLE(lpcstr), &dwInfo));
		if (dwInfo & OBJFEAT_INSTALLED) 
			_com_issue_error(S_FALSE);		

	// Ident geben lassen
	// dwID muß an dieser Stelle == 0 sein
	DWORD dwID = 0;

		THROW_FAILED_HRESULT(IASP -> GetCooky(&dwID));
		if (dwID != 0) _com_issue_error(E_UNEXPECTED);

	// RunThread -> BeginProperty(), Laufzeifehler RAUS
	// bei NOTIMPL trotzdem installieren
		hr = IASP -> Install();
		if (FAILED(hr) && hr != E_NOTIMPL) 
			_com_issue_error(S_FALSE);	// nur S_FALSE zurück, damit Save() erolgreich abgeschlossen werden kann

	////////////////////////////////////////////
	// Installieren			
	WObjectProperty IOP = IU;
	
		dwID = g_pBSE -> AddPropertyFunction (IOP);
		if (0 == dwID) _com_issue_error(E_UNEXPECTED);

	// Ident für Uninstall setzen
		THROW_FAILED_HRESULT(IASP -> SetCooky(dwID));

	// StreamInfo setzen
		dwInfo |= OBJFEAT_INSTALLED;
		hr = GetStreamInfo() -> Set (A2OLE(lpcstr), dwInfo);
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
		if (E_NOINTERFACE == hr) 
			hr = S_FALSE; // Kein Fehler, WEITERmachen
	}

	m_fRemovedInstall = false;
	return hr;
}

HRESULT CProjectScript2::SetProperty(LPCSTR lpcstr, LPCSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)
{
	ASSERT(NULL != pText || NULL != hCode || (dwSaveFlag & CC_RELATEDSCRIPTS));

	USES_CONVERSION;

	///////////////////////////////////////////////////////////////////
	// SPEICHERN

	HRESULT hr = NOERROR;
	// nur	RELATED SPEICHERN
	HRESULT hr1 = SetPropertyRelated(lpcstr, lplpstr, uiCnt, dwSaveFlag);
	if (SUCCEEDED(hr1)) return hr1;

	ebSaveStruct SS;
	memset(&SS, 0, sizeof(ebSaveStruct));
	try
	{	//	ALLES SPEICHERN
		// Objekt geben lesen
		WUnknown IU;
		THROW_FAILED_HRESULT(GetObjManagement() -> GetObject(A2OLE(lpcstr), IU.ppi()));

		dwSaveFlag |= SUPERITEM;
		SS.dwSaveFlag = dwSaveFlag; 

		if (NULL != pText && (dwSaveFlag & CC_SCRIPT)) 
			SS.pText = (LPSTR)pText;
		if (NULL != hCode && (dwSaveFlag & CC_CODE))
			SS.hCode = hCode;
		if (uiCnt) {
			SS.uiCntRelScripts = uiCnt;
			SS.lplpstrRelScripts = lplpstr;
		}
		if (dwSaveFlag & CC_EXPORTALL)
		{
			SS.pText = (LPSTR)pText;
			SetMan(lpcstr);
		}
		// Erstmal Objecteigenschaften deinstallieren
		THROW_FAILED_HRESULT(RemoveInstall (lpcstr));
		// Streaminfo setzen
		WScriptProperty IScriptProperty(IU);
		THROW_FAILED_HRESULT(GetStreamInfo() -> Set (A2OLE(lpcstr), dwSaveFlag));
		// Scriptprops etzen
		THROW_FAILED_HRESULT(IScriptProperty -> Set(&SS));
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}	
	return hr;
}

HRESULT CProjectScript2::SetPropertyRelated(LPCSTR lpcstr, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)
{
	ASSERT(lpcstr);
	// nur	RELATED
	if (!(dwSaveFlag & CC_RELATEDSCRIPTS)) return E_UNEXPECTED;

	HRESULT hr = NOERROR;

	USES_CONVERSION;

	try
	{
	WUnknown IU;

	// Objekt geben lesen
		THROW_FAILED_HRESULT(GetObjManagement() -> GetObject(A2OLE(lpcstr), IU.ppi()));	
		
	ebSaveStruct SS;

		memset(&SS, 0, sizeof(ebSaveStruct));
		SS.dwSaveFlag = dwSaveFlag; 
		SS.uiCntRelScripts = uiCnt;
		SS.lplpstrRelScripts = lplpstr;

		THROW_FAILED_HRESULT(WScriptProperty(IU) -> Set(&SS));		
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}

	return hr;
}

HRESULT CProjectScript2::GetProperty (LPCSTR lpcstr, LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplpstr, UINT & uiCnt)
{
	ASSERT(ppcMacroText);
	ASSERT(phCode);
	ASSERT(lplplpstr);
	
	*phCode = NULL;
	*ppcMacroText = NULL;
	*lplplpstr = NULL;
	uiCnt = 0;

	HRESULT hr = NOERROR;

	ebSaveStruct SS;
	memset(&SS, 0, sizeof(ebSaveStruct));

	USES_CONVERSION;
	try
	{// Objekt geben lesen
		WUnknown IU;
		THROW_FAILED_HRESULT(GetObjManagement() -> GetObject(A2OLE(lpcstr), IU.ppi()));	
		// Kopieren der Daten
		WScriptProperty ISP(IU);
		THROW_FAILED_HRESULT(ISP -> Get(&SS));  

		if (SS.hCode) *phCode = SS.hCode;
		if (SS.pText) *ppcMacroText = SS.pText;
		if (SS.uiCntRelScripts) {
			uiCnt = SS.uiCntRelScripts;
			*lplplpstr = SS.lplpstrRelScripts;
		}
	}
	catch (_com_error& e)
	{// FEHLER
		if (SS.hCode) CoTaskMemFree(SS.hCode); SS.hCode = NULL;
		if (SS.pText) CoTaskMemFree(SS.pText); SS.pText = NULL;
		MEMFREE(SS.lplpstrRelScripts, SS.uiCntRelScripts);
		hr = _COM_ERROR(e);
	}
	return hr;
}
 
HRESULT CProjectScript2::GetTextsAndCreateNew(LPCSTR lpcstrImportName, LPSTR *lplpstrRelScriptNames, UINT uiCnt)
{
	ASSERT(lpcstrImportName);
	if (NULL == lpcstrImportName) return E_POINTER;

	HRESULT hr = NOERROR;
	LPSTR *lplpstrRelTexts = NULL;
	UINT  uiTexts = 0;
	CComObject<CSubProjectScript> *pSub = NULL;

	LPSTR lpstrDummyText = NULL;
	ebHCODE hDummyCode = NULL;
	LPSTR *lplpstrDummyRel = NULL;
	UINT uiDummyCnt = 0;

	ebHCODE hCompiledCode = NULL;

	USES_CONVERSION;
	try 
	{// Wenn ein InportExportProject, Texte geben lassen
		WUnknown IU;
		THROW_FAILED_HRESULT(GetObjManagement() ->  GetObject(A2OLE(lpcstrImportName), IU.ppi()));
		WExportImportProject IEIP = IU;
		THROW_FAILED_HRESULT(IEIP -> GetTexts(&lplpstrRelTexts, uiTexts));

		if (uiTexts != uiCnt) _com_issue_error(E_UNEXPECTED); 

		for (UINT ui = 0; ui < uiCnt; ui++)
		{
			lplpstrDummyRel = NULL;
			uiDummyCnt = 0;
			
			// Name Text geben lassen
			LPSTR lpstrName = lplpstrRelScriptNames[ui];
			if (NULL == lpstrName) _com_issue_error(E_INVALIDARG);
			LPSTR lpstrText = lplpstrRelTexts[ui];
			if (NULL == lpstrText) _com_issue_error(E_INVALIDARG);
			
			// Nun neue Items erzeugen
			pSub = new CComObject<CSubProjectScript>;
			pSub -> AddRef();
			// Initialisieren de NEU Erzeugten
			THROW_FAILED_HRESULT(pSub->Init(GetObjManagement(), GetStreamInfo(), CLSID_Script));			
			WBSProperty IBSP = pSub;
			IBSP -> SetScriptName(lpstrName);
			
			// eigentliches Item geben lassen
			WObjManHelper IOMH = pSub;
			IOMH -> SetParentName(m_strMacroName);
			THROW_FAILED_HRESULT(IOMH -> Open(&lpstrDummyText, &hDummyCode, &lplpstrDummyRel, uiDummyCnt));	// Text, Code, StringListe geben lassen
			// Nur Text vorhanden, dann kompilieren
			Compile	(lpstrText, &hCompiledCode);
			// auf Platte schreiben (Streamen)
			DWORD dwSaveFlag = hCompiledCode ? CC_CODE|CC_SCRIPT : CC_SCRIPT;
			
			/////////////////////////////////////////////////////////////////////////
			// GEFAHR, es werden natürlich alle ProjektStreams mit lpstrText überschrieben !!!
			THROW_FAILED_HRESULT (IOMH -> Save(lpstrText, hCompiledCode, NULL, 0, dwSaveFlag));
			// wieder freigeben
			COTASKMEMFREE(lpstrDummyText);
			COTASKMEMFREE(hDummyCode);
			MEMFREE(lplpstrDummyRel, uiDummyCnt);
			if (hCompiledCode) ebCode_Free(hCompiledCode); hCompiledCode = NULL;
			RELEASE(pSub);
		}		
	} 
	catch(_com_error& e) 
	{
		hr = _COM_ERROR(e);
		if (E_NOINTERFACE == hr)
			hr = S_OK;
	}
	catch(bad_alloc) 
	{
		hr = E_OUTOFMEMORY;
	}
	if (hCompiledCode) ebCode_Free(hCompiledCode); hCompiledCode = NULL;
	COTASKMEMFREE(lpstrDummyText);
	COTASKMEMFREE(hDummyCode);
	MEMFREE(lplpstrDummyRel, uiDummyCnt);
	RELEASE(pSub);		
	MEMFREE(lplpstrRelTexts, uiTexts);		
	return hr;
}

HRESULT CProjectScript2::SetMan(LPCSTR lpcstrImportName)
{
	ASSERT(lpcstrImportName);
	if (NULL == lpcstrImportName) return E_POINTER;

	HRESULT hr = NOERROR;
	USES_CONVERSION;
	try 
	{// Wenn ein InportExportProject, Texte geben lassen
		WUnknown IU;
		THROW_FAILED_HRESULT(GetObjManagement() ->  GetObject(A2OLE(lpcstrImportName), IU.ppi()));
		WExportImportProject IEIP = IU;
		IEIP -> SetManagement(GetObjManagement());
	} 
	catch(_com_error& e) 
	{
		hr = _COM_ERROR(e);
		if (E_NOINTERFACE == hr)
			hr = S_OK;
	}
	catch(bad_alloc) 
	{
		hr = E_OUTOFMEMORY;
	}
	return hr;
}

HRESULT CProjectScript2::SetScript (LPCSTR lpcstr) 
{
	USES_CONVERSION;
	WUnknown IU;
	// Objekt geben lesen bzw. überprüfen, ob schon erzeugt (Stream geöffnet bzw. File geöffnet ?)
	HRESULT hr = GetObjManagement() -> GetObject(A2OLE(lpcstr), IU.ppi());
	if (SUCCEEDED(hr)) 
	{// Persistenz erzeugen (auf Platte)
		hr = GetObjManagement() -> SaveObject (A2OLE(lpcstr));
		if (FAILED(hr)) return hr;
		// Objecteigenschaften eventuell wieder installieren, 
		// wenn Speichern erfolgreich und diese vorher deinstalliert wurden
		hr = Install (lpcstr);
		// nicht implementiert bzw. Laufzeifehler
		if (E_NOTIMPL == hr || E_ABORT == hr) hr = S_FALSE;
	}
	return hr;
}

// Nur Object instanzieren
HRESULT CProjectScript2::GetScript(LPCSTR lpcstrScriptName, REFIID riid, BOOL fCreateTemp)
{	
	USES_CONVERSION;
	// Objekt geben lesen
	WUnknown IU;
	HRESULT hr = GetObjManagement() -> GetObject(A2OLE(lpcstrScriptName), IU.ppi());		
	if (FAILED(hr)) 
	{	// kein Objekt mit diesem Namen, GetObject FAILED
		// CoCreateInstance(...
		hr = GetObjManagement() -> CreateObject(riid, A2OLE(lpcstrScriptName), STGM_READWRITE, IU.ppi(), fCreateTemp);
		if (SUCCEEDED(hr))
		{
			hr = S_FALSE;
		}
	}
	// Wenn Objekt noch nicht geladen und nicht in SaveAs (File laden)
	IUnknown *pIU = NULL;
	if (pIU == m_IUnknown && m_strMacroName == lpcstrScriptName)
	{// Query...
		m_IUnknown = IU;
	}

	return hr;
}

HRESULT CProjectScript2::CopyTo(REFIID riid, LPCSTR lpcstrFileName, LPCSTR lpcstrMacroName, LPSTR *ppMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui)
{
	HRESULT hr = NOERROR;

	*lplplp = NULL;
	ui = 0;
	*ppMacroText = NULL;
	*phCode = NULL;

	try 
	{
		DWORD dwSaveFlag = 0;
	//////////////////////////
	// Erstmal File öffnen
		THROW_FAILED_HRESULT(GetScript (lpcstrFileName, riid, true));
		// Text, Code, ... von File geben lassen
		THROW_FAILED_HRESULT(GetProperty (lpcstrFileName, ppMacroText, phCode, lplplp, ui));
	//////////////////////////
	// Storagescript erzeugen
		THROW_FAILED_HRESULT(GetScript(lpcstrMacroName, CLSID_Script, false));

		if (*ppMacroText) dwSaveFlag = CC_SCRIPT;
		if (*phCode) dwSaveFlag |= CC_CODE;
		// File nach Storage kopieren also abspeichern
		// anderes SetProperty(... als bei Super
		THROW_FAILED_HRESULT(SetProperty(lpcstrMacroName, *ppMacroText, *phCode, *lplplp, ui, dwSaveFlag));	
		THROW_FAILED_HRESULT(SetScript (lpcstrMacroName));
	
		// Für Importall() !!!			
		THROW_FAILED_HRESULT(GetTextsAndCreateNew(lpcstrFileName, *lplplp, ui));

		// File wieder zumachen, freigeben	
		Delete (lpcstrFileName);
	}
	catch (_com_error& e)
	{
		if (*phCode) CoTaskMemFree(*phCode); *phCode = NULL;
		if (*ppMacroText) CoTaskMemFree(*ppMacroText); *ppMacroText = NULL;
		MEMFREE(*lplplp, ui);
		
		Delete (lpcstrFileName);
		hr = _COM_ERROR(e);
	}
	return hr;
}

HRESULT CProjectScript2::SaveAsFromDisc (LPCSTR lpcstrFileName, DWORD dwSaveFlag)	// Script unter neuem Namen speichern
{
	if (!(dwSaveFlag & GETFROMDISC)) return E_UNEXPECTED;

	// Speichern nach neues oder geöffnetes File
	LPSTR lpstrText = NULL;
	ebHCODE hCode = 0;
	LPSTR *lplpstrRel = NULL;
	UINT ui = 0;
	HRESULT hr = NOERROR;

	try
	{
		// Objekt erzeugen/geben lassen, File laden
		if (dwSaveFlag & CC_EXPORTALL) // ExportAll !!!
		{
			THROW_FAILED_HRESULT(GetScript(lpcstrFileName, CLSID_ExportImportProject, true));// nur temporär
			// Hier den Code und den Text des Selektierten geben lassen !!!
			THROW_FAILED_HRESULT(GetProperty (m_strMacroName, &lpstrText, &hCode, &lplpstrRel, ui));
			// anderes SetProperty(... als bei Sub
			THROW_FAILED_HRESULT(SetProperty(lpcstrFileName, lpstrText, hCode, lplpstrRel, ui, dwSaveFlag));	
		}
		else
		{
			THROW_FAILED_HRESULT(GetScript(lpcstrFileName, CLSID_FileScript, true));// nur temporär
			// Hier den Code und den Text des Selektierten geben lassen !!!
			THROW_FAILED_HRESULT(GetProperty (m_strMacroName, &lpstrText, &hCode, &lplpstrRel, ui));
			// nur Text abspeichern
			// anderes SetProperty(... als bei Sub
			THROW_FAILED_HRESULT(SetProperty(lpcstrFileName, lpstrText, hCode, NULL, 0, dwSaveFlag));	
		}
		//Save Properties dieses Objektes in anderes File
		THROW_FAILED_HRESULT(SetScript (lpcstrFileName));
		// auf jeden Fall wieder löschen, Objekt an sich 
		THROW_FAILED_HRESULT(Delete (lpcstrFileName));
	}
	catch (_com_error& e)
	{
		Delete (lpcstrFileName);
		hr = _COM_ERROR(e);
	}
	COTASKMEMFREE(lpstrText);
	COTASKMEMFREE(hCode);
	MEMFREE(lplpstrRel, ui);
	return hr;
}
	
HRESULT CProjectScript2::SaveAsFromDebugger (LPCSTR lpcstrFileName, LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)	// Script unter neuem Namen speichern
{
	if (dwSaveFlag & GETFROMDISC) return E_UNEXPECTED;

	HRESULT hr = NOERROR;
	try 
	{// Objekt erzeugen/geben lassen, File laden
		if (dwSaveFlag & CC_EXPORTALL) // ExportAll !!!
		{
			THROW_FAILED_HRESULT(GetScript(lpcstrFileName, CLSID_ExportImportProject, true));// nur temporär
			// anderes SetProperty(... als bei Sub
			THROW_FAILED_HRESULT(SetProperty(lpcstrFileName, pText, hCode, lplpstr, uiCnt, dwSaveFlag));	
		}
		else
		{
			THROW_FAILED_HRESULT(GetScript(lpcstrFileName, CLSID_FileScript, true));// nur temporär
			// nur Text abspeichern
			// anderes SetProperty(... als bei Sub
			THROW_FAILED_HRESULT(SetProperty(lpcstrFileName, pText, hCode, NULL, 0, dwSaveFlag));	
		}
		//Save Properties dieses Objektes in anderes File
		THROW_FAILED_HRESULT(SetScript (lpcstrFileName));
		// auf jeden Fall wieder löschen, Objekt an sich 
		THROW_FAILED_HRESULT(Delete (lpcstrFileName));
	}
	catch (_com_error& e)
	{
		Delete (lpcstrFileName);
		hr = _COM_ERROR(e);
	}
	return hr;
}

STDMETHODIMP CProjectScript::GetSaveAsFilters(LPSTR *lplp)
{
	ASSERT(lplp);
	if (NULL == lplp) return E_POINTER;

	USES_CONVERSION;
	try
	{
		CString strFilters = GetDefaultName(IDS_SAVEASFILTERS);
		int iLen = strFilters.GetLength();
		if (0 == iLen) _com_issue_error(E_FAIL);
		LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

		strcpy(lpstr, strFilters);
		
		*lplp = lpstr;
	} 
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}
STDMETHODIMP CProjectScript::GetFileExt(LPSTR *lplp)
{
	ASSERT(lplp);
	if (NULL == lplp) return E_POINTER;

	USES_CONVERSION;
	try
	{
		CString strExt = GetDefaultName(IDS_SCRIPTEXT); 
		int iLen = strExt.GetLength();
		if (0 == iLen) _com_issue_error(E_FAIL);
		LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

		strcpy(lpstr, strExt);
		
		*lplp = lpstr;
	} 
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}

STDMETHODIMP CProjectScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,
										BOOL fSuper
										)
{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CFunctionScript> *pProjScript = NULL;
	// ProjectScript instanzieren
	try 
	{
		pProjScript = new CComObject<CFunctionScript>;
		WObjectManagement IOM;
		WStreamInfo IS;
		THROW_FAILED_HRESULT(GetGeneralScripts(IOM.ppi()));
		THROW_FAILED_HRESULT(GetInfoGeneralScripts(IS.ppi()));
		WObjManHelper IOMH = this;
		THROW_FAILED_HRESULT(pProjScript->Init(
										IOMH,
										IOM, 
										IS, 
										riid,
										lpcstrName,
										lpcstrDecl,
										lpcstrType,
										lpcstrParams,
										lpcstrComment
										));
		// Query
		WTreeItem IT = pProjScript;
		*pp = IT.detach();
	}
	catch (bad_alloc) 
	{
		return E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		DELETE_OBJ(pProjScript);
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CObjFeatProjectScript::GetSaveAsFilters(LPSTR *lplp)
{
	ASSERT(lplp);
	if (NULL == lplp) return E_POINTER;

	USES_CONVERSION;
	try
	{
		CString strFilters = GetDefaultName(IDS_SAVEASOEFILTERS);
		int iLen = strFilters.GetLength();
		if (0 == iLen) _com_issue_error(E_FAIL);
		LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

		strcpy(lpstr, strFilters);
		
		*lplp = lpstr;
	} 
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}
STDMETHODIMP CObjFeatProjectScript::GetFileExt(LPSTR *lplp)
{
	ASSERT(lplp);
	if (NULL == lplp) return E_POINTER;

	USES_CONVERSION;
	try
	{
		CString strExt = GetDefaultName(IDS_OEEXT); 
		int iLen = strExt.GetLength();
		if (0 == iLen) _com_issue_error(E_FAIL);
		LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

		strcpy(lpstr, strExt);
		
		*lplp = lpstr;
	} 
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}

HRESULT CObjFeatProjectScript::CopyTo(REFIID riid, LPCSTR lpcstrFileName, LPCSTR lpcstrMacroName, LPSTR *ppMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui)
{
	HRESULT hr = NOERROR;

	*lplplp = NULL;
	ui = 0;
	*ppMacroText = NULL;
	*phCode = NULL;

	try 
	{
		DWORD dwSaveFlag = 0;
	//////////////////////////
	// Erstmal File öffnen
		THROW_FAILED_HRESULT(GetScript (lpcstrFileName, riid, true));
		// Text, Code, ... von File geben lassen
		THROW_FAILED_HRESULT(GetProperty (lpcstrFileName, ppMacroText, phCode, lplplp, ui));
	//////////////////////////
	// Storagescript erzeugen
		THROW_FAILED_HRESULT(GetScript(lpcstrMacroName, CLSID_CreateObjectFeatureScript, false));

		if (*ppMacroText) dwSaveFlag = CC_SCRIPT;
		if (*phCode) dwSaveFlag |= CC_CODE;
		// File nach Storage kopieren also abspeichern
		// anderes SetProperty(... als bei Super
		THROW_FAILED_HRESULT(SetProperty(lpcstrMacroName, *ppMacroText, *phCode, *lplplp, ui, dwSaveFlag));	
		THROW_FAILED_HRESULT(SetScript (lpcstrMacroName));
	
		// Für Importall() !!!			
		THROW_FAILED_HRESULT(GetTextsAndCreateNew(lpcstrFileName, *lplplp, ui));

		// File wieder zumachen, freigeben	
		Delete (lpcstrFileName);
	}
	catch (_com_error& e)
	{
		if (*phCode) CoTaskMemFree(*phCode); *phCode = NULL;
		if (*ppMacroText) CoTaskMemFree(*ppMacroText); *ppMacroText = NULL;
		MEMFREE(*lplplp, ui);
		
		Delete (lpcstrFileName);
		hr = _COM_ERROR(e);
	}
	return hr;
}
STDMETHODIMP CObjFeatProjectScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)
{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CFunctionScript> *pProjScript = NULL;
	// ProjectScript instanzieren
	try 
	{
		pProjScript = new CComObject<CFunctionScript>;
		WObjectManagement IOM;
		WStreamInfo IS;
		THROW_FAILED_HRESULT(GetObjFeatScripts(IOM.ppi()));
		THROW_FAILED_HRESULT(GetInfoObjFeatScripts(IS.ppi()));
		WObjManHelper IOMH = this;
		
		THROW_FAILED_HRESULT(pProjScript->Init(
										IOMH,
										IOM, 
										IS, 
										riid,
										lpcstrName,
										lpcstrDecl,
										lpcstrType,
										lpcstrParams,
										lpcstrComment
										));
		// Query
		WTreeItem IT = pProjScript;
		*pp = IT.detach();
	}
	catch (bad_alloc) 
	{
		return E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		DELETE_OBJ(pProjScript);
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CFilterProjectScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)
{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CFunctionScript> *pProjScript = NULL;
	// ProjectScript instanzieren
	try 
	{
		pProjScript = new CComObject<CFunctionScript>;
		WObjectManagement IOM;
		WStreamInfo IS;
		THROW_FAILED_HRESULT(GetFilterScripts(IOM.ppi()));
		THROW_FAILED_HRESULT(GetInfoFilterScripts(IS.ppi()));
		WObjManHelper IOMH = this;
		THROW_FAILED_HRESULT(pProjScript->Init(
										IOMH,
										IOM, 
										IS, 
										riid,
										lpcstrName,
										lpcstrDecl,
										lpcstrType,
										lpcstrParams,
										lpcstrComment		
										));
		// Query
		WTreeItem IT = pProjScript;
		*pp = IT.detach();
	}
	catch (bad_alloc) 
	{
		return E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		DELETE_OBJ(pProjScript);
		return _COM_ERROR(e);
	}
	return S_OK;
}


STDMETHODIMP CSubProjectScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)
{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CFunctionScript> *pProjScript = NULL;
	// ProjectScript instanzieren
	try 
	{
		pProjScript = new CComObject<CFunctionScript>;
		WObjectManagement IOM;
		WStreamInfo IS;
		THROW_FAILED_HRESULT(GetGeneralScripts(IOM.ppi()));
		THROW_FAILED_HRESULT(GetInfoGeneralScripts(IS.ppi()));
		// Initialisieren	
		WObjManHelper IOMH = this;
		THROW_FAILED_HRESULT(pProjScript->Init(
										IOMH,
										IOM, 
										IS, 
										riid,
										lpcstrName,
										lpcstrDecl,
										lpcstrType,
										lpcstrParams,		
										lpcstrComment		
										));
		// Query
		WTreeItem IT = pProjScript;
		*pp = IT.detach();
	}
	catch (bad_alloc) 
	{
		return E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		DELETE_OBJ(pProjScript);
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CSubObjFeatProjectScript::GetSaveAsFilters(LPSTR *lplp)
{
	ASSERT(lplp);
	if (NULL == lplp) return E_POINTER;

	USES_CONVERSION;
	try
	{
		CString strFilters = GetDefaultName(IDS_SAVEASOEFILTERS);
		int iLen = strFilters.GetLength();
		if (0 == iLen) _com_issue_error(E_FAIL);
		LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

		strcpy(lpstr, strFilters);
		
		*lplp = lpstr;
	} 
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}
STDMETHODIMP CSubObjFeatProjectScript::GetFileExt(LPSTR *lplp)
{
	ASSERT(lplp);
	if (NULL == lplp) return E_POINTER;

	USES_CONVERSION;
	try
	{
		CString strExt = GetDefaultName(IDS_OEEXT); 
		int iLen = strExt.GetLength();
		if (0 == iLen) _com_issue_error(E_FAIL);
		LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

		strcpy(lpstr, strExt);
		
		*lplp = lpstr;
	} 
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}
HRESULT CSubObjFeatProjectScript::CopyTo(REFIID riid, LPCSTR lpcstrFileName, LPCSTR lpcstrMacroName, LPSTR *ppMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui)
{
	HRESULT hr = NOERROR;

	*lplplp = NULL;
	ui = 0;
	*ppMacroText = NULL;
	*phCode = NULL;

	try 
	{
		DWORD dwSaveFlag = 0;
	//////////////////////////
	// Erstmal File öffnen
		THROW_FAILED_HRESULT(GetScript (lpcstrFileName, riid, true));
		// Text, Code, ... von File geben lassen
		THROW_FAILED_HRESULT(GetProperty (lpcstrFileName, ppMacroText, phCode, lplplp, ui));
	//////////////////////////
	// Storagescript erzeugen
		THROW_FAILED_HRESULT(GetScript(lpcstrMacroName, CLSID_CreateObjectFeatureScript, false));

		if (*ppMacroText) dwSaveFlag = CC_SCRIPT;
		if (*phCode) dwSaveFlag |= CC_CODE;
		// File nach Storage kopieren also abspeichern
		// anderes SetProperty(... als bei Super
		THROW_FAILED_HRESULT(SetProperty(lpcstrMacroName, *ppMacroText, *phCode, *lplplp, ui, dwSaveFlag));	
		THROW_FAILED_HRESULT(SetScript (lpcstrMacroName));
	
		// Für Importall() !!!			
		THROW_FAILED_HRESULT(GetTextsAndCreateNew(lpcstrFileName, *lplplp, ui));

		// File wieder zumachen, freigeben	
		Delete (lpcstrFileName);
	}
	catch (_com_error& e)
	{
		if (*phCode) CoTaskMemFree(*phCode); *phCode = NULL;
		if (*ppMacroText) CoTaskMemFree(*ppMacroText); *ppMacroText = NULL;
		MEMFREE(*lplplp, ui);
		
		Delete (lpcstrFileName);
		hr = _COM_ERROR(e);
	}
	return hr;
}
STDMETHODIMP CSubObjFeatProjectScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)
{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CFunctionScript> *pProjScript = NULL;
	// ProjectScript instanzieren
	try 
	{
		pProjScript = new CComObject<CFunctionScript>;
		WObjectManagement IOM;
		WStreamInfo IS;
		THROW_FAILED_HRESULT(GetObjFeatScripts(IOM.ppi()));
		THROW_FAILED_HRESULT(GetInfoObjFeatScripts(IS.ppi()));
		WObjManHelper IOMH = this;
		THROW_FAILED_HRESULT(pProjScript->Init(
										IOMH,
										IOM, 
										IS, 
										riid,
										lpcstrName,
										lpcstrDecl,
										lpcstrType,
										lpcstrParams,		
										lpcstrComment		
										));
		WTreeItem IT = pProjScript;
		*pp = IT.detach();
	}
	catch (bad_alloc) 
	{
		return E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		DELETE_OBJ(pProjScript);
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CSubFilterProjectScript::GetSaveAsFilters(LPSTR *lplp)
{
	ASSERT(lplp);
	if (NULL == lplp) return E_POINTER;

	USES_CONVERSION;
	try
	{
		CString strFilters = GetDefaultName(IDS_SAVEASFILTERFILTER);
		int iLen = strFilters.GetLength();
		if (0 == iLen) _com_issue_error(E_FAIL);
		LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

		strcpy(lpstr, strFilters);
		
		*lplp = lpstr;
	} 
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}
STDMETHODIMP CSubFilterProjectScript::GetFileExt(LPSTR *lplp)
{
	ASSERT(lplp);
	if (NULL == lplp) return E_POINTER;

	USES_CONVERSION;
	try
	{
		CString strExt = GetDefaultName(IDS_FILTEREXT); 
		int iLen = strExt.GetLength();
		if (0 == iLen) _com_issue_error(E_FAIL);
		LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

		strcpy(lpstr, strExt);
		
		*lplp = lpstr;
	} 
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}

STDMETHODIMP CSubFilterProjectScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)
{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CFunctionScript> *pProjScript = NULL;
	// ProjectScript instanzieren
	try 
	{
		pProjScript = new CComObject<CFunctionScript>;
		WObjectManagement IOM;
		WStreamInfo IS;
		THROW_FAILED_HRESULT(GetFilterScripts(IOM.ppi()));
		THROW_FAILED_HRESULT(GetInfoFilterScripts(IS.ppi()));
		WObjManHelper IOMH = this;
		THROW_FAILED_HRESULT(pProjScript->Init(
										IOMH,
										IOM, 
										IS, 
										riid,
										lpcstrName,
										lpcstrDecl,
										lpcstrType,
										lpcstrParams,		
										lpcstrComment		
										));
		// Query
		WTreeItem IT = pProjScript;
		*pp = IT.detach();
	}
	catch (bad_alloc) 
	{
		return E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		DELETE_OBJ(pProjScript);
		return _COM_ERROR(e);
	}
	return S_OK;
}

STDMETHODIMP CSubProjectScript::New(LPSTR *ppcMacroText)
{
	ASSERT (!m_strMacroName.IsEmpty());

	CString strDefaultScr = GenerateDefaultMakroText();
	if (strDefaultScr.IsEmpty()) return E_FAIL;
	
	*ppcMacroText = NULL;
	*ppcMacroText = (LPSTR)CoTaskMemAlloc(strDefaultScr.GetLength()+1);
	if (NULL == *ppcMacroText) return E_OUTOFMEMORY;
	
	strcpy(*ppcMacroText, strDefaultScr);

	SetDirty(true);// wenn schon geladen und es überschrieben werden soll
	
	return NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////
// protected
HRESULT CSubProjectScript::SetProperty(LPCSTR lpcstr, LPCSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)
{
	ASSERT(lpcstr);
	ASSERT(NULL != pText || NULL != hCode);

	if (NULL == pText && NULL == hCode) return E_FAIL;

	HRESULT hr = NOERROR;

	USES_CONVERSION;

	try
	{
	WUnknown IU;

	// Objekt geben lesen
		THROW_FAILED_HRESULT(GetObjManagement() -> GetObject(A2OLE(lpcstr), IU.ppi()));
	
	ebSaveStruct SS;

		memset(&SS, 0, sizeof(ebSaveStruct));
		SS.dwSaveFlag = dwSaveFlag; 

		if (NULL != pText && (dwSaveFlag & CC_SCRIPT)) 
			SS.pText = (LPSTR)pText;
		if (NULL != hCode && (dwSaveFlag & CC_CODE))
			SS.hCode = hCode;

		THROW_FAILED_HRESULT(GetStreamInfo() -> Set (A2OLE(m_strMacroName), dwSaveFlag));
		THROW_FAILED_HRESULT(WScriptProperty(IU) -> Set(&SS));
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}
	
	return hr;
}


HRESULT CSubProjectScript::GetProperty (LPCSTR lpcstr, LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplpstr, UINT & uiCnt)
{
	ASSERT(ppcMacroText);
	ASSERT(phCode);
	ASSERT(lplplpstr);
	
	*phCode = NULL;
	*ppcMacroText = NULL;

	HRESULT hr = NOERROR;
	ebSaveStruct SS;
	memset(&SS, 0, sizeof(ebSaveStruct)); 

	USES_CONVERSION;	
	try
	{	// Objekt geben lesen
		WUnknown IU;		
		THROW_FAILED_HRESULT(GetObjManagement() -> GetObject(A2OLE(lpcstr), IU.ppi()));		
		/////////////////////////////////
		// Kopieren der Daten
		WScriptProperty ISP(IU);
		THROW_FAILED_HRESULT(ISP -> Get(&SS));  

		if (SS.hCode) *phCode = SS.hCode;
		if (SS.pText) *ppcMacroText = SS.pText;
	}
	catch (_com_error& e)
	{// FEHLER
		COTASKMEMFREE(SS.hCode);
		COTASKMEMFREE(SS.pText);
		hr = _COM_ERROR(e);
	}
	return hr;
}

CString CSubProjectScript::GenerateDefaultMakroText()
{
	CString strDefault = GetDefaultName(IDS_SUBDEFAULTSCRIPT);
	CString strText, strName, strContainerText, str;

	LPSTR pText = NULL;
	TRY {
		pText = strText.GetBuffer (_MAX_PATH);
		if (pText == NULL) return strText;
	}
	CATCH (CMemoryException, e) {
		return 	strText;
	}                  
	END_CATCH

	strName = m_strMacroName;
	strContainerText = m_strParentName;
	str = GetDefaultName(IDS_GENCOMMENTSUB);

	ASSERT(!strName.IsEmpty());
	ASSERT(!strContainerText.IsEmpty());

	wsprintf (pText, strDefault, (LPCSTR)strContainerText, (LPCSTR)strName, g_cbNil, str);

	strText.ReleaseBuffer();

	return strText;
}

////////////////////////////////////////////////////////////////////////////
// ITreeItem_Methods CExternProjectScript
STDMETHODIMP CExternProjectScript::NewFunction (				
		LPCSTR lpcstrName, LPCSTR lpcstrDecl, LPCSTR lpcstrType, LPCSTR lpcstrParams, LPCSTR lpcstrComment, LPSTR *lplpstr
		)
{
	ASSERT(lplpstr);
	if (NULL == lplpstr) return E_POINTER;
	*lplpstr = NULL;

	CComObject<CFunctionScript> *pProjScript = NULL;
	HRESULT hr = NOERROR;
	try
	{
		pProjScript = new CComObject<CFunctionScript>;
		pProjScript  -> AddRef();
		WObjManHelper IOMH = this;
		THROW_FAILED_HRESULT(pProjScript->Init(
										IOMH,
										NULL, 
										NULL, 
										CLSID_NULL,
										lpcstrName,
										lpcstrDecl,
										lpcstrType,
										lpcstrParams,		
										lpcstrComment		
										));
		pProjScript -> SetParentName(m_strMacroName);
		THROW_FAILED_HRESULT(pProjScript -> New(lplpstr));
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	pProjScript  -> Release();
	return hr;
}
STDMETHODIMP CExternProjectScript::Open (LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui, BOOL fCreateTemp)
{
	ASSERT (!m_strMacroName.IsEmpty());

	*ppcMacroText = NULL;
	*phCode = NULL;
	*lplplp = NULL;
	ui = 0;

	HRESULT hr = GetScript (m_strMacroName, m_clsid, fCreateTemp);

	if (SUCCEEDED(hr))
	{ 
		hr = GetProperty (m_strMacroName, ppcMacroText, phCode, lplplp, ui);

		if (SUCCEEDED(hr)) 
		{// erfolgreich geladen
			SetInitNew(true);// diesen immer neu setzen
		}
	}
	
	return hr;
}

STDMETHODIMP CExternProjectScript::New	(LPSTR *ppcMacroText)
{
// Ist von CSubPro... abgeleitet, als Default muß jedoch SUPER geladen werden
	HRESULT hr = CProjectScript2::New(ppcMacroText);
	if (SUCCEEDED(hr)) 
	{// erfolgreich geladen
		SetInitNew(true);// diesen immer neu setzen
		SetDirty(false);// Wird in CProjectScript2::New() true gesetzt. Stimmt dort auch, da alter Text überschrieben wird.
						// Bei externen wird jedoch eine ganz neue Datei erstellt, die nicht dirty ist.
	}

	return hr;
}

STDMETHODIMP CExternProjectScript::SaveAs (LPCSTR lpcstrScriptName, LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)
{
	ASSERT(lpcstrScriptName);
	if (NULL == lpcstrScriptName) return E_POINTER;

	USES_CONVERSION;
	try
	{	
		HRESULT hr = NOERROR;
		// Bei "Unter gleichem Namen" nur Save()
		if (lpcstrScriptName == m_strMacroName)
		{
			hr = Save(pText, hCode, lplpstr, uiCnt, dwSaveFlag);
			// gleich RAUS
			_com_issue_error(hr);
		}
		// Unter Umständen (bei neuem Externen), noch keine Datei geladen
		hr = GetScript(lpcstrScriptName, CLSID_FileScript, true);
		if (FAILED(hr)) _com_issue_error(hr);
		// Altes File aus Liste !!!
		GetObjManagement() -> DelObject (A2OLE(m_strMacroName));
		// Neuen Namen zuweisen !!!
		SetScriptName(lpcstrScriptName);
		// Unter neuem Namen abspeichern
		hr = Save(pText, hCode, lplpstr, uiCnt, dwSaveFlag);
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch (_com_error& e)
	{	
		return _COM_ERROR(e);
	}
	
	return NOERROR;
}

STDMETHODIMP CExternProjectScript::Save(LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)
{
	ASSERT(!m_strMacroName.IsEmpty());

	// wird kopiert, 
	// anderes SetProperty(... als bei Sub
	HRESULT hr = SetProperty(m_strMacroName, pText, hCode, lplpstr, uiCnt, dwSaveFlag);
	// Ist kopiert, 
	if (SUCCEEDED(hr))
	{// in  STREAM speichern	
		hr = SetScript (m_strMacroName);
		if (FAILED(hr)) return hr; 

		SetDirty(false);
	}

	return hr;
}

STDMETHODIMP CExternProjectScript::Delete ()
{	// Objekt, Stream, Info löschen
	HRESULT hr = NOERROR;
	if (FAILED(Delete (m_strMacroName)))// Bei neuem Externem ist noch kein instanziert worden
		hr = S_FALSE;
	// Eintrag in Tree muß gelöscht werden
	((ITreeItem *)this) -> Release();
	return hr;
}
///////////////////////////////////////////////////////
// Eigenes Delete, KEINE Streaminfo löschen !!!
HRESULT CExternProjectScript::Delete (LPCSTR lpcstr)
{
	USES_CONVERSION;
	return	GetObjManagement() -> DelObject (A2OLE(lpcstr));
}

///////////////////////////////////////////////////////
// Eigenes SetProperty, KEINE Streaminfo setzen !!!
HRESULT	CExternProjectScript::SetProperty (LPCSTR lpcstrName, LPCSTR pText, ebHCODE hCode, LPSTR *lplp, UINT, DWORD dwSaveFlag)
{
	ASSERT(lpcstrName);
	ASSERT(NULL != pText || NULL != hCode);
	if (NULL == lpcstrName) return E_POINTER;
	if (NULL == pText && NULL == hCode) return E_INVALIDARG;

	HRESULT hr = NOERROR;

	USES_CONVERSION;

	try
	{
	WUnknown IU;

	// Objekt geben lesen
		THROW_FAILED_HRESULT(GetObjManagement() -> GetObject(A2OLE(lpcstrName), IU.ppi()));
	
	ebSaveStruct SS;

		memset(&SS, 0, sizeof(ebSaveStruct));
		SS.dwSaveFlag = dwSaveFlag; 

		if (NULL != pText && (dwSaveFlag & CC_SCRIPT)) 
			SS.pText = (LPSTR)pText;
		if (NULL != hCode && (dwSaveFlag & CC_CODE))
			SS.hCode = hCode;

		THROW_FAILED_HRESULT(WScriptProperty(IU) -> Set(&SS));
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
	}
	
	return hr;

}

/////////////////////////////////////////////////////////////////////////////////
// FilterScripts
STDMETHODIMP CFilterProjectScript::GetSaveAsFilters(LPSTR *lplp)
{
	ASSERT(lplp);
	if (NULL == lplp) return E_POINTER;

	USES_CONVERSION;
	try
	{
		CString strFilters = GetDefaultName(IDS_SAVEASFILTERFILTER);
		int iLen = strFilters.GetLength();
		if (0 == iLen) _com_issue_error(E_FAIL);
		LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

		strcpy(lpstr, strFilters);
		
		*lplp = lpstr;
	} 
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}
STDMETHODIMP CFilterProjectScript::GetFileExt(LPSTR *lplp)
{
	ASSERT(lplp);
	if (NULL == lplp) return E_POINTER;

	USES_CONVERSION;
	try
	{
		CString strExt = GetDefaultName(IDS_FILTEREXT); 
		int iLen = strExt.GetLength();
		if (0 == iLen) _com_issue_error(E_FAIL);
		LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

		strcpy(lpstr, strExt);
		
		*lplp = lpstr;
	} 
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return NOERROR;
}
STDMETHODIMP CFilterProjectScript::New (LPSTR *ppcMacroText)
{
	ASSERT (!m_strMacroName.IsEmpty());
				
	CString strDefaultScr (GetFilterDefaultScript());
	if (strDefaultScr.IsEmpty()) return E_FAIL;
		
	*ppcMacroText = NULL;
	*ppcMacroText = (LPSTR)CoTaskMemAlloc(strDefaultScr.GetLength()+1);
	if (NULL == *ppcMacroText) return E_OUTOFMEMORY;

	strcpy(*ppcMacroText, strDefaultScr);
	
	SetDirty(true);// wenn schon geladen und es überschrieben werden soll

	return NOERROR;
}
/////////////////////////////////////////////////////////////////////////////////
// FunctionScripts
CFunctionScript::CFunctionScript()
{
	m_ix = 0;
	m_iy = 0;
	m_pParentProject = NULL;
}
CFunctionScript::~CFunctionScript()
{
	if (m_pParentProject)
		m_pParentProject -> Release();
	m_pParentProject = NULL; 
}
HRESULT CFunctionScript::Init(	IObjManHelper *pParentProject,
								IObjectManagement *pIOM, 
								IStreamInfo * pIS, 
								REFIID riid,
								LPCSTR lpcstrName,
								LPCSTR lpcstrDecl,
								LPCSTR lpcstrType,
								LPCSTR lpcstrParams,
								LPCSTR lpcstrComment)		
{	
	ASSERT(NULL != lpcstrName);
	ASSERT(NULL != pParentProject);

	// Basisklasse initialisieren
	CProjectScript2::Init(pIOM, pIS, CLSID_FunctionItem);

	m_strFunctionName = lpcstrName;
	m_strType = lpcstrType;
	m_strDecl = lpcstrDecl;
	m_strParams = lpcstrParams;
	m_strComment = lpcstrComment;
	// Welches Bildchen ?
	m_iImage = IMAGE_PROCEDURE;
	if (NULL != lpcstrType && '\0' != *lpcstrType)	m_iImage = IMAGE_FUNCTION;
	
	if (pParentProject)
	{
		m_pParentProject = pParentProject;
		m_pParentProject -> AddRef();
	}
	return S_OK;
}

STDMETHODIMP CFunctionScript::GetCode (ebHCODE* phCode) 
{ 
	HRESULT hr = NOERROR;
	try
	{
		WBSProperty ISP = (ITreeItem *)m_pParentProject;
		HRESULT hr = ISP -> GetCode(phCode); 
		if (FAILED(hr)) _com_issue_error(hr);
	} 
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	} 
	return hr;
}
STDMETHODIMP CFunctionScript::SetCode (ebHCODE hCode) 
{ 
	HRESULT hr = NOERROR;
	try
	{
		WBSProperty ISP = (ITreeItem *)m_pParentProject;
		HRESULT hr = ISP -> SetCode(hCode); 
		if (FAILED(hr)) _com_issue_error(hr);
	} 
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	} 
	return hr;
} 

STDMETHODIMP CFunctionScript::New (LPSTR *ppcMacroText) 
{// neue Funktion erzeugen
	ASSERT (!m_strFunctionName.IsEmpty());
				
	CString strDefaultScr =  GenerateDefaultFunctionText();
	if (strDefaultScr.IsEmpty()) return E_FAIL;
	
	*ppcMacroText = NULL;
	*ppcMacroText = (LPSTR)CoTaskMemAlloc(strDefaultScr.GetLength()+1);
	if (NULL == *ppcMacroText) return  E_OUTOFMEMORY;

	strcpy(*ppcMacroText, strDefaultScr);
	// erstmal Dirty, bei open eventuell zurücksetzen 
	SetDirty (true);

	return NOERROR;
}

STDMETHODIMP CFunctionScript::Delete ()
{// Später Function-Text löchen
// jetzt nur Eintrag in Tree löschen
	((ITreeItem *)this) -> Release();
	return S_OK;
}

STDMETHODIMP CFunctionScript::Save(LPSTR pText, ebHCODE hCode, LPSTR *lplpstr, UINT uiCnt, DWORD dwSaveFlag)
{
//  In diesem Falle den Parent, nämlich das Script geben lassen, in dem sich die Funktion befinden muss
	HRESULT hr = m_pParentProject  -> Save (pText, hCode, lplpstr, uiCnt, dwSaveFlag);
	return hr;
}

STDMETHODIMP CFunctionScript::Open (LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui, BOOL fCreateTemp)
{
	HRESULT hr = NOERROR;
	// jedesmal bei COMPILE() wird neues FunctionItem erzeugt, dann aktuellen Code nehmen
	hr = OpenFromNewScript();
	if (S_FALSE == hr)
		hr = OpenFromSavedScript(ppcMacroText, phCode, lplplp, ui, fCreateTemp);

	return hr;
}

HRESULT CFunctionScript::OpenFromNewScript()
{
	ebHCODE hCode = NULL;
	HRESULT hr = S_FALSE;
	// jedesmal bei COMPILE() wird neues FunctionItem erzeugt, dann aktuellen Code nehmen
	// Code vom Parent
	if (GetInitNew())
	{
		hr = GetCode(&hCode);
		if (SUCCEEDED(hr) && hCode)
		{
			hr = FindSubOrFunctionString (hCode);// Nur die Stelle im Script selektieren
			CoTaskMemFree(hCode); hCode = NULL;
			if (SUCCEEDED(hr))
				return S_OK;
		}
	}
	return hr;
}
HRESULT CFunctionScript::OpenFromSavedScript(LPSTR *ppcMacroText, ebHCODE *phCode, LPSTR **lplplp, UINT & ui, BOOL fCreateTemp)
{
//  In diesem Falle den Parent, nämlich das Script geben lassen, in dem sich die Funktion befinden muss
	*ppcMacroText = NULL;
	*phCode = NULL;
	*lplplp = NULL;
	ui = 0;

	HRESULT hr = NOERROR;
	ebHCODE hActualCode = NULL;
	ebHCODE hCodeDisk = NULL;

	// jedesmal bei COMPILE() wird neues FunctionItem erzeugt, dann aktuellen Code nehmen
	// Code vom Parent, immer aktueller
	hr = GetCode(&hActualCode);
	if (SUCCEEDED(hr))
	{
		hr = GetScript (m_strMacroName, m_clsid, fCreateTemp);
		if (SUCCEEDED(hr))
		{// Code und Text von Platte
			hr = GetProperty (m_strMacroName, ppcMacroText, &hCodeDisk, lplplp, ui);
		}
	}

	if (hActualCode)
	{// Wenn aktueller Code, dann hier Funktion suchen 
		hr = FindSubOrFunctionString (hActualCode);
		if (hCodeDisk) CoTaskMemFree(hCodeDisk); hCodeDisk = NULL;
		if (SUCCEEDED(hr))
			*phCode = hActualCode;
	}
	else if (hCodeDisk)
	{// Sonst von Platte nehmen
		hr = FindSubOrFunctionString (hCodeDisk);
		if (SUCCEEDED(hr))
			*phCode = hCodeDisk;
	}
	
	if (GetDirty())
	{// Wird ein ganz anderer geöffnet, ist dieser nie Dirty
// Wenn Dirty und er selbst soll geöffnet werden, alten Text und Code belassen, jeweils NULL zurückliefern
		if (*ppcMacroText) CoTaskMemFree(*ppcMacroText); *ppcMacroText = NULL;
		if (*phCode) CoTaskMemFree(*phCode); *phCode = NULL;
		MEMFREE(*lplplp, ui);
	}

	return hr;
}

CString CFunctionScript::GenerateDefaultFunctionText()
{
	CString strDefault, strText, strContainerText;
	LPSTR pText = NULL;

	TRY {
		pText = strText.GetBuffer (_MAX_PATH);
		if (pText == NULL) return strText;
	}
	CATCH (CMemoryException, e) {
		AfxMessageBox (IDS_NOMEMORY);
		return 	strText;
	}                  
	END_CATCH

	strContainerText = m_strParentName;

	ASSERT(!m_strFunctionName.IsEmpty());
	ASSERT(!strContainerText.IsEmpty());

	if (m_strType.IsEmpty())
	{
		if (m_strComment.IsEmpty())
			m_strComment = GetDefaultName(IDS_GENCOMMENTSUB);
		strDefault = GetDefaultName(IDS_SUBDEFAULTSCRIPT);
		
		if (m_strParams.IsEmpty())
			wsprintf (pText, strDefault, (LPCSTR)strContainerText, (LPCSTR)m_strFunctionName, g_cbNil, (LPCSTR)m_strComment);
		else
			wsprintf (pText, strDefault, (LPCSTR)strContainerText, (LPCSTR)m_strFunctionName, (LPCSTR) m_strParams, (LPCSTR)m_strComment);
	}
	else
	{
		if (m_strComment.IsEmpty())
			m_strComment = GetDefaultName(IDS_GENCOMMENTFNCT);
		strDefault = GetDefaultName(IDS_FUNCTIONDEFAULTSCRIPT);

		if (m_strParams.IsEmpty())
			wsprintf (pText, strDefault, (LPCSTR)strContainerText, (LPCSTR)m_strFunctionName, g_cbNil, (LPCSTR)m_strType, (LPCSTR)m_strComment);
		else
			wsprintf (pText, strDefault, (LPCSTR)strContainerText, (LPCSTR)m_strFunctionName, (LPCSTR)m_strParams, (LPCSTR)m_strType, (LPCSTR)m_strComment);
	}

	strText.ReleaseBuffer();

	return strText;
}

HRESULT CFunctionScript::FindSubOrFunctionString (const ebHCODE hCode)
{
	ASSERT(m_strFunctionName);

	if (NULL == hCode) return S_FALSE;
	
	ebPROCINFO PI;
	ebBOOL fNext = true;
	ebHENUM hEnum = NULL;
	HRESULT hr = NOERROR;

	// alle Entries enumerieren und in TreeItem erzeugen
	hEnum = ebGetFirstProc(hCode, &PI);
	if (hEnum == NULL) return E_HANDLE;
		
	while (fNext) 
	{
		// Function gefunden ?
		if (0 == _stricmp (m_strFunctionName, PI.szName))
		{// CursorPos setzen
			if (0 == PI.wType)
				m_ix = 4; // Sub
			else
				m_ix = 9; // Function

			m_iy = PI.wStartLine-1;
		}
	
		fNext = ebGetNextProc(hEnum, &PI);
	}		
	
	ebEnumClose(hEnum);

	return S_OK;
}

/////////////////////////////////////////////////////////////////////////////////
// ObjFeatScripts
STDMETHODIMP CObjFeatProjectScript::New (LPSTR *ppcMacroText)
{
	ASSERT (!m_strMacroName.IsEmpty());
				
	CString strDefaultScr (GetPropertyDefaultScript());
	if (strDefaultScr.IsEmpty()) return E_FAIL;
		
	*ppcMacroText = NULL;
	*ppcMacroText = (LPSTR)CoTaskMemAlloc(strDefaultScr.GetLength()+1);
	if (NULL == *ppcMacroText) return E_OUTOFMEMORY;

	strcpy(*ppcMacroText, strDefaultScr);
	
	SetDirty(true);// wenn schon geladen und es überschrieben werden soll

	return NOERROR;
}


////////////////////////////////////////////////////////////////////////////////////
// ITreeItem_Methods-CKeyDummyProjectScript
STDMETHODIMP CKeyDummyProjectScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)

{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CProjectScript> *pProjScript = NULL;
	CComObject<CSubProjectScript> *pSub = NULL;
	try
	{
		WTreeItem IT;
		WObjectManagement IOM;
		WStreamInfo IS;
		THROW_FAILED_HRESULT(GetGeneralScripts(IOM.ppi()));
		THROW_FAILED_HRESULT(GetInfoGeneralScripts(IS.ppi()));

		if (fSuper)
		{
			pProjScript = new CComObject<CProjectScript>;
			// Initialisieren de NEU Erzeugten
			THROW_FAILED_HRESULT(pProjScript->Init(IOM, IS, riid));
			IT = pProjScript;// Query
		}
		else
		{
			pSub = new CComObject<CSubProjectScript>;
		// Initialisieren de NEU Erzeugten
			THROW_FAILED_HRESULT(pSub->Init(IOM, IS, riid));			
			IT =  pSub;// Query
		}		
		*pp = IT.detach();
	}
	catch(_com_error& e)
	{
		DELETE_OBJ(pProjScript);
		DELETE_OBJ(pSub);
		return _COM_ERROR(e);
	}
	catch (bad_alloc) 
	{
		DELETE_OBJ(pProjScript);
		DELETE_OBJ(pSub);
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

STDMETHODIMP CKeyFilterProjectScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)

{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CFilterProjectScript> *pProjScript = NULL;
	CComObject<CSubFilterProjectScript> *pSub = NULL;
	try
	{
		WTreeItem IT;
		WObjectManagement IOM;
		WStreamInfo IS;
		THROW_FAILED_HRESULT(GetFilterScripts(IOM.ppi()));
		THROW_FAILED_HRESULT(GetInfoFilterScripts(IS.ppi()));

		if (fSuper)
		{
			pProjScript = new CComObject<CFilterProjectScript>;
			// Initialisieren
			THROW_FAILED_HRESULT(pProjScript->Init(IOM, IS, riid));
			IT = pProjScript;// Query
		}
		else
		{
			pSub = new CComObject<CSubFilterProjectScript>;
			// Initialisieren
			THROW_FAILED_HRESULT(pSub->Init(IOM, IS, riid));
			IT =  pSub;			// Query
		}
		*pp = IT.detach();
	}
	catch(_com_error& e)
	{
		DELETE_OBJ(pProjScript);
		DELETE_OBJ(pSub);
		return _COM_ERROR(e);
	}
	catch (bad_alloc) 
	{
		DELETE_OBJ(pProjScript);
		DELETE_OBJ(pSub);
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

STDMETHODIMP CKeyObjFeatProjectScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)

{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CObjFeatProjectScript> *pProjScript = NULL;
	CComObject<CSubObjFeatProjectScript> *pSub = NULL;
	try
	{
		CLSID clsid;
		// Clisd mappen
		if (IsEqualCLSID(riid, CLSID_Script))
		{
			clsid = CLSID_CreateObjectFeatureScript;
		}
		else if (IsEqualCLSID(riid, CLSID_FileScript))
		{
			clsid = CLSID_CreateObjectFeatureFileScript;		
		}
		else 
			clsid = riid;
		
		WTreeItem IT;
		WObjectManagement IOM;
		WStreamInfo IS;
		THROW_FAILED_HRESULT(GetObjFeatScripts(IOM.ppi()));
		THROW_FAILED_HRESULT(GetInfoObjFeatScripts(IS.ppi()));

		if (fSuper)
		{
			pProjScript = new CComObject<CObjFeatProjectScript>;
			// Initialisieren
			THROW_FAILED_HRESULT(pProjScript->Init(IOM, IS, clsid));
			IT = pProjScript;		// Query
		}
		else
		{
			pSub = new CComObject<CSubObjFeatProjectScript>;
			// Initialisieren
			THROW_FAILED_HRESULT(pSub->Init(IOM, IS, clsid));
			IT =  pSub;			// Query
		}
		*pp = IT.detach();
	}
	catch(_com_error& e)
	{
		DELETE_OBJ(pProjScript);
		DELETE_OBJ(pSub);
		return _COM_ERROR(e);
	}
	catch (bad_alloc) 
	{
		DELETE_OBJ(pProjScript);
		DELETE_OBJ(pSub);
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

//////////////////////////////////////////////////////////////////////
// CRootDummy
STDMETHODIMP CRootDummyScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)
{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CKeyDummyProjectScript> *pProjScript = NULL;
	try
	{
		pProjScript = new CComObject<CKeyDummyProjectScript>;
		// Query
		WTreeItem IT = pProjScript;
		*pp = IT.detach();
	}
	catch (bad_alloc) 
	{
		DELETE_OBJ(pProjScript);
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

STDMETHODIMP CRootFilterScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)
{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CKeyFilterProjectScript> *pProjScript = NULL;
	try
	{
		pProjScript = new CComObject<CKeyFilterProjectScript>;
		// Query
		WTreeItem IT = pProjScript;
		*pp = IT.detach();
	}
	catch (bad_alloc) 
	{
		DELETE_OBJ(pProjScript);
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

STDMETHODIMP CRootObjFeatScript::CreateInsertItem	(										
										ITreeItem **pp, 
										REFIID riid, 
										LPCSTR lpcstrName,
										LPCSTR lpcstrDecl,
										LPCSTR lpcstrType,
										LPCSTR lpcstrParams,		
										LPCSTR lpcstrComment,		
										BOOL fSuper
										)
{
	ASSERT(pp);
	if (NULL == pp) return E_POINTER;
	*pp = NULL;

	CComObject<CKeyObjFeatProjectScript> *pProjScript = NULL;
	try
	{
		pProjScript = new CComObject<CKeyObjFeatProjectScript>;
		// Query
		WTreeItem IT = pProjScript;
		*pp = IT.detach();
	}
	catch (bad_alloc) 
	{
		DELETE_OBJ(pProjScript);
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

HRESULT CProjectScript2::Compile	(LPSTR lpstrText, ebHCODE *phCode)
{
	if (*phCode) return S_OK;

	HRESULT hr = NOERROR; 
	ebCOMPILESTRUCT CompileStruct;
	memset (&CompileStruct, 0, sizeof(CompileStruct));

	try
	{
		if (NULL == *phCode && NULL == lpstrText) _com_issue_error(E_UNEXPECTED);

		CebCompiler Compiler;
		memset(&CompileStruct, 0, sizeof(ebLPCOMPILESTRUCT)); 
		
		CebInstance *pInst = &(g_pBSE -> ebInst());
		if (NULL == pInst) _com_issue_error(E_POINTER);
		if (NULL == pInst -> GetHandle()) _com_issue_error(E_HANDLE);

		CompileStruct.wVersion = CS_VERSION;						/* version of this structure (CS_VERSION) */
		CompileStruct.lpText = lpstrText;	 							/* Script to be compiled */
		CompileStruct.hInstance = pInst -> GetHandle();			/* instance of the application (returned fro ebInit) */

		CompileStruct.wFlags |= CF_USECONSTPROC;
		CompileStruct.lpfnConst = PreDefinedConstants;
		CompileStruct.ConstData = 0L;

		if (Compiler.Compile(&CompileStruct)) _com_issue_error (E_FAIL);
		if (NULL == CompileStruct.hCode) _com_issue_error (E_HANDLE);

		*phCode = CompileStruct.hCode;
	}
	catch(_com_error& e)
	{	// Fehler erst hier ausgeben
		hr = _COM_ERROR(e);
	}
	return hr;
}
