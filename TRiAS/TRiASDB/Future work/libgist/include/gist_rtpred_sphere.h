// gist_rtpred_sphere.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_sphere.h,v 1.1 1998/06/18 00:56:57 aoki Exp $

#ifndef GIST_RTPRED_SPHERE_H
#define GIST_RTPRED_SPHERE_H

#ifdef __GNUG__
#pragma interface "gist_rtpred_sphere.h"
#endif

#include "gist_rtpred_point.h"		// for rt_point

class rt_rect;

class rt_sphere : public rt_pred {
public:
    // this 'center' point may be a centroid as well.  it points to
    // the same memory as the underlying sphere center, so it will
    // remain up-to-date without maintenance (and, conversely, any
    // changes made to it will propagate to the sphere).  it is
    // generated and maintained to simplify the computation of (e.g.)
    // distance computations.
    rt_point center;

    rt_sphere(const rt_point& p, double r = 0.0);
    rt_sphere(int d, const double* c)
	: rt_pred(d, (double*) c, false),
	  center(d, (double*) c) {}

    // needed for pickSplit():
    double span() const { return(0.0); }	// XXX
    double margin() const { return(0.0); }	// XXX

    // for minDist():
    double dist(const rt_point& p) const;

    inline double& radius() const
	{ return(coord[dimension]); }

    bool contains(const rt_point& p) const;
    bool contains(const rt_rect& r) const;
    bool contains(const rt_sphere& s) const;
    bool overlaps(const rt_rect& r) const;

    static int size2dim(int s) { return((s/sizeof(double))-1); }
    static int dim2size(int d) { return((d+1)*sizeof(double)); }
};

// sphere-tree internal node key.

class rt_bounding_sphere : public rt_sphere {
public:
    rt_bounding_sphere(const rt_point& p)
	: rt_sphere(p) {}
    rt_bounding_sphere(int d, const double* c)
	: rt_sphere(d, c) {}
    rt_bounding_sphere(const rt_bounding_sphere& s)
	: rt_sphere(s.center, s.radius()) {}

    bool isEqual(const rt_bounding_sphere& s) const;

    rt_bounding_sphere* expand(const rt_point& p, bool preserve = true);
    rt_bounding_sphere* expand(const rt_bounding_sphere& s, bool preserve = true);
};

#endif // GIST_RTPRED_SPHERE_H
