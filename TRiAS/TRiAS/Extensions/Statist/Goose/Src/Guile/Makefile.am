## $Id: Makefile.am,v 1.12 1999/05/26 20:36:25 trow Exp $ ##

# -I. and buildir gets the .x files

goosemoduledir = $(datadir)/guile/goose

INCLUDES = \
	-I.	\
	-I$(top_builddir)/src/guile	\
	-I$(top_srcdir)/src/guile	\
	$(GLIB_CFLAGS) \
	-I$(top_srcdir)/src/specfns \
	-I$(top_srcdir)/src/util \
	-I$(top_srcdir)/src/linear \
	-I$(top_srcdir)/src/containers \
	-I$(top_srcdir)/src/stats \
	-I$(includedir) \
	 $(GUILE_INCS) -DPREFIX=\"$(prefix)\" -DGOOSE_GUILE_DIR=\"$(goosemoduledir)\"

lib_LTLIBRARIES = libgoose-guile.la

##############################################################################

### Code to handle building with the "Magic Snarfer"

goose_snarfs = \
	bootstrap_wrap.x \
	pest_wrap.x \
	LinearRegression_smob.x \
	Random_smob.x \
	RealSet_smob.x

BUILT_SOURCES = $(goose_snarfs)
MAINTAINERCLEANFILES = $(goose_snarfs)
CLEANFILES = $(goose_snarfs)
EXTRA_DIST = $(goose_snarfs) gooseboot.scm Random_smob.scm RealSet_smob.scm

SUFFIXES=.x

# just use `make CC=g++' and the revised guile-snarf which uses ${CC} will work
# for C++ prototype extraction
%.x: %.cpp
	$(CXX) -E -DSCM_MAGIC_SNARFER $(INCLUDES) $< | awk 'BEGIN{foo=0} /%%%start/{foo=1} foo==1{print $0}/%%%end/{foo=0}' | sed -e 's/.*\%\%\%start//g' | sed -e 's/\%\%\%end.*//g' > $@

##############################################################################

libgoose_guile_la_SOURCES = \
        guilegoose.cpp \
	specfns_smob.cpp \
	AsciiImport_smob.cpp \
	bootstrap_wrap.cpp \
	ConfInt_smob.cpp \
	pest_wrap.cpp \
	Random_smob.cpp \
	RealSet_smob.cpp \
	LinearRegression_smob.cpp \
	snarf.h


## Dump it in the same directory as goose.
libgoose_guileincludedir = $(includedir)/goose

## Only one header, just for ease of programming. #include <goose/guilegoose.h>

libgoose_guileinclude_HEADERS = \
        guilegoose.h

#install .scm files
install-data-local:
	$(mkinstalldirs) $(goosemoduledir)
	$(INSTALL_DATA) $(srcdir)/gooseboot.scm  $(goosemoduledir)/gooseboot.scm
	$(INSTALL_DATA) $(srcdir)/Random_smob.scm  $(goosemoduledir)/Random_smob.scm
	$(INSTALL_DATA) $(srcdir)/RealSet_smob.scm  $(goosemoduledir)/RealSet_smob.scm

libgoose_guile_la_LDFLAGS = -version-info $(GUILEGOOSE_CURRENT):$(GUILEGOOSE_REVISION):$(GUILEGOOSE_AGE)

bin_PROGRAMS = gooseshell

gooseshell_SOURCES = gooseshell.cpp

gooseshell_LDADD = \
	$(GLIB_LIBS) \
	$(top_builddir)/src/specfns/libgoose-specfns.la \
	$(top_builddir)/src/util/libgoose-util.la \
	$(top_builddir)/src/linear/libgoose-linear.la \
	$(top_builddir)/src/containers/libgoose-containers.la \
	$(top_builddir)/src/stats/libgoose-stats.la \
	$(GUILE_LIBS) \
	./libgoose-guile.la


## $Id: Makefile.am,v 1.12 1999/05/26 20:36:25 trow Exp $ ##







