// amdb_rtree.cc						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_rtree.cc,v 1.13 1998/12/22 02:02:12 mashah Exp $

#include "amdb_ext.h"
#include "amdb_support.h"
#include "gist_unordered.h"
#include "gist_disppredcursor.h"

// This bunch of static functions is just a tentative solution. What needs to be done
// is to integrate amdb_ext_t into the class hierarchy and use inheritance for those
// functions.

static void rt_point_display(
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

static void rt_rect_display(
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
    gist_predcursor_t pcursor;
    pcursor.add(page);
    if (pcursor.numElems == 0) return; // nothing to show

    amdb_support::displayRects(pcursor, env, highlights, numHighlights,
	g, normalColor, highlightColor, width, height);
}

static void sp_point_display(
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
    gist_predcursor_t pcursor;
    pcursor.add(page);
    if (pcursor.numElems == 0) return; // nothing to show

    if (page.level() == 1) {
	amdb_support::displayPoints(pcursor, env, highlights, numHighlights,
	    g, normalColor, highlightColor, width, height);
    } else {
	amdb_support::displayBoundingSpheres(pcursor, env, highlights, numHighlights,
	    g, normalColor, highlightColor, width, height);
    }
}

static void ss_point_display(
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
    gist_predcursor_t pcursor;
    pcursor.add(page);
    if (pcursor.numElems == 0) return; // nothing to show

    if (page.level() == 1) {
	amdb_support::displayPoints(pcursor, env, highlights, numHighlights,
	    g, normalColor, highlightColor, width, height);
    } else {
	amdb_support::displayCentroidSpheres(pcursor, env, highlights, numHighlights,
	    g, normalColor, highlightColor, width, height);
    }
}

static void sr_point_display(
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
    gist_predcursor_t pcursor;
    pcursor.add(page);
    if (pcursor.numElems == 0) return; // nothing to show

    if (page.level() == 1) {
	amdb_support::displayPoints(pcursor, env, highlights, numHighlights,
	    g, normalColor, highlightColor, width, height);
    } else {
	amdb_support::displaySphereRects(pcursor, env, highlights, numHighlights,
	    g, normalColor, highlightColor, width, height);
    }
}

static void rt_point_display_preds(
	JNIEnv* env, // in
	jint width, // in: width of window
	jint height, // in: height of window
	jobject graphicsContext, // in: Java class: java.awt.Graphics
	jobject colors[], // in: array of java.awt.Color objects
	gist_disppredcursor_t& pcursor) // in: predicates to display
{

    if (pcursor.numPreds() == 0) return; // nothing to show

}

amdb_ext_t amdb_rt_point_ext(gist_ext_t::rt_point_ext_id, 
    amdb_support::unorderedPenalty, rt_point_display, 
    amdb_support::display_rt_point_preds, 
    amdb_support::unorderedConsistent);

amdb_ext_t amdb_rt_rect_ext(gist_ext_t::rt_rect_ext_id, 
    amdb_support::unorderedPenalty, rt_rect_display, 
    amdb_support::display_rt_rect_preds, 
    amdb_support::unorderedConsistent);

amdb_ext_t amdb_sp_point_ext(gist_ext_t::sp_point_ext_id, 
    amdb_support::unorderedPenalty, sp_point_display, 
    amdb_support::display_sp_point_preds, 
    amdb_support::unorderedConsistent);

amdb_ext_t amdb_ss_point_ext(gist_ext_t::ss_point_ext_id, 
    amdb_support::unorderedPenalty, ss_point_display, 
    amdb_support::display_ss_point_preds, 
    amdb_support::unorderedConsistent);

amdb_ext_t amdb_sr_point_ext(gist_ext_t::sr_point_ext_id, 
    amdb_support::unorderedPenalty, sr_point_display, 
    amdb_support::display_sr_point_preds, 
    amdb_support::unorderedConsistent);

amdb_ext_t amdb_rr_point_ext(gist_ext_t::rr_point_ext_id, 
    amdb_support::unorderedPenalty, rt_point_display,
    amdb_support::display_rt_point_preds,
    amdb_support::unorderedConsistent);
