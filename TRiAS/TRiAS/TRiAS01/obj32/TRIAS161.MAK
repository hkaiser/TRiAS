# -----------------------------------------------------------------------------
# File: TRiAS161.mak
# Genrieren der Versionsinfo's für TRIAS321.DLL

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DBDATE=920727
DBVERSION = 5
DBRELEASE = 00
DBBUILD = 003

DATE=971007
VERSION = 6
RELEASE = 30
BUILD = 001

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = trias321

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
	@del $(STUB).asm
	@del $(NAME).rcv
	@del TRiAS31d.def

formake:	$(STUB).exe TRiAS321.Rcv TRiAS31d.def

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
TRiAS321.Rcv:	trias01v.tpl trias161.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D .\obj32\trias01v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) tmp.rcv .\obj32\trias321.rcv
	@del tmp.rcv > nul

trias31d.def:   trias31d.tpl trias161.mak
        $(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) desc.tpl trias31d.def
        cat trias31d.tpl >> trias31d.def

trias321.hdr:   trias321.tpl trias161.mak
        $(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) desc.tpl trias321.hdr
        cat trias321.tpl >> trias321.def
