// Objekte, die verschiedene Suchalgorithmen implementieren
// File: MatchingObjects.h

#if !defined(_MATCHINGOBJECTS_H)
#define _MATCHINGOBJECTS_H

#include <ospace/string/src/regex.h>	// GNU regular expression matcher
#include <ospace/string/regexp.h>

#include "TRiASHelper.h"

///////////////////////////////////////////////////////////////////////////////
// Basisklasse für Matching von String
class CMatchStringBase :
	public CComDualImpl<DMatchString, &IID_DMatchString, &LIBID_TRiASHelperLib,
			TYPELIB_HELPER_VERSION_MAJOR, TYPELIB_HELPER_VERSION_MINOR>
{
protected:
	bool m_fIgnoreCase;
	bool m_fNegateMatch;
	CComBSTR m_bstrToMatch;

public:
		CMatchStringBase(void) : m_fIgnoreCase(false) {}
		~CMatchStringBase(void) {}

// sonstige Member
	STDMETHOD(put_MatchText) (THIS_ BSTR bstrMatching);
	STDMETHOD(get_MatchText) (THIS_ BSTR *pbstrMatching);
	STDMETHOD(get_MatchCase) (THIS_ VARIANT_BOOL *pfMatchCase);
	STDMETHOD(put_MatchCase) (THIS_ VARIANT_BOOL fFlag);
	STDMETHOD(get_NegateMatch) (THIS_ VARIANT_BOOL *pfNegateMatch);
	STDMETHOD(put_NegateMatch) (THIS_ VARIANT_BOOL fNegateMatch);

// Test, ob Objekt initialisiert ist
inline bool IsNotValid (void) { return !m_bstrToMatch; }
};

///////////////////////////////////////////////////////////////////////////////
// Exaktes Matching (mit/ohne CaseTest)
class CMatchPlainTextExakt :
	public CMatchStringBase,
	public CComObjectRoot
{
private:
	bool m_fFullMatch;
	bool m_fExistanceOnly;
	bool m_fTestBOB;
	size_t m_iMatchLen;

public:
		CMatchPlainTextExakt (void) 
			: m_fFullMatch(true), m_fExistanceOnly(false) {}
		~CMatchPlainTextExakt (void) {}

	BEGIN_COM_MAP(CMatchPlainTextExakt)
		COM_INTERFACE_ENTRY(DMatchString)
		COM_INTERFACE_ENTRY2(IDispatch, DMatchString)
	END_COM_MAP()

// DMatchString methods
	STDMETHOD(MatchString) (THIS_ BSTR bstrToMatch, int *piMatched);
	STDMETHOD(put_MatchText) (THIS_ BSTR bstrMatching);
	STDMETHOD(put_MatchCase) (THIS_ VARIANT_BOOL fFlag);

	void SetFullMatch (bool fFlag) { m_fFullMatch = fFlag ? true : false; }
	bool GetFullMatch (void) { return m_fFullMatch ? true : false; }

	void SetExistanceOnly (bool fFlag) { m_fExistanceOnly = fFlag ? true : false; }
	bool GetExistanceOnly (void) { return m_fExistanceOnly ? true : false; }

	void SetMatchBOB (bool fFlag) { m_fTestBOB = fFlag ? true : false; }
	bool GetMatchBOB (void) { return m_fTestBOB ? true : false; }
};

///////////////////////////////////////////////////////////////////////////////
// RegExpression Matching (mit/ohne CaseTest)
class CRegExpr : 
	public os_regexp 
{
public:
		~CRegExpr (void);

	void MatchCase (bool fMatchCase);
};

class CMatchRegExprExakt :
	public CMatchStringBase,
	public CComObjectRoot
{
private:
	CRegExpr m_regxToMatch;
	bool m_fFullMatch;

public:
		CMatchRegExprExakt (void) {}
		~CMatchRegExprExakt (void) {}

	BEGIN_COM_MAP(CMatchRegExprExakt)
		COM_INTERFACE_ENTRY(DMatchString)
		COM_INTERFACE_ENTRY2(IDispatch, DMatchString)
	END_COM_MAP()

// DMatchString methods
	STDMETHOD(MatchString) (THIS_ BSTR bstrToMatch, int *piMatched);

	STDMETHOD(put_MatchText) (THIS_ BSTR bstrMatching);
	STDMETHOD(put_MatchCase) (THIS_ VARIANT_BOOL fFlag);

	void SetFullMatch (bool fFlag) { m_fFullMatch = fFlag ? true : false; }
	bool GetFullMatch (void) { return m_fFullMatch ? true : false; }
};

///////////////////////////////////////////////////////////////////////////////
// Fuzzy Matching
const int COMP_LEN = 20;
const int ARR_SIZE = COMP_LEN + 1;

const int addition = 1;		// change constants in this block
const int change   = 2;		// of four lines if needed.
const int deletion = 3;

inline int SMALLEST_OF (int x, int y, int z)
{ 
	return ((x < y) ? min(x, z) : min(y, z)); 
}

class CMatchFuzzy :
	public CMatchStringBase,
	public CComObjectRoot
{
public:
	inline int ZERO_IF_EQUAL (BSTR bstr, int x, int y)
		{ return (towupper(m_bstrToMatch[x-1]) == towupper(bstr[y-1]) ? 0 : change); }

private:
	int m_distance[ARR_SIZE][ARR_SIZE];
	int m_iLen;
	int m_iThreshold;

public:
		CMatchFuzzy (void) {}
		~CMatchFuzzy (void) {}

	BEGIN_COM_MAP(CMatchFuzzy)
		COM_INTERFACE_ENTRY(DMatchString)
		COM_INTERFACE_ENTRY2(IDispatch, DMatchString)
	END_COM_MAP()

// DMatchString methods
	STDMETHOD(MatchString) (THIS_ BSTR bstrToMatch, int *piMatched);

	STDMETHOD(put_MatchText) (THIS_ BSTR bstrMatching);
};

#endif // _MATCHINGOBJECTS_H
