// ================================================================================================-
//  FILE:  StdString.h
//  AUTHOR:	Joe O'Leary (with outside help noted in comments)
//  REMARKS:
//		This header file declares the CString class.  This string class is
//		derived from the Standard C++ Libarary string classes (one of them)
//		and adds to them the MFC CString conveniences of
//			- UNICODE support and
//			- implicit casts to PCTSTR
//			- loading from resource files
//			- formatting (via Format()) function.
//			- writing to/reading from COM IStream interfaces
//			- Functional objects for use in STL algorithms
//
//		This header also declares our own version of the MFC/ATL UNICODE-MBCS
//		conversion macros.  Our version looks exactly like the Microsoft's to
//		facilitate portability.
//
// COPYRIGHT:
//		1999 Joseph M. O'Leary.  This code is free.  Use it anywhere you want.  Rewrite
//		it, restructure it, whatever you want.  Please don't blame me if it causes your
//		$30 billion dollar satellite to explode.  If you redistribute it in any form, I
//		would appreciate it if you would leave this notice here.
//
//		If you find any bugs, please let me know:
//
//				jmoleary@earthlink.net
// =================================================================================================

#ifndef _STDSTRING_H_
#define _STDSTRING_H_


// Turn off browser references

#ifdef _MSC_VER
	#pragma component(browser, off, references, "CString")
#endif

// Avoid legacy code screw up -- if _UNICODE is defined, then UNICODE must be as well
#if defined (_UNICODE) && !defined (UNICODE)
	#define UNICODE
#endif

// If this class is not being built as a part of the W32 library, then we have not
// yet included W32Base.h so we've got to include and define all the necessary stuff here 

#ifndef _W32BASE_H_

	#define W32DLLSPEC		// define this to nothing (i.e. we're not part of W32.DLL)
	#include <locale>
	#include <TCHAR.H>
	#ifndef STRICT
		#define STRICT
	#endif
	#include <windows.h>

	// In non-MFC builds, ASSERT and VERIFY probably won't be defined, so
	// check to see if they are defined and, if not, define them ourself.

	#ifndef ASSERT
		#include <crtdbg.h>	// probably already included but do it just in case
		#define ASSERT(f) _ASSERTE((f))
	#endif
	#ifndef VERIFY
		#ifdef _DEBUG
			#define VERIFY(x) ASSERT((x))
		#else
			#define VERIFY(x) x
		#endif
	#endif

	#ifndef TRACE
		#define TRACE
	#endif

#endif

#include <functional>		// needed for StdStringLessNoCase, et al

// If this is a recent enough version of VC include comdef.h, we can write many CString
// functions to deal with COM types and compiler support classes like _bstr_t

#if defined (_MSC_VER) && (_MSC_VER >= 1100)
	#include <comdef.h>
	#define STDSTRING_INC_COMDEF		// signal that we #included MS comdef.h file
#endif

// Microsoft defines PCSTR, PCWSTR, etc, but no PCTSTR.  I hate to use the versions
// with the "L" in front of them because that's a leftover from Win 16 days, even
// though it evaluates to the same thing.  Define a PCSTR as an LPCTSTR.

#ifndef PCTSTR_DEFINED
	typedef const TCHAR* PCTSTR;
	#define PCTSTR_DEFINED
#endif

#ifndef PCOLESTR
	#define PCOLESTR	LPCOLESTR
#endif
#ifndef POLESTR
	#define POLESTR		LPOLESTR
#endif

// UNICODE/MBCS conversion macros.  These are made to work just like the MFC/ATL ones.  We
// will not define them if
//		_NO_STDCONVERSION	- the developer explicitly turned them off
//		USES_CONVERSION		- this is an ATL/MFC build and they are already defined

#ifndef _NO_STDCONVERSION
	#if defined (USES_CONVERSION)

		#define _NO_STDCONVERSION	// Let StdString.cpp know it should not compile functions

	#else

		// In MFC builds we can just use the MFC UNICODE conversion macros.
		// In NON-MFC builds will have to define them ourselves

		#include <malloc.h>

		#ifdef _MFC_VER

			#include <afxconv.h>
			#define _NO_STDCONVERSION	// Let StdString.cpp know it should not compile functions

		#else

			// Define our conversion macros to look exactly like Microsoft's to facilitate
			// using this stuff both with and without MFC/ATL

			#ifndef _DEBUG
				#define USES_CONVERSION int _convert; _convert
			#else
				#define USES_CONVERSION int _convert = 0
			#endif

			W32DLLSPEC PWSTR  StdA2WHelper(PWSTR pw, PCSTR pa, int nChars);
			W32DLLSPEC PSTR   StdW2AHelper(PSTR pa, PCWSTR pw, int nChars);

			#define A2W(pa) (\
				((PCSTR)(pa) == NULL) ? NULL : (\
					_convert = (strlen((pa))+1),\
					StdA2WHelper((LPWSTR) alloca(_convert*2), (pa), _convert)))

			#define W2A(pw) (\
				((PCWSTR)(pw) == NULL) ? NULL : (\
					_convert = (wcslen((pw))+1)*2,\
					StdW2AHelper((PSTR) alloca(_convert), (pw), _convert)))

			#define A2CW(pa) ((PCWSTR)A2W((pa)))
			#define W2CA(pw) ((PCSTR)W2A((pw)))

			#ifdef _UNICODE
				#define T2A W2A
				#define A2T A2W
				inline PWSTR T2W(PTSTR p) { return p; }
				inline PTSTR W2T(PWSTR p) { return p; }
				#define T2CA W2CA
				#define A2CT A2CW
				inline PCWSTR T2CW(PCTSTR p) { return p; }
				inline PCTSTR W2CT(PCWSTR p) { return p; }
			#else
				#define T2W A2W
				#define W2T W2A
				inline PSTR T2A(PTSTR p) { return p; }
				inline PTSTR A2T(PSTR p) { return p; }
				#define T2CW A2CW
				#define W2CT W2CA
				inline PCSTR T2CA(PCTSTR p) { return p; }
				inline PCTSTR A2CT(PCSTR p) { return p; }
			#endif // #ifdef _UNICODE

			#if defined(_UNICODE)
			// in these cases the default (TCHAR) is the same as OLECHAR
				inline size_t ocslen(PCOLESTR x) { return wcslen(x); }
				inline OLECHAR* ocscpy(POLESTR dest, PCOLESTR src) { return wcscpy(dest, src); }
				inline PCOLESTR T2COLE(PCTSTR p) { return p; }
				inline PCTSTR OLE2CT(PCOLESTR p) { return p; }
				inline POLESTR T2OLE(PTSTR p) { return p; }
				inline PTSTR OLE2T(POLESTR p) { return p; }
			#elif defined(OLE2ANSI)
			// in these cases the default (TCHAR) is the same as OLECHAR
				inline size_t ocslen(PCOLESTR x) { return strlen(x); }
				inline OLECHAR* ocscpy(POLESTR dest, LPCOLESTR src) { return strcpy(dest, src); }
				inline PCOLESTR T2COLE(PCTSTR p) { return p; }
				inline PCTSTR OLE2CT(PCOLESTR p) { return p; }
				inline POLESTR T2OLE(PTSTR p) { return p; }
				inline PTSTR OLE2T(POLESTR p) { return p; }
			#else
				inline size_t ocslen(PCOLESTR x) { return wcslen(x); }
				inline OLECHAR* ocscpy(POLESTR dest, PCOLESTR src)
				{return (POLESTR) memcpy(dest, src, (wcslen(src)+1)*sizeof(WCHAR));}
				//CharNextW doesn't work on Win95 so we use this
				#define T2COLE(pa)	A2CW((pa))
				#define T2OLE(pa)	A2W((pa))
				#define OLE2CT(po)	W2CA((po))
				#define OLE2T(po)	W2A((po))
			#endif

			#ifdef OLE2ANSI
				inline POLESTR A2OLE(PSTR p) { return p;}
				inline PSTR OLE2A(POLESTR p) { return p;}
				#define W2OLE W2A
				#define OLE2W A2W
				inline PCOLESTR A2COLE(PCSTR p) { return p;}
				inline PCSTR OLE2CA(PCOLESTR p) { return p;}
				#define W2COLE W2CA
				#define OLE2CW A2CW
			#else
				inline POLESTR W2OLE(PWSTR p) { return p; }
				inline PWSTR OLE2W(POLESTR p) { return p; }
				#define A2OLE A2W
				#define OLE2A W2A
				inline PCOLESTR W2COLE(PCWSTR p) { return p; }
				inline PCWSTR OLE2CW(PCOLESTR p) { return p; }
				#define A2COLE A2CW
				#define OLE2CA W2CA
			#endif

			inline BSTR OLE2BSTR(PCOLESTR p) {return ::SysAllocString(p);}
			#if defined(_UNICODE)
			// in these cases the default (TCHAR) is the same as OLECHAR
				inline BSTR T2BSTR(PCTSTR p) {return ::SysAllocString(p);}
				inline BSTR A2BSTR(PCSTR p) {USES_CONVERSION; return ::SysAllocString(A2COLE(p));}
				inline BSTR W2BSTR(PCWSTR p) {return ::SysAllocString(p);}
			#elif defined(OLE2ANSI)
			// in these cases the default (TCHAR) is the same as OLECHAR
				inline BSTR T2BSTR(PCTSTR p) {return ::SysAllocString(p);}
				inline BSTR A2BSTR(PCSTR p) {return ::SysAllocString(p);}
				inline BSTR W2BSTR(PCWSTR p) {USES_CONVERSION; return ::SysAllocString(W2COLE(p));}
			#else
				inline BSTR T2BSTR(PCTSTR p) {USES_CONVERSION; return ::SysAllocString(T2COLE(p));}
				inline BSTR A2BSTR(PCSTR p) {USES_CONVERSION; return ::SysAllocString(A2COLE(p));}
				inline BSTR W2BSTR(PCWSTR p) {return ::SysAllocString(p);}
			#endif

		#endif // #ifdef _MFC_VER

	#endif // #ifndef USES_CONVERSION
#endif // #ifndef _NO_STDCONVERSION

// Define our own macros for "other" type to TCHAR type conversion
// i.e. in a UNICODE build "other" would be char.  In a non-UNICODE
// build, "other" would be wchar_t  These macros make the declaration
// of the CString class a lot cleaner

#ifdef _UNICODE
	#define O2T A2T				// "other" type string to generic text type string
	#define O2CT A2CT			// constant "other" type string to generic text type string
	#define T2O T2A				// generic text type string to "other" type string.
	#define T2CO T2CA			// generic text type string to constant "other type string.
#else
	#define	O2T W2T
	#define O2CT W2CT
	#define T2O T2W
	#define T2CO T2CW
#endif

// Define some short names for types that we will refer to in our definition of
// the CString class.

#ifdef _UNICODE
	#define TOTHER	char		// the "other" char type			(opposite of TCHAR)
	#define	POSTR PSTR			// the "other" string type			(opposite of PTSTR)
	#define	PCOSTR PCSTR		// the "other" const string type	(oppsite of PCTSTR)
	const PCOSTR szONull = "";	// an empty string of the "other" type.
#else
	#define TOTHER wchar_t		
	#define POSTR PWSTR		
	#define PCOSTR PCWSTR		
	const PCOSTR szONull = L"";
#endif

const PCTSTR szTNull = _T("");	// an empty string of the TCHAR" type

typedef std::basic_string<TCHAR> STRBASE;	// our base class
typedef std::basic_string<TOTHER> STROTHER; // opposite of our base

// Define TSTRING -- this is a basic_string built around the TCHAR type, kind of like MFC CString
// It is also our base class.

#ifndef _TSTRING_DEFINED_
#define _TSTRING_DEFINED_
	typedef std::basic_string<TCHAR> TSTRING;
#endif

//			Now we can define the class (finally!)
// =====================================================================================================
// CLASS: CString
// REMARKS:
//		This class is a simplified version of the Standard C++ Library string or basic string class.  It
//		is derived from basic_string<TCHAR> and adds some MFC CString-like functionality
//
//		Basically, this is my attempt to make Standard C++ library strings as easy to use as the MFC
//		CString class.
// =====================================================================================================

#define CString _SS	// Make CString actually use a shorter name to avoid compiler warning 4786
class W32DLLSPEC CString : public STRBASE
{
public:

	typedef std::allocator<TCHAR> MYALLOC;
	// constructors
	CString();
	CString(const CString& str);
	CString(const STRBASE& str);
	CString(const STROTHER& str);
	CString(PCTSTR pT);
	CString(PCOSTR pO);
	CString(const_iterator first, const_iterator last);
	CString(size_type nSize, value_type ch, const allocator_type& al=std::allocator<TCHAR>());
#ifdef STDSTRING_INC_COMDEF
	CString(const _bstr_t& bstr);							// takes the _bstr_t MS compiler COM support class
#endif

	// assignment operators
	CString&			operator=(const CString& str);		// copy constructor
	CString&			operator=(const STRBASE& str);			// takes a base std string type (string or wstring)
	CString&			operator=(const STROTHER& str);			// takes the other std string type (string or wstring)
	CString&			operator=(PCTSTR pT);					// takes const TCHAR pointer
	CString&			operator=(PCOSTR pO);					// takes const pointer to "other" type (opposite of PCTSTR)
	CString&			operator=(TCHAR);						// takes single character of TCHAR type
	CString&			operator=(TOTHER);						// takes single character of the "other" type
#ifdef STDSTRING_INC_COMDEF
	CString&			operator=(const _bstr_t& bstr);			// takes the _bstr_t MS compiler COM support class
#endif

	// These overloads are also needed to fix the MSVC assignment bug (only for MS' STL -- KB: Q172398).
	//  *** Thanks to Pete The Plumber for catching this one ***
	CString&			assign(const CString& str, CString::size_type nStart, CString::size_type nChars);
	CString&			assign(PCTSTR pT, CString::size_type nChars);
	CString&			assign(CString::size_type nChars, CString::value_type val);
	CString&			assign(const CString& str);
	CString&			assign(PCTSTR pT);
	CString&			assign(CString::const_iterator iterFirst, CString::const_iterator iterLast);

	// comparison (equality)  
	bool				operator==(const CString& str) const;
	bool				operator==(const STRBASE& str) const;
	bool				operator==(const STROTHER& str) const;
	bool				operator==(PCTSTR pT) const;
	bool				operator==(PCOSTR pO) const;
	bool				operator==(TCHAR t) const;
	bool				operator==(TOTHER t) const;
	bool				Equals(PCTSTR pT, bool bUseCase=false) const;	// allows (& defaults to) case INsensitive comparison
//	bool				WildcardEquals(PCTSTR pT, bool bUseCase=false) const; // allows (& defaults to) case INsensitive comparison and allows wildcards

	// comparison operators (inequality)  
	bool				operator!=(const CString& str) const;
	bool				operator!=(const STRBASE& str) const;
	bool				operator!=(const STROTHER& str) const;
	bool				operator!=(PCTSTR pT) const;
	bool				operator!=(PCOSTR pO) const;
	bool				operator!=(TCHAR t) const;
	bool				operator!=(TOTHER t) const;

	// comparison operator (less than)
	bool operator<(const CString& str) const;
	bool operator<(PCTSTR str) const;

	// concatenation.
	const CString&	operator+=(const CString& str);
	const CString&	operator+=(const STRBASE& str);
	const CString&	operator+=(const STROTHER& str);
	const CString&	operator+=(PCTSTR pT);
	const CString&	operator+=(PCOSTR pO);
	const CString&	operator+=(TCHAR t);
	const CString&	operator+=(TOTHER t);
#ifdef STDSTRING_INC_COMDEF
	const CString&	operator+=(const _bstr_t& bstr);
#endif

	// addition operators -- global friend functions.
	friend CString	operator+(const CString& str1, const CString& str2);
	friend CString	operator+(const CString& str, TCHAR ch);
	friend CString	operator+(TCHAR ch, const CString& str);
	friend CString	operator+(const CString& str, TOTHER ch);
	friend CString	operator+(TOTHER ch, const CString& str);
	friend CString	operator+(const CString& str, PCTSTR sz);
	friend CString	operator+(PCTSTR sz, const CString& str);
	friend CString	operator+(const CString& str, PCOSTR sz);
	friend CString	operator+(PCOSTR sz, const CString& str);
#ifdef STDSTRING_INC_COMDEF
	friend CString	operator+(const _bstr_t& bstr, const CString& str);
	friend CString	operator+(const CString& str, const _bstr_t& bstr);
#endif

	// Conversion to "other" type of string (i.e. to string if we're a wstring, to wstring if we're a string)
	STROTHER Other() const { USES_CONVERSION; return T2CO(c_str()); };

	// Functions that make us almost as easy to use as MFC's CString
							operator PCTSTR() const;				// implicit cast to const TCHAR*
			bool			Load(UINT nId);							// load using resource id
			void			Format(PCTSTR szFormat, ...);			// format using literal string
			void			Format(UINT nId, ...);					// format using resource string identifier
	void					FormatV(PCTSTR szFormat, va_list argList);	// format using a va_list instead of ...
			CString&		TrimRight();							// chop off all whitespace characters on right
			CString&		TrimLeft();								// chop off all whitespace characters on left
			CString&		ToUpper();								// make uppercase
			CString&		ToLower();								// make lowercase
			bool			IsEmpty() const { return empty(); };
			int				GetLength(){ return size(); }
			void			Empty(){ empty(); }
			int				Find( const char *sz ){ return find(sz); }
			CString			Left( int nPos ){ CString strRet = substr(0,nPos); return strRet; }
			CString			Mid( int nPos ){ CString strRet = substr(nPos); return strRet; }
			CString			Mid( int nPos, int nCount ){ CString strRet = substr(nPos,nCount); return strRet; }
	// Array-indexing operators.  I thought we did not need to redefine these, but they don't work unless we
	// redefine them here.  (Thanks to Julian Selman for pointing this out)

			TCHAR&			operator[](int nIdx);
			const TCHAR&	operator[](int nIdx) const;	


#ifdef STDSTRING_INC_COMDEF
	HRESULT					StreamSave(IStream* pStream) const;		// write to an IStream
	HRESULT					StreamLoad(IStream* pStream);			// read from an IStream;
	ULONG					StreamSize() const;						// how many bytes needed to write to an IStream?
#endif
//	static	bool			Wildstrcmp (PCTSTR c_s, PCTSTR c_mask);


	// These static functions simplify copying one C-style string to another, either one or two byte.

	static	void			CopyString(PCTSTR p_szSource, PTSTR p_szDest, int p_nMaxChars=0);
	static	void			CopyString(PCOSTR p_szSource, POSTR p_szDest, int p_nMaxChars=0);
	static	void			CopyString(PCSTR p_szSource, PWSTR p_szDest, int p_nMaxChars=0);
	static	void			CopyString(PCWSTR p_szSource, PSTR, int p_nMaxChars=0);

	// If this is NOT an MFC build, provide a SetResourceHandle function so that those who call
	// the versions of Load(), Format(), or the constructor that take resource IDs can provide
	// an alternate HINST of a DLL to search.  This is not exactly the list of link libraries
	// that MFC provides but it's better than nothing.   It's also not thread safe but I 

	static	void			SetResourceHandle(HINSTANCE hNew);
	static	HINSTANCE		GetResourceHandle();

protected:

#if !defined(_MFC_VER)
	static		HINSTANCE	hInstResource;						// implementation of Get/SetResourceHandle in non-MFC builds
#endif
};

#define _TRES(pctstr) (LOWORD((DWORD)(pctstr)))					// shorthand conversion from PCTSTR to string resource ID

// CString inline constructors

inline CString::CString() {}
inline CString::CString(const STRBASE& str) { *this = str; };
//inline CString::CString(PCTSTR pT) { *this = (pT == NULL ? szTNull : pT); };
inline CString::CString(PCOSTR pO) { *this = (pO == NULL ? szONull : pO); };
inline CString::CString(const CString& str) { *this = str; };
inline CString::CString(const STROTHER& str) { *this = str; };
inline CString::CString(const_iterator first, const_iterator last) : STRBASE(first, last) {};
inline CString::CString(size_type nSize, value_type ch, const allocator_type& al) : STRBASE(nSize, ch, al) { }
#ifdef STDSTRING_INC_COMDEF
	inline CString::CString(const _bstr_t& bstr) { *this = static_cast<PCTSTR>(bstr); }
#endif

// CString inline assignment operators -- the erase() function
// call fixes the MSVC assignment bug (see knowledge base article Q172398).

inline CString& CString::operator=(const CString& str)
{ if ( str.data() != data() ) { erase(); STRBASE::assign(str.data());} return *this; };
inline CString& CString::operator=(const STRBASE& str)
{ if ( str.data() != data() ) { erase(); STRBASE::assign(str.data());} return *this; };
inline CString& CString::operator=(const STROTHER& str)
{  erase(); USES_CONVERSION; STRBASE::assign(O2CT(str.data())); return *this; };
inline CString& CString::operator=(PCTSTR pT)
{ if ( pT != data() ) { erase(); if ( pT != NULL ) STRBASE::assign(pT); } return *this; };
inline CString& CString::operator=(PCOSTR pO)
{ erase(); if ( pO != NULL ) { USES_CONVERSION; STRBASE::assign(O2CT(pO)); } return *this; };
inline CString& CString::operator=(TOTHER t)
{ erase(); USES_CONVERSION; STRBASE::assign(O2CT(&t)); return *this; };
inline CString& CString::operator=(TCHAR t) 
{ erase(); STRBASE::assign(1,t); return *this; };
#ifdef STDSTRING_INC_COMDEF
	inline CString& CString::operator=(const _bstr_t& bstr)
	{ return operator=(static_cast<PCTSTR>(bstr)); }
#endif

// These overloads are also needed to fix the MSVC assignment bug (KB: Q172398)
//  *** Thanks to Pete The Plumber for catching this one ***

inline CString& CString::assign(const CString& str, CString::size_type nStart, CString::size_type nChars)
{ if( str.data() != data() ) erase(); STRBASE::assign(str, nStart, nChars); return *this; }
inline CString& CString::assign(PCTSTR pT, CString::size_type nChars)
{ if( pT != data() ) erase(); STRBASE::assign(pT, nChars); return *this; }
inline CString& CString::assign(CString::size_type nChars, CString::value_type val)
{ erase(); STRBASE::assign(nChars, val); return *this; }
inline CString& CString::assign(const CString& str)
{ return assign(str, 0, npos); }
inline CString& CString::assign(PCTSTR pT)
{ return assign(pT, CString::traits_type::length(pT)); }
inline CString& CString::assign(CString::const_iterator iterFirst, CString::const_iterator iterLast)
{ replace(begin(), end(), iterFirst, iterLast); return *this; }


// CString inline comparison (equality) 
 
inline bool CString::operator==(const CString& str) const
{ return compare(str.c_str()) == 0; };
inline bool CString::operator==(const STRBASE& str) const
{ return compare(str.data()) == 0; };
inline bool CString::operator==(const STROTHER& str) const
{ USES_CONVERSION; return compare(O2CT(str.data())) == 0; };
inline bool CString::operator==(PCTSTR pT) const
{ return compare(pT) == 0; };
inline bool CString::operator==(PCOSTR pO) const
{ USES_CONVERSION; return compare(O2CT(pO)) == 0; };
inline bool CString::operator==(TCHAR t) const
{ return operator==(STRBASE(1,t)); };
inline bool CString::operator==(TOTHER t) const
{ USES_CONVERSION; return operator==(CString(O2CT(&t))); };
inline bool CString::Equals(PCTSTR pT, bool bUseCase/*=false*/) const       // defaults to case insensitive
{ return  bUseCase ? compare(pT) == 0 : _tcsicmp(CString(*this), pT) == 0; } // get copy, THEN compare (thread safe)
//inline bool CString::WildcardEquals(PCTSTR pT, bool bUseCase/*=false*/) const       // defaults to case insensitive
//{ CString me(*this), mask(pT); if( !bUseCase ) { me.ToUpper(); mask.ToUpper(); } return Wildstrcmp(me, mask); } // get copy, THEN compare (thread safe)


// CString inline comparison operators (inequality) 
 
inline bool CString::operator!=(const CString& str) const
{ return compare(str.c_str()) != 0; };
inline bool CString::operator!=(const STRBASE& str) const
{ return compare(str.data()) != 0; };
inline bool CString::operator!=(const STROTHER& str) const
{ USES_CONVERSION; return compare(O2CT(str.data())) != 0; };
inline bool CString::operator!=(PCTSTR pT) const
{ return compare(pT) != 0; };
inline bool CString::operator!=(PCOSTR pO) const
{ USES_CONVERSION; return compare(O2CT(pO)) != 0; };
inline bool CString::operator!=(TCHAR t) const
{ return operator!=(STRBASE(1,t)); };
inline bool CString::operator!=(TOTHER t) const
{ USES_CONVERSION; return operator!=(CString(O2CT(&t))); };


// CString comparison operator (less than)

inline bool CString::operator<(const CString& str) const
{ return compare(str) < 0; };
inline bool CString::operator<(PCTSTR str) const
{ return compare(str) < 0; };

// CString inline concatenation.

inline const CString& CString::operator+=(const CString& str)
{ append(str); return *this; };
inline const CString& CString::operator+=(const STRBASE& str)
{ append(str); return *this; };
inline const CString& CString::operator+=(const STROTHER& str)
{ USES_CONVERSION; *this += O2CT(str.c_str()); return *this; };
inline const CString& CString::operator+=(PCTSTR pT)
{ if ( pT != NULL ) append(pT); return *this; };
inline const CString& CString::operator+=(PCOSTR pO)
{ USES_CONVERSION; if ( pO != NULL ) append(O2CT(pO)); return *this; };
inline const CString& CString::operator+=(TCHAR t)
{ append(1, t); return *this; };
inline const CString& CString::operator+=(TOTHER t)
{ USES_CONVERSION; append(O2CT(&t)); return *this; };
#ifdef STDSTRING_INC_COMDEF
	inline const CString& CString::operator+=(const _bstr_t& bstr)
	{ return operator+=(static_cast<PCTSTR>(bstr)); }
#endif

// CString friend addition functions defined as inline

inline CString operator+(const CString& str1, const CString& str2)
{ CString strRet(str1); return strRet.append(str2); }
inline CString operator+(const CString& str, TCHAR ch)
{ CString strRet(str); return strRet.append(1, ch); }
inline CString operator+(TCHAR ch, const CString& str)
{ CString strRet(1, ch); return strRet.append(str); }
inline CString operator+(const CString& str, TOTHER ch)
{ return str + STROTHER(1, ch).data(); }
inline CString operator+(TOTHER ch, const CString& str)
{ CString strRet; strRet = ch; return strRet.append(str); }
inline CString operator+(const CString& str, PCTSTR sz)
{ CString strRet(str); return sz == NULL ? strRet : strRet.append(sz); }
inline CString operator+(PCTSTR sz, const CString& str)
{ CString strRet(sz); return strRet.append(str); }
inline CString operator+(const CString& str, PCOSTR sz)
{ CString strRet(str); return strRet.append(CString(sz)); }
inline CString operator+(PCOSTR sz, const CString& str)
{ CString strRet(sz); return strRet.append(str); }
#ifdef STDSTRING_INC_COMDEF
	inline CString operator+(const _bstr_t& bstr, const CString& str)
	{ return CString(static_cast<PCTSTR>(bstr)) + str; }
	inline CString operator+(const CString& str, const _bstr_t& bstr)
	{ return str + static_cast<PCTSTR>(bstr); }
#endif



inline TCHAR&		CString::operator[](int nIdx) { return STRBASE::operator[](nIdx); }
inline const TCHAR& CString::operator[](int nIdx) const { return STRBASE::operator[](nIdx); }
inline				CString::operator PCTSTR() const { return c_str(); };	// implicit cast to const TCHAR*


// In MFC builds, define some global serialization operators

#ifdef _MFC_VER
	W32DLLSPEC CArchive& AFXAPI operator>>(CArchive& ar, CString& string);
	W32DLLSPEC CArchive& AFXAPI operator<<(CArchive& ar, const CString& string);
	inline void CString::SetResourceHandle(HINSTANCE hNew) { AfxSetResourceHandle(hNew); }
	inline HINSTANCE CString::GetResourceHandle() { return AfxGetResourceHandle(); };
#else
	inline void CString::SetResourceHandle(HINSTANCE hNew) { CString::hInstResource = hNew; }
	inline HINSTANCE CString::GetResourceHandle() { return CString::hInstResource; };
#endif

// Some code still refers to old names of this class -- Account for this.
#define CSTLString	CString
#define CW32String	CString

// WUSysMessage -- return the system string corresponding to a system error or HRESULT value.
W32DLLSPEC CString WUSysMessage(DWORD dwError, DWORD p_dwLangId=MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT));

// WUFormat -- creates and formats a CString with one line of code instead of the two it normally takes
W32DLLSPEC CString WUFormat(PCTSTR szFormat, ...);
W32DLLSPEC CString WUFormat(UINT nId, ...);

// ------------------------------------------------------------------------------------------------------
// FUNCTIONAL COMPARATORS:
// REMARKS:
//		These structs are derived from the std::binary_function template.  They give us functional
//		classes (which may be used in Standard C++ Library collections and algorithms) that perform
//		case-insensitive comparisons of CString objects.  This is useful for maps in which the key
//		may be the proper string but in the wrong case.
// ------------------------------------------------------------------------------------------------------
#define StdStringLessNoCase		_SSLNC		// define shorter name to avoid compiler warning 4786
#define StdStringEqualsNoCase	_SSENC		// define shorter name to avoid compiler warning 4786
struct W32DLLSPEC StdStringLessNoCase : std::binary_function<CString, CString, bool>
{
	bool operator()(const CString& strFirst, const CString& strSecond) const
	{ return _tcsicmp(strFirst, strSecond) < 0; }
};
struct W32DLLSPEC StdStringEqualsNoCase : std::binary_function<CString, CString, bool>
{
	bool operator()(const CString& strFirst, const CString& strSecond) const
	{ return _tcsicmp(strFirst, strSecond) == 0; }
};



#endif	// #ifndef _STDSTRING_H_