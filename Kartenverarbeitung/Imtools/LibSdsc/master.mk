#
#       $Header:$
#       Copyright (c) 1989-1992  San Diego Supercomputer Center (SDSC)
#               San Diego, California, USA
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
#       This low-level architecture-specific make file builds the SDSC
#       library for a specific machine architecture.
#
#  HISTORY
#       $Log:$


#
#  Incomming Variables:
#  	Directory Structure:
#		BINDIR		-  where are binaries, relative to Makefile
#		LIBDIR		-  where are libraries, relative to Makefile
#		SRCDIR		-  where is source, relative to object dir
#		INCDIR		-  where are includes, relative to object dir
#	Library Name:
#		LIB		-  name of library
#	Architecture:
#		ARCH		-  program to run to get architecture name
#	Flags:
#		CF		-  compiler flags
#		LF		-  linker flags
#		LINTF		-  lint flags
#		CC		-  compiler to use
#		LINT		-  lint to use
#

SHELL =		/bin/sh

INCLUDES =	-I$(INCDIR)
DEFINES =	
CFLAGS =	$(CF) $(INCLUDES) $(DEFINES)
LINTFLAGS =	$(LINTF) $(INCLUDES) $(DEFINES)
LIBS =		$(LIB) $(LF) -lm

LIBOBJS =	bin.o arg.o tag.o 
BINOBJS =	binverify binprint mkhost argtest argtest2 xform tagverify



#
#  Make the library
bin.o:	$(SRCDIR)/bin.c $(INCDIR)/bin.h $(INCDIR)/sdsc.h $(INCDIR)/sdscconfig.h
	$(CC) -c $(CFLAGS) $(SRCDIR)/bin.c

arg.o:	$(SRCDIR)/arg.c $(INCDIR)/arg.h $(INCDIR)/sdsc.h $(INCDIR)/sdscconfig.h
	$(CC) -c $(CFLAGS) $(SRCDIR)/arg.c

tag.o:	$(SRCDIR)/tag.c $(INCDIR)/tag.h $(INCDIR)/bin.h $(INCDIR)/sdsc.h \
	$(INCDIR)/sdscconfig.h
	$(CC) -c $(CFLAGS) $(SRCDIR)/tag.c

lib:	$(LIBOBJS)
	-rm -f $(LIB)
	ar qv $(LIB) $(LIBOBJS)
	-if [ -f /usr/bin/ranlib -o -f /bin/ranlib -o -f /usr/local/bin/ranlib ] ; then ranlib $(LIB) ; fi

clean:
	rm -f *.o $(LIB) $(BINOBJS)


#
#  Make a lint pass on the library
bin.lint:	$(SRCDIR)/bin.c $(INCDIR)/bin.h $(INCDIR)/sdsc.h \
	$(INCDIR)/sdscconfig.h
	$(LINT) -c $(LINTFLAGS) $(SRCDIR)/bin.c

arg.lint:	$(SRCDIR)/arg.c $(INCDIR)/arg.h $(INCDIR)/sdsc.h \
	$(INCDIR)/sdscconfig.h
	$(LINT) $(LINTFLAGS) $(SRCDIR)/arg.c

tag.lint:	$(SRCDIR)/tag.c $(INCDIR)/tag.h $(INCDIR)/bin.h \
	$(INCDIR)/sdsc.h \
	$(INCDIR)/sdscconfig.h
	$(LINT) $(LINTFLAGS) $(SRCDIR)/tag.c

lint:	bin.lint arg.lint tag.lint 




#
#  Make the binaries (the verification suite)
allbin:	$(BINOBJS)

binverify:	$(SRCDIR)/binverify.c
	$(CC) $(CFLAGS) $(SRCDIR)/binverify.c $(LIBDIR)/libsdsc.a -o binverify

binprint:	$(SRCDIR)/binprint.c
	$(CC) $(CFLAGS) $(SRCDIR)/binprint.c $(LIBDIR)/libsdsc.a -o binprint

mkhost:		$(SRCDIR)/mkhost.c
	$(CC) $(CFLAGS) $(SRCDIR)/mkhost.c $(LIBDIR)/libsdsc.a -o mkhost

argtest:	$(SRCDIR)/argtest.c
	$(CC) $(CFLAGS) $(SRCDIR)/argtest.c $(LIBDIR)/libsdsc.a -o argtest

argtest2:	$(SRCDIR)/argtest2.c
	$(CC) $(CFLAGS) $(SRCDIR)/argtest2.c $(LIBDIR)/libsdsc.a -o argtest2

xform:		$(SRCDIR)/xform.c
	$(CC) $(CFLAGS) $(SRCDIR)/xform.c $(LIBDIR)/libsdsc.a -o xform

tagverify:	$(SRCDIR)/tagverify.c
	$(CC) $(CFLAGS) $(SRCDIR)/tagverify.c $(LIBDIR)/libsdsc.a -o tagverify

t:	$(SRCDIR)/t.c
	$(CC) $(CFLAGS) $(SRCDIR)/t.c -o t
