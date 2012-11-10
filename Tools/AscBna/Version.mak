# -----------------------------------------------------------------------------
# Version.mak (AscBna)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK011019
VERSION = 2
RELEASE = 00
BUILD = 020

COPYRIGHT = $(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

# -----------------------------------------------------------------------------
# commands
REPLACE = ersetz

# -----------------------------------------------------------------------------
# CopyrightEinträge Generieren 
new:
	@del DBVersio.h

formake:	DBVersio.h 

DBVersio.h:	DBVersio.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) DBVersio.tpl DBVersio.h
	@echo $@

