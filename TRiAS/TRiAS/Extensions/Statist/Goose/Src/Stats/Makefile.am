### $Id: Makefile.am,v 1.11 1999/08/07 05:55:03 trow Exp $ ###

INCLUDES = -I$(top_srcdir)/src/specfns -I$(top_srcdir)/src/util -I$(top_srcdir)/src/linear -I$(top_srcdir)/src/containers -I$(includedir) $(GLIB_CFLAGS)
 
lib_LTLIBRARIES = libgoose-stats.la

libgoose_stats_la_SOURCES = \
	KernelDE.cpp \
	LinearRegression.cpp \
	MetaCurve.cpp \
	PolynomialRegression.cpp \
	bootstrap.cpp \
	descriptive.cpp \
	fit.cpp \
	jackknife.cpp \
	kolmogorov_smirnov.cpp \
	moving_average.cpp \
	normality_testing.cpp \
	parametric_estimation.cpp \
	runs.cpp \
	wilcoxon.cpp \
	CochranQ.cpp \
	Kruskal_Wallis.cpp \
	McNemar.cpp \
	Spearman.cpp

libgoose_statsincludedir = $(includedir)/goose

libgoose_statsinclude_HEADERS = \
	KernelDE.h \
	LinearRegression.h \
	MetaCurve.h \
	PolynomialRegression.h \
	bootstrap.h \
	descriptive.h \
	fit.h \
	jackknife.h \
	kolmogorov_smirnov.h \
	moving_average.h \
	normality_testing.h \
	parametric_estimation.h \
	runs.h \
	wilcoxon.h \
	CochranQ.h \
	Kruskal_Wallis.h \
	McNemar.h \
	Spearman.h

libgoose_stats_la_LDFLAGS = -version-info $(GOOSE_CURRENT):$(GOOSE_REVISION):$(GOOSE_AGE)

### $Id: Makefile.am,v 1.11 1999/08/07 05:55:03 trow Exp $ ###
