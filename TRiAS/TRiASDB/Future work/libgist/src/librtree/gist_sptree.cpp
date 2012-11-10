// gist_sptree.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_sptree.cc,v 1.4 1999/06/16 03:07:41 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_sptree.h"
#endif

#include "gist_rtpred_rect.h"
#include "gist_rtpred_sphere.h"
#include "gist_sptree.h"
#include "gist_rtreecext.h"
#include "gist_support.h"

///////////////////////////////////////////////////////////////////////////////
// static helper methods
///////////////////////////////////////////////////////////////////////////////

static double
sp_pt_dist(const void *item, int itemLen, const rt_pred& query)
{
    rt_bounding_sphere s(rt_bounding_sphere::size2dim(itemLen),
	(double *) item);
    return(s.dist((rt_point&) query));
}

static bool
sp_equal_sp(const void *c1, int l, const rt_pred& s2)
{
    rt_bounding_sphere s1(rt_bounding_sphere::size2dim(l), (const double *) c1);
    return (s1.isEqual((const rt_bounding_sphere&) s2));
}

static bool
sp_contains_pt(const void *c1, int l, const rt_pred& p2)
{
    rt_bounding_sphere s1(rt_bounding_sphere::size2dim(l), (const double *) c1);
    return (s1.contains((const rt_point&) p2));
}

static bool
sp_contains_rect(const void *c1, int l, const rt_pred& r2)
{
    rt_bounding_sphere s1(rt_bounding_sphere::size2dim(l), (const double *) c1);
    return (s1.contains((const rt_rect&) r2));
}

static bool
sp_contains_sp(const void *c1, int l, const rt_pred& s2)
{
    rt_bounding_sphere s1(rt_bounding_sphere::size2dim(l), (const double *) c1);
    return (s1.contains((const rt_bounding_sphere&) s2));
}

static bool
sp_overlaps_rect(const void *c1, int l, const rt_pred& r2)
{
    rt_bounding_sphere s1(rt_bounding_sphere::size2dim(l), (const double *) c1);
    return (s1.overlaps((const rt_rect&) r2));
}

static double
pt_span(const rt_pred& pred)
{
    return(((const rt_point&) pred).span());
}

static double
sp_span(const rt_pred& pred)
{
    return(((const rt_bounding_sphere&) pred).span());
}

static double
pt_margin(const rt_pred& pred)
{
    return(((const rt_point&) pred).margin());
}

static rt_pred*
sp_pt_expand(rt_pred* pred, const void *item, int itemLen, bool preserve)
{
    assert(pred == NULL || pred->dim() == rt_point::size2dim(itemLen));
    rt_point p(rt_point::size2dim(itemLen), (const double *) item);
    return(pred ? ((rt_bounding_sphere*) pred)->expand(p, preserve)
	: new rt_bounding_sphere(p));
}

static rt_pred*
sp_sp_expand(rt_pred* pred, const void *item, int itemLen, bool preserve)
{
    assert(pred == NULL || pred->dim() == rt_bounding_sphere::size2dim(itemLen));
    rt_bounding_sphere s(rt_bounding_sphere::size2dim(itemLen),
	(const double *) item);
    return(pred ? ((rt_bounding_sphere*) pred)->expand(s, preserve)
	: new rt_bounding_sphere(s));
}

///////////////////////////////////////////////////////////////////////////////
// sp_ext_t function tables
///////////////////////////////////////////////////////////////////////////////

rtbase_ext_t::CmpFctTbl spPointCmpTbl = {
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
	  &sp_contains_pt,
	  &sp_contains_pt,
	  &sp_contains_pt,
	  &sp_contains_pt,
	  &rt_pred::alwaysTrue,
	  &sp_contains_pt,
	  &sp_contains_pt,
	  &sp_contains_pt,
	},
	{ &rt_pred::alwaysTrue,	// sphere key, rect query
	  &sp_contains_rect,
	  &sp_overlaps_rect,
	  &sp_contains_rect,
	  &sp_overlaps_rect,
	  &rt_pred::alwaysTrue,
	  &sp_overlaps_rect,
	  &sp_overlaps_rect,
	  &sp_overlaps_rect,
	}
    }
};
rtbase_ext_t::ExpandFctTbl spPointExpandTbl = {
    &sp_pt_expand,						// leaf
    &sp_sp_expand						// internal
};
rtbase_ext_t::PropFctTbl spPointPropTbl = {
    { &pt_span, NULL },						// leaf
    { &sp_span, NULL }						// internal
};
rtbase_ext_t::ConvFctTbl spPointConvTbl = {
    { &rt_point::size2dim, &rt_point::dim2size },		// leaf
    { &rt_bounding_sphere::size2dim, &rt_bounding_sphere::dim2size } // internal
};
rtbase_ext_t::BpCmpFctTbl spPointBpCmpTbl = {
    &sp_equal_sp,
    &sp_contains_pt,						// leaf
    &sp_contains_sp						// internal
};
rtbase_ext_t::OpTbl spPointOpTbl = {
    gist_cursorext_t::cext_stack_id,		// nooper
    gist_cursorext_t::cext_stack_id,		// equal
    gist_cursorext_t::cext_stack_id,		// overlap
    gist_cursorext_t::cext_stack_id,		// contains
    gist_cursorext_t::cext_stack_id,		// contained
    gist_cursorext_t::cext_sp_point_nn_id,	// nearest
    gist_cursorext_t::cext_stack_id,		// count_overlap
    gist_cursorext_t::cext_stack_id,		// count_sample
    gist_cursorext_t::cext_stack_id,		// count_combo
};

sp_ext_t sppoint_ext(spPointCmpTbl, spPointExpandTbl,
    spPointPropTbl, spPointConvTbl, spPointBpCmpTbl, spPointOpTbl);
gist_unorderedn_ext_t sp_point_ext(gist_ext_t::sp_point_ext_id,
    "sp_point_ext", gist_support::printSsPred, gist_support::printInt,
    gist_support::parsePoint, gist_support::parseInt, gist_support::parseGeoQuery,
    sppoint_ext);

rtbase_nn_cursorext_t::RtPrioFctTbl spPointNnPrioTbl = {
    { &rt_point::dist_point, NULL },				// leaf
    { &sp_pt_dist, NULL }					// internal
};

rtbase_nn_cursorext_t sp_point_nn_cext(
    gist_cursorext_t::cext_sp_point_nn_id, spPointNnPrioTbl);
