### $Id: Makefile.am,v 1.4 1999/07/09 19:44:32 trow Exp $ ###

INCLUDES = -I$(includedir)

lib_LTLIBRARIES = libgoose-util.la

libgoose_util_la_SOURCES = \
	DataConverter.cpp \
	Exception.cpp \
	Permutation.cpp \
	Random.cpp \
	goose.cpp \
	stringtools.cpp \
	zdouble.cpp

libgooseincludedir = $(includedir)/goose

libgooseinclude_HEADERS = \
	ConfInt.h \
	DataConverter.h \
	Exception.h \
	Permutation.h \
	Progress.h	\
	RCArray.h \
	RCMatrix.h \
	Random.h \
	WarningController.h \
	constants.h \
	stringtools.h \
	zdouble.h

libgoose_util_la_LDFLAGS = -version-info $(GOOSE_CURRENT):$(GOOSE_REVISION):$(GOOSE_AGE)

### $Id: Makefile.am,v 1.4 1999/07/09 19:44:32 trow Exp $ ###