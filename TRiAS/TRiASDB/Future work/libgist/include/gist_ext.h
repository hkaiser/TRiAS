// gist_ext.h							-*- c++ -*-
// Copyright (c) 1997, Regents of the University of California
// $Id: gist_ext.h,v 1.21 2000/03/10 01:39:03 mashah Exp $


#ifndef GIST_EXT_H
#define GIST_EXT_H

class gist_p;
#include "vec_t.h"

// VCPORT_B
#ifndef WIN32
class ostream;
#endif
// VCPORT_E

class gist_query_t;
class gist_cursorext_t;

/*
 * gist_penalty_t:
 * insertion penalty, computed during greedy descent to a leaf node
 */
class gist_penalty_t {
public:
    static const double max_penalty;

    gist_penalty_t() {}
    gist_penalty_t(double p) : p(p) {}
    double p; // a double must be enough

    bool operator<(const gist_penalty_t &pen) { return p < pen.p; }
    operator double() const { return p; }
    gist_penalty_t& operator=(const gist_penalty_t &pen) { p = pen.p; return *this; }
    gist_penalty_t& operator=(double pen) { p = pen; return *this; }
};


/*
 * Interface for Gist extension classes.
 *
 * The procedures here are mostly node layout abstractions, only
 * union{Key,Page}(), check(), print*() and eqQuery() are data
 * abstractions.
 *
 * The subclasses of gist_ext_t are supposed to implement the node
 * layout aspects, and offer a cleaner interface that requires the
 * user to specify only the data abstraction routines.
 *
 * The subclass implementer can use any of the gist_p member functions
 * to implement a specific node layout. Also, every page contains a BP
 * (slot index: gist_p::bpSlot), except for the root page.
 *
 * The subclass implementation must guarantee that 
 *
 * - every entry (consisting of some key data and a data/child
 *   pointer) on the page is stored as a keyrec_t (with keyrec_t as a
 *   header and the key and data following) and has a slot associated
 *   with it, no matter how much the key is compressed (the intention
 *   is that the data and child pointers are accessible via
 *   gist_p::rec(index).elem() and gist_p::rec(index).child());
 *
 * - slot indices are stable until the next *successful* call to
 *   insert(), remove(), updateKey() and pickSplit() (i.e., they don't
 *   change between a call to pickSplit() and remove(); also,
 *   updateKey() must not change the slot assignments if it returns
 *   with an error);
 *
 * The following things are *not* required:
 *
 * - using a contiguous block of slots in the slot array (used and
 *   unused slots may alternate)
 *
 * - the information to reconstruct a full key need not be stored in a
 *   single entry, as long as getKey() can reconstruct the key given
 *   the associated slot index
 * 
 * In order to implement logical undo of data item insertion and
 * deletion in Shore, we need to be able to associate extension
 * objects with log records and access those extension objects at
 * recovery time. The type gist_ext_ids records IDs for extension
 * objects and the array gist_ext_list maps those IDs to the
 * corresponding objects.  Every new extension object should have an
 * entry in gist_ext_ids, have its own myId set to that entry and its
 * myName set to some descriptive name (used for amdb) as well as
 * "register" itself in gist_ext_list.  */

class gist_ext_t {
public:

    // list of extension object IDs
    enum gist_ext_ids {
	rt_point_ext_id,	// R-tree
	rt_rect_ext_id,
	bt_int_ext_id,		// B-tree
	bt_str_ext_id,
	rstar_point_ext_id,	// R*-tree
	rstar_rect_ext_id,
	sp_point_ext_id,	// sphere-tree
	ss_point_ext_id,	// SR-tree
	sr_point_ext_id,	// SR-tree
	rr_point_ext_id,	// ranked R-tree
	npt_ext_id, 		// NP-tree
    gist_numext
    };
    // ID of the particular extension object at hand
    const gist_ext_ids myId;
    const char* myName;
    // array of extension objects 
    static gist_ext_t *gist_ext_list[gist_numext];


    // here are the node layout-specific routines

    // Create a new entry on a page (without updating the BP).  Return
    // eRECWONTFIT if the new entry does not fit on the page.
    virtual rc_t insert(
        gist_p& page,
	const vec_t& key,
	const vec_t& data,
	shpid_t child)
	= 0;

    // Remove a number of entries, identified by their slot indices
    // (without updating the BP).
    virtual rc_t remove(
        gist_p& page,
	const int slots[],
	int numSlots)
	= 0;

    // For internal nodes only: update the key for the entry in the
    // given slot.
    virtual rc_t updateKey(
        gist_p& page,
	int& slot, // in/out: old/new slot assignment
	const vec_t& newKey)
	= 0;

    // Find the entry with the lowest insertion penalty for the given
    // key; return the slot index in 'slot'.
    virtual void findMinPen(
        const gist_p& page,
	const vec_t& key,
	const vec_t& data,
	int& slot)
	= 0;

    // Search the page for entries matching the given query; return
    // their slot indices in 'matches'.
    virtual void search(
        gist_p& page,
	const gist_query_t* query,
	int matches[],
	int& numMatches)
	= 0;

    // Return the key of the entry in the given slot. If a
    // conversion/decompression of the key takes place, the key is
    // written into the memory pointed to by key.ptr(0).  If no
    // conversion takes place, the key points to the buffered page.
    virtual void getKey(
        const gist_p& page,
	int slot,
	vec_t& key)
        = 0;

    // Determine how to split the given node. The split info is the
    // slot indices of those entries that go to the right
    // sibling. Make sure that rightEntries only contains the indices
    // of existing slots. This procedure also calculates the new BPs
    // (which have to be copied into left-/rightBp).  The new
    // entry/-ies that will be inserted after the split are given in
    // entry1 and -2 (if they are leaf entries, the second component
    // will hold the data pointer); those need to be taken into
    // consideration when calculating the BPs.  (if there's no second
    // entry to be inserted, entry2.size() == 0). The caller also
    // needs to know which page to insert each entry on; this
    // information is returned in *GoesRight.  If no new entries are
    // given (both .sizes() == 0), this "split" is performed by
    // gist::pickSplit, not an actual insertion operation.  to be
    // taken into account.
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
	bool& twoGoesRight)
	= 0;

    // Computes BP of the predicates contained on the page plus one or two 
    // extra predicates added to the page.
    // - 'bp' must point to a buffer of size gist_p::max_tup_sz (or
    //   larger).
    // - 'bpIsValid' indicates whether or not 'bp' contains a
    //   valid instance of the BP type, i.e., one that represents the 
    //   current contents of 'page. If 'bpIsValid', only pred1/-2 need to be 
    //   added to it. If '!bpIsValid', the BP must be generated from scratch
    //   for all of the predicates on the page (plus pred1/-2). The latter is required
    //   for bulk-loading (for the most recently constructed page, for which
    //   no BP exists) and for deletion (there is no "incremental
    //   deletion," i.e., we cannot (in general) apply some update
    //   operation to the old BP that is guaranteed to result in an
    //   adequately accurate BP).
    // - 'pred1' and 'pred2' are the extra predicates added to the page (and, if 
    //   the BP is valid, those predicates would not be included in 'bp'). Either 
    //   one can be empty (pred.size() == 0).
    // - 'bpChanged' indicates whether the output 'bp' is different
    //   from the input 'bp'.  'bpChanged' is only meaningful if
    //   'bpIsValid' is true (otherwise it is automatically true).
    virtual void unionBp(
        const gist_p& page, // in
	vec_t& bp, // in/out
	bool bpIsValid, // in
	const vec_t& pred1, // in
	const vec_t& pred2, // in
	bool& bpChanged) = 0; // out

    // here are the datatype-specific routines

    // returns the appropriate cursor extension to process this query.
    virtual gist_cursorext_t* queryCursor(
	const gist_query_t* query) const = 0;

    // Return true if the predicate is contained by the BP.  Used
    // during gist_t::check() to verify the integrity of the node's
    // content.
    virtual bool check(
	const vec_t& bp,
	const vec_t& pred,
	int level) // level of page
	= 0;

    // The remaining functions are only needed to support the command
    // line interface and amdb. We use function
    // pointers instead of inheritance to facilitate extension configuration
    // (won't have to pollute each extension with these functions).
    // These functions are optional and need not be supplied in the constructor.

    typedef void (*PrintPredFct)(
	std::ostream& s, // what to print to
	const vec_t& pred, // pred.ptr(0) contains pointer to 8-byte aligned predicate
	int level); // level of page where pred is stored; leaves are at 1
    typedef void (*PrintDataFct)(
	std::ostream& s, // what to print to
	const vec_t& data); // data.ptr(0) contains pointer to *unaligned* data
    PrintPredFct printPred;
    PrintDataFct printData;

    // The parsing functions return either RCOK or ePARSEERROR.
    // - 'out': output parameters, which point to allocated
    //   memory (allocation not necessary inside functions)
    // - 'query': output parameter, which does *not* point to allocated
    //   memory. The reason is that a query is a possibly complex data
    //   structure that cannot easily be laid out sequentially in memory. Allocation
    //   is therefore best done by a constructor. 

    typedef rc_t (*ParseFct)(const char* str, void* out, int& len);
    ParseFct parsePred; // parses string and returns leaf-level predicate and  its length
    ParseFct parseData; // same as parsePred, only for data

    typedef rc_t (*ParseQueryFct)(const char* str, gist_query_t*& query);
    ParseQueryFct parseQuery; // parses string and returns query
        
    gist_ext_t::gist_ext_t(
        gist_ext_ids id,
	const char *name,
	PrintPredFct printPred,
	PrintDataFct printData,
	ParseFct parsePred,
	ParseFct parseData,
	ParseQueryFct parseQuery) :
	myId(id), myName(name), printPred(printPred), printData(printData),
	parsePred(parsePred), parseData(parseData), parseQuery(parseQuery)
    {
        gist_ext_list[id] = this;
    }

};

#endif // GIST_EXT_H

