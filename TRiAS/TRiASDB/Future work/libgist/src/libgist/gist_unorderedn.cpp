// gist_unorderedn.cc
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_unorderedn.cc,v 1.22 2000/03/15 00:24:26 mashah Exp $

#ifdef __GNUG__
#pragma implementation "gist_unorderedn.h"
#endif

#include <stdlib.h>

// VCPORT_B
#ifdef WIN32
#include <iostream>

using namespace std;
#else
#include <iostream.h>
#endif
// VCPORT_E

#include "gist_unorderedn.h"
#include "gist_unordered.h"

rc_t
gist_unorderedn_ext_t::insert(
    gist_p& page,
    const vec_t& key,
    const vec_t& data,
    shpid_t child)
{
    return (page.insert(key, data, page.nrecs(), child));
}

static int
intCmp(
    const void*		a,
    const void*		b)
{
    return *((int *) a) - *((int *) b);
}


rc_t
gist_unorderedn_ext_t::remove(
    gist_p& page,
    const int slots[],
    int numSlots)
{
    qsort((void *) slots, numSlots, sizeof(int), intCmp);
    for (int i = numSlots-1; i >= 0; i--) {
        W_DO(page.remove(slots[i]));
    }
    return RCOK;
}

rc_t
gist_unorderedn_ext_t::updateKey(
    gist_p& page,
    int& slot,
    const vec_t& newKey)
{
    const keyrec_t& tup = page.rec(slot);

    // make sure we have enough space (or: the key might have shrunk)
    int need = align(newKey.len(0) + sizeof(keyrec_t)) - 
        align(page.rec_size(slot));
    if (need > 0 && (unsigned) need > page.usable_space()) {
        return (eRECWONTFIT);
    }

    // update item
    shpid_t child = tup.child();
    W_DO(page.remove(slot));
    rc_t status = page.insert(newKey, cvec_t(), slot, child);
    assert(status != eRECWONTFIT);
    return (status);
}

void
gist_unorderedn_ext_t::findMinPen(
    const gist_p& page,
    const vec_t& newKey,
    const vec_t& data,
    int& slot)
{
    int count = page.nrecs();
    gist_penalty_t min_penalty(gist_penalty_t::max_penalty);
    gist_penalty_t penalty;

    // loop through all the entries
    for (int i = 0; i < count; i++) {
	const keyrec_t &tup = page.rec(i);
        ext.penalty((void *) tup.key(), tup.klen(), page.level(), newKey.ptr(0),
	    newKey.len(0), penalty);
	if (penalty < min_penalty) {
	    slot = i;
	    min_penalty = penalty;
	}
    }
}

void
gist_unorderedn_ext_t::search(
    gist_p& page,
    const gist_query_t* query,
    int matches[],
    int& numMatches)
{
    numMatches = 0;
    int count = page.nrecs();

    for (int i = 0; i < count; i++) {
        const keyrec_t &tup = page.rec(i);
	if (ext.consistent(query, tup.key(), tup.klen(), page.level())) {
	    // we have a matching entry; push it on the stack
	    matches[numMatches] = i;
	    numMatches++;
	}
    }
}

void
gist_unorderedn_ext_t::getKey(
    const gist_p& page,
    int slot,
    vec_t& key)
{
    const keyrec_t& tup = page.rec(slot);
    key.set(tup.key(), tup.klen());
}

rc_t
gist_unorderedn_ext_t::pickSplit(
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
    gist_predcursor_t pcursor;
    pcursor.add(page);

    // 'pcursor' also contains the new entry/entries (i.e., the one(s)
    // that caused the split but have not yet been inserted).  these
    // are given special "slots" that are off the end of the actual
    // slot array.
    if (entry1.size() != 0) {
	pcursor.add(entry1.ptr(0), entry1.len(0));
    }
    if (entry2.size() != 0) {
	pcursor.add(entry2.ptr(0), entry2.len(0));
    }
    int entry1Pos = page.nrecs();
    int entry2Pos = entry1Pos + 1;

    int leftLen, rightLen;
    ext.pickSplit(pcursor, page, rightEntries, numRight,
        oldBp.ptr(0), oldBp.len(0), leftBp.ptr(0), leftLen, rightBp.ptr(0), rightLen);

    // fix up left/rightBp
    const void* keyptr = leftBp.ptr(0);
    leftBp.set(keyptr, leftLen);
    keyptr = rightBp.ptr(0);
    rightBp.set(keyptr, rightLen);

    // find out where the new items (entry1 and entry2) go and clean
    // up the slot array (we must not return the "slot indices" of
    // entry1/entry2)
    oneGoesRight = twoGoesRight = false;
	int i;
    for (i = 0; i < numRight; i++) {
        if (rightEntries[i] == entry1Pos || rightEntries[i] == entry2Pos) {
	    if (rightEntries[i] == entry1Pos) {
		oneGoesRight = true;
	    } else {
		twoGoesRight = true;
	    }
	    // compress rightEntries
	    for (int j = i; j < numRight-1; j++) {
	        rightEntries[j] = rightEntries[j+1];
	    }
	    i--; // rightEntries[i] was overwritten by an unseen slot
	    numRight--;
	}
    }
#ifndef NDEBUG
    for (i = 0; i < numRight; ++i) {
	assert(rightEntries[i] != entry1Pos);
	assert(rightEntries[i] != entry2Pos);
	assert(rightEntries[i] >= 0 && rightEntries[i] < page.nrecs());
    }
#endif
    return RCOK;
}

void
gist_unorderedn_ext_t::unionBp(
    const gist_p& page,
    vec_t& bp,
    bool bpIsValid,
    const vec_t& pred1,
    const vec_t& pred2,
    bool& bpChanged)
{
    gist_predcursor_t pcursor;
    pcursor.add(page);
    ext.union_bp(pcursor, page, pred1, pred2, bp, bpChanged, bpIsValid);
}

gist_cursorext_t*
gist_unorderedn_ext_t::queryCursor(
    const gist_query_t* query) const
{
    return ext.queryCursor(query);
}

bool
gist_unorderedn_ext_t::check(
    const vec_t& bp,
    const vec_t& pred,
    int level)
{
    return ext.check(bp.ptr(0), bp.len(0), pred.ptr(0), pred.len(0), level);
}
        
gist_unorderedn_ext_t::gist_unorderedn_ext_t(
    gist_ext_t::gist_ext_ids id,
    const char* name,
    PrintPredFct printPred,
    PrintDataFct printData,
    ParseFct parsePred,
    ParseFct parseData,
    ParseQueryFct parseQuery,
    gist_unordered_ext_t& ext) :
    gist_ext_t(id, name, printPred, printData, parsePred, parseData, parseQuery),
    ext(ext)
{
    gist_ext_t::gist_ext_list[myId] = this;
}
