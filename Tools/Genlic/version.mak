# Genrieren der Versionsinfo's 

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 031213
VERSION = 1
RELEASE = 00
BUILD = 001

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

GLOBAL_COPYRIGHT = $(TRIAS_COPYRIGHT)

REPLACE = ersetz
NAME = Genlic
DEF = $(NAME).def

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del res\$(NAME).rcv
	@del res\copystr.rc

formake:	res\$(NAME).rcv res\copystr.rc

# Personalisierungsinformation
res\$(NAME).rcv:	res\$(NAME)v.tpl version.mak
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
			res\$(NAME)v.tpl res\$(NAME).rcv
	@echo $@

res\copystr.rc:	res\copystrt.tpl version.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			res\copystrt.tpl res\copystr.rc
	@echo $@

