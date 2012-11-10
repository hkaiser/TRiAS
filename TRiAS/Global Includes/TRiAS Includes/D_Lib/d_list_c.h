#ifndef __D_LIST_C_H__	/* { */
#define __D_LIST_C_H__

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

typedef void (*delete_func)( void* val, void* data);

class D_VoidListNode_c
{
public:
	D_VoidListNode_c( void* v, D_VoidListNode_c* nxt)
		: val( v),
		  next( nxt)
	{}

	void*			val;
	D_VoidListNode_c*	next;
};

class D_VoidList_c
{
public:
	D_VoidList_c( delete_func del_func = 0, void* del_data = 0)
		: _list( 0),
		  _entries( 0),
		  _del_func( del_func),
		  _del_data( del_data),
		  _prev_node( 0),
		  _prev_index( NO_SUCH_ELEMENT)
		{}
	//D_VoidList_c( const D_VoidList_c& src);
	~D_VoidList_c()
		{ clear(); }

	void insert( void* val);
		// inserts in the beginning of the list
	void remove();
		// removes from the beginning of the list, i.e.
		// the last inserted node
	void clear();
		// removes everything

	size_t index( int (*testFunc)( void* elem, void* data),
			void* data) const;
		// returns number (from 0) or NO_SUCH_ELEMENT
	void* at( size_t index);
		// index is from 0 (not from 1)
	size_t entries() const
		{ return( _entries); }

private:
	D_VoidList_c& operator =( const D_VoidList_c&) { return *this; }

	D_VoidListNode_c		*_list;
	size_t				_entries;

	delete_func			_del_func;
	void*				_del_data;

	size_t				_prev_index;
	D_VoidListNode_c		*_prev_node;

};

#endif	/* } __D_LIST_C_H__ */
