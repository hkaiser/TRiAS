# Genrieren der Versionsinfo's für TRSABiS.EXT

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 040503
VERSION = 1
RELEASE = 00
BUILD = 045

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = TRSABiS
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(NAME).rcv
	@del $(DEF)
	@del version.h

formake:	$(DEF) $(NAME).rcv version.h

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl TrSabis16.mak
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

$(DEF):		$(NAME).tpl TrSabis16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			$(NAME).tpl $(DEF)

version.h:	version.tpl TrSabis16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
			version.tpl version.h
