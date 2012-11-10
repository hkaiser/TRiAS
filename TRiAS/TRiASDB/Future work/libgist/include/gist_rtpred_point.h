// gist_rtpred_point.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_point.h,v 1.2 1998/09/24 05:15:54 marcel Exp $

#ifndef GIST_RTPRED_POINT_H
#define GIST_RTPRED_POINT_H

#ifdef __GNUG__
#pragma interface "gist_rtpred_point.h"
#endif

#include "gist_defs.h"		// for w_assert3()
#include "gist_rtpred.h"

class rt_point : public rt_pred {
public:
    rt_point(int d);			// preset with 0 coords
    rt_point(int d, double *coord)	// coords left as-is, can be changed
	: rt_pred(d, coord, false) {}
    rt_point(int d, const double *coord)// coords left as-is
	: rt_pred(d, (double *) coord, false) {}
    rt_point(const rt_point& pt);	// deep copy

    bool isEqual(const rt_point& p) const;

    double dist(const rt_point& pt) const;
    double dist(const rt_rect& r) const;
    static double dist_point(const void* p1, int p1Len, const rt_pred& p2);

    bool contains(const rt_point& pt) const;
    bool contains(const rt_rect& rect) const;
    static bool contains_point(const void* p1, int p1Len, const rt_pred& p2);
    static bool contains_rect(const void* p1, int p1Len, const rt_pred& p2);
    static bool contained_rect(const void* p1, int p1Len, const rt_pred& p2);

    double& co(int i) const
	{ assert(i >= 0 && i < dimension); return coord[i]; }
    
    static int size2dim(int s) { return(s/sizeof(double)); }
    static int dim2size(int d) { return(d*sizeof(double)); }
};

#endif // GIST_RTPRED_POINT_H
