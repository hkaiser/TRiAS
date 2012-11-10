#ifndef __STATREG_H
#define __STATREG_H

#define USES_AUTORET HRESULT hr
///////////////////////////////////////
#define RET_ON_ERROR(x) \
		if (FAILED(hr = x))\
			return hr;
///////////////////////////////////////
#ifdef _DEBUG
#define REPORT_ERROR(name, func) \
		if (func != ERROR_SUCCESS)\
			ATLTRACE(_T("NON CRITICAL ERROR : %s failed\n"), name);
#else //!_DEBUG
#define REPORT_ERROR(name, func) \
		func;
#endif //_DEBUG

///////////////////////////////////////
#define MAX_TYPE            MAX_VALUE
#define MAX_VALUE           4096

const TCHAR  chSemiColon         = _T(';');
const TCHAR  chDirSep            = _T('\\');
const TCHAR  chComma             = _T(',');
const TCHAR  chDelete            = _T('~');
const TCHAR  chEOS               = _T('\0');
const TCHAR  chTab               = _T('\t');
const TCHAR  chLF                = _T('\n');
const TCHAR  chCR                = _T('\r');
const TCHAR  chSpace             = _T(' ');
const TCHAR  chRightBracket      = _T('}');
const TCHAR  chLeftBracket       = _T('{');
const TCHAR  chVarLead           = _T('%');
const TCHAR  chQuote             = _T('\'');
const TCHAR  chEquals            = _T('=');
//const LPCTSTR  szRightBracket  = _T("}");
//const LPCTSTR  szLeftBracket   = _T("{");
//const LPCTSTR  szEquals            = _T("=");
//const LPCTSTR  szDirSep          = _T("\\");
const LPCTSTR  szStringVal       = _T("S");
const LPCTSTR  szDwordVal        = _T("D");
const LPCTSTR  szBinaryVal       = _T("B");
const LPCTSTR  szValToken        = _T("Val");
const LPCTSTR  szForceRemove     = _T("ForceRemove");
const LPCTSTR  szNoRemove        = _T("NoRemove");
const LPCTSTR  szDelete          = _T("Delete");

#define chEscape chDirSep

#define IDS_REGISTRAR_DESC              48
#define IDS_NOT_IN_MAP                  49
#define IDS_UNEXPECTED_EOS              50
#define IDS_VALUE_SET_FAILED            51
#define IDS_RECURSE_DELETE_FAILED       52
#define IDS_EXPECTING_EQUAL             53
#define IDS_CREATE_KEY_FAILED           54
#define IDS_DELETE_KEY_FAILED           55
#define IDS_OPEN_KEY_FAILED             56
#define IDS_CLOSE_KEY_FAILED            57
#define IDS_UNABLE_TO_COERCE            58
#define IDS_BAD_HKEY                    59
#define IDS_MISSING_OPENKEY_TOKEN       60
#define IDS_CONVERT_FAILED              61
#define IDS_TYPE_NOT_SUPPORTED          62
#define IDS_COULD_NOT_CONCAT            63
#define IDS_COMPOUND_KEY                64
#define IDS_INVALID_MAPKEY              65
#define IDS_UNSUPPORTED_VT              66
#define IDS_VALUE_GET_FAILED            67
#define IDS_VALUE_TOO_LARGE             68
#define IDS_MISSING_VALUE_DELIMETER     69
#define IDS_DATA_NOT_BYTE_ALIGNED       70

typedef struct tagExpander
{
	BSTR    bstrKey;
	BSTR    bstrValue;
#ifndef OLE2ANSI
#ifndef UNICODE
	LPSTR   lpszValue;
#endif
#endif
}EXPANDER;

class CExpansionVector
{
public:
	CExpansionVector()
	{
		m_cEls = 0;
		m_nSize=10;
		m_p=(EXPANDER**)malloc(m_nSize*sizeof(EXPANDER*));
	}
	HRESULT Add(LPCOLESTR lpszKey, LPCOLESTR lpszValue);
	LPTSTR Find(LPTSTR lpszKey);
	HRESULT ClearReplacements();


private:
	EXPANDER** m_p;
	int m_cEls;
	int m_nSize;
};

class CRegException
{
public:
	CRegException()
	{
		m_nID       = 0;
		m_cLines    = 0;
	}

	UINT        m_nID;
	int         m_cLines; // Line number where error occured

	void operator=(const CRegException& re)
	{
		m_nID       = re.m_nID;
		m_cLines    = re.m_cLines;
	}

};

class CRegObject
{
public:

	~CRegObject(){ClearReplacements();}

	// Map based methods
	HRESULT AddReplacement(LPCOLESTR lpszKey, LPCOLESTR lpszItem);
	HRESULT ClearReplacements();
	LPTSTR StrFromMap(LPTSTR lpszKey);

	// Register via a given mechanism
	HRESULT ResourceRegister(BSTR bstrFileName, VARIANT varID, VARIANT varType, CRegException& re);
	HRESULT ResourceUnregister(BSTR bstrFileName, VARIANT varID, VARIANT varType, CRegException& re);
	HRESULT FileRegister(BSTR bstrFileName, CRegException& re);
	HRESULT FileUnregister(BSTR bstrFileName, CRegException& re);
	HRESULT StringRegister(BSTR bstrData, CRegException& re);
	HRESULT StringUnregister(BSTR bstrData, CRegException& re);

	// Operate on single key methods
	static HRESULT DeleteKey(BSTR bstrKey, CRegException& re);
	static HRESULT AddKey(BSTR keyName, CRegException& re);
	static HRESULT GetKeyValue(BSTR keyName, BSTR valueName, VARIANT* value, CRegException& re);
	static HRESULT SetKeyValue(BSTR keyName, BSTR valueName, VARIANT value,
		CRegException& re, BOOL bCreateKey);

protected:

	HRESULT MemMapAndRegister(BSTR bstrFileName, BOOL bRegister, CRegException& re);
	HRESULT RegisterFromResource(BSTR bstrFileName, LPCTSTR szID, LPCTSTR szType,
								 CRegException& re, BOOL bRegister);
	HRESULT RegisterWithString(BSTR bstrData, BOOL bRegister, CRegException& re);


	static HRESULT GenerateError(UINT nID, CRegException& re);

	CExpansionVector                                m_RepMap;
	CComObjectThreadModel::AutoCriticalSection      m_csMap;
};


class CRegParser
{
public:
	CRegParser(CRegObject* pRegObj);

	HRESULT PreProcessBuffer(LPTSTR lpszReg, LPTSTR* ppszReg);

	HRESULT         RegisterBuffer(LPTSTR szReg, BOOL bRegister);
	CRegException&  GetRegException() { return m_re; }

protected:

	void    SkipWhiteSpace();
	HRESULT NextToken(LPTSTR szToken);
	HRESULT AddValue(CRegKey& rkParent,LPCTSTR szValueName, LPTSTR szToken);
	BOOL    CanForceRemoveKey(LPCTSTR szKey);
	BOOL    HasSubKeys(HKEY hkey);
	BOOL    HasValues(HKEY hkey);
	HRESULT RegisterSubkeys(HKEY hkParent, BOOL bRegister, BOOL bInRecovery = FALSE);
	BOOL    IsSpace(TCHAR ch);
	void    IncrementLinePos();
	void    IncrementLineCount(){m_cLines++;}


	LPTSTR  m_pchCur;
	int     m_cLines;

	CRegObject*     m_pRegObj;
	CRegException   m_re;

private:

	HRESULT GenerateError(UINT nID);
	HRESULT HandleReplacements(LPTSTR& szToken);
	HRESULT SkipAssignment(LPTSTR szToken);

	BOOL    EndOfVar() { return chQuote == *m_pchCur && chQuote != *CharNext(m_pchCur); }

};

inline HRESULT CRegObject::FileRegister(BSTR bstrFileName, CRegException& re)
{
	return MemMapAndRegister(bstrFileName, TRUE, re);
}

inline HRESULT CRegObject::FileUnregister(BSTR bstrFileName, CRegException& re)
{
	return MemMapAndRegister(bstrFileName, FALSE, re);
}

inline HRESULT CRegObject::StringRegister(BSTR bstrData, CRegException& re)
{
	return RegisterWithString(bstrData, TRUE, re);
}

inline HRESULT CRegObject::StringUnregister(BSTR bstrData, CRegException& re)
{
	return RegisterWithString(bstrData, FALSE, re);
}


#endif //__STATREG_H
