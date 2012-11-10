# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- \\
# NOTICE:                                                             \\
#   This file is part of "The SI Library of Unit-Based Computation."  \\
#   See "doc/README" for copyright, license, and other information.   \\
# -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=- \\

# ======================================================================
#
# Makefile for SIunits ("The SI Library of Units-Based Computation")
#
# Target list:
#	all		build/install hdrs, libs, tests, and docs targets
#	clean		remove unnecessary intermediate files
#	docs		build/install documentation files
#	hdrs		build/install header filess
#	libs		build/install library files
#	print		obtain hardcopy of all pertinent sources
#	realclean	make clean + remove tests and docs targets
#	shar		prepare distribution self-extracting shar file
#	tar		prepare distribution tar file
#	tests		build/install selected validation test executables
#	uninstall	make realclean + remove all other installed targets
#
# Library file targets (see documentation for names' significance):
#	stdModel.a
#	relModel.a
#	hepModel.a
#	qtmModel.a
#	natModel.a
#
# ======================================================================


# ----------------------------------------------------------------------
# Define the product name:
# ----------------------------------------------------------------------

PRODUCT	= SIunits


# ----------------------------------------------------------------------
# Define the destination directories:
# ----------------------------------------------------------------------

tgtdir	= $(HOME)/bin/$(PRODUCT)/# base directory for installed product
docdir	= $(tgtdir)doc/#	# directory for installed postscript
incldir = $(tgtdir)include/#	# directory for installed headers
libdir	= $(tgtdir)lib/#	# directory for installed libraries
testdir	= $(tgtdir)bin/#	# directory for installed test binaries
tmpdir	= $(tgtdir)tmp/#	# directory for intermediate results


# ----------------------------------------------------------------------
# Define the build software and options to be used during building:
# ----------------------------------------------------------------------

# we don't care about any of this make's build-in rules:
MAKEFLAGS = -r

# preprocessor and its flags:
CPP	= KCC
ABI	=#-32
CPPFLAGS=\
	 -I$(incldir)\
	 -D__KAI_STRICT\
	 -D__STRICT_ANSI__\
	 $(ABI)

# C++ compiler and its flags:
CXX	= KCC
howOPT	= +K0
KAIv3_3	= --one_per
onPC	= --backend -m486
CXXFLAGS=\
	 $(CPPFLAGS)\
	 --strict\
	 --abstract_pointer\
	 --no_implicit_include\
	 --no_implicit_typename\
	 $(howOPT) $(KAIv3_3) $(onPC)

# linker and its flags:
LD	= KCC
LDFLAGS	=\
	 $(ABI)\
	 -L$(libdir)\


# ----------------------------------------------------------------------
# Define other utilities:
# ----------------------------------------------------------------------

A2PS	= a2ps -nu -c -2 -s2 -nL
CHMOD	= @chmod
CP	= cp
DIFF	= diff
DVIPS	= dvips -q
LATEX	= latex
LPR	= flpr -h fnprt -q wh9w_ps_duplex
MKDIR	= @mkdir -m755 -p
RM	= rm -f
RMALL	= $(RM) -r
SED	= sed
SHAR	= shar
TAR	= tar


# ----------------------------------------------------------------------
# Itemize the package (distribution) contents:
# ----------------------------------------------------------------------

DISTDIRS=			\
	doc			\
	src			\
	SIunits			\
	test			\

BUILDERS=			\
	makefile		\
	sort.dims		\
	src/calibrate.cc	\

DOCSRCS	=			\
	doc/intro.tex		\

TXTSRCS	=			\
	README			\
	doc/README		\
	doc/algebra.txt		\
	doc/abstract.txt	\
	doc/bib.txt		\

HDRSRCS	=			\
	SIunits/allModel_cc	\
	SIunits/allModel_h	\
	SIunits/anyModel.h	\
	SIunits/calibration	\
	SIunits/consts.dat	\
	SIunits/dims.dat	\
	SIunits/elements.dat	\
	SIunits/hepModel.h	\
	SIunits/natModel.h	\
	SIunits/qtmModel.h	\
	SIunits/relModel.h	\
	SIunits/si.h		\
	SIunits/stdModel.h	\
	SIunits/wv.h		\

LIBSRCS	=			\
	src/hep/Model.cc	\
	src/nat/Model.cc	\
	src/qtm/Model.cc	\
	src/rel/Model.cc	\
	src/std/Model.cc	\

TESTSRCS=			\
	test/testconsts.cc	\
	test/fullTest.cc	\
	test/example1.cc	\
	test/example2.cc	\
	test/example3.cc	\
	test/ex_RadLen.cc	\

CONTENTS=		\
	$(BUILDERS) 	\
	$(DOCSRCS) 	\
	$(TXTSRCS) 	\
	$(HDRSRCS) 	\
	$(LIBSRCS) 	\
	$(TESTSRCS)	\


# ----------------------------------------------------------------------
# Itemize the detailed package targets:
# ----------------------------------------------------------------------

DIRTGTS =			\
	$(docdir)		\
	$(incldir)		\
	$(libdir)		\
	$(testdir)		\

DOCTGTS	=			\
	$(docdir)intro.ps	\

HDRTGTS	=			\
	$(incldir)allModel_cc	\
	$(incldir)allModel_h	\
	$(incldir)anyModel.h	\
	$(incldir)calibration	\
	$(incldir)consts.dat	\
	$(incldir)dims.dat	\
	$(incldir)elements.dat	\
	$(incldir)hepModel.h	\
	$(incldir)natModel.h	\
	$(incldir)qtmModel.h	\
	$(incldir)relModel.h	\
	$(incldir)si.h		\
	$(incldir)stdModel.h	\
	$(incldir)wv.h		\

LIBTGTS =			\
	$(libdir)libstdModel.a	\
	$(libdir)librelModel.a	\
	$(libdir)libhepModel.a	\
	$(libdir)libqtmModel.a	\
	$(libdir)libnatModel.a	\

TEST1TGTS=			\
	$(testdir)teststdconsts	\
	$(testdir)testrelconsts	\
	$(testdir)testhepconsts	\
	$(testdir)testqtmconsts	\
	$(testdir)testnatconsts	\

TEST2TGTS=			\
	$(testdir)fullTeststd	\
	$(testdir)fullTestrel	\
	$(testdir)fullTesthep	\
	$(testdir)fullTestqtm	\
	$(testdir)fullTestnat	\

EXAMPLES=			\
	$(testdir)ex_RadLen	\
	$(testdir)example1	\
	$(testdir)example2	\
	$(testdir)example3	\

# ----------------------------------------------------------------------
# Build and install all libs, tests, and docs targets:
# ----------------------------------------------------------------------

.PHONY : all
all    : docs hdrs libs tests


# ----------------------------------------------------------------------
# Create needed target directories:
# ----------------------------------------------------------------------

$(DIRTGTS) :
	-$(MKDIR) $(tgtdir) $@


# ----------------------------------------------------------------------
# Build and install new calibration file:
# ---------------------------------------------------------------------- 
.PHONY      : calibrate calibration

calibrate   : $(testdir) $(testdir)calibrate SIunits/consts.dat

$(testdir)calibrate : src/calibrate.cc $(libdir)libstdModel.a
	$(CXX) $(CXXFLAGS) $< $(LDFLAGS) -lstdModel -lm -o $@
	$(CHMOD) 755 $@

calibration : $(incldir) calibrate
	$(testdir)calibrate > $(incldir)calibration
	$(CHMOD) 644 $(incldir)calibration


# ----------------------------------------------------------------------
# Remove detritus (unnecessary intermediate files):
# ----------------------------------------------------------------------

.PHONY : clean
clean  :
	-$(RM) intro.aux intro.dvi intro.log intro.ps intro.toc
	-$(RMALL) $(foreach d,std rel hep qtm nat,src/$d/ti_files/)
	-$(RMALL) test/dir_*/


# ----------------------------------------------------------------------
# Build and install postscript documentation files:
# ----------------------------------------------------------------------

.PHONY : docs
docs   : $(docdir) $(DOCTGTS)

$(DOCTGTS) : $(docdir)%.ps : doc/%.tex
	( $(LATEX) $< && $(LATEX) $< ) > /dev/null
	$(DVIPS) $*.dvi -o $@


# ----------------------------------------------------------------------
# Build and install header files:
# ----------------------------------------------------------------------

.PHONY : hdrs
hdrs   : $(incldir) $(HDRTGTS)

$(filter $(incldir)%,$(HDRTGTS)) : $(incldir)% : SIunits/%
	$(CP) $< $@
	$(CHMOD) 644 $@


# ----------------------------------------------------------------------
# Build and install library files:
# ----------------------------------------------------------------------

.PHONY : libs
libs   : hdrs $(libdir) $(LIBTGTS)

MOSTHDRTGTS = $(filter-out %calibration,$(HDRTGTS))

$(filter $(libdir)lib%Model.a,$(LIBTGTS)) : $(libdir)lib%Model.a : src/%/Model.cc $(MOSTHDRTGTS)
	cd src/$*; $(CXX) $(CXXFLAGS) Model.cc -o $@
	$(CHMOD) 644 $@

$(filter-out $(libdir)libstdModel.a,$(LIBTGTS)) : $(filter %calibration,$(HDRTGTS))

# ----------------------------------------------------------------------
# Print the complete library source code:
# ----------------------------------------------------------------------

.PHONY : print
print  : $(BUILDERS) $(HDRSRCS) $(LIBSRCS)
	$(A2PS) $(BUILDERS) $(HDRSRCS) $(LIBSRCS) | $(LPR)


# ----------------------------------------------------------------------
# make clean, then also remove tests and docs targets, leaving directories:
# ----------------------------------------------------------------------

.PHONY    : realclean
realclean : clean
	-$(RM) ../$(PRODUCT).tar ../$(PRODUCT).shar
	-$(RM) $(docdir)intro.ps
	-$(RM) $(testdir)calibrate
	-$(RMALL) $(foreach d,std rel hep qtm nat,$(testdir)test$(d)consts)
	-$(RMALL) $(foreach d,std rel hep qtm nat,$(testdir)fullTest$(d))


# ----------------------------------------------------------------------
# Undo and remove all installed & intermediate files, and directories:
# ----------------------------------------------------------------------

.PHONY    : uninstall
uninstall : realclean
	-$(RMALL) $(tgtdir)


# ----------------------------------------------------------------------
# Prepare a distribution tar file:
# ----------------------------------------------------------------------

.PHONY : tar
tar    : ../$(PRODUCT).tar
../$(PRODUCT).tar : $(CONTENTS)
	cd ..; $(TAR) -cf $(PRODUCT).tar `echo ' '$(CONTENTS) | sed "s: : $(PRODUCT)/:g"`


# ----------------------------------------------------------------------
# Prepare a self-extracting (shell archive) distribution file:
# ----------------------------------------------------------------------

.PHONY : shar
shar   : ../$(PRODUCT).shar
../$(PRODUCT).shar : $(CONTENTS)
	cd ..; $(SHAR) `echo ' '$(CONTENTS) | sed "s: : $(PRODUCT)/:g"` > $(PRODUCT).shar 2> /dev/null


# ----------------------------------------------------------------------
# Prepare validation test executables:
# ----------------------------------------------------------------------

.PHONY : tests
tests  : $(testdir) $(TEST1TGTS) $(TEST2TGTS) $(EXAMPLES)

$(filter $(testdir)test%consts,$(TEST1TGTS)) : $(testdir)test%consts : $(libdir)lib%Model.a test/testconsts.cc $(HDRTGTS)
	-$(MKDIR) test/dir_$(@F)
	cd test/dir_$(@F); $(CXX) $(CXXFLAGS)\
		-DUSE$*Model ../testconsts.cc $(LDFLAGS) -l$*Model -lm -o $@
	$(CHMOD) 755 $@

$(filter $(testdir)fullTest%,$(TEST2TGTS)) : $(testdir)fullTest% : $(libdir)lib%Model.a test/fullTest.cc $(HDRTGTS)
	-$(MKDIR) test/dir_$(@F)
	cd test/dir_$(@F); $(CXX) $(CXXFLAGS)\
		-DUSE$*Model ../fullTest.cc $(LDFLAGS) -l$*Model -lm -o $@
	$(CHMOD) 755 $@

$(filter $(testdir)%,$(EXAMPLES)) : $(testdir)% : test/%.cc $(HDRTGTS)
	-$(MKDIR) test/dir_$(@F)
	cd test/dir_$(@F); $(CXX) $(CXXFLAGS)\
		-DUSEstdModel ../$(@F).cc $(LDFLAGS) -lstdModel -lm -o $@
	$(CHMOD) 755 $@

#=======================================================================
