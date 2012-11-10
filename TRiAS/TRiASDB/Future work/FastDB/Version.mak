# Genrieren der Versionsinfo's 

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 030121
VERSION = 1
RELEASE = 00
BUILD = 036

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

REPLACE = ersetz
NAME = Fastdb
DEF = $(NAME).def

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@-del res\$(NAME).rcv > nul
	@-del $(NAME).def > nul

formake:	res\$(NAME).rcv $(NAME).def Version.h

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

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

$(NAME).def:	$(NAME).tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(NAME).def
	@echo $@


