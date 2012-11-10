# $Header: $
# Copyright© 1999-2002 GEOPunkt GmbH & Co. KG, NL Potsdam, All rights reserved
# Created: 20.04.2002 16:45:45 
#
# @doc
# @module version.mak | Generieren der Versionsinfo's 

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 020421
VERSION = 1
RELEASE = 00
BUILD = 004

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

REPLACE = ersetz
NAME = RUNCMDAS

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@-del $(NAME).rcv > nul
	@-del $(NAME).def > nul

formake:	$(NAME).rcv $(NAME).def Version.h

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl version.mak
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
	@echo $@

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@


