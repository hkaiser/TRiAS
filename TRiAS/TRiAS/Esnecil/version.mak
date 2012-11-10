# Genrieren der Versionsinfo's 

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 031216
VERSION = 1
RELEASE = 00
BUILD = 001

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

GLOBAL_COPYRIGHT = $(TRIAS_COPYRIGHT)

REPLACE = ersetz
NAME = Esnecil
DEF = $(NAME).def

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del EsnecilVersion.h

formake:	EsnecilVersion.h

# Personalisierungsinformation
EsnecilVersion.h:	EsnecilVersion.tpl version.mak ..\Include\triasver.mak
	@$(REPLACE) \
		$(GLOBAL_COPYRIGHT) \
			EsnecilVersion.tpl EsnecilVersion.h
	@echo $@

