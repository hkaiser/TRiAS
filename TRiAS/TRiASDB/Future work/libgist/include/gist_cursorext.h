// gist_cursorext.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_cursorext.h,v 1.2 1999/09/27 01:08:51 marcel Exp $

#ifndef GIST_CURSOREXT_H
#define GIST_CURSOREXT_H

#ifdef __GNUG__
#pragma interface "gist_cursorext.h"
#endif

#include "gist_defs.h"		// for shpid_t
#include "gist_p.h"		// for gist_p::max_scnt
#include "gist_ext.h"		// for gist_penalty_t
#include "gist_cursor.h"	// for gist_lstk

//
// gist_cursorext_t
//
// a given gist_cursorext_t may be applied to any gist_ext_t that
// contains the same pair of internal/leaf key types and supports the
// relevant query predicate.  just as a gist_ext_t corresponds to the
// 4-tuple <internal-type,leaf-type,query-type,tree> and contains the
// necessary "system catalog" information for that combination, a
// gist_cursorext_t corresponds to the 4-tuple 
// <internal-type,leaf-type,query-type,iterator> (iterator implies both 
// a traversal order and a result).
//
// note that these methods must be able to handle the predicates found
// at any level of the tree.  how a given gist_cursorext_t handles
// this is extension-specific.
//
// in general, extenders should not need to subclass this class at
// all.
//
class gist_cursorext_t {
public:
    enum gist_cursorext_id {
	cext_stack_id,
	cext_rt_point_nn_id,
	cext_rt_rect_nn_id,
	cext_sp_point_nn_id,
	cext_ss_point_nn_id,
	cext_sr_point_nn_id,
	cext_rr_point_nn_id,
	cext_rr_point_it_id,
	cext_rr_point_ar_id,
	cext_rr_point_co_id,
	cext_npt_id,
	cext_numext
    };

    static gist_cursorext_t* gist_cursorext_list[cext_numext];

    // register/deregister this extension in the global extension
    // table
    gist_cursorext_t(gist_cursorext_id id);
    virtual ~gist_cursorext_t();

    virtual bool prio() = 0;

    // clear all state
    virtual rc_t iter_reset(
	gist_cursor_t& cursor) = 0;

    // prepare for query execution
    virtual rc_t iter_init(
	gist_cursor_t& cursor,		// in
	const shpid_t& root) = 0;	// in

    // updates the internal cursor state with the specified contents
    // of 'page'.  'which' and 'numWhich' correspond to the out
    // parameters of gist_ext_t::search().
    virtual rc_t iter_update(
	gist_cursor_t& cursor,		// in
	const gist_p& page,		// in
	int numWhich,			// in
	const int which[]) = 0;		// in/out

    // copies a result record into the provided buffer if one is
    // currently available.  returns RCOK if a result has been placed
    // in 'item' and eEOF if no further results will ever be returned.
    virtual rc_t iter_fetch(
	gist_cursor_t& cursor,		// in
	void* item) = 0;		// out

protected:
    gist_cursorext_id myId;
};

//
// gist_stack_cursorext_t
//
// the existence of this class is an optimization hack.  we can
// simulate depth-first search using priority queues trivially, but
// it's nice to make the common case (unprioritized retrieval of
// records) as low-overhead as possible.
//
// as part of this optimization, we define this class to return
// records in "physical order".  (if an application wants to retrieve
// records in any other order, it should be doing so explicitly using
// gist_queue_set_cursorext_t or a subclass.)  this lets structures
// like B-trees (which maintain their entries in a specific order)
// work without any special logic.
//
// only applications that want stack-based traversal should subclass
// this class.
//
class gist_stack_cursorext_t : public gist_cursorext_t {
public:
    gist_stack_cursorext_t(gist_cursorext_id id);

    bool prio() { return(false); }

    virtual rc_t iter_reset(
	gist_cursor_t& cursor);

    virtual rc_t iter_init(
	gist_cursor_t& cursor,
	const shpid_t& root);

    virtual rc_t iter_update(
	gist_cursor_t& cursor,
	const gist_p& page,
	int numWhich,
	const int which[]);

    virtual rc_t iter_fetch(
	gist_cursor_t& cursor,
	void* item);

protected:
    static rc_t push_leaf(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem);

    static rc_t push_node(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem);
};

extern gist_stack_cursorext_t stack_cext;

//
// gist_queue_set_cursorext_t
//
// this implements one case of prioritized traversal: priority and
// state functions that are applied to each matching node entry on a
// page, as a set.  (hence, setPrioFct() and setStateFct() will always
// be called for a page, even if the record set is empty.)  this
// occurs, e.g., when we choose a subset of node entries from a page
// -- random sampling, left-side-only descent to the leaf level, etc.
//
// there aren't many cases where you should be subclassing this class.
//
class gist_queue_set_cursorext_t : public gist_cursorext_t  {
public:
    typedef rc_t (*ResetFct)(
	gist_cursor_t& cursor);
    typedef rc_t (*FinalFct)(
	gist_cursor_t& cursor,
	gist_prioq_entry& entry,
	bool isLast);			// true if clearing out the queue
    typedef rc_t (*SetPrioFct)(
	gist_cursor_t& cursor,
	const gist_p& page,
	int numWhich,
	const int which[],
	gist_penalty_t prios[]);
    typedef rc_t (*SetStateFct)(
	gist_cursor_t& cursor,
	const gist_p& page,
	int numWhich,
	const int which[],
	const gist_penalty_t prios[]);

    bool prio() { return(true); }

    gist_queue_set_cursorext_t(
	gist_cursorext_id id,
	ResetFct reset,
	SetPrioFct prio,
	SetStateFct state,
	FinalFct final);

    virtual rc_t iter_reset(
	gist_cursor_t& cursor);

    virtual rc_t iter_init(
	gist_cursor_t& cursor,
	const shpid_t& root);

    virtual rc_t iter_update(
	gist_cursor_t& cursor,
	const gist_p& page,
	int numWhich,
	const int which[]);

    virtual rc_t iter_fetch(
	gist_cursor_t& cursor,
	void* item);

    // helper functions - these can be called by user-defined state
    // functions

    static rc_t push_leaf(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem,
	const vec_t& keyv,
	const gist_penalty_t& prio);

    // does not push the key onto the queue
    static rc_t push_node(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem,
	const vec_t& keyv,
	const gist_penalty_t& prio);

    // does push the key onto the queue
    static rc_t push_node_key(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem,
	const vec_t& keyv,
	const gist_penalty_t& prio);

protected:
    ResetFct resetFct;
    SetPrioFct setPrioFct;
    SetStateFct setStateFct;
    FinalFct finalFct;

    static rc_t defaultReset(
	gist_cursor_t& cursor);
 
    static rc_t defaultFinal(
	gist_cursor_t& cursor,
	gist_prioq_entry& entry,
	bool isLast);
};

//
// gist_queue_cursorext_t
//
// this implements the common case of prioritized traversal: priority
// and state functions that are applied independently to each matching
// node entry.  (note that this implies that prioFct() and stateFct()
// will not be called at all for a page if none of the records match!)
//
// most NN-type applications should be subclassing this class.
//
class gist_queue_cursorext_t : public gist_queue_set_cursorext_t  {
public:
    typedef rc_t (*PrioFct)(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem,
	const vec_t& keyv,
	gist_penalty_t& prio);

    typedef rc_t (*StateFct)(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem,
	const vec_t& keyv,
	const gist_penalty_t& prio);

    gist_queue_cursorext_t(
	gist_cursorext_id id,
	ResetFct reset,
	PrioFct prio,
	StateFct state,
	FinalFct final);

    // this is optimized for the case where we call prioFct() and
    // stateFct() consecutively on the same record.
    virtual rc_t iter_update(
	gist_cursor_t& cursor,
	const gist_p& page,
	int numWhich,
	const int which[]);

    static rc_t defaultPrio(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem,
	const vec_t& keyv,
	gist_penalty_t& prio);

    // useful for cursor extension object initializations
    static rc_t defaultState(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem,
	const vec_t& keyv,
	const gist_penalty_t& prio);

protected:
    PrioFct prioFct;
    StateFct stateFct;
};

//
// gist_switch_cursorext_t
//
// implements a simple cursor extension that can switch (once) between
// two other cursor extensions.  'switchFct' is called after each call
// to iter_update(); the switch occurs the first time it returns
// 'true'.
//
// this interface is deprecated.  the design for this class isn't as
// well thought-out as the others; very few user applications should
// need to do this.
//
class gist_switch_cursorext_t : public gist_cursorext_t {
public:
    typedef bool (*SwitchFct)(gist_cursor_t& cursor);

    gist_switch_cursorext_t(
	gist_cursorext_id id0,
	SwitchFct sf,
	gist_cursorext_id id1,
	gist_cursorext_id id2);

    bool prio() { return(true); }

    virtual rc_t iter_reset(
	gist_cursor_t& cursor);

    virtual rc_t iter_init(
	gist_cursor_t& cursor,
	const shpid_t& root);

    virtual rc_t iter_update(
	gist_cursor_t& cursor,
	const gist_p& page,
	int numWhich,
	const int which[]);

    virtual rc_t iter_fetch(
	gist_cursor_t& cursor,
	void* item);

protected:
    SwitchFct switchFct;

    struct state {
	int which;
	gist_cursor_t cursors[2];
    };

    // internal helper routine - copies only the parts of the cursor
    // that affect the cursor extension (cext, iter, state) and not
    // the parts that are "global" (k, io, etc.).
    static void cursor_copy(
	gist_cursor_t& c1,
	const gist_cursor_t& c2);

    gist_cursorext_id id[2];
    gist_cursorext_t* cext[2];
};

#endif // GIST_CURSOREXT_H
