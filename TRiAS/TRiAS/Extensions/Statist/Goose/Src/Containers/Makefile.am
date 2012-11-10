### $Id: Makefile.am,v 1.8 1999/05/17 23:52:08 hp Exp $ ###

INCLUDES = -I$(top_srcdir)/src/util -I$(includedir) $(GLIB_CFLAGS)

lib_LTLIBRARIES = libgoose-containers.la

libgoose_containers_la_SOURCES = \
	AsciiImport.cpp	\
	AsciiReader.cpp \
	CategoricalSet.cpp \
	Category.cpp \
	ColumnDivider.cpp	\
	DataSet.cpp \
	DateSet.cpp \
	HoleSet.cpp \
	RealSet.cpp \
	StringSet.cpp 

libgoose_containersincludedir = $(includedir)/goose

libgoose_containersinclude_HEADERS = \
	AsciiImport.h	\
	AsciiReader.h	\
	CategoricalSet.h \
	Category.h \
	ColumnDivider.h	\
	DataSet.h \
	DateSet.h \
	HoleSet.h \
	RealSet.h \
	StringSet.h

libgoose_containers_la_LDFLAGS = -version-info $(GOOSE_CURRENT):$(GOOSE_REVISION):$(GOOSE_AGE)

### $Id: Makefile.am,v 1.8 1999/05/17 23:52:08 hp Exp $ ###