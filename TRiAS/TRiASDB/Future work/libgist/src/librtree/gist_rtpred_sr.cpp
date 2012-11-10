// gist_rtpred_sr.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_sr.cc,v 1.2 1998/09/24 05:22:11 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_rtpred_sr.h"
#endif

#include "gist_rtpred_sr.h"

rt_sphererect::rt_sphererect(const rt_point& p)
    : rt_pred(p.dim(), new double[dim2size(p.dim())/sizeof(double)], true),
      rect(p.dim(), coord),
      sphere(p.dim(), coord + rt_rect::dim2size(p.dim())/sizeof(double))
{
    for (int i = 0; i < dimension; ++i) {
	sphere.center.co(i) = rect.lo(i) = rect.hi(i) = p.co(i);
    }
    sphere.radius() = 0.0;
    sphere.rank.nrec() = 1;
}

rt_sphererect::rt_sphererect(const rt_sphererect& sr)
    : rt_pred(sr.dim(), new double[dim2size(sr.dim())/sizeof(double)], true),
      rect(sr.dim(), (double*) coord),
      sphere(sr.dim(), coord + rt_rect::dim2size(sr.dim())/sizeof(double))
{
    for (int i = 0; i < dimension; ++i) {
	sphere.center.co(i) = sr.sphere.center.co(i);
	rect.lo(i) = sr.rect.lo(i);
	rect.hi(i) = sr.rect.hi(i);
    }
    sphere.radius() = sr.sphere.radius();
    sphere.rank.nrec() = sr.sphere.rank.nrec();
}

bool
rt_sphererect::isEqual(const rt_sphererect& s) const
{
    return(((rt_pred*) this)->isEqual(s, dim2size(dimension)));
}

bool
rt_sphererect::contains(const rt_point& p) const
{
    return(sphere.contains(p) && rect.contains(p));
}

bool
rt_sphererect::contains(const rt_rect& r) const
{
    return(sphere.contains(r) && rect.contains(r));
}

bool
rt_sphererect::contains(const rt_sphererect& sr) const
{
    return(sphere.contains(sr.sphere) && rect.contains(sr.rect));
}

bool
rt_sphererect::overlaps(const rt_rect& r) const
{
    return(sphere.overlaps(r) && rect.overlaps(r));
}

double
rt_sphererect::dist(const rt_point& p) const
{
    assert(p.dim() == dimension);
    double sdist = sphere.dist(p);
    double rdist = rect.dist(p);
    return((sdist > rdist) ? sdist : rdist);
}

void
rt_sphererect::tighten()
{
    double dist = rect.maxdist(sphere.center);

    if (dist < sphere.radius()) {
	sphere.radius() = dist;
    }
}

rt_sphererect*
rt_sphererect::expand(const rt_point& p, bool preserve)
{
    assert(p.dim() == dimension);

    (void) rect.expand(p, preserve);
    (void) sphere.expand(p, preserve);
    if (!preserve) {
	tighten();
    }

    return(this);
}

rt_sphererect*
rt_sphererect::expand(const rt_sphererect& sr, bool preserve)
{
    assert(sr.dim() == dimension);

    (void) rect.expand(sr.rect, preserve);	// XXX
    (void) sphere.expand(sr.sphere, preserve);	// XXX
    if (!preserve) {
	tighten();
    }

    return(this);
}
