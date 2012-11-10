## $Id: Makefile.am,v 1.8 1999/07/09 19:12:05 trow Exp $ ##

## Include from the src directory
INCLUDES = \
	$(GLIB_CFLAGS) \
	-I$(top_srcdir)/src/specfns \
	-I$(top_srcdir)/src/util \
	-I$(top_srcdir)/src/linear \
	-I$(top_srcdir)/src/containers \
	-I$(top_srcdir)/src/stats \
	-I$(includedir)	

LDADD = \
	$(GLIB_LIBS) \
	$(top_builddir)/src/specfns/libgoose-specfns.la \
	$(top_builddir)/src/util/libgoose-util.la \
	$(top_builddir)/src/linear/libgoose-linear.la \
	$(top_builddir)/src/containers/libgoose-containers.la \
	$(top_builddir)/src/stats/libgoose-stats.la

EXTRA_DIST = runtests.pl README

noinst_PROGRAMS = \
	test_A001 \
	test_A002 \
	test_B001 \
	test_B002 \
	test_B003 \
	test_B004 \
	test_B005 \
	test_B006 \
	test_E001 \
	test_E002 \
	test_E003 \
	test_E004 \
	test_G001 \
	test_H001

test_A001_SOURCES = test_A001.cpp
test_A002_SOURCES = test_A002.cpp
test_B001_SOURCES = test_B001.cpp
test_B002_SOURCES = test_B002.cpp
test_B003_SOURCES = test_B003.cpp
test_B004_SOURCES = test_B004.cpp
test_B005_SOURCES = test_B005.cpp
test_B006_SOURCES = test_B006.cpp
test_E001_SOURCES = test_E001.cpp
test_E002_SOURCES = test_E002.cpp
test_E003_SOURCES = test_E003.cpp
test_E004_SOURCES = test_E004.cpp
test_G001_SOURCES = test_G001.cpp
test_H001_SOURCES = test_H001.cpp

## $Id: Makefile.am,v 1.8 1999/07/09 19:12:05 trow Exp $ ##