# Genrieren der Versionsinfo's 

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 000107
VERSION = 2
RELEASE = 00
BUILD = 060

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

REPLACE = ersetz
NAME = GdbAsc

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del res\$(NAME).rcv
	@del res\copystr.rc
	@del dbversio.h

formake:	res\$(NAME).rcv res\copystr.rc dbversio.h

# Personalisierungsinformation
res\$(NAME).rcv:	res\$(NAME)v.tpl version.mak
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
			res\$(NAME)v.tpl res\$(NAME).rcv

res\copystr.rc2:	res\copystrt.tpl version.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			res\copystrt.tpl res\copystr.rc2

dbversio.h:	version.tpl version.mak
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
			version.tpl dbversio.h
