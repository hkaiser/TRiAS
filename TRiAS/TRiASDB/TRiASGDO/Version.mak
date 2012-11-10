!include <TRiASVerLang.mak>
APP_SHORT		= TRiASGDO
!if "0x0407" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Einheitliche DB-Schnittstelle für GDO-basierte Projekte.
!else if "0x0409" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Unique Databaseinterface for GDO-based Projects.
!else
!error "Undefined Build-Language"
!endif
APP_YEAR		= 1998-1999
APP_COPYRIGHT	= AK030122
APP_VERSION		= 1
APP_RELEASE		= 0
APP_BUILD	= 1170
APP_TLB_MAJOR	= 1
APP_TLB_MINOR	= 0
SOURCE_FILES = *.cpp *.rc res\*.rgs
!include <triasverEx.mak>
