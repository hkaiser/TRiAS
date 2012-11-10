# Generieren der Versionsinfo's für KOMPAKT.EXT

TRIAS2INCLUDE = c:\triasdev.mvc\include

!include $(TRIAS2INCLUDE)\triasver.Mak

# Generierungsdatum (yymmdd) und Version
DATE=001207
VERSION = 2
RELEASE = 13
BUILD = 031

COPYRIGHT = KK$(DATE)

PNAME = $(TRIAS_PNAME) 
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = kompakt
NNAME = kompias

# Version 3.0 vorbehalten
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neubilden
all:	formake 

$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK) /NOLOGO /KNOWEAS $(STUB)

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(STUB).asm
	@del $(NNAME).rcv
	@del $(DEF)
	@del about.src
	@del versio32.h

formake:	$(DEF) $(STUB).exe $(NNAME).rcv about.src versio32.h

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NNAME).rcv:	$(NAME)v.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(NAME)v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) tmp.rcv $(NNAME).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

about.src:	about.dlg
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B about.dlg tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv about.src
	@del tmp.rcv > nul

versio32.h:	versio32.tpl 
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) versio32.tpl versio32.h

