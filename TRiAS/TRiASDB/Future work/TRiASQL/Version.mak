# -----------------------------------------------------------------------------
# Version.mak (TRiASQL)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK990909
VERSION = 1
RELEASE = 00
BUILD = 002

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
	@del TRiASQL.rcv
	@del TRiASQL.Def
#	@del .\Help\TRiASQL.Fmt
#	@del .\Help\Contents.Hpj

formake:	Version.h TRiASQL.rcv TRiASQL.Def # .\Help\TRiASQL.Fmt .\Help\Contents.Hpj

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

TRiASQL.def:	TRiASQL.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) TRiASQL.tpl TRiASQL.def
	@echo $@

# Personalisierungsinformation
TRiASQL.rcv:	TRiASQLv.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E TRiASQLv.tpl tmp
	@$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	@$(REPLACE) $(COMPANYNAME) tmp1 TRiASQL.rcv
	@del tmp > nul
	@del tmp1 > nul
	@echo $@

# Helpfilequellen vorbereiten
.\Help\TRiASQL.Fmt:	.\Help\TRiASQLFmt.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A .\Help\TRiASQLFmt.tpl tmp
	@$(REPLACE) $(COMPANYNAME) tmp .\Help\TRiASQL.Fmt
	@del tmp > nul
	@echo $@

.\Help\Contents.Hpj:	.\Help\Contents.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A .\Help\Contents.tpl tmp
	@$(REPLACE) $(COMPANYNAME) tmp .\Help\Contents.Hpj
	@del tmp > nul
	@echo $@
