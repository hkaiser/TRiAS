// gist_nptree.cc						-*- c++ -*-
// Copyright (c) 1997, 1998 Regents of the University of California
// $Id: gist_nptree.cc,v 1.3 2000/03/15 00:24:40 mashah Exp $

#ifdef __GNUG__
#pragma implementation "gist_nptree.h"
#endif

#include <stdlib.h>			// for random()

// VCPORT_B
#ifdef WIN32
#include <strstream>

using namespace std;
#else
#include <strstream.h>			// for istrstream()
#endif
// VCPORT_E

#include "gist_compat.h"
#include "gist_nptree.h"
#include "gist_support.h" // for print<>, parse<>, etc.
#include "sequence.h"

// forward declarations
static void _printNptPred( ostream& s, const vec_t& pred, int level);
static rc_t _parseNptPred( const char* str, void* out, int& len);
static rc_t _parseNptQuery( const char* str, gist_query_t*& query);
static rc_t _nptPrio( gist_cursor_t& cursor, const gist_p& page,
    int whichItem, const vec_t& keyv, gist_penalty_t& prio);


///////////////////////////////////////////////////////////////////////////////
// np_query_t methods
///////////////////////////////////////////////////////////////////////////////

np_query_t::~np_query_t() 
{
    if (seq != NULL) {
	free(seq);
    }
}

static nptree_ext_t _nptree_ext;
gist_unorderedn_ext_t npt_ext(gist_ext_t::npt_ext_id,
    "npt_ext", _printNptPred, gist_support::printInt,
    _parseNptPred, gist_support::parseInt,
    _parseNptQuery, _nptree_ext);


////////////////////////////////////////////////////////////////////////////////
// consistent - not used for NP-tree
//
// Description:
//
// Return Values:
//      true
////////////////////////////////////////////////////////////////////////////////

bool
nptree_ext_t::consistent(
    const gist_query_t* query,
    const void *pred,
    int predLen,
    int level) const
{
    return(true);
}


////////////////////////////////////////////////////////////////////////////////
// union - update/recompute profile
//
// Description:
//	- nothing so far, SPs are empty
//
// Return Values:
//      true
////////////////////////////////////////////////////////////////////////////////

void
nptree_ext_t::union_bp(
    const gist_predcursor_t& pcursor, // in
    const gist_p& page, // in
    const vec_t& pred1, // in
    const vec_t& pred2, // in
    vec_t& bp, // in/out
    bool& bpChanged, // out
    bool bpIsValid) // in
    const
{
    if (!bpIsValid) {
	// so far, we only produce empty SPs
        bp.reset();
    } else {
        bpChanged = false;
    }
}


////////////////////////////////////////////////////////////////////////////////
// queryCursor - return NN query cursor
//
// Description:
//
// Return Values:
//      cext_npt cursor ext. or cext_stack_ext
////////////////////////////////////////////////////////////////////////////////

gist_cursorext_t*
nptree_ext_t::queryCursor(
    const gist_query_t* query) const
{
    np_query_t* q = (np_query_t*) query;
    if (q->oper == np_query_t::np_nooper) {
	return(gist_cursorext_t::gist_cursorext_list[
	    gist_cursorext_t::cext_stack_id]);
    } else {
	return(gist_cursorext_t::gist_cursorext_list[
	    gist_cursorext_t::cext_npt_id]);
    }
}


////////////////////////////////////////////////////////////////////////////////
// check - check correctness of profile
//
// Description:
//	- nothing so far, SPs are empty
//
// Return Values:
//      true
////////////////////////////////////////////////////////////////////////////////

bool
nptree_ext_t::check(
    const void *bp, 
    int bplen, 
    const void *pred, 
    int predlen, 
    int level) const
{
    return(true);
}


////////////////////////////////////////////////////////////////////////////////
// penalty - compute insertion penalty
//
// Description:
//	- compute random penalty for now
//
////////////////////////////////////////////////////////////////////////////////

void
nptree_ext_t::penalty(
    const void *subtreePred,
    int predLen,
    int level,
    const void *newKey,
    int keyLen,
    gist_penalty_t &p) const
{

	// VCPORT_B
	//We need a cleaner way of dealing with random numbers. 
	//Perhaps we should include our own random libraries?
#ifdef WIN32
	p = (double) rand();
#else
    p = (double) random();
#endif
	// VCPORT_E

}


////////////////////////////////////////////////////////////////////////////////
// pickSplit - determine split info
//
// Description:
//	- for now, split at midpoint and return empty SPs
//
////////////////////////////////////////////////////////////////////////////////

void
nptree_ext_t::pickSplit(
    gist_predcursor_t &pcursor,
    const gist_p& page,
    int rightEntries[] /*out*/,
    int &numRightEntries /*out*/,
    const void *oldBp,
    int oldLen,
    void *leftBp /*out*/,
    int &leftLen /*in/out*/,
    void *rightBp /*out*/,
    int &rightLen /*int/out*/) const
{
    numRightEntries = pcursor.numElems / 2;
    int i, j;
    for (i = pcursor.numElems - numRightEntries, j = 0; i < pcursor.numElems;
        i++, j++) {

        rightEntries[j] = i;
    }
    leftLen = 0;
    rightLen = 0;
}


////////////////////////////////////////////////////////////////////////////////
// _printNptPred - print nptree predicates
//
// Description:
//	- print string predicates for leaves, nothing for internal nodes
//
////////////////////////////////////////////////////////////////////////////////

static void
_printNptPred(
    ostream& s,
    const vec_t& pred,
    int level)
{
    if (level == 1) {
        char* str = (char*) pred.ptr(0);
	s << str;
    }
}

////////////////////////////////////////////////////////////////////////////////
// _parseNptPred - parse string predicate
//
// Description:
//
////////////////////////////////////////////////////////////////////////////////

static rc_t
_parseNptPred(
    const char* str,
    void* out,
    int& len)
{
    return(gist_support::parseString(str, out, len));
}


////////////////////////////////////////////////////////////////////////////////
// _parseNptQuery - parse NN query with string argument
//
// Description:
//
////////////////////////////////////////////////////////////////////////////////

static rc_t
_parseNptQuery(
    const char* str,
    gist_query_t*& query)
{
    istrstream s(str, strlen(str));
//    rc_t status;
    np_query_t::np_oper oper;

    s >> ws; // remove leading whitespace
    char op[16]; // operator (~)
    s >> op;
    if (s.fail()) {
	// no qualification
	oper = np_query_t::np_nooper;
    } else {
	if (strcmp(op, "~") == 0) {
	    oper = np_query_t::np_nearest;
	} else {
	    // didn't recognize that operator 
	    return(ePARSEERROR);
	}
    }

    if (oper == np_query_t::np_nooper) {
        // no qualification, nothing to parse
	np_query_t* q = new np_query_t(oper, "");
	query = q;
	return(RCOK);
    }

    const int MAXSTRLEN = 8192;
    char arg1[MAXSTRLEN];
//    char arg2[MAXSTRLEN];
    int dummy; // len not needed

    // parse first argument
    W_DO(gist_support::parseString(s, arg1, dummy));

    // construct query
    char* seq = strdup(arg1);
    np_query_t* q = new np_query_t(oper, seq);
    query = q;
    return(RCOK);
}

static rc_t
_nptPrio(
    gist_cursor_t& cursor,	// in 
    const gist_p& page,		// in 
    int whichItem,		// in 
    const vec_t& keyv,		// in 
    gist_penalty_t& prio)	// out
{
    if (page.is_leaf()) {
	const np_query_t* query = (const np_query_t*) cursor.query;
	Sequence querySeq(query->seq);
	Sequence pageSeq((char*) keyv.ptr(0));
	double score, dummyDouble;
	querySeq.localAlign(pageSeq, blosum62, 8, score, dummyDouble);
	prio = score;
    } else {
        prio = 1.0 * MAXINT; // higher than anything localAlign() will return
    }
    return(RCOK);
}

gist_queue_cursorext_t cext_npt(gist_cursorext_t::cext_npt_id, 
    NULL, _nptPrio, NULL, NULL);
