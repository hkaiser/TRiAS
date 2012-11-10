// gist_rtpred_rect.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_rect.cc,v 1.2 1998/09/24 05:22:07 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_rtpred_rect.h"
#endif

#include <math.h>			// for sqrt(), fabs()

#include "gist_rtpred_point.h"
#include "gist_rtpred_rect.h"

rt_rect::rt_rect(int d)
    : rt_pred(d, new double[dim2size(d)/sizeof(double)], true)
{ 
    // initialize coordinates
    for (int i = 0; i < dimension; i++) {
        lo(i) = hi(i) = 0.0;
    }
}

rt_rect::rt_rect(const rt_rect &r)
    : rt_pred(r.dim(), new double[dim2size(r.dim())/sizeof(double)], true)
{
    for (int i = 0; i < dimension; i++) {
        lo(i) = r.lo(i);
        hi(i) = r.hi(i);
    }
}

rt_rect::rt_rect(const rt_point &p)
    : rt_pred(p.dim(), new double[dim2size(p.dim())/sizeof(double)], true)
{
    for (int i = 0; i < dimension; i++) {
        hi(i) = lo(i) = p.co(i);
    }
}

rt_rect&
rt_rect::operator=(const rt_rect& rhs)
{
    // we allow this to happen because we sometimes allocate an
    // uninitialized rt_rect using automatic storage and then fill it
    // in later.
    if (dimension != rhs.dim()) {
	clear();
	dimension = rhs.dim();
	coord = new double[dim2size(dimension)/sizeof(double)];
	dealloc = true;
    }

    for (int i = 0; i < dimension; i++) {
        lo(i) = rhs.lo(i);
        hi(i) = rhs.hi(i);
    }
    return *this;
}

bool 
rt_rect::isEqual(const rt_rect& r) const
{
    // just compare the coordinate array.
    return(((rt_pred*) this)->isEqual(r, 2 * dimension));
}

double 
rt_rect::span() const
{ 
    double result = 1.0;

    for (int i=0; i<dimension; i++) {
	if (lo(i) > hi(i)) {
	    result = 0.0;
	    break;
	}
	result = result * (hi(i) - lo(i));
    }
    return result; 
}

double
rt_rect::margin() const
{
    double result = 0.0;

    for (int i = 0; i < dimension; i++) {
	if (hi(i) > lo(i)) {
	    result += hi(i) - lo(i);
	}
    }
    return result;
}

rt_rect*
rt_rect::expand(const rt_point & pt, bool preserve)
{
    assert(pt.dim() == dimension);
    for (int i = 0; i < dimension; i++) {
	// adjust upper/lower bounds for dimension i
	if (!preserve || pt.co(i) < lo(i)) {
	    lo(i) = pt.co(i);
	}
	if (!preserve || pt.co(i) > hi(i)) {
	    hi(i) = pt.co(i);
	}
    }
    return(this);
}

rt_rect*
rt_rect::expand(const rt_rect & rect, bool preserve) 
{
    assert(rect.dim() == dimension);
    for (int i = 0; i < dimension; i++) {
	// adjust upper/lower bounds for dimension i
	// assuming rect.Lo(i) <= rect.Hi(i)
	if (!preserve || rect.lo(i) < lo(i)) {
	    lo(i) = rect.lo(i);
	}
	if (!preserve || rect.hi(i) > hi(i)) {
	    hi(i) = rect.hi(i);
	}
    }
    return(this);
}

double
rt_rect::overlap(const rt_rect& rect) const
{
    assert(rect.dim() == dimension);
    double overlap = 1.0;

    for (int i = 0; i < dimension; i++) {
        double low = (rect.lo(i) > lo(i) ? rect.lo(i) : lo(i));
        double high = (rect.hi(i) < hi(i) ? rect.hi(i) : hi(i));
	if (low > high) {
	    // no overlap
	    return 0.0;
	}
	overlap *= high - low;
    }
    return overlap;
}

bool 
rt_rect::overlaps(const rt_rect & rect) const
{
    assert(rect.dim() == dimension);
    for (int i = 0; i < dimension; i++) {
	// check each dimension for overlapping
	if (hi(i) < rect.lo(i) || lo(i) > rect.hi(i))  {
	    // non-overlapping in one-dimension
	    return false;
	}
    }
    // overlapping in all dimensions
    return true;
}

bool 
rt_rect::contains(const rt_rect & rect) const
{
    assert(rect.dim() == dimension);

    for (int i = 0; i < dimension; i++) {
	if (rect.lo(i) < lo(i) || rect.hi(i) > hi(i)) {
	    // out of range in dimension i
	    return false;
	}
    }
    return true;
}

bool 
rt_rect::contains(const rt_point & pt) const
{
    assert(pt.dim() == dimension);
    for (int i = 0; i < dimension; i++) {
	if (pt.co(i) > hi(i) || pt.co(i) < lo(i)) {
	    // out of range in dimension i
	    return false;
	}
    }
    return true;
}

double
rt_rect::dist(const rt_rect& rect)  const
{
    assert(dimension == rect.dim());

    double sum = 0.0;
    for (int i = 0; i < dimension; i++) {
	// this dimension only contributes to the L2 distance between
	// the rectangles if they are wholly disjoint along it.
	double diff;
	if (hi(i) < rect.lo(i)) {
	    diff = rect.lo(i) - hi(i);
	    sum += diff * diff;
	} else if (rect.hi(i) < lo(i)) {
	    diff = lo(i) - rect.hi(i);
	    sum += diff * diff;
	}
    }
    return(sqrt(sum));
}

double
rt_rect::dist(const rt_point& pt) const
{
    assert(dimension == pt.dim());

    double sum = 0.0;
    for (int i = 0; i < dimension; i++) {
	// this dimension only contributes to the L2 distance if the
	// point and rectangle do not overlap along it.
	double diff;
	if (pt.co(i) < lo(i)) {
	    diff = lo(i) - pt.co(i);
	    sum += diff * diff;
	} else if (pt.co(i) > hi(i)) {
	    diff = pt.co(i) - hi(i);
	    sum += diff * diff;
	}
    }
    return(sqrt(sum));
}

double
rt_rect::maxdist(const rt_point& p) const
{
    // find the distance to the farthest corner.  because of rectangle
    // symmetry (a rectangle contains all combinations of its hi/lo
    // values) and the fact that the maximal distance from a line to a
    // segment is always one of its endpoints, we can just greedily
    // pick the hi/lo in each dimension that gives the largest
    // distance.
    double dist = 0.0;
    for (int i = 0; i < p.dim(); ++i) {
	double dlo = fabs(lo(i) - p.co(i));
	double dhi = fabs(hi(i) - p.co(i));
	double diff;
	if (dlo > dhi) {
	    diff = dlo;
	} else {
	    diff = dhi;
	}
	dist += diff * diff;
    }
    return(sqrt(dist));
}

double
rt_rect::dist_point(const void *p1, int p1Len, const rt_pred& p2)
{
    rt_rect p(rt_rect::size2dim(p1Len), (const double *) p1);
    return(p.dist((rt_point&) p2));
}

bool
rt_rect::overlaps_rect(const void *p1, int p1Len, const rt_pred& p2)
{
    rt_rect p(rt_rect::size2dim(p1Len), (const double *) p1);
    return(p.overlaps((rt_rect&) p2));
}

bool
rt_rect::contains_point(const void *p1, int p1Len, const rt_pred& p2)
{
    rt_rect p(rt_rect::size2dim(p1Len), (const double *) p1);
    return(p.contains((rt_point&) p2));
}

bool
rt_rect::contains_rect(const void *p1, int p1Len, const rt_pred& p2)
{
    rt_rect p(rt_rect::size2dim(p1Len), (const double *) p1);
    return(p.contains((rt_rect&) p2));
}

bool
rt_rect::contained_rect(const void *p1, int p1Len, const rt_pred& p2)
{
    rt_rect p(rt_rect::size2dim(p1Len), (const double *) p1);
    return(((rt_rect&) p2).contains(p));
}
