# Generieren der Versionsinfo's für TRIASIGM.EXT

!include "$(TRIASINCLUDE)/triasver.mak"

# Generierungsdatum (yymmdd) und Version
DATE = 040609
VERSION = 5
RELEASE = 10
BUILD = 079

COPYRIGHT = KK$(DATE)

PNAME = $(TRIAS_PNAME) 
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = kompias
DEF = $(NAME).def

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(NAME).rcv
	@del $(DEF)
	@del versio32.h

formake:	$(DEF) $(NAME).rcv versio32.h 

# Personalisierungsinformation
$(NAME).rcv:	$(NAME)v.tpl kompak36.mak 
	$(REPLACE) \
		$(VERSION) \
		$(RELEASE) \
		$(BUILD) \
		$(COPYRIGHT) \
		$(PNAME) \
		$(PADDRESS) \
		$(TRIAS_VERSION) \
		$(TRIAS_RELEASE) \
			$(NAME)v.tpl $(NAME).rcv

$(DEF):		$(NAME).tpl kompak36.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) $(NAME).tpl $(DEF)

versio32.h:	versio32.tpl kompak36.mak
	ersetz $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) versio32.tpl versio32.h

