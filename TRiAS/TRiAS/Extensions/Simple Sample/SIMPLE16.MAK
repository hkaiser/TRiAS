# Genrieren der Versionsinfo's fr SIMPLE.EXT

# Generierungsdatum (yymmdd) und Version
DATE=970304
VERSION = 2
RELEASE = 00
BUILD = 001

COPYRIGHT = HK$(DATE)

PNAME = "Version f\xfcr den internen Gebrauch"
PADDRESS = "uve GmbH Fernerkundungszentrum Potsdam"

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = simple
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
	@del version.h
#	@del defabout.src

formake:	$(DEF) $(STUB).exe $(NAME).rcv version.h

#defabout.src

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B $(NAME)v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv $(NAME).rcv
	@del tmp.rcv > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

defabout.src:	defabout.dlg
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B defabout.dlg tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv defabout.src
	@del tmp.rcv > nul

version.h:	version.tpl
	$(REPLACE) $(VERSION) $(RELEASE) version.tpl version.h
