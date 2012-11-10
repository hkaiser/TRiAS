# Genrieren der Versionsinfo's für BSCRIPT.EXT

!include <$(TRIASINCLUDE)/triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 041116
VERSION = 3
RELEASE = 07
BUILD = 133

VERSION_ALT = 4
RELEASE_ALT = 00

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = bscript
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neubilden
all:    formake 

$(STUB).exe:    $(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK) /NOLOGO /KNOWEAS $(STUB);

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(NAME).rcv
	@del $(DEF)
	@del versio32.h
	@del bscrext.rc

formake:        $(DEF) $(NAME).rcv versio32.h bscrext.rc

# Personalisierungsinformation
$(NAME).rcv:    $(NAME)v.tpl  bscrip16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E $(NAME)v.tpl tmp
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	$(REPLACE) $(COMPANYNAME) tmp1 $(NAME).rcv
	@del tmp > nul
	@del tmp1 > nul

$(DEF):         $(NAME).tpl bscrip16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

versio32.h:     versio32.tpl bscrip16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(TRIAS_VERSION) $(TRIAS_RELEASE) $(TRIAS_BUILD) versio32.tpl versio32.h

bscrext.rc:     bscrextp.tpl bscrip16.mak
	$(REPLACE) $(VERSION_ALT) $(RELEASE_ALT) bscrextp.tpl bscrext.rc
