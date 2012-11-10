// gist_unorderedn.h						-*- c++ -*-
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_unorderedn.h,v 1.16 1998/11/12 20:25:44 marcel Exp $

#ifndef GIST_UNORDEREDN_H
#define GIST_UNORDEREDN_H

#ifdef __GNUG__
#pragma interface "gist_unorderedn.h"
#endif

/*
 * Gist extension for unordered nodes.
 *
 * The node layout implemented here is the same as that of R-trees:
 * items are stored in arbitrary order on the page (so that all items
 * must be examined when looking for a matching one or minimum-penalty
 * item).  This class does not implement any datatype-specific
 * behavior; this is delegated to gist_unordered_ext_t (note the
 * missing 'n'), which offers an interface similar to what is
 * described in the original Gist publication.
 */

#include "gist_ext.h"		// for gist_ext_t

class gist_unordered_ext_t; // vanilla Gist extension interface

class gist_unorderedn_ext_t : public gist_ext_t {
public:

    const gist_unordered_ext_t& ext;

    virtual rc_t insert(
        gist_p& page,
	const vec_t& key,
	const vec_t& data,
	shpid_t child);

    virtual rc_t remove(
        gist_p& page,
	const int slots[],
	int numSlots);

    virtual rc_t updateKey(
        gist_p& page,
	int& slot,
	const vec_t& newKey);

    virtual void findMinPen(
        const gist_p& page,
	const vec_t& newKey,
	const vec_t& data,
	int& slot);

    virtual void search(
        gist_p& page,
	const gist_query_t* query,
	int matches[],
	int& numMatches);

    virtual void getKey(
        const gist_p& page,
	int slot,
	vec_t& key);

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

    virtual void unionBp(
        const gist_p& page,
	vec_t& bp,
	bool bpIsValid,
	const vec_t& pred1,
	const vec_t& pred2,
	bool& bpChanged);

    virtual gist_cursorext_t* queryCursor(
	const gist_query_t* query) const;

    virtual bool check(
	const vec_t& bp,
	const vec_t& pred,
	int level);

    gist_unorderedn_ext_t(
        gist_ext_t::gist_ext_ids myId,
	const char* name,
	PrintPredFct printPred,
	PrintDataFct printData,
	ParseFct parsePred,
	ParseFct parseData,
	ParseQueryFct parseQuery,
	gist_unordered_ext_t& ext);

};

#endif // ifndef GIST_UNORDEREDN_H
