// -*- Mode: C++ -*-

//          BT.h
//
// Copyright (c) 1996, Regents of the University of California
// $Header: /usr/local/devel/GiST/libGiST/BTree/BT.h,v 1.1.1.1 1996/08/06 23:47:18 jmh Exp $

#ifndef BT_H
#define BT_H

#include "GiST.h"
#include "GiSTfile.h"
#include "BTentry.h"
#include "BTnode.h"
#include "BTpredicate.h"

class BT : public GiST
{
public:
  // optional, for debugging support
  GiSTobjid IsA() { return BT_CLASS; }

protected:
  // Required members
  GiSTnode  *CreateNode()  const { return new BTnode; }
  GiSTstore *CreateStore() const { return new GiSTfile; }

  // set special property
  int  IsOrdered()    const { return 1; }
};

#endif

