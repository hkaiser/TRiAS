// gist_srtree.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_srtree.cc,v 1.7 2000/03/15 00:24:52 mashah Exp $

#ifdef __GNUG__
#pragma implementation "gist_srtree.h"
#endif

#include "gist_defs.h"		// for assert()
#include "gist_rtpred_sr.h"
#include "gist_srtree.h"
#include "gist_ball.h"		// for EnclosingBall()
#include "gist_rtreecext.h"
#include "gist_support.h" // for print<>, parse<>, etc.

// VCPORT_B
const float ss_ext_t::MINSPLITUTIL = (float)0.3;
// VCPORT_E

///////////////////////////////////////////////////////////////////////////////
// sr_ext_t helper functions
///////////////////////////////////////////////////////////////////////////////

static double
sr_pt_dist(const void *item, int itemLen, const rt_pred& query)
{
    rt_sphererect sr(rt_sphererect::size2dim(itemLen), (double *) item);
    return(sr.dist((rt_point&) query));
}

static bool
sr_equal_sr(const void *c1, int l, const rt_pred& sr2)
{
    rt_sphererect sr1(rt_sphererect::size2dim(l), (const double *) c1);
    return (sr1.isEqual((const rt_sphererect&) sr2));
}

static bool
sr_contains_pt(const void *c1, int l, const rt_pred& p2)
{
    rt_sphererect sr1(rt_sphererect::size2dim(l), (const double *) c1);
    return (sr1.contains((const rt_point&) p2));
}

static bool
sr_contains_rect(const void *c1, int l, const rt_pred& r2)
{
    rt_sphererect sr1(rt_sphererect::size2dim(l), (const double *) c1);
    return (sr1.contains((const rt_rect&) r2));
}

static bool
sr_contains_sr(const void *c1, int l, const rt_pred& p2)
{
    rt_sphererect sr1(rt_sphererect::size2dim(l), (const double *) c1);
    return (sr1.contains((const rt_sphererect&) p2));
}

static bool
sr_overlaps_rect(const void *c1, int l, const rt_pred& r2)
{
    rt_sphererect sr1(rt_sphererect::size2dim(l), (const double *) c1);
    return (sr1.overlaps((const rt_rect&) r2));
}

static double
pt_span(const rt_pred& pred)
{
    return(((const rt_point&) pred).span());
}

static double
sr_span(const rt_pred& pred)
{
    return(((const rt_sphererect&) pred).span());
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
sr_center(rt_pred* pred, const void* item, int itemLen)
{
    int d = rt_sphererect::size2dim(itemLen);
    assert(pred == NULL || pred->dim() == d);
    double *c = (double*) (((char*) item) + rt_rect::dim2size(d)); // XXX center
    if (pred == NULL) {
	return(new rt_point(d, c));
    }
    pred->set(c);
    return(pred);
}

static rt_pred*
sr_pt_expand(rt_pred* pred, const void *item, int itemLen, bool preserve)
{
    assert(pred == NULL || pred->dim() == rt_point::size2dim(itemLen));
    rt_point p(rt_point::size2dim(itemLen), (const double *) item);
    return(pred ? ((rt_sphererect*) pred)->expand(p, preserve)
	: new rt_sphererect(p));
}

static rt_pred*
sr_sr_expand(rt_pred* pred, const void* item, int itemLen, bool preserve)
{
    assert(pred == NULL || pred->dim() == rt_sphererect::size2dim(itemLen));
    rt_sphererect sr(rt_sphererect::size2dim(itemLen), (const double *) item);
    return(pred ? ((rt_sphererect*) pred)->expand(sr, preserve)
	: new rt_sphererect(sr));
}

///////////////////////////////////////////////////////////////////////////////
// sr_ext_t function tables
///////////////////////////////////////////////////////////////////////////////

rtbase_ext_t::CmpFctTbl srPointCmpTbl = {
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
	{ &rt_pred::alwaysTrue,	// sphererect key, point query
	  &sr_contains_pt,
	  &sr_contains_pt,
	  &sr_contains_pt,
	  &sr_contains_pt,
	  &rt_pred::alwaysTrue,
	  &sr_contains_pt,
	  &sr_contains_pt,
	  &sr_contains_pt,
	},
	{ &rt_pred::alwaysTrue,	// sphererect key, rect query
	  &sr_contains_rect,
	  &sr_overlaps_rect,
	  &sr_contains_rect,
	  &sr_overlaps_rect,
	  &rt_pred::alwaysTrue,
	  &sr_overlaps_rect,
	  &sr_overlaps_rect,
	  &sr_overlaps_rect,
	}
    }
};
rtbase_ext_t::ExpandFctTbl srPointExpandTbl = {
    &sr_pt_expand,						// leaf
    &sr_sr_expand						// internal
};
rtbase_ext_t::PropFctTbl srPointPropTbl = {
    { &pt_span, NULL },						// leaf
    { &sr_span, NULL }						// internal
};
rtbase_ext_t::BpCmpFctTbl srPointBpCmpTbl = {
    &sr_equal_sr,
    &sr_contains_pt,						// leaf
    &sr_contains_sr						// internal
};
rtbase_ext_t::ConvFctTbl srPointConvTbl = {
    { &rt_point::size2dim, &rt_point::dim2size },		// leaf
    { &rt_sphererect::size2dim, &rt_sphererect::dim2size }	// internal
};
ss_ext_t::CenterFctTbl srPointCenterTbl = {
    &pt_center,
    &sr_center
};
rtbase_ext_t::OpTbl srPointOpTbl = {
    gist_cursorext_t::cext_stack_id,		// nooper
    gist_cursorext_t::cext_stack_id,		// equal
    gist_cursorext_t::cext_stack_id,		// overlap
    gist_cursorext_t::cext_stack_id,		// contains
    gist_cursorext_t::cext_stack_id,		// contained
    gist_cursorext_t::cext_sr_point_nn_id,	// nearest
    gist_cursorext_t::cext_stack_id,		// count_overlap
    gist_cursorext_t::cext_stack_id,		// count_sample
    gist_cursorext_t::cext_stack_id,		// count_combo
};

sr_ext_t srpoint_ext(srPointCmpTbl, srPointExpandTbl,
    srPointPropTbl, srPointConvTbl, srPointBpCmpTbl,
    srPointOpTbl, srPointCenterTbl);
gist_unorderedn_ext_t sr_point_ext(gist_ext_t::sr_point_ext_id,
    "sr_point_ext", gist_support::printSrPred, gist_support::printInt,
    gist_support::parsePoint, gist_support::parseInt, gist_support::parseGeoQuery,
    srpoint_ext);

rtbase_nn_cursorext_t::RtPrioFctTbl srPointNnPrioTbl = {
    { &rt_point::dist_point, NULL },				// leaf
    { &sr_pt_dist, NULL }					// internal
};

rtbase_nn_cursorext_t sr_point_nn_cext(
    gist_cursorext_t::cext_sr_point_nn_id, srPointNnPrioTbl);

///////////////////////////////////////////////////////////////////////////////
// sr_ext_t methods
///////////////////////////////////////////////////////////////////////////////

void
sr_ext_t::penalty(
    const void *subtreePred,
    int predLen,
    int level,
    const void *newKey,
    int keyLen,
    gist_penalty_t &p) const
{
    int d = rt_point::size2dim(keyLen);
    rt_sphererect sr(d, (double*) subtreePred);
    rt_point pt(d, (double*) newKey);
    p.p = sr.sphere.center.dist(pt);
}


/////////////////////////////////////////////////////////////////////////
// gist::insert - insert a new entry into the tree
//
// Description:
//	- if !bpIsValid, generates bounding sphere from scratch for 
//	  the page predicates plus pred1/-2
//	- if bpIsValid, adds in pred1/-2 incrementally
//
// Preconditions:
// Postconditions:
//
/////////////////////////////////////////////////////////////////////////

void
sr_ext_t::union_bp(
    const gist_predcursor_t& pcursor,	// in
    const gist_p& page,			// in
    const vec_t& pred1,			// in
    const vec_t& pred2,			// in
    vec_t& bp,				// in/out
    bool& bpChanged,			// out
    bool bpIsValid)			// in
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
	rt_rect r(d);
	rt_sphererect* sBp = NULL;
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
	    sBp = (rt_sphererect*) newBp;

	    inCenter[i] = inCenters + i * d;
	    for (int j = 0; j < d; ++j) {
		inCenter[i][j] = sBp->sphere.center.co(j);
	    }
	    inRadii[i] = sBp->sphere.radius();
	    nrec += sBp->sphere.rank.nrec();

	    // assign first rect, then expand
	    (void) r.expand(sBp->rect, i != 0);
	}

	assert(sBp != NULL);
	EnclosingBall(d, howmany,
	    inCenter, (level > 1) ? inRadii : (double*) NULL,
	    sBp->sphere.center.coords(), sBp->sphere.radius());
	sBp->sphere.rank.nrec() = nrec;
	delete [] inCenter;
	delete [] inCenters;
	delete [] inRadii;
	(void) memcpy(sBp->rect.coords(), r.coords(), rt_rect::dim2size(d));
	sBp->tighten();
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
