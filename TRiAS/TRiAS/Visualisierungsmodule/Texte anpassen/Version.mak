# -----------------------------------------------------------------------------
# Version.mak (TxtRotl)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK010207
VERSION = 3
RELEASE = 20
BUILD = 013

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
	@del TxtRotl.rcv
	@del TxtRotl.Def

formake:	Version.h TxtRotl.rcv TxtRotl.Def 

Version.h:	Version.tpl Version.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			Version.tpl Version.h
	@echo $@

TxtRotl.def:	TxtRotl.tpl Version.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			TxtRotl.tpl TxtRotl.def
	@echo $@

# Personalisierungsinformation
TxtRotl.rcv:	TxtRotlv.tpl Version.mak
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
			TxtRotlv.tpl TxtRotl.rcv
	@echo $@


