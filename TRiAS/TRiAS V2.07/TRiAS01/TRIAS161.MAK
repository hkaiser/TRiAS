# -----------------------------------------------------------------------------
# File: TRiAS161.mak
# Genrieren der Versionsinfo's für TRIAS321.DLL

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DBDATE=920727
DBVERSION = 5
DBRELEASE = 00
DBBUILD = 003

DATE=971223
VERSION = 6
RELEASE = 30
BUILD = 011

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

formake:	$(STUB).exe trias321.rcv

$(STUB).asm:	$(STUB).tpl TRiAS161.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
trias321.rcv:	trias01v.tpl TRiAS161.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D trias01v.tpl tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) tmp.rcv trias321.rcv
	@del tmp.rcv > nul

