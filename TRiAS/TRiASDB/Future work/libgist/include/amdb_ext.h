// amdb_ext.h							-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_ext.h,v 1.12 1998/12/13 00:01:06 marcel Exp $

#ifndef AMDB_EXT_H
#define AMDB_EXT_H

#include "gist_defs.h"		// for rc_t
#include "gist_ext.h"		// for gist_ext_t::gist_ext_ids
#include "jni.h"		// for display() prototype

/*
 * Interface for Amdb extension classes. 
 * 
 * These are parallel to the libgist extension classes: each libgist extension
 * class has one amdb extension class. Upon successful completion of a parse
 * function, it must return RCOK, otherwise ePARSEERROR. The parsed
 * object is returned through the 'out' parameter and its lengths through the
 * 'len' parameter (the latter is not necessary for queries). The 'out'
 * parameter in ParseFct can be assumed to point to allocated memory, allocation
 * is therefore not necessary.  The 'out' parameter in ParseQueryFct does not
 * point to allocated memory, the function must allocated the appropriate data
 * structure itself. The reason is that a query is a possibly complex data
 * structure that cannot easily be laid out sequentially in memory. Allocation
 * is therefore best done with a constructor. 
 *
 * The penalty function is necessary for penalty checks. The corresponding
 * function in gist_ext_t, findMinPen, only returns the slot index of the item
 * with the minimum insertion penalty and cannot be used.
 */

class gist_query_t;
class gist_disppredcursor_t;

class amdb_ext_t {

public:

    gist_ext_t::gist_ext_ids id; // our ID
    static amdb_ext_t* amdb_ext_list[gist_ext_t::gist_numext];
    static amdb_ext_t* extension(gist_ext_t* ext) 
    {
        return (amdb_ext_list[ext->myId]);
    }

    // returns insertion penalty of new (key, data) pair into subtree given by slot
    // (just passing the key at that slot is not enough, because part of it might be
    // elsewhere on the page)
    // XXX currently, this is only needed by gist_m::_collect_penalties(), which we
    // don\'t really use anymore - we should retire this at some point
    typedef void (*PenaltyFct)(
	gist_ext_t* ext,
	const gist_p& page,
	int slot,
	const void* key,
	int klen,
	const void* data,
	int dlen,
	gist_penalty_t& p);
    PenaltyFct penalty;

    // draws the content of the given page via Java Graphics calls
    typedef void (*DisplayFct)(
        const gist_p& page,
	JNIEnv* env,
	jint* highlights,
	jint numHighlights,
	jobject graphicsContext, // Java class: java.awt.Graphics
	jobject normalColor,
	jobject highlightColor,
	jint width,
	jint height);
    DisplayFct display;

    // draws the content of the given page via Java Graphics calls
    typedef rc_t (*DisplayPredsFct)(
	JNIEnv* env, // in
	jint width, // in: width of window
	jint height, // in: height of window
	jobject graphicsContext, // in: Java class: java.awt.Graphics
	jobject colors[], // in: array of java.awt.Color objects
	gist_disppredcursor_t& pcursor); // in: predicates to display
    DisplayPredsFct displayPreds;

    // consistent: evaluates pred w.r.t. query
    typedef bool (*ConsistentFct)(
	gist_ext_t* ext,
        const gist_query_t* query,
	const vec_t& pred,
	int level); // at what level was that predicate found (leaf = 1)
    ConsistentFct consistent;

    amdb_ext_t(
        gist_ext_t::gist_ext_ids id,
	PenaltyFct p,
	DisplayFct d,
	DisplayPredsFct dp,
        ConsistentFct consistent);

};

#endif
