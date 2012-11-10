// amdb_rstartree.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_rstartree.cc,v 1.11 2000/03/15 00:24:50 mashah Exp $

#include "amdb_ext.h"

// VCPORT_B
#ifdef WIN32
#include <iostream>

using namespace std;
#else
#include <iostream.h>
#endif
// VCPORT_E

#include "amdb_support.h"
#include "gist_p.h"
#include "gist_unordered.h"

static void
rstar_point_display(
    const gist_p& page,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject g, // Java class: java.awt.Graphics
    jobject normalColor, // Java class: java.awt.Color
    jobject highlightColor, // Java class: java.awt.Color
    jint width,
    jint height)
{
    gist_predcursor_t pcursor;
    pcursor.add(page);
    if (pcursor.numElems == 0) return; // nothing to show

    if (page.level() == 1) {
        amdb_support::displayPoints(pcursor, env, highlights, numHighlights,
	    g, normalColor, highlightColor, width, height);
    } else {
        amdb_support::displayRects(pcursor, env, highlights, numHighlights,
	    g, normalColor, highlightColor, width, height);
    }
}

static void
rstar_rect_display(
    const gist_p& page,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject g, // Java class: java.awt.Graphics
    jobject normalColor, // Java class: java.awt.Color
    jobject highlightColor, // Java class: java.awt.Color
    jint width,
    jint height)
{
    gist_predcursor_t pcursor;
    pcursor.add(page);
    if (pcursor.numElems == 0) return; // nothing to show

    amdb_support::displayRects(pcursor, env, highlights, numHighlights, 
        g, normalColor, highlightColor, width, height);
}

amdb_ext_t amdb_rstar_point_ext(gist_ext_t::rstar_point_ext_id, 
    amdb_support::unorderedPenalty, rstar_point_display,
    amdb_support::display_rt_point_preds, 
    amdb_support::unorderedConsistent);
amdb_ext_t amdb_rstar_rect_ext(gist_ext_t::rstar_rect_ext_id, 
    amdb_support::unorderedPenalty, rstar_rect_display, NULL,
    amdb_support::unorderedConsistent);
