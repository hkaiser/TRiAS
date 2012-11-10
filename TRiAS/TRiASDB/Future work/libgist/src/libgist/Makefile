# Makefile
# Copyright (c) 1997, 1998, Regents of the University of California
# $Id: Makefile,v 1.51 1999/09/27 01:15:49 marcel Exp $

include ../Makefile.inc

DEST = $(LIBGISTHOME)/lib

LIBRARY = $(DEST)/libgist.a
SHLIB = $(DEST)/libgist.so

LIBGISTDIR = .
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
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(LIBRARY) *~ \#*\# .pure* *pure*.o core

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
	echo Installing $(PROGRAM) in $(DEST)
	install -s $(PROGRAM) $(DEST)

# DO NOT DELETE THIS LINE -- make depend depends on it.
