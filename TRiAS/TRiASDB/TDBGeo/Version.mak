!include <TRiASVerLang.mak>
APP_SHORT		= TDBGeo
!if "0x0407" == "$(TRIAS_LANGUAGE)"
APP_LONG		= TRiASDB Geometrieobjekte.
!else if "0x0409" == "$(TRIAS_LANGUAGE)"
APP_LONG		= TRiASDB Geometry objects.
!else
!error "Undefined Build-Language"
!endif
APP_YEAR		= 1998-2002
APP_COPYRIGHT	= HK021010
APP_VERSION		= 1
APP_RELEASE		= 00
APP_BUILD	= 374
APP_TLB_MAJOR	= 1
APP_TLB_MINOR	= 0
IDL_FILES= \
	.\Help\TDBGEO.hh \
	.\Help\TDBGEO.cnt \
	.\Help\TDBGEO.hpj
DOC_FILES= \
	.\TDBGEO.idl		\
	$(IDL_FILES)
# !message CFG = $(CFG)
!if "$(CFG)" == "_DEBUGMT"
RC_DEFINES=_USE_PERFMON_COUNTERS /d _ATL_FREE_THREADED
!elseif "$(CFG)" == "_DEBUG"
RC_DEFINES=_USE_PERFMON_COUNTERS /d _ATL_APARTMENT_THREADED
!elseif "$(CFG)" == "NDEBUGMT"
RC_DEFINES=_ATL_FREE_THREADED
!elseif "$(CFG)" == "NDEBUG"
RC_DEFINES=_ATL_APARTMENT_THREADED
!else
!error "Bitte _DEBUG/_DEBUGMT oder NDEBUG/NDEBUGMT angeben!"
!endif
#
#
!include <triasverEx.mak>
#
# Vorbereiten der Dokumentations-Dateien
DOCUMENT_SRC_IDL= \
	.\TDBGEO.idl
#
#
.\Help\TDBGEO.hh:	$(DOCUMENT_SRC_IDL) .\help\TDBGEOhh.sed .\help\TDBGEOhh.awk
	@sed -f .\help\TDBGEOhh.sed .\TDBGEO.idl > $@
	@sort $@ > tmp1
	@uniq tmp1 | gawk -f .\help\TDBGEOhh.awk | sed -e "/#define x/d" > $@
	@xcopy /F $@ $(TRIASINCLUDE)
	@del /F /Q tmp1 > nul
#
#
.\Help\TDBGEO.cnt:	.\Help\TDBGEOTpl.cnt $(DOCUMENT_SRC_IDL)
	@$(REPLACE) $(APP_VERSION) $(APP_RELEASE) .\Help\TDBGEOTpl.cnt $@
	@xcopy /F $@ $(TRIASHELP)
#
#
.\Help\TDBGEO.hpj:	.\Help\TDBGEO.tpl
	@$(REPLACE) \
		$(APP_VERSION) \
		$(APP_RELEASE) \
		$(APP_BUILD) \
		$(APP_COPYRIGHT) \
		$(COMPANYNAME) \
			.\Help\TDBGEO.Tpl $@
