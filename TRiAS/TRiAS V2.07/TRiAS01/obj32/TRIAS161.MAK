# -----------------------------------------------------------------------------
# File: TRiAS161.mak
# Genrieren der Versionsinfo's für TRIAS321.DLL

!include <triasver207.mak>

# Generierungsdatum (yymmdd) und Version
DBDATE=920727
DBVERSION = 5
DBRELEASE = 00
DBBUILD = 003

DATE=980608
VERSION = 6
RELEASE = 30
BUILD = 002

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
	@del TRiAS321.def

formake:	$(STUB).exe TRiAS321.Rcv TRiAS31d.def TRiAS321.def

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
TRiAS321.Rcv:	trias01v.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D trias01v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) tmp.rcv trias321.rcv
	@del tmp.rcv > nul

TRiAS31d.def:	..\TRiAS31d.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D desc.tpl TRiAS31d.def
	cat ..\TRiAS31d.tpl >> TRiAS31d.def

TRiAS321.def:	..\TRiAS321.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D desc.tpl TRiAS321.def
	cat ..\TRiAS321.tpl >> TRiAS321.def
