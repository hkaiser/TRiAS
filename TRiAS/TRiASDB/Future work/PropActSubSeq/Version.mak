# -----------------------------------------------------------------------------
# Version.mak (PropActSubSeq)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK990404
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
	@del PropActSubSeq.rcv
	@del PropActSubSeq.Def

formake:	Version.h PropActSubSeq.rcv PropActSubSeq.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

PropActSubSeq.def:	PropActSubSeq.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) PropActSubSeq.tpl PropActSubSeq.def
	@echo $@

# Personalisierungsinformation
PropActSubSeq.rcv:	PropActSubSeqv.tpl Version.mak
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
			PropActSubSeqv.tpl PropActSubSeq.rcv
	@echo $@

