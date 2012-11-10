!include <TRiASVerLang.mak>
APP_SHORT		= Linesig
!if "0x0407" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Objektbezogene Visualisierung von Linien
!else if "0x0409" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Objectrelated visualisation of lines.
!else
!error "Undefined Build-Language"
!endif
APP_YEAR		= 1995-2001
APP_COPYRIGHT	= AK010314
APP_VERSION		= 4
APP_RELEASE		= 0
APP_BUILD	= 218
APP_TLB_MAJOR	= 1
APP_TLB_MINOR	= 0
SOURCE_FILES = *.cpp *.rc
!include <triasverEx.mak>
