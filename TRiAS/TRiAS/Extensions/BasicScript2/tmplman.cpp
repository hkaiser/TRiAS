#include "bscriptp.hxx"
#include "bscript.h"		// ResourceKonstanten

#include <new>

#include "tmplman.h"

#if _MSC_VER >= 1100
using std::bad_alloc;
#endif // _MSC_VER >= 1100

CTemplateManagement::CTemplateManagement()
{
	m_strTemplate.Empty();
	m_iResID = 0;
}
CTemplateManagement::~CTemplateManagement()
{
}
// muß dieses Aussehen haben
// "ReturnType,FunctionName(Decl)\0"
///////////////////////////////////////////////////
// Template von aussen setzen
HRESULT CTemplateManagement::Set(LPSTR lpstrTemplate) 
{ 
	ASSERT(lpstrTemplate); 
	if (NULL == lpstrTemplate) return E_POINTER; 
	m_strTemplate.Empty();
	m_strTemplate = lpstrTemplate; 
	return S_OK;
}
// Template von Resource holen
HRESULT CTemplateManagement::Load(int iResID, LPSTR lpstrType)
{
	LPSTR lpstrFunction = NULL;
	LPSTR lpstrComment = NULL;
	HRESULT hr = NOERROR;
	try
	{
		lpstrFunction = new char[MAXSTRLENGTH];
		lpstrComment = new char[MAXSTRLENGTH];
		if (NULL == lpstrComment || NULL == lpstrFunction) _com_issue_error(E_POINTER);

		THROW_FAILED_HRESULT(LoadFunction(
										iResID, 
										lpstrType,
										lpstrFunction,
										MAXSTRLENGTH,
										lpstrComment,
										MAXSTRLENGTH));
		// Umkopieren
		m_strTemplate = lpstrFunction;
		m_iResID = iResID;
		m_strComment = lpstrComment;
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	catch(bad_alloc)
	{
		hr = E_OUTOFMEMORY;
	}
	DELETE_OBJ(lpstrFunction);
	DELETE_OBJ(lpstrComment);
	return hr;
}

// Parameter der Funktion als String zurückgeben
HRESULT CTemplateManagement::GetParams(LPSTR lpstr, int iLen)
{
	return GetFnctParams(lpstr, iLen);
}
// Namen der Funktion als String zurückgeben
HRESULT CTemplateManagement::GetName(LPSTR lpstr, int iLen)
{// liefert Namen der Funktion bzw. Prozedur
	return GetFunctionName(lpstr, iLen);
}
// RetTyp der Funktion als String zurückgeben
HRESULT CTemplateManagement::GetType(LPSTR lpstr, int iLen)
{// liefert Funktionstyp
	return 	GetFunctionType(lpstr, iLen);
}
// Deklaration der Funktion als String zurückgeben
HRESULT CTemplateManagement::GetDeclaration	(LPSTR lpstr, int iLen)
{
	return GetFnctDeclaration(lpstr, iLen);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper

HRESULT CTemplateManagement::LoadFunction(	
											int iResID, 
											LPCSTR lpcstrTemplateType,
											LPSTR lpstrFuntion,
											int iLenFunction,
											LPSTR lpstrComment,
											int iLenComment)
{
	ASSERT(lpstrComment);
	ASSERT(lpstrFuntion);
	if (NULL == lpstrComment || NULL == lpstrFuntion) return E_POINTER;
	ASSERT(iLenComment > 0);
	ASSERT(iLenFunction > 0);
	if (iLenFunction <= 0 || iLenComment <= 0) return E_INVALIDARG;

	LPSTR lpszTemplateName = MAKEINTRESOURCE(iResID);
	HANDLE hMem = NULL;
	HRESULT hr = NOERROR;
	try
	{
		// find the resrouce in my EXE
		HINSTANCE hInst = AfxFindResourceHandle(lpszTemplateName, lpcstrTemplateType);
		if (hInst == NULL) _com_issue_error(E_HANDLE);
		HRSRC hResource = ::FindResource(hInst, lpszTemplateName, lpcstrTemplateType);
		if (hResource == NULL) _com_issue_error(E_HANDLE);
		// Größe der jeweiligen Resource geben lassen		
		DWORD dwMemSize = SizeofResource(
							hInst,	// resource-module handle  
							hResource); 	// resource handle 
		if (0 == dwMemSize) _com_issue_error(E_FAIL);

		// allocate memory for it and load it in
		hMem = LoadResource(hInst, hResource);
		if (hMem == NULL) _com_issue_error(E_HANDLE);
		// lock it
		BYTE FAR *lpMem = NULL;
		lpMem = (BYTE FAR *)LockResource(hMem);
		if (lpMem == NULL) _com_issue_error(E_POINTER);
	
		int i = 0;

		while (*lpMem && i <= dwMemSize) 
		{		
			// next ID
			int id = *lpMem++; i++;			// watch out for alignment!
			id |= *lpMem++ << 8; i++;
		
			if (id == COMMENT && lpMem)
			{
				if (iLenComment <= strlen((LPCSTR)lpMem))
					_com_issue_error(E_INVALIDARG);
				strcpy (lpstrComment, (LPCSTR)lpMem);
			}
			else if (id == FUNCTIONDEF && lpMem)
			{
				if (iLenFunction <= strlen((LPCSTR)lpMem)) 
					_com_issue_error(E_INVALIDARG);
				strcpy (lpstrFuntion, (LPCSTR)(lpMem));
			}
			// to end of Text
			while (*lpMem) 
			{
				i++;
				lpMem++;
			}
			lpMem++;// skip '\0' to id 
			i++;
		}
	}
	catch (_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	if (hMem) {
		UnlockResource(hMem);
		FreeResource(hMem);
	}
	return hr;	
}

HRESULT CTemplateManagement::GetFnctParams(LPSTR lpstr, int iLen)
{
	ASSERT(!m_strTemplate.IsEmpty());
	if (m_strTemplate.IsEmpty()) return E_UNEXPECTED;

	HRESULT hr = NOERROR;
	try
	{	// Kopie anfertigen, sonst wird mit strtok der String verändert
		char strTemplate [MAXSTRLENGTH];
		strcpy(strTemplate, m_strTemplate);
		LPSTR lpstrT = strTemplate;

		while ('(' != *lpstrT) 
			lpstrT++;
		// Steht nun vor (, einen weiter, dann vor Params
		lpstrT++;
		// Params rausschneiden
		lpstrT = strtok(lpstrT, ")");
		if (NULL == lpstrT) // kein Parameter
			*lpstr = '\0';
		else
		{
			int iLenTok = strlen(lpstrT);
			if (0 == iLenTok || iLenTok >= iLen) _com_issue_error(E_INVALIDARG);
			strcpy(lpstr, lpstrT);
		}
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	catch(CMemoryException)
	{
		hr = E_OUTOFMEMORY;
	}
	return hr;	
}
HRESULT CTemplateManagement::GetFunctionName(LPSTR lpstr, int iLen)
{
	ASSERT(!m_strTemplate.IsEmpty());
	if (m_strTemplate.IsEmpty()) return E_UNEXPECTED;

	HRESULT hr = NOERROR;
	try
	{	// Kopie anfertigen, sonst wird mit strtok der String verändert
		char strTemplate [MAXSTRLENGTH];
		strcpy(strTemplate, m_strTemplate);
		// An den Anfang
		LPSTR lpstrtok = strtok(strTemplate, ",");
		// zu Funktionsnamen bzw. Subnamen
		lpstrtok = strtok(NULL, "(");
		if (NULL == lpstrtok) _com_issue_error(E_POINTER);

		int iLenTok = strlen(lpstrtok);
		if (0 == iLenTok || iLenTok >= iLen) _com_issue_error(E_INVALIDARG);

		strcpy(lpstr, lpstrtok);
	}
	catch(_com_error& e)
	{
		hr = _COM_ERROR(e);
	}
	return hr;	
}

HRESULT CTemplateManagement::GetFunctionType(LPSTR lpstr, int iLen)
{
	try
	{
		// Kopie anfertigen, sonst wird mit strtok der String verändert
		char strTemplate [MAXSTRLENGTH];
		strcpy(strTemplate, m_strTemplate);		
		// An den Anfang
		LPSTR lpstrtok = strtok(strTemplate, ",");
		int iLenTok = strlen(lpstrtok);
		if (0 == iLenTok || iLenTok >= iLen) _com_issue_error(E_INVALIDARG);
		// Prozedur
		if (0 == strcmp(lpstrtok, "Void")) _com_issue_error(S_FALSE);
		strcpy(lpstr, lpstrtok);
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	catch(CMemoryException)
	{
		return E_OUTOFMEMORY;
	}
	return S_OK;
}

HRESULT CTemplateManagement::GetFnctDeclaration	(LPSTR lpstr, int iLen)
{// Bis zum Komma laufen und rausliefern
	try
	{
		LPSTR lpstrTempl = m_strTemplate.GetBuffer(MAXSTRLENGTH);
		// zum Komma
		while (',' != *lpstrTempl) 
			lpstrTempl++;
		// einen weiter und kopieren
		lpstrTempl++;

		if (0 == strlen(lpstrTempl) || strlen(lpstrTempl) >= iLen) _com_issue_error(E_FAIL);

		strcpy(lpstr, lpstrTempl);
	}
	catch(CMemoryException)
	{
		return E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}

HRESULT CTemplateManagement::GetComment	(LPSTR lpstr, int iLen)
{// Bis zum Komma laufen und rausliefern
	try
	{
		LPSTR lpstrTempl = m_strComment.GetBuffer(MAXSTRLENGTH);
		if (0 == strlen(lpstrTempl) || strlen(lpstrTempl) >= iLen) _com_issue_error(S_FALSE);

		strcpy(lpstr, lpstrTempl);
	}
	catch(CMemoryException)
	{
		return E_OUTOFMEMORY;
	}
	catch(_com_error& e)
	{
		return _COM_ERROR(e);
	}
	return S_OK;
}
