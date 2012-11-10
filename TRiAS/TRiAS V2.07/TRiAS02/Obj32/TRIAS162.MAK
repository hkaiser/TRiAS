# Genrieren der Versionsinfo's fr TRIAS322.DLL

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE=980613
VERSION = 5
RELEASE = 20
BUILD = 052
COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = trias322

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
	@del trias32d.def
	@del trias322.def

formake:	$(STUB).exe trias322.rcv trias32d.def trias322.def

$(STUB).asm:	$(STUB).tpl 
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
trias322.rcv:	trias32v.rc
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) @A @B @C @D trias32v.rc tmp.rcv
	$(REPLACE) $(PNAME) $(PADDRESS) $(TRIAS_VERSION) $(TRIAS_RELEASE) tmp.rcv trias322.rcv
	@del tmp.rcv > nul

trias32d.def:	trias32d.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) desc.tpl trias32d.def
	cat trias32d.tpl >> trias32d.def

trias322.def:	trias322.tpl
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) desc.tpl trias322.def
	cat trias322.tpl >> trias322.def

