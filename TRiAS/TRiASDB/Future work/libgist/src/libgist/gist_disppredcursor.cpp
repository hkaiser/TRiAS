// gist_disppredcursor.cc
// Copyright (c) 1998, Regents of the University of California
// $Id: gist_disppredcursor.cc,v 1.5 2000/03/15 00:24:25 mashah Exp $


#include <assert.h>
#include "gist_p.h"
#include "gist.h"

#ifdef __GNUG__
#pragma implementation "gist_disppredcursor.h"
#endif
#include "gist_disppredcursor.h"

// STL
// VCPORT_B
#ifdef WIN32
#include <algorithm>

using namespace std;
#else
#include <algo.h>
#endif
// VCPORT_E

///////////////////////////////////////////////////////////////////////////////
// gist_disppredcursor_t::gist_disppredcursor_t - constructor
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

gist_disppredcursor_t::gist_disppredcursor_t(
    gist* index) :
    _index(index), _predInfo(), _next(0), _page()
{
}


///////////////////////////////////////////////////////////////////////////////
// gist_disppredcursor_t::~gist_disppredcursor_t - destructor
//
// Description:
//
///////////////////////////////////////////////////////////////////////////////

gist_disppredcursor_t::~gist_disppredcursor_t()
{
    PredInfoVector::iterator it;
    for (it = _predInfo.begin(); it != _predInfo.end(); it++) {
        gist::DisplayPredInfo* info = (gist::DisplayPredInfo *) *it;
	delete info;
    }
}


///////////////////////////////////////////////////////////////////////////////
// gist_disppredcursor_t::getNext -
// 	returns next predicate (color only used for display purposes)
//
// Description:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

rc_t
gist_disppredcursor_t::getNext(
    void*& key, // out
    int& klen, // out
    int& level, // out
    int& color) // out
{
    if (_next >= _predInfo.size()) {
        return(eEOF);
    }

    gist::DisplayPredInfo* info = (gist::DisplayPredInfo*) _predInfo[_next];
    _next++;
    assert(info != NULL);

    // fix page containing pred, if necessary 
    if (!_page.is_fixed() || _page.pid() != info->node) {
        if (_page.is_fixed()) {
	    _index->_unfix_page(_page);
	}
	W_DO(_index->_fix_page(_page, info->node, LATCH_SH));
    }

    // extract key
    vec_t keyv(_key, gist_p::max_tup_sz);
    _index->extension()->getKey(_page, info->slot, keyv);
    key = keyv.ptr(0);
    klen = keyv.len(0);
    level = info->level;
    color = info->color;

    return(RCOK);
}


///////////////////////////////////////////////////////////////////////////////
// gist_disppredcursor_t::numPreds -
// 	returns remaining number of predicates in cursor
//
// Description:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

int
gist_disppredcursor_t::numPreds()
{
    return(_predInfo.size() - _next);
}


///////////////////////////////////////////////////////////////////////////////
// gist_disppredcursor_t::add - add single predicate
//
// Description:
//
// Return Values:
//      RCOK
///////////////////////////////////////////////////////////////////////////////

void
gist_disppredcursor_t::add(
    shpid_t pageno,
    int slot,
    int level,
    int color)
{
    gist::DisplayPredInfo* info = new gist::DisplayPredInfo(pageno, slot,
        level, color);
    assert(info != NULL);
    info->node = pageno;
    info->slot = slot;
    info->level = level;
    info->color = color;
    _predInfo.push_back((void *) info);
}

// add all predicates on page
rc_t
gist_disppredcursor_t::add(
    shpid_t pageno,
    int level,
    int color)
{
    // don't use _page here, this would fuck up ongoing scans
    gist_p page;
    W_DO(_index->_fix_page(page, pageno, LATCH_SH));
    int recCnt = page.nrecs();
    int i;
    for (i = 0; i < recCnt; i++) {
        _predInfo.push_back((void *) new gist::DisplayPredInfo(pageno, i,
	    level, color));
    }
    _index->_unfix_page(page);
    return(RCOK);
}

