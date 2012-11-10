# -----------------------------------------------------------------------------
# Version.mak (LoadableCommands)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK041112
VERSION = 1
RELEASE = 00
BUILD = 004

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
	@del LoadableCommands.rcv
	@del LoadableCommands.Def

formake:	Version.h LoadableCommands.rcv LoadableCommands.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

LoadableCommands.def:	LoadableCommands.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) LoadableCommands.tpl LoadableCommands.def
	@echo $@

# Personalisierungsinformation
LoadableCommands.rcv:	LoadableCommandsv.tpl Version.mak
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
			LoadableCommandsv.tpl LoadableCommands.rcv
	@echo $@

