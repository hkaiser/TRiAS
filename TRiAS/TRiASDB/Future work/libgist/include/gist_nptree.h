// gist_nptree.h					-*- c++ -*-
// Copyright (c) 1997, 1998, Regents of the University of California
// $Id: gist_nptree.h,v 1.1 1999/09/27 01:08:52 marcel Exp $

#ifndef GIST_NPTREE_H
#define GIST_NPTREE_H

#ifdef __GNUG__
#pragma interface "gist_nptree.h"
#endif

#include "gist_query.h"		// for gist_query_t
#include "gist_cursorext.h"	// for gist_cursorext_t::*
#include "gist_unordered.h"	// for gist_unordered_ext_t
#include "gist_unorderedn.h"	// for gist_unorderedn_ext_t
#ifdef AMDB
#include "amdb_ext.h"
#endif



///////////////////////////////////////////////////////////////////////////////
// np_query_t
///////////////////////////////////////////////////////////////////////////////

class np_query_t : public gist_query_t {
public:
    enum np_oper {
        np_nooper,
	np_nearest,
	set_numoper
    };

    np_query_t(np_oper oper, const char* seq) :
        oper(oper), seq(strdup(seq)) {}

    ~np_query_t(); // calls destructor for parameter

    np_oper oper;
    char* seq;
};

///////////////////////////////////////////////////////////////////////////////
// nptree_ext_t
///////////////////////////////////////////////////////////////////////////////

class nptree_ext_t : public gist_unordered_ext_t {
public:

    nptree_ext_t() {}

    bool consistent(
        const gist_query_t* query,
	const void *pred,
	int predLen,
	int level) const;

    void union_bp(
	const gist_predcursor_t& pcursor, // in
	const gist_p& page, // in
	const vec_t& pred1, // in
	const vec_t& pred2, // in
	vec_t& bp, // in/out
	bool& bpChanged, // out
	bool bpIsValid) // in
	const;

    gist_cursorext_t* queryCursor(
	const gist_query_t* query) const;

    bool check(
        const void *bp, 
	int bplen, 
	const void *pred, 
	int predlen, 
	int level) const; 

    void penalty(
        const void *subtreePred,
	int predLen,
	int level,
	const void *newKey,
	int keyLen,
	gist_penalty_t &p) const;

    void pickSplit(
        gist_predcursor_t &pcursor,
	const gist_p& page,
	int rightEntries[] /*out*/,
	int &numRightEntries /*out*/,
	const void *oldBp,
	int oldLen,
	void *leftBp /*out*/,
	int &leftLen /*in/out*/,
	void *rightBp /*out*/,
	int &rightLen /*int/out*/) const;
};

extern gist_unorderedn_ext_t npt_ext;

#ifdef AMDB
extern amdb_ext_t amdb_npt_ext;
#endif // AMDB

#endif // GIST_NPTREE_H
