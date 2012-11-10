# -----------------------------------------------------------------------------
# Version.mak (TRiASOleDB)

!include <triasver.mak>

# -----------------------------------------------------------------------------
# Generierungsdatum (yymmdd) und Version
DATE = HK040503
VERSION = 2
RELEASE = 00
BUILD = 315 		# V1.00.100: 23. Mai 2001, 13:32
					# V1.00.200: 24. Juni 2001, 11:08
					# V2.00.210: 25. Juni 2001, 21:35, starting implementation of write support
					# V2.00.300: 19. Juli 2001, 23:42

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
	@del TRiASOleDB.rcv
	@del TRiASOleDB.Def

formake:	Version.h TRiASOleDB.rcv TRiASOleDB.Def 

Version.h:	Version.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) #$(COPYRIGHT) Version.tpl Version.h
	@echo $@

#TRiASOleDB.def:	TRiASOleDB.tpl Version.mak
	@$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) TRiASOleDB.tpl TRiASOleDB.def
	@echo $@

# Personalisierungsinformation
TRiASOleDB.rcv: TRiASOleDBv.tpl Version.mak
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
			TRiASOleDBv.tpl TRiASOleDB.rcv
	@echo $@

