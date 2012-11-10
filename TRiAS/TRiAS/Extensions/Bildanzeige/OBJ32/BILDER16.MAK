# Generieren der Versionsinfo's für BILDER32.DLL

!include "$(TRIASINCLUDE)/triasver.mak"

# Generierungsdatum (yymmdd) und Version
DATE=010225
VERSION = 3
RELEASE = 10
BUILD = 020

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = bilder32
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
# CopyrightEintraege Generieren 
new:
	@del $(NAME).rcv
	@del $(DEF)
	@del versio32.h

formake:	$(DEF) $(NAME).rcv versio32.h

# Personalisierungsinformation
$(NAME).rcv:	bilderv.rc bilder16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E bilderv.rc tmp
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	$(REPLACE) $(COMPANYNAME) tmp1 $(NAME).rcv
	@del tmp > nul
	@del tmp1 > nul

$(DEF):		$(NAME).tpl bilder16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

versio32.h:	version.tpl bilder16.mak
	$(REPLACE) $(VERSION) $(RELEASE) version.tpl versio32.h
