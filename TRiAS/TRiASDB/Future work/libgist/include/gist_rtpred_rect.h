// gist_rtpred_rect.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_rect.h,v 1.1 1998/06/18 00:56:55 aoki Exp $

#ifndef GIST_RTPRED_RECT_H
#define GIST_RTPRED_RECT_H

#ifdef __GNUG__
#pragma interface "gist_rtpred_rect.h"
#endif

#include "gist_defs.h"		// for w_assert3()
#include "gist_rtpred.h"	// for rt_pred

class rt_point;

class rt_rect : public rt_pred {
public:
    rt_rect()
	: rt_pred(0, NULL, false) {}
    rt_rect(int d);			// preset with 0 coords
    rt_rect(int d, const double *coord)	// coords left as-is
	: rt_pred(d, (double *) coord, false) {};
    rt_rect(const rt_point& p);
    rt_rect(const rt_rect& r);		// deep copy

    rt_rect& operator=(const rt_rect& rhs);
    bool isEqual(const rt_rect& r) const;

    // needed for pickSplit():
    double span() const;
    double margin() const;

    inline double & lo(int i) const
	{ assert(i >= 0 && i < dimension); return coord[2*i]; }
    inline double & hi(int i) const
	{ assert(i >= 0 && i < dimension); return coord[2*i+1]; }

    // expanding this rect to include another point or rect
    rt_rect* expand(const rt_point& pt, bool preserve = true);
    rt_rect* expand(const rt_rect& rect, bool preserve = true);

    double dist(const rt_point& pt) const;
    double dist(const rt_rect& rect) const;	// currently unused
    static double dist_point(const void* p1, int p1Len, const rt_pred& p2);

    bool overlaps(const rt_rect& rect) const;
    static bool overlaps_rect(const void* p1, int p1Len, const rt_pred& p2);
    bool contains(const rt_rect& rect) const;
    bool contains(const rt_point& pt) const;
    static bool contains_point(const void* p1, int p1Len, const rt_pred& p2);
    static bool contains_rect(const void* p1, int p1Len, const rt_pred& p2);
    static bool contained_rect(const void* p1, int p1Len, const rt_pred& p2);

    // helpers:
    // returns span(intersect(rect)) without modifying anything
    double overlap(const rt_rect& rect) const;
    // returns distance from p to farthest point in rect
    double maxdist(const rt_point& p) const;

    static int size2dim(int s) { return(s/(2*sizeof(double))); }
    static int dim2size(int d) { return(d*(2*sizeof(double))); }
};

#endif // GIST_RTPRED_RECT_H
