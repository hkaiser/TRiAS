
#include "bscriptp.hxx"

#include "macrguid.h"

#include "imacro.h"                  
#include "enumscpt.h"
#include "strmimp.h"
#include "perstimp.h"
#include "macroimp.h"
#include "macro.h"

#define MAXTEXT	0x0000FFEFL		// maximale ScriptGröße

#if defined(WIN32)
#define __huge
#endif // WIN32

/*
 * Constructor Parameters:
 *  pObj            LPVOID pointing to the object we live in.
 *  pUnkOuter       LPUNKNOWN of the controlling unknown.
 */

CImpIPersistStream::CImpIPersistStream(LPUNKNOWN pUnkOuter, CMacro *pMacro)
{
	m_cRef=0;

	m_fIsDirty = false;

	m_pUnkOuter=pUnkOuter;
	m_pMacro = pMacro;

	m_pText = NULL;
	m_hCode = NULL;
}


CImpIPersistStream::~CImpIPersistStream(void)
{
	if (m_pText) CoTaskMemFree (m_pText);
	m_pText = NULL;
	if (m_hCode)  CoTaskMemFree (m_hCode);
	m_hCode = NULL;	
}
/*
 * Purpose:
 *  Delegating IUnknown members for CImpIPersistStream.
 */

STDMETHODIMP CImpIPersistStream::QueryInterface(REFIID riid, LPVOID FAR *ppv)
{
return m_pUnkOuter->QueryInterface(riid, ppv);
}

STDMETHODIMP_(ULONG) CImpIPersistStream::AddRef(void)
{
    ++m_cRef;
return m_pUnkOuter->AddRef();
}

STDMETHODIMP_(ULONG) CImpIPersistStream::Release(void)
{
    --m_cRef;
return m_pUnkOuter->Release();
}
/*
 * CImpIPersistStream::GetClassID
 *
 * Purpose:
 *  Returns the CLSID of the object represented by this interface.
 */

STDMETHODIMP CImpIPersistStream::GetClassID(LPCLSID pClsID)
{
return NOERROR;
}
/*
 * CImpIPersistStream::IsDirty
 *
 * Purpose:
 *  Tells the caller if we have made changes to this object since
 *  it was loaded or initialized new.
 */
STDMETHODIMP CImpIPersistStream::IsDirty(void)
{
// wenn noch nicht gespeichert
	if (true == m_fIsDirty)
		return ResultFromScode(S_OK);	
// schon gespeichert
return ResultFromScode(S_FALSE);
}
/*
 * CImpIPersistStream::Load
 *
 * Purpose:
 *  Instructs the object to load itself from a previously saved
 *  IStream that was handled by Save in another object lifetime.
 *  The seek pointer in this stream will be exactly the same as
 *  it was when Save was called, and this function must leave
 *  the seek pointer the same as it was on exit from Save, regardless
 *  of success or failure.  This function should not hold on to
 *  pIStream.
*/


HRESULT CImpIPersistStream::LoadHeader (LPSTREAM pIStream, ebFILEHEADER *pHeader)
{                      
	ASSERT(pIStream);

ULONG ulBytes = 0;
// erst Headerinfo lesen
LARGE_INTEGER li;
	LISet32 (li, 0);

HRESULT hr = pIStream -> Seek (li, STREAM_SEEK_SET, NULL);
	if (FAILED(hr)) return hr;		
	hr = pIStream -> Read ((LPVOID)pHeader, sizeof(ebFILEHEADER), &ulBytes); 
	if (FAILED(hr) || 0==ulBytes) return ResultFromScode(E_FAIL);

	if (ulBytes==sizeof(ebFILEHEADER) && pHeader->id==FH_ID && pHeader->wVersion==FH_VERSION) 	
	    return NOERROR;

return hr;
}

STDMETHODIMP CImpIPersistStream::Load(LPSTREAM pIStream)
{                      
	ASSERT(pIStream);

ebFILEHEADER Head; 
	memset(&Head, 0, sizeof(Head));                          	
HRESULT hr = LoadHeader (pIStream, &Head) ;
	if (FAILED (hr)) return hr;

	if(m_hCode) CoTaskMemFree(m_hCode); 
	m_hCode = NULL;

	if (Head.dwCodeSz > 0 && Head.dwScriptSz > 0) 
		hr = LoadCode_FromDB (pIStream, Head); 
	else if (Head.dwScriptSz > 0)
		hr = LoadScript_FromDB (pIStream, Head);
	else 
		ASSERT(0);

	if (FAILED(hr)) return hr;					

	m_fIsDirty = false;
	
return hr;
}
/*
 * CImpIPersistStream::Save
 *
 * Purpose:
 *  Saves the data for this object to an IStream.  Be sure not
 *  to change the position of the seek pointer on entry to this
 *  function: the caller will assume that you write from the
 *  current offset.  Leave the stream's seek pointer at the end
 *  of the data written on exit.
 */

STDMETHODIMP CImpIPersistStream::Save(LPSTREAM pIStream, 
				BOOL fClearDirty )
{                     
	ASSERT(pIStream);
	// bei Speichern dirty = false	
HRESULT hr = SaveScript_InDB (pIStream, m_pMacro -> GetCompiled());
	if(FAILED(hr)) return hr;

// Speichern abgeschlossen
	if (fClearDirty) 
// bleibt trotz Speichern dirty, da in einem anderen STREAM als geöffneten gespeichert wurde
		m_fIsDirty = true;     
	else
		m_fIsDirty = false;	
	
return NOERROR;
}

/*
 * CImpIPersistStream::GetSizeMax
 *
 * Purpose:
 *  Returns the size of the data we would write if Save was
 *  called right now.
 *
 * Parameters:
 *  pcbSize         ULARGE_INTEGER FAR * in which to save the size
 *                  of the stream an immediate call to Save would
 *                  write.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIPersistStream::GetSizeMax(ULARGE_INTEGER FAR
    * pcbSize)
{
return NOERROR;
}


// Script als Textdatei einlesen ----------------------------------------------
HRESULT CImpIPersistStream::LoadScript_FromDB (LPSTREAM pIStream, ebFILEHEADER &rHead)
{
	ASSERT(pIStream);

ULONG ulBytes = 0;
	if (m_pText) CoTaskMemFree (m_pText); m_pText = NULL;
	m_pText = (LPSTR) CoTaskMemAlloc (rHead.dwScriptSz+1);  
	if (m_pText == NULL) return ResultFromScode(E_OUTOFMEMORY);

LARGE_INTEGER li;
	LISet32 (li, rHead.dwScript);

HRESULT hr = pIStream -> Seek (li,  STREAM_SEEK_SET, NULL);
	if (FAILED(hr)) { 
		CoTaskMemFree(m_pText); m_pText = NULL; return hr;
	}
	hr = pIStream -> Read (m_pText, (ULONG)rHead.dwScriptSz, &ulBytes);
	
	ASSERT(ulBytes<MAXTEXT);		
	ASSERT(ulBytes>0);

	if (FAILED(hr) || ulBytes != (ULONG)rHead.dwScriptSz) { 
		CoTaskMemFree (m_pText); m_pText = NULL; return ResultFromScode(E_FAIL);
	}
	
return hr;
}

// Compilierten Script laden --------------------------------------------------
HRESULT CImpIPersistStream::LoadCode_FromDB (LPSTREAM pIStream, ebFILEHEADER &rHead)
{                                
LPVOID lpCode = CoTaskMemAlloc (rHead.dwCodeSz);
	if(lpCode == NULL) return ResultFromScode(E_OUTOFMEMORY);

// Code lesen
LARGE_INTEGER li;
	LISet32 (li, rHead.dwCode);
HRESULT hr = pIStream -> Seek (li,  STREAM_SEEK_SET, NULL);
	if (FAILED(hr)) { 
		CoTaskMemFree(lpCode); lpCode = NULL; return hr; 
	} 
ULONG ulBytes = 0;
	hr = pIStream -> Read (lpCode, rHead.dwCodeSz, &ulBytes);
	if (FAILED(hr) || ulBytes != (ULONG)(rHead.dwCodeSz)) { 
		CoTaskMemFree(lpCode); lpCode = NULL; return ResultFromScode(E_FAIL); 
	}	
	
	if (m_pText) CoTaskMemFree (m_pText); m_pText = NULL;
	m_pText = (LPSTR) CoTaskMemAlloc (rHead.dwScriptSz+1);  
	if (m_pText == NULL) { 
		CoTaskMemFree(lpCode); lpCode = NULL; return ResultFromScode(E_OUTOFMEMORY);  
	}

// Script an sich lesen 
	LISet32 (li, rHead.dwScript);
	hr = pIStream -> Seek (li,  STREAM_SEEK_SET, NULL);
	if (FAILED(hr)) { 
		CoTaskMemFree(lpCode); lpCode = NULL; CoTaskMemFree(m_pText); m_pText = NULL; return hr; 
	}
	hr = pIStream -> Read (m_pText, (ULONG)rHead.dwScriptSz, &ulBytes);	
	
	ASSERT(ulBytes<MAXTEXT);	
	ASSERT(ulBytes>0);

	if (FAILED(hr) || ulBytes!=(ULONG)rHead.dwScriptSz || ulBytes==0 || ulBytes>MAXTEXT) {
		CoTaskMemFree(lpCode); lpCode = NULL; CoTaskMemFree(m_pText); m_pText = NULL; 
		return ResultFromScode(E_FAIL);  
	}
		
	m_hCode = ebCode_Create(lpCode);	
		
return hr;
}                                                                               

// Script speichern ----------------------------------------------
HRESULT CImpIPersistStream::SaveScript_InDB (LPSTREAM pIStream, DWORD dwFlag)
{
	ASSERT (pIStream);
ULARGE_INTEGER libEndPos;

ebFILEHEADER Head;
		memset (&Head, 0, sizeof (Head));
		Head.wVersion = FH_VERSION;
		Head.id = FH_ID;

LARGE_INTEGER li;
	LISet32 (li, 0);	

HRESULT hr = NOERROR;

	if (dwFlag == CC_ALL) {
	
		ASSERT(m_pText);
		ASSERT(m_hCode);
		ASSERT(strlen(m_pText)>0);
		ASSERT(ebCode_GetSize(m_hCode)>0);

		Head.dwScriptSz = strlen(m_pText)+1;
		Head.dwCodeSz = ebCode_GetSize(m_hCode);
	
		hr = pIStream -> Seek (li, SEEK_SET, NULL);
		if(FAILED(hr)) return hr;
		hr = pIStream -> Write ((LPCSTR)&Head, sizeof(Head), NULL);	// Header schreiben
		if(FAILED(hr)) return hr;

		hr = pIStream -> Seek (li, SEEK_CUR, &libEndPos);	
		if(FAILED(hr)) return hr;
		Head.dwCode =  libEndPos.LowPart;
		hr = pIStream -> Write (ebCode_GetPointer(m_hCode), Head.dwCodeSz, NULL);
		if(FAILED(hr)) return hr;

		hr = pIStream -> Seek (li, SEEK_CUR, &libEndPos);
		if(FAILED(hr)) return hr;
		Head.dwScript =  libEndPos.LowPart;
		hr = pIStream -> Write (m_pText, Head.dwScriptSz, NULL);
		if(FAILED(hr)) return hr;
	}
	else if (dwFlag & CC_SCRIPT) {	

		ASSERT(m_pText);
		ASSERT(strlen(m_pText)>0);

		Head.dwScriptSz = strlen(m_pText)+1;

		hr = pIStream -> Seek (li, SEEK_SET, NULL);
		if(FAILED(hr)) return hr;
		hr = pIStream -> Write ((LPCSTR)&Head, sizeof(Head), NULL);	// Header schreiben
		if(FAILED(hr)) return hr;

		hr = pIStream -> Seek (li, SEEK_CUR, &libEndPos);
		if(FAILED(hr)) return hr;
		Head.dwScript =  libEndPos.LowPart;
		hr = pIStream -> Write (m_pText, strlen(m_pText)+1, NULL);
		if(FAILED(hr)) return hr;
	}
	else if (dwFlag & CC_CODE) {
		
		ASSERT(m_hCode);
		ASSERT(ebCode_GetSize(m_hCode)>0);
		
		Head.dwCodeSz = ebCode_GetSize(m_hCode);
	
		hr = pIStream -> Seek (li, SEEK_SET, NULL);
		if(FAILED(hr)) return hr;
		hr = pIStream -> Write ((LPCSTR)&Head, sizeof(Head), NULL);	// Header schreiben
		if(FAILED(hr)) return hr;

		hr = pIStream -> Seek (li, SEEK_CUR, &libEndPos);	
		if(FAILED(hr)) return hr;
		Head.dwCode =  libEndPos.LowPart;
		hr = pIStream -> Write (ebCode_GetPointer(m_hCode), Head.dwCodeSz, NULL);
		if(FAILED(hr)) return hr;
	}
	else ASSERT(0);

// nun Header mit den wirklich geschriebenen Groessen noch einmal schreiben		
	LISet32 (li, 0);
	hr = pIStream -> Seek (li, SEEK_SET, NULL);
	if(FAILED(hr)) return hr;
	hr = pIStream -> Write ((LPCSTR)&Head, sizeof(Head), NULL);	
	if(FAILED(hr)) return hr;

return hr;		
}

HRESULT CImpIPersistStream::SetCode(ebHCODE hCode)
{
	if (NULL == hCode) return ResultFromScode(S_FALSE);
	
	ASSERT(ebCode_GetSize(hCode)>0);
	
	if (ebCode_GetSize(hCode) <= 0) return ResultFromScode(E_FAIL);

	if(m_hCode) CoTaskMemFree(m_hCode);
	m_hCode = NULL;

LPVOID lpCode = ebCode_GetPointer(hCode);

LPVOID lpCodeNew = CoTaskMemAlloc (ebCode_GetSize(hCode));
	if (NULL == lpCodeNew) return ResultFromScode(E_OUTOFMEMORY);

	memcpy(lpCodeNew, lpCode, ebCode_GetSize(hCode));

	m_hCode = ebCode_Create(lpCodeNew);

return NOERROR;
}

HRESULT CImpIPersistStream::GetCode(ebHCODE *phCode)
{
	ASSERT(phCode);
	if (NULL == m_hCode) return ResultFromScode(S_FALSE);
	
	ASSERT(ebCode_GetSize(m_hCode)>0);
	if (ebCode_GetSize(m_hCode) <= 0) return ResultFromScode(E_FAIL);

LPVOID lpCodeNew = CoTaskMemAlloc (ebCode_GetSize(m_hCode));
	if (NULL == lpCodeNew) return ResultFromScode(E_OUTOFMEMORY);

LPVOID lpCode = ebCode_GetPointer(m_hCode);

	memcpy(lpCodeNew, lpCode, ebCode_GetSize(m_hCode));

	*phCode = ebCode_Create(lpCodeNew);

return NOERROR;
}

HRESULT CImpIPersistStream::GetScriptText (LPSTR *ppText)
{
	ASSERT(m_pText);

int iLen = strlen(m_pText)+1;

	ASSERT(iLen>0);

// Text kopieren		
	*ppText = (LPSTR) CoTaskMemAlloc (iLen);	
	if (NULL == *ppText) return ResultFromScode (E_FAIL);

	strcpy (*ppText, m_pText);

return NOERROR;
}

HRESULT CImpIPersistStream::SetScriptText (char *pText)
{        
	ASSERT(pText);

int iLen = strlen(pText)+1;
	
	ASSERT(iLen>0);
	
	if (m_pText) CoTaskMemFree (m_pText);
	m_pText = NULL;
			
	m_pText = (LPSTR) CoTaskMemAlloc (iLen);  
	if (m_pText == NULL) return ResultFromScode (E_OUTOFMEMORY);
	
	strcpy (m_pText, pText);                   
	
return NOERROR;
}

