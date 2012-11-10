// gist_rtpred.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rtpred.h,v 1.1 1998/06/18 00:56:52 aoki Exp $

#ifndef GIST_RTPRED_H
#define GIST_RTPRED_H

#ifdef __GNUG__
#pragma interface "gist_rtpred.h"
#endif

#include <stdio.h>		// for NULL

// 'rt_pred' and its descendants are just wrappers around the on-disk
// representation of the various spatial predicates.  they provide a
// class (for method invocation) as well as a place for
// commonly-needed derived metadata.  they are only generated and used
// when we need to compute on the predicates; since they are generally
// produced on-demand, and possibly repeatedly, we need to be able to
// do so efficiently.  hence, we typically provide two constructor
// interfaces: one that allocates a new chunk of memory and one that
// does not.

class rt_point;
class rt_rect;

class rt_pred {
protected:
    int dimension;	// this is the dimensionality, NOT the arity of coord[]
    double *coord;	// the on-disk representation of the spatial predicate
    bool dealloc;	// true if memory behind coord needs to be delete()'d
public:
    rt_pred(int dim, double* c = NULL, bool d = false);
    ~rt_pred();
    void clear();
    void set(double* c, bool d = false);

    // in order to perform pickSplit(), we must be able to compute the
    // volume (d-dimensional area, needed for R-tree/R*-tree) and
    // perimeter (d-1 dimensional area, needed for R*-tree).  we make
    // them virtual here to make sure that they are considered (even
    // if they are only stubbed out).
    double span() const { return(0.0); }	// XXX
    double margin() const { return(0.0); }	// XXX

    // by contrast, the spatial predicates used by consistent() and
    // minDist() are defined as needed, i.e., a given rt_arg need not
    // support any given rt_oper.
    bool isEqual(const rt_pred& p, int n) const;

    static bool alwaysTrue(const void* p1, int p1Len, const rt_pred& p2)
	{ return(true); }

    int dim() const { return(dimension); }
    double* coords() const { return(coord); }
};

#endif // GIST_RTPRED_H
