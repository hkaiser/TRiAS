# Makefile
# Copyright (c) 1997, 1998, Regents of the University of California
# $Header: /usr/local/devel/GiST/libgist/src/Makefile,v 1.19 1999/09/27 01:09:01 marcel Exp $

include Makefile.inc

all: CMDLINE AMDB

cmdline: CMDLINE

amdb: AMDB

pure: CMDLINEP

LIBGIST: 
	cd libgist ; $(MAKE) 

LIBRTREE:
	cd librtree ; $(MAKE) 

LIBBTREE:
	cd libbtree ; $(MAKE) 

LIBNPTREE:
	cd libnptree ; $(MAKE) 

CMDLINE: LIBGIST LIBRTREE LIBBTREE LIBNPTREE
	cd cmdline; $(MAKE)

CMDLINEP: LIBGIST LIBRTREE LIBBTREE
	cd cmdline; $(MAKE) pure

AMDB: GUI ANALYSIS TREEVIEW AMDBGIST 

GUI: 
	cd gui; $(MAKE) 

TREEVIEW: 
	cd treeview; $(MAKE) 

AMDBGIST: 
	cd amdbgist; $(MAKE) 

ANALYSIS: 
	cd analysis; $(MAKE) 

ALLDIRS= libgist librtree libbtree libnptree \
	cmdline gui analysis amdbgist treeview

clean:
	HERE=`pwd`; \
	for i in $(ALLDIRS); do \
	  cd $$i; $(MAKE) clean; cd $$HERE; \
	done

cleanmake:
	HERE=`pwd`; \
	for i in $(ALLDIRS); do \
	  cd $$i; $(MAKE) cleanmake; cd $$HERE; \
	done

distclean: clean cleanmake
	find $(LIBGISTHOME) -type f \( \
	  -name '*.so' -o \
	  -name '*.a' -o \
	  -name '.#*' -o \
	  -name '.nfs*' -o \
	  -name '.pure*' -o \
	  -name Makefile.bak -o \
	  -name TAGS -o \
	  -name tags -o \
	  -name ID \) -print | xargs $(RM)

depend:
	HERE=`pwd`; \
	for i in $(ALLDIRS); do \
	  cd $$i; $(MAKE) depend; cd $$HERE; \
	done

TAGS tags::
	cd $(LIBGISTHOME); \
	$(RM) TAGS; \
	find include src -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.h' -o -name '*.y' -o -name '*.l' \) -print | \
	xargs etags --c++ --append

#
# if you have mkid-3.0.8, use the commented line below instead of
# the one given (which is for GNU id-utils-3.2).
#
# we need to use our own id-lang.map because the one provided with
# id-utils-3.2 directs .cc and .cpp files to a C++ scanner that does
# not yet exist.
#
ID::
	cd $(LIBGISTHOME); \
	$(RM) ID; \
	mkid --lang-map=etc/id-lang.map --prune="tests CVS"
#	find include src -type f \( -name '*.cpp' -o -name '*.cc' -o -name '*.h' -o -name '*.y' -o -name '*.l' \) -print | mkid-3.0.8 -
