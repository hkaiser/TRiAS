!include <TRiASVerLang.mak>
APP_SHORT		= TRiASCS
!if "0x0407" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Koordinatensysteme
!else if "0x0409" == "$(TRIAS_LANGUAGE)"
APP_LONG		= Coordinate Systems
!else
!error "Undefined Build-Language"
!endif
APP_YEAR		= 1998-2005
APP_COPYRIGHT	= HK050104
APP_VERSION		= 1
APP_RELEASE		= 00
APP_BUILD	= 491
APP_TLB_MAJOR	= 1
APP_TLB_MINOR	= 0
IDL_FILES= \
	.\Help\TRiASCs.hh \
	.\Help\TRiASCs.cnt \
	.\Help\TRiASCs.hpj
DOC_FILES= \
	.\TRiASCS.idl		\
	.\epsg.h			\
	.\triascs.hmc		\
	vb\GeoZuGau.bas		\
	vb\CSSet.bas		\
	vb\ModTestGoodEnvelope.bas \
	$(IDL_FILES)
SOURCE_FILES= \
	*.cpp \
	*.h \
	*.rc \
	*.rgs \
	.\LibCTF\*.cpp \
	.\LibCTF\*.h
#
#
!include <triasverEx.mak>
#
# Vorbereiten der Dokumentations-Dateien
DOCUMENT_SRC_IDL= \
	.\TRiASCs.idl
#
#
.\Help\TRiASCs.hh:	$(DOCUMENT_SRC_IDL) .\help\TRiASCshh.sed .\help\TRiASCshh.awk
	@sed -f .\help\TRiASCshh.sed .\TRiASCs.idl > $@
	@sort $@ > tmp1
	@uniq tmp1 | gawk -f .\help\TRiASCshh.awk | sed -e "/#define x/d" > $@
	@xcopy /F $@ $(TRIASINCLUDE)
	@del /F /Q tmp1 > nul
#
#
.\Help\TRiASCs.cnt:	.\Help\TRiASCsTpl.cnt $(DOCUMENT_SRC_IDL)
	@$(REPLACE) $(APP_VERSION) $(APP_RELEASE) .\Help\TRiASCsTpl.cnt $@
	@xcopy /F $@ $(TRIASHELP)
#
#
.\Help\TRiASCs.hpj:	.\Help\TRiASCs.tpl
	@$(REPLACE) \
		$(APP_VERSION) \
		$(APP_RELEASE) \
		$(APP_BUILD) \
		$(APP_COPYRIGHT) \
		$(COMPANYNAME) \
			.\Help\TRiASCs.Tpl $@
