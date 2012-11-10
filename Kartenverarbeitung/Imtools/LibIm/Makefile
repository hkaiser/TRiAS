#
#	$Header: /sdsc/dev/vis/image/imtools/v3.0/libim/src/RCS/Makefile,v 1.1 1995/06/30 06:46:12 bduggan Exp $
#	Copyright (c) 1989-1992  San Diego Supercomputer Center (SDSC)
#		San Diego, California, USA
#
#	Users and possessors of this source code are hereby granted a
#	nonexclusive, royalty-free copyright and design patent license to
#	use this code in individual software.  License is not granted for
#	commercial resale, in whole or in part, without prior written
#	permission from SDSC.  This source is provided "AS IS" without express
#	or implied warranty of any kind.
#
#	For further information contact:
#		E-Mail:		info@sds.sdsc.edu
#
#		Surface Mail:	Information Center
#				San Diego Supercomputer Center
#				P.O. Box 85608
#				San Diego, CA  92138-5608
#				(619) 534-5000
#

#
#  FILE
#	Makefile	-  make the image manipulation library
#
#  PROJECT
#	libim		-  SDSC image manipulation library
#
#  DESCRIPTION
#	The Image Tools Library contains the functionality needed to manipulate
#	images and convert between file storage formats.
#
#
#  HISTORY
#	$Log: Makefile,v $
# Revision 1.1  1995/06/30  06:46:12  bduggan
# Initial revision
#
#	This Makefile invokes the file 'master.mk' after figuring out
#	which architecture we are building for.  The architure is discerned
#	using the 'mach' script.  The library, and all binaries are then
#	built into a subdirectory of the directory containing this file.
#
#  Generic Makefile setup:
#  	Directory Structure:
#		BINDIR		-  where are binaries, relative to Makefile
#		LIBDIR		-  where are libraries, relative to Makefile
#		BINSRCDIR	-  where is source, relative to the binary dir
#		LIBSRCDIR	-  where is source, relative to the library dir
#		BININCDIR	-  where are includes, relative to binary dir
#		LIBINCDIR	-  where are includes, relative to library dir
#		SODIR		-  where is the shared library, relative to Makefile
#	Shell:
#		SHELL		-  shell to use (always /bin/sh)
#	Architecture:
#		ARCH		-  program to run to get architecture name
#	Standard Flags:
#		LIBMAKEFLAGS	-  flags to pass to make when building libs
#		BINMAKEFLAGS	-  flags to pass to make when building binaries
#		DEFINES		-  defines to pass to the compiler when building the library
#				   define USE_TIFF_LIB to use the tiff library
#				   define USE_GHOSTSCRIPT to use ghostscript
#                                  define USE_JPEG_LIB to use the jpeg library.
#                                  Please see the accompanying README file for 
#                                  information about how to use the defines above.
#
#				   You may specify the executable name for ghostscript
#				   or the path by either using -DIM_GHOSTSCRIPT=\"/bin/gs\"
#				   (says that the path is /bin/gs) or by setting the environment 
#				   variable 'IM_GHOSTSCRIPT' during run-time.
#				   (The default is to try to find 'gs' in the PATH variable.)
#
#	To modify the particular compiler or flags used for an architecture
#	search forward for LIBFLAGS three times.
#
ARCH =		`../mach`
BINDIR =	./$(ARCH)
LIBDIR =	./$(ARCH)
BINSRCDIR =	..
LIBSRCDIR =	..
BININCDIR =	$(BINSRCDIR)/include
LIBINCDIR =	$(LIBSRCDIR)/include
DEFINES =	"-DUSE_GHOSTSCRIPT"
DEFINESGTJ =    "-DUSE_GHOSTSCRIPT -DUSE_TIFF_LIB -DUSE_JPEG_LIB"

SODIR = 	./$(ARCH)

SHELL =		/bin/sh

# If your host architecture has TIFF, JPEG, and Ghostscript support (i.e.,
# it's been compiled successfully there), then use LIBMAKEFLAGSGTJ.  Otherwise
# use LIBMAKEFLAGS.
LIBMAKEFLAGS =	-f $(LIBSRCDIR)/master.mk LIB=$(LIB) SRCDIR=$(LIBSRCDIR) \
		INCDIR=$(LIBINCDIR) LIBDIR=../$(LIBDIR) ARCH=$(ARCH) \
		DEFINES=$(DEFINES)
LIBMAKEFLAGSGTJ= -f $(LIBSRCDIR)/master.mk LIB=$(LIB) SRCDIR=$(LIBSRCDIR) \
		INCDIR=$(LIBINCDIR) LIBDIR=../$(LIBDIR) ARCH=$(ARCH) \
		DEFINES=$(DEFINESGTJ)
SOMAKEFLAGS =	-f $(LIBSRCDIR)/master.mk SO=$(SO) SRCDIR=$(LIBSRCDIR) \
		INCDIR=$(LIBINCDIR) LIBDIR=../$(LIBDIR) ARCH=$(ARCH) \
		DEFINES=$(DEFINES)
SOMAKEFLAGSGTJ= -f $(LIBSRCDIR)/master.mk SO=$(SO) SRCDIR=$(LIBSRCDIR) \
		INCDIR=$(LIBINCDIR) LIBDIR=../$(LIBDIR) ARCH=$(ARCH) \
		DEFINES=$(DEFINESGTJ) SODIR=$(SODIR)
BINMAKEFLAGS =	-f $(BINSRCDIR)/master.mk LIB=$(LIB) SRCDIR=$(BINSRCDIR) \
		INCDIR=$(BININCDIR) LIBDIR=../$(LIBDIR) ARCH=$(ARCH)

# LIB is the name of the library.
# SO is the name of the shared library (if we're making one.)
# SA is the name of the shared archive (if we need to make one)
# VARFILES are files that contain only global variable declarations.
# VARFILES is only used if we're making a shared archive.

LIB =		libim.a
SO =		libim.so.3.0
SA =		libim.sa.3.0
VARFILES =	imerrno.o 

#  Top level make targets:
#	all	-  build the library and its binary test programs
#	lib	-  just build the library
#	clean	-  clean out things
#
all:	lib

lib:
	@make ARCH=$(ARCH) arch_lib

so:
	@make ARCH=$(ARCH) arch_so

# Make the Core Objects
#
im.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imclt.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imfile.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imfmt.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imgiflzw.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imlzw.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

#immix.o:
#	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imschemes.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imvfb.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imvfbadjust.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imvfbcomp.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imvfbflip.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imvfbhist.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imvfblight.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imvfbresize.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imvfbrotate.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imvfbto.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imvfbchan.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

macpack.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin


# Make the Image Formats
#
imbmp.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

#imcgm.o:
#	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imcur.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imeps.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imgif.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imhdfread.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imhdfwrite.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imico.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imicon.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imiff.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imjpeg.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

immiff.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

immpnt.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

impbm.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

impcx.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

impic.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

impict.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

impix.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imps.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imras.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imrla.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imrle.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imrgb.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imsoftimage.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imsynu.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imtga.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imtiff.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imviff.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imx.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imxbm.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imxpm.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin

imxwd.o:
	@make ARCH=$(ARCH) WHAT=$@ arch_bin


#  Make things clean
#
clean:
	@make ARCH=$(ARCH) arch_clean

arch_clean:
	@echo "Cleaning out $(LIB) for $(ARCH)"
	@if [ ! -d $(LIBDIR) ] ; then mkdir $(LIBDIR); fi
	@cd $(LIBDIR); make $(LIBMAKEFLAGS) clean

#  Make a binary
#
# LIBFLAGS
#	To change the compiler / flags, just find your
#	architecture in the list below and modify the CC
#	parameter and/or the CF parameter.
#
#	CC	Compiler
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
	crayy)         make CF="-h noopt" CC="cc" LF="-lnet"	$(BINMAKEFLAGS) $(WHAT);;\
	crayc90)       make CF="-O0 -hnopragma=allinline:allvector:opt" CC="CC" LF="-lnet"	$(BINMAKEFLAGS) $(WHAT);;\
	decstation)    make CF="-Wf,-XNl4096 -Olimit 1000" CC="cc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	decalpha)      make CF="-O" CC="gcc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	decvax)        make CF="-J -O" CC="cc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	hp700)         make CF="-O" CC="cc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	ibmrs6000)     make CF="-O" CC="cc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	next)          make CF="-O -fwritable-strings" CC="cc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	sgi5.3)        make CF="" CC="cc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	sgi6.1)        make CF="" CC="cc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	sgi5d)         make CF="-Wf,-XNl4096 -Olimit 1000" CC="cc" LF=""	$(BINMAKEFLAGS) $(WHAT);;\
	sun3)          make CF="-O" CC="cc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	sun4)          make CF="-O" CC="gcc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	sparc)         make CF="-O" CC="gcc" LF=""		$(BINMAKEFLAGS) $(WHAT);;\
	*)	       echo "Unknown architecture.  Cannot build.";;\
	esac


#
#  Make a library
#
# LIBFLAGS
#	To change the compiler / flags, just find your
#	architecture in the list below and modify the CC
#	parameter and/or the CF parameter.
#
#	CC	Compiler
#	CF	Compile flags
#	LF	Link flags
#
#	None of these are actually used.  When creating
#	a library, you don't need to compile.  However,
#	the flags are passed to master.mk anyway, for
#	consistency.
arch_lib:
	@echo "Building $(LIB) for $(ARCH)"
	@-if [ ! -d $(LIBDIR) ] ; then mkdir $(LIBDIR); fi
	@cd $(LIBDIR);\
	case $(ARCH) in \
	alliantfx2800) make CF="-OMils -i -w" CC="fxc"	$(LIBMAKEFLAGS) lib;;\
	crayy)         make CF="-h noopt" CC="cc"	$(LIBMAKEFLAGS) lib;;\
	crayc90)         make CF="-O0 -hnopragma=allinline:allvector:opt" CC="CC"	$(LIBMAKEFLAGS) lib;;\
	decstation)    make CF="-Wf,-XNl4096 -Olimit 1000" CC="cc" 	$(LIBMAKEFLAGS) lib;;\
	decalpha)      make CF="-O" CC="gcc" 	$(LIBMAKEFLAGSGTJ) lib;;\
	decvax)        make CF="-J -Wf,-XNl4096 -O -Olimit 1000" CC="cc" 	$(LIBMAKEFLAGS) lib;;\
	hp700)         make CF="-O" CC="cc" 		$(LIBMAKEFLAGS) lib;;\
	ibmrs6000)     make CF="-O" CC="cc" 		$(LIBMAKEFLAGS) lib;;\
	next)          make CF="-O -fwritable-strings" CC="cc" 		$(LIBMAKEFLAGS) lib;;\
	sgi5.3)        make CF="-O" CC="cc" LF=""	$(LIBMAKEFLAGSGTJ) lib;;\
	sgi6.1)        make CF="-O" CC="cc" LF=""	$(LIBMAKEFLAGSGTJ) lib;;\
	sun3)          make CF="-O" CC="cc" 		$(LIBMAKEFLAGS) lib;;\
	sun4)          make CF="-O" CC="gcc" 		$(LIBMAKEFLAGSGTJ) lib;;\
	sparc)         make CF="-O" CC="gcc" 		$(LIBMAKEFLAGS) lib;;\
	*)	       echo "Unknown architecture.  Cannot build.";;\
	esac


#  Make a shared object
#
#
# LIBFLAGS
#
#	(These two aren't used.)
#	CC	compiler
#	CF	compile flags
#
#	LD	Linker
#	LF	Link flags
#	SOOBJS	Other libraries to include in our shared library
#	MAKESA	Indicates whether we need to make a .sa file. 
#	SA	The name of the .sa file, if we need to make one.
#
#	If you'd like to include a new combination of libraries
#	in the shared library (the flag SOOBJS), proceed as follows:
#		1.  Add your combination.
#		    i.e. jpeg_m will include just the jpeg and math
#		    libraries.
#		2. Edit the file master.mk
#		    Search for LIBFLAGS.  Follow the instructions there.
arch_so:
	@echo "Building $(SO) for $(ARCH)"
	@-if [ ! -d $(LIBDIR) ] ; then mkdir $(LIBDIR); fi
	@cd $(SODIR);\
	case $(ARCH) in \
	decalpha)      make CC="gcc" CF="-fpic" LD="gcc" LDFLAGS="-shared" SOOBJS=jpeg_sdsc_tiff_m $(SOMAKEFLAGSGTJ) MAKESA="no" so;;\
	sgi5.3)        make CC="CC"  CF="-woff 3262" LD="CC" LDFLAGS="-shared" SOOBJS=all_jpeg_sdsc_tiff MAKESA="no" $(SOMAKEFLAGSGTJ) so;;\
	sgi6.1)        make CC="CC"  CF="" LD="CC" LDFLAGS="-shared" SOOBJS=all_jpeg_sdsc_tiff MAKESA="no" $(SOMAKEFLAGSGTJ) so;;\
	sun4)          make CC="gcc" CF="-fpic" LD="ld"  LDFLAGS="-assert pure-text" SOOBJS=none $(SOMAKEFLAGSGTJ) SA=$(SA) VARFILES=$(VARFILES)  MAKESA="yes" so;;\
	*)	       echo "Unsupported architecture.  Cannot build.";;\
	esac

