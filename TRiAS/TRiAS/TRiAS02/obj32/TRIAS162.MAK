# Generieren der Versionsinfo's für TRIAS322.DLL

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 040508
VERSION = 6
RELEASE = 00
BUILD = 224				# 200: 30.11.2000, 22:59

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

obj32\$(STUB).exe:	obj32\$(STUB).asm
	@cd obj32
	$(ASM) $(ASMF) $(STUB) 
	$(LINK) /NOLOGO /KNOWEAS $(STUB);
	@cd ..

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del obj32\$(NAME).rcv
	@del obj32\trias32d.def
	@del obj32\trias322.def

formake:	obj32\trias322.rcv obj32\trias32d.def obj32\trias322.def

# Personalisierungsinformation
obj32\trias322.rcv:	obj32\trias32v.tpl obj32\trias162.mak
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
			obj32\trias32v.tpl obj32\trias322.rcv

obj32\trias32d.def:	obj32\trias32d.tpl obj32\trias162.mak obj32\desc.tpl
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			obj32\desc.tpl obj32\trias32d.def
#	cat obj32\trias32d.tpl >> obj32\trias32d.def

obj32\trias322.def:	obj32\trias322.tpl obj32\trias162.mak obj32\desc.tpl
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			obj32\desc.tpl obj32\trias322.def
#	cat obj32\trias322.tpl >> obj32\trias322.def

