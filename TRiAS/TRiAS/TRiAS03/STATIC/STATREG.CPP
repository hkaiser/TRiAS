
LPCTSTR   rgszNeverDelete[] = //Component Catagories
{
	_T("CLSID"), _T("TYPELIB")
};

const int   cbNeverDelete = sizeof(rgszNeverDelete) / sizeof(LPCTSTR*);

LPTSTR StrChr(LPTSTR lpsz, TCHAR ch)
{
	LPTSTR p = NULL;
	while (*lpsz)
	{
		if (*lpsz == ch)
		{
			p = lpsz;
			break;
		}
		lpsz = CharNext(lpsz);
	}
	return p;
}

static HKEY WINAPI HKeyFromString(LPTSTR szToken)
{
	struct keymap
	{
		LPCTSTR lpsz;
		HKEY hkey;
	};
	static const keymap map[] = {
		{_T("HKCR"), HKEY_CLASSES_ROOT},
		{_T("HKCU"), HKEY_CURRENT_USER},
		{_T("HKLM"), HKEY_LOCAL_MACHINE},
		{_T("HKU"),  HKEY_USERS},
		{_T("HKPD"), HKEY_PERFORMANCE_DATA},
		{_T("HKDD"), HKEY_DYN_DATA},
		{_T("HKCC"), HKEY_CURRENT_CONFIG},
		{_T("HKEY_CLASSES_ROOT"), HKEY_CLASSES_ROOT},
		{_T("HKEY_CURRENT_USER"), HKEY_CURRENT_USER},
		{_T("HKEY_LOCAL_MACHINE"), HKEY_LOCAL_MACHINE},
		{_T("HKEY_USERS"), HKEY_USERS},
		{_T("HKEY_PERFORMANCE_DATA"), HKEY_PERFORMANCE_DATA},
		{_T("HKEY_DYN_DATA"), HKEY_DYN_DATA},
		{_T("HKEY_CURRENT_CONFIG"), HKEY_CURRENT_CONFIG}
	};

	for (int i=0;i<sizeof(map)/sizeof(keymap);i++)
	{
		if (!lstrcmpi(szToken, map[i].lpsz))
			return map[i].hkey;
	}
	return NULL;
}

static HKEY HKeyFromCompoundString(LPTSTR szToken, LPTSTR& szTail)
{
	if (NULL == szToken)
		return NULL;

	LPTSTR lpsz = StrChr(szToken, chDirSep);

	if (NULL == lpsz)
		return NULL;

	szTail = CharNext(lpsz);
	*lpsz = chEOS;
	HKEY hKey = HKeyFromString(szToken);
	*lpsz = chDirSep;
	return hKey;
}

static LPVOID QueryValue(HKEY hKey, LPCTSTR szValName, DWORD& dwType)
{
	DWORD dwCount = 0;

	if (RegQueryValueEx(hKey, szValName, NULL, &dwType, NULL, &dwCount) != ERROR_SUCCESS)
	{
		ATLTRACE(_T("RegQueryValueEx failed for Value %s\n"), szValName);
		return NULL;
	}

	if (!dwCount)
	{
		ATLTRACE(_T("RegQueryValueEx returned 0 bytes\n"));
		return NULL;
	}

	// Not going to Check for fail on CoTaskMemAlloc & RegQueryValueEx as NULL
	// will be returned regardless if anything failed

	LPVOID pData = CoTaskMemAlloc(dwCount);
	RegQueryValueEx(hKey, szValName, NULL, &dwType, (LPBYTE) pData, &dwCount);
	return pData;
}

/////////////////////////////////////////////////////////////////////////////
//

HRESULT CRegParser::GenerateError(UINT nID)
{
	m_re.m_nID   = nID;
	m_re.m_cLines = m_cLines;
	return DISP_E_EXCEPTION;
}


CRegParser::CRegParser(CRegObject* pRegObj)
{
	m_pRegObj           = pRegObj;
	m_pchCur            = NULL;
	m_cLines            = 1;
}

BOOL CRegParser::IsSpace(TCHAR ch)
{
	switch (ch)
	{
		case chSpace:
		case chTab:
		case chCR:
		case chLF:
				return TRUE;
	}

	return FALSE;
}

void CRegParser::IncrementLinePos()
{
	m_pchCur = CharNext(m_pchCur);
	if (chLF == *m_pchCur)
		IncrementLineCount();
}

void CRegParser::SkipWhiteSpace()
{
	while(IsSpace(*m_pchCur))
		IncrementLinePos();
}

HRESULT CRegParser::NextToken(LPTSTR szToken)
{
	USES_CONVERSION;

	UINT ichToken = 0;

	SkipWhiteSpace();

	// NextToken cannot be called at EOS
	if (chEOS == *m_pchCur)
		return GenerateError(IDS_UNEXPECTED_EOS);

	// handle quoted value / key
	if (chQuote == *m_pchCur)
	{
		LPCTSTR szOrig = szToken;

		IncrementLinePos(); // Skip Quote

		while (chEOS != *m_pchCur && !EndOfVar())
		{
			if (chQuote == *m_pchCur) // If it is a quote that means we must skip it
				IncrementLinePos();   // as it has been escaped

			LPTSTR pchPrev = m_pchCur;
			IncrementLinePos();

			if (szToken + sizeof(WORD) >= MAX_VALUE + szOrig)
				return GenerateError(IDS_VALUE_TOO_LARGE);
			for (int i = 0; pchPrev+i < m_pchCur; i++, szToken++)
				*szToken = *(pchPrev+i);
		}

		if (chEOS == *m_pchCur)
		{
			ATLTRACE(_T("NextToken : Unexpected End of File\n"));
			return GenerateError(IDS_UNEXPECTED_EOS);
		}

		*szToken = chEOS;
		IncrementLinePos(); // Skip end quote
	}

	else
	{   // Handle non-quoted ie parse up till first "White Space"
		while (chEOS != *m_pchCur && !IsSpace(*m_pchCur))
		{
			LPTSTR pchPrev = m_pchCur;
			IncrementLinePos();
			for (int i = 0; pchPrev+i < m_pchCur; i++, szToken++)
				*szToken = *(pchPrev+i);
		}

		*szToken = chEOS;
	}
	return S_OK;
}

static BOOL VTFromRegType(LPCTSTR szValueType, VARTYPE& vt)
{
	struct typemap
	{
		LPCTSTR lpsz;
		VARTYPE vt;
	};
	static const typemap map[] = {
		{szStringVal, VT_BSTR},
		{szDwordVal,  VT_I4}
	};

	for (int i=0;i<sizeof(map)/sizeof(typemap);i++)
	{
		if (!lstrcmpi(szValueType, map[i].lpsz))
		{
			vt = map[i].vt;
			return TRUE;
		}
	}

	return FALSE;

}

HRESULT CRegParser::AddValue(CRegKey& rkParent,LPCTSTR szValueName, LPTSTR szToken)
{
	USES_CONVERSION;
	USES_AUTORET;

	TCHAR       szTypeToken[MAX_TYPE];
	VARTYPE     vt;
	LONG        lRes = ERROR_SUCCESS;
	UINT        nIDRes = 0;

	RET_ON_ERROR(NextToken(szTypeToken))
	if (!VTFromRegType(szTypeToken, vt))
	{
		ATLTRACE(_T("%s Type not supported\n"), szTypeToken);
		return GenerateError(IDS_TYPE_NOT_SUPPORTED);
	}

	TCHAR szValue[MAX_VALUE];
	SkipWhiteSpace();
	RET_ON_ERROR(NextToken(szValue));
	long lVal;

	switch (vt)
	{
	case VT_BSTR:
		lRes = rkParent.SetValue(szValue, szValueName);
		ATLTRACE(_T("Setting Value %s at %s\n"), szValue, !szValueName ? _T("default") : szValueName);
		break;
	case VT_I4:
		VarI4FromStr(T2OLE(szValue), 0, 0, &lVal);
		lRes = rkParent.SetValue(lVal, szValueName);
		ATLTRACE(_T("Setting Value %d at %s\n"), lVal, !szValueName ? _T("default") : szValueName);
		break;
	}

	if (ERROR_SUCCESS != lRes)
	{
		nIDRes = IDS_VALUE_SET_FAILED;
		hr = HRESULT_FROM_WIN32(lRes);
	}

	RET_ON_ERROR(NextToken(szToken))

	return S_OK;
}

BOOL CRegParser::CanForceRemoveKey(LPCTSTR szKey)
{
	for (int iNoDel = 0; iNoDel < cbNeverDelete; iNoDel++)
		if (!lstrcmpi(szKey, rgszNeverDelete[iNoDel]))
			 return FALSE;                       // We cannot delete it

	return TRUE;
}

BOOL CRegParser::HasSubKeys(HKEY hkey)
{
	DWORD       cbSubKeys = 0;

	if (FAILED(RegQueryInfoKey(hkey, NULL, NULL, NULL,
							   &cbSubKeys, NULL, NULL,
							   NULL, NULL, NULL, NULL, NULL)))
	{
		ATLTRACE(_T("Should not be here!!\n"));
		_ASSERTE(FALSE);
		return FALSE; // REVIEW:really not a good return for this scenerio!
	}

	return cbSubKeys > 0;
}

BOOL CRegParser::HasValues(HKEY hkey)
{
	DWORD       cbValues = 0;

	LONG lResult = RegQueryInfoKey(hkey, NULL, NULL, NULL,
								  NULL, NULL, NULL,
								  &cbValues, NULL, NULL, NULL, NULL);
	if (ERROR_SUCCESS != lResult)
	{
		ATLTRACE(_T("RegQueryInfoKey Failed "));
		_ASSERTE(FALSE);
		return FALSE;
	}

	if (1 == cbValues)
	{
		DWORD cbData = 0;
		lResult = RegQueryValueEx(hkey, NULL, NULL, NULL, NULL, &cbData);

		if (ERROR_SUCCESS == lResult)
			return !cbData;
		else
			return TRUE;
	}

	return cbValues > 0;
}

HRESULT CRegParser::SkipAssignment(LPTSTR szToken)
{
	USES_AUTORET;
	TCHAR szValue[MAX_VALUE];

	if (*szToken == chEquals)
	{
		RET_ON_ERROR(NextToken(szToken))
		// Skip assignment
		SkipWhiteSpace();
		RET_ON_ERROR(NextToken(szValue));
		RET_ON_ERROR(NextToken(szToken))
	}

	return S_OK;
}


HRESULT CRegParser::RegisterSubkeys(HKEY hkParent, BOOL bRegister, BOOL bInRecovery)
{
	USES_AUTORET;

	CRegKey keyCur;
	TCHAR   szToken[MAX_VALUE];
	LONG    lRes;
	TCHAR   szKey[MAX_VALUE];
	BOOL    bDelete = TRUE;
	BOOL    bRecover = bInRecovery;

	ATLTRACE(_T("Num Els = %d\n"), cbNeverDelete);
	RET_ON_ERROR(NextToken(szToken))  // Should be key name


	while (*szToken != chRightBracket) // Continue till we see a }
	{
		BOOL bTokenDelete = !lstrcmpi(szToken, szDelete);

		if (!lstrcmpi(szToken, szForceRemove) ||
			bTokenDelete)
		{
			RET_ON_ERROR(NextToken(szToken))

			if (bRegister)
			{
				CRegKey rkForceRemove;

				if (StrChr(szToken, chDirSep) != NULL)
					return GenerateError(IDS_COMPOUND_KEY);

				if (CanForceRemoveKey(szToken))
				{
					rkForceRemove.Attach(hkParent);
					rkForceRemove.RecurseDeleteKey(szToken);
					rkForceRemove.Detach();
				}
				if (bTokenDelete)
				{
					RET_ON_ERROR(NextToken(szToken))
					RET_ON_ERROR(SkipAssignment(szToken))
					goto EndCheck;
				}
			}

		}

		if (!lstrcmpi(szToken, szNoRemove))
		{
			bDelete = FALSE;    // set even for register
			RET_ON_ERROR(NextToken(szToken))
		}

		if (!lstrcmpi(szToken, szValToken)) // need to add a value to hkParent
		{
			TCHAR  szValueName[_MAX_PATH];

			RET_ON_ERROR(NextToken(szValueName))
			RET_ON_ERROR(NextToken(szToken))

			if (*szToken != chEquals)
				return GenerateError(IDS_EXPECTING_EQUAL);

			if (bRegister)
			{
				CRegKey rk;

				rk.Attach(hkParent);
				hr = AddValue(rk, szValueName, szToken);
				rk.Detach();

				if (FAILED(hr))
					return hr;

				goto EndCheck;
			}
			else
			{
				if (!bRecover)
				{
					ATLTRACE(_T("Deleting %s\n"), szValueName);
					REPORT_ERROR(_T("RegDeleteValue"), RegDeleteValue(hkParent, szValueName))
				}

				RET_ON_ERROR(SkipAssignment(szToken)) // Strip off type
				continue;  // can never have a subkey
			}
		}

		if (StrChr(szToken, chDirSep) != NULL)
			return GenerateError(IDS_COMPOUND_KEY);

		if (bRegister)
		{
			lRes = keyCur.Open(hkParent, szToken, KEY_ALL_ACCESS);
			if (ERROR_SUCCESS != lRes)
			{
				// Failed all access try read only
				lRes = keyCur.Open(hkParent, szToken, KEY_READ);
				if (ERROR_SUCCESS != lRes)
				{
					// Finally try creating it
					ATLTRACE(_T("Creating key %s\n"), szToken);
					lRes = keyCur.Create(hkParent, szToken);
					if (ERROR_SUCCESS != lRes)
						return GenerateError(IDS_CREATE_KEY_FAILED);
				}
			}

			RET_ON_ERROR(NextToken(szToken))

			if (*szToken == chEquals)
				RET_ON_ERROR(AddValue(keyCur, NULL, szToken)) // NULL == default
		}
		else
		{
			if (!bRecover && keyCur.Open(hkParent, szToken) != ERROR_SUCCESS)
				bRecover = TRUE;

#ifdef _DEBUG
			if (!bRecover)
				ATLTRACE(_T("Opened Key %s\n"), szToken);
			else
				ATLTRACE(_T("Ignoring Open key on %s : In Recovery mode\n"), szToken);
#endif _DEBUG

			// Remember Subkey
			lstrcpyn(szKey, szToken, _MAX_PATH);

			// If in recovery mode

			if (bRecover || HasSubKeys(keyCur) || HasValues(keyCur))
			{
				RET_ON_ERROR(NextToken(szToken))
				RET_ON_ERROR(SkipAssignment(szToken))

				if (*szToken == chLeftBracket)
					RET_ON_ERROR(RegisterSubkeys(keyCur.m_hKey, bRegister, bRecover))

				if (!bRecover && HasSubKeys(keyCur))
				{
					// See if the KEY is in the NeverDelete list and if so, don't
					if (CanForceRemoveKey(szKey))
					{
						ATLTRACE(_T("Deleting non-empty subkey %s by force\n"), szKey);
						REPORT_ERROR(_T("RecurseDeleteKey"), keyCur.RecurseDeleteKey(szKey))
					}
					RET_ON_ERROR(NextToken(szToken))
					continue;
				}
			}

			if (!bRecover && keyCur.Close() != ERROR_SUCCESS)
			   return GenerateError(IDS_CLOSE_KEY_FAILED);

			if (!bRecover && bDelete)
			{
				ATLTRACE(_T("Deleting Key %s\n"), szKey);
				REPORT_ERROR(_T("RegDeleteKey"), RegDeleteKey(hkParent, szKey))
			}

			RET_ON_ERROR(NextToken(szToken))
			RET_ON_ERROR(SkipAssignment(szToken))
		}

EndCheck:

		if (bRegister)
		{
			if (*szToken == chLeftBracket)
			{
				RET_ON_ERROR(RegisterSubkeys(keyCur.m_hKey, bRegister, FALSE))
				RET_ON_ERROR(NextToken(szToken))
			}
		}
	}

	return S_OK;
}

class CParseBuffer
{
public:
	int nPos;
	int nSize;
	LPTSTR p;
	CParseBuffer(int nInitial);
	~CParseBuffer() {CoTaskMemFree(p);}
	BOOL AddChar(TCHAR ch);
	LPTSTR Detach();

};

LPTSTR CParseBuffer::Detach()
{
	LPTSTR lp = p;
	p = NULL;
	return lp;
}

CParseBuffer::CParseBuffer(int nInitial)
{
	nPos = 0;
	nSize = nInitial;
	p = (LPTSTR) CoTaskMemAlloc(nSize*sizeof(TCHAR));
}

BOOL CParseBuffer::AddChar(TCHAR ch)
{
	if (nPos == nSize) // realloc
	{
		nSize *= 2;
		p = (LPTSTR) CoTaskMemRealloc(p, nSize*sizeof(TCHAR));
	}
	p[nPos++] = ch;
	return TRUE;
}

HRESULT CRegParser::PreProcessBuffer(LPTSTR lpszReg, LPTSTR* ppszReg)
{
	USES_CONVERSION;
	_ASSERTE(lpszReg != NULL);
	_ASSERTE(ppszReg != NULL);
	*ppszReg = NULL;
	int nSize = lstrlen(lpszReg)*2;
	CParseBuffer pb(nSize);
	m_pchCur = lpszReg;
	HRESULT hr = S_OK;

	while (*m_pchCur != NULL) // look for end
	{
		if (*m_pchCur == _T('%'))
		{
			IncrementLinePos();
			if (*m_pchCur == _T('%'))
				pb.AddChar(*m_pchCur);
			else
			{
				LPTSTR lpszNext = StrChr(m_pchCur, _T('%'));
				if (lpszNext == NULL)
				{
					ATLTRACE(_T("Error no closing % found\n"));
					hr = GenerateError(IDS_UNEXPECTED_EOS);
					break;
				}
				int nLength = lpszNext - m_pchCur;
				if (nLength > 31)
				{
					hr = E_FAIL;
					break;
				}
				TCHAR buf[32];
				lstrcpyn(buf, m_pchCur, nLength+1);
				LPTSTR lpszVar = m_pRegObj->StrFromMap(buf);
				if (lpszVar == NULL)
				{
					hr = GenerateError(IDS_NOT_IN_MAP);
					break;
				}
				while (*lpszVar)
				{
					pb.AddChar(*lpszVar);
					lpszVar++;
				}
				while (m_pchCur != lpszNext)
					IncrementLinePos();
			}
		}
		else
			pb.AddChar(*m_pchCur);
		IncrementLinePos();
	}
	pb.AddChar(NULL);
	if (SUCCEEDED(hr))
		*ppszReg = pb.Detach();
	return hr;
}


HRESULT CRegParser::RegisterBuffer(LPTSTR szBuffer, BOOL bRegister)
{
	TCHAR   szToken[_MAX_PATH];
	HRESULT hr = S_OK;

	LPTSTR szReg;
	hr = PreProcessBuffer(szBuffer, &szReg);
	if (FAILED(hr))
		return hr;

	m_pchCur = szReg;

	// Preprocess szReg

	while (chEOS != *m_pchCur)
	{
		hr = NextToken(szToken);
		if (FAILED(hr))
			break;

		HKEY hkBase;
		if ((hkBase = HKeyFromString(szToken)) == NULL)
		{
			ATLTRACE(_T("HKeyFromString failed on %s\n"), szToken);
			hr = GenerateError(IDS_BAD_HKEY);
			break;
		}

		RET_ON_ERROR(NextToken(szToken))

		if (chLeftBracket != *szToken)
		{
			ATLTRACE(_T("Syntax error, expecting a {, found a %s\n"), szToken);
			hr = GenerateError(IDS_MISSING_OPENKEY_TOKEN);
			break;
		}
		if (bRegister)
		{
			LPTSTR szRegAtRegister = m_pchCur;
			HRESULT hr = RegisterSubkeys(hkBase, bRegister);
			if (FAILED(hr))
			{
				ATLTRACE(_T("Failed to register, cleaning up!\n"));
				m_pchCur = szRegAtRegister;
				RegisterSubkeys(hkBase, FALSE);
				break;
			}
		}
		else
		{
			hr = RegisterSubkeys(hkBase, bRegister);
			if (FAILED(hr))
				break;
		}

		SkipWhiteSpace();
	}
	CoTaskMemFree(szReg);
	return hr;
}

HRESULT CExpansionVector::Add(LPCOLESTR lpszKey, LPCOLESTR lpszValue)
{
	USES_CONVERSION;
	HRESULT hr = S_OK;

	EXPANDER*   pExpand = new EXPANDER;
	pExpand->bstrKey = SysAllocString(lpszKey);
	pExpand->bstrValue = SysAllocString(lpszValue);
#ifndef OLE2ANSI
#ifndef UNICODE
	LPSTR p = OLE2T(lpszValue);
	pExpand->lpszValue = (LPSTR) CoTaskMemAlloc(lstrlen(p)+1*sizeof(char));
	lstrcpy(pExpand->lpszValue, p);
#endif
#endif

	if (m_cEls == m_nSize)
	{
		m_nSize*=2;
		m_p = (EXPANDER**)realloc(m_p, m_nSize*sizeof(EXPANDER*));
	}

	if (NULL != m_p)
	{
		m_p[m_cEls] = pExpand;
		m_cEls++;
	}
	else
		hr = E_OUTOFMEMORY;

	return hr;

}

LPTSTR CExpansionVector::Find(LPTSTR lpszKey)
{
	USES_CONVERSION;
	for (int iExpand = 0; iExpand < m_cEls; iExpand++)
	{
		if (!lstrcmpi(OLE2T(m_p[iExpand]->bstrKey), lpszKey)) //are equal
#if defined(UNICODE) | defined(OLE2ANSI)
			return m_p[iExpand]->bstrValue;
#else
			return m_p[iExpand]->lpszValue;
#endif
	}
	return NULL;
}

HRESULT CExpansionVector::ClearReplacements()
{
	for (int iExpand = 0; iExpand < m_cEls; iExpand++)
	{
		EXPANDER* pExp = m_p[iExpand];
		SysFreeString(pExp->bstrKey);
		SysFreeString(pExp->bstrValue);
#ifndef OLE2ANSI
#ifndef UNICODE
		CoTaskMemFree(pExp->lpszValue);
#endif
#endif
		delete pExp;
	}
	m_cEls = 0;
	return S_OK;
}

HRESULT CRegObject::GenerateError(UINT nID, CRegException& re)
{
	re.m_nID    = nID;
	re.m_cLines = -1;

	return DISP_E_EXCEPTION;
}

HRESULT CRegObject::AddReplacement(LPCOLESTR lpszKey, LPCOLESTR lpszItem)
{
	m_csMap.Lock();
	HRESULT hr = m_RepMap.Add(lpszKey, lpszItem);
	m_csMap.Unlock();
	return hr;
}

HRESULT CRegObject::RegisterFromResource(BSTR bstrFileName, LPCTSTR szID,
										 LPCTSTR szType, CRegException& re,
										 BOOL bRegister)
{
	USES_CONVERSION;

	HRESULT     hr;
	CRegParser  parser(this);
	HINSTANCE   hInstResDll;
	HRSRC       hrscReg;
	HGLOBAL     hReg;
	DWORD       dwSize;
	LPSTR       szRegA;
	LPTSTR      szReg;

	hInstResDll = LoadLibraryEx(OLE2T(bstrFileName), NULL, LOAD_LIBRARY_AS_DATAFILE);

	if (NULL == hInstResDll)
	{
		ATLTRACE(_T("Failed to LoadLibrary on %s\n"), OLE2T(bstrFileName));
		hr = HRESULT_FROM_WIN32(GetLastError());
		goto ReturnHR;
	}

	hrscReg = FindResource((HMODULE)hInstResDll, szID, szType);

	if (NULL == hrscReg)
	{
		ATLTRACE(_T("Failed to FindResource on ID:%s TYPE:%s\n"), szID, szType);
		hr = HRESULT_FROM_WIN32(GetLastError());
		goto ReturnHR;
	}

	hReg = LoadResource((HMODULE)hInstResDll, hrscReg);

	if (NULL == hReg)
	{
		ATLTRACE(_T("Failed to LoadResource \n"));
		hr = HRESULT_FROM_WIN32(GetLastError());
		goto ReturnHR;
	}

	dwSize = SizeofResource((HMODULE)hInstResDll, hrscReg);
	szRegA = (LPSTR)hReg;
	if (szRegA[dwSize] != NULL)
	{
		szRegA = (LPSTR)_alloca(dwSize+1);
		memcpy(szRegA, (void*)hReg, dwSize+1);
		szRegA[dwSize] = NULL;
	}

	szReg = A2T(szRegA);

#ifdef _DEBUG
	OutputDebugString(szReg); //would call ATLTRACE but szReg is > 512 bytes
	OutputDebugString(_T("\n"));
#endif //_DEBUG

	hr = parser.RegisterBuffer(szReg, bRegister);

	if (FAILED(hr))
		re = parser.GetRegException();

ReturnHR:

	if (NULL != hInstResDll)
		FreeLibrary((HMODULE)hInstResDll);
	return hr;
}

static LPCTSTR StringFromResID(VARIANT& var)
{
	CComVariant varTemp;

	if (FAILED(VariantChangeType(&varTemp, &var, VARIANT_NOVALUEPROP, VT_I2)))
		return NULL;

	return MAKEINTRESOURCE(varTemp.iVal);

}

HRESULT CRegObject::ResourceRegister(BSTR bstrFileName, VARIANT varID,
							   VARIANT varType, CRegException& re)
{
	USES_CONVERSION;
	LPCTSTR szID, szType;

	if (VT_BSTR == varID.vt)
		szID = OLE2T(varID.bstrVal);
	else
		szID = StringFromResID(varID);

	if (NULL == szID)
		return E_INVALIDARG;

	if (VT_BSTR == varType.vt)
		szType = OLE2T(varType.bstrVal);
	else
		szType = StringFromResID(varType);

	if (NULL == szType)
		return E_INVALIDARG;

	return RegisterFromResource(bstrFileName, szID, szType, re, TRUE);
}

HRESULT CRegObject::ResourceUnregister(BSTR bstrFileName, VARIANT varID,
							   VARIANT varType, CRegException& re)
{
	USES_CONVERSION;
	LPCTSTR szID, szType;

	if (VT_BSTR == varID.vt)
		szID = OLE2T(varID.bstrVal);
	else
		szID = StringFromResID(varID);

	if (NULL == szID)
		return E_INVALIDARG;

	if (VT_BSTR == varType.vt)
		szType = OLE2T(varType.bstrVal);
	else
		szType = StringFromResID(varType);

	if (NULL == szType)
		return E_INVALIDARG;

	return RegisterFromResource(bstrFileName, szID, szType, re, FALSE);
}

HRESULT CRegObject::RegisterWithString(BSTR bstrData, BOOL bRegister, CRegException& re)
{
	USES_CONVERSION;
	CRegParser  parser(this);


	LPTSTR szReg = OLE2T(bstrData);

#ifdef _DEBUG
	OutputDebugString(szReg); //would call ATLTRACE but szReg is > 512 bytes
	OutputDebugString(_T("\n"));
#endif //_DEBUG

	HRESULT hr = parser.RegisterBuffer(szReg, bRegister);

	if (FAILED(hr))
		re = parser.GetRegException();

	return hr;
}

HRESULT CRegObject::ClearReplacements()
{
	m_csMap.Lock();
	HRESULT hr = m_RepMap.ClearReplacements();
	m_csMap.Unlock();
	return hr;
}

HRESULT CRegObject::DeleteKey(BSTR bstrKey, CRegException& re)
{
	USES_CONVERSION;
	LPTSTR szTail;

	HKEY hkeyRoot = HKeyFromCompoundString(OLE2T(bstrKey), szTail);
	if (NULL == hkeyRoot)
		return GenerateError(IDS_BAD_HKEY, re);

	CRegKey key;
	key.Attach(hkeyRoot);
	LONG lRes = key.RecurseDeleteKey(szTail);
	if (ERROR_SUCCESS != lRes)
		return GenerateError(IDS_DELETE_KEY_FAILED, re);

	return S_OK;
}

HRESULT CRegObject::AddKey(BSTR keyName, CRegException& re)
{
	USES_CONVERSION;

	LPTSTR szTail;

	HKEY hkeyRoot = HKeyFromCompoundString(OLE2T(keyName), szTail);
	if (NULL == hkeyRoot)
		return GenerateError(IDS_BAD_HKEY, re);

	CRegKey key;
	LONG lRes = key.Create(hkeyRoot, szTail);
	if (ERROR_SUCCESS != lRes)
		return GenerateError(IDS_CREATE_KEY_FAILED, re);

	return S_OK;
}

HRESULT CRegObject::SetKeyValue(BSTR keyName, BSTR valueName, VARIANT value,
	CRegException& re, BOOL bCreateKey)
{
	USES_CONVERSION;
	LPTSTR szTail;

	HKEY hkeyRoot = HKeyFromCompoundString(OLE2T(keyName), szTail);
	if (hkeyRoot == NULL)
		return GenerateError(IDS_BAD_HKEY, re);

	CRegKey key;
	LONG lRes;
	if (bCreateKey)
		lRes = key.Create(hkeyRoot, szTail);
	else
		lRes = key.Open(hkeyRoot, szTail);
	if (ERROR_SUCCESS != lRes)
		return GenerateError(IDS_CREATE_KEY_FAILED, re);

	LPTSTR pval =  *valueName == 0 ?    NULL : OLE2T(valueName);

	CComVariant varString;
	BSTR pb = value.bstrVal;
	BYTE*   pData;
	long    lBound, uBound;
	UINT nIDRes = IDS_CONVERT_FAILED;
	HRESULT hr = S_OK;
	switch (value.vt)
	{
		case VT_I2:
			lRes = key.SetValue(value.iVal, pval);
			break;
		case VT_I4:
			lRes = key.SetValue(value.lVal, pval);
			break;
		case VT_R4:
		case VT_R8:
		case VT_BOOL:
		case VT_DATE:
		case VT_CY:
			lRes = ERROR_SUCCESS;
			hr = DISP_E_TYPEMISMATCH;
			nIDRes = IDS_VALUE_SET_FAILED;
			break;
		case VT_BSTR:
			lRes = key.SetValue(OLE2T(pb), pval);
			break;
		case VT_SAFEARRAY|VT_UI1:
			hr = E_FAIL;
			if (SafeArrayGetDim(value.parray) != 1) // Verify 1 Dimension
				break;

			hr = SafeArrayGetLBound(value.parray, 1, &lBound);
			if (FAILED(hr))
				break;

			hr = SafeArrayGetUBound(value.parray, 1, &uBound);
			if (FAILED(hr))
				break;
			hr = SafeArrayAccessData(value.parray, (void**)&pData);
			if (FAILED(hr))
				break;

			lRes = RegSetValueEx(key, pval, 0, REG_BINARY, pData,
				(uBound - lBound) + 1);
			SafeArrayUnaccessData(value.parray);
			break;
		default:
			lRes = ERROR_INVALID_DATA;
	}

	if (ERROR_SUCCESS != lRes)
		return GenerateError(IDS_VALUE_SET_FAILED, re);
	if (FAILED(hr))
		return GenerateError(nIDRes, re);

	return S_OK;
}

HRESULT CRegObject::GetKeyValue(BSTR keyName, BSTR valueName, VARIANT* value, CRegException& re)
{
	USES_CONVERSION;
	LPTSTR      szTail;
	HRESULT     hr;

	HKEY hkeyRoot = HKeyFromCompoundString(OLE2T(keyName), szTail);
	if (NULL == hkeyRoot)
		return GenerateError(IDS_BAD_HKEY, re);

	CRegKey key;
	LONG lRes = key.Open(hkeyRoot, szTail);
	if (ERROR_SUCCESS != lRes)
		return GenerateError(IDS_OPEN_KEY_FAILED, re);

	DWORD dwType;
	LPVOID pData = QueryValue(key.m_hKey, OLE2T(valueName), dwType);
	value->vt = VT_EMPTY;

	if (NULL == pData)
		return S_OK;

	hr = S_OK;
	switch (dwType)
	{
		case REG_DWORD:
			value->vt = VT_I4;
			value->lVal = *((long *) pData);
			break;
		case REG_SZ:
			value->vt = VT_BSTR;
			value->bstrVal = SysAllocString(T2OLE((LPTSTR)pData));
			if (NULL == value->bstrVal)
				hr = E_OUTOFMEMORY;
			break;
		default:
			hr = E_FAIL;
	}

	CoTaskMemFree(pData);

	if (FAILED(hr))
		return GenerateError(IDS_VALUE_GET_FAILED, re);

	return hr;
}

LPTSTR CRegObject::StrFromMap(LPTSTR lpszKey)
{
	m_csMap.Lock();
	LPTSTR lpsz = m_RepMap.Find(lpszKey);
	if (lpsz == NULL) // not found!!
		ATLTRACE(_T("Map Entry not found\n"));
	m_csMap.Unlock();
	return lpsz;
}

HRESULT CRegObject::MemMapAndRegister(BSTR bstrFileName, BOOL bRegister,
									  CRegException& re)
{
	USES_CONVERSION;

	CRegParser  parser(this);

	HANDLE hFile = CreateFile(OLE2T(bstrFileName), GENERIC_READ, 0, NULL,
							  OPEN_EXISTING,
							  FILE_ATTRIBUTE_READONLY,
							  NULL);

	if (NULL == hFile)
	{
		ATLTRACE(_T("Failed to CreateFile on %s\n"), OLE2T(bstrFileName));
		return HRESULT_FROM_WIN32(GetLastError());
	}

	DWORD cbFile = GetFileSize(hFile, NULL); // No HiOrder DWORD required

	HANDLE hMapping = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);

	if (NULL == hMapping)
	{
		ATLTRACE(_T("Failed to CreateFileMapping\n"));
		return HRESULT_FROM_WIN32(GetLastError());
	}

	LPVOID pMap = MapViewOfFile(hMapping, FILE_MAP_READ, 0, 0, 0);

	if (NULL == pMap)
	{
		ATLTRACE(_T("Failed to MapViewOfFile\n"));
		return HRESULT_FROM_WIN32(GetLastError());
	}

	LPTSTR szReg = A2T((char*)pMap);

	if (chEOS != szReg[cbFile]) //ensure buffer is NULL terminated
	{
		ATLTRACE(_T("ERROR : Bad or missing End of File\n"));
		return E_FAIL; // make a real error
	}

#ifdef _DEBUG
	OutputDebugString(szReg); //would call ATLTRACE but szReg is > 512 bytes
	OutputDebugString(_T("\n"));
#endif //_DEBUG

	HRESULT hRes = parser.RegisterBuffer(szReg, bRegister);

	if (FAILED(hRes))
		re = parser.GetRegException();

	UnmapViewOfFile(pMap);
	CloseHandle(hMapping);
	CloseHandle(hFile);

	return hRes;
}
