// gist_rtreecext.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtreecext.h,v 1.1 1998/06/18 00:57:01 aoki Exp $

#ifndef GIST_RTREECEXT_H
#define GIST_RTREECEXT_H

#include <vector>

#include "gist_rtree.h"		// for rt_pred, etc.
#include "gist_cursorext.h"	// for gist_queue_cursorext_t

struct rr_counts {
    double min;
    double ctr;
    double max;

    rr_counts() : min(0.0), ctr(0.0), max(0.0) {}
};

//
// rtbase_cursorext_t
//
class rtbase_cursorext_t : public gist_queue_cursorext_t {
public:
    typedef double (*RtPrioFct)(
	const void* item,
	int itemLen,
	const rt_pred& queryPred);
    typedef RtPrioFct RtPrioFctTbl[rtbase_ext_t::numLvl][rt_query_t::rt_numarg];
    typedef rc_t (*RtStateFct)(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem,
	const vec_t& keyv,
	const gist_penalty_t& prio);
    typedef RtStateFct RtStateFctTbl[rtbase_ext_t::numLvl][rt_query_t::rt_numarg];

    rtbase_cursorext_t(
	gist_cursorext_id id,
	ResetFct reset,
	RtPrioFctTbl prio,
	RtStateFctTbl state,
	FinalFct final);
	
protected:
    RtPrioFctTbl prioTbl;
    RtStateFctTbl stateTbl;

    // rtbaseItPrio() and rtbaseItState() replace defaultPrio() and
    // defaultState(), calling the (slightly simplified) static
    // functions loaded into 'prioTbl' and 'stateTbl'.

    static rc_t rtbaseItPrio(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem,
	const vec_t& keyv,
	gist_penalty_t& prio);

    static rc_t rtbaseItState(
	gist_cursor_t& cursor,
	const gist_p& page,
	int whichItem,
	const vec_t& keyv,
	const gist_penalty_t& prio);
};

//
// rtbase_nn_cursorext_t
//
// this is just a simplification of rtbase_cursorext_t that just does
// traversal and therefore can ignore everything except the priority
// function.
//
class rtbase_nn_cursorext_t : public rtbase_cursorext_t {
public:
    rtbase_nn_cursorext_t(
	gist_cursorext_id id,
	RtPrioFctTbl prio);
};

//
// rtbase_ar_cursorext_t
//
class rtbase_ar_cursorext_t : public gist_queue_set_cursorext_t {
public:
    typedef struct {
	rr_counts* counts;
	double total;	// # of matching records sampled
	double n;	// # of records sampled (including rejections)
	std::vector<gist_prioq_entry> frontier;
	gist_penalty_t* prios;
	gist_penalty_t prevPrio;
    } ArState;

    typedef double (*RtPrioFct)(
	const void* item,
	int itemLen,
	const rt_pred& queryPred);
    typedef RtPrioFct RtPrioFctTbl[rtbase_ext_t::numLvl][rt_query_t::rt_numarg];
    
    rtbase_ar_cursorext_t(
	gist_cursorext_id id,
	RtPrioFctTbl samplePrio);
	
protected:
    RtPrioFctTbl prioTbl;

    // helpers for the static functions below

    static int pick_prio(
	int nPrios,
	const gist_penalty_t prios[]);

    static void pick_frontier(
	gist_cursor_t& cursor);

    static bool reject_prio(
	gist_penalty_t& actual,
	gist_penalty_t& estimated);

    // static functions to be stuck into the various
    // gist_queue_set_cursorext_t callback slots

    static rc_t arReset(
	gist_cursor_t& cursor);

    static rc_t arSetPrio(
	gist_cursor_t& cursor,
	const gist_p& page,
	int numWhich,
	const int which[],
	gist_penalty_t prios[]);

    static rc_t arSetState(
	gist_cursor_t& cursor,
	const gist_p& page,
	int numWhich,
	const int which[],
	const gist_penalty_t prios[]);

    static rc_t arFinal(
	gist_cursor_t& cursor,
	gist_prioq_entry& entry,
	bool isLast);
};

extern rtbase_ar_cursorext_t rr_point_ar_cext;

extern rtbase_nn_cursorext_t rt_point_nn_cext;
extern rtbase_nn_cursorext_t rt_rect_nn_cext;
extern rtbase_nn_cursorext_t rr_point_nn_cext;
extern rtbase_nn_cursorext_t sp_point_nn_cext;
extern rtbase_nn_cursorext_t ss_point_nn_cext;
extern rtbase_nn_cursorext_t sr_point_nn_cext;
extern rtbase_cursorext_t rr_point_it_cext;

extern gist_switch_cursorext_t rr_point_co_cext;

#endif // GIST_RTREECEXT_H
