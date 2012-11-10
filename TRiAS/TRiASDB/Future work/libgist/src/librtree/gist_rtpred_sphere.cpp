// gist_rtpred_sphere.cc					-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_sphere.cc,v 1.2 1998/09/24 05:22:09 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_rtpred_sphere.h"
#endif

#include "gist_rtpred_rect.h"
#include "gist_rtpred_sphere.h"

///////////////////////////////////////////////////////////////////////////////
// rt_sphere methods
///////////////////////////////////////////////////////////////////////////////

rt_sphere::rt_sphere(const rt_point& p, double r)
    : rt_pred(p.dim(), new double[dim2size(p.dim())/sizeof(double)], true),
      center(p.dim(), (double*) coord)
{
    for (int i = 0; i < dimension; ++i) {
	center.co(i) = p.co(i);
    }
    radius() = r;
}

double
rt_sphere::dist(const rt_point& p) const
{
    // the distance from a sphere to a point is (1) 0 if the point is
    // contained by the sphere and (2) the distance from the surface
    // of the sphere to the point otherwise.
    double d = center.dist(p) - radius();
    return((d <= 0.0) ? 0.0 : d);
}

bool
rt_sphere::contains(const rt_point& p) const
{
    return(center.dist(p) <= radius());
}

bool
rt_sphere::contains(const rt_rect& r) const
{
    double dist = r.maxdist(center);
    return(dist > radius());
}

bool
rt_sphere::contains(const rt_sphere& s) const
{
    return(center.dist(s.center) + s.radius() <= radius());
}

bool
rt_sphere::overlaps(const rt_rect& r) const
{
    return(r.dist(center) <= radius());
}

///////////////////////////////////////////////////////////////////////////////
// rt_bounding_sphere methods
///////////////////////////////////////////////////////////////////////////////

bool
rt_bounding_sphere::isEqual(const rt_bounding_sphere& s) const
{
    return(((rt_pred*) this)->isEqual(s, dim2size(dimension)));
}

// XXX NOTE: there is a fundamental crock in the way expand() works.
// there exist predicates that are not computable by just adding
// predicates one-by-one to a running bounding predicate.  (for
// example, a bounding sphere constructed in this way is not a minimal
// bounding sphere for the original set of shapes.)  do not expend any
// energy on these interfaces until this is straightened out.

rt_bounding_sphere*
rt_bounding_sphere::expand(const rt_point& p, bool preserve)
{
    assert(0);
    return(this);
}

rt_bounding_sphere*
rt_bounding_sphere::expand(const rt_bounding_sphere& s, bool preserve)
{
    assert(0);
    return(this);
}
