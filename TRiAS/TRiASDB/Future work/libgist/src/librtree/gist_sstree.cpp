// gist_sstree.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_sstree.cc,v 1.6 1999/06/16 03:07:42 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_sstree.h"
#endif

#include "gist_compat.h"		// for MAXDOUBLE
#include "gist_defs.h"			// for assert()
#include "gist_rtpred_rect.h"		// for rt_rect
#include "gist_rtpred_ss.h"
#include "gist_sstree.h"
#include "gist_ball.h"			// for EnclosingBall()
#include "gist_rtreecext.h"
#include "gist_support.h" // for print<>, parse<>, etc.

///////////////////////////////////////////////////////////////////////////////
// static helper methods
///////////////////////////////////////////////////////////////////////////////

static double
ss_pt_dist(const void *item, int itemLen, const rt_pred& query)
{
    rt_centroid_sphere s(rt_centroid_sphere::size2dim(itemLen),
	(double *) item);
    return(s.dist((rt_point&) query));
}

static bool
ss_equal_ss(const void *c1, int l, const rt_pred& s2)
{
    rt_centroid_sphere s1(rt_centroid_sphere::size2dim(l), (const double *) c1);
    return (s1.isEqual((const rt_centroid_sphere&) s2));
}

static bool
ss_contains_pt(const void *c1, int l, const rt_pred& p2)
{
    rt_centroid_sphere s1(rt_centroid_sphere::size2dim(l), (const double *) c1);
    return (s1.contains((const rt_point&) p2));
}

static bool
ss_contains_rect(const void *c1, int l, const rt_pred& r2)
{
    rt_centroid_sphere s1(rt_centroid_sphere::size2dim(l), (const double *) c1);
    return (s1.contains((const rt_rect&) r2));
}

static bool
ss_contains_ss(const void *c1, int l, const rt_pred& s2)
{
    rt_centroid_sphere s1(rt_centroid_sphere::size2dim(l), (const double *) c1);
    return (s1.contains((const rt_centroid_sphere&) s2));
}

static bool
ss_overlaps_rect(const void *c1, int l, const rt_pred& r2)
{
    rt_centroid_sphere s1(rt_centroid_sphere::size2dim(l), (const double *) c1);
    return (s1.overlaps((const rt_rect&) r2));
}

static double
pt_span(const rt_pred& pred)
{
    return(((const rt_point&) pred).span());
}

static double
ss_span(const rt_pred& pred)
{
    return(((const rt_centroid_sphere&) pred).span());
}

static double
pt_margin(const rt_pred& pred)
{
    return(((const rt_point&) pred).margin());
}

static rt_pred*
pt_center(rt_pred* pred, const void* item, int itemLen)
{
    int d = rt_point::size2dim(itemLen);
    assert(pred == NULL || pred->dim() == d);
    double *c = (double*) item;					// XXX center
    if (pred == NULL) {
	return(new rt_point(d, c));
    }
    pred->set(c);
    return(pred);
}

static rt_pred*
ss_center(rt_pred* pred, const void* item, int itemLen)
{
    int d = rt_centroid_sphere::size2dim(itemLen);
    assert(pred == NULL || pred->dim() == d);
    double *c = (double*) item;					// XXX center
    if (pred == NULL) {
	return(new rt_point(d, c));
    }
    pred->set(c);
    return(pred);
}

static rt_pred*
ss_pt_expand(rt_pred* pred, const void *item, int itemLen, bool preserve)
{
    assert(pred == NULL || pred->dim() == rt_point::size2dim(itemLen));
    rt_point p(rt_point::size2dim(itemLen), (const double *) item);
    return(pred ? ((rt_centroid_sphere*) pred)->expand(p, preserve)
	: new rt_centroid_sphere(p));
}

static rt_pred*
ss_ss_expand(rt_pred* pred, const void *item, int itemLen, bool preserve)
{
    assert(pred == NULL || pred->dim() == rt_centroid_sphere::size2dim(itemLen));
    rt_centroid_sphere s(rt_centroid_sphere::size2dim(itemLen),
	(const double *) item);
    return(pred ? ((rt_centroid_sphere*) pred)->expand(s, preserve)
	: new rt_centroid_sphere(s));
}

///////////////////////////////////////////////////////////////////////////////
// ss_ext_t function tables
///////////////////////////////////////////////////////////////////////////////

rtbase_ext_t::CmpFctTbl ssPointCmpTbl = {
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
	{ &rt_pred::alwaysTrue,	// sphere key, point query
	  &ss_contains_pt,
	  &ss_contains_pt,
	  &ss_contains_pt,
	  &ss_contains_pt,
	  &rt_pred::alwaysTrue,
	  &ss_contains_pt,
	  &ss_contains_pt,
	  &ss_contains_pt,
	},
	{ &rt_pred::alwaysTrue,	// sphere key, rect query
	  &ss_contains_rect,
	  &ss_overlaps_rect,
	  &ss_contains_rect,
	  &ss_overlaps_rect,
	  &rt_pred::alwaysTrue,
	  &ss_overlaps_rect,
	  &ss_overlaps_rect,
	  &ss_overlaps_rect,
	}
    }
};
rtbase_ext_t::ExpandFctTbl ssPointExpandTbl = {
    &ss_pt_expand,						// leaf
    &ss_ss_expand						// internal
};
rtbase_ext_t::PropFctTbl ssPointPropTbl = {
    { &pt_span, NULL },						// leaf
    { &ss_span, NULL }						// internal
};
rtbase_ext_t::BpCmpFctTbl ssPointBpCmpTbl = {
    &ss_equal_ss,
    &ss_contains_pt,						// leaf
    &ss_contains_ss						// internal
};
rtbase_ext_t::ConvFctTbl ssPointConvTbl = {
    { &rt_point::size2dim, &rt_point::dim2size },		// leaf
    { &rt_centroid_sphere::size2dim, &rt_centroid_sphere::dim2size } // internal
};
ss_ext_t::CenterFctTbl ssPointCenterTbl = {
    &pt_center,
    &ss_center
};
rtbase_ext_t::OpTbl ssPointOpTbl = {
    gist_cursorext_t::cext_stack_id,		// nooper
    gist_cursorext_t::cext_stack_id,		// equal
    gist_cursorext_t::cext_stack_id,		// overlap
    gist_cursorext_t::cext_stack_id,		// contains
    gist_cursorext_t::cext_stack_id,		// contained
    gist_cursorext_t::cext_ss_point_nn_id,	// nearest
    gist_cursorext_t::cext_stack_id,		// count_overlap
    gist_cursorext_t::cext_stack_id,		// count_sample
    gist_cursorext_t::cext_stack_id,		// count_combo
};

ss_ext_t sspoint_ext(ssPointCmpTbl, ssPointExpandTbl,
    ssPointPropTbl, ssPointConvTbl, ssPointBpCmpTbl,
    ssPointOpTbl, ssPointCenterTbl);
gist_unorderedn_ext_t ss_point_ext(gist_ext_t::ss_point_ext_id,
    "ss_point_ext", gist_support::printSsPred, gist_support::printInt,
    gist_support::parsePoint, gist_support::parseInt, gist_support::parseGeoQuery,
    sspoint_ext);

rtbase_nn_cursorext_t::RtPrioFctTbl ssPointNnPrioTbl = {
    { &rt_point::dist_point, NULL },				// leaf
    { &ss_pt_dist, NULL }					// internal
};

rtbase_nn_cursorext_t ss_point_nn_cext(
    gist_cursorext_t::cext_ss_point_nn_id, ssPointNnPrioTbl);

///////////////////////////////////////////////////////////////////////////////
// ss_ext_t methods
///////////////////////////////////////////////////////////////////////////////

ss_ext_t::ss_ext_t(
    CmpFctTbl tbl,
    ExpandFctTbl exp,
    PropFctTbl pf,
    ConvFctTbl cf,
    BpCmpFctTbl bcf,
    OpTbl op,
    CenterFctTbl cenf)
    : rtbase_ext_t(tbl, exp, pf, cf, bcf, op)
{
    for (int i = 0; i < numLvl; ++i) {
	centerFcts[i] = cenf ? cenf[i] : NULL;
    }
}

void
ss_ext_t::penalty(
    const void *subtreePred,
    int predLen,
    int level,
    const void *newKey,
    int keyLen,
    gist_penalty_t &p) const
{
    int d = rt_point::size2dim(keyLen);
    rt_centroid_sphere s(d, (double*) subtreePred);
    rt_point pt(d, (double*) newKey);
    p.p = s.center.dist(pt);
}


/////////////////////////////////////////////////////////////////////////
// ss_ext_t::union_bp - generate bounding sphere for collection of predicates
//
// Description:
// 	- SS-tree weighted centroid spheres can be incrementally
//        updated because they need not be minimal.  however, the BPs
//        resulting from a split are computed using the minimal
//        bounding sphere.  this kind of behavior is only possible when
//        the definition of the BP type is such that more than one
//        adequately accurate BP is possible for a given set of
//        predicates.  although some BP accuracy is lost, we incur
//        constant insertion cost most of the time and quadratic cost
//        1/n of the time.
//	- if !bpIsValid, generates bounding sphere from scratch for 
//	  the page predicates plus pred1/-2
//	- if bpIsValid, adds in pred1/-2 incrementally
//
// Preconditions:
// Postconditions:
// Notes:
/////////////////////////////////////////////////////////////////////////

void
ss_ext_t::union_bp(
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

    int d; // dimension of predicates
    if (!bpIsValid) {
	d = convFcts[level > 1][rt_dim](pcursor.elems[0].keyLen);
	bpLen = convFcts[1][rt_size](d); // size of BP
	bp.set(bpPtr, bpLen);
	bpChanged = true; // we're generating a new one
    } else {
	// if a BP is given, we know it's an internal node predicate
	// (i.e., level > 1 == true)
	d = convFcts[1][rt_dim](bpLen);
	bpChanged = false;
    }

    rt_pred* newBp = NULL;
    if (!bpIsValid) {
	// create the new BP from scratch, also taking the extra
	// predicates into account (unlike rtbase_ext_t, which adds them
	// in incrementally)
	int howmany = pcursor.numElems;
	if (pred1.size() != 0) {
	    howmany += 1;
	}
	if (pred2.size() != 0) {
	    howmany += 1;
	}
	double** inCenter = new double*[howmany];
	double* inCenters = new double[d * howmany];
	double* inRadii = (double*) new double[howmany];
	rt_centroid_sphere* sBp = NULL;
	double nrec = 0;

	for (int i = 0; i < howmany; ++i) {
	    // assign pred. to newBp ('preserve' param is false)
	    if (i < pcursor.numElems) {
		newBp = expandFcts[level > 1](newBp, pcursor.elems[i].key,
		    pcursor.elems[i].keyLen, false);
	    } else if (i == pcursor.numElems) {
		newBp = expandFcts[level > 1](newBp, pred1.ptr(0), pred1.len(0), false);
	    } else {
		newBp = expandFcts[level > 1](newBp, pred2.ptr(0), pred2.len(0), false);
	    }
	    sBp = (rt_centroid_sphere*) newBp;

	    inCenter[i] = inCenters + i * d;
	    for (int j = 0; j < d; ++j) {
		inCenter[i][j] = sBp->center.co(j);
	    }
	    inRadii[i] = sBp->radius();
	    nrec += sBp->rank.nrec();
	}

	assert(sBp != NULL);
	EnclosingBall(d, howmany,
	    inCenter, (level > 1) ? inRadii : (double*) NULL,
	    sBp->center.coords(), sBp->radius());
	sBp->rank.nrec() = nrec;
	delete [] inCenter;
	delete [] inCenters;
	delete [] inRadii;
    } else {
        // add in pred1/-2 incrementally 
	newBp = expandFcts[1](NULL, bpPtr, bpLen, false); // make copy of existing BP
	if (pred1.len(0) != 0) {
	    newBp = expandFcts[level > 1](newBp, pred1.ptr(0), pred1.len(0), true);
	}
	if (pred2.len(0) != 0) {
	    newBp = expandFcts[level > 1](newBp, pred2.ptr(0), pred2.len(0), true);
	}
    }

    // flag whether or not we need to change the stored BP
    if (bpIsValid) {
	bpChanged = !bpCmpFcts[rt_bpequal](bpPtr, bpLen, *newBp);
    }

    if (bpChanged) {
	(void) memcpy(bpPtr, newBp->coords(), bpLen);
    }
    delete newBp;
}


typedef struct {
    double coord;
    int itemNo;
} ssSort;

static int 
ssSortCmp(const void* a, const void* b)
{
    ssSort* l = (ssSort*) a;
    ssSort* r = (ssSort*) b;
    return((l->coord < r->coord) ? -1 : ((l->coord > r->coord) ? 1 : 0));
}

// returns the variance of 'coords'
static double
ssVariance(const double* coords, const int n)
{
    double mean = 0.0;
    int i;
    for (i = 0; i < n; ++i) {
	mean += coords[i];
    }
    mean /= (double) n;
    double sum = 0.0;
    for (i = 0; i < n; ++i) {
	double diff = coords[i] - mean;
	sum += diff * diff;
    }
    return(sum / (double) n);
}

void
ss_ext_t::pickSplit(
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
    int level = page.level();
    int itemCnt = pcursor.numElems;	// # of items on the page
    if (itemCnt < 2) {			// we can't split with fewer entries!
	// XXX nicer error-handling goes here.
	assert(0);
    }

    int nDims = convFcts[level > 1][rt_dim](pcursor.elems[0].keyLen);
    leftLen = rightLen = convFcts[1][rt_size](nDims);

    int i, j;

    // copy all of the necessary coordinates out of the BPs (we need
    // dimension vectors to pass into ssVariance).
    rt_point* tmpPt = NULL;
    double* vals = new double[nDims * itemCnt];
    for (i = 0; i < itemCnt; ++i) {
	tmpPt = (rt_point*) centerFcts[level > 1](tmpPt, pcursor.elems[i].key,
	    pcursor.elems[i].keyLen);
	for (j = 0; j < nDims; ++j) {
	    vals[j * itemCnt + i] = tmpPt->co(j);
	}
    }
    delete tmpPt;

    // determine the axis with the highest variance; we will use this
    // as the split axis.
    int split = -1;
    double maxVar = -1.0;
    for (j = 0; j < nDims; ++j) {
	double var = ssVariance(&(vals[j * itemCnt]), itemCnt);
	if (var > maxVar) {
	    maxVar = var;
	    split = j;
	}
    }

    // sort the points by their split axis coordinates.
    ssSort* which = new ssSort[itemCnt];
    for (i = 0; i < itemCnt; ++i) {
	which[i].itemNo = i;
	which[i].coord = vals[split * itemCnt + i];
    }
    qsort(which, itemCnt, sizeof(ssSort), ssSortCmp);
    delete [] vals;

    // now, find the split position that minimizes the total variance
    // of both clusters.  the minimum acceptable space utilization
    // usually restricts the positions that can be chosen.  'spos' is
    // the array index of the rightmost item that must be in the left
    // cluster and 'epos' is the array index of the leftmost item that
    // must be in the right cluster.  (this code assumes that each
    // cluster must contain at least one item.)
    double* axis = new double[itemCnt];
    for (i = 0; i < itemCnt; ++i) {
	axis[i] = which[i].coord;
    }
    int sPos = (int) (MINSPLITUTIL * itemCnt), ePos = itemCnt - (sPos + 1);
    int best = -1;
    double minVarSum = MAXDOUBLE;
    for (i = sPos; i < ePos; ++i) {
	double lVar = ssVariance(axis, i + 1);
	double rVar = ssVariance(axis + (i + 1), itemCnt - (i + 1));
	double varSum = lVar + rVar;
	if (varSum < minVarSum) {
	    minVarSum = varSum;
	    best = i;
	}
    }
    delete [] axis;

    // we're done.  copy everything into the out parameters.
    numRight = 0;
    vec_t dummyPred;
    bool dummy;
    gist_predcursor_t rCursor;
    for (i = best + 1; i < itemCnt; ++i) {
	int item = which[i].itemNo;
	assert(item >= 0 && item < itemCnt);
	rCursor.add(pcursor.elems[item].key, pcursor.elems[item].keyLen);
	rightEntries[numRight] = item;
	++numRight;
    }
    vec_t rVec(rightBp, rightLen);
    union_bp(rCursor, page, dummyPred, dummyPred, rVec, dummy, false);
    gist_predcursor_t lCursor;
    for (i = 0; i <= best; ++i) {
	int item = which[i].itemNo;
	assert(item >= 0 && item < itemCnt);
	lCursor.add(pcursor.elems[item].key, pcursor.elems[item].keyLen);
    }
    vec_t lVec(leftBp, leftLen);
    union_bp(lCursor, page, dummyPred, dummyPred, lVec, dummy, false);

    delete [] which;
}
