// gist_rtreecext.cc						-*- c++ -*-
// Copyright (c) 1997, 1998 Regents of the University of California
// $Id: gist_rtreecext.cc,v 1.3 2000/03/15 00:24:52 mashah Exp $

#ifdef __GNUG__
#pragma implementation "gist_rtreecext.h"
#endif

#include "gist_compat.h"	// for drand48()
#include "gist.h"		// for gist
#include "gist_rtreecext.h"

// VCPORT_B
#ifdef WIN32
#include <iostream>
#endif
// VCPORT_E

///////////////////////////////////////////////////////////////////////////////
// rtbase_cursorext_t
///////////////////////////////////////////////////////////////////////////////

rc_t
rtbase_cursorext_t::rtbaseItPrio(
    gist_cursor_t& cursor,
    const gist_p& page,
    int whichItem,
    const vec_t& keyv,
    gist_penalty_t& prio)
{
    assert(cursor.query != NULL);
    assert(cursor.cext != NULL);

    const rt_query_t* query = (const rt_query_t*) cursor.query;
    const rt_pred& sarg = *(query->value);
    int level = page.level();
    const rtbase_cursorext_t* cext =
	(const rtbase_cursorext_t*) cursor.cext;
    RtPrioFct pf = cext->prioTbl[level > 1][query->argType];
    if (pf != NULL) {
	prio = pf(keyv.ptr(0), keyv.len(0), sarg);
    }
    return(RCOK);
}

rc_t
rtbase_cursorext_t::rtbaseItState(
    gist_cursor_t& cursor,
    const gist_p& page,
    int whichItem,
    const vec_t& keyv,
    const gist_penalty_t& prio)
{
    assert(cursor.query != NULL);
    assert(cursor.cext != NULL);

    const rt_query_t* query = (const rt_query_t*) cursor.query;
    int level = page.level();
    const rtbase_cursorext_t* cext =
	(const rtbase_cursorext_t*) cursor.cext;
    RtStateFct sf = cext->stateTbl[level > 1][query->argType];
    if (sf != NULL) {
	W_DO(sf(cursor, page, whichItem, keyv, prio));
    }
    return(RCOK);
}

rtbase_cursorext_t::rtbase_cursorext_t(
    gist_cursorext_id id,
    ResetFct reset,
    RtPrioFctTbl prio,
    RtStateFctTbl state,
    FinalFct final)
    : gist_queue_cursorext_t(id, reset, &rtbaseItPrio, &rtbaseItState, final)
{
    for (int i = 0; i < rtbase_ext_t::numLvl; ++i) {
	for (int j = 0; j < rt_query_t::rt_numarg; ++j) {
	    prioTbl[i][j] = prio ? prio[i][j] : NULL;
	    stateTbl[i][j] = state ? state[i][j] : NULL;
	}
    }
}

///////////////////////////////////////////////////////////////////////////////
// rtbase_nn_cursorext_t
///////////////////////////////////////////////////////////////////////////////

rtbase_nn_cursorext_t::rtbase_nn_cursorext_t(
    gist_cursorext_id id,
    RtPrioFctTbl prio)
    : rtbase_cursorext_t(id, NULL, prio, NULL, NULL)
{
    // this extension just returns records -- we never use the
    // customized state functions in 'stateTbl'.
    stateFct = &defaultState;
}

///////////////////////////////////////////////////////////////////////////////
// rtbase_ar_cursorext_t
///////////////////////////////////////////////////////////////////////////////

#include "gist_rrtree.h"

rtbase_ar_cursorext_t::rtbase_ar_cursorext_t(
    gist_cursorext_id id,
    RtPrioFctTbl samplePrio)
    : gist_queue_set_cursorext_t(
	id, &arReset, &arSetPrio, &arSetState, &arFinal)
{
      for (int i = 0; i < rtbase_ext_t::numLvl; ++i) {
	for (int j = 0; j < rt_query_t::rt_numarg; ++j) {
	    prioTbl[i][j] = samplePrio ? samplePrio[i][j] : NULL;
	}
    }
}

int
rtbase_ar_cursorext_t::pick_prio(
    int nPrios,
    const gist_penalty_t prios[])
{
    if (nPrios == 1) {
	return(0);
    }

    double sum = 0.0;
    int i;
    for (i = 0; i < nPrios; ++i) {
	sum = sum + prios[i];
    }
    double pick = drand48() * sum;
    sum = 0.0;
    for (i = 0; i < nPrios; ++i) {
	sum = sum + prios[i];
	if (sum > pick) {
	    break;
	}
    }
    assert(i >= 0 && i < nPrios);
    return(i);
}

bool
rtbase_ar_cursorext_t::reject_prio(
    gist_penalty_t& actual,
    gist_penalty_t& estimated)
{
    assert(estimated > 0);
#if 0
    assert(actual > 0);
#endif
    assert(estimated >= actual);

    return(estimated * drand48() > actual);
}

void
rtbase_ar_cursorext_t::pick_frontier(
    gist_cursor_t& cursor)
{
    ArState* state = (ArState*) cursor.state;
    int chosen = pick_prio(state->frontier.size(), state->prios);
    gist_prioq_entry& e = state->frontier[chosen];
    assert(
	e.typ == gist_lstk_entry::eNode || e.typ == gist_lstk_entry::eItem);

    gist_prioq_t* queue = (gist_prioq_t*) cursor.iter;
    gist_prioq_entry* ep = new gist_prioq_entry;
    (void) memcpy(ep, &e, sizeof(e));
    queue->push(ep);

    state->prevPrio = 0.0;
}

rc_t
rtbase_ar_cursorext_t::arReset(
    gist_cursor_t& cursor)
{
    if (cursor.iter == NULL) {
	// clear from previous use
	ArState* state = (ArState*) cursor.state;
	delete [] state->prios;
	delete state;	// STL delete()s its own (copied) entries
	cursor.state = NULL;
    } else {
	// make ready for first use
	ArState* state = new ArState;
	state->total = state->n = state->prevPrio = 0.0;
	state->counts = new rr_counts;
	cursor.state = state;

	gist_prioq_t* queue = (gist_prioq_t*) cursor.iter;
	gist_prioq_entry e;
	double sum = 0.0;
	while (queue->empty() == false) {
	    queue->pop(&e);
	    state->frontier.push_back(e);
	}
	int nelems = state->frontier.size();
	e.typ = gist_lstk_entry::eIllegal;		// !gc
	int i;
	for (i = 0; i < nelems; ++i) {
	    assert(state->frontier[i].typ != gist_lstk_entry::eIllegal);
	}
	
	state->prios = new gist_penalty_t[nelems];
	for (i = 0; i < nelems; ++i) {
	    state->prios[i] = state->frontier[i].penalty;
	}
	
	pick_frontier(cursor);
    }
    return(RCOK);
}

rc_t
rtbase_ar_cursorext_t::arSetPrio(
    gist_cursor_t& cursor,
    const gist_p& page,
    int numWhich,
    const int which[],
    gist_penalty_t prios[])
{
    assert(numWhich >= 0 && numWhich <= page.nrecs());
    assert(numWhich == page.nrecs() || which != NULL);

    const rt_query_t* query = (const rt_query_t*) cursor.query;
    const rt_pred& sarg = *(query->value);
    int level = page.level();
    const rtbase_ar_cursorext_t* cext =
	(const rtbase_ar_cursorext_t*) cursor.cext;
    RtPrioFct bppf = cext->prioTbl[1][query->argType];
    RtPrioFct pf = cext->prioTbl[level > 1][query->argType];

    for (int i = 0; i < numWhich; i++) {
	int whichItem = which ? which[i] : i;
#if 0
	if (whichItem < gist_p::bpSlot || whichItem > page.nrecs()) {
	    return(eBADSLOTNUMBER);
	}
#endif
	if (whichItem > page.nrecs()) {
	    return(eBADSLOTNUMBER);
	}

	const keyrec_t& tup = page.rec(whichItem);
	gist::AlignedPred x;
	vec_t keyv;
	keyv.set(x.pred, gist_p::max_tup_sz);
	cursor.ext->getKey(page, whichItem, keyv);

#if 0
	if (whichItem == gist_p::bpSlot) {
	    prios[i] = bppf(keyv.ptr(0), keyv.len(0), sarg);
	} else {
#endif
	    prios[i] = pf(keyv.ptr(0), keyv.len(0), sarg);
#if 0
	}
#endif
    }
    
    return(RCOK);
}

rc_t
rtbase_ar_cursorext_t::arSetState(
    gist_cursor_t& cursor,
    const gist_p& page,
    int numWhich,
    const int which[],
    const gist_penalty_t prios[])
{
    assert(numWhich >= 0 && numWhich <= page.nrecs());
    assert(numWhich == page.nrecs() || which != NULL);

    ArState* state = (ArState*) cursor.state;

    if (state->prevPrio != 0.0) {
	gist_penalty_t bpPrio = 0.0;
#if 0
	int bpSlot = gist_p::bpSlot;
	W_DO(arSetPrio(cursor, page, 1, &bpSlot, &bpPrio));
#endif
	for (int i = 0; i < numWhich; ++i) {
	    bpPrio = bpPrio + prios[which[i]];
	}
	if (reject_prio(bpPrio, state->prevPrio) == true) {
#if defined(PRINT_OBJECTS)
	    std::cout << "REJECT " << bpPrio << " " << state->prevPrio << std::endl;
#endif
	    // state->total += 0.0;
	    state->n += 1.0;	// rejection counts as a sample
	    pick_frontier(cursor);
	    return(RCOK);
	}
    }

    if (page.is_leaf()) {
#if defined(PRINT_OBJECTS)
	std::cout << "ACCEPT" << std::endl;
#endif
	state->total += numWhich;
	state->n += 1.0;
	pick_frontier(cursor);
    } else {
	int chosen = pick_prio(numWhich, prios);
	state->prevPrio = prios[chosen];

	gist_prioq_t* queue = (gist_prioq_t*) cursor.iter;
	const keyrec_t& tup = page.rec(chosen);
	queue->push(new gist_prioq_entry(tup.child(), page.pid(),
	    prios[chosen]));
    }

    return(RCOK);
}

rc_t
rtbase_ar_cursorext_t::arFinal(
    gist_cursor_t& cursor,
    gist_prioq_entry& entry,
    bool isLast)
{
    // we never push eItems
    assert(entry.typ == gist_lstk_entry::eNode);
    if (isLast == true) {
	(void) memset(&entry, 0, sizeof(entry));
	entry.typ = gist_lstk_entry::eItem;
	entry.val.item.key = new rr_counts;
	entry.val.item.klen = sizeof(rr_counts);
	ArState* state = (ArState*) cursor.state;
	if (state->n != 0.0) {
	    state->counts->min = state->counts->ctr = state->counts->max =
		state->total / state->n;
	}
	(void) memcpy(entry.val.item.key, state->counts, sizeof(rr_counts));
	entry.val.item.data = new double(0.0);
	entry.val.item.dlen = sizeof(double);

	// this result record is the last thing returned!
	cursor.k = 1;
    }
    return(RCOK);
}
