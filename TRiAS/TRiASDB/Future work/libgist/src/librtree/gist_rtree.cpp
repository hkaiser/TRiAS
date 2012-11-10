// gist_rtree.cc						-*- c++ -*-
// Copyright (c) 1997, 1998 Regents of the University of California
// $Id: gist_rtree.cc,v 1.30 2000/03/15 00:24:51 mashah Exp $

#ifdef __GNUG__
#pragma implementation "gist_rtree.h"
#endif

#include <math.h>			// for fabs()

#include "gist_rtpred_point.h"
#include "gist_rtpred_rect.h"
#include "gist_rtree.h"
#include "gist_rtreecext.h"
#include "gist_support.h" // for print<>, parse<>, etc.

///////////////////////////////////////////////////////////////////////////////
// rt_query_t methods
///////////////////////////////////////////////////////////////////////////////

rt_query_t::~rt_query_t() 
{
    if (value != NULL) {
	if (argType == rt_pointarg) {
	    rt_point *pt =  (rt_point *) value;
	    delete pt;
	} else {
	    rt_rect *rect =  (rt_rect *) value;
	    delete rect;
	}
    }
}

///////////////////////////////////////////////////////////////////////////////
// static helper methods
///////////////////////////////////////////////////////////////////////////////

static bool
rect_equal_pt(const void *c1, int l, const rt_pred& p2)
{
    rt_rect r1(rt_rect::size2dim(l), (const double *) c1);
    return (((const rt_point&) p2).contains(r1));
}

static bool
rect_equal_rect(const void *c1, int l, const rt_pred& r2)
{
    rt_rect r1(rt_rect::size2dim(l), (const double *) c1);
    return (r1.isEqual((const rt_rect&) r2));
}

static double
pt_span(const rt_pred& pred)
{
    return(((const rt_point&) pred).span());
}

static double
rect_span(const rt_pred& pred)
{
    return(((const rt_rect&) pred).span());
}

static double
pt_margin(const rt_pred& pred)
{
    return(((const rt_point&) pred).margin());
}

static double
rect_margin(const rt_pred& pred)
{
    return(((const rt_rect&) pred).margin());
}

static rt_pred*
rect_pt_expand(rt_pred* pred, const void* item, int itemLen, bool preserve)
{
    assert(pred == NULL || pred->dim() == rt_point::size2dim(itemLen));
    rt_point p(rt_point::size2dim(itemLen), (const double *) item);
    return(pred ? ((rt_rect*) pred)->expand(p, preserve) : new rt_rect(p));
}

static rt_pred*
rect_rect_expand(rt_pred* pred, const void* item, int itemLen, bool preserve)
{
    assert(pred == NULL || pred->dim() == rt_rect::size2dim(itemLen));
    rt_rect r(rt_rect::size2dim(itemLen), (const double *) item);
    return(pred ? ((rt_rect*) pred)->expand(r, preserve) : new rt_rect(r));
}


// VCPORT_B
const float rtbase_ext_t::MINSPLITUTIL = 0.5;
// VCPORT_E

///////////////////////////////////////////////////////////////////////////////
// rt_ext_t function tables
///////////////////////////////////////////////////////////////////////////////

rtbase_ext_t::CmpFctTbl pointCmpTbl = {
    // nooper, equal, overlap, contains, contained, nearest, count_overlap
    {								// leaf
	{ &rt_pred::alwaysTrue,	// point key, point query
	  &rt_point::contains_point,
	  &rt_point::contains_point,
	  &rt_point::contains_point,
	  &rt_point::contains_point,
	  &rt_pred::alwaysTrue,
	  &rt_point::contains_point,
	  &rt_point::contains_point,
	  &rt_point::contains_point,
	},
	{ &rt_pred::alwaysTrue,	// point key, rect query
	  &rt_point::contains_rect,
	  &rt_point::contained_rect,
	  &rt_point::contains_rect,
	  &rt_point::contained_rect,
	  &rt_pred::alwaysTrue,
	  &rt_point::contained_rect,
	  &rt_point::contained_rect,
	  &rt_point::contained_rect,
	}
    },
    {								// internal
	{ &rt_pred::alwaysTrue, // rect key, point query
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	  &rt_pred::alwaysTrue,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	},
	{ &rt_pred::alwaysTrue,	// rect key, rect query
	  &rt_rect::contains_rect,
	  &rt_rect::overlaps_rect,
	  &rt_rect::contains_rect,
	  &rt_rect::overlaps_rect,
	  &rt_pred::alwaysTrue,
	  &rt_rect::overlaps_rect,
	  &rt_rect::overlaps_rect,
	  &rt_rect::overlaps_rect,
	}
    }
};
rtbase_ext_t::ExpandFctTbl pointExpandTbl = {
    &rect_pt_expand,						// leaf
    &rect_rect_expand						// internal
};
rtbase_ext_t::PropFctTbl pointPropTbl = {
    { &pt_span, &pt_margin },					// leaf
    { &rect_span, &rect_margin }				// internal
};
rtbase_ext_t::BpCmpFctTbl pointBpCmpTbl = {
    &rect_equal_rect,
    &rt_rect::contains_point,					// leaf
    &rt_rect::contains_rect					// internal
};
rtbase_ext_t::ConvFctTbl pointConvTbl = {
    { &rt_point::size2dim, &rt_point::dim2size },		// leaf
    { &rt_rect::size2dim, &rt_rect::dim2size }			// internal
};
rtbase_ext_t::OpTbl pointOpTbl = {
    gist_cursorext_t::cext_stack_id,		// nooper
    gist_cursorext_t::cext_stack_id,		// equal
    gist_cursorext_t::cext_stack_id,		// overlap
    gist_cursorext_t::cext_stack_id,		// contains
    gist_cursorext_t::cext_stack_id,		// contained
    gist_cursorext_t::cext_rt_point_nn_id,	// nearest
    gist_cursorext_t::cext_stack_id,		// count_overlap
    gist_cursorext_t::cext_stack_id,		// count_sample
    gist_cursorext_t::cext_stack_id,		// count_combo
};

rt_ext_t point_ext(pointCmpTbl, pointExpandTbl,
    pointPropTbl, pointConvTbl, pointBpCmpTbl, pointOpTbl);
gist_unorderedn_ext_t rt_point_ext(gist_ext_t::rt_point_ext_id,
    "rt_point_ext", gist_support::printPtRtPred, gist_support::printInt,
    gist_support::parsePoint, gist_support::parseInt, gist_support::parseGeoQuery,
    point_ext);

rtbase_ext_t::CmpFctTbl rectCmpTbl = {
    // nooper, equal, overlap, contains, contained, nearest, count_overlap
    {								// leaf
	{ &rt_pred::alwaysTrue,	// rect key, point query
	  &rect_equal_pt,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	  &rect_equal_pt,
	  &rt_pred::alwaysTrue,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	},
	{ &rt_pred::alwaysTrue,	// rect key, rect query
	  &rect_equal_rect,
	  &rt_rect::overlaps_rect,
	  &rt_rect::contains_rect,
	  &rt_rect::contained_rect,
	  &rt_pred::alwaysTrue,
	  &rt_rect::overlaps_rect,
	  &rt_rect::overlaps_rect,
	  &rt_rect::overlaps_rect,
	}
    },
    {								// internal
	{ &rt_pred::alwaysTrue,	// rect key, point query
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	  &rt_pred::alwaysTrue,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	  &rt_rect::contains_point,
	},
	{ &rt_pred::alwaysTrue,	// rect key, rect query
	  &rt_rect::contains_rect,
	  &rt_rect::overlaps_rect,
	  &rt_rect::contains_rect,
	  &rt_rect::overlaps_rect,
	  &rt_pred::alwaysTrue,
	  &rt_rect::overlaps_rect,
	  &rt_rect::overlaps_rect,
	  &rt_rect::overlaps_rect,
	}
    }
};
rtbase_ext_t::ExpandFctTbl rectExpandTbl = {
    &rect_rect_expand,						// leaf
    &rect_rect_expand						// internal
};
rtbase_ext_t::PropFctTbl rectPropTbl = {
    { &rect_span, &rect_margin },				// leaf
    { &rect_span, &rect_margin }				// internal
};
rtbase_ext_t::ConvFctTbl rectConvTbl = {
    { &rt_rect::size2dim, &rt_rect::dim2size },			// leaf
    { &rt_rect::size2dim, &rt_rect::dim2size }			// internal
};
rtbase_ext_t::BpCmpFctTbl rectBpCmpTbl = {
    &rect_equal_rect,
    &rt_rect::contains_rect,					// leaf
    &rt_rect::contains_rect					// internal
};
rtbase_ext_t::OpTbl rectOpTbl = {
    gist_cursorext_t::cext_stack_id,		// nooper
    gist_cursorext_t::cext_stack_id,		// equal
    gist_cursorext_t::cext_stack_id,		// overlap
    gist_cursorext_t::cext_stack_id,		// contains
    gist_cursorext_t::cext_stack_id,		// contained
    gist_cursorext_t::cext_rt_rect_nn_id,	// nearest
    gist_cursorext_t::cext_stack_id,		// count_overlap
    gist_cursorext_t::cext_stack_id,		// count_sample
    gist_cursorext_t::cext_stack_id,		// count_combo
};

rt_ext_t rect_ext(rectCmpTbl, rectExpandTbl, 
    rectPropTbl, rectConvTbl, rectBpCmpTbl, rectOpTbl);
gist_unorderedn_ext_t rt_rect_ext(gist_ext_t::rt_rect_ext_id,
    "rt_rect_ext", gist_support::printRectRtPred, gist_support::printInt,
    gist_support::parseRect, gist_support::parseInt, gist_support::parseGeoQuery,
    rect_ext);

rtbase_nn_cursorext_t::RtPrioFctTbl rtPointNnPrioTbl = {
    { &rt_point::dist_point, NULL },				// leaf
    { &rt_rect::dist_point, NULL }				// internal
};
rtbase_nn_cursorext_t::RtPrioFctTbl rtRectNnPrioTbl = {
    { &rt_rect::dist_point, NULL },				// leaf
    { &rt_rect::dist_point, NULL }				// internal
};

rtbase_nn_cursorext_t rt_point_nn_cext(
    gist_cursorext_t::cext_rt_point_nn_id, rtPointNnPrioTbl);
rtbase_nn_cursorext_t rt_rect_nn_cext(
    gist_cursorext_t::cext_rt_rect_nn_id, rtRectNnPrioTbl);

///////////////////////////////////////////////////////////////////////////////
// rtbase_ext_t methods
///////////////////////////////////////////////////////////////////////////////

rtbase_ext_t::rtbase_ext_t(
    CmpFctTbl tbl,
    ExpandFctTbl exp,
    PropFctTbl pf,
    ConvFctTbl cf,
    BpCmpFctTbl bcf,
    OpTbl op)
{
    int i, j, k;

    // copy function tables
    for (i = 0; i < numLvl; i++) {
        for (j = 0; j < rt_query_t::rt_numarg; j++) {
	    for (k = 0; k < rt_query_t::rt_numoper; k++) {
	        cmpFcts[i][j][k] = tbl ? tbl[i][j][k] : NULL;
	    }
	}
	for (j = 0; j < rt_numprop; ++j) {
	    propFcts[i][j] = pf ? pf[i][j] : NULL;
	}
	for (j = 0; j < rt_numconv; ++j) {
	    convFcts[i][j] = cf ? cf[i][j] : NULL;
	}
	expandFcts[i] = exp ? exp[i] : NULL;
    }
    for (i = 0; i < rt_bpnumcmp; ++i) {
	bpCmpFcts[i] = bcf? bcf[i] : NULL;
    }
    for (i = 0; i < rt_query_t::rt_numoper; ++i) {
	opTbl[i] = op ? op[i] : gist_cursorext_t::cext_stack_id;
    }
}

bool
rtbase_ext_t::consistent(
    const gist_query_t* query,
    const void *pred,
    int predLen,
    int level) const
{
    rt_query_t *q = (rt_query_t *) query;
    rt_pred* sarg = (rt_pred*) q->value;

    return (cmpFcts[level > 1][q->argType][q->oper](pred, predLen, *sarg));
}


/////////////////////////////////////////////////////////////////////////
// rtbase_ext_t::union_bp - generate BR for collection of predicates
//
// Description:
//	- if !bpIsValid, create one from scratch by unioning the predicates
//	  on the page
//	- if either pred1 or pred2 is passed in, union them to the BP 
//	  incrementally
//
/////////////////////////////////////////////////////////////////////////

void
rtbase_ext_t::union_bp(
    const gist_predcursor_t& pcursor, // in
    const gist_p& page, // in
    const vec_t& pred1, // in
    const vec_t& pred2, // in
    vec_t& bp, // in/out
    bool& bpChanged, // out
    bool bpIsValid) // in
    const
{
    int level = page.level();
    void* bpPtr = bp.ptr(0);
    int bpLen = bp.len(0);

    rt_pred* newBp = NULL; // the first 'expand' will create a predicate
    int d; // dimension of predicates
    if (!bpIsValid) {
	// need to build a BP for the predicates on the page from scratch
	assert(pcursor.numElems > 0);
	d = convFcts[level > 1][rt_dim](pcursor.elems[0].keyLen);
	bpLen = convFcts[1][rt_size](d); // size of BP
	bp.set(bpPtr, bpLen);
	bpChanged = true; // we're generating a new one

	for (int i = 0; i < pcursor.numElems; i++) {
	    newBp = expandFcts[level > 1](newBp, pcursor.elems[i].key,
		pcursor.elems[i].keyLen, true);
	}
    } else {
	// if a BP is given, we know it's an internal node predicate (level > 1 == true)
	d = convFcts[true][rt_dim](bpLen);
	bpChanged = false;
	newBp = expandFcts[1](NULL, bpPtr, bpLen, false); // copy existing BP
    }

    // add the extra predicates to the BP
    if (pred1.len(0) != 0) {
	newBp = expandFcts[level > 1](newBp, pred1.ptr(0), pred1.len(0), true);
    }
    if (pred2.len(0) != 0) {
	newBp = expandFcts[level > 1](newBp, pred2.ptr(0), pred2.len(0), true);
    }

    // flag whether or not we need to change the stored BP
    if (bpIsValid) {
	bpChanged = bpChanged || !bpCmpFcts[rt_bpequal](bpPtr, bpLen, *newBp);
    }

    if (bpChanged) {
	(void) memcpy(bpPtr, newBp->coords(), bpLen);
    }
    delete newBp;
}


gist_cursorext_t*
rtbase_ext_t::queryCursor(
    const gist_query_t* query) const
{
    rt_query_t* q = (rt_query_t*) query;
    rt_query_t::rt_oper op = q->oper;
    assert(op >= 0 && op < rt_query_t::rt_numoper);
    gist_cursorext_t::gist_cursorext_id id = opTbl[op];
    assert(id >= 0 && id < gist_cursorext_t::cext_numext);
    return(gist_cursorext_t::gist_cursorext_list[id]);
}

bool
rtbase_ext_t::check(
    const void *bp, 
    int bplen, 
    const void *pred, 
    int predlen, 
    int level) const
{
    rt_pred* p = expandFcts[level > 1](NULL, pred, predlen, false);
    bool res = bpCmpFcts[rt_bpint](bp, bplen, *p);
    if (!res) {
	int x = 1;			// gdb watch/break line
    }
    assert(convFcts[level > 1][rt_dim](predlen) == convFcts[1][rt_dim](bplen));
    delete p;
    return res;
}


///////////////////////////////////////////////////////////////////////////////
// rt_ext_t methods
///////////////////////////////////////////////////////////////////////////////

void
rt_ext_t::penalty(
    const void *subtreePred,
    int predLen,
    int level,
    const void *newKey,
    int keyLen,
    gist_penalty_t &p) const
{
    rt_pred* newBp = expandFcts[1](NULL, subtreePred, predLen, false);
    double oldSpan = propFcts[1][rt_span](*newBp);
    (void) expandFcts[0](newBp, newKey, keyLen, true);
    double newSpan = propFcts[1][rt_span](*newBp);
    p.p = (newSpan > oldSpan) ? (newSpan - oldSpan) : 0.0;
    delete newBp;
}

void
rt_ext_t::pickSplit(
    gist_predcursor_t &pcursor,
    const gist_p& page,
    int rightEntries[] /*out*/,
    int &numRight /*out*/,
    const void *oldBp,
    int oldLen,
    void *leftBp /*out*/,
    int &leftLen /*in/out*/,
    void *rightBp /*out*/,
    int &rightLen /*in/out*/) const
{
    // Guttman's original quadratic split algorithm works as follows:
    // - pick two seed entries by (quadratically) finding the pair A,B
    //   with the lowest 'waste' factor:
    //		waste(A,B) = area(union(A,B)) - area(A) - area(B)
    // - assign the remaining entries to one of the two clusters, X,Y,
    //   based on their 'enlargement' factor:
    //		enlarge(X,A) = area(union(X,A)) - area(X)
    //   - find some item A with max{|enlarge(X,A) - enlarge(Y,A)|}
    //   - assign A to X,Y based on min{enlarge(X,A),enlarge(Y,A)}
    //     (using min{area(X),area(Y)} and min{|X|,|Y|}, respectively, 
    //     to break ties; these are the same assignment criteria as for
    //     the linear split algorithm)
    //   this step is also quadratic since both the inner and outer
    //   loops are linear.

    // in order to use this pickSplit(), the bp type must support a
    // way to compute its span (i.e., volume).

    int level = page.level();
    int itemCnt = pcursor.numElems;	// # of items on the page
    if (itemCnt < 2) {			// we can't split with fewer entries!
	// XXX nicer error-handling goes here.
	assert(0);
    }

    int i, j;

    // find the item pair that cause the most waste.
    double maxWaste = -1.0;
    int leftSeed = -1, rightSeed = -1;
    double* spans = new double[itemCnt];
    rt_pred* tmpBp = NULL;
    for (i = 0; i < itemCnt; ++i) {
	assert(pcursor.elems[0].keyLen == pcursor.elems[i].keyLen);
	tmpBp = expandFcts[level > 1](tmpBp, pcursor.elems[i].key,
	    pcursor.elems[i].keyLen, false);
	spans[i] = propFcts[1][rt_span](*tmpBp);
    }
    for (i = 0; i < itemCnt; ++i) {
	const void* k1 = pcursor.elems[i].key;
	int k1len = pcursor.elems[i].keyLen;
	for (j = i + 1; j < itemCnt; ++j) { // XXX assumes union is symmetric
	    tmpBp = expandFcts[level > 1](tmpBp, k1, k1len, false);

	    const void* k2 = pcursor.elems[j].key;
	    int k2len = pcursor.elems[j].keyLen;

	    (void) expandFcts[level > 1](tmpBp, k2, k2len, true);
	    double bpspan = propFcts[1][rt_span](*tmpBp);
	    if (bpspan - (spans[i] + spans[j]) >= maxWaste) {
		leftSeed = i;
		rightSeed = j;
		maxWaste = bpspan - (spans[i] + spans[j]);
	    }
	}
    }
    delete tmpBp;
    delete [] spans;
    // at this point, leftSeed and rightSeed must be valid because we
    // must have at least one pair and therefore must have a maximally
    // wasteful pair.

    // initialize the left and right clusters using the new seeds.
    // leftPred and rightPred are actually instances of the
    // appropriate bp class.
    rt_pred* leftPred = (rt_pred*)
	expandFcts[level > 1](NULL, pcursor.elems[leftSeed].key,
	    pcursor.elems[leftSeed].keyLen, false);
    rt_pred* rightPred = (rt_pred*)
	expandFcts[level > 1](NULL, pcursor.elems[rightSeed].key,
	    pcursor.elems[rightSeed].keyLen, false);
    int d = convFcts[level > 1][rt_dim](pcursor.elems[leftSeed].keyLen);
    leftLen = rightLen = convFcts[1][rt_size](d);
    int numLeft = numRight = 1;
    rightEntries[0] = rightSeed;
    int remaining = itemCnt - 2;

    if (remaining > 0) {
	// 'which' tracks the items that have not yet been assigned to
	// any cluster.  we assume that the order in which the items
	// on a page are processed does not matter (which may not be
	// reasonable for all trees).
	int* which = new int[remaining];
	for (i = 0, j = 0; i < itemCnt; ++i) {
	    if (i != leftSeed && i != rightSeed) {
		which[j++] = i;
	    }
	}

	int threshold = (int) (MINSPLITUTIL * itemCnt);
	rt_pred* tmpPred = NULL;
	while (remaining > 0) {
	    // if one of the clusters is now guaranteed to fall under
	    // the minimum utilization, we just assign the remaining
	    // entries to that cluster and quit.
	    rt_pred* fixup = NULL;
	    if (numLeft + remaining < threshold) {
		numLeft += remaining;
		fixup = leftPred;
	    } else if (numRight + remaining < threshold) {
		fixup = rightPred;
	    }
	    if (fixup) {
		for (i = 0; i < remaining; ++i) {
		    (void) expandFcts[level > 1](fixup,
			pcursor.elems[which[i]].key,
			pcursor.elems[which[i]].keyLen, true);
		    if (fixup == rightPred) {
			rightEntries[numRight] = which[i];
			++numRight;
		    }
		}
		remaining = 0;
		continue; // break while
	    }

	    // otherwise, choose the next item for assignment using
	    // the enlargement factor.
	    double leftSpan = propFcts[1][rt_span](*leftPred);
	    double rightSpan = propFcts[1][rt_span](*rightPred);
	    double maxDiff = -1.0;
	    double leftEnlarge = -1.0, rightEnlarge = -1.0;
	    int chosen = -1;
	    for (i = 0; i < remaining; ++i) {
		const void* k = pcursor.elems[which[i]].key;
		int klen = pcursor.elems[which[i]].keyLen;

		tmpPred = expandFcts[1](tmpPred, leftPred->coords(), leftLen,
		    false);
		(void) expandFcts[level > 1](tmpPred, k, klen, true);
		double newLeft = propFcts[1][rt_span](*tmpPred) - leftSpan;

		tmpPred = expandFcts[1](tmpPred, rightPred->coords(), rightLen,
		    false);
		(void) expandFcts[level > 1](tmpPred, k, klen, true);
		double newRight = propFcts[1][rt_span](*tmpPred) - rightSpan;

		double newDiff = fabs(newLeft - newRight);
		if (newDiff > maxDiff) {
		    chosen = i;
		    maxDiff = newDiff;
		    leftEnlarge = newLeft;
		    rightEnlarge = newRight;
		}
	    }
	    assert(chosen >= 0 && chosen < remaining);

	    // now, choose the target cluster for this item.
	    bool pickLeft = true;
	    if (leftEnlarge != rightEnlarge) {
		pickLeft = (leftEnlarge < rightEnlarge);
	    } else if (leftSpan != rightSpan) {
		pickLeft = (leftSpan < rightSpan);
	    } else if (numLeft != numRight) {
		pickLeft = (numLeft < numRight);
	    }
	    rt_pred* pickPred;
	    if (pickLeft) {
		pickPred = leftPred;
		++numLeft;
	    } else {
		pickPred = rightPred;
		rightEntries[numRight] = which[chosen];
		++numRight;
	    }
	    (void) expandFcts[level > 1](pickPred,
		pcursor.elems[which[chosen]].key,
		pcursor.elems[which[chosen]].keyLen, true);

	    // now, fix up 'which' so that only unchosen items remain
	    // in the valid portion of the array.
	    which[chosen] = which[remaining - 1];
	    --remaining;
	}
	delete tmpPred;
	delete [] which;
    }

    // finally, just save 'leftPred' and 'rightPred' into 'leftBp' and
    // 'rightBp' and we're done.
    (void) memcpy(leftBp, leftPred->coords(), leftLen);
    (void) memcpy(rightBp, rightPred->coords(), rightLen);
    delete leftPred;
    delete rightPred;

    assert(numLeft + numRight == itemCnt);
}
