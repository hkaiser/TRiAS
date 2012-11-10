// gist_extensions.h							-*- c++ -*-
// Copyright (c) 1999 Regents of the University of California
// $Id: gist_extensions.h,v 1.3 1999/12/14 06:06:24 marcel Exp $

// include this file if you want to use one or more of the available extensions
// available with libgist, but don't include and use them by name (e.g., if you
// just refer to them via gist_ext_t::gist_ext_list)

#ifndef GIST_EXTENSIONS_H
#define GIST_EXTENSIONS_H

// include for extensions
#include "gist_btree.h"
#include "gist_rtree.h"
#include "gist_rstartree.h"
#include "gist_nptree.h"
#include "gist_rrtree.h"
#include "gist_sptree.h"
#include "gist_sstree.h"
#include "gist_srtree.h"

// pull in extension objects from their respective object files
static gist_ext_t* _gist_exts[] = {
    &rt_point_ext,
    &rt_rect_ext,
    &bt_int_ext,
    &bt_str_ext,
    &rstar_point_ext,
    &rstar_rect_ext,
    &sp_point_ext,
    &ss_point_ext,
    &sr_point_ext,
    &rr_point_ext,
    &npt_ext,
};

#ifdef AMDB
static amdb_ext_t* _amdb_exts[] = {
    &amdb_rt_point_ext,
    &amdb_rt_rect_ext,
    &amdb_bt_int_ext,
    &amdb_bt_str_ext,
    &amdb_rstar_point_ext,
    &amdb_rstar_rect_ext,
    &amdb_sp_point_ext,
    &amdb_ss_point_ext,
    &amdb_sr_point_ext,
    &amdb_rr_point_ext,
    &amdb_npt_ext
};
#endif

#endif // GIST_EXTENSIONS_H

