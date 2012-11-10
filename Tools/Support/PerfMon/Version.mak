# -----------------------------------------------------------------------------
# Version.mak (PerfMon)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK990916
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
# CopyrightEintraege Generieren 
new:
	@del Version.h
	@del PerfMon.rcv
	@del PerfMon.Def

formake:	Version.h PerfMon.rcv PerfMon.Def	

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

PerfMon.def:	PerfMon.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) PerfMon.tpl PerfMon.def
	@echo $@

# Personalisierungsinformation
PerfMon.rcv:	PerfMonv.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E PerfMonv.tpl tmp
	@$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	@$(REPLACE) $(COMPANYNAME) tmp1 PerfMon.rcv
	@del tmp > nul
	@del tmp1 > nul
	@echo $@

