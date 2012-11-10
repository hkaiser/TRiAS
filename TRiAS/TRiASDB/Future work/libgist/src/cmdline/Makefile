# Makefile
# Copyright (c) 1998, Regents of the University of California
# $Id: Makefile,v 1.24 2000/03/15 00:23:48 mashah Exp $

include ../Makefile.inc

LIBS = $(LIBGISTHOME)/lib/libgist.a \
    $(LIBGISTHOME)/lib/libbtree.a \
    $(LIBGISTHOME)/lib/librtree.a \
    $(LIBGISTHOME)/lib/libnptree.a

# -lstdc++ needed for the sww installation (Sparc Solaris)
CMDLINELIBS = -lbtree -lrtree -lnptree -lgist -lm -lstdc++

DEST = .

PROG = $(DEST)/gistcmdline

SRCS = cmdline_gram.y cmdline_scan.l cmdline.cc
OBJS = cmdline_gram.tab.o cmdline_scan.o cmdline.o
TMPS = cmdline_gram.tab.cc cmdline_scan.cc cmdline_gram_tab.h \
	cmdline_gram.output cmdline_help.h cmdline_ts.h

all: $(PROG)

$(PROG): $(OBJS) $(LIBS)
	$(LINKER) -L$(LIBDIR) $(OBJS) -o $(PROG) $(CMDLINELIBS)
	$(CP) $(PROG) $(LIBGISTHOME)/bin

pure: $(OBJS) $(LIBS)
	purify -chain-length=12 -cache-dir=/tmp \
	$(LINKER) -L$(LIBDIR) $(OBJS) -o $(PROG) $(CMDLINELIBS)

cmdline_gram.tab.cc: cmdline_gram.y
	$(YACC) $(YACCFLAGS) $^
	mv cmdline_gram.tab.c $@
	mv cmdline_gram.tab.h cmdline_gram_tab.h

cmdline_scan.cc: cmdline_scan.l
	$(LEX) $(LEXFLAGS) $^ > $@

cmdline_help.h: cmdline_gram.y
	echo 'static char* usage = "\' > $@; \
	egrep '// usage: ' $< | \
	sed -e 's/.*usage:[ ]*/\\t/' -e 's/"/\\"/g' -e 's/$$/\\n\\/' | \
	sort >> $@; \
	echo '";' >> $@

cmdline_ts.h:
	echo 'static char* timestamp = "\' > $@; \
	echo `date` '";' >> $@

cmdline.o: cmdline_help.h cmdline_ts.h

clean:
	rm -f $(OBJS) $(PROG) core *~ \#*\# .pure* *pure*.o TAGS

cleanmake:
	sed -n -e '1,/^# DO NOT DELETE THIS LINE/p' < Makefile > Makefile.tmp;\
	mv Makefile Makefile.bak;\
	mv Makefile.tmp Makefile

depend: $(TMPS)
	sed -n -e '1,/^# DO NOT DELETE THIS LINE/p' < Makefile > Makefile.tmp;\
	$(CC) -MM $(DEFINES) $(INCS) $(filter %.cc,$(SRCS) $(TMPS)) >> Makefile.tmp;\
	mv Makefile Makefile.bak;\
	mv Makefile.tmp Makefile

# DO NOT DELETE THIS LINE -- make depend depends on it.
