# -----------------------------------------------------------------------------
# Version.mak (TRiASUI)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK020316
VERSION = 1
RELEASE = 00
BUILD = 054

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
	@del TRiASUI.rcv
	@del TRiASUI.Def
#	@del .\Help\TRiASUI.Fmt
#	@del .\Help\Contents.Hpj

formake:	Version.h TRiASUI.rcv TRiASUI.Def	# .\Help\TRiASUI.Fmt .\Help\Contents.Hpj

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

TRiASUI.def:	TRiASUI.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) TRiASUI.tpl TRiASUI.def
	@echo $@

# Personalisierungsinformation
TRiASUI.rcv:	TRiASUIv.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E TRiASUIv.tpl tmp
	@$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	@$(REPLACE) $(COMPANYNAME) tmp1 TRiASUI.rcv
	@del tmp > nul
	@del tmp1 > nul
	@echo $@

# Helpfilequellen vorbereiten
.\Help\TRiASUI.Fmt:	.\Help\TRiASUIFmt.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A .\Help\TRiASUIFmt.tpl tmp
	@$(REPLACE) $(COMPANYNAME) tmp .\Help\TRiASUI.Fmt
	@del tmp > nul
	@echo $@

.\Help\Contents.Hpj:	.\Help\Contents.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A .\Help\Contents.tpl tmp
	@$(REPLACE) $(COMPANYNAME) tmp .\Help\Contents.Hpj
	@del tmp > nul
	@echo $@
