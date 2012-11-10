# -----------------------------------------------------------------------------
# Version.mak (TRiASICN)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK010131
VERSION = 1
RELEASE = 00
BUILD = 012

COPYRIGHT = $(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

# -----------------------------------------------------------------------------
# commands
REPLACE = ersetz

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del Version.h
	@del TRiASICN.rcv
	@del TRiASICN.Def

formake:	Version.h TRiASICN.rcv TRiASICN.Def	

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

TRiASICN.def:	TRiASICN.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) TRiASICN.tpl TRiASICN.def
	@echo $@

# Personalisierungsinformation
TRiASICN.rcv:	TRiASICNv.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E TRiASICNv.tpl tmp
	@$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	@$(REPLACE) $(COMPANYNAME) tmp1 TRiASICN.rcv
	@del tmp > nul
	@del tmp1 > nul
	@echo $@

