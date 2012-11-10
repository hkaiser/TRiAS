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

#include <d_list_c.h>

#if 0	/* TODO - needed? */
D_VoidList_c::D_VoidList_c( const D_VoidList_c& src)
	: _list( 0),
	  _del_func( 0),
	  _del_data( 0),
	  _prev_node( 0),
	  _prev_index( NO_SUCH_ELEMENT)
{
	D_VoidListNode_c* cur = 0;
	for( D_VoidListNode_c* n = src._list; n != 0; n = n->next)
	{
		D_VoidListNode_c* node = new D_VoidListNode_c(
				n->val, 0);
		if( cur == 0)
			_list = node;
		else
			cur->next = node;
		cur = node;
	}
	_entries = src._entries;
}
#endif

void D_VoidList_c::clear()
{
	for( D_VoidListNode_c* n = _list; n != 0; )
	{
		D_VoidListNode_c* next = n->next;
		if( _del_func != 0)
			(*_del_func)( n->val, _del_data);
		delete n;
		n = next;
	}
	_list = 0;
	_entries = 0;
	_prev_node = 0;
	_prev_index = NO_SUCH_ELEMENT;
}

void D_VoidList_c::insert( void* val)
{
	D_VoidListNode_c* node = new D_VoidListNode_c( val, _list);
	_list = node;
	_entries ++ ;
	_prev_node = 0;
	_prev_index = NO_SUCH_ELEMENT;
}

void D_VoidList_c::remove()
{
	if( _list == 0)
		return;
	D_VoidListNode_c* node = _list->next;
	if( _del_func != 0)
		(*_del_func)( _list->val, _del_data);
	delete _list;
	_list = node;
	_entries -- ;
	_prev_node = 0;
	_prev_index = NO_SUCH_ELEMENT;
}

size_t D_VoidList_c::index( int (*testFunc)( void* elem, void* data),
		void* data) const
{
	size_t i = 0;
	for( D_VoidListNode_c* n = _list; n != 0; i ++, n = n->next)
	{
		int res = testFunc( n->val, data);
		if( res)
			return( i);
	}
	return( NO_SUCH_ELEMENT);
}

void* D_VoidList_c::at( size_t index)
{
	// most often case is sequential retrieving
	if( _prev_index != NO_SUCH_ELEMENT && index == _prev_index + 1)
	{
		_prev_node = _prev_node->next;
		_prev_index ++ ;
		return( _prev_node->val);
	}
	size_t i = 0;
	for( D_VoidListNode_c* n = _list; n != 0; i ++, n = n->next)
	{
		if( i == index)
		{
			_prev_node = n;
			_prev_index = index;
			return( n->val);
		}
	}
	// illegal operation - returning of 0 pointer
	return( 0);
}

