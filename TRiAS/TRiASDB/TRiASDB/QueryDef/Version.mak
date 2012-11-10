# -----------------------------------------------------------------------------
# Version.mak (QueryDef)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK010927
VERSION = 1
RELEASE = 00
BUILD = 060

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
	@del QueryDef.rcv
	@del QueryDef.Def

formake:	Version.h QueryDef.rcv QueryDef.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

QueryDef.def:	QueryDef.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) QueryDef.tpl QueryDef.def
	@echo $@

# Personalisierungsinformation
QueryDef.rcv:	QueryDefv.tpl Version.mak
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
			QueryDefv.tpl QueryDef.rcv
	@echo $@

