# Makefile
# Copyright (c) 1997, Regents of the University of California
# $Id: Makefile,v 1.2 1999/09/27 01:15:55 marcel Exp $

include ../Makefile.inc

DEST = $(LIBGISTHOME)/lib

LIBRARY = $(LIBDIR)/libnptree.a
SHLIB = $(LIBDIR)/libnptree.so

LIBNPTREEDIR = .
include ./Makefile.src

OBJS = $(SRCS:.cc=.o)

%.o: %.cc
	$(CC) -c $(CFLAGS) $(INCS) $*.cc

all: $(LIBRARY) #$(SHLIB)

$(LIBRARY): $(OBJS)
	rm -f $(LIBRARY)
	$(AR) rs $(LIBRARY) $(OBJS)

$(SHLIB): $(OBJS)
	rm -f $(SHLIB)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) -lgist

clean:
	rm -f $(OBJS) $(LIBRARY) $(SHLIB) *~ \#*\# .pure* *pure*.o core

cleanmake:
	sed -n -e '1,/^# DO NOT DELETE THIS LINE/p' < Makefile > Makefile.tmp;\
	mv Makefile Makefile.bak;\
	mv Makefile.tmp Makefile

depend:
	sed -n -e '1,/^# DO NOT DELETE THIS LINE/p' < Makefile > Makefile.tmp;\
	$(CC) -MM $(DEFINES) $(INCS) $(SRCS) >> Makefile.tmp;\
	mv Makefile Makefile.bak;\
	mv Makefile.tmp Makefile

.depend:
	$(MAKE) depend
	touch .depend

install: $(PROGRAM)
	echo Installing $(PROGRAM) in $(LIBDIR)
	install -s $(PROGRAM) $(DEST)

# DO NOT DELETE THIS LINE -- make depend depends on it.
