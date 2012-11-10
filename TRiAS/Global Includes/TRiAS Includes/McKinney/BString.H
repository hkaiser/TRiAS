#ifndef _MCKINNEY_BSTRING_H_D9F3E660_235C_11d2_8F8E_0060085FC1CE
#define _MCKINNEY_BSTRING_H_D9F3E660_235C_11d2_8F8E_0060085FC1CE

#if !defined(_OLETYPE_H_D9F3E660_235C_11d2_8F8E_0060085FC1CE)
#error "You must include this file with OleType.h"
#endif

#include "OleType.h"
#include "AtlConv.h"

/////////////////////////////////////////////////////////////////////////////
// Strings

#ifdef _DEBUG
#define MC_PADCHAR '@'
#else
#define MC_PADCHAR '\0'
#endif

// Some macros for casting and text conversion
typedef WCHAR       _WCHAR;
typedef CHAR        _CHAR;
#define _WTEXT(t)   LPCWSTR(L ## t)
#define _W(t)       LPCWSTR(L ## t)
#define _WC(c)      WCHAR(L ## c)
#define _NTEXT(t)   LPCSTR(t)
#define _N(t)       LPCSTR(t)
#define _BTEXT(t)   String(_W(t))
#define _B(t)       String(_W(t))
#define WNULL       LPCWSTR(NULL)
#define BNULL       String(WNULL)

inline BSTR SysAllocStringA(LPCSTR sz) {
	USES_CONVERSION;
	return ::SysAllocString( A2W(sz) );
}
inline BSTR SysAllocStringLenA(LPCSTR sz, unsigned cch) {
	USES_CONVERSION;
	return SysAllocStringLen( A2W(sz), cch );
}

typedef Long FindFlags;
const FindFlags ffNone = 0x0;
const FindFlags ffReverse = 0x1;
const FindFlags ffIgnoreCase = 0x2;

//@B String1
class String {
//    friend class Buffer;
public:
// Constructors
    String();
    String(const String& s);
    // Danger! C++ can't tell the difference between BSTR and LPWSTR. If
    // you pass LPWSTR to this constructor, you'll get very bad results,
    // so don't. Instead cast to constant before assigning.
    String(BSTR bs);
    // Any non-const LPSTR or LPWSTR should be cast to LPCSTR or LPCWSTR
    // so that it comes through here
    String(LPCSTR sz);
    String(LPCWSTR wsz);
    // Filled with given character (default -1 means unitialized allocate)
    String(int cch, WCHAR wch = WCHAR(-1));

// Destructor
    ~String();
//@E String1

// Assignment
	const String& operator=( const String& s ) {
		::SysFreeString( m_bs );
		m_bs = ::SysAllocString( s.m_bs );
		return *this;
	}
    // BSTR only -- use const version for character strings
    const String& operator=(const BSTR& bs) {
		::SysFreeString( m_bs );
		m_bs = ::SysAllocString( bs );
		return *this;
	}
    // Cast LPSTR to LPCSTR
    const String& operator=(LPCSTR sz) {
		::SysFreeString(m_bs);
		m_bs = A2WBSTR(sz);
		return *this;
	}
    // Cast LPWSTR to LPCWSTR
    const String& operator=(const LPCWSTR& wsz) {
		::SysFreeString(m_bs);
		m_bs = ::SysAllocString(wsz);
		return *this;
	}
    const String& operator=(CHAR ch);
    const String& operator=(WCHAR wch);

// Type casts
	operator BSTR() const {					// as a const OLE BSTR
		return (BSTR)m_bs;
	}
    operator BSTR() {						// as an OLE BSTR
	    return ::SysAllocString(m_bs);
	}
    operator LPCSTR();						// as a const ANSI string
    operator LPCWSTR() {					// as a const Unicode string
	    return m_bs;
	}

// Attributes & Operations
	int Length() const {
		return ::SysStringLen(m_bs);
	}
	int LengthZ() const {
		return wcslen(m_bs);
	}
	BOOL IsEmpty() {
		return 0 == ::SysStringLen(m_bs);
	}
	BOOL IsNull() {
		return m_bs == NULL;
	}
	void Empty() {
//    DestroyA();
		if( 0 == ::SysReAllocString(&m_bs, L"") )
			throw E_OUTOFMEMORY;
	}
	void Nullify() {
//    DestroyA();
		if( 0 == ::SysReAllocString(&m_bs, NULL) )
			throw E_OUTOFMEMORY;
	}
    String& NullIfEmpty();             // Return null for empty (handy for APIs)

	BSTR Detach() {
		BSTR s = m_bs;
		m_bs = NULL;
		return s;
	}

    // Adjust length in place
    void Resize(Long cch);
    // Adjust length in place to first null
    void ResizeZ();
    // Resize a string, filling it with PADCHAR
    void Fill(int cch, WCHAR wch = WCHAR(MC_PADCHAR));

    // Indexing
    WCHAR& operator[](int i);

    // String concatenation
    const String & operator+=(const String& string);
    const String & operator+=(WCHAR wch);
    const String & operator+=(CHAR ch);
    const String & operator+=(LPCWSTR wsz);
    const String & operator+=(LPCSTR sz);

    friend String operator+(const String& string1, const String& string2);
    friend String operator+(const String& string, const WCHAR wch);
    friend String operator+(const WCHAR wch, const String& string);
    friend String operator+(const String& string, const CHAR ch);
    friend String operator+(const CHAR ch, const String& string);
    friend String operator+(const String& string, BSTR bs);
    friend String operator+(BSTR bs, const String& string);
    friend String operator+(const String& string, LPCWSTR wsz);
    friend String operator+(const String& string, LPCSTR sz);
    friend String operator+(LPCWSTR wsz, const String& string);
    friend String operator+(LPCSTR sz, const String& string);

// String comparison

    int Compare(LPCWSTR wsz) const;

    int CompareNoCase(LPCWSTR wsz) const;

    // Collate is often slower than Compare but is MBSC/Unicode
    //  aware as well as locale-sensitive with respect to sort order.
    int Collate(LPCWSTR wsz) const;

// SuString extraction
    String Mid(Long nFirst, Long nCount) const;
    String Mid(Long nFirst) const;
    String Left(Long nCount) const;
    String Right(Long nCount) const;

// Upper/lower/reverse conversion
    // Basic names
    String UCase() {
		String	S( m_bs );
		_wcsupr( S.m_bs );
		return S;
	}
    String LCase() const {
		String	S( m_bs );
		_wcslwr( S.m_bs );
		return S;
	}
//    const String & Reverse();

// Trim
    const String & RTrim();
    const String & LTrim();
    const String & Trim();

// Searching (return starting index, or 0 if not found)
    // like "C" strstr
    int Find(String& s, FindFlags ff = ffNone, Long iStart = -1) const;
    int Find(LPCWSTR wsz, FindFlags ff = ffNone, Long iStart = -1) const;
    int Find(LPCSTR sz, FindFlags ff = ffNone, Long iStart = -1) const;
    // Like "C" strchr
    int Find(WCHAR wch, FindFlags ff = ffNone, Long iStart = -1) const;
    int Find(CHAR ch, FindFlags ff = ffNone, Long iStart = -1) const;

    friend ostream& operator<<(ostream& os, String& s);

//@B String2
private:
    BSTR   m_bs;            // The Unicode data
//    LPSTR  m_pch;           // ANSI representation of it
    Boolean m_fDestroy;     // Destruction flag

    // Implementation helpers
    void Concat(int c, LPCWSTR wsz);
    void DestroyW();
//    void DestroyA();

};
//@E String2

// Operators
BOOL operator==(const String& s1, const String& s2);
BOOL operator!=(const String& s1, const String& s2);
BOOL operator<(const String& s1, const String& s2);
BOOL operator>(const String& s1, const String& s2);
BOOL operator>=(const String& s1, const String& s2);
BOOL operator<=(const String& s1, const String& s2);

String UCase(String& s);
String LCase(String& s);
String Reverse(String& s);

String RTrim(String& s);
String LTrim(String& s);
String Trim(String& s);

WCHAR CharToWChar(CHAR ch);
CHAR WCharToChar(WCHAR wch);

WCHAR *wcsichr(const WCHAR *wsz, WCHAR wch);
WCHAR *wcsrichr(const WCHAR *wsz, WCHAR wch, long iStart = -1);
WCHAR *wcsrchr(const WCHAR *wsz, WCHAR wch, long iStart = -1);
       
WCHAR *wcsistr(const WCHAR *wsz, const WCHAR *wszFind);
WCHAR *wcsrstr(const WCHAR *wsz, const WCHAR *wszFind, long iStart = -1);
WCHAR *wcsristr(const WCHAR *wsz, const WCHAR *wszFind, long iStart = -1);

/*
// Buffer object for non-const string parameters
class Buffer
{
public:
// Constructor
    Buffer(String& s);
    Buffer(String& s, Long c);

// Destructor
    ~Buffer();

// Conversion operator
    operator LPSTR();
    operator LPWSTR();

private:
    String * m_ps;

// No assignment allowed (declared private, but not defined)
    Buffer& operator=(const Buffer&);
    Buffer(const Buffer&);
};
*/
// iostream helpers

// manipulator for CrLf sequence
inline ostream& __cdecl endcl(ostream& os) { return os << "\r\n" << flush; }
ostream& operator<<(ostream& os, WCHAR wch);

inline String::String()
	: m_bs(::SysAllocString(NULL)), /*m_pch(NULL),*/ m_fDestroy(True)
{
}

inline String::String(const String& s)
	: m_bs(::SysAllocString(s.m_bs)), /*m_pch(NULL),*/ m_fDestroy(True)
{
}

// Convert BSTR to String
inline String::String(BSTR bs)
	: m_bs(::SysAllocString(bs)), /*m_pch(NULL),*/ m_fDestroy(False)
{
}

inline String::String(LPCWSTR wsz)
	: m_bs(::SysAllocString(wsz)), /*m_pch(NULL),*/ m_fDestroy(True)
{
}
inline String::String(LPCSTR sz)
	: m_bs(SysAllocStringA(sz)), /*m_pch(NULL),*/ m_fDestroy(True)
{
}
//@E StringCon

//@B StringDes
inline String::~String() {
    DestroyW();
}

// Invalidate ANSI buffer
/*
inline void String::DestroyA()
{
    if (m_pch) {
        delete[] m_pch;
        m_pch = NULL;
    }
}
*/
inline void String::DestroyW( ) {
	::SysFreeString( m_bs );
	m_bs = NULL;
}
//@E StringDes


inline void String::Resize(Long cch) {
//    DestroyA();
    if(::SysReAllocStringLen(&m_bs, m_bs, cch) == 0) throw E_OUTOFMEMORY;
}

inline void String::ResizeZ() {
    Resize(LengthZ());
}

inline const String& String::operator+=(const String& s) {
    Concat(s.Length(), s.m_bs);
    return *this;
}

inline const String& String::operator+=(WCHAR wch) {
    Concat(1, &wch);
    return *this;
}

inline const String& String::operator+=(LPCWSTR wsz) {
    Concat(wcslen(wsz), wsz);
    return *this;
}

inline String String::Mid(Long i) const {
    return Mid(i, Length() - i + 1);
}

inline const String & String::Trim() {
    RTrim();
    LTrim();
    return *this;
}

inline int String::Find(String& s, FindFlags ff, Long iStart) const {
    return (Find(s.m_bs, ff, iStart));
}

inline int String::Find(LPCSTR sz, FindFlags ff, Long iStart) const {
    return (Find(String(sz), ff, iStart));
}

inline int String::Find(CHAR ch, FindFlags ff, Long iStart) const {
    return (Find(CharToWChar(ch), ff, iStart));
}

inline int String::Compare(LPCWSTR s ) const
	{ return wcscmp( m_bs, s ); }

inline BOOL operator==(const String& s1, const String& s2)
    { return s1.Compare(s2) == 0; }
inline BOOL operator==(const String& s1, const BSTR& s2)
    { return s1.Compare(s2) == 0; }
inline BOOL operator!=(const String& s1, const String& s2)
    { return s1.Compare(s2) != 0; }
inline BOOL operator!=(const String& s1, const BSTR& s2)
    { return s1.Compare(s2) != 0; }
inline BOOL operator<(const String& s1, const String& s2)
    { return s1.Compare(s2) < 0; }
inline BOOL operator<=(const String& s1, const String& s2)
    { return s1.Compare(s2) <= 0; }
inline BOOL operator>(const String& s1, const String& s2)
    { return s1.Compare(s2) > 0; }
inline BOOL operator>=(const String& s1, const String& s2)
    { return s1.Compare(s2) >= 0; }

/*
inline Buffer::Buffer(String& s) : m_ps(&s)
{
}

inline Buffer::Buffer(String& s, Long c)
{
    s.Resize(c);
    m_ps = &s;
}

inline Buffer::~Buffer()
{
    if (m_ps->m_pch != NULL) {
        mbstowcs(m_ps->m_bs, m_ps->m_pch, size_t(-1));
    }
}

inline Buffer::operator LPWSTR()
{
    return m_ps->m_bs;
}
*/
#endif // _BSTRING_H_D9F3E660_235C_11d2_8F8E_0060085FC1CE
