#
#	$Header: /sdsc/dev/vis/image/imtools/v3.0/libim/src/RCS/master.mk,v 1.1 1995/06/30 06:46:31 bduggan Exp $
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
#	Makefile	-  make the image tools library
#
#  PROJECT
#	IMAGE		-  image library and tools
#
#  DESCRIPTION
#	The image library converts image file formats, queries their
#	characteristics, manipulates them, and so on.
#
#  HISTORY
#	$Log: master.mk,v $
# Revision 1.1  1995/06/30  06:46:31  bduggan
# Initial revision
#


#
#  Incomming Variables:
#  	Directory Structure:
#		BINDIR		-  where are binaries, relative to Makefile
#		LIBDIR		-  where are libraries, relative to Makefile
#		SRCDIR		-  where is source, relative to object dir
#		INCDIR		-  where are includes, relative to object dir
#		INCTIFF		-  where are the includes for tiff
#		INCJPEG		-  where are the includes for jpeg
#		SODIR		-  where are shared object files (absolute path)
#	Library Name:
#		LIB		-  name of library
#	Architecture:
#		ARCH		-  program to run to get architecture name
#	Flags:
#		CF		-  compiler flags
#		LF		-  linker flags
#		CC		-  compiler to use
#

SHELL =		/bin/sh

LIBSDSC =	../../libsdsc/$(ARCH)/libsdsc.a
INCSDSC =	-I../../libsdsc/include

INCIM =		-I../../libim/include

TIFFDIR =	../../libtiff
INCTIFF =       -I$(TIFFDIR)
LIBTIFF =	$(TIFFDIR)/$(ARCH)/libtiff.a

JPEGDIR =	../../libjpeg
INCJPEG = 	-I$(JPEGDIR)
LIBJPEG =	$(JPEGDIR)/$(ARCH)/libjpeg.a

INCLUDES =	-I$(INCDIR) $(INCSDSC) $(INCIM) $(INCTIFF) $(INCJPEG)
# DEFINES =	(passed in from main makefile)
CFLAGS =	$(CF) $(INCLUDES) $(DEFINES)  

COREOBJS =	im.o \
		imclt.o \
		imerrno.o \
		imfile.o \
		imfmt.o \
		imgiflzw.o \
		imlzw.o \
		imschemes.o \
		immiscschemes.o \
		imvfb.o \
		imvfbadjust.o \
		imvfbcomp.o \
		imvfbflip.o \
		imvfbhist.o\
		imvfblight.o \
		imvfbresize.o \
		imvfbrotate.o \
		imvfbto.o \
		imvfbchan.o \
		macpack.o 

#		imcgm.o 
FORMATOBJS =	imbmp.o \
		imcur.o	\
		imeps.o \
		imgif.o \
		imhdfread.o	\
		imhdfwrite.o	\
		imico.o \
		imicon.o \
		imiff.o \
		imjpeg.o \
		immiff.o \
		immpnt.o \
		impbm.o \
		impcx.o \
		impic.o \
		impict.o \
		impix.o	\
		imps.o	\
		imras.o	\
		imrla.o \
		imrle.o \
		imrgb.o \
		imsoftimage.o \
		imsynu.o \
		imtga.o \
		imtiff.o \
		imviff.o \
		imx.o	\
		imxbm.o	\
		imxpm.o	\
		imxwd.o


LIBOBJS =	$(COREOBJS) $(FORMATOBJS)


# Core objects
#
im.o:		$(SRCDIR)/im.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/im.c

imclt.o:	$(SRCDIR)/imclt.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imclt.c

imerrno.o:	$(SRCDIR)/imerrno.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imerrno.c

imfile.o:	$(SRCDIR)/imfile.c $(INCDIR)/im.h $(INCDIR)/impref.h \
		$(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imfile.c

imfmt.o:	$(SRCDIR)/imfmt.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imfmt.c

imgiflzw.o:	$(SRCDIR)/imgiflzw.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imgiflzw.c

imlzw.o:	$(SRCDIR)/imlzw.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imlzw.c

imschemes.o:	$(SRCDIR)/imschemes.c $(INCDIR)/im.h $(INCDIR)/iminternal.h 
		$(CC) -c $(CFLAGS) $(SRCDIR)/imschemes.c

immiscschemes.o:	$(SRCDIR)/immiscschemes.c $(INCDIR)/im.h $(INCDIR)/iminternal.h 
		$(CC) -c $(CFLAGS) $(SRCDIR)/immiscschemes.c

imvfb.o:	$(SRCDIR)/imvfb.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imvfb.c

imvfbadjust.o:	$(SRCDIR)/imvfbadjust.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imvfbadjust.c

imvfbcomp.o:	$(SRCDIR)/imvfbcomp.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imvfbcomp.c

imvfbflip.o:	$(SRCDIR)/imvfbflip.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imvfbflip.c

imvfbhist.o:	$(SRCDIR)/imvfbhist.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imvfbhist.c

imvfblight.o:	$(SRCDIR)/imvfblight.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imvfblight.c

imvfbresize.o:	$(SRCDIR)/imvfbresize.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imvfbresize.c

imvfbrotate.o:	$(SRCDIR)/imvfbrotate.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imvfbrotate.c

imvfbto.o:	$(SRCDIR)/imvfbto.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imvfbto.c

imvfbchan.o:	$(SRCDIR)/imvfbchan.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imvfbchan.c

macpack.o:	$(SRCDIR)/macpack.c
		$(CC) -c $(CFLAGS) $(SRCDIR)/macpack.c



# Format objects
imbmp.o:	$(SRCDIR)/imbmp.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imbmp.c

#imcgm.o:	$(SRCDIR)/imcgm.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
#		$(CC) -c $(CFLAGS) $(SRCDIR)/imcgm.c

imcur.o:	$(SRCDIR)/imcur.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imcur.c

imeps.o:	$(SRCDIR)/imeps.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imeps.c

imgif.o:	$(SRCDIR)/imgif.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imgif.c

imhdfread.o:	$(SRCDIR)/imhdfread.c $(INCDIR)/im.h $(INCDIR)/iminternal.h \
		$(INCDIR)/imhdfinternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imhdfread.c

imhdfwrite.o:	$(SRCDIR)/imhdfwrite.c $(INCDIR)/im.h $(INCDIR)/iminternal.h \
		$(INCDIR)/imhdfinternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imhdfwrite.c

imico.o:	$(SRCDIR)/imico.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imico.c

imicon.o:	$(SRCDIR)/imicon.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imicon.c

imiff.o:	$(SRCDIR)/imiff.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imiff.c

imjpeg.o:	$(SRCDIR)/imjpeg.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imjpeg.c

immiff.o:	$(SRCDIR)/immiff.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/immiff.c

immpnt.o:	$(SRCDIR)/immpnt.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/immpnt.c

impbm.o:	$(SRCDIR)/impbm.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/impbm.c

impcx.o:	$(SRCDIR)/impcx.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/impcx.c

impic.o:	$(SRCDIR)/impic.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/impic.c

impict.o:	$(SRCDIR)/impict.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/impict.c

impix.o:	$(SRCDIR)/impix.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/impix.c

imps.o:		$(SRCDIR)/imps.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imps.c

imras.o:	$(SRCDIR)/imras.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imras.c

imrla.o:	$(SRCDIR)/imrla.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imrla.c

imrgb.o:	$(SRCDIR)/imrgb.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imrgb.c

imrle.o:	$(SRCDIR)/imrle.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imrle.c

imsoftimage.o:	$(SRCDIR)/imsoftimage.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imsoftimage.c

imsynu.o:	$(SRCDIR)/imsynu.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imsynu.c

imtga.o:	$(SRCDIR)/imtga.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imtga.c

imtiff.o:	$(SRCDIR)/imtiff.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imtiff.c

imviff.o:	$(SRCDIR)/imviff.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imviff.c

imx.o:		$(SRCDIR)/imx.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imx.c

imxbm.o:	$(SRCDIR)/imxbm.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imxbm.c

imxpm.o:	$(SRCDIR)/imxpm.c $(INCDIR)/im.h $(INCDIR)/iminternal.h $(INCDIR)/imxpm.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imxpm.c

imxwd.o:	$(SRCDIR)/imxwd.c $(INCDIR)/im.h $(INCDIR)/iminternal.h
		$(CC) -c $(CFLAGS) $(SRCDIR)/imxwd.c


lib:		$(LIBOBJS)
		-rm -f $(LIB)
		ar qv $(LIB) $(LIBOBJS)
		-if [ -f /usr/bin/ranlib -o -f /bin/ranlib -o -f /usr/local/bin/ranlib ] ; then ranlib $(LIB) ; fi

#
# LIBFLAGS
#	To add a new combination, just duplicate a pair of lines below
#	and include your own combination of libraries on the lines.
#
#	The prefix 'all' in the string of libraries means that the
#	particular compiler requires the -all option in order to
#	include all of the .o files in a .a in the output file.

so:		$(LIBOBJS)
		-rm -f $(SO)
		@case $(SOOBJS) in \
		jpeg_sdsc_tiff_m)	echo "$(LD) $(LDFLAGS) -o $(SO) $(LIBOBJS) $(LIBTIFF) $(LIBJPEG) $(LIBSDSC) -lm";\
					$(LD) $(LDFLAGS) -o $(SO) $(LIBOBJS) $(LIBTIFF) $(LIBJPEG) $(LIBSDSC) -lm ;;\
		all_jpeg_sdsc_tiff)	echo "$(LD) $(LDFLAGS) -o $(SO) $(LIBOBJS) -all $(LIBTIFF) -all $(LIBJPEG) -all $(LIBSDSC) ";\
					$(LD) $(LDFLAGS) -o $(SO) $(LIBOBJS) -all $(LIBTIFF) -all $(LIBJPEG) -all $(LIBSDSC) ;;\
		all_jpeg_sdsc_tiff_m)	echo "$(LD) $(LDFLAGS) -o $(SO) $(LIBOBJS) -all $(LIBTIFF) -all $(LIBJPEG) -all $(LIBSDSC) -all -lm";\
					$(LD) $(LDFLAGS) -o $(SO) $(LIBOBJS) -all $(LIBTIFF) -all $(LIBJPEG) -all $(LIBSDSC) ;;\
		none)			echo "$(LD) $(LDFLAGS) -o $(SO) $(LIBOBJS)";\
					$(LD) $(LDFLAGS) -o $(SO) $(LIBOBJS);;\
		*)			echo "Unsupported library combination.  Please add it to master.mk";;\
		esac
		@if [ $(MAKESA) = "yes" ]; then 	\
			rm -f $(SA);	\
			ar qv $(SA) $(VARFILES);\
			ranlib $(SA);	\
		fi

clean:
		rm -f *.o $(LIB)
