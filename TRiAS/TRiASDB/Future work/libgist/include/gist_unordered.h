// gist_unordered.h						-*- c++ -*-
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_unordered.h,v 1.13 1998/11/12 20:25:44 marcel Exp $


#ifndef GIST_UNORDERED_H
#define GIST_UNORDERED_H

#include "gist_p.h"		// for gist_p::max_scnt

class gist_query_t;

class gist_predcursor_t {
public:

    struct entry {
        const void *key;
	int keyLen;
    };

    // + 2: for new entries
    enum { // MSVC 5.0 doesn't allow "const int ..." here
        maxElems = gist_p::max_scnt + 2
    };
    int numElems;
    entry elems[maxElems];

    gist_predcursor_t();
    ~gist_predcursor_t(); 

    // make cursor return predicate
    void add(const void* data, int len);

    // make cursor return keys on page
    void add(const gist_p& page);

    // start from the beginning
    void reset();
};


class gist_unordered_ext_t  {
public:

    // consistent: evaluates pred w.r.t. query
    virtual bool consistent(
        const gist_query_t* query,
	const void* pred,
	int predLen,
	int level) const = 0; // at what level was that predicate found (leaf = 1)

    // returns insertion penalty of new key into subtree
    virtual void penalty(
        const void* subtreePred,
	int predLen,
	int level, // at what level was that predicate found
	const void* newKey,
	int keyLen,
	gist_penalty_t& p) const = 0;

    // union all the keys on a single page, plus up to two extra keys
    virtual void union_bp(
	const gist_predcursor_t& pcursor, // in
	const gist_p& page, // in
	const vec_t& pred1, // in
	const vec_t& pred2, // in
	vec_t& bp, // in/out
	bool& bpChanged, // out
	bool bpIsValid) // in
	const = 0;

    // Determine which entries go on the new sibling after a split
    // (the indices of the entries that should be moved right are
    // stored in rightEntries, their number in numRight; the indices
    // are returned by gist_predcursor_t::fetch() and do not have to
    // be stored in the order delivered by fetch() in rightEntries);
    // compute the new BPs for both nodes (can't do it with union,
    // because we might need to know the BP of the other sibling).
    // If the old BP is NULL, we're splitting the root; the bounds
    // should be assumed to be infinite in this case.
    virtual void pickSplit(
        gist_predcursor_t& pcursor, // used to retrieve entries for page
	const gist_p& page,
	int rightEntries[], // out: store indices of entries to go on right sibling
	int& numRightEntries, // out: store number of entries to go right
	const void* oldBp, // pre-split BP of original page
	int oldLen, // length of pre-split BP
	void* leftBp, // out: new BP of original page
	int& leftLen, // out: length of new left BP
	void* rightBp, // out: new BP of new right sibling
	int& rightLen) // out: length of new right BP
	const = 0;

    virtual gist_cursorext_t* queryCursor(
	const gist_query_t* query) const = 0;

    // Return true if the predicate is contained by the BP.
    // Used during gist_t::check() to verify the integrity of 
    // the node's content.
    virtual bool check(
        const void* bp, // BP on page
	int bplen, // length of BP
	const void* pred, // single entry's predicate
	int predlen, // length of predicate
	int level) // level of page
	const = 0;

};

#endif // GIST_UNORDERED_H
