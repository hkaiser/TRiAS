# -----------------------------------------------------------------------------
# Version.mak (VidCtrl)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK020717
VERSION = 1
RELEASE = 00
BUILD = 037

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
	@del VidCtrl.rcv
	@del VidCtrl.Def

formake:	Version.h VidCtrl.rcv VidCtrl.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) Version.tpl Version.h
	@echo $@

VidCtrl.def:	VidCtrl.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) VidCtrl.tpl VidCtrl.def
	@echo $@

# Personalisierungsinformation
VidCtrl.rcv:	VidCtrlv.tpl Version.mak
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
			VidCtrlv.tpl VidCtrl.rcv
	@echo $@

