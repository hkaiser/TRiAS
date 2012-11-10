// gist_srtree.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_srtree.h,v 1.3 1998/11/09 03:44:26 marcel Exp $

#ifndef GIST_SRTREE_H
#define GIST_SRTREE_H

#ifdef __GNUG__
#pragma interface "gist_srtree.h"
#endif

#include "gist_sstree.h"		// for ss_ext_t

/*
 * sr_ext_t:
 *
 * this class implements an SR-tree extension as a subclass of a
 * regular R-tree (i.e., gist_unordered_ext_t).  it does NOT implement
 * forced reinsertion.  it is derived from the SS-tree and, like the
 * SS-tree, is a point access method (only).
 *
 * the SR-tree was originally described in: N. Katayama and S. Satoh,
 * "The SR-tree: An Index Structure for High-Dimensional Nearest
 * Neighbor Queries," Proc. 1997 ACM-SIGMOD Conf. on Management of
 * Data, Tucson, AZ, May 1997, 369-380.
*/

class sr_ext_t : public ss_ext_t {
public:
    sr_ext_t(CmpFctTbl tbl, ExpandFctTbl exp, PropFctTbl pf,
	ConvFctTbl cf, BpCmpFctTbl bcf, OpTbl op, CenterFctTbl cenf)
	: ss_ext_t(tbl, exp, pf, cf, bcf, op, cenf) {};

    void penalty(
        const void *subtreePred,
	int predLen,
	int level,
	const void *newKey,
	int keyLen,
	gist_penalty_t &p) const;

    void union_bp(
	const gist_predcursor_t& pcursor,	// in
	const gist_p& page,			// in
	const vec_t& pred1,			// in
	const vec_t& pred2,			// in
	vec_t& bp,				// in/out
	bool& bpChanged,			// out
	bool bpIsValid)				// in
	const;
};

extern gist_unorderedn_ext_t sr_point_ext;

#ifdef AMDB
extern amdb_ext_t amdb_sr_point_ext;
#endif

#endif // GIST_SRTREE_H
