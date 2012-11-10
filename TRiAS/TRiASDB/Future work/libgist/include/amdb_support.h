// amdb_support.h						-*- c++ -*-
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_support.h,v 1.16 2000/03/10 01:39:00 mashah Exp $

#ifndef AMDB_SUPPORT_H
#define AMDB_SUPPORT_H

#ifdef __GNUG__
#pragma interface "amdb_support.h"
#endif

#include <stdio.h>		// for NULL

#include "gist_defs.h"		// for rc_t
#include "gist_disppredcursor.h" 
#include "jni.h"		// for displayPoints() prototype


/*
 * amdb_support:
 *
 * Collection of static routines that can be used for the interface routines of the 
 * amdb_ext_t extension. They are made public through this interface so they can
 * be used for a variety of extensions.
 */

class gist_ext_t;
class gist_p;
class gist_query_t;
class gist_penalty_t;

// VCPORT_B
#ifndef WIN32
class istream;
#endif
// VCPORT_E

class gist_predcursor_t;

class amdb_support
{

public:

    static const int displayDim;

    // penalty in 'unordered' nodes (traditional Gist style)
    static void unorderedPenalty(
	gist_ext_t* e,
	const gist_p& page,
	int slot,
	const void* key,
	int klen,
	const void* data,
	int dlen,
	gist_penalty_t& p);

    static bool unorderedConsistent(
	gist_ext_t* ext,
        const gist_query_t* query,
	const vec_t& pred,
	int level);

    // parse single integer
    static rc_t parseInt(
	const char* str,
	void* out,
	int& len);

    // parse single integer
    static rc_t parseInt(
	istream& s,
	void* out,
	int& len);

    static rc_t parseStr(
	const char* str,
	void* out,
	int& len);

    // parse sequence of doubles, one for each dimension
    static rc_t parsePoint(
	const char* str,
	void* out,
	int& len);

    // same, reading from an istream
    static rc_t parsePoint(
	istream& s,
	void* out,
	int& len);

    static void displayPoints(
        gist_predcursor_t& pcursor,
	JNIEnv* env,
	jint* highlights,
	jint numHighlights,
	jobject graphicsContext, // Java class: java.awt.Graphics
	jobject normalColor,
	jobject highlightColor,
	jint width,
	jint height);

    // parse sequence of doubles, two for each dimension
    static rc_t parseRect(
	const char* str,
	void* out,
	int& len);

    // same, reading from an istream
    static rc_t parseRect(
	istream& s,
	void* out,
	int& len);

    static void  display_bt_int_pred(
        const gist_p& page,
	JNIEnv* env,
	jint* highlights,
	jint numHighlights,
	jobject graphicsContext, // Java class: java.awt.Graphics
	jobject normalColor,
	jobject highlightColor,
	jint width,
	jint height);

    static void  display_bt_int_data(
        const gist_p& page,
	JNIEnv* env,
	jint* highlights,
	jint numHighlights,
	jobject graphicsContext, // Java class: java.awt.Graphics
	jobject normalColor,
	jobject highlightColor,
	jint width,
	jint height);

    static void  display_bt_str_pred(
        const gist_p& page,
	JNIEnv* env,
	jint* highlights,
	jint numHighlights,
	jobject graphicsContext, // Java class: java.awt.Graphics
	jobject normalColor,
	jobject highlightColor,
	jint width,
	jint height);

    static void  display_bt_str_data(
        const gist_p& page,
	JNIEnv* env,
	jint* highlights,
	jint numHighlights,
	jobject graphicsContext, // Java class: java.awt.Graphics
	jobject normalColor,
	jobject highlightColor,
	jint width,
	jint height);

    static void displayRects(
        gist_predcursor_t& pcursor,
	JNIEnv* env,
	jint* highlights,
	jint numHighlights,
	jobject graphicsContext, // Java class: java.awt.Graphics
	jobject normalColor,
	jobject highlightColor,
	jint width,
	jint height);

    static void displayBoundingSpheres(
        gist_predcursor_t& pcursor,
	JNIEnv* env,
	jint* highlights,
	jint numHighlights,
	jobject graphicsContext, // Java class: java.awt.Graphics
	jobject normalColor,
	jobject highlightColor,
	jint width,
	jint height);

    static void displayCentroidSpheres(
        gist_predcursor_t& pcursor,
	JNIEnv* env,
	jint* highlights,
	jint numHighlights,
	jobject graphicsContext, // Java class: java.awt.Graphics
	jobject normalColor,
	jobject highlightColor,
	jint width,
	jint height);

    static void displaySphereRects(
        gist_predcursor_t& pcursor,
	JNIEnv* env,
	jint* highlights,
	jint numHighlights,
	jobject graphicsContext, // Java class: java.awt.Graphics
	jobject normalColor,
	jobject highlightColor,
	jint width,
	jint height);

    // parse query for spatial AMs; returns an rt_query_t in 'query';
    // query looks like "<op> <arg> (<point> | <rect>)", where <op> = [&<>=]
    // and arg = [pr]
    static rc_t parseGeoQuery(
	const char* str,
	gist_query_t*& query);

    static rc_t display_rt_point_preds(
	JNIEnv* env,
	jint    width,
	jint    height,
	jobject graphicsContext, // in: Java class: java.awt.Graphics
	jobject colors[], // in: array of java.awt.Color objects
	gist_disppredcursor_t& pcursor); // in: predicates to display

    static rc_t display_rt_rect_preds(
	JNIEnv* env,
	jint    width,
	jint    height,
	jobject graphicsContext, // in: Java class: java.awt.Graphics
	jobject colors[], // in: array of java.awt.Color objects
	gist_disppredcursor_t& pcursor); // in: predicates to display

    static rc_t display_sp_point_preds(
	JNIEnv* env,
	jint    width,
	jint    height,
	jobject graphicsContext, // in: Java class: java.awt.Graphics
	jobject colors[], // in: array of java.awt.Color objects
	gist_disppredcursor_t& pcursor); // in: predicates to display

    static rc_t display_ss_point_preds(
	JNIEnv* env,
	jint    width,
	jint    height,
	jobject graphicsContext, // in: Java class: java.awt.Graphics
	jobject colors[], // in: array of java.awt.Color objects
	gist_disppredcursor_t& pcursor); // in: predicates to display

    static rc_t display_sr_point_preds(
	JNIEnv* env,
	jint    width,
	jint    height,
	jobject graphicsContext, // in: Java class: java.awt.Graphics
	jobject colors[], // in: array of java.awt.Color objects
	gist_disppredcursor_t& pcursor); // in: predicates to display
};

#endif
