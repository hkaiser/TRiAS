// gist_rtpred_ss.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_ss.cc,v 1.3 1998/09/24 05:22:12 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_rtpred_ss.h"
#endif

#include "gist_rtpred_ss.h"

void
rt_centroid_sphere::_init(const rt_point& p, double r, double n)
{
    for (int i = 0; i < dimension; ++i) {
	center.co(i) = p.co(i);
    }
    radius() = r;
    rank.nrec() = n;
}

rt_centroid_sphere::rt_centroid_sphere(const rt_point& p)
    : rt_sphere(p.dim(),
        new double[rt_centroid_sphere::dim2size(p.dim())/sizeof(double)]),
      rank(p.dim(), coord + (rt_sphere::dim2size(p.dim())/sizeof(double)))
{
    dealloc = true;
    _init(p, 0.0, 1.0);
}

rt_centroid_sphere::rt_centroid_sphere(const rt_centroid_sphere& s)
    : rt_sphere(s.dim(),
	new double[rt_centroid_sphere::dim2size(s.dim())/sizeof(double)]),
      rank(s.dim(), coord + (rt_sphere::dim2size(s.dim())/sizeof(double)))
{
    dealloc = true;
    _init(s.center, s.radius(), s.rank.nrec());
}

bool
rt_centroid_sphere::isEqual(const rt_centroid_sphere& s) const
{
    return(((rt_pred*) this)->isEqual(s, dim2size(dimension)));
}

rt_centroid_sphere*
rt_centroid_sphere::expand(const rt_point& p, bool preserve)
{
    assert(dimension == p.dim());

    if (!preserve) {
	_init(p, 0.0, 1.0);
	return(this);
    }

    double oldRadius = radius();

    rt_point old(dimension);
    (void) memcpy(old.coords(), center.coords(), rt_point::dim2size(dimension));
    for (int i = 0; i < dimension; ++i) {
	center.co(i) =
	    (center.co(i) * rank.nrec() + p.co(i)) / (rank.nrec() + 1.0);
    }
    rank.nrec() += 1.0;

    radius() += center.dist(old);
    double newRadius = center.dist(p);
    if (newRadius > radius()) {
	radius() = newRadius;
    }

    assert(oldRadius <= radius());

    return(this);
}

rt_centroid_sphere*
rt_centroid_sphere::expand(const rt_centroid_sphere& s, bool preserve)
{
    assert(dimension == s.dim());

    if (!preserve) {
	_init(s.center, s.radius(), s.rank.nrec());
	return(this);
    }

    double oldRadius = radius();

    // unlike conventional bounding predicates, which just nail down
    // some (expanding) part of the space, the boundaries of a
    // centroid-based sphere always move around upon insertion -- the
    // centroid (almost) always moves.  before doing so, we need to
    // save a copy of the old centroid.
    rt_point old(dimension);
    (void) memcpy(old.coords(), center.coords(), rt_point::dim2size(dimension));
    for (int i = 0; i < dimension; ++i) {
	center.co(i) =
	    (center.co(i) * rank.nrec() + s.center.co(i) * s.rank.nrec()) /
	    (rank.nrec() + s.rank.nrec());
    }
    rank.nrec() += s.rank.nrec();

    // expand the radius by the distance just moved by the centroid.
    // this ensures that all of the items previously contained are
    // still contained (obviously, this is a worst-case calculation).
    radius() += center.dist(old);

    // now we just need to make sure that the sphere contains the new
    // item.
    double newRadius = center.dist(s.center) + s.radius();
    if (newRadius > radius()) {
	radius() = newRadius;
    }

    assert(oldRadius <= radius());

    return(this);
}
