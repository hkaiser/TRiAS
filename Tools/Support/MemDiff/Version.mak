# -----------------------------------------------------------------------------
# Version.mak (MemDiffExt)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK991015
VERSION = 1
RELEASE = 00
BUILD = 001

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
	@del MemDiffExt.rcv
	@del MemDiffExt.Def

formake:	Version.h MemDiffExt.rcv MemDiffExt.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

MemDiffExt.def:	MemDiffExt.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) MemDiffExt.tpl MemDiffExt.def
	@echo $@

# Personalisierungsinformation
MemDiffExt.rcv:	MemDiffExtv.tpl Version.mak
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
			MemDiffExtv.tpl MemDiffExt.rcv
	@echo $@

