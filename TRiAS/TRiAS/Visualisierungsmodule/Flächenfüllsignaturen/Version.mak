# -----------------------------------------------------------------------------
# Version.mak (FillMode)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK001201
VERSION = 2
RELEASE = 00
BUILD = 015

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
	@del FillMode.rcv
	@del FillMode.Def

formake:	Version.h FillMode.rcv FillMode.Def 

Version.h:	Version.tpl Version.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			Version.tpl Version.h
	@echo $@

FillMode.def:	FillMode.tpl Version.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			FillMode.tpl FillMode.def
	@echo $@

# Personalisierungsinformation
FillMode.rcv:	FillModev.tpl Version.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(TRIAS_VERSION) \
		$(TRIAS_RELEASE) \
		$(COMPANYNAME) \
			FillModev.tpl FillMode.rcv
	@echo $@


