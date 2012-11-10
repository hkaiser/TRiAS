// gist_rstartree.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_rstartree.cc,v 1.19 2000/03/15 00:24:51 mashah Exp $

#ifdef __GNUG__
#pragma implementation "gist_rstartree.h"
#endif

#include <stdlib.h>

#include "gist_compat.h"	// for MAXDOUBLE
#include "gist_rtpred_point.h"
#include "gist_rstartree.h"
#include "gist_support.h" // for print<>, parse<>, etc.


// VCPORT_B
// # of entries involved in overlap computation during findMinPen
const int rstar_ext_t::MINPENENTRIES = 16;

// minimum page utilization after split (according to R*-tree paper)
const float rstar_ext_t::MINSPLITUTIL = float(0.4);
// VCPORT_E

/////////////////////////////////////////////////////////////////////////
// rstar_ext_t::minPenAuxCmp - qsort comparison fct for MinPenAux
//
// Description:
//	- comparison of the penalty component in MinPenAux to sort
//	  in ascending order
//
// Return Values:
//      -1, 0, 1
/////////////////////////////////////////////////////////////////////////

int
rstar_ext_t::minPenAuxCmp(const void* a, const void* b)
{
    MinPenAux* e1 = (MinPenAux *) a;
    MinPenAux* e2 = (MinPenAux *) b;

    if (e1->p < e2->p) {
        return -1;
    } else if (e2->p < e1->p) {
        return 1;
    } else {
        return 0;
    }
}


/////////////////////////////////////////////////////////////////////////
// rstar_ext_t::findMinPen - min. penalty computation
//
// Description:
// 	- level > 2: entry with min. area enlargement (min. area for ties)
// 	- level = 2: entry with min overlap enlargement
// 	  (enlargement of overlap with other nodes on that page),
//	  min area enlargement for ties. Since the latter is O(n^2), we approximate
//	  it by only computing the overlap for the best 32 entries (best in terms of
//	  area enlargement)
//
/////////////////////////////////////////////////////////////////////////

void
rstar_ext_t::findMinPen(
    const gist_p& page,
    const vec_t& newKey,
    const vec_t& data,
    int& slot)
{
    int count = page.nrecs();

    // loop through all the entries and compute the area enlargements
    for (int i = 0; i < count; i++) {
	const keyrec_t &tup = page.rec(i);
	ext.penalty((void *) tup.key(), tup.klen(), page.level(), newKey.ptr(0),
	    newKey.len(0), temps.penalties[i].p);
	temps.penalties[i].slot = i;
    }

    // sort area enlargements
    qsort(temps.penalties, count, sizeof(MinPenAux), minPenAuxCmp);

    if (page.level() > 2) {
        // pick item with min. area enlargement, min. area
	gist_penalty_t minPenalty(gist_penalty_t::max_penalty);
	double minArea = 0.0;
	slot = -1;

	for (int i = 0; i < count; i++) {
	    const keyrec_t& tup = page.rec(temps.penalties[i].slot);
	    rt_rect br(rt_rect::size2dim(tup.klen()), (const double *) tup.key());

	    if (temps.penalties[i].p < minPenalty) {
		minPenalty = temps.penalties[i].p;
		minArea = br.span();
	        slot = temps.penalties[i].slot;
	    } else if (temps.penalties[i].p == minPenalty) {
		if (br.span() < minArea) {
		    minArea = br.span();
		    slot = temps.penalties[i].slot;
		}
	    } else {
	        // minPenalty < temps.penalties[i].p: we're done
		assert(slot != -1);
		break;
	    } 
	}

    } else {
        assert(page.level() == 2);
	// pick item with min overlap enlargement, min area enlargement among
	// the best 32 entries in terms of area enlargement

	double minOverlapEnlargement = MAXDOUBLE; // min overlap enlargement
	gist_penalty_t minAreaEnlargement(gist_penalty_t::max_penalty);
	double overlapEnlargement;
	
	for (int i = 0; i < count && i < MINPENENTRIES; i++) {
	    const keyrec_t& tup = page.rec(temps.penalties[i].slot);
	    rt_rect br(rt_rect::size2dim(tup.klen()), (const double *) tup.key());

	    computeOverlapEnlargement(temps.penalties[i].slot, newKey, page,
	        overlapEnlargement);
	    if (overlapEnlargement <= minOverlapEnlargement) {
		gist_penalty_t pen;
		// compute area enlargement
		ext.penalty((void *) tup.key(), tup.klen(), page.level(), newKey.ptr(0),
		    newKey.len(0), pen);
	        if (overlapEnlargement == minOverlapEnlargement &&
		    pen >= minAreaEnlargement) {

		    continue;
		}

		minOverlapEnlargement = overlapEnlargement;
		minAreaEnlargement = pen;
		slot = temps.penalties[i].slot;
	    }
	}

    }
    return;
}


/////////////////////////////////////////////////////////////////////////
// rstar_ext_t::computeOverlapEnlargement - betw. enlarged BR and remaining BRs
//
// Description:
// 	- iterates through all BRs on page, computing enlargement of overlap
//	  with expanded target BR
//
/////////////////////////////////////////////////////////////////////////

void
rstar_ext_t::computeOverlapEnlargement(
    int slot,
    const vec_t& newKey,
    const gist_p& page,
    double& overlapEnlargement)
{
    // compute enlarged rect
    const keyrec_t& tup = page.rec(slot);
    rt_rect preBr(rt_rect::size2dim(tup.klen()), (const double *) tup.key());
    rt_rect postBr(preBr); // make a copy, so we don't overwrite data on the page
    (*((rt_ext_t&) ext).expandFcts[0])(&postBr, newKey.ptr(0), newKey.len(0), true);

    int recCnt = page.nrecs();
    overlapEnlargement = 0.0;
    int i;
    for (i = 0; i < recCnt; i++) {
	if (i != slot) {
	    // extract rect
	    const keyrec_t& t = page.rec(i);
	    rt_rect rect(rt_rect::size2dim(t.klen()), (const double *) t.key());
	    overlapEnlargement += rect.overlap(postBr) - rect.overlap(preBr);
	}
    }
}


/////////////////////////////////////////////////////////////////////////
// rstar_ext_t::splitAuxCmp - qsort comparison fct for SplitAux
//
// Description:
//	- sorts in ascending order, first on lo, then hi
//
// Return Values:
//      -1, 0, 1
/////////////////////////////////////////////////////////////////////////

int
rstar_ext_t::splitAuxCmp(const void* a, const void* b)
{
    const SplitAux* e1 = (const SplitAux *) a;
    const SplitAux* e2 = (const SplitAux *) b;

    if (e1->lo < e2->lo) {
        return -1;
    } else if (e1->lo == e2->lo) {
        if (e1->hi < e2->hi) {
	    return -1;
	} else if (e1->hi == e2->hi) {
	    return 0;
	} else {
	    return 1;
	}
    } else {
        return 1;
    }
}


/////////////////////////////////////////////////////////////////////////
// rstar_ext_t::SplitAux::init - initialize SplitAux 
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

void
rstar_ext_t::SplitAux::init(
    int slot,
    const double* val,
    int dims,
    int dim,
    bool isPoint)
{
    this->slot = slot;
    if (isPoint) {
	rt_point pt(dims, val);
	this->lo = pt.co(dim);
	this->hi = pt.co(dim);
    } else {
	rt_rect rect(dims, val);
	this->lo = rect.lo(dim);
	this->hi = rect.hi(dim);
    }
}


/////////////////////////////////////////////////////////////////////////
// rstar_ext_t::initalBr - initialize BR with single page entry
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

void
rstar_ext_t::initialBr(
    rt_rect& r,
    bool isPoint,
    const double* coords)
{
    int dims = r.dim();
    for (int i = 0; i < dims; i++) {
	if (isPoint) {
	    r.lo(i) = r.hi(i) = coords[i];
	} else {
	    r.lo(i) = coords[2*i];
	    r.hi(i) = coords[2*i+1];
	}
    }
}


/////////////////////////////////////////////////////////////////////////
// rstar_ext_t::getKey - fetches key from page or new entries
//
// Description:
//	- if slot < page.nrecs(), fetches key from page, otherwise
//	  from entry1 (slot == page.nrecs()) or entry2 (slot == page.nrecs()+1)
//
/////////////////////////////////////////////////////////////////////////

void
rstar_ext_t::getKey(
    int slot,
    const gist_p& page,
    const vec_t& entry1,
    const vec_t& entry2,
    void*& key,
    int& klen)
{
    int recCnt = page.nrecs();
    if (slot < recCnt) {
	// key to union with comes from page
	const keyrec_t& tup = page.rec(slot);
	key = (void *) tup.key();
	klen = tup.klen();
    } else if (slot == recCnt) {
        // union with key of entry 1
	key = entry1.ptr(0);
	klen = entry1.len(0);
    } else {
        // union with key of entry 2
	key = entry2.ptr(0);
	klen = entry2.len(0);
    }
}


/////////////////////////////////////////////////////////////////////////
// rstar_ext_t::pickSplit - compute split info
//
// Description:
// 	- split page as described in R*-tree paper: sort rectangles along axes,
//	  choose split axis to minimize margin, distribute entries to minimize overlap
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
rstar_ext_t::pickSplit(
    gist_p& page,
    int rightEntries[],
    int& numRight,
    const vec_t& oldBp,
    vec_t& leftBp,
    vec_t& rightBp,
    const vec_t& entry1,
    bool& oneGoesRight,
    const vec_t& entry2,
    bool& twoGoesRight)
{
    rt_ext_t& rtext = (rt_ext_t&) ext;

    // find split axis:
    // along each axis, first sort entries (on lo, hi), then compute sum of 
    // all possible distributions' margin (a distribution of items onto 2 pages 
    // must assign at least MINSPLITUTIL of the entries to each page)
    int dims;
    int numEntries = -1; // total # of entries, including entry1/-2
    bool isPoint; // true if point data, false for rectangles on page
    assert(page.nrecs() > 0); // shouldn't try to split empty page anyway
    const keyrec_t& tup = page.rec(0); // we need this to find the data's dimension
    if (page.level() == 1) {
	// we're at a leaf and need to find the data-specific dimension
        dims = (*rtext.convFcts[0][rt_ext_t::rt_dim])(tup.klen());
	isPoint = (rt_point::dim2size(dims) == (int) tup.klen()) ? true : false;
    } else {
	// non-leaf data can only be rectangles, which are stored as 2xdim doubles
	dims = rt_rect::size2dim(tup.klen());
        isPoint = false;
    }

    int recCnt = page.nrecs();
    double minMargin = MAXDOUBLE; // min. margin seen so far across dimension
    int minDim = -1; // dimension with minimum avg margin
    for (int dim = 0; dim < dims; dim++) {
	// load sorting array with page entries and newly inserted entry/entries
        for (int i = 0; i < recCnt; i++) {
	    const keyrec_t& tup = page.rec(i);
	    temps.sortArray[i].init(i, (const double *) tup.key(),
	        dims, dim, isPoint);
	}
	numEntries = recCnt;
	// entry1
	if (entry1.size() != 0) {
	    temps.sortArray[numEntries].init(numEntries,
	        (const double *) entry1.ptr(0), dims, dim, isPoint);
	    numEntries++;
	}
	// entry2
	if (entry2.size() != 0) {
	    temps.sortArray[numEntries].init(numEntries,
	        (const double *) entry2.ptr(0), dims, dim, isPoint);
	    numEntries++;
	}

	// sort
	qsort(temps.sortArray, numEntries, sizeof(SplitAux), splitAuxCmp);

	// compute margins of BRs of possible distributions:
	// compute BRs of left node incrementally (add in next item), compute BRs of 
	// right node from scratch for every possible distribution (can't do it 
	// incrementally, because we're removing items from the 'right node');
	// also compute optimal split point for later on (minimizes overlap between nodes)
	int minEntries = (int) ((double) numEntries * MINSPLITUTIL);
	double totalMargin = 0.0;
	void* key;
	int klen;

	// the left BR contains at least the first key of the sort array
	rt_rect leftBr(dims);
	getKey(temps.sortArray[0].slot, page, entry1, entry2, key, klen);
	initialBr(leftBr, isPoint, (const double *) key);

	rt_rect rightBr(dims);
	bool dummy;
	gist_predcursor_t dummyPcursor; // leave it empty, it's not needed
	double minOverlap = MAXDOUBLE;
	double combinedSpan = 0.0; // total area of both BRs, breaks ties for split point
	int brSize = rt_rect::dim2size(dims);
	for (int leftEntries = 2; leftEntries <= numEntries - minEntries; leftEntries++) {
	    // accumulate BR for left node
	    getKey(temps.sortArray[leftEntries-1].slot, page, entry1, entry2, key, klen);
	    vec_t tmpKeyLeft(key, klen);
	    vec_t tmpBpLeft(leftBr.coords(), brSize);
	    rtext.union_bp(dummyPcursor, page, tmpKeyLeft, vec_t(), tmpBpLeft, dummy, true);

	    if (leftEntries >= minEntries) {
	        // this is a legal distribution
	
		// compute the right node's BR
		getKey(temps.sortArray[leftEntries].slot, page, entry1, entry2, key, klen);
		initialBr(rightBr, isPoint, (const double *) key);
		for (int i = leftEntries + 1; i < numEntries; i++) {
		    getKey(temps.sortArray[i].slot, page, entry1, entry2, key, klen);
		    vec_t tmpKeyRight(key, klen);
		    vec_t tmpBpRight(rightBr.coords(), brSize);
		    rtext.union_bp(dummyPcursor, page, tmpKeyRight, vec_t(), tmpBpRight,
		        dummy, true);
		}

		// accumulate margins
		totalMargin += leftBr.margin() + rightBr.margin();

		// check if this would be a good split point
		double overlap = leftBr.overlap(rightBr);
		double span = leftBr.span() + rightBr.span();
		if (overlap < minOverlap || (overlap == minOverlap && span < combinedSpan)) {
		    // found a better split point
		    temps.dimInfo[dim].splitPoint = leftEntries;
		    temps.dimInfo[dim].leftBr = leftBr;
		    temps.dimInfo[dim].rightBr = rightBr;
		    minOverlap = overlap;
		    combinedSpan = leftBr.span() + rightBr.span();
		}
	    }
	}
	if (totalMargin < minMargin) {
	    // we found a better split axis
	    minMargin = totalMargin;
	    minDim = dim;
	}
    }

    // We now have an optimal split axis (minDim) and a split point
    // (temps.dimInfo[minDim].splitPoint) perpendicular to the split axis that
    // minimizes the amount of overlap between the two nodes. Sort the node
    // entries again along the split axis.
	int i;
    for (i = 0; i < recCnt; i++) {
	const keyrec_t& tup = page.rec(i);
	temps.sortArray[i].init(i, (const double *) tup.key(), dims, minDim, isPoint);
    }
    // entry1
    if (entry1.size() != 0) {
	temps.sortArray[recCnt].init(recCnt, (const double *) entry1.ptr(0),
	    dims, minDim, isPoint);
    }
    // entry2
    if (entry2.size() != 0) {
	temps.sortArray[recCnt+1].init(recCnt+1,
	    (const double *) entry2.ptr(0), dims, minDim, isPoint);
    }
    qsort(temps.sortArray, numEntries, sizeof(SplitAux), splitAuxCmp);

    // copy the BRs, distribute the entries and assign positions for entry1/-2
    (void) memcpy(leftBp.ptr(0), temps.dimInfo[minDim].leftBr.coords(),
	rt_rect::dim2size(dims));
    leftBp.set(leftBp.ptr(0), rt_rect::dim2size(dims));
    (void) memcpy(rightBp.ptr(0), temps.dimInfo[minDim].rightBr.coords(),
	rt_rect::dim2size(dims));
    rightBp.set(rightBp.ptr(0), rt_rect::dim2size(dims));
    numRight = 0;
    oneGoesRight = twoGoesRight = false;
    for (i = temps.dimInfo[minDim].splitPoint; i < numEntries; i++) {
        if (temps.sortArray[i].slot < recCnt) {
	    rightEntries[numRight] = temps.sortArray[i].slot;
	    numRight++;
	} else if (temps.sortArray[i].slot == recCnt) {
	    // this is entry1
	    oneGoesRight = true;
	} else {
	    // this is entry2
	    twoGoesRight = true;
	}
    }

    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// rstar_ext_t::rstar_ext_t - constructor
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

rstar_ext_t::rstar_ext_t(
    gist_ext_t::gist_ext_ids id,
    const char* name,
    PrintPredFct printPred,
    PrintDataFct printData,
    ParseFct parsePred,
    ParseFct parseData,
    ParseQueryFct parseQuery,
    rt_ext_t& ext) :
    gist_unorderedn_ext_t(id, name, printPred, printData, parsePred, parseData,
        parseQuery, ext)
{
}

rstar_ext_t rstar_point_ext(gist_ext_t::rstar_point_ext_id,
    "rstar_point_ext", gist_support::printPtRtPred, gist_support::printInt,
    gist_support::parsePoint, gist_support::parseInt, gist_support::parseGeoQuery,
    point_ext);
rstar_ext_t rstar_rect_ext(gist_ext_t::rstar_rect_ext_id,
    "rstar_rect_ext", gist_support::printRectRtPred, gist_support::printInt,
    gist_support::parseRect, gist_support::parseInt, gist_support::parseGeoQuery,
    rect_ext);
