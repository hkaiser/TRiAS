#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <new>
#include <iobjman.h>

#include "conststr.h"
#include "macrguid.h"
#include "iscrprop.h"

extern CComModule _Module;

#include "macro.h"
#include "expall.h"

#define OS_NO_STREAM_SUPPORT

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

#if defined(WIN32)
#define __huge
#endif // WIN32

DefineSmartInterface(ScriptProperty);
DefineSmartInterface(StreamInfo);

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

//////////////////////////////////////////////////////////////////////////////////////
// Globale Funktionen
BOOL	LoadString(CString & str, int IDS);
CString GetFileName (CString &rPath, BOOL fExt);
HRESULT MessageNoCode(HWND hWnd, ebHCODE hCode, LPCSTR lpcstrName);

///////////////////////////////////////////////////////////////////////////////////////
// CExportImportProject

CExportImportProject::CExportImportProject()
{
}

CExportImportProject::~CExportImportProject()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////
// *** IPersistFIle ***
STDMETHODIMP CExportImportProject::Save (LPCOLESTR pszFileName, BOOL fRemember)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetModuleState());
	return SaveAll (pszFileName, fRemember);;
}

STDMETHODIMP CExportImportProject::Load(LPCOLESTR pszFileName, DWORD dwMode)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetModuleState());
	return LoadAll(pszFileName, dwMode);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// *** IExportImportProject
STDMETHODIMP_(void)  CExportImportProject::SetManagement	(IObjectManagement* pIOM)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetModuleState());
	m_IObjectManagement = pIOM;
}
STDMETHODIMP CExportImportProject::GetTexts(LPSTR **lplplpstrRelTexts, UINT & ui)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetModuleState());
	return GetSubTexts(lplplpstrRelTexts, ui);
}

HRESULT CExportImportProject::SaveAll (LPCOLESTR pszFileName, BOOL fRemember)
{
	HANDLE fh = NULL;
	HRESULT hr = NOERROR;
	try
	{	// File öffnen
		THROW_FAILED_HRESULT(GetFileHandle(pszFileName, fRemember, &fh));
		// An den Anfang des Files setzen
		if (SUCCEEDED(SaveCodeOnly(fh)))
			_com_issue_error(S_FALSE); // Gleich RAUS
		// {{BEGINFILE(...
		THROW_FAILED_HRESULT(WriteBeginLabel(fh));
		// erstmal da Oberste wegspeichern	
		THROW_FAILED_HRESULT(SaveSuper(fh));
		// All Related wegspeichern
		THROW_FAILED_HRESULT(SaveSubs(fh));
		// An den Anfang des Files zurücksetzen
		SetFilePointer(fh, 0, NULL, FILE_BEGIN);
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	// File schliessen
	if (fh) CloseHandle(fh); fh = NULL;
	m_IObjectManagement.Assign(NULL);
	return hr;
}

HRESULT CExportImportProject::WriteSplitBetweenFiles(HANDLE fh, LPCSTR lpcstrFileName)
{
	ASSERT(lpcstrFileName);
	ASSERT(fh);
	if (NULL == fh) return E_HANDLE;
	if (NULL == lpcstrFileName) return E_POINTER;
	///////////////////////////////////////////////////////////////
	// Hier werden ein SplitterString und der Filename des Unterscript weggeschrieben
	LPSTR lpstrBuffer = NULL;
	HRESULT hr = NOERROR;
	try
	{
		DWORD dwWritten = 0;		
		lpstrBuffer = new char[_MAX_PATH];
		if (NULL == lpstrBuffer) _com_issue_error(E_POINTER);
		
		wsprintf(lpstrBuffer, g_cbSplitBetweeFiles, lpcstrFileName);

		int iSize = strlen(lpstrBuffer);
		if (0 == iSize) _com_issue_error(E_FAIL);
		// OHNE NULL wegschreiben !!!
		if (!WriteFile (fh, (LPVOID)lpstrBuffer, iSize, &dwWritten, NULL))
			return E_FAIL;
		if (iSize != dwWritten) _com_issue_error(E_FAIL);
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	catch(bad_alloc)
	{
		hr = E_OUTOFMEMORY;
	}
	DELETE_OBJ(lpstrBuffer);
	return S_OK;
}

HRESULT CExportImportProject::SaveEnd (HANDLE fh)
{
	ASSERT(fh);
	if (NULL == fh) return E_HANDLE;

	DWORD dwWritten = 0;		
	char  s = '\0';
	// Ohne NULL wegschreiben !!!
	if (!WriteFile (fh, (LPVOID)&s, 1, &dwWritten, NULL))
		return E_FAIL;
	if (dwWritten != 1) return E_FAIL;
	
	return S_OK;
	
}

HRESULT CExportImportProject::SaveText(HANDLE fh, LPCSTR lpcstrText)
{
	ASSERT(lpcstrText);
	ASSERT(fh);
	if (NULL == fh) return E_HANDLE;
	if (NULL == lpcstrText) return E_POINTER;

	DWORD dwWritten = 0;		
	int iSize = strlen(lpcstrText);
	if (0 == iSize) return E_INVALIDARG;
	// Ohne NULL wegschreiben !!!
	if (!WriteFile (fh, (LPVOID)lpcstrText, iSize, &dwWritten, NULL))
		return E_FAIL;
	if (dwWritten != iSize) return E_FAIL;
	
	return S_OK;
}

HRESULT CExportImportProject::SaveSuper (HANDLE fh)
{
	if (!(CC_EXPORTALL & m_dwSaveFlag) || !(m_dwSaveFlag & CC_SCRIPT) || NULL == m_pText) return E_UNEXPECTED;
	// Nur den Text abspeichern von sich selbst abspeichern
	HRESULT hr = NOERROR;
	try
	{// Bei Export oder wenn nur Text geladen wurde nur Text speichern
		if (0 == strlen(m_pText)) _com_issue_error(E_INVALIDARG); // Wenn Export und leer, FEHLER

		DWORD dwSize = strlen(m_pText);
		DWORD dwWritten = 0;
		// Nur Text speichern, 
		// OHNE NULL wegschreiben !!!
		if (!WriteFile (fh, (LPVOID)m_pText, dwSize, &dwWritten, NULL)) _com_issue_error(E_FAIL);
		if (dwWritten != dwSize) _com_issue_error(E_FAIL);	
	}
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return hr;
}

HRESULT CExportImportProject::SaveSubs (HANDLE fh)
{
	ASSERT(m_IObjectManagement);
	if (m_IObjectManagement == NULL) return E_POINTER;

	USES_CONVERSION;

	HRESULT hr = NOERROR;
	ebSaveStruct SS;
	memset(&SS, 0, sizeof(ebSaveStruct));

	try
	{
		list<os_string>::iterator it = m_listRelatedScripts.begin(); 
		// Alle Objekte geben lassen und Code und Text mit wegspeichern				
		while(it != m_listRelatedScripts.end())
		{
			LPCSTR lpcstr = (*it).c_str();
			if (NULL == lpcstr) _com_issue_error(E_POINTER);
			// Splitter einfügen zwischen den verschiedenen Files
			THROW_FAILED_HRESULT(WriteSplitBetweenFiles(fh, lpcstr));
			
			WUnknown IU;
			THROW_FAILED_HRESULT(m_IObjectManagement -> GetObject(A2OLE(lpcstr), IU.ppi()));

			// Text und Code holen
			WScriptProperty ISP = IU; //query...
			memset(&SS, 0, sizeof(ebSaveStruct));
			THROW_FAILED_HRESULT(ISP -> Get(&SS));	
			// Nur den Text abspeichern
			if (NULL != SS.pText)
			{
				THROW_FAILED_HRESULT(SaveText(fh, SS.pText));
			}

			COTASKMEMFREE(SS.pText);
			COTASKMEMFREE(SS.hCode);
			MEMFREE(SS.lplpstrRelScripts, SS.uiCntRelScripts);
			
			it++;
		}
		// erst am Ende die '\0' wegschreiben
		THROW_FAILED_HRESULT(SaveEnd(fh));

	}
	catch(_com_error& e)
	{
		COTASKMEMFREE(SS.pText);
		COTASKMEMFREE(SS.hCode);
		MEMFREE(SS.lplpstrRelScripts, SS.uiCntRelScripts);
		hr = _COM_ERROR(e);
	}
	return hr;
}
// find a sub-string 
int CExportImportProject::FindStringPosition(LPCSTR lpcstrText, LPCSTR lpcstrSub, LPSTR *lplpstrNext)
{
	ASSERT(lpcstrText);
	ASSERT(lpcstrSub);
	if (NULL == lpcstrSub || NULL == lpcstrText) return 0;

	// find first matching substring
	*lplpstrNext = strstr(lpcstrText, lpcstrSub);
	// return -1 for not found, distance from beginning otherwise
	return (*lplpstrNext == NULL) ? -1 : (int)(*lplpstrNext - lpcstrText);
}

HRESULT CExportImportProject::LoadAll(LPCOLESTR pszFileName, DWORD dwMode)
{ 
	ASSERT(pszFileName);
	if (NULL == pszFileName) return E_POINTER;

	HRESULT hr = NOERROR;
	LPSTR lpstrText = NULL;
	HANDLE fh = 0;	


	try
	{
		// File kreieren/öffnen, wenn READ/WRITE nicht möglich, nur READ öffnen
		THROW_FAILED_HRESULT(CreateFile (pszFileName, dwMode, &fh));

		if (S_OK == IsEmptyFile (fh)) 
		{// File leer
			if (fh) CloseHandle(fh); fh = NULL;
			return S_OK;	
		}
		// Ganzen Text laden, Buffer mit CoTaskMemAlloc erzeugen
		THROW_FAILED_HRESULT(LoadTextOnly(&lpstrText, fh));
		// {{BEGINFILE(...
		LPSTR lpstrNext = NULL;
		HRESULT hr = ReadBeginLabel(lpstrText, &lpstrNext);
		if (S_OK != hr) 
		{// Auch wenn kein ganzes Projekt in dieser Datei gespeichert, trotzdem laden
			THROW_FAILED_HRESULT(LoadWholeText((LPCSTR)lpstrText));
		}
		else
		{	// Super laden und erzeugen
			hr = LoadSuper((LPCSTR)lpstrNext, &lpstrNext);
			// Auch, wenn keine Subs vorhanden sind, wird wenigstens der Text geladen
			if (S_OK != hr) _com_issue_error(hr);
			// Subs laden und erzeugen
			THROW_FAILED_HRESULT(LoadSubs (lpstrNext));
		}
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	// Schliessen
	COTASKMEMFREE(lpstrText);
	if (fh) CloseHandle(fh); fh = NULL;
	return hr;
}

HRESULT CExportImportProject::LoadSuper(LPCSTR lpcstrText, LPSTR *lplpstrNext)
{ 
	ASSERT(lpcstrText);
	if (NULL == lpcstrText) return E_POINTER;

	HRESULT hr = NOERROR;

	USES_CONVERSION;
	try
	{
		COTASKMEMFREE(m_pText);

		int iPos = FindStringPosition(lpcstrText, g_cbSplit, lplpstrNext);
		if (0 == iPos || -1 == iPos) 
		{	// Text nicht gefunden
			iPos = strlen(lpcstrText);
			hr = S_FALSE;
		}
		
		m_pText = (LPSTR)CoTaskMemAlloc(iPos+1);
		if (NULL == m_pText) _com_issue_error(E_OUTOFMEMORY); 

		strncpy(m_pText, lpcstrText, iPos);
		m_pText[iPos] = '\0';
	}
	catch(bad_alloc)
	{
		hr = E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}

HRESULT CExportImportProject::LoadWholeText(LPCSTR lpcstrText)
{ 
	ASSERT(lpcstrText);
	if (NULL == lpcstrText) return E_POINTER;

	HRESULT hr = NOERROR;

	USES_CONVERSION;
	try
	{
		COTASKMEMFREE(m_pText);

		int iLen = strlen(lpcstrText);
		if (0 == iLen) _com_issue_error(E_INVALIDARG); 

		m_pText = (LPSTR)CoTaskMemAlloc(iLen+1);
		if (NULL == m_pText) _com_issue_error(E_OUTOFMEMORY); 

		strcpy(m_pText, lpcstrText);
	}
	catch(bad_alloc)
	{
		hr = E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}

HRESULT CExportImportProject::LoadSub(LPSTR lpstrNext, LPSTR *lplpstrNextNext)
{ 
	ASSERT(lplpstrNextNext);
	if (NULL == lplpstrNextNext) return E_POINTER;

	LPSTR lpstrSearch = NULL;
	LPSTR lpstrText = NULL;

	HRESULT hr = NOERROR;

	USES_CONVERSION;
	try
	{
		ASSERT_THROW_INVALIDSTRING(lpstrNext);

		lpstrSearch = new char[strlen(lpstrNext)+1];
		if (NULL == lpstrSearch) _com_issue_error(E_POINTER);
		// Da mit 0 bei jedem Schritt aufgefüllt wird
		strcpy(lpstrSearch, lpstrNext);

		//////////////////////////////////////////////////////////////
		// Name des Subs suchen

		// erstmal Ende des Labels finden ( '{{NEXTFILE("Name"... )
		LPSTR lpstr = strtok(lpstrSearch, "(");
		// Name des Subs finden ( "Name")... )
		LPSTR lpstrName = strtok(NULL, ")");
		if (NULL == lpstrName) _com_issue_error(E_POINTER);
		
		//////////////////////////////////////////////////////////////
		// Text des Subs suchen

		// PointerText steht immer noch vor '{{NEXTFILE("Name"... )
		// also vorschieben (+strlen(lpstrSplitBetweenFiles)), um nächstes Label zu finden
		
		char SplitBetweenFiles[80];
		wsprintf(SplitBetweenFiles, g_cbSplitBetweeFiles, lpstrName);
		
		int iPos = FindStringPosition(
							lpstrNext+strlen(SplitBetweenFiles)-1, 
							g_cbSplit, 
							lplpstrNextNext);
		if (0 == iPos)  _com_issue_error(E_INVALIDARG);

		if (-1 == iPos)
		{// Letzter
			iPos = strlen(lpstrNext+strlen(SplitBetweenFiles)-1);
			if (0 == iPos)  _com_issue_error(E_INVALIDARG);
			// while aussen beenden
			hr = S_FALSE;
		}

		lpstrText = new char[iPos+1];
		if (NULL == lpstrText) _com_issue_error(E_POINTER); 
		
		strncpy(lpstrText, lpstrNext+strlen(SplitBetweenFiles)-1, iPos);
		lpstrText[iPos] = '\0';

		// Liste für Ausgabe füllen 
		m_listRelatedScripts.push_back(lpstrName);
		m_listRelatedTexts.push_back(lpstrText);
	}
	catch(bad_alloc)
	{
		hr = E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	DELETE_OBJ(lpstrText);
	DELETE_OBJ(lpstrSearch);
	return hr;
}

HRESULT CExportImportProject::LoadSubs(LPSTR lpstrNextText)
{ 
	ASSERT(lpstrNextText);
	if (NULL == lpstrNextText) return E_POINTER;

	HRESULT hr = NOERROR;
	LPSTR lpstrNext = NULL;
	try
	{
		while (S_OK == LoadSub(lpstrNextText, &lpstrNext))
		{
			lpstrNextText = lpstrNext;
		}
	}
	catch(bad_alloc)
	{
		hr = E_OUTOFMEMORY;
	}
	return hr;
}

HRESULT CExportImportProject::LoadTextOnly (LPSTR *lplpstr, HANDLE fh)
{
	ASSERT(lplpstr);
	if (NULL == lplpstr) return E_POINTER;
	ASSERT(fh);
	if (NULL == fh) return E_HANDLE;

	*lplpstr = NULL;
	try
	{
		// An den Anfang setzen
		SetFilePointer(fh, 0, NULL, FILE_BEGIN);	
		// Dateigrösse feststellen
		LONG lSize = SetFilePointer(fh, 0, NULL, FILE_END);	
		if (0 == lSize) _com_issue_error(E_FAIL); // CreateNew
		
		SetFilePointer(fh, 0, NULL, FILE_BEGIN);	

		*lplpstr = (LPSTR)CoTaskMemAlloc(lSize+1);
		if (NULL == *lplpstr) _com_issue_error(E_OUTOFMEMORY);

		DWORD dwRead = 0;
		if (!ReadFile(fh, (LPVOID)*lplpstr, (DWORD)lSize, &dwRead, NULL) || lSize != dwRead)
			_com_issue_error(E_FAIL);
	}
	catch (_com_error& e)
	{
		COTASKMEMFREE(*lplpstr);
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CExportImportProject::GetSubTexts(LPSTR **lplplpstrRelTexts, UINT & ui)
{
	ASSERT(lplplpstrRelTexts);
	if (NULL == lplplpstrRelTexts) return E_POINTER;

	HRESULT hr = NOERROR;
	int i = 0;
	int i2 = 0;
	LPSTR *lplpstr = NULL;

	*lplplpstrRelTexts = NULL;
	try
	{
		list<os_string>::iterator it = m_listRelatedTexts.begin(); 
		while(it != m_listRelatedTexts.end()) {
			i++;
			it++;
		}
		lplpstr = (LPSTR*) CoTaskMemAlloc(i*sizeof(LPSTR));
		if (NULL == lplpstr) _com_issue_error(E_OUTOFMEMORY);

		it = m_listRelatedTexts.begin(); 		
		while(it != m_listRelatedTexts.end())
		{
			int iLen = strlen((*it).c_str())+1;
			LPSTR lpstr = (LPSTR)CoTaskMemAlloc(iLen);
			if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

			strcpy(lpstr, (*it).c_str());
			lplpstr[i2] = lpstr;
			
			i2++;
			it++;
		}
		ui = i;
		*lplplpstrRelTexts = lplpstr;
	}
	catch(_com_error& e)
	{
		MEMFREE(*lplplpstrRelTexts, i2);
		hr = _COM_ERROR(e);
	}
	return hr;
}

HRESULT CExportImportProject::WriteBeginLabel(HANDLE fh)
{
	ASSERT(fh);
	if (NULL == fh) return E_HANDLE;

	LPSTR lpstr = NULL;
	HRESULT hr = NOERROR;
	try
	{
		SetFilePointer(fh, 0, NULL, FILE_BEGIN);

		lpstr = new char[80];
		if (NULL == lpstr) _com_issue_error(E_POINTER);
		wsprintf(lpstr, g_cbBeginBeforFiles, m_strScriptName, 0, 0);
		// OHNE NULL wegschreiben !!!
		int iSize = strlen(lpstr);
		if (0 == iSize) _com_issue_error(E_FAIL);

		DWORD dwWritten = 0;
		if (!WriteFile (fh, (LPVOID)lpstr, iSize, &dwWritten, NULL))
			_com_issue_error(E_FAIL);
		if (iSize != dwWritten) _com_issue_error(E_FAIL);
	}
	catch(bad_alloc)
	{
		hr = E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	DELETE_OBJ(lpstr);
	return hr;
}

HRESULT CExportImportProject::ReadBeginLabel(LPSTR lpstr, LPSTR *lplpstrNext)
{
	ASSERT(lplpstrNext);
	if (NULL == lplpstrNext) return E_POINTER;
	ASSERT(lpstr);
	if (NULL == lpstr) return E_POINTER;

	LPSTR lpstrBuffer = NULL;
	HRESULT hr = NOERROR;

	*lplpstrNext = NULL;
	try
	{
		// Bis zur Klammer lesen
		int iPos = FindStringPosition(
							lpstr, 
							g_cbBegin, 
							lplpstrNext);
		if (NULL == *lplpstrNext || -1 == iPos) _com_issue_error(S_FALSE); 

		// Size(Stringlabel) ermitteln
		lpstrBuffer = new char[_MAX_PATH];
		if (NULL == lpstrBuffer) _com_issue_error(E_POINTER);
		wsprintf(lpstrBuffer, g_cbBeginBeforFiles, m_strScriptName, 0, 0);
		int iLen = strlen(lpstrBuffer);
		// Size(vor Stringlabel) + Size(Stringlabel) +'\n' zu Text dazuaddieren
		*lplpstrNext += iLen;
	}
	catch(bad_alloc)
	{
		hr = E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		hr =_COM_ERROR(e);
	}
	DELETE_OBJ(lpstrBuffer);
	return hr;
}

HRESULT CExportImportProject::SaveCodeOnly(HANDLE fh)
{
	if (!(m_dwSaveFlag & CC_CODE)) return E_UNEXPECTED;
	
	ASSERT(fh);
	if (NULL == fh) return E_HANDLE;
	ASSERT(m_IObjectManagement);
	if (m_IObjectManagement == NULL) return E_POINTER;

	USES_CONVERSION;

	HRESULT hr = NOERROR;
	ebSaveStruct SS;
	memset(&SS, 0, sizeof(ebSaveStruct));
	ebHCODE hCode = NULL; 

	try
	{
		////////////////////////////////////////////////////////
		// Hier mit CString arbeiten, einfacher
		CString strWholeText = m_pText;

		list<os_string>::iterator it = m_listRelatedScripts.begin(); 
		// Alle Objekte geben lassen und Code und Text mit wegspeichern				
		while(it != m_listRelatedScripts.end())
		{
			LPCSTR lpcstr = (*it).c_str();
			if (NULL == lpcstr) _com_issue_error(E_POINTER);
			
			WUnknown IU;
			THROW_FAILED_HRESULT(m_IObjectManagement -> GetObject(A2OLE(lpcstr), IU.ppi()));

			// Text und Code holen
			WScriptProperty ISP = IU; //query...
			memset(&SS, 0, sizeof(ebSaveStruct));
			THROW_FAILED_HRESULT(ISP -> Get(&SS));	
			// Nur den Text abspeichern
			if (NULL != SS.pText) 
			{
				strWholeText += SS.pText;
			}

			COTASKMEMFREE(SS.pText);
			COTASKMEMFREE(SS.hCode);
			MEMFREE(SS.lplpstrRelScripts, SS.uiCntRelScripts);
			
			it++;
		}
		// Alle Texte addiert, Kompilieren
		THROW_FAILED_HRESULT(Compile(strWholeText, &hCode));
		THROW_FAILED_HRESULT(SaveCode(fh, hCode));
	}
	catch(_com_error& e)
	{
		if (hCode) ebCode_Free(hCode); hCode = NULL;
		COTASKMEMFREE(SS.pText);
		COTASKMEMFREE(SS.hCode);
		MEMFREE(SS.lplpstrRelScripts, SS.uiCntRelScripts);
		hr = _COM_ERROR(e);
	}
	catch(CMemoryException *p)
	{// Für die Zuweisung im CSting strWholeText
		COTASKMEMFREE(SS.pText);
		COTASKMEMFREE(SS.hCode);
		MEMFREE(SS.lplpstrRelScripts, SS.uiCntRelScripts);
		if (hCode) ebCode_Free(hCode); hCode = NULL;
		hr = E_OUTOFMEMORY;
		p -> Delete();
	}
	return hr;
}

HRESULT CExportImportProject::Compile	(LPCSTR lpcstrText, ebHCODE *phCode)
{
	if (*phCode) return S_OK;

	HRESULT hr = NOERROR; 
	ebCOMPILESTRUCT CompileStruct;
	memset (&CompileStruct, 0, sizeof(CompileStruct));

	try
	{
		if (NULL == *phCode && NULL == lpcstrText) _com_issue_error(E_UNEXPECTED);

		CebCompiler Compiler;
		memset(&CompileStruct, 0, sizeof(ebLPCOMPILESTRUCT)); 
		
		CebInstance *pInst = &(g_pBSE -> ebInst());
		if (NULL == pInst) _com_issue_error(E_POINTER);
		if (NULL == pInst -> GetHandle()) _com_issue_error(E_HANDLE);

		CompileStruct.wVersion = CS_VERSION;						/* version of this structure (CS_VERSION) */
		CompileStruct.lpText = (LPSTR)lpcstrText;	 							/* Script to be compiled */
		CompileStruct.hInstance = pInst -> GetHandle();			/* instance of the application (returned fro ebInit) */

		CompileStruct.wFlags |= CF_USECONSTPROC;
		CompileStruct.lpfnConst = PreDefinedConstants;
		CompileStruct.ConstData = 0L;

		Compiler.Compile(&CompileStruct);

		MessageNoCode(GetActiveWindow(), CompileStruct.hCode, m_strScriptName);
		if (NULL == CompileStruct.hCode) _com_issue_error (E_HANDLE);

		*phCode = CompileStruct.hCode;
	}
	catch(_com_error& e)
	{	// Fehler erst hier ausgeben
		hr = _COM_ERROR(e);
	}
	return hr;
}

HRESULT CExportImportProject::SaveCode(HANDLE fh, ebHCODE hCode)
{
	ASSERT(hCode);
	if (NULL == hCode) return E_HANDLE;
	ASSERT(fh);
	if (NULL == fh) return E_HANDLE;
	ASSERT(0 != ebCode_GetSize(hCode));
	if (NULL == ebCode_GetSize(hCode)) return E_INVALIDARG;
	ASSERT(ebCode_GetPointer(hCode));
	if (NULL == ebCode_GetPointer(hCode)) return E_POINTER;

	HRESULT hr = NOERROR;
	try
	{
		ebFILEHEADER rHead;
		THROW_FAILED_HRESULT(SaveHeader (fh, rHead, hCode));

		DWORD dwWritten = 0;
		LONG lDistanceToMove = (LONG)rHead.dwCode;
		// Bis zum Code laufen
		SetFilePointer(
					fh,					// handle of file 
					lDistanceToMove,	// number of bytes to move file pointer 
					NULL,				// address of high-order word of distance to move  
					FILE_BEGIN);
		
		if (!WriteFile (fh, (LPVOID)ebCode_GetPointer(hCode), rHead.dwCodeSz, &dwWritten, NULL))
			_com_issue_error(E_FAIL);
		if (dwWritten != (DWORD)rHead.dwCodeSz)
			_com_issue_error(E_INVALIDARG);	
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;
}

HRESULT CExportImportProject::SaveHeader (HANDLE fh, ebFILEHEADER & rHead, ebHCODE hCode)
{
	ASSERT(hCode);
	if (NULL == hCode) return E_HANDLE;
	ASSERT(fh);
	if (NULL == fh) return E_HANDLE;
	ASSERT(0 != ebCode_GetSize(hCode));
	if (NULL == ebCode_GetSize(hCode)) return E_INVALIDARG;

	if (!(m_dwSaveFlag & CC_CODE)) return E_UNEXPECTED;

	HRESULT hr = NOERROR;;
	try
	{
		DWORD dwWritten = 0;

		// an den Anfang setzen
		SetFilePointer(fh,0, NULL, FILE_BEGIN);

		memset(&rHead, 0, sizeof(ebFILEHEADER));
		rHead.wVersion = FH_VERSION;
		rHead.id = FH_ID;

		rHead.dwCodeSz = ebCode_GetSize(hCode);
		// wenigstens Code oder Text
		rHead.dwCode = (DWORD)sizeof(rHead);
		rHead.dwScript =  0;		
		// Header schreiben
		if (!WriteFile (fh, (LPVOID)&rHead, (DWORD)sizeof(rHead), &dwWritten, NULL))
			_com_issue_error(E_FAIL);
		if (dwWritten != (DWORD)sizeof(rHead))
			_com_issue_error(E_INVALIDARG);
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	// nicht Code  E_FAIL
	return hr;
}
