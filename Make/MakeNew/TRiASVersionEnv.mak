# Setzen der aktuellen TRiAS Version

!include <$(TRIASINCLUDE)/triasver.mak>

VERSION = $(TRIAS_VERSION)
RELEASE = $(TRIAS_RELEASE)
BUILD = $(TRIAS_BUILD)
DATE = $(TRIAS_DATE)

settriasversionenv:
	@-echo === Setting TRiAS version of current build
	@-setx BUILDING_TRIAS_VERSION "$(DATE).$(VERSION)$(RELEASE).$(BUILD)" -m

resettriasversionenv:
	@-echo === Resetting TRiAS version of current build
	@-setx BUILDING_TRIAS_VERSION "" -m