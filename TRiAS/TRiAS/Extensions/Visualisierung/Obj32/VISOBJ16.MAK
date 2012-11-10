# Generieren der Versionsinfo's für VISOBJ32.DLL

!include $(TRIASINCLUDE)\triasver.mak

# Generierungsdatum (yymmdd) und Version
DATE = 050104
VERSION = 3
RELEASE = 30
BUILD = 141		#HK000806: 100

COPYRIGHT = HK$(DATE)

PNAME = $(TRIAS_PNAME)
PADDRESS = $(TRIAS_PADDRESS)

STUB = rights
RIGHTS = $(STUB).exe
REPLACE = ersetz
NAME = visobj32
DEF = $(NAME).def

# Alles neubilden
all:	formake 

# -----------------------------------------------------------------------------
# CopyrightEintraege Generieren 
new:
	@del $(NAME).rcv
	@del $(DEF)
	@del defabout.src
	@del versio32.h

formake:	$(DEF) $(NAME).rcv defabout.src versio32.h

# Personalisierungsinformation
obj32\$(NAME).rcv:	obj32\visobj3v.tpl obj32\visobj16.mak
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
			obj32\visobj3v.tpl obj32\$(NAME).rcv

obj32\$(DEF):		obj32\$(NAME).tpl obj32\visobj16.mak
	$(REPLACE) $(VERSION) $(RELEASE) $(BUILD) $(COPYRIGHT) obj32\$(NAME).tpl obj32\$(DEF)

obj32\versio32.h:	obj32\versio32.tpl obj32\visobj16.mak
	$(REPLACE) $(VERSION) $(RELEASE) obj32\versio32.tpl obj32\versio32.h
