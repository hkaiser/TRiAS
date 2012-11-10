// gist.cc
// Copyright (c) 1997, 1998, Regents of the University of California
// $Id: gist.cc,v 1.53 2000/03/15 00:24:23 mashah Exp $

/*
 * Comments on the various #ifdefs:
 *
 * 1) #ifdef AMDB: If libgist is used as part of amdb, it needs to
 *    keep counters and call back to amdb when breakpoint-worthy
 *    events happen.
 */

#ifdef __GNUG__
#pragma implementation "gist.h"
#endif

// VCPORT_B
#ifdef WIN32
#pragma warning(disable:4786) // Templates can cause names to get too long for
							  // debug information. Disables this warning.
#endif
// VCPORT_E

#include <new.h>
#include <math.h>
#include <stdlib.h>

// VCPORT_B
#ifdef WIN32
#include <iostream>
#include <fstream>
using namespace std;
#else
#include <iostream.h>
#include <fstream.h>
#endif
// VCPORT_E

#include <stdio.h>

#include "gist_compat.h"	// for MAXDOUBLE
#include "gist_defs.h"

#include "gist_ext.h"
#include "gist_cursor.h"
#include "gist_cursorext.h"
#include "gist_ustk.h"
#ifdef AMDB
#include "amdb_wkldprofile.h"
//#include "amdb_ext.h"
#endif
#include "gist.h"


// didn't know where else to put these
const double gist_penalty_t::max_penalty = MAXDOUBLE;
gist_ext_t* gist_ext_t::gist_ext_list[gist_ext_t::gist_numext];

// misc
const shpid_t gist::rootNo = ROOTPAGE;


/////////////////////////////////////////////////////////////////////////
// gist - Constructor
//
// Description:
//
/////////////////////////////////////////////////////////////////////////

gist::gist() : _ext(NULL), _isOpen(false), _file()
#ifdef AMDB
    , _breakHandler(NULL), _profile(NULL)
#endif
{
}


/////////////////////////////////////////////////////////////////////////
// ~gist - Destructor
//
// Description:
// 	- close index
//
/////////////////////////////////////////////////////////////////////////

gist::~gist()
{
    close();
}


/////////////////////////////////////////////////////////////////////////
// _new_page - allocate a new page
//
// Description:
//	- format page and add header entry in slot 0
//	- if we pass in a descriptor, no page in the file is
//	  allocated (need this for gist::splitNode())
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_new_page(
    shpid_t 			root,
    gist_p&			p,
    int2 			level,
    gist_file::page_descr*	descr)
{
    if (descr == NULL) {
	p._descr = _file.allocPage();
    } else {
        p._descr = descr;
    }
    assert(p._descr != NULL);
    p._pp = (page_s *) p._descr->page;

    gistctrl_t hdr;
    hdr.root = root;
    hdr.level = level;
    W_DO(p.format(p._descr->pageNo, &hdr));
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// is_empty - return true if tree is empty
//
// Description:
//
// Return Values:
//      true/false
/////////////////////////////////////////////////////////////////////////

bool 
gist::is_empty()
{
    gist_p page;

    W_DO(_fix_page(page, rootNo, LATCH_SH));
    return(page.nrecs() == 0);
}


/////////////////////////////////////////////////////////////////////////
// open - open index file
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::open(
    const char*		filename)
{
    W_DO(_file.open(filename, _ext));
    _isOpen = true;
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// close - close index file
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::close()
{
    if (_isOpen) {
	W_DO(_file.close());
	_isOpen = false;
    }
#ifdef AMDB
    // don't dealloc profile, the caller might still need it
#endif
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// flush - flush index file
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::flush()
{
    W_DO(_file.flush());
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// create - create new index file
//
// Description:
//	- initializes tree with empty root and flushes file
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::create(
    const char*		filename,
    gist_ext_t*		extension)
{
    _ext = extension;
    W_DO(_file.create(filename, _ext));
    _isOpen = true;

    // create the root page
    gist_p root;
    _new_page(rootNo, root, 1); // this is a leaf
    assert(rootNo == root.pid());
    _unfix_page(root);
    W_DO(_file.flush());
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// create - create index and bulk-load it
//
// Description:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::create(
    const char*		filename,
    gist_ext_t*		extension,
    TupleStream		s,
    void*		sParam,
    float		fillFactor)
{
    // create the root (must be in page 1)
    W_DO(create(filename, extension));

    // set up temp files for BPs
    char* temp1 = "temp1"; // to be changed later
    char* temp2 = "temp2";
    bool toTemp1 = true; // true: write BPs to temp1



	// VCPORT_B
	// Gotta make sure that the temp files that are written are written in binary
#ifdef WIN32
	ofstream bpOutStream(temp1, ios_base::out | ios_base::binary);
	ofstream tmpfile(temp2, ios_base::out | ios_base::binary);
#else
	ofstream bpOutStream(temp1); // creates empty file
    ofstream tmpfile(temp2); // creates empty file
#endif
	// VCPORT_E

    tmpfile.close();

	// VCPORT_B
	// The state bits for the stream are not reset when file is close on NT
#ifdef WIN32
	tmpfile.clear();
#endif
	// VCPORT_E

	// VCPORT_B
	// Again make sure you read it in binary as well ...
#ifdef WIN32
	ifstream bpInStream(temp2, ios_base::in | ios_base::binary);
#else
	ifstream bpInStream(temp2); // opens empty file
#endif
	// VCPORT_E

    if (fillFactor > 1.0) fillFactor = 1.0; // can't fill page more than once

    // build tree level by level
    int level = 0;
    for (;;) {
        level++;
	TupleStream tupStream;
	void* streamParam;
	if (level == 1) {
	    // read from user-supplied tuple stream
	    tupStream = s;
	    streamParam = sParam;
	} else {
	    tupStream = _readBpFromTemp;
	    streamParam = (void *) &bpInStream;
	}
	int pageCnt;
	gist_p lastPage;
	W_DO(_build_level(tupStream, streamParam, fillFactor, level, rootNo,
	    bpOutStream, NULL, pageCnt, lastPage));

	bpInStream.close();
	bpOutStream.close();
	// VCPORT_B
	// The state bits for the stream are not reset when file is close on NT
#ifdef WIN32
	bpInStream.clear();
	bpOutStream.clear();
#endif
	// VCPORT_E

	if (pageCnt == 1) {
	    // The last level we produced contains only 1 page: this
	    // is the root level. We must copy the last page of this
	    // level to the (fixed-location) root page, adjust the
	    // level in the root page's header and then delete the
	    // last page.
	    gist_p rootPage;
	    W_DO(_fix_page(rootPage, rootNo, LATCH_EX));
	    W_DO(lastPage.copy(rootPage));
	    rootPage.set_level(level);
	    _unfix_page(rootPage);
	    W_DO(_file.freePage(lastPage._descr));
	    lastPage._pp = NULL;

	    // remove temp files
	    if (unlink(temp1) != 0) return(eFILEERROR);
	    if (unlink(temp2) != 0) return(eFILEERROR);

	    flush();
	    return(RCOK);
	}

	// switch BP input and output for the next level
	toTemp1 = (toTemp1 ? false : true);
	if (toTemp1) {
	    // write to temp1, read from temp2

		// VCPORT_B
#ifdef WIN32
		bpOutStream.open(temp1, ios_base::out | ios_base::binary);
		bpInStream.open(temp2, ios_base::in | ios_base::binary);
#else
	    bpOutStream.open(temp1);
	    bpInStream.open(temp2);
#endif
	} else {
#ifdef WIN32
	    bpOutStream.open(temp2, ios_base::out | ios_base::binary);
	    bpInStream.open(temp1, ios_base::in | ios_base::binary);
#else
	    bpOutStream.open(temp2);
	    bpInStream.open(temp1);
#endif
		// VCPORT_E
	}

    }

    // can't get here
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// _locate_leaf - descend to leaf along minimum-penalty path
//
// Description:
//	- record path on 'stack'
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_locate_leaf(
    shpid_t 		root, // root of index
    gist_ustk&		gstack, // out: path to leaf
    const vec_t&	key, // key to insert
    const vec_t&	data) // data to insert
{
    shpid_t currPid = root;
    gist_p page;
    int index;

    for (;;) {

	W_DO(_fix_page(page, currPid, LATCH_EX));

#ifdef AMDB
	if (_breakHandler != NULL) {
	    // construct bp info
	    amdb_breakpoints::BreakInfo info;
	    info.event = (page.is_leaf() ? amdb_breakpoints::locateLeafEvent :
		amdb_breakpoints::traversalEvent);
	    info.node = currPid;
	    (void) _breakHandler(&info);
	}
#endif

	if (!page.is_leaf()) {
	    _ext->findMinPen(page, key, data, index);
	    gstack.push(page, index);
	} else {
	    // we found a leaf
	    gstack.push(page, 0);
	    return (RCOK); // leave the leaf latched
	}

	// follow child pointer
	currPid = page.rec(index).child();
	// no page.unfix(); we leave the pages fixed for now
    }
}


/////////////////////////////////////////////////////////////////////////
// _extract_bp - extract BP from parent page of stack entry
//
// Description:
//	- BP is in parent entry of node given by 'stkIdx'
//	- call ext->getKey() to extract the key, but make a copy
//	  if getKey() hasn't done so (BP extracted for modification)
//	- if the node has no parent (is the root), we set
//	  bp.len(0) to 0
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

void
gist::_extract_bp(
    gist_ustk&	gstack,
    int		stkIdx,
    vec_t&	bp)
{
    if (gstack.is_root(stkIdx)) {
        bp.set(bp.ptr(0), 0);
	return;
    }
    void* bpdata = bp.ptr(0);
    gist_ustk_entry *e = gstack.top(stkIdx + 1);
    _ext->getKey(e->page, e->idx, bp);
    if (bp.ptr(0) != bpdata) {
        // getKey() changed bp to point to the page, 
	// we need to make a copy now
	(void) memcpy(bpdata, bp.ptr(0), bp.len(0));
	bp.set(bpdata, bp.len(0));
    }
}


/////////////////////////////////////////////////////////////////////////
// _insert_leaf - Insert key/data pair on leaf and update BP
//
// Description:
//	- notify amdb of insertion
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
//      eRECWONTFIT
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_insert_leaf(
    gist_p&		page, // leaf to insert on
    const vec_t&	key, // key of new entry
    const vec_t&	data, // data of new entry
    vec_t&		bpv, // BP as stored in parent entry
    bool&		bpChanged) // out: true if the BP changed
{
    int cnt = page.nrecs();

    // insert new item 

#ifdef AMDB
    if (_breakHandler != NULL) {
	// construct bp info
	amdb_breakpoints::BreakInfo info;
	info.event = amdb_breakpoints::nodeInsertEvent;
	info.node = page.pid();
	(void) _breakHandler(&info);
    }
#endif

    rc_t status = _ext->insert(page, key, data, 0);
    if (status != RCOK) {
        return (status);
    }

#ifdef AMDB
    if (_breakHandler != NULL) {
	// construct bp info
	amdb_breakpoints::BreakInfo info;
	info.event = amdb_breakpoints::itemInsertedEvent;
	info.param.updNodeParam = page.pid();
	(void) _breakHandler(&info);
    }
#endif

    // update the BP, if there is one
    if (!page.is_root()) {
	unsigned int oldLen = bpv.len(0);
	_ext->unionBp(page, bpv, true, key, vec_t(), bpChanged);
	assert(bpv.len(0) <= gist_p::max_tup_sz);
	assert(bpChanged || oldLen == bpv.len(0));

#ifdef AMDB
	if (bpChanged) {
	    // notify amdb
	    if (_breakHandler != NULL) {
		// construct bp info
		amdb_breakpoints::BreakInfo info;
		info.event = amdb_breakpoints::bpUpdateEvent;
		info.node = page.pid();
		(void) _breakHandler(&info);
	    }
	}
#endif

    } else {
	// the root doesn't have a BP
	bpChanged = false;
    }

    return (RCOK);
}


/////////////////////////////////////////////////////////////////////////
// _apply_update - Update/insert entries on page and update BP
//
// Description:
// 	- If both 'leftBp' and 'rightBp' contain keys with non-zero size, we
// 	  are inserting the BPs resulting from a page split.  In general,
// 	  'leftBp' (having been recomputed to fit its new contents by
// 	  pickSplit()) will be different from that present before the split.
//	- If only 'leftBp' has non-zero size, we are simply applying an
// 	  update caused by a change in a child BP.
//	- We compute the updated BP *before* modifying the page contents,
//	  otherwise the new key(s) would be present on the page and also
//	  passed as arguments 'pred1/-2' into unionBp
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
//      eRECWONTFIT
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_apply_update(
    gist_p&		page, // in/out: parent to update
    int& 		leftIdx, // in/out: slot index of entry for orig. child page
    const vec_t&	leftBp, // in: BP of orig. child page
    const vec_t&	rightBp, // in: BP of new child (or NULL if orig. child not split)
    shpid_t 		rightChild, // in: pointer to new child
    vec_t&		bp, // in/out: BP as stored in parent entry
    bool&		bpChanged) // out: true if the BP changed
{
    if (!page.is_root()) {
	unsigned int oldLen = bp.len(0);
	_ext->unionBp(page, bp, true, leftBp, rightBp, bpChanged);
	assert(bp.len(0) <= gist_p::max_tup_sz);
	assert(bpChanged || oldLen == bp.len(0));

#ifdef AMDB
	if (bpChanged) {
	    if (_breakHandler != NULL) {
		// construct bp info
		amdb_breakpoints::BreakInfo info;
		info.event = amdb_breakpoints::bpUpdateEvent;
		info.node = page.pid();
		(void) _breakHandler(&info);
	    }
	}
#endif

    } else {
        bpChanged = false;
    }

    // update the entry for the original page
    W_DO(_ext->updateKey(page, leftIdx, leftBp));

#ifdef AMDB
    // call to updateKey() updated a BP
    if (_breakHandler != NULL) {
	// construct bp info
	amdb_breakpoints::BreakInfo info;
	info.event = amdb_breakpoints::bpUpdatedEvent;
	info.param.updNodeParam = page.pid();
	(void) _breakHandler(&info);
    }
#endif

    // insert rightBp, if we have one
    if (rightBp.size() != 0) {
#ifdef AMDB
	if (_breakHandler != NULL) {
	    // construct bp info
	    amdb_breakpoints::BreakInfo info;
	    info.event = amdb_breakpoints::nodeInsertEvent;
	    info.node = page.pid();
	    (void) _breakHandler(&info);
	}
#endif

	// insert the entry for the new right sibling
	rc_t status = _ext->insert(page, rightBp, vec_t(), rightChild);
	if (status != RCOK) {
	    return (status);
	}

#ifdef AMDB
	if (_breakHandler != NULL) {
	    // construct bp info
	    amdb_breakpoints::BreakInfo info;
	    info.event = amdb_breakpoints::itemInsertedEvent;
	    info.param.updNodeParam = page.pid();
	    (void) _breakHandler(&info);
	}
#endif
    }

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// _split - split page and update parent
//
// Description:
// 	- Split page, given the split info, and return the new right page
// 	  through rightSib. 
//	- Both page and rightSib remain fixed.
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_split(
    shpid_t 		root,
    gist_p&		page, // in/out: page to split
    gist_ustk&		gstack, // records ancestors
    int 		stkIdx, // our pos on stack
    const int 		rightEntries[], // slot indices of entries for the right sibling
    int 		numRight, // how many right entries
    gist_p&		rightSib, // out: new right sibling
    vec_t&		leftBp, // BP for page
    vec_t&		rightBp) // BP for rightSib
{
#ifdef AMDB
    if (_breakHandler != NULL) {
	// construct bp info
	amdb_breakpoints::BreakInfo info;
	info.event = amdb_breakpoints::splitEvent;
	info.node = page.pid();
	(void) _breakHandler(&info);
    }
#endif

    if (gstack.is_root(stkIdx)) {
        // do root split
	gist_p leftChild;

	// both children will be at the level the root is at now
	W_DO(_new_page(root, leftChild, page.level()));
	W_DO(_new_page(root, rightSib, page.level()));

	// copy all entries on root into leftChild
	W_DO(page.copy(leftChild));

	// create a blank root page
	gistctrl_t hdr;
	hdr.root = root;
	hdr.level = page.level() + 1; // added one level
	W_DO(page.format(root, &hdr));

	// split the left child
	W_DO(_split_node(leftChild, rightSib, rightEntries, numRight));

#ifdef AMDB
	if (_breakHandler != NULL) {
	    // construct bp info for root split
	    amdb_breakpoints::BreakInfo info;
	    info.event = amdb_breakpoints::newRootEvent;
	    info.param.newRootParam.leftNode = leftChild.pid();
	    info.param.newRootParam.rightNode = rightSib.pid();
	    info.param.newRootParam.rightChildren = new amdb_breakpoints::ChildVect();
	    _getChildren(rightSib, info.param.newRootParam.rightChildren);
	    (void) _breakHandler(&info);
	}
#endif
	// add the two new entries to the otherwise empty root
	W_DO(_ext->insert(page, leftBp, vec_t(), leftChild.pid()));
	W_DO(_ext->insert(page, rightBp, vec_t(), rightSib.pid()));

	// unfix root and return left child as split page.  we needn't
	// fix the stack, because _update_parent() will not be called
	_unfix_page(page);
	page = leftChild;
    } else {
        // do regular split
	W_DO(_new_page(root, rightSib, page.level()));
	W_DO(_split_node(page, rightSib, rightEntries, numRight));

#ifdef AMDB
	if (_breakHandler != NULL) {
	    // Construct bp info for node split. This structure change
	    // event must be reported at this point rather than after
	    // the parent update (the parent update might hit another
	    // breakpoint and try to display the tree, which requires
	    // the in-core tree structure to be updated).
	    amdb_breakpoints::BreakInfo info;
	    info.event = amdb_breakpoints::newNodeEvent;
	    info.param.newNodeParam.origNode = page.pid();
	    info.param.newNodeParam.rightSib = rightSib.pid();
	    info.param.newNodeParam.rightChildren = new amdb_breakpoints::ChildVect();
	    _getChildren(rightSib, info.param.newNodeParam.rightChildren);
	    (void) _breakHandler(&info);
	}
#endif

	// leave both page and rightSib fixed, the caller might have
	// to insert into one of them

	W_DO(_update_parent(root, gstack, stkIdx+1, leftBp, rightBp,
	    rightSib.pid()));
    }

    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// _split_node - split single page 
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_split_node(
    gist_p&		left, // page to split (remove entries from)
    gist_p&		right, // page to add entries to
    const int 		rightEntries[], // slot indices of entries to be moved right
    int 		numRight) // number of entries to move right
{
    // first, move entries to new right sibling
    AlignedPred x, y;
    char *data = y.pred;
    vec_t keyv;
    vec_t datav;

    // gist::_split() guarantees that this is true (see above).
    assert(!left.is_root());
    assert(!right.is_root());

    // distribute the entries;
    for (int i = 0; i < numRight; i++) {
	int idx = rightEntries[i];
	assert(idx < left.nrecs()); // gist_ext_t::pickSplit says this shouldn't happen

	// item exists on page; copy it (both key and data)
	keyv.set(x.pred, gist_p::max_tup_sz);
	_ext->getKey(left, idx, keyv);
	(void) memcpy(data, left.rec(idx).elem(), left.rec(idx).elen());
	datav.set(data, left.rec(idx).elen());
	W_DO(_ext->insert(right, keyv, datav, left.rec(idx).child()));
    }

    // Clean up the original page: remove the moved entries
    W_DO(_ext->remove(left, rightEntries, numRight));

    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// intCmp - qsort integer comparison function
//
// Return Values:
/////////////////////////////////////////////////////////////////////////

static int
intCmp(
    const void*		a,
    const void*		b)
{
    return *((int *) a) - *((int *) b);
}


/////////////////////////////////////////////////////////////////////////
// insert - insert a new entry into the tree
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::insert(
    const void*		key, 
    const int	    	klen,
    const void*		data,
    const int	    	dlen)
{
    vec_t keyv(key, klen);
    vec_t datav(data, dlen);

#ifdef AMDB
    if (_breakHandler != NULL) {
	// construct bp info
	amdb_breakpoints::BreakInfo info;
	info.event = amdb_breakpoints::insertEvent;
	if (_breakHandler(&info)) {
	    printf("cancelled insert\n");
	    return RCOK; // function was cancelled
	}
    }
#endif

    gist_ustk gstack;
    bool wasSplit = false; // true if leaf is split

    W_DO(_locate_leaf(rootNo, gstack, keyv, datav));
    gist_p &leaf = gstack.top()->page;

    // extract BP from parent entry
    AlignedPred w;
    vec_t bpv(w.pred, gist_p::max_tup_sz);
    _extract_bp(gstack, 0, bpv);

    // insert item/update BP
    bool bpChanged = false;
    rc_t status = _insert_leaf(leaf, keyv, datav, bpv, bpChanged);
    if (status && status != eRECWONTFIT) {
        return (status);
    }

    if (status == eRECWONTFIT) {
	// something didn't fit; we must split the page

	// find out how to split
	int rightEntries[gist_p::max_scnt];
	int numRight = gist_p::max_scnt;
	AlignedPred x, y;
	vec_t leftv(x.pred, gist_p::max_tup_sz);
	vec_t rightv(y.pred, gist_p::max_tup_sz);
	bool newGoesRight, dummyBool;
	W_DO(_ext->pickSplit(leaf, rightEntries, numRight, bpv, leftv, rightv,
	    vec_t(keyv, datav), newGoesRight, vec_t(), dummyBool));
	assert(leftv.len(0) <= gist_p::max_tup_sz);
	assert(rightv.len(0) <= gist_p::max_tup_sz);
	assert(numRight <= gist_p::max_scnt);
	// assert(_check_split_info(leaf, rightEntries, numRight));

        // do the split
	gist_p rightSib;
	W_DO(_split(rootNo, leaf, gstack, 0, rightEntries, numRight, rightSib, leftv,
	    rightv));
	wasSplit = true;

	// try again; the bp is already updated due to the split
	gist_p &p = newGoesRight ? rightSib : leaf;
#ifdef AMDB
	if (_breakHandler != NULL) {
	    // construct bp info
	    amdb_breakpoints::BreakInfo info;
	    info.event = amdb_breakpoints::nodeInsertEvent;
	    info.node = p.pid();
	    (void) _breakHandler(&info);
	}
#endif
	W_DO(_ext->insert(p, keyv, datav, 0));

#ifdef AMDB
	if (_breakHandler != NULL) {
	    // construct bp info
	    amdb_breakpoints::BreakInfo info;
	    info.event = amdb_breakpoints::itemInsertedEvent;
	    info.param.updNodeParam = p.pid();
	    (void) _breakHandler(&info);
	}
#endif

	_unfix_page(leaf);
	_unfix_page(rightSib);
    }

    if (bpChanged && !wasSplit) {
        W_DO(_update_parent(rootNo, gstack, 1, bpv, vec_t(), 0));

	_unfix_page(leaf);
    }

    // unfix pages that haven't been unfixed before in calls to
    // _split() and _update_parent()
    while (!gstack.is_empty()) {
        gist_ustk_entry *e = gstack.pop();
	if (e->page.is_fixed()) {
	    _unfix_page(e->page);
	}
    }

    // XXX debug
    assert(_file.allUnpinned());

    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// _update_parent - Update internal node and propagate changes
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_update_parent(
    shpid_t 		root,
    gist_ustk&		gstack, // records ancestors
    int 		stkIdx, // parent level on stack
    const vec_t&	leftPred, // BP of orig. child page
    const vec_t&	rightPred, // BP of child's new sibling
    shpid_t 		rightChild) // pointer to child's new sibling
{
    gist_p &page = gstack.top(stkIdx)->page;

    // extract BP from parent entry
    AlignedPred w;
    vec_t bpv(w.pred, gist_p::max_tup_sz);
    _extract_bp(gstack, stkIdx, bpv);

    // save the pointer to the original child page
    const shpid_t childPtr = page.rec(gstack.top(stkIdx)->idx).child();

    // apply the updates to the parent page (update bp and left item's
    // pred, insert new item)
    bool bpChanged;
    rc_t status = _apply_update(page, gstack.top(stkIdx)->idx, leftPred, rightPred,
        rightChild, bpv, bpChanged);
    if (status != eRECWONTFIT) {
	// either we're done or there was some error; in any case,
	// we're finished with this node
	if (!status && bpChanged) {
	    W_DO(_update_parent(root, gstack, stkIdx+1, bpv, vec_t(), 0));
	}
	_unfix_page(page);
        return (status);
    }

    // something didnt fit, we have to split the page

    // we don't need the entry for the original child anymore
    W_DO(_ext->remove(page, &(gstack.top(stkIdx)->idx), 1));

    // get split info
    int rightEntries[gist_p::max_scnt];
    int numRight;
    AlignedPred x, y;
    vec_t leftv(x.pred, gist_p::max_tup_sz);
    vec_t rightv(y.pred, gist_p::max_tup_sz);
    bool leftGoesRight;
    bool rightGoesRight;
    W_DO(_ext->pickSplit(page, rightEntries, numRight, bpv, leftv, rightv, leftPred,
        leftGoesRight, rightPred, rightGoesRight));
    assert(leftv.len(0) <= gist_p::max_tup_sz);
    assert(rightv.len(0) <= gist_p::max_tup_sz);
    assert(numRight <= gist_p::max_scnt);
    // assert(_check_split_info(leaf, rightEntries, numRight));

    // do the split
    gist_p rightSib;
    W_DO(_split(root, page, gstack, stkIdx, rightEntries, numRight, rightSib, leftv,
        rightv));

    // insert left item
    gist_p &leftPg = leftGoesRight ? rightSib : page;

#ifdef AMDB
    if (_breakHandler != NULL) {
        // we're finalizing a split of an internal node by inserting
        // the entries for the original and new child in their
        // respective parents
	amdb_breakpoints::BreakInfo info;
	info.event = amdb_breakpoints::relocateChildEvent;
	if (leftGoesRight) {
	    info.param.relocateChildParam.child = childPtr;
	    info.param.relocateChildParam.oldParent = page.pid();
	    info.param.relocateChildParam.newParent = rightSib.pid();
	    (void) _breakHandler(&info);
	}
	if (rightGoesRight) {
	    info.param.relocateChildParam.child = rightChild;
	    info.param.relocateChildParam.oldParent = page.pid();
	    info.param.relocateChildParam.newParent = rightSib.pid();
	    (void) _breakHandler(&info);
	}
    }
#endif

    W_DO(_ext->insert(leftPg, leftPred, vec_t(), childPtr));

    // insert right item (if there is one)
    if (rightPred.size() != 0) {
	gist_p& rightPg = rightGoesRight ? rightSib : page;

#ifdef AMDB
	if (_breakHandler != NULL) {
	    // construct bp info
	    amdb_breakpoints::BreakInfo info;
	    info.event = amdb_breakpoints::nodeInsertEvent;
	    info.node = rightPg.pid();
	    (void) _breakHandler(&info);
	}
#endif

	W_DO(_ext->insert(rightPg, rightPred, vec_t(), rightChild));

#ifdef AMDB
	if (_breakHandler != NULL) {
	    // construct bp info
	    amdb_breakpoints::BreakInfo info;
	    info.event = amdb_breakpoints::itemInsertedEvent;
	    info.param.updNodeParam = rightPg.pid();
	    (void) _breakHandler(&info);
	}
#endif
    }

    _unfix_page(page);
    _unfix_page(rightSib);

    return RCOK;
}
 

/////////////////////////////////////////////////////////////////////////
// remove - Remove entries matching query
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::remove(
    const gist_query_t* query)
{

#ifdef AMDB
    if (_breakHandler != NULL) {
	// construct bp info
	amdb_breakpoints::BreakInfo info;
	info.event = amdb_breakpoints::removeEvent;
	if (_breakHandler(&info)) return RCOK; // function was cancelled
    }
#endif

    gist_cursor_t cursor;
    gist_p page;
    bool eof = false;
    unsigned int idx;
    shpid_t prevLeaf = 0, leaf; // assumes: 0 is not a valid page no
    AlignedPred x, y;
    char *key = x.pred, *data = y.pred;
    smsize_t klen, dlen;
    int matches[gist_p::max_scnt];
    int numMatches = 0;

    // run a query to find matching items
    W_DO(fetch_init(cursor, query, 0));
    for (;;) {
	klen = gist_p::max_tup_sz;
	dlen = gist_p::max_tup_sz;
        W_DO(_fetch(cursor, key, klen, data, dlen, leaf, idx, eof));
	if (eof || leaf != prevLeaf) {
	    // we're either at the end or switching to a new leaf:
	    // delete the stuff on the last page we visited
	    prevLeaf = leaf;
	    if (page.is_fixed()) {

#ifdef AMDB
		if (_breakHandler != NULL) {
		    // construct bp info
		    amdb_breakpoints::BreakInfo info;
		    info.event = amdb_breakpoints::nodeDeleteEvent;
		    info.node = page.pid();
		    (void) _breakHandler(&info);
		}
#endif

		// do the deletions
		W_DO(_ext->remove(page, matches, numMatches));

#ifdef AMDB
		if (_breakHandler != NULL) {
		    // construct bp info
		    amdb_breakpoints::BreakInfo info;
		    info.event = amdb_breakpoints::itemDeletedEvent;
		    info.param.updNodeParam = page.pid();
		    (void) _breakHandler(&info);
		}
#endif

	        _unfix_page(page);
	    }
	    if (eof) {
		// no more tuples, we're done
		cursor.reset(); // reset cursor to dealloc stack
	        return (RCOK);
	    }
	    W_DO(_fix_page(page, leaf, LATCH_EX));
	    numMatches = 0;
	}
	// accumulate matches which we'll remove when
	// we move on to the next leaf (or finish the query)
	matches[numMatches] = idx;
	numMatches++;
    }
}


/////////////////////////////////////////////////////////////////////////
// fetch_init - Initialize query cursor
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::fetch_init(
    gist_cursor_t&	cursor,
    const gist_query_t*	query,
    int 		k,
    int			io)
{
    cursor.ext = _ext;

#ifdef AMDB
    // check for breakpoint
    if (_breakHandler != NULL) {
	// construct bp info
	amdb_breakpoints::BreakInfo info;
	info.event = amdb_breakpoints::fetchEvent;
	if (_breakHandler(&info)) return RCOK; // function was cancelled
    }

    if (_profile != NULL) {
        // create new amdb_wkldprofile::Query for the coming query
	_profile->addQuery();
    }
#endif

    // we assume that remnants from prior searches have been erased already
    cursor.query = query;
    cursor.k = (k < 1) ? MAXINT : k;
    cursor.io = (io < 1) ? MAXINT : io;
    cursor.cext = cursor.ext->queryCursor(query);
    cursor.cext->iter_init(cursor, rootNo);

    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// _static_fix_page - fix page in buffer pool
//
// Description:
//	- pin page and set descriptor in 'page'
//	- we need this function to be static so we can call 
//	  it from other static member functions (such as _optItemStream)
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_static_fix_page(
    gist_file&    	file,
    gist_p&		page,
    shpid_t 		pageNo,
    latch_mode_t	mode)
{
    page._descr = file.pinPage(pageNo);
    if (page._descr == NULL) {
        return eOUTOFSPACE;
    }
    page._pp = (page_s *) page._descr->page;
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// _static_unfix_page - unfix page in buffer pool
//
// Description:
//	- this is a static member function for the same reasons as
//	  _static_fix_page
/////////////////////////////////////////////////////////////////////////

void
gist::_static_unfix_page(
    gist_file&    	file,
    gist_p&		page)
{
    assert(page._descr->pinCount > 0);
    assert(page._pp != NULL);
    file.unpinPage(page._descr);
    page._pp = NULL;
}


/////////////////////////////////////////////////////////////////////////
// fetch - return next matching tuple
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::fetch(
    gist_cursor_t&	cursor,
    void*		key,
    smsize_t&		klen,
    void*		el,
    smsize_t&		elen,
    bool&		eof)
{
    shpid_t leaf;
    unsigned int idx;

    rc_t status;
    if (cursor.cext->prio() == true) {
        status = _fetch_nn(cursor, key, klen, el, elen, leaf, idx, eof);
    } else {
        status = _fetch(cursor, key, klen, el, elen, leaf, idx, eof);
    }
#ifdef AMDB
    // maintain profiling information
    if (_profile != NULL) {
	if (!eof) {
	    // record the returned item (its itemno)
	    _profile->addToResultSet(leaf, idx);
	} else {
	    // query is finished: update the per-query and global
	    // traversal statistics
	    _profile->finalizeQuery(rootNo);
	}
    }
#endif

    if (eof) {
        cursor.reset(); // We're done, get rid of state.
    }
    return (status);
}


/////////////////////////////////////////////////////////////////////////
// _copy_rec - copy lstk entry to output variables
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

inline rc_t
_copy_rec(
    void* key,
    smsize_t& klen,
    void* data,
    smsize_t& dlen,
    shpid_t& leafNo,
    unsigned int& idx,
    gist_lstk_entry& e)
{
    if (klen < e.val.item.klen || dlen < e.val.item.dlen) {
	// not enough space to copy the items
	delete [] e.val.item.key;
	delete [] e.val.item.data;
	e.typ = gist_lstk_entry::eIllegal;	// !gc
	return(eRECWONTFIT);
    }
    
    //copy key and data ptr
    (void) memcpy(key, e.val.item.key, e.val.item.klen);
    klen = e.val.item.klen;
    (void) memcpy(data, e.val.item.data, e.val.item.dlen);
    dlen = e.val.item.dlen;
    leafNo = e.val.item.page;
    idx = e.val.item.idx;
    delete [] e.val.item.key;
    delete [] e.val.item.data;
    e.typ = gist_lstk_entry::eIllegal;		// !gc
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// _fetch - return next match from lookup stack
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_fetch(
    gist_cursor_t&	cursor,
    void*		key,
    smsize_t&		klen,
    void*		data,
    smsize_t&		dlen,
    shpid_t&		leafNo,
    unsigned int&	idx,
    bool&		eof)
{
    AlignedPred x;
    char *k = x.pred; // for 8-byte alignment
    eof = false;
    gist_stack_cursorext_t* cext = (gist_stack_cursorext_t*) cursor.cext;

    int numMatches;
    int matches[gist_p::max_scnt];
    gist_lstk_entry e;
    while (cext->iter_fetch(cursor, &e) != eEOF) {
        if (e.typ == gist_lstk_entry::eItem) {
	    W_DO(_copy_rec(key, klen, data, dlen, leafNo, idx, e));
            return (RCOK);
        }

        // fix the page, process it, then unfix it
	gist_p page;
	W_DO(_fix_page(page, e.val.node.page, LATCH_SH));
	cursor.ext->search(page, cursor.query, matches, numMatches);

	// we needn't push more leaf items on the stack than our retrieval
	// limit would allow us to return (don't try to apply this
	// optimization to priority queues - at this point, we haven't
	// prioritized the items).
	if (page.is_leaf() && numMatches > cursor.k) {
	    numMatches = cursor.k;
	}

	cext->iter_update(cursor, page, numMatches, matches);

#ifdef AMDB
	// break event
	if (_breakHandler != NULL) {
	    // construct bp info
	    amdb_breakpoints::BreakInfo info;
	    info.event = amdb_breakpoints::traversalEvent;
	    info.node = e.val.node.page;
	    (void) _breakHandler(&info);
	}

        // maintain profiling information
	if (_profile != NULL) {
	    _profile->traversePage(page.pid(), page.is_leaf(),
		e.val.node.parent);
	    // count retrievals, now that we're done with the page
	    if (page.is_leaf()) {
	        _profile->countRetrievals(page.pid(), numMatches, matches);
	    }
	}
#endif

	_unfix_page(page);
    }
    e.typ = gist_lstk_entry::eIllegal;		// !gc

    eof = true;
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// _fetch - return next match from lookup stack (nearest neighbor)
//
// Description:
// 	- To keep parents around, we park parent entries on the queue
//	  without ever GCing them.
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_fetch_nn(
    gist_cursor_t&	cursor,
    void*		key,
    smsize_t&		klen,
    void*		data,
    smsize_t&		dlen,
    shpid_t&		leafNo,
    unsigned int&	idx,
    bool&		eof)
{
    eof = false;
    gist_queue_cursorext_t* cext = (gist_queue_cursorext_t*) cursor.cext;

    int numMatches;
    int matches[gist_p::max_scnt];
    gist_prioq_entry e;
    while (cext->iter_fetch(cursor, &e) != eEOF) {
        if (e.typ == gist_lstk_entry::eItem) {
	    W_DO(_copy_rec(key, klen, data, dlen, leafNo, idx, e));
#ifdef AMDB
            if (_profile != NULL) {
		// count 1 retrieved item
	        _profile->countRetrievals(leafNo, 1, (int *) &idx);
	    }
#endif
            return (RCOK);
        }

        // fix the page, process it, then unfix it
	gist_p page;
	W_DO(_fix_page(page, e.val.node.page, LATCH_SH));
	cursor.ext->search(page, cursor.query, matches, numMatches);

	// insert the entries into priority queue
	cext->iter_update(cursor, page, numMatches, matches);

#ifdef AMDB
	// break event
	if (_breakHandler != NULL) {
	    // construct bp info
	    amdb_breakpoints::BreakInfo info;
	    info.event = amdb_breakpoints::traversalEvent;
	    info.node = e.val.node.page;
	    (void) _breakHandler(&info);
	}

        // maintain profiling information
	if (_profile != NULL) {
	    _profile->traversePage(page.pid(), page.is_leaf(), e.val.node.parent);
	}
#endif

	_unfix_page(page);
    }
    e.typ = gist_lstk_entry::eIllegal;		// !gc

    eof = true;
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// _check_node - check node for structural consistency
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

void
gist::_check_node(
    gist_p&		node,
    const vec_t&	bpv)
{
    int recCnt = node.nrecs();
    AlignedPred x;
    vec_t predv;

    for (int i = 0; i < recCnt; i++) {
	const keyrec_t &tup = node.rec(i);
	predv.set(x.pred, gist_p::max_tup_sz);
	_ext->getKey(node, i, predv);
	if (!_ext->check(bpv, predv, node.level())) {
	    fprintf(stderr, "node %d: pred %d not contained in BP\n",
		node.pid(), i);
	}
    }
}


/////////////////////////////////////////////////////////////////////////
// _check_sub - check subtree for structural consistency
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_check_sub(
    shpid_t 		pgno,
    const vec_t&	pred,
    shpid_t		parent,
    int			slot,
    ReachInfo 		reached[])
{
    gist_p page;
    W_DO(_fix_page(page, pgno, LATCH_SH));
    AlignedPred x;
    vec_t predv;

    if (pred.size() != 0) {
	assert(!page.is_root());

	// make sure that the BP contains all other predicates
	_check_node(page, pred);
    }

    if (page.level() > 1) {
	// keep track of nodes reached
	int recCnt = page.nrecs();
	for (int i = 0; i < recCnt; i++) {
	    const keyrec_t &tup = page.rec(i);
	    shpid_t childPtr = tup.child();

	    // check if this is an entry w/ a valid child ptr
	    // (might just be state internal to the node layout)
	    if (childPtr <= 0) continue;

	    if (reached[childPtr].count > 0) {
	        // someone else is pointing to this already
		fprintf(stderr, "additional reference to %d from %d, slot %d\n",
		    childPtr, pgno, i);
	    } else {
	        reached[childPtr].parent = pgno; // that's us
	    }
	    reached[childPtr].count++;

	    // check subtrees recursively
	    predv.set(x.pred, gist_p::max_tup_sz);
	    _ext->getKey(page, i, predv);
	    W_DO(_check_sub(tup.child(), predv, pgno, i, reached));
	}
    }

    _unfix_page(page);
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// check - check tree for structural consistency
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::check()
{
    assert(_isOpen);

    int nodeCnt = _file.size();
    ReachInfo *reached = new ReachInfo[nodeCnt];
	int i;
    for (i = 0; i < nodeCnt; i++) {
	reached[i].count = 0;
	reached[i].parent = 0;
	reached[i].isFree = false;
    }

    reached[rootNo].count = 1;
    W_DO(_check_sub(rootNo, vec_t(), 0, 0, reached));

    // free pages in the file should not be reachable
    shpid_t* freeList = new shpid_t[nodeCnt];
    assert(freeList != NULL);
    int numFree = nodeCnt;
    _file.freelist(freeList, numFree);
    for (i = 0; i < numFree; i++) {
	ReachInfo& info = reached[freeList[i]];
        info.isFree = true;
        if (info.count != 0) {
	    cerr << "free node " << freeList[i] << " referenced "
		 << info.count << " times (orig. parent: " << info.parent
		 << ")" << endl;
	}
    }
    delete [] freeList;

    for (i = 1; i < nodeCnt; i++) {
	ReachInfo& info = reached[i];
	if (info.count != 1 && 
	    !(info.count == 0 && info.isFree)) {

	    // something's fishy
	    cerr << "node " << i << " referenced "
		 << info.count << " times (orig. parent: " << info.parent
		 << ")" << endl;
	}
    }
    delete [] reached;
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// _dump_pg - write contents of single page to output stream
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

void
gist::_dump_pg(
    ostream&		s,
    gist_p&		page)
{
    int lvl = page.level();
    // dump header
    s << "level: " << lvl << " #slots: " << page.nrecs() << " avail: "
        << (int) page.usable_space() << endl;

    // dump contents
    int recCnt = page.nrecs();
    AlignedPred x;
    vec_t keyv;
    for (int i = 0; i < recCnt; i++) {
        const keyrec_t &tup = page.rec(i);
	s << "[" << i << "] <";
	keyv.set(x.pred, gist_p::max_tup_sz);
	_ext->getKey(page, i, keyv);
	_ext->printPred(s, keyv, lvl);
	s << "> len: " << (int) tup.klen();
	if (lvl == 1) {
	    s << " data: ";
	    _ext->printData(s, vec_t(tup.elem(), tup.elen()));
	    s << " len: " << (int) tup.elen() << endl;
	} else {
	    s << " child: " << tup.child() << endl;
	}
    }
}


/////////////////////////////////////////////////////////////////////////
// _dump_sub - dump entire subtree to output stream
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_dump_sub(
    ostream& 		s,
    shpid_t 		pgno)
{
    gist_p page;

    W_DO(_fix_page(page, pgno, LATCH_SH));
    s << "[" << page.pid() << "] ";
    _dump_pg(s, page);
    int recCnt = page.nrecs();
    if (page.level() > 1) {
	for (int i = 0; i < recCnt; i++) {
	    const keyrec_t &tup = page.rec(i);
	    W_DO(_dump_sub(s, tup.child()));
	}
    }
    _unfix_page(page);
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// dump - dump tree to output stream
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::dump(
    ostream&		s,
    shpid_t 		pgno)
{
    if (pgno != 0) {
        gist_p page;
	W_DO(_fix_page(page, pgno, LATCH_SH));
	_dump_pg(s, page);
	_unfix_page(page);
    } else {
        W_DO(_dump_sub(s, rootNo));
    }
    return RCOK;
}


rc_t
gist::dmp(
    shpid_t	pgno)
{
    if (pgno != 0) {
        gist_p page;
	W_DO(_fix_page(page, pgno, LATCH_SH));
	_dump_pg(cout, page);
	_unfix_page(page);
    } else {
        W_DO(_dump_sub(cout, rootNo));
    }
    return(RCOK);
}


/////////////////////////////////////////////////////////////////////////
// _prepare_page - allocate page during bulk loading
//
// Description:
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_prepare_page(
    gist_p&		page,
    shpid_t		rootPid,
    int			level)
{
    W_DO(_new_page(rootPid, page, level)); // first page on level
    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// _finalize_page - finalize page after it was bulk-loaded
//
// Description:
// 	- compute the BP, write it out and unfix the page
//
// Preconditions:
// Postconditions:
// Notes:
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t
gist::_finalize_page(
    gist_p& 	page,
    ostream&	outStream) // receives BPs of finished pages
{
    // compute the BP - even if we have already computed one, it may
    // have been computed incrementally, so compute a tight one now.
    vec_t dummyPred;
    bool dummy;
    AlignedPred x;
    vec_t bpv(x.pred, gist_p::max_tup_sz);
    _ext->unionBp(page, bpv, false, vec_t(), vec_t(), dummy);

    // write to outStream
    int len = bpv.size();
    outStream.write((char *) &len, sizeof(len));
    outStream.write((char *) bpv.ptr(0), len);
    shpid_t pageno = page.pid();
    outStream.write((char *) &pageno, sizeof(pageno));

    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// _build_level - bulk-load one level of tree
//
// Description:
//	- obtain items from tupStream() parameter fct
//	- insert items on current page until we exceed the target
//	  fill factor or tupStream() signals a forced page break
//	- then, compute a BP for the page, write it to bpOutStream
//	  and start a new page
//	- 'page' stays pinned when returning
//
// Return Values:
//      RCOK
/////////////////////////////////////////////////////////////////////////

rc_t		
gist::_build_level(
    TupleStream&	tupStream,
    void*		streamParam,
    float		fillFactor,
    int			level,
    shpid_t 		rootPid,
    ostream&		bpOutStream,
    BreakNotifyFct	breakNotify,
    int&		pageCnt,
    gist_p&		page) // used as the current page to insert on
{
    AlignedPred x, y;
    int klen, dlen;
    vec_t keyv, datav;
    shpid_t child;

//    AlignedPred bpPred;

    // we should keep at least that much free space (make sure it's not uint!)
    int minFreeSpace = (size_t) ((1.0 - fillFactor) * ((float) gist_p::data_sz));
    int itemCnt = 0;

    rc_t status;
    W_DO(_prepare_page(page, rootPid, level)); // first page on level
    pageCnt = 1;
    bool breakPage = false;
    for (;;) {
	status = tupStream(x.pred, klen, y.pred, dlen, child, streamParam);
	if (status != RCOK && status != ePAGEBREAK) {
	    break;
	} 

	if (status == ePAGEBREAK) {
	    // the tuple stream encountered the end-of-page marker
	    breakPage = true;
	    continue; // for
	}

	assert(gist_p::rec_size(klen, dlen) <= gist_p::max_tup_sz);

	// create a new page if the parse routine returned an
	// end-of-page marker or we might exceed the target
	// utilization (we assume that the new record uses up about as
	// much space as its combined key and data sizes, which might
	// not be the case, if we compress records in some way; it
	// seems to be a conservative assumption, because the
	// "compressed" storage shouldn't blow records up).
        if (breakPage ||
	    ((int) page.usable_space() -
	    (int) gist_p::rec_size(klen, dlen) <= minFreeSpace)) {

	    // if this isn't a forced break, the caller might want to
	    // know about it
	    if (!breakPage && breakNotify != NULL) {
	        breakNotify(itemCnt, streamParam);
	    }
	    W_DO(_finalize_page(page, bpOutStream));
	    _unfix_page(page);
	    W_DO(_prepare_page(page, rootPid, level));
	    pageCnt++;
	    breakPage = false;
	    // don't reset BP for new page, we need this BP for union_page() of
	    // the next page
	}

	keyv.set(x.pred, klen);
	datav.set(y.pred, dlen);
	status = _ext->insert(page, keyv, datav, child);
	if (status != RCOK) return status;
	itemCnt++;
    }
    if (status != eEOF) return status;
    if (itemCnt == 0) return eFILEERROR; // can't have empty level
    W_DO(_finalize_page(page, bpOutStream)); // last page
    // don't unfix page, it'll be returned to the caller

    return RCOK;
}


/////////////////////////////////////////////////////////////////////////
// _readBpFromTemp - read BPs from temp file 
//
// Description:
//	- temp file written by _build_level() during build of last level
//
// Return Values:
//      RCOK: BP returned
//	eFILEERROR: something wrong
//	eEOF: no more BPs
/////////////////////////////////////////////////////////////////////////

rc_t		
gist::_readBpFromTemp(
    void* 	key,
    int&	klen,
    void* 	data,
    int&	dlen,
    shpid_t&	child,
    void* 	param)
{
    ifstream* s = (ifstream *) param;

// VCPORT_B
// WIN32 API expects (char *) not (void *)
#ifdef WIN32
	s->read((char *) &klen, sizeof(klen));
#else
    s->read((void *) &klen, sizeof(klen));
#endif
// VCPORT_E

    if (s->eof()) return(eEOF);

// VCPORT_B
// WIN32 API expects (char *) not (void *)
#ifdef WIN32
	s->read((char *) key, klen);
#else
    s->read(key, klen);
#endif
// VCPORT_E

    dlen = 0;

// VCPORT_B
// WIN32 API expects (char *) not (void *)
#ifdef WIN32
	s->read((char *) &child, sizeof(child));
#else
    s->read((void *) &child, sizeof(child));
#endif
// VCPORT_E

    if (!s->eof() && !s->good()) return(eFILEERROR);
    return(RCOK);
}

size_t totalMem = 0;

#if 0
extern void* operator
new(size_t size)
{
    void* p;

    totalMem += size;
    p = malloc(size);
    return p;
}
#endif
