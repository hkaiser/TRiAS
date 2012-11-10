# Makefile
# Copyright (c) 1998, Regents of the University of California
# $Id: Makefile,v 1.14 2000/03/15 00:23:22 mashah Exp $

include ../Makefile.inc

# set this to 0 if you don't want to see debugging output from Libgist.cc
DEBUG = 0

# -lstdc++ causes inclusion of undef'd symbol (__eh_pc) on Sparc Solaris
LIBDIRS = -L$(LIBGISTHOME)/lib
#LIBDIRS = -L$(GPPLIBS) -L$(LIBGISTHOME)/lib
LIBS = -lbtree -lrtree -lnptree -lgist -lm

ifneq (${DEBUG},0)
DEFINES += -DDEBUG${DEBUG}
endif

AMDB = true

JSRCS = ResultProcessor.java \
	ExtensionInfo.java \
	Libgist.java \
	LibgistException.java \
	LibgistCommand.java \
	DisplayPredInfo.java

# generated headers for native functions
GENHDRS = Libgist.h

CSRCS = Libgist.cc

CLASSES = $(JSRCS:.java=.class)

OBJS = $(CSRCS:.cc=.o)

SHLIB = ../../lib/libamdb.so

all: $(CLASSES) $(SHLIB)

$(SHLIB): $(GENHDRS) $(OBJS) $(LIBGISTOBJS)
	$(LINKER) $(LDFLAGS) -o $(SHLIB) $(OBJS) $(LIBS)

clean:
	$(RM) $(OBJS) $(GENHDRS) *.class $(SHLIB) core
    
cleanmake:
	sed -n -e '1,/^# DO NOT DELETE THIS LINE/p' < Makefile > Makefile.tmp;\
	mv Makefile Makefile.bak;\
	mv Makefile.tmp Makefile

depend:
	sed -n -e '1,/^# DO NOT DELETE THIS LINE/p' < Makefile > Makefile.tmp;\
	$(CC) -MM $(DEFINES) $(INCS) $(SRCS) $(CSRCS) >> Makefile.tmp;\
	mv Makefile Makefile.bak;\
	mv Makefile.tmp Makefile

# DO NOT DELETE THIS LINE -- make depend depends on it.
