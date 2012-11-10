// amdb_support.cc
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_support.cc,v 1.24 2000/03/15 00:24:21 mashah Exp $

#ifdef __GNUG__
#pragma implementation "amdb_support.h"
#endif

// VCPORT_B
#ifdef WIN32
#include <iostream>
#include <strstream>

using namespace std;
#else
#include <iostream.h>
#include <strstream.h>
#endif
// VCPORT_E

#include <stdio.h>
#include "gist_defs.h"
#include "gist_ext.h"
#include "gist_compat.h"
#include "gist_unorderedn.h"
#include "gist_unordered.h"
#include "amdb_support.h"
#include "gist_rtpred_point.h"
#include "gist_rtpred_rect.h"
#include "gist_rtpred_sphere.h"
#include "gist_rtpred_ss.h"
#include "gist_rtpred_sr.h"
#include "gist_rtree.h"		// for rt_query_t
#include "gist_disppredcursor.h"
#include <math.h>
#include <stdlib.h>

#define HANDLEEXC(env)	\
{	\
    jthrowable exc = (env)->ExceptionOccurred();	\
    if (exc) {	\
        (env)->ExceptionDescribe();	\
	return;	\
    }	\
}

static bool idsInitialized = false;
static jmethodID drawRectId;
static jmethodID setColorId;
static jmethodID drawOvalId;
static jmethodID verticalId;
static jmethodID horizontalId;
static jmethodID translateId;
static jclass paintScaleClass;

static void
initIds(JNIEnv* env, jobject gc)
{
    if (idsInitialized) {
        return;
    }
    // make java.awt.Graphics global and determine various method ID
    jclass cl = env->GetObjectClass(gc);
    HANDLEEXC(env);
    jclass graphicsClass = (jclass) env->NewGlobalRef(cl);
    HANDLEEXC(env);
    drawOvalId = env->GetMethodID(graphicsClass, "drawOval", "(IIII)V");
    HANDLEEXC(env);
    drawRectId = env->GetMethodID(graphicsClass, "drawRect", "(IIII)V");
    HANDLEEXC(env);
    setColorId = env->GetMethodID(graphicsClass, "setColor", 
	"(Ljava/awt/Color;)V");
    HANDLEEXC(env);
    translateId = env->GetMethodID(graphicsClass, "translate", "(II)V");
    HANDLEEXC(env);
    jclass pl = env->FindClass("PaintScale");
    HANDLEEXC(env);
    paintScaleClass = (jclass) env->NewGlobalRef(pl);
    HANDLEEXC(env);
    verticalId = env->GetStaticMethodID(paintScaleClass, "vertical",
	"(Ljava/awt/Graphics;IIIFFII)I");
    HANDLEEXC(env);
    horizontalId = env->GetStaticMethodID(paintScaleClass, "horizontal", 
	"(Ljava/awt/Graphics;IIIFFI)I");
    HANDLEEXC(env);
    idsInitialized = true;
}

// VCPORT_B
const int amdb_support::displayDim = 2;
	// we can only display data in 2 dimensions; applies to all display functions
// VCPORT_E

void
amdb_support::unorderedPenalty(
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
    const gist_unordered_ext_t* ext = &((gist_unorderedn_ext_t *) e)->ext;
    const keyrec_t& tup = page.rec(slot);
    ext->penalty(tup.key(), tup.klen(), page.level(), key, klen, p);
}


/////////////////////////////////////////////////////////////////////////
// amdb_support::unorderedConsistent - call gist_unordered_t.consistent()
//
// Description:
//
// Return Values:
//      true/false
/////////////////////////////////////////////////////////////////////////

bool
amdb_support::unorderedConsistent(
    gist_ext_t* ext,
    const gist_query_t* query,
    const vec_t& pred,
    int level)
{
    const gist_unordered_ext_t* e = &((gist_unorderedn_ext_t *) ext)->ext;
    return(e->consistent(query, pred.ptr(0), pred.len(0), level));
}


rc_t
amdb_support::parseStr(
    const char* str,
    void* out,
    int& len)
{
    (void) strcpy((char *) out, str);
    len = strlen(str) + 1;
    return RCOK;
}

static rc_t
parseStr(
    const char* str,
    void* out,
    smsize_t& len)
{
    (void) strcpy((char *) out, str);
    len = strlen(str) + 1;
    return RCOK;
}


rc_t
amdb_support::parseInt(
    const char* str,
    void* out,
    int& len)
{
    istrstream s(str, strlen(str));
    return parseInt(s, out, len);
}

rc_t
amdb_support::parseInt(
    istream& s,
    void* out,
    int& len)
{
    s >> *((int *) out);
    if (s.fail()) return ePARSEERROR;
    len = sizeof(int);
    return RCOK;
}

rc_t
amdb_support::parsePoint(
    const char* str,
    void* out,
    int& len)
{
    istrstream s(str, strlen(str));
    return parsePoint(s, out, len);
}

#if 0
rc_t
amdb_support::parsePoint(
    istream& s,
    void* out,
    int& len)
{
    bool pageEnd = false;
    double* coords = (double *) out;
    int dims = 0;
    while (!s.eof()) {
	s >> *coords;
	if (s.fail()) {
	    // something went wrong
	    return ePARSEERROR;
	}
	coords++;
	dims++;
    }
    if (dims == 0) return ePARSEERROR; // can't have point with 0 dimensions
    len = pageEnd ? 0 : dims * sizeof(double);
    return RCOK;
}
#endif

rc_t
amdb_support::parsePoint(
    istream& s,
    void* out,
    int& len)
{
    double* coords = (double *) out;
    int dims = 0;
    while (s >> *coords) {
	coords++;
	dims++;
    }
    if (dims == 0) {
        return(ePARSEERROR); // can't have point with 0 dimensions
    }
    len = dims * sizeof(double);
    return(RCOK);
}

// returns -1 if it could not draw both scales sucessfully ...
// modifies w, h, and translates graphics context ...
int
drawScales(
    jint *w,
    jint *h,
    double xmin,
    double xmax,
    double ymin,
    double ymax,
    JNIEnv* env, 
    jobject& graphicsContext)
{
    jint width  = *w;
    jint height = *h;

    jint textheight = 10;
    jint leftborder = 2;
    jint rightborder = 2;

    jint topborder = textheight / 2;
    
    jint tickheight = 4;

    height -= textheight + tickheight + 7;

    // paint vertical scale ...
    jint sw = 
	env->CallStaticIntMethod(paintScaleClass, verticalId, 
	    graphicsContext, leftborder, topborder, 
	    height, (float) ymin, 
	    (float) ymax, 5, 1);

    sw += leftborder + rightborder + 1;

    // draw y-axis ...
    env->CallVoidMethod(graphicsContext, drawRectId, sw - rightborder, 5, 0, 
	height - topborder + 1);

    // paint horizontal scale ...
    
    jint ew =
	env->CallStaticIntMethod(paintScaleClass, horizontalId,
	    graphicsContext, height + 1, sw, width, (float) xmin,
	    (float) xmax, 5);

    *w = width = ew;
    if (width < 0) {
	*h = height - topborder;
	return 1;
    }

    // draw x-axis ..
    env->CallVoidMethod(graphicsContext, drawRectId, sw - 1, height + 1, ew,
	0);

    // width -= sw + ew;
    height -= topborder;
    *h = height;
    if (height < 0) 
	return 1;

    env->CallVoidMethod(graphicsContext, translateId, sw, topborder);
    
    return 0;
}


// display a page full of predicates for bt_int ...

void 
amdb_support::display_bt_int_pred(
    const gist_p& page,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject graphicsContext, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{

    int ntups = page.nrecs();

    int i;
    
    int key;

    for (i = 0; i < ntups; i++) {
	const keyrec_t &tup = page.rec(i);
	
	// can't print directly ... sometimes not aligned.

	(void) memcpy((void *) &key, tup.key(), sizeof(i));

	cout << "key: " << key << " child: " << tup.child() << endl;

    }

}

// display a page full of data for bt_int ...

void
amdb_support::display_bt_int_data(
    const gist_p& page,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject graphicsContext, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{

    int ntups = page.nrecs();

    int i;

    int key, data;

    for (i = 0; i < ntups; i++) {
	const keyrec_t &tup = page.rec(i);

	(void) memcpy ((void *) &key, tup.key(), sizeof(i));

	(void) memcpy ((void *) &data, tup.elem(), sizeof(i));

	cout << "key: " << key << " data: " << data << endl;
    }

}

// display a page full of strings ....

void 
amdb_support::display_bt_str_pred(
    const gist_p& page,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject graphicsContext, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{

    int ntups = page.nrecs();

    int i;
    
    const char *key;

    for (i = 0; i < ntups; i++) {
	const keyrec_t &tup = page.rec(i);
	
	// can't print directly ... sometimes not aligned.
	
	key = tup.key();

	cout << "key: " << key << " child: " << tup.child() << endl;

    }

}

// display a page full of string and data ...

void
amdb_support::display_bt_str_data(
    const gist_p& page,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject graphicsContext, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{

    int ntups = page.nrecs();

    int i;

    const char *key;
    int data;

    for (i = 0; i < ntups; i++) {
	const keyrec_t &tup = page.rec(i);

	key = tup.key();

	(void) memcpy ((void *) &data, tup.elem(), sizeof(i));

	cout << "key: " << key << " data: " << data << endl;
    }

}

// display a page full of points
void
amdb_support::displayPoints(
    gist_predcursor_t& pcursor,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject graphicsContext, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{
    initIds(env, graphicsContext);

    // we can only display 2-dim data
    int dim = rt_point::size2dim(pcursor.elems[0].keyLen);
    if (dim != displayDim) return;

    // find min/max along each dimension
    double min[displayDim];
    double max[displayDim];
    // stored points are arrays of dim doubles
	int i;
    for (i = 0; i < pcursor.numElems; i++) {
        rt_point pt(dim, (const double *) pcursor.elems[i].key);
		int j;
	for (j = 0; j < displayDim; j++) {
	    if (i == 0) {
		min[j] = pt.co(j);
		max[j] = pt.co(j);
	    } else {
		if (min[j] > pt.co(j)) min[j] = pt.co(j);
		if (max[j] < pt.co(j)) max[j] = pt.co(j);
	    }
	}
    }

    int notok = drawScales(&width, &height, min[0], max[0], min[1], max[1],
	env, graphicsContext);
    
    if (notok)
	return;

    double scales[displayDim];

    scales[0] = ((double) width) / (max[0] - min[0]);
    scales[1] = ((double) height) / (max[1] - min[1]);

    // draw non-highlighted points
    int j = 0; // index into highlights
    env->CallVoidMethod(graphicsContext, setColorId, normalColor);
    for (i = 0; i < pcursor.numElems; i++) {
	rt_point pt(dim, (const double *) pcursor.elems[i].key);
        int x = (int) floor((pt.co(0) - min[0]) * scales[0]);
        int y = height - (int) floor((pt.co(1) - min[1]) * scales[1]);
	// decide which color to use
	if (j < numHighlights && highlights[j] == i) {
	    // this is to be highlighted; we'll do that later
	    j++;
	} else {
	    env->CallVoidMethod(graphicsContext, drawRectId, x, y, 1, 1);
	}
    }

    // draw highlighted points after the non-highlighted ones, so we don't 
    // obscure the highlights
    env->CallVoidMethod(graphicsContext, setColorId, highlightColor);
    for (i = 0; i < numHighlights; i++) {
	rt_point pt(dim, (const double *) pcursor.elems[highlights[i]].key);
        int x = (int) floor((pt.co(0) - min[0]) * scales[0]);
        int y = height - (int) floor((pt.co(1) - min[1]) * scales[1]);
	env->CallVoidMethod(graphicsContext, drawRectId, x, height - y, 1, 1);
    }

}

rc_t
amdb_support::parseRect(
    const char* str,
    void* out,
    int& len)
{
    istrstream s(str, strlen(str));
    return parseRect(s, out, len);
}

rc_t
amdb_support::parseRect(
    istream& s,
    void* out,
    int& len)
{
    double* coords = (double *) out;
    int dims = 0;
    while (!s.eof()) {
        s >> *coords;
	if (s.fail() || s.eof()) return ePARSEERROR;
        s >> *(coords + 1);
	if (s.fail()) return ePARSEERROR;
	coords += 2;
	dims++;
    }
    if (dims == 0) return ePARSEERROR;
    len = dims * 2 * sizeof(double);
    return RCOK;
}

// display scales ...

// returns the height of the horizontal scale drawn on bottom border ...
// void
// amdb_support::dispHscale() {

// }

// // returns the width of vertical scale drawn on left border ...
// int
// amdb_support::dispVscale(
//     int numTicks,
//     double min,
//     double max,
//     int ymin,
//     int ymax,
//     jobject graphicsContext,
//     jobject fontMetrics,
//     jobject normalColor,
//     JNIEnv* env
// )
// {
//     int h = ymax - ymin;
//     double range = max - min;

//     double d = (double) h / (double) numTicks;

//     double dv = (double) range / (double) numTicks;
    
//     int strh, strw = 0, maxstrw = 0;

//     env->CallVoidMethod(graphicsContext, setColorId, normalColor);

//     int pos;

//     double value;

//     for (i = 0; i < numTicks; i++) {
	
// 	pos   = (int)   floor(i*d);
// 	value = (double) ( rint(i * d * 100) / 100.00 ) + min;
	
// 	strw = env->CallIntMethod(
	
//     }

// }

// display a page full of rectangles
void
amdb_support::displayRects(
    gist_predcursor_t& pcursor,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject graphicsContext, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{
    initIds(env, graphicsContext);

    // we can only display 2-dim data
    int dim = rt_rect::size2dim(pcursor.elems[0].keyLen);
    
    // Uncomment if you care ...
    // if (dim != displayDim) return;

    // find min/max along each dimension
    double min[displayDim];
    double max[displayDim];
	int i;
    for (i = 0; i < pcursor.numElems; i++) {
        rt_rect r(dim, (const double *) pcursor.elems[i].key);
		int j;
	for (j = 0; j < displayDim; j++) {
	    if (i == 0) {
		min[j] = r.lo(j);
		max[j] = r.hi(j);
	    } else {
		if (min[j] > r.lo(j)) min[j] = r.lo(j);
		if (max[j] < r.hi(j)) max[j] = r.hi(j);
	    }
	}
    }

    int notok = drawScales(&width, &height, min[0], max[0], min[1], max[1],
	env, graphicsContext);
    
    if (notok)
	return;

    double scales[displayDim];
    scales[0] = ((double) width) / (max[0] - min[0]);
    scales[1] = ((double) height) / (max[1] - min[1]);

    // draw non-highlighted rects
    env->CallVoidMethod(graphicsContext, setColorId, normalColor);
    int j = 0; // index into hightlights
    for (i = 0; i < pcursor.numElems; i++) {
	rt_rect r(dim, (const double *) pcursor.elems[i].key);
        int x1 = (int) floor((r.lo(0) - min[0]) * scales[0]);
        int x2 = (int) floor((r.hi(0) - min[0]) * scales[0]);
        int y1 = (int) floor((r.lo(1) - min[1]) * scales[1]);
        int y2 = (int) floor((r.hi(1) - min[1]) * scales[1]);
	// decide which color to use
	if (j < numHighlights && highlights[j] == i) {
	    // this is to be highlighted; we'll draw that later
	    j++;
	} else {
	    y1 = height - y1;
	    y2 = height - y2;
	    env->CallVoidMethod(graphicsContext, drawRectId, x1, y2, x2-x1, 
		abs(y2-y1));
	}
    }

    // draw highlighted rects after non-highlighted ones, so we don't obscure
    // the highlights
    env->CallVoidMethod(graphicsContext, setColorId, highlightColor);
    for (i = 0; i < numHighlights; i++) {
	rt_rect r(dim, (const double *) pcursor.elems[highlights[i]].key);
        int x1 = (int) floor((r.lo(0) - min[0]) * scales[0]);
        int x2 = (int) floor((r.hi(0) - min[0]) * scales[0]);
        int y1 = (int) floor((r.lo(1) - min[1]) * scales[1]);
        int y2 = (int) floor((r.hi(1) - min[1]) * scales[1]);
	y1 = height - y1;
	y2 = height - y2;
	env->CallVoidMethod(graphicsContext, drawRectId, x1, y2, x2-x1, 
	    abs(y2-y1));
    }

}


void
amdb_support::displayBoundingSpheres(
    gist_predcursor_t& pcursor,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject graphicsContext, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{
    initIds(env, graphicsContext);
    
    // we can only display 2-dim data
    int dim = rt_bounding_sphere::size2dim(pcursor.elems[0].keyLen);

    // Uncomment if you care ...
    // if (dim != displayDim) return;

    // find min/max along each dimension
    double min[displayDim];
    double max[displayDim];

    double tmin, tmax;

	int i;
    for (i = 0; i < pcursor.numElems; i++) {
        rt_bounding_sphere s(dim, (const double *) pcursor.elems[i].key);
		int j;
	for (j = 0; j < displayDim; j++) {
	    tmin = s.center.co(j) - s.radius();
	    tmax = s.center.co(j) + s.radius();
	    if (i == 0) {
		min[j] = tmin;
		max[j] = tmax;
	    } else {
		if (min[j] > tmin) min[j] = tmin;
		if (max[j] < tmax) max[j] = tmax;
	    }
	}
    }

    int notok = drawScales(&width, &height, min[0], max[0], min[1], max[1],
	env, graphicsContext);
    
    if (notok)
	return;

    double scales[displayDim];
    scales[0] = ((double) width) / (max[0] - min[0]);
    scales[1] = ((double) height) / (max[1] - min[1]);

    // draw non-highlighted rects
    env->CallVoidMethod(graphicsContext, setColorId, normalColor);
    int j = 0; // index into hightlights
    int x,y,w,h;
    for (i = 0; i < pcursor.numElems; i++) {
	rt_bounding_sphere s(dim, (const double *) pcursor.elems[i].key);
	
	x = (int) floor((s.center.co(0) - min[0]) * scales[0]);
	y = (int) floor((s.center.co(1) - min[1]) * scales[1]);
	
	w = (int) floor((s.radius()) * scales[0]);
	h = (int) floor((s.radius()) * scales[1]);
	
	// decide which color to use
	if (j < numHighlights && highlights[j] == i) {
	    // this is to be highlighted; we'll draw that later
	    j++;
	} else {
	    y = height - y;
	    env->CallVoidMethod(graphicsContext, drawOvalId,
		(x - w), (y - h), 2*w, 2*h);
	}
    }

    // draw highlighted rects after non-highlighted ones, so we don't obscure
    // the highlights
    env->CallVoidMethod(graphicsContext, setColorId, highlightColor);
    for (i = 0; i < numHighlights; i++) {

	rt_bounding_sphere s(dim, (const double *) pcursor.elems[highlights[i]].key);

	x = (int) floor((s.center.co(0) - min[0]) * scales[0]);
	y = (int) floor((s.center.co(1) - min[1]) * scales[1]);
	
	w = (int) floor((s.radius()) * scales[0]);
	h = (int) floor((s.radius()) * scales[1]);

	y = height - y;
	env->CallVoidMethod(graphicsContext, drawOvalId, 
	    (x - w), (y - h), 2*w, 2*h);
    }

}

void
amdb_support::displayCentroidSpheres(
    gist_predcursor_t& pcursor,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject graphicsContext, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{
    initIds(env, graphicsContext);
    
    // we can only display 2-dim data
    int dim = rt_centroid_sphere::size2dim(pcursor.elems[0].keyLen);

    // Uncomment if you care ...
    // if (dim != displayDim) return;
    
    // find min/max along each dimension
    double min[displayDim];
    double max[displayDim];

    double tmin, tmax;

	int i;
    for (i = 0; i < pcursor.numElems; i++) {
        rt_centroid_sphere s(dim, (const double *) pcursor.elems[i].key);
		int j;
	for (j = 0; j < displayDim; j++) {
	    tmin = s.center.co(j) - s.radius();
	    tmax = s.center.co(j) + s.radius();
	    if (i == 0) {
		min[j] = tmin;
		max[j] = tmax;
	    } else {
		if (min[j] > tmin) min[j] = tmin;
		if (max[j] < tmax) max[j] = tmax;
	    }
	}
    }

    int notok = drawScales(&width, &height, min[0], max[0], min[1], max[1],
	env, graphicsContext);
    
    if (notok)
	return;

    double scales[displayDim];
    scales[0] = ((double) width) / (max[0] - min[0]);
    scales[1] = ((double) height) / (max[1] - min[1]);

    // draw non-highlighted rects
    env->CallVoidMethod(graphicsContext, setColorId, normalColor);
    int j = 0; // index into hightlights
    int x,y,w,h;
    for (i = 0; i < pcursor.numElems; i++) {
	rt_centroid_sphere s(dim, (const double *) pcursor.elems[i].key);

	x = (int) floor((s.center.co(0) - min[0]) * scales[0]);
	y = (int) floor((s.center.co(1) - min[1]) * scales[1]);
	
	w = (int) floor((s.radius()) * scales[0]);
	h = (int) floor((s.radius()) * scales[1]);
	
	// decide which color to use
	if (j < numHighlights && highlights[j] == i) {
	    // this is to be highlighted; we'll draw that later
	    j++;
	} else {
	    y = height - y;
	    env->CallVoidMethod(graphicsContext, drawOvalId, 
		(x - w), (y - h), 2*w, 2*h);
	}
    }

    // draw highlighted rects after non-highlighted ones, so we don't obscure
    // the highlights
    env->CallVoidMethod(graphicsContext, setColorId, highlightColor);
    for (i = 0; i < numHighlights; i++) {

	rt_centroid_sphere s(dim, (const double *) pcursor.elems[highlights[i]].key);

	x = (int) floor((s.center.co(0) - min[0]) * scales[0]);
	y = (int) floor((s.center.co(1) - min[1]) * scales[1]);
	
	w = (int) floor((s.radius()) * scales[0]);
	h = (int) floor((s.radius()) * scales[1]);

	y = height - y;
	env->CallVoidMethod(graphicsContext, drawOvalId, 
	    (x - w), (y - h), 2*w, 2*h);
    }

}

void
amdb_support::displaySphereRects(
    gist_predcursor_t& pcursor,
    JNIEnv* env,
    jint* highlights,
    jint numHighlights,
    jobject graphicsContext, // Java class: java.awt.Graphics
    jobject normalColor,
    jobject highlightColor,
    jint width,
    jint height)
{
    initIds(env, graphicsContext);

    // we can only display 2-dim data
    int dim = rt_sphererect::size2dim(pcursor.elems[0].keyLen);

    // Uncomment if you care ...
    // if (dim != displayDim) return;
    
    // find min/max along each dimension
    double min[displayDim];
    double max[displayDim];

    double tmin, tmax;

	int i;
    for (i = 0; i < pcursor.numElems; i++) {
	rt_sphererect sr(dim, (const double *) pcursor.elems[i].key);

	rt_rect& r = sr.rect;
	rt_centroid_sphere& s = sr.sphere;
	
	int j;
	for (j = 0; j < displayDim; j++) {
	    tmin = s.center.co(j) - s.radius();
	    tmax = s.center.co(j) + s.radius();

	    if (tmin > r.lo(j))
		tmin = r.lo(j);
	    if (tmax < r.hi(j))
		tmax = r.hi(j);

	    if (i == 0) {
		min[j] = tmin;
		max[j] = tmax;
	    } else {
		if (min[j] > tmin) min[j] = tmin;
		if (max[j] < tmax) max[j] = tmax;
	    }
	}
    }

    int notok = drawScales(&width, &height, min[0], max[0], min[1], max[1],
	env, graphicsContext);
    
    if (notok)
	return;

    double scales[displayDim];
    scales[0] = ((double) width) / (max[0] - min[0]);
    scales[1] = ((double) height) / (max[1] - min[1]);

    // draw non-highlighted rects
    env->CallVoidMethod(graphicsContext, setColorId, normalColor);
    int j = 0; // index into hightlights
    int x,y,w,h;
    int x1,x2,y1,y2;

    for (i = 0; i < pcursor.numElems; i++) {
	rt_sphererect sr(dim, (const double *) pcursor.elems[i].key);

	rt_rect& r = sr.rect;
	rt_centroid_sphere& s = sr.sphere;

        x1 = (int) floor((r.lo(0) - min[0]) * scales[0]);
	x2 = (int) floor((r.hi(0) - min[0]) * scales[0]);
        y1 = height - (int) floor((r.lo(1) - min[1]) * scales[1]);
	y2 = height - (int) floor((r.hi(1) - min[1]) * scales[1]);

	x = (int) floor((s.center.co(0) - min[0]) * scales[0]);
	y = height - (int) floor((s.center.co(1) - min[1]) * scales[1]);
	
	w = (int) floor((s.radius()) * scales[0]);
	h = (int) floor((s.radius()) * scales[1]);
	
	// decide which color to use
	if (j < numHighlights && highlights[j] == i) {
	    // this is to be highlighted; we'll draw that later
	    j++;
	} else {
	    env->CallVoidMethod(graphicsContext, drawOvalId, 
		(x - w), (y - h), 2*w, 2*h);
	    env->CallVoidMethod(graphicsContext, drawRectId, 
		x1, y2, x2-x1, abs(y2-y1));
	}
    }

    // draw highlighted rects after non-highlighted ones, so we don't obscure
    // the highlights
    env->CallVoidMethod(graphicsContext, setColorId, highlightColor);
    for (i = 0; i < numHighlights; i++) {

	rt_sphererect sr(dim, (const double *) pcursor.elems[highlights[i]].key);

	rt_rect& r = sr.rect;
	rt_centroid_sphere& s = sr.sphere;
	
	x1 = (int) floor((r.lo(0) - min[0]) * scales[0]);
	x2 = (int) floor((r.hi(0) - min[0]) * scales[0]);
        y1 = height - (int) floor((r.lo(1) - min[1]) * scales[1]);
        y2 = height - (int) floor((r.hi(1) - min[1]) * scales[1]);

	x = (int) floor((s.center.co(0) - min[0]) * scales[0]);
	y = height - (int) floor((s.center.co(1) - min[1]) * scales[1]);
	
	w = (int) floor((s.radius()) * scales[0]);
	h = (int) floor((s.radius()) * scales[1]);
	
	env->CallVoidMethod(graphicsContext, drawOvalId, 
	    (x - w), (y - h), 2*w, 2*h);
	env->CallVoidMethod(graphicsContext, drawRectId, 
	    x1, y2, x2-x1, abs(y2-y1));
    }

}

rc_t
amdb_support::parseGeoQuery(
    const char* str,
    gist_query_t*& query)
{
    if (strcmp(str, "") == 0) {
        // no qualification
	query = new rt_query_t(rt_query_t::rt_nooper, 
	    rt_query_t::rt_pointarg, NULL);
	return RCOK;
    }

    istrstream s(str, strlen(str));

    s >> ws; // remove leading whitespace
    char op; // operator (&, <, >, =)
    s >> op;
    if (s.fail()) return ePARSEERROR;
    rt_query_t::rt_oper oper;
    switch (op) {
	case '&':
	    oper = rt_query_t::rt_overlap;
	    break;
	case '<':
	    oper = rt_query_t::rt_contained;
	    break;
	case '>':
	    oper = rt_query_t::rt_contains;
	    break;
	case '=':
	    oper = rt_query_t::rt_equal;
	    break;
	case '~':
	    oper = rt_query_t::rt_nearest;
	    break;
	case '#':
	    oper = rt_query_t::rt_count_overlap;
	    break;
	case '!':
	    oper = rt_query_t::rt_count_sample;
	    break;
	case '@':
	    oper = rt_query_t::rt_count_combo;
	    break;
	default:
	    return ePARSEERROR;
    }

    s >> ws;
    char arg; // point ('p') or rectangle ('r')
    s >> arg;
    if (s.fail()) return ePARSEERROR;
    if ((arg != 'p' && arg != 'r') ||
        (arg == 'r' && oper == rt_query_t::rt_nearest)) {

	// cannot run NN search with rectangle as center
	return ePARSEERROR;
    }

    double coord[gist_p::max_tup_sz/sizeof(double)];
    int len;
    if (arg == 'p') {
        // construct point argument
	parsePoint(s, (void *) coord, len);
	int dim = len / sizeof(double);
	rt_point* pt = new rt_point(dim);
	for (int i = 0; i < dim; i++) {
	    pt->co(i) = coord[i];
	}

	query = new rt_query_t(oper, rt_query_t::rt_pointarg, pt);
    } else {
        // construct rectangle argument
	parseRect(s, (void *) coord, len);
	int dim = len / (2 * sizeof(double));
	rt_rect* rect = new rt_rect(dim);
	for (int i = 0; i < dim; i++) {
	    rect->lo(i) = coord[2*i];
	    rect->hi(i) = coord[2*i+1];
	}

	query = new rt_query_t(oper, rt_query_t::rt_rectarg, rect);
    }

    return RCOK;
}

// functions which implement display functions with the
// new predicate cursor interface ...

rc_t
amdb_support::display_rt_point_preds(
    JNIEnv* env,
    jint    width,
    jint    height,
    jobject graphicsContext, // in: Java class: java.awt.Graphics
    jobject colors[], // in: array of java.awt.Color objects
    gist_disppredcursor_t& pcursor) // in: predicates to display

{
    if (pcursor.numPreds() == 0) return RCOK; // nothing to display ...

    // cout << "display_rt_point_preds()" << endl;
    
    initIds(env, graphicsContext);

    char tempData[gist_p::max_tup_sz];

    void *key = (void *) tempData;
    int keyLen;
    int keyLevel;
    int keyColor;

    // get initial key so we can determine the number of dims ...

    pcursor.getNext(key, keyLen, keyLevel, keyColor);

    // we can only display 2-dim data
    int dim;

    if (keyLevel == 1)
	dim = rt_point::size2dim(keyLen);
    else
	dim = rt_rect::size2dim(keyLen);
    
//     if (dim != displayDim) {
// 	cout << "display() displayDim != dim: " << displayDim << " " << dim << endl;
//         return RCOK;
//     }

    // find min/max along each dimension
    double min[displayDim];
    double max[displayDim];
    
    int j;

    // initialize the ranges along each dimension ...

    if (keyLevel == 1) {
	rt_point pt(dim, (const double *) key);
	for (j = 0; j < displayDim; j++) {
	    min[j] = pt.co(j);
	    max[j] = pt.co(j);
	}
    } else {
	rt_rect r(dim, (const double *) key);
	for (j = 0; j < displayDim; j++) {
	    min[j] = r.lo(j);
	    max[j] = r.hi(j);
	}
    }

    while (pcursor.getNext(key, keyLen, keyLevel, keyColor) != eEOF) {
	// If level is one then its a leaf ... 
	if (keyLevel == 1) {
	    rt_point pt(dim, (const double *) key);
	    for (j = 0; j < displayDim; j++) {
		if (min[j] > pt.co(j)) min[j] = pt.co(j);
		if (max[j] < pt.co(j)) max[j] = pt.co(j);
	    }
	} else {
	    rt_rect r(dim, (const double *) key);
	    for (j = 0; j < displayDim; j++) {
		if (min[j] > r.lo(j)) min[j] = r.lo(j);
		if (max[j] < r.hi(j)) max[j] = r.hi(j);
	    }
	}
    } 

    int notok = drawScales(&width, &height, min[0], max[0], min[1], max[1],
	env, graphicsContext);
    
    if (notok)
	return notok;

    double scales[displayDim];
    scales[0] = ((double) width) / (max[0] - min[0]);
    scales[1] = ((double) height) / (max[1] - min[1]);

    // we pass in the colors for each of the preds so now we just do it 
    // once.

    pcursor.reset();

    int x, y, x1, x2, y1, y2;

    //    for (int i = 0; i < pcursor.numElems(); i++) {
	
    while (pcursor.getNext(key, keyLen, keyLevel, keyColor) != eEOF) {
	// if on leaf, plot a point ...
	if (keyLevel == 1) {

	    rt_point pt(dim, (const double *) key);
	    x = (int) floor((pt.co(0) - min[0]) * scales[0]);
	    y = height - (int) floor((pt.co(1) - min[1]) * scales[1]);
	
	    env->CallVoidMethod(graphicsContext, setColorId, colors[keyColor]);

	    env->CallVoidMethod(graphicsContext, drawRectId, x, y, 1, 1);

	} else {

	    rt_rect r(dim, (const double *) key);
	    x1 = (int) floor((r.lo(0) - min[0]) * scales[0]);
	    x2 = (int) floor((r.hi(0) - min[0]) * scales[0]);
	    y1 = (int) floor((r.lo(1) - min[1]) * scales[1]);
	    y2 = (int) floor((r.hi(1) - min[1]) * scales[1]);
	    
	    env->CallVoidMethod(graphicsContext, setColorId, colors[keyColor]);

	    y1 = height - y1;
	    y2 = height - y2;
	    
	    env->CallVoidMethod(graphicsContext, drawRectId, x1, y2, x2-x1, 
		abs(y2-y1));

	}
    }

    return(RCOK);
}


rc_t
amdb_support::display_sp_point_preds(
    JNIEnv* env,
    jint    width,
    jint    height,
    jobject graphicsContext, // in: Java class: java.awt.Graphics
    jobject colors[], // in: array of java.awt.Color objects
    gist_disppredcursor_t& pcursor) // in: predicates to display
{
    if (pcursor.numPreds() == 0) return RCOK; // nothing to display ...

    initIds(env, graphicsContext);

    char tempData[gist_p::max_tup_sz];

    void *key = (void *) tempData;
    int keyLen;
    int keyLevel;
    int keyColor;

    // get initial key so we can determine the number of dims ...

    pcursor.getNext(key, keyLen, keyLevel, keyColor);

    // we can only display 2-dim data
    int dim;

    if (keyLevel == 1)
	dim = rt_point::size2dim(keyLen);
    else 
	dim = rt_bounding_sphere::size2dim(keyLen);
    
//     if (dim != displayDim) {
// 	cout << "display() displayDim != dim: " << displayDim 
// 	     << " " << dim << endl;
//         return RCOK;
//     }

    // find min/max along each dimension
    double min[displayDim];
    double max[displayDim];
    
    int j;
    
    double tmin, tmax;

    // initialize the ranges along each dimension ...

    if (keyLevel == 1) {
	rt_point pt(dim, (const double *) key);
	for (j = 0; j < displayDim; j++) {
	    min[j] = pt.co(j);
	    max[j] = pt.co(j);
	}
    } else {
	rt_bounding_sphere s(dim, (const double *) key);
	for (j = 0; j < displayDim; j++) {
	    tmin = s.center.co(j) - s.radius();
	    tmax = s.center.co(j) + s.radius();
	    min[j] = tmin;
	    max[j] = tmax;
	}
    }

    while (pcursor.getNext(key, keyLen, keyLevel, keyColor) != eEOF) {
	// If level is one then its a leaf ... 
	if (keyLevel == 1) {
	    rt_point pt(dim, (const double *) key);
	    for (j = 0; j < displayDim; j++) {
		if (min[j] > pt.co(j)) min[j] = pt.co(j);
		if (max[j] < pt.co(j)) max[j] = pt.co(j);
	    }
	} else {
	    rt_bounding_sphere s(dim, (const double *) key);
	    for (j = 0; j < displayDim; j++) {
		tmin = s.center.co(j) - s.radius();
		tmax = s.center.co(j) + s.radius();
		if (min[j] > tmin) min[j] = tmin;
		if (max[j] < tmax) max[j] = tmax;
	    }
	}
    } 

    int notok = drawScales(&width, &height, min[0], max[0], min[1], max[1],
	env, graphicsContext);
    
    if (notok)
	return notok;

    double scales[displayDim];
    scales[0] = ((double) width) / (max[0] - min[0]);
    scales[1] = ((double) height) / (max[1] - min[1]);

    // we pass in the colors for each of the preds so now we just do it 
    // once.

    pcursor.reset();

    int x, y, w, h;

    //    for (int i = 0; i < pcursor.numElems(); i++) {
	
    while (pcursor.getNext(key, keyLen, keyLevel, keyColor) != eEOF) {
	// if on leaf, plot a point ...
	if (keyLevel == 1) {

	    rt_point pt(dim, (const double *) key);
	    x = (int) floor((pt.co(0) - min[0]) * scales[0]);
	    y = height - (int) floor((pt.co(1) - min[1]) * scales[1]);
	
	    env->CallVoidMethod(graphicsContext, setColorId, colors[keyColor]);

	    env->CallVoidMethod(graphicsContext, drawRectId, x, y, 1, 1);

	} else {


	    rt_bounding_sphere s(dim, (const double *) key);

	    x = (int) floor((s.center.co(0) - min[0]) * scales[0]);
	    y = (int) floor((s.center.co(1) - min[1]) * scales[1]);
	
	    w = (int) floor((s.radius()) * scales[0]);
	    h = (int) floor((s.radius()) * scales[1]);

	    env->CallVoidMethod(graphicsContext, setColorId, colors[keyColor]);

	    y = height - y;

	    env->CallVoidMethod(graphicsContext, drawOvalId, 
		(x - w), (y - h), 2*w, 2*h);
	}
    }

    return(RCOK);

}

rc_t
amdb_support::display_ss_point_preds(
	JNIEnv* env,
	jint    width,
	jint    height,
	jobject graphicsContext, // in: Java class: java.awt.Graphics
	jobject colors[], // in: array of java.awt.Color objects
	gist_disppredcursor_t& pcursor) // in: predicates to display
{
    if (pcursor.numPreds() == 0) return RCOK; // nothing to display ...

    initIds(env, graphicsContext);

    char tempData[gist_p::max_tup_sz];

    void *key = (void *) tempData;
    int keyLen;
    int keyLevel;
    int keyColor;

    // get initial key so we can determine the number of dims ...

    pcursor.getNext(key, keyLen, keyLevel, keyColor);

    // we can only display 2-dim data
    int dim;

    if (keyLevel == 1)
	dim = rt_point::size2dim(keyLen);
    else 
	dim = rt_centroid_sphere::size2dim(keyLen);
    
//     if (dim != displayDim) {
// 	cout << "display() displayDim != dim: " << displayDim 
// 	     << " " << dim << endl;
//         return RCOK;
//     }

    // find min/max along each dimension
    double min[displayDim];
    double max[displayDim];
    
    int j;
    
    double tmin, tmax;
    
    // initialize the ranges along each dimension ...

    if (keyLevel == 1) {
	rt_point pt(dim, (const double *) key);
	for (j = 0; j < displayDim; j++) {
	    min[j] = pt.co(j);
	    max[j] = pt.co(j);
	}
    } else {
	rt_centroid_sphere s(dim, (const double *) key);
	for (j = 0; j < displayDim; j++) {
	    tmin = s.center.co(j) - s.radius();
	    tmax = s.center.co(j) + s.radius();
	    min[j] = tmin;
	    max[j] = tmax;
	}
    }

    while (pcursor.getNext(key, keyLen, keyLevel, keyColor) != eEOF) {
	// If level is one then its a leaf ... 
	if (keyLevel == 1) {
	    rt_point pt(dim, (const double *) key);
	    for (j = 0; j < displayDim; j++) {
		if (min[j] > pt.co(j)) min[j] = pt.co(j);
		if (max[j] < pt.co(j)) max[j] = pt.co(j);
	    }
	} else {
	    rt_centroid_sphere s(dim, (const double *) key);
	    for (j = 0; j < displayDim; j++) {
		tmin = s.center.co(j) - s.radius();
		tmax = s.center.co(j) + s.radius();
		if (min[j] > tmin) min[j] = tmin;
		if (max[j] < tmax) max[j] = tmax;
	    }
	}
    } 

    int notok = drawScales(&width, &height, min[0], max[0], min[1], max[1],
	env, graphicsContext);
    
    if (notok)
	return notok;

    double scales[displayDim];
    scales[0] = ((double) width) / (max[0] - min[0]);
    scales[1] = ((double) height) / (max[1] - min[1]);

    // we pass in the colors for each of the preds so now we just do it 
    // once.

    pcursor.reset();

    int x, y, w, h;

    //    for (int i = 0; i < pcursor.numElems(); i++) {
	
    while (pcursor.getNext(key, keyLen, keyLevel, keyColor) != eEOF) {
	// if on leaf, plot a point ...
	if (keyLevel == 1) {

	    rt_point pt(dim, (const double *) key);
	    x = (int) floor((pt.co(0) - min[0]) * scales[0]);
	    y = height - (int) floor((pt.co(1) - min[1]) * scales[1]);
	
	    env->CallVoidMethod(graphicsContext, setColorId, colors[keyColor]);

	    env->CallVoidMethod(graphicsContext, drawRectId, x, y, 1, 1);

	} else {


	    rt_bounding_sphere s(dim, (const double *) key);

	    x = (int) floor((s.center.co(0) - min[0]) * scales[0]);
	    y = (int) floor((s.center.co(1) - min[1]) * scales[1]);
	
	    w = (int) floor((s.radius()) * scales[0]);
	    h = (int) floor((s.radius()) * scales[1]);

	    env->CallVoidMethod(graphicsContext, setColorId, colors[keyColor]);

	    y = height - y;

	    env->CallVoidMethod(graphicsContext, drawOvalId, 
		(x - w), (y - h), 2*w, 2*h);
	}
    }

    return(RCOK);

}

rc_t
amdb_support::display_sr_point_preds(
	JNIEnv* env,
	jint    width,
	jint    height,
	jobject graphicsContext, // in: Java class: java.awt.Graphics
	jobject colors[], // in: array of java.awt.Color objects
	gist_disppredcursor_t& pcursor) // in: predicates to display
{
    if (pcursor.numPreds() == 0) return RCOK; // nothing to display ...

    initIds(env, graphicsContext);

    char tempData[gist_p::max_tup_sz];

    void *key = (void *) tempData;
    int keyLen;
    int keyLevel;
    int keyColor;

    // get initial key so we can determine the number of dims ...

    pcursor.getNext(key, keyLen, keyLevel, keyColor);

    // we can only display 2-dim data
    int dim;

    if (keyLevel == 1)
	dim = rt_point::size2dim(keyLen);
    else 
	dim = rt_sphererect::size2dim(keyLen);
    
//     if (dim != displayDim) {
// 	cout << "display() displayDim != dim: " << displayDim 
// 	     << " " << dim << endl;
//         return RCOK;
//     }

    // find min/max along each dimension
    double min[displayDim];
    double max[displayDim];

    int j;

    double tmin, tmax;
    
    // initialize the ranges along each dimension ...

    if (keyLevel == 1) {
	rt_point pt(dim, (const double *) key);
	for (j = 0; j < displayDim; j++) {
	    min[j] = pt.co(j);
	    max[j] = pt.co(j);
	}
    } else {
	rt_sphererect sr(dim, (const double *) key);

	rt_rect& r = sr.rect;
	rt_centroid_sphere& s = sr.sphere;

	for (j = 0; j < displayDim; j++) {
	    tmin = s.center.co(j) - s.radius();
	    tmax = s.center.co(j) + s.radius();

	    if (tmin > r.lo(j))
		tmin = r.lo(j);
	    if (tmax < r.hi(j))
		tmax = r.hi(j);

	    min[j] = tmin;
	    max[j] = tmax;
	}
    }

    while (pcursor.getNext(key, keyLen, keyLevel, keyColor) != eEOF) {
	// If level is one then its a leaf ... 
	if (keyLevel == 1) {
	    rt_point pt(dim, (const double *) key);
	    for (j = 0; j < displayDim; j++) {
		if (min[j] > pt.co(j)) min[j] = pt.co(j);
		if (max[j] < pt.co(j)) max[j] = pt.co(j);
	    }
	} else {
	    rt_sphererect sr(dim, (const double *) key);

	    rt_rect& r = sr.rect;
	    rt_centroid_sphere& s = sr.sphere;

	    for (j = 0; j < displayDim; j++) {
		tmin = s.center.co(j) - s.radius();
		tmax = s.center.co(j) + s.radius();

		if (tmin > r.lo(j))
		    tmin = r.lo(j);
		if (tmax < r.hi(j))
		    tmax = r.hi(j);

		if (min[j] > tmin) min[j] = tmin;
		if (max[j] < tmax) max[j] = tmax;
	    }
	}
    }

    int notok = drawScales(&width, &height, min[0], max[0], min[1], max[1],
	env, graphicsContext);
    
    if (notok)
	return notok;

    double scales[displayDim];
    scales[0] = ((double) width) / (max[0] - min[0]);
    scales[1] = ((double) height) / (max[1] - min[1]);

    // we pass in the colors for each of the preds so now we just do it 
    // once.

    pcursor.reset();

    int x, y, w, h, x1, x2, y1, y2;

    while (pcursor.getNext(key, keyLen, keyLevel, keyColor) != eEOF) {
	// if on leaf, plot a point ...
	if (keyLevel == 1) {

	    rt_point pt(dim, (const double *) key);
	    x = (int) floor((pt.co(0) - min[0]) * scales[0]);
	    y = height - (int) floor((pt.co(1) - min[1]) * scales[1]);
	
	    env->CallVoidMethod(graphicsContext, setColorId, colors[keyColor]);

	    env->CallVoidMethod(graphicsContext, drawRectId, x, y, 1, 1);

	} else {


	    rt_sphererect sr(dim, (const double *) key);

	    rt_rect& r = sr.rect;
	    rt_centroid_sphere& s = sr.sphere;

	    x1 = (int) floor((r.lo(0) - min[0]) * scales[0]);
	    x2 = (int) floor((r.hi(0) - min[0]) * scales[0]);
	    y1 = height - (int) floor((r.lo(1) - min[1]) * scales[1]);
	    y2 = height - (int) floor((r.hi(1) - min[1]) * scales[1]);

	    x = (int) floor((s.center.co(0) - min[0]) * scales[0]);
	    y = height - (int) floor((s.center.co(1) - min[1]) * scales[1]);
	
	    w = (int) floor((s.radius()) * scales[0]);
	    h = (int) floor((s.radius()) * scales[1]);

	    env->CallVoidMethod(graphicsContext, setColorId, colors[keyColor]);

	    env->CallVoidMethod(graphicsContext, drawOvalId, 
		(x - w), (y - h), 2*w, 2*h);

	    env->CallVoidMethod(graphicsContext, drawRectId, 
		x1, y2, x2-x1, abs(y2-y1));
	}
    }

    return(RCOK);

}

rc_t
amdb_support::display_rt_rect_preds(
    JNIEnv* env,
    jint    width,
    jint    height,
    jobject graphicsContext, // in: Java class: java.awt.Graphics
    jobject colors[], // in: array of java.awt.Color objects
    gist_disppredcursor_t& pcursor) // in: predicates to display

{
    if (pcursor.numPreds() == 0) return RCOK; // nothing to display ...

    initIds(env, graphicsContext);

    char tempData[gist_p::max_tup_sz];

    void *key = (void *) tempData;
    int keyLen;
    int keyLevel;
    int keyColor;

    // get initial key so we can determine the number of dims ...

    pcursor.getNext(key, keyLen, keyLevel, keyColor);

    // we can only display 2-dim data
    int dim;

    dim = rt_rect::size2dim(keyLen);
    
//     if (dim != displayDim) {
// 	cout << "display() displayDim != dim: " << displayDim 
// 	     << " " << dim << endl;
//         return RCOK;
//     }

    // find min/max along each dimension
    double min[displayDim];
    double max[displayDim];
    
    int j;

    // initialize the ranges along each dimension ...

    rt_rect r(dim, (const double *) key);
    for (j = 0; j < displayDim; j++) {
	min[j] = r.lo(j);
	max[j] = r.hi(j);
    }

    while (pcursor.getNext(key, keyLen, keyLevel, keyColor) != eEOF) {
	rt_rect r(dim, (const double *) key);
	for (j = 0; j < displayDim; j++) {
	    if (min[j] > r.lo(j)) min[j] = r.lo(j);
	    if (max[j] < r.hi(j)) max[j] = r.hi(j);
	}
    } 

    int notok = drawScales(&width, &height, min[0], max[0], min[1], max[1],
	env, graphicsContext);
    
    if (notok)
	return notok;

    double scales[displayDim];
    scales[0] = ((double) width) / (max[0] - min[0]);
    scales[1] = ((double) height) / (max[1] - min[1]);

    // we pass in the colors for each of the preds so now we just do it 
    // once.

    pcursor.reset();

    int x1, x2, y1, y2;

    while (pcursor.getNext(key, keyLen, keyLevel, keyColor) != eEOF) {

	rt_rect r(dim, (const double *) key);
	x1 = (int) floor((r.lo(0) - min[0]) * scales[0]);
	x2 = (int) floor((r.hi(0) - min[0]) * scales[0]);
	y1 = (int) floor((r.lo(1) - min[1]) * scales[1]);
	y2 = (int) floor((r.hi(1) - min[1]) * scales[1]);
	
	env->CallVoidMethod(graphicsContext, setColorId, colors[keyColor]);
	
	y1 = height - y1;
	y2 = height - y2;
	
	env->CallVoidMethod(graphicsContext, drawRectId, x1, y2, x2-x1, 
	    abs(y2-y1));
    }

    return(RCOK);
}
