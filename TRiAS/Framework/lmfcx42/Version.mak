!include <TRiASVerLang.mak>
APP_SHORT		= LMFCX42
!if "0x0407" == "$(TRIAS_LANGUAGE)"
APP_LONG		= MFC Extensions
!else if "0x0409" == "$(TRIAS_LANGUAGE)"
APP_LONG		= MFC extensions
!else
!error "Undefined Build-Language"
!endif
APP_YEAR		= 1995-2005
APP_COPYRIGHT	= HK050104
APP_VERSION		= 3
APP_RELEASE		= 0
APP_BUILD	= 107
APP_TLB_MAJOR	= 1
APP_TLB_MINOR	= 0
RC_DEFINES		= _AFXEXT
SOURCE_FILES = *.cpp
!include <triasverEx.mak>
