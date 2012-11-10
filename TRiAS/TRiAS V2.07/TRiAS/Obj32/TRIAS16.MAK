# Makefile fuer TRIAS (C++ 2.0d2)
# File: MAKEFILE

# TRIAS: %W%	%E%

!include <triasver207.mak>

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

# SU-Variante
#PNAME = "Âåðñèÿ äëÿ Öåíòðà Àýðîêîñìè÷åñêèõ"
#PADDRESS = "Èññëåäîâàíèé Çåìëè"

# Schlitter/Neef
#PNAME = "Version für die BVV Chemie GmbH"
#PADDRESS = ""

#PNAME = "Version für die Entwicklungsträgergesellschaft"
#PADDRESS = "Rummelsburger Bucht"

#PNAME = "Version für das Ministerium für Umwelt,"
#PADDRESS = "Naturschutz und Raumordnung Brandenburg"

#PADDRESS = "internen Gebrauch (uve Potsdam GmbH)"
#PADDRESS = "internen Gebrauch (uve GmbH Herne)"

#PNAME = "Herrn Simon"
#PADDRESS = "Treuhand Liegenschaftsgesellschaft"

#PNAME = "Herrn Zeidler"
#PADDRESS = "BQP Bitterfeld"

#PNAME = "Herrn Dr. Neef"
#PADDRESS = "Chemie AG Bitterfeld"
#PADDRESS = "GBG Berlin"

#PNAME = "Herr Simon"
#PADDRESS = "Treuhand-Liegenschaftsgesellschaft"

#PNAME = "Herrn Bock"
#PADDRESS = "Senat Berlin, Abteilung III"

#PNAME = "Herrn Schiller"
#PADDRESS = "Umweltverantwortlicher des RAW Schöneweide"

#PNAME = "Herrn Langenickel"
#PADDRESS = "EWU Engineering GmbH Berlin"

#PNAME = "Dr. Eckstein/Dr.Walkow"
#PNAME = "Version für das"
#PADDRESS = "Landratsamt Bitterfeld"

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

DESTDIR = c:\trias.mvc\trias

# Generieren der WINDOW's - Anwendung
all:	formake 

# CopyrightEintraege Generieren -----------------------------------------------
infodlg.src:	infodlg.dlg 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) infodlg.dlg infodlg.src

signon1.src:	signon1.dlg 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B signon1.dlg tmp.src
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.src signon1.src
	@del tmp.src > nul

$(STUB).c:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).c

$(STUB).exe:	$(STUB).c exec.obj spawn.obj
	$(CC) -c $(STUB).c 
	@echo $(STUB).obj exec.obj spawn.obj > $(STUB).lnk
	@echo $(STUB).exe >> $(STUB).lnk
	@echo nul >> $(STUB).lnk
	@echo c:\msvc\lib\ ; >> $(STUB).lnk
	$(LINK) /nol @$(STUB).lnk

# Personalisierungsinformation ------------------------------------------------
$(APP).rcv:	$(APP)v.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(APP)v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(APP).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

pkeycode.h:	$(MAKEKEY).exe 
	$(MAKEKEY) $(PNAME) $(PADDRESS) > pkeycode.h

$(MAKEKEY).exe:	$(MAKEKEY).c mycrypt.c
	cl $(MAKEKEY).c mycrypt.c

copystr.rc:	copystrnewt.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C copystrnewt.rc tmp.rc
	$(REPLACE) $(PNAME) $(PADDRESS) $(BUILDSTRING) tmp.rc copystr.rc
	@del tmp.rc > nul

TRiASVersion.h:	TRiASVersion.tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) TRiASVersion.tpl TRiASVersion.h

# bei Copyright-Aenderungen 'make new' abarbeiten ! ---------------------------
new:	remove

remove:
	@del infodlg.src
	@del $(APP).rcv
	@del pkeycode.h
	@del signon1.src
	@del copystr.rc
	@del $(DEF)
	@del TRiASVersion.h

# Abhängigkeiten für Umgeleitete Dateien (für make)
formake:	infodlg.src $(APP).rcv pkeycode.h signon1.src copystr.rc $(DEF) TRiASVersion.h

