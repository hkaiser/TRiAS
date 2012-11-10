# -----------------------------------------------------------------------------
# Version.mak (UnRegTRiAS)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK020422
VERSION = 1
RELEASE = 00
BUILD = 011

COPYRIGHT = $(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

# -----------------------------------------------------------------------------
# commands
REPLACE = ersetz

# -----------------------------------------------------------------------------
# CopyrightEinträge Generieren 
new:
	@del UnRegTRiAS.rcv UnRegTRiAS.def

formake:	UnRegTRiAS.rcv UnRegTRiAS.def

# Personalisierungsinformation
UnRegTRiAS.rcv:	UnRegTRiASv.tpl Version.mak
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
			UnRegTRiASv.tpl UnRegTRiAS.rcv
	@echo $@

UnRegTRiAS.def:	UnRegTRiAS.tpl Version.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			UnRegTRiAS.tpl UnRegTRiAS.def
	@echo $@
