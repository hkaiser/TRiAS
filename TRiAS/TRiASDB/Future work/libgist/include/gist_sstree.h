// gist_sstree.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_sstree.h,v 1.4 2000/03/10 01:39:05 mashah Exp $

#ifndef GIST_SSTREE_H
#define GIST_SSTREE_H

#ifdef __GNUG__
#pragma interface "gist_sstree.h"
#endif

#include "gist_rtree.h"		// for rtbase_ext_t

/*
 * ss_ext_t:
 *
 * this class implements an SS-tree extension as a subclass of a
 * regular R-tree (i.e., gist_unordered_ext_t).  it does NOT implement
 * forced reinsertion.  the SS-tree is a point access method (only).
 *
 * the SS-tree was originally described in: D. A. White and R. Jain,
 * "Similarity Indexing with the SS-tree," Proc. 12th Int'l Conf. on
 * Data Engineering, New Orleans, LA, Feb. 1996, 516-523.
 *
 * XXX we should probably call this 'rtvar_ext_t' since it really
 * represents the family of point-only trees that split based on the
 * dimensional variance.
 */

class ss_ext_t : public rtbase_ext_t {
public:

	// VCPORT_B
    static const float MINSPLITUTIL;
	// VCPORT_E

    typedef rt_pred* (*PointFct)(rt_pred* pred, const void* item, int len);
    typedef PointFct CenterFctTbl[numLvl];
    CenterFctTbl centerFcts;	// returns center of key/bp

    ss_ext_t(CmpFctTbl tbl, ExpandFctTbl exp, PropFctTbl pf,
	ConvFctTbl cf, BpCmpFctTbl bcf, OpTbl op, CenterFctTbl cenf);

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
	int &rightLen /*int/out*/) const;
};

extern gist_unorderedn_ext_t ss_point_ext;

#ifdef AMDB
extern amdb_ext_t amdb_ss_point_ext;
#endif

#endif // GIST_SSTREE_H
