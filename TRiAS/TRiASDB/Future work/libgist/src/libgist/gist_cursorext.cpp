// gist_cursorext.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_cursorext.cc,v 1.4 1998/12/14 00:46:50 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_cursorext.h"
#endif

#include "gist.h"		// for gist::AlignedPred
#include "gist_cursorext.h"

//
// the static (i.e., global) table of cursor extensions; each cursor
// extension registers itself here so the user can call it (if the
// extension is not instantiated, e.g., because the appropriate object
// file was never linked into the application, it will not appear in
// the table and therefore cannot be called).
//
gist_cursorext_t* 
gist_cursorext_t::gist_cursorext_list[gist_cursorext_t::cext_numext];

//
// stack-based record traversal is used by internal routines (e.g.,
// gist::remove()), so we instantiate it here in the main libgist
// library.
//
gist_stack_cursorext_t stack_cext(gist_cursorext_t::cext_stack_id);

///////////////////////////////////////////////////////////////////////////////
// gist_cursorext_t
///////////////////////////////////////////////////////////////////////////////

gist_cursorext_t::gist_cursorext_t(gist_cursorext_id id)
{
    assert(id >= 0 && id < cext_numext);

    gist_cursorext_list[id] = this;

    myId = id;
}

gist_cursorext_t::~gist_cursorext_t()
{
    assert(myId >= 0 && myId < cext_numext);
    assert(gist_cursorext_list[myId] == this);

    gist_cursorext_list[myId] = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// gist_stack_cursorext_t
///////////////////////////////////////////////////////////////////////////////

gist_stack_cursorext_t::gist_stack_cursorext_t(gist_cursorext_id id)
    : gist_cursorext_t(id)
{
}

rc_t
gist_stack_cursorext_t::iter_reset(
    gist_cursor_t& cursor)
{
    assert(cursor.iter != NULL);

    gist_lstk* stack = (gist_lstk*) cursor.iter;
    stack->reset();
    delete stack;
    cursor.iter = NULL;

    return(RCOK);
}

rc_t
gist_stack_cursorext_t::iter_init(
    gist_cursor_t& cursor,
    const shpid_t& root)
{
    assert(cursor.iter == NULL);

    gist_lstk* stack = new gist_lstk();
    stack->push(root, root);
    cursor.iter = stack;

    return(RCOK);
}

rc_t
gist_stack_cursorext_t::push_leaf(
    gist_cursor_t& cursor,
    const gist_p& page,
    int whichItem)
{
    gist_lstk* stack = (gist_lstk*) cursor.iter;
    const keyrec_t& tup = page.rec(whichItem);
    gist::AlignedPred x;
    vec_t keyv;
    keyv.set(x.pred, gist_p::max_tup_sz);
    cursor.ext->getKey(page, whichItem, keyv);
    stack->push((void *) keyv.ptr(0), keyv.len(0),
	(void *) tup.elem(), tup.elen(), page.pid(), whichItem);

    return(RCOK);
}

rc_t
gist_stack_cursorext_t::push_node(
    gist_cursor_t& cursor,
    const gist_p& page,
    int whichItem)
{
    gist_lstk* stack = (gist_lstk*) cursor.iter;
    const keyrec_t& tup = page.rec(whichItem);
    if (tup.child() == 0) {
	return(eBADSLOTNUMBER);
    }
    (void) stack->push(tup.child(), page.pid());

    return(RCOK);
}

rc_t
gist_stack_cursorext_t::iter_update(
    gist_cursor_t& cursor,
    const gist_p& page,
    int numWhich,
    const int which[])
{
    assert(numWhich >= 0 && numWhich <= page.nrecs());
    assert(numWhich == page.nrecs() || which != NULL);
    assert(cursor.iter != NULL);
    
    for (int i = numWhich - 1; i >= 0; i--) {
	int whichItem = which ? which[i] : (numWhich - 1) - i;
	if (whichItem < 0 || whichItem > page.nrecs()) {
	    return(eBADSLOTNUMBER);
	}
	if (page.is_leaf()) {
	    W_DO(push_leaf(cursor, page, whichItem));
	} else {
	    W_DO(push_node(cursor, page, whichItem));
	}
    }

    return(RCOK);
}

rc_t
gist_stack_cursorext_t::iter_fetch(
    gist_cursor_t& cursor,
    void* item)
{
    assert(cursor.iter != NULL);
    assert(item != NULL);

    gist_lstk* stack = (gist_lstk*) cursor.iter;
    gist_lstk_entry* ep = (gist_lstk_entry*) item;

    if (cursor.k <= 0 || stack->is_empty()) {
	return(eEOF);
    }

    stack->pop(*ep);
    switch (ep->typ) {
    case gist_lstk_entry::eItem:
	// from above we know cursor.k > 0
	cursor.k--;
	break;
    case gist_lstk_entry::eNode:
	if (cursor.io <= 0) {
	    // there are no records left in the stack -- this is
	    // depth-first search, so eItems will always be at the
	    // top, if there are any.
	    return(eEOF);
	}
	cursor.io--;
	break;
    default:
	break;
    }

    return(RCOK);
}

///////////////////////////////////////////////////////////////////////////////
// gist_queue_set_cursorext_t
///////////////////////////////////////////////////////////////////////////////

gist_queue_set_cursorext_t::gist_queue_set_cursorext_t(
    gist_cursorext_id id,
    ResetFct reset,
    SetPrioFct prio,
    SetStateFct state,
    FinalFct final)
    : gist_cursorext_t(id), setPrioFct(prio), setStateFct(state)
{
    resetFct = (reset == NULL) ? &defaultReset : reset;
    finalFct = (final == NULL) ? &defaultFinal : final;
}

rc_t
gist_queue_set_cursorext_t::defaultReset(
    gist_cursor_t& cursor)
{
    return(RCOK);
}

rc_t
gist_queue_set_cursorext_t::iter_reset(
    gist_cursor_t& cursor)
{
    assert(cursor.iter != NULL);

    gist_prioq_t* queue = (gist_prioq_t*) cursor.iter;
    queue->reset();
    delete queue;
    cursor.iter = NULL;

    W_DO(resetFct(cursor));

    return(RCOK);
} 

rc_t
gist_queue_set_cursorext_t::iter_init(
    gist_cursor_t& cursor,
    const shpid_t& root)
{
    assert(cursor.iter == NULL);

    // the penalty for the first item in the queue doesn't matter --
    // we're just going to pop it off immediately.
    gist_prioq_t* queue = new gist_prioq_t;
    queue->push(new gist_prioq_entry(root, root, 0.0));
    cursor.iter = queue;

    W_DO(resetFct(cursor));

    return(RCOK);
}

rc_t
gist_queue_set_cursorext_t::push_leaf(
    gist_cursor_t& cursor,
    const gist_p& page,
    int whichItem,
    const vec_t& keyv,
    const gist_penalty_t& prio)
{
    gist_prioq_t* queue = (gist_prioq_t*) cursor.iter;
    const keyrec_t& tup = page.rec(whichItem);
    queue->push(new gist_prioq_entry((void *) keyv.ptr(0), keyv.len(0),
	(void *) tup.elem(), tup.elen(), page.pid(), whichItem, prio));

    return(RCOK);
}

rc_t
gist_queue_set_cursorext_t::push_node(
    gist_cursor_t& cursor,
    const gist_p& page,
    int whichItem,
    const vec_t& keyv,
    const gist_penalty_t& prio)

{
    gist_prioq_t* queue = (gist_prioq_t*) cursor.iter;
    const keyrec_t& tup = page.rec(whichItem);
    if (tup.child() == 0) {
	return(eBADSLOTNUMBER);
    }
    queue->push(new gist_prioq_entry(tup.child(), page.pid(), prio));

    return(RCOK);
}

rc_t
gist_queue_set_cursorext_t::push_node_key(
    gist_cursor_t& cursor,
    const gist_p& page,
    int whichItem,
    const vec_t& keyv,
    const gist_penalty_t& prio)
{
    gist_prioq_t* queue = (gist_prioq_t*) cursor.iter;
    const keyrec_t& tup = page.rec(whichItem);
    if (tup.child() == 0) {
	return(eBADSLOTNUMBER);
    }
    queue->push(new gist_prioq_entry(tup.child(), page.pid(), prio,
	(void *) keyv.ptr(0), keyv.len(0)));

    return(RCOK);
}

rc_t
gist_queue_set_cursorext_t::iter_update(
    gist_cursor_t& cursor,
    const gist_p& page,
    int numWhich,
    const int which[])
{
    assert(numWhich >= 0 && numWhich <= page.nrecs());
    assert(numWhich == page.nrecs() || which != NULL);
    assert(cursor.iter != NULL);

    gist_penalty_t prios[gist_p::max_scnt];
    W_DO(setPrioFct(cursor, page, numWhich, which, prios));
    W_DO(setStateFct(cursor, page, numWhich, which, prios));
    
    return(RCOK);
}

rc_t
gist_queue_set_cursorext_t::defaultFinal(
    gist_cursor_t& cursor,
    gist_prioq_entry& entry,
    bool isLast)
{
    // by doing nothing, we will default to returning leaf entries
    // from the queue until we run out (or hit the retrieval limit).
    return((isLast == true) ? eEOF : RCOK);
}

rc_t
gist_queue_set_cursorext_t::iter_fetch(
    gist_cursor_t& cursor,
    void* item)
{
    assert(cursor.iter != NULL);
    assert(item != NULL);

    gist_prioq_t* queue = (gist_prioq_t*) cursor.iter;
    gist_prioq_entry* ep = (gist_prioq_entry*) item;

    if (cursor.k <= 0) {
	return(eEOF);
    }

    while (queue->empty() == false) {
	queue->pop(ep);
	if (cursor.io > 0) {
	    if (ep->typ == gist_lstk_entry::eItem) {
		cursor.k--;
	    } else if (ep->typ == gist_lstk_entry::eNode) {
		cursor.io--;
		delete [] ep->val.node.key;
	    }
	    return(RCOK);
	}
	// we're in the cleanup phase
	W_DO(finalFct(cursor, *ep, false));
	if (ep->typ == gist_lstk_entry::eItem) {
	    cursor.k--;
	    return(RCOK);
	} else if (ep->typ == gist_lstk_entry::eNode) {
	    delete [] ep->val.node.key;
	}
    }
    // we're in the wrapup phase
    W_DO(finalFct(cursor, *ep, true));
    if (ep->typ == gist_lstk_entry::eItem) {
	cursor.k--;
	return(RCOK);
    }

    return(eEOF);
}

///////////////////////////////////////////////////////////////////////////////
// gist_queue_cursorext_t
///////////////////////////////////////////////////////////////////////////////

gist_queue_cursorext_t::gist_queue_cursorext_t(
    gist_cursorext_id id,
    ResetFct reset,
    PrioFct prio,
    StateFct state,
    FinalFct final)
    : gist_queue_set_cursorext_t(id, reset, NULL, NULL, final)
{
    prioFct = (prio == NULL) ? defaultPrio : prio;
    stateFct = (state == NULL) ? defaultState : state;
}

rc_t
gist_queue_cursorext_t::defaultPrio(
    gist_cursor_t& cursor,
    const gist_p& page,
    int whichItem,
    const vec_t& keyv,
    gist_penalty_t& prio)
{
    prio = 1.0;

    return(RCOK);
}

rc_t
gist_queue_cursorext_t::defaultState(
    gist_cursor_t& cursor,
    const gist_p& page,
    int whichItem,
    const vec_t& keyv,
    const gist_penalty_t& prio)
{
    if (page.is_leaf()) {
	W_DO(push_leaf(cursor, page, whichItem, keyv, prio));
    } else {
	W_DO(push_node(cursor, page, whichItem, keyv, prio));
    }

    return(RCOK);
}

rc_t
gist_queue_cursorext_t::iter_update(
    gist_cursor_t& cursor,
    const gist_p& page,
    int numWhich,
    const int which[])
{
    assert(numWhich >= 0 && numWhich <= page.nrecs());
    assert(numWhich == page.nrecs() || which != NULL);

    for (int i = 0; i < numWhich; i++) {
	int whichItem = which ? which[i] : i;
	if (whichItem < 0 || whichItem > page.nrecs()) {
	    return(eBADSLOTNUMBER);
	}

	const keyrec_t& tup = page.rec(whichItem);
	gist::AlignedPred x;
	vec_t keyv;
	keyv.set(x.pred, gist_p::max_tup_sz);
	cursor.ext->getKey(page, whichItem, keyv);

	gist_penalty_t prio;
	W_DO(prioFct(cursor, page, whichItem, keyv, prio));
	W_DO(stateFct(cursor, page, whichItem, keyv, prio));
    }
    
    return(RCOK);
}

///////////////////////////////////////////////////////////////////////////////
// gist_switch_cursorext_t
///////////////////////////////////////////////////////////////////////////////

gist_switch_cursorext_t::gist_switch_cursorext_t(
    gist_cursorext_id id0,
    SwitchFct sf,
    gist_cursorext_id id1,
    gist_cursorext_id id2)
    : gist_cursorext_t(id0),
      switchFct(sf)
{
    id[0] = id1;
    id[1] = id2;
    cext[0] = gist_cursorext_list[id1];
    cext[1] = gist_cursorext_list[id2];
}

void
gist_switch_cursorext_t::cursor_copy(
    gist_cursor_t& c1,
    const gist_cursor_t& c2)
{
    c1.cext = c2.cext;
    c1.iter = c2.iter;
    c1.state = c2.state;
}

rc_t
gist_switch_cursorext_t::iter_reset(
    gist_cursor_t& cursor)
{
    state* s = (state*) cursor.state;

    rc_t status = RCOK;

    gist_cursor_t tmp;
    cursor_copy(tmp, cursor);
    for (int i = 0; i < 2 && status == RCOK; ++i) {
	cursor_copy(cursor, s->cursors[i]);
	status = cext[i]->iter_reset(cursor);
	cursor_copy(s->cursors[i], cursor);
    }
    cursor_copy(cursor, tmp);

    delete s;
    cursor.state = NULL;

    return(status);
}

rc_t
gist_switch_cursorext_t::iter_init(
    gist_cursor_t& cursor,
    const shpid_t& root)
{
    state* s = new state;
    s->which = 0;
    cursor.state = s;

    rc_t status = RCOK;

    gist_cursor_t tmp;
    cursor_copy(tmp, cursor);
    for (int i = 0; i < 2 && status == RCOK; ++i) {
	cursor_copy(cursor, s->cursors[i]);
	cursor.cext = cext[i];
	status = cext[i]->iter_init(cursor, root);
	cursor_copy(s->cursors[i], cursor);
    }
    cursor_copy(cursor, tmp);

    return(status);
}

rc_t
gist_switch_cursorext_t::iter_update(
    gist_cursor_t& cursor,
    const gist_p& page,
    int numWhich,
    const int which[])
{
    state* s = (state*) cursor.state;

    gist_cursor_t tmp;
    cursor_copy(tmp, cursor);
    cursor_copy(cursor, s->cursors[s->which]);
    rc_t status = cext[s->which]->iter_update(cursor, page, numWhich, which);
    cursor_copy(s->cursors[s->which], cursor);
    cursor_copy(cursor, tmp);

    if (switchFct(cursor) == true) {
	s->which = 1;
    }

    return(status);
}

rc_t
gist_switch_cursorext_t::iter_fetch(
    gist_cursor_t& cursor,
    void* item)
{
    state* s = (state*) cursor.state;

    gist_cursor_t tmp;
    cursor_copy(tmp, cursor);
    cursor_copy(cursor, s->cursors[s->which]);
    rc_t status = cext[s->which]->iter_fetch(cursor, item);
    cursor_copy(s->cursors[s->which], cursor);
    cursor_copy(cursor, tmp);

    return(status);
}
