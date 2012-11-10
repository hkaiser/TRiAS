# -----------------------------------------------------------------------------
# Version.mak (TRiASXP)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK010814
VERSION = 1
RELEASE = 00
BUILD = 009

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
	@del TRiASXP.rcv
	@del TRiASXP.Def

formake:	Version.h TRiASXP.rcv TRiASXP.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) #$(COPYRIGHT) Version.tpl Version.h
	@echo $@

TRiASXP.def:	TRiASXP.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) TRiASXP.tpl TRiASXP.def
	@echo $@

# Personalisierungsinformation
TRiASXP.rcv:	TRiASXPv.tpl Version.mak
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
			TRiASXPv.tpl TRiASXP.rcv
	@echo $@

