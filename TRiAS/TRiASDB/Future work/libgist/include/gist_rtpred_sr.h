// gist_rtpred_sr.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_sr.h,v 1.1 1998/06/18 00:56:58 aoki Exp $

#ifndef GIST_RTPRED_SR_H
#define GIST_RTPRED_SR_H

#ifdef __GNUG__
#pragma interface "gist_rtpred_sr.h"
#endif

#include "gist_rtpred_rect.h"	// for rt_rect
#include "gist_rtpred_ss.h"	// for rt_centroid_sphere

// SR-tree internal node key.
class rt_sphererect : public rt_pred {
private:
public:
    rt_rect rect;
    rt_centroid_sphere sphere;

    rt_sphererect(const rt_point& p);
    rt_sphererect(int d, const double* c)
	: rt_pred(d, (double*) c, false),
	  rect(d, (double*) c),
	  sphere(d, ((double*) c) + rt_rect::dim2size(d)/sizeof(double)) {}
    rt_sphererect(const rt_sphererect& sr);

    // needed for pickSplit():
    double span() const { return(0.0); }	// XXX
    double margin() const { return(0.0); }	// XXX

    // needed for minDist():
    double dist(const rt_point& p) const;

    // needed for consistent():
    bool contains(const rt_point& p) const;
    bool contains(const rt_rect& r) const;
    bool contains(const rt_sphererect& p) const;
    bool overlaps(const rt_rect& r) const;

    bool isEqual(const rt_sphererect& s) const;
    rt_sphererect* expand(const rt_point& p, bool preserve = true);
    rt_sphererect* expand(const rt_sphererect& s, bool preserve = true);

    void tighten();

    static int size2dim(int s) { return(((s/sizeof(double))-2)/3); }
    static int dim2size(int d) { return(((d*3)+2)*sizeof(double)); }
};

#endif // GIST_RTPRED_SR_H
