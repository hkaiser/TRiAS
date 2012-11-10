# -----------------------------------------------------------------------------
# Version.mak (LineTools)

#!include <triasver.mak>
!include "$(TRIASINCLUDE)/triasver.mak"

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = KK030331
VERSION = 1
RELEASE = 00
BUILD = 021

COPYRIGHT = $(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

# -----------------------------------------------------------------------------
# commands
REPLACE = ersetz

# -----------------------------------------------------------------------------
# CopyrightEinträge Generieren 
new:
	@del Version.h
	@del LineTools.rcv
	@del LineTools.Def

formake:	Version.h LineTools.rcv LineTools.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

LineTools.def:	LineTools.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) LineTools.tpl LineTools.def
	@echo $@

# Personalisierungsinformation
LineTools.rcv:	LineToolsv.tpl Version.mak
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
			LineToolsv.tpl LineTools.rcv
	@echo $@

