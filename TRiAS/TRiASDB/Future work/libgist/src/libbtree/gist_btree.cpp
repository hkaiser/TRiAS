// gist_btree.cc
// Copyright (c) 1997, 1998, Regents of the University of California
// $Id: gist_btree.cc,v 1.28 2000/03/15 00:24:09 mashah Exp $

#ifdef __GNUG__
#pragma implementation "gist_btree.h"
#endif

#include <string.h>
#include <stdlib.h>

// VCPORT_B
#ifdef WIN32
#include <iostream>

using namespace std;
#else
#include <iostream.h>
#endif
// VCPORT_E

#include "gist_compat.h"	// for MAXINT/MININT
#include "gist_btree.h"
#include "gist_cursorext.h"	// for gist_cursorext_t::*
#include "gist_support.h"	// for print<>, parse<>, etc.
#include <assert.h>

bt_query_t::bt_query_t(bt_oper oper, void *val1, void *val2)
    : oper(oper), val1(val1), val2(val2)
{
}

bt_query_t::~bt_query_t()
{
    if (val1 != NULL) delete val1;
    if (val2 != NULL) delete val2;
}

static int
int_cmp(const void *a, const void *b)
{
    // can't simply copy ints, alignment might be wrong
    int x, y;
    (void) memcpy((void *) &x, a, sizeof(x));
    (void) memcpy((void *) &y, b, sizeof(y));
    if (x < y) { 
        return -1;
    } else if (x > y) {
        return 1;
    } else {
        return 0;
    }
    // this doesn't work when a is close to -2^31
    //int res = (*((int *) a) - *((int *) b));
}

static int
double_cmp(const void *a, const void *b)
{
    double x = *((double *) a);
    double y = *((double *) b);
    if (x < y) {
        return -1;
    } else if (x > y) {
        return 1;
    } else {
        return 0;
    }
}

static int
str_cmp(const void *a, const void *b)
{
    return (strcmp((const char *) a, (const char *) b));
}


///////////////////////////////////////////////////////////////////////////////
// gist_btree::gist_btree - constructor
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

bt_ext_t::bt_ext_t(
    gist_ext_t::gist_ext_ids id,
    const char* name,
    PrintPredFct printPred,
    PrintDataFct printData,
    ParseFct parsePred,
    ParseFct parseData,
    ParseQueryFct parseQuery,
    CmpFct keyCmp,
    CmpFct dataCmp,
    SizeFct keySize,
    SizeFct dataSize,
    NegInftyFct negInftyKey,
    NegInftyFct negInftyData) :
    gist_ext_t(id, name, printPred, printData, parsePred, parseData, parseQuery),
    keyCmp(keyCmp), dataCmp(dataCmp), keySize(keySize),
    dataSize(dataSize), negInftyKey(negInftyKey), negInftyData(negInftyData)
{
};


///////////////////////////////////////////////////////////////////////////////
// gist_btree::insert - insert new entry in sort order
//
// Description:
//	- insert after rightmost slot with item <= (key, data)
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t
bt_ext_t::insert(
    gist_p& page,
    const vec_t& key,
    const vec_t& dataPtr,
    shpid_t child)
{
    const void* data;
    if (page.is_leaf()) {
        data = dataPtr.ptr(0);
    } else {
        // by convention, our key also contains a data pointer (to
        // make the internal node keys unique); we don't want to use
        // this during _binSearch(), so we 'skip' over it.
	data = (const void *) (((char *) key.ptr(0)) + this->keySize(key.ptr(0)));
    }
    int slot = _binSearch(page, key.ptr(0), data, false);
    W_DO(page.insert(key, dataPtr, slot + 1, child));
    return RCOK;
}


///////////////////////////////////////////////////////////////////////////////
// gist_btree::remove - remove number of slots
//
// Description:
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t 
bt_ext_t::remove(
    gist_p& page,
    const int slots[],
    int numSlots)
{
    for (int i = numSlots - 1; i >= 0; i--) {
        W_DO(page.remove(slots[i]));
    }
    return RCOK;
}


///////////////////////////////////////////////////////////////////////////////
// gist_btree::updateKey - nothing to do
//
// Description:
//	- B-tree partitions the data space, no BPs to update 
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t
bt_ext_t::updateKey(
    gist_p& page,
    int& slot,
    const vec_t& newKey)
{
    return RCOK;
}


///////////////////////////////////////////////////////////////////////////////
// gist_btree::findMinPen - return insertion subtree of (key, data)
//
// Description:
//	- return slof of rightmost item that is <= (key, data)
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

void
bt_ext_t::findMinPen(
    const gist_p& page,
    const vec_t& key,
    const vec_t& data,
    int& slot)
{
    slot = _binSearch(page, key.ptr(0), data.ptr(0), false);
    assert(slot != -1);
}


///////////////////////////////////////////////////////////////////////////////
// gist_btree::search - return qualifying slots
//
// Description:
//	- return slof of rightmost item that is <= (key, data)
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

void 
bt_ext_t::search(
    gist_p& page,
    const gist_query_t* query,
    int matches[],
    int& numMatches)
{
    const bt_query_t* q = (const bt_query_t *) query;
    int start, end; // start and end slot to scan

    numMatches = 0;
    switch (q->oper) {
    case bt_query_t::bt_nooper:
        start = 0;
	end = page.nrecs() - 1;
	break;
    case bt_query_t::bt_eq:
        start = _binSearch(page, q->val1, NULL, true);
	if (start == -1) {
	    // we're not going to find anything here
	    return;
	}
	// if we're at an internal node and val1 == key[start], there might be 
	// duplicates of val on the child to the left of child[start] (unless
	// we're already at the left boundary)
	if (!page.is_leaf() && start > 0 &&
	    keyCmp(page.rec(start).key(), q->val1) == 0) {

	    start--;
	}

	// The end of the range would be the rightmost slot with the same key,
	// but since _binSearch() can't find that or the position of the next higher
	// key, we pretend our range extends to the end of the page and check the 
	// keys as we go through the slots.
	end = page.nrecs() - 1;
	break;
    case bt_query_t::bt_lt:
    case bt_query_t::bt_le:
        start = 0;
	end = _binSearch(page, q->val1, NULL, true);
	break;
    case bt_query_t::bt_gt:
    case bt_query_t::bt_ge:
        start = _binSearch(page, q->val1, NULL, true);
	if (start == -1) start = 0;
	end = page.nrecs() - 1;
	break;
    case bt_query_t::bt_betw:  // equiv. to >= val1 && <= val2
        start = _binSearch(page, q->val1, NULL, true);
	if (start == -1) start = 0;
        end = _binSearch(page, q->val2, NULL, true);
	break;
    default: // something's wrong
        assert(0);
    };

    bool hit = false;
    bool stop = false; // bt_eq might tell us to stop
    for (int slot = start; slot <= end; slot++) {
        if (page.is_leaf()) {
	    switch (q->oper) {
	    case bt_query_t::bt_nooper:
		hit = true;
		break;
	    case bt_query_t::bt_eq:
	        if (keyCmp(page.rec(slot).key(), q->val1) == 0) {
		    hit = true;
		} else {
		    hit = false;
		    stop = true; // no more equal keys on this page
		}
		break;
	    case bt_query_t::bt_lt:
	        if (slot != end || keyCmp(page.rec(slot).key(), q->val1) < 0) {
		    hit = true;
		}
		break;
	    case bt_query_t::bt_le:
		hit = true;
		break;
	    case bt_query_t::bt_gt:
	        if (slot != start || keyCmp(page.rec(slot).key(), q->val1) > 0) {
		    hit = true;
		}
		break;
	    case bt_query_t::bt_ge:
		// start positioned on rightmost item <= key, we must only return
		// items < key
	        if (slot != start || keyCmp(page.rec(slot).key(), q->val1) >= 0) {
		    hit = true;
		}
		break;
	    case bt_query_t::bt_betw:
	        if (slot != start || keyCmp(page.rec(slot).key(), q->val1) >= 0) {
		    hit = true;
		}
		break;
	    default: // something's fishy
	        assert(0);
	    }

	} else { // internal node
	    switch (q->oper) {
	    case bt_query_t::bt_lt: 
		if (slot == end) {
		    // only goto child if its smallest key < val1; _binSearch()
		    // might have found key == val1)
		    if (keyCmp(page.rec(slot).key(), q->val1) < 0) hit = true;
		} else {
		    hit = true;
		}
		break;
	    case bt_query_t::bt_eq: 
		// stop checking the entries when we hit one that's > val1
	        if (keyCmp(page.rec(slot).key(), q->val1) > 0) {
		    hit = false;
		    stop = true;
		} else {
		    hit = true;
		}
		break;
	    default:
	        hit = true;
	    }
	}
	if (hit) {
	    matches[numMatches] = slot;
	    numMatches++;
	    hit = false;
	}
	if (stop) {
	    break;
	}
    }
}


///////////////////////////////////////////////////////////////////////////////
// gist_btree:getKey - return pointer to key on page
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

void 
bt_ext_t::getKey(
    const gist_p& page,
    int slot,
    vec_t& key)
{
    const keyrec_t& tup = page.rec(slot);
    key.set(tup.key(), tup.klen());
}


///////////////////////////////////////////////////////////////////////////////
// gist_btree::pickSplit - choose split point that balances size of nodes
//
// Description:
// 	- Chooses a split point that roughly balances the size of the two new
//	  nodes. Also takes sizes of new entries into account.
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t 
bt_ext_t::pickSplit(
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
    // first, count the number of bytes used for all keys (also the new ones)
    int totalBytes = 0;
    int slotCnt = page.nrecs();
    int i;
    for (i = 0; i < slotCnt; i++) {
	// for internal entries, we include the data pointers, because
	// these will also be distributed (and who knows, they might
	// even be varying length)
	totalBytes += page.rec(i).klen();
    }
    totalBytes += entry1.len(0);
    if (entry1.size() != 0) slotCnt++;
    totalBytes += entry2.len(0);
    if (entry2.size() != 0) slotCnt++;

    PosInfo entries[gist_p::max_scnt + 2];
    keyrec_t::hdr_s hdr1, hdr2;
    _loadPosInfo(page, entry1, entry2, hdr1, hdr2, entries);
    // now, accumulate entries until you exceed half the total size
    // (entries[] contains sizes for all entries in key/data order, including new entries)
    int total = 0;
    i = 0;
    while (total < totalBytes/2 && i < slotCnt) {
        total += entries[i].hdr->klen();
	i++;
    }
    assert(i != slotCnt); // can't be...

    // everything from slot i on goes right ...
    numRight = 0;
    oneGoesRight = false;
    twoGoesRight = false;
    for (int j = i; j < slotCnt; j++) {
	if (entries[j].slot > 0) {
	    rightEntries[numRight] = entries[j].slot;
	    numRight++;
	} else if (entries[j].slot == -1) {
	    oneGoesRight = true;
	} else {
	    assert(entries[j].slot == -2);
	    twoGoesRight = true;
	}
    }

    // the BP of the original node stays the same
    if (oldBp.size() != 0) {
	(void) memcpy(leftBp.ptr(0), oldBp.ptr(0), oldBp.len(0));
	const void *leftptr = leftBp.ptr(0);
	leftBp.set(leftptr, oldBp.len(0));
    } else {
        // this is what used to be the root;
	// the BP becomes -infinity
	void *leftptr = leftBp.ptr(0);
	negInftyKey(leftptr);
	int leftsz = this->keySize(leftptr);
	void *dataptr = (void *) ((char *) leftptr + leftsz);
	negInftyData(dataptr);
	leftsz += this->dataSize(dataptr);
	leftBp.set(leftptr, leftsz);
    }

    // the BP of the new right sibling is the item at the split point
    void* rightptr = rightBp.ptr(0);
    int rightlen;
    if (entries[i].slot > 0) {
        // take then BP from the page
	const keyrec_t& tup = page.rec(entries[i].slot);
	(void) memcpy(rightptr, tup.key(), tup.klen());
	rightlen = tup.klen();
	if (page.is_leaf()) {
	    // also copy the data ptr
	    (void) memcpy((void *) ((char *) rightptr + rightlen), tup.elem(), tup.elen());
	    rightlen += tup.elen();
	}
    } else {
        const vec_t* e;
	if (entries[i].slot == -1) {
	    e = &entry1;
	} else {
	    assert(entries[i].slot == -2);
	    e = &entry2;
	}
	(void) memcpy(rightptr, e->ptr(0), e->len(0));
	rightlen = e->len(0);
	if (page.is_leaf()) {
	    (void) memcpy((void *) ((char *) rightptr + (int) rightlen), e->ptr(1), e->len(1));
	    rightlen += e->len(1);
	}
    }
    rightBp.set(rightptr, rightlen);

    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// bt_ext_t::unionBp - generate BP
//
// Description:
//	- B-trees partition the data space, which means that BPs do not
//	  change when data is added to or delete from a page
//	- unfortunately, we can't generally provide the correct BP 
// 	  for bulk-loading (don't know when to return -\infty)
//
/////////////////////////////////////////////////////////////////////////

void
bt_ext_t::unionBp(
    const gist_p& page, // in
    vec_t& bp, // in/out
    bool bpIsValid, // in
    const vec_t& pred1, // in
    const vec_t& pred2, // in
    bool& bpChanged) // out
{
    bpChanged = false;
}

gist_cursorext_t*
bt_ext_t::queryCursor(
    const gist_query_t* query) const
{
    return gist_cursorext_t::gist_cursorext_list[gist_cursorext_t::cext_stack_id];
}

bool 
bt_ext_t::check(
    const vec_t& bp,
    const vec_t& pred,
    int level)
{
    if (keyCmp(pred.ptr(0), bp.ptr(0)) < 0) return false;
    if (level > 1) {
        // check data contained in predicate
	void* bpData = (char *) bp.ptr(0) + keySize(bp.ptr(0));
	void* predData = (char *) pred.ptr(0) + keySize(pred.ptr(0));
	return (dataCmp(predData, bpData) >= 0);
    }
    return true;
}

int
bt_ext_t::_binSearch(
    const gist_p& page,
    const void* key,
    const void* data,
    bool keyOnly) // true: only compare keys
{
    int hi = page.nrecs() - 1;
    if (hi == -1) {
        // nothing on this page yet
	return -1;
    }
    int lo = 0;
    int mid;
    const void* midkey;
    const void* middata;
    int res;

    for (;;) {
	mid = (hi + lo) / 2;
        const keyrec_t& tup = page.rec(mid);
	midkey = tup.key();
	if (page.is_leaf()) {
	    middata = tup.elem();
	} else {
	    int sz = this->keySize(midkey);
	    middata = (const void *) (((char *) midkey) + sz);
	}
	res = keyCmp(key, midkey);
	if (!keyOnly && res == 0) {
	    res = dataCmp(data, middata);
	}
	if (res < 0) {
	    // key is smaller than midpoint
	    hi = mid - 1;
	} else if (res > 0) {
	    lo = mid + 1;
	} else {
	    // found an exact match, but not sure it's the first one
	    hi = mid; // not mid - 1, we might end up returning mid
	    if (hi == lo) return hi;
	}
	if (hi < lo) return hi;
    }
#if 0 // just for explanatory purposes
    if (res < 0) {
        return mid-1;
	// because mid-1 is our upper bound, but also our lower bound
	// (hi <= lo) 
    } else {
        // res > 0: lo = hi, because mid < hi and lo now = mid + 1
        return hi;
    }
#endif
}

// Determine where the two new entries would go on the page (which slots they
// would occupy). Returns this info through array of PosInfos, two of which will 
// contain info for new entries
void
bt_ext_t::_loadPosInfo(
    gist_p& page,
    const vec_t& entry1,
    const vec_t& entry2,
    keyrec_t::hdr_s& hdr1, // in: hdr_s for 1st entry, needed for entries[]
    keyrec_t::hdr_s& hdr2, // in: hdr_s for 2nd entry, needed for entries[]
    PosInfo entries[]) // out: hdrs of all items of page + new entries, sorted in key/data order
{
    int cnt = page.nrecs();
    int numEntries = cnt;
    int k;
    for (k = 0; k < cnt; k++) {
        entries[k].hdr = &page.rec(k);
	entries[k].slot = k;
    }
    
    if (entry1.size() == 0) {
	// no entries to add to PosInfo, we're done
        return;
    }

    // Figure out where entry1/-2 would go.
    const void *data1, *data2;
    if (page.is_leaf()) {
	data1 = entry1.ptr(1);
	data2 = entry2.ptr(1);
    } else {
	// extract data portion from "key"
	data1 = (((char *) entry1.ptr(0)) + this->keySize(entry1.ptr(0)));
	data2 = (((char *) entry2.ptr(0)) + this->keySize(entry2.ptr(0)));
    }
    int oneSlot = _binSearch(page, entry1.ptr(0), data1, false) + 1;
    int twoSlot = -1;
    const vec_t* firstEntry = NULL; // new entry with "lower" slot index
    const vec_t* secondEntry = NULL; // new entry with "higher" slot index
    if (entry2.size() != 0) {
	twoSlot = _binSearch(page, entry2.ptr(0), data2, false) + 1;
	if (oneSlot == twoSlot) {
	    // we have to determine which one of the entries goes first
	    int res = keyCmp(entry1.ptr(0), entry2.ptr(0));
	    if (res == 0) {
	        res = dataCmp(data1, data2);
	    }
	    if (res < 0) {
	        firstEntry = &entry1;
		secondEntry = &entry2;
	    } else if (res > 0) {
	        firstEntry = &entry2;
		secondEntry = &entry1;
	    } else {
	        // res == 0: something's wrong (we've got perfect duplicates)
		assert(0);
	    }
	} else if (oneSlot < twoSlot) {
	    firstEntry = &entry1;
	    secondEntry = &entry2;
	} else { // oneSlot > twoSlot
	    firstEntry = &entry2;
	    secondEntry = &entry2;
	}
    } else {
        // we only have entry1
	secondEntry = &entry1;
    }
    int firstSlot = (oneSlot > twoSlot ? twoSlot : oneSlot);
    int secondSlot = (oneSlot > twoSlot ? oneSlot : twoSlot);
    bool oneGoesFirst = (firstEntry == &entry1);

    // insert one entry
    hdr1.klen = secondEntry->len(0);
    numEntries++;
    for (k = numEntries-1; k > secondSlot; k--) {
        entries[k] = entries[k-1];
    }
    entries[secondSlot].hdr = (keyrec_t *) &hdr1;
    entries[secondSlot].slot = (oneGoesFirst ? -2 : -1);

    // insert other entry
    if (entry2.size() != 0) {
	hdr2.klen = firstEntry->len(0);
	numEntries++;
	for (k = numEntries-1; k > firstSlot; k--) {
	    entries[k] = entries[k-1];
	}
	entries[firstSlot].hdr = (keyrec_t *) &hdr2;
	entries[firstSlot].slot = (oneGoesFirst ? -1 : -2);
    }
}

static int
int_size(const void *i)
{
    return sizeof(int);
}

static void
int_negInfty(void *i)
{
    // can't use assignment, i might not be aligned properly
    int min = MININT;
    (void) memcpy(i, (void *) &min, sizeof(min));
}

bt_ext_t bt_int_ext(gist_ext_t::bt_int_ext_id, "bt_int_ext",
    gist_support::printIntBtPred, gist_support::printInt,
    gist_support::parseInt, gist_support::parseInt,
    gist_support::parseIntQuery, int_cmp, int_cmp,
    int_size, int_size, int_negInfty, int_negInfty);

static int
str_size(const void *s)
{
    return strlen((char *) s) + 1;
}

static void
str_negInfty(void *s)
{
    *((char *) s) = '\0';
}

bt_ext_t bt_str_ext(gist_ext_t::bt_str_ext_id, "bt_str_ext",
    gist_support::printStringBtPred, gist_support::printInt,
    gist_support::parseString, gist_support::parseInt,
    gist_support::parseStringQuery, str_cmp, int_cmp,
    str_size, int_size, str_negInfty, int_negInfty);
