## $Id: Makefile.am,v 1.2 1999/07/15 17:42:32 trow Exp $ ##

INCLUDES = -I$(includedir)

lib_LTLIBRARIES = libgoose-specfns.la

libgoose_specfns_la_SOURCES = \
	bdtr.cpp \
	btdtr.cpp \
	chdtr.cpp \
	choose.cpp \
	const.cpp \
	fdtr.cpp \
	gamma.cpp \
	gdtr.cpp \
	hypergeom.cpp \
	igam.cpp \
	igami.cpp \
	incbet.cpp \
	incbi.cpp \
	mtherr.cpp \
	nbdtr.cpp \
	ndtr.cpp \
	ndtri.cpp \
	pdtr.cpp \
	stdtr.cpp \
	unity.cpp 

libgoose_specfnsincludedir = $(includedir)/goose

libgoose_specfnsinclude_HEADERS = \
	mconf.h \
	specfns.h \
	specfns_protos.h

libgoose_specfns_la_LDFLAGS = -version-info $(GOOSE_CURRENT):$(GOOSE_REVISION):$(GOOSE_AGE)

## $Id: Makefile.am,v 1.2 1999/07/15 17:42:32 trow Exp $ ##