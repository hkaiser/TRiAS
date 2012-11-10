# -----------------------------------------------------------------------------
# File: TRiAS161.mak
# Genrieren der Versionsinfo's für TRIAS321.DLL

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DBDATE=920727
DBVERSION = 5
DBRELEASE = 00
DBBUILD = 003

DATE = 041125
VERSION = 6
RELEASE = 31
BUILD = 273		# V6.31.200: 7. Juni 2001, 13:12

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = trias321

ASM = ml.exe
ASMF = /I. /Zm /c /D?PLM=0 /D?WIN=1 /Ta
LINK = link16.exe

# Alles neubilden
all:	formake 

$(STUB).exe:	$(STUB).asm
	$(ASM) $(ASMF) $(STUB).asm 
	$(LINK) /NOLOGO /KNOWEAS $(STUB);

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(STUB).asm
	@del $(NAME).rcv
	@del TRiAS31d.def

formake:	trias321.rcv TRiAS31d.def	#$(STUB).exe 

$(STUB).asm:	$(STUB).tpl TRiAS161.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(STUB).tpl $(STUB).asm

# Personalisierungsinformation
trias321.rcv:	trias01v.tpl TRiAS161.mak
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
			trias01v.tpl trias321.rcv

trias31d.def:   trias31d.tpl TRiAS161.mak
        $(REPLACE) \
			$(VERSION) \
			$(RELEASE) \
			$(BUILD) \
			$(COPYRIGHT) \
				desc.tpl trias31d.def
		cat trias31d.tpl >> trias31d.def

trias321.def:   trias321.tpl TRiAS161.mak
        $(REPLACE) \
			$(VERSION) \
			$(RELEASE) \
			$(BUILD) \
			$(COPYRIGHT) \
				desc.tpl trias321.def
		cat trias321.tpl >> trias321.def

DbmsVersion.h:   DbmsVersion.tpl TRiAS161.mak
        $(REPLACE) \
			$(VERSION) \
			$(RELEASE) \
			$(BUILD) \
				DbmsVersion.tpl DbmsVersion.h
