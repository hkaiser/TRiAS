!include <TRiASVerLang.mak>
APP_SHORT		= TErrTrk
!if "0x0407" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Fehlerverfolgung.
!else if "0x0409" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Error tracking.
!else
!error "Undefined Build-Language"
!endif
APP_YEAR		= 1998
APP_COPYRIGHT	= AK001202
APP_VERSION		= 1
APP_RELEASE		= 0
APP_BUILD	= 128
APP_TLB_MAJOR	= 1
APP_TLB_MINOR	= 0
!include <triasverEx.mak>
