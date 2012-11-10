# Generieren der Versionsinfo's für BERLIN.EXT

#!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE=990121
VERSION = 3
RELEASE = 00
BUILD = 002

COPYRIGHT = KK$(DATE)


PNAME = "Version f\xfcr den internen Gebrauch"
PADDRESS = "uve GmbH Fernerkundungszentrum Potsdam"

STUB = rights

RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = Berlin
DEF = $(NAME).def


ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe


# Alles neubilden
all:	formake 

$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK) /NOLOGO /KNOWEAS $(STUB);

# -----------------------------------------------------------------------------
# CopyrightEinträge Generieren 
new:
	@del $(STUB).asm
	@del $(NAME).rcv
	@del $(DEF)
	@del version.h

formake:	$(DEF) $(STUB).exe $(NAME).rcv version.h


$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(NAME)v.tpl tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

version.h:	version.tpl
	$(REPLACE) $(VERSION) $(RELEASE) version.tpl version.h
