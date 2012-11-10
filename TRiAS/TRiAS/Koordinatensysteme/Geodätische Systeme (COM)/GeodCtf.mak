# Makefile für Koordinatentransformation
# Windows/DLL-Version
# MSVC V1.5 (Windows)

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 040608
VERSION = 4
RELEASE = 00
BUILD = 079
COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = GeodCtf_COM
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neu bilden
all:	formake

# Versionskontrolle -----------------------------------------------------------
new:
	@del $(DEF) > nul
	@del $(NAME).rcv > nul

formake:	$(DEF) $(NAME).rcv 

$(DEF):		$(NAME).tpl GeodCtf.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)
	@echo $(DEF)		

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl GeodCtf.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(TRIAS_VERSION) \
		$(TRIAS_RELEASE) \
		$(COMPANYNAME) \
			$(NAME)v.tpl $(NAME).rcv
	@echo $(NAME).rcv		


