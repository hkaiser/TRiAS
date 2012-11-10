#ifndef __D_LEVELINFO_C_H__	/* { */
#define __D_LEVELINFO_C_H__

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

#include <d_support_c.h>

//--------------------------------------------------------
class D_LevelInfo_c
{
public:
	D_LevelInfo_c( D_Support_c::Scope scope, int weight, int no)
		: _scope( scope),
		  _weight( weight),
		  _no( no)
		{}
	D_LevelInfo_c( const D_LevelInfo_c& src)
		: _scope( src._scope),
		  _weight( src._weight),
		  _no( src._no)
		{}
	virtual D_LevelInfo_c& operator =( const D_LevelInfo_c& src)
		{
			_scope = src._scope;
			_weight = src._weight;
			_no = src._no;
			return( *this);
		}
	virtual ~D_LevelInfo_c() {}

// This attributes are public just for internal use
	D_Support_c::Scope	_scope;
	int			_weight;
	int			_no;
	// This field is treated as long or char* depending on
	// derived class, but (to eliminate use of templates) some
	// functions requires it "as is" - void*.
	void*			_info;

private:
	D_LevelInfo_c() {}

	virtual void _print( ostream& s) = 0;

friend ostream& operator <<( ostream& s, D_LevelInfo_c& o)
	{
		o._print( s);
		return( s);
	}

};

//--------------------------------------------------------
class D_LevelNumberInfo_c
	: public D_LevelInfo_c
{
public:
	D_LevelNumberInfo_c( D_Support_c::Scope scope,
			int weight, int no,
			long info)
		: D_LevelInfo_c( scope, weight, no)
		{ _info = (void*)info; }
	D_LevelNumberInfo_c( const D_LevelNumberInfo_c& src)
		: D_LevelInfo_c( src)
		{ _info = src._info; }
	virtual D_LevelNumberInfo_c& operator =(
			const D_LevelNumberInfo_c& src)
		{
			D_LevelInfo_c::operator =( src);
			_info = src._info;
			return( *this);
		}
	virtual ~D_LevelNumberInfo_c() {}

	long GetInfo()
		{ return (long)_info; }
	void SetInfo( long info)
		{ _info = (void*)info; }

private:

	virtual void _print( ostream& s)
	{
		s << "D_LevelNumberInfo_c: _no = [" << _no <<
			"] _info = [" << (long)_info << "]\n" << flush;
	}

};

//--------------------------------------------------------
class D_LevelStringInfo_c
	: public D_LevelInfo_c
{
public:
	D_LevelStringInfo_c( D_Support_c::Scope scope,
			int weight, int no,
			char* info)
		: D_LevelInfo_c( scope, weight, no)
		{ _info = (void*)estrdup( info); }
	D_LevelStringInfo_c( const D_LevelStringInfo_c& src)
		: D_LevelInfo_c( src)
		{ _info = (void*)estrdup( (char*)src._info); }
	virtual D_LevelStringInfo_c& operator =(
			const D_LevelStringInfo_c& src)
		{
			D_LevelInfo_c::operator =( src);
			SetInfo( (char*)src._info);
			return( *this);
		}
	virtual ~D_LevelStringInfo_c()
		{ delete[] (char*)_info; }

	char* GetInfo()
		{ return (char*)_info; }
	void SetInfo( char* info)
		{
		  delete[] (char*)_info;
		  _info = (void*)estrdup( info);
		}

private:

	static char* estrdup( const char* src)
	{
		char* dst = new char[ strlen( src) + 1];
		if( dst != 0)
			strcpy( dst, src);
		return( dst);
	}

	virtual void _print( ostream& s)
	{
		s << "D_LevelNumberInfo_c: _no = [" << _no <<
			"] _info = [" << (char*)_info << "]\n" << flush;
	}

};

#endif	/* } __D_LEVELINFO_C_H__ */
