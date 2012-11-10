#ifndef __D_REGEXPR_H__	/* { */
#define __D_REGEXPR_H__

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

#if !defined( USE_3PARTY_ROGUE) && !defined( USE_3PARTY_YACL)	/* { */

#include <string.h>
#include <malloc.h>

#include <regexp.h>

class D_StringImpl_c
{

public:

	D_StringImpl_c()
		: _str( 0),
		  _size( 0)
	{}

	~D_StringImpl_c()
	{
		if( _str)
			delete[] _str;
		_str = 0;
		_size = 0;
	}

	D_StringImpl_c( const char* str)
	{
		if( str)
		{
			_size = strlen( str);
			_str = new char[ _size + 1];
			strcpy( _str, str);
		}
		else
		{
			_str = 0;
			_size = 0;
		}
	}

	D_StringImpl_c( const D_StringImpl_c& src)
		: _size( src._size)
	{
		if( src._str)
		{
			_str = new char[ _size + 1];
			strcpy( _str, src._str);
		}
		else
			_str = 0;
	}

	D_StringImpl_c& operator =( const D_StringImpl_c& src)
	{
		if( _str)
			delete[] _str;
		_size = src._size;
		if( src._str)
		{
			_str = new char[ _size + 1];
			strcpy( _str, src._str);
		}
		else
			_str = 0;
		return( *this);
	}

	D_StringImpl_c& operator =( const char* str)
	{
		if( _str)
			delete[] _str;
		if( str)
		{
			_size = strlen( str);
			_str = new char[ _size + 1];
			strcpy( _str, str);
		}
		else
		{
			_size = 0;
			_str = 0;
		}
		return( *this);
	}

	D_StringImpl_c& operator +=( const char* str)
	{
		if( str == 0)	// no change
			return( *this);
		if( _str)
		{
			_size += strlen( str);
			char* tmp = new char[ _size + 1];
			strcpy( tmp, _str);
			strcat( tmp, str);
			delete[] _str;
			_str = tmp;
		}
		else
		{
			_size = strlen( str);
			_str = new char[ _size + 1];
			strcpy( _str, str);
		}
		return( *this);
	}

	const char* data() const
	{ return( _str); }

	size_t length() const
	{ return( _size); }

	operator const char* () const
	{ return( _str); }

	size_t index( const char* pat) const
	{
		if( _str == 0 || pat == 0)
			return( NO_SUCH_ELEMENT);
		char* s = strstr( _str, pat);
		if( s == 0)
			return( NO_SUCH_ELEMENT);
		return( s - _str);
	}

	const char* substr( size_t where, size_t len) const
	{
		if( _str == 0)
			return( 0);
		if( where + len > _size)
			return( 0);
		static char* buf = 0;
		static size_t sz = 0;
		if( sz < len)
		{
			if( buf)
				delete[] buf;
			sz = len;
			// Yes, this is a memory leak...
			// But so it works for statics!
			buf = new char[ sz + 1];
		}
		strncpy( buf, _str + where, len);
		buf[len] = '\0';
		return( buf);
	}

	void replace( size_t where, size_t len,	const char* new_str)
	{
		if( _str == 0)
			return;
		if( where + len > _size)
			return;
		if( new_str == 0)
			return;
		_size = _size - len + strlen( new_str);
		char* tmp = new char[ _size + 1];
		if( where)
			strncpy( tmp, _str, where);
		tmp[where] = '\0';
		strcat( tmp, new_str);
		strcat( tmp, _str + where + len);
		delete[] _str;
		_str = tmp;
	}

friend int operator ==( const D_StringImpl_c& s1,
					const D_StringImpl_c& s2)
	{
		if( s1._str == s2._str)
			return( 1);
		if( s1._size != s2._size)
			return( 0);
		if( strcmp( s1._str, s2._str) == 0)
			return( 1);
		return( 0);
	}

private:

	char*	_str;
	size_t	_size;
};

class D_RegExpImpl_c
{

public:

	D_RegExpImpl_c( const char* regExp)
		: _pattern( regExp),
		  _ok( 1)
	{
		_current = this;
		_re = regcomp( (char*)_pattern.data());
	}

	D_RegExpImpl_c( const D_RegExpImpl_c& r)
		: _pattern( r._pattern.data()),
		  _ok( 1)
	{
		_current = this;
		_re = regcomp( (char*)_pattern.data());
	}

	~D_RegExpImpl_c()
	{
		if( _re)
			free( _re);
	}

	D_RegExpImpl_c& operator = (const char* regExp)
	{
		_pattern = regExp;
		_ok = 1;
		if( _re)
			free( _re);
		_current = this;
		_re = regcomp( (char*)_pattern.data());
		return( *this);
	}

	D_RegExpImpl_c& operator =( const D_RegExpImpl_c& r)
	{
		_pattern = r._pattern;
		_ok = 1;
		if( _re)
			free( _re);
		_current = this;
		_re = regcomp( (char*)_pattern.data());
		return( *this);
	}

	long match( const char* string, size_t& length) const
	{
		if( !_ok)
			return( NO_SUCH_ELEMENT);
		_current = this;
		if( regexec( (regexp*)_re, (char*)string) <= 0)
			return( NO_SUCH_ELEMENT);
		length = _re->endp[0] - _re->startp[0];
		return( _re->startp[0] - string);
	}

	int isOK() const
	{ return( _ok); }

friend void D_RegError( char*)
	{
		if( D_RegExpImpl_c::_current)
			((D_RegExpImpl_c*)D_RegExpImpl_c::_current)->_ok = 0;
	}

private:

	D_StringImpl_c	_pattern;
	regexp* 	_re;
	int		_ok;

	static const D_RegExpImpl_c*	_current;

};

#endif	/* } !USE_3PARTY_ROGUE && !USE_3PARTY_YACL */

#endif /* } __D_REGEXPR_H__ */
