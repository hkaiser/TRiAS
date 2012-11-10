# Genrieren der Versionsinfo's für OLEAUTO.EXT

!include <triasver207.mak>

# Generierungsdatum (yymmdd) und Version
DATE=981221
VERSION = 2
RELEASE = 20
BUILD = 262

RC_VERSION = 2
RC_RELEASE = 10

COPYRIGHT = HK_vb$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = oleauto
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK16 = link16.exe

# Alles neubilden
all:	formake 

$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK16) /NOLOGO /KNOWEAS $(STUB);

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(STUB).asm
	@del $(NAME).rcv
	@del $(DEF)
	@del versio32.h
	@del olebsext.rc

formake:	$(DEF) $(STUB).exe $(NAME).rcv versio32.h olebsext.rc

$(STUB).asm:	$(STUB).tpl oleaut16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl oleaut16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D $(NAME)v.tpl tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl oleaut16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

versio32.h:	versio32.tpl oleaut16.mak
	$(REPLACE) $(VERSION) $(RELEASE) versio32.tpl versio32.h

olebsext.rc:	olbsextp.tpl oleaut16.mak
	$(REPLACE) $(RC_VERSION) $(RC_RELEASE) olbsextp.tpl olebsext.rc
