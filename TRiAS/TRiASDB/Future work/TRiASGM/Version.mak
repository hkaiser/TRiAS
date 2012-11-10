# -----------------------------------------------------------------------------
# Version.mak (TRiASGM)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK980925
VERSION = 1
RELEASE = 00
BUILD = 022

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
	@del TRiASGM.rcv
	@del TRiASGM.Def
	@del .\Help\TRiASGM.Fmt

formake:	Version.h TRiASGM.rcv TRiASGM.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

TRiASGM.def:	TRiASGM.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) TRiASGM.tpl TRiASGM.def
	@echo $@

# Personalisierungsinformation
TRiASGM.rcv:	TRiASGMv.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E TRiASGMv.tpl tmp
	@$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	@$(REPLACE) $(COMPANYNAME) tmp1 TRiASGM.rcv
	@del tmp > nul
	@del tmp1 > nul
	@echo $@

