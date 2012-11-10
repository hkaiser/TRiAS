// gist_rtpred_rr.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred_rr.cc,v 1.3 1998/09/24 05:22:08 marcel Exp $

#ifdef __GNUG__
#pragma implementation "gist_rtpred_rr.h"
#endif

#include "gist_rtpred_rr.h"

rt_rrect::rt_rrect(const rt_point& p)
    : rt_rect(p.dim(),
	new double[rt_rrect::dim2size(p.dim())/sizeof(double)]),
      rank(p.dim(), coord + (rt_rect::dim2size(p.dim())/sizeof(double)))
{
    dealloc = true;
    for (int i = 0; i < dimension; i++) {
        hi(i) = lo(i) = p.co(i);
    }
    rank.nrec() = 1;
}

rt_rrect::rt_rrect(const rt_rrect& r)
    : rt_rect(r.dim(),
	new double[rt_rrect::dim2size(r.dim())/sizeof(double)]),
      rank(r.dim(), coord + (rt_rect::dim2size(r.dim())/sizeof(double)))
{
    dealloc = true;
    for (int i = 0; i < dimension; i++) {
        lo(i) = r.lo(i);
        hi(i) = r.hi(i);
    }
    rank.nrec() = r.rank.nrec();
}

bool 
rt_rrect::isEqual(const rt_rrect& r) const
{
    // just compare the coordinate array.
    return(((rt_pred*) this)->isEqual(r, 2 * dimension + 1));
}

rt_rrect*
rt_rrect::expand(const rt_point& p, bool preserve)
{
    assert(dimension == p.dim());

    (void) rt_rect::expand(p, preserve);
    (void) rank.expand(1, preserve);

    return(this);
}

rt_rrect*
rt_rrect::expand(const rt_rrect& r, bool preserve)
{
    assert(dimension == r.dim());
    
    (void) rt_rect::expand(r, preserve);
    (void) rank.expand(r.rank, preserve);

    return(this);
}
