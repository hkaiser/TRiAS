#
#	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/Makefile,v 1.1 1995/06/30 06:46:38 bduggan Exp $
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
#		E-Mail:         info@sds.sdsc.edu
#
#		Surface Mail:   Information Center
#				San Diego Supercomputer Center
#				P.O. Box 85608
#				San Diego, CA  92138-5608
#				(619) 534-5000
#

#
#  FILE
#	Makefile	-  make the image tools
#
#  PROJECT
#	IMAGE		-  image library and tools
#
#  DESCRIPTION
#	The Image Tools manipulate images and convert between file storage
#	formats.
#
#	This Makefile invokes the file 'master.mk' after identifying
#	the host architecture.  The architecture is discerned using 
#	the 'mach' script.  The library, and all binaries are then
#	built into a subdirectory of the directory containing this file.
#
#  HISTORY
#	$Log: Makefile,v $
# Revision 1.1  1995/06/30  06:46:38  bduggan
# Initial revision
#
#

#
#  Generic Makefile setup:
#	Directory Structure:
#		BINDIR          -  where are binaries, relative to Makefile
#		BINSRCDIR       -  where is source, relative to the binary dir
#		BININCDIR       -  where are includes, relative to binary dir
#	Shell:
#		SHELL           -  shell to use (always /bin/sh)
#	Architecture:
#		ARCH            -  program to run to get architecture name
#	Standard Flags:
#		BINMAKEFLAGS    -  flags to pass to make when building binaries
#		MODE		-  whether the binaries should be static or dynamic.
#	If you wish to modify this file to support a different
#	architecture-compiler combination, then search forward
#	for 'BINFLAGS'.
#

MODE =		static
BINSRCDIR =	..
BININCDIR =	$(BINSRCDIR)/include
BINDIR =	./$(ARCH)
SHELL =		/bin/sh
ARCH =		`../mach`
BINMAKEFLAGS =	-f $(BINSRCDIR)/master.mk SRCDIR=$(BINSRCDIR) INCDIR=$(BININCDIR) ARCH=$(ARCH)



#  Top level make targets:
#	all	-  build the binaries
#	bin	-  build the binaries
#	clean	-  clean out things

all:	imsource bin

bin:	imadjust imcat imcltroll imcomp imconv imcopy imfile imfill imflip \
	imformats imgray imhist immono impaste imroll imrotate imscale \
	imshear imsplit imstoryboard imkey imlighten imdissolve imprint


#  Make the individual tools
#
imadjust:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imcat:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imcltroll:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imcomp:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imconv:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imcopy:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imdissolve:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imfile:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imfill:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imflip:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imformats:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imgray:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imhist:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

immono:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imlighten:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

impaste:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imprint:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imroll:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imrotate:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imscale:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imshear:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imsplit:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imstoryboard:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin

imkey:
	@make ARCH=$(ARCH) WHAT=$@ MODE=$(MODE) arch_bin


#  Make the source
#
imsource:	imregister.c imfeedback.c

imregister.c:	imregister.raw.c imregister.form
	rm -f imregister.c
	cp imregister.raw.c imregister.c
	chmod ugo+rw imregister.c
	sed 's/$$/\\n\\/' < imregister.form >> imregister.c
	echo '";' >> imregister.c

imfeedback.c:	imfeedback.raw.c imfeedback.form
	rm -f imfeedback.c
	cp imfeedback.raw.c imfeedback.c
	chmod ugo+rw imfeedback.c
	sed 's/$$/\\n\\/' < imfeedback.form >> imfeedback.c
	echo '";' >> imfeedback.c



#  Make things clean
#
clean:
	@make ARCH=$(ARCH) WHAT=dummy arch_clean

arch_clean:
	@echo "Cleaning out binaries for $(ARCH)"
	@-if [ ! -d $(BINDIR) ] ; then mkdir $(BINDIR); fi
	@cd $(BINDIR); make $(BINMAKEFLAGS) clean


#
#  Make a binary
#
#	BINFLAGS
#
#	To change which compiler is used for a given architecture,
#	find your architecture in the list below, and modify the
#	'CC' and 'CF' parameters.
#
#	List of flags:
#
#		CC		The compiler to use
#				This is used for both compiling and linking
#		CF		Flags during compiling
#		LF		Flags during linking
#		WHAT		What we're creating
#		MODE		Whether it's dynamic or static
#		STATIC_LIBS	If the mode is static, these are the
#				libraries to which we should
#				link.  
#		DYNAMIC_LIBS	If the mode is dynamic, these are
#				the libraries to which we should
#				link.
#		The preceeding two flags work like this:
#			jpeg_sdsc_tiff_m
#				means link to the jpeg library,
#				the tiff library, libsdsc, and the
#				math library.
#			If you wish to create your own combination of
#			libraries then you should :
#				1. Make s new string
#				   (i.e. jpeg_m	to just link to the 
#					jpeg and math libraries)
#				2. Edit master.mk.  Search for 'BINFLAGS'
#				   and add your combination to the list.
#				   (See the instructions there.)
#
#		BINMAKEFLAGS 	Locations of things, etc.
#
arch_bin:
	@echo "Building $(WHAT) for $(ARCH)"
	@-if [ ! -d $(BINDIR) ] ; then mkdir $(BINDIR); fi
	@cd $(BINDIR);\
	case $(ARCH) in \
	crayc90)       make CF="-O0 -hnopragma=allinline:allvector:opt" CC="CC" LF="" WHAT=$(WHAT) MODE=$(MODE) STATIC_LIBS=m DYNAMIC_LIBS=m $(BINMAKEFLAGS) $(WHAT);;\
	decalpha)      make CF="-O" CC="gcc" LF="" WHAT=$(WHAT) MODE=$(MODE) $(BINMAKEFLAGS) STATIC_LIBS=jpeg_sdsc_tiff_m DYNAMIC_LIBS=jpeg_sdsc_tiff_m $(WHAT);;\
	next)          make CF="-O -fwritable-strings" CC="cc" LF="" WHAT=$(WHAT) STATIC_LIBS=m DYNAMIC_LIBS=m MODE=$(MODE)	$(BINMAKEFLAGS) $(WHAT);;\
	sgi5.3)         make CF="-O" CC="cc" LF="" WHAT=$(WHAT) MODE=$(MODE) DYNAMIC_LIBS=m STATIC_LIBS=jpeg_sdsc_tiff_m	$(BINMAKEFLAGS) $(WHAT);;\
	sgi6.1)         make CF="-O" CC="cc" LF="" WHAT=$(WHAT) MODE=$(MODE) DYNAMIC_LIBS=m STATIC_LIBS=jpeg_sdsc_tiff_m	$(BINMAKEFLAGS) $(WHAT);;\
	sun4)          make CF="-O" CC="gcc" LF="-lm" WHAT=$(WHAT) MODE=$(MODE)		$(BINMAKEFLAGS) STATIC_LIBS=jpeg_sdsc_tiff_m DYNAMIC_LIBS=jpeg_sdsc_tiff_m $(WHAT);;\
	*)	       echo "Unknown architecture.  Cannot build.";;\
	esac
