# Makefile.inc
# Copyright (c) 1997, Regents of the University of California
# $Id: Makefile.inc,v 1.33 1999/12/14 06:06:37 marcel Exp $

SYSTEM = $(shell uname -s)
ARCH = $(shell uname -m)

include $(LIBGISTHOME)/src/Makefile.paths.$(SYSTEM).$(ARCH)

#
# we build for amdb
#
AMDB = true

#
# if you're using this makefile, you must be using unix.
#
DEFINES = -DUNIX
ifeq (${AMDB},true)
DEFINES+= -DAMDB
endif

EXTRA_CFLAGS =
CFLAGS = -ggdb3 -Wno-unused $(DEFINES)
LIBDIR = $(LIBGISTHOME)/lib

#
# STL's includes must precede the JDK includes, there are conflicting
# names defined (tree.h)
#
INCS = -I$(GPPINCL) -I$(LIBGISTHOME)/include 
ifeq (${AMDB},true)
ifeq (${HAVEJDK},true)
CFLAGS+= -fpic -D_REENTRANT
INCS+= $(JDKINCS)
else
INCS+= -I$(LIBGISTHOME)/include/jdk
endif
endif

CFLAGS += ${EXTRA_CFLAGS}

#
# we recommend bison and flex for this code.
# if you want to use yacc and lex, you'll need to muck with the
# Makefiles a bit.
#
LEX = flex
LEXFLAGS = -It
YACC = bison
YACCFLAGS = -dv

CP = cp

%.o: %.cc
	$(CC) -c $(CFLAGS) $(INCS) $*.cc

#
# Java stuff
# 

JC = javac
JAVA = java
JAVAH = javah
CPATH = ../gui:../analysis:../amdbgist:../treeview:$(CLASSPATH)
#CPATH = ../gui:../analysis:../amdbgist:../treeview:$(JFCINSTALL)/swingall.jar:$(JDKINSTALL)/lib/classes.zip:$(CLASSPATH)
JAVAFLAGS = -classpath $(CPATH) -mx64m -ms16m
JHFLAGS = -classpath $(CPATH) -jni
JFLAGS = -classpath $(CPATH) -deprecation

%.class: %.java
	$(JC) $(JFLAGS) $*.java

%.h: %.class
	$(JAVAH) $(JHFLAGS) $*
	touch $@
