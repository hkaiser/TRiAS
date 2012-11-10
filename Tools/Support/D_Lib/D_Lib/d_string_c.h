#ifndef __D_STRING_C_H__	/* { */
#define __D_STRING_C_H__

//
// *D_Lib* Copyright 1996-1999  Anatoly Kardash, anatoly-k@geocities.com
//
// Permission to use, copy, modify, and distribute, this software
// and its documentation for any purpose is hereby granted without
// fee, provided that the above copyright notice appear in all copies
// and that both that copyright notice and this permission notice
// appear in supporting documentation, and that the name of the
// copyright holders be used in advertising or publicity pertaining
// to distribution of the software with specific, written prior
// permission, and that no fee is charged for further distribution
// of this software, or any modifications thereof. The copyright
// holder make no representations about the suitability of this
// software for any purpose. It is provided "as is" without express
// or implied warranty.
//
// THE COPYRIGHT HOLDER DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
// SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
// FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR
// ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA, PROFITS, QPA OR GPA,
// WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS
// ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
// OF THIS SOFTWARE.
//

#include <d_consts.h>

#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)
//#error A 3rd-party library used must be specified (either USE_3PARTY_ROGUE or USE_3PARTY_YACL)

#include <d_regexpr.h>

#endif

#ifdef USE_3PARTY_ROGUE	/* { */

#ifdef DEBUG	/* { */
#ifndef RWDEBUG	/* { */
#define RWDEBUG
#endif		/* } RWDEBUG */
#endif		/* } DEBUG */

#include <rw/cstring.h>
#include <rw/regexp.h>

#endif			/* } USE_3PARTY_ROGUE */

#ifdef USE_3PARTY_YACL	/* { */

#if 0
#ifdef _MSC_VER /* {  MS VC++ does not support standard bool well */
#if _MSC_VER == 1010 || _MSC_VER == 1020	/* { */
// VC++ v.4.1 and v.4.2 warns that bool is reserved but anyway
// does not support it :-)
// 1010 means v.4.1; 1020 means v.4.2 :-)
#pragma warning( disable : 4237)
#endif  /* } _MSC_VER == 1010 || _MSC_VER == 1020 */
#endif  /* } _MSC_VER */
#endif

#include "base/regexpr.h"

#endif			/* } USE_3PARTY_YACL */

class D_RegExp_c
{
public:

	enum statVal { OK, NOT_OK};

	D_RegExp_c( const char* str)
		: _regexp( str)
	{}

	D_RegExp_c( const D_RegExp_c& src)
		: _regexp( src._regexp)
	{}

	statVal status()	// not const - it clears the status
	{
#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */

		if( _regexp.isOK())
			return( OK);
		else
			return( NOT_OK);

#else	/* }{ !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

#ifdef USE_3PARTY_ROGUE	/* { */
		if( _regexp.status() == RWCRegexp::OK)
			return( OK);
		else
			return( NOT_OK);
#endif			/* } USE_3PARTY_ROGUE */
#ifdef USE_3PARTY_YACL	/* { */
		CL_String err = _regexp.LastError();
		if( err.Size() > 0)
			return( NOT_OK);
		else
			return( OK);
#endif			/* } USE_3PARTY_YACL */

#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */
	}

private:

	D_RegExp_c& operator =( const D_RegExp_c&) { return( *this); }

#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */

	D_RegExpImpl_c	_regexp;

#else	/* }{ !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

#ifdef USE_3PARTY_ROGUE	/* { */
	RWCRegexp	_regexp;
#endif			/* } USE_3PARTY_ROGUE */
#ifdef USE_3PARTY_YACL	/* { */
	CL_RegExpr	_regexp;
#endif			/* } USE_3PARTY_YACL */

#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

friend class D_String_c;
};

class D_String_c
{
public:

	D_String_c()
	{}

	D_String_c( const char* str)
		: _str( str)
	{}

#ifdef USE_3PARTY_ROGUE	/* { */
	D_String_c( const RWCSubString& sstr)
		: _str( sstr)
	{}
#endif			/* } USE_3PARTY_ROGUE */

	D_String_c( const D_String_c& src)
		: _str( src._str)
	{}

	D_String_c& operator =( const D_String_c& src)
	{ _str = src._str; return( *this); }

	D_String_c& operator =( const char* src)
	{ _str = src; return( *this); }

	D_String_c& operator +=( const char* str)
	{ _str += str; return( *this); }

	const char* data() const
	{
#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */
		return( _str.data());
#else	/* }{ !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

#ifdef USE_3PARTY_ROGUE	/* { */
		return( _str.data());
#endif			/* } USE_3PARTY_ROGUE */
#ifdef USE_3PARTY_YACL	/* { */
		return( _str.AsPtr());
#endif			/* } USE_3PARTY_YACL */

#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */
	}

	size_t length() const
	{
#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */
		return( (size_t)_str.length());
#else	/* }{ !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

#ifdef USE_3PARTY_ROGUE	/* { */
		return( (size_t)_str.length());
#endif			/* } USE_3PARTY_ROGUE */
#ifdef USE_3PARTY_YACL	/* { */
		return( (size_t)_str.Size());
#endif			/* } USE_3PARTY_YACL */

#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */
	}

	operator const char* () const
	{ return( _str.operator const char* ()); }

	size_t index( const char* pat)
	{
#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */

		size_t sz = _str.index( pat);
		return( sz);

#else	/* }{ !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

#ifdef USE_3PARTY_ROGUE	/* { */
		size_t sz = _str.index( pat);
		if( sz == RW_NPOS)
			sz = NO_SUCH_ELEMENT;
		return( sz);
#endif			/* } USE_3PARTY_ROGUE */
#ifdef USE_3PARTY_YACL	/* { */
		long sz = _str.Index( pat);
		if( sz == -1)
			return( NO_SUCH_ELEMENT);
		return( (size_t)sz);
#endif			/* } USE_3PARTY_YACL */

#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */
	}

	void replace( size_t where, size_t len,	const char* new_str)
	{
#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */
		_str.replace( where, len, new_str);
#else	/* }{ !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

#ifdef USE_3PARTY_ROGUE	/* { */
		_str.replace( where, len, new_str, strlen( new_str));
#endif			/* } USE_3PARTY_ROGUE */
#ifdef USE_3PARTY_YACL	/* { */
		_str.Replace( where, len, new_str);
#endif			/* } USE_3PARTY_YACL */

#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */
	}

	D_String_c operator ()( const D_RegExp_c& re) const
	{
#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */

		size_t len;
		size_t i = (size_t)re._regexp.match( _str, len);
		if( i == NO_SUCH_ELEMENT)
		{
			D_String_c empty;
			return( empty);
		}
		return( _str.substr( i, len));

#else	/* }{ !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

#ifdef USE_3PARTY_ROGUE	/* { */
		return( _str( re._regexp));
#endif			/* } USE_3PARTY_ROGUE */
#ifdef USE_3PARTY_YACL	/* { */
		long len;
		CL_RegExpr& regexp = (CL_RegExpr&)re._regexp;
		long i = regexp.Match( _str, len);
		if( i == -1)
		{
			D_String_c empty;
			return( empty);
		}
		return( D_String_c( _str( i, len)));
#endif			/* } USE_3PARTY_YACL */

#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */
	}

friend int operator ==( const D_String_c& s1, const D_String_c& s2)
	{ return( s1._str == s2._str); }

private:

#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */
	D_StringImpl_c	_str;
#else	/* }{ !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

#ifdef USE_3PARTY_ROGUE	/* { */
	RWCString	_str;
#endif			/* } USE_3PARTY_ROGUE */
#ifdef USE_3PARTY_YACL	/* { */
	CL_String	_str;
#endif			/* } USE_3PARTY_YACL */

#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */
};

#endif	/* } __D_STRING_C_H__ */
