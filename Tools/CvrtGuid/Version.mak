# -----------------------------------------------------------------------------
# Version.mak (CvrtGuid)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK020710
VERSION = 1
RELEASE = 00
BUILD = 003

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
	@del CvrtGuid.rcv
	@del CvrtGuid.Def

formake:	Version.h CvrtGuid.rcv CvrtGuid.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

CvrtGuid.def:	CvrtGuid.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) CvrtGuid.tpl CvrtGuid.def
	@echo $@

# Personalisierungsinformation
CvrtGuid.rcv:	CvrtGuidv.tpl Version.mak
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
			CvrtGuidv.tpl CvrtGuid.rcv
	@echo $@

