# Makefile für Koordinatentransformation
# Windows/DLL-Version
# MSVC V1.5 (Windows)

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 021219
VERSION = 4
RELEASE = 00
BUILD = 067
COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = default
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neu bilden
all:	formake

# Versionskontrolle -----------------------------------------------------------
$(STUB).exe:	$(STUB).asm 
	masm rights;
	$(LINK) rights;

new:
	@del $(DEF) > nul
	@del $(STUB).asm > nul
	@del $(NAME).rcv > nul

formake:	$(DEF) $(STUB).exe $(NAME).rcv 

$(DEF):		$(NAME).tpl default.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)
	@echo $(DEF)

$(STUB).asm:	$(STUB).tpl default.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm
	@echo $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl default.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E $(NAME)v.tpl tmp
	@$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	@$(REPLACE) $(COMPANYNAME) tmp1 $(NAME).rcv
	@del tmp > nul
	@del tmp1 > nul
	@echo $(NAME).rcv
