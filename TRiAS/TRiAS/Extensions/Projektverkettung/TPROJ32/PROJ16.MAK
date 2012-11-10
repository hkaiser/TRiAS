# Generieren der Versionsinfo's fr PROJECTD.DLL
 

# Generierungsdatum (yymmdd) und Version
DATE=02111á
VERSION = 5
RELEASE = 00
BUILD = 011

COPYRIGHT = KK$(DATE)

PNAME = "Version f\xfcr den internen Gebrauch"
PADDRESS = "GEOPunkt GmbH"

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = tproj32
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
	@del $(NAME).rcv
	@del $(DEF)
	@del versio32.h

formake:	$(DEF) $(NAME).rcv versio32.h

# Personalisierungsinformation
$(NAME).rcv:	tproj32v.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B tproj32v.tpl tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

versio32.h:		versio32.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) versio32.tpl versio32.h

