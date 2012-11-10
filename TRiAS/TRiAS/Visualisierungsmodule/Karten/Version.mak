!include <TRiASVerLang.mak>
APP_SHORT		= Karten
!if "0x0407" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Objektbezogene Visualisierung von Hintergrundrasterbildern
!else if "0x0409" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Objectrelated visualisation of rasterimages.
!else
!error "Undefined Build-Language"
!endif
APP_YEAR		= 1995-2005
APP_COPYRIGHT	= HK050614
APP_VERSION		= 4
APP_RELEASE		= 0
APP_BUILD	= 431
APP_TLB_MAJOR	= 1
APP_TLB_MINOR	= 0
SOURCE_FILES = *.cpp *.rc
!include <triasverEx.mak>
