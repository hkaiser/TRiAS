// This is -*- C++ -*-
// $Id: snarf.h,v 1.3 1999/04/23 02:26:38 trow Exp $

#ifndef _INC_SNARF_H
#define _INC_SNARF_H


// Our own, more C++-friendly, magic snarfing macros.
#ifndef SCM_MAGIC_SNARFER

#define GOOSE_PROC(fname, string_name, req, opt, var, ARGLIST) \
static char str_##fname[] = string_name; \
static SCM scm_fn_##fname ARGLIST

#else

#define GOOSE_PROC(fname, string_name, req, opt, var, ARGLIST) \
%%%start \
   scm_make_gsubr(string_name, req, opt, var, reinterpret_cast<SCM(*)(...)>(scm_fn_##fname)); \
%%%end

#endif

#endif // _INC_SNARF_H

// $Id: snarf.h,v 1.3 1999/04/23 02:26:38 trow Exp $
