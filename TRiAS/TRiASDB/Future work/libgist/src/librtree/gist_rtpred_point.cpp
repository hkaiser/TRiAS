// gist_rtpred_point.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_point.cc,v 1.2 1998/09/24 05:22:06 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_rtpred_point.h"
#endif

#include <math.h>			// for sqrt()

#include "gist_rtpred_point.h"
#include "gist_rtpred_rect.h"

rt_point::rt_point(int d)
    : rt_pred(d, new double[dim2size(d)/sizeof(double)], true)
{
    // initialize coordinates
    for (int i = 0; i < dimension; i++) {
	coord[i] = 0.0;
    }
}

rt_point::rt_point(const rt_point& pt)
    : rt_pred(pt.dim(), new double[dim2size(pt.dim())/sizeof(double)], true)
{
    for (int i = 0; i < dimension; i++) {
        coord[i] = pt.coord[i];
    }
}

bool 
rt_point::isEqual(const rt_point& p) const
{
    // just compare the coordinate array.
    return(((rt_pred*) this)->isEqual(p, dimension));
}

double
rt_point::dist(const rt_point& pt) const
{
    assert(dimension == pt.dim());

    // compute distance using the L2 (euclidean) norm.
    double sum = 0.0;
    for (int i = 0; i < dimension; i++) {
	double diff = coord[i] - pt.coord[i];
	sum += diff * diff;
    }
    return(sqrt(sum));
}

bool 
rt_point::contains(const rt_rect& rect) const
{
    assert(dimension == rect.dim());

    // the only way this can happen is if the rectangle is a point
    // with the same coordinates (i.e., rectangle == point).
    for (int i = 0; i < dimension; i++) {
        if (rect.lo(i) != rect.hi(i) || rect.lo(i) != coord[i]) {
            // out of range in dimension i
            return false;
        }
    }
    return true;
}

bool 
rt_point::contains(const rt_point& pt) const
{
    return isEqual(pt);
}

double
rt_point::dist_point(const void *p1, int p1Len, const rt_pred& p2)
{
    rt_point p(rt_point::size2dim(p1Len), (const double *) p1);
    return (p.dist((const rt_point&) p2));
}

bool
rt_point::contains_point(const void *p1, int p1Len, const rt_pred& p2)
{
    rt_point p(rt_point::size2dim(p1Len), (const double *) p1);
    return (p.contains((const rt_point&) p2));
}

bool
rt_point::contains_rect(const void *p1, int p1Len, const rt_pred& p2)
{
    rt_point p(rt_point::size2dim(p1Len), (const double *) p1);
    return (p.contains((const rt_rect&) p2));
}

bool
rt_point::contained_rect(const void *p1, int p1Len, const rt_pred& p2)
{
    rt_point p(rt_point::size2dim(p1Len), (const double *) p1);
    return (((const rt_rect&) p2).contains(p));
}
