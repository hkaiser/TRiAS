// Mode: -*- C++ -*-

//          GiSTfile.h
//
// Copyright (c) 1996, Regents of the University of California
// $Header: /usr/local/devel/GiST/libGiST/libGiST/GiSTfile.h,v 1.1.1.1 1996/08/06 23:47:21 jmh Exp $

#ifndef GISTFILE_H
#define GISTFILE_H

#include "libGiST/GiSTstore.h"

namespace trias_gist {

// GiSTfile is a simple storage class for GiSTs to work over 
// UNIX/NT files.

#define GiST_PAGE_SIZE	4096

class GiSTfile : public GiSTstore {
public:
  GiSTfile() : GiSTstore() {}

  void CreateNew(const char *filename, bool fTruncateExisting = false);
  void Open(const char *filename);
  void Close();

  void Read(GiSTpage page, char *buf);
  void Write(GiSTpage page, const char *buf);
  GiSTpage Allocate();
  void Deallocate(GiSTpage page);
  void Sync() {}
  int PageSize() const { return GiST_PAGE_SIZE; }

private:
  int fileHandle;
};

}	// namespace trias_gist 

#endif
