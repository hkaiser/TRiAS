// gist_rtpred_rr.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_rr.h,v 1.2 1998/07/17 05:55:06 aoki Exp $

#ifndef GIST_RTPRED_RR_H
#define GIST_RTPRED_RR_H

#ifdef __GNUG__
#pragma interface "gist_rtpred_rr.h"
#endif

#include "gist_defs.h"		// for w_assert3()
#include "gist_rtpred_rect.h"	// for rt_rect
#include "gist_rtpred_rank.h"	// for rt_rank

class rt_point;

class rt_rrect : public rt_rect {
public:
    rt_rank rank;

    rt_rrect(const rt_point& p);
    rt_rrect(int d, const double* c)
	: rt_rect(d, (double*) c),
	  rank(d, (double*) (c + (rt_rect::dim2size(d)/sizeof(double)))) {}
    rt_rrect(const rt_rrect& r);

    bool isEqual(const rt_rrect& r) const;

    rt_rrect* expand(const rt_point& p, bool preserve = true);
    rt_rrect* expand(const rt_rrect& r, bool preserve = true);

    static int size2dim(int s) { return(((s/sizeof(double))-1)/2); }
    static int dim2size(int d) { return(((2*d)+1)*sizeof(double)); }
};

#endif // GIST_RTPRED_RR_H
