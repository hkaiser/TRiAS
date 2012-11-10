#
#	$Header: /sdsc/dev/vis/image/imtools/v3.0/imtools/src/RCS/master.mk,v 1.1 1995/06/30 06:46:45 bduggan Exp $
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
#	The image tools convert image files, query their characteristics,
#	and so on.
#
#  HISTORY
#	$Log: master.mk,v $
# Revision 1.1  1995/06/30  06:46:45  bduggan
# Initial revision
#
#


#
#  Incoming Variables:
#	Directory Structure:
#		BINDIR		-  where are binaries, relative to Makefile
#		SRCDIR		-  where is source, relative to the binary dir
#		INCDIR		-  where are includes, relative to binary dir
#	Shell:
#		SHELL           -  shell to use (always /bin/sh)
#	Architecture:
#		ARCH            -  program to run to get architecture name
#	Flags:
#		CF		-  compiler flags
#		LF		-  linker flags
#		CC		-  compiler to use

SHELL =		/bin/sh

LIBSDSC =	../../libsdsc/$(ARCH)/libsdsc.a
INCSDSC =	-I../../libsdsc/include

LIBIM =		../../libim/$(ARCH)/libim.a
INCIM =		-I../../libim/include

LIBTIFF =	../../libtiff/$(ARCH)/libtiff.a
LIBJPEG =	../../libjpeg/$(ARCH)/libjpeg.a

# The next lines are for shared objects
SODIR = 	../../libim/$(ARCH)
SOIM =		$(SODIR)/libim.so.3.0

SOFLAGS =	$(SOIM) 

INCLUDES =	-I$(INCDIR) $(INCIM) $(INCSDSC)
DEFINES =
CFLAGS =	$(CF) $(INCLUDES) $(DEFINES)

LD = $(CC)

IMTOOLSOBJ =	imtools.o imregister.o imfeedback.o



# Generic code used by most of the tools
#
imtools.o:	$(SRCDIR)/imtools.c $(INCDIR)/imtools.h
	$(CC) -c $(CFLAGS) $(SRCDIR)/imtools.c

imregister.o:	$(SRCDIR)/imregister.c $(INCDIR)/imtools.h
	$(CC) -c $(CFLAGS) $(SRCDIR)/imregister.c

imfeedback.o:	$(SRCDIR)/imfeedback.c $(INCDIR)/imtools.h
	$(CC) -c $(CFLAGS) $(SRCDIR)/imfeedback.c



#
# BINFLAGS
# 	To add a new combination of libraries to this list, simply
#		1. Duplicate the two lines beginning with jpeg_sdsc_tiff_m
#		2. Create a new macro that looks like JSTMLIBS but
#		   containing your combination of libraries
#

JSTMLIBS = $(LIBJPEG) $(LIBSDSC) $(LIBTIFF) -lm

$(WHAT).o:	$(SRCDIR)/$(WHAT).c $(INCDIR)/imtools.h
	$(CC) -c $(CFLAGS) $(SRCDIR)/$(WHAT).c

$(WHAT):	$(IMTOOLSOBJ) $(WHAT).o
	@if [ $(MODE) = "static" ] ; then \
		case "$(STATIC_LIBS)" in \
		jpeg_sdsc_tiff_m)		echo "$(LD) $(WHAT).o $(IMTOOLSOBJ) $(LIBIM) $(JSTMLIBS) $(LF) -o $(WHAT)"; \
					$(LD) $(WHAT).o $(IMTOOLSOBJ) $(LIBIM) $(JSTMLIBS) $(LF) -o $(WHAT);; \
		m)			echo "$(LD) $(WHAT).o $(IMTOOLSOBJ) $(LIBIM) -lm $(LIBSDSC) -o $(WHAT)"; \
					$(LD) $(WHAT).o $(IMTOOLSOBJ) $(LIBIM) -lm $(LIBSDSC) -o $(WHAT);; \
		none)			echo "$(LD) $(WHAT).o $(IMTOOLSOBJ) $(LIBIM) $(LIBSDSC) -o $(WHAT)"; \
					$(LD) $(WHAT).o $(IMTOOLSOBJ) $(LIBIM) $(LIBSDSC) -o $(WHAT);; \
		*)			echo "Unsupported library combination.  Please add it to master.mk";;\
		esac \
	else	\
		case "$(DYNAMIC_LIBS)" in \
		jpeg_sdsc_tiff_m)	echo "$(LD) $(SOFLAGS) $(WHAT).o $(IMTOOLSOBJ) $(JSTMLIBS) -o $(WHAT)"; \
					$(LD) $(SOFLAGS) $(WHAT).o $(IMTOOLSOBJ) $(JSTMLIBS) -o $(WHAT);; \
		m)			echo "$(LD) $(WHAT).o $(IMTOOLSOBJ) $(SOFLAGS) -lm -o $(WHAT)"; \
					$(LD) $(WHAT).o $(IMTOOLSOBJ) $(SOFLAGS) -lm -o $(WHAT);; \
		none)			echo "$(LD) $(SOFLAGS) $(WHAT).o $(IMTOOLSOBJ) -o $(WHAT)"; \
					$(LD) $(SOFLAGS) $(WHAT).o $(IMTOOLSOBJ) -o $(WHAT);; \
		*)			echo "Unsupported library combination.  Please add it to master.mk";;\
		esac \
	fi
#	strip $(WHAT)


# imprint.o:	$(SRCDIR)/imprint.c $(INCDIR)/imtools.h
#	$(CC) -g -c $(CFLAGS) $(SRCDIR)/imprint.c $(LIBP)
#
# imprint:	$(LIBIM) $(IMTOOLSOBJ) imprint.o
#	if [ $(LDTYPE) = "static" ] ; then \
#		$(LD) $(LDFLAGS) imprint.o $(IMTOOLSOBJ) $(LIBS) -o imprint; \
#	else
#		$(LD) $(LDFLAGS) imprint.o $(IMTOOLSOBJ) $(LIBS) -o imprint; \
#	fi
#	strip imprint


clean:
	rm -f *.o imadjust imcat imcltroll imcomp imconv imcopy imdissolve imfile imfill imflip imformats imgray imhist immono impaste imroll imrotate imscale imshear imsplit imstoryboard imkey
