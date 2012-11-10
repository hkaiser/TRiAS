# Genrieren der Versionsinfo's für OBJMAN.DLL

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 041108
VERSION = 2
RELEASE = 05
BUILD = 045

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = objman
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
	@del versio32.h

formake:	$(DEF) $(STUB).exe $(NAME).rcv versio32.h 

$(STUB).asm:	$(STUB).tpl objman16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm
	@echo $@

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl objman16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E $(NAME)v.tpl tmp
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	$(REPLACE) $(COMPANYNAME) tmp1 $(NAME).rcv
	@del tmp > nul
	@del tmp1 > nul
	@echo $@

$(DEF):		$(NAME).tpl objman16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)
	@echo $@

versio32.h:	versio32.tpl objman16.mak
	$(REPLACE) $(VERSION) $(RELEASE) versio32.tpl versio32.h
	@echo $@

