!include <TRiASVerLang.mak>
APP_SHORT		= TRiASMDS
!if "0x0407" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Metadatenservice
!else if "0x0409" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Metadataservice.
!else
!error "Undefined Build-Language"
!endif
APP_YEAR		= 1998-1999
APP_COPYRIGHT	= AK010704
APP_VERSION		= 1
APP_RELEASE		= 0
APP_BUILD	= 254
APP_TLB_MAJOR	= 1
APP_TLB_MINOR	= 0
DOC_FILES= .\TRiASMDS.idl	\
	.\vb\ModTestFormatOKS.bas	\
	.\vb\ModTestRegExp.bas	\
	.\vb\ModTestMDSKey.bas
!include <triasverEx.mak>
