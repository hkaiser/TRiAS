// gist_rstartree.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rstartree.h,v 1.9 2000/03/10 01:39:04 mashah Exp $

#ifdef __GNUG__
#pragma interface "gist_rstartree.h"
#endif

#ifndef GIST_RSTARTREE_H
#define GIST_RSTARTREE_H

#include "gist_rtpred_rect.h"		// for rt_rect
#include "gist_rtree.h"
#ifdef AMDB
#include "amdb_ext.h"
#endif

/*
 * rstar_ext_t:
 *
 * This class implements an R*-tree extension as a subclass of a regular
 * R-tree. For R*-trees, the extension routines findMinPen() and pickSplit()
 * need to be changed. 
 */

class rstar_ext_t : public gist_unorderedn_ext_t {

protected:

	// VCPORT_B
    // # of entries involved in overlap computation during findMinPen
	static const int MINPENENTRIES;

    // minimum page utilization after split (according to R*-tree paper)
    static const float MINSPLITUTIL;
	// VCPORT_E

    // holds area enlargement and slot index of item (for findMinPen)
    struct MinPenAux {
	gist_penalty_t p;
	int slot;
    };

    // info we compute for each dimension when choosing a split dimension
    struct DimInfo {
        int splitPoint; // index of first element in sortArray to go right
	rt_rect leftBr; // left BR of optimum split
	rt_rect rightBr; // right BR of optimum split
    };

    // used by pickSplit to sort entries on lower/upper value along single dimension
    struct SplitAux {
	int slot;
	double lo;
	double hi;

	void init(int slot, const double* val, int dims, int dim, bool isPoint);
    };

    // temporary storage used during findMinPen and pickSplit;
    // allocated here so we needn't do it repeatedly during insertions

	// VCPORT_B
    struct tempStorage {
        MinPenAux penalties[gist_p::max_slot];
	DimInfo dimInfo[gist_p::max_tup_sz/sizeof(double)];
	SplitAux sortArray[gist_p::max_slot];
    } temps;
	// VCPORT_E

    // for qsort
    static int splitAuxCmp(const void* a, const void* b);
    static int minPenAuxCmp(const void* a, const void* b);

    // set single element in array of SplitAux
    void loadSortArray(
	SplitAux& e,
	int slot,
	const double* val,
	int dims,
	int dim,
	bool isPoint);

    // initialize BR r with coords, converting point coords to a rectangle
    void initialBr(
        rt_rect& r,
        bool isPoint,
	const double* coords);

    // extract key and key length of entry in  'slot' ('slot' could mean entry1 or -2)
    void getKey(
	int slot,
	const gist_p& page,
	const vec_t& entry1,
	const vec_t& entry2,
	void*& key,
	int& klen);

    void computeOverlapEnlargement(
        int slot,
	const vec_t& newKey,
	const gist_p& page,
	double& overlap);

public:

    virtual void findMinPen(
        const gist_p& page,
	const vec_t& newKey,
	const vec_t& data,
	int& slot);

    virtual rc_t pickSplit(
        gist_p& page,
	int rightEntries[],
	int& numRight,
	const vec_t& oldBp,
	vec_t& leftBp,
	vec_t& rightBp,
	const vec_t& entry1,
	bool& oneGoesRight,
	const vec_t& entry2,
	bool& twoGoesRight);


    rstar_ext_t(
        gist_ext_t::gist_ext_ids myId,
	const char* name,
	PrintPredFct printPred,
	PrintDataFct printData,
	ParseFct parsePred,
	ParseFct parseData,
	ParseQueryFct parseQuery,
	rt_ext_t& ext); // same gist_unordered_t that is used for R-trees

    virtual ~rstar_ext_t() {} // declared virtual so g++ won't complain
};

extern rstar_ext_t rstar_point_ext;
extern rstar_ext_t rstar_rect_ext;

#ifdef AMDB
extern amdb_ext_t amdb_rstar_point_ext;
extern amdb_ext_t amdb_rstar_rect_ext;
#endif

#endif // GIST_RSTARTREE_H
