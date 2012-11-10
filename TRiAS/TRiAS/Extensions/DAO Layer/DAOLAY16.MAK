# Genrieren der Versionsinfo's für DAOLAYER.EBN

!include "$(TRIASINCLUDE)/TRiASVer.mak"

# Generierungsdatum (yymmdd) und Version

DATE=020718
VERSION = 2
RELEASE = 00
BUILD = 023

RES_VERSION = 1
RES_RELEASE = 10

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

COPYRIGHT = HK$(DATE)

#PNAME = "Version f\xfcr den internen Gebrauch"
#PADDRESS = "Fernerkundungszentrum Potsdam GmbH"

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = daolayer
DEFD = daolayed.def
DEF = daolayer.def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe
DUMPBIN=c:\msdev\bin\dumpbin.exe

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
	@del $(DEFD)
	@del $(DEF)
	@del res\daoextf.rc

formake:	$(DEF) $(DEFD) $(NAME).rcv res\daoextf.rc		# $(STUB).exe 

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
$(NAME).rcv:	daolayv.tpl daolay16.mak
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
			daolayv.tpl $(NAME).rcv

$(DEFD):		$(NAME).tpl daolay16.mak
        $(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEFD)

$(DEF):			$(NAME).tpl daolay16.mak
        $(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

res\daoextf.rc:	res\daoextp.tpl daolay16.mak
	$(REPLACE) \
		$(RES_VERSION) \
		$(RES_RELEASE) \
		$(COPYRIGHT) \
		res\daoextp.tpl res\daoextf.rc
