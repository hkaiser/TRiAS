# Genrieren der Versionsinfo's für EdbsAlk.ext

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 040504
VERSION = 3
RELEASE = 03
BUILD = 015

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = EdbsAlk
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
#	@del $(STUB).asm

formake:	$(DEF) $(NAME).rcv versio32.h	# $(STUB).exe 

$(STUB).asm:	$(STUB).tpl Version.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(REPLACE) \
		$(COMPANYNAME) \
			$(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl Version.mak
	$(REPLACE) \
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

$(DEF):		$(NAME).tpl Version.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

versio32.h:	versio32.tpl Version.mak
	$(REPLACE) $(VERSION) $(RELEASE) versio32.tpl versio32.h
