# Genrieren der Versionsinfo's 

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 041125
VERSION = 1
RELEASE = 00
BUILD = 012

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

REPLACE = ersetz
NAME = ColorRes
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

res\copystr.rct:	res\copystrt.tpl version.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			res\copystrt.tpl res\copystr.rct
	@echo $@

