// summinfo.cpp : implementation of the CDrawDoc class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "fakemfcp.hxx"
#include <winnls.h>

#include "fakemfc.h"
#include "strings.h"

#if !defined(_MAC)

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include <objbase.h>

// the DEFINE_GUID macro in the following header now allocates data
#include "summinfo.h"

const OLECHAR szSummInfo[] = OLESTR("\005SummaryInformation");

#if defined(_UNICODE)
LPCSTR tcstocs(LPCTSTR lpctStr) {			 			// typed char (WCHAR) to CHAR
	static CHAR strTemp[1024];
	wcstombs(strTemp, lpctStr, 1024);
	return strTemp;
}
#else // !defined(_UNICODE)
#define tcstocs(lpctStr) (LPCSTR)(lpctStr)
#endif

CSummInfo::CSummInfo()
{
	m_propSet.SetFormatVersion (0);

DWORD dwOSVer = (DWORD)MAKELONG(LOWORD(GetVersion()), 2);

	m_propSet.SetOSVersion(dwOSVer);
	m_propSet.SetClassID (FMTID_SummaryInformation);
	m_pSection = m_propSet.AddSection (FMTID_SummaryInformation);

UINT cp = GetACP();

	m_pSection -> Set (PID_CODEPAGE, (void*)&cp, VT_I2);
	SetTitle(g_cbNil);
	SetSubject(g_cbNil);
	SetAuthor(g_cbNil);
	SetKeywords(g_cbNil);
	SetComments(g_cbNil);
	SetTemplate(g_cbNil);
	SetLastAuthor(g_cbNil);
	m_pSection -> Set (PID_REVNUMBER, (void *)_T("0"), VT_LPSTR);

FILETIME zeroTime = {0L, 0L};

	m_pSection -> Set(PID_EDITTIME, (void *)&zeroTime, VT_FILETIME);
	m_pSection -> Set(PID_LASTPRINTED, (void *)&zeroTime, VT_FILETIME);
	m_pSection -> Set(PID_LASTSAVE_DTM, (void *)&zeroTime, VT_FILETIME);
	m_pSection -> Set(PID_CREATE_DTM, (void *)&zeroTime, VT_FILETIME);
	SetNumPages (0);
	SetNumWords (0);
	SetNumChars (0);
	SetAppname (g_cbNil);
	SetSecurity (0);
}

bool CSummInfo::SetTitle( LPCTSTR szTitle )
{
	return m_pSection->Set (PID_TITLE, (void*)tcstocs(szTitle), VT_LPSTR);
}

CString CSummInfo::GetTitle()
{
	return CString((LPCSTR)m_pSection->Get(PID_TITLE)); 
}

bool CSummInfo::SetSubject( LPCTSTR szSubject )
{
	return m_pSection->Set (PID_SUBJECT, (void*)tcstocs(szSubject), VT_LPSTR);
}

CString CSummInfo::GetSubject()
{
	return CString((LPCSTR)m_pSection->Get(PID_SUBJECT)); 
}

bool CSummInfo::SetAuthor (LPCTSTR szAuthor )
{
	return m_pSection->Set (PID_AUTHOR, (void*)tcstocs(szAuthor), VT_LPSTR);
}

CString CSummInfo::GetAuthor()
{
	return CString((LPCSTR)m_pSection->Get(PID_AUTHOR)); 
}

bool CSummInfo::SetKeywords (LPCTSTR szKeywords )
{
	return m_pSection->Set (PID_KEYWORDS, (void*)tcstocs(szKeywords), VT_LPSTR);
}

CString CSummInfo::GetKeywords()
{
	return CString((LPCSTR)m_pSection->Get(PID_KEYWORDS)); 
}

bool CSummInfo::SetComments (LPCTSTR szComments )
{
	return m_pSection->Set (PID_COMMENTS, (void*)tcstocs(szComments), VT_LPSTR);
}

CString CSummInfo::GetComments()
{
	return CString((LPCSTR)m_pSection->Get(PID_COMMENTS)); 
}

bool CSummInfo::SetTemplate (LPCTSTR szTemplate )
{
	return m_pSection->Set (PID_TEMPLATE, (void*)tcstocs(szTemplate), VT_LPSTR);
}

CString CSummInfo::GetTemplate()
{
	return CString((LPCSTR)m_pSection->Get(PID_TEMPLATE)); 
}

bool CSummInfo::SetLastAuthor (LPCTSTR szLastAuthor )
{
	return m_pSection->Set (PID_LASTAUTHOR, (void*)tcstocs(szLastAuthor), VT_LPSTR);
}

CString CSummInfo::GetLastAuthor()
{
	return CString((LPCSTR)m_pSection->Get(PID_LASTAUTHOR)); 
}

bool CSummInfo::IncrRevNum()
{
ULONG count;

	_stscanf ((LPCTSTR)GetRevNum(), _T("%lu"), &count);
	count++;

TCHAR buff[20];

	_stprintf(buff, _T("%lu"), count);
	return m_pSection->Set (PID_REVNUMBER, (void*)buff, VT_LPSTR);
}

CString CSummInfo::GetRevNum()
{
	return CString((LPCSTR)m_pSection->Get(PID_REVNUMBER));
}

void CSummInfo::StartEditTimeCount()
{
FILETIME now;

	CoFileTimeNow(&now);
	startEdit = *(__int64*)&now;
}

bool CSummInfo::AddCountToEditTime()
{
FILETIME now;

	CoFileTimeNow(&now);
	__int64 currTime = *(__int64*)&now;
	__int64 thisSession = currTime - startEdit;
	__int64 lastTotal = *(__int64*)m_pSection->Get(PID_EDITTIME);
	__int64 newTotal = lastTotal + thisSession;

return m_pSection->Set(PID_EDITTIME, (void*)&newTotal, VT_FILETIME);
}

CString CSummInfo::GetEditTime()
{
FILETIME now;

	CoFileTimeNow(&now);
	__int64 currTime = *(__int64*)&now;
	__int64 thisSession = currTime - startEdit;
	__int64 lastTotal = *(__int64*)m_pSection->Get(PID_EDITTIME);
	__int64 newTotal = lastTotal + thisSession;

ULONG editMinutes = (ULONG)(newTotal/600000000);
TCHAR buff[20];

	_stprintf(buff, _T("%lu min"), editMinutes);
	return CString(buff); 
}

bool CSummInfo::RecordPrintDate()
{
FILETIME printDate;

	CoFileTimeNow(&printDate);
	return m_pSection->Set(PID_LASTPRINTED, (void*)&printDate, VT_FILETIME);
}

CString CSummInfo::GetLastPrintDate()
{
FILETIME* pPrintDate = (FILETIME*)m_pSection->Get(PID_LASTPRINTED);

	if ((pPrintDate == NULL) ||
	    ((pPrintDate->dwLowDateTime == 0L ) &&
	     (pPrintDate->dwHighDateTime == 0L)   ))
	{
		return CString(g_cbNil);
	} else {
	COleDateTime tempDate = *pPrintDate;
	
		return tempDate.Format(); 
	}
}

bool CSummInfo::RecordCreateDate()
{
FILETIME createDate;

	CoFileTimeNow(&createDate);
	return m_pSection->Set(PID_CREATE_DTM, (void*)&createDate, VT_FILETIME);
}

CString CSummInfo::GetCreateDate()
{
FILETIME* pCreateDate = (FILETIME*)m_pSection->Get(PID_CREATE_DTM); 

	if ((pCreateDate == NULL) ||
	    ((pCreateDate->dwLowDateTime == 0L ) &&
	     (pCreateDate->dwHighDateTime == 0L)   ))
	{
		return CString(g_cbNil);
	} else {
	COleDateTime tempDate = *pCreateDate;
	
		return tempDate.Format(); 
	}
}

bool CSummInfo::RecordSaveDate()
{
FILETIME saveDate;

	CoFileTimeNow(&saveDate);
	return m_pSection->Set(PID_LASTSAVE_DTM, (void*)&saveDate, VT_FILETIME);
}

CString CSummInfo::GetLastSaveDate()
{
FILETIME *pSaveDate = (FILETIME*)m_pSection->Get(PID_LASTSAVE_DTM);

	if ((pSaveDate == NULL) ||
		((pSaveDate->dwLowDateTime == 0L ) &&
	     (pSaveDate->dwHighDateTime == 0L)   ))
	{
		return CString(g_cbNil);
	} else {
	COleDateTime tempDate = *pSaveDate;
	
		return tempDate.Format(); 
	}
}

bool CSummInfo::SetNumPages( ULONG nPages )
{
	return m_pSection->Set(PID_PAGECOUNT, (void*)&nPages, VT_I4);
}

CString CSummInfo::GetNumPages()
{
TCHAR buff[20];
ULONG* pNumPages = (ULONG*)m_pSection->Get(PID_PAGECOUNT);

	if (pNumPages != NULL) {
		_stprintf(buff, _T("%lu"), *pNumPages); 
		return CString(buff);
	} else
		return CString(g_cbNil);
}

bool CSummInfo::SetNumWords( ULONG nWords )
{
	return m_pSection->Set(PID_WORDCOUNT, (void*)&nWords, VT_I4);
}

CString CSummInfo::GetNumWords()
{
TCHAR buff[20];
ULONG* pNumWords = (ULONG*)m_pSection->Get(PID_WORDCOUNT);

	if (pNumWords != NULL) {
		_stprintf(buff, _T("%lu"), *pNumWords); 
		return CString(buff);
	} else
		return CString(g_cbNil);
}

ULONG CSummInfo::GetNumWordsNum()
{
ULONG* pNumWords = (ULONG*)m_pSection->Get(PID_WORDCOUNT);

	if (pNumWords != NULL) {
		return *pNumWords;
	} else
		return 0L;
}

bool CSummInfo::SetNumChars( ULONG nChars )
{
	return m_pSection->Set(PID_CHARCOUNT, (void*)&nChars, VT_I4);
}

CString CSummInfo::GetNumChars()
{
TCHAR buff[20];
ULONG* pNumChars = (ULONG*)m_pSection->Get(PID_CHARCOUNT);

	if (pNumChars != NULL) {
		_stprintf(buff, _T("%lu"), *pNumChars); 
		return CString(buff);
	} else
		return CString(g_cbNil);
}

ULONG CSummInfo::GetNumCharsNum()
{
ULONG* pNumChars = (ULONG*)m_pSection->Get(PID_CHARCOUNT);

	if (pNumChars != NULL) {
		return *pNumChars;
	} else
		return 0L;
}

bool CSummInfo::SetAppname( LPCTSTR szAppname )
{
	return m_pSection->Set(PID_APPNAME, (void*)tcstocs(szAppname), VT_LPSTR);
}

CString CSummInfo::GetAppname()
{
	return CString((LPCSTR)m_pSection->Get(PID_APPNAME)); 
}

bool CSummInfo::SetSecurity( ULONG nLevel )
{
	return m_pSection->Set(PID_SECURITY, (void*)&nLevel, VT_I4);
}

CString CSummInfo::GetSecurity()
{
ULONG* pSecurity = (ULONG*)m_pSection->Get(PID_SECURITY);
CString str = g_cbNil;

	if (pSecurity != NULL) {
		if (0 <= *pSecurity && 4 >= *pSecurity) 
			VERIFY(str.LoadString (IDS_SECURITYLEVEL + *pSecurity));
		else {
		TCHAR buff[20];

			_stprintf(buff, _T("%lu"), *pSecurity); 
			str = buff;
		}
	} 

return str;
}

ULONG CSummInfo::GetSecurityNum()
{
ULONG* pSecurity = (ULONG*)m_pSection->Get(PID_SECURITY);

	if (pSecurity != NULL) {
		return *pSecurity;
	} else
		return 0L;
}

HRESULT CSummInfo::WriteToStorage (LPSTORAGE lpRootStg)
{
	if (lpRootStg != NULL) {
	LPSTREAM lpStream = NULL;
	HRESULT hr = lpRootStg->CreateStream (szSummInfo, 
				   STGM_SHARE_EXCLUSIVE|STGM_CREATE|STGM_READWRITE, 
				   0, 0, &lpStream);
	
		if (FAILED(hr)) {
			TRACE(_T("CreateStream failed\n"));
			return hr;
		} else {
			hr = m_propSet.WriteToStream (lpStream);
			lpStream -> Release();
			
			if(FAILED(hr)) {
				TRACE(_T("WriteToStream failed\n"));
				return hr;
			}

//			lpRootStg->Commit(STGC_DEFAULT);	
			return hr;
		}
	}

return ResultFromScode (E_POINTER);
}

HRESULT CSummInfo::ReadFromStorage( LPSTORAGE lpRootStg )
{
	if (lpRootStg != NULL) {
	LPSTREAM lpStream = NULL;
	HRESULT hr = lpRootStg->OpenStream (szSummInfo, 
				   NULL, STGM_SHARE_EXCLUSIVE|STGM_READ, 
				   0, &lpStream);
		
		if (FAILED(hr)) {
			TRACE(_T("OpenStream failed\n"));
			return hr;
		} else {
			hr = m_propSet.ReadFromStream (lpStream);
			lpStream -> Release();

			if (FAILED(hr)) {
				TRACE(_T("ReadFromStream failed\n"));
				return hr;
			}
			m_pSection = m_propSet.GetSection(FMTID_SummaryInformation);
			if (NULL == m_pSection)
				return E_UNEXPECTED;
			return NOERROR;
		}
	}

return ResultFromScode (E_POINTER);
}

#endif // !defined(_MAC)
