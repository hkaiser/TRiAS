// amdb_btree.cc
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_btree.cc,v 1.17 2000/03/15 00:24:09 mashah Exp $

#include <stdio.h>
#include <malloc.h>
#include "gist_defs.h"
#include "amdb_ext.h"
#include "amdb_support.h"
#include "gist_btree.h"

// VCPORT_B
#ifdef WIN32
#include <strstream>
#include <iostream>
#else
#include <strstream.h>
#include <iostream.h>
#endif
// VCPORT_E

static bool
btConsistent(
    gist_ext_t* ext,
    const gist_query_t* query,
    const vec_t& pred,
    int level)
{
    assert(0);
    return(false);
}

// penalty in B-trees: 1 if newKey outside interval at slot, otherwise 0
static void
btPenalty(
    gist_ext_t* e,
    const gist_p& page,
    int slot,
    const void* key,
    int klen,
    const void* data,
    int dlen,
    gist_penalty_t& p)
{
    assert(!page.is_leaf());
    bt_ext_t* ext = (bt_ext_t *) e;
    const keyrec_t& left = page.rec(slot);
    const void* slotkey = left.key();
    const void* slotdata = (const void *) (((char *) slotkey) + ext->keySize(slotkey));
    int res = ext->keyCmp(key, slotkey);
    if (res < 0 || (res == 0 && ext->dataCmp(data, slotdata) < 0)) {
        // key to left of interval
	p = 1.0;
	return;
    }
    if (slot < page.nrecs() - 1) {
        // there's a right neighbor slot, let's check it out
	const keyrec_t& right = page.rec(slot+1);
	slotkey = right.key();
	slotdata = (const void *) (((char *) slotkey) + ext->keySize(slotkey));
	res = ext->keyCmp(key, slotkey);
	if (res >= 0 || (res == 0 && ext->dataCmp(data, slotdata) >= 0)) {
	    // key to right of interval
	    p = 1.0;
	    return;
	}
    }
    // we're apparently inside the interval (although that's not entirely clear:
    // if the slot happens to be the last one on the page, and it's left boundary is 
    // smaller than the key, we simply assume to be within the interval, although
    // the true node boundaries might contradict that)
    p = 0.0;
}

static void
bt_int_display(
    const gist_p& page,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject g, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{
    if (page.nrecs() == 0) return; // nothing to show.

    if (page.level() == 1) {
        amdb_support::display_bt_int_data(page, env, highlights, 
            numHighlights, g, normalColor, highlightColor, width, height);
    } else {
        amdb_support::display_bt_int_pred(page, env, highlights,
	    numHighlights, g, normalColor, highlightColor, width, height);
    }
}

static void bt_str_display(
    const gist_p& page,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject g, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{
    if (page.nrecs() == 0) return; // nothing to show.

    if (page.level() == 1) {
        amdb_support::display_bt_str_data(page, env, highlights, 
            numHighlights, g, normalColor, highlightColor, width, height);
    } else {
        amdb_support::display_bt_str_pred(page, env, highlights,
	    numHighlights, g, normalColor, highlightColor, width, height);
    }
}

amdb_ext_t amdb_bt_int_ext(gist_ext_t::bt_int_ext_id, btPenalty, bt_int_display,
    NULL, btConsistent);
amdb_ext_t amdb_bt_str_ext(gist_ext_t::bt_str_ext_id, btPenalty, bt_str_display,
    NULL, btConsistent);
