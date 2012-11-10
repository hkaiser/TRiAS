// gist_rtpred_rank.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_rank.h,v 1.1 1998/06/18 00:56:54 aoki Exp $

#ifndef GIST_RTPRED_RANK_H
#define GIST_RTPRED_RANK_H

#ifdef __GNUG__
//#pragma interface "gist_rtpred_rank.h"
#endif

#include "gist_rtpred_point.h"		// for rt_point

class rt_rank : public rt_pred {
public:
    rt_rank(int d, const double* c)
	: rt_pred(d, (double*) c) {}
    rt_rank(const rt_point& p)
	: rt_pred(p.dim(), new double[1], true) { nrec() = 1; }
    rt_rank(const rt_rank& r)
	: rt_pred(r.dim(), new double[1], true) { nrec() = r.nrec(); }

    inline double& nrec() const { return(coord[0]); }

    rt_rank* expand(int n, bool preserve)
	{ nrec() = preserve ? (nrec() + n) : n; return(this); }
    rt_rank* expand(const rt_rank& r, bool preserve)
	{ nrec() = preserve ? (nrec() + r.nrec()) : r.nrec(); return(this); }

    static int size2dim(int s) { return(1); }
    static int dim2size(int d) { return(sizeof(double)); }
};

#endif // GIST_RTPRED_RANK_H
