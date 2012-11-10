# Generieren der Versionsinfo's für OLEAUTO.EXT

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 041217
VERSION = 2
RELEASE = 20
BUILD = 535		# 400 am 21. September 2000, 20:31
                # 2.20.500 am 2. November 2002, 19:54

RC_VERSION = 4
RC_RELEASE = 00

COPYRIGHT = HK_vb$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = oleauto
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK16 = link16.exe

# Alles neubilden
all:	formake 

$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK16) /NOLOGO /KNOWEAS $(STUB);

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(NAME).rcv
	@del $(DEF)
	@del versio32.h
	@del olebsext.rc
#	@del $(STUB).asm

formake:	$(DEF) $(NAME).rcv versio32.h olebsext.rc	# $(STUB).exe 

$(STUB).asm:	$(STUB).tpl oleaut16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl oleaut16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(TRIAS_VERSION) \
		$(TRIAS_RELEASE) \
		$(COMPANYNAME) \
			$(NAME)v.tpl $(NAME).rcv

$(DEF):		$(NAME).tpl oleaut16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

versio32.h:	versio32.tpl oleaut16.mak
	$(REPLACE) $(VERSION) $(RELEASE) versio32.tpl versio32.h

olebsext.rc:	olbsextp.tpl oleaut16.mak
	$(REPLACE) $(RC_VERSION) $(RC_RELEASE) olbsextp.tpl olebsext.rc
	xcopy /F olebsext.rc .\win32\olebsext.rc

# Helpfilequellen vorbereiten
.\Documentation\OleAuto.fmt:	.\Documentation\OleAutofmt.tpl oleaut16.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(COMPANYNAME) \
			.\Documentation\OleAutofmt.tpl .\Documentation\OleAuto.Fmt

.\Documentation\OleAuto.cnt:	.\Documentation\OleAutotpl.cnt oleaut16.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(COMPANYNAME) \
			.\Documentation\OleAutotpl.cnt .\Documentation\OleAuto.cnt

.\Documentation\Contents.hpj:	.\Documentation\contents.tpl oleaut16.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(COMPANYNAME) \
			.\Documentation\contents.tpl .\Documentation\Contents.hpj

DOCUMENT_SRC_IDL = .\Win32\triastlb.idl \
				$(TRIASINCLUDE)\idl\TRiASBaseInterfaces.idl \
				$(TRIASINCLUDE)\idl\ProgInd2.idl \
                $(TRIASINCLUDE)\idl\PropertySequence.idl \
                $(TRIASINCLUDE)\idl\PropertySequenceService.idl

DOCUMENT_SRC =	.\Documentation\Preface.d \
				.\Documentation\VariablesInBasicScript.d \
				.\Documentation\ObjectsInBasicScript.d \
				.\Documentation\Dataobjects.d \
				.\Documentation\contents.d \
				$(DOCUMENT_SRC_IDL)

.\Documentation\OleAuto.rtf:	$(DOCUMENT_SRC) .\Documentation\OleAuto.fmt
	@autoduck /rh /t4 \
			 /L .\Documentation\contents.log \
			 /s .\Documentation\OleAuto.Fmt \
			 /o .\Documentation\OleAuto.rtf \
				$(DOCUMENT_SRC)

.\Documentation\OleAuto.hh:	$(DOCUMENT_SRC_IDL) .\Documentation\OleAutohh.sed .\Documentation\OleAutohh.awk
	@sed -f .\Documentation\OleAutohh.sed .\Win32\triastlb.idl > .\Documentation\triastlb.hh
	@sed -f .\Documentation\OleAutohh.sed $(TRIASINCLUDE)\idl\TRiASBaseInterfaces.idl >> .\Documentation\triastlb.hh
	@sed -f .\Documentation\OleAutohh.sed $(TRIASINCLUDE)\idl\ProgInd2.idl >> .\Documentation\triastlb.hh
	@sed -f .\Documentation\OleAutohh.sed $(TRIASINCLUDE)\idl\PropertySequence.idl >> .\Documentation\triastlb.hh
	@sed -f .\Documentation\OleAutohh.sed $(TRIASINCLUDE)\idl\PropertySequenceService.idl >> .\Documentation\triastlb.hh
	@sort .\Documentation\triastlb.hh > tmp1
	@uniq tmp1 | gawk -f .\Documentation\OleAutohh.awk | sed -e "/#define x/d" > .\Documentation\OleAuto.hh
	@xcopy /F .\Documentation\OleAuto.hh $(TRIASINCLUDE)
#	@del /F /Q tmp1 .\Documentation\triastlb.hh > nul

!IF "$(DEBUG)" != ""
HCRTF_FLAGS = /A
!ELSE
HCRTF_FLAGS =
!ENDIF

.\Documentation\OleAuto.hlp:	.\Documentation\Contents.hpj .\Documentation\OleAuto.rtf .\Documentation\OleAuto.hh .\Documentation\OleAuto.cnt
	@hcrtf $(HCRTF_FLAGS) /o .\Documentation\OleAuto.hlp /xn .\Documentation\Contents.hpj 
	@xcopy /F .\Documentation\OleAuto.hlp $(TRIASINCLUDE)\help 
