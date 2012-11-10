# Generieren der Versionsinfo's für GEOMETR.DLL

!include <$(TRIASINCLUDE)/triasver.mak>
!include <$(TRIASINCLUDE)/GeometryVersion.mak>

# Generierungsdatum (yymmdd) und Version
DATE = $(GEOMETRY_DATE)
VERSION = $(GEOMETRY_VERSION)
RELEASE = $(GEOMETRY_RELEASE)
BUILD = $(GEOMETRY_BUILD)

COPYRIGHT = WM$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = geometr

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neubilden
all:	formake 

$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB) 
	$(LINK) /NOLOGO /KNOWEAS $(STUB);

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
#	@del $(STUB).asm
	@del $(NAME).rcv

formake:        geometr.rcv		#$(STUB).exe 

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
#geometr.rcv:   geometrv.rc
#        $(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B geometrv.rc tmp.rcv
#        $(REPLACE) $(PNAME) $(PADDRESS) tmp.rcv geometr.rcv
#	@del tmp.rcv > nul

$(NAME).rcv:    $(NAME)v.tpl makefile $(TRIASINCLUDE)\GeometryVersion.mak
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
