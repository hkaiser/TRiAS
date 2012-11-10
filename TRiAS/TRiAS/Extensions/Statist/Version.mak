# -----------------------------------------------------------------------------
# Version.mak (Statist)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK041114
VERSION = 2
RELEASE = 00
BUILD = 213			# V2.00.100: 28. Januar 2001, 23:07
					# V2.00.200: 17. Dezember 2002, 10:58

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
	@del Statist.rcv
	@del Statist.Def
	@del .\Help\Statist.Fmt
	@del .\Help\Contents.Hpj

formake:	Version.h Statist.rcv Statist.Def .\Help\Statist.Fmt .\Help\Contents.Hpj

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

Statist.def:	Statist.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Statist.tpl Statist.def
	@echo $@

# Personalisierungsinformation
Statist.rcv:	Statistv.tpl Version.mak
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
			Statistv.tpl Statist.rcv
	@echo $@

# Helpfilequellen vorbereiten
.\Help\Statist.Fmt:	.\Help\StatistFmt.tpl Version.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(COMPANYNAME) \
			.\Help\StatistFmt.tpl .\Help\Statist.Fmt
	@echo $@

.\Help\Contents.Hpj:	.\Help\Contents.tpl Version.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(COMPANYNAME) \
			.\Help\Contents.tpl .\Help\Contents.Hpj
	@echo $@
