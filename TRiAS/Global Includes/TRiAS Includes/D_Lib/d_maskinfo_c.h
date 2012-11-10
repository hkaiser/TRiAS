#ifndef __D_MASKINFO_C_H__	/* { */
#define __D_MASKINFO_C_H__

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

#include <d_string_c.h>

struct D_level_info_for_find
{
	D_Support_c::Scope	scope;
	int			no;

	D_level_info_for_find( D_Support_c::Scope s, int n)
		: scope( s), no( n)
	{}
};

class D_MaskInfo_c
{
public:
	D_MaskInfo_c( const char* msk, D_Support_c::Scope scope,
			int weight, int lvl_no, long info)
		: _mask( msk),
		  _mask_str( msk),
		  _levels( _delete_level_info)
		{ SetLevelInfo( scope, weight, lvl_no, info); }
	D_MaskInfo_c( const char* msk, D_Support_c::Scope scope,
			int weight, int lvl_no, char* info)
		: _mask( msk),
		  _mask_str( msk),
		  _levels( _delete_level_info)
		{ SetLevelInfo( scope, weight, lvl_no, info); }
#if 0	/* TODO - needed? */
	D_MaskInfo_c( const D_MaskInfo_c& mi)
		: _mask( mi._mask),
		  _mask_str( mi._mask_str),
		  _levels( mi._levels)
		{}
#endif
	~D_MaskInfo_c() {}

	D_RegExp_c::statVal GetRegExpStatus()
		{ return( _mask.status()); }

	int Compare( const char* str) const		// using regexp
	{
		const D_String_c s( str);
		if( s( _mask) == s)
			return( 1);
		return( 0);
	}

	int CompareMask( const char* str) const		// exactly
	{
		if( strcmp( str, _mask_str) == 0)
			return( 1);
		return( 0);
	}

	inline void SetLevelInfo( D_Support_c::Scope scope,
			int weight, int lvl_no, long info);
	inline void SetLevelInfo( D_Support_c::Scope scope,
			int weight, int lvl_no, char* info);

	D_String_c& GetMaskStr()
		{ return( _mask_str); }
	D_VoidList_c& GetLevelInfos()
		{ return( _levels); }

	static int FindLevelInfo(
			const D_LevelInfo_c& linfo, void* data)
	{
		const D_level_info_for_find* li =
			(const D_level_info_for_find*)data;
		if( linfo._no != li->no)
			return( 0);
		if( li->scope == D_Support_c::D_ANY_SCOPE)
			return( 1);
		if( linfo._scope == li->scope)
			return( 1);
		return( 0);
	}

private:
	D_String_c	_mask_str;
	D_RegExp_c	_mask;
	D_VoidList_c	_levels;

	D_MaskInfo_c& operator =( D_MaskInfo_c&)
		{ return( *this); }

	static void _delete_level_info( void* li, void* )
	{
		D_LevelInfo_c* linfo = (D_LevelInfo_c*)li;
		delete linfo;
	}

friend ostream& operator <<( ostream& s, D_MaskInfo_c& o)
	{
		s << "D_MaskInfo_c: _mask_str = [" << o._mask_str <<
			"]\n" << flush;
		size_t m_entries = o._levels.entries();
		for( size_t i = 0; i < m_entries; i ++)
		{
			D_LevelInfo_c* li =
				(D_LevelInfo_c*)o._levels.at( i);
			s << "\t" << *li;
		}
		return( s);
	}

};

inline void D_MaskInfo_c::SetLevelInfo( D_Support_c::Scope scope,
		int weight, int lvl_no, char* info)
{
	D_level_info_for_find tmp( scope, lvl_no);
	size_t index = _levels.index(
			( int (*)(void*,void*))FindLevelInfo,
			(void*)&tmp);
	if( index == NO_SUCH_ELEMENT)
	{
		_levels.insert( new D_LevelStringInfo_c(
				scope, weight, lvl_no, info));
		return;
	}
	D_LevelStringInfo_c* li =
		(D_LevelStringInfo_c*)_levels.at( index);
	li->SetInfo( info);
	li->_weight = weight;
}

inline void D_MaskInfo_c::SetLevelInfo( D_Support_c::Scope scope,
		int weight, int lvl_no, long info)
{
	D_level_info_for_find tmp( scope, lvl_no);
	size_t index = _levels.index(
			( int (*)(void*,void*))FindLevelInfo,
			(void*)&tmp);
	if( index == NO_SUCH_ELEMENT)
	{
		_levels.insert( new D_LevelNumberInfo_c(
				scope, weight, lvl_no, info));
		return;
	}
	D_LevelNumberInfo_c* li =
		(D_LevelNumberInfo_c*)_levels.at( index);
	li->_info = (void*)info;
	li->_weight = weight;
}

#endif	/* } __D_MASKINFO_C_H__ */
