# analysis/Makefile
# Copyright (c) 1998, Regents of the University of California
# $Id: Makefile,v 1.1 1999/06/21 00:33:18 marcel Exp $

include ../Makefile.inc

SRCS = Workload.java  \
	QueryStats.java \
	WkldStatsDlg.java \
	AnalysisInfo.java \
	SplitStatsDlg.java \
	SplitStats.java \
	PenaltyStatsDlg.java \
	PenaltyStats.java

HMETISSRCS = hmetis_cmdline.cc
HMETISOBJS = $(HMETISSRCS:.cc=.o)

CLASSES = $(SRCS:.java=.class)

#all: $(CLASSES) myhmetis
all: $(CLASSES)

myhmetis: $(HMETISOBJS)
	$(CC) -o $@ -L. $(HMETISOBJS) -lhmetis -lm	
	cp $@ $(HOME)/bin/$@

clean:
	$(RM) *.class

cleanmake:

depend:

# DO NOT DELETE THIS LINE -- make depend depends on it.
