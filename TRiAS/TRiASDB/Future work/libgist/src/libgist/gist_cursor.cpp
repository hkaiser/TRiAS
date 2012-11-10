// gist_cursor.cc
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_cursor.cc,v 1.12 2000/03/15 00:24:25 mashah Exp $


#ifdef __GNUG__
#pragma implementation "gist_cursor.h"
#endif

// VCPORT_B
#ifdef WIN32
#pragma warning(disable:4786) // Templates can cause names to get too long for
							  // debug information. Disables this warning.
#endif
// VCPORT_E

// VCPORT_B
#ifdef WIN32
#include <iostream>

using namespace std;
#else
#include <iostream.h>
#endif
// VCPORT_E

#include <new.h>
#include "gist_defs.h"
#include "gist_p.h"
#include "gist_ext.h"
#include "gist_cursor.h"
#include "gist_cursorext.h"

gist_lstk_entry::gist_lstk_entry(
    shpid_t page,
    shpid_t parent) : typ(eNode)
{
    val.node.page = page;
#ifdef AMDB
    val.node.parent = parent;
#endif // AMDB
    val.node.key = NULL;
    val.node.klen = 0;
}

gist_lstk_entry::gist_lstk_entry(
    void* key,
    smsize_t klen,
    void* data,
    smsize_t dlen,
    shpid_t page,
    int idx) : typ(eItem)
{
    val.item.klen = klen;
    val.item.key = (void *) new char[klen];
    assert(val.item.key);
    (void) memcpy(val.item.key, key, klen);
    val.item.dlen = dlen;
    val.item.data = (void *) new char[dlen];
    assert(val.item.data);
    (void) memcpy(val.item.data, data, dlen);
    val.item.page = page;
    val.item.idx = idx;
}

// don't throw the stuff behind key and data away
gist_lstk_entry::~gist_lstk_entry()
{
}

gist_prioq_entry::gist_prioq_entry(
    shpid_t page,
    shpid_t parent,
    const gist_penalty_t& p,
    const void* key,
    smsize_t klen)
    : gist_lstk_entry(page, parent), penalty(p)
{
    if (key != NULL && klen > 0) {
	val.node.key = new char[klen];
	val.node.klen = klen;
	assert(val.node.key != NULL);
	assert(val.node.klen <= gist_p::max_tup_sz);
	(void) memcpy(val.node.key, key, klen);
    }
}

gist_prioq_entry::gist_prioq_entry(
    void* key,
    smsize_t klen,
    void* data,
    smsize_t dlen,
    shpid_t page,
    int idx,
    const gist_penalty_t& p) :
    gist_lstk_entry(key, klen, data, dlen, page, idx),
    penalty(p)
{
}

gist_prioq_entry::~gist_prioq_entry()
{
    switch (typ) {
    case eItem:
        delete [] val.item.key;
        delete [] val.item.data;
	break;
    case eNode:
        delete [] val.node.key;
	break;
    default:
	break;
    }
}

bool
gist_lstk::is_full()
{
    return _top >= lstk_chunk+lstk_chunk*lstk_chunk;
}

bool
gist_lstk::is_empty()
{
    return _top == 0;
}

gist_lstk::gist_lstk()
{
    _top = 0;
    for (int i = 0; i < lstk_chunk; i++) {
	_indirect[i] = NULL;
    }
}

gist_lstk::~gist_lstk()
{
    reset();
}

void
gist_lstk::push(
    shpid_t 			pid,
    shpid_t 			parent)
{
    (void) _push(gist_lstk_entry::eNode, pid, parent, NULL, 0, NULL, 0, 0);
}

void
gist_lstk::push(
    void*		key,
    smsize_t 		klen,
    void*		data,
    smsize_t 		dlen,
    shpid_t 		page,
    int 		idx)
{
    (void) _push(gist_lstk_entry::eItem, page, 0, key, klen, data, dlen, idx);
}

gist_lstk_entry &
gist_lstk_entry::operator=(
    const gist_lstk_entry&	e)
{
    this->typ = e.typ;
    if (e.typ == eNode) {
        this->val.node.page = e.val.node.page;
#ifdef AMDB
        this->val.node.parent = e.val.node.parent;
#endif
    } else {
        this->val.item.key = e.val.item.key;
        this->val.item.klen = e.val.item.klen;
        this->val.item.data = e.val.item.data;
        this->val.item.dlen = e.val.item.dlen;
        this->val.item.page = e.val.item.page;
        this->val.item.idx = e.val.item.idx;
    }
    return *this;
}

void
gist_lstk::pop(
    gist_lstk_entry&	e)
{
    assert(! is_empty());
    if (_top <= lstk_chunk) {
	_top--;
	e = _stk[_top];
    } else {
	_top--;
	e = _indirect[_top/lstk_chunk-1][_top%lstk_chunk];
	if (_top >= lstk_chunk && _top % lstk_chunk == 0) {
	    delete [] _indirect[_top/lstk_chunk - 1];
	    _indirect[_top/lstk_chunk - 1] = 0;
	}
    }
}

gist_lstk_entry* 
gist_lstk::_push(
    gist_lstk_entry::eType	typ,
    shpid_t 			pid,
    shpid_t 			parent,
    void*			key,
    smsize_t			klen,
    void* 			data,
    smsize_t			dlen,
    int				idx)
{
    gist_lstk_entry *target;

    // locate position on stack
    assert(!is_full());
    if (_top < lstk_chunk) {
	target = &_stk[_top];
	_top++;
    } else {
	int2 pos = _top / lstk_chunk - 1;
	int2 off = _top % lstk_chunk;
	if (!_indirect[pos]) {
	    _indirect[pos] = new gist_lstk_entry[lstk_chunk];
	}
	target = &_indirect[pos][off];
	_top++;
    }

    if (typ == gist_lstk_entry::eNode) {
	// new gist_lstk_entry will be stored at target
	target = new (target) gist_lstk_entry(pid, parent);
    } else {
	target = new (target) gist_lstk_entry(key, klen, data, dlen, pid, idx);
    }

    return (target);
}

void
gist_lstk::reset()
{
    // pop all entries of stack and erase key and data
    while (_top > 0) {
	gist_lstk_entry e;
	(void) pop(e);
	switch (e.typ) {
	case gist_lstk_entry::eItem:
	    delete e.val.item.key;
	    delete e.val.item.data;
	    break;
	case gist_lstk_entry::eNode:
	    delete e.val.node.key;
	    break;
	default:
	    break;
	}
    }
}

/*
 * gist_prioq_t
 */

gist_prioq_t::gist_prioq_t() : queue(NULL)
{
    queue = new Queue();
}

gist_prioq_t::~gist_prioq_t() {
    reset();
    delete queue;
}
  
void
gist_prioq_t::push(gist_prioq_entry* e)
{
    queue->push_back(e);
    push_heap(queue->begin(), queue->end(), comp);
}

void
gist_prioq_t::pop(gist_prioq_entry* e)
{
    gist_prioq_entry* res = queue->front();
    (void) memcpy(e, res, sizeof(*res));
    pop_heap(queue->begin(), queue->end(), comp);
    queue->pop_back();

    // if we don't reset the entry type, the destructor for 'res' will
    // free 'key'/'data' now (we want the destructor of 'e' to free
    // them).
    res->typ = gist_lstk_entry::eIllegal;
    delete res;
}

void
gist_prioq_t::reset()
{
    for (Queue::iterator it = queue->begin(); it != queue->end(); it++) {
	delete *it;
    }
    queue->erase(queue->begin(), queue->end());
}

/*
 * gist_cursor_t
 */

void
gist_cursor_t::reset()
{
    k = 0;
    io = 0;
    cext->iter_reset(*this);
}
