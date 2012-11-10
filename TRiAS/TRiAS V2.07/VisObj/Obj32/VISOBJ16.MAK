# Generieren der Versionsinfo's für VISOBJ32.DLL

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE=981208
VERSION = 3
RELEASE = 30
BUILD = 051

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = visobj32
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
	@del defabout.src
	@del versio32.h

formake:	$(DEF) $(STUB).exe $(NAME).rcv defabout.src versio32.h

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	visobj3v.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E visobj3v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp.rcv tmp1
	$(REPLACE) $(COMPANYNAME) tmp1 $(NAME).rcv
	@del tmp.rcv > nul
	@del tmp1 > nul

$(DEF):		$(NAME).tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

defabout.src:	defabout.dlg
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B defabout.dlg tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv defabout.src
	@del tmp.rcv > nul

versio32.h:	versio32.tpl
	$(REPLACE) $(VERSION) $(RELEASE) versio32.tpl versio32.h
