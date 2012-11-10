#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <iobjman.h>

#include "macrguid.h"
#include "iscrprop.h"

extern CComModule _Module;

#include "macro.h"

#define OS_NO_STREAM_SUPPORT

#if defined(_DEBUG) && defined(WIN32)
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

#if defined(WIN32)
#define __huge
#endif // WIN32

///////////////////////////////////////////////////////////////////////////////
// SmartInterfaces
DefineSmartInterface(AddScriptProperty);
DefineSmartInterface(Storage);
///////////////////////////////////////////////////////////////////////////////
// algemeine globale Funktionen
BOOL LoadString(CString & str, int IDS);
HRESULT TestclsID (LPSTORAGE pIStorage, const CLSID &clsIDTest);
HRESULT MakeFileName(LPCSTR pPathName, LPSTR pNameToUse, LPCSTR pcFileExt);
HRESULT MakePathName(LPCSTR pPathName, LPSTR pNameToUse);
HRESULT MakeSubStorage(LPSTORAGE pIRootStorage, 
						LPSTORAGE *ppISubStorage,
						const CString &strStorName, 
						BOOL fDirect, CLSID clsID);
HRESULT OpenSubStorage(LPSTORAGE pIRootStorage, 
						LPSTORAGE *ppISubStorage,
						const CString &strStorName, 
						BOOL fDirect, CLSID clsID);
void	MessageNoAccess(HWND hWnd, LPCSTR lpcstr);


//////////////////////////////////////////////////////////////////////////////
//	Methods: CMacroScript2->Chain
CMacroScript2::CMacroScript2()
{
	m_dwSaveFlag = 0;
	m_fIsDirty = 0;
	m_pText = NULL;
	m_hCode = NULL;
	m_strScriptName.Empty();
}

CMacroScript2::~CMacroScript2()
{
	TRACE1("Es wird Makroscript: %s freigegeben.\n", m_strScriptName);

	if (m_hCode) CoTaskMemFree(m_hCode);
	m_hCode = NULL;

	if (m_pText) CoTaskMemFree (m_pText);
	m_pText = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// *** IScriptProperty ***
STDMETHODIMP CMacroScript2::Set(LPSAVESTRUCT pSS)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	ASSERT(NULL != pSS);

	m_dwSaveFlag = 0;

	HRESULT hr = SetProperties(pSS);
	// Wenn fehlschlägt
	if (FAILED(hr))
		hr = SetRelatedOnly(pSS);

	m_dwSaveFlag = pSS -> dwSaveFlag;
	m_fIsDirty = true;	

	return hr;
}

STDMETHODIMP CMacroScript2::Get(LPSAVESTRUCT pSS)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// eventuell SaveFlag abfragen
	ASSERT(pSS);	
	// Gerade kreiert ?
	if (NULL == m_hCode && NULL == m_pText)
		return E_UNEXPECTED;

	LPVOID lpCodeNew = NULL;
	LPSTR lpstr = NULL;

	pSS -> hCode = NULL;
	pSS -> pText = NULL;
	pSS -> lplpstrRelScripts = NULL;
	
	try
	{
		if (m_hCode) 
		{
		// Code kopieren
			lpCodeNew = CoTaskMemAlloc (ebCode_GetSize(m_hCode));	
			if (NULL == lpCodeNew) _com_issue_error(E_OUTOFMEMORY);

		LPVOID lpCode = ebCode_GetPointer(m_hCode);

			memcpy(lpCodeNew, lpCode, ebCode_GetSize(m_hCode));
			pSS -> hCode = ebCode_Create(lpCodeNew);
		}

		if (m_pText)
		{
		// Text kopieren		
			pSS -> pText = (LPSTR) CoTaskMemAlloc (strlen(m_pText)+1);	
			if (NULL == pSS -> pText) 
				_com_issue_error(E_OUTOFMEMORY);
			strcpy (pSS -> pText, m_pText);
		}

		UINT uiCnt = RelScriptsCount();

		if (uiCnt)
		{
		UINT ui = 0;
		
			pSS -> lplpstrRelScripts = (LPSTR *)CoTaskMemAlloc(uiCnt*sizeof(LPSTR));
			if (NULL == pSS -> lplpstrRelScripts) 
				_com_issue_error(E_OUTOFMEMORY);
			pSS -> uiCntRelScripts = uiCnt;
			
		list<os_string>::iterator it = m_listRelatedScripts.begin(); 
					
			while(it != m_listRelatedScripts.end())
			{
			int iLen = strlen((*it).c_str())+1;

				lpstr = (LPSTR)CoTaskMemAlloc(iLen);
				if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

				strcpy(lpstr, (*it).c_str());
				pSS -> lplpstrRelScripts[ui] = lpstr;
				
				ui++;
				it++;
			}
		}
	}
	catch (_com_error &e)
	{
		if (lpCodeNew) CoTaskMemFree(lpCodeNew); lpCodeNew = NULL;
		if (pSS -> hCode) CoTaskMemFree(pSS -> hCode); pSS -> hCode = NULL;
		if (pSS -> pText) CoTaskMemFree(pSS -> pText ); pSS -> pText  = NULL;
		if (lpstr) CoTaskMemFree(lpstr); lpstr = NULL;
		MEMFREE(pSS -> lplpstrRelScripts, pSS -> uiCntRelScripts);

		return _COM_ERROR(e);	
	}

	return NOERROR;
}

////////////////////////////////////////////////////////////////////////////////////////////////
// *** IPersistStream / IPersistStreamInit ***

STDMETHODIMP CMacroScript::GetClassID(LPCLSID pClsID)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	*pClsID = CLSID_Script;
	return NOERROR;
}

STDMETHODIMP CMacroScript2::IsDirty(void)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return m_fIsDirty ? S_OK : S_FALSE;
}

STDMETHODIMP CMacroScript2::Load(LPSTREAM pIStream)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());
	ASSERT(pIStream);

	HRESULT hr = SetNameFromStream(pIStream);
	if (FAILED(hr)) return hr;
	
	ebFILEHEADER Head;
	memset(&Head, 0, sizeof(Head));                          	
	
	hr = LoadHeader (pIStream, &Head) ;

	if (SUCCEEDED(hr)) 
	{
		if (Head.dwCodeSz > 0 && Head.dwScriptSz > 0) 
			hr = LoadAll (pIStream, Head); 
		else if (Head.dwScriptSz > 0)
			hr = LoadText (pIStream, Head);
		else if (Head.dwCodeSz > 0)
			hr = LoadCode (pIStream, Head);
		else 
			ASSERT(0);

		if (SUCCEEDED(hr)) 
		{
			hr = LoadRelatedScripts(pIStream);
			if (FAILED(hr)) hr = S_FALSE; // alte Scripts
		}
	}
	if (FAILED(hr)) return hr;					
	
	m_fIsDirty = false;

	return hr;
}

STDMETHODIMP CMacroScript2::Save(LPSTREAM pIStream, BOOL fClearDirty)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	ASSERT(pIStream);

	HRESULT hr = NOERROR;
	try
	{// nur Related Schreiben, wenn SaveFlag == CC_Related
		hr = WriteRelatedScriptsOnly(pIStream);
		if (S_FALSE != hr) _com_issue_error(hr); // und RAUS, wenn S_OK oder fail
		// Code und Text speichern
		hr = SaveAll (pIStream);
		if (FAILED(hr)) _com_issue_error(hr);
		// am Ende Related schreiben
		hr = WriteRelatedScripts(pIStream);
		if (FAILED(hr)) _com_issue_error(hr);
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	// Speichern abgeschlossen
	if (SUCCEEDED(hr) && fClearDirty) 
		m_fIsDirty = false;     
	return hr;
}

STDMETHODIMP CMacroScript2::GetSizeMax (ULARGE_INTEGER FAR *)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return E_NOTIMPL;
}

STDMETHODIMP CMacroScript2::InitNew(void)
{
//	AFX_MANAGE_STATE(AfxGetAppModuleState());
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// *** Hilfsfunktionen

HRESULT CMacroScript2::SetNameFromStream(LPSTREAM lpStr)
{
	ASSERT(lpStr);
	if (NULL == lpStr) return E_POINTER;

STATSTG stat;
HRESULT hr = S_OK;
	
	USES_CONVERSION;
	try
	{
		THROW_FAILED_HRESULT(lpStr -> Stat (&stat, STATFLAG_DEFAULT));
		m_strScriptName = stat.pwcsName;

	WAddScriptProperty IAS((IScriptProperty *)this);	// Nicht alle Objekte brauchen auch ihren Namen
														// -> throw QI_Ex...
		THROW_FAILED_HRESULT(IAS -> SetName(m_strScriptName));
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
		if (hr == E_NOINTERFACE) 
			hr = S_FALSE; // Nicht alle Objekte brauchen auch ihren Namen
	}

	if (stat.pwcsName) CoTaskMemFree (stat.pwcsName);
	return hr;
}

// Script speichern ----------------------------------------------
HRESULT CMacroScript2::SaveAll (LPSTREAM pIStream)
{
	ASSERT (pIStream);
	
	if (m_dwSaveFlag & CC_SCRIPT || m_dwSaveFlag & CC_CODE) 
	{
		ebFILEHEADER Head;
			
		memset (&Head, 0, sizeof (Head));

		Head.wVersion = FH_VERSION;
		Head.id = FH_ID;
		if ((m_dwSaveFlag & CC_SCRIPT) && NULL != m_pText)
		{
			Head.dwScriptSz = strlen(m_pText)+1;
		}
		if ((m_dwSaveFlag & CC_CODE) && NULL != m_hCode)
		{
			Head.dwCodeSz = ebCode_GetSize(m_hCode);
		}

		Head.dwCode = (DWORD)sizeof(Head);
		Head.dwScript =  (DWORD)sizeof(Head) + Head.dwCodeSz;
		
		ULONG cbWritten = 0;	

		HRESULT hr = pIStream -> Write ((LPCSTR)&Head, sizeof(Head), &cbWritten);	// Header schreiben
		if (FAILED(hr)) return hr;
		if (cbWritten != sizeof(Head)) return E_FAIL;

		if (m_dwSaveFlag & CC_ALL) 
		{
			ASSERT(m_pText);
			ASSERT(m_hCode);
			ASSERT(strlen(m_pText)>0);
			ASSERT(ebCode_GetSize(m_hCode)>0);

			hr = pIStream -> Write (ebCode_GetPointer(m_hCode), Head.dwCodeSz, &cbWritten);
			if(FAILED(hr)) return hr;
			if (cbWritten != sizeof(Head.dwCodeSz)) return E_FAIL;

			hr = pIStream -> Write (m_pText, Head.dwScriptSz, &cbWritten);
			if(FAILED(hr)) return hr;
			if (cbWritten != sizeof(Head.dwScriptSz)) return E_FAIL;
		}
		
		// immer in dieser Reihenfolge
		// 1. Code 
		// 2. Text

		if (m_dwSaveFlag & CC_CODE) 
		{	
			ASSERT(m_hCode);
			ASSERT(Head.dwCodeSz);
			
			hr = pIStream -> Write (ebCode_GetPointer(m_hCode), Head.dwCodeSz, &cbWritten);
			if(FAILED(hr)) return hr;
			if (cbWritten != Head.dwCodeSz) return E_FAIL;
		}

		if (m_dwSaveFlag & CC_SCRIPT) 
		{	
			ASSERT(m_pText);
			ASSERT(Head.dwScriptSz);

			hr = pIStream -> Write (m_pText, Head.dwScriptSz, &cbWritten);
			if(FAILED(hr)) return hr;
			if (cbWritten != Head.dwScriptSz) return E_FAIL;
		}
		
		return S_OK;
	}

	return E_UNEXPECTED;
}

// Alles laden --------------------------------------------------
HRESULT CMacroScript2::LoadAll (LPSTREAM pIStream, ebFILEHEADER &rHead)
{                 
	// immer in dieser Reihenfolge
	// 1. Code 
	// 2. Text
	
	HRESULT hr = LoadCode(pIStream, rHead);
	if (FAILED(hr)) return hr;
	
	hr = LoadText(pIStream, rHead);
	if (FAILED(hr)) return hr;
	
return hr;
}                                                                               

// Script als Textdatei einlesen ----------------------------------------------
HRESULT CMacroScript2::LoadText (LPSTREAM pIStream, ebFILEHEADER &rHead)
{
	ASSERT(pIStream);

	HRESULT hr = NOERROR;
	LARGE_INTEGER li;

	try 
	{
		if (m_pText) CoTaskMemFree (m_pText); m_pText = NULL;
		
		m_pText = (LPSTR) CoTaskMemAlloc (rHead.dwScriptSz);  
		if (m_pText == NULL) _com_issue_error(E_OUTOFMEMORY);

	int iLi = rHead.dwScript -sizeof(rHead) - rHead.dwCodeSz;

	// Seekpointer zum Anfang  des Textes setzen, es wurde erst der Code gelesen
		LISet32 (li, iLi);
		THROW_FAILED_HRESULT(pIStream -> Seek (li, SEEK_CUR, NULL));

	ULONG ulBytes = 0;
	
		THROW_FAILED_HRESULT(pIStream -> Read (m_pText, (ULONG)rHead.dwScriptSz, &ulBytes));
		if (ulBytes != (ULONG)rHead.dwScriptSz) 
			_com_issue_error(E_UNEXPECTED);

	// Länge evtl korrigieren
//		if (0 >= ulBytes) ulBytes = 0;
//		if (MAXTEXT < ulBytes) ulBytes = MAXTEXT;

	} catch (_com_error &e) {
		if (m_pText) CoTaskMemFree (m_pText); m_pText = NULL; 
		return _COM_ERROR(e);
	}
	return hr;
}

// Code laden --------------------------------------------------
HRESULT CMacroScript2::LoadCode (LPSTREAM pIStream, ebFILEHEADER &rHead)
{
	ASSERT(pIStream);

LPVOID lpCode = NULL;
LARGE_INTEGER li;

	try 
	{
		lpCode = CoTaskMemAlloc (rHead.dwCodeSz);	
		if(lpCode == NULL) _com_issue_error(E_OUTOFMEMORY);

	// Seekpointer zum Anfang des Codes setzen
		LISet32 (li, (rHead.dwCode - sizeof(rHead)));
		THROW_FAILED_HRESULT(pIStream -> Seek (li, SEEK_CUR, NULL));

	ULONG ulBytes = 0;
		
		THROW_FAILED_HRESULT(pIStream -> Read (lpCode, rHead.dwCodeSz, &ulBytes));
		if (ulBytes != (ULONG)(rHead.dwCodeSz)) 
			_com_issue_error(E_UNEXPECTED);
		
		if (m_hCode) CoTaskMemFree(m_hCode); 
		m_hCode = ebCode_Create(lpCode);	

	} catch (_com_error &e) {
		if (lpCode) CoTaskMemFree(lpCode); lpCode = NULL; 
		return _COM_ERROR(e); 
	}
	return S_OK;
}

HRESULT CMacroScript2::WriteRelatedScriptsOnly(LPSTREAM pIStream)
{// Es sollen nur Related-Scripts gespeichert werden
	ASSERT(pIStream);

	if (! (m_dwSaveFlag & CC_RELATEDSCRIPTS) ) return S_FALSE;

	HRESULT hr = NOERROR;
	ebFILEHEADER Head;
	LARGE_INTEGER li;	
	int iLi = 0;

	memset(&Head, 0, sizeof(ebFILEHEADER));
	// wird um FileHeader-Grösse weitergesetzt
	hr = LoadHeader (pIStream, &Head);
	if (FAILED(hr)) return hr;
	// nochmal um Script-Grösse + Code-Grösse weitersetzen
	iLi = Head.dwCodeSz + Head.dwScriptSz;
	LISet32 (li, iLi);

	hr = pIStream -> Seek(li, SEEK_CUR, NULL);
	if (FAILED(hr)) return hr;

	hr = WriteRelatedScripts(pIStream);
	if (FAILED(hr)) return hr;

	return S_OK;
}

HRESULT CMacroScript2::WriteRelatedScripts(LPSTREAM pIStream)
{
	ASSERT(pIStream);

	ULONG cbWritten = 0;
	int iCount = RelScriptsCount();

	HRESULT hr = pIStream -> Write (&iCount, sizeof(int), &cbWritten);	// Count schreiben
	if ((int)cbWritten != sizeof(int)) return E_FAIL;
	if (FAILED(hr)) return hr;
	if (0 == iCount) return NOERROR;
	if (100 < iCount) return E_FAIL; // zu viele

	list<os_string>::iterator it = m_listRelatedScripts.begin(); 

	while(it != m_listRelatedScripts.end())
	{
		LPCSTR lpcstr = (*it).c_str();
		int iSize = strlen(lpcstr)+1;

		hr = pIStream -> Write (&iSize, sizeof(int), &cbWritten);	// Count schreiben
		if ((int)cbWritten != sizeof(int)) return E_FAIL;
		if (FAILED(hr)) return hr;

		hr = pIStream -> Write (lpcstr, iSize, &cbWritten);	// Count schreiben
		if ((int)cbWritten != iSize) return E_FAIL;
		if (FAILED(hr)) return hr;

		it++;
	}

	return hr;
}

HRESULT CMacroScript2::LoadRelatedScripts(LPSTREAM pIStream)
{
	ASSERT(pIStream);

	ULONG cbRead;
	int iCount = 0;
	// Anzahl aller Entries lesen
	HRESULT hr = pIStream -> Read (&iCount, sizeof(int), &cbRead);
	if (cbRead != (ULONG)sizeof(int)) return S_FALSE;
	if (FAILED(hr)) return hr; 

	if (0 != iCount && 100 > iCount)
	{
		for (int i=0; i<iCount;i++)
		{		
			int iSize = 0;
			// Size von String lesen
			hr = pIStream -> Read (&iSize, sizeof(int), &cbRead);	
			if ((int)cbRead != sizeof(int)) return E_FAIL;
			if (FAILED(hr)) return hr;

			char str[MAXSTRLENGTH];
			// String von Size lesen
			hr = pIStream -> Read(str, iSize, &cbRead);	
			if ((int)cbRead != iSize) return E_FAIL;
			if (FAILED(hr)) return hr;

			str[iSize-1] = '\0';

			os_string oss(str);
			// Map füllen
			m_listRelatedScripts.push_back(oss);
		}
	}
	
	return hr;
}

HRESULT CMacroScript2::LoadHeader (LPSTREAM pIStream, ebFILEHEADER *pHeader)
{                      
	ASSERT(pIStream);

	ULONG ulBytes = 0;

	HRESULT hr = pIStream -> Read ((LPVOID)pHeader, sizeof(ebFILEHEADER), &ulBytes); 
	if (FAILED(hr)) return hr;

	if (ulBytes == sizeof(ebFILEHEADER) && pHeader->id==FH_ID && pHeader->wVersion==FH_VERSION) 	
	    return S_OK;

	return E_FAIL;
}

UINT CMacroScript2::RelScriptsCount()
{
	list<os_string>::iterator it = m_listRelatedScripts.begin(); 
	UINT uiCnt = 0;
	while(it != m_listRelatedScripts.end())
	{
		uiCnt++;
		it++;
	}

return uiCnt;
}

HRESULT CMacroScript2::CreateStream(LPSTORAGE lpIStorage, BSTR bstr, LPSTREAM *ppIStream)
{
	ASSERT(NULL != bstr);
	ASSERT(ppIStream);
	ASSERT(lpIStorage);

	USES_CONVERSION;

	DWORD dwMode = STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE; 

	// Stream kreieren
	HRESULT hr = lpIStorage -> CreateStream (bstr, dwMode, 0, 0, ppIStream);

	if (SUCCEEDED(hr)) 
	{
		ASSERT(*ppIStream);

		LARGE_INTEGER li;	
		LISet32 (li, 0);
		// Stream erstmal auf Anfang des Files setzen
		hr = (*ppIStream) -> Seek(li, STREAM_SEEK_SET, NULL);
	}

return hr;
}

HRESULT CMacroScript2::SetRelatedOnly (LPSAVESTRUCT pSS)
{
	ASSERT(NULL != pSS);
	// wenn beim Setzen der Properties auch schon SetProperty versagt
	if (( ! (pSS -> dwSaveFlag & CC_RELATEDSCRIPTS) ))
		return E_FAIL; // CC_RELATEDSCRIPTS ?

	return SetRelated(pSS);
}

HRESULT CMacroScript2::SetRelated (LPSAVESTRUCT pSS)
{
	ASSERT(pSS);

	m_listRelatedScripts.erase(m_listRelatedScripts.begin(), m_listRelatedScripts.end());

	if (pSS -> uiCntRelScripts && pSS -> lplpstrRelScripts)
	{
		UINT ui;
		LPSTR lpstr = NULL;
	
		for (ui = 0; ui < pSS -> uiCntRelScripts; ui++)
		{
			lpstr = pSS -> lplpstrRelScripts[ui];
			ASSERT(lpstr);
			if (NULL == lpstr) return E_POINTER;

			os_string osstr(lpstr);
			m_listRelatedScripts.push_back(osstr);
		}
	}

	return NOERROR;
}

HRESULT CMacroScript2::SetText (LPSAVESTRUCT pSS)
{
	ASSERT(pSS);

	if (pSS -> pText && (pSS -> dwSaveFlag & CC_SCRIPT))
	{
		if (m_pText) CoTaskMemFree (m_pText); m_pText = NULL;
				
		m_pText = (LPSTR) CoTaskMemAlloc (strlen(pSS->pText)+1);  
		if (m_pText == NULL) return E_OUTOFMEMORY;
		
		strcpy (m_pText, pSS -> pText);                   
	}

	return NOERROR;
}

HRESULT CMacroScript2::SetCode (LPSAVESTRUCT pSS)
{
	ASSERT(pSS);

	if (pSS -> hCode && (pSS -> dwSaveFlag & CC_CODE))
	{
		if (m_hCode) CoTaskMemFree(m_hCode);
		m_hCode = NULL;

		LPVOID lpCode = ebCode_GetPointer(pSS->hCode);

		UINT uiSize = ebCode_GetSize(pSS->hCode);
		LPVOID lpCodeNew = CoTaskMemAlloc (uiSize);
		if (NULL == lpCodeNew) return E_OUTOFMEMORY;

		memcpy(lpCodeNew, lpCode, ebCode_GetSize(pSS->hCode));

		m_hCode = ebCode_Create(lpCodeNew);
	}

	return NOERROR;
}

HRESULT CMacroScript2::SetProperties (LPSAVESTRUCT pSS)
{
	ASSERT(NULL != pSS);

	// Muss Code oder Text oder Beides vorhanden sein
	if ( ( ! (pSS -> dwSaveFlag & CC_CODE) ) && ( ! (pSS -> dwSaveFlag & CC_SCRIPT) ) )
		return E_FAIL; // CC_RELATEDSCRIPTS ?

	// Code setzen
	HRESULT hr = SetCode (pSS);

	if (SUCCEEDED(hr))
	{
		// Text setzen
		hr = SetText (pSS);

		if (SUCCEEDED(hr))
		{
	// Related setzen
			return SetRelated (pSS);
		}
	}

	return hr;
}

#define	INIT		0 
#define SCRIBBLE	1
#define ISLOAD		2

/////////////////////////////////////////////////////////////////////////////////////
// Methods: CMacroFileScript2
CMacroFileScript2::CMacroFileScript2()
{
	m_dwSaveFlag = 0;

	m_fIsDirty = 0;
	
	m_pText = NULL;
	m_hCode = NULL;

	m_strScriptName.Empty();

	m_fhOpenFile = 0;
	m_iState = INIT;

	m_fLoadWithHeader = false;
}

CMacroFileScript2::~CMacroFileScript2()
{
	TRACE1("Es wird Makroscript: %s freigegeben.\n", m_strScriptName);

	if (m_hCode) CoTaskMemFree(m_hCode);
	m_hCode = NULL;

	if (m_pText) CoTaskMemFree (m_pText);
	m_pText = NULL;

	if (m_fhOpenFile)  CloseHandle (m_fhOpenFile);
	m_fhOpenFile = 0;
}


////////////////////////////////////////////////////////////////////////////////////////////////
// *** IScriptProperty ***
HRESULT CMacroFileScript2::SetNameFromFile(LPCSTR lpcstr)
{
	ASSERT(lpcstr);
	if (NULL == lpcstr) return E_POINTER;

HRESULT hr = S_OK;

	USES_CONVERSION;
	try
	{
	WAddScriptProperty IAS((IScriptProperty *)this); // Nicht alle Objekte brauchen auch ihren Namen
														// -> throw QI_Ex...
		THROW_FAILED_HRESULT(IAS -> SetName(lpcstr));
	}
	catch (_com_error &e)
	{
		hr = _COM_ERROR(e);
		if (hr == E_NOINTERFACE) 
			hr = S_FALSE; // Nicht alle Objekte brauchen auch ihren Namen
	}
	return hr;
}

STDMETHODIMP CMacroFileScript2::Set(LPSAVESTRUCT pSS)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	ASSERT(NULL != pSS);

	m_dwSaveFlag = 0;

	HRESULT hr = SetProperties(pSS);
	// Wenn fehlschlägt
	if (FAILED(hr))
		hr = SetRelatedOnly(pSS);

	m_dwSaveFlag = pSS -> dwSaveFlag;
	// Bei Importiertem IMMER HEADER wegschreiben
	if (m_dwSaveFlag & CC_IMPORT)
		m_fLoadWithHeader = true;
	m_fIsDirty = true;	

	return NOERROR;
}

HRESULT CMacroFileScript2::SetRelatedOnly (LPSAVESTRUCT pSS)
{
	ASSERT(NULL != pSS);
	// wenn beim Setzen der Properties auch schon SetProperty versagt
	if (( ! (pSS -> dwSaveFlag & CC_RELATEDSCRIPTS) ))
		return E_FAIL; // CC_RELATEDSCRIPTS ?

	return SetRelated(pSS);
}

HRESULT CMacroFileScript2::SetRelated (LPSAVESTRUCT pSS)
{
	ASSERT(pSS);

	m_listRelatedScripts.erase(m_listRelatedScripts.begin(), m_listRelatedScripts.end());

	if (pSS -> uiCntRelScripts && pSS -> lplpstrRelScripts)
	{
		UINT ui;
		LPSTR lpstr = NULL;
	
		for (ui = 0; ui < pSS -> uiCntRelScripts; ui++)
		{
			lpstr = pSS -> lplpstrRelScripts[ui];
			ASSERT(lpstr);
			if (NULL == lpstr) return E_POINTER;
			os_string osstr(lpstr);
			m_listRelatedScripts.push_back(osstr);
		}
	}

	return NOERROR;
}

HRESULT CMacroFileScript2::SetText (LPSAVESTRUCT pSS)
{
	ASSERT(pSS);

	if (pSS -> pText && (pSS -> dwSaveFlag & CC_SCRIPT || pSS -> dwSaveFlag & CC_EXPORTALL))
	{
		if (m_pText) CoTaskMemFree (m_pText);
		m_pText = NULL;
				
		m_pText = (LPSTR) CoTaskMemAlloc (strlen(pSS->pText)+1);  
		if (m_pText == NULL) return E_OUTOFMEMORY;
		
		strcpy (m_pText, pSS -> pText);                   
	}

	return NOERROR;
}

HRESULT CMacroFileScript2::SetCode (LPSAVESTRUCT pSS)
{
	ASSERT(pSS);

	if (pSS -> hCode && (pSS -> dwSaveFlag & CC_CODE))
	{
		if (m_hCode) CoTaskMemFree(m_hCode);
		m_hCode = NULL;

		LPVOID lpCode = ebCode_GetPointer(pSS->hCode);

		UINT uiSize = ebCode_GetSize(pSS->hCode);
		LPVOID lpCodeNew = CoTaskMemAlloc (uiSize);
		if (NULL == lpCodeNew) return E_OUTOFMEMORY;

		memcpy(lpCodeNew, lpCode, ebCode_GetSize(pSS->hCode));

		m_hCode = ebCode_Create(lpCodeNew);
	}

	return NOERROR;
}

HRESULT CMacroFileScript2::SetProperties (LPSAVESTRUCT pSS)
{
	ASSERT(NULL != pSS);

	// Muss Code oder Text oder Beides vorhanden sein
	if ( ( ! (pSS -> dwSaveFlag & CC_CODE) ) && ( ! (pSS -> dwSaveFlag & CC_SCRIPT) ) )
		return E_FAIL; // CC_RELATEDSCRIPTS ?

	// Code setzen
	HRESULT hr = SetCode (pSS);

	if (SUCCEEDED(hr))
	{
		// Text setzen
		hr = SetText (pSS);

		if (SUCCEEDED(hr))
		{	// Related setzen
			hr = SetRelated (pSS);
		}
	}

	return hr;
}

STDMETHODIMP CMacroFileScript2::Get(LPSAVESTRUCT pSS)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	// eventuell SaveFlag abfragen
	ASSERT(pSS);	
	// Gerade kreiert ?
	if (NULL == m_hCode && NULL == m_pText)
		return E_UNEXPECTED;

	LPVOID lpCodeNew = NULL;
	LPSTR lpstr = NULL;

	pSS -> hCode = NULL;
	pSS -> pText = NULL;
	pSS -> lplpstrRelScripts = NULL;
	
	try
	{
		if (m_hCode) 
		{
		// Code kopieren
			lpCodeNew = CoTaskMemAlloc (ebCode_GetSize(m_hCode));	
			if (NULL == lpCodeNew) _com_issue_error(E_OUTOFMEMORY);

		LPVOID lpCode = ebCode_GetPointer(m_hCode);

			memcpy(lpCodeNew, lpCode, ebCode_GetSize(m_hCode));
			pSS -> hCode = ebCode_Create(lpCodeNew);
		}

		if (m_pText)
		{
		// Text kopieren		
			pSS -> pText = (LPSTR) CoTaskMemAlloc (strlen(m_pText)+1);	
			if (NULL == pSS -> pText) _com_issue_error(E_OUTOFMEMORY);

			strcpy (pSS -> pText, m_pText);
		}

		UINT uiCnt = RelScriptsCount();

		if (uiCnt)
		{
			UINT ui = 0;
			pSS -> lplpstrRelScripts = (LPSTR *)CoTaskMemAlloc(uiCnt*sizeof(LPSTR));
			if (NULL == pSS -> lplpstrRelScripts) _com_issue_error(E_OUTOFMEMORY);

			pSS -> uiCntRelScripts = uiCnt;
			
		list<os_string>::iterator it = m_listRelatedScripts.begin(); 
					
			while(it != m_listRelatedScripts.end())
			{
			int iLen = strlen((*it).c_str())+1;
		
				lpstr = (LPSTR)CoTaskMemAlloc(iLen);
				if (NULL == lpstr) _com_issue_error(E_OUTOFMEMORY);

				strcpy(lpstr, (*it).c_str());
				pSS -> lplpstrRelScripts[ui] = lpstr;
				
				ui++;
				it++;
			}
		}
	}
	catch (_com_error &e)
	{
		if (lpCodeNew) CoTaskMemFree(lpCodeNew); lpCodeNew = NULL;
		if (pSS -> hCode) CoTaskMemFree(pSS -> hCode); pSS -> hCode = NULL;
		if (pSS -> pText) CoTaskMemFree(pSS -> pText ); pSS -> pText  = NULL;
		if (lpstr) CoTaskMemFree(lpstr); lpstr = NULL;
		MEMFREE(pSS -> lplpstrRelScripts, pSS -> uiCntRelScripts);

		return _COM_ERROR(e);	
	}

	return NOERROR;
}

////////////////////////////////////////////////////////////////////////////
// IPersistFile
STDMETHODIMP CMacroFileScript::GetClassID(LPCLSID pClsID)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	*pClsID = CLSID_FileScript;
	
return NOERROR;
}

STDMETHODIMP CMacroFileScript2::IsDirty(void)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	return m_fIsDirty ? S_OK : S_FALSE;
}


STDMETHODIMP CMacroFileScript2::Load (LPCOLESTR pszFileName, DWORD dwStrMode)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	USES_CONVERSION;

	HRESULT hr = NOERROR;
	HANDLE fh = 0;	
	ebFILEHEADER Head;
	memset(&Head, 0, sizeof(Head));                          	

	try
	{
//		if (m_fhOpenFile) CloseHandle(m_fhOpenFile); m_fhOpenFile = NULL;
		// File kreieren/öffnen, wenn READ/WRITE nicht möglich, nur READ öffnen
		hr = CreateFile (pszFileName, dwStrMode, &fh);
		if (FAILED(hr)) _com_issue_error(hr);
		// CreateNew
		hr = IsEmptyFile (fh);	
		// kein leeres File
		if (S_OK != hr) 
		{// Fileanfang, versucht, FileHeader zu laden
			hr = LoadHeader (fh, &Head);
			// Kein Header ?
			if (FAILED(hr)) 
			{// wenigstens Text laden
				m_fLoadWithHeader = false;
				hr = LoadTextOnly(fh);
			}
			else
			{// Code, Text, Relatives, Fileanfang
				m_fLoadWithHeader = true;
				hr = LoadAll (fh, Head);
			}
			if (FAILED(hr)) _com_issue_error(hr);
		}

		
		HRESULT hr = SetNameFromFile(m_strScriptName);
		if (FAILED(hr)) _com_issue_error(hr);
		m_fIsDirty = false;
		m_iState = ISLOAD;
	}
	catch (_com_error& e)
	{
		if (m_pText) CoTaskMemFree(m_pText); m_pText = NULL;
		if (m_hCode) CoTaskMemFree(m_hCode); m_hCode = NULL;
		hr = _COM_ERROR(e);
	}
	// Schliessen
	if (fh) CloseHandle(fh); fh = NULL;
	return hr;
}

STDMETHODIMP CMacroFileScript2::Save(LPCOLESTR pszFileName, BOOL fRemember)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	if (m_iState != ISLOAD) return E_UNEXPECTED;

	HANDLE fh = 0;
	HANDLE fhOld = NULL;
	HRESULT hr = NOERROR;

	USES_CONVERSION;
	try
	{	// Altes File öffnen
		hr = CreateFile(A2OLE(m_strScriptName), STGM_READWRITE, &fhOld);
		if (FAILED(hr)) _com_issue_error(hr);
		// CC_Related, Old-File Header lesen, Related hinter Code/Text speichern
		hr = WriteRelatedScriptsOnly(fhOld);
		// File gleich hier wieder schliessen, damit Save ins Selbige nicht fehlschlägt
		if (fhOld) CloseHandle(fhOld); fhOld = NULL;
		// RAUS, wenn Erfolg oder wenn noch nie gespeichert worden war
		if (S_OK == hr || E_UNEXPECTED == hr) _com_issue_error(hr); 
		////////////////////////////////////////////////////////////////////////////////
		// File zum Speichern TRUNCATED öffnen
		hr = GetFileHandle(pszFileName, fRemember, &fh);
		if (FAILED(hr)) _com_issue_error(hr);
		// CC_Export , dann RAUS, S_OK zwingt am Ende FileHandle fh freizugeben		
		hr = SaveTextOnly(fh);
		if (S_FALSE != hr) _com_issue_error(hr);
		// Fileanfang, Header, Text, Code und Relatives, Fileanfang
		hr = SaveAll(fh);
		if (FAILED(hr)) _com_issue_error(hr);
		// erfolgreich
		m_fIsDirty = false;
	}
	catch (_com_error& e)
	{
		if (FAILED(_COM_ERROR(e))) {
			if (m_pText) CoTaskMemFree(m_pText); m_pText = NULL;
			if (m_hCode) CoTaskMemFree(m_hCode); m_hCode = NULL;
		}
		hr = _COM_ERROR(e);
	}
	// File schliessen
	if (fh) CloseHandle(fh); fh = NULL;
	if (fhOld) CloseHandle(fhOld); fhOld = NULL;
	return hr;
}

// Speichern abgeschlossen
STDMETHODIMP CMacroFileScript2::SaveCompleted(LPCOLESTR pszFileName)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	m_iState = SCRIBBLE;
	return NOERROR;
}

STDMETHODIMP CMacroFileScript2::GetCurFile(LPOLESTR __RPC_FAR *ppszFileName)
{// Setzt den Modulstatus der MFC.dll auf diese DLL
	AFX_MANAGE_STATE(AfxGetAppModuleState());

	ASSERT(ppszFileName);
	*ppszFileName = NULL;
	return E_FAIL;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// *** Hilfsfunktionen

HRESULT CMacroFileScript2::LoadAll (HANDLE fh, ebFILEHEADER & rH)
{
	ASSERT(fh);

	HRESULT hr = E_FAIL;

	if (rH.dwCodeSz > 0)
	{
		hr = LoadCode (fh, rH);
		if (FAILED(hr)) return hr;
	}
	if (rH.dwScriptSz > 0)
	{
		hr = LoadText (fh, rH);
		if (FAILED(hr)) return hr;
	}

	hr = LoadRelatedScripts(fh, rH);
	if (FAILED(hr)) hr = S_FALSE;// alte Scripts
	// an den Anfang zurück
	SetFilePointer(fh, 0, NULL, FILE_BEGIN);

	return hr;
}
HRESULT CMacroFileScript2::CreateFile (LPCOLESTR pszFileName, DWORD dwStrMode, HANDLE *pfh)
{
	USES_CONVERSION; 
	try {
	DWORD dwMode = -1;
		
		THROW_FAILED_HRESULT(MapCreateFileModes(dwStrMode, &dwMode));
	
	LPSTR lpstr = OLE2A(pszFileName);
	HANDLE fhOpenFile  = NULL;

	/////////////////////////////////
	// File READ/WRITE öffnen
		fhOpenFile = ::CreateFile(
								lpstr,					// pointer to name of the file 
								dwMode,					// access (read-write) mode 
								0,						// share mode 
								NULL,					// pointer to security attributes 
								OPEN_ALWAYS,			// how to create 
								FILE_ATTRIBUTE_NORMAL,	// file attributes 
								NULL);					// handle to file with attributes to copy , win95 NULL

		if (INVALID_HANDLE_VALUE == fhOpenFile)	{
		// Wenigstens nur LESEN öffnen
			fhOpenFile = ::CreateFile(lpstr, GENERIC_READ, 0,	NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,	NULL);					
			if (INVALID_HANDLE_VALUE == fhOpenFile)
			{
				MessageNoAccess(GetActiveWindow(), lpstr); 
				_com_issue_error(E_HANDLE);
			}
		}

		m_strScriptName = lpstr;		
		*pfh = fhOpenFile; 
	}
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	}
	
	return NOERROR;
}
HRESULT CMacroFileScript2::CreateSaveFile (LPCOLESTR pszFileName, HANDLE *pfh)
{
	USES_CONVERSION; 
	try {
	LPSTR lpstr = OLE2A(pszFileName);
	HANDLE fhOpenFile  = NULL;

	/////////////////////////////////
	// TRUNCATED öffnen
		fhOpenFile = ::CreateFile(lpstr, GENERIC_WRITE, 0,	NULL, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL,	NULL);
		if (INVALID_HANDLE_VALUE == fhOpenFile) 
		{
			MessageNoAccess(GetActiveWindow(), lpstr); 
			_com_issue_error(E_HANDLE);
		}
		*pfh = fhOpenFile; 
	}
	catch (_com_error &e)
	{
		return _COM_ERROR(e);
	}	
	return NOERROR;
}

// Script speichern ----------------------------------------------
HRESULT CMacroFileScript2::SaveAll (HANDLE fh)
{
	ASSERT(fh);

	if (m_dwSaveFlag & CC_SCRIPT || m_dwSaveFlag & CC_CODE) 
	{		
		// Header initialisieren und wegschreiben
		ebFILEHEADER Head;

		HRESULT hr = SaveHeader (fh, Head);
		if (FAILED(hr)) return hr;
		
		if (m_dwSaveFlag & CC_CODE)
		{// Pointer hinter Header setzen
			hr = SaveCode(fh, Head);
			if (FAILED(hr)) return hr;
		}
		if (m_dwSaveFlag & CC_SCRIPT)
		{// Pointer hinter Code setzen
			hr = SaveText(fh, Head);
			if (FAILED(hr)) return hr;
		}
		// Pointer hinter Text setzen
		hr = WriteRelatedScripts(fh, Head);
		if (FAILED(hr)) return hr;

		// an den Beginn setzen
		SetFilePointer(
				fh,					// handle of file 
				0,	// number of bytes to move file pointer 
				NULL,				// address of high-order word of distance to move  
				FILE_BEGIN); // Current ist hinter letzter Stringgrösse 

		return S_OK;
	}

	return E_UNEXPECTED;		
}

// Script als Textdatei einlesen ----------------------------------------------
HRESULT CMacroFileScript2::LoadText (HANDLE fh, ebFILEHEADER &rHead)
{
	ASSERT(fh);

	HRESULT hr = NOERROR;

	try
	{
		if (m_pText) CoTaskMemFree(m_pText); m_pText = NULL;
		
		m_pText = (LPSTR)CoTaskMemAlloc(rHead.dwScriptSz);
		if (NULL == m_pText) return E_OUTOFMEMORY; 

	DWORD dwRead = 0;
	LONG lDistanceToMove = (LONG) rHead.dwScript;

	// Steht nach LoadCode CodeAnfang
		SetFilePointer(fh, lDistanceToMove, NULL,FILE_BEGIN);

		if (!ReadFile (fh, (LPVOID)m_pText, rHead.dwScriptSz, &dwRead, NULL)) 
			_com_issue_error(E_FAIL);
		if (dwRead != rHead.dwScriptSz)	
			_com_issue_error(E_UNEXPECTED);

		m_pText[rHead.dwScriptSz-1] = '\0';
	}
	catch (_com_error &e)
	{
		if (m_pText) CoTaskMemFree(m_pText); m_pText = NULL;
		return _COM_ERROR(e);
	}

	return hr;
}

HRESULT CMacroFileScript2::SaveTextOnly (HANDLE fh)
{
	ASSERT(fh);
	if (NULL == fh) return E_HANDLE;
	if (NULL == m_pText) return S_FALSE;
	//////////////////////////////////////////////////
	// Wenn Code und Export IMMER Code abspeichern !!!
	if ((CC_EXPORT & m_dwSaveFlag) && (CC_CODE & m_dwSaveFlag) && m_hCode) return S_FALSE;

	HRESULT hr = S_FALSE;

	USES_CONVERSION;
	try
	{// Bei Export oder wenn nur Text geladen wurde nur Text speichern
		if (CC_EXPORTALL & m_dwSaveFlag || CC_EXPORT & m_dwSaveFlag || false == m_fLoadWithHeader) 
		{
			if (0 == strlen(m_pText)) _com_issue_error(E_POINTER); // Wenn Export und leer, FEHLER

			DWORD dwSize = strlen(m_pText)+1;
			DWORD dwWritten = 0;
			// Auf den Anfang setzen
			SetFilePointer(fh, 0, NULL, FILE_BEGIN);	
			// Nur Text speichern
			if (!WriteFile (fh, (LPVOID)m_pText, dwSize, &dwWritten, NULL)) _com_issue_error(E_FAIL);
			if (dwWritten != dwSize) _com_issue_error(E_FAIL);	
			hr = S_OK;
		}
	}
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	}
	
	return hr;
}

HRESULT CMacroFileScript2::LoadTextOnly (HANDLE fh)
{
	ASSERT(fh);

	try
	{
		if (m_pText) CoTaskMemFree(m_pText); m_pText = NULL;
	
	// An den Anfang setzen
		SetFilePointer(fh, 0, NULL, FILE_BEGIN);	
	
	// Dateigrösse feststellen
	LONG lSize = SetFilePointer(fh, 0, NULL, FILE_END);	
	
		if (0 == lSize) _com_issue_error(E_FAIL); // CreateNew

	DWORD dwRead = 0;
		
		SetFilePointer(fh, 0, NULL, FILE_BEGIN);	
		m_pText = (LPSTR)CoTaskMemAlloc(lSize+1);
		if (NULL == m_pText) _com_issue_error(E_OUTOFMEMORY);

		if (!ReadFile(fh, (LPVOID)m_pText, (DWORD)lSize, &dwRead, NULL) || lSize != dwRead)
			_com_issue_error(E_FAIL);
		
		m_pText[lSize] = '\0';
	}
	catch (_com_error &e)
	{
		if (m_pText) CoTaskMemFree(m_pText); m_pText = NULL;
		return _COM_ERROR(e);
	}
	
	return S_OK;
}

// Code laden --------------------------------------------------
HRESULT CMacroFileScript2::LoadCode (HANDLE fh, ebFILEHEADER &rHead)
{
	ASSERT(fh);

	try
	{
		HRESULT hr = NOERROR;
		LPVOID lpCode = NULL;
		DWORD dwRead = 0;
		LONG lDistanceToMove = (LONG) rHead.dwCode;

		if (m_hCode) CoTaskMemFree (m_hCode); m_hCode = NULL;

		lpCode = CoTaskMemAlloc(rHead.dwCodeSz);
		if (lpCode == NULL) _com_issue_error(E_OUTOFMEMORY); 

		// Steht nach LoadHeader noch am Anfang
		SetFilePointer(fh, lDistanceToMove, NULL, FILE_BEGIN);
	
		if (!ReadFile (fh, (LPVOID)lpCode, rHead.dwCodeSz, &dwRead, NULL) || dwRead != (DWORD)rHead.dwCodeSz)
			_com_issue_error(E_FAIL);

		m_hCode = ebCode_Create(lpCode);
	}
	catch (_com_error &e)
	{
		if (m_hCode) CoTaskMemFree (m_hCode); m_hCode = NULL;
		return _COM_ERROR(e);
	}

	return S_OK;
}

HRESULT CMacroFileScript2::SaveCode(HANDLE fh, ebFILEHEADER & rHead)
{
	ASSERT(fh);

	DWORD dwWritten = 0;
	LONG lDistanceToMove = (LONG)rHead.dwCode;
	// Bis zum Code laufen
	SetFilePointer(
				fh,					// handle of file 
				lDistanceToMove,	// number of bytes to move file pointer 
				NULL,				// address of high-order word of distance to move  
				FILE_BEGIN);
	
	if (!WriteFile (fh, (LPVOID)ebCode_GetPointer(m_hCode), rHead.dwCodeSz, &dwWritten, NULL))
		return E_FAIL;
	if (dwWritten != (DWORD)rHead.dwCodeSz)
		return E_FAIL;	
	
	return S_OK;
}

HRESULT CMacroFileScript2::SaveText(HANDLE fh, ebFILEHEADER & rHead)
{
	ASSERT(fh);

	DWORD dwWritten = 0;
	LONG lDistanceToMove = (LONG)rHead.dwScript;
	// Bis zum Scripttext laufen
	SetFilePointer(
				fh,					// handle of file 
				lDistanceToMove,	// number of bytes to move file pointer 
				NULL,				// address of high-order word of distance to move  
				FILE_BEGIN);

	if (!WriteFile (fh, (LPVOID)m_pText, rHead.dwScriptSz, &dwWritten, NULL))
		return E_FAIL;
	if (dwWritten != (DWORD)rHead.dwScriptSz)
		return E_FAIL;	

	return S_OK;
}

HRESULT CMacroFileScript2::WriteRelatedScriptsOnly(HANDLE fh)
{// Es sollen nur Related-Scripts gespeichert werden
	ASSERT(fh);

	if (! (m_dwSaveFlag & CC_RELATEDSCRIPTS) ) return S_FALSE;

	HRESULT hr = NOERROR;
	ebFILEHEADER Head;

	memset(&Head, 0, sizeof(ebFILEHEADER));

	// wird um FileHeader-Grösse weitergesetzt
	hr = LoadHeader (fh, &Head);
	if (FAILED(hr)) return E_UNEXPECTED; // noch nie gespeichert worden
	// Setzt Pointer selbstständig auf Beginn der RelatedScripts
	hr = WriteRelatedScripts(fh, Head);
	if (FAILED(hr)) return hr;

	// an den Beginn setzen
	SetFilePointer(
				fh,					// handle of file 
				0,	// number of bytes to move file pointer 
				NULL,				// address of high-order word of distance to move  
				FILE_BEGIN); // Current ist hinter letzter Stringgrösse 

	return S_OK;
}

HRESULT CMacroFileScript2::WriteRelatedScripts(HANDLE fh, ebFILEHEADER & rHead)
{
	ASSERT(fh);

	DWORD dwWritten = 0;
	HRESULT hr = NOERROR;
	int iCount = RelScriptsCount();
	LONG lDistanceToMove = (LONG)rHead.dwScript +(LONG)rHead.dwScriptSz;

	// Pointer hinter  Script setzen 
	SetFilePointer(fh,	lDistanceToMove, NULL, FILE_BEGIN);
	// wenigstens Count 0  schreiben
	if (!WriteFile (fh, (LPVOID)&iCount, (DWORD)sizeof(int), &dwWritten , NULL))
		return E_FAIL;
	if ((DWORD)sizeof(int) != dwWritten)
		return E_FAIL;

	if (0 == iCount) return S_FALSE;
	if (100 < iCount) return E_FAIL; // zu viele

	// Pointer steht nun hinter  Count
	SetFilePointer(fh,	sizeof(int), NULL, FILE_CURRENT);

	list<os_string>::iterator it = m_listRelatedScripts.begin(); 

	while(it != m_listRelatedScripts.end())
	{
		LPCSTR lpcstr = (*it).c_str();
		int iSize = strlen(lpcstr)+1;

		if (!WriteFile (fh, (LPVOID)&iSize, (DWORD)sizeof(int), &dwWritten, NULL))
			return E_FAIL;		
		if ((DWORD)sizeof(int) != dwWritten)
			return E_FAIL;

		// Pointer steht nun hinter Size
		SetFilePointer(fh,	sizeof(int), NULL,FILE_CURRENT);

		if (!WriteFile (fh, (LPVOID)lpcstr, (DWORD)iSize, &dwWritten, NULL))
			return E_FAIL;
		if ((DWORD)iSize != dwWritten)
			return E_FAIL;

		// Pointer steht nun hinter  String von Grösse Size
		SetFilePointer(fh,	iSize, NULL, FILE_CURRENT);

		it++;
	}

	return hr;
}

HRESULT CMacroFileScript2::LoadRelatedScripts(HANDLE fh, ebFILEHEADER & rHead)
{
	ASSERT(fh);

	HRESULT hr = NOERROR;
	int iCount = 0;
	DWORD dwRead = 0;
	LONG lMove = (LONG)rHead.dwScript + (LONG)rHead.dwScriptSz;

	SetFilePointer(
				fh,		// handle of file 
				lMove,				// number of bytes to move file pointer 
				NULL,				// address of high-order word of distance to move  
				FILE_BEGIN);

	// Pointer steht hinter Script
	// Anzahl aller Entries lesen
	if (!ReadFile (fh, (LPVOID)&iCount, (DWORD)sizeof(int), &dwRead, NULL))
		return E_FAIL;
	if ((DWORD)sizeof(int) != dwRead)
		return E_FAIL;

	if (0 == iCount) return S_FALSE;
	if (100 < iCount) return E_FAIL; // zu viele

	// Hinter gelesenen Count setzen Integer-gross
	SetFilePointer(fh, sizeof(int),	NULL, FILE_CURRENT);

	for (int i=0; i<iCount;i++)
	{		
		char str[MAXSTRLENGTH];
		int iSize = 0;

		// Size von String lesen
		if (!ReadFile (fh, (LPVOID)&iSize, (DWORD)sizeof(int), &dwRead, NULL))
			return E_FAIL;
		if ((DWORD)sizeof(int) != dwRead)
			return E_FAIL;

		// Hinter gelesenen Stringgrösse
		SetFilePointer(fh, sizeof(int),	NULL, FILE_CURRENT);
	
		// String von Size lesen
		if (!ReadFile (fh, (LPVOID)str, (DWORD)iSize, &dwRead, NULL))
			return E_FAIL;
		if ((DWORD)iSize != dwRead)
			return E_FAIL;

		// Hinter gelesenen String setzen Stringgrösse weiter
		SetFilePointer(fh, iSize, NULL, FILE_CURRENT);
	
		str[iSize-1] = '\0';

		os_string oss(str);
		// Map füllen
		m_listRelatedScripts.push_back(oss);
	}
	
	return hr;
}

HRESULT CMacroFileScript2::IsEmptyFile (HANDLE fh)
{
	ASSERT(fh);

	SetFilePointer(fh, 0, NULL, FILE_BEGIN);	
	// Dateigrösse feststellen
	LONG lSize = SetFilePointer(fh, 0, NULL, FILE_END);	
	// zurücksetzen
	SetFilePointer(fh, 0, NULL, FILE_BEGIN);	

	if (0 == lSize) 
		return S_OK;
	return S_FALSE;
}

HRESULT CMacroFileScript2::MapCreateFileModes(DWORD dwMode, DWORD *pdwMode)
{
	// Mapping von Streammodes auf FileModes von CreateFile(...
	HRESULT hr = NOERROR;

	switch(dwMode)
	{
		case STGM_READ:
		{
			*pdwMode = GENERIC_READ;
			break;
		}
		case STGM_WRITE:
		{
			*pdwMode = GENERIC_WRITE;
			break;
		}
		case STGM_READWRITE:
		{
			*pdwMode = GENERIC_WRITE|GENERIC_READ;
			break;
		}
		default:
		{
			*pdwMode = -1;
			hr = E_FAIL;
		}
	}

	return hr;
}

HRESULT CMacroFileScript2::SaveHeader (HANDLE fh, ebFILEHEADER & rHead)
{
	ASSERT(fh);

	HRESULT hr = E_FAIL;
	DWORD dwWritten = 0;

	// an den Anfang setzen
	SetFilePointer(
				fh,		// handle of file 
				0,					// number of bytes to move file pointer 
				NULL,				// address of high-order word of distance to move  
				FILE_BEGIN);
		

	memset(&rHead, 0, sizeof(ebFILEHEADER));

	rHead.wVersion = FH_VERSION;
	rHead.id = FH_ID;
	if ((m_dwSaveFlag & CC_SCRIPT) && NULL != m_pText)
	{
		rHead.dwScriptSz = strlen(m_pText)+1;
		hr = S_OK;
	}
	if ((m_dwSaveFlag & CC_CODE) && NULL != m_hCode)
	{
		rHead.dwCodeSz = ebCode_GetSize(m_hCode);
		// wenigstens Code oder Text
		hr = S_OK;
	}
	
	if (SUCCEEDED(hr))
	{
		rHead.dwCode = (DWORD)sizeof(rHead);
		rHead.dwScript =  (DWORD)sizeof(rHead) + rHead.dwCodeSz;		
		// Header schreiben
		if (!WriteFile (fh, (LPVOID)&rHead, (DWORD)sizeof(rHead), &dwWritten, NULL))
			return E_FAIL;
		if (dwWritten != (DWORD)sizeof(rHead))
			return E_FAIL;
	}

	// nicht Code oder Text: E_FAIL
	return hr;
}

HRESULT CMacroFileScript2::LoadHeader (HANDLE fh, ebFILEHEADER *pHeader)
{                      
	ASSERT(fh);

	// an den Anfang setzen
	SetFilePointer(
				fh,		// handle of file 
				0,					// number of bytes to move file pointer 
				NULL,				// address of high-order word of distance to move  
				FILE_BEGIN);
		
	HRESULT hr = NOERROR;
	DWORD dwBytes = 0;
	
	if (!ReadFile (fh, (LPVOID)pHeader, (DWORD)sizeof(ebFILEHEADER), &dwBytes, NULL))
		return E_FAIL;
	
	if (dwBytes != (DWORD)sizeof(ebFILEHEADER) || 
		pHeader -> id != FH_ID || 
		pHeader -> wVersion != FH_VERSION)
	{
		return E_FAIL;
	}

	return hr;
}

HRESULT CMacroFileScript2::GetFileHandle(LPCOLESTR lpcolestr, BOOL fRemember, HANDLE *pfh)
{
	USES_CONVERSION;

	HANDLE fh = 0;

	if (NULL == lpcolestr)
	{// altes bleibt offen, Save
		HRESULT hr = CreateSaveFile (A2OLE(m_strScriptName), &fh);
		if (FAILED(hr)) return hr;
	}
	else if (NULL != lpcolestr && fRemember)
	{// neues wird geöffnet und dorthin gespeichert, SaveAs
		//if (m_fhOpenFile)  CloseHandle(m_fhOpenFile); m_fhOpenFile = 0;		
		HRESULT hr = CreateSaveFile(lpcolestr, &fh); 
		if (FAILED(hr)) return hr;
		// NAmen merken
		m_strScriptName = OLE2A(lpcolestr);
	}
	else if (NULL != lpcolestr && false == fRemember)
	{// altes wird beibehalten aber in anderes gespeichert, CopyTo
		HRESULT hr = CreateSaveFile(lpcolestr, &fh); 
		if (FAILED(hr)) return hr;
		// NAmen nicht merken
	}
	*pfh = fh;
	
	return NOERROR;
}

UINT CMacroFileScript2::RelScriptsCount()
{
	list<os_string>::iterator it = m_listRelatedScripts.begin(); 
	UINT uiCnt = 0;
	while(it != m_listRelatedScripts.end())
	{
		uiCnt++;
		it++;
	}

return uiCnt;
}

///////////////////////////////////////////////////////////////////////////
// Globale Funktionen
HRESULT TestclsID (LPSTORAGE pIStorage, const CLSID &clsIDTest)
{
CLSID clsID;
HRESULT hr = ReadClassStg (pIStorage, &clsID);
	if (FAILED(hr)) return hr;
		
	if (!IsEqualCLSID (clsID, clsIDTest)) {
		if (clsID == CLSID_NULL)	// Absturz beim letzten mal
			hr = WriteClassStg (pIStorage, clsIDTest);
		else
			hr = ResultFromScode(E_FAIL);
	}
return hr;
}

HRESULT MakePathName(LPCSTR pPathName, LPSTR pNameToUse)
{
	ASSERT(pPathName);
	ASSERT(pNameToUse);

	char *pDrive = new char [_MAX_DRIVE];
	char *pPath = new char [_MAX_DIR];

	if (pDrive == NULL || pPath == NULL) {
		if (pDrive) delete (pDrive);
		if (pPath) delete (pPath);
		return ResultFromScode (E_OUTOFMEMORY);
	}
	
	// DateiNamen splitten
	_splitpath (pPathName, pDrive, pPath, NULL, NULL);
	// auszugebender Name
	_makepath (pNameToUse, pDrive, pPath, NULL, NULL);

	// Speicher freigeben
	delete (pDrive);
	delete (pPath);
		                        
	return NOERROR;		
}
HRESULT MakeSubStorage(LPSTORAGE pIRootStorage, 
						LPSTORAGE *ppISubStorage,
						const CString &strStorName, 
						BOOL fDirect, 
						CLSID clsID)
{   
    ASSERT(pIRootStorage);
	ASSERT(ppISubStorage);
	if (NULL == ppISubStorage) return E_POINTER;
	if (NULL == pIRootStorage) return STG_E_INVALIDPOINTER;
	ASSERT(!strStorName.IsEmpty());
	if (strStorName.IsEmpty()) return E_INVALIDARG;

	USES_CONVERSION;

	*ppISubStorage = NULL;
	try
	{
		WStorage ISubStorage;
		DWORD dwMode =	STGM_READWRITE | STGM_SHARE_EXCLUSIVE ;	
		
		if (fDirect) dwMode |= STGM_DIRECT;
		else dwMode |= STGM_TRANSACTED;
		// Storage vorhanden ?
		HRESULT hr = pIRootStorage -> OpenStorage (	A2OLE(strStorName), 
													NULL, 
													dwMode, 
													NULL,
													0, 
													ISubStorage.ppi());
		if (STG_E_FILENOTFOUND == hr) 
		{// Storage nicht vorhanden, neuen anlegen
			hr = pIRootStorage -> CreateStorage (A2OLE(strStorName), 
													dwMode, 
													0, 
													0, 
													ISubStorage.ppi());
			if (FAILED(hr)) _com_issue_error(hr);
			// ClassId wegschreiben
			hr = WriteClassStg (ISubStorage, clsID);
			if (FAILED(hr)) _com_issue_error(hr);
		}

		hr = TestclsID (ISubStorage, clsID);
		if (FAILED(hr)) _com_issue_error(hr);
		// Erfolg
		*ppISubStorage = ISubStorage.detach();
	}
	catch (_com_error& e)
	{
		return _COM_ERROR(e);
	}		
	return S_OK;
} 

HRESULT OpenSubStorage(LPSTORAGE pIRootStorage, 
						LPSTORAGE *ppISubStorage,
						const CString &strStorName, 
						BOOL fDirect, CLSID clsID)
{       
	ASSERT(!strStorName.IsEmpty());
	ASSERT(pIRootStorage);

LPSTORAGE pIStorage;
DWORD dwMode =	STGM_READWRITE | STGM_SHARE_EXCLUSIVE ;	

	if (fDirect) dwMode = dwMode | STGM_DIRECT;
	else dwMode = dwMode | STGM_TRANSACTED;

	USES_CONVERSION;

	HRESULT hr = pIRootStorage -> OpenStorage (	A2OLE(strStorName), 
												NULL, dwMode, NULL,
												0, &pIStorage);
	if (FAILED(hr)) {
		*ppISubStorage = NULL;
		return hr;
	}
						
	hr = TestclsID (pIStorage, clsID);
	if (FAILED(hr)) { 
		pIStorage -> Release(); 
		return hr; 
	}
	
	*ppISubStorage = pIStorage;
	
return NOERROR;
} 


HRESULT MakeDummyStorage(LPCSTR lpcstr, LPSTORAGE *lplpStor)
{
	ASSERT(lpcstr);
	ASSERT(lplpStor);
	if (NULL == lplpStor || NULL == lpcstr) return E_POINTER;

	*lplpStor = NULL;

	USES_CONVERSION;
	try
	{// erstmal versuchen, zu öffnen
		WStorage IS;
		HRESULT hr = StgOpenStorage(
					A2OLE(lpcstr),
					NULL,
					STGM_TRANSACTED|STGM_READWRITE|STGM_SHARE_EXCLUSIVE, 
					NULL,
					0, 
					IS.ppi()
					);

		if (FAILED(hr))
		{// kann nicht geöffnet werden, erzeugen
			THROW_FAILED_HRESULT(StgCreateDocfile(
							A2OLE(lpcstr), 
							STGM_TRANSACTED|STGM_READWRITE|STGM_CREATE|STGM_SHARE_EXCLUSIVE, 
							0, 
							IS.ppi()
							));
		}

		*lplpStor = IS.detach();
		ASSERT(NULL != *lplpStor);
		if (NULL == *lplpStor) _com_issue_error(E_POINTER);
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

void MessageNoAccess(HWND hWnd, LPCSTR lpcstr)
{
	ASSERT(hWnd);
	ASSERT(lpcstr);

	CString str, strCap;
	char Buffer[_MAX_PATH];

	LoadString (str, IDS_NOFILEACCESS);
	LoadString (strCap, IDS_LONGCLASSNAME);
	wsprintf(Buffer, str, lpcstr);
	
	::MessageBox (hWnd, Buffer, strCap, MB_OK | MB_ICONINFORMATION);
}