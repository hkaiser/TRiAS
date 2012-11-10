# Makefile fuer TRIAS (C++ 2.0d2)
# File: MAKEFILE

# TRIAS: %W%	%E%

!include <triasver.mak>

# CopyrightEintrag
# bei Copyright-Aenderungen 'make new' abarbeiten !
BUILDSTRING = $(TRIAS_BUILDSTRING)
VERSION = $(TRIAS_VERSION)
RELEASE = $(TRIAS_RELEASE)
BUILD = $(TRIAS_BUILD)
COPYRIGHT = $(TRIAS_COPYRIGHT)

# allgemeine Version
PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

DEBUG=1

!IF $(DEBUG)==1
ASMF= /D?PLM=0 /D?WIN=1 /Zi 
!ELSE
ASMF= /D?PLM=0 /D?WIN=1
!ENDIF

LINK = link
LIB = lib
ASM = masm
CC = cl /nologo
CCXX = $(CC)
EMCCXX = $(CC)
RC = rc
REPLACE = ersetz
CVPACK = cvpack
IMPLIB = implib
YXX=yxx
FPP = fpp
AD = autodoc.exe
HC = hc31.exe

NAME = trias32
STUB = startup

APP = $(NAME)
MAP = $(NAME).map
DEF = $(NAME).def
SYM = $(NAME).sym
LIB = $(NAME).lib
EXE = $(NAME).exe
DEF = $(NAME).def

RIGHTS = $(STUB).exe
MAKEKEY = makekey

# Generieren der WINDOW's - Anwendung
all:	formake 

# CopyrightEintraege Generieren -----------------------------------------------
obj32\infodlg.src:	obj32\infodlg.dlg obj32\trias16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(COMPANYNAME) \
			obj32\infodlg.dlg obj32\infodlg.src

obj32\signon1.src:	obj32\signon1.dlg obj32\trias16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(COMPANYNAME) \
			obj32\signon1.dlg obj32\signon1.src

obj32\$(APP).rcv:	obj32\$(APP)v.tpl obj32\trias16.mak obj32\trias.lic
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(COMPANYNAME) \
			obj32\$(APP)v.tpl obj32\$(APP).rcv

obj32\$(DEF):		obj32\$(NAME).tpl obj32\trias16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			obj32\$(NAME).tpl obj32\$(DEF)

obj32\pkeycode.h:	obj32\trias16.mak
	.\obj32\$(MAKEKEY).exe $(PNAME) $(PADDRESS) > obj32\pkeycode.h

$(MAKEKEY).exe:	$(MAKEKEY).c mycrypt.c
	cl $(MAKEKEY).c mycrypt.c

obj32\copystr.rc:	obj32\copystrt.tpl obj32\trias16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(BUILDSTRING) \
		$(COMPANYNAME) \
		$(COMPANYNAME_SHORT) \
			obj32\copystrt.tpl obj32\copystr.rc

obj32\TRiASVersion.h:	obj32\TRiASVersion.tpl obj32\trias16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			obj32\TRiASVersion.tpl obj32\TRiASVersion.h

obj32\trias16.mak:	$(TRIASINCLUDE)\triasver.mak
	@touch obj32\trias16.mak

#obj32\trias.lic:	obj32\trias16.mak
#	Genlic -o obj32\trias.lic $(COPYRIGHT)

# bei Copyright-Aenderungen 'make new' abarbeiten ! ---------------------------
new:	remove

remove:
	@del obj32\$(APP).rcv
	@del obj32\pkeycode.h
	@del obj32\signon1.src
	@del obj32\copystr.rc
	@del obj32\$(DEF)
	@del obj32\TRiASVersion.h
#	@del obj32\trias.lic

# Abhängigkeiten für Umgeleitete Dateien (für make)
formake:	obj32\$(APP).rcv obj32\pkeycode.h obj32\signon1.src \
	obj32\copystr.rc obj32\$(DEF) obj32\TRiASVersion.h 
	
#obj32\trias.lic

