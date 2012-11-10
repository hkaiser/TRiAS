// This is -*- C++ -*-
// $Id: guilegoose.h,v 1.5 1999/05/12 16:25:46 trow Exp $

/* 
 * guilegoose.h
 *
 * Copyright (C) 1998 EMC Capital Management
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */

#ifndef _INC_GUILEGOOSE_H
#define _INC_GUILEGOOSE_H

extern "C" {
#include <stdlib.h>
#include <libguile.h>
#include <guile/gh.h>
}

// It's important to use quotes around these, they will be found 
//  in the current directory when installed.
#include "ConfInt.h"
#include "RealSet.h"
#include "LinearRegression.h"

bool scm_confintp(SCM);
ConfInt* scm2confint(SCM);
SCM confint2scm(const ConfInt&);

bool scm_randomp(SCM);
Random* scm2random(SCM);
SCM random2scm(Random*);

bool scm_realsetp(SCM);
RealSet* scm2realset(SCM);
SCM realset2scm(RealSet*);
 // the SCM object won't "own" the RealSet
SCM realset2scm_handle(RealSet*);


bool scm_linregp(SCM);
LinearRegression* scm2linreg(SCM);
SCM linreg2scm(LinearRegression*);

// Throw errors
// It is unlikely that these result in destructors being called.
//  Maybe they do though.
void goose_scm_tagged_error(const char* tag, const char *subr, const char *msg);
void goose_scm_error(const char *subr, const char *msg);

// Registers all the scheme types.
void scm_init_goose ();

// Macro magic for turning goose exceptions into scm exceptions.
// x = string name of function
#define GOOSE_CATCH(x) catch (Exception e) { goose_scm_error(x, e.what().c_str()); }

#endif
