// amdb_nptree.cc
// Copyright (c) 1998, Regents of the University of California
// $Id: amdb_nptree.cc,v 1.2 2000/03/15 00:24:39 mashah Exp $

#include <stdio.h>
#include <malloc.h>
#include "gist_defs.h"
#include "amdb_ext.h"
#include "amdb_support.h"
#include "gist_nptree.h"

// VCPORT_B
#ifdef WIN32

#include <strstream>
#include <iostream>

using namespace std;

#else

#include <strstream.h>
#include <iostream.h>

#endif
// VCPORT_E

static rc_t
nptree_display(
    JNIEnv* env,
    jint    width,
    jint    height,
    jobject graphicsContext, // in: Java class: java.awt.Graphics
    jobject colors[], // in: array of java.awt.Color objects
    gist_disppredcursor_t& pcursor) // in: predicates to display
{
    return(RCOK);
}

// consistent() not useful: we're only running NN queries
amdb_ext_t amdb_npt_ext(gist_ext_t::npt_ext_id, NULL , NULL, nptree_display, NULL);
