# -----------------------------------------------------------------------------
# Version.mak (TRiASCFG)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK041112
VERSION = 1
RELEASE = 00
BUILD = 065

COPYRIGHT = $(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

# -----------------------------------------------------------------------------
# commands
REPLACE = ersetz

# -----------------------------------------------------------------------------
# CopyrightEinträge Generieren 
new:
	@del TRiASCFG.rcv
	@del TRiASCFG.def

formake:	TRiASCFG.rcv TRiASCFG.def

# Personalisierungsinformation
TRiASCFG.rcv:	TRiASCFGv.tpl Version.mak
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
			TRiASCFGv.tpl TRiASCFG.rcv
	@echo $@

TRiASCFG.def:	TRiASCFG.tpl Version.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			TRiASCFG.tpl TRiASCFG.def
	@echo $@
