## $Id: Makefile.am,v 1.6 1999/06/03 19:27:22 trow Exp $ ##

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

noinst_PROGRAMS =  \
	gala1 \
	gausskd \
	jack_test \
	linreg \
	perm1 \
	rand1 \
	random_bench \
	shapiro_wilks \
	test_ascii_import	\
	test_gof \
	test_matrix \
	test_normal_ci \
	test_regression \
	test_runs \
	tiny \
	wilcoxon_table

gala1_SOURCES = gala1.cpp
gausskd_SOURCES = gausskd.cpp
jack_test_SOURCES = jack_test.cpp
linreg_SOURCES = linreg.cpp
perm1_SOURCES = perm1.cpp
rand1_SOURCES = rand1.cpp
random_bench_SOURCES = random_bench.cpp
shapiro_wilks_SOURCES = shapiro_wilks.cpp
test_ascii_import_SOURCES = test_ascii_import.cpp
test_gof_SOURCES = test_gof.cpp
test_matrix_SOURCES = test_matrix.cpp
test_normal_ci_SOURCES = test_normal_ci.cpp
test_regression_SOURCES = test_regression.cpp
test_runs_SOURCES = test_runs.cpp
tiny_SOURCES = tiny.cpp
wilcoxon_table_SOURCES = wilcoxon_table.cpp

## $Id: Makefile.am,v 1.6 1999/06/03 19:27:22 trow Exp $ ##
