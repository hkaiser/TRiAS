// gist_sptree.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_sptree.h,v 1.3 1998/11/09 03:44:25 marcel Exp $

#ifndef GIST_SPTREE_H
#define GIST_SPTREE_H

#ifdef __GNUG__
#pragma interface "gist_sptree.h"
#endif

#include "gist_rtree.h"		// for rtbase_ext_t

/*
 * sp_ext_t:
 *
 * this class implements an sphere-tree extension as a subclass of a
 * regular R-tree (i.e., gist_unordered_ext_t).  the sphere-tree is,
 * in almost all ways, an R-tree with minimum bounding spheres instead
 * of minimum bounding rectangles.
 *
 * the sphere-tree was originally described in: P. van Oosterom and
 * E. Claassen, "Orientation Insensitive Indexing Methods for
 * Geometric Objects," Proc. 4th Symp. on Spatial Data Handling,
 * Zurich, Switzerland, July 1990, 1016-1029.
 */

class sp_ext_t : public rtbase_ext_t {
public:
    sp_ext_t(CmpFctTbl tbl, ExpandFctTbl exp, PropFctTbl pf,
	ConvFctTbl cf, BpCmpFctTbl bcf, OpTbl op)
	: rtbase_ext_t(tbl, exp, pf, cf, bcf, op) {};

    void penalty(
        const void *subtreePred,
	int predLen,
	int level,
	const void *newKey,
	int keyLen,
	gist_penalty_t &p) const {}

    // - sphere-tree minimum bounding spheres cannot (in general) be
    //   updated incrementally.  we need all of the predicates to be
    //   provided whenever the BP is computed (otherwise, the bounding
    //   sphere will not be minimal) -- we cannot avoid the overall
    //   quadratic cost.
    void union_bp(
	const gist_predcursor_t& pcursor, // in
	const gist_p& page, // in
	const vec_t& pred1, // in
	const vec_t& pred2, // in
	vec_t& bp, // in/out
	bool& bpChanged, // out
	bool bpIsValid) // in
	const {}

    void pickSplit(
        gist_predcursor_t &pcursor,
	const gist_p& page,
	int rightEntries[] /*out*/,
	int &numRightEntries /*out*/,
	const void *oldBp,
	int oldLen,
	void *leftBp /*out*/,
	int &leftLen /*in/out*/,
	void *rightBp /*out*/,
	int &rightLen /*int/out*/) const {}
};

extern gist_unorderedn_ext_t sp_point_ext;

#ifdef AMDB
extern amdb_ext_t amdb_sp_point_ext;
#endif

#endif // GIST_SPTREE_H
