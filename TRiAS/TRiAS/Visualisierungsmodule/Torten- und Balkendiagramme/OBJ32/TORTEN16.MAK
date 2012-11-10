# Genrieren der Versionsinfo's für TORTEN.VMD

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 010207
VERSION = 3
RELEASE = 20
BUILD = 014
COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = torten32
DEF = $(NAME).def

ASM = masm
ASMF = /D?PLM=0 /D?WIN=1
LINK = link16.exe

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del .\obj32\$(DEF) > nul
	@del .\obj32\$(NAME).rcv > nul

formake:	.\obj32\$(NAME).rcv .\obj32\$(DEF) 

.\obj32\$(DEF):		.\obj32\$(NAME).tpl .\obj32\torten16.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			.\obj32\$(NAME).tpl .\obj32\$(DEF)

# Personalisierungsinformation
.\obj32\$(NAME).rcv:	.\obj32\tortenv.tpl .\obj32\torten16.mak
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
			.\obj32\tortenv.tpl .\obj32\$(NAME).rcv

