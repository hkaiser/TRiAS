// gist_rrtree.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rrtree.cc,v 1.6 1999/06/16 03:07:41 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_rrtree.h"
#endif

#include "gist_rtpred_rr.h"
#include "gist_rrtree.h"
#include "gist_rtreecext.h"
#include "gist_support.h"

//
// rtbase_cursorext_t
//

static double
rr_pt_ovlp(const void *item, int itemLen, const rt_pred& query)
{
    rt_rrect rr(rt_rrect::size2dim(itemLen), (double *) item);
    // smaller priorities come out first
    double prio = rr.contains((rt_point&) query) ? -1.0 : 0.0;
    return(prio);
}

static double
rr_rect_ovlp(const void *item, int itemLen, const rt_pred& query)
{
    rt_rrect rr(rt_rrect::size2dim(itemLen), (double *) item);
    rt_rect& qr = (rt_rect&) query;
    // smaller priorities come out first
    // full match: 100% overlap with zero uncertainty
    // no match: 0% overlap with zero uncertainty
    double prio = 0.0;
    if (qr.overlaps(rr) && !qr.contains(rr)) {
	// partial match: 100% uncertainty
	prio = -(rr.rank.nrec());
    }
    return(prio);
}

static rc_t
rr_leaf_state(
    gist_cursor_t& cursor,
    const gist_p& page,
    int whichItem,
    const vec_t& keyv,
    const gist_penalty_t& prio)
{
    // update the count.  each leaf record counts as one, obviously.
    rr_counts* count = (rr_counts*) cursor.state;
    count->min += 1.0;
    count->ctr += 1.0;
    count->max += 1.0;

    // don't push the leaf record into the queue -- we don't want to
    // return any of the leaf records themselves.

    return(RCOK);
}

static rc_t
rr_reset(gist_cursor_t& cursor)
{
    if (cursor.state == NULL) {
	double* d = new double[3];
	d[0] = d[1] = d[2] = 0.0;
	cursor.state = d;
    } else {
	delete [] cursor.state;
	cursor.state = NULL;
    }

    return(RCOK);
}

static rc_t
rr_final(gist_cursor_t& cursor, gist_prioq_entry& entry, bool isLast)
{
    rr_counts* count = (rr_counts*) cursor.state;
    if (isLast == true) {
	(void) memset(&entry, 0, sizeof(entry));
	entry.typ = gist_lstk_entry::eItem;
	entry.val.item.key = new rr_counts;
	entry.val.item.klen = sizeof(rr_counts);
	(void) memcpy(entry.val.item.key, count, sizeof(*count));
	entry.val.item.data = new double(0.0);
	entry.val.item.dlen = sizeof(double);

	// this result record is the last thing returned!
	cursor.k = 1;
    } else {
	assert(entry.typ == gist_lstk_entry::eNode);
	rt_rrect rr(rt_rrect::size2dim(entry.val.node.klen),
	    (double *) entry.val.node.key);
	rt_query_t* query = (rt_query_t*) cursor.query;
	if (query->argType == rt_query_t::rt_rectarg) {
	    rt_rect* qr = (rt_rect*) query->value;
	    if (qr->contains(rr)) {
		count->min += rr.rank.nrec();
		count->ctr += rr.rank.nrec();
		count->max += rr.rank.nrec();
	    } else {
		// this uses the uniformity assumption to guess an
		// appropriate center value - 'overlap' sometimes
		// returns zero because 'overlaps' returns true when
		// edges coincide.
		double ovlp = rr.overlap(*qr);
		double span = rr.span();
		if (ovlp > 0.0 && span > 0.0) {
		    // count->min += rr.rank.nrec * 0.0;
		    count->ctr += rr.rank.nrec() * (ovlp / span);
		    count->max += rr.rank.nrec(); // * 1.0
		}
	    }
	}
    }
    return(RCOK);
}

rtbase_cursorext_t::RtPrioFctTbl rrPointItPrioTbl = {
    { NULL,        NULL },					// leaf
    { &rr_pt_ovlp, &rr_rect_ovlp }				// internal
};
rtbase_cursorext_t::RtStateFctTbl rrPointItStateTbl = {
    { &rr_leaf_state, &rr_leaf_state },				// leaf
    { &gist_queue_set_cursorext_t::push_node_key,
      &gist_queue_set_cursorext_t::push_node_key }		// internal
};
rtbase_cursorext_t rr_point_it_cext(
    gist_cursorext_t::cext_rr_point_it_id,
    &rr_reset,
    rrPointItPrioTbl,
    rrPointItStateTbl,
    &rr_final);

//
// rtbase_nn_cursorext_t
//

static double
rr_pt_dist(const void *item, int itemLen, const rt_pred& query)
{
    rt_rrect r(rt_rrect::size2dim(itemLen), (const double *) item);
    return(r.dist((rt_point&) query));
}

static bool
rr_equal_rr(const void *c1, int l, const rt_pred& r2)
{
    rt_rrect r1(rt_rrect::size2dim(l), (const double *) c1);
    return (r1.isEqual((const rt_rrect&) r2));
}

static bool
pt_contained_rect(const void *c1, int l, const rt_pred& r2)
{
    rt_point p1(rt_point::size2dim(l), (const double *) c1);
    return (((const rt_rect&) r2).contains(p1));
}

static bool
rr_contains_pt(const void *c1, int l, const rt_pred& p2)
{
    rt_rrect r1(rt_rrect::size2dim(l), (const double *) c1);
    return (r1.contains((const rt_point&) p2));
}

static bool 
rr_contains_rect(const void *c1, int l, const rt_pred& r2)
{
    rt_rrect r1(rt_rrect::size2dim(l), (const double *) c1);
    return (r1.contains((const rt_rect&) r2));
}

static bool 
rr_contains_rr(const void *c1, int l, const rt_pred& r2)
{
    rt_rrect r1(rt_rrect::size2dim(l), (const double *) c1);
    return (r1.contains((const rt_rrect&) r2));
}

static bool
rr_overlaps_rect(const void *c1, int l, const rt_pred& r2)
{
    rt_rrect r1(rt_rrect::size2dim(l), (const double *) c1);
    return (r1.overlaps((const rt_rect&) r2));
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
rr_pt_expand(rt_pred* pred, const void* item, int itemLen, bool preserve)
{
    assert(pred == NULL || pred->dim() == rt_point::size2dim(itemLen));
    rt_point p(rt_point::size2dim(itemLen), (const double *) item);
    return(pred ? ((rt_rrect*) pred)->expand(p, preserve) : new rt_rrect(p));
}

static rt_pred*
rr_rr_expand(rt_pred* pred, const void* item, int itemLen, bool preserve)
{
    assert(pred == NULL || pred->dim() == rt_rrect::size2dim(itemLen));
    rt_rrect r(rt_rrect::size2dim(itemLen), (const double *) item);
    return(pred ? ((rt_rrect*) pred)->expand(r, preserve) : new rt_rrect(r));
}

rtbase_ext_t::CmpFctTbl rrPointCmpTbl = {
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
	{ &rt_pred::alwaysTrue,	// rrect key, point query
	  &rr_contains_pt,
	  &rr_contains_pt,
	  &rr_contains_pt,
	  &rr_contains_pt,
	  &rt_pred::alwaysTrue,
	  &rr_contains_pt,
	  &rr_contains_pt,
	  &rr_contains_pt,
	},
	{ &rt_pred::alwaysTrue,	// rrect key, rect query
	  &rr_contains_rect,
	  &rr_overlaps_rect,
	  &rr_contains_rect,
	  &rr_overlaps_rect,
	  &rt_pred::alwaysTrue,
	  &rr_overlaps_rect,
	  &rr_overlaps_rect,
	  &rr_overlaps_rect,
	}
    }
};
rtbase_ext_t::ExpandFctTbl rrPointExpandTbl = {
    &rr_pt_expand,						// leaf
    &rr_rr_expand						// internal
};
rtbase_ext_t::PropFctTbl rrPointPropTbl = {
    { &pt_span, &pt_margin },					// leaf
    { &rect_span, &rect_margin }				// internal
};
rtbase_ext_t::BpCmpFctTbl rrPointBpCmpTbl = {
    &rr_equal_rr,
    &rr_contains_pt,						// leaf
    &rr_contains_rr						// internal
};
rtbase_ext_t::ConvFctTbl rrPointConvTbl = {
    { &rt_point::size2dim, &rt_point::dim2size },		// leaf
    { &rt_rrect::size2dim, &rt_rrect::dim2size }		// internal
};
rtbase_ext_t::OpTbl rrPointOpTbl = {
    gist_cursorext_t::cext_stack_id,		// nooper
    gist_cursorext_t::cext_stack_id,		// equal
    gist_cursorext_t::cext_stack_id,		// overlap
    gist_cursorext_t::cext_stack_id,		// contains
    gist_cursorext_t::cext_stack_id,		// contained
    gist_cursorext_t::cext_rr_point_nn_id,	// nearest
    gist_cursorext_t::cext_rr_point_it_id,	// count_overlap
    gist_cursorext_t::cext_rr_point_ar_id,	// count_sample
    gist_cursorext_t::cext_rr_point_co_id,	// count_combo
};

rt_ext_t rrpoint_ext(rrPointCmpTbl, rrPointExpandTbl, 
    rrPointPropTbl, rrPointConvTbl, rrPointBpCmpTbl, rrPointOpTbl);
gist_unorderedn_ext_t rr_point_ext(gist_ext_t::rr_point_ext_id,
    "rr_point_ext", gist_support::printPtRtPred, gist_support::printInt,
    gist_support::parsePoint, gist_support::parseInt, gist_support::parseGeoQuery,
    rrpoint_ext);

//
// rtbase_nn_cursorext_t
//

rtbase_cursorext_t::RtPrioFctTbl rrPointNnPrioTbl = {
    { &rt_point::dist_point, NULL },				// leaf
    { &rr_pt_dist, NULL }					// internal
};

rtbase_nn_cursorext_t rr_point_nn_cext(
    gist_cursorext_t::cext_rr_point_nn_id, rrPointNnPrioTbl);

//
// rtbase_ar_cursorext_t
//

static double
rr_pt_rank(const void *item, int itemLen, const rt_pred& query)
{
    return(1.0);
}

static double
rr_rect_rank(const void *item, int itemLen, const rt_pred& query)
{
    rt_rrect rr(rt_rrect::size2dim(itemLen), (double *) item);
    return(rr.rank.nrec());
}

rtbase_ar_cursorext_t::RtPrioFctTbl rrPointArPrioTbl = {
    { &rr_pt_rank,   &rr_pt_rank },				// leaf
    { &rr_rect_rank, &rr_rect_rank }				// internal
};
rtbase_ar_cursorext_t rr_point_ar_cext(
    gist_cursorext_t::cext_rr_point_ar_id,
    rrPointArPrioTbl);

//
// rr_point_co_cext
//

static bool
co_switch(gist_cursor_t& cursor)
{
    return(cursor.io > 1);
}

gist_switch_cursorext_t rr_point_co_cext(
    gist_cursorext_t::cext_rr_point_co_id,
    &co_switch,
    gist_cursorext_t::cext_rr_point_it_id,
    gist_cursorext_t::cext_rr_point_ar_id);
