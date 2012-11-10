#
#       $Header:$
#       Copyright (c) 1989-1994  San Diego Supercomputer Center (SDSC)
#               a division of General Atomics, San Diego, California, USA
#
#       Users and possessors of this source code are hereby granted a
#       nonexclusive, royalty-free copyright and design patent license to
#       use this code in individual software.  License is not granted for
#       commercial resale, in whole or in part, without prior written
#       permission from SDSC.  This source is provided "AS IS" without express
#       or implied warranty of any kind.
#
#       For further information contact:
#               E-Mail:         info@sds.sdsc.edu
#
#               Surface Mail:   Information Center
#                               San Diego Supercomputer Center
#                               P.O. Box 85608
#                               San Diego, CA  92138-5608
#                               (619) 534-5000
#

#
#  FILE
#       Makefile        -  make the SDSC library
#
#  PROJECT
#       libsdsc         -  SDSC library
#
#  DESCRIPTION
#	The SDSC Library contains miscellaneous utilities for reading and
#	writing binary files, parsing command-line arguments, and so on.
#
#	This Makefile invokes the file 'master.mk' after identifying
#	the host architecture.  The architecture is discerned using the 
#	'mach' script.  The library, and all binaries are then
#	built into a subdirectory of the directory containing this file.
#
#  HISTORY
#       $Log:$
#
#
#  Generic Makefile setup:
#  	Directory Structure:
#		BINDIR		-  where are binaries, relative to Makefile
#		LIBDIR		-  where are libraries, relative to Makefile
#		BINSRCDIR	-  where is source, relative to the binary dir
#		LIBSRCDIR	-  where is source, relative to the library dir
#		BININCDIR	-  where are includes, relative to binary dir
#		LIBINCDIR	-  where are includes, relative to library dir
#	Shell:
#		SHELL		-  shell to use (always /bin/sh)
#	Architecture:
#		ARCH		-  program to run to get architecture name
#	Standard Flags:
#		LIBMAKEFLAGS	-  flags to pass to make when building libs
#		BINMAKEFLAGS	-  flags to pass to make when building binaries
#
# To modify the particular compiler that is used for an architecture,
# search forwards for LIBFLAGS twice.
#
SRCDIR =	.
INCDIR =	./include
BINDIR =	./$(ARCH)
LIBDIR =	./$(ARCH)
BINSRCDIR =	..
LIBSRCDIR =	..
BININCDIR =	$(BINSRCDIR)/include
LIBINCDIR =	$(LIBSRCDIR)/include
SHELL =		/bin/sh
ARCH =		`../mach`
LIBMAKEFLAGS =	-f $(LIBSRCDIR)/master.mk SRCDIR=$(LIBSRCDIR) \
		INCDIR=$(LIBINCDIR) LIBDIR=../$(LIBDIR) LIB=$(LIB) ARCH=$(ARCH)
BINMAKEFLAGS =	-f $(BINSRCDIR)/master.mk SRCDIR=$(BINSRCDIR) \
		INCDIR=$(BININCDIR) LIBDIR=../$(LIBDIR) LIB=$(LIB) ARCH=$(ARCH)

LIB =		libsdsc.a



#  Top level make targets:
#	all	-  build the library and its binary test programs
#	bin	-  just build the binaries
#	lib	-  just build the library
#	clean	-  clean out things
#
all:	lib allbin

lib:
	@make ARCH=$(ARCH) arch_lib

lint:
	@make ARCH=$(ARCH) arch_lint


#  Make the verification tools
#
allbin:
	@make ARCH=$(ARCH) WHAT=allbin arch_bin

binverify:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

binprint:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

mkhost:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

tagverify:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

argtest:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

argtest2:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

xform:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

t:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin



#  Make things clean
#
clean:
	@make ARCH=$(ARCH) arch_clean

arch_clean:
	@echo "Cleaning out binaries and $(LIB) for $(ARCH)"
	@-if [ ! -d $(BINDIR) ] ; then mkdir $(BINDIR); fi
	@-if [ ! -d $(LIBDIR) ] ; then mkdir $(LIBDIR); fi
	@cd $(BINDIR); make $(BINMAKEFLAGS) clean
	@cd $(LIBDIR); make $(LIBMAKEFLAGS) clean


#
#  Make a binary
#
# LIBFLAGS
#   To change the compiler used for an architecture, find
# your architecture in the list below, and then modify..
#
#	CC 	C Compiler
#	CF	Compile flags
#	LF	Link flags
#
arch_bin:
	@echo "Building $(WHAT) for $(ARCH)"
	@-if [ ! -d $(BINDIR) ] ; then mkdir $(BINDIR); fi
	@cd $(BINDIR);\
	case $(ARCH) in \
	alliantfx2800) make CF="-OMils -i -w" CC="fxc" LF=""	$(BINMAKEFLAGS) $(WHAT);\
		       /usr/alliant/execute -w -ce $(WHAT);;\
	crayy)         make CF="-h noopt" CC="cc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	crayc90)       make CF="-O0 -hnopragma=allinline:allvector:opt" CC="cc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	dec_risc)      make CF="-Wf,-XNl4096 -Olimit 1000" CC="gcc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	decalpha)      make CF="-O" CC="gcc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	decvax)        make CF="-J -O" CC="cc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	hp700)         make CF="-O" CC="gcc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	ibm_rs)        make CF="-O" CC="gcc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	next)          make CF="-O" CC="cc"  LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	sgi5.3)           make CF="-O" CC="cc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	sgi6.1)           make CF="-O" CC="cc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	sgi5d)         make CF="-Wf,-XNl4096 -Olimit 1000 -ansi -fullwarn -prototypes" CC="cc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	so12)          make CF="-O" CC="gcc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	sun3)          make CF="-O" CC="cc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	sun4)          make CF="-O" CC="gcc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	*)	       echo "Unknown architecture.  Cannot build.";;\
	esac

#
#  Make a library
#
# LIBFLAGS
#   To change the compiler used for an architecture, find
# your architecture in the list below, and then modify..
#
#	CC 	C Compiler
#	CF	Compile flags
# These aren't really used, since we're just making a library.
# However, they're passed to master.mk for consistency.
#
arch_lib:
	@echo "Building $(LIB) for $(ARCH)"
	@-if [ ! -d $(LIBDIR) ] ; then mkdir $(LIBDIR); fi
	@cd $(LIBDIR);\
	case $(ARCH) in \
	alliantfx2800) \
		make CF="-OMils -i -w" CC="fxc"		$(LIBMAKEFLAGS) lib;;\
	crayy) \
		make CF="-h noopt" CC="cc"		$(LIBMAKEFLAGS) lib;;\
	crayc90) \
		make CF="-O0 -hnopragma=allinline:allvector:opt" CC="cc"	$(LIBMAKEFLAGS) lib;;\
	dec_risc) \
		make CF="-Wf,-XNl4096 -Olimit 1000" CC="cc" 	$(LIBMAKEFLAGS) lib;;\
	decalpha) \
		make CF="-O" CC="gcc" 			$(LIBMAKEFLAGS) lib;;\
	decvax) \
		make CF="-J -Wf,-XNl4096 -O -Olimit 1000" CC="cc" 	$(LIBMAKEFLAGS) lib;;\
	hp700) \
		make CF="-O" CC="cc" 			$(LIBMAKEFLAGS) lib;;\
	ibm_rs) \
		make CF="-O" CC="cc" 			$(LIBMAKEFLAGS) lib;;\
	next) \
		make CF="-O" CC="cc" 			$(LIBMAKEFLAGS) lib;;\
	sgi5.3) \
		make CF="" CC="cc" 	$(LIBMAKEFLAGS) lib;;\
	sgi6.1) \
		make CF="" CC="cc" 	$(LIBMAKEFLAGS) lib;;\
	sgi5d) \
		make CF="-Wf,-XNl4096 -Olimit 1000 -ansi -fullwarn -prototypes" CC="cc" 	$(LIBMAKEFLAGS) lib;;\
	so12) \
		make CF="-O" CC="gcc" 		$(LIBMAKEFLAGS) lib;;\
	sun3) \
		make CF="-O" CC="cc" 		$(LIBMAKEFLAGS) lib;;\
	sun4) \
		make CF="-O" CC="gcc" 		$(LIBMAKEFLAGS) lib;;\
	sparc) \
		make CF="-O" CC="gcc" 		$(LIBMAKEFLAGS) lib;;\
	*) \
		echo "Unknown architecture.  Cannot build.";;\
	esac

#  Make a lint pass
#
#	decalpha lint options:
#	    Checking is on by default, off by request.
#		-MA	Enforces ANSI C standard rules.
#		-Q	This option turns on checking for all common programming
#			techniques which might cause problems when moving from
#			32-bit systems to 64-bit systems.
#		-Qs	Suppresses checking for problematic sign extensions to
#			long.  (never seems to be relevant!)
#		-Qc	Suppresses checking for problematic type casts.
#			(otherwise it complains about all malloc usage!)
#		-u	Suppress complaints about functions and external
#			variables used and not defined, or defined and not used.
#		-v	Suppress complaints about unused arguments in functions.
#		-x	Do not report variables referred to by external
#			declarations but never used.
#
#	sgi/sgi5d lint options:
#	    Checking is on by default, off by request.
#	    SGI lint is ANSI compliant, so enable ANSI prototypes.
#		-x	Do not report variables referred to by external
#			declarations but never used.
#		-y	At each function call, warn if there is no function
#			prototype in scope.
#		-z	Turn off warnings about undefined structure definitions.
#
#	sun4/sparc lint options:
#	    Checking is off by default, on by request.
#	    Sun lint is not ANSI compliant, so don't enable ANSI checking.
#		-a	Report assignments of long values to variables that are
#			not long.
#		-b	Report break statements that cannot be reached.
#		-c	Complain about casts which have questionable
#			portability.
#		-h	Apply a number of heuristic tests to attempt to intuit
#			bugs, improve style, and reduce waste.
#		-u	Do not complain about functions and external variables
#			used and not defined, or defined and not used.
#		-x	Report variables referred to by extern declarations
#			but never used.
#		-z	Do not complain about structures that are never
#			defined.
#		
arch_lint:
	@echo "Linting for $(ARCH)"
	@-if [ ! -d $(LIBDIR) ] ; then mkdir $(LIBDIR); fi
	@cd $(LIBDIR);\
	case $(ARCH) in \
	alliantfx2800) \
		;;\
	crayc90) \
		;;\
	crayy) \
		;;\
	dec_risc) \
		;;\
	decalpha) \
		make LINTF="-MA -Qsc -u -v -x" LINT="lint" $(LIBMAKEFLAGS) lint;;\
	decvax) \
		;;\
	hp700) \
		;;\
	ibm_rs) \
		;;\
	next) \
		;;\
	sgi5.3) \
		make LINTF="-x -y -z" LINT="lint" $(LIBMAKEFLAGS) lint;;\
	sgi6.1) \
		make LINTF="-x -y -z" LINT="lint" $(LIBMAKEFLAGS) lint;;\
	sgi5d) \
		make LINTF="-x -y -z" LINT="lint" $(LIBMAKEFLAGS) lint;;\
	sun3) \
		;;\
	sun4) \
		make LINTF="-a -b -c -h -u -x -z" LINT="lint" $(LIBMAKEFLAGS) lint;;\
	sparc) \
		make LINTF="-a -b -c -h -u -x -z" LINT="lint" $(LIBMAKEFLAGS) lint;;\
	*) \
		echo "Unknown architecture.  Cannot lint.";;\
	esac
