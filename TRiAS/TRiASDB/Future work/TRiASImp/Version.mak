# -----------------------------------------------------------------------------
# Version.mak (TRiASGDO)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = AD980215
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
# CopyrightEintraege Generieren 
new:
	@del Version.h
	@del TRiASImport.rcv
	@del TRiASImport.Def

formake:	Version.h TRiASImport.rcv

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

TRiASImport.Def:	TRiASImport.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) TRiASImport.tpl TRiASImport.Def
	@echo $@

# Personalisierungsinformation
triasimport.rcv:	triasimpv.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) triasimpv.tpl triasimport.rcv
	@echo $@
