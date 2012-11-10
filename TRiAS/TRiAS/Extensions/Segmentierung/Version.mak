# -----------------------------------------------------------------------------
# Version.mak (Segment)

#!include <triasver.mak>
!include "$(TRIASINCLUDE)/triasver.mak"

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = KK020904
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
	@del Segment.rcv
	@del Segment.Def

formake:	Version.h Segment.rcv Segment.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

Segment.def:	Segment.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Segment.tpl Segment.def
	@echo $@

# Personalisierungsinformation
Segment.rcv:	Segmentv.tpl Version.mak
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
			Segmentv.tpl Segment.rcv
	@echo $@

