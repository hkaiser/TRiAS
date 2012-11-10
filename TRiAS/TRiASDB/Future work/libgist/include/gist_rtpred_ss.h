// gist_rtpred_ss.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_ss.h,v 1.1 1998/06/18 00:56:59 aoki Exp $

#ifndef GIST_RTPRED_SS_H
#define GIST_RTPRED_SS_H

#ifdef __GNUG__
#pragma interface "gist_rtpred_ss.h"
#endif

#include "gist_rtpred_point.h"		// for rt_point
#include "gist_rtpred_rank.h"		// for rt_rank
#include "gist_rtpred_sphere.h"		// for rt_sphere

class rt_centroid_sphere : public rt_sphere {
private:
    void _init(const rt_point& c, double r, double n);
public:
    rt_rank rank;

    rt_centroid_sphere(const rt_point& p);
    rt_centroid_sphere(int d, const double* c)
	: rt_sphere(d, c),
	  rank(d, c + (rt_sphere::dim2size(d)/sizeof(double))) {}
    rt_centroid_sphere(const rt_centroid_sphere& s);

    bool isEqual(const rt_centroid_sphere& s) const;

    rt_centroid_sphere* expand(const rt_point& p, bool preserve = true);
    rt_centroid_sphere* expand(const rt_centroid_sphere& s, bool preserve = true);

    static int size2dim(int s) { return((s/sizeof(double))-2); }
    static int dim2size(int d) { return((d+2)*sizeof(double)); }
};

#endif // GIST_RTPRED_SS_H
