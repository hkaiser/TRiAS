# Generieren der Versionsinfo's fr ATTRIBUD.DLL
 

# Generierungsdatum (yymmdd) und Version
DATE=970827
VERSION = 3
RELEASE = 00
BUILD = 011

COPYRIGHT = KK$(DATE)

PNAME = "Version f\xfcr den internen Gebrauch"
PADDRESS = "uve GmbH Fernerkundungszentrum Potsdam"

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = attr32
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
	@del $(STUB).asm
	@del $(NAME).rcv
	@del $(DEF)
	@del about.src
	@del versio32.h

formake:	$(DEF) $(STUB).exe $(NAME).rcv about.src versio32.h

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	attr32v.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B attr32v.tpl tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

about.src:	about.dlg
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B about.dlg tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv about.src
	@del tmp.rcv > nul

versio32.h:		versio32.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) versio32.tpl versio32.h

