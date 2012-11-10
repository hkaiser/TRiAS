!include <TRiASVerLang.mak>
APP_SHORT		= LPict42
!if "0x0407" == "$(TRIAS_LANGUAGE)"
APP_LONG		= RasterImage Layer
!else if "0x0409" == "$(TRIAS_LANGUAGE)"
APP_LONG		= RasterImage Layer
!else
!error "Undefined Build-Language"
!endif
APP_YEAR		= 1995-2002
APP_COPYRIGHT	= AK050104
APP_VERSION		= 3
APP_RELEASE		= 0
APP_BUILD	= 387
APP_TLB_MAJOR	= 1
APP_TLB_MINOR	= 0
RC_DEFINES		= _AFXEXT
SOURCE_FILES = *.cpp
!include <triasverEx.mak>
