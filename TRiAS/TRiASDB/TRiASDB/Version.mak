# -----------------------------------------------------------------------------
# Version.mak (TRiASDB)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK040918
VERSION = 1
RELEASE = 00
BUILD = 931		# 700 am 25. Mai 2000, 21:07 Uhr
				# 800 am 16. Januar 2001, 14:08 Uhr
				# 900 am 18. Dezember 2002, 11:32 Uhr

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
	@del TRiASDB.rcv
	@del TRiASDB.Def
	@del .\Help\TRiASDB.Fmt
	@del .\Help\Contents.Hpj

formake:	Version.h TRiASDB.rcv TRiASDB.Def .\Help\TRiASDB.Fmt .\Help\Contents.Hpj

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

TRiASDB.def:	TRiASDB.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) TRiASDB.tpl TRiASDB.def
	@echo $@

# Personalisierungsinformation
triasdb.rcv:	triasdbv.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D @E triasdbv.tpl tmp
	@$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) @A tmp tmp1
	@$(REPLACE) $(COMPANYNAME) tmp1 triasdb.rcv
	@del tmp > nul
	@del tmp1 > nul
	@echo $@

# Helpfilequellen vorbereiten
.\Help\TRiASDB.Fmt:	.\Help\TRiASDBFmt.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A .\Help\TRiASDBFmt.tpl tmp
	@$(REPLACE) $(COMPANYNAME) tmp .\Help\TRiASDB.Fmt
	@del tmp > nul
	@echo $@

.\Help\Contents.Hpj:	.\Help\Contents.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A .\Help\Contents.tpl tmp
	@$(REPLACE) $(COMPANYNAME) tmp .\Help\Contents.Hpj
	@del tmp > nul
	@echo $@
