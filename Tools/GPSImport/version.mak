# Genrieren der Versionsinfo's 

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 020708
VERSION = 1
RELEASE = 00
BUILD = 013

COPYRIGHT = KK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

REPLACE = ersetz
NAME = GPSImport
DEF = $(NAME).def

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del res\$(NAME).rcv
	@del res\GPSstr.rc

formake:	res\$(NAME).rcv res\GPSstr.rc

# Personalisierungsinformation
res\$(NAME).rcv:	res\$(NAME)v.tpl version.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(TRIAS_VERSION) \
		$(TRIAS_RELEASE) \
		$(COMPANYNAME) \
			res\$(NAME)v.tpl res\$(NAME).rcv
	@echo $@

res\GPSstr.rc:	res\GPSstrt.tpl version.mak
	@$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(TRIAS_VERSION) \
		$(TRIAS_RELEASE) \
		$(COMPANYNAME) \
			res\GPSstrt.tpl res\GPSstr.rc
	@echo $@

