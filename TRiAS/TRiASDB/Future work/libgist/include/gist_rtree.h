// gist_rtree.h							-*- c++ -*-
// Copyright (c) 1997, 1998, Regents of the University of California
// $Id: gist_rtree.h,v 1.18 2000/03/10 01:39:04 mashah Exp $

#ifndef GIST_RTREE_H
#define GIST_RTREE_H

#ifdef __GNUG__
#pragma interface "gist_rtree.h"
#endif

#include "gist_query.h"		// for gist_query_t
#include "gist_cursorext.h"	// for gist_cursorext_t::*
#include "gist_unordered.h"	// for gist_unordered_ext_t
#include "gist_unorderedn.h"	// for gist_unorderedn_ext_t
#ifdef AMDB
#include "amdb_ext.h"
#endif

class rt_pred;

///////////////////////////////////////////////////////////////////////////////
// rt_query_t
///////////////////////////////////////////////////////////////////////////////

class rt_query_t : public gist_query_t {
public:
    enum rt_oper {
        rt_nooper,
	rt_equal,
	rt_overlap,
	rt_contains,	// stored key contains query key
	rt_contained,	// stored key is contained by query key
	rt_nearest,
	rt_count_overlap,
	rt_count_sample,
	rt_count_combo,
	rt_numoper
    };

    // The type of the search argument (i.e., of 'value').  Not all
    // extensions necessarily support all search argument types.
    enum rt_arg {
        rt_pointarg,
	rt_rectarg,
	rt_numarg
    };

    rt_query_t(rt_oper oper, rt_arg arg, rt_pred* val) :
        oper(oper), argType(arg), value(val) {}

    ~rt_query_t(); // calls destructor for parameter

    rt_oper oper;
    rt_arg argType;
    rt_pred* value;
};

///////////////////////////////////////////////////////////////////////////////
// rt_ext_t
///////////////////////////////////////////////////////////////////////////////

class rtbase_ext_t : public gist_unordered_ext_t {
public:

	// VCPORT_B
    static const float MINSPLITUTIL;

	enum rt_lvl {
		numLvl = 2
	};

	// VCPORT_E

    enum rt_conv {
	rt_dim = 0,
	rt_size,
	rt_numconv
    };

    enum rt_prop {
	rt_span = 0,
	rt_margin,
	rt_numprop
    };

    enum rt_bpcmp {
	rt_bpequal = 0,	// bp (internal predicate) equality
	rt_bpleaf,	// internal predicate contains leaf predicate
	rt_bpint,	// internal predicate contains internal predicate
	rt_bpnumcmp
    };

    // function table for consistent(): one for each operator (e.g.,
    // contains), possible argument type and leaf/internal level
    typedef bool (*CmpFct)(const void* item, int len, const rt_pred& pred);

    typedef CmpFct CmpFctTbl[numLvl][rt_query_t::rt_numarg][rt_query_t::rt_numoper];

    CmpFctTbl cmpFcts;
    typedef CmpFct BpCmpFctTbl[rt_bpnumcmp];
    BpCmpFctTbl bpCmpFcts;

    // for penalty()/pickSplit()/union_key():
    typedef rt_pred* (*PredFct)(rt_pred* pred, const void* item, int len, bool preserve);
    typedef PredFct ExpandFctTbl[numLvl];
    ExpandFctTbl expandFcts;
        // expand BP with key/bp; if bp == NULL, create a new BP from the given BP/key
    typedef double (*PropFct)(const rt_pred& pred);
    typedef PropFct PropFctTbl[numLvl][rt_numprop];
    PropFctTbl propFcts;	// compute a particular property of a predicate

    // general utility:
    typedef int (*ConvFct)(int n);
    typedef ConvFct ConvFctTbl[numLvl][rt_numconv];
    ConvFctTbl convFcts;	// returns dimension (size) of key/bp

    typedef gist_cursorext_t::gist_cursorext_id OpTbl[rt_query_t::rt_numoper];
    OpTbl opTbl;

    rtbase_ext_t(CmpFctTbl tbl, ExpandFctTbl exp, PropFctTbl pf,
	ConvFctTbl cf, BpCmpFctTbl bcf, OpTbl op);

    bool consistent(
        const gist_query_t* query,
	const void *pred,
	int predLen,
	int level) const;

    // Union all the keys on a single page, plus up to two extra keys.
    // If 'bpIsValid', the BP is updated incrementally with pred1/-2.
    void union_bp(
	const gist_predcursor_t& pcursor, // in
	const gist_p& page, // in
	const vec_t& pred1, // in
	const vec_t& pred2, // in
	vec_t& bp, // in/out
	bool& bpChanged, // out
	bool bpIsValid) // in
	const;

    gist_cursorext_t* queryCursor(
	const gist_query_t* query) const;

    bool check(
        const void *bp, 
	int bplen, 
	const void *pred, 
	int predlen, 
	int level) const; 

    // note that several methods remain pure virtual, as in
    // gist_unordered_ext_t, so this is an abstract class as well.
};

/*
 * rt_ext_t
 *
 * the R-tree was originally described in: A. Guttman, "R-trees: A
 * Dynamic Index Structure for Spatial Searching," Proc. 1984
 * ACM-SIGMOD Conf. on Management of Data, Boston, MA, June 1984,
 * 47-57.
 *
 * XXX we should probably call this 'rtspan_ext_t' since it really
 * represents the family of trees that split based on the span
 * (volume) of the new BPs.
 */

class rt_ext_t : public rtbase_ext_t {
public:
    rt_ext_t(CmpFctTbl tbl, ExpandFctTbl exp, PropFctTbl pf,
	ConvFctTbl cf, BpCmpFctTbl bcf, OpTbl op)
	: rtbase_ext_t(tbl, exp, pf, cf, bcf, op) {};

    // A note on union(): rt_ext_t has the standard behavior (from rtbase_ext_t),
    // because R-tree minimum bounding rectangles can always be updated
    // incrementally.  We only need the current BP and the values of
    // the new predicates (i.e., those to be added).  We should use
    // incremental updates whenever we can because the overall cost
    // to insert n predicates is linear rather than quadratic.

    // computes enlargement of subtree pred area
    void penalty(
        const void *subtreePred,
	int predLen,
	int level,
	const void *newKey,
	int keyLen,
	gist_penalty_t &p) const;

    // implements Guttman's "quadratic" split algorithm.
    void pickSplit(
        gist_predcursor_t &pcursor,
	const gist_p& page,
	int rightEntries[] /*out*/,
	int &numRightEntries /*out*/,
	const void *oldBp,
	int oldLen,
	void *leftBp /*out*/,
	int &leftLen /*in/out*/,
	void *rightBp /*out*/,
	int &rightLen /*int/out*/) const;
};

extern gist_unorderedn_ext_t rt_point_ext;
extern gist_unorderedn_ext_t rt_rect_ext;
extern gist_unorderedn_ext_t rr_point_ext;

// these are provided for other extensions based on rt_point/rt_rect
// (e.g., R*-trees).
extern rt_ext_t rect_ext;
extern rt_ext_t point_ext;

#ifdef AMDB
extern amdb_ext_t amdb_rt_point_ext;
extern amdb_ext_t amdb_rt_rect_ext;
extern amdb_ext_t amdb_rr_point_ext;
#endif // AMDB

#endif // GIST_RTREE_H
