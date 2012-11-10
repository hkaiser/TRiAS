# Genrieren der Versionsinfo's 

!include <triasver.mak>

# Generierungsdatum (yymmdd) und Version
DATE = 031214
VERSION = 1
RELEASE = 02
BUILD = 127		# 100: am 22. Juni 2000, 22:47

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

REPLACE = ersetz
NAME = TRiASDBDS

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEinträge Generieren 
new:
	@del res\$(NAME).rcv
	Version.h

formake:	res\$(NAME).rcv Version.h

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

Version.h:	Version.tpl Version.mak
	@$(REPLACE) \
        $(VERSION) \
        $(RELEASE) \
        $(BUILD) \
        $(DATE) \
        $(COMPANYNAME) \
            Version.tpl Version.h
	@echo $@


