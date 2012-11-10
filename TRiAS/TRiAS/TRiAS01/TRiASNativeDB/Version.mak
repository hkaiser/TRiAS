# -----------------------------------------------------------------------------
# Version.mak (TRiASNativeDB)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK040503
VERSION = 1
RELEASE = 00
BUILD = 066

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
	@del TRiASNativeDB.rcv
	@del TRiASNativeDB.Def

formake:	Version.h TRiASNativeDB.rcv TRiASNativeDB.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

TRiASNativeDB.def:	TRiASNativeDB.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) TRiASNativeDB.tpl TRiASNativeDB.def
	@echo $@

# Personalisierungsinformation
TRiASNativeDB.rcv:	TRiASNativeDBv.tpl Version.mak
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
			TRiASNativeDBv.tpl TRiASNativeDB.rcv
	@echo $@

